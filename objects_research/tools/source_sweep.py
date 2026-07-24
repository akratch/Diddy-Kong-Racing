#!/usr/bin/env python3
"""Parallel source-neighborhood sweeps for func_80017A18.

Candidates are compiled as isolated full translation units, then scored in the
parent process with the exact asm-differ API used by realscore.py.  Generated
sources and objects live only in a validated temporary directory.
"""

import argparse
import concurrent.futures
import itertools
import os
import random
import shutil
import subprocess
import tempfile

import realdiff


FUNC_DECL_END = "\n\n    spF8 = 0;"


def split_declarations(source):
    func_start = source.index("s32 func_80017A18(")
    body_start = source.index("{\n", func_start) + 2
    decl_end = source.index(FUNC_DECL_END, body_start)
    prefix = source[:body_start]
    declarations = source[body_start:decl_end].splitlines(keepends=True)
    suffix = source[decl_end:]
    if not declarations or any(not line.startswith("    ") for line in declarations):
        raise ValueError("unexpected declaration block")
    return prefix, declarations, suffix


def declaration_relocations(source):
    prefix, declarations, suffix = split_declarations(source)
    yield "baseline", source
    for old_index, line in enumerate(declarations):
        remaining = declarations[:old_index] + declarations[old_index + 1 :]
        for new_index in range(len(declarations)):
            if new_index == old_index:
                continue
            moved = remaining[:new_index] + [line] + remaining[new_index:]
            tag = f"move_{old_index:02d}_to_{new_index:02d}_{line.strip()}"
            yield tag, prefix + "".join(moved) + suffix


def edge_carrier_variants(source):
    """Reuse two FP locals that are dead across the edge-plane test."""
    coefficient_names = ("A1", "B1", "C1", "D1")
    donors = ("sum1", "t", "new_var3", "var_f18", "var_f20", "var_f22")
    old_loads = """\
                        sum1 = curPlanes[0];
                        B1 = curPlanes[1];
                        C1 = curPlanes[2];
                        new_var3 = curPlanes[3];
                        if (((((sum1 * x3) + (B1 * y3)) + (C1 * z3)) + new_var3) > 4.0f) {
"""
    if old_loads not in source:
        raise ValueError("edge-plane load block not found")

    declaration_anchor = "    f32 B1;\n    f32 C1;\n"
    if declaration_anchor not in source:
        raise ValueError("edge coefficient declaration anchor not found")

    yield "baseline", source
    for reused_positions in itertools.combinations(range(4), 2):
        declared_positions = tuple(i for i in range(4) if i not in reused_positions)
        for donor_order in itertools.permutations(donors, 2):
            variables = list(coefficient_names)
            for position, donor in zip(reused_positions, donor_order):
                variables[position] = donor
            for declaration_order in (
                declared_positions,
                tuple(reversed(declared_positions)),
            ):
                declarations = "".join(
                    f"    f32 {coefficient_names[position]};\n"
                    for position in declaration_order
                )
                loads = "".join(
                    f"                        {variable} = curPlanes[{position}];\n"
                    for position, variable in enumerate(variables)
                )
                expression = (
                    f"                        if ((((({variables[0]} * x3) + "
                    f"({variables[1]} * y3)) + ({variables[2]} * z3)) + "
                    f"{variables[3]}) > 4.0f) {{\n"
                )
                candidate = source.replace(
                    declaration_anchor, declarations, 1
                ).replace(old_loads, loads + expression, 1)
                tag = (
                    f"reuse_{coefficient_names[reused_positions[0]]}_"
                    f"{coefficient_names[reused_positions[1]]}_as_"
                    f"{donor_order[0]}_{donor_order[1]}_decl_"
                    + "_".join(coefficient_names[i] for i in declaration_order)
                )
                yield tag, candidate


def balanced_edge_carrier_variants(source):
    """Reuse three coefficient locals and add one dead declaration back."""
    coefficient_names = ("A1", "B1", "C1", "D1")
    donors = ("sum1", "t", "new_var3", "var_f18", "var_f20", "var_f22")
    old_loads = """\
                        sum1 = curPlanes[0];
                        B1 = curPlanes[1];
                        C1 = curPlanes[2];
                        new_var3 = curPlanes[3];
                        if (((((sum1 * x3) + (B1 * y3)) + (C1 * z3)) + new_var3) > 4.0f) {
"""
    declaration_anchor = "    f32 B1;\n    f32 C1;\n"
    if old_loads not in source or declaration_anchor not in source:
        raise ValueError("balanced edge carrier anchors not found")
    yield "baseline", source
    for declared_position in range(4):
        reused_positions = tuple(
            position for position in range(4) if position != declared_position
        )
        for donor_order in itertools.permutations(donors, 3):
            variables = list(coefficient_names)
            for position, donor in zip(reused_positions, donor_order):
                variables[position] = donor
            for phantom_first in (False, True):
                declared = f"    f32 {coefficient_names[declared_position]};\n"
                phantom = "    f32 edgePhantom;\n"
                declarations = (
                    phantom + declared if phantom_first else declared + phantom
                )
                loads = "".join(
                    f"                        {variable} = curPlanes[{position}];\n"
                    for position, variable in enumerate(variables)
                )
                expression = (
                    f"                        if ((((({variables[0]} * x3) + "
                    f"({variables[1]} * y3)) + ({variables[2]} * z3)) + "
                    f"{variables[3]}) > 4.0f) {{\n"
                )
                candidate = source.replace(
                    declaration_anchor, declarations, 1
                ).replace(old_loads, loads + expression, 1)
                tag = (
                    f"balanced_edge_decl_{coefficient_names[declared_position]}_"
                    f"donors_{'_'.join(donor_order)}_"
                    f"phantomfirst_{int(phantom_first)}"
                )
                yield tag, candidate


def balanced_edge_phantom_relocations(source):
    """Relocate the phantom for the best three-carrier topology."""
    old_loads = """\
                        sum1 = curPlanes[0];
                        B1 = curPlanes[1];
                        C1 = curPlanes[2];
                        new_var3 = curPlanes[3];
                        if (((((sum1 * x3) + (B1 * y3)) + (C1 * z3)) + new_var3) > 4.0f) {
"""
    new_loads = """\
                        sum1 = curPlanes[0];
                        B1 = curPlanes[1];
                        t = curPlanes[2];
                        new_var3 = curPlanes[3];
                        if (((((sum1 * x3) + (B1 * y3)) + (t * z3)) + new_var3) > 4.0f) {
"""
    declaration_anchor = "    f32 B1;\n    f32 C1;\n"
    if old_loads not in source or declaration_anchor not in source:
        raise ValueError("balanced edge phantom anchors not found")
    transformed = source.replace(
        declaration_anchor, "    f32 B1;\n", 1
    ).replace(old_loads, new_loads, 1)
    prefix, declarations, suffix = split_declarations(transformed)
    yield "balanced_phantom_no_phantom", transformed
    phantom = "    f32 edgePhantom;\n"
    for position in range(len(declarations) + 1):
        moved = declarations[:position] + [phantom] + declarations[position:]
        yield (
            f"balanced_phantom_at_{position:02d}",
            prefix + "".join(moved) + suffix,
        )


def fully_balanced_edge_carrier_variants(source):
    coefficient_names = ("A1", "B1", "C1", "D1")
    donors = ("sum1", "t", "new_var3", "var_f18", "var_f20", "var_f22")
    old_loads = """\
                        sum1 = curPlanes[0];
                        B1 = curPlanes[1];
                        C1 = curPlanes[2];
                        new_var3 = curPlanes[3];
                        if (((((sum1 * x3) + (B1 * y3)) + (C1 * z3)) + new_var3) > 4.0f) {
"""
    declaration_anchor = "    f32 B1;\n    f32 C1;\n"
    if old_loads not in source or declaration_anchor not in source:
        raise ValueError("fully balanced edge anchors not found")
    yield "baseline", source
    declaration_orders = (
        "    f32 edgePhantom1;\n    f32 edgePhantom2;\n",
        "    f32 edgePhantom2;\n    f32 edgePhantom1;\n",
    )
    for donor_order in itertools.permutations(donors, 4):
        loads = "".join(
            f"                        {variable} = curPlanes[{position}];\n"
            for position, variable in enumerate(donor_order)
        )
        expression = (
            f"                        if ((((({donor_order[0]} * x3) + "
            f"({donor_order[1]} * y3)) + ({donor_order[2]} * z3)) + "
            f"{donor_order[3]}) > 4.0f) {{\n"
        )
        for declaration_index, declarations in enumerate(declaration_orders):
            candidate = source.replace(
                declaration_anchor, declarations, 1
            ).replace(old_loads, loads + expression, 1)
            yield (
                f"fully_balanced_{'_'.join(donor_order)}_"
                f"declorder_{declaration_index}",
                candidate,
            )


def head_permutations(source):
    first = """\
        x1 = targetPointsX[i];
        y1 = targetPointsY[i];
        z1 = targetPointsZ[i];
"""
    movable = (
        "        var_f22 = originPointsZ[i];\n",
        "        radius = collisionRadii[i] * scale;\n",
        "        j = arg0->collisionFacetCount;\n",
        "        var_f20 = ((0, originPointsY))[i];\n",
        "        var_f18 = originPointsX[i];\n",
        "        counter = 0;\n",
    )
    first_pos = source.find(first)
    end_anchor = "        var_f18 = var_f18;\n"
    if first_pos < 0:
        raise ValueError("outer-loop fixed head block not found")
    movable_start = first_pos + len(first)
    movable_end = source.find(end_anchor, movable_start)
    if movable_end < 0:
        raise ValueError("outer-loop head end not found")
    current_movable = source[movable_start:movable_end]
    current_lines = tuple(current_movable.splitlines(keepends=True))
    if sorted(current_lines) != sorted(movable):
        raise ValueError("outer-loop head has unexpected statements")
    old = first + current_movable
    yield "baseline", source
    for order in itertools.permutations(range(len(movable))):
        tag = "head_" + "_".join(str(index) for index in order)
        yield tag, source.replace(
            old, first + "".join(movable[index] for index in order), 1
        )


def origin_x_pointer_variants(source):
    head = "        var_f18 = originPointsX[i];\n"
    if source.count(head) != 1:
        raise ValueError("origin X head load not found uniquely")
    before, after = source.split(head, 1)
    later_spellings = (
        "originPointsX[-1]",
        "*(originPointsX - 1)",
        "*(originPointsX + -1)",
        "originPointsX[0 - 1]",
    )
    head_spellings = (
        "        var_f18 = *originPointsX++;\n",
        "        var_f18 = *(originPointsX++);\n",
        "        var_f18 = *originPointsX;\n        originPointsX++;\n",
        "        var_f18 = originPointsX[0];\n        originPointsX++;\n",
    )
    yield "baseline", source
    for head_index, head_spelling in enumerate(head_spellings):
        for later_index, later_spelling in enumerate(later_spellings):
            replaced = after.replace("originPointsX[i]", later_spelling)
            tag = f"origin_x_ptr_head{head_index}_later{later_index}"
            yield tag, before + head_spelling + replaced


def origin_pointer_subset_variants(source):
    axes = (
        (
            "x",
            "        var_f18 = originPointsX[i];\n",
            "        var_f18 = *originPointsX++;\n",
            "originPointsX[i]",
            "originPointsX[-1]",
        ),
        (
            "y",
            "        var_f20 = ((0, originPointsY))[i];\n",
            "        var_f20 = *((0, originPointsY++));\n",
            "originPointsY[i]",
            "originPointsY[-1]",
        ),
        (
            "z",
            "        var_f22 = originPointsZ[i];\n",
            "        var_f22 = *originPointsZ++;\n",
            "originPointsZ[i]",
            "originPointsZ[-1]",
        ),
    )
    if any(source.count(head) != 1 for _, head, _, _, _ in axes):
        raise ValueError("origin pointer subset head anchor missing")
    yield "baseline", source
    for mask in range(1, 8):
        candidate = source
        tags = []
        for index, (name, head, replacement, later, later_replacement) in enumerate(axes):
            if mask & (1 << index):
                candidate = candidate.replace(head, replacement, 1)
                candidate = candidate.replace(later, later_replacement)
                tags.append(name)
        yield "origin_pointer_subset_" + "".join(tags), candidate


def origin_x_increment_placement_variants(source):
    head = "        var_f18 = originPointsX[i];\n"
    load = "        var_f18 = *originPointsX;\n"
    anchors = (
        "        var_f18 = *originPointsX;\n",
        "        radius = collisionRadii[i] * scale;\n",
        "        j = arg0->collisionFacetCount;\n",
        "        var_f20 = ((0, originPointsY))[i];\n",
        "        var_f22 = originPointsZ[i];\n",
        "        counter = 0;\n",
        "        var_f18 = var_f18;\n",
        "        var_f20 = var_f20;\n",
        "        var_f22 = var_f22;\n",
    )
    if source.count(head) != 1:
        raise ValueError("origin X increment placement head missing")
    yield "baseline", source
    loaded = source.replace(head, load, 1).replace(
        "originPointsX[i]", "originPointsX[-1]"
    )
    for index, anchor in enumerate(anchors):
        if loaded.count(anchor) < 1:
            raise ValueError(f"origin X increment placement anchor missing: {anchor}")
        candidate = loaded.replace(
            anchor, anchor + "        originPointsX++;\n", 1
        )
        yield f"origin_x_increment_after_{index}", candidate


def origin_x_copy_layout_variants(source):
    x_variants = origin_x_pointer_variants(source)
    next(x_variants)
    _, x_source = next(x_variants)
    for tag, candidate in origin_copy_layout_variants(x_source):
        yield "origin_x_" + tag, candidate


def empty_probe_variants(source):
    variables = (
        "arg0",
        "arg1",
        "numCollisions",
        "originPointsX",
        "originPointsY",
        "originPointsZ",
        "targetPointsX",
        "targetPointsY",
        "targetPointsZ",
        "collisionRadii",
        "surfaces",
        "planes",
        "i",
        "j",
        "k",
        "ret",
        "counter",
        "spF8",
        "var_s6",
        "redoLoop",
        "curPlanes",
        "node",
    )
    anchors = {
        "preloop": "    for (i = 0; i < arg1; i++) {\n",
        "head": "        curOriginX = var_f18;\n",
        "tail": "        var_s6 <<= 1;\n",
        "final": "    if (!var_f22) { }\n",
    }
    forms = (
        "if ({variable}) {{ }}",
        "if (!{variable}) {{ }}",
        "{variable} = {variable};",
        "{variable} = ({variable} = {variable});",
    )
    yield "baseline", source
    for anchor_name, anchor in anchors.items():
        if source.count(anchor) != 1:
            raise ValueError(f"probe anchor {anchor_name} not found uniquely")
        indent = anchor[: len(anchor) - len(anchor.lstrip())]
        for variable in variables:
            for form_index, form in enumerate(forms):
                statement = indent + form.format(variable=variable) + "\n"
                candidate = source.replace(anchor, statement + anchor, 1)
                yield (
                    f"probe_{anchor_name}_{variable}_form{form_index}",
                    candidate,
                )


def origin_read_variants(source):
    """Choose array/master/saved-copy origins independently at three use sites."""
    main_old = (
        "new_var3 = originPointsY[i];\n"
        "                new_var3 = new_var3;\n"
        "                new_var3 = (((A * originPointsX[i]) + "
        "(B * new_var3)) + (C * originPointsZ[i])) + D;"
    )
    interpolation_old = (
        "x3 = var_f18 + ((x1 - originPointsX[i]) * t);\n"
        "                    y3 = var_f20 + ((y1 - originPointsY[i]) * t);\n"
        "                    z3 = var_f22 + (((z1 - originPointsZ[i]) * t) * 1.0f);"
    )
    restore_old = (
        "x1 = originPointsX[i];\n"
        "                            y1 = originPointsY[i];\n"
        "                            z1 = originPointsZ[i];"
    )
    if not all(old in source for old in (main_old, interpolation_old, restore_old)):
        raise ValueError("origin read site not found")
    choices = {
        "array": (
            "originPointsX[i]",
            "originPointsY[i]",
            "originPointsZ[i]",
        ),
        "master": ("var_f18", "var_f20", "var_f22"),
        "copy": ("curOriginX", "curOriginY", "curOriginZ"),
    }
    yield "baseline", source
    for main_name, interpolation_name, restore_name in itertools.product(
        choices, repeat=3
    ):
        if (main_name, interpolation_name, restore_name) == (
            "array",
            "array",
            "array",
        ):
            continue
        mx, my, mz = choices[main_name]
        ix, iy, iz = choices[interpolation_name]
        rx, ry, rz = choices[restore_name]
        main_new = (
            f"new_var3 = {my};\n"
            f"                new_var3 = new_var3;\n"
            f"                new_var3 = (((A * {mx}) + (B * new_var3)) + "
            f"(C * {mz})) + D;"
        )
        interpolation_new = (
            f"x3 = var_f18 + ((x1 - {ix}) * t);\n"
            f"                    y3 = var_f20 + ((y1 - {iy}) * t);\n"
            f"                    z3 = var_f22 + (((z1 - {iz}) * t) * 1.0f);"
        )
        restore_new = (
            f"x1 = {rx};\n"
            f"                            y1 = {ry};\n"
            f"                            z1 = {rz};"
        )
        candidate = (
            source.replace(main_old, main_new, 1)
            .replace(interpolation_old, interpolation_new, 1)
            .replace(restore_old, restore_new, 1)
        )
        yield (
            f"origin_reads_main_{main_name}_interp_{interpolation_name}_"
            f"restore_{restore_name}",
            candidate,
        )


def _partitioned_sum(variable, terms, mask, indent):
    groups = []
    current = []
    for index, term in enumerate(terms):
        current.append(term)
        if index == len(terms) - 1 or (mask & (1 << index)):
            groups.append(current)
            current = []
    lines = []
    for index, group in enumerate(groups):
        expression = " + ".join(group)
        if index == 0:
            lines.append(f"{indent}{variable} = {expression};\n")
        else:
            lines.append(f"{indent}{variable} = {variable} + {expression};\n")
    return "".join(lines)


def local_chain_variants(source):
    """Search statement partitions after switching the origin dot to locals."""
    old_chain = """\
                sum2 = (((A * x1) + (B * y1)) + (C * z1)) + D;
                new_var3 = originPointsY[i];
                new_var3 = new_var3;
                new_var3 = (((A * originPointsX[i]) + (B * new_var3)) + (C * originPointsZ[i])) + D;
                sum1 = new_var3 - radius;
                sum2 -= radius;
"""
    old_restore = """\
                            x1 = originPointsX[i];
                            y1 = originPointsY[i];
                            z1 = originPointsZ[i];
"""
    if old_chain not in source or old_restore not in source:
        raise ValueError("local chain search anchor not found")
    restore = """\
                            x1 = var_f18;
                            y1 = var_f20;
                            z1 = var_f22;
"""
    source = source.replace(old_restore, restore, 1)
    indent = " " * 16
    target_terms = ("A * x1", "B * y1", "C * z1", "D")
    yield "baseline", source.replace(old_chain, old_chain, 1)
    for origin_accumulator in ("sum1", "new_var3"):
        for source_order in ("origin_target", "target_origin"):
            for origin_mask in range(8):
                for target_mask in range(8):
                    for preload_y in (False, True):
                        if preload_y and origin_accumulator != "new_var3":
                            continue
                        for self_assign in (False, True):
                            if self_assign and not preload_y:
                                continue
                            origin_y = "new_var3" if preload_y else "var_f20"
                            origin_terms = (
                                "A * var_f18",
                                f"B * {origin_y}",
                                "C * var_f22",
                                "D",
                            )
                            origin_prefix = ""
                            if preload_y:
                                origin_prefix = (
                                    f"{indent}new_var3 = var_f20;\n"
                                    + (
                                        f"{indent}new_var3 = new_var3;\n"
                                        if self_assign
                                        else ""
                                    )
                                )
                            origin_code = origin_prefix + _partitioned_sum(
                                origin_accumulator,
                                origin_terms,
                                origin_mask,
                                indent,
                            )
                            if origin_accumulator == "sum1":
                                origin_code += f"{indent}sum1 -= radius;\n"
                            else:
                                origin_code += (
                                    f"{indent}sum1 = new_var3 - radius;\n"
                                )
                            target_code = _partitioned_sum(
                                "sum2", target_terms, target_mask, indent
                            )
                            target_code += f"{indent}sum2 -= radius;\n"
                            if source_order == "origin_target":
                                replacement = origin_code + target_code
                            else:
                                replacement = target_code + origin_code
                            candidate = source.replace(old_chain, replacement, 1)
                            tag = (
                                f"local_chain_acc_{origin_accumulator}_"
                                f"order_{source_order}_om{origin_mask}_tm{target_mask}_"
                                f"pre{int(preload_y)}_self{int(self_assign)}"
                            )
                            yield tag, candidate


def natural_main_interleave_variants(source):
    """Interleave the two natural dot-product chains while preserving each order."""
    old_chain = """\
                sum1 = B * y2;
                sum1 = sum1 - spC0 + C * z2 + D + A * x2;
                sum2 = A * x1;
                sum2 = sum2 + B * y1;
                sum2 = sum2 + C * z1;
                sum2 = sum2 + D;
                sum2 = sum2 - spC0;
"""
    if source.count(old_chain) != 1:
        raise ValueError("natural main interleave chain anchor missing")

    axis_names = ("A", "B", "C")
    origin_terms = {"A": "A * x2", "B": "B * y2", "C": "C * z2"}
    target_terms = {"A": "A * x1", "B": "B * y1", "C": "C * z1"}
    for origin_order in itertools.permutations(axis_names):
        origin_steps = [
            f"                sum1 = {origin_terms[origin_order[0]]};\n",
            f"                sum1 += {origin_terms[origin_order[1]]};\n",
            f"                sum1 += {origin_terms[origin_order[2]]};\n",
            "                sum1 += D;\n",
            "                sum1 -= spC0;\n",
        ]
        for target_order in itertools.permutations(axis_names):
            target_steps = [
                f"                sum2 = {target_terms[target_order[0]]};\n",
                f"                sum2 += {target_terms[target_order[1]]};\n",
                f"                sum2 += {target_terms[target_order[2]]};\n",
                "                sum2 += D;\n",
                "                sum2 -= spC0;\n",
            ]
            for origin_positions in itertools.combinations(range(10), 5):
                origin_position_set = set(origin_positions)
                oi = 0
                ti = 0
                lines = []
                bits = []
                for position in range(10):
                    if position in origin_position_set:
                        lines.append(origin_steps[oi])
                        oi += 1
                        bits.append("o")
                    else:
                        lines.append(target_steps[ti])
                        ti += 1
                        bits.append("t")
                yield (
                    "natural_interleave_"
                    + "".join(origin_order)
                    + "_"
                    + "".join(target_order)
                    + "_"
                    + "".join(bits),
                    source.replace(old_chain, "".join(lines), 1),
                )


def natural_main_partition_interleave_variants(
    source,
    origin_order=("A", "B", "C"),
    target_order=("A", "B", "C"),
    mask_pairs=None,
):
    """Interleave every ABCD-radius statement partition of both natural chains."""
    old_chain = """\
                sum1 = B * y2;
                sum1 = sum1 - spC0 + C * z2 + D + A * x2;
                sum2 = A * x1;
                sum2 = sum2 + B * y1;
                sum2 = sum2 + C * z1;
                sum2 = sum2 + D;
                sum2 = sum2 - spC0;
"""
    if source.count(old_chain) != 1:
        raise ValueError("natural partition interleave chain anchor missing")

    def make_chunks(variable, coordinates, order, mask):
        products = {
            "A": f"A * {coordinates[0]}",
            "B": f"B * {coordinates[1]}",
            "C": f"C * {coordinates[2]}",
        }
        terms = (
            (1, products[order[0]]),
            (1, products[order[1]]),
            (1, products[order[2]]),
            (1, "D"),
            (-1, "spC0"),
        )
        groups = [[]]
        for index, term in enumerate(terms):
            groups[-1].append(term)
            if index < 4 and mask & (1 << index):
                groups.append([])

        def expression(group):
            pieces = []
            for index, (sign, term) in enumerate(group):
                if index == 0:
                    pieces.append(("-" if sign < 0 else "") + term)
                else:
                    pieces.append((" - " if sign < 0 else " + ") + term)
            return "".join(pieces)

        lines = []
        for index, group in enumerate(groups):
            expr = expression(group)
            if index == 0:
                lines.append(f"                {variable} = {expr};\n")
            elif group[0][0] < 0:
                lines.append(
                    f"                {variable} = {variable} - {expr[1:]};\n"
                )
            else:
                lines.append(
                    f"                {variable} = {variable} + {expr};\n"
                )
        return lines

    pairs = (
        itertools.product(range(16), repeat=2)
        if mask_pairs is None
        else mask_pairs
    )
    for origin_mask, target_mask in pairs:
        origin_steps = make_chunks(
            "sum1", ("x2", "y2", "z2"), origin_order, origin_mask
        )
        target_steps = make_chunks(
            "sum2", ("x1", "y1", "z1"), target_order, target_mask
        )
        total = len(origin_steps) + len(target_steps)
        for origin_positions in itertools.combinations(
            range(total), len(origin_steps)
        ):
            origin_position_set = set(origin_positions)
            oi = 0
            ti = 0
            lines = []
            bits = []
            for position in range(total):
                if position in origin_position_set:
                    lines.append(origin_steps[oi])
                    oi += 1
                    bits.append("o")
                else:
                    lines.append(target_steps[ti])
                    ti += 1
                    bits.append("t")
            yield (
                "natural_partition_"
                + "".join(origin_order)
                + "_"
                + "".join(target_order)
                + f"_{origin_mask:x}_{target_mask:x}_"
                + "".join(bits),
                source.replace(old_chain, "".join(lines), 1),
            )


def natural_main_top_partition_order_variants(source):
    mask_pairs = (
        (0xA, 0x2),
        (0xE, 0x2),
        (0xA, 0x3),
        (0xA, 0x4),
        (0xA, 0x8),
        (0xE, 0x4),
        (0xE, 0x8),
        (0xA, 0x1),
        (0xE, 0x1),
        (0x8, 0x2),
        (0xC, 0x2),
        (0x9, 0x2),
        (0xD, 0x2),
        (0xB, 0x5),
        (0xF, 0x5),
    )
    for origin_order in itertools.permutations(("A", "B", "C")):
        for target_order in itertools.permutations(("A", "B", "C")):
            yield from natural_main_partition_interleave_variants(
                source, origin_order, target_order, mask_pairs
            )


def natural_outer_head_permutation_variants(source):
    """Permute the seven per-point loads that determine the long-lived FPR webs."""
    lines = (
        "        x1 = arg6[i];\n",
        "        y1 = arg7[i];\n",
        "        z1 = arg8[i];\n",
        "        y3 = arg3[i];\n",
        "        z3 = arg4[i];\n",
        "        sum2 = arg5[i];\n",
        "        spC0 = arg9[i] * argB;\n",
    )
    old = "".join(lines)
    if source.count(old) != 1:
        raise ValueError("natural outer head permutation anchor missing")
    for order in itertools.permutations(range(len(lines))):
        yield (
            "natural_head_" + "".join(str(index) for index in order),
            source.replace(old, "".join(lines[index] for index in order), 1),
        )


def natural_guarded_facet_loop_variants(source):
    """Express the target's facet-count guard and inner do/while directly."""
    old_head = """\
        counter = 0;
        do {
            x2 = y3;
            y2 = z3;
            z2 = sum2;
            redoLoop = FALSE;

            for (j = 0; j < arg0->collisionFacetCount; j++) {
"""
    old_tail = """\
                }
            }
            sum2 = z2;
            z3 = y2;
            y3 = x2;
        } while (redoLoop);
"""
    if source.count(old_head) != 1 or source.count(old_tail) != 1:
        raise ValueError("natural guarded facet loop anchor missing")

    saves = (
        "                x2 = y3;\n",
        "                y2 = z3;\n",
        "                z2 = sum2;\n",
    )
    restores = (
        "                y3 = x2;\n",
        "                z3 = y2;\n",
        "                sum2 = z2;\n",
    )
    conditions = (
        "arg0->collisionFacetCount > 0",
        "0 < arg0->collisionFacetCount",
        "arg0->collisionFacetCount != 0",
    )
    for redo_before_j in (False, True):
        for condition_index, condition in enumerate(conditions):
            for save_order in itertools.permutations(range(3)):
                for restore_order in itertools.permutations(range(3)):
                    top_statements = (
                        "            redoLoop = FALSE;\n"
                        "            j = 0;\n"
                        if redo_before_j
                        else
                        "            j = 0;\n"
                        "            redoLoop = FALSE;\n"
                    )
                    head = (
                        "        counter = 0;\n"
                        "        do {\n"
                        + top_statements
                        + f"            if ({condition}) {{\n"
                        + "".join(saves[index] for index in save_order)
                        + "                do {\n"
                    )
                    tail = (
                        "                }\n"
                        "                    j++;\n"
                        "                } while (j < arg0->collisionFacetCount);\n"
                        + "".join(restores[index] for index in restore_order)
                        + "            }\n"
                        "        } while (redoLoop);\n"
                    )
                    yield (
                        f"natural_guard_redofirst{int(redo_before_j)}_"
                        f"cond{condition_index}_save"
                        + "".join(map(str, save_order))
                        + "_restore"
                        + "".join(map(str, restore_order)),
                        source.replace(old_head, head, 1).replace(
                            old_tail, tail, 1
                        ),
                    )


def natural_scratch_chain_bridge_variants(source):
    """Bring the scratch lineage's successful self-carrier schedule to locals."""
    old_chain = """\
                sum1 = A * x2 + B * y2;
                sum1 = sum1 + C * z2 + D;
                sum2 = A * x1 + B * y1;
                sum1 = sum1 - spC0;
                sum2 = sum2 + C * z1 + D - spC0;
"""
    if source.count(old_chain) != 1:
        raise ValueError("natural scratch chain bridge anchor missing")

    target_forms = (
        (
            "                sum2 = (((A * x1) + (B * y1)) + "
            "(C * z1)) + D;\n"
            "                sum2 -= spC0;\n"
        ),
        (
            "                sum2 = A * x1 + B * y1 + C * z1 + D;\n"
            "                sum2 -= spC0;\n"
        ),
        (
            "                sum2 = A * x1 + B * y1;\n"
            "                sum2 = sum2 + C * z1 + D;\n"
            "                sum2 -= spC0;\n"
        ),
        (
            "                sum2 = A * x1;\n"
            "                sum2 = sum2 + B * y1;\n"
            "                sum2 = sum2 + C * z1;\n"
            "                sum2 = sum2 + D;\n"
            "                sum2 = sum2 - spC0;\n"
        ),
    )
    carriers = ("sum1", "t", "A1", "B1", "C1", "D1")
    for carrier in carriers:
        for self_count in range(4):
            preload = f"                {carrier} = y2;\n"
            preload += (
                f"                {carrier} = {carrier};\n" * self_count
            )
            origin_forms = (
                (
                    preload
                    + f"                {carrier} = (((A * x2) + "
                    f"(B * {carrier})) + (C * z2)) + D;\n"
                    + (
                        f"                sum1 = {carrier} - spC0;\n"
                        if carrier != "sum1"
                        else "                sum1 -= spC0;\n"
                    )
                ),
                (
                    preload
                    + f"                {carrier} = A * x2 + "
                    f"B * {carrier} + C * z2 + D;\n"
                    + (
                        f"                sum1 = {carrier} - spC0;\n"
                        if carrier != "sum1"
                        else "                sum1 -= spC0;\n"
                    )
                ),
                (
                    f"                {carrier} = A * x2 + B * y2;\n"
                    f"                {carrier} = {carrier} + C * z2 + D;\n"
                    + (
                        f"                sum1 = {carrier} - spC0;\n"
                        if carrier != "sum1"
                        else "                sum1 -= spC0;\n"
                    )
                ),
            )
            for origin_index, origin in enumerate(origin_forms):
                for target_index, target in enumerate(target_forms):
                    for source_order in ("origin_target", "target_origin"):
                        replacement = (
                            origin + target
                            if source_order == "origin_target"
                            else target + origin
                        )
                        yield (
                            f"natural_scratch_carrier_{carrier}_"
                            f"self{self_count}_origin{origin_index}_"
                            f"target{target_index}_{source_order}",
                            source.replace(old_chain, replacement, 1),
                        )


def natural_dead_accumulator_variants(source):
    """Reuse locals dead at the plane chains as alternate SSA accumulators."""
    old_chain = """\
                sum1 = A * x2 + B * y2;
                sum1 = sum1 + C * z2 + D;
                sum2 = A * x1 + B * y1;
                sum1 = sum1 - spC0;
                sum2 = sum2 + C * z1 + D - spC0;
"""
    if source.count(old_chain) != 1:
        raise ValueError("natural dead accumulator anchor missing")

    carriers = ("sum1", "sum2", "t", "A1", "B1", "C1", "D1", "x3", "y3", "z3")
    for origin_carrier in carriers:
        for target_carrier in carriers:
            if target_carrier == origin_carrier:
                continue
            origin_steps = (
                f"                {origin_carrier} = A * x2 + B * y2;\n",
                f"                {origin_carrier} = {origin_carrier} + C * z2 + D;\n",
                f"                sum1 = {origin_carrier} - spC0;\n",
            )
            target_steps = (
                f"                {target_carrier} = A * x1 + B * y1;\n",
                f"                sum2 = {target_carrier} + C * z1 + D - spC0;\n",
            )
            for origin_positions in itertools.combinations(range(5), 3):
                origin_position_set = set(origin_positions)
                oi = 0
                ti = 0
                lines = []
                bits = []
                for position in range(5):
                    if position in origin_position_set:
                        lines.append(origin_steps[oi])
                        oi += 1
                        bits.append("o")
                    else:
                        lines.append(target_steps[ti])
                        ti += 1
                        bits.append("t")
                yield (
                    f"natural_acc_o{origin_carrier}_t{target_carrier}_"
                    + "".join(bits),
                    source.replace(old_chain, "".join(lines), 1),
                )


def natural_self_probe_variants(source):
    """Probe optimizer lifetime splits with otherwise dead self assignments."""
    anchors = (
        "                A = planes[4 * triIndex + 0];\n",
        "                sum1 = A * x2 + B * y2;\n",
        "                if (sum1 >= -0.1 && sum2 < -0.1) {\n",
    )
    variables = (
        "x1",
        "y1",
        "z1",
        "x2",
        "y2",
        "z2",
        "A",
        "B",
        "C",
        "D",
        "sum1",
        "sum2",
        "t",
        "A1",
        "B1",
        "C1",
        "D1",
        "x3",
        "y3",
        "z3",
    )
    if any(source.count(anchor) != 1 for anchor in anchors):
        raise ValueError("natural self probe anchor missing")
    yield "baseline", source
    for anchor_index, anchor in enumerate(anchors):
        indent = anchor[: len(anchor) - len(anchor.lstrip())]
        for variable in variables:
            forms = (
                f"{variable} = {variable};",
                f"{variable} = ({variable} = {variable});",
                f"if ({variable}) {{ }}",
                f"if (!{variable}) {{ }}",
            )
            for form_index, form in enumerate(forms):
                probe = indent + form + "\n"
                yield (
                    f"natural_probe_a{anchor_index}_{variable}_f{form_index}",
                    source.replace(anchor, probe + anchor, 1),
                )
        for left_index, right_index in itertools.combinations(
            range(len(variables)), 2
        ):
            left = variables[left_index]
            right = variables[right_index]
            probe = (
                indent
                + f"{left} = {left};\n"
                + indent
                + f"{right} = {right};\n"
            )
            yield (
                f"natural_probe_a{anchor_index}_{left}_{right}_pair",
                source.replace(anchor, probe + anchor, 1),
            )


def natural_expression_tree_variants(source):
    """Enumerate parenthesized dot-product trees, including radius placement."""
    old_chain = """\
                sum1 = A * x2 + B * y2;
                sum1 = sum1 + C * z2 + D;
                sum2 = A * x1 + B * y1;
                sum1 = sum1 - spC0;
                sum2 = sum2 + C * z1 + D - spC0;
"""
    if source.count(old_chain) != 1:
        raise ValueError("natural expression tree anchor missing")

    def trees(terms, operators):
        if len(terms) == 1:
            return (terms[0],)
        results = []
        for split in range(1, len(terms)):
            left_terms = terms[:split]
            right_terms = terms[split:]
            left_operators = operators[: split - 1]
            right_operators = operators[split:]
            operator = operators[split - 1]
            for left in trees(left_terms, left_operators):
                for right in trees(right_terms, right_operators):
                    results.append(f"({left} {operator} {right})")
        return tuple(results)

    def chain_forms(variable, coordinates):
        products = (
            f"A * {coordinates[0]}",
            f"B * {coordinates[1]}",
            f"C * {coordinates[2]}",
            "D",
        )
        forms = []
        for expression in trees(
            products + ("spC0",), ("+", "+", "+", "-")
        ):
            forms.append(
                (f"                {variable} = {expression};\n",)
            )
        for expression in trees(products, ("+", "+", "+")):
            forms.append(
                (
                    f"                {variable} = {expression};\n",
                    f"                {variable} = {variable} - spC0;\n",
                )
            )
        return tuple(forms)

    origin_forms = chain_forms("sum1", ("x2", "y2", "z2"))
    target_forms = chain_forms("sum2", ("x1", "y1", "z1"))
    seen = set()
    for origin_index, origin_steps in enumerate(origin_forms):
        for target_index, target_steps in enumerate(target_forms):
            total = len(origin_steps) + len(target_steps)
            for origin_positions in itertools.combinations(
                range(total), len(origin_steps)
            ):
                origin_position_set = set(origin_positions)
                oi = 0
                ti = 0
                lines = []
                bits = []
                for position in range(total):
                    if position in origin_position_set:
                        lines.append(origin_steps[oi])
                        oi += 1
                        bits.append("o")
                    else:
                        lines.append(target_steps[ti])
                        ti += 1
                        bits.append("t")
                replacement = "".join(lines)
                if replacement in seen:
                    continue
                seen.add(replacement)
                yield (
                    f"natural_tree_o{origin_index:02d}_t{target_index:02d}_"
                    + "".join(bits),
                    source.replace(old_chain, replacement, 1),
                )


def natural_origin_save_placement_variants(source):
    old_head = """\
        counter = 0;
        do {
            redoLoop = FALSE;
            z2 = sum2;
            y2 = z3;
            x2 = y3;
"""
    old_bottom = """\
            sum2 = z2;
            z3 = y2;
            y3 = x2;
"""
    if source.count(old_head) != 1 or source.count(old_bottom) != 1:
        raise ValueError("natural origin save placement anchor missing")

    saves = (
        "            x2 = y3;\n",
        "            y2 = z3;\n",
        "            z2 = sum2;\n",
    )
    restores = (
        "            y3 = x2;\n",
        "            z3 = y2;\n",
        "            sum2 = z2;\n",
    )
    yield "baseline", source
    for placement in ("outside", "before_redo", "after_redo"):
        for save_order in itertools.permutations(range(3)):
            ordered_saves = "".join(saves[index] for index in save_order)
            if placement == "outside":
                head = (
                    "        counter = 0;\n"
                    + ordered_saves.replace("            ", "        ")
                    + "        do {\n"
                    + "            redoLoop = FALSE;\n"
                )
            elif placement == "before_redo":
                head = (
                    "        counter = 0;\n"
                    "        do {\n"
                    + ordered_saves
                    + "            redoLoop = FALSE;\n"
                )
            else:
                head = (
                    "        counter = 0;\n"
                    "        do {\n"
                    "            redoLoop = FALSE;\n"
                    + ordered_saves
                )
            for restore_order in itertools.permutations(range(3)):
                bottom = "".join(restores[index] for index in restore_order)
                yield (
                    f"natural_save_{placement}_"
                    + "".join(map(str, save_order))
                    + "_restore_"
                    + "".join(map(str, restore_order)),
                    source.replace(old_head, head, 1).replace(
                        old_bottom, bottom, 1
                    ),
                )


def natural_feature_bridge_variants(source):
    """Transplant the near-match edge/control features onto the natural base."""
    edge_declaration = "    f32 A1, B1, C1, D1;\n"
    edge_block = """\
                    for (k = 0; k < 3 && var_a2 == TRUE; k++) {
                        closestTri = node->edgeBisectorPlane[k];

                        A1 = planes[4 * closestTri + 0];
                        B1 = planes[4 * closestTri + 1];
                        C1 = planes[4 * closestTri + 2];
                        D1 = planes[4 * closestTri + 3];

                        t = A1 * x3;
                        t = t + B1 * y3 + C1 * z3 + D1;
                        if (t > 4.0f) {
                            var_a2 = FALSE;
                        }

                    }
"""
    stores = """\
                        arg6[i] = x1;
                        arg7[i] = y1;
                        arg8[i] = z1;
                        argA[i] = 0;
"""
    if any(
        source.count(anchor) != 1
        for anchor in (edge_declaration, edge_block, stores, "    u32 var_a2;\n")
    ):
        raise ValueError("natural feature bridge anchor missing")

    yield "baseline", source
    for use_edge in (False, True):
        for use_literal_ret in (False, True):
            for surface_first in (False, True):
                if not (use_edge or use_literal_ret or surface_first):
                    continue
                candidate = source
                control_name = "ret" if use_literal_ret else "var_a2"
                if use_edge:
                    candidate = candidate.replace(
                        edge_declaration,
                        (
                            "    f32 B1;\n"
                            "    f32 C1;\n"
                            "    f32 *curPlanes;\n"
                            "    f32 new_var3;\n"
                        ),
                        1,
                    )
                    candidate = candidate.replace(
                        edge_block,
                        f"""\
                    for (k = 0; (k < 3) && ({control_name} == 1); k++) {{
                        triIndex = node->edgeBisectorPlane[k] & 0xFFFFFFFFFFFFFFFF;
                        curPlanes = planes;
                        curPlanes += ((triIndex * 4) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF;
                        sum1 = curPlanes[0];
                        B1 = curPlanes[1];
                        C1 = curPlanes[2];
                        new_var3 = curPlanes[3];
                        if (((((sum1 * x3) + (B1 * y3)) + (C1 * z3)) + new_var3) > 4.0f) {{
                            {control_name} = 0;
                        }}
                    }}
""",
                        1,
                    )
                if use_literal_ret:
                    candidate = candidate.replace(
                        "    u32 var_a2;\n", "    s32 ret;\n", 1
                    )
                    candidate = candidate.replace("var_a2", "ret")
                    candidate = candidate.replace("ret = TRUE;", "ret = 1;")
                    candidate = candidate.replace("ret = FALSE;", "ret = 0;")
                    candidate = candidate.replace("ret == TRUE", "ret == 1")
                if surface_first:
                    candidate = candidate.replace(
                        stores,
                        (
                            "                        argA[i] = 0;\n"
                            "                        arg6[i] = x1;\n"
                            "                        arg7[i] = y1;\n"
                            "                        arg8[i] = z1;\n"
                        ),
                        1,
                    )
                yield (
                    f"natural_bridge_edge{int(use_edge)}_"
                    f"ret{int(use_literal_ret)}_"
                    f"surface{int(surface_first)}",
                    candidate,
                )


def natural_edge_reuse_variants(source):
    edge_declaration = "    f32 A1, B1, C1, D1;\n"
    edge_block = """\
                    for (k = 0; k < 3 && var_a2 == TRUE; k++) {
                        closestTri = node->edgeBisectorPlane[k];

                        A1 = planes[4 * closestTri + 0];
                        B1 = planes[4 * closestTri + 1];
                        C1 = planes[4 * closestTri + 2];
                        D1 = planes[4 * closestTri + 3];

                        t = A1 * x3;
                        t = t + B1 * y3 + C1 * z3 + D1;
                        if (t > 4.0f) {
                            var_a2 = FALSE;
                        }

                    }
"""
    if source.count(edge_declaration) != 1 or source.count(edge_block) != 1:
        raise ValueError("natural edge reuse anchor missing")

    names = ("B1", "C1", "new_var3", "edgePad")
    load_lines = {
        "A": "                        sum1 = planes[4 * closestTri + 0];\n",
        "B": "                        B1 = planes[4 * closestTri + 1];\n",
        "C": "                        C1 = planes[4 * closestTri + 2];\n",
        "D": "                        new_var3 = planes[4 * closestTri + 3];\n",
    }
    yield "baseline", source
    for declaration_order in itertools.permutations(names):
        declarations = "".join(
            f"    f32 {name};\n" for name in declaration_order
        )
        declared = source.replace(edge_declaration, declarations, 1)
        for load_order in itertools.permutations("ABCD"):
            loads = "".join(load_lines[name] for name in load_order)
            for chain_mode in ("one", "split"):
                if chain_mode == "one":
                    chain = """\
                        if (((((sum1 * x3) + (B1 * y3)) + (C1 * z3)) + new_var3) > 4.0f) {
"""
                else:
                    chain = """\
                        t = sum1 * x3;
                        t = t + B1 * y3 + C1 * z3 + new_var3;
                        if (t > 4.0f) {
"""
                block = f"""\
                    for (k = 0; k < 3 && var_a2 == TRUE; k++) {{
                        closestTri = node->edgeBisectorPlane[k];
{loads}
{chain}                            var_a2 = FALSE;
                        }}

                    }}
"""
                yield (
                    "natural_edge_reuse_decl_"
                    + "".join(name[0] for name in declaration_order)
                    + "_load_"
                    + "".join(load_order)
                    + "_"
                    + chain_mode,
                    declared.replace(edge_block, block, 1),
                )


def natural_edge_index_variants(source):
    declaration = "    s32 closestTri;\n"
    edge_block = """\
                    for (k = 0; k < 3 && var_a2 == TRUE; k++) {
                        closestTri = node->edgeBisectorPlane[k];

                        A1 = planes[4 * closestTri + 0];
                        B1 = planes[4 * closestTri + 1];
                        C1 = planes[4 * closestTri + 2];
                        D1 = planes[4 * closestTri + 3];

                        t = A1 * x3;
                        t = t + B1 * y3 + C1 * z3 + D1;
                        if (t > 4.0f) {
                            var_a2 = FALSE;
                        }

                    }
"""
    if source.count(declaration) != 1 or source.count(edge_block) != 1:
        raise ValueError("natural edge index anchor missing")

    yield "baseline", source
    for type_name in ("s32", "u32", "s16", "u16"):
        declared = source.replace(
            declaration, f"    {type_name} closestTri;\n", 1
        )
        for assignment in (
            "node->edgeBisectorPlane[k]",
            "node->edgeBisectorPlane[k] & 0xFFFFFFFF",
            "node->edgeBisectorPlane[k] & 0xFFFFFFFFFFFFFFFF",
            "(u16) node->edgeBisectorPlane[k]",
        ):
            for index_expression in (
                "4 * closestTri",
                "closestTri * 4",
                "(closestTri * 4) & 0xFFFFFFFF",
                "((closestTri * 4) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF",
            ):
                block = f"""\
                    for (k = 0; k < 3 && var_a2 == TRUE; k++) {{
                        closestTri = {assignment};

                        A1 = planes[{index_expression} + 0];
                        B1 = planes[{index_expression} + 1];
                        C1 = planes[{index_expression} + 2];
                        D1 = planes[{index_expression} + 3];

                        t = A1 * x3;
                        t = t + B1 * y3 + C1 * z3 + D1;
                        if (t > 4.0f) {{
                            var_a2 = FALSE;
                        }}

                    }}
"""
                yield (
                    f"natural_edge_index_{type_name}_"
                    f"a{assignment.replace(' ', '')}_"
                    f"i{index_expression.replace(' ', '')}",
                    declared.replace(edge_block, block, 1),
                )


def origin_coalescing_variants(source):
    """Probe one-home origin webs while leaving the successful array reads."""
    axes = (
        ("X", "curOriginX", "var_f18"),
        ("Y", "curOriginY", "var_f20"),
        ("Z", "curOriginZ", "var_f22"),
    )
    forms = ("distinct", "self", "none", "save_only", "restore_only")
    yield "baseline", source
    for choices in itertools.product(forms, repeat=3):
        if choices == ("distinct",) * 3:
            continue
        candidate = source
        for (_, copy, master), form in zip(axes, choices):
            save = f"        {copy} = {master};\n"
            restore = f"            {master} = {copy};\n"
            if candidate.count(save) != 1 or candidate.count(restore) != 1:
                raise ValueError(f"origin coalescing anchors missing for {copy}")
            if form == "distinct":
                new_save, new_restore = save, restore
            elif form == "self":
                new_save = f"        {master} = {master};\n"
                new_restore = f"            {master} = {master};\n"
            elif form == "none":
                new_save = new_restore = ""
            elif form == "save_only":
                new_save, new_restore = save, f"            {master} = {master};\n"
            elif form == "restore_only":
                new_save, new_restore = f"        {master} = {master};\n", restore
            else:
                raise AssertionError(form)
            candidate = candidate.replace(save, new_save, 1).replace(
                restore, new_restore, 1
            )
        yield "origin_coalesce_" + "_".join(choices), candidate


def origin_save_placement_variants(source):
    old_pre = """\
        var_f18 = var_f18;
        var_f20 = var_f20;
        var_f22 = var_f22;
"""
    do_anchor = """\
        do {
            redoLoop = 0;
"""
    restore_lines = (
        "            var_f22 = curOriginZ;\n",
        "            var_f20 = curOriginY;\n",
        "            var_f18 = curOriginX;\n",
    )
    old_restore = "".join(restore_lines)
    if old_pre not in source or do_anchor not in source or old_restore not in source:
        raise ValueError("origin save placement anchors not found")
    save_lines = (
        "            curOriginX = var_f18;\n",
        "            curOriginY = var_f20;\n",
        "            curOriginZ = var_f22;\n",
    )
    yield "baseline", source
    for placement in ("before_redo", "after_redo"):
        for save_order in itertools.permutations(range(3)):
            for restore_order in itertools.permutations(range(3)):
                saves = "".join(save_lines[index] for index in save_order)
                restores = "".join(
                    restore_lines[index] for index in restore_order
                )
                if placement == "before_redo":
                    replacement = "        do {\n" + saves + "            redoLoop = 0;\n"
                else:
                    replacement = do_anchor + saves
                candidate = (
                    source.replace(old_pre, "", 1)
                    .replace(do_anchor, replacement, 1)
                    .replace(old_restore, restores, 1)
                )
                tag = (
                    f"origin_save_{placement}_"
                    + "".join(str(i) for i in save_order)
                    + "_restore_"
                    + "".join(str(i) for i in restore_order)
                )
                yield tag, candidate


def origin_restore_expression_variants(source):
    axes = (
        ("curOriginX", "var_f18"),
        ("curOriginY", "var_f20"),
        ("curOriginZ", "var_f22"),
    )
    forms = {
        "copy": lambda copy, master: copy,
        "self": lambda copy, master: master,
        "volatile": lambda copy, master: f"*(volatile f32 *) &{master}",
        "pointer": lambda copy, master: f"*(f32 *) &{master}",
        "redo_self_copy": lambda copy, master: (
            f"redoLoop ? {master} : {copy}"
        ),
        "redo_copy_self": lambda copy, master: (
            f"redoLoop ? {copy} : {master}"
        ),
        "counter_self_copy": lambda copy, master: (
            f"counter ? {master} : {copy}"
        ),
        "comma_self": lambda copy, master: f"(0, {master})",
        "plus_zero": lambda copy, master: f"{master} + 0.0f",
        "times_one": lambda copy, master: f"{master} * 1.0f",
    }
    yield "baseline", source
    for choices in itertools.product(forms, repeat=3):
        if choices == ("copy",) * 3:
            continue
        candidate = source
        for (copy, master), form_name in zip(axes, choices):
            old = f"            {master} = {copy};\n"
            if candidate.count(old) != 1:
                raise ValueError(f"restore expression anchor missing for {master}")
            expression = forms[form_name](copy, master)
            new = f"            {master} = {expression};\n"
            candidate = candidate.replace(old, new, 1)
        yield "origin_restore_" + "_".join(choices), candidate


def origin_bottom_probe_variants(source):
    axes = (
        ("curOriginZ", "var_f22"),
        ("curOriginY", "var_f20"),
        ("curOriginX", "var_f18"),
    )
    old = "".join(
        f"            {master} = {copy};\n" for copy, master in axes
    )
    if old not in source:
        raise ValueError("origin bottom probe anchor not found")

    def action_lines(action, copy, master):
        indent = " " * 12
        copy_line = f"{indent}{master} = {copy};\n"
        self_line = f"{indent}{master} = {master};\n"
        positive = f"{indent}if ({master}) {{ }}\n"
        negative = f"{indent}if (!{master}) {{ }}\n"
        return {
            "copy": copy_line,
            "self": self_line,
            "none": "",
            "probe_pos": positive,
            "probe_neg": negative,
            "self_probe": self_line + negative,
            "copy_probe": copy_line + negative,
            "probe_copy": negative + copy_line,
        }[action]

    actions = (
        "copy",
        "self",
        "none",
        "probe_pos",
        "probe_neg",
        "self_probe",
        "copy_probe",
        "probe_copy",
    )
    yield "baseline", source
    for choices in itertools.product(actions, repeat=3):
        if choices == ("copy",) * 3:
            continue
        replacement = "".join(
            action_lines(action, copy, master)
            for action, (copy, master) in zip(choices, axes)
        )
        yield (
            "origin_bottom_" + "_".join(choices),
            source.replace(old, replacement, 1),
        )


def origin_copy_layout_variants(source):
    prefix, declarations, suffix = split_declarations(source)
    copy_declarations = {
        "f32 curOriginX;",
        "f32 curOriginY;",
        "f32 curOriginZ;",
    }
    if not copy_declarations.issubset(
        {line.strip() for line in declarations}
    ):
        raise ValueError("origin copy declarations not found")
    remaining = [
        line if line.endswith("\n") else line + "\n"
        for line in declarations
        if line.strip() not in copy_declarations
    ]
    old_restore = """\
            var_f22 = curOriginZ;
            var_f20 = curOriginY;
            var_f18 = curOriginX;
"""
    if old_restore not in suffix:
        raise ValueError("origin copy restore block not found")
    yield "baseline", source
    for array_length in (3, 4):
        declaration = f"    f32 curOrigin[{array_length}];\n"
        for position in range(len(remaining) + 1):
            new_declarations = (
                remaining[:position] + [declaration] + remaining[position:]
            )
            for indices in itertools.permutations(range(3)):
                x_index, y_index, z_index = indices
                restore = (
                    f"            var_f22 = curOrigin[{z_index}];\n"
                    f"            var_f20 = curOrigin[{y_index}];\n"
                    f"            var_f18 = curOrigin[{x_index}];\n"
                )
                candidate_suffix = suffix.replace(old_restore, restore, 1)
                yield (
                    f"origin_array_len{array_length}_at{position:02d}_"
                    f"xyz{x_index}{y_index}{z_index}",
                    prefix + "".join(new_declarations) + candidate_suffix,
                )


def origin_copy_oob_variants(source):
    """Tune bottom reload homes with fixed-offset reads from the dead locals."""
    old_restore = """\
            var_f22 = curOriginZ;
            var_f20 = curOriginY;
            var_f18 = curOriginX;
"""
    if old_restore not in source:
        raise ValueError("origin copy OOB restore block not found")

    yield "baseline", source
    expected = (1, -3, -1)
    for deltas in itertools.product(range(-5, 4), repeat=3):
        lines = []
        for copy, master, delta in zip(
            ("curOriginZ", "curOriginY", "curOriginX"),
            ("var_f22", "var_f20", "var_f18"),
            deltas,
        ):
            lines.append(f"            {master} = (&{copy})[{delta}];\n")
        tag = "origin_copy_oob_" + "_".join(
            ("p" if delta >= 0 else "m") + str(abs(delta))
            for delta in deltas
        )
        if deltas == expected:
            tag += "_expected"
        yield tag, source.replace(old_restore, "".join(lines), 1)


def origin_array_save_variants(source):
    """Use one tuned origin array for both the loop-head saves and reloads."""
    prefix, declarations, suffix = split_declarations(source)
    copy_declarations = {
        "f32 curOriginX;",
        "f32 curOriginY;",
        "f32 curOriginZ;",
    }
    remaining = [
        line if line.endswith("\n") else line + "\n"
        for line in declarations
        if line.strip() not in copy_declarations
    ]
    old_pre = """\
        var_f18 = var_f18;
        var_f20 = var_f20;
        var_f22 = var_f22;
"""
    do_anchor = """\
        do {
            redoLoop = 0;
"""
    old_restore = """\
            var_f22 = curOriginZ;
            var_f20 = curOriginY;
            var_f18 = curOriginX;
"""
    origin_chain = """\
                new_var3 = originPointsY[i];
                new_var3 = new_var3;
                new_var3 = (((A * originPointsX[i]) + (B * new_var3)) + (C * originPointsZ[i])) + D;
"""
    interpolation = """\
                    x3 = var_f18 + ((x1 - originPointsX[i]) * t);
                    y3 = var_f20 + ((y1 - originPointsY[i]) * t);
                    z3 = var_f22 + (((z1 - originPointsZ[i]) * t) * 1.0f);
"""
    counter_restore = """\
                            x1 = originPointsX[i];
                            y1 = originPointsY[i];
                            z1 = originPointsZ[i];
"""
    if any(
        anchor not in suffix
        for anchor in (
            old_pre,
            do_anchor,
            old_restore,
            origin_chain,
            interpolation,
            counter_restore,
        )
    ):
        raise ValueError("origin array save anchor missing")

    for position in range(27, min(33, len(remaining) + 1)):
        declaration = "    f32 curOrigin[3];\n"
        new_declarations = (
            remaining[:position] + [declaration] + remaining[position:]
        )
        for indices in itertools.permutations(range(3)):
            x_index, y_index, z_index = indices
            restore = (
                f"            var_f22 = curOrigin[{z_index}];\n"
                f"            var_f20 = curOrigin[{y_index}];\n"
                f"            var_f18 = curOrigin[{x_index}];\n"
            )
            laid_out = prefix + "".join(new_declarations) + suffix.replace(
                old_restore, restore, 1
            )
            save_lines = (
                f"            curOrigin[{x_index}] = var_f18;\n",
                f"            curOrigin[{y_index}] = var_f20;\n",
                f"            curOrigin[{z_index}] = var_f22;\n",
            )
            placements = [("self", (), old_pre, do_anchor)]
            for save_order in itertools.permutations(range(3)):
                saves_pre = "".join(
                    save_lines[index].replace("            ", "        ", 1)
                    for index in save_order
                )
                saves_inner = "".join(save_lines[index] for index in save_order)
                placements.extend(
                    (
                        ("pre_" + "".join(map(str, save_order)), save_order, saves_pre, do_anchor),
                        (
                            "before_" + "".join(map(str, save_order)),
                            save_order,
                            "",
                            "        do {\n" + saves_inner + "            redoLoop = 0;\n",
                        ),
                        (
                            "after_" + "".join(map(str, save_order)),
                            save_order,
                            "",
                            do_anchor + saves_inner,
                        ),
                    )
                )
            for placement, _, pre_replacement, do_replacement in placements:
                placed = laid_out.replace(old_pre, pre_replacement, 1)
                if placement != "self":
                    placed = placed.replace(do_anchor, do_replacement, 1)
                for usage_mask in range(8):
                    candidate = placed
                    if usage_mask & 1:
                        candidate = candidate.replace(
                            origin_chain,
                            f"""\
                new_var3 = curOrigin[{y_index}];
                new_var3 = new_var3;
                new_var3 = (((A * curOrigin[{x_index}]) + (B * new_var3)) + (C * curOrigin[{z_index}])) + D;
""",
                            1,
                        )
                    if usage_mask & 2:
                        candidate = candidate.replace(
                            interpolation,
                            f"""\
                    x3 = curOrigin[{x_index}] + ((x1 - curOrigin[{x_index}]) * t);
                    y3 = curOrigin[{y_index}] + ((y1 - curOrigin[{y_index}]) * t);
                    z3 = curOrigin[{z_index}] + (((z1 - curOrigin[{z_index}]) * t) * 1.0f);
""",
                            1,
                        )
                    if usage_mask & 4:
                        candidate = candidate.replace(
                            counter_restore,
                            f"""\
                            x1 = curOrigin[{x_index}];
                            y1 = curOrigin[{y_index}];
                            z1 = curOrigin[{z_index}];
""",
                            1,
                        )
                    yield (
                        f"origin_array_save_at{position}_"
                        f"xyz{x_index}{y_index}{z_index}_"
                        f"{placement}_use{usage_mask:x}",
                        candidate,
                    )


def origin_copy_scope_variants(source):
    prefix, declarations, suffix = split_declarations(source)
    copy_names = {
        "f32 curOriginX;",
        "f32 curOriginY;",
        "f32 curOriginZ;",
    }
    if not copy_names.issubset({line.strip() for line in declarations}):
        raise ValueError("origin copy scope declarations not found")
    remaining = [
        line if line.endswith("\n") else line + "\n"
        for line in declarations
        if line.strip() not in copy_names
    ]
    source = prefix + "".join(remaining) + suffix
    restore = """\
            var_f22 = curOriginZ;
            var_f20 = curOriginY;
            var_f18 = curOriginX;
"""
    if restore not in source:
        raise ValueError("origin copy scope restore not found")
    do_anchor = """\
        do {
            redoLoop = 0;
"""
    if do_anchor not in source:
        raise ValueError("origin copy scope do anchor not found")
    yield "baseline_without_copy_decls", source
    names = ("curOriginX", "curOriginY", "curOriginZ")
    for order in itertools.permutations(names):
        inline_declarations = "".join(
            f"            f32 {name};\n" for name in order
        )
        for placement in ("restore", "block", "do_top"):
            if placement == "restore":
                candidate = source.replace(
                    restore, inline_declarations + restore, 1
                )
            elif placement == "block":
                block_declarations = "".join(
                    f"                f32 {name};\n" for name in order
                )
                block_restore = restore.replace("            ", "                ")
                candidate = source.replace(
                    restore,
                    "            {\n"
                    + block_declarations
                    + block_restore
                    + "            }\n",
                    1,
                )
            else:
                candidate = source.replace(
                    do_anchor, do_anchor + inline_declarations, 1
                )
            yield (
                f"origin_copy_scope_{placement}_{'_'.join(order)}",
                candidate,
            )


def origin_copy_qualifier_variants(source):
    names = ("curOriginX", "curOriginY", "curOriginZ")
    qualifiers = ("plain", "volatile", "register")
    yield "baseline", source
    for choices in itertools.product(qualifiers, repeat=3):
        if choices == ("plain",) * 3:
            continue
        candidate = source
        for name, qualifier in zip(names, choices):
            old = f"    f32 {name};"
            if candidate.count(old) != 1:
                raise ValueError(f"origin qualifier declaration missing for {name}")
            prefix = "" if qualifier == "plain" else qualifier + " "
            candidate = candidate.replace(
                old, f"    {prefix}f32 {name};", 1
            )
        yield "origin_qualifier_" + "_".join(choices), candidate


def origin_statement_order_variants(source):
    pre_lines = (
        "        var_f18 = var_f18;\n",
        "        var_f20 = var_f20;\n",
        "        var_f22 = var_f22;\n",
    )
    restore_lines = (
        "            var_f22 = curOriginZ;\n",
        "            var_f20 = curOriginY;\n",
        "            var_f18 = curOriginX;\n",
    )
    old_pre = "".join(pre_lines)
    old_restore = "".join(restore_lines)
    if old_pre not in source or old_restore not in source:
        raise ValueError("origin statement order anchors not found")
    yield "baseline", source
    for pre_order in itertools.permutations(range(3)):
        for restore_order in itertools.permutations(range(3)):
            candidate = source.replace(
                old_pre, "".join(pre_lines[i] for i in pre_order), 1
            ).replace(
                old_restore,
                "".join(restore_lines[i] for i in restore_order),
                1,
            )
            yield (
                "origin_statement_pre_"
                + "".join(str(i) for i in pre_order)
                + "_restore_"
                + "".join(str(i) for i in restore_order),
                candidate,
            )


def origin_declaration_permutations(source):
    prefix, declarations, suffix = split_declarations(source)
    names = (
        "f32 curOriginX;",
        "f32 curOriginY;",
        "f32 curOriginZ;",
        "f32 var_f18;",
        "f32 var_f20;",
        "f32 var_f22;",
    )
    stripped = [line.strip() for line in declarations]
    positions = [stripped.index(name) for name in names]
    insertion_position = min(positions)
    remaining = [
        line if line.endswith("\n") else line + "\n"
        for line in declarations
        if line.strip() not in names
    ]
    yield "baseline", source
    for order in itertools.permutations(names):
        ordered = [f"    {name}\n" for name in order]
        new_declarations = (
            remaining[:insertion_position]
            + ordered
            + remaining[insertion_position:]
        )
        yield (
            "origin_declarations_" + "_".join(name.split()[1][:-1] for name in order),
            prefix + "".join(new_declarations) + suffix,
        )


def natural_origin_topology_variants(source):
    """Fuse the origin and interpolated-point lifetimes as seen in the target."""
    declaration_block = """\
    f32 curOriginY;
    f32 curOriginX;
    f32 var_f18;
    f32 var_f20;
    f32 var_f22;
    f32 curOriginZ;
"""
    outer_block = """\
        var_f18 = originPointsX[i];
        radius = collisionRadii[i] * scale;
        j = arg0->collisionFacetCount;
        var_f20 = ((0, originPointsY))[i];
        var_f22 = originPointsZ[i];
        counter = 0;
        var_f18 = var_f18;
        var_f20 = var_f20;
        var_f22 = var_f22;
        do {
            redoLoop = 0;
"""
    origin_chain = """\
                new_var3 = originPointsY[i];
                new_var3 = new_var3;
                new_var3 = (((A * originPointsX[i]) + (B * new_var3)) + (C * originPointsZ[i])) + D;
"""
    interpolation = """\
                    x3 = var_f18 + ((x1 - originPointsX[i]) * t);
                    y3 = var_f20 + ((y1 - originPointsY[i]) * t);
                    z3 = var_f22 + (((z1 - originPointsZ[i]) * t) * 1.0f);
"""
    counter_restore = """\
                            x1 = originPointsX[i];
                            y1 = originPointsY[i];
                            z1 = originPointsZ[i];
"""
    bottom_restore = """\
            var_f22 = curOriginZ;
            var_f20 = curOriginY;
            var_f18 = curOriginX;
"""
    final_probe = "\n    if (!var_f22) { }\n"
    anchors = (
        declaration_block,
        outer_block,
        origin_chain,
        interpolation,
        counter_restore,
        bottom_restore,
        final_probe,
    )
    if any(anchor not in source for anchor in anchors):
        raise ValueError("natural origin topology anchor missing")

    declaration_orders = tuple(itertools.permutations(("x2", "y2", "z2")))
    save_orders = tuple(itertools.permutations(range(3)))
    restore_orders = tuple(itertools.permutations(range(3)))
    save_lines = (
        "            x2 = y3;\n",
        "            y2 = z3;\n",
        "            z2 = sum2;\n",
    )
    restore_lines = (
        "            y3 = x2;\n",
        "            z3 = y2;\n",
        "            sum2 = z2;\n",
    )

    for declaration_order in declaration_orders:
        declarations = "".join(f"    f32 {name};\n" for name in declaration_order)
        declared = source.replace(declaration_block, declarations, 1)
        for save_order in save_orders:
            for restore_order in restore_orders:
                outer = """\
        y3 = originPointsX[i];
        z3 = originPointsY[i];
        sum2 = originPointsZ[i];
        radius = collisionRadii[i] * scale;
        counter = 0;
        do {
            redoLoop = 0;
""" + "".join(save_lines[index] for index in save_order)
                candidate = (
                    declared.replace(outer_block, outer, 1)
                    .replace(
                        origin_chain,
                        """\
                new_var3 = y2;
                new_var3 = new_var3;
                new_var3 = (((A * x2) + (B * new_var3)) + (C * z2)) + D;
""",
                        1,
                    )
                    .replace(
                        interpolation,
                        """\
                    x3 = x2 + ((x1 - x2) * t);
                    y3 = y2 + ((y1 - y2) * t);
                    z3 = z2 + (((z1 - z2) * t) * 1.0f);
""",
                        1,
                    )
                    .replace(
                        counter_restore,
                        """\
                            x1 = x2;
                            y1 = y2;
                            z1 = z2;
""",
                        1,
                    )
                    .replace(
                        bottom_restore,
                        "".join(restore_lines[index] for index in restore_order),
                        1,
                    )
                    .replace(final_probe, "\n", 1)
                )
                yield (
                    "natural_origin_decl_"
                    + "".join(name[-1] for name in declaration_order)
                    + "_save_"
                    + "".join(str(index) for index in save_order)
                    + "_restore_"
                    + "".join(str(index) for index in restore_order),
                    candidate,
                )


def origin_carrier_fusion_variants(source):
    """Fuse origin carriers without replacing the current arithmetic topology."""
    pre_assignments = (
        ("        var_f18 = originPointsX[i];\n", "        y3 = originPointsX[i];\n"),
        (
            "        var_f20 = ((0, originPointsY))[i];\n",
            "        z3 = ((0, originPointsY))[i];\n",
        ),
        ("        var_f22 = originPointsZ[i];\n", "        sum2 = originPointsZ[i];\n"),
    )
    save_assignments = (
        ("        var_f18 = var_f18;\n", "        var_f18 = y3;\n"),
        ("        var_f20 = var_f20;\n", "        var_f20 = z3;\n"),
        ("        var_f22 = var_f22;\n", "        var_f22 = sum2;\n"),
    )
    restore_assignments = (
        ("            var_f18 = curOriginX;\n", "            y3 = var_f18;\n"),
        ("            var_f20 = curOriginY;\n", "            z3 = var_f20;\n"),
        ("            var_f22 = curOriginZ;\n", "            sum2 = var_f22;\n"),
    )
    origin_chain = """\
                new_var3 = originPointsY[i];
                new_var3 = new_var3;
                new_var3 = (((A * originPointsX[i]) + (B * new_var3)) + (C * originPointsZ[i])) + D;
"""
    interpolation = """\
                    x3 = var_f18 + ((x1 - originPointsX[i]) * t);
                    y3 = var_f20 + ((y1 - originPointsY[i]) * t);
                    z3 = var_f22 + (((z1 - originPointsZ[i]) * t) * 1.0f);
"""
    counter_restore = """\
                            x1 = originPointsX[i];
                            y1 = originPointsY[i];
                            z1 = originPointsZ[i];
"""
    final_probe = "\n    if (!var_f22) { }\n"
    anchors = (
        *(old for old, _ in pre_assignments),
        *(old for old, _ in save_assignments),
        *(old for old, _ in restore_assignments),
        origin_chain,
        interpolation,
        counter_restore,
        final_probe,
    )
    if any(anchor not in source for anchor in anchors):
        raise ValueError("origin carrier fusion anchor missing")

    direct_origins = ("originPointsX[i]", "originPointsY[i]", "originPointsZ[i]")
    saved_origins = ("var_f18", "var_f20", "var_f22")
    for fusion_mask in range(8):
        fused = source
        for axis in range(3):
            if fusion_mask & (1 << axis):
                fused = fused.replace(*pre_assignments[axis], 1)
                fused = fused.replace(*save_assignments[axis], 1)
                fused = fused.replace(*restore_assignments[axis], 1)

        for equation_mask in range(8):
            equation_values = tuple(
                saved_origins[axis]
                if equation_mask & (1 << axis)
                else direct_origins[axis]
                for axis in range(3)
            )
            equation = f"""\
                new_var3 = {equation_values[1]};
                new_var3 = new_var3;
                new_var3 = (((A * {equation_values[0]}) + (B * new_var3)) + (C * {equation_values[2]})) + D;
"""
            with_equation = fused.replace(origin_chain, equation, 1)
            for interpolation_mask in range(8):
                interpolation_values = tuple(
                    saved_origins[axis]
                    if interpolation_mask & (1 << axis)
                    else direct_origins[axis]
                    for axis in range(3)
                )
                interpolated = f"""\
                    x3 = var_f18 + ((x1 - {interpolation_values[0]}) * t);
                    y3 = var_f20 + ((y1 - {interpolation_values[1]}) * t);
                    z3 = var_f22 + (((z1 - {interpolation_values[2]}) * t) * 1.0f);
"""
                with_interpolation = with_equation.replace(
                    interpolation, interpolated, 1
                )
                for reset_mask in range(8):
                    reset_values = tuple(
                        saved_origins[axis]
                        if reset_mask & (1 << axis)
                        else direct_origins[axis]
                        for axis in range(3)
                    )
                    reset = f"""\
                            x1 = {reset_values[0]};
                            y1 = {reset_values[1]};
                            z1 = {reset_values[2]};
"""
                    candidate = with_interpolation.replace(
                        counter_restore, reset, 1
                    )
                    tag = (
                        f"origin_carrier_f{fusion_mask:x}_"
                        f"eq{equation_mask:x}_ip{interpolation_mask:x}_"
                        f"reset{reset_mask:x}"
                    )
                    yield tag + "_probe", candidate
                    yield tag + "_no_probe", candidate.replace(final_probe, "\n", 1)


def snapshot_origin_topology_variants(source):
    """Stop using origin pointers in-loop while retaining the near-match graph."""
    copy_declarations = (
        "    f32 curOriginY;\n",
        "    f32 curOriginX;\n",
        "    f32 curOriginZ;\n",
    )
    pre_self = """\
        var_f18 = var_f18;
        var_f20 = var_f20;
        var_f22 = var_f22;
"""
    bottom = """\
            var_f22 = curOriginZ;
            var_f20 = curOriginY;
            var_f18 = curOriginX;
"""
    origin_chain = """\
                new_var3 = originPointsY[i];
                new_var3 = new_var3;
                new_var3 = (((A * originPointsX[i]) + (B * new_var3)) + (C * originPointsZ[i])) + D;
"""
    interpolation = """\
                    x3 = var_f18 + ((x1 - originPointsX[i]) * t);
                    y3 = var_f20 + ((y1 - originPointsY[i]) * t);
                    z3 = var_f22 + (((z1 - originPointsZ[i]) * t) * 1.0f);
"""
    counter_restore = """\
                            x1 = originPointsX[i];
                            y1 = originPointsY[i];
                            z1 = originPointsZ[i];
"""
    final_probe = "\n    if (!var_f22) { }\n"
    if any(
        anchor not in source
        for anchor in (
            *copy_declarations,
            pre_self,
            bottom,
            origin_chain,
            interpolation,
            counter_restore,
            final_probe,
        )
    ):
        raise ValueError("snapshot origin topology anchor missing")

    bottom_forms = {
        "copy": bottom,
        "none": "",
        "self": (
            "            var_f22 = var_f22;\n"
            "            var_f20 = var_f20;\n"
            "            var_f18 = var_f18;\n"
        ),
    }
    for keep_copies in (False, True):
        base = source
        if not keep_copies:
            for declaration in copy_declarations:
                base = base.replace(declaration, "", 1)
        for keep_pre in (False, True):
            with_pre = base if keep_pre else base.replace(pre_self, "", 1)
            for bottom_name, bottom_replacement in bottom_forms.items():
                if not keep_copies and bottom_name == "copy":
                    continue
                with_bottom = with_pre.replace(bottom, bottom_replacement, 1)
                for usage_mask in range(8):
                    candidate = with_bottom
                    if usage_mask & 1:
                        candidate = candidate.replace(
                            origin_chain,
                            """\
                new_var3 = var_f20;
                new_var3 = new_var3;
                new_var3 = (((A * var_f18) + (B * new_var3)) + (C * var_f22)) + D;
""",
                            1,
                        )
                    if usage_mask & 2:
                        candidate = candidate.replace(
                            interpolation,
                            """\
                    x3 = var_f18 + ((x1 - var_f18) * t);
                    y3 = var_f20 + ((y1 - var_f20) * t);
                    z3 = var_f22 + (((z1 - var_f22) * t) * 1.0f);
""",
                            1,
                        )
                    if usage_mask & 4:
                        candidate = candidate.replace(
                            counter_restore,
                            """\
                            x1 = var_f18;
                            y1 = var_f20;
                            z1 = var_f22;
""",
                            1,
                        )
                    tag = (
                        f"snapshot_origin_copies{int(keep_copies)}_"
                        f"pre{int(keep_pre)}_{bottom_name}_use{usage_mask:x}"
                    )
                    yield tag + "_probe", candidate
                    yield tag + "_no_probe", candidate.replace(final_probe, "\n", 1)


def origin_alias_variants(source):
    """Read the loop-bottom origin restore through the masters' own homes."""
    copy_declarations = (
        "    f32 curOriginY;\n",
        "    f32 curOriginX;\n",
        "    f32 curOriginZ;\n",
    )
    restore = """\
            var_f22 = curOriginZ;
            var_f20 = curOriginY;
            var_f18 = curOriginX;
"""
    if any(line not in source for line in copy_declarations) or restore not in source:
        raise ValueError("origin alias anchor missing")

    storage_modes = {
        "drop": "",
        "keep": "".join(copy_declarations),
        "pad_array": "    f32 aliasPad[3];\n",
        "pad_scalars": (
            "    f32 aliasPad0;\n"
            "    f32 aliasPad1;\n"
            "    f32 aliasPad2;\n"
        ),
    }
    casts = (
        "((f32 *) &{anchor})[{index}]",
        "(*(f32 *) ((u8 *) &{anchor} + ({index} * 4)))",
        "((volatile f32 *) &{anchor})[{index}]",
    )
    masters = ("var_f18", "var_f20", "var_f22")

    yield "baseline", source
    stripped = source
    for line in copy_declarations:
        stripped = stripped.replace(line, "", 1)
    for storage_name, storage in storage_modes.items():
        stored = stripped.replace(
            "    f32 var_f18;\n", storage + "    f32 var_f18;\n", 1
        )
        for anchor_index, anchor in enumerate(masters):
            for index_order in itertools.permutations(range(-2, 3), 3):
                for cast_index, cast in enumerate(casts):
                    expressions = [
                        cast.format(anchor=anchor, index=index)
                        for index in index_order
                    ]
                    replacement = (
                        f"            var_f22 = {expressions[2]};\n"
                        f"            var_f20 = {expressions[1]};\n"
                        f"            var_f18 = {expressions[0]};\n"
                    )
                    yield (
                        f"origin_alias_{storage_name}_anchor{anchor_index}_"
                        f"idx{'_'.join(str(i) for i in index_order)}_cast{cast_index}",
                        stored.replace(restore, replacement, 1),
                    )


def final_probe_variants(source):
    old = "    if (!var_f22) { }\n"
    if old not in source:
        raise ValueError("final probe anchor missing")
    expressions = (
        "",
        "    if (var_f22) { }\n",
        "    if (!var_f20) { }\n",
        "    if (var_f20) { }\n",
        "    if (!var_f18) { }\n",
        "    if (var_f18) { }\n",
        "    var_f22 = var_f22;\n",
        "    var_f20 = var_f20;\n",
        "    var_f18 = var_f18;\n",
        "    if (!(var_f22 = var_f22)) { }\n",
        "    if (!(var_f20 = var_f20)) { }\n",
        "    if (!(var_f18 = var_f18)) { }\n",
    )
    yield "baseline", source
    for index, expression in enumerate(expressions):
        yield f"final_probe_{index:02d}", source.replace(old, expression, 1)


def origin_array_web_variants(source):
    """Use one explicit array for the three do-loop origin copies."""
    prefix, declarations, suffix = split_declarations(source)
    copy_names = {
        "f32 curOriginX;",
        "f32 curOriginY;",
        "f32 curOriginZ;",
    }
    if not copy_names.issubset({line.strip() for line in declarations}):
        raise ValueError("origin array web declarations missing")
    remaining = [
        line if line.endswith("\n") else line + "\n"
        for line in declarations
        if line.strip() not in copy_names
    ]
    declaration_positions = range(max(0, len(remaining) - 8), len(remaining) + 1)
    pre = """\
        var_f18 = var_f18;
        var_f20 = var_f20;
        var_f22 = var_f22;
"""
    origin_chain = """\
                new_var3 = originPointsY[i];
                new_var3 = new_var3;
                new_var3 = (((A * originPointsX[i]) + (B * new_var3)) + (C * originPointsZ[i])) + D;
"""
    interpolation = """\
                    x3 = var_f18 + ((x1 - originPointsX[i]) * t);
                    y3 = var_f20 + ((y1 - originPointsY[i]) * t);
                    z3 = var_f22 + (((z1 - originPointsZ[i]) * t) * 1.0f);
"""
    counter_restore = """\
                            x1 = originPointsX[i];
                            y1 = originPointsY[i];
                            z1 = originPointsZ[i];
"""
    bottom = """\
            var_f22 = curOriginZ;
            var_f20 = curOriginY;
            var_f18 = curOriginX;
"""
    for anchor in (pre, origin_chain, interpolation, counter_restore, bottom):
        if anchor not in suffix:
            raise ValueError("origin array web anchor missing")

    for position in declaration_positions:
        new_declarations = (
            remaining[:position]
            + ["    f32 curOrigin[3];\n"]
            + remaining[position:]
        )
        declared = prefix + "".join(new_declarations) + suffix
        for indices in itertools.permutations(range(3)):
            x_index, y_index, z_index = indices
            save_lines = (
                f"        curOrigin[{x_index}] = var_f18;\n",
                f"        curOrigin[{y_index}] = var_f20;\n",
                f"        curOrigin[{z_index}] = var_f22;\n",
            )
            restore_lines = (
                f"            var_f22 = curOrigin[{z_index}];\n",
                f"            var_f20 = curOrigin[{y_index}];\n",
                f"            var_f18 = curOrigin[{x_index}];\n",
            )
            for save_order in itertools.permutations(range(3)):
                saved = declared.replace(
                    pre, "".join(save_lines[index] for index in save_order), 1
                ).replace(bottom, "".join(restore_lines), 1)
                for read_mask in range(8):
                    candidate = saved
                    if read_mask & 1:
                        candidate = candidate.replace(
                            origin_chain,
                            f"""\
                new_var3 = curOrigin[{y_index}];
                new_var3 = new_var3;
                new_var3 = (((A * curOrigin[{x_index}]) + (B * new_var3)) + (C * curOrigin[{z_index}])) + D;
""",
                            1,
                        )
                    if read_mask & 2:
                        candidate = candidate.replace(
                            interpolation,
                            f"""\
                    x3 = curOrigin[{x_index}] + ((x1 - curOrigin[{x_index}]) * t);
                    y3 = curOrigin[{y_index}] + ((y1 - curOrigin[{y_index}]) * t);
                    z3 = curOrigin[{z_index}] + (((z1 - curOrigin[{z_index}]) * t) * 1.0f);
""",
                            1,
                        )
                    if read_mask & 4:
                        candidate = candidate.replace(
                            counter_restore,
                            f"""\
                            x1 = curOrigin[{x_index}];
                            y1 = curOrigin[{y_index}];
                            z1 = curOrigin[{z_index}];
""",
                            1,
                        )
                    yield (
                        f"origin_array_web_at{position:02d}_"
                        f"xyz{x_index}{y_index}{z_index}_"
                        f"save{''.join(str(i) for i in save_order)}_"
                        f"reads{read_mask}",
                        candidate,
                    )


def coefficient_qualifier_variants(source):
    names = ("A", "B", "C", "D")
    qualifiers = ("plain", "volatile", "register")
    yield "baseline", source
    for choices in itertools.product(qualifiers, repeat=len(names)):
        if choices == ("plain",) * len(names):
            continue
        candidate = source
        for name, qualifier in zip(names, choices):
            old = f"    f32 {name};\n"
            if candidate.count(old) != 1:
                raise ValueError(f"coefficient declaration missing for {name}")
            prefix = "" if qualifier == "plain" else qualifier + " "
            candidate = candidate.replace(
                old, f"    {prefix}f32 {name};\n", 1
            )
            yield "coefficient_qualifier_" + "_".join(choices), candidate


def register_hint_variants(source):
    """Probe old-IDO register hints on the long-lived argument/local webs."""
    prefix, declarations, suffix = split_declarations(source)
    declaration_text = "".join(declarations)
    argument_fragments = (
        "ObjectModel *arg0",
        "s32 arg1",
        "s32 *numCollisions",
        "f32 *originPointsX",
        "f32 *originPointsY",
        "f32 *originPointsZ",
        "f32 *targetPointsX",
        "f32 *targetPointsY",
        "f32 *targetPointsZ",
        "f32 *collisionRadii",
        "s8 *surfaces",
        "f32 scale",
    )
    local_declarations = (
        "    s32 var_s6;\n",
        "    f32 sum1;\n",
        "    f32 sum2;\n",
        "    f32 t;\n",
        "    f32 x3;\n",
        "    f32 y3;\n",
        "    f32 z3;\n",
        "    f32 var_f18;\n",
        "    f32 var_f20;\n",
        "    f32 var_f22;\n",
    )
    if any(prefix.count(fragment) < 1 for fragment in argument_fragments):
        raise ValueError("register hint argument anchor missing")
    if any(declaration_text.count(fragment) != 1 for fragment in local_declarations):
        raise ValueError("register hint local anchor missing")

    yield "baseline", source
    for mask in range(1, 1 << len(argument_fragments)):
        candidate_prefix = prefix
        for index, fragment in enumerate(argument_fragments):
            if mask & (1 << index):
                before, separator, after = candidate_prefix.rpartition(fragment)
                if not separator:
                    raise ValueError(f"register hint argument vanished: {fragment}")
                candidate_prefix = before + "register " + fragment + after
        yield (
            f"register_args_{mask:03x}",
            candidate_prefix + declaration_text + suffix,
        )
    for mask in range(1, 1 << len(local_declarations)):
        candidate_declarations = declaration_text
        for index, declaration in enumerate(local_declarations):
            if mask & (1 << index):
                candidate_declarations = candidate_declarations.replace(
                    declaration,
                    declaration.replace("    ", "    register ", 1),
                    1,
                )
        yield (
            f"register_locals_{mask:03x}",
            prefix + candidate_declarations + suffix,
        )


def declaration_multi_shuffle_variants(source):
    """Deterministic multi-move search beyond the single-relocation local optimum."""
    prefix, declarations, suffix = split_declarations(source)
    movable = [
        index
        for index, line in enumerate(declarations)
        if "f32 " in line and "*" not in line
    ]
    rng = random.Random(0x80017A18)
    seen = {tuple(declarations)}
    yield "baseline", source

    # Exhaust useful Cartesian products of the obvious declaration groups.
    groups = (
        ("    f32 A;\n", "    f32 B;\n", "    f32 C;\n", "    f32 D;\n"),
        ("    f32 x1;\n", "    f32 y1;\n", "    f32 z1;\n"),
        ("    f32 x3;\n", "    f32 y3;\n", "    f32 z3;\n"),
    )
    group_positions = [
        [declarations.index(line) for line in group] for group in groups
    ]
    for coeff_order in itertools.permutations(groups[0]):
        for target_order in itertools.permutations(groups[1]):
            for hit_order in itertools.permutations(groups[2]):
                candidate_lines = list(declarations)
                for positions, order in zip(
                    group_positions, (coeff_order, target_order, hit_order)
                ):
                    for position, line in zip(sorted(positions), order):
                        candidate_lines[position] = line
                key = tuple(candidate_lines)
                if key in seen:
                    continue
                seen.add(key)
                yield (
                    "decl_group_"
                    + "".join(line.split()[1][:-1] for line in coeff_order)
                    + "_"
                    + "".join(line.split()[1][:-1] for line in target_order)
                    + "_"
                    + "".join(line.split()[1][:-1] for line in hit_order),
                    prefix + "".join(candidate_lines) + suffix,
                )

    # Random multi-swap perturbations preserve the overall successful layout
    # while crossing the no-improvement barrier of any one relocation.
    while len(seen) < 12000:
        candidate_lines = list(declarations)
        swap_count = rng.randint(2, 10)
        for _ in range(swap_count):
            left, right = rng.sample(movable, 2)
            candidate_lines[left], candidate_lines[right] = (
                candidate_lines[right],
                candidate_lines[left],
            )
        key = tuple(candidate_lines)
        if key in seen:
            continue
        seen.add(key)
        yield (
            f"decl_multiswap_{len(seen):05d}_{swap_count}",
            prefix + "".join(candidate_lines) + suffix,
        )


def compile_and_dump(job):
    index, tag, source, temp_dir = job
    c_path = os.path.join(temp_dir, f"candidate_{index:05d}.c")
    o_path = os.path.join(temp_dir, f"candidate_{index:05d}.o")
    with open(c_path, "w") as out:
        out.write(source)
    result = subprocess.run(
        ["/tmp/objeval.sh", c_path, o_path], capture_output=True, text=True
    )
    try:
        if result.returncode or not os.path.exists(o_path) or os.path.getsize(o_path) == 0:
            return index, tag, None
        return index, tag, realdiff.objdump(o_path)
    finally:
        for path in (c_path, o_path):
            if os.path.exists(path):
                os.unlink(path)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("base")
    parser.add_argument(
        "--mode",
        choices=[
            "decl-relocate",
            "edge-carriers",
            "balanced-edge-carriers",
            "balanced-edge-phantom-relocate",
            "fully-balanced-edge-carriers",
            "head-permute",
            "origin-x-pointer",
            "origin-pointer-subsets",
            "origin-x-increment-placement",
            "origin-x-copy-layout",
            "empty-probes",
            "origin-reads",
            "local-chain",
            "natural-main-interleave",
            "natural-main-partition-interleave",
            "natural-main-bestorder-partition",
            "natural-main-top-partition-orders",
            "natural-outer-head-permutations",
            "natural-guarded-facet-loop",
            "natural-scratch-chain-bridge",
            "natural-dead-accumulators",
            "natural-self-probes",
            "natural-expression-trees",
            "natural-origin-save-placement",
            "natural-feature-bridge",
            "natural-edge-reuse",
            "natural-edge-index",
            "origin-coalesce",
            "origin-save-placement",
            "origin-restore-expr",
            "origin-bottom-probes",
            "origin-copy-layout",
            "origin-copy-oob",
            "origin-array-save",
            "origin-copy-scope",
            "origin-copy-qualifiers",
            "origin-statement-order",
            "origin-decl-permute",
            "natural-origin-topology",
            "origin-carrier-fusion",
            "snapshot-origin-topology",
            "origin-alias",
            "final-probe",
            "origin-array-web",
            "coefficient-qualifiers",
            "register-hints",
            "decl-multi-shuffle",
        ],
        default="decl-relocate",
    )
    parser.add_argument("--workers", type=int, default=min(os.cpu_count() or 1, 10))
    parser.add_argument("--top", type=int, default=30)
    parser.add_argument("--detail-index", type=int)
    parser.add_argument("--emit-index")
    args = parser.parse_args()

    with open(args.base) as inp:
        source = inp.read()
    if args.mode == "decl-relocate":
        candidates = list(declaration_relocations(source))
    elif args.mode == "edge-carriers":
        candidates = list(edge_carrier_variants(source))
    elif args.mode == "balanced-edge-carriers":
        candidates = list(balanced_edge_carrier_variants(source))
    elif args.mode == "balanced-edge-phantom-relocate":
        candidates = list(balanced_edge_phantom_relocations(source))
    elif args.mode == "fully-balanced-edge-carriers":
        candidates = list(fully_balanced_edge_carrier_variants(source))
    elif args.mode == "head-permute":
        candidates = list(head_permutations(source))
    elif args.mode == "origin-x-pointer":
        candidates = list(origin_x_pointer_variants(source))
    elif args.mode == "origin-pointer-subsets":
        candidates = list(origin_pointer_subset_variants(source))
    elif args.mode == "origin-x-increment-placement":
        candidates = list(origin_x_increment_placement_variants(source))
    elif args.mode == "origin-x-copy-layout":
        candidates = list(origin_x_copy_layout_variants(source))
    elif args.mode == "empty-probes":
        candidates = list(empty_probe_variants(source))
    elif args.mode == "origin-reads":
        candidates = list(origin_read_variants(source))
    elif args.mode == "local-chain":
        candidates = list(local_chain_variants(source))
    elif args.mode == "natural-main-interleave":
        candidates = list(natural_main_interleave_variants(source))
    elif args.mode == "natural-main-partition-interleave":
        candidates = list(natural_main_partition_interleave_variants(source))
    elif args.mode == "natural-main-bestorder-partition":
        candidates = list(
            natural_main_partition_interleave_variants(
                source, ("A", "C", "B"), ("B", "A", "C")
            )
        )
    elif args.mode == "natural-main-top-partition-orders":
        candidates = list(natural_main_top_partition_order_variants(source))
    elif args.mode == "natural-outer-head-permutations":
        candidates = list(natural_outer_head_permutation_variants(source))
    elif args.mode == "natural-guarded-facet-loop":
        candidates = list(natural_guarded_facet_loop_variants(source))
    elif args.mode == "natural-scratch-chain-bridge":
        candidates = list(natural_scratch_chain_bridge_variants(source))
    elif args.mode == "natural-dead-accumulators":
        candidates = list(natural_dead_accumulator_variants(source))
    elif args.mode == "natural-self-probes":
        candidates = list(natural_self_probe_variants(source))
    elif args.mode == "natural-expression-trees":
        candidates = list(natural_expression_tree_variants(source))
    elif args.mode == "natural-origin-save-placement":
        candidates = list(natural_origin_save_placement_variants(source))
    elif args.mode == "natural-feature-bridge":
        candidates = list(natural_feature_bridge_variants(source))
    elif args.mode == "natural-edge-reuse":
        candidates = list(natural_edge_reuse_variants(source))
    elif args.mode == "natural-edge-index":
        candidates = list(natural_edge_index_variants(source))
    elif args.mode == "origin-coalesce":
        candidates = list(origin_coalescing_variants(source))
    elif args.mode == "origin-save-placement":
        candidates = list(origin_save_placement_variants(source))
    elif args.mode == "origin-restore-expr":
        candidates = list(origin_restore_expression_variants(source))
    elif args.mode == "origin-bottom-probes":
        candidates = list(origin_bottom_probe_variants(source))
    elif args.mode == "origin-copy-layout":
        candidates = list(origin_copy_layout_variants(source))
    elif args.mode == "origin-copy-oob":
        candidates = list(origin_copy_oob_variants(source))
    elif args.mode == "origin-array-save":
        candidates = list(origin_array_save_variants(source))
    elif args.mode == "origin-copy-scope":
        candidates = list(origin_copy_scope_variants(source))
    elif args.mode == "origin-copy-qualifiers":
        candidates = list(origin_copy_qualifier_variants(source))
    elif args.mode == "origin-statement-order":
        candidates = list(origin_statement_order_variants(source))
    elif args.mode == "origin-decl-permute":
        candidates = list(origin_declaration_permutations(source))
    elif args.mode == "natural-origin-topology":
        candidates = list(natural_origin_topology_variants(source))
    elif args.mode == "origin-carrier-fusion":
        candidates = list(origin_carrier_fusion_variants(source))
    elif args.mode == "snapshot-origin-topology":
        candidates = list(snapshot_origin_topology_variants(source))
    elif args.mode == "origin-alias":
        candidates = list(origin_alias_variants(source))
    elif args.mode == "final-probe":
        candidates = list(final_probe_variants(source))
    elif args.mode == "origin-array-web":
        candidates = list(origin_array_web_variants(source))
    elif args.mode == "coefficient-qualifiers":
        candidates = list(coefficient_qualifier_variants(source))
    elif args.mode == "register-hints":
        candidates = list(register_hint_variants(source))
    elif args.mode == "decl-multi-shuffle":
        candidates = list(declaration_multi_shuffle_variants(source))
    else:
        raise AssertionError(args.mode)

    config = realdiff.make_config()
    target = realdiff.AD.process(realdiff.objdump(realdiff.TARGET), config)
    temp_dir = tempfile.mkdtemp(prefix="func_80017A18_sweep_", dir="/tmp")
    results = []
    try:
        if args.detail_index is not None:
            index = args.detail_index
            if not 0 <= index < len(candidates):
                raise ValueError(f"detail index {index} is out of range")
            tag, candidate_source = candidates[index]
            if args.emit_index:
                with open(args.emit_index, "w") as out:
                    out.write(candidate_source)
                print(f"emitted={args.emit_index}")
            _, _, dump = compile_and_dump((index, tag, candidate_source, temp_dir))
            if dump is None:
                raise RuntimeError(f"candidate {index} did not compile")
            candidate = realdiff.AD.process(dump, config)
            diff = realdiff.AD.do_diff(target, candidate, config)
            components = {
                "stack": realdiff.component_score(target, candidate, stack=1),
                "reg": realdiff.component_score(target, candidate, reg=5),
                "reorder": realdiff.component_score(
                    target, candidate, reorder=60
                ),
                "insert": realdiff.component_score(
                    target, candidate, insert=100
                ),
                "delete": realdiff.component_score(
                    target, candidate, delete=100
                ),
            }
            print(
                f"index={index} tag={tag} score={diff.score} "
                + " ".join(f"{key}={value}" for key, value in components.items())
            )
            for row in diff.lines:
                if row.boring:
                    continue
                marker = row.fmt2.plain()[:1]
                left = ""
                right = ""
                if row.line1 is not None:
                    left = (
                        f"{row.line1.line_num:04x}  {row.line1.original}"
                    )
                if row.line2 is not None:
                    right = (
                        f"{row.line2.line_num:04x}  {row.line2.original}"
                    )
                print(f"{marker}  {left:<46} | {right}")
            return
        jobs = [
            (index, tag, candidate, temp_dir)
            for index, (tag, candidate) in enumerate(candidates)
        ]
        print(
            f"mode={args.mode} candidates={len(jobs)} workers={args.workers}",
            flush=True,
        )
        with concurrent.futures.ProcessPoolExecutor(
            max_workers=args.workers
        ) as executor:
            for completed, (index, tag, dump) in enumerate(
                executor.map(compile_and_dump, jobs, chunksize=2), 1
            ):
                if dump is not None:
                    candidate = realdiff.AD.process(dump, config)
                    score = realdiff.AD.do_diff(target, candidate, config).score
                    results.append((score, index, tag))
                if completed % 250 == 0 or completed == len(jobs):
                    best = min(results) if results else None
                    print(
                        f"progress={completed}/{len(jobs)} best={best}",
                        flush=True,
                    )
    finally:
        if temp_dir.startswith("/tmp/func_80017A18_sweep_"):
            shutil.rmtree(temp_dir)

    print("\nTOP")
    for score, index, tag in sorted(results)[: args.top]:
        print(f"{score:5d}  index={index:5d}  {tag}")


if __name__ == "__main__":
    main()
