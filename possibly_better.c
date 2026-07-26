// trackmenu_render_names
#define NO_RENDER                   0
#define PREVIEW_WIZPIG              1
#define PREVIEW_TAJ                 2

#define WORLD_DF                    3
#define WORLD_FFL                   4

#define RACE_TROPHY                 4
#define RACE_MINIGAME               5

#define RACE_NOT_VISITED           -1

#define TROPHY_WON                  3
void func_8008FF1C(UNUSED s32 updateRate) {
    s32 i;
    s32 tempInt;

    char *tempChar;
    char *hubName;
    
    s32 trackCursorX;
    s32 tempInt2;
    s32 trackCursorY;
    s32 maxTrackY;
    
    s8 *trackMenuIds;
    Settings *settings;
    TrackRenderDetails *cur;
    
    s32 trackX;
    s32 trackY;
    s32 j;
    s32 startIndex;
    

    
    settings = get_settings();
    trackMenuIds = (s8 *) get_misc_asset(ASSET_MISC_TRACKS_MENU_IDS);
    
    if (gMenuDelay <= -23 || gMenuDelay >= 23) {
        return;
    }

    maxTrackY = (gFFLUnlocked == -1) ? WORLD_DF : WORLD_FFL;

    trackCursorX = gTrackSelectX / X_TILE_SIZE;
    trackCursorY = (s32)(gTrackSelectY / -gTrackSelectViewportY);
    
    
    startIndex = -1;
    for (i = startIndex, cur = gTrackSelectRenderDetails; i < 2; i++, trackY++) {
        trackY = trackCursorY + i;
        for (j = startIndex; j < 2; j++, cur++) {
            trackX = trackCursorX + j;
            if (trackY < 0 || trackY > maxTrackY || trackX < 0 || trackX > 5) {
                cur->visible = NO_RENDER;
            }
            else {
                cur->visible = PREVIEW_WIZPIG;
                cur->hubName = get_level_name(get_hub_area_id(trackY + 1));
                if (gTrackSelectIDs[trackY][trackX] != -1) {
                    cur->trackName = get_level_name(trackMenuIds[(trackY * 6) + trackX]);
                    if (trackX == RACE_TROPHY) {
                        if (((settings->trophies >> (trackY * 2)) & TROPHY_WON) == TROPHY_WON) {
                            cur->visible = PREVIEW_TAJ;
                        }
                    }
                    else if (settings->courseFlagsPtr[trackMenuIds[(trackY * 6) + trackX]] & 2) {
                        cur->visible = PREVIEW_TAJ;
                    }
                }
                else {
                    cur->trackName = (char*)gQMarkPtr;
                }
                
                cur->xOff = (trackX * X_TILE_SIZE) - gTrackSelectX;
                cur->yOff = (gTrackSelectViewportY * -trackY) - gTrackSelectY;
                cur->opacity = 0xFF;
                
                if (trackX == gSelectedTrackX && trackY == gSelectedTrackY) {
                    cur->vp1 = 1;
                    if (gOpacityDecayTimer < 32) {
                        cur->opacity = gOpacityDecayTimer * 8;
                    }
                }
                else {
                    cur->vp1 = 0;
                }
                
                cur->vp2 = 0;
                
                if (gMenuDelay == 0) {
                    if (trackY > 0) {
                        cur->vp2 |= 1;
                    }
                    if (trackX < 5) {
                        cur->vp2 |= 2;
                    }
                    if (trackY < maxTrackY) {
                        cur->vp2 |= 4;
                    }
                    if (trackX > 0) {
                        cur->vp2 |= 8;
                    }
                    if (trackX == RACE_TROPHY && trackY == WORLD_FFL) {
                        cur->vp2 &= ~2;
                    }
                    if (trackX == RACE_MINIGAME && trackY == WORLD_DF) {
                        cur->vp2 &= ~4;
                    }
                }
                
                if (trackX == RACE_TROPHY) {
                    cur->border = 6;
                }
                else if (trackX == RACE_MINIGAME) {
                    cur->border = 5;
                }
                else {
                    cur->border = 4;
                }
            }
        }
    }
    
    camDisableUserView(0, TRUE);
    menu_camera_centre();
    set_ortho_matrix_view(&sMenuCurrDisplayList, &sMenuCurrHudMat);
    rendermode_reset(&sMenuCurrDisplayList);
    gDPPipeSync(sMenuCurrDisplayList++);
    
    D_80126928 = 64;
    D_8012692C = 32;
    gTrackMenuHubName = NULL;

    for (i = 0; i < ARRAY_COUNT(gTrackSelectRenderDetails); i++) {
        if (gTrackSelectRenderDetails[i].visible != 0) {
            trackmenu_render_2D(gTrackSelectRenderDetails[i].xOff, gTrackSelectRenderDetails[i].yOff,
                                gTrackSelectRenderDetails[i].hubName, gTrackSelectRenderDetails[i].trackName,
                                gTrackSelectRenderDetails[i].opacity, gTrackSelectRenderDetails[i].border,
                                gTrackSelectRenderDetails[i].vp1,
                                (gTrackSelectRenderDetails[i].visible == 1) ? D_800E05D4 : D_800E05F4,
                                gTrackSelectRenderDetails[i].vp2);
        }
    }


    gTrackSelectVertsFlip = 1 - gTrackSelectVertsFlip;
}
