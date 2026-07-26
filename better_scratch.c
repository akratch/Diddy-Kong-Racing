s32 func_80017A18(ObjectModel *arg0, s32 arg1, s32 *numCollisions, f32 *originPointsX, f32 *originPointsY, f32 *originPointsZ, f32 *targetPointsX, f32 *targetPointsY, f32 *targetPointsZ, f32 *collisionRadii, s8 *surfaces, f32 scale)
{
    f32 *planes;
    s32 i;
    s32 j;
    s32 k;
    f32 sum1;
    f32 sum2;
    f32 t;
    s32 ret;
    s32 counter;
    s32 var_s6;
    u32 redoLoop;
    s32 spF8;
    f32 A1;
    f32 B1;
    f32 C1;
    f32 D1;
    f32 A;
    f32 B;
    f32 C;
    f32 y1;
    f32 x3;
    f32 *curPlanes;
    f32 new_var3;
    f32 y3;
    f32 z3;
    f32 radius;
    f32 x1;
    f32 D;
    f32 z1;
    CollisionNode *node;
    f32 curOriginY;
    f32 curOriginX;
    f32 var_f18;
    f32 var_f20;
    f32 var_f22;
    f32 curOriginZ;

    spF8 = 0;
    planes = arg0->collisionPlanes;
    var_s6 = 1;
    for (i = 0; i < arg1; i++) {
        x1 = targetPointsX[i];
        y1 = targetPointsY[i];
        z1 = targetPointsZ[i];
        var_f18 = originPointsX[i];
        radius = collisionRadii[i] * scale;
        j = arg0->collisionFacetCount;
        var_f20 = ((0, originPointsY))[i];
        var_f22 = originPointsZ[i];
        counter = 0;
        curOriginX = var_f18;
        curOriginY = var_f20;
        curOriginZ = var_f22;
        do {
            redoLoop = 0;
            for (j = 0; j < arg0->collisionFacetCount; j++) {
                u16 triIndex;
                node = (CollisionNode *) (&arg0->collisionFacets[0, j]);
                triIndex = node->colPlaneIndex;
                curPlanes = planes;
                curPlanes += 4 * triIndex;
                A = curPlanes[0];
                B = curPlanes[1];
                C = curPlanes[2 & 0xFFFFu];
                D = curPlanes[3];
                sum2 = (((A * x1) + (B * y1)) + (C * z1)) + D;
                new_var3 = originPointsY[i];
                new_var3 = new_var3;
                new_var3 = (((A * originPointsX[i]) + (B * new_var3)) + (C * originPointsZ[i])) + D;
                sum1 = new_var3 - radius;
                sum2 -= radius;
                if ((sum1 >= (-0.1)) && (sum2 < (-0.1))) {
                    if (sum1 != sum2) {
                        t = sum1 / (sum1 - sum2);
                    } else {
                        sum1++;
                        sum1--;
                        t = 0.0f;
                    }
                    x3 = var_f18 + ((x1 - originPointsX[i]) * t);
                    y3 = var_f20 + ((y1 - originPointsY[i]) * t);
                    z3 = var_f22 + (((z1 - originPointsZ[i]) * t) * 1.0f);
                    ret = 1;
                    for (k = 0; (k < 3) && (ret == 1); k++) {
                        triIndex = node->closestTri[k] & 0xFFFFFFFFFFFFFFFF;
                        curPlanes = planes;
                        curPlanes += ((triIndex * 4) & 0xFFFFFFFFFFFFFFFF) & 0xFFFFFFFFFFFFFFFF;
                        A1 = curPlanes[0];
                        B1 = curPlanes[1];
                        C1 = curPlanes[2];
                        D1 = curPlanes[3];
                        if (((((A1 * x3) + (B1 * y3)) + (C1 * z3)) + D1) > 4.0f) {
                            ret = 0;
                        }
                    }

                    if (ret != 0) {
                        redoLoop = 1;
                        if (B > 0.707) {
                            y1 = (radius - (((A * x1) + (C * z1)) + D)) / B;
                        } else {
                            x1 -= sum2 * A;
                            y1 -= sum2 * B;
                            z1 -= sum2 * C;
                        }
                        counter++;
                        if (counter > 10) {
                            redoLoop = 0;
                            x1 = originPointsX[i];
                            y1 = originPointsY[i];
                            z1 = originPointsZ[i];
                        }
                        surfaces[i] = 0;
                        targetPointsX[i] = x1;
                        targetPointsY[i] = y1;
                        targetPointsZ[i] = z1;
                        j = arg0->collisionFacetCount;
                        if (sum2) { }
                    }
                }
            }
            var_f22 = curOriginZ;
            var_f20 = curOriginY;
            var_f18 = curOriginX;
        } while (redoLoop);
        if (counter > 0) {
            numCollisions[0]++;
            spF8 |= var_s6;
        }
        var_s6 <<= 1;
    }

    if (!var_f22) { }
    return spF8;
}
