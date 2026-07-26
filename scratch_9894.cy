s32 func_80017A18(ObjectModel *arg0, s32 arg1, s32 *arg2, f32 *arg3, f32 *arg4, f32 *arg5, f32 *arg6, f32 *arg7,
                  f32 *arg8, f32 *arg9, s8 *argA, f32 argB) {
    f32 *planes;
    s32 i, j, k;
    f32 sum1, sum2;
    f32 t;
    u32 var_a2; // u32 required here to force loading 1 instead of a3 into it
    s32 counter;
    s32 spF8; // f8
    s32 var_s6;
    CollisionFacetPlanes *node;
    f32 pad;
    s32 closestTri;
    f32 A; // e4
    f32 B; // e0
    f32 C; // dc
    f32 D; // d8
    f32 A1, B1, C1, D1;
    s32 redoLoop;
    f32 spC0; // c0
    f32 x1;   // bc
    f32 y1;
    f32 z1; // b4
    f32 x3, y3, z3;
    f32 x2; // a4
    f32 y2; // a0
    f32 z2; // 9c

    spF8 = 0;
    planes = arg0->collisionPlanes;
    var_s6 = 1;

    for (i = 0; i < arg1; i++) {
        x1 = arg6[i];
        y1 = arg7[i];
        z1 = arg8[i];
        y3 = arg3[i];
        z3 = arg4[i];
        sum2 = arg5[i];
        spC0 = arg9[i] * argB;

        counter = 0;
        do {
            redoLoop = FALSE;
            j = 0;
            if (arg0->collisionFacetCount > 0) {
                x2 = y3;
                y2 = z3;
                z2 = sum2;
                do {
                    node = &arg0->collisionFacets[j];
                    closestTri = node->basePlaneIndex;

                    A = planes[4 * closestTri + 0];
                    B = planes[4 * closestTri + 1];
                    C = planes[4 * closestTri + 2];
                    D = planes[4 * closestTri + 3];
                    sum1 = A * x2 + B * y2 + C * z2 + D;
                    sum2 = A * x1 + B * y1 + C * z1 + D;
                    y3 = x2;
                    sum1 -= spC0;
                    sum2 -= spC0;
                    if (sum1 >= -0.1 && sum2 < -0.1) {
                        z3 = (z1 - z2);
                        y3 = (y1 - y2);
                        x3 = (x1 - x2);
                        if (sum1 != sum2) {
                            t = sum1 / (sum1 - sum2);
                        } else {
                            t = 0.0f;
                        }

                        var_a2 = TRUE;
                        x3 = x3 * t + x2;
                        y3 = y3 * t + y2;
                        z3 = z3 * t + z2;

                        for (k = 0; k < 3 && var_a2 == TRUE; k++) {
                            closestTri = node->edgeBisectorPlane[k];

                            A1 = planes[4 * closestTri + 0];
                            B1 = planes[4 * closestTri + 1];
                            C1 = planes[4 * closestTri + 2];
                            D1 = planes[4 * closestTri + 3];
                            t = A1 * x3 + B1 * y3 + C1 * z3 + D1;
                            if (t > 4.0f) {
                                var_a2 = FALSE;
                            }
                        }

                        if (var_a2) {
                            redoLoop = TRUE;
                            if (B > 0.707) {
                                y1 = (spC0 - (A * x1 + C * z1 + D)) / B;
                            } else {
                                x1 -= sum2 * A;
                                y1 -= sum2 * B;
                                z1 -= sum2 * C;
                            }
                            counter++;
                            if (counter > 10) {
                                redoLoop = FALSE;
                                x1 = x2;
                                y1 = y2;
                                z1 = z2;
                            }
                            argA[i] = 0;
                            arg6[i] = x1;
                            arg7[i] = y1;
                            arg8[i] = z1;

                            j = arg0->collisionFacetCount; // break
                        }
                    }
                    j++;
                } while (j < arg0->collisionFacetCount);
                sum2 = z2;
                z3 = y2;
                
            }
        } while (redoLoop);

        if (counter > 0) {
            arg2[0]++;
            spF8 |= var_s6;
        }
        var_s6 <<= 1;
    }

    return spF8;
}
