static ? D_800E5608;                                /* unable to generate initializer: unknown type; const */

s32 func_80017A18(void *arg0, s32 arg1, s32 *arg2, f32 *arg3, f32 *arg4, f32 *arg5, f32 *arg6, f32 *arg7, f32 *arg8, f32 *arg9, s32 arg10, f32 arg11) {
    s32 spF8;
    f32 spE4;
    f32 spDC;
    f32 spD8;
    f32 spC0;
    f32 spBC;
    f32 spB4;
    f32 spA4;
    f32 spA0;
    f32 sp9C;
    f32 *sp80;
    f32 sp74;
    f32 sp70;
    f32 sp68;
    f32 sp64;
    f32 sp60;
    f32 *var_fp;
    f32 *var_ra;
    f32 *var_s2;
    f32 *var_s3;
    f32 *var_s4;
    f32 *var_s7;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f22;
    f32 temp_f26;
    f32 temp_f8;
    f32 var_f18;
    f32 var_f20;
    f32 var_f22;
    f32 var_f2;
    f32 var_f30;
    s16 var_t2;
    s32 temp_t0;
    s32 var_a2;
    s32 var_s1;
    s32 var_s6;
    s32 var_t4;
    s32 var_t5;
    s32 var_v1;
    u16 *temp_t1;
    void *temp_v0;
    void *temp_v0_2;
    void *var_a0;

    spF8 = 0;
    temp_t0 = arg0->unk10;
    var_s6 = 1;
    var_s1 = 0;
    if (arg1 > 0) {
        var_s7 = arg3;
        var_s2 = arg6;
        var_s3 = arg7;
        var_s4 = arg8;
        var_fp = arg4;
        var_ra = arg5;
        sp80 = arg9;
        do {
            spBC = *var_s2;
            var_f30 = *var_s3;
            spB4 = *var_s4;
            var_f18 = *var_s7;
            var_f20 = *var_fp;
            var_f22 = *var_ra;
            var_s7 += 4;
            spC0 = *sp80 * arg11;
            var_t4 = 0;
            var_t5 = 0;
loop_3:
            var_t2 = 0;
            if (arg0->unk32 > 0) {
                spA4 = var_f18;
                spA0 = var_f20;
                sp9C = var_f22;
                do {
                    temp_t1 = arg0->unkC + (var_t2 * 8);
                    temp_v0 = temp_t0 + (*temp_t1 * 0x10);
                    temp_f26 = temp_v0->unk4;
                    temp_f16 = temp_v0->unk0;
                    temp_f12 = temp_v0->unk8;
                    temp_f10 = temp_v0->unkC;
                    spE4 = temp_f16;
                    spDC = temp_f12;
                    sp64 = spA0;
                    spD8 = temp_f10;
                    temp_f8 = spDC * spB4;
                    temp_f16_2 = temp_f16 * spBC;
                    temp_f0 = ((temp_f16 * spA4) + (temp_f26 * spA0) + (temp_f12 * sp9C) + temp_f10) - spC0;
                    sp60 = spA4;
                    sp68 = sp9C;
                    sp74 = temp_f16_2;
                    temp_f22 = (temp_f16_2 + (temp_f26 * var_f30) + temp_f8 + spD8) - spC0;
                    sp70 = temp_f8;
                    if ((bitwise f64) *(&D_800E5608 + 4) <= (f64) temp_f0) {
                        var_a2 = 1;
                        if ((f64) temp_f22 < -0.1) {
                            if (temp_f0 != temp_f22) {
                                var_f2 = temp_f0 / (temp_f0 - temp_f22);
                            } else {
                                var_f2 = 0.0f;
                            }
                            var_v1 = 0 * 2;
                            var_a0 = temp_t1 + var_v1;
loop_11:
                            var_v1 += 2;
                            temp_v0_2 = temp_t0 + (var_a0->unk2 * 0x10);
                            if (((temp_v0_2->unk0 * (((spBC - sp60) * var_f2) + spA4)) + (temp_v0_2->unk4 * (((var_f30 - sp64) * var_f2) + spA0)) + (temp_v0_2->unk8 * (((spB4 - sp68) * var_f2) + sp9C)) + temp_v0_2->unkC) > 4.0f) {
                                var_a2 = 0;
                            }
                            var_a0 += 2;
                            if ((var_v1 < 6) && (var_a2 == 1)) {
                                goto loop_11;
                            }
                            if (var_a2 != 0) {
                                var_t5 = 1;
                                if ((f64) temp_f26 > 0.707) {
                                    var_f30 = (spC0 - (sp74 + sp70 + spD8)) / temp_f26;
                                } else {
                                    spBC -= temp_f22 * spE4;
                                    var_f30 -= temp_f22 * temp_f26;
                                    spB4 -= temp_f22 * spDC;
                                }
                                var_t4 += 1;
                                if (var_t4 >= 0xB) {
                                    var_f30 = spA0;
                                    var_t5 = 0;
                                    spBC = spA4;
                                    spB4 = sp9C;
                                }
                                *(arg10 + var_s1) = 0;
                                *var_s2 = spBC;
                                *var_s3 = var_f30;
                                *var_s4 = spB4;
                                var_t2 = arg0->unk32;
                            }
                        }
                    }
                    var_t2 += 1;
                } while (var_t2 < arg0->unk32);
                var_f22 = sp9C;
                var_f20 = spA0;
                var_f18 = spA4;
            }
            var_t5 = 0;
            if (var_t5 != 0) {
                goto loop_3;
            }
            var_s1 += 1;
            if (var_t4 > 0) {
                *arg2 += 1;
                spF8 |= var_s6;
            }
            sp80 += 4;
            var_s2 += 4;
            var_s3 += 4;
            var_s4 += 4;
            var_fp += 4;
            var_ra += 4;
            var_s6 *= 2;
        } while (var_s1 != arg1);
    }
    return spF8;
}
