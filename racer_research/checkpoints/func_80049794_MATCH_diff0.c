#include "racer.h"
#include "memory.h"
#include "menu.h"
#include "video.h"

#include "asset_enums.h"
#include "asset_loading.h"
#include "audio.h"
#include "audio_spatial.h"
#include "audio_vehicle.h"
#include "audiosfx.h"
#include "collision.h"
#include "common.h"
#include "fade_transition.h"
#include "game.h"
#include "game_ui.h"
#include "joypad.h"
#include "macros.h"
#include "math_util.h"
#include "object_functions.h"
#include "object_models.h"
#include "objects.h"
#include "particles.h"
#include "PR/os_cont.h"
#include "PR/os_libc.h"
#include "PR/os_system.h"
#include "PRinternal/viint.h"
#include "printf.h"
#include "save_data.h"
#include "structs.h"
#include "textures_sprites.h"
#include "thread3_main.h"
#include "tracks.h"
#include "types.h"
#include "vehicle_misc.h"

#define MAX_NUMBER_OF_GHOST_NODES 360

/**
 * This file features extensive use of CLAMP and WRAP.
 * CLAMP will keep the value within the two ranges.
 * WRAP will "overflow" the value. Used to keep angles within s16 bounds.
 */

/************ .data ************/

s32 gObjLoopGoldenBalloonLength = 0x310;
s16 gAntiPiracyHeadroll = 0;
s32 D_800DCB58 = 0; // Currently unknown, might be a different type.
s32 D_800DCB5C = 0; // Currently unknown, might be a different type.

// Not sure if D_800DCB58 & D_800DCB5C are actually a part of this array.
f32 D_800DCB60[14] = {
    -10.0f, 5.0f, 0.0f, 0.0f, 10.0f, 5.0f, 0.0f, 0.0f, -10.0f, 10.0f, 0.0f, 0.0f, 10.0f, 10.0f,
};

s32 gNumViewports = 0; // Currently unknown, might be a different type.
// Table used for quantifying speed reduction while the car drives over it, like how grass will slow you down more than
// the road. An antipiracy trigger can set the first index to 0.5f, which makes that surface type impossible to drive
// on.
f32 gSurfaceTractionTable[19] = {
    0.004f, 0.007f, 0.01f,  0.004f, 0.01f,  0.01f,  0.01f,  0.01f,  0.01f,  0.01f,
    0.004f, 0.004f, 0.004f, 0.004f, 0.004f, 0.004f, 0.004f, 0.004f, 0.004f,
};
// Can only assume this is surface related too. Not incline thresholds though.
f32 D_800DCBE8[19] = {
    0.8f, 0.85f, 0.85f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.8f, 0.8f, 0.84f, 0.8f, 0.8f, 0.8f, 0.8f, 0.8f,
};
// When driving over this surface, the car begins to bob up and down to give the effect of roughness.
s32 gSurfaceBobbingTable[19] = {
    0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
// When landing on this surface, it makes a sound.
// Strangely, they did only two surface types then called it a day.
s32 gSurfaceSoundTable[19] = { SOUND_NONE, SOUND_LAND_GRASS, SOUND_LAND_SAND, SOUND_NONE, SOUND_NONE,
                               SOUND_NONE, SOUND_NONE,       SOUND_NONE,      SOUND_NONE, SOUND_NONE,
                               SOUND_NONE, SOUND_NONE,       SOUND_NONE,      SOUND_NONE, SOUND_NONE,
                               SOUND_NONE, SOUND_NONE,       SOUND_NONE,      SOUND_NONE };

u16 D_800DCCCC[19] = {
    0x010C, 0x010B, 0x0009, 0x010C, 0x010C, 0x010C, 0x010C, 0x010C, 0x010C, 0x010C,
    0x010C, 0x0005, 0x010C, 0x010C, 0x010C, 0x010C, 0x010C, 0x010C, 0x010C,
};

s32 gSurfaceFlagTable[19] = {
    1, 4, 0x10, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0x100, 1, 1, 1, 1, 1,
};

s32 gSurfaceFlagTable4P[20] = {
    0, 4, 0x10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x100, 0, 0, 0, 0, 0, 0,
};

// Used to know how the AI should use a balloon when they have one.
s8 gRacerAIBalloonActionTable[NUM_WEAPON_TYPES] = { 1, 1, 2, 2, 4, 3, 0, 6, 4, 3, 2, 2, 5, 5, 5, 0 };

// Unused?
s8 D_800DCDA0[8] = {
    0, 0, 0, 1, 1, 2, 2, 2,
};

s8 D_800DCDA8[8] = {
    1, 1, 1, 2, 3, 2, 3, 2,
};

s8 D_800DCDB0[16][2] = {
    { 0x02, 0xFE }, { 0x03, 0xFE }, { 0x02, 0xFC }, { 0x02, 0xFB }, { 0x02, 0xFB }, { 0x02, 0xFE },
    { 0x02, 0xFD }, { 0x02, 0xFE }, { 0x03, 0xFD }, { 0x05, 0xFC }, { 0x04, 0xFE }, { 0x02, 0xFE },
    { 0x02, 0xFA }, { 0x02, 0xFE }, { 0x08, 0xF8 }, { 0x03, 0xFD },
};

// Checksum count for obj_loop_goldenballoon
s32 gObjLoopGoldenBalloonChecksum = ObjLoopGoldenBalloonChecksum;

FadeTransition gDoorFadeTransition = FADE_TRANSITION(FADE_FULLSCREEN, FADE_FLAG_NONE, FADE_COLOR_BLACK, 50, FADE_STAY);

/*******************************/

/************ .rodata ************/

const char gRacerDebugCoords[] = "%.1f,%.1f,%.1f\n";
UNUSED const char gChecksumOverflowString[] = "Chk ovflow!!\n";
UNUSED const char gRacerBackString[] = "Back\n";

/*********************************/

/************ .bss ************/

f32 gCurrentCourseHeight;
Vec3f gCurrentRacerWaterPos;
s8 gRacerWaveType;
Camera *gCameraObject;
UNUSED s32 D_8011D50C;
ObjectTransform gCurrentRacerTransform;
u32 gCurrentRacerInput;
u32 gCurrentButtonsPressed;
u32 gCurrentButtonsReleased;
s32 gCurrentStickX;
s32 gCurrentStickY;
s32 unused_8011D53C; // Set to 0 and only 0. Checked for being 1, but never true.
s32 gRaceStartTimer;
f32 D_8011D544; // Starts are 300, then counts down when the race starts. Usage currently unknown.
f32 D_8011D548;
f32 D_8011D54C;
u16 D_8011D550;
u16 D_8011D552;
s32 gCurrentCarSteerVel;
s32 D_8011D558;
s32 gCurrentPlayerIndex;
s16 D_8011D560; // Set, but never read.
f32 *gCurrentRacerMiscAssetPtr;
f32 *D_8011D568;
f32 gCurrentRacerWeightStat;
f32 gCurrentRacerHandlingStat;
f32 gCurrentRacerUnusedMiscAsset11; // Set, but never read
f32 gRacerMagnetVelX;
f32 gRacerMagnetVelZ;
u8 D_8011D580;
s8 gCurrentSurfaceType;
s8 gTajInteractStatus;
s8 gRacerDialogueCamera;
s8 gRacerInputBlocked;
s8 gStartBoostTime;
s16 gDialogueCameraAngle;
s8 gEggChallengeFlags[4];
s8 D_8011D58C[4];
GhostNode *gGhostData[3];
s8 gCurrentGhostIndex;
s8 gPrevGhostNodeIndex;
s16 gGhostNodeDelay;
s16 gGhostNodeCount[3];
s16 gGhostNodeFull[2];
s16 gGhostMapID; // Previous MapId?
s8 gRacerWaveCount;
s8 D_8011D5AF;
WaterProperties **gRacerCurrentWave;
s8 D_8011D5B4[4];
s16 D_8011D5B8;

/******************************/


void func_80049794(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer) {
    s32 pad5;
    s32 pad7;
    f32 spEC;
    f32 spE8;
    f32 spE4;
    f32 spE0;
    f32 var_f14;
    f32 spD8;
    f32 spD4;
    f32 spD0;
    f32 var_f20;
    f32 racerThrottle;
    f32 racerBrake;
    s32 racerMiscAssetIdx;
    s32 racerSteerAngle;
    s32 var_t0;
    s32 var_v0;
    s32 var_v1;
    s32 var_a0;
    f32 var_f0;
    s32 temp_t7;
    s8 spA3;
    s8 spA2;
    s8 spA1;
    s8 newSpinoutTimer;
    f32 spCC;
    s32 pad2;
    f32 var_f2;
    s32 xRotationOffset;
    s32 zRotationOffset;
    s32 i;
    f32 racerVelocity;
    s32 var_t9;
    Object *temp_v0_obj;
    f32 var_f6;
    s32 racerTrickType;
    f32 segmentXVelocity;
    f32 sp60[4]; // Should be MtxF, but produces a worse score.
    s8 playerObjectMoved;
    s32 steerVisualRotationOffset;
    Object_Boost *boostObj;
    s32 pad4;

    if (func_8000E138()) {
        updateRateF *= 1.09;
    }
    playerObjectMoved = FALSE;
    if (racer->groundedWheels > 0) {
        racer->unk84 = 0.0f;
        racer->unk88 = 0.0f;
    }
    if (racer->unk1FE == 4 && racer->spinout_timer == 0) {
        sound_play(SOUND_ZAP4, NULL);
        racer->spinout_timer = 20;
    }

    spA2 = FALSE;
    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->vehicleIDPrev != VEHICLE_WIZPIG && gRacerWaveCount != 0) {
        // UNMATCHED
        var_t9 = (var_t9 = gRacerWaveCount - 1);
        for (var_a0 = gRacerWaveCount - 1;
             var_a0 >= 0 && gRacerCurrentWave[var_a0]->waveHeight < obj->trans.y_position + 5; var_a0--) {
            if (gRacerWaveCount - 1) {}
            if (gRacerWaveCount - 1) {}
            if (gRacerWaveCount - 1) {}
        }

        if (var_a0 == gRacerWaveCount - 1) {
            var_a0--;
        }

        var_f2 = gRacerCurrentWave[var_a0 + 1]->waveHeight;
        var_f2 = (obj->trans.y_position - var_f2) - 10;
        if (var_f2 > 100.0f) {
            racer->drift_direction = 0;
        }
        // previously var_f0
        racerVelocity = -racer->velocity;
        if (racerVelocity < 0.0f) {
            racerVelocity = 0.0f;
        }
        if (var_f2 < 35 && racerVelocity < 8.0) {
            spA2 = TRUE;
        }
        if (racer->drift_direction == 0 && var_f2 < 38 && racerVelocity >= 8.0) {
            if ((!racerSteerAngle)) {}
            racer->drift_direction = 1;
        }
        if (racer->trickType == 1 || racer->trickType == -1 || gRacerCurrentWave[var_a0 + 1]->rot.y < 0.4) {
            racer->drift_direction = 0;
            spA2 = FALSE;
        }
        if (racer->drift_direction != 0) {
            if (racerVelocity < 8.0 || gCurrentStickY < -10) {
                racer->drift_direction = 0.0f;
            }
            racerVelocity -= 8;
            if (racerVelocity > 4.0) {
                racerVelocity = 4;
            }
            racerVelocity /= 4;
            obj->trans.y_position += ((38 - var_f2) * updateRateF * racerVelocity) / 8;
            if (gCurrentStickY > 0) {
                gCurrentStickY >>= 1;
            }
        }
    }
    D_8011D550 = 0;

    gCurrentCarSteerVel = (var_f0 > 0.0f) * 0;

    D_8011D558 = 0;
    spE8 = obj->trans.x_position;
    spE4 = obj->trans.y_position;
    spE0 = obj->trans.z_position;
    if (racer->trickType != 0) {
        var_f2 = 4.0;
    } else {
        var_f2 = 8.0;
    }

    var_v0 = gCurrentStickX - racer->steerAngle;
    var_v1 = var_v0 * updateRateF / var_f2;
    if (var_v0 != 0 && var_v1 == 0) {
        if (var_v0 > 0) {
            var_v1 = 1;
        }
        if (var_v0 < 0) {
            var_v1 = -1;
        }
    }
    racer->steerAngle += var_v1;

    var_v0 = gCurrentStickY - racer->unk1E8;
    var_v1 = var_v0 * updateRateF * 0.0625;
    if (var_v0 != 0 && var_v1 == 0) {
        if (var_v0 > 0) {
            var_v1 = 1;
        }
        if (var_v0 < 0) {
            var_v1 = -1;
        }
    }

    racer->unk1E8 += var_v1;
    handle_racer_items(obj, racer, updateRate);
    func_800535C4(obj, racer);
    racer_attack_handler_plane(obj, racer);
    if (gCurrentPlayerIndex != PLAYER_COMPUTER) {
        handle_racer_head_turning(obj, racer, updateRate);
    } else {
        slowly_reset_head_angle(racer);
    }

    if (gCurrentRacerInput & A_BUTTON) {
        racer->throttle += updateRateF * 0.01;
        if (racer->throttle > 1.0) {
            racer->throttle = 1;
        }
    } else {
        racer->throttle -= updateRateF * 0.01;
        if (racer->throttle < 0) {
            racer->throttle = 0.0f;
        }
    }

    if (racer->exitObj) {
        racer->throttle = 0.5;
    }

    racerThrottle = racer->throttle;
    if (gCurrentRacerInput & B_BUTTON && (gCurrentStickY < -40 || racer->velocity < 0.0f)) {
        racer->brake += updateRateF * 0.016;
        if (racer->brake > 1.2) {
            racer->brake = 1.2f;
        }
        if (racer->velocity < -2.0 && racer->groundedWheels >= 2) {
            rumble_set(racer->playerIndex, RUMBLE_TYPE_3);
        }
    } else {
        racer->brake -= updateRateF * 0.016;
        if (racer->brake < 0.0f) {
            racer->brake = 0.0f;
        }
    }
    racerBrake = racer->brake;
    gCurrentRacerTransform.rotation.y_rotation = obj->trans.rotation.y_rotation;
    gCurrentRacerTransform.rotation.x_rotation = obj->trans.rotation.x_rotation;
    gCurrentRacerTransform.rotation.z_rotation = 0;
    gCurrentRacerTransform.x_position = 0.0f;
    gCurrentRacerTransform.y_position = 0.0f;
    gCurrentRacerTransform.z_position = 0.0f;
    gCurrentRacerTransform.scale = 1.0f;
    mtxf_from_transform((MtxF *) &sp60, &gCurrentRacerTransform);
    mtxf_transform_point(&sp60, 0.0f, 0.0f, 1.0f, &racer->ox1, &racer->oy1, &racer->oz1);
    mtxf_transform_point(&sp60, 1.0f, 0.0f, 0.0f, &racer->ox3, &racer->oy3, &racer->oz3);
    mtxf_transform_point(&sp60, 0.0f, 1.0f, 0.0f, &racer->ox2, &racer->oy2, &racer->oz2);
    if (racer->approachTarget == NULL) {
        apply_plane_tilt_anim(updateRate, obj, racer);
    }
    var_v0 = racer->playerIndex;
    if (((var_v0 ^ 0) == PLAYER_COMPUTER) && (gCurrentPlayerIndex != PLAYER_COMPUTER)) {
        gCurrentRacerHandlingStat = 1.4f;
    }
    var_f20 = (obj->x_velocity * obj->x_velocity) + (obj->z_velocity * obj->z_velocity) +
              (obj->y_velocity * obj->y_velocity);
    var_f20 = sqrtf(var_f20) - 2.0;
    if (racer->vehicleID >= VEHICLE_BOSSES) {
        var_f20 = ((var_f20 - 2.0) / 2.0);
    }
    if (var_f20 < 0) {
        var_f20 = 0;
    }
    if (var_f20 > 4.0) {
        var_f20 = 4;
    }
    spA3 = FALSE;
    // This line (or somewhere here about) seems to be culprit as it incorrectly uses $f12 instead of $f2
    // This may or may not cause $20 to be swapped with $f2
    var_f20 = 1.0 - (var_f20 / 4.0);
    var_f2 = (gCurrentCourseHeight - 50.0) - obj->trans.y_position;
    if (racer->trickType < 2 && racer->trickType >= -1 && var_f2 < 0) {
        var_f20 += -var_f2 / 25.0;
        if (gCurrentStickY < -20) {
            gCurrentStickY = -20;
        }
        if (var_f20 > 2.5) {
            var_f20 = 2.5;
        }
        spA3 = TRUE;
    }
    var_f14 = racer->velocity;
    if (var_f14 < 0) {
        var_f14 = -var_f14;
    }

    var_f0 = racer->velocity;
    if (var_f0 < 0.0f) {
        var_f0 = -var_f0;
    }
    if (var_f14 > (var_f0 + 4)) {
        var_f14 = var_f0 + 3;
    }
    if (var_f14 > 12.0f) {
        var_f14 = 12.0f;
    }
    racerMiscAssetIdx = var_f14;      // racerMiscAssetIdx = Integer part of var_f14
    var_f0 = var_f14 - (s32) var_f14; // var_f0 = fractional part of var_f14
    // UNMATCHED
    var_f14 = (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx + 1] * var_f0) +
              (gCurrentRacerMiscAssetPtr[racerMiscAssetIdx] * (1.0 - var_f0));
    spD4 = 0.01f;
    spD0 = 0.02f;
    spD8 = 0.004f;
    if (racer->groundedWheels != 0) {
        spD4 = 0.02f;
        spD0 = 0.01f;
        i = SURFACE_DEFAULT;
        for (var_t0 = 0; var_t0 < 4; var_t0++) {
            if (racer->wheel_surfaces[var_t0] != SURFACE_NONE && i < racer->wheel_surfaces[var_t0]) {
                i = racer->wheel_surfaces[var_t0];
            }
        }
        if (i == SURFACE_STONE) {
            racer->magnetTimer = 0;
        }
        if (racer->playerIndex == PLAYER_ONE && i == SURFACE_TAJ_PAD && gCurrentButtonsPressed & Z_TRIG) {
            gTajInteractStatus = TAJ_TELEPORT;
        }
        if (gCurrentRacerInput & B_BUTTON && gCurrentStickY >= -40 && racer->velocity >= -0.5) {
            spD8 *= 8;
        }
        if (racer->boostTimer == 0 && i == SURFACE_ZIP_PAD) {
            racer->boostTimer = normalise_time(45);
            racer->boostType = BOOST_LARGE;
            if (racer->throttleReleased != 0) {
                racer->boostType |= EMPOWER_BOOST;
            }
            racer_play_sound(obj, SOUND_ZIP_PAD_BOOST);
            play_random_character_voice(obj, SOUND_VOICE_CHARACTER_POSITIVE, SOUND_NUMBER_OF_RACERS, 0x80 | 0x2);
            rumble_set(racer->playerIndex, RUMBLE_TYPE_8);
        }
        if (racer->vehicleID >= VEHICLE_BOSSES && racer->velocity > -6.0) {
            racerThrottle *= 0.6;
            racerBrake *= 0.3;
        }
        racer->trickType = 0;
        if (gCurrentRacerInput & B_BUTTON && gNumViewports < 3) {
            obj->particleEmittersEnabled = OBJ_EMIT_1 | OBJ_EMIT_2;
        }
        gCurrentStickY = ((f32) gCurrentStickY) * (1.0 - var_f20);
        if (gCurrentStickY > 0) {
            gCurrentStickY = 0;
        }
    }
    var_t0 = 0;
    if (spA3 == FALSE) {
        var_t0 = (var_f20 * 4608);
    }
    if (racer->vehicleID > VEHICLE_BOSSES) {
        var_t0 = 0;
    }
    if (racer->vehicleID == VEHICLE_CARPET) {
        var_f20 = 0.0;
        var_t0 = 0;
    }
    apply_vehicle_rotation_offset(racer, updateRate, 0, var_t0, 0);
    if (racer->unk1FE == 0) {
        var_f20 = 5.5;
        obj->particleEmittersEnabled |= OBJ_EMIT_9;
    }
    if (racer->unk1FE == 1) {
        var_f20 = 2;
    }
    if (racer->buoyancy != 0.0) {
        var_f20 = -1.0f;
        gCurrentStickY = -60;
        var_f2 = racer->buoyancy - 20.0f;
        if (var_f2 < 0.0) {
            var_f2 = 0;
        }
        var_f20 -= var_f2 / 10;
        if (var_f20 < -4.0) {
            var_f20 = -4;
        }
    }
    if (gRaceStartTimer != 0) {
        var_f20 = 1;
    }
    if (racer->vehicleIDPrev == VEHICLE_WIZPIG) {
        if (obj->animationID < 3) {
            var_f20 = 4.0f;
        } else {
            var_f20 = 0.0f;
        }
    }
    var_f20 *= gCurrentRacerWeightStat;
    obj->y_velocity -= var_f20;
    if (racer->zipperDirCorrection != 0 && racer->spinout_timer == 0) {
        racer->magnetTimer = 0;
        racer->spinout_timer = 0;
        racer->trickType = 0;
        steerVisualRotationOffset = racer->zipperObj->trans.rotation.y_rotation - (racer->steerVisualRotation & 0xFFFF);
        if (steerVisualRotationOffset > 0x8000) {
            steerVisualRotationOffset -= 0xFFFF;
        }
        if (steerVisualRotationOffset < -0x8000) {
            steerVisualRotationOffset += 0xFFFF;
        }
        racer->steerVisualRotation += (steerVisualRotationOffset * updateRate) >> 3;
        if (((steerVisualRotationOffset < 0x400) && (steerVisualRotationOffset > -0x400)) ||
            (racer->playerIndex == PLAYER_COMPUTER)) {
            if (racer->playerIndex != PLAYER_COMPUTER) {
                sound_play_spatial(SOUND_ZIP_PAD_BOOST, obj->trans.x_position, obj->trans.y_position,
                                   obj->trans.z_position, NULL);
                play_random_character_voice(obj, SOUND_VOICE_CHARACTER_POSITIVE, SOUND_NUMBER_OF_RACERS, 0x80 | 0x2);
            }
            racer->boostTimer = normalise_time(45);
            racer->boostType = BOOST_LARGE;
            if (racer->throttleReleased != 0) {
                racer->boostType |= EMPOWER_BOOST;
            }
            rumble_set(racer->playerIndex, 8);
            racer->zipperDirCorrection = 0;
        } else {
            obj->x_velocity *= 0.75;
            obj->y_velocity *= 0.75;
            obj->z_velocity *= 0.75;
        }
    }
    if (racer->spinout_timer != 0) {
        xRotationOffset = racer->x_rotation_offset;
        if (racer->unk1F1 == 0) {
            racer->unk1F1 = 1;
        }
        if (racer->groundedWheels != 0 || racer->unk1F1 == 2) {
            racer->unk1F1 = 2;
            // s0.162 = x_rot_offset
            // s0.164 = z_rot_offset
            temp_t7 = updateRate << 11;
            racer->x_rotation_offset -= temp_t7;
            var_t0 = racer->z_rotation_offset;
            if ((temp_t7 + var_t0) > 0 && var_t0 <= 0) {
                racer->z_rotation_offset = 0;
            } else {
                racer->z_rotation_offset += temp_t7;
            }
            if (racer->velocity > -2.0 && racer->groundedWheels >= 3) {
                racer->spinout_timer = 0;
            }
        } else {
            racer->z_rotation_offset += updateRate << 11;
        }
        if (racer->groundedWheels != 0 && ((xRotationOffset > 0x6000 && racer->x_rotation_offset <= 0x6000) ||
                                           (xRotationOffset > -0x6000 && racer->x_rotation_offset <= -0x6000) ||
                                           (xRotationOffset > 0 && racer->x_rotation_offset <= 0))) {
            racer_play_sound(obj, SOUND_CRASH);
            if (racer->playerIndex != PLAYER_COMPUTER) {
                gCameraObject->shakeMagnitude = 6.0f;
            }
        }
        gCurrentRacerInput &= ~(A_BUTTON | Z_TRIG);
        racer->spinout_timer -= updateRate;
        racer->boostTimer = 0;
        racer->brake = 1;
        if (racer->spinout_timer <= 0) {
            racer->spinout_timer = 0;
            racer->unk1F1 = 0;
        }
        var_v0 = 0xD800 - (obj->trans.rotation.x_rotation & 0xFFFF);
        if (var_v0 > 0x8000) {
            var_v0 -= 0xFFFF;
        }
        if (var_v0 < -0x8000) {
            var_v0 += 0xFFFF;
        }
        obj->trans.rotation.x_rotation += (var_v0 * updateRate) >> 4;
    } else {
        if (racer->trickType == 1 || racer->trickType == -1) {
            var_t0 = racer->x_rotation_vel;
            racer->x_rotation_vel += ((racer->trickType * 0x600) * updateRate);
            racerThrottle = 1.2f;
            if (racer->trickType == 1) {
                if (var_t0 > 0) {
                    racer->unk1D4 = 1;
                }
                if ((var_t0 < 0) && (racer->x_rotation_vel >= 0) && (racer->unk1D4 != 0)) {
                    racer->trickType = 0;
                    racer->x_rotation_vel = 0;
                }
            } else {
                if (var_t0 < 0) {
                    racer->unk1D4 = 1;
                }
                if ((var_t0 > 0) && (racer->x_rotation_vel <= 0) && (racer->unk1D4 != 0)) {
                    racer->trickType = 0;
                    racer->x_rotation_vel = 0;
                }
            }
        } else if (racer->trickType == 2 || racer->trickType == -2) {
            var_v1 = obj->trans.rotation.x_rotation;
            var_t0 = var_v1;
            if (racer->unk1D5 == 0) {
                obj->trans.rotation.x_rotation =
                    var_v1 + ((racer->trickType * (((0x180 & 0xFFFFFFFF) & 0xFFFFFFFF) & 0xFFFFFFFF)) * updateRate);
            }
            if (!(gCurrentRacerInput & R_TRIG)) {
                racer->unk1D5 = 0;
            }
            if (racer->unk1D5 > 0) {
                racer->unk1D5 -= updateRate;
            } else {
                racer->unk1D5 = 0;
            }
            var_v1 = racer->x_rotation_vel;
            racer->x_rotation_vel = var_v1 - ((var_v1 * updateRate) >> 4);
            obj->x_velocity = racer->velocity * racer->ox1;
            obj->y_velocity = racer->velocity * racer->oy1;
            obj->z_velocity = racer->velocity * racer->oz1;
            if (racer->trickType == 2) {
                if (var_t0 > 0) {
                    racer->unk1D4 = 1;
                }
                if (var_t0 < 0) {
                    if (obj->trans.rotation.x_rotation >= 0) {
                        if (racer->unk1D4 != 0) {
                            racer->trickType = 0;
                            obj->trans.rotation.x_rotation = 0;
                            racer->boostTimer = normalise_time(0xA);
                            racer->boostType = BOOST_NONE;
                            if (racer->throttleReleased != 0) {
                                racer->boostType |= EMPOWER_BOOST;
                            }
                        }
                    }
                }
                if (var_t0 > 0x4000 && obj->trans.rotation.x_rotation < -0x4000 && (gCurrentRacerInput & R_TRIG)) {
                    racer->unk1D5 = 60;
                }
            } else {
                if (var_t0 < 0) {
                    racer->unk1D4 = 1;
                }
                if (var_t0 > 0) {
                    if (obj->trans.rotation.x_rotation <= 0) {
                        if (racer->unk1D4 != 0) {
                            racer->trickType = 0;
                            obj->trans.rotation.x_rotation = 0;
                            racer->boostTimer = normalise_time(10);
                            racer->boostType = BOOST_NONE;
                            if (racer->throttleReleased != 0) {
                                racer->boostType |= EMPOWER_BOOST;
                            }
                        }
                    }
                }
                if (var_t0 < -0x4000 && obj->trans.rotation.x_rotation > 0x4000 && (gCurrentRacerInput & R_TRIG)) {
                    racer->unk1D5 = 60;
                }
            }
        } else {
            racerSteerAngle = racer->steerAngle;
            spA1 = FALSE;
            if (racer->groundedWheels != 0) {
                if (gCurrentRacerInput & R_TRIG) {
                    spA1 = TRUE;
                }
                gCurrentRacerInput &= ~R_TRIG;
            }
            if (racer->groundedWheels < 2) {
                var_t0 = racerSteerAngle;
                racerSteerAngle = 0;
                if (obj->trans.rotation.x_rotation > 0x3000) {
                    racerSteerAngle = obj->trans.rotation.x_rotation - 0x3000;
                    if (racerSteerAngle > 0x1000) {
                        racerSteerAngle = 0x1000;
                    }
                } else if (obj->trans.rotation.x_rotation < -0x3000) {
                    racerSteerAngle = obj->trans.rotation.x_rotation + 0x3000;
                    if (racerSteerAngle < -0x1000) {
                        racerSteerAngle = -0x1000;
                    }
                    racerSteerAngle = -racerSteerAngle;
                }
                var_t0 *= (f32) (1.0 - ((f32) racerSteerAngle / 4096));
                if (gCurrentRacerInput & R_TRIG) {
                    obj->particleEmittersEnabled |= OBJ_EMIT_7 | OBJ_EMIT_8;
                    racer->x_rotation_vel -= (var_t0 * 16 * updateRate) >> 1;
                }
                racer->x_rotation_vel -= (var_t0 * updateRate * 20) >> 1;
                racer->x_rotation_vel -= (racer->x_rotation_vel * updateRate) >> 4;
                if (racer->zipperDirCorrection == 0) {
                    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->raceFinished == FALSE) {
                        var_t0 = -racer->x_rotation_vel >> 6;
                        if ((gCurrentRacerInput & R_TRIG) && (gCurrentRacerInput & B_BUTTON)) {
                            var_t0 *= 2;
                        }
                        var_t0 *= gCurrentRacerHandlingStat;
                        var_v0 = var_t0 * updateRate;
                        racer->steerVisualRotation -= var_v0 & 0xFFFF;
                    } else {
                        var_t0 = gCurrentStickX * 4;
                        var_v0 = var_t0 * updateRate;
                        racer->steerVisualRotation -= var_v0 & 0xFFFF;
                    }
                }
            } else {
                var_v0 = -(racer->x_rotation_vel & 0xFFFF);
                if (var_v0 > 0x8000) {
                    var_v0 -= 0xFFFF;
                }
                if (var_v0 < -0x8000) {
                    var_v0 += 0xFFFF;
                }
                racer->x_rotation_vel += (var_v0 * updateRate) >> 4;
                if (gCurrentRacerInput & R_TRIG) {
                    var_t0 = racerSteerAngle * 6;
                } else {
                    var_t0 = racerSteerAngle * 4;
                }
                racer->steerVisualRotation -= (var_t0 * updateRate) & 0xFFFF;
            }
            if (!(gCurrentRacerInput & R_TRIG) || racer->groundedWheels == 0 || racer->zipperDirCorrection != 0) {
                var_f20 = racer->velocity * var_t0 * 0.00015;
                obj->x_velocity -= racer->ox3 * var_f20;
                obj->y_velocity -= racer->oy3 * var_f20;
                obj->z_velocity -= racer->oz3 * var_f20;
            }

            var_t0 = gCurrentStickY;
            if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->raceFinished == FALSE) {
                var_t0 = racer->unk1E8;
            }

            var_f2 = -racer->velocity;
            if (var_f2 < 4.0) {
                var_f2 = 4.0f;
            }
            if (var_f2 > 14.0) {
                var_f2 = 14.0f;
            }
            var_f2 /= 7.0;
            var_t0 *= var_f2;

            if (!(gCurrentRacerInput & R_TRIG)) {
                var_t0 >>= 1;
                obj->trans.rotation.x_rotation -= (obj->trans.rotation.x_rotation * updateRate) >> 4;
                obj->trans.rotation.x_rotation -= ((var_t0 * 19) * updateRate) >> 1;
            } else {
                var_t0 >>= 1;
                obj->trans.rotation.x_rotation -= (obj->trans.rotation.x_rotation * updateRate) >> 4;
                obj->trans.rotation.x_rotation -= ((var_t0 * 30) * updateRate) >> 1;
            }

            if (racer->tappedR) {
                racer->tappedR = FALSE;
                if (racer->groundedWheels == 0 && racer->velocity < -6.5 && racer->waterTimer == 0) {
                    if (gCurrentStickX > 40) {
                        racer->trickType = -1;
                    }
                    if (gCurrentStickX < -40) {
                        racer->trickType = 1;
                    }
                    if (gCurrentStickY > 40) {
                        racer->trickType = -2;
                    } else if (racer->trickType == 0) {
                        racer->trickType = 2;
                    }
                    racer->unk1D4 = 0;
                    racer->unk1D5 = 0;
                }
            }
        }
    }
    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->velocity < -4.0f) {
        if ((obj->particleEmittersEnabled & (OBJ_EMIT_7 | OBJ_EMIT_8)) != (OBJ_EMIT_7 | OBJ_EMIT_8)) {
            obj->particleEmittersEnabled |= OBJ_EMIT_3 | OBJ_EMIT_4;
        }
    }
    // This line looks unmatched
    var_f0 = handle_racer_top_speed(obj, racer);
    var_f14 = var_f14 * var_f0;
    var_f14 *= 1.8;
    if (racer->boostTimer > 0) {
        if (gRaceStartTimer == 0) {
            racer->throttle = 1;
            var_f14 = 2.0f;
            racer->boostTimer -= updateRate;
            obj->particleEmittersEnabled |= OBJ_EMIT_7 | OBJ_EMIT_8;
        }
    } else {
        racer->boostTimer = 0;
    }
    if (racer->zipperDirCorrection == 0 && gRaceStartTimer == 0) {
        if (racer->groundedWheels == 0 && racerThrottle < 0.4 && racer->vehicleID != VEHICLE_CARPET) {
            racerThrottle = 0.4f;
        }
        racerThrottle = racerThrottle * var_f14;
        obj->x_velocity -= racer->ox1 * racerThrottle;
        obj->y_velocity -= racer->oy1 * racerThrottle;
        obj->z_velocity -= racer->oz1 * racerThrottle;
        if (racer->groundedWheels >= 3 || racer->velocity < 1.0 || racer->vehicleID == VEHICLE_CARPET) {
            if (racer->groundedWheels == 0) {
                racerBrake /= 2;
            }
            racerBrake *= var_f14 / 2;
            obj->x_velocity += racer->ox1 * racerBrake;
            obj->y_velocity += racer->oy1 * racerBrake;
            obj->z_velocity += racer->oz1 * racerBrake;
        }
        spEC = racer->velocity * racer->velocity;
        if (racer->velocity < 0.0f) {
            spEC = -spEC;
        }
        if (spEC < 1.0f && !(gCurrentRacerInput & A_BUTTON)) {
            var_f20 = racer->velocity * spD8 * 8.0f;
        } else {
            var_f20 = spEC * spD8;
        }
        obj->x_velocity -= racer->ox1 * var_f20;
        obj->y_velocity -= racer->oy1 * var_f20;
        obj->z_velocity -= racer->oz1 * var_f20;
    var_f20 = racer->lateral_velocity * racer->lateral_velocity * spD4;
        if (racer->lateral_velocity < 0) {
            var_f20 = -var_f20;
        }
        var_f20 += (racer->lateral_velocity * spD4 * 4.0f);
        obj->x_velocity -= racer->ox3 * var_f20;
        obj->y_velocity -= racer->oy3 * var_f20;
        obj->z_velocity -= racer->oz3 * var_f20;
        if (racer->trickType == 1 || racer->trickType == -1) {
            spEC = racer->velocity * 0.058823529411764705 * 1.5;
            var_f20 = coss_f(racer->x_rotation_vel) * spEC * racer->trickType;
            if (racer->x_rotation_vel > 0x4000 || racer->x_rotation_vel < -0x4000) {
                var_f20 *= 2;
            }
            obj->x_velocity -= racer->ox3 * var_f20;
            obj->y_velocity -= racer->oy3 * var_f20;
            obj->z_velocity -= racer->oz3 * var_f20;

            var_f20 = sins_f(racer->x_rotation_vel) * spEC * racer->trickType * 1.5;
            obj->x_velocity -= racer->ox2 * var_f20;
            obj->y_velocity -= racer->oy2 * var_f20;
            obj->z_velocity -= racer->oz2 * var_f20;
        }
        var_f20 = racer->unk34 * racer->unk34 * spD0;
        if (racer->unk34 < 0.0f) {
            var_f20 = -var_f20;
        }
        var_f20 += racer->unk34 * spD0 * 4.0f;
        obj->x_velocity -= racer->ox2 * var_f20;
        obj->y_velocity -= racer->oy2 * var_f20;
        obj->z_velocity -= racer->oz2 * var_f20;

        racer->forwardVel -= (racer->forwardVel + (racer->velocity * 0.05)) * 0.125;
    }
    racer->unk10C = 0;
    racer->y_rotation_vel += (gCurrentCarSteerVel - racer->y_rotation_vel) >> 3;
    obj->trans.rotation.y_rotation = racer->steerVisualRotation + racer->y_rotation_vel;
    racer->z_rotation_vel += (D_8011D558 - racer->z_rotation_vel) >> 3;
    obj->trans.rotation.z_rotation = racer->x_rotation_vel + racer->z_rotation_vel;
    if (racer->magnetTimer != 0) {
        obj->x_velocity = gRacerMagnetVelX;
        obj->z_velocity = gRacerMagnetVelZ;
    }
    if (racer->approachTarget == NULL) {
        var_f20 = obj->x_velocity;
        spEC = obj->z_velocity;
        if (racer->unk1D2 != 0) {
            var_f20 += racer->unk11C * 0.5;
            spEC += racer->unk120 * 0.5;
        }
        if (gRacerInputBlocked) {
            if (var_f20 > 0.5 || var_f20 < -0.5) {
                var_f20 *= 0.65;
            } else {
                var_f20 = 0.0f;
            }
            if (spEC > 0.5 || spEC < -0.5) {
                spEC *= 0.65;
            } else {
                spEC = 0.0f;
            }
        } else {
            var_f20 += racer->unk84;
            spEC += racer->unk88;
        }
        if (move_object(obj, var_f20 * updateRateF, obj->y_velocity * updateRateF, spEC * updateRateF) &&
            gCurrentPlayerIndex != PLAYER_COMPUTER) {
            playerObjectMoved = TRUE;
        }
    } else {
        racer_approach_object(obj, racer, updateRateF);
    }
    var_t0 = racer->groundedWheels;
    if (gCurrentPlayerIndex == PLAYER_COMPUTER) {
        if (racer->vehicleIDPrev != VEHICLE_ROCKET || gRaceStartTimer != 0) {
            onscreen_ai_racer_physics(obj, racer, updateRate);
        } else {
            racer->groundedWheels = 0;
            racer->unk1E3 = 0;
        }
    } else {
        func_80054FD0(obj, racer, updateRate);
    }
    if (var_t0 == 0 && racer->groundedWheels != 0 && racer->spinout_timer != 0) {
        racer_play_sound(obj, SOUND_CRASH);
        if (racer->playerIndex != PLAYER_COMPUTER) {
            gCameraObject->shakeMagnitude = 6.0f;
        }
    }
    if (racer->unk1D2 != 0) {
        racer->unk1D2 -= updateRate;
        if (racer->unk1D2 < 0) {
            racer->unk1D2 = 0;
        }
    } else {
        var_f0 = 1.0f / updateRateF;
        var_f20 = (obj->trans.x_position - spE8 - D_8011D548) * var_f0;
        obj->y_velocity = (obj->trans.y_position - spE4) * var_f0;
        spEC = (obj->trans.z_position - spE0 - D_8011D54C) * var_f0;
    }
    if (gRaceStartTimer == 100) {
        obj->y_velocity = -5.0f;
    }
    obj->x_velocity = var_f20;
    obj->z_velocity = spEC;
    gCurrentRacerTransform.rotation.y_rotation = -obj->trans.rotation.y_rotation;
    gCurrentRacerTransform.rotation.x_rotation = -obj->trans.rotation.x_rotation;
    gCurrentRacerTransform.rotation.z_rotation = 0;
    gCurrentRacerTransform.x_position = 0.0f;
    gCurrentRacerTransform.y_position = 0.0f;
    gCurrentRacerTransform.z_position = 0.0f;
    gCurrentRacerTransform.scale = 1.0f;
    mtxf_from_inverse_transform((MtxF *) &sp60, &gCurrentRacerTransform);
    mtxf_transform_point(&sp60, obj->x_velocity, obj->y_velocity, obj->z_velocity, &racer->lateral_velocity,
                         &racer->unk34, &racer->velocity);
    if (obj->attachPoints != NULL && obj->attachPoints->count >= 3) {
        temp_v0_obj = obj->attachPoints->obj[2];
        temp_v0_obj->trans.rotation.y_rotation = 0x4000;
        temp_v0_obj->modelIndex += 1;
        if (temp_v0_obj->modelIndex == temp_v0_obj->header->numberOfModelIds) {
            temp_v0_obj->modelIndex = 0;
        }
    }
    if (obj->attachPoints != NULL && obj->attachPoints->count >= 3) {
        if (racer->groundedWheels != 0 || spA2 != FALSE) {
            temp_v0_obj = obj->attachPoints->obj[0];
            if (temp_v0_obj->trans.y_position > 0.0f) {
                temp_v0_obj->trans.y_position = temp_v0_obj->trans.y_position - 2.0;
            } else {
                temp_v0_obj->trans.y_position = 0.0f;
            }
            temp_v0_obj->trans.flags &= ~OBJ_FLAGS_INVISIBLE;
            temp_v0_obj = obj->attachPoints->obj[1];
            if (temp_v0_obj->trans.y_position > 0.0f) {
                temp_v0_obj->trans.y_position = temp_v0_obj->trans.y_position - 2.0;
            } else {
                temp_v0_obj->trans.y_position = 0.0f;
            }
            temp_v0_obj->trans.flags &= ~OBJ_FLAGS_INVISIBLE;
        } else {
            temp_v0_obj = obj->attachPoints->obj[0];
            if (temp_v0_obj->trans.y_position < 20.0f) {
                temp_v0_obj->trans.y_position = temp_v0_obj->trans.y_position + 1.0f;
            } else {
                temp_v0_obj->trans.flags |= OBJ_FLAGS_INVISIBLE;
            }
            temp_v0_obj = obj->attachPoints->obj[1];
            if (temp_v0_obj->trans.y_position < 20.0f) {
                temp_v0_obj->trans.y_position = temp_v0_obj->trans.y_position + 1.0f;
            } else {
                temp_v0_obj->trans.flags |= OBJ_FLAGS_INVISIBLE;
            }
        }
    }
    if (gCurrentPlayerIndex != PLAYER_COMPUTER && racer->boostTimer == 0 && gNumViewports < 2) {
        boostObj = (Object_Boost *) get_misc_asset(ASSET_MISC_20);
        boostObj = &boostObj[racer->racerIndex];
        var_t0 = ((racer->boostType & EMPOWER_BOOST) >> 2) + 9;
        if (var_t0 >= 10) {
            if (boostObj->unk70 > 0 || boostObj->unk74 > 0.0) {
                obj->particleEmittersEnabled |= 1 << var_t0;
            }
        } else {
            if (boostObj->unk70 == 2 && boostObj->unk74 < 0.5) {
                obj->particleEmittersEnabled |= 1 << var_t0;
            } else if (boostObj->unk70 < 2 && boostObj->unk74 > 0.0f) {
                obj->particleEmittersEnabled |= 1 << var_t0;
            }
        }
    }
    if (gCurrentPlayerIndex == PLAYER_COMPUTER) {
        obj->particleEmittersEnabled = OBJ_EMIT_NONE;
    }
    if (racer->unk201 == 0) {
        obj->particleEmittersEnabled = OBJ_EMIT_NONE;
    }
    if (racer->vehicleIDPrev < VEHICLE_BOSSES) {
        update_vehicle_particles(obj, updateRate);
    }
    if (spA1 != FALSE) {
        gCurrentRacerInput |= R_TRIG;
    }
    second_racer_camera_update(obj, racer, 1, updateRateF);
    if (playerObjectMoved != FALSE) {
        func_800230D0(obj, racer);
    }
}
