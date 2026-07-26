typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;
typedef signed char s8;
typedef short s16;
typedef long s32;
typedef long long s64;
typedef volatile unsigned char vu8;
typedef volatile unsigned short vu16;
typedef volatile unsigned long vu32;
typedef volatile unsigned long long vu64;
typedef volatile signed char vs8;
typedef volatile short vs16;
typedef volatile long vs32;
typedef volatile long long vs64;
typedef float f32;
typedef double f64;
typedef unsigned int size_t;
typedef float MtxF[4][4];
typedef s32 MtxS[4][4];
typedef s16 VertexList;
typedef u8 TriangleList;
typedef u32 uintptr_t;
typedef struct LevelObjectEntryCommon {
    u8 objectID;
    u8 size;
    s16 x, y, z;
} LevelObjectEntryCommon;
typedef struct LevelObjectEntry_Racer {
               LevelObjectEntryCommon common;
               s16 angleZ;
               s16 angleX;
               s16 angleY;
               s16 playerIndex;
} LevelObjectEntry_Racer;
typedef struct LevelObjectEntry_Scenery {
               LevelObjectEntryCommon common;
               u8 modelIndex;
               u8 radius;
               u8 angleY;
               u8 solid;
} LevelObjectEntry_Scenery;
typedef struct LevelObjectEntry_Animator {
               LevelObjectEntryCommon common;
               s8 batchID;
               s8 speedFactorX;
               s8 speedfactorY;
               s8 padB;
} LevelObjectEntry_Animator;
typedef struct LevelObjectEntry_Weapon {
               LevelObjectEntryCommon common;
} LevelObjectEntry_Weapon;
typedef struct LevelObjectEntry_Smoke {
               LevelObjectEntryCommon common;
} LevelObjectEntry_Smoke;
typedef struct LevelObjectEntry_Exit {
               LevelObjectEntryCommon common;
               u8 destinationMapId;
               u8 pad9;
               s8 overworldSpawnIndex;
               u8 padB[5];
               u8 radius;
               u8 angleY;
               u8 pad12[5];
               u8 returnSpawnIndex;
               s8 bossFlag;
               u8 pad19;
} LevelObjectEntry_Exit;
typedef struct LevelObjectEntry_Audio {
               LevelObjectEntryCommon common;
               u16 soundId;
               u16 range;
               u8 volume;
               u8 minVolume;
               u8 pitch;
               u8 fastFalloff;
               u8 priority;
               u8 unk11;
} LevelObjectEntry_Audio;
typedef struct LevelObjectEntry_AudioLine {
               LevelObjectEntryCommon common;
               u8 unk8;
               u8 unk9;
               u16 soundID;
               u8 lineID;
               u8 unkD;
               u16 unkE;
               u8 unk10;
               u8 unk11;
               u8 unk12;
               u8 unk13;
} LevelObjectEntry_AudioLine;
typedef struct LevelObjectEntry_CameraControl {
               LevelObjectEntryCommon common;
               s8 cameraID;
               s8 pad9;
} LevelObjectEntry_CameraControl;
typedef struct LevelObjectEntry_SetupPoint {
               LevelObjectEntryCommon common;
               u8 racerIndex;
               u8 entranceID;
               u8 angleY;
               s8 vehicle;
} LevelObjectEntry_SetupPoint;
typedef struct LevelObjectEntry_Dino_Whale {
               LevelObjectEntryCommon common;
} LevelObjectEntry_Dino_Whale;
typedef struct LevelObjectEntry_Checkpoint {
               LevelObjectEntryCommon common;
               u8 scale;
               u8 index;
               u8 angleY;
               s8 unkB;
               s8 unkC;
               s8 unkD;
               s8 unkE;
               s8 unkF;
               s8 unk10;
               s8 unk11;
               s8 unk12;
               s8 unk13;
               s8 unk14;
               s8 unk15;
               s8 unk16;
               u8 isAltCheckpoint;
               s8 unk18;
               u8 unk19;
               s8 vehicleType;
               u8 unk1B;
} LevelObjectEntry_Checkpoint;
typedef struct LevelObjectEntry_Door {
               LevelObjectEntryCommon common;
               u8 closedRotation;
               u8 openRotation;
               u8 modelIndex;
               u8 distanceToOpen;
               s8 doorID;
               u8 balloonCount;
               u8 doorType;
               u8 textID;
               u8 unk10;
               s8 keyID;
               u8 scale;
               s8 localBalloons;
               s8 levelID;
               u8 balloonCountOverride;
} LevelObjectEntry_Door;
typedef struct LevelObjectEntry_FogChanger {
               LevelObjectEntryCommon common;
               u8 distance;
               u8 r;
               u8 g;
               u8 b;
               s16 near;
               s16 far;
               s16 switchTimer;
} LevelObjectEntry_FogChanger;
typedef struct LevelObjectEntry_AiNode {
               LevelObjectEntryCommon common;
               u8 unk8;
               u8 nodeID;
               u8 adjacent[4];
               s8 elevation;
               s8 padF;
} LevelObjectEntry_AiNode;
typedef struct LevelObjectEntry_WeaponBalloon {
               LevelObjectEntryCommon common;
               u8 unk8;
               u8 balloonType;
               u8 scale;
               u8 padB;
} LevelObjectEntry_WeaponBalloon;
typedef struct LevelObjectEntry_AudioSeqLine {
               LevelObjectEntryCommon common;
               u8 unk8[0xC];
} LevelObjectEntry_AudioSeqLine;
typedef struct LevelObjectEntry_BombExplosion {
               LevelObjectEntryCommon common;
               s8 opacity_hi;
} LevelObjectEntry_BombExplosion;
typedef struct LevelObjectEntry_WBalloonPop {
               LevelObjectEntryCommon common;
} LevelObjectEntry_WBalloonPop;
typedef struct LevelObjectEntry_Unknown25 {
               LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown25;
typedef struct LevelObjectEntry_SkyControl {
               LevelObjectEntryCommon common;
               u8 setting;
               u8 radius;
} LevelObjectEntry_SkyControl;
typedef struct LevelObjectEntry_AudioReverb {
               LevelObjectEntryCommon common;
               u8 magnitude;
               u8 lineID;
               u8 vertexIndex;
               u8 unkB;
} LevelObjectEntry_AudioReverb;
typedef struct LevelObjectEntry_Torch_Mist {
               LevelObjectEntryCommon common;
               u8 animSpeed;
               u8 radius;
               u8 unkA;
               u8 unkB;
} LevelObjectEntry_Torch_Mist;
typedef struct LevelObjectEntry_TexScroll {
               LevelObjectEntryCommon common;
               s16 textureIndex;
               s8 unkA;
               s8 unkB;
} LevelObjectEntry_TexScroll;
typedef struct LevelObjectEntry_ModeChange {
               LevelObjectEntryCommon common;
               u8 radius;
               u8 angleY;
               u8 vehicleID;
               u8 padB;
} LevelObjectEntry_ModeChange;
typedef struct LevelObjectEntry_StopWatchMan {
               LevelObjectEntryCommon common;
               u8 unk8[4];
} LevelObjectEntry_StopWatchMan;
typedef struct LevelObjectEntry_Banana {
               LevelObjectEntryCommon common;
} LevelObjectEntry_Banana;
typedef struct LevelObjectEntry_RgbaLight {
               LevelObjectEntryCommon common;
               u8 unk8;
               u8 unk9;
               u8 colourR;
               u8 colourG;
               u8 colourB;
               u8 intensity;
               s16 radius;
               s16 unk10;
               s16 unk12;
               s16 unk14;
               s16 unk16;
               s16 unk18;
               s16 unk1A;
               u8 unk1C;
} LevelObjectEntry_RgbaLight;
typedef struct LevelObjectEntry_Buoy_PirateShip {
               LevelObjectEntryCommon common;
               u8 unk8[4];
} LevelObjectEntry_Buoy_PirateShip;
typedef struct LevelObjectEntry_Weather {
               LevelObjectEntryCommon common;
               s16 radius;
               s16 unkA;
               s16 unkC;
               s16 unkE;
               u8 unk10;
               u8 unk11;
               s16 unk12;
} LevelObjectEntry_Weather;
typedef struct LevelObjectEntry_Bridge_WhaleRamp {
               LevelObjectEntryCommon common;
               u8 modelIndex;
               u8 angleY;
               u8 unkA;
               u8 unkB;
               u8 radius;
               u8 unkD;
               s8 bobAmount;
               u8 allowedVehicles;
} LevelObjectEntry_Bridge_WhaleRamp;
typedef struct LevelObjectEntry_RampSwitch {
               LevelObjectEntryCommon common;
               u8 unk8;
               u8 unk9;
} LevelObjectEntry_RampSwitch;
typedef struct LevelObjectEntry_SeaMonster {
               LevelObjectEntryCommon common;
} LevelObjectEntry_SeaMonster;
typedef struct LevelObjectEntry_Bonus {
               LevelObjectEntryCommon common;
               u8 radius;
               u8 angleY;
               u8 unkA;
} LevelObjectEntry_Bonus;
typedef struct LevelObjectEntry_LensFlare {
               LevelObjectEntryCommon common;
               s16 angleX;
               s16 angleY;
               u8 set1;
               u8 set2;
               u8 largeShine;
               u8 padA;
               u8 red;
               u8 green;
               u8 blue;
               u8 alpha;
} LevelObjectEntry_LensFlare;
typedef struct LevelObjectEntry_LensFlareSwitch {
               LevelObjectEntryCommon common;
               s16 radius;
               u8 pad[10];
} LevelObjectEntry_LensFlareSwitch;
typedef struct LevelObjectEntry_CollectEgg {
               LevelObjectEntryCommon common;
} LevelObjectEntry_CollectEgg;
typedef struct LevelObjectEntry_EggCreator {
               LevelObjectEntryCommon common;
} LevelObjectEntry_EggCreator;
typedef struct LevelObjectEntry_CharacterFlag {
               LevelObjectEntryCommon common;
               s16 angleZ;
               s16 radius;
               s16 angleY;
               s16 playerIndex;
} LevelObjectEntry_CharacterFlag;
typedef struct LevelObjectEntry_Animation {
               LevelObjectEntryCommon common;
               u8 z_rotation;
               u8 x_rotation;
               u8 y_rotation;
               u8 scale;
               s16 objectIdToSpawn;
               s16 animationStartDelay;
               s8 actorIndex;
               s8 order;
               s8 objAnimIndex;
               s8 unk13;
               s8 nodeSpeed;
               s8 unk15;
               u8 unk16;
               s8 objAnimSpeed;
               u8 objAnimLoopType;
               u8 rotateType;
               s8 yawSpinSpeed;
               s8 rollSpinSpeed;
               s8 pitchSpinSpeed;
               s8 goToNode;
               u8 unk1E;
               s8 unk1F;
               s8 unk20;
               s8 channel;
               s8 unk22;
               s8 unk23;
               s16 pauseFrameCount;
               s8 specialHide;
               u8 messageId;
               s8 unk28;
               s8 unk29;
               s8 unk2A;
               s8 fadeAlpha;
               s8 nextAnim;
               s8 unk2D;
               s8 soundEffect;
               s8 fadeOptions;
               s8 unk30;
               u8 unk31;
} LevelObjectEntry_Animation;
typedef struct LevelObjectEntry_InfoPoint {
               LevelObjectEntryCommon common;
               u8 hitbox[3];
               u8 unkB;
} LevelObjectEntry_InfoPoint;
typedef struct LevelObjectEntry_Trigger {
               LevelObjectEntryCommon common;
               u8 scale;
               s8 index;
               u8 angleY;
               u8 unkB;
               u8 unkC;
               u8 unkD;
} LevelObjectEntry_Trigger;
typedef struct LevelObjectEntry_AirZippers_WaterZippers {
               LevelObjectEntryCommon common;
               u8 unk8;
               u8 radius;
               u8 angleY;
               u8 padB;
} LevelObjectEntry_AirZippers_WaterZippers;
typedef struct LevelObjectEntry_TimeTrial_Ghost {
               LevelObjectEntryCommon common;
} LevelObjectEntry_TimeTrial_Ghost;
typedef struct LevelObjectEntry_Butterfly {
               LevelObjectEntryCommon common;
               u16 unk8;
               u8 unkA;
               u8 unkB;
} LevelObjectEntry_Butterfly;
typedef struct LevelObjectEntry_Fish {
               LevelObjectEntryCommon common;
               u16 unk8;
               u8 unkA;
               u8 unkB;
               u8 unkC;
               u8 unkD;
               u8 unkE;
               u8 unkF;
} LevelObjectEntry_Fish;
typedef struct LevelObjectEntry_Parkwarden {
               LevelObjectEntryCommon common;
} LevelObjectEntry_Parkwarden;
typedef struct LevelObjectEntry_WorldKey {
               LevelObjectEntryCommon common;
               u8 keyID;
               u8 pad9;
} LevelObjectEntry_WorldKey;
typedef struct LevelObjectEntry_BananaCreator {
               LevelObjectEntryCommon common;
} LevelObjectEntry_BananaCreator;
typedef struct LevelObjectEntry_TreasureSucker {
               LevelObjectEntryCommon common;
               s8 playerID;
               u8 pad9;
} LevelObjectEntry_TreasureSucker;
typedef struct LevelObjectEntry_Log {
               LevelObjectEntryCommon common;
               u8 modelIndex;
               u8 radius;
               u8 angleY;
               u8 padB;
} LevelObjectEntry_Log;
typedef struct LevelObjectEntry_LavaSpurt {
               LevelObjectEntryCommon common;
               u8 delayTimer;
               u8 initialTimer;
} LevelObjectEntry_LavaSpurt;
typedef struct LevelObjectEntry_PosArrow {
               LevelObjectEntryCommon common;
} LevelObjectEntry_PosArrow;
typedef struct LevelObjectEntry_HitTester {
               LevelObjectEntryCommon common;
} LevelObjectEntry_HitTester;
typedef struct LevelObjectEntry_MidiFade {
               LevelObjectEntryCommon common;
               u8 scale;
               u8 angleY;
               u8 unkA[16];
               u8 unk1A;
               u8 unk1B;
} LevelObjectEntry_MidiFade;
typedef struct LevelObjectEntry_DynamicLightingObject {
               LevelObjectEntryCommon common;
} LevelObjectEntry_DynamicLightingObject;
typedef struct LevelObjectEntry_EffectBox {
               LevelObjectEntryCommon common;
               u8 unk8;
               u8 unk9;
               u8 unkA;
               u8 unkB;
               u8 unkC;
               u8 unkD;
               u8 unkE;
               u8 unkF;
} LevelObjectEntry_EffectBox;
typedef struct LevelObjectEntry_TrophyCab {
               LevelObjectEntryCommon common;
               u8 angleY;
               u8 pad9;
} LevelObjectEntry_TrophyCab;
typedef struct LevelObjectEntry_Bubbler {
               LevelObjectEntryCommon common;
               u8 particlePropertyID;
               u8 particleBehaviourID;
               u16 particleDensity;
               u8 unkC[4];
} LevelObjectEntry_Bubbler;
typedef struct LevelObjectEntry_FlyCoin {
               LevelObjectEntryCommon common;
} LevelObjectEntry_FlyCoin;
typedef struct LevelObjectEntry_GoldenBalloon {
               LevelObjectEntryCommon common;
               s8 balloonID;
               u8 scale;
               s8 challengeID;
               u8 padB;
} LevelObjectEntry_GoldenBalloon;
typedef struct LevelObjectEntry_Laserbolt {
               LevelObjectEntryCommon common;
} LevelObjectEntry_Laserbolt;
typedef struct LevelObjectEntry_Lasergun {
               LevelObjectEntryCommon common;
               u8 angleY;
               u8 angleX;
               s8 targeting;
               s8 fireRate;
               u8 laserDuration;
               u8 radius;
} LevelObjectEntry_Lasergun;
typedef struct LevelObjectEntry_GroundZipper {
               LevelObjectEntryCommon common;
               u8 unk8;
               u8 scale;
               u8 angleY;
               u8 unkB;
} LevelObjectEntry_GroundZipper;
typedef struct LevelObjectEntry_OverridePos {
               LevelObjectEntryCommon common;
               s8 behaviorId;
               s8 cutsceneId;
} LevelObjectEntry_OverridePos;
typedef struct LevelObjectEntry_WizpigShip {
               LevelObjectEntryCommon common;
} LevelObjectEntry_WizpigShip;
typedef struct LevelObjectEntry_SilverCoin {
               LevelObjectEntryCommon common;
} LevelObjectEntry_SilverCoin;
typedef struct LevelObjectEntry_Boost {
               LevelObjectEntryCommon common;
} LevelObjectEntry_Boost;
typedef struct LevelObjectEntry_Boost2 {
               LevelObjectEntryCommon common;
               s8 racerIndex;
} LevelObjectEntry_Boost2;
typedef struct LevelObjectEntry_WardenSmoke {
               LevelObjectEntryCommon common;
} LevelObjectEntry_WardenSmoke;
typedef struct LevelObjectEntry_Unknown94 {
               LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown94;
typedef struct LevelObjectEntry_Unknown96 {
               LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown96;
typedef struct LevelObjectEntry_Snowball {
               LevelObjectEntryCommon common;
} LevelObjectEntry_Snowball;
typedef struct LevelObjectEntry_Teleport {
               LevelObjectEntryCommon common;
               s8 levelID;
               u8 pad9;
} LevelObjectEntry_Teleport;
typedef struct LevelObjectEntry_Lighthouse_RocketSignpost {
               LevelObjectEntryCommon common;
               u8 unk8;
               u8 radius;
               u8 angleY;
               u8 padB;
} LevelObjectEntry_Lighthouse_RocketSignpost;
typedef struct LevelObjectEntry_Windsail {
               LevelObjectEntryCommon common;
} LevelObjectEntry_Windsail;
typedef struct LevelObjectEntry_RangeTrigger {
               LevelObjectEntryCommon common;
               u16 radius;
               u16 particleFlags;
} LevelObjectEntry_RangeTrigger;
typedef struct LevelObjectEntry_Fireball_Octoweapon {
               LevelObjectEntryCommon common;
} LevelObjectEntry_Fireball_Octoweapon;
typedef struct LevelObjectEntry_Frog {
               LevelObjectEntryCommon common;
               s16 homeRadius;
               u8 drumstick;
               u8 padB;
} LevelObjectEntry_Frog;
typedef struct LevelObjectEntry_SilverCoinAdv2 {
               LevelObjectEntryCommon common;
} LevelObjectEntry_SilverCoinAdv2;
typedef struct LevelObjectEntry_TTDoor {
               LevelObjectEntryCommon common;
               u8 angleY;
               u8 unk9;
               u8 radius;
               u8 textID;
               u8 scale;
               u8 padD;
               s8 doorType;
               s8 padF;
} LevelObjectEntry_TTDoor;
typedef struct LevelObjectEntry_MidiFadePoint {
               LevelObjectEntryCommon common;
               u16 unk8;
               u16 unkA;
               u8 unkC[16];
               u8 unk1C;
               u8 unk1D;
} LevelObjectEntry_MidiFadePoint;
typedef struct LevelObjectEntry_OctoBubble {
               LevelObjectEntryCommon common;
} LevelObjectEntry_OctoBubble;
typedef struct LevelObjectEntry_LevelName {
               LevelObjectEntryCommon common;
               s8 levelID;
               s8 radius;
} LevelObjectEntry_LevelName;
typedef struct LevelObjectEntry_Midichset {
               LevelObjectEntryCommon common;
               u16 unk8;
               u8 unkA;
               u8 unkB;
} LevelObjectEntry_Midichset;
typedef struct LevelObjectEntry8000E2B4 {
    LevelObjectEntryCommon common;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
} LevelObjectEntry8000E2B4;
typedef struct LevelObjectEntry80011AD0 {
    LevelObjectEntryCommon common;
    u8 pad8[0x6];
    u8 unkD;
} LevelObjectEntry80011AD0;
typedef struct LevelObjectEntry8003FC44 {
    LevelObjectEntryCommon common;
    s8 unk9;
    s8 unkA;
} LevelObjectEntry8003FC44;
typedef struct LevelObjectEntry_WaveGenerator {
    LevelObjectEntryCommon common;
    u8 unk8;
    u8 unk9;
    u16 waveSize;
    u16 unkC;
    u16 unkE;
    u8 unk10;
    u8 unk11;
} LevelObjectEntry_WaveGenerator;
typedef struct LevelObjectEntry_WavePower {
    LevelObjectEntryCommon common;
    u16 radius;
    u16 power;
    u16 divisor;
} LevelObjectEntry_WavePower;
typedef struct LevelObjectEntry_CharacterSelect {
    LevelObjectEntryCommon common;
    u8 pad8[0xA];
    s8 unk12;
    s8 unk13;
    s8 unk14;
    s8 unk15;
    u8 unk16;
    s8 unk17;
    u8 unk18;
    s8 pad19[5];
    u8 unk1E;
    s8 unk1F;
    s8 pad20[4];
    s16 unk24;
    s8 unk26;
    u8 unk27;
    s8 unk28;
    s8 unk29;
    s8 unk2A;
    s8 unk2B;
    s8 unk2C;
    s8 unk2D;
    s8 unk2E;
    s8 unk2F;
    s8 unk30;
} LevelObjectEntry_CharacterSelect;
typedef struct LevelObjectEntry_Unk8000CC7C {
    LevelObjectEntryCommon common;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
} LevelObjectEntry_Unk8000CC7C;
typedef struct LevelObjectEntry_Unknown20 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown20;
typedef struct LevelObjectEntry_Unknown21 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown21;
typedef struct LevelObjectEntry_Unknown24 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown24;
typedef struct LevelObjectEntry_Unknown34 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown34;
typedef struct LevelObjectEntry_Unknown35 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown35;
typedef struct LevelObjectEntry_Unknown42 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown42;
typedef struct LevelObjectEntry_Unknown48 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown48;
typedef struct LevelObjectEntry_Unknown63 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown63;
typedef struct LevelObjectEntry_Unknown91 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown91;
typedef struct LevelObjectEntry_Unknown92 {
    LevelObjectEntryCommon common;
    u8 unk8;
    u8 unk9;
} LevelObjectEntry_Unknown92;
typedef struct LevelObjectEntry_Unknown106 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown106;
typedef struct LevelObjectEntry_Unknown114 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown114;
typedef struct LevelObjectEntry_AnimatedObject {
    LevelObjectEntryCommon common;
} LevelObjectEntry_AnimatedObject;
typedef struct LevelObjectEntry_DynamicLightObject2 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_DynamicLightObject2;
typedef struct LevelObjectEntry_ParkWarden {
    LevelObjectEntryCommon common;
} LevelObjectEntry_ParkWarden;
typedef struct LevelObjectEntry_TajTelepoint {
    LevelObjectEntryCommon common;
} LevelObjectEntry_TajTelepoint;
typedef struct LevelObjectEntry_CameraAnimation {
    LevelObjectEntryCommon common;
} LevelObjectEntry_CameraAnimation;
typedef struct LevelObjectEntry_BossHazardTrigger {
    LevelObjectEntryCommon common;
    u8 unk8[4];
} LevelObjectEntry_BossHazardTrigger;
typedef struct LevelObjectEntry_DoorOpener {
    LevelObjectEntryCommon common;
} LevelObjectEntry_DoorOpener;
typedef struct LevelObjectEntry_PigRocketeer {
    LevelObjectEntryCommon common;
} LevelObjectEntry_PigRocketeer;
typedef struct LevelObjectEntry_WizpigGhosts {
    LevelObjectEntryCommon common;
} LevelObjectEntry_WizpigGhosts;
typedef struct LevelObjectEntry_Unknown120 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown120;
typedef struct LevelObjectEntry_Unknown121 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown121;
typedef struct LevelObjectEntry_Unknown122 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown122;
typedef struct LevelObjectEntry_Unknown123 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown123;
typedef struct LevelObjectEntry_Unknown124 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown124;
typedef struct LevelObjectEntry_Unknown125 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown125;
typedef struct LevelObjectEntry_Unknown126 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown126;
typedef struct LevelObjectEntry_Unknown127 {
    LevelObjectEntryCommon common;
} LevelObjectEntry_Unknown127;
typedef struct LevelObjectEntry_Hud {
    LevelObjectEntryCommon common;
    s32 offsetY;
} LevelObjectEntry_Hud;
typedef struct LevelObjectEntry_BHV_UNK_5C {
    LevelObjectEntryCommon common;
    s8 unk8;
    s8 unk9;
} LevelObjectEntry_BHV_UNK_5C;
typedef struct LevelObjectEntry {
    union {
        LevelObjectEntry_Racer racer;
        LevelObjectEntry_Scenery scenery;
        LevelObjectEntry_Fish fish;
        LevelObjectEntry_Animator animator;
        LevelObjectEntry_Weapon weapon;
        LevelObjectEntry_Smoke smoke;
        LevelObjectEntry_Exit exit;
        LevelObjectEntry_Audio audio;
        LevelObjectEntry_AudioLine audioLine;
        LevelObjectEntry_CameraControl cameraControl;
        LevelObjectEntry_SetupPoint setupPoint;
        LevelObjectEntry_Dino_Whale dino_whale;
        LevelObjectEntry_Checkpoint checkpoint;
        LevelObjectEntry_Door door;
        LevelObjectEntry_FogChanger fogChanger;
        LevelObjectEntry_AiNode aiNode;
        LevelObjectEntry_WeaponBalloon weaponBalloon;
        LevelObjectEntry_AudioSeqLine audioSeqLine;
        LevelObjectEntry_BombExplosion bombExplosion;
        LevelObjectEntry_WBalloonPop balloonPop;
        LevelObjectEntry_Unknown25 unk25;
        LevelObjectEntry_SkyControl skyControl;
        LevelObjectEntry_AudioReverb audioReverb;
        LevelObjectEntry_Torch_Mist torch_mist;
        LevelObjectEntry_TexScroll texScroll;
        LevelObjectEntry_ModeChange modeChange;
        LevelObjectEntry_StopWatchMan tt;
        LevelObjectEntry_Banana banana;
        LevelObjectEntry_RgbaLight rgbaLighting;
        LevelObjectEntry_Buoy_PirateShip buoy_pirateShip;
        LevelObjectEntry_Weather weather;
        LevelObjectEntry_Bridge_WhaleRamp bridge_whaleRamp;
        LevelObjectEntry_RampSwitch rampSwitch;
        LevelObjectEntry_SeaMonster seaMonster;
        LevelObjectEntry_Bonus bonus;
        LevelObjectEntry_LensFlare lensFlare;
        LevelObjectEntry_LensFlareSwitch lensFlareSwitch;
        LevelObjectEntry_CollectEgg collectEgg;
        LevelObjectEntry_EggCreator eggCreator;
        LevelObjectEntry_CharacterFlag characterFlag;
        LevelObjectEntry_Animation animation;
        LevelObjectEntry_InfoPoint infoPoint;
        LevelObjectEntry_Trigger trigger;
        LevelObjectEntry_AirZippers_WaterZippers airzipper_waterzipper;
        LevelObjectEntry_TimeTrial_Ghost ghost;
        LevelObjectEntry_Butterfly butterfly;
        LevelObjectEntry_Parkwarden taj;
        LevelObjectEntry_WorldKey worldKey;
        LevelObjectEntry_BananaCreator bananaCreator;
        LevelObjectEntry_TreasureSucker treasureSucker;
        LevelObjectEntry_Log log;
        LevelObjectEntry_LavaSpurt lavaSpurt;
        LevelObjectEntry_PosArrow posArrow;
        LevelObjectEntry_HitTester hitTester;
        LevelObjectEntry_MidiFade midiFade;
        LevelObjectEntry_DynamicLightingObject dynamicLighting;
        LevelObjectEntry_EffectBox effectBox;
        LevelObjectEntry_TrophyCab trophyCabinet;
        LevelObjectEntry_Bubbler bubbler;
        LevelObjectEntry_FlyCoin flyCoin;
        LevelObjectEntry_GoldenBalloon goldenBalloon;
        LevelObjectEntry_Laserbolt laserbolt;
        LevelObjectEntry_Lasergun lasergun;
        LevelObjectEntry_GroundZipper groundZipper;
        LevelObjectEntry_OverridePos overridePos;
        LevelObjectEntry_WizpigShip wizpigShip;
        LevelObjectEntry_SilverCoin silverCoin;
        LevelObjectEntry_Boost boost;
        LevelObjectEntry_WardenSmoke tajSmoke;
        LevelObjectEntry_Unknown94 unk94;
        LevelObjectEntry_Unknown96 unk96;
        LevelObjectEntry_Snowball snowball;
        LevelObjectEntry_Teleport teleport;
        LevelObjectEntry_Lighthouse_RocketSignpost lighthouse_signpost;
        LevelObjectEntry_Windsail windsail;
        LevelObjectEntry_RangeTrigger rangeTrigger;
        LevelObjectEntry_Fireball_Octoweapon fireball_octoweapon;
        LevelObjectEntry_Frog frog;
        LevelObjectEntry_SilverCoinAdv2 silverCoinAdv2;
        LevelObjectEntry_TTDoor ttDoor;
        LevelObjectEntry_MidiFadePoint midiFadePoint;
        LevelObjectEntry_OctoBubble octoBubble;
        LevelObjectEntry_LevelName levelName;
        LevelObjectEntry_Midichset midichset;
        LevelObjectEntry8000E2B4 unk8000E2B4;
        LevelObjectEntry80011AD0 unk80011AD0;
        LevelObjectEntry8003FC44 unk8003FC44;
        LevelObjectEntry_WaveGenerator waveGenerator;
        LevelObjectEntry_WavePower wavePower;
        LevelObjectEntry_CharacterSelect characterSelect;
        LevelObjectEntry_Hud hud;
        LevelObjectEntry_BHV_UNK_5C bhv_unk_5C;
    };
} LevelObjectEntry;
enum SoundID {
             SOUND_NONE,
             SOUND_CAR_SLIDE,
             SOUND_CAR_SLIDE2,
             SOUND_INTRO_PLANE,
             SOUND_INTRO_KIDS,
             SOUND_UNK_05,
             SOUND_UNK_06,
             SOUND_UNK_07,
             SOUND_UNK_08,
             SOUND_STOMP,
             SOUND_UNK_0A,
             SOUND_UNK_0B,
             SOUND_CRASH,
             SOUND_CRASH_CHARACTER,
             SOUND_BALLOON_POP,
             SOUND_PLOP,
             SOUND_UNK_10,
             SOUND_EXPLOSION,
             SOUND_NYOOM,
             SOUND_UNK_13,
             SOUND_UNK_14,
             SOUND_UNK_15,
             SOUND_WHOOSH1,
             SOUND_EXPLOSION2,
             SOUND_VOICE_TT_GET_READY,
             SOUND_VOICE_TT_GO,
             SOUND_LAND_GRASS,
             SOUND_LAND_SAND,
             SOUND_CAR_BRAKE,
             SOUND_UNK_1D,
             SOUND_UNK_1E,
             SOUND_UNK_1F,
             SOUND_UNK_20,
             SOUND_NITRO_BOOST,
             SOUND_SELECT,
             SOUND_VOICE_TAJ_CUTSCENE_0,
             SOUND_VOICE_TAJ_CUTSCENE_1,
             SOUND_VOICE_TAJ_WAHEY,
             SOUND_VOICE_TAJ_HOHO,
             SOUND_LIGHTNING,
             SOUND_VOICE_TAJ_WOAH,
             SOUND_VOICE_TAJ_HINT,
             SOUND_UNK_2A,
             SOUND_RIBBIT,
             SOUND_SPLOOSH,
             SOUND_VOICE_TAJ_WINNER,
             SOUND_VOICE_CONKER_YEHAHA,
             SOUND_VOICE_TIMBER_WOW,
             SOUND_WHOOSH2,
             SOUND_WHOOSH3,
             SOUND_VOICE_TAJ_BALLOON,
             SOUND_UNK_33,
             SOUND_TWINKLE,
             SOUND_VOICE_WIZPIG_LAUGH,
             SOUND_NYOOM_HIGH,
             SOUND_UNK_37,
             SOUND_VOICE_TT_RADIO,
             SOUND_DOOR_CLOSE,
             SOUND_VOICE_TT_THREE,
             SOUND_VOICE_TT_TWO,
             SOUND_VOICE_BUMPER_OHNO,
             SOUND_VOICE_TIPTUP_WAH,
             SOUND_VOICE_TT_ONE,
             SOUND_VOICE_TT_BLASTOFF,
             SOUND_ROCKET_LAUNCH,
             SOUND_UNK_41,
             SOUND_VOICE_DIDDY_LAUGH,
             SOUND_VOICE_BANJO_GUHHUH,
             SOUND_VOICE_DIDDY_LAUGH2,
             SOUND_VOICE_PIPSY_LAUGH,
             SOUND_VOICE_TIMBER_YEAH,
             SOUND_VOICE_KRUNCH_HOHOO,
             SOUND_VOICE_WIZPIG_LAUGH_SHORT,
             SOUND_VOICE_TAJ_CUTSCENE2,
             SOUND_VOICE_PIPSY_YEHAW,
             SOUND_VOICE_TAJ_CUTSCENE3,
             SOUND_VOICE_TAJ_CUTSCENE4,
             SOUND_VOICE_DIDDY_LAUGH_LOW,
             SOUND_VOICE_UNK_4E,
             SOUND_VOICE_UNK_4F,
             SOUND_VOICE_UNK_50,
             SOUND_VOICE_WIZPIG_LAUGH2,
             SOUND_VOICE_WIZPIG_LAUGH3,
             SOUND_VOICE_WIZPIG_ENDING,
             SOUND_VOICE_WIZPIG_UNK0,
             SOUND_UNK_55,
             SOUND_VOICE_WIZPIG_SEEYA,
             SOUND_VOICE_WIZPIG_LAUGH4,
             SOUND_VOICE_BLUEY_REMATCH1,
             SOUND_VOICE_BLUEY_REMATCH2,
             SOUND_VOICE_BLUEY_REMATCH3,
             SOUND_UNK_5B,
             SOUND_UNK_5C,
             SOUND_TING_LOW,
             SOUND_TING_HIGH,
             SOUND_BOOST_LEVEL3,
             SOUND_UNK_60,
             SOUND_UNK_61,
             SOUND_ELECTRIC_BUZZ,
             SOUND_UNK_63,
             SOUND_UNK_64,
             SOUND_UNK_65,
             SOUND_VOICE_TT_WRONG_WAY,
             SOUND_VOICE_TT_NONONO,
             SOUND_MENU_BACK,
             SOUND_MENU_BACK2,
             SOUND_UNK_6A,
             SOUND_VOICE_WIZPIG_ENCOUNTER,
             SOUND_VOICE_WIZPIG_DEFEAT,
             SOUND_VOICE_WIZPIG_GROAN,
             SOUND_VOICE_WIZPIG_SCREAM,
             SOUND_ZAP,
             SOUND_ZAP2,
             SOUND_ZAP3,
             SOUND_VOICE_WIZPIG_SCREAM2,
             SOUND_VOICE_KRUNCH_LAUGH,
             SOUND_UNK_74,
             SOUND_VOICE_WIZPIG_SCREAM3,
             SOUND_VOICE_DRUMSTUCK_BWAK,
             SOUND_VOICE_BLUEY_GOODBYE,
             SOUND_VOICE_BANJO_YAHOO,
             SOUND_VOICE_BLUEY_SILVERCOINS2,
             SOUND_CAR_REV,
             SOUND_UNK_7B,
             SOUND_UNK_7C,
             SOUND_UNK_7D,
             SOUND_UNK_7E,
             SOUND_UNK_7F,
             SOUND_UNK_80,
             SOUND_UNK_81,
             SOUND_UNK_82,
             SOUND_UNK_83,
             SOUND_UNK_84,
             SOUND_VOICE_BLUEY_TROPHY_CHALLENGE,
             SOUND_VOICE_BLUEY_AMULET,
             SOUND_VOICE_KRUNCH_SELECT,
             SOUND_VOICE_BUMPER_SELECT,
             SOUND_VOICE_TIPTUP_SELECT,
             SOUND_VOICE_CONKER_SELECT,
             SOUND_VOICE_TIMBER_SELECT,
             SOUND_VOICE_BANJO_SELECT,
             SOUND_VOICE_DRUMSTICK_SELECT,
             SOUND_VOICE_PIPSY_SELECT,
             SOUND_VOICE_TT_SELECT,
             SOUND_VOICE_DIDDY_SELECT,
             SOUND_VOICE_BLUEY_RETRY,
             SOUND_VOICE_BLUEY_NEVERMIND,
             SOUND_VOICE_KRUNCH_EHH,
             SOUND_VOICE_BUMPER_UHH,
             SOUND_VOICE_TIPTUP_AHH,
             SOUND_VOICE_CONKER_AHH,
             SOUND_VOICE_TIMBER_RAGH,
             SOUND_VOICE_BANJO_WOAH,
             SOUND_VOICE_DRUMSTICK_WAH,
             SOUND_VOICE_PIPSY_UHOH,
             SOUND_VOICE_TT_WOAH,
             SOUND_VOICE_DIDDY_WOAH,
             SOUND_VOICE_BLUEY_SILVERCOINS3,
             SOUND_VOICE_BLUEY_SILVERCOINS4,
             SOUND_SHIELD,
             SOUND_COLLECT_ITEM,
             SOUND_COLLECT_ITEM_TIER2,
             SOUND_COLLECT_ITEM_TIER3,
             SOUND_VOICE_TRICKY_WOAH,
             SOUND_VOICE_TRICKY_WOAH2,
             SOUND_VOICE_TRICKY_HM,
             SOUND_VOICE_TRICKY_HMMM,
             SOUND_VOICE_BLUEY_EH,
             SOUND_VOICE_BLUEY_OHNO,
             SOUND_FLUTTERING,
             SOUND_PLANE_ENGINE,
             SOUND_BOING,
             SOUND_STOMP2,
             SOUND_STOMP3,
             SOUND_BOUNCE,
             SOUND_UNK_AF,
             SOUND_FOOTSTEP,
             SOUND_UNK_B1,
             SOUND_MENU_PICK,
             SOUND_VOICE_WIZPIG_LAUGH_SHORT2,
             SOUND_VOICE_WIZPIG_LAUGH_SHORT3,
             SOUND_VOICE_WIZPIG_HA,
             SOUND_VOICE_WIZPIG_H2,
             SOUND_VOICE_BLUEY_HAHA,
             SOUND_VOICE_BLUEY_HAHA2,
             SOUND_VOICE_BLUEY_SILVERCOINS1,
             SOUND_VOICE_TRICKY_ENCOUNTER1,
             SOUND_VOICE_TRICKY_SILVERCOINS1,
             SOUND_VOICE_TRICKY_SILVERCOINS2,
             SOUND_VOICE_TRICKY_GOODTRY,
             SOUND_VOICE_TRICKY_NEVERMIND,
             SOUND_VOICE_TRICKY_RETRY,
             SOUND_VOICE_TRICKY_SILVERCOINS6,
             SOUND_VOICE_TRICKY_TROPHY1,
             SOUND_VOICE_TRICKY_TROPHY2,
             SOUND_VOICE_TRICKY_TROPHY3,
             SOUND_VOICE_TRICKY_TROPHY4,
             SOUND_VOICE_TRICKY_SILVERCOINS4,
             SOUND_VOICE_TRICKY_SILVERCOINS5,
             SOUND_VOICE_TRICKY_REMATCH1,
             SOUND_VOICE_TRICKY_REMATCH2,
             SOUND_VOICE_TRICKY_REMATCH3,
             SOUND_VOICE_SMOKEY_ENCOUNTER1,
             SOUND_VOICE_SMOKEY_ENCOUNTER2,
             SOUND_VOICE_SMOKEY_SILVERCOINS1,
             SOUND_VOICE_SMOKEY_SILVERCOINS2,
             SOUND_VOICE_SMOKEY_GOODTRY,
             SOUND_VOICE_SMOKEY_SILVERCOINS3,
             SOUND_VOICE_SMOKEY_SILVERCOINS4,
             SOUND_UNK_D1,
             SOUND_VOICE_SMOKEY_BADLUCK,
             SOUND_VOICE_SMOKEY_RETRY,
             SOUND_VOICE_SMOKEY_TROPHY1,
             SOUND_VOICE_SMOKEY_TROPHY2,
             SOUND_VOICE_SMOKEY_TROPHY3,
             SOUND_VOICE_SMOKEY_REMATCH2,
             SOUND_VOICE_SMOKEY_REMATCH3,
             SOUND_VOICE_BUBBLER_ENCOUNTER1,
             SOUND_VOICE_BUBBLER_ENCOUNTER2,
             SOUND_VOICE_BUBBLER_SILVERCOINS1,
             SOUND_VOICE_BUBBLER_SILVERCOINS2,
             SOUND_VOICE_BUBBLER_SILVERCOINS3,
             SOUND_VOICE_BUBBLER_BADLUCK,
             SOUND_VOICE_BUBBLER_BADLUCK2,
             SOUND_VOICE_BUBBLER_RETRY,
             SOUND_VOICE_BUBBLER_TROPHY1,
             SOUND_VOICE_BUBBLER_TROPHY2,
             SOUND_VOICE_BUBBLER_TROPHY3,
             SOUND_VOICE_BUBBLER_TROPHY4,
             SOUND_VOICE_BUBBLER_REMATCH2,
             SOUND_VOICE_BUBBLER_REMATCH3,
             SOUND_VOICE_BUBBLER_SILVERCOINS4,
             SOUND_VOICE_BUBBLER_HAHA,
             SOUND_VOICE_BLUEY_ENCOUNTER1,
             SOUND_VOICE_BLUEY_ENCOUNTER2,
             SOUND_MENU_PICK2,
             SOUND_MENU_PICK3,
             SOUND_UNK_ED,
             SOUND_UNK_EE,
             SOUND_SELECT2,
             SOUND_VOICE_TRICKY_WOAH3,
             SOUND_VOICE_TRICKY_WOAH4,
             SOUND_VOICE_SMOKEY_EH,
             SOUND_VOICE_SMOKEY_HEH,
             SOUND_VOICE_BLUEY_EH2,
             SOUND_VOICE_BLUEY_OHNO2,
             SOUND_VOICE_TRICKY_LAUGH,
             SOUND_VOICE_TRICKY_LAUGH2,
             SOUND_VOICE_SMOKEY_HAH,
             SOUND_VOICE_SMOKEY_LAUGH,
             SOUND_VOICE_BLUEY_HAHA3,
             SOUND_VOICE_BLUEY_HAHA4,
             SOUND_UNK_FC,
             SOUND_CROWD,
             SOUND_HUD_LAP_TICK,
             SOUND_UNK_FF,
             SOUND_VOICE_TT_LAP2,
             SOUND_VOICE_TT_FINAL_LAP,
             SOUND_VOICE_TT_FINISH,
             SOUND_UNK_103,
             SOUND_UNK_104,
             SOUND_VOICE_TT_DIDDY_KONG_RACING,
             SOUND_VOICE_TT_PRESS_START,
             SOUND_ZIP_PAD_BOOST,
             SOUND_UNK_108,
             SOUND_UNK_109,
             SOUND_UNK_10A,
             SOUND_STOMP4,
             SOUND_STOMP5,
             SOUND_INTRO_KIDS2,
             SOUND_INTRO_PLANE2,
             SOUND_VOICE_TAJ_HELLO,
             SOUND_WHOOSH4,
             SOUND_VOICE_TAJ_BYE,
             SOUND_VOICE_TAJ_ALAKAZOOM,
             SOUND_CYMBAL,
             SOUND_SELECT3,
             SOUND_VOICE_TT_ANCIENT_LAKE,
             SOUND_VOICE_TT_BOULDER_CANYON,
             SOUND_VOICE_TT_CRESCENT_ISLAND,
             SOUND_VOICE_TT_DARKMOON_CAVERNS,
             SOUND_VOICE_TT_EVERFROST_PEAK,
             SOUND_VOICE_TT_FOSSIL_CANYON,
             SOUND_VOICE_TT_FROSTY_VILLAGE,
             SOUND_VOICE_TT_GREENWOOD_VILLAGE,
             SOUND_VOICE_TT_HOT_TOP_VOLCANO,
             SOUND_VOICE_TT_HAUNTED_WOODS,
             SOUND_VOICE_TT_JUNGLE_FALLS,
             SOUND_VOICE_TT_PIRATE_LAGOON,
             SOUND_VOICE_TT_SNOWBALL_VALLEY,
             SOUND_VOICE_TT_SPACEDUST_VALLEY,
             SOUND_VOICE_TT_SPACEPORT_ALPHA,
             SOUND_VOICE_TT_TREASURE_CAVES,
             SOUND_VOICE_TT_STAR_CITY,
             SOUND_VOICE_TT_WALRUS_COVE,
             SOUND_VOICE_TT_WINDMILL_PLAINS,
             SOUND_VOICE_TT_DINO_DOMAIN,
             SOUND_VOICE_TT_DRAGON_FOREST,
             SOUND_VOICE_TT_FUTURE_FUN_LAND,
             SOUND_VOICE_TT_ICICLE_PYRAMID,
             SOUND_VOICE_TT_SHERBET_ISLAND,
             SOUND_VOICE_TT_SNOWFLAKE_MOUNTAIN,
             SOUND_VOICE_TT_SMOKEY_CASTLE,
             SOUND_VOICE_TT_TROPHY_RACE,
             SOUND_VOICE_TT_WHALE_BAY,
             SOUND_CAR_REV2,
             SOUND_VOICE_TT_SNORE,
             SOUND_LASER_GUN,
             SOUND_NYOOM2,
             SOUND_NYOOM3,
             SOUND_HOMING_ROCKET,
             SOUND_INCOMING_ROCKET,
             SOUND_BOUNCE2,
             SOUND_WHEE,
             SOUND_MAGNET_HUM,
             SOUND_TYRE_SCREECH,
             SOUND_TWANG,
             SOUND_UNK_13D,
             SOUND_VOICE_TT_POWERUP,
             SOUND_SPLAT,
             SOUND_PLOP2,
             SOUND_VOICE_TT_INTRO,
             SOUND_VOICE_TT_SEE_YOU,
             SOUND_VOICE_TT_OK,
             SOUND_VOICE_TT_LAP_RECORD,
             SOUND_VOICE_TT_RACE_RECORD,
             SOUND_UNK_146,
             SOUND_VOICE_TT_GO_FOR_IT,
             SOUND_VOICE_TT_KEEP_GOING,
             SOUND_VOICE_TT_YOU_CAN_DO_THIS,
             SOUND_UNK_14A,
             SOUND_VOICE_TT_OH_NO,
             SOUND_VOICE_TT_TOO_BAD,
             SOUND_VOICE_TT_UNLUCKY,
             SOUND_VOICE_TT_NOT_AGAIN,
             SOUND_TING_HIGHER,
             SOUND_TING_HIGHEST,
             SOUND_SPLOINK2,
             SOUND_BUBBLE,
             SOUND_VOICE_TT_DARKWATER_BEACH,
             SOUND_VOICE_TT_FIRE_MOUNTAIN,
             SOUND_POP,
             SOUND_HORN_KRUNCH,
             SOUND_HORN_BUMPER,
             SOUND_HORN_TIPTUP,
             SOUND_HORN_CONKER,
             SOUND_HORN_TIMBER,
             SOUND_HORN_BANJO,
             SOUND_HORN_DRUMSTICK,
             SOUND_HORN_PIPSY,
             SOUND_HORN_TT,
             SOUND_HORN_DIDDY,
             SOUND_HORN_UNUSED1,
             SOUND_HORN_UNUSED2,
             SOUND_VOICE_KRUNCH_POSITIVE1,
             SOUND_VOICE_BUMPER_POSITIVE1,
             SOUND_VOICE_TIPTUP_POSITIVE1,
             SOUND_VOICE_CONKER_POSITIVE1,
             SOUND_VOICE_TIMBER_POSITIVE1,
             SOUND_VOICE_BANJO_POSITIVE1,
             SOUND_VOICE_DRUMSTICK_POSITIVE1,
             SOUND_VOICE_PIPSY_POSITIVE1,
             SOUND_VOICE_TT_POSITIVE1,
             SOUND_VOICE_DIDDY_POSITIVE1,
             SOUND_VOICE_UNUSED1_POSITIVE1,
             SOUND_VOICE_UNUSED2_POSITIVE1,
             SOUND_VOICE_KRUNCH_POSITIVE2,
             SOUND_VOICE_BUMPER_POSITIVE2,
             SOUND_VOICE_TIPTUP_POSITIVE2,
             SOUND_VOICE_CONKER_POSITIVE2,
             SOUND_VOICE_TIMBER_POSITIVE2,
             SOUND_VOICE_BANJO_POSITIVE2,
             SOUND_VOICE_DRUMSTICK_POSITIVE2,
             SOUND_VOICE_PIPSY_POSITIVE2,
             SOUND_VOICE_TT_POSITIVE2,
             SOUND_VOICE_DIDDY_POSITIVE2,
             SOUND_VOICE_UNUSED1_POSITIVE2,
             SOUND_VOICE_UNUSED2_POSITIVE2,
             SOUND_VOICE_KRUNCH_POSITIVE3,
             SOUND_VOICE_BUMPER_POSITIVE3,
             SOUND_VOICE_TIPTUP_POSITIVE3,
             SOUND_VOICE_CONKER_POSITIVE3,
             SOUND_VOICE_TIMBER_POSITIVE3,
             SOUND_VOICE_BANJO_POSITIVE3,
             SOUND_VOICE_DRUMSTICK_POSITIVE3,
             SOUND_VOICE_PIPSY_POSITIVE3,
             SOUND_VOICE_TT_POSITIVE3,
             SOUND_VOICE_DIDDY_POSITIVE3,
             SOUND_VOICE_UNUSED1_POSITIVE3,
             SOUND_VOICE_UNUSED2_POSITIVE3,
             SOUND_VOICE_KRUNCH_POSITIVE4,
             SOUND_VOICE_BUMPER_POSITIVE4,
             SOUND_VOICE_TIPTUP_POSITIVE4,
             SOUND_VOICE_CONKER_POSITIVE4,
             SOUND_VOICE_TIMBER_POSITIVE4,
             SOUND_VOICE_BANJO_POSITIVE4,
             SOUND_VOICE_DRUMSTICK_POSITIVE4,
             SOUND_VOICE_PIPSY_POSITIVE4,
             SOUND_VOICE_TT_POSITIVE4,
             SOUND_VOICE_DIDDY_POSITIVE4,
             SOUND_VOICE_UNUSED1_POSITIVE4,
             SOUND_VOICE_UNUSED2_POSITIVE4,
             SOUND_VOICE_KRUNCH_POSITIVE5,
             SOUND_VOICE_BUMPER_POSITIVE5,
             SOUND_VOICE_TIPTUP_POSITIVE5,
             SOUND_VOICE_CONKER_POSITIVE5,
             SOUND_VOICE_TIMBER_POSITIVE5,
             SOUND_VOICE_BANJO_POSITIVE5,
             SOUND_VOICE_DRUMSTICK_POSITIVE5,
             SOUND_VOICE_PIPSY_POSITIVE5,
             SOUND_VOICE_TT_POSITIVE5,
             SOUND_VOICE_DIDDY_POSITIVE5,
             SOUND_VOICE_UNUSED1_POSITIVE5,
             SOUND_VOICE_UNUSED2_POSITIVE5,
             SOUND_VOICE_KRUNCH_POSITIVE6,
             SOUND_VOICE_BUMPER_POSITIVE6,
             SOUND_VOICE_TIPTUP_POSITIVE6,
             SOUND_VOICE_CONKER_POSITIVE6,
             SOUND_VOICE_TIMBER_POSITIVE6,
             SOUND_VOICE_BANJO_POSITIVE6,
             SOUND_VOICE_DRUMSTICK_POSITIVE6,
             SOUND_VOICE_PIPSY_POSITIVE6,
             SOUND_VOICE_TT_POSITIVE6,
             SOUND_VOICE_DIDDY_POSITIVE6,
             SOUND_VOICE_UNUSED1_POSITIVE6,
             SOUND_VOICE_UNUSED2_POSITIVE6,
             SOUND_VOICE_KRUNCH_POSITIVE7,
             SOUND_VOICE_BUMPER_POSITIVE7,
             SOUND_VOICE_TIPTUP_POSITIVE7,
             SOUND_VOICE_CONKER_POSITIVE7,
             SOUND_VOICE_TIMBER_POSITIVE7,
             SOUND_VOICE_BANJO_POSITIVE7,
             SOUND_VOICE_DRUMSTICK_POSITIVE7,
             SOUND_VOICE_PIPSY_POSITIVE7,
             SOUND_VOICE_TT_POSITIVE7,
             SOUND_VOICE_DIDDY_POSITIVE7,
             SOUND_VOICE_UNUSED1_POSITIVE7,
             SOUND_VOICE_UNUSED2_POSITIVE7,
             SOUND_VOICE_KRUNCH_POSITIVE8,
             SOUND_VOICE_BUMPER_POSITIVE8,
             SOUND_VOICE_TIPTUP_POSITIVE8,
             SOUND_VOICE_CONKER_POSITIVE8,
             SOUND_VOICE_TIMBER_POSITIVE8,
             SOUND_VOICE_BANJO_POSITIVE8,
             SOUND_VOICE_DRUMSTICK_POSITIVE8,
             SOUND_VOICE_PIPSY_POSITIVE8,
             SOUND_VOICE_TT_POSITIVE8,
             SOUND_VOICE_DIDDY_POSITIVE8,
             SOUND_VOICE_UNUSED1_POSITIVE8,
             SOUND_VOICE_UNUSED2_POSITIVE8,
             SOUND_VOICE_KRUNCH_NEGATIVE1,
             SOUND_VOICE_BUMPER_NEGATIVE1,
             SOUND_VOICE_TIPTUP_NEGATIVE1,
             SOUND_VOICE_CONKER_NEGATIVE1,
             SOUND_VOICE_TIMBER_NEGATIVE1,
             SOUND_VOICE_BANJO_NEGATIVE1,
             SOUND_VOICE_DRUMSTICK_NEGATIVE1,
             SOUND_VOICE_PIPSY_NEGATIVE1,
             SOUND_VOICE_TT_NEGATIVE1,
             SOUND_VOICE_DIDDY_NEGATIVE1,
             SOUND_VOICE_UNUSED1_NEGATIVE1,
             SOUND_VOICE_UNUSED2_NEGATIVE1,
             SOUND_VOICE_KRUNCH_NEGATIVE2,
             SOUND_VOICE_BUMPER_NEGATIVE2,
             SOUND_VOICE_TIPTUP_NEGATIVE2,
             SOUND_VOICE_CONKER_NEGATIVE2,
             SOUND_VOICE_TIMBER_NEGATIVE2,
             SOUND_VOICE_BANJO_NEGATIVE2,
             SOUND_VOICE_DRUMSTICK_NEGATIVE2,
             SOUND_VOICE_PIPSY_NEGATIVE2,
             SOUND_VOICE_TT_NEGATIVE2,
             SOUND_VOICE_DIDDY_NEGATIVE2,
             SOUND_VOICE_UNUSED1_NEGATIVE2,
             SOUND_VOICE_UNUSED2_NEGATIVE2,
             SOUND_VOICE_KRUNCH_NEGATIVE3,
             SOUND_VOICE_BUMPER_NEGATIVE3,
             SOUND_VOICE_TIPTUP_NEGATIVE3,
             SOUND_VOICE_CONKER_NEGATIVE3,
             SOUND_VOICE_TIMBER_NEGATIVE3,
             SOUND_VOICE_BANJO_NEGATIVE3,
             SOUND_VOICE_DRUMSTICK_NEGATIVE3,
             SOUND_VOICE_PIPSY_NEGATIVE3,
             SOUND_VOICE_TT_NEGATIVE3,
             SOUND_VOICE_DIDDY_NEGATIVE3,
             SOUND_VOICE_UNUSED1_NEGATIVE3,
             SOUND_VOICE_UNUSED2_NEGATIVE3,
             SOUND_VOICE_KRUNCH_NEGATIVE4,
             SOUND_VOICE_BUMPER_NEGATIVE4,
             SOUND_VOICE_TIPTUP_NEGATIVE4,
             SOUND_VOICE_CONKER_NEGATIVE4,
             SOUND_VOICE_TIMBER_NEGATIVE4,
             SOUND_VOICE_BANJO_NEGATIVE4,
             SOUND_VOICE_DRUMSTICK_NEGATIVE4,
             SOUND_VOICE_PIPSY_NEGATIVE4,
             SOUND_VOICE_TT_NEGATIVE4,
             SOUND_VOICE_DIDDY_NEGATIVE4,
             SOUND_VOICE_UNUSED1_NEGATIVE4,
             SOUND_VOICE_UNUSED2_NEGATIVE4,
             SOUND_VOICE_KRUNCH_NEGATIVE5,
             SOUND_VOICE_BUMPER_NEGATIVE5,
             SOUND_VOICE_TIPTUP_NEGATIVE5,
             SOUND_VOICE_CONKER_NEGATIVE5,
             SOUND_VOICE_TIMBER_NEGATIVE5,
             SOUND_VOICE_BANJO_NEGATIVE5,
             SOUND_VOICE_DRUMSTICK_NEGATIVE5,
             SOUND_VOICE_PIPSY_NEGATIVE5,
             SOUND_VOICE_TT_NEGATIVE5,
             SOUND_VOICE_DIDDY_NEGATIVE5,
             SOUND_VOICE_UNUSED1_NEGATIVE5,
             SOUND_VOICE_UNUSED2_NEGATIVE5,
             SOUND_VOICE_KRUNCH_NEGATIVE6,
             SOUND_VOICE_BUMPER_NEGATIVE6,
             SOUND_VOICE_TIPTUP_NEGATIVE6,
             SOUND_VOICE_CONKER_NEGATIVE6,
             SOUND_VOICE_TIMBER_NEGATIVE6,
             SOUND_VOICE_BANJO_NEGATIVE6,
             SOUND_VOICE_DRUMSTICK_NEGATIVE6,
             SOUND_VOICE_PIPSY_NEGATIVE6,
             SOUND_VOICE_TT_NEGATIVE6,
             SOUND_VOICE_DIDDY_NEGATIVE6,
             SOUND_VOICE_UNUSED1_NEGATIVE6,
             SOUND_VOICE_UNUSED2_NEGATIVE6,
             SOUND_VOICE_KRUNCH_NEGATIVE7,
             SOUND_VOICE_BUMPER_NEGATIVE7,
             SOUND_VOICE_TIPTUP_NEGATIVE7,
             SOUND_VOICE_CONKER_NEGATIVE7,
             SOUND_VOICE_TIMBER_NEGATIVE7,
             SOUND_VOICE_BANJO_NEGATIVE7,
             SOUND_VOICE_DRUMSTICK_NEGATIVE7,
             SOUND_VOICE_PIPSY_NEGATIVE7,
             SOUND_VOICE_TT_NEGATIVE7,
             SOUND_VOICE_DIDDY_NEGATIVE7,
             SOUND_VOICE_UNUSED1_NEGATIVE7,
             SOUND_VOICE_UNUSED2_NEGATIVE7,
             SOUND_VOICE_KRUNCH_NEGATIVE8,
             SOUND_VOICE_BUMPER_NEGATIVE8,
             SOUND_VOICE_TIPTUP_NEGATIVE8,
             SOUND_VOICE_CONKER_NEGATIVE8,
             SOUND_VOICE_TIMBER_NEGATIVE8,
             SOUND_VOICE_BANJO_NEGATIVE8,
             SOUND_VOICE_DRUMSTICK_NEGATIVE8,
             SOUND_VOICE_PIPSY_NEGATIVE8,
             SOUND_VOICE_TT_NEGATIVE8,
             SOUND_VOICE_DIDDY_NEGATIVE8,
             SOUND_VOICE_BLUEY_REMATCH4,
             SOUND_VOICE_BLUEY_TROPHY2,
             SOUND_DOOR_OPEN,
             SOUND_UNK_223,
             SOUND_UNK_224,
             SOUND_VOICE_TRICKY_OW,
             SOUND_VOICE_TRICKY_OW2,
             SOUND_VOICE_SMOKEY_HM,
             SOUND_VOICE_SMOKEY_HM2,
             SOUND_VOICE_BLUEY_AIEE,
             SOUND_VOICE_BLUEY_OHNO3,
             SOUND_VOICE_BOSS_LAUGH,
             SOUND_VOICE_BOSS_LAUGH2,
             SOUND_VOICE_BLUEY_EH3,
             SOUND_VOICE_TT_GAME_STATUS,
             SOUND_VOICE_TT_OKAY,
             SOUND_VOICE_TT_TIME_TRIAL_OFF,
             SOUND_VOICE_TT_TIME_TRIAL_ON,
             SOUND_NITRO_LEVEL3_CHARGE,
             SOUND_NITRO_LEVEL3_BOOST,
             SOUND_VOICE_TAJ_SELECT_VEHICLE,
             SOUND_VOICE_TAJ_ABRAKADABRA,
             SOUND_VOICE_TAJ_ALAKAZAM,
             SOUND_VOICE_TAJ_ALAKAZOOM2,
             SOUND_VOICE_TAJ_MENUBACK,
             SOUND_VOICE_TAJ_CHALLENGE_MENU,
             SOUND_VOICE_TAJ_MENUBACK2,
             SOUND_VOICE_BRONTO_ROAR,
             SOUND_WHOOSH5,
             SOUND_COLLECT_BALLOON,
             SOUND_RAIN,
             SOUND_THUNDER,
             SOUND_ZAP4,
             SOUND_MENU_BACK3,
             SOUND_VOICE_BUBBLER_OW,
             SOUND_VOICE_BUBBLER_AUGH,
             SOUND_VOICE_BUBBLER_HOHO,
             SOUND_VOICE_BUBBLER_HOHO2,
             SOUND_VOICE_BUBBLER_AW,
             SOUND_VOICE_BUBBLER_OW2,
             SOUND_VOICE_BUBBLER_AUGH2,
             SOUND_DRAWBRIDGE_BELL,
             SOUND_BUBBLE_RISE,
             SOUND_VOICE_TT_BEAT_MY_TIME,
             SOUND_VOICE_TT_WELL_DONE,
             SOUND_VOICE_TT_TRY_ANOTHER_TRACK,
             SOUND_VOICE_TT_BEAT_ALL_TIMES,
             SOUND_VOICE_TT_UNLOCKED,
             SOUND_VOICE_TAJ_CHALLENGE_RACE,
             SOUND_UNK_251,
             SOUND_UNK_252,
             SOUND_UNK_253,
             SOUND_UNK_254,
             SOUND_UNK_255,
             SOUND_UNK_256,
             SOUND_UNK_257,
             SOUND_UNK_258,
             SOUND_UNK_259,
             SOUND_UNK_25A,
             SOUND_UNK_25B,
             SOUND_UNK_25C,
             SOUND_UNK_25D,
             SOUND_UNK_25E,
             SOUND_UNK_25F,
             SOUND_UNK_260,
             SOUND_UNK_261,
             SOUND_UNK_262,
             SOUND_UNK_263,
             SOUND_UNK_264,
             SOUND_UNK_265,
             SOUND_UNK_266,
             SOUND_UNK_267,
             SOUND_UNK_268,
             SOUND_UNK_269,
             SOUND_UNK_26A,
             SOUND_UNK_26B,
             SOUND_UNK_26C,
             SOUND_UNK_26D,
             SOUND_UNK_26E,
             SOUND_UNK_26F,
             SOUND_UNK_270,
             SOUND_UNK_271,
             SOUND_UNK_272,
             SOUND_UNK_273,
             SOUND_UNK_274,
             SOUND_UNK_275,
             SOUND_UNK_276,
             SOUND_UNK_277,
             SOUND_UNK_278,
             SOUND_UNK_279,
             SOUND_UNK_27A,
             SOUND_UNK_27B,
             SOUND_UNK_27C,
             SOUND_UNK_27D,
             SOUND_UNK_27E,
             NUM_SOUND_IDS
};
enum SequenceID {
    SEQUENCE_NONE,
    SEQUENCE_NONE2,
    SEQUENCE_AMULET_THEME,
    SEQUENCE_VICTORY_THEME,
    SEQUENCE_TROPHY_THEME,
    SEQUENCE_AMBIENT_GRASS,
    SEQUENCE_INTRO_CUTSCENE,
    SEQUENCE_TITLE_THEME,
    SEQUENCE_DARKMOON_CAVERNS,
    SEQUENCE_JUNGLE_FALLS,
    SEQUENCE_ANCIENT_LAKE,
    SEQUENCE_FROSTY_VILLAGE,
    SEQUENCE_SECRET_TUNE,
    SEQUENCE_FOSSIL_CANYON,
    SEQUENCE_HOT_TOP_VOLCANO,
    SEQUENCE_WHALE_BAY,
    SEQUENCE_WALRUS_COVE,
    SEQUENCE_NO_TROPHY_FOR_YOU,
    SEQUENCE_GOLD_BALLOONS,
    SEQUENCE_COLLECTION_TUNE,
    SEQUENCE_MAIN_LOBBY_AREA,
    SEQUENCE_PARTY_POOPER,
    SEQUENCE_EVERFROST_PEAK,
    SEQUENCE_WIZPIG_ATTACKS,
    SEQUENCE_MAIN_MENU,
    SEQUENCE_FIRST_PLACE,
    SEQUENCE_CHOOSE_YOUR_RACER,
    SEQUENCE_UNK27,
    SEQUENCE_BOSS_CHALLENGE_VICTORY,
    SEQUENCE_TAJS_RACES,
    SEQUENCE_RACE_START_FANFARE,
    SEQUENCE_GREENWOOD_VILLAGE,
    SEQUENCE_ENTRANCED,
    SEQUENCE_AMBIENT_NIGHT,
    SEQUENCE_BATTLE_THEME,
    SEQUENCE_AMBIENT_BEACH,
    SEQUENCE_TTS_THEME,
    SEQUENCE_CRESCENT_ISLAND,
    SEQUENCE_BOSS_CHALLENGE_FAILURE,
    SEQUENCE_STAR_CITY,
    SEQUENCE_BOULDER_CANYON,
    SEQUENCE_AMBIENT_UNK,
    SEQUENCE_SPACEPORT_ALPHA,
    SEQUENCE_SILVER_COIN_1,
    SEQUENCE_SILVER_COIN_2,
    SEQUENCE_SILVER_COIN_3,
    SEQUENCE_SILVER_COIN_4,
    SEQUENCE_SILVER_COIN_5,
    SEQUENCE_SILVER_COIN_6,
    SEQUENCE_SILVER_COIN_7,
    SEQUENCE_SILVER_COIN_8,
    SEQUENCE_WIZPIGS_TERROR,
    SEQUENCE_BOSS_DOOR_UNLOCKED,
    SEQUENCE_WIZPIGS_FIMAL_CHALLENGE,
    SEQUENCE_KEY_COLLECT,
    SEQUENCE_WIZPIGS_RACES,
    SEQUENCE_WIZPIGS_DEFEAT,
    SEQUENCE_BOSS_CHALLENGES,
    SEQUENCE_WIZPIG_IS_BLASTED_OFF,
    SEQUENCE_ENDING_PARTY_1,
    SEQUENCE_ENDING_PARTY_2,
    SEQUENCE_BATTLE_VICTORY,
    SEQUENCE_BATTLE_LOSE,
    SEQUENCE_HAUNTED_WOODS,
    SEQUENCE_AMBIENT_HAUNTED_WOODS,
    SEQUENCE_PIRATE_LAGOON,
    NUM_SEQUENCE_IDS
};
typedef enum AssetSectionsEnum {
    ASSET_AI_BEHAVIOUR,
    ASSET_AI_BEHAVIOUR_TABLE,
    ASSET_TEXTURES_3D,
    ASSET_TEXTURES_3D_TABLE,
    ASSET_TEXTURES_2D,
    ASSET_TEXTURES_2D_TABLE,
    ASSET_GAME_TEXT,
    ASSET_GAME_TEXT_TABLE,
    ASSET_MENU_TEXT,
    ASSET_MENU_TEXT_TABLE,
    ASSET_SCREENS,
    ASSET_SCREENS_TABLE,
    ASSET_SPRITES,
    ASSET_SPRITES_TABLE,
    ASSET_EMPTY_14,
    ASSET_MISC,
    ASSET_MISC_TABLE,
    ASSET_HUD_ELEMENT_IDS,
    ASSET_MENU_ELEMENT_IDS,
    ASSET_WEATHER_PARTICLES,
    ASSET_LEVEL_OBJECT_MAPS_TABLE,
    ASSET_LEVEL_OBJECT_MAPS,
    ASSET_LEVEL_HEADERS_TABLE,
    ASSET_LEVEL_HEADERS,
    ASSET_LEVEL_NAMES_TABLE,
    ASSET_LEVEL_NAMES,
    ASSET_LEVEL_MODELS_TABLE,
    ASSET_LEVEL_MODELS,
    ASSET_OBJECT_MODELS_TABLE,
    ASSET_OBJECT_MODELS,
    ASSET_ANIMATION_IDS,
    ASSET_OBJECT_ANIMATIONS_TABLE,
    ASSET_OBJECT_ANIMATIONS,
    ASSET_OBJECT_HEADERS_TABLE,
    ASSET_OBJECTS,
    ASSET_LEVEL_OBJECT_TRANSLATION_TABLE,
    ASSET_EMPTY_37_TABLE,
    ASSET_EMPTY_37,
    ASSET_AUDIO_TABLE,
    ASSET_AUDIO,
    ASSET_PARTICLES_TABLE,
    ASSET_PARTICLES,
    ASSET_PARTICLE_BEHAVIORS_TABLE,
    ASSET_PARTICLE_BEHAVIORS,
    ASSET_FONTS,
    ASSET_JAPANESE_FONTS_TABLE,
    ASSET_JAPANESE_FONTS,
    ASSET_DUMMY_PARTICLE_IDS,
    ASSET_TTGHOSTS_TABLE,
    ASSET_TTGHOSTS,
    ASSET_SECTIONS_COUNT
} AssetSectionsEnum;
typedef enum AssetAiBehaviourEnum {
    ASSET_AI_BEHAVIOUR_0,
    ASSET_AI_BEHAVIOUR_1,
    ASSET_AI_BEHAVIOUR_2,
    ASSET_AI_BEHAVIOUR_3,
    ASSET_AI_BEHAVIOUR_4,
    ASSET_AI_BEHAVIOUR_5,
    ASSET_AI_BEHAVIOUR_6,
    ASSET_AI_BEHAVIOUR_7,
    ASSET_AI_BEHAVIOUR_8,
    ASSET_AI_BEHAVIOUR_9,
    ASSET_AI_BEHAVIOUR_COUNT
} AssetAiBehaviourEnum;
typedef enum AssetTextures3dEnum {
    ASSET_TEX3D_SPACE_WHITEWALL200496,
    ASSET_TEX3D_SPACE_GREENWALL337,
    ASSET_TEX3D_SPACE_WHITEWALL,
    ASSET_TEX3D_SPACE_WHITEWALLWITHARROW,
    ASSET_TEX3D_SPACE_NEONROCKETSIGN,
    ASSET_TEX3D_WATER_WATER,
    ASSET_TEX3D_WATER_WATER2,
    ASSET_TEX3D_OBJECTS_ZIPPER,
    ASSET_TEX3D_SPACE_CEILINGLIGHTS,
    ASSET_TEX3D_SPACE_WHITEWALLALPHA_0,
    ASSET_TEX3D_SPACE_WHITEWALLALPHA_1,
    ASSET_TEX3D_SPACE_WHITEWALLBLUELINE,
    ASSET_TEX3D_WATER_WATER3,
    ASSET_TEX3D_WATER_WATERSTILL,
    ASSET_TEX3D_COMMON_REDARROWSIGN,
    ASSET_TEX3D_WATER_WATER4,
    ASSET_TEX3D_COMMON_LAVA,
    ASSET_TEX3D_OBJECTS_ZIPPER2,
    ASSET_TEX3D_TROPICAL_PIRATESHIPTAFFRAIL,
    ASSET_TEX3D_COMMON_YELLOWARROWSIGN,
    ASSET_TEX3D_COMMON_FLOORTILE,
    ASSET_TEX3D_WINTER_ICE,
    ASSET_TEX3D_WINTER_ICE2,
    ASSET_TEX3D_WINTER_SNOWYWALL,
    ASSET_TEX3D_WINTER_CANDYCANE,
    ASSET_TEX3D_WINTER_IGLOOBRICK,
    ASSET_TEX3D_COMMON_SAND,
    ASSET_TEX3D_SPACE_BOOSTLOOP,
    ASSET_TEX3D_TROPICAL_DIRTWALLSANDY,
    ASSET_TEX3D_TROPICAL_DIRTWALL,
    ASSET_TEX3D_TROPICAL_ROCKGUARDRAIL,
    ASSET_TEX3D_COMMON_BLUEYELLOWARROWS,
    ASSET_TEX3D_MEDIEVAL_CASTLEWINDOW,
    ASSET_TEX3D_MEDIEVAL_CASTLEBRIDGE,
    ASSET_TEX3D_MEDIEVAL_YELLOWSTONE,
    ASSET_TEX3D_MEDIEVAL_YELLOWSTONEHILLSIDE,
    ASSET_TEX3D_UNUSED_BETADKRLOGO,
    ASSET_TEX3D_SPACE_FINISHLINE_0,
    ASSET_TEX3D_SPACE_FINISHLINE_1,
    ASSET_TEX3D_SPACE_FINISHLINE_2,
    ASSET_TEX3D_SPACE_FINISHLINE_3,
    ASSET_TEX3D_SPACE_FINISHLINE_4,
    ASSET_TEX3D_SPACE_CAVEWALL,
    ASSET_TEX3D_MEDIEVAL_SMOKEYFENCE,
    ASSET_TEX3D_COMMON_COBBLESTONEFLOOR,
    ASSET_TEX3D_MEDIEVAL_HAY,
    ASSET_TEX3D_MEDIEVAL_HAYEYE,
    ASSET_TEX3D_TROPICAL_SUNKINSHIPFLOORBOARD,
    ASSET_TEX3D_WINTER_ICYFLOOR,
    ASSET_TEX3D_MEDIEVAL_WINDMILLBASE,
    ASSET_TEX3D_MEDIEVAL_DIRTTRANSITION,
    ASSET_TEX3D_MEDIEVAL_WHEATFIELD,
    ASSET_TEX3D_MEDIEVAL_CASTLEWALLSWITHSHADOW,
    ASSET_TEX3D_MEDIEVAL_CASTLEWALLS,
    ASSET_TEX3D_MEDIEVAL_CASTLEMERLON,
    ASSET_TEX3D_DINO_ORANGEWALL,
    ASSET_TEX3D_SPACE_WHITEWALLBRICKS,
    ASSET_TEX3D_UNUSED_PROAM64BALLOONREDLINE,
    ASSET_TEX3D_TROPICAL_FOG,
    ASSET_TEX3D_MEDIEVAL_WINDSAIL,
    ASSET_TEX3D_WINTER_SNOWYREDARROWDOWN,
    ASSET_TEX3D_MEDIEVAL_GARDENFENCE,
    ASSET_TEX3D_MEDIEVAL_VILLAGEWHITEWALL,
    ASSET_TEX3D_COMMON_HANGINGMOSS,
    ASSET_TEX3D_COMMON_HANGINGMOSS2,
    ASSET_TEX3D_COMMON_GRASS,
    ASSET_TEX3D_COMMON_GRASS2,
    ASSET_TEX3D_WINTER_UNKNOWNROCKYTEXTURE,
    ASSET_TEX3D_TROPICAL_MOSSYROCK,
    ASSET_TEX3D_TROPICAL_MOSSYROCK2,
    ASSET_TEX3D_WINTER_SNOWYWALL2,
    ASSET_TEX3D_COMMON_DEBUGREDYELLOW,
    ASSET_TEX3D_COMMON_DEBUGPURPLE,
    ASSET_TEX3D_WINTER_ICE3,
    ASSET_TEX3D_WINTER_SEMITRANSICE,
    ASSET_TEX3D_WINTER_SEMITRANSICE2,
    ASSET_TEX3D_WINTER_SEMITRANSICE3,
    ASSET_TEX3D_MEDIEVAL_TREEBRANCH,
    ASSET_TEX3D_WINTER_ICECEILING,
    ASSET_TEX3D_WINTER_HANGINGICE_0,
    ASSET_TEX3D_WINTER_HANGINGICE_1,
    ASSET_TEX3D_WINTER_HANGINGICE_2,
    ASSET_TEX3D_WINTER_CRYSTAL,
    ASSET_TEX3D_WINTER_CRYSTALSHADOW,
    ASSET_TEX3D_SPACE_DOCK64_0,
    ASSET_TEX3D_SPACE_DOCK64_1,
    ASSET_TEX3D_SPACE_DOCK64_2,
    ASSET_TEX3D_SPACE_DOCK64_3,
    ASSET_TEX3D_SPACE_DOCK64_4,
    ASSET_TEX3D_SPACE_DOCK64_5,
    ASSET_TEX3D_SPACE_DOCK64_6,
    ASSET_TEX3D_SPACE_DOCK64_7,
    ASSET_TEX3D_SPACE_DOCK64_8,
    ASSET_TEX3D_SPACE_DOCK64_9,
    ASSET_TEX3D_SPACE_DOCK64_10,
    ASSET_TEX3D_SPACE_DOCK64_11,
    ASSET_TEX3D_COMMON_WOOD,
    ASSET_TEX3D_UNUSED_BETAN64LOGO_0,
    ASSET_TEX3D_UNUSED_BETAN64LOGO_1,
    ASSET_TEX3D_TROPICAL_BROWNBRICKTILE,
    ASSET_TEX3D_WINTER_SNOW,
    ASSET_TEX3D_WINTER_SNOW2,
    ASSET_TEX3D_WINTER_SEMITRANSICE4,
    ASSET_TEX3D_COMMON_PORTAL,
    ASSET_TEX3D_MEDIEVAL_STONETILE,
    ASSET_TEX3D_MEDIEVAL_STONETILE2,
    ASSET_TEX3D_WINTER_BRICKWALLWITHSNOW,
    ASSET_TEX3D_TROPICAL_BRICKWALL,
    ASSET_TEX3D_COMMON_WOODPLANKS,
    ASSET_TEX3D_TROPICAL_PIRATESHIPWOODPLANKS,
    ASSET_TEX3D_COMMON_LIFEPRESERVERRING,
    ASSET_TEX3D_TROPICAL_REDSTONE,
    ASSET_TEX3D_COMMON_STONE,
    ASSET_TEX3D_DINO_RARELOGOSTONE,
    ASSET_TEX3D_TROPICAL_STONEWALLSANDY,
    ASSET_TEX3D_COMMON_ARROWSIGNSHADOW,
    ASSET_TEX3D_WINTER_ICEBRICKS,
    ASSET_TEX3D_WINTER_ICEBRICKSWITHSNOW,
    ASSET_TEX3D_WINTER_HANGINGSNOW,
    ASSET_TEX3D_WINTER_HANGINGSNOW2,
    ASSET_TEX3D_COMMON_ELEMENTGRADIENT,
    ASSET_TEX3D_WINTER_SNOWTREESBILLBOARD_0,
    ASSET_TEX3D_WINTER_SNOWTREESBILLBOARD_1,
    ASSET_TEX3D_WINTER_ICYSNOW,
    ASSET_TEX3D_WINTER_SNOWYFENCE,
    ASSET_TEX3D_WINTER_ICYPATH,
    ASSET_TEX3D_TROPICAL_JUNGLETREESBILLBOARD_0,
    ASSET_TEX3D_TROPICAL_JUNGLETREESBILLBOARD_1,
    ASSET_TEX3D_TROPICAL_MOSSYSHIPPLANKSBROKEN,
    ASSET_TEX3D_TROPICAL_MOSSYSHIPPLANKS,
    ASSET_TEX3D_TROPICAL_MOSSYSHIPTORNSAIL,
    ASSET_TEX3D_TROPICAL_PIRATESHIPREARDECORATION,
    ASSET_TEX3D_MEDIEVAL_THATCHROOFING,
    ASSET_TEX3D_MEDIEVAL_HOUSEWINDOWWITHPLANTS,
    ASSET_TEX3D_MEDIEVAL_HOUSEDOOR,
    ASSET_TEX3D_MEDIEVAL_HOUSEROOFSUPPORT,
    ASSET_TEX3D_MEDIEVAL_HOUSEWALLSUPPORT,
    ASSET_TEX3D_COMMON_WHITE,
    ASSET_TEX3D_COMMON_FINISHLINETAPE,
    ASSET_TEX3D_WINTER_ICEBRICKS2,
    ASSET_TEX3D_WATER_WATERSTILL2,
    ASSET_TEX3D_COMMON_UNUSEDTRACKSELCTFRAMETEXTURE,
    ASSET_TEX3D_COMMON_SANDDRY,
    ASSET_TEX3D_COMMON_SANDDRYTOWET,
    ASSET_TEX3D_DINO_ANCIENTLAKESIGN,
    ASSET_TEX3D_COMMON_LOGEXPOSEDSIDE,
    ASSET_TEX3D_WINTER_BRICKRAILWITHSNOWEDGE,
    ASSET_TEX3D_WINTER_BRICKRAILWITHSNOW,
    ASSET_TEX3D_COMMON_COLOURFULARROW,
    ASSET_TEX3D_SPACE_BLUEFLOORTILE,
    ASSET_TEX3D_TROPICAL_PIRATESHIPUNDERSIDE,
    ASSET_TEX3D_TROPICAL_PIRATESHIPSAILS,
    ASSET_TEX3D_TROPICAL_PIRATESHIPBOWSPIRIT,
    ASSET_TEX3D_COMMON_SAND2,
    ASSET_TEX3D_OBJECTS_TRACKSELECTFRAMEGOLD,
    ASSET_TEX3D_TROPICAL_PIRATESHIPCANNON,
    ASSET_TEX3D_COMMON_CHAINLINK,
    ASSET_TEX3D_COMMON_FINISHLINETAPE2,
    ASSET_TEX3D_COMMON_FINISHLINEWATER,
    ASSET_TEX3D_COMMON_FINISHLINECHEQUEREDREDWHITE,
    ASSET_TEX3D_COMMON_FINISHLINECHEQUEREDREDYELLOW,
    ASSET_TEX3D_COMMON_FINISHLINECHEQUEREDPURPLEYELLOW,
    ASSET_TEX3D_COMMON_CYANYELLOWARROWSIGN,
    ASSET_TEX3D_COMMON_BLUEYELLOWARROWS2_0,
    ASSET_TEX3D_COMMON_BLUEYELLOWARROWS2_1,
    ASSET_TEX3D_COMMON_BLUEYELLOWARROWS2_2,
    ASSET_TEX3D_COMMON_TRANSPARENT,
    ASSET_TEX3D_UNUSED_STONEWITHGRASS,
    ASSET_TEX3D_DINO_ORANGESTONE,
    ASSET_TEX3D_DINO_THINCLOUD,
    ASSET_TEX3D_OBJECTS_DOMECLOUDS,
    ASSET_TEX3D_OBJECTS_DOMECLOUDS2,
    ASSET_TEX3D_DINO_TEMPLEBRICK,
    ASSET_TEX3D_WINTER_SNOW3,
    ASSET_TEX3D_DINO_TEMPLEBRICKTILE,
    ASSET_TEX3D_TROPICAL_CASTLETOWERBLOCK,
    ASSET_TEX3D_UNUSED_BRIDGE,
    ASSET_TEX3D_UNUSED_BRIDGE2,
    ASSET_TEX3D_COMMON_FLASHINGARROW,
    ASSET_TEX3D_UNUSED_METALENVIRONMENTMAP,
    ASSET_TEX3D_COMMON_GRASSTRANSITION,
    ASSET_TEX3D_COMMON_GRASS3,
    ASSET_TEX3D_TROPICAL_PIRATESHIPGUARDRAIL,
    ASSET_TEX3D_OBJECTS_WOODBRIDGE,
    ASSET_TEX3D_WINTER_SNOWYPATH,
    ASSET_TEX3D_TROPICAL_MOSSYOVERLAY,
    ASSET_TEX3D_DINO_FOSSILCANYONSIGN,
    ASSET_TEX3D_OBJECTS_TROPHYCABBASE,
    ASSET_TEX3D_COMMON_ORANGESTONEWALLHILLSIDE,
    ASSET_TEX3D_TROPICAL_BLUESTONEWALLSANDYWITHMOSS,
    ASSET_TEX3D_COMMON_DIRTBLUESTONETRANSITION,
    ASSET_TEX3D_COMMON_BLUESTONE,
    ASSET_TEX3D_COMMON_BLUESTONESANDY,
    ASSET_TEX3D_DINO_HOTTOPVOLCANOSIGN,
    ASSET_TEX3D_UNUSED_UNKNOWNICYTEXTURE,
    ASSET_TEX3D_UNUSED_TRANSPARENT,
    ASSET_TEX3D_TROPICAL_BLUESTONEWALLSANDYHEAVYMOSS,
    ASSET_TEX3D_UNUSED_MOSS,
    ASSET_TEX3D_DINO_JUNGLEFALLSSIGN,
    ASSET_TEX3D_SPACE_BLINKINGCOMPUTERLIGHTS,
    ASSET_TEX3D_MEDIEVAL_YELLOWHOUSEWALL,
    ASSET_TEX3D_COMMON_COLOUREDLAMP,
    ASSET_TEX3D_DINO_VOLCANOWALL,
    ASSET_TEX3D_DINO_VOLCANOWALLMAGMATRANSITION,
    ASSET_TEX3D_DINO_MAGMAHIGHLINETRANSITION,
    ASSET_TEX3D_DINO_VOLCANOWALL2,
    ASSET_TEX3D_COMMON_YELLOWBRICKTILE,
    ASSET_TEX3D_COMMON_YELLOWBRICKTILE2,
    ASSET_TEX3D_TROPICAL_GRASSUNCOLORED,
    ASSET_TEX3D_SPACE_BLUEWALLWITHYELLOWARROWS,
    ASSET_TEX3D_SPACE_BLUEWALLSMALLLIGHT,
    ASSET_TEX3D_SPACE_BLUEWALL,
    ASSET_TEX3D_SPACE_WALLTILELIGHTS,
    ASSET_TEX3D_COMMON_GRASS4,
    ASSET_TEX3D_COMMON_GRASS5,
    ASSET_TEX3D_COMMON_GRASS6,
    ASSET_TEX3D_OBJECTS_TROPHYCABEDGE,
    ASSET_TEX3D_WINTER_STONEWALLSNOWY,
    ASSET_TEX3D_WINTER_BLUESTONEWALLSNOWY,
    ASSET_TEX3D_COMMON_STONEPATH,
    ASSET_TEX3D_OBJECTS_DOMESUNSHINING,
    ASSET_TEX3D_COMMON_SANDWATERTRANSITION,
    ASSET_TEX3D_COMMON_NINTENDOLOGO,
    ASSET_TEX3D_UNUSED_TANSTONETILE,
    ASSET_TEX3D_DINO_ORANGESTONE2,
    ASSET_TEX3D_DINO_VOLCANOWALL3,
    ASSET_TEX3D_COMMON_SAND3,
    ASSET_TEX3D_TROPICAL_PALMTREESBILLBOARD_0,
    ASSET_TEX3D_TROPICAL_PALMTREESBILLBOARD_1,
    ASSET_TEX3D_TROPICAL_PALMTREESBILLBOARD_2,
    ASSET_TEX3D_TROPICAL_PALMTREESBILLBOARD2_0,
    ASSET_TEX3D_TROPICAL_PALMTREESBILLBOARD2_1,
    ASSET_TEX3D_TROPICAL_PALMTREESBILLBOARD2_2,
    ASSET_TEX3D_TROPICAL_PALMTREESBILLBOARD2_3,
    ASSET_TEX3D_TROPICAL_PALMTREESBILLBOARD2_4,
    ASSET_TEX3D_TROPICAL_PALMTREELEAVES,
    ASSET_TEX3D_TROPICAL_PALMTREEBARKBROWN,
    ASSET_TEX3D_TROPICAL_ASSETTEX3DTROPICALPALMTREESBILLBOARD3,
    ASSET_TEX3D_TROPICAL_PALMTREEBARKWHITE,
    ASSET_TEX3D_TROPICAL_PALMTREESHADOW,
    ASSET_TEX3D_TROPICAL_PALMTREEBARKWHITE2,
    ASSET_TEX3D_COMMON_LIGHTSHAFT,
    ASSET_TEX3D_COMMON_LIGHTSHAFT2,
    ASSET_TEX3D_OBJECTS_SPACECOLUMNBLOCKSATURN,
    ASSET_TEX3D_TROPICAL_TOWERSPIRE,
    ASSET_TEX3D_TROPICAL_SHIPWOODPLANKS,
    ASSET_TEX3D_COMMON_VINES,
    ASSET_TEX3D_COMMON_VINES2,
    ASSET_TEX3D_COMMON_TAJPADGRASS,
    ASSET_TEX3D_MEDIEVAL_TREEBRANCHWITHVINES,
    ASSET_TEX3D_COMMON_REDCARPET,
    ASSET_TEX3D_COMMON_LARGETREELOG,
    ASSET_TEX3D_DINO_TEMPLESTONEDINO,
    ASSET_TEX3D_MEDIEVAL_WHITEWALLWITHFLAGS,
    ASSET_TEX3D_MEDIEVAL_TOWNCASTLESPRITE,
    ASSET_TEX3D_WINTER_VILLAGEVIADUCTSHADOW,
    ASSET_TEX3D_DINO_DIRTPATH,
    ASSET_TEX3D_UNUSED_PROAM64BALLOONROPE,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKY_0,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKY_1,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKY_2,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKY_3,
    ASSET_TEX3D_TROPICAL_SHIPTORNSAIL,
    ASSET_TEX3D_TROPICAL_SHIPSAILSHADOW,
    ASSET_TEX3D_COMMON_SANDTRANSITION,
    ASSET_TEX3D_COMMON_SANDUNDERWATER,
    ASSET_TEX3D_OBJECTS_SPACECOLUMNBLOCK,
    ASSET_TEX3D_DINO_VOLCANOSTONE,
    ASSET_TEX3D_SPACE_MOONSTONE,
    ASSET_TEX3D_TROPICAL_TOWERWINDOW,
    ASSET_TEX3D_COMMON_BROWNSTONEBRICK,
    ASSET_TEX3D_DINO_SANDWETDRYTRANSITION,
    ASSET_TEX3D_WINTER_DARKSTONEWALLSNOWY,
    ASSET_TEX3D_WINTER_SNOWTREESBILLBOARDSMALL,
    ASSET_TEX3D_WINTER_SNOW4,
    ASSET_TEX3D_WINTER_HANGINGSNOW3,
    ASSET_TEX3D_WINTER_HANGINGSNOW4,
    ASSET_TEX3D_WINTER_DARKSTONEWALLSNOWY2,
    ASSET_TEX3D_WINTER_SNOWCHARBLUEEYE,
    ASSET_TEX3D_WINTER_SNOWCHARYELLOWEYE,
    ASSET_TEX3D_WINTER_SNOWCHARBLUEGOGGLES,
    ASSET_TEX3D_WINTER_VILLAGEWINDOWLIGHTS,
    ASSET_TEX3D_WINTER_VILLAGEWINDOWLIGHTSGLOW,
    ASSET_TEX3D_WINTER_SNOWCHARNOSE,
    ASSET_TEX3D_WINTER_CYANSTONE,
    ASSET_TEX3D_WINTER_SNOWTREESBILLBOARDSMALL2,
    ASSET_TEX3D_WINTER_CYANSTONESNOW,
    ASSET_TEX3D_WINTER_PINKWHITESNOW,
    ASSET_TEX3D_SPACE_PURPLESTONE,
    ASSET_TEX3D_COMMON_FINISHLINEFLAGGREEN_0,
    ASSET_TEX3D_COMMON_FINISHLINEFLAGGREEN_1,
    ASSET_TEX3D_COMMON_FINISHLINEFLAGGREEN_2,
    ASSET_TEX3D_COMMON_FINISHLINEFLAGGREEN_3,
    ASSET_TEX3D_TROPICAL_STARFISH,
    ASSET_TEX3D_COMMON_FINISHLINEFLAGORANGE_0,
    ASSET_TEX3D_COMMON_FINISHLINEFLAGORANGE_1,
    ASSET_TEX3D_COMMON_FINISHLINEFLAGORANGE_2,
    ASSET_TEX3D_COMMON_FINISHLINEFLAGORANGE_3,
    ASSET_TEX3D_COMMON_FINISHLINEFLAGORANGE_4,
    ASSET_TEX3D_DINO_FINISHLINEPALMTREESSHADOW,
    ASSET_TEX3D_WATER_WATERSCROLLING,
    ASSET_TEX3D_DINO_FIREMOUNTAINLAVA,
    ASSET_TEX3D_DINO_FIREMOUNTAINREDBASE,
    ASSET_TEX3D_DINO_FIREMOUNTAINYELLOWBASE,
    ASSET_TEX3D_DINO_FIREMOUNTAINGREENBASE,
    ASSET_TEX3D_DINO_FIREMOUNTAINBLUEBASE,
    ASSET_TEX3D_COMMON_BROWNDIRTWALL,
    ASSET_TEX3D_COMMON_BROWNDIRTWALLHILLTOP,
    ASSET_TEX3D_COMMON_BROWNDIRTWALLHILLTOPSANDY,
    ASSET_TEX3D_COMMON_LIGHTSHAFT3,
    ASSET_TEX3D_TROPICAL_LAGOONCASTLEMERLON,
    ASSET_TEX3D_MEDIEVAL_HOUSEGUARDRAILFLAGS,
    ASSET_TEX3D_MEDIEVAL_BLUEFLAG,
    ASSET_TEX3D_MEDIEVAL_WHITEFLAG,
    ASSET_TEX3D_MEDIEVAL_YELLOWFLAG,
    ASSET_TEX3D_DINO_VOLCANOCEILINGSHADOW,
    ASSET_TEX3D_TROPICAL_LAGOONCASTLEMERLON2,
    ASSET_TEX3D_COMMON_WATERFALL,
    ASSET_TEX3D_OBJECTS_WHITEFENCE,
    ASSET_TEX3D_OBJECTS_DOMEWHITE,
    ASSET_TEX3D_COMMON_SANDABOVEWATER,
    ASSET_TEX3D_COMMON_WOODBARK,
    ASSET_TEX3D_TROPICAL_LAGOONCASTLETILE,
    ASSET_TEX3D_OBJECTS_SPACECOLUMNGOLDHORN,
    ASSET_TEX3D_COMMON_SAND4,
    ASSET_TEX3D_COMMON_SAND5,
    ASSET_TEX3D_DINO_MAGMAFALL,
    ASSET_TEX3D_OBJECTS_DIDDYBROWNFUR,
    ASSET_TEX3D_OBJECTS_TTPLANEWING,
    ASSET_TEX3D_OBJECTS_BLUEYNOSE,
    ASSET_TEX3D_OBJECTS_TAJEYE,
    ASSET_TEX3D_MEDIEVAL_TOWERBELFRY,
    ASSET_TEX3D_MEDIEVAL_TOWERBELFRY2,
    ASSET_TEX3D_MEDIEVAL_TOWERBASE,
    ASSET_TEX3D_MEDIEVAL_TOWERBASEWINDOW,
    ASSET_TEX3D_OBJECTS_CARBACKLIGHTSLOWPOLY,
    ASSET_TEX3D_OBJECTS_TIMBERSTRIPES,
    ASSET_TEX3D_OBJECTS_BUMPERBACK,
    ASSET_TEX3D_OBJECTS_BUMPERFRONT,
    ASSET_TEX3D_OBJECTS_BUMPERHEADFUR,
    ASSET_TEX3D_OBJECTS_BUMPERGLOVEPLUS,
    ASSET_TEX3D_OBJECTS_BUMPERGOGGLESFRONT,
    ASSET_TEX3D_OBJECTS_BUMPERREDPILOTCAP,
    ASSET_TEX3D_OBJECTS_BUMPERSHOULDERFUR,
    ASSET_TEX3D_OBJECTS_BUMPERNOSE,
    ASSET_TEX3D_OBJECTS_RACERCOMMONRED,
    ASSET_TEX3D_OBJECTS_BUMPERHEADFURLOWPOLY,
    ASSET_TEX3D_OBJECTS_BUMPERFACELOWPOLY,
    ASSET_TEX3D_OBJECTS_BUMPERBACKLOWPOLY,
    ASSET_TEX3D_OBJECTS_BUMPERGOGGLESSIDE,
    ASSET_TEX3D_OBJECTS_BUMPERHEADFURLIGHT,
    ASSET_TEX3D_OBJECTS_BUMPERGOGGLESSIDE2,
    ASSET_TEX3D_OBJECTS_BANJOBACKPACK,
    ASSET_TEX3D_OBJECTS_BANJOSHORTS,
    ASSET_TEX3D_OBJECTS_BANJOSHORTSCHARSELECT,
    ASSET_TEX3D_OBJECTS_BANJOCHEST,
    ASSET_TEX3D_OBJECTS_BANJOCHESTCHARSELECT,
    ASSET_TEX3D_OBJECTS_BANJOHAIRTOPCHARSELECT,
    ASSET_TEX3D_OBJECTS_BANJOWRISTANKLESCHARSELECT,
    ASSET_TEX3D_OBJECTS_BANJOEARSHADOW,
    ASSET_TEX3D_OBJECTS_BANJOEYES,
    ASSET_TEX3D_UNUSED_BETABALLOONBANJO_0,
    ASSET_TEX3D_UNUSED_BETABALLOONBANJO_1,
    ASSET_TEX3D_UNUSED_BETABALLOONBANJO_2,
    ASSET_TEX3D_UNUSED_BETABALLOONBANJO_3,
    ASSET_TEX3D_OBJECTS_BANJOSKIN,
    ASSET_TEX3D_OBJECTS_BANJOCHESTLOWPOLY,
    ASSET_TEX3D_OBJECTS_BANJOHAIRFUR,
    ASSET_TEX3D_OBJECTS_BANJOARMFUR,
    ASSET_TEX3D_OBJECTS_BANJONECK,
    ASSET_TEX3D_OBJECTS_BANJONECKFURBACK,
    ASSET_TEX3D_OBJECTS_BANJOBACKLOWESTPOLY,
    ASSET_TEX3D_OBJECTS_BANJOBACKPACKSTRAPS,
    ASSET_TEX3D_OBJECTS_BANJOBACKLOWPOLY,
    ASSET_TEX3D_OBJECTS_DIDDYNOSE,
    ASSET_TEX3D_OBJECTS_RACERCOMMONBLACK,
    ASSET_TEX3D_OBJECTS_TTVEHICLESILVER,
    ASSET_TEX3D_OBJECTS_BUBBLERTENTACLESTOP,
    ASSET_TEX3D_OBJECTS_DRUMSTICKVEHICLECYAN,
    ASSET_TEX3D_OBJECTS_BETATIPTUPBALLOONENVMAP,
    ASSET_TEX3D_OBJECTS_BANJOCARENVMAP,
    ASSET_TEX3D_OBJECTS_TIPTUPCARENVMAP,
    ASSET_TEX3D_OBJECTS_CONKERSHIRT,
    ASSET_TEX3D_OBJECTS_BONUS,
    ASSET_TEX3D_OBJECTS_RACERCOMMONUNDERSIDE,
    ASSET_TEX3D_OBJECTS_TIMBERCAPBRIM,
    ASSET_TEX3D_OBJECTS_TIMBERCAPBRIMCHARSELECT,
    ASSET_TEX3D_OBJECTS_TIMBERHANDS,
    ASSET_TEX3D_OBJECTS_DRUMSTICKVEST,
    ASSET_TEX3D_OBJECTS_DRUMSTICKBACKLOWPOLY,
    ASSET_TEX3D_OBJECTS_DRUMSTICKBEAK,
    ASSET_TEX3D_OBJECTS_DRUMSTICKFEATHERS,
    ASSET_TEX3D_OBJECTS_TTAMULETEYE,
    ASSET_TEX3D_UNUSED_BETADRUMSTICKBALLOON_0,
    ASSET_TEX3D_UNUSED_BETADRUMSTICKBALLOON_1,
    ASSET_TEX3D_UNUSED_BETADRUMSTICKBALLOON_2,
    ASSET_TEX3D_UNUSED_BETADRUMSTICKBALLOON_3,
    ASSET_TEX3D_OBJECTS_DRUMSTICKLOWERBACK,
    ASSET_TEX3D_OBJECTS_DRUMSTICKFRONTLOWPOLY,
    ASSET_TEX3D_OBJECTS_DRUMSTICKFEETCHARSELECT,
    ASSET_TEX3D_OBJECTS_DRUMSTICKFEATHERS2,
    ASSET_TEX3D_OBJECTS_DRUMSTICKPANTSBOTTOMCHARSELECT,
    ASSET_TEX3D_OBJECTS_DIDDYMOUTHCHARSELECT,
    ASSET_TEX3D_OBJECTS_DRUMSTICKEYES,
    ASSET_TEX3D_OBJECTS_RACERCOMMONPLANEUNDERSIDE,
    ASSET_TEX3D_OBJECTS_BLUEYTUXEDOPIECE,
    ASSET_TEX3D_OBJECTS_CONKERFUR,
    ASSET_TEX3D_OBJECTS_CONKEREYES,
    ASSET_TEX3D_OBJECTS_CONKEYMOUTH,
    ASSET_TEX3D_OBJECTS_CONKERFURSOLID,
    ASSET_TEX3D_OBJECTS_CONKERSHOESCHARSELECT,
    ASSET_TEX3D_OBJECTS_CONKERBACK,
    ASSET_TEX3D_UNUSED_BETABANJOBALLOONENVMAP,
    ASSET_TEX3D_OBJECTS_RACERCOMMONBREAKLIGHT,
    ASSET_TEX3D_OBJECTS_BANJOBREAKLIGHT1,
    ASSET_TEX3D_OBJECTS_BANJOBREAKLIGHT2,
    ASSET_TEX3D_OBJECTS_BANJOBREAKLIGHT3,
    ASSET_TEX3D_OBJECTS_BANJOBREAKLIGHT4,
    ASSET_TEX3D_OBJECTS_BANJOBREAKLIGHT5,
    ASSET_TEX3D_UNUSED_RACERCOMMONPLANEBREAKLIGHT,
    ASSET_TEX3D_OBJECTS_DRUMSTICKSTRAPS,
    ASSET_TEX3D_OBJECTS_DIDDYLOWERBACK,
    ASSET_TEX3D_OBJECTS_DIDDYLOWERFRONT,
    ASSET_TEX3D_UNUSED_DIDDYUNKNOWN,
    ASSET_TEX3D_UNUSED_DIDDYEYENOBLINK,
    ASSET_TEX3D_OBJECTS_DIDDYCAPSTRAP,
    ASSET_TEX3D_OBJECTS_DIDDYCAP,
    ASSET_TEX3D_OBJECTS_DIDDYBACKLOWPOLY,
    ASSET_TEX3D_OBJECTS_DIDDYBACKSTAR,
    ASSET_TEX3D_OBJECTS_DIDDYWRIST,
    ASSET_TEX3D_OBJECTS_DIDDYEYE,
    ASSET_TEX3D_OBJECTS_YELLOWDINOSAURFEET,
    ASSET_TEX3D_OBJECTS_GREENDINOSAURUNDERSIDE,
    ASSET_TEX3D_OBJECTS_YELLOWDINOSAURNECKTRANSITION,
    ASSET_TEX3D_OBJECTS_GREENDINOSAURFACESMILE,
    ASSET_TEX3D_OBJECTS_YELLOWDINOSAURNOSE,
    ASSET_TEX3D_OBJECTS_GREENDINOSAURNOSE,
    ASSET_TEX3D_OBJECTS_GREENDINOSAURSKIN,
    ASSET_TEX3D_OBJECTS_YELLOWDINOSAURNECKBACK,
    ASSET_TEX3D_OBJECTS_YELLOWDINOSAURLIMBS,
    ASSET_TEX3D_OBJECTS_RACERCOMMONSTEERINGWHEEL,
    ASSET_TEX3D_OBJECTS_DIDDYFRONTNECKLOOP,
    ASSET_TEX3D_OBJECTS_SMOKEYTRICKYTONGUE,
    ASSET_TEX3D_OBJECTS_SMOKEYARMSBACKSCALES,
    ASSET_TEX3D_OBJECTS_SMOKEYBACKHEADSCALES,
    ASSET_TEX3D_OBJECTS_SMOKEYUNDERSIDE,
    ASSET_TEX3D_OBJECTS_SMOKEYEYE,
    ASSET_TEX3D_OBJECTS_SPACECOLUMNSMOKEYEYE,
    ASSET_TEX3D_OBJECTS_SMOKEYFEETBOTTOM,
    ASSET_TEX3D_OBJECTS_SMOKEYCHEEK,
    ASSET_TEX3D_OBJECTS_DRUMSTICKSTRAPSLOWPOLY,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKYCLOUDS_0,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKYCLOUDS_1,
    ASSET_TEX3D_OBJECTS_RACERCOMMONCAREXHAUST,
    ASSET_TEX3D_OBJECTS_RACERCOMMONCAREXHAUSTLOWPOLY,
    ASSET_TEX3D_OBJECTS_EXIT,
    ASSET_TEX3D_OBJECTS_STOPWATCHEYE_0,
    ASSET_TEX3D_OBJECTS_STOPWATCHEYE_1,
    ASSET_TEX3D_OBJECTS_STOPWATCHEYE_2,
    ASSET_TEX3D_OBJECTS_FROGBELLY,
    ASSET_TEX3D_UNUSED_BLUE,
    ASSET_TEX3D_OBJECTS_TIPTUPSHELLOUTLINE,
    ASSET_TEX3D_UNUSED_BETABALLOONBUMPER_0,
    ASSET_TEX3D_UNUSED_BETABALLOONBUMPER_1,
    ASSET_TEX3D_UNUSED_BETABALLOONBUMPER_2,
    ASSET_TEX3D_UNUSED_BETABALLOONBUMPER_3,
    ASSET_TEX3D_OBJECTS_BUMPEREYES,
    ASSET_TEX3D_OBJECTS_GOLDENVMAP,
    ASSET_TEX3D_OBJECTS_GOLDENVMAP2,
    ASSET_TEX3D_OBJECTS_GOLDBALLOONENVMAP,
    ASSET_TEX3D_OBJECTS_GREENENVMAP,
    ASSET_TEX3D_OBJECTS_DIDDYCARENVMAP,
    ASSET_TEX3D_OBJECTS_RACERCOMMONPLANETAILLIGHT,
    ASSET_TEX3D_OBJECTS_TIMBERCARENVMAP,
    ASSET_TEX3D_COMMON_DEBUGGRAY,
    ASSET_TEX3D_OBJECTS_TIMBERCAPBACK,
    ASSET_TEX3D_OBJECTS_TIMBERCAPFRONT,
    ASSET_TEX3D_OBJECTS_TIMBERCAPTOP,
    ASSET_TEX3D_OBJECTS_TIMBERHEADFUR,
    ASSET_TEX3D_OBJECTS_TIMBERSTRIPESARMSNECKBACK,
    ASSET_TEX3D_OBJECTS_TIMBERSTRIPESARMSNECKBACKPLANE,
    ASSET_TEX3D_OBJECTS_TIMBERSTRIPESLIMBSBACKCHARSELECT,
    ASSET_TEX3D_SPACE_WHITEWALLWITHPIPES,
    ASSET_TEX3D_OBJECTS_SMOKEYLEGS,
    ASSET_TEX3D_SPACE_RINGSMETALENVMAP,
    ASSET_TEX3D_OBJECTS_KRUNCHJACKETSIDES,
    ASSET_TEX3D_OBJECTS_DOTS,
    ASSET_TEX3D_OBJECTS_KRUNCHSCUTES,
    ASSET_TEX3D_UNUSED_BETABALLOONKRUNCH_0,
    ASSET_TEX3D_UNUSED_BETABALLOONKRUNCH_1,
    ASSET_TEX3D_UNUSED_BETABALLOONKRUNCH_2,
    ASSET_TEX3D_UNUSED_BETABALLOONKRUNCH_3,
    ASSET_TEX3D_OBJECTS_KRUNCHUNDERSIDE,
    ASSET_TEX3D_OBJECTS_KRUNCHEYE,
    ASSET_TEX3D_OBJECTS_KRUNCHEYELOWPOLY,
    ASSET_TEX3D_OBJECTS_KRUNCHSKULL,
    ASSET_TEX3D_OBJECTS_KRUNCHTOES,
    ASSET_TEX3D_OBJECTS_KRUNCHSKIN,
    ASSET_TEX3D_OBJECTS_KRUNCHHEADSIDES,
    ASSET_TEX3D_OBJECTS_KRUNCHHEADTOPLOWPOLY,
    ASSET_TEX3D_OBJECTS_KRUNCHMOUTH,
    ASSET_TEX3D_OBJECTS_KRUNCHBACKLOWPOLY,
    ASSET_TEX3D_OBJECTS_EMPTYCARBREAKLIGHTS,
    ASSET_TEX3D_COMMON_TROPHYRACEFLAG,
    ASSET_TEX3D_OBJECTS_DIDDYSKIN,
    ASSET_TEX3D_OBJECTS_TAJTRUNKTOP,
    ASSET_TEX3D_OBJECTS_MODE,
    ASSET_TEX3D_OBJECTS_PIPSYEARS,
    ASSET_TEX3D_OBJECTS_PIPSYHEADTOP,
    ASSET_TEX3D_WINTER_SNOWCHARBOW,
    ASSET_TEX3D_OBJECTS_PIPSYBOW,
    ASSET_TEX3D_OBJECTS_PIPSYBELLY,
    ASSET_TEX3D_OBJECTS_PIPSYSAILORSUIT,
    ASSET_TEX3D_OBJECTS_PIPSYEYES,
    ASSET_TEX3D_OBJECTS_PTERODACTYLEYE,
    ASSET_TEX3D_UNUSED_BETABALLOONPIPSY_0,
    ASSET_TEX3D_UNUSED_BETABALLOONPIPSY_1,
    ASSET_TEX3D_UNUSED_BETABALLOONPIPSY_2,
    ASSET_TEX3D_UNUSED_BETABALLOONPIPSY_3,
    ASSET_TEX3D_OBJECTS_PIPSYGLOVES,
    ASSET_TEX3D_OBJECTS_PIPSYARMS,
    ASSET_TEX3D_OBJECTS_PIPSYNOSEWHISKERS,
    ASSET_TEX3D_OBJECTS_PIPSYHEAD,
    ASSET_TEX3D_OBJECTS_PIPSYBACKCHARSELECT,
    ASSET_TEX3D_OBJECTS_TIMBERMOUTHLOWPOLY,
    ASSET_TEX3D_OBJECTS_GREENDINOSAURINSIDEMOUTH,
    ASSET_TEX3D_OBJECTS_STOPWATCHMOUTHWORRIED,
    ASSET_TEX3D_OBJECTS_STOPWATCHMOUTHHAPPY,
    ASSET_TEX3D_OBJECTS_STOPWATCHMOUTHOPENMOUTH,
    ASSET_TEX3D_OBJECTS_BUMPERGOGGLESFRONTCHARSELECT,
    ASSET_TEX3D_OBJECTS_TIMBEREARSLOWPOLY,
    ASSET_TEX3D_OBJECTS_DRUMSTICKCARENVMAP,
    ASSET_TEX3D_OBJECTS_PLAYER1SELECT,
    ASSET_TEX3D_OBJECTS_PLAYER2SELECT,
    ASSET_TEX3D_OBJECTS_PLAYER3SELECT,
    ASSET_TEX3D_OBJECTS_PLAYER4SELECT,
    ASSET_TEX3D_UNUSED_BETABALLOONPLAYER1_0,
    ASSET_TEX3D_UNUSED_BETABALLOONPLAYER1_1,
    ASSET_TEX3D_UNUSED_BETABALLOONPLAYER1_2,
    ASSET_TEX3D_UNUSED_BETABALLOONPLAYER1_3,
    ASSET_TEX3D_UNUSED_BETABALLOONPLAYER2_0,
    ASSET_TEX3D_UNUSED_BETABALLOONPLAYER2_1,
    ASSET_TEX3D_UNUSED_BETABALLOONPLAYER2_2,
    ASSET_TEX3D_UNUSED_BETABALLOONPLAYER2_3,
    ASSET_TEX3D_UNUSED_BETABALLOONPLAYER3_0,
    ASSET_TEX3D_UNUSED_BETABALLOONPLAYER3_1,
    ASSET_TEX3D_UNUSED_BETABALLOONPLAYER3_2,
    ASSET_TEX3D_UNUSED_BETABALLOONPLAYER3_3,
    ASSET_TEX3D_UNUSED_BETABALLOONPLAYER4_0,
    ASSET_TEX3D_UNUSED_BETABALLOONPLAYER4_1,
    ASSET_TEX3D_UNUSED_BETABALLOONPLAYER4_2,
    ASSET_TEX3D_UNUSED_BETABALLOONPLAYER4_3,
    ASSET_TEX3D_MEDIEVAL_SIGNSHIELD,
    ASSET_TEX3D_MEDIEVAL_COBBLEGROUND,
    ASSET_TEX3D_MEDIEVAL_YELLOWCOBBLEGROUND,
    ASSET_TEX3D_OBJECTS_BUBBLERSKINSIDESSMOOTH,
    ASSET_TEX3D_OBJECTS_BUBBLEREYE,
    ASSET_TEX3D_OBJECTS_BUBBLERSKINSIDESDOTS,
    ASSET_TEX3D_OBJECTS_BUBBLEREYESOCKET,
    ASSET_TEX3D_OBJECTS_TIPTUPSHELL,
    ASSET_TEX3D_OBJECTS_KRUNCHCARENVMAP,
    ASSET_TEX3D_UNUSED_BETABALLOONKRUNCHENVMAP,
    ASSET_TEX3D_MEDIEVAL_TURNSIGN,
    ASSET_TEX3D_OBJECTS_YELLOWDINOSAURBACK,
    ASSET_TEX3D_OBJECTS_GREENDINOSAURBACK,
    ASSET_TEX3D_OBJECTS_WIZPIGCAPE,
    ASSET_TEX3D_OBJECTS_WIZPIGNOSESIDE,
    ASSET_TEX3D_OBJECTS_WIZPIGNOSEFRONT,
    ASSET_TEX3D_OBJECTS_WIZPIGHOOF,
    ASSET_TEX3D_OBJECTS_SMOKEYSKIN,
    ASSET_TEX3D_OBJECTS_SMOKEYWINGSOUTLINE,
    ASSET_TEX3D_OBJECTS_WIZPIGAMULETNOSE,
    ASSET_TEX3D_OBJECTS_WIZPIGHEADEYE,
    ASSET_TEX3D_OBJECTS_TRICKYTOPSMOUTHEDGE,
    ASSET_TEX3D_OBJECTS_WIZPIGHEADBELOWEARS,
    ASSET_TEX3D_OBJECTS_WIZPIGFOREHEAD,
    ASSET_TEX3D_OBJECTS_WIZPIGCLOTHES,
    ASSET_TEX3D_OBJECTS_WIZPIGJEWELEYE,
    ASSET_TEX3D_OBJECTS_WIZPIGHAIR,
    ASSET_TEX3D_OBJECTS_WIZPIGEAR,
    ASSET_TEX3D_OBJECTS_WIZPIGHEADMOUTH,
    ASSET_TEX3D_OBJECTS_TRICKYTOPSCHEEK,
    ASSET_TEX3D_UNUSED_TRICKYTOPSUNKNOWN,
    ASSET_TEX3D_OBJECTS_TRICKYTOPSFRILLBACK,
    ASSET_TEX3D_OBJECTS_TRICKYTOPSFRILLFRONT,
    ASSET_TEX3D_OBJECTS_TRICKYTOPSUNDERSIDE,
    ASSET_TEX3D_OBJECTS_TRICKYTOPSBACK,
    ASSET_TEX3D_OBJECTS_WIZPIGSKINLINES,
    ASSET_TEX3D_OBJECTS_TRICKYTOPSNAPE,
    ASSET_TEX3D_OBJECTS_TRICKYTOPSNOSE,
    ASSET_TEX3D_OBJECTS_WIZPIGSKIN,
    ASSET_TEX3D_COMMON_CHARSELECTHILLFENCE,
    ASSET_TEX3D_UNUSED_BETABALLOONPIPSYENVMAP,
    ASSET_TEX3D_OBJECTS_PIPSYCARENVMAP,
    ASSET_TEX3D_UNUSED_BETATAJPAD,
    ASSET_TEX3D_UNUSED_BETATAJPAD2,
    ASSET_TEX3D_OBJECTS_TAJSKIN,
    ASSET_TEX3D_OBJECTS_BLUEYTUSKS,
    ASSET_TEX3D_OBJECTS_DRUMSTICKFEATHERSCHARSELECT,
    ASSET_TEX3D_UNUSED_BETABALLOONDRUMSTICKENVMAP,
    ASSET_TEX3D_OBJECTS_TTCLOCKHAND,
    ASSET_TEX3D_OBJECTS_TTSCREW,
    ASSET_TEX3D_OBJECTS_PIPSYHEADLOWPOLY,
    ASSET_TEX3D_OBJECTS_TIPTUPNOSE,
    ASSET_TEX3D_OBJECTS_TIPTUPTOESCHARSELECT,
    ASSET_TEX3D_OBJECTS_TIPTUPSHELLBACKCENTER,
    ASSET_TEX3D_OBJECTS_TIPTUPFRONT,
    ASSET_TEX3D_OBJECTS_TIPTUPEYE,
    ASSET_TEX3D_OBJECTS_TIPTUPNECK,
    ASSET_TEX3D_OBJECTS_TIPTUPFRONTFRAME,
    ASSET_TEX3D_UNUSED_BETABALLOONPLAYERSENVMAP,
    ASSET_TEX3D_OBJECTS_CONKERCARENVMAP,
    ASSET_TEX3D_OBJECTS_CONKERBACKLOWPOLY,
    ASSET_TEX3D_OBJECTS_PIPSYBACKLOWPOLY,
    ASSET_TEX3D_OBJECTS_RACERCOMMONSTEERINGWHEEL2,
    ASSET_TEX3D_OBJECTS_TTEYE,
    ASSET_TEX3D_UNUSED_TTEYESTILL,
    ASSET_TEX3D_OBJECTS_DRUMSTICKSTRAPSBUTTONLOWPOLY,
    ASSET_TEX3D_OBJECTS_DRUMSTICKSTRAPSBUTTON,
    ASSET_TEX3D_OBJECTS_TTCROWN,
    ASSET_TEX3D_OBJECTS_TTGLOVE,
    ASSET_TEX3D_OBJECTS_TTMOUTHSMILE,
    ASSET_TEX3D_OBJECTS_TTRIM,
    ASSET_TEX3D_OBJECTS_TTSHOE,
    ASSET_TEX3D_OBJECTS_BUBBLERTENTACLESBACKSIDE,
    ASSET_TEX3D_OBJECTS_SMOKEYSHADOW,
    ASSET_TEX3D_OBJECTS_YELLOWDINOSAUREYE,
    ASSET_TEX3D_OBJECTS_GREENDINOSAUREYE,
    ASSET_TEX3D_OBJECTS_RACERCOMMONBLACK2,
    ASSET_TEX3D_OBJECTS_TIMBERFRONT,
    ASSET_TEX3D_OBJECTS_TIMBERMOUTH,
    ASSET_TEX3D_UNUSED_BETABALLOONTIMBER_0,
    ASSET_TEX3D_UNUSED_BETABALLOONTIMBER_1,
    ASSET_TEX3D_UNUSED_BETABALLOONTIMBER_2,
    ASSET_TEX3D_UNUSED_BETABALLOONTIMBER_3,
    ASSET_TEX3D_OBJECTS_TIMBERFACEWHITEFUR,
    ASSET_TEX3D_OBJECTS_TIMBEREYE,
    ASSET_TEX3D_OBJECTS_TRICKYTOPSSKINLIMBS,
    ASSET_TEX3D_OBJECTS_SMOKEYMOUTH,
    ASSET_TEX3D_OBJECTS_TIMBERFRONTCHARSELECT,
    ASSET_TEX3D_OBJECTS_TIMBERNOSE,
    ASSET_TEX3D_OBJECTS_TIMBERFUR,
    ASSET_TEX3D_OBJECTS_TIMBERFOOT,
    ASSET_TEX3D_OBJECTS_TIMBERBACKLOWPOLY,
    ASSET_TEX3D_OBJECTS_TIMBERCHEEK,
    ASSET_TEX3D_OBJECTS_TIMBERCHEEKPLANE,
    ASSET_TEX3D_OBJECTS_TIMBERCHEEKCHARSELECT,
    ASSET_TEX3D_UNUSED_BETABALLOONTIPTUP_0,
    ASSET_TEX3D_UNUSED_BETABALLOONTIPTUP_1,
    ASSET_TEX3D_UNUSED_BETABALLOONTIPTUP_2,
    ASSET_TEX3D_UNUSED_BETABALLOONTIPTUP_3,
    ASSET_TEX3D_OBJECTS_TIPTUPSKIN,
    ASSET_TEX3D_OBJECTS_TIPTUPBACKLOWPOLY,
    ASSET_TEX3D_OBJECTS_TIPTUPNAPE,
    ASSET_TEX3D_OBJECTS_WIZPIGEYE,
    ASSET_TEX3D_OBJECTS_TRICKYTOPSLIMBS,
    ASSET_TEX3D_OBJECTS_TRICKYTOPSBOTTOMLIGHT,
    ASSET_TEX3D_OBJECTS_TRICKYTOPSFOREHEAD,
    ASSET_TEX3D_UNUSED_WIZPIGROCKETUNUSEDSHADOW,
    ASSET_TEX3D_OBJECTS_TRICKYTOPSTOES,
    ASSET_TEX3D_OBJECTS_WIDESCREEN,
    ASSET_TEX3D_OBJECTS_RACERCOMMONHOVERBOTTOM,
    ASSET_TEX3D_OBJECTS_BUMPERHOVERTOPLOWPOLY,
    ASSET_TEX3D_OBJECTS_TIPTUPHOVERTOP,
    ASSET_TEX3D_OBJECTS_CONKERHOVERTOP,
    ASSET_TEX3D_OBJECTS_BANJOHOVERTOP,
    ASSET_TEX3D_OBJECTS_DIDDYHOVERTOP,
    ASSET_TEX3D_OBJECTS_TIMBERHOVERTOP,
    ASSET_TEX3D_OBJECTS_KRUNCHHOVERTOP,
    ASSET_TEX3D_OBJECTS_PIPSYHOVERTOP,
    ASSET_TEX3D_OBJECTS_DRUMSTICKHOVERTOP,
    ASSET_TEX3D_OBJECTS_BUMPERHOVERTOP,
    ASSET_TEX3D_OBJECTS_TAJTURBAN,
    ASSET_TEX3D_OBJECTS_TAJTUSKS,
    ASSET_TEX3D_OBJECTS_RACERCOMMONREDLOWPOLY,
    ASSET_TEX3D_OBJECTS_STOPWATCHFRAMEENVMAP,
    ASSET_TEX3D_OBJECTS_BLUEYSKINENVMAP,
    ASSET_TEX3D_OBJECTS_TAJFRONT,
    ASSET_TEX3D_OBJECTS_TAJCHEEK,
    ASSET_TEX3D_OBJECTS_TAJLIMBS,
    ASSET_TEX3D_OBJECTS_TAJVEST,
    ASSET_TEX3D_OBJECTS_TAJLEGSIDES,
    ASSET_TEX3D_OBJECTS_BLUEYCHEEK,
    ASSET_TEX3D_OBJECTS_RACERCOMMONWHITE,
    ASSET_TEX3D_OBJECTS_DRUMSTICKWINGSTOP,
    ASSET_TEX3D_OBJECTS_TIPTUPPLANEWING,
    ASSET_TEX3D_OBJECTS_CONKERPLANEWING,
    ASSET_TEX3D_OBJECTS_BANJOPLANEWING,
    ASSET_TEX3D_OBJECTS_DIDDYPLANEWING,
    ASSET_TEX3D_OBJECTS_TIMBERPLANEWING,
    ASSET_TEX3D_OBJECTS_KRUNCHPLANEWING,
    ASSET_TEX3D_OBJECTS_PIPSYPLANEWING,
    ASSET_TEX3D_OBJECTS_DRUMSTICKPLANEWING,
    ASSET_TEX3D_OBJECTS_BUMPERPLANEWING,
    ASSET_TEX3D_OBJECTS_BUMPERCARENVMAP,
    ASSET_TEX3D_UNUSED_BETABALLOONBUMPERENVMAP,
    ASSET_TEX3D_UNUSED_GOLDBALLOONSTRIPES,
    ASSET_TEX3D_COMMON_BROWNDIRTPATH,
    ASSET_TEX3D_DINO_FOSSILHOLES,
    ASSET_TEX3D_SPACE_GREENWALLWITHDIALS,
    ASSET_TEX3D_COMMON_DIRTWALLSANDY2,
    ASSET_TEX3D_SPACE_WHITEWALLYELLOWARROWDOWN,
    ASSET_TEX3D_SPACE_SPACESHIPEARTH,
    ASSET_TEX3D_SPACE_VENTFANGRATE,
    ASSET_TEX3D_OBJECTS_FANBLADE,
    ASSET_TEX3D_OBJECTS_DOMEORANGESKY_0,
    ASSET_TEX3D_OBJECTS_DOMEORANGESKY_1,
    ASSET_TEX3D_OBJECTS_DOMEORANGESKY_2,
    ASSET_TEX3D_OBJECTS_DOMEORANGESKY_3,
    ASSET_TEX3D_SPACE_GLASSWINDOW,
    ASSET_TEX3D_SPACE_BLINKINGLIGHT,
    ASSET_TEX3D_COMMON_HANGINGMOSS3,
    ASSET_TEX3D_MEDIEVAL_YELLOWHOUSEFRONT,
    ASSET_TEX3D_MEDIEVAL_YELLOWHOUSESIDE,
    ASSET_TEX3D_SPACE_GREENWALLGRAPH,
    ASSET_TEX3D_SPACE_GREENWALLTANKS,
    ASSET_TEX3D_COMMON_BLUESTONESANDYMOSSY,
    ASSET_TEX3D_DINO_ORANGESTONESANDY,
    ASSET_TEX3D_COMMON_DEBUGPURPLEHIT,
    ASSET_TEX3D_SPACE_ARCHSUPPORT,
    ASSET_TEX3D_SPACE_STARSSIGN,
    ASSET_TEX3D_SPACE_KILLERINSTINCTSIGN,
    ASSET_TEX3D_OBJECTS_DOMEORANGESKY2_0,
    ASSET_TEX3D_OBJECTS_DOMEORANGESKY2_1,
    ASSET_TEX3D_OBJECTS_DOMEORANGESKY2_2,
    ASSET_TEX3D_OBJECTS_DOMEORANGESKY2_3,
    ASSET_TEX3D_SPACE_BLUEWALLLIGHT,
    ASSET_TEX3D_SPACE_BLUEWALLLIGHT2,
    ASSET_TEX3D_SPACE_BLUEWALLSTRIPES,
    ASSET_TEX3D_SPACE_WHITEWALLBRICKSDETAILS,
    ASSET_TEX3D_SPACE_BLUETUNNELLIGHT,
    ASSET_TEX3D_DINO_LILYPADEDGE,
    ASSET_TEX3D_MEDIEVAL_BLUEWALLFRAME,
    ASSET_TEX3D_MEDIEVAL_BLUEWALLWINDOWANDFLAGS,
    ASSET_TEX3D_MEDIEVAL_BLUEWALLWINDOWANDDOOR,
    ASSET_TEX3D_MEDIEVAL_BLUEWALLROPE,
    ASSET_TEX3D_OBJECTS_DOMEGRASS_0,
    ASSET_TEX3D_OBJECTS_DOMEGRASS_1,
    ASSET_TEX3D_OBJECTS_DOMEGRASS_2,
    ASSET_TEX3D_OBJECTS_DOMEGRASS_3,
    ASSET_TEX3D_OBJECTS_MONORAILN64LOGO,
    ASSET_TEX3D_DINO_TEMPLEBRICK2,
    ASSET_TEX3D_SPACE_WHITEWALLPIPES,
    ASSET_TEX3D_TROPICAL_N64LOGOSHIPSAIL_0,
    ASSET_TEX3D_TROPICAL_N64LOGOSHIPSAIL_1,
    ASSET_TEX3D_SPACE_WHITEWALLN64TANK,
    ASSET_TEX3D_UNUSED_BLACKUNKNOWN,
    ASSET_TEX3D_SPACE_N64SIGNSQUARE,
    ASSET_TEX3D_SPACE_SUNNEONSIGN,
    ASSET_TEX3D_SPACE_STREETROAD,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKY2_0,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKY2_1,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKY2_2,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKY2_3,
    ASSET_TEX3D_OBJECTS_DOMEDESERT_0,
    ASSET_TEX3D_OBJECTS_DOMEDESERT_1,
    ASSET_TEX3D_OBJECTS_DOMEDESERT_2,
    ASSET_TEX3D_OBJECTS_DOMEDESERT_3,
    ASSET_TEX3D_UNUSED_NINTENDOLOGONEGATIVE_0,
    ASSET_TEX3D_UNUSED_NINTENDOLOGONEGATIVE_1,
    ASSET_TEX3D_UNUSED_NINTENDOLOGONEGATIVE_2,
    ASSET_TEX3D_UNUSED_NINTENDOLOGONEGATIVE_3,
    ASSET_TEX3D_OBJECTS_DOMESPACESTARS_0,
    ASSET_TEX3D_OBJECTS_DOMESPACESTARS_1,
    ASSET_TEX3D_OBJECTS_DOMESPACESTARS_2,
    ASSET_TEX3D_OBJECTS_DOMESPACEORANGESKY_0,
    ASSET_TEX3D_OBJECTS_DOMESPACEORANGESKY_1,
    ASSET_TEX3D_OBJECTS_DOMESPACEORANGESKY_2,
    ASSET_TEX3D_OBJECTS_DOMESPACEYELLOWSKY_0,
    ASSET_TEX3D_OBJECTS_DOMESPACEYELLOWSKY_1,
    ASSET_TEX3D_OBJECTS_DOMESPACEYELLOWSKY_2,
    ASSET_TEX3D_MEDIEVAL_VILLAGESTONEWALL,
    ASSET_TEX3D_COMMON_REDARROWSIGN2,
    ASSET_TEX3D_MEDIEVAL_VILLAGEROOFN64LOGO,
    ASSET_TEX3D_SPACE_SKYSCRAPERLIGHTS,
    ASSET_TEX3D_SPACE_WHITEWALLBRICKS2,
    ASSET_TEX3D_SPACE_WHITEWALLN64LOGO,
    ASSET_TEX3D_COMMON_WOODBRIDGEDARKBROWN,
    ASSET_TEX3D_WINTER_FINISHLINEFLAGBLACKYELLOW,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKY3_0,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKY3_1,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKY3_2,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKY3_3,
    ASSET_TEX3D_SPACE_SPACEGRASS,
    ASSET_TEX3D_UNUSED_CASTLEWALLTILEMOSSY,
    ASSET_TEX3D_SPACE_VENTFANBORDER,
    ASSET_TEX3D_SPACE_WHITEWALLBLUEPIPE,
    ASSET_TEX3D_OBJECTS_DOMETOPBROWN,
    ASSET_TEX3D_MEDIEVAL_VILLAGEPLANKFENCE,
    ASSET_TEX3D_OBJECTS_PTERODACTYLUNDERSIDE,
    ASSET_TEX3D_OBJECTS_PTERODACTYLNOSE,
    ASSET_TEX3D_OBJECTS_PTERODACTYLSKIN,
    ASSET_TEX3D_OBJECTS_PTERODACTYLSPINEHEAD,
    ASSET_TEX3D_OBJECTS_PTERODACTYLWINGS,
    ASSET_TEX3D_SPACE_REDWALLSMALLLEVERS,
    ASSET_TEX3D_SPACE_REDWALLBIGLEVERS,
    ASSET_TEX3D_SPACE_REDWALLR4300,
    ASSET_TEX3D_SPACE_REDWALLCOMPUTER,
    ASSET_TEX3D_MEDIEVAL_ROOFTILESHINGLES,
    ASSET_TEX3D_SPACE_COLOREDSTONE,
    ASSET_TEX3D_MEDIEVAL_BLUECASTLEMERLON,
    ASSET_TEX3D_SPACE_RARESIGNFLASHING,
    ASSET_TEX3D_SPACE_REDGROUNDARROW,
    ASSET_TEX3D_SPACE_REDWALLBIGLEVERS2,
    ASSET_TEX3D_MEDIEVAL_ORANGEHOUSEWALLWINDOW,
    ASSET_TEX3D_MEDIEVAL_ORANGEHOUSEGUARDRAIL,
    ASSET_TEX3D_SPACE_ARCHSUPPORTBASE,
    ASSET_TEX3D_OBJECTS_SPACESHIPBOOSTER,
    ASSET_TEX3D_SPACE_REDPILLARSPIKE,
    ASSET_TEX3D_DINO_FOSSILBONE,
    ASSET_TEX3D_SPACE_WHITEWALLRARELOGO,
    ASSET_TEX3D_MEDIEVAL_ROOFTILESHINGLESRED,
    ASSET_TEX3D_MEDIEVAL_ROOFTILESHINGLES2,
    ASSET_TEX3D_OBJECTS_CHARSELECTSHADOW,
    ASSET_TEX3D_SPACE_BLUEPAVEMENT,
    ASSET_TEX3D_OBJECTS_DOMESUNRAYS,
    ASSET_TEX3D_COMMON_DIRTROADSANDY,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKYISLAND,
    ASSET_TEX3D_OBJECTS_DOMEBLACKBOTTOM,
    ASSET_TEX3D_OBJECTS_DOMESNOWYNIGHT_0,
    ASSET_TEX3D_OBJECTS_DOMESNOWYNIGHT_1,
    ASSET_TEX3D_OBJECTS_DOMESNOWYNIGHT_2,
    ASSET_TEX3D_OBJECTS_DOMESNOWYNIGHT_3,
    ASSET_TEX3D_OBJECTS_DOMESNOWYNIGHT_4,
    ASSET_TEX3D_OBJECTS_DOMESNOWYNIGHT_5,
    ASSET_TEX3D_OBJECTS_DOMESNOWYNIGHT_6,
    ASSET_TEX3D_OBJECTS_DOMESNOWYNIGHT_7,
    ASSET_TEX3D_OBJECTS_DOMESNOWYNIGHT_8,
    ASSET_TEX3D_OBJECTS_DOMESNOWYNIGHT_9,
    ASSET_TEX3D_OBJECTS_DOMESNOWYNIGHT_10,
    ASSET_TEX3D_OBJECTS_DOMESNOWYNIGHT_11,
    ASSET_TEX3D_COMMON_BLACKSEMITRANSPARENT,
    ASSET_TEX3D_OBJECTS_SPACESHIPBLASTER,
    ASSET_TEX3D_OBJECTS_DOMEVOLCANO_0,
    ASSET_TEX3D_OBJECTS_DOMEVOLCANO_1,
    ASSET_TEX3D_OBJECTS_DOMEVOLCANO_2,
    ASSET_TEX3D_OBJECTS_DOMEVOLCANO_3,
    ASSET_TEX3D_OBJECTS_DOMEVOLCANO_4,
    ASSET_TEX3D_OBJECTS_DOMEVOLCANO_5,
    ASSET_TEX3D_OBJECTS_DOMEVOLCANO_6,
    ASSET_TEX3D_OBJECTS_DOMEVOLCANO_7,
    ASSET_TEX3D_OBJECTS_DOMEVOLCANO_8,
    ASSET_TEX3D_OBJECTS_DOMEVOLCANO_9,
    ASSET_TEX3D_OBJECTS_DOMEVOLCANO_10,
    ASSET_TEX3D_OBJECTS_DOMEVOLCANO_11,
    ASSET_TEX3D_OBJECTS_DOMESNOWYNIGHTTOP,
    ASSET_TEX3D_WINTER_ICYPATHSNOWY,
    ASSET_TEX3D_SPACE_SPACEWALL,
    ASSET_TEX3D_OBJECTS_DOMESPACEBLUE_0,
    ASSET_TEX3D_OBJECTS_DOMESPACEBLUE_1,
    ASSET_TEX3D_OBJECTS_DOMESPACEBLUE_2,
    ASSET_TEX3D_OBJECTS_DOMESPACEBLUE_3,
    ASSET_TEX3D_OBJECTS_DOMESPACEBLUE_4,
    ASSET_TEX3D_OBJECTS_DOMESPACEBLUE_5,
    ASSET_TEX3D_OBJECTS_DOMESPACEBLUE_6,
    ASSET_TEX3D_OBJECTS_DOMESPACEBLUE_7,
    ASSET_TEX3D_OBJECTS_DOMESPACEBLUE_8,
    ASSET_TEX3D_OBJECTS_DOMESPACEBLUE_9,
    ASSET_TEX3D_OBJECTS_DOMESPACEBLUE_10,
    ASSET_TEX3D_OBJECTS_DOMESPACEBLUE_11,
    ASSET_TEX3D_OBJECTS_DOMESPACEBLUE_12,
    ASSET_TEX3D_OBJECTS_DOMESPACEBLUE_13,
    ASSET_TEX3D_OBJECTS_DOMESPACEBLUE_14,
    ASSET_TEX3D_OBJECTS_DOMESPACEBLUE_15,
    ASSET_TEX3D_OBJECTS_DOMESPACEBLUE_16,
    ASSET_TEX3D_OBJECTS_DOMESPACEBLUE_17,
    ASSET_TEX3D_OBJECTS_DOMESPACEBLUE_18,
    ASSET_TEX3D_OBJECTS_DOMESPACEBLUE_19,
    ASSET_TEX3D_SPACE_FINISHLINEWHITESPACE_0,
    ASSET_TEX3D_SPACE_FINISHLINEWHITESPACE_1,
    ASSET_TEX3D_SPACE_WHITEWALLBLOCKSLARGE,
    ASSET_TEX3D_COMMON_FOGWHITE,
    ASSET_TEX3D_SPACE_FINISHLINESPACE2_0,
    ASSET_TEX3D_SPACE_FINISHLINESPACE2_1,
    ASSET_TEX3D_SPACE_STADIUMLIGHTS,
    ASSET_TEX3D_OBJECTS_DOMESPACEPINK_0,
    ASSET_TEX3D_OBJECTS_DOMESPACEPINK_1,
    ASSET_TEX3D_OBJECTS_DOMESPACEPINK_2,
    ASSET_TEX3D_OBJECTS_DOMESPACEPINK_3,
    ASSET_TEX3D_OBJECTS_DOMESPACEPINKTOP,
    ASSET_TEX3D_SPACE_WHITEWALLSMALLYELLOWARROW,
    ASSET_TEX3D_SPACE_WHITEWALLVENT,
    ASSET_TEX3D_SPACE_POLE,
    ASSET_TEX3D_SPACE_BUILDINGEDGE,
    ASSET_TEX3D_DINO_ANCIENTSTONE,
    ASSET_TEX3D_OBJECTS_DOMEORANGESKY3_0,
    ASSET_TEX3D_OBJECTS_DOMEORANGESKY3_1,
    ASSET_TEX3D_OBJECTS_DOMEORANGESKY3_2,
    ASSET_TEX3D_OBJECTS_DOMEORANGESKY3_3,
    ASSET_TEX3D_SPACE_WHITEWALLBLUETANKS,
    ASSET_TEX3D_MEDIEVAL_TREETRUNKSWOODS_0,
    ASSET_TEX3D_MEDIEVAL_TREETRUNKSWOODS_1,
    ASSET_TEX3D_MEDIEVAL_TREETRUNKSWOODS_2,
    ASSET_TEX3D_MEDIEVAL_THATCHROOFING2,
    ASSET_TEX3D_MEDIEVAL_VILLAGEDOORROUND,
    ASSET_TEX3D_MEDIEVAL_WHITEHOUSEWALL,
    ASSET_TEX3D_MEDIEVAL_WHITEHOUSEWALLWINDOW,
    ASSET_TEX3D_UNUSED_UTURN,
    ASSET_TEX3D_WINTER_ICYWATERFALL,
    ASSET_TEX3D_SPACE_WHITEWALLSCREEN,
    ASSET_TEX3D_OBJECTS_SILVERTROPHYEYE,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKY4_0,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKY4_1,
    ASSET_TEX3D_MEDIEVAL_VILLAGEWHITEWALL5,
    ASSET_TEX3D_SPACE_WHITEWALLSTEELCYLINDER,
    ASSET_TEX3D_SPACE_CITYLIGHTSYELLOWWHITE,
    ASSET_TEX3D_UNUSED_BETABUMPERICON,
    ASSET_TEX3D_COMMON_LOGEXPOSEDSIDE2,
    ASSET_TEX3D_COMMON_LOGBARK,
    ASSET_TEX3D_COMMON_LOGBARK2,
    ASSET_TEX3D_COMMON_LOGEXPOSEDSIDE3,
    ASSET_TEX3D_OBJECTS_DOMECOAST_0,
    ASSET_TEX3D_OBJECTS_DOMECOAST_1,
    ASSET_TEX3D_OBJECTS_DOMECOAST_2,
    ASSET_TEX3D_OBJECTS_DOMECOAST_3,
    ASSET_TEX3D_OBJECTS_DOMECOAST_4,
    ASSET_TEX3D_OBJECTS_DOMECOAST_5,
    ASSET_TEX3D_OBJECTS_DOMECOAST_6,
    ASSET_TEX3D_OBJECTS_DOMECOAST_7,
    ASSET_TEX3D_COMMON_REDARROWSIGN3,
    ASSET_TEX3D_OBJECTS_REDSPACESHIP,
    ASSET_TEX3D_UNUSED_UNKNOWNSIGNTEXTURE,
    ASSET_TEX3D_SPACE_ARROWNEONFLASHING,
    ASSET_TEX3D_TROPICAL_PIRATESHIPTRIM,
    ASSET_TEX3D_OBJECTS_DOORBOSSTOP,
    ASSET_TEX3D_OBJECTS_DOORBOSSBOTTOM,
    ASSET_TEX3D_OBJECTS_DOORBOSSWIZPIGDECO,
    ASSET_TEX3D_WINTER_WATERFROZEN,
    ASSET_TEX3D_OBJECTS_BRONZETROPHYENVMAP,
    ASSET_TEX3D_COMMON_BROWNSTONE,
    ASSET_TEX3D_OBJECTS_MAGICCARPETMIDDLE,
    ASSET_TEX3D_OBJECTS_MAGICCARPETEDGE,
    ASSET_TEX3D_OBJECTS_RAREWARELOGOGOLD,
    ASSET_TEX3D_UNUSED_BETATTDOORTOP,
    ASSET_TEX3D_UNUSED_BETATTDOORBOTTON,
    ASSET_TEX3D_OBJECTS_CHECKPOINT,
    ASSET_TEX3D_UNUSED_BETADRUMSTICKICON,
    ASSET_TEX3D_OBJECTS_DOMESUN,
    ASSET_TEX3D_OBJECTS_N64LOGOBLUE,
    ASSET_TEX3D_COMMON_ORANGEWOOD,
    ASSET_TEX3D_OBJECTS_N64LOGOGREEN,
    ASSET_TEX3D_OBJECTS_SEAMONSTEREYE,
    ASSET_TEX3D_UNUSED_SEAMONSTERUNKNOWN,
    ASSET_TEX3D_OBJECTS_YELLOWDINOSAURUNDERSIDE,
    ASSET_TEX3D_OBJECTS_SEAMONSTERUNDERSIDE,
    ASSET_TEX3D_OBJECTS_SEAMONSTERHEADBOTTOM,
    ASSET_TEX3D_OBJECTS_SEAMONSTERCHEEK,
    ASSET_TEX3D_OBJECTS_YELLOWDINOSAURCHEEK,
    ASSET_TEX3D_OBJECTS_SEAMONSTERNOSE,
    ASSET_TEX3D_OBJECTS_SEAMONSTERHEADTOP,
    ASSET_TEX3D_OBJECTS_YELLOWDINOSAURMOUTH,
    ASSET_TEX3D_OBJECTS_YELLOWDINOSAUREYEBROWS,
    ASSET_TEX3D_OBJECTS_SMOKEYEARS,
    ASSET_TEX3D_OBJECTS_SMOKEYNOSE,
    ASSET_TEX3D_OBJECTS_SMOKEYHEADTOP,
    ASSET_TEX3D_OBJECTS_N64LOGORED,
    ASSET_TEX3D_SPACE_BLUESTONEFLOOR,
    ASSET_TEX3D_OBJECTS_EXITSIGNSMALL,
    ASSET_TEX3D_OBJECTS_EXITSIGN,
    ASSET_TEX3D_TROPICAL_WOODGUARDRAIL,
    ASSET_TEX3D_WINTER_ICYPINKWALLSNOWY,
    ASSET_TEX3D_TROPICAL_FOG2,
    ASSET_TEX3D_OBJECTS_DOMEYELLOWSKY_0,
    ASSET_TEX3D_OBJECTS_DOMEYELLOWSKY_1,
    ASSET_TEX3D_OBJECTS_DOMEYELLOWSKY_2,
    ASSET_TEX3D_OBJECTS_DOMEYELLOWSKY_3,
    ASSET_TEX3D_DINO_DINOSAURTRACKS,
    ASSET_TEX3D_TROPICAL_SANDPATHGRASSY,
    ASSET_TEX3D_WINTER_VILLAGEHOUSEWALL,
    ASSET_TEX3D_OBJECTS_GOLDTROPHYSLEAVE,
    ASSET_TEX3D_OBJECTS_GOLDSILVERTROPHYMOUTH,
    ASSET_TEX3D_OBJECTS_LIGHTHOUSEBRICKDARK,
    ASSET_TEX3D_OBJECTS_LIGHTHOUSEBRICK,
    ASSET_TEX3D_OBJECTS_DOMEPLANETS_0,
    ASSET_TEX3D_OBJECTS_DOMEPLANETS_1,
    ASSET_TEX3D_OBJECTS_DOMEPLANETS_2,
    ASSET_TEX3D_OBJECTS_DOMEPLANETS_3,
    ASSET_TEX3D_OBJECTS_DOMEPLANETS_4,
    ASSET_TEX3D_OBJECTS_DOMEPLANETS_5,
    ASSET_TEX3D_OBJECTS_DOMEPLANETS_6,
    ASSET_TEX3D_OBJECTS_DOMESKYGRADIENT,
    ASSET_TEX3D_OBJECTS_GOLDGRADIENTDARK,
    ASSET_TEX3D_OBJECTS_GOLDGRADIENT,
    ASSET_TEX3D_OBJECTS_GOLDTROPHYSIGN,
    ASSET_TEX3D_COMMON_GRASSCHARSELECT,
    ASSET_TEX3D_OBJECTS_DOMEGREENBOTTOM,
    ASSET_TEX3D_OBJECTS_SPACESHIP14,
    ASSET_TEX3D_SPACE_SMALLGREENLIGHTS,
    ASSET_TEX3D_COMMON_HANGINGMOSS4,
    ASSET_TEX3D_SPACE_SPACEPOLEGREEN,
    ASSET_TEX3D_SPACE_GREENWALLMODULE,
    ASSET_TEX3D_OBJECTS_SPACESHIP2SIDE,
    ASSET_TEX3D_OBJECTS_SPACESHIP2CONNECTOR,
    ASSET_TEX3D_SPACE_REDWALLGREENSCREEN,
    ASSET_TEX3D_OBJECTS_SPACESHIP2SMALLLIGHTS,
    ASSET_TEX3D_OBJECTS_SPACESHIP214,
    ASSET_TEX3D_COMMON_GREYSTONE,
    ASSET_TEX3D_SPACE_COLOUREDSTONE,
    ASSET_TEX3D_COMMON_GREYPAVEMENT,
    ASSET_TEX3D_UNUSED_DOMEUNUSED,
    ASSET_TEX3D_UNUSED_BETAAIRZIPPER,
    ASSET_TEX3D_UNUSED_SIGN100,
    ASSET_TEX3D_WINTER_SNOWWALLSMALL,
    ASSET_TEX3D_WINTER_SNOWWALLLARGE,
    ASSET_TEX3D_UNUSED_UNKNOWNDECAL,
    ASSET_TEX3D_UNUSED_UNKNOWNGREENDOTS,
    ASSET_TEX3D_OBJECTS_DOMEGRASSYHILLS,
    ASSET_TEX3D_OBJECTS_DOMEGRASS,
    ASSET_TEX3D_UNUSED_BETAKRUNCHICON,
    ASSET_TEX3D_OBJECTS_DOORLEVELBOTTOM,
    ASSET_TEX3D_OBJECTS_DOORLEVELTOP,
    ASSET_TEX3D_OBJECTS_DOORLEVELTOPDONE,
    ASSET_TEX3D_UNUSED_DOORLEVELTOPUNUSED,
    ASSET_TEX3D_OBJECTS_DOORLEVELBOTTOMDONE,
    ASSET_TEX3D_UNUSED_DOORLEVELBOTTOMUNUSED,
    ASSET_TEX3D_UNUSED_DOORLEVELBOTTOMUNUSEDQMARK,
    ASSET_TEX3D_OBJECTS_DOORNUMBERSONESDIGIT,
    ASSET_TEX3D_OBJECTS_DOORNUMBERSTENSDIGIT,
    ASSET_TEX3D_OBJECTS_SPACESHIP2FRONT,
    ASSET_TEX3D_OBJECTS_LIGHTHOUSEDOOR,
    ASSET_TEX3D_OBJECTS_LIGHTHOUSEBRICK2,
    ASSET_TEX3D_OBJECTS_LIGHTHOUSEBEACONBOTTOM,
    ASSET_TEX3D_OBJECTS_LIGHTHOUSEROCKETWINGS,
    ASSET_TEX3D_OBJECTS_LIGHTHOUSEWINDOW,
    ASSET_TEX3D_COMMON_ELECTRICITYANIMATED,
    ASSET_TEX3D_OBJECTS_LIGHTHOUSEGLASSWINDOW,
    ASSET_TEX3D_SPACE_GLASSWINDOW2,
    ASSET_TEX3D_OBJECTS_LOGEND,
    ASSET_TEX3D_SPACE_LOOPGUARDRAIL,
    ASSET_TEX3D_OBJECTS_MIDIFADE,
    ASSET_TEX3D_OBJECTS_MISSLEBODY,
    ASSET_TEX3D_OBJECTS_MISSLEBACK,
    ASSET_TEX3D_UNUSED_MODE2,
    ASSET_TEX3D_OBJECTS_MONORAILFRONT,
    ASSET_TEX3D_OBJECTS_MONORAILRAILSKIRT,
    ASSET_TEX3D_OBJECTS_MONORAILFRONTTOP,
    ASSET_TEX3D_UNUSED_BETAPIPSYICON,
    ASSET_TEX3D_UNUSED_OLDFORESTTREEBARK,
    ASSET_TEX3D_OBJECTS_DOMEBLUETOP,
    ASSET_TEX3D_WINTER_ICETUNNELCEILING,
    ASSET_TEX3D_UNUSED_DOMEGREENUNKNOWN,
    ASSET_TEX3D_OBJECTS_TROPHYSIGNQMARK,
    ASSET_TEX3D_OBJECTS_BUBBLERHEAD,
    ASSET_TEX3D_OBJECTS_BUBBLERUNDERSIDE,
    ASSET_TEX3D_DINO_ORANGESTONE3,
    ASSET_TEX3D_TROPICAL_PALMTREELEAVES2,
    ASSET_TEX3D_TROPICAL_PALMTREEBARKBROWN2,
    ASSET_TEX3D_TROPICAL_PALMTREESHADOW2,
    ASSET_TEX3D_UNUSED_PAPERCENTER,
    ASSET_TEX3D_UNUSED_PAPEREDGE,
    ASSET_TEX3D_OBJECTS_SEAMONSTERSPINE,
    ASSET_TEX3D_OBJECTS_DOORWIZPIG_0,
    ASSET_TEX3D_OBJECTS_DOORWIZPIG_1,
    ASSET_TEX3D_OBJECTS_DOORWIZPIG_2,
    ASSET_TEX3D_OBJECTS_DOORWIZPIG_3,
    ASSET_TEX3D_COMMON_SEPIASTONE,
    ASSET_TEX3D_WINTER_WATERFROZEN2,
    ASSET_TEX3D_OBJECTS_GOLDTROPHYEYE,
    ASSET_TEX3D_OBJECTS_WIZPIGMOUNTAINEYE,
    ASSET_TEX3D_OBJECTS_WIZPIGMOUNTAINNOSE,
    ASSET_TEX3D_OBJECTS_GOLDTROPHYNOSE,
    ASSET_TEX3D_UNUSED_PROAM64BALLOONLOGO,
    ASSET_TEX3D_COMMON_RAINBOW,
    ASSET_TEX3D_COMMON_BLUEDARK,
    ASSET_TEX3D_COMMON_RARELOGOGRAY,
    ASSET_TEX3D_COMMON_RARELOGOGOLD,
    ASSET_TEX3D_OBJECTS_RAREWARE,
    ASSET_TEX3D_OBJECTS_SPACESHIP5,
    ASSET_TEX3D_SPACE_REDPATH,
    ASSET_TEX3D_COMMON_REDYELLOWLAMP,
    ASSET_TEX3D_SPACE_REDBRICKS,
    ASSET_TEX3D_OBJECTS_SPACESHIPFRONT,
    ASSET_TEX3D_DINO_ERODEDCANYONROCKSHADOW,
    ASSET_TEX3D_TROPICAL_PIRATESHIPROPE,
    ASSET_TEX3D_COMMON_YELLOWBRICK,
    ASSET_TEX3D_COMMON_YELLOWSTONEGROUND,
    ASSET_TEX3D_UNUSED_GRASSSANDYUNKNOWN,
    ASSET_TEX3D_COMMON_GREYPAVEMENTEDGE,
    ASSET_TEX3D_TROPICAL_YELLOWBRICKTILESANDY,
    ASSET_TEX3D_WINTER_DARKSTONEWALL,
    ASSET_TEX3D_DINO_ORANGESTONE4,
    ASSET_TEX3D_DINO_ORANGESTONE5,
    ASSET_TEX3D_UNUSED_PAPERUNKNOWN,
    ASSET_TEX3D_OBJECTS_SHIELDLEVEL1,
    ASSET_TEX3D_OBJECTS_SHIELDLEVEL2,
    ASSET_TEX3D_OBJECTS_SHIELDLEVEL3,
    ASSET_TEX3D_UNUSED_SIGNBALLOON,
    ASSET_TEX3D_UNUSED_SIGNWHITE,
    ASSET_TEX3D_UNUSED_SIGNYELLOW,
    ASSET_TEX3D_OBJECTS_SILVERTROPHYENVMAP,
    ASSET_TEX3D_UNUSED_SIGN60,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKY5_0,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKY5_1,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKY5_2,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKY5_3,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKY5_4,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKY5_5,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKY5_6,
    ASSET_TEX3D_OBJECTS_DOMEBLUESKY5_7,
    ASSET_TEX3D_SPACE_WALLTILELIGHTS2,
    ASSET_TEX3D_UNUSED_PAPERDECORATION,
    ASSET_TEX3D_SPACE_WALLTILELIGHTSLARGE,
    ASSET_TEX3D_WINTER_VILLAGEDOOR,
    ASSET_TEX3D_WINTER_HANGINGSNOW5,
    ASSET_TEX3D_WINTER_WOODENGUARDRAILSNOWY,
    ASSET_TEX3D_WINTER_DARKSTONEWALLSNOWY3,
    ASSET_TEX3D_WINTER_HANGINGSNOW6,
    ASSET_TEX3D_OBJECTS_SNOWBALLFACE,
    ASSET_TEX3D_WINTER_SNOW5,
    ASSET_TEX3D_OBJECTS_DOMEPLANETS2,
    ASSET_TEX3D_SPACE_BLUELIGHTSTONE,
    ASSET_TEX3D_SPACE_PURPLEPATH,
    ASSET_TEX3D_SPACE_PINKSTONE,
    ASSET_TEX3D_SPACE_ARCHINNER,
    ASSET_TEX3D_UNUSED_SPACESHIPUNKNOWN5,
    ASSET_TEX3D_UNUSED_SPACESHIPUNKNOWN6,
    ASSET_TEX3D_UNUSED_SPACESHIPUNKNOWN7,
    ASSET_TEX3D_COMMON_MOON,
    ASSET_TEX3D_UNUSED_SATURN,
    ASSET_TEX3D_UNUSED_SPACESHIPFRONTLOWRES,
    ASSET_TEX3D_OBJECTS_ASTEROID,
    ASSET_TEX3D_COMMON_SUN,
    ASSET_TEX3D_COMMON_SUN2,
    ASSET_TEX3D_UNUSED_SPACESHIPUNKNOWN8,
    ASSET_TEX3D_UNUSED_SPACESHIPUNKNOWN9,
    ASSET_TEX3D_COMMON_FINISHLINEFLAGORANGE2_0,
    ASSET_TEX3D_COMMON_FINISHLINEFLAGORANGE2_1,
    ASSET_TEX3D_COMMON_FINISHLINEFLAGSNOWY_0,
    ASSET_TEX3D_COMMON_FINISHLINEFLAGSNOWY_1,
    ASSET_TEX3D_COMMON_FINISHLINEFLAGSNOWY_2,
    ASSET_TEX3D_COMMON_FINISHLINEFLAGSNOWY_3,
    ASSET_TEX3D_COMMON_FINISHLINEFLAGSNOWY_4,
    ASSET_TEX3D_COMMON_LEVELNAMEBORDER,
    ASSET_TEX3D_OBJECTS_BRONZETROPHYEYE,
    ASSET_TEX3D_OBJECTS_BRONZETROPHYSMILE,
    ASSET_TEX3D_OBJECTS_BRONZETROPHYSCREW,
    ASSET_TEX3D_OBJECTS_EFFECTBOX,
    ASSET_TEX3D_OBJECTS_DOMEYELLOWSUN,
    ASSET_TEX3D_OBJECTS_DOMEBOTTOMSNOW,
    ASSET_TEX3D_UNUSED_SEAMONSTERUNKNOWN2,
    ASSET_TEX3D_UNUSED_SEAMONSTERUNKNOWNEYE,
    ASSET_TEX3D_OBJECTS_DOMEMOONCRESCENT,
    ASSET_TEX3D_OBJECTS_LIGHTHOUSEROCKETBOOSTER,
    ASSET_TEX3D_UNUSED_BETATIPTUPICON,
    ASSET_TEX3D_DINO_FALLENTREELOGSHADOW,
    ASSET_TEX3D_UNUSED_SIGN30,
    ASSET_TEX3D_OBJECTS_TRICKYTOPSFACEEYEBOTTOM,
    ASSET_TEX3D_OBJECTS_TRICKYTOPSEYESOCKET,
    ASSET_TEX3D_DINO_TRICKYTOPSSTATUEEYE,
    ASSET_TEX3D_OBJECTS_BRONZETROPHYDECORATION,
    ASSET_TEX3D_OBJECTS_GOLDTROPHYDECORATION,
    ASSET_TEX3D_OBJECTS_GOLDTROPHYNUMBER,
    ASSET_TEX3D_OBJECTS_SILVERTROPHYNUMBER,
    ASSET_TEX3D_OBJECTS_BRONZETROPHYNUMBER,
    ASSET_TEX3D_OBJECTS_SILVERTROPHYDECORATION,
    ASSET_TEX3D_WINTER_BLUEYSTATUEEYE,
    ASSET_TEX3D_WATER_WATER5,
    ASSET_TEX3D_OBJECTS_DOMEISLANDCOAST_0,
    ASSET_TEX3D_OBJECTS_DOMEISLANDCOAST_1,
    ASSET_TEX3D_OBJECTS_DOMEISLANDCOAST_2,
    ASSET_TEX3D_OBJECTS_DOMEISLANDCOAST_3,
    ASSET_TEX3D_OBJECTS_DOMEISLANDCOAST_4,
    ASSET_TEX3D_OBJECTS_DOMEISLANDCOAST_5,
    ASSET_TEX3D_OBJECTS_DOMEISLANDCOAST_6,
    ASSET_TEX3D_OBJECTS_DOMEISLANDCOAST_7,
    ASSET_TEX3D_OBJECTS_DOORWORLDGATEBACKBOTTOM,
    ASSET_TEX3D_OBJECTS_DOORWORLDGATESIDE,
    ASSET_TEX3D_OBJECTS_DOORWORLDGATEFRONTTOP,
    ASSET_TEX3D_OBJECTS_DOORWORLDGATEFRONTBOTTOM,
    ASSET_TEX3D_OBJECTS_DOORWORLDGATEBACKTOP,
    ASSET_TEX3D_OBJECTS_WHALEUNDERSIDE,
    ASSET_TEX3D_OBJECTS_WHALEFIN,
    ASSET_TEX3D_OBJECTS_WHALEEYE,
    ASSET_TEX3D_OBJECTS_WHALEBLOWHOLE,
    ASSET_TEX3D_OBJECTS_WHALEMOUTHTOP,
    ASSET_TEX3D_OBJECTS_WHALEMOUTHBOTTOM,
    ASSET_TEX3D_OBJECTS_WHALENOSE,
    ASSET_TEX3D_COMMON_WATERFALL2,
    ASSET_TEX3D_SPACE_REDGLASSWINDOW,
    ASSET_TEX3D_OBJECTS_WOODBLOCK,
    ASSET_TEX3D_OBJECTS_WOODSIGN,
    ASSET_TEX3D_OBJECTS_DOORLEVELSINGLEDONETOP,
    ASSET_TEX3D_OBJECTS_DOORLEVELSINGLEDONEBOTTOM,
    ASSET_TEX3D_UNUSED_DOORLEVELCHECKMARK,
    ASSET_TEX3D_UNUSED_DOORLEVELDONECHECKMARKTOP,
    ASSET_TEX3D_UNUSED_DOORLEVELDONECHECKMARKBOTTOM,
    ASSET_TEX3D_UNUSED_WOODUNKNOWN,
    ASSET_TEX3D_UNUSED_WHALEBAYPROGRAMMERARTSIGN,
    ASSET_TEX3D_UNUSED_TREASURECAVESPROGRAMMERARTSIGN,
    ASSET_TEX3D_UNUSED_CRESCENTISLANDPROGRAMMERARTSIGN,
    ASSET_TEX3D_UNUSED_PIRATELAGOONPROGRAMMERARTSIGN,
    ASSET_TEX3D_UNUSED_WOODUNKNOWN2,
    ASSET_TEX3D_UNUSED_VOLCANOSTONE,
    ASSET_TEX3D_OBJECTS_DOORTTICONLEFT,
    ASSET_TEX3D_OBJECTS_DOORTTICONRIGHT,
    ASSET_TEX3D_OBJECTS_DOORTTTOPRIGHT,
    ASSET_TEX3D_OBJECTS_DOORTTBOTTOMRIGHT,
    ASSET_TEX3D_OBJECTS_DOORTTTOPRIGHTACTIVE,
    ASSET_TEX3D_OBJECTS_DOORTTBOTTOMRIGHTTOPACTIVE,
    ASSET_TEX3D_OBJECTS_DOORTTBOTTOMRIGHTACTIVE,
    ASSET_TEX3D_OBJECTS_DOORBOSSBOTTOM2,
    ASSET_TEX3D_MEDIEVAL_ROOFTILESHINGLES4,
    ASSET_TEX3D_MEDIEVAL_VILLAGEWHITEWALL2,
    ASSET_TEX3D_UNUSED_TAJPADSNOW,
    ASSET_TEX3D_OBJECTS_DOORCHALLENGETOP,
    ASSET_TEX3D_OBJECTS_DOORCHALLENGEBOTTOM,
    ASSET_TEX3D_UNUSED_VINESONWOOD,
    ASSET_TEX3D_WINTER_HANGINGICE2,
    ASSET_TEX3D_UNUSED_UNKNOWNBALCONY,
    ASSET_TEX3D_UNUSED_GROUNDCOBBLE,
    ASSET_TEX3D_UNUSED_GREENBRICKWALL,
    ASSET_TEX3D_UNUSED_OLDBRICKWALL,
    ASSET_TEX3D_MEDIEVAL_ORANGEGATETIP,
    ASSET_TEX3D_COMMON_SANDWETDRYTRANSITION2,
    ASSET_TEX3D_MEDIEVAL_ROOFTILESHINGLES3,
    ASSET_TEX3D_MEDIEVAL_STEELGATE,
    ASSET_TEX3D_MEDIEVAL_STEELGATETIP,
    ASSET_TEX3D_COMMON_DIRTWALLMOSSY,
    ASSET_TEX3D_SPACE_BLUELIGHTNINGBOLT,
    ASSET_TEX3D_OBJECTS_WIZPIGSHIPEYE,
    ASSET_TEX3D_OBJECTS_WIZPIGSHIPNOSE,
    ASSET_TEX3D_OBJECTS_WIZPIGSHIPEXHASTBOTTOM,
    ASSET_TEX3D_OBJECTS_WIZPIGSHIPEXHASTTOP,
    ASSET_TEX3D_OBJECTS_REDSTRIPESFORSPACESHIP,
    ASSET_TEX3D_OBJECTS_PARTYPOST_0,
    ASSET_TEX3D_OBJECTS_PARTYPOST_1,
    ASSET_TEX3D_OBJECTS_PARTYPOST_2,
    ASSET_TEX3D_OBJECTS_PARTYPOST_3,
    ASSET_TEX3D_OBJECTS_PARTYPOST_4,
    ASSET_TEX3D_OBJECTS_PARTYPOST_5,
    ASSET_TEX3D_OBJECTS_DOORBOSSTAJTOP,
    ASSET_TEX3D_OBJECTS_DOORBOSSTAJBOTTOM,
    ASSET_TEX3D_OBJECTS_DOORLEVELGBNUMBERTOPRIGHT,
    ASSET_TEX3D_OBJECTS_DOORLEVELGBNUMBERTOPLEFT,
    ASSET_TEX3D_OBJECTS_DOORLEVELGBNUMBERBOTTOMRIGHT,
    ASSET_TEX3D_OBJECTS_DOORLEVELGBNUMBERBOTTOMLEFT,
    ASSET_TEX3D_UNUSED_FORESTBILLBOARD,
    ASSET_TEX3D_COMMON_BROWNSTONE2,
    ASSET_TEX3D_UNUSED_GREYSTONELARGE,
    ASSET_TEX3D_COMMON_LOGLARGEMOSSY,
    ASSET_TEX3D_COMMON_LOGEXPOSEDSIDE4,
    ASSET_TEX3D_MEDIEVAL_WATERFOUNTAIN,
    ASSET_TEX3D_UNUSED_UNKNOWNPURPLE,
    ASSET_TEX3D_UNUSED_UNKNOWNRED,
    ASSET_TEX3D_UNUSED_UNKNOWNRED2,
    ASSET_TEX3D_MEDIEVAL_VILLAGEWHITEWALL3,
    ASSET_TEX3D_COMMON_WOODGUARDRAILTOP,
    ASSET_TEX3D_UNUSED_VILLAGEGREYWALL,
    ASSET_TEX3D_MEDIEVAL_VILLAGEWHITEWALL4,
    ASSET_TEX3D_COMMON_FINISHLINEREDTAPE,
    ASSET_TEX3D_OBJECTS_BLUEYEYE,
    ASSET_TEX3D_COMMON_TRANSPARENT2,
    ASSET_TEX3D_UNUSED_GREENCYANGRADIENT,
    ASSET_TEX3D_UNUSED_GOLDUNKNOWN,
    ASSET_TEX3D_MEDIEVAL_SHRUBBERY,
    ASSET_TEX3D_COMMON_CYANYELLOWARROWSIGN2,
    ASSET_TEX3D_COMMON_DEBUGYELLOWBLUEINVISIBLE,
    ASSET_TEX3D_COMMON_BROWNSTONEGRASSY,
    ASSET_TEX3D_COMMON_BROWNSTONEGRASSY2,
    ASSET_TEX3D_OBJECTS_WIZPIGMOUTH,
    ASSET_TEX3D_WINTER_WALRUSCOVESIGN,
    ASSET_TEX3D_WINTER_EVERFROSTPEAKSIGN,
    ASSET_TEX3D_WINTER_FROSTYVILLAGESIGN,
    ASSET_TEX3D_WINTER_SNOWBALLVALLEY,
    ASSET_TEX3D_OBJECTS_WIZPIGROBELOWRES,
    ASSET_TEX3D_OBJECTS_WIZPIGSKINLOWRES,
    ASSET_TEX3D_COMMON_CYANYELLOWARROWNSIGNWITHBORDER,
    ASSET_TEX3D_TROPICAL_WHALEBAYSIGN,
    ASSET_TEX3D_TROPICAL_TREASURECAVESSIGN,
    ASSET_TEX3D_TROPICAL_CRESCENTISLANDSIGN,
    ASSET_TEX3D_TROPICAL_PIRATELAGOONSIGN,
    ASSET_TEX3D_OBJECTS_ROCKETENVMAP,
    ASSET_TEX3D_OBJECTS_WIZPIGBELTLOWRES,
    ASSET_TEX3D_SPACE_PURPLEWIZPIGSTONEDARK,
    ASSET_TEX3D_SPACE_PURPLEWIZPIGSTONE,
    ASSET_TEX3D_SPACE_PURPLEWIZPIGSTONEWALL,
    ASSET_TEX3D_SPACE_PURPLEWIZPIGSAND,
    ASSET_TEX3D_SPACE_WIZPIGCHAIRSEATCUSHION,
    ASSET_TEX3D_SPACE_WIZPIGCHARSEAT,
    ASSET_TEX3D_OBJECTS_ROCKETENVMAP2,
    ASSET_TEX3D_MEDIEVAL_HAUNTEDWOODSIGN,
    ASSET_TEX3D_MEDIEVAL_WINDMILLPLAINSSIGN,
    ASSET_TEX3D_MEDIEVAL_BOULDERCANYONSIGN,
    ASSET_TEX3D_MEDIEVAL_GREENWOODVILLAGESIGN_0,
    ASSET_TEX3D_MEDIEVAL_GREENWOODVILLAGESIGN_1,
    ASSET_TEX3D_SPACE_SPACEDUSTALLEYSIGN,
    ASSET_TEX3D_SPACE_DARKMOONCAVERNSSIGN_0,
    ASSET_TEX3D_SPACE_DARKMOONCAVERNSSIGN_1,
    ASSET_TEX3D_UNUSED_TWILIGHTCITYSIGN,
    ASSET_TEX3D_SPACE_SPACEPORTALPHASIGN,
    ASSET_TEX3D_SPACE_WIZPIGROOMARCHSIDETOP,
    ASSET_TEX3D_SPACE_WIZPIGROOMARCHFRONT,
    ASSET_TEX3D_SPACE_WIZPIGROOMARCHBOTTOM,
    ASSET_TEX3D_SPACE_WIZPIGROOMARCHSIDEBOTTOM,
    ASSET_TEX3D_UNUSED_KEITHPIGDOOR,
    ASSET_TEX3D_UNUSED_KEITHPIGDOOR2,
    ASSET_TEX3D_UNUSED_KEITHPIGDOOR3,
    ASSET_TEX3D_OBJECTS_SPACESHIPSIDEBOOSTER,
    ASSET_TEX3D_UNUSED_SPACESHIPUNKNOWN,
    ASSET_TEX3D_UNUSED_SPACESHIPUNKNOWN2,
    ASSET_TEX3D_UNUSED_SPACESHIPUNKNOWN3,
    ASSET_TEX3D_UNUSED_SPACESHIPUNKNOWN4,
    ASSET_TEX3D_SPACE_BIGPLANET,
    ASSET_TEX3D_UNUSED_WIZPIGROCKETTRANSPARENT,
    ASSET_TEX3D_WINTER_CANDYCANE2,
    ASSET_TEX3D_COMMON_DEBUGREDGREEN,
    ASSET_TEX3D_COMMON_FIRSTPLACE_0,
    ASSET_TEX3D_COMMON_FIRSTPLACE_1,
    ASSET_TEX3D_COMMON_FIRSTPLACE_2,
    ASSET_TEX3D_COMMON_FIRSTPLACE_3,
    ASSET_TEX3D_UNUSED_SMALLBOLT,
    ASSET_TEX3D_UNUSED_LARGEBOLT,
    ASSET_TEX3D_UNUSED_PURPLEPATH,
    ASSET_TEX3D_UNUSED_PURPLEPATHEDGE,
    ASSET_TEX3D_COMMON_YELLOWBRICKTILE3,
    ASSET_TEX3D_WINTER_HANGINGICE3,
    ASSET_TEX3D_WINTER_BROWNSTONESNOWY,
    ASSET_TEX3D_OBJECTS_GOLDENTAJEYE,
    ASSET_TEX3D_OBJECTS_YELLOWTRICKYTOPSTOES,
    ASSET_TEX3D_OBJECTS_YELLOWTRICKYTOPSFRILL,
    ASSET_TEX3D_OBJECTS_YELLOWTRICKYTOPSBACK,
    ASSET_TEX3D_OBJECTS_PINKTRICKYTOPSTOES,
    ASSET_TEX3D_OBJECTS_PINKTRICKYTOPSUNDERSIDE,
    ASSET_TEX3D_OBJECTS_PINKTRICKYTOPSNOSE,
    ASSET_TEX3D_OBJECTS_PINKTRICKYTOPSFRILL,
    ASSET_TEX3D_OBJECTS_PINKTRICKYTOPSBACK,
    ASSET_TEX3D_OBJECTS_PINKTRICKYTOPSEYE,
    ASSET_TEX3D_OBJECTS_PINKTRICKYTOPSSKIN,
    ASSET_TEX3D_OBJECTS_MAGNETFX,
    ASSET_TEX3D_OBJECTS_MINISHIPNOSE,
    ASSET_TEX3D_OBJECTS_MINISHIPHULL,
    ASSET_TEX3D_OBJECTS_MINISHIPEXHAST,
    ASSET_TEX3D_OBJECTS_MINISHIPBOOSTER,
    ASSET_TEX3D_OBJECTS_MINISHIPBOOSTEREXHAST,
    ASSET_TEX3D_SPACE_FANUPDRAFT,
    ASSET_TEX3D_OBJECTS_N64LOGOYELLOW,
    ASSET_TEX3D_UNUSED_MENUTEX_0,
    ASSET_TEX3D_UNUSED_MENUTEX_1,
    ASSET_TEX3D_UNUSED_MENUTEX_2,
    ASSET_TEX3D_UNUSED_MENUTEX_3,
    ASSET_TEX3D_UNUSED_MENUTEX_4,
    ASSET_TEX3D_UNUSED_MENUTEX_5,
    ASSET_TEX3D_UNUSED_MENUTEX_6,
    ASSET_TEX3D_UNUSED_MENUTEX_7,
    ASSET_TEX3D_UNUSED_MENUTEX_8,
    ASSET_TEX3D_UNUSED_MENUTEX_9,
    ASSET_TEX3D_UNUSED_MENUTEX_10,
    ASSET_TEX3D_UNUSED_MENUTEX_11,
    ASSET_TEX3D_UNUSED_MENUTEX_12,
    ASSET_TEX3D_UNUSED_MENUTEX_13,
    ASSET_TEX3D_UNUSED_MENUTEX_14,
    ASSET_TEX3D_UNUSED_MENUTEX_15,
    ASSET_TEX3D_UNUSED_MENUTEX_16,
    ASSET_TEX3D_UNUSED_MENUTEX_17,
    ASSET_TEX3D_UNUSED_MENUTEX_18,
    ASSET_TEX3D_UNUSED_MENUTEX_19,
    ASSET_TEX3D_UNUSED_MENUTEX_20,
    ASSET_TEX3D_UNUSED_MENUTEX_21,
    ASSET_TEX3D_UNUSED_MENUTEX_22,
    ASSET_TEX3D_UNUSED_MENUTEX_23,
    ASSET_TEX3D_UNUSED_MENUTEX_24,
    ASSET_TEX3D_UNUSED_MENUTEX_25,
    ASSET_TEX3D_UNUSED_PLANESHADOW,
    ASSET_TEX3D_UNUSED_MAGICCARPETSHADOW,
    ASSET_TEX3D_UNUSED_UNKNOWNEFFECT,
    ASSET_TEX3D_OBJECTS_TRADEMARK,
    ASSET_TEX3D_MEDIEVAL_TANSTONETILE,
    ASSET_TEX3D_WINTER_ICICLEPYRAMIDTOPENTRANCETEXUNKNOWN,
    ASSET_TEX3D_SPACE_STARCITYSIGN,
    ASSET_TEX3D_OBJECTS_LEVELDOORSILVERBALLOONTOPRIGHT,
    ASSET_TEX3D_OBJECTS_LEVELDOORSILVERBALLOONTOPLEFT,
    ASSET_TEX3D_OBJECTS_LEVELDOORSILVERBALLOONBOTTOMRIGHT,
    ASSET_TEX3D_OBJECTS_LEVELDOORSILVERBALLOONBOTTOMLEFT,
    ASSET_TEX3D_OBJECTS_LEVELDOORSILVERBALLOONBOTTOMFULLCLEAR,
    ASSET_TEX3D_OBJECTS_LEVELDOORSILVERBALLOONTOPFULLCLEAR,
    ASSET_TEX3D_OBJECTS_SILVERBALLOONENVMAP,
    ASSET_TEX3D_OBJECTS_LEVELDOORSILVERNUMBERTOP,
    ASSET_TEX3D_OBJECTS_LEVELDOORSILVERNUMBERBOTTOM,
    ASSET_TEX3D_OBJECTS_SPACESHIP3WINDOW,
    ASSET_TEX3D_OBJECTS_SPACESHIP3HULL,
    ASSET_TEX3D_OBJECTS_SPACESHIP3BOOSTER,
    ASSET_TEX3D_OBJECTS_SPACESHIP3FRONT,
    ASSET_TEX3D_COMMON_YELLOWBRICKTILE4,
    ASSET_TEX3D_COMMON_VOID,
    ASSET_TEX3D_COMMON_DEBUGFIREMOUNTAINCEILING,
    ASSET_TEX3D_UNUSED_YELLOWARROWSIGN2,
    ASSET_TEX3D_COMMON_FINISHLINEFLAGSNOWY2_0,
    ASSET_TEX3D_COMMON_FINISHLINEFLAGSNOWY2_1,
    ASSET_TEX3D_COMMON_FINISHLINEFLAGSNOWY2_2,
    ASSET_TEX3D_COMMON_FINISHLINEFLAGSNOWY2_3,
    ASSET_TEX3D_COMMON_FINISHLINEFLAGSNOWY2_4,
    ASSET_TEX3D_COMMON_WATERFALL3,
    ASSET_TEX3D_COMMON_YELLOWBRICKTILE5,
    ASSET_TEX3D_COMMON_REDARROWSIGN4,
    ASSET_TEX3D_COMMON_YELLOWBRICKTILE6,
    ASSET_TEX3D_MEDIEVAL_VILLAGEGREYWALL2,
    ASSET_TEX3D_COMMON_YELLOWBRICKTILE7,
    ASSET_TEX3D_COMMON_SAND6,
    ASSET_TEX3D_TROPICAL_PALMTREESHADOWLONG,
    ASSET_TEX3D_COMMON_DEBUGBLACKWHITE,
    ASSET_TEX3D_SPACE_RAREWARESIGNNONBLINKING,
    ASSET_TEXTURES_3D_1401,
    ASSET_TEXTURES_3D_1402,
    ASSET_TEXTURES_3D_1403,
    ASSET_TEXTURES_3D_1404,
    ASSET_TEXTURES_3D_1405,
    ASSET_TEXTURES_3D_1406,
    ASSET_TEXTURES_3D_1407,
    ASSET_TEXTURES_3D_1408,
    ASSET_TEXTURES_3D_1409,
    ASSET_TEXTURES_3D_1410,
    ASSET_TEXTURES_3D_1411,
    ASSET_TEXTURES_3D_1412,
    ASSET_TEXTURES_3D_1413,
    ASSET_TEXTURES_3D_1414,
    ASSET_TEX3D_SPACE_REDPILLARSPIKE2,
    ASSET_TEXTURES_3D_COUNT
} AssetTextures3dEnum;
typedef enum AssetTextures2dEnum {
    ASSET_TEX2D_SMALLFONT_0,
    ASSET_TEX2D_SMALLFONT_1,
    ASSET_TEX2D_SMALLFONT_2,
    ASSET_TEX2D_HUD_RETICLESQUARE,
    ASSET_TEX2D_HUD_RETICLECIRCLE,
    ASSET_TEX2D_HUD_RETICLEX,
    ASSET_TEX2D_UNUSED_CAROUTLINE,
    ASSET_TEX2D_UNUSED_TRANSPARENT,
    ASSET_TEX2D_SHADOW_CAR,
    ASSET_TEX2D_SHADOW_CIRCLE,
    ASSET_TEX2D_SHADOW_PLANE,
    ASSET_TEX2D_SHADOW_MAGICCARPET,
    ASSET_TEX2D_SHADOW_WIZPIGROCKET,
    ASSET_TEX2D_SHADOW_UNKNOWN,
    ASSET_TEX2D_SHADOW_PTERODACTYL,
    ASSET_TEX2D_SHADOW_SMOKEY,
    ASSET_TEX2D_OBJECTS_GROUNDZIPPER,
    ASSET_TEX2D_MINIMAP_FOSSILCANYON,
    ASSET_TEX2D_MINIMAP_ANCIENTLAKE,
    ASSET_TEX2D_MINIMAP_PIRATELAGOON,
    ASSET_TEX2D_MINIMAP_WHALEBAY,
    ASSET_TEX2D_MINIMAP_SNOWBALLVALLEY,
    ASSET_TEX2D_MINIMAP_HOTTOPVOLCANO,
    ASSET_TEX2D_MINIMAP_CRESCENTISLAND,
    ASSET_TEX2D_MINIMAP_UNUSED,
    ASSET_TEX2D_MINIMAP_EVERFROSTPEAK,
    ASSET_TEX2D_MINIMAP_UNUSED2,
    ASSET_TEX2D_MINIMAP_WALRUSCOVE,
    ASSET_TEX2D_MINIMAP_UNUSED3,
    ASSET_TEX2D_MINIMAP_BOULDERCANYON,
    ASSET_TEX2D_MINIMAP_SMOKEYCASTLE,
    ASSET_TEX2D_MINIMAP_CENTRALAREA,
    ASSET_TEX2D_MINIMAP_FIREMOUNTAIN,
    ASSET_TEX2D_MINIMAP_SPACEPORTALPHA,
    ASSET_TEX2D_MINIMAP_SPACEDUSTALLEY,
    ASSET_TEX2D_MINIMAP_TREASURECAVES,
    ASSET_TEX2D_MINIMAP_GREENWOODVILLAGE,
    ASSET_TEX2D_MINIMAP_DARKMOONCAVERNS,
    ASSET_TEX2D_MINIMAP_STARCITY,
    ASSET_TEX2D_MINIMAP_WINDMILLPLAINS,
    ASSET_TEX2D_MINIMAP_FROSTYVILLAGE,
    ASSET_TEX2D_MINIMAP_DARKWATERBEACH,
    ASSET_TEX2D_MINIMAP_JUNGLEFALLS,
    ASSET_TEX2D_MINIMAP_ICICLEPYRAMID,
    ASSET_TEX2D_MINIMAP_HAUNTEDWOODS,
    ASSET_TEX2D_MINIMAP_BLUEY,
    ASSET_TEX2D_MINIMAP_BUBBLER,
    ASSET_TEX2D_MINIMAP_SMOKEY,
    ASSET_TEX2D_MINIMAP_TRICKYTOPS,
    ASSET_TEX2D_MINIMAP_WIZPIG1,
    ASSET_TEX2D_MINIMAP_WIZPIG2,
    ASSET_TEX2D_WEATHER_SNOWFLAKE,
    ASSET_TEX2D_WEATHER_RAIN,
    ASSET_TEX2D_WEATHER_UNKNOWN,
    ASSET_TEX2D_WEATHER_RAINDROP_0,
    ASSET_TEX2D_WEATHER_RAINDROP_1,
    ASSET_TEX2D_WEATHER_RAINDROP_2,
    ASSET_TEX2D_WEATHER_RAINDROP_3,
    ASSET_TEX2D_WEATHER_RAINDROP_4,
    ASSET_TEX2D_WEATHER_SNOWFLAKE2,
    ASSET_TEX2D_PARTICLE_SMOKE,
    ASSET_TEX2D_PARTICLE_SMOKE2,
    ASSET_TEX2D_WATER_DETAIL,
    ASSET_TEX2D_WATER_DETAIL2,
    ASSET_TEX2D_OBJECTS_LENSFLARE1,
    ASSET_TEX2D_OBJECTS_LENSFLARE2,
    ASSET_TEX2D_OBJECTS_LENSFLARE3,
    ASSET_TEX2D_UNKNOWN_WATERFALL,
    ASSET_TEX2D_UNKNOWN_WATERFALL2,
    ASSET_TEX2D_UNKNOWN_WHITECLOUDS,
    ASSET_TEX2D_PARTICLES_TREELEAF,
    ASSET_TEX2D_UNKNOWN_REDGREENUNKNOWN,
    ASSET_TEX2D_UNKNOWN_SCHOOLOFFISH,
    ASSET_TEX2D_UNKNOWN_BUTTERFLYORANGE,
    ASSET_TEX2D_UNKNOWN_BUTTERFLYPURPLE,
    ASSET_TEX2D_UNKNOWN_BAT,
    ASSET_TEX2D_UNKNOWN_FISH,
    ASSET_TEX2D_UNKNOWN_BROWNEGG,
    ASSET_TEX2D_PARTICLES_SMOKE3,
    ASSET_TEX2D_PARTICLES_SMOKE4_0,
    ASSET_TEX2D_PARTICLES_SMOKE4_1,
    ASSET_TEX2D_PARTICLES_SMOKE4_2,
    ASSET_TEX2D_PARTICLES_SMOKE4_3,
    ASSET_TEX2D_PARTICLES_SMOKE4_4,
    ASSET_TEX2D_PARTICLES_SMOKE4_5,
    ASSET_TEX2D_PARTICLES_SMOKE4_6,
    ASSET_TEX2D_PARTICLES_BUBBLESSMALL_0,
    ASSET_TEX2D_PARTICLES_BUBBLESSMALL_1,
    ASSET_TEX2D_PARTICLES_SMOKE5,
    ASSET_TEX2D_FUNFONT_0,
    ASSET_TEX2D_FUNFONT_1,
    ASSET_TEX2D_FUNFONT_2,
    ASSET_TEX2D_FUNFONT_3,
    ASSET_TEX2D_FUNFONT_4,
    ASSET_TEX2D_FUNFONT_5,
    ASSET_TEX2D_MENU_TRACKSELECTBGDINODOMAIN_0,
    ASSET_TEX2D_MENU_TRACKSELECTBGDINODOMAIN_1,
    ASSET_TEX2D_MENU_TRACKSELECTBGSHERBETISLAND_0,
    ASSET_TEX2D_MENU_TRACKSELECTBGSHERBETISLAND_1,
    ASSET_TEX2D_MENU_TRACKSELECTBGSNOWFLAKEMOUNTAIN_0,
    ASSET_TEX2D_MENU_TRACKSELECTBGSNOWFLAKEMOUNTAIN_1,
    ASSET_TEX2D_MENU_TRACKSELECTBGDRAGONFOREST_0,
    ASSET_TEX2D_MENU_TRACKSELECTBGDRAGONFOREST_1,
    ASSET_TEX2D_MENU_TRACKSELECTBGFUTUREFUNLAND_0,
    ASSET_TEX2D_MENU_TRACKSELECTBGFUTUREFUNLAND_1,
    ASSET_TEX2D_UNKNOWN_UNKWHITETEX,
    ASSET_TEX2D_MENU_TRACKSELECTLOCKED_0,
    ASSET_TEX2D_MENU_TRACKSELECTLOCKED_1,
    ASSET_TEX2D_MENU_TRACKSELECTLOCKED_2,
    ASSET_TEX2D_MENU_TRACKSELECTUNLOCKED_0,
    ASSET_TEX2D_MENU_TRACKSELECTUNLOCKED_1,
    ASSET_TEX2D_MENU_TRACKSELECTUNLOCKED_2,
    ASSET_TEX2D_MENU_ARROWBLUERIGHT,
    ASSET_TEX2D_MENU_ARROWBLUEUP,
    ASSET_TEX2D_MENU_ARROWBLUELEFT,
    ASSET_TEX2D_MENU_ARROWBLUEDOWN,
    ASSET_TEX2D_OBJECTS_BUBBLEWEAPON_0,
    ASSET_TEX2D_OBJECTS_BUBBLEWEAPON_1,
    ASSET_TEX2D_OBJECTS_BUBBLEWEAPON_2,
    ASSET_TEX2D_OBJECTS_BUBBLEWEAPON_3,
    ASSET_TEX2D_MENU_TTBEATENICON,
    ASSET_TEX2D_HUD_EGGICON,
    ASSET_TEX2D_HUD_KRUNCHICON,
    ASSET_TEX2D_HUD_BUMPERICON,
    ASSET_TEX2D_HUD_TIPTUPICON,
    ASSET_TEX2D_HUD_TIMBERICON,
    ASSET_TEX2D_HUD_CONKERICON,
    ASSET_TEX2D_HUD_BANJOICON,
    ASSET_TEX2D_HUD_DRUMSTICKICON,
    ASSET_TEX2D_HUD_PIPSYICON,
    ASSET_TEX2D_HUD_TTICON,
    ASSET_TEX2D_HUD_DIDDYICON,
    ASSET_TEX2D_UNKNOWN_SMALLGOLDCAP,
    ASSET_TEX2D_MENU_CARICON_0,
    ASSET_TEX2D_MENU_CARICON_1,
    ASSET_TEX2D_MENU_HOVERICON_0,
    ASSET_TEX2D_MENU_HOVERICON_1,
    ASSET_TEX2D_MENU_PLANEICON_0,
    ASSET_TEX2D_MENU_PLANEICON_1,
    ASSET_TEX2D_MENU_LABELCAROPTIONNONSELECTED,
    ASSET_TEX2D_MENU_LABELCAROPTIONSELECTED,
    ASSET_TEX2D_MENU_LABELHOVEROPTIONNONSELECTED,
    ASSET_TEX2D_MENU_LABELHOVEROPTIONSELECTED,
    ASSET_TEX2D_MENU_LABELPLANEOPTIONNONSELECTED,
    ASSET_TEX2D_MENU_LABELPLANEOPTIONSELECTED,
    ASSET_TEX2D_MENU_TIMETRIALONICON_0,
    ASSET_TEX2D_MENU_TIMETRIALONICON_1,
    ASSET_TEX2D_MENU_TIMETRIALOFFICON_0,
    ASSET_TEX2D_MENU_TIMETRIALOFFICON_1,
    ASSET_TEX2D_MENU_LABELONOPTIONNONSELECTED,
    ASSET_TEX2D_MENU_LABELONOPTIONSELECTED,
    ASSET_TEX2D_MENU_LABELOFFOPTIONNONSELECTED,
    ASSET_TEX2D_MENU_LABELOFFOPTIONSELECTED,
    ASSET_TEX2D_MENU_LABELPLAYER1,
    ASSET_TEX2D_MENU_LABELPLAYER2,
    ASSET_TEX2D_MENU_LABELPLAYER3,
    ASSET_TEX2D_MENU_LABELPLAYER4,
    ASSET_TEX2D_MENU_LABELTT,
    ASSET_TEX2D_MENU_LABELVEHICLE,
    ASSET_TEX2D_SUBTITLEFONT_0,
    ASSET_TEX2D_SUBTITLEFONT_1,
    ASSET_TEX2D_SUBTITLEFONT_2,
    ASSET_TEX2D_BIGFONT_A,
    ASSET_TEX2D_BIGFONT_B,
    ASSET_TEX2D_BIGFONT_C,
    ASSET_TEX2D_BIGFONT_D,
    ASSET_TEX2D_BIGFONT_E,
    ASSET_TEX2D_BIGFONT_F,
    ASSET_TEX2D_BIGFONT_G,
    ASSET_TEX2D_BIGFONT_H,
    ASSET_TEX2D_BIGFONT_I,
    ASSET_TEX2D_BIGFONT_J,
    ASSET_TEX2D_BIGFONT_K,
    ASSET_TEX2D_BIGFONT_L,
    ASSET_TEX2D_BIGFONT_M,
    ASSET_TEX2D_BIGFONT_N,
    ASSET_TEX2D_BIGFONT_O,
    ASSET_TEX2D_BIGFONT_P,
    ASSET_TEX2D_BIGFONT_Q,
    ASSET_TEX2D_BIGFONT_R,
    ASSET_TEX2D_BIGFONT_S,
    ASSET_TEX2D_BIGFONT_T,
    ASSET_TEX2D_BIGFONT_U,
    ASSET_TEX2D_BIGFONT_V,
    ASSET_TEX2D_BIGFONT_W,
    ASSET_TEX2D_BIGFONT_X,
    ASSET_TEX2D_BIGFONT_Y,
    ASSET_TEX2D_BIGFONT_Z,
    ASSET_TEX2D_BIGFONT_QUESTIONMARK,
    ASSET_TEX2D_BIGFONT_PERIOD,
    ASSET_TEX2D_OBJECTS_SPARKLE_0,
    ASSET_TEX2D_OBJECTS_SPARKLE_1,
    ASSET_TEX2D_OBJECTS_SPARKLE_2,
    ASSET_TEX2D_OBJECTS_SPARKLE_3,
    ASSET_TEX2D_OBJECTS_SPARKLE_4,
    ASSET_TEX2D_OBJECTS_SPARKLE_5,
    ASSET_TEX2D_OBJECTS_SPARKLE_6,
    ASSET_TEX2D_OBJECTS_BOMBEXPLOSIONBLUE,
    ASSET_TEX2D_OBJECTS_BOMBEXPLOSIONYELLOW,
    ASSET_TEX2D_OBJECTS_BOMBEXPLOSIONRED,
    ASSET_TEX2D_OBJECTS_BOMBEXPLOSIONGREEN,
    ASSET_TEX2D_OBJECTS_BOMBEXPLOSIONCYAN,
    ASSET_TEX2D_OBJECTS_BOMBEXPLOSIONWHITE,
    ASSET_TEX2D_OBJECTS_BOMBEXPLOSIONORANGE,
    ASSET_TEX2D_OBJECTS_BOMBEXPLOSIONPURPLE,
    ASSET_TEX2D_UNKNOWN_WHITEGREYCHECKBOARD,
    ASSET_TEX2D_UNKNOWN_NEGATIVERED,
    ASSET_TEX2D_UNKNOWN_NEGATIVEBLUE,
    ASSET_TEX2D_UNKNOWN_NEGATIVEGREEN,
    ASSET_TEX2D_UNKNOWN_NEGATIVEPURPLE,
    ASSET_TEX2D_OBJECTS_RAINBOW_0,
    ASSET_TEX2D_OBJECTS_RAINBOW_1,
    ASSET_TEX2D_OBJECTS_EGG_0,
    ASSET_TEX2D_OBJECTS_EGG_1,
    ASSET_TEX2D_OBJECTS_EGG_2,
    ASSET_TEX2D_OBJECTS_EGG_3,
    ASSET_TEX2D_MENU_WOODPANEL,
    ASSET_TEX2D_MENU_COBBLEPANEL,
    ASSET_TEX2D_MENU_PORTALPANEL,
    ASSET_TEX2D_MENU_ICONRUBBISHBIN,
    ASSET_TEX2D_MENU_ICONN64,
    ASSET_TEX2D_MENU_ICONTIMES,
    ASSET_TEX2D_MENU_ICONCONTROLLERPAK,
    ASSET_TEX2D_MENU_ICONEXTERNALDATA,
    ASSET_TEX2D_MENU_ICONGHOSTS,
    ASSET_TEX2D_OBJECTS_BOMB_0,
    ASSET_TEX2D_OBJECTS_BOMB_1,
    ASSET_TEX2D_PARTICLES_OILPUDDLE,
    ASSET_TEX2D_OBJECTS_OILSLICK,
    ASSET_TEX2D_UNKNOWN_EYESINDARK,
    ASSET_TEX2D_HUD_COLON,
    ASSET_TEX2D_HUD_RETICALHOMING_0,
    ASSET_TEX2D_HUD_RETICALHOMING_1,
    ASSET_TEX2D_OBJECTS_DEBUGREDSPHERE,
    ASSET_TEX2D_HUD_FINISH_0,
    ASSET_TEX2D_HUD_FINISH_1,
    ASSET_TEX2D_HUD_FINISH_2,
    ASSET_TEX2D_HUD_GETREADY_0,
    ASSET_TEX2D_HUD_GETREADY_1,
    ASSET_TEX2D_HUD_GETREADY_2,
    ASSET_TEX2D_HUD_GO_0,
    ASSET_TEX2D_HUD_GO_1,
    ASSET_TEX2D_HUD_LAP,
    ASSET_TEX2D_HUD_FORWARDSLASH,
    ASSET_TEX2D_HUD_TIME,
    ASSET_TEX2D_HUD_PLACENUMBER_0,
    ASSET_TEX2D_HUD_PLACENUMBER_1,
    ASSET_TEX2D_HUD_PLACENUMBER_2,
    ASSET_TEX2D_HUD_PLACENUMBER_3,
    ASSET_TEX2D_HUD_PLACENUMBER_4,
    ASSET_TEX2D_HUD_PLACENUMBER_5,
    ASSET_TEX2D_HUD_PLACENUMBER_6,
    ASSET_TEX2D_HUD_PLACENUMBER_7,
    ASSET_TEX2D_HUD_TIMERNUMBER_0,
    ASSET_TEX2D_HUD_TIMERNUMBER_1,
    ASSET_TEX2D_HUD_TIMERNUMBER_2,
    ASSET_TEX2D_HUD_TIMERNUMBER_3,
    ASSET_TEX2D_HUD_TIMERNUMBER_4,
    ASSET_TEX2D_HUD_TIMERNUMBER_5,
    ASSET_TEX2D_HUD_TIMERNUMBER_6,
    ASSET_TEX2D_HUD_TIMERNUMBER_7,
    ASSET_TEX2D_HUD_TIMERNUMBER_8,
    ASSET_TEX2D_HUD_TIMERNUMBER_9,
    ASSET_TEX2D_HUD_COLONSMALL,
    ASSET_TEX2D_HUD_TIMERNUMBERSMALL_0,
    ASSET_TEX2D_HUD_TIMERNUMBERSMALL_1,
    ASSET_TEX2D_HUD_TIMERNUMBERSMALL_2,
    ASSET_TEX2D_HUD_TIMERNUMBERSMALL_3,
    ASSET_TEX2D_HUD_TIMERNUMBERSMALL_4,
    ASSET_TEX2D_HUD_TIMERNUMBERSMALL_5,
    ASSET_TEX2D_HUD_TIMERNUMBERSMALL_6,
    ASSET_TEX2D_HUD_TIMERNUMBERSMALL_7,
    ASSET_TEX2D_HUD_TIMERNUMBERSMALL_8,
    ASSET_TEX2D_HUD_TIMERNUMBERSMALL_9,
    ASSET_TEX2D_HUD_GOSMALL,
    ASSET_TEX2D_HUD_LAPSMALL,
    ASSET_TEX2D_HUD_GETREADYSMALL,
    ASSET_TEX2D_HUD_FINALSMALL,
    ASSET_TEX2D_HUD_FINISHSMALL,
    ASSET_TEX2D_HUD_LAP2SMALL,
    ASSET_TEX2D_HUD_WAYSMALL,
    ASSET_TEX2D_HUD_WRONGSMALL,
    ASSET_TEX2D_OBJECTS_POSITIONARROW_0,
    ASSET_TEX2D_OBJECTS_POSITIONARROW_1,
    ASSET_TEX2D_OBJECTS_POSITIONARROW_2,
    ASSET_TEX2D_HUD_TIMERNUMBERSSINGLETEX,
    ASSET_TEX2D_HUD_TIMERNUMBERSSMALLSINGLETEX,
    ASSET_TEX2D_HUD_COLON2,
    ASSET_TEX2D_HUD_COLORSMALL2,
    ASSET_TEX2D_HUD_LAP2,
    ASSET_TEX2D_HUD_TIME2,
    ASSET_TEX2D_HUD_FORWARDSLASHSMALL,
    ASSET_TEX2D_HUD_FORWARDSLASH2,
    ASSET_TEX2D_HUD_X,
    ASSET_TEX2D_HUD_PLACENUMBERSSINGLETEX,
    ASSET_TEX2D_HUD_PLACENUMBERSUFFIXES,
    ASSET_TEX2D_HUD_XSMALL,
    ASSET_TEX2D_HUD_SILVERCOINCOLLECTED,
    ASSET_TEX2D_HUD_GOLDENBALLOONICON,
    ASSET_TEX2D_HUD_SILVERBALLOONICON,
    ASSET_TEX2D_OBJECTS_LEVELNAME,
    ASSET_TEX2D_MINIMAP_NPC,
    ASSET_TEX2D_MINIMAP_PLAYER,
    ASSET_TEX2D_HUD_WEAPONICONBOOST_0,
    ASSET_TEX2D_HUD_WEAPONICONBOOST_1,
    ASSET_TEX2D_HUD_WEAPONICONBOOST_2,
    ASSET_TEX2D_HUD_WEAPONICONROCKET_0,
    ASSET_TEX2D_HUD_WEAPONICONROCKET_1,
    ASSET_TEX2D_HUD_WEAPONICONROCKET_2,
    ASSET_TEX2D_HUD_WEAPONICONTRAP_0,
    ASSET_TEX2D_HUD_WEAPONICONTRAP_1,
    ASSET_TEX2D_HUD_WEAPONICONTRAP_2,
    ASSET_TEX2D_HUD_WEAPONICONSHIELD_0,
    ASSET_TEX2D_HUD_WEAPONICONSHIELD_1,
    ASSET_TEX2D_HUD_WEAPONICONSHIELD_2,
    ASSET_TEX2D_HUD_WEAPONICONMAGNET_0,
    ASSET_TEX2D_HUD_WEAPONICONMAGNET_1,
    ASSET_TEX2D_HUD_WEAPONICONMAGNET_2,
    ASSET_TEX2D_HUD_WEAPONICONROCKETNUMBERS_0,
    ASSET_TEX2D_HUD_WEAPONICONROCKETNUMBERS_1,
    ASSET_TEX2D_HUD_WEAPONICONROCKETNUMBERS_2,
    ASSET_TEX2D_HUD_WEAPONICONROCKETNUMBERS_3,
    ASSET_TEX2D_HUD_WEAPONICONROCKETNUMBERS_4,
    ASSET_TEX2D_HUD_WEAPONICONROCKETNUMBERS_5,
    ASSET_TEX2D_HUD_WEAPONICONROCKETNUMBERS_6,
    ASSET_TEX2D_HUD_WEAPONICONROCKETNUMBERS_7,
    ASSET_TEX2D_HUD_WEAPONICONROCKETNUMBERS_8,
    ASSET_TEX2D_HUD_WEAPONICONROCKETNUMBERS_9,
    ASSET_TEX2D_UNUSED_BETAICONKRUNCH,
    ASSET_TEX2D_UNUSED_BETAICONBUMPER,
    ASSET_TEX2D_UNUSED_BETAICONTIPTUP,
    ASSET_TEX2D_UNUSED_BETAICONCONKER,
    ASSET_TEX2D_UNUSED_BETAICONTIMBER,
    ASSET_TEX2D_UNUSED_BETAICONBANJO,
    ASSET_TEX2D_UNUSED_BETAICONDRUMSTICK,
    ASSET_TEX2D_UNUSED_BETAICONPIPSY,
    ASSET_TEX2D_HUD_FINALLAP_0,
    ASSET_TEX2D_HUD_FINALLAP_1,
    ASSET_TEX2D_HUD_FINALLAP_2,
    ASSET_TEX2D_HUD_FINALLAP_3,
    ASSET_TEX2D_HUD_FINALLAP_4,
    ASSET_TEX2D_HUD_FINAL_0,
    ASSET_TEX2D_HUD_FINAL_1,
    ASSET_TEX2D_HUD_LAPLARGE_0,
    ASSET_TEX2D_HUD_LAPLARGE_1,
    ASSET_TEX2D_HUD_LAP2_2,
    ASSET_TEX2D_HUD_WAY,
    ASSET_TEX2D_HUD_WRONG_0,
    ASSET_TEX2D_HUD_WRONG_1,
    ASSET_TEX2D_UNUSED_PROAMLOGO_0,
    ASSET_TEX2D_UNUSED_PROAMLOGO_1,
    ASSET_TEX2D_UNUSED_PROAMLOGO_2,
    ASSET_TEX2D_HUD_SPEEDOMETERTICKS,
    ASSET_TEX2D_HUD_SPEEDOMETER0,
    ASSET_TEX2D_HUD_SPEEDOMETER30,
    ASSET_TEX2D_HUD_SPEEDOMETER60,
    ASSET_TEX2D_HUD_SPEEDOMETER90,
    ASSET_TEX2D_HUD_SPEEDOMETER120,
    ASSET_TEX2D_HUD_SPEEDOMETER150,
    ASSET_TEX2D_HUD_SPEEDOMETERARROW,
    ASSET_TEX2D_HUD_FIRSTPLACEONE_0,
    ASSET_TEX2D_HUD_FIRSTPLACEONE_1,
    ASSET_TEX2D_HUD_FIRSTPLACEST_0,
    ASSET_TEX2D_HUD_FIRSTPLACEST_1,
    ASSET_TEX2D_OBJECTS_BALLOONSTRING_0,
    ASSET_TEX2D_OBJECTS_BALLOONSTRING_1,
    ASSET_TEX2D_OBJECTS_BALLOONSTRING_2,
    ASSET_TEX2D_OBJECTS_BALLOONSTRING_3,
    ASSET_TEX2D_OBJECTS_BALLOONSTRING_4,
    ASSET_TEX2D_OBJECTS_BALLOONSTRING_5,
    ASSET_TEX2D_OBJECTS_BALLOONSTRING_6,
    ASSET_TEX2D_OBJECTS_BALLOONSTRING_7,
    ASSET_TEX2D_OBJECTS_BALLOONSTRING_8,
    ASSET_TEX2D_OBJECTS_BALLOONSTRING_9,
    ASSET_TEX2D_OBJECTS_BALLOONSTRING_10,
    ASSET_TEX2D_OBJECTS_BALLOONSTRING_11,
    ASSET_TEX2D_OBJECTS_BALLOONSTRING_12,
    ASSET_TEX2D_OBJECTS_BALLOONSTRING_13,
    ASSET_TEX2D_OBJECTS_BALLOONSTRING_14,
    ASSET_TEX2D_OBJECTS_BALLOONSTRING_15,
    ASSET_TEX2D_OBJECTS_BALLOONSTRING_16,
    ASSET_TEX2D_OBJECTS_BALLOONSTRING_17,
    ASSET_TEX2D_OBJECTS_BALLOONSTRING_18,
    ASSET_TEX2D_OBJECTS_BALLOONSTRING_19,
    ASSET_TEX2D_MENU_TITLE_0,
    ASSET_TEX2D_MENU_TITLE_1,
    ASSET_TEX2D_MENU_TITLE_2,
    ASSET_TEX2D_MENU_TITLE_3,
    ASSET_TEX2D_MENU_TITLE_4,
    ASSET_TEX2D_MENU_TITLE_5,
    ASSET_TEX2D_MENU_TITLE_6,
    ASSET_TEX2D_MENU_TITLE_7,
    ASSET_TEX2D_MENU_TITLE_8,
    ASSET_TEX2D_MENU_TITLE_9,
    ASSET_TEX2D_MENU_TITLE_JP_0,
    ASSET_TEX2D_MENU_TITLE_JP_1,
    ASSET_TEX2D_MENU_TITLE_JP_2,
    ASSET_TEX2D_MENU_TITLE_JP_3,
    ASSET_TEX2D_MENU_TITLE_JP_4,
    ASSET_TEX2D_MENU_TITLE_JP_5,
    ASSET_TEX2D_MENU_TITLE_JP_6,
    ASSET_TEX2D_MENU_TITLE_JP_7,
    ASSET_TEX2D_MENU_TITLE_JP_8,
    ASSET_TEX2D_MENU_TITLE_JP_9,
    ASSET_TEX2D_MENU_TRADEMARKSMALL,
    ASSET_TEX2D_UNKNOWN_FIREBALLUNKNOWN_0,
    ASSET_TEX2D_UNKNOWN_FIREBALLUNKNOWN_1,
    ASSET_TEX2D_UNKNOWN_FIREBALLUNKNOWN_2,
    ASSET_TEX2D_UNKNOWN_FIREBALLUNKNOWN_3,
    ASSET_TEX2D_OBJECTS_FIREBALL_0,
    ASSET_TEX2D_OBJECTS_FIREBALL_1,
    ASSET_TEX2D_OBJECTS_FIREBALL_2,
    ASSET_TEX2D_OBJECTS_FIREBALL_3,
    ASSET_TEX2D_OBJECTS_FIREBALL_4,
    ASSET_TEX2D_OBJECTS_FIREBALL_5,
    ASSET_TEX2D_OBJECTS_FIREBALL_6,
    ASSET_TEX2D_OBJECTS_FIREBALL_7,
    ASSET_TEX2D_OBJECTS_FIREBALL_8,
    ASSET_TEX2D_OBJECTS_FIREBALL_9,
    ASSET_TEX2D_OBJECTS_WIZGHOST_0,
    ASSET_TEX2D_OBJECTS_WIZGHOST_1,
    ASSET_TEX2D_OBJECTS_WIZGHOST_2,
    ASSET_TEX2D_OBJECTS_WIZGHOST_3,
    ASSET_TEX2D_OBJECTS_WIZGHOST_4,
    ASSET_TEX2D_OBJECTS_WIZGHOST_5,
    ASSET_TEX2D_OBJECTS_WIZGHOST_6,
    ASSET_TEX2D_OBJECTS_WIZGHOST_7,
    ASSET_TEX2D_OBJECTS_WIZGHOST_8,
    ASSET_TEX2D_OBJECTS_WIZGHOST_9,
    ASSET_TEX2D_OBJECTS_WIZGHOST_10,
    ASSET_TEX2D_OBJECTS_WIZGHOST_11,
    ASSET_TEX2D_OBJECTS_WIZGHOST_12,
    ASSET_TEX2D_UNKNOWN_UNKNOWNLIGHT_0,
    ASSET_TEX2D_UNKNOWN_UNKNOWNLIGHT_1,
    ASSET_TEX2D_UNKNOWN_SMALLSTAR,
    ASSET_TEX2D_OBJECTS_BUOY_0,
    ASSET_TEX2D_OBJECTS_BUOY_1,
    ASSET_TEX2D_OBJECTS_BUOY_2,
    ASSET_TEX2D_OBJECTS_BUOY_3,
    ASSET_TEX2D_OBJECTS_SMARTIETREE_0,
    ASSET_TEX2D_OBJECTS_SMARTIETREE_1,
    ASSET_TEX2D_OBJECTS_SMARTIETREE_2,
    ASSET_TEX2D_OBJECTS_SMARTIETREE_3,
    ASSET_TEX2D_OBJECTS_BEACHTREE_0,
    ASSET_TEX2D_OBJECTS_BEACHTREE_1,
    ASSET_TEX2D_OBJECTS_BEACHTREE_2,
    ASSET_TEX2D_OBJECTS_BLUEBERRYBUSH_0,
    ASSET_TEX2D_OBJECTS_BLUEBERRYBUSH_1,
    ASSET_TEX2D_OBJECTS_BLUEBERRYBUSH_2,
    ASSET_TEX2D_OBJECTS_BLUEBERRYBUSH_3,
    ASSET_TEX2D_OBJECTS_BLUEBERRYBUSH_4,
    ASSET_TEX2D_OBJECTS_BLUEBERRYBUSH_5,
    ASSET_TEX2D_OBJECTS_RUBBERSNOWTREE_0,
    ASSET_TEX2D_OBJECTS_RUBBERSNOWTREE_1,
    ASSET_TEX2D_OBJECTS_RUBBERSNOWTREE_2,
    ASSET_TEX2D_OBJECTS_RUBBERSNOWTREE_3,
    ASSET_TEX2D_OBJECTS_SKINNYSNOWTREE_0,
    ASSET_TEX2D_OBJECTS_SKINNYSNOWTREE_1,
    ASSET_TEX2D_OBJECTS_SKINNYSNOWTREE_2,
    ASSET_TEX2D_OBJECTS_SKINNYSNOWTREE_3,
    ASSET_TEX2D_OBJECTS_XMASTREE_0,
    ASSET_TEX2D_OBJECTS_XMASTREE_1,
    ASSET_TEX2D_OBJECTS_XMASTREE_2,
    ASSET_TEX2D_OBJECTS_XMASTREE_3,
    ASSET_TEX2D_OBJECTS_ALPINESNOWTREE_0,
    ASSET_TEX2D_OBJECTS_ALPINESNOWTREE_1,
    ASSET_TEX2D_OBJECTS_ALPINESNOWTREE_2,
    ASSET_TEX2D_OBJECTS_ALPINESNOWTREE_3,
    ASSET_TEX2D_OBJECTS_RUBBERTREE_0,
    ASSET_TEX2D_OBJECTS_RUBBERTREE_1,
    ASSET_TEX2D_OBJECTS_RUBBERTREE_2,
    ASSET_TEX2D_OBJECTS_RUBBERTREE_3,
    ASSET_TEX2D_OBJECTS_PALMTREETOP_0,
    ASSET_TEX2D_OBJECTS_PALMTREETOP_1,
    ASSET_TEX2D_OBJECTS_PALMTREETOP_2,
    ASSET_TEX2D_OBJECTS_PALMTREETOP_3,
    ASSET_TEX2D_OBJECTS_PALMTREETOP_4,
    ASSET_TEX2D_OBJECTS_PALMPLANT_0,
    ASSET_TEX2D_OBJECTS_PALMPLANT_1,
    ASSET_TEX2D_OBJECTS_PALMPLANT_2,
    ASSET_TEX2D_OBJECTS_PALMTREETOPCHEA_0,
    ASSET_TEX2D_OBJECTS_PALMTREETOPCHEA_1,
    ASSET_TEX2D_OBJECTS_FIRTREE_0,
    ASSET_TEX2D_OBJECTS_FIRTREE_1,
    ASSET_TEX2D_OBJECTS_FIRTREE_2,
    ASSET_TEX2D_OBJECTS_FIRTREE_3,
    ASSET_TEX2D_OBJECTS_SPACETREE_0,
    ASSET_TEX2D_OBJECTS_SPACETREE_1,
    ASSET_TEX2D_OBJECTS_LAMPPOST_0,
    ASSET_TEX2D_OBJECTS_LAMPPOST_1,
    ASSET_TEX2D_OBJECTS_LAMPPOST_2,
    ASSET_TEX2D_OBJECTS_LAMPPOST_3,
    ASSET_TEX2D_OBJECTS_FLOWERS_WHITEBUTTERCUP_0,
    ASSET_TEX2D_OBJECTS_FLOWERS_WHITEBUTTERCUP_1,
    ASSET_TEX2D_OBJECTS_FLOWERS_YELLOWBELLFLOWER_0,
    ASSET_TEX2D_OBJECTS_FLOWERS_YELLOWBELLFLOWER_1,
    ASSET_TEX2D_OBJECTS_FLOWERS_YELLOWBUTTERCUP_0,
    ASSET_TEX2D_OBJECTS_FLOWERS_YELLOWBUTTERCUP_1,
    ASSET_TEX2D_OBJECTS_FLOWERS_BLUEBUTTERCUP_0,
    ASSET_TEX2D_OBJECTS_FLOWERS_BLUEBUTTERCUP_1,
    ASSET_TEX2D_OBJECTS_FLOWERS_WATERLILY_0,
    ASSET_TEX2D_OBJECTS_FLOWERS_WATERLILY_1,
    ASSET_TEX2D_OBJECTS_REEDNOLEAF_0,
    ASSET_TEX2D_OBJECTS_REEDNOLEAF_1,
    ASSET_TEX2D_OBJECTS_REEDLEAVES_0,
    ASSET_TEX2D_OBJECTS_REEDLEAVES_1,
    ASSET_TEX2D_OBJECTS_REEDLEAVES_2,
    ASSET_TEX2D_OBJECTS_REEDONELEAF_0,
    ASSET_TEX2D_OBJECTS_REEDONELEAF_1,
    ASSET_TEX2D_OBJECTS_REEDONELEAF_2,
    ASSET_TEX2D_OBJECTS_SNOWMANTOPHAT_0,
    ASSET_TEX2D_OBJECTS_SNOWMANTOPHAT_1,
    ASSET_TEX2D_OBJECTS_SNOWMANTOPHAT_2,
    ASSET_TEX2D_OBJECTS_SNOWMANTOPHAT_3,
    ASSET_TEX2D_OBJECTS_BELL,
    ASSET_TEX2D_OBJECTS_SNOWMAN_0,
    ASSET_TEX2D_OBJECTS_SNOWMAN_1,
    ASSET_TEX2D_OBJECTS_SNOWMAN_2,
    ASSET_TEX2D_OBJECTS_SNOWMAN_3,
    ASSET_TEX2D_UNUSED_TORCHWITHEYES,
    ASSET_TEX2D_OBJECTS_DEBUGORBRED,
    ASSET_TEX2D_OBJECTS_DEBUGORBYELLOW,
    ASSET_TEX2D_UNUSED_BETAANCIENTLAKESIGN_0,
    ASSET_TEX2D_UNUSED_BETAANCIENTLAKESIGN_1,
    ASSET_TEX2D_UNUSED_BETAANCIENTLAKESIGN_2,
    ASSET_TEX2D_UNUSED_BETAANCIENTLAKESIGN_3,
    ASSET_TEX2D_UNUSED_BETAANCIENTLAKESIGN_4,
    ASSET_TEX2D_OBJECTS_DEBUGFOGCHANGER,
    ASSET_TEX2D_OBJECTS_DEBUGANIMCAR,
    ASSET_TEX2D_OBJECTS_DEBUGSKYCONTROL,
    ASSET_TEX2D_OBJECTS_DEBUGCAMERACONTROL,
    ASSET_TEX2D_UNUSED_DEBUGUNKNOWNEXIT,
    ASSET_TEX2D_UNUSED_DEBUGUNKNOWNTRAFFICLIGHT,
    ASSET_TEX2D_OBJECTS_DEBUGANIMATOR,
    ASSET_TEX2D_OBJECTS_DEBUGAUDIO,
    ASSET_TEX2D_OBJECTS_DEBUGAUDIOLINE,
    ASSET_TEX2D_OBJECTS_DEBUGAUDIOSEQLINE,
    ASSET_TEX2D_OBJECTS_DEBUGAUDIOSEQ,
    ASSET_TEX2D_OBJECTS_DEBUGAUDIOREVERB_0,
    ASSET_TEX2D_OBJECTS_DEBUGAUDIOREVERB_1,
    ASSET_TEX2D_OBJECTS_BALLOONBOOST_0,
    ASSET_TEX2D_OBJECTS_BALLOONBOOST_1,
    ASSET_TEX2D_OBJECTS_BALLOONBOOST_2,
    ASSET_TEX2D_OBJECTS_BALLOONMISSILE_0,
    ASSET_TEX2D_OBJECTS_BALLOONMISSILE_1,
    ASSET_TEX2D_OBJECTS_BALLOONMISSILE_2,
    ASSET_TEX2D_OBJECTS_BALLOONTRAP_0,
    ASSET_TEX2D_OBJECTS_BALLOONTRAP_1,
    ASSET_TEX2D_OBJECTS_BALLOONTRAP_2,
    ASSET_TEX2D_OBJECTS_BALLOONSHIELD_0,
    ASSET_TEX2D_OBJECTS_BALLOONSHIELD_1,
    ASSET_TEX2D_OBJECTS_BALLOONSHIELD_2,
    ASSET_TEX2D_OBJECTS_BALLOONMAGNET_0,
    ASSET_TEX2D_OBJECTS_BALLOONMAGNET_1,
    ASSET_TEX2D_OBJECTS_BALLOONMAGNET_2,
    ASSET_TEX2D_UNUSED_BALLOONMISSILEGIFT_0,
    ASSET_TEX2D_UNUSED_BALLOONMISSILEGIFT_1,
    ASSET_TEX2D_UNUSED_BALLOONMISSILEGIFT_2,
    ASSET_TEX2D_UNUSED_BALLOONBOOSTGIFT_0,
    ASSET_TEX2D_UNUSED_BALLOONBOOSTGIFT_1,
    ASSET_TEX2D_UNUSED_BALLOONBOOSTGIFT_2,
    ASSET_TEX2D_OBJECTS_BALLOONGOLD_0,
    ASSET_TEX2D_OBJECTS_BALLOONGOLD_1,
    ASSET_TEX2D_OBJECTS_BALLOONGOLD_2,
    ASSET_TEX2D_OBJECTS_BALLOONSILVER_0,
    ASSET_TEX2D_OBJECTS_BALLOONSILVER_1,
    ASSET_TEX2D_OBJECTS_BALLOONSILVER_2,
    ASSET_TEX2D_OBJECTS_BANANA_0,
    ASSET_TEX2D_OBJECTS_BANANA_1,
    ASSET_TEX2D_OBJECTS_BANANA_2,
    ASSET_TEX2D_OBJECTS_BANANA_3,
    ASSET_TEX2D_OBJECTS_BANANA_4,
    ASSET_TEX2D_OBJECTS_BANANA_5,
    ASSET_TEX2D_OBJECTS_BANANA_6,
    ASSET_TEX2D_OBJECTS_BANANA_7,
    ASSET_TEX2D_OBJECTS_SILVERCOIN_0,
    ASSET_TEX2D_OBJECTS_SILVERCOIN_1,
    ASSET_TEX2D_OBJECTS_SILVERCOIN_2,
    ASSET_TEX2D_OBJECTS_SILVERCOIN_3,
    ASSET_TEX2D_OBJECTS_SILVERCOIN_4,
    ASSET_TEX2D_OBJECTS_SILVERCOIN_5,
    ASSET_TEX2D_OBJECTS_SILVERCOIN_6,
    ASSET_TEX2D_OBJECTS_SILVERCOIN_7,
    ASSET_TEX2D_OBJECTS_SILVERCOIN_8,
    ASSET_TEX2D_OBJECTS_SILVERCOIN_9,
    ASSET_TEX2D_OBJECTS_SILVERCOIN_10,
    ASSET_TEX2D_OBJECTS_CHECKPOINTFLAG_0,
    ASSET_TEX2D_OBJECTS_CHECKPOINTFLAG_1,
    ASSET_TEX2D_OBJECTS_CHECKPOINTFLAG_2,
    ASSET_TEX2D_OBJECTS_CHECKPOINTFLAG_3,
    ASSET_TEX2D_OBJECTS_CHECKPOINTFLAG_4,
    ASSET_TEX2D_OBJECTS_CHECKPOINTFLAG_5,
    ASSET_TEX2D_OBJECTS_CHECKPOINTFLAG_6,
    ASSET_TEX2D_OBJECTS_CHECKPOINTFLAG_7,
    ASSET_TEX2D_OBJECTS_CHECKPOINTFLAG_8,
    ASSET_TEX2D_UNUSED_RAREWARECOIN_0,
    ASSET_TEX2D_UNUSED_RAREWARECOIN_1,
    ASSET_TEX2D_UNUSED_RAREWARECOIN_2,
    ASSET_TEX2D_UNUSED_RAREWARECOIN_3,
    ASSET_TEX2D_UNUSED_RAREWARECOIN_4,
    ASSET_TEX2D_UNUSED_RAREWARECOIN_5,
    ASSET_TEX2D_UNUSED_RAREWARECOIN_6,
    ASSET_TEX2D_UNUSED_RAREWARECOIN_7,
    ASSET_TEX2D_UNUSED_RAREWARECOIN_8,
    ASSET_TEX2D_UNUSED_RAREWARECOIN_9,
    ASSET_TEX2D_UNUSED_RAREWARECOIN_10,
    ASSET_TEX2D_UNUSED_SILVERCOINVERTICAL,
    ASSET_TEX2D_HUD_BANANAICON_0,
    ASSET_TEX2D_HUD_BANANAICON_1,
    ASSET_TEX2D_PARTICLES_SPARKLE_0,
    ASSET_TEX2D_PARTICLES_SPARKLE_1,
    ASSET_TEX2D_PARTICLES_SPARKLE_2,
    ASSET_TEX2D_PARTICLES_SPARKLE_3,
    ASSET_TEX2D_PARTICLES_SPARKLE_4,
    ASSET_TEX2D_OBJECTS_DEBUGEGGCREATOR_0,
    ASSET_TEX2D_OBJECTS_DEBUGEGGCREATOR_1,
    ASSET_TEX2D_OBJECTS_DEBUGEGGCREATOR_2,
    ASSET_TEX2D_OBJECTS_DEBUGEGGCREATOR_3,
    ASSET_TEX2D_OBJECTS_DEBUGEGGCREATOR_4,
    ASSET_TEX2D_OBJECTS_DEBUGEGGCREATOR_5,
    ASSET_TEX2D_UNUSED_BONUSGEM_0,
    ASSET_TEX2D_UNUSED_BONUSGEM_1,
    ASSET_TEX2D_UNUSED_BONUSGEM_2,
    ASSET_TEX2D_UNUSED_BONUSGEM_3,
    ASSET_TEX2D_UNUSED_BONUSGEM_4,
    ASSET_TEX2D_UNUSED_BONUSGEM_5,
    ASSET_TEX2D_UNUSED_BONUSGEM_6,
    ASSET_TEX2D_UNUSED_BONUSGEM_7,
    ASSET_TEX2D_HUD_INDICATORICONCAUTION,
    ASSET_TEX2D_HUD_INDICATORICONDOWN,
    ASSET_TEX2D_HUD_INDICATORICONUTURN,
    ASSET_TEX2D_HUD_INDICATORICONTURN,
    ASSET_TEX2D_HUD_INDICATORICONSLIGHTTURN,
    ASSET_TEX2D_OBJECTS_SMOKEOBJECT_0,
    ASSET_TEX2D_OBJECTS_SMOKEOBJECT_1,
    ASSET_TEX2D_OBJECTS_SMOKEOBJECT_2,
    ASSET_TEX2D_OBJECTS_SMOKEOBJECT_3,
    ASSET_TEX2D_OBJECTS_SMOKEOBJECT_4,
    ASSET_TEX2D_OBJECTS_SMOKEOBJECT_5,
    ASSET_TEX2D_OBJECTS_SMOKEOBJECT_6,
    ASSET_TEX2D_OBJECTS_SMOKEOBJECT_7,
    ASSET_TEX2D_OBJECTS_SMOKEOBJECT_8,
    ASSET_TEX2D_OBJECTS_SMOKEOBJECT_9,
    ASSET_TEX2D_OBJECTS_SMOKEOBJECT_10,
    ASSET_TEX2D_OBJECTS_SMOKEOBJECT_11,
    ASSET_TEX2D_OBJECTS_SMOKEOBJECT_12,
    ASSET_TEX2D_OBJECTS_SMOKEOBJECT_13,
    ASSET_TEX2D_OBJECTS_SMOKEOBJECT_14,
    ASSET_TEX2D_OBJECTS_SMOKEOBJECT_15,
    ASSET_TEX2D_OBJECTS_SMOKECLOUD_0,
    ASSET_TEX2D_OBJECTS_SMOKECLOUD_1,
    ASSET_TEX2D_OBJECTS_SMOKECLOUD_2,
    ASSET_TEX2D_OBJECTS_SMOKECLOUD_3,
    ASSET_TEX2D_OBJECTS_SMOKECLOUD_4,
    ASSET_TEX2D_OBJECTS_SMOKECLOUD_5,
    ASSET_TEX2D_OBJECTS_SMOKECLOUD_6,
    ASSET_TEX2D_OBJECTS_SMOKECLOUD_7,
    ASSET_TEX2D_OBJECTS_SMOKECLOUD_8,
    ASSET_TEX2D_OBJECTS_SMOKEGRASS_0,
    ASSET_TEX2D_OBJECTS_SMOKEGRASS_1,
    ASSET_TEX2D_OBJECTS_SMOKEGRASS_2,
    ASSET_TEX2D_OBJECTS_SMOKEGRASS_3,
    ASSET_TEX2D_OBJECTS_SMOKEGRASS_4,
    ASSET_TEX2D_OBJECTS_SMOKEGRASS_5,
    ASSET_TEX2D_OBJECTS_SMOKEGRASS_6,
    ASSET_TEX2D_OBJECTS_SMOKEGRASS_7,
    ASSET_TEX2D_OBJECTS_SMOKEGRASS_8,
    ASSET_TEX2D_OBJECTS_SMOKEGRASS_9,
    ASSET_TEX2D_OBJECTS_SMOKEGRASS_10,
    ASSET_TEX2D_OBJECTS_SMOKEGRASS_11,
    ASSET_TEX2D_OBJECTS_SMOKEGRASS_12,
    ASSET_TEX2D_OBJECTS_SMOKEGRASS_13,
    ASSET_TEX2D_OBJECTS_MIST_0,
    ASSET_TEX2D_OBJECTS_MIST_1,
    ASSET_TEX2D_OBJECTS_MIST_2,
    ASSET_TEX2D_OBJECTS_MIST_3,
    ASSET_TEX2D_OBJECTS_MIST_4,
    ASSET_TEX2D_OBJECTS_MIST_5,
    ASSET_TEX2D_OBJECTS_MIST_6,
    ASSET_TEX2D_OBJECTS_MIST_7,
    ASSET_TEX2D_OBJECTS_MIST_8,
    ASSET_TEX2D_OBJECTS_MIST_9,
    ASSET_TEX2D_OBJECTS_MIST_10,
    ASSET_TEX2D_OBJECTS_FLAMINGTORCH_0,
    ASSET_TEX2D_OBJECTS_FLAMINGTORCH_1,
    ASSET_TEX2D_OBJECTS_FLAMINGTORCH_2,
    ASSET_TEX2D_OBJECTS_FLAMINGTORCH_3,
    ASSET_TEX2D_OBJECTS_FLAMINGTORCH_4,
    ASSET_TEX2D_OBJECTS_FLAMINGTORCH_5,
    ASSET_TEX2D_OBJECTS_FLAMINGTORCH_6,
    ASSET_TEX2D_OBJECTS_FLAMINGTORCH_7,
    ASSET_TEX2D_OBJECTS_FLAMINGTORCH_8,
    ASSET_TEX2D_OBJECTS_FLAMINGTORCH_9,
    ASSET_TEX2D_OBJECTS_FLAMINGTORCH_10,
    ASSET_TEX2D_OBJECTS_FLAMINGTORCH_11,
    ASSET_TEX2D_UNUSED_SPLASH_0,
    ASSET_TEX2D_UNUSED_SPLASH_1,
    ASSET_TEX2D_UNUSED_SPLASH_2,
    ASSET_TEX2D_UNUSED_SPLASH_3,
    ASSET_TEX2D_UNUSED_SPLASH_4,
    ASSET_TEX2D_UNUSED_SPLASH_5,
    ASSET_TEX2D_UNUSED_SPLASH_6,
    ASSET_TEX2D_UNUSED_SPLASH_7,
    ASSET_TEX2D_UNUSED_SPLASH_8,
    ASSET_TEX2D_UNUSED_SPLASH_9,
    ASSET_TEX2D_UNUSED_SPLASH_10,
    ASSET_TEX2D_UNUSED_SPLASH_11,
    ASSET_TEX2D_UNUSED_SPLASH_12,
    ASSET_TEX2D_UNUSED_SPLASH_13,
    ASSET_TEX2D_UNUSED_SPLASH_14,
    ASSET_TEX2D_UNUSED_SPLASH_15,
    ASSET_TEX2D_UNUSED_SPLASH_16,
    ASSET_TEX2D_UNUSED_SPLASH_17,
    ASSET_TEX2D_UNUSED_SPLASH_18,
    ASSET_TEX2D_UNUSED_SPLASH_19,
    ASSET_TEX2D_UNUSED_SPLASH_20,
    ASSET_TEX2D_UNUSED_SPLASH_21,
    ASSET_TEX2D_UNUSED_SPLASH_22,
    ASSET_TEX2D_UNUSED_SPLASH_23,
    ASSET_TEX2D_UNUSED_WEAPONBALLOONPOP_0,
    ASSET_TEX2D_UNUSED_WEAPONBALLOONPOP_1,
    ASSET_TEX2D_UNUSED_WEAPONBALLOONPOP_2,
    ASSET_TEX2D_UNUSED_WEAPONBALLOONPOP_3,
    ASSET_TEX2D_UNUSED_WEAPONBALLOONPOP_4,
    ASSET_TEX2D_UNUSED_WEAPONBALLOONPOP_5,
    ASSET_TEX2D_UNUSED_WEAPONBALLOONPOP_6,
    ASSET_TEX2D_UNUSED_WEAPONBALLOONPOP_7,
    ASSET_TEX2D_UNUSED_WEAPONBALLOONPOP_8,
    ASSET_TEX2D_UNUSED_WEAPONBALLOONPOP_9,
    ASSET_TEX2D_UNUSED_WEAPONBALLOONPOP_10,
    ASSET_TEX2D_UNUSED_WEAPONBALLOONPOP_11,
    ASSET_TEX2D_UNUSED_WEAPONBALLOONPOP_12,
    ASSET_TEX2D_OBJECTS_LAVASPURT_0,
    ASSET_TEX2D_OBJECTS_LAVASPURT_1,
    ASSET_TEX2D_OBJECTS_LAVASPURT_2,
    ASSET_TEX2D_OBJECTS_LAVASPURT_3,
    ASSET_TEX2D_OBJECTS_LAVASPURT_4,
    ASSET_TEX2D_OBJECTS_LAVASPURT_5,
    ASSET_TEX2D_OBJECTS_LAVASPURT_6,
    ASSET_TEX2D_OBJECTS_LAVASPURT_7,
    ASSET_TEX2D_OBJECTS_LAVASPURT_8,
    ASSET_TEX2D_OBJECTS_LAVASPURT_9,
    ASSET_TEX2D_OBJECTS_LAVASPURT_10,
    ASSET_TEX2D_OBJECTS_LAVASPURT_11,
    ASSET_TEX2D_OBJECTS_LAVASPURT_12,
    ASSET_TEX2D_UNKNOWN_UNKNOWNSMALLPOP_0,
    ASSET_TEX2D_UNKNOWN_UNKNOWNSMALLPOP_1,
    ASSET_TEX2D_UNKNOWN_UNKNOWNSMALLPOP_2,
    ASSET_TEX2D_UNKNOWN_UNKNOWNSMALLPOP_3,
    ASSET_TEX2D_UNKNOWN_UNKNOWNSMALLPOP_4,
    ASSET_TEX2D_UNKNOWN_UNKNOWNSMALLPOP_5,
    ASSET_TEX2D_UNKNOWN_UNKNOWNSMALLPOP_6,
    ASSET_TEX2D_UNKNOWN_UNKNOWNSMALLPOP_7,
    ASSET_TEX2D_UNKNOWN_UNKNOWNSMALLPOP_8,
    ASSET_TEX2D_UNKNOWN_UNKNOWNSMALLPOP_9,
    ASSET_TEX2D_UNKNOWN_UNKNOWNSMALLPOP_10,
    ASSET_TEX2D_UNKNOWN_UNKNOWNSMALLPOP_11,
    ASSET_TEX2D_UNKNOWN_UNKNOWNSMALLPOP_12,
    ASSET_TEX2D_UNKNOWN_UNKNOWNSMALLPOP_13,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE0_0,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE0_1,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE0_2,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE0_3,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE0_4,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE0_5,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE0_6,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE0_7,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE0_8,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE0_9,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE0_10,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE0_11,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE0_12,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE0_13,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE0_14,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE0_15,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE1_0,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE1_1,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE1_2,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE1_3,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE1_4,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE1_5,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE1_6,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE1_7,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE1_8,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE1_9,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE1_10,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE1_11,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE1_12,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE1_13,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE1_14,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE1_15,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE2_0,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE2_1,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE2_2,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE2_3,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE2_4,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE2_5,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE2_6,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE2_7,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE2_8,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE2_9,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE2_10,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE2_11,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE2_12,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE2_13,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE2_14,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE2_15,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE3_0,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE3_1,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE3_2,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE3_3,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE3_4,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE3_5,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE3_6,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE3_7,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE3_8,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE3_9,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE3_10,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE3_11,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE3_12,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE3_13,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE3_14,
    ASSET_TEX2D_VEHICLE_PARTS_TYRE3_15,
    ASSET_TEX2D_VEHICLE_PARTS_FAN0_0,
    ASSET_TEX2D_VEHICLE_PARTS_FAN0_1,
    ASSET_TEX2D_VEHICLE_PARTS_FAN0_2,
    ASSET_TEX2D_VEHICLE_PARTS_FAN0_3,
    ASSET_TEX2D_VEHICLE_PARTS_FAN0_4,
    ASSET_TEX2D_VEHICLE_PARTS_FAN0_5,
    ASSET_TEX2D_VEHICLE_PARTS_FAN0_6,
    ASSET_TEX2D_VEHICLE_PARTS_FAN0_7,
    ASSET_TEX2D_VEHICLE_PARTS_FAN0_8,
    ASSET_TEX2D_VEHICLE_PARTS_FAN0_9,
    ASSET_TEX2D_VEHICLE_PARTS_FAN0_10,
    ASSET_TEX2D_VEHICLE_PARTS_FAN0_11,
    ASSET_TEX2D_VEHICLE_PARTS_FAN0_12,
    ASSET_TEX2D_VEHICLE_PARTS_FAN0_13,
    ASSET_TEX2D_VEHICLE_PARTS_FAN0_14,
    ASSET_TEX2D_VEHICLE_PARTS_FAN0_15,
    ASSET_TEX2D_VEHICLE_PARTS_FAN1_0,
    ASSET_TEX2D_VEHICLE_PARTS_FAN1_1,
    ASSET_TEX2D_VEHICLE_PARTS_FAN1_2,
    ASSET_TEX2D_VEHICLE_PARTS_FAN1_3,
    ASSET_TEX2D_VEHICLE_PARTS_FAN1_4,
    ASSET_TEX2D_VEHICLE_PARTS_FAN1_5,
    ASSET_TEX2D_VEHICLE_PARTS_FAN1_6,
    ASSET_TEX2D_VEHICLE_PARTS_FAN1_7,
    ASSET_TEX2D_VEHICLE_PARTS_FAN1_8,
    ASSET_TEX2D_VEHICLE_PARTS_FAN1_9,
    ASSET_TEX2D_VEHICLE_PARTS_FAN1_10,
    ASSET_TEX2D_VEHICLE_PARTS_FAN1_11,
    ASSET_TEX2D_VEHICLE_PARTS_FAN1_12,
    ASSET_TEX2D_VEHICLE_PARTS_FAN1_13,
    ASSET_TEX2D_VEHICLE_PARTS_FAN1_14,
    ASSET_TEX2D_VEHICLE_PARTS_FAN1_15,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER0_0,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER0_1,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER0_2,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER0_3,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER0_4,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER0_5,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER0_6,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER0_7,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER0_8,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER0_9,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER0_10,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER0_11,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER0_12,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER0_13,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER0_14,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER0_15,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER1_0,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER1_1,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER1_2,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER1_3,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER1_4,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER1_5,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER1_6,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER1_7,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER1_8,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER1_9,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER1_10,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER1_11,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER1_12,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER1_13,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER1_14,
    ASSET_TEX2D_VEHICLE_PARTS_PROPELLER1_15,
    ASSET_TEX2D_UNUSED_RARELETTERS_0,
    ASSET_TEX2D_UNUSED_RARELETTERS_1,
    ASSET_TEX2D_UNUSED_RARELETTERS_2,
    ASSET_TEX2D_OBJECTS_BOLTGLOW_0,
    ASSET_TEX2D_OBJECTS_BOLTGLOW_1,
    ASSET_TEX2D_MENU_ICONTROPHYNOTCOLLECTED,
    ASSET_TEX2D_MENU_ICONTROPHYCOLLECTED,
    ASSET_TEX2D_MENU_ICONKEYNOTCOLLECTED,
    ASSET_TEX2D_MENU_ICONKEYCOLLECTED,
    ASSET_TEX2D_MENU_ICONWIZPIGAMULET0_0,
    ASSET_TEX2D_MENU_ICONWIZPIGAMULET0_1,
    ASSET_TEX2D_MENU_ICONWIZPIGAMULET1_0,
    ASSET_TEX2D_MENU_ICONWIZPIGAMULET1_1,
    ASSET_TEX2D_MENU_ICONWIZPIGAMULET2_0,
    ASSET_TEX2D_MENU_ICONWIZPIGAMULET2_1,
    ASSET_TEX2D_MENU_ICONWIZPIGAMULET3_0,
    ASSET_TEX2D_MENU_ICONWIZPIGAMULET3_1,
    ASSET_TEX2D_MENU_ICONWIZPIGAMULET4_0,
    ASSET_TEX2D_MENU_ICONWIZPIGAMULET4_1,
    ASSET_TEX2D_MENU_ICONTTAMULET0_0,
    ASSET_TEX2D_MENU_ICONTTAMULET0_1,
    ASSET_TEX2D_MENU_ICONTTAMULET1_0,
    ASSET_TEX2D_MENU_ICONTTAMULET1_1,
    ASSET_TEX2D_MENU_ICONTTAMULET2_0,
    ASSET_TEX2D_MENU_ICONTTAMULET2_1,
    ASSET_TEX2D_MENU_ICONTTAMULET3_0,
    ASSET_TEX2D_MENU_ICONTTAMULET3_1,
    ASSET_TEX2D_MENU_ICONTTAMULET4_0,
    ASSET_TEX2D_MENU_ICONTTAMULET4_1,
    ASSET_TEXTURES_2D_COUNT
} AssetTextures2dEnum;
typedef enum AssetGameTextEnum {
    ASSET_GAME_TEXT_0,
    ASSET_GAME_TEXT_1,
    ASSET_GAME_TEXT_2,
    ASSET_GAME_TEXT_3,
    ASSET_GAME_TEXT_4,
    ASSET_GAME_TEXT_5,
    ASSET_GAME_TEXT_6,
    ASSET_GAME_TEXT_7,
    ASSET_GAME_TEXT_8,
    ASSET_GAME_TEXT_9,
    ASSET_GAME_TEXT_10,
    ASSET_GAME_TEXT_11,
    ASSET_GAME_TEXT_12,
    ASSET_GAME_TEXT_13,
    ASSET_GAME_TEXT_14,
    ASSET_GAME_TEXT_15,
    ASSET_GAME_TEXT_16,
    ASSET_GAME_TEXT_17,
    ASSET_GAME_TEXT_18,
    ASSET_GAME_TEXT_19,
    ASSET_GAME_TEXT_20,
    ASSET_GAME_TEXT_21,
    ASSET_GAME_TEXT_22,
    ASSET_GAME_TEXT_23,
    ASSET_GAME_TEXT_24,
    ASSET_GAME_TEXT_25,
    ASSET_GAME_TEXT_26,
    ASSET_GAME_TEXT_27,
    ASSET_GAME_TEXT_28,
    ASSET_GAME_TEXT_29,
    ASSET_GAME_TEXT_30,
    ASSET_GAME_TEXT_31,
    ASSET_GAME_TEXT_32,
    ASSET_GAME_TEXT_33,
    ASSET_GAME_TEXT_34,
    ASSET_GAME_TEXT_35,
    ASSET_GAME_TEXT_36,
    ASSET_GAME_TEXT_37,
    ASSET_GAME_TEXT_38,
    ASSET_GAME_TEXT_39,
    ASSET_GAME_TEXT_40,
    ASSET_GAME_TEXT_41,
    ASSET_GAME_TEXT_42,
    ASSET_GAME_TEXT_43,
    ASSET_GAME_TEXT_44,
    ASSET_GAME_TEXT_45,
    ASSET_GAME_TEXT_46,
    ASSET_GAME_TEXT_47,
    ASSET_GAME_TEXT_48,
    ASSET_GAME_TEXT_49,
    ASSET_GAME_TEXT_50,
    ASSET_GAME_TEXT_51,
    ASSET_GAME_TEXT_52,
    ASSET_GAME_TEXT_53,
    ASSET_GAME_TEXT_54,
    ASSET_GAME_TEXT_55,
    ASSET_GAME_TEXT_56,
    ASSET_GAME_TEXT_57,
    ASSET_GAME_TEXT_58,
    ASSET_GAME_TEXT_59,
    ASSET_GAME_TEXT_60,
    ASSET_GAME_TEXT_61,
    ASSET_GAME_TEXT_62,
    ASSET_GAME_TEXT_63,
    ASSET_GAME_TEXT_64,
    ASSET_GAME_TEXT_65,
    ASSET_GAME_TEXT_66,
    ASSET_GAME_TEXT_67,
    ASSET_GAME_TEXT_68,
    ASSET_GAME_TEXT_69,
    ASSET_GAME_TEXT_70,
    ASSET_GAME_TEXT_71,
    ASSET_GAME_TEXT_72,
    ASSET_GAME_TEXT_73,
    ASSET_GAME_TEXT_74,
    ASSET_GAME_TEXT_75,
    ASSET_GAME_TEXT_76,
    ASSET_GAME_TEXT_77,
    ASSET_GAME_TEXT_78,
    ASSET_GAME_TEXT_79,
    ASSET_GAME_TEXT_80,
    ASSET_GAME_TEXT_81,
    ASSET_GAME_TEXT_82,
    ASSET_GAME_TEXT_83,
    ASSET_GAME_TEXT_84,
    ASSET_GAME_TEXT_85,
    ASSET_GAME_TEXT_86,
    ASSET_GAME_TEXT_87,
    ASSET_GAME_TEXT_88,
    ASSET_GAME_TEXT_89,
    ASSET_GAME_TEXT_90,
    ASSET_GAME_TEXT_91,
    ASSET_GAME_TEXT_92,
    ASSET_GAME_TEXT_93,
    ASSET_GAME_TEXT_94,
    ASSET_GAME_TEXT_95,
    ASSET_GAME_TEXT_96,
    ASSET_GAME_TEXT_97,
    ASSET_GAME_TEXT_98,
    ASSET_GAME_TEXT_99,
    ASSET_GAME_TEXT_100,
    ASSET_GAME_TEXT_101,
    ASSET_GAME_TEXT_102,
    ASSET_GAME_TEXT_103,
    ASSET_GAME_TEXT_104,
    ASSET_GAME_TEXT_105,
    ASSET_GAME_TEXT_106,
    ASSET_GAME_TEXT_107,
    ASSET_GAME_TEXT_108,
    ASSET_GAME_TEXT_109,
    ASSET_GAME_TEXT_110,
    ASSET_GAME_TEXT_111,
    ASSET_GAME_TEXT_112,
    ASSET_GAME_TEXT_113,
    ASSET_GAME_TEXT_114,
    ASSET_GAME_TEXT_115,
    ASSET_GAME_TEXT_116,
    ASSET_GAME_TEXT_117,
    ASSET_GAME_TEXT_118,
    ASSET_GAME_TEXT_119,
    ASSET_GAME_TEXT_120,
    ASSET_GAME_TEXT_121,
    ASSET_GAME_TEXT_122,
    ASSET_GAME_TEXT_123,
    ASSET_GAME_TEXT_124,
    ASSET_GAME_TEXT_125,
    ASSET_GAME_TEXT_126,
    ASSET_GAME_TEXT_127,
    ASSET_GAME_TEXT_128,
    ASSET_GAME_TEXT_129,
    ASSET_GAME_TEXT_130,
    ASSET_GAME_TEXT_131,
    ASSET_GAME_TEXT_132,
    ASSET_GAME_TEXT_133,
    ASSET_GAME_TEXT_134,
    ASSET_GAME_TEXT_135,
    ASSET_GAME_TEXT_136,
    ASSET_GAME_TEXT_137,
    ASSET_GAME_TEXT_138,
    ASSET_GAME_TEXT_139,
    ASSET_GAME_TEXT_140,
    ASSET_GAME_TEXT_141,
    ASSET_GAME_TEXT_142,
    ASSET_GAME_TEXT_143,
    ASSET_GAME_TEXT_144,
    ASSET_GAME_TEXT_145,
    ASSET_GAME_TEXT_146,
    ASSET_GAME_TEXT_147,
    ASSET_GAME_TEXT_148,
    ASSET_GAME_TEXT_149,
    ASSET_GAME_TEXT_150,
    ASSET_GAME_TEXT_151,
    ASSET_GAME_TEXT_152,
    ASSET_GAME_TEXT_153,
    ASSET_GAME_TEXT_154,
    ASSET_GAME_TEXT_155,
    ASSET_GAME_TEXT_156,
    ASSET_GAME_TEXT_157,
    ASSET_GAME_TEXT_158,
    ASSET_GAME_TEXT_159,
    ASSET_GAME_TEXT_160,
    ASSET_GAME_TEXT_161,
    ASSET_GAME_TEXT_162,
    ASSET_GAME_TEXT_163,
    ASSET_GAME_TEXT_164,
    ASSET_GAME_TEXT_165,
    ASSET_GAME_TEXT_166,
    ASSET_GAME_TEXT_167,
    ASSET_GAME_TEXT_168,
    ASSET_GAME_TEXT_169,
    ASSET_GAME_TEXT_170,
    ASSET_GAME_TEXT_171,
    ASSET_GAME_TEXT_172,
    ASSET_GAME_TEXT_173,
    ASSET_GAME_TEXT_174,
    ASSET_GAME_TEXT_175,
    ASSET_GAME_TEXT_176,
    ASSET_GAME_TEXT_177,
    ASSET_GAME_TEXT_178,
    ASSET_GAME_TEXT_179,
    ASSET_GAME_TEXT_180,
    ASSET_GAME_TEXT_181,
    ASSET_GAME_TEXT_182,
    ASSET_GAME_TEXT_183,
    ASSET_GAME_TEXT_184,
    ASSET_GAME_TEXT_185,
    ASSET_GAME_TEXT_186,
    ASSET_GAME_TEXT_187,
    ASSET_GAME_TEXT_188,
    ASSET_GAME_TEXT_189,
    ASSET_GAME_TEXT_190,
    ASSET_GAME_TEXT_191,
    ASSET_GAME_TEXT_192,
    ASSET_GAME_TEXT_193,
    ASSET_GAME_TEXT_194,
    ASSET_GAME_TEXT_195,
    ASSET_GAME_TEXT_196,
    ASSET_GAME_TEXT_197,
    ASSET_GAME_TEXT_198,
    ASSET_GAME_TEXT_199,
    ASSET_GAME_TEXT_200,
    ASSET_GAME_TEXT_201,
    ASSET_GAME_TEXT_202,
    ASSET_GAME_TEXT_203,
    ASSET_GAME_TEXT_204,
    ASSET_GAME_TEXT_205,
    ASSET_GAME_TEXT_206,
    ASSET_GAME_TEXT_207,
    ASSET_GAME_TEXT_208,
    ASSET_GAME_TEXT_209,
    ASSET_GAME_TEXT_210,
    ASSET_GAME_TEXT_211,
    ASSET_GAME_TEXT_212,
    ASSET_GAME_TEXT_213,
    ASSET_GAME_TEXT_214,
    ASSET_GAME_TEXT_215,
    ASSET_GAME_TEXT_216,
    ASSET_GAME_TEXT_217,
    ASSET_GAME_TEXT_218,
    ASSET_GAME_TEXT_219,
    ASSET_GAME_TEXT_220,
    ASSET_GAME_TEXT_221,
    ASSET_GAME_TEXT_222,
    ASSET_GAME_TEXT_223,
    ASSET_GAME_TEXT_224,
    ASSET_GAME_TEXT_225,
    ASSET_GAME_TEXT_226,
    ASSET_GAME_TEXT_227,
    ASSET_GAME_TEXT_228,
    ASSET_GAME_TEXT_229,
    ASSET_GAME_TEXT_230,
    ASSET_GAME_TEXT_231,
    ASSET_GAME_TEXT_232,
    ASSET_GAME_TEXT_233,
    ASSET_GAME_TEXT_234,
    ASSET_GAME_TEXT_235,
    ASSET_GAME_TEXT_236,
    ASSET_GAME_TEXT_237,
    ASSET_GAME_TEXT_238,
    ASSET_GAME_TEXT_239,
    ASSET_GAME_TEXT_240,
    ASSET_GAME_TEXT_241,
    ASSET_GAME_TEXT_242,
    ASSET_GAME_TEXT_243,
    ASSET_GAME_TEXT_244,
    ASSET_GAME_TEXT_245,
    ASSET_GAME_TEXT_246,
    ASSET_GAME_TEXT_247,
    ASSET_GAME_TEXT_248,
    ASSET_GAME_TEXT_249,
    ASSET_GAME_TEXT_250,
    ASSET_GAME_TEXT_251,
    ASSET_GAME_TEXT_252,
    ASSET_GAME_TEXT_253,
    ASSET_GAME_TEXT_254,
    ASSET_GAME_TEXT_255,
    ASSET_GAME_TEXT_256,
    ASSET_GAME_TEXT_257,
    ASSET_GAME_TEXT_258,
    ASSET_GAME_TEXT_259,
    ASSET_GAME_TEXT_260,
    ASSET_GAME_TEXT_261,
    ASSET_GAME_TEXT_262,
    ASSET_GAME_TEXT_263,
    ASSET_GAME_TEXT_264,
    ASSET_GAME_TEXT_265,
    ASSET_GAME_TEXT_266,
    ASSET_GAME_TEXT_267,
    ASSET_GAME_TEXT_268,
    ASSET_GAME_TEXT_269,
    ASSET_GAME_TEXT_270,
    ASSET_GAME_TEXT_271,
    ASSET_GAME_TEXT_272,
    ASSET_GAME_TEXT_273,
    ASSET_GAME_TEXT_274,
    ASSET_GAME_TEXT_275,
    ASSET_GAME_TEXT_276,
    ASSET_GAME_TEXT_277,
    ASSET_GAME_TEXT_278,
    ASSET_GAME_TEXT_279,
    ASSET_GAME_TEXT_280,
    ASSET_GAME_TEXT_281,
    ASSET_GAME_TEXT_282,
    ASSET_GAME_TEXT_283,
    ASSET_GAME_TEXT_284,
    ASSET_GAME_TEXT_285,
    ASSET_GAME_TEXT_286,
    ASSET_GAME_TEXT_287,
    ASSET_GAME_TEXT_288,
    ASSET_GAME_TEXT_289,
    ASSET_GAME_TEXT_290,
    ASSET_GAME_TEXT_291,
    ASSET_GAME_TEXT_292,
    ASSET_GAME_TEXT_293,
    ASSET_GAME_TEXT_294,
    ASSET_GAME_TEXT_295,
    ASSET_GAME_TEXT_296,
    ASSET_GAME_TEXT_297,
    ASSET_GAME_TEXT_298,
    ASSET_GAME_TEXT_299,
    ASSET_GAME_TEXT_300,
    ASSET_GAME_TEXT_301,
    ASSET_GAME_TEXT_302,
    ASSET_GAME_TEXT_303,
    ASSET_GAME_TEXT_304,
    ASSET_GAME_TEXT_305,
    ASSET_GAME_TEXT_306,
    ASSET_GAME_TEXT_307,
    ASSET_GAME_TEXT_308,
    ASSET_GAME_TEXT_309,
    ASSET_GAME_TEXT_310,
    ASSET_GAME_TEXT_311,
    ASSET_GAME_TEXT_312,
    ASSET_GAME_TEXT_313,
    ASSET_GAME_TEXT_314,
    ASSET_GAME_TEXT_315,
    ASSET_GAME_TEXT_316,
    ASSET_GAME_TEXT_317,
    ASSET_GAME_TEXT_318,
    ASSET_GAME_TEXT_319,
    ASSET_GAME_TEXT_320,
    ASSET_GAME_TEXT_321,
    ASSET_GAME_TEXT_322,
    ASSET_GAME_TEXT_323,
    ASSET_GAME_TEXT_324,
    ASSET_GAME_TEXT_325,
    ASSET_GAME_TEXT_326,
    ASSET_GAME_TEXT_327,
    ASSET_GAME_TEXT_328,
    ASSET_GAME_TEXT_329,
    ASSET_GAME_TEXT_330,
    ASSET_GAME_TEXT_331,
    ASSET_GAME_TEXT_332,
    ASSET_GAME_TEXT_333,
    ASSET_GAME_TEXT_334,
    ASSET_GAME_TEXT_335,
    ASSET_GAME_TEXT_336,
    ASSET_GAME_TEXT_337,
    ASSET_GAME_TEXT_338,
    ASSET_GAME_TEXT_339,
    ASSET_GAME_TEXT_COUNT
} AssetGameTextEnum;
typedef enum AssetMenuTextEnum {
    ASSET_MENU_TEXT_ENGLISH,
    ASSET_MENU_TEXT_FRENCH,
    ASSET_MENU_TEXT_GERMAN,
    ASSET_MENU_TEXT_JAPANESE,
    ASSET_MENU_TEXT_COUNT
} AssetMenuTextEnum;
typedef enum AssetMenuTextIdsEnum {
    ASSET_MENU_TEXT_STEREO,
    ASSET_MENU_TEXT_MONO,
    ASSET_MENU_TEXT_HEADPHONES,
    ASSET_MENU_TEXT_SFXVOLUME,
    ASSET_MENU_TEXT_MUSICVOLUME,
    ASSET_MENU_TEXT_RETURN,
    ASSET_MENU_TEXT_AUDIOOPTIONS,
    ASSET_MENU_TEXT_MUSICTEST,
    ASSET_MENU_TEXT_ENTERINITIALS,
    ASSET_MENU_TEXT_BESTTIME,
    ASSET_MENU_TEXT_BESTLAP,
    ASSET_MENU_TEXT_SILVERCOIN,
    ASSET_MENU_TEXT_GOLDCOIN,
    ASSET_MENU_TEXT_CHALLENGE,
    ASSET_MENU_TEXT_ENTERCODE,
    ASSET_MENU_TEXT_CLEARALLCODES,
    ASSET_MENU_TEXT_CODELIST,
    ASSET_MENU_TEXT_MAGICCODES,
    ASSET_MENU_TEXT_BADCODE,
    ASSET_MENU_TEXT_ALLCODESDELETED,
    ASSET_MENU_TEXT_MAGICCODESLIST,
    ASSET_MENU_TEXT_ON,
    ASSET_MENU_TEXT_OFF,
    ASSET_MENU_TEXT_TRYAGAIN,
    ASSET_MENU_TEXT_SELECTTRACK,
    ASSET_MENU_TEXT_RETURNTOLOBBY,
    ASSET_MENU_TEXT_SELECTCHARACTER,
    ASSET_MENU_TEXT_SAVEGHOST,
    ASSET_MENU_TEXT_QUIT,
    ASSET_MENU_TEXT_LAPTIMES,
    ASSET_MENU_TEXT_OVERALLTIME,
    ASSET_MENU_TEXT_RACEORDER,
    ASSET_MENU_TEXT_RECORDTIMES,
    ASSET_MENU_TEXT_RANKINGS,
    ASSET_MENU_TEXT_LANGUAGE,
    ASSET_MENU_TEXT_CONTPAK,
    ASSET_MENU_TEXT_OPTIONS,
    ASSET_MENU_TEXT_CHANGEVEHICLE,
    ASSET_MENU_TEXT_HELP,
    ASSET_MENU_TEXT_CHALLENGES,
    ASSET_MENU_TEXT_VEHICLESELECT,
    ASSET_MENU_TEXT_CAR,
    ASSET_MENU_TEXT_HOVERCRAFT,
    ASSET_MENU_TEXT_PLANE,
    ASSET_MENU_TEXT_MAINMENU,
    ASSET_MENU_TEXT_CHALLENGESELECT,
    ASSET_MENU_TEXT_CARCHALLENGE,
    ASSET_MENU_TEXT_HOVERCHALLENGE,
    ASSET_MENU_TEXT_PLANECHALLENGE,
    ASSET_MENU_TEXT_LOSETOTAJ_0,
    ASSET_MENU_TEXT_LOSETOTAJ_1,
    ASSET_MENU_TEXT_EXIT,
    ASSET_MENU_TEXT_TTINTRO_0,
    ASSET_MENU_TEXT_TTINTRO_1,
    ASSET_MENU_TEXT_TTINTRO_2,
    ASSET_MENU_TEXT_TTINTRO_3,
    ASSET_MENU_TEXT_TTINTRO_4,
    ASSET_MENU_TEXT_TTINTRO_5,
    ASSET_MENU_TEXT_TTINTRO_6,
    ASSET_MENU_TEXT_TTINTRO_7,
    ASSET_MENU_TEXT_TTINTRO_8,
    ASSET_MENU_TEXT_TTINTRO_9,
    ASSET_MENU_TEXT_TTINTRO_10,
    ASSET_MENU_TEXT_TTINTRO_11,
    ASSET_MENU_TEXT_PAKERROR,
    ASSET_MENU_TEXT_TIMETRIALON,
    ASSET_MENU_TEXT_TIMETRIALOFF,
    ASSET_MENU_TEXT_NOCONTPAK,
    ASSET_MENU_TEXT_CONTPAKFULL,
    ASSET_MENU_TEXT_BADCONTPAK,
    ASSET_MENU_TEXT_TROPHYRACE,
    ASSET_MENU_TEXT_STATUS,
    ASSET_MENU_TEXT_GAMEA,
    ASSET_MENU_TEXT_GAMEB,
    ASSET_MENU_TEXT_GAMEC,
    ASSET_MENU_TEXT_NEW,
    ASSET_MENU_TEXT_GAMESELECT,
    ASSET_MENU_TEXT_GAMETOCOPY,
    ASSET_MENU_TEXT_GAMETOCOPYTO,
    ASSET_MENU_TEXT_GAMETOERASE,
    ASSET_MENU_TEXT_COPY,
    ASSET_MENU_TEXT_ERASE,
    ASSET_MENU_TEXT_GHOSTDATA,
    ASSET_MENU_TEXT_NOGHOSTSSAVED,
    ASSET_MENU_TEXT_ERASEGHOST,
    ASSET_MENU_TEXT_CANCEL,
    ASSET_MENU_TEXT_CONTPAK1,
    ASSET_MENU_TEXT_CONTPAK2,
    ASSET_MENU_TEXT_CONTPAK3,
    ASSET_MENU_TEXT_CONTPAK4,
    ASSET_MENU_TEXT_CONTPAKX,
    ASSET_MENU_TEXT_CONTPAKNOTPRESENT,
    ASSET_MENU_TEXT_CONTPAKTRYAGAIN,
    ASSET_MENU_TEXT_CONTPAKHASCORRUPTDATA_0,
    ASSET_MENU_TEXT_CONTPAKHASCORRUPTDATA_1,
    ASSET_MENU_TEXT_CONTPAKISDAMAGED_0,
    ASSET_MENU_TEXT_CONTPAKISDAMAGED_1,
    ASSET_MENU_TEXT_CONTPAKISFULL,
    ASSET_MENU_TEXT_CONTINUE,
    ASSET_MENU_TEXT_CONTPAKDIFFERENT_0,
    ASSET_MENU_TEXT_CONTPAKDIFFERENT_1,
    ASSET_MENU_TEXT_CONTPAKRETRY,
    ASSET_MENU_TEXT_CANNOTSTOREANYMOREGHOSTS_0,
    ASSET_MENU_TEXT_CANNOTSTOREANYMOREGHOSTS_1,
    ASSET_MENU_TEXT_ADVTWOLOADERROR_0,
    ASSET_MENU_TEXT_ADVTWOLOADERROR_1,
    ASSET_MENU_TEXT_ADVTWOLOADERROR_2,
    ASSET_MENU_TEXT_ADVTWOLOADERROR_3,
    ASSET_MENU_TEXT_ADVTWOLOADERROR_4,
    ASSET_MENU_TEXT_ADVTWOLOADERROR_5,
    ASSET_MENU_TEXT_PAKNOTES,
    ASSET_MENU_TEXT_DELETENOTEX,
    ASSET_MENU_TEXT_DELETE,
    ASSET_MENU_TEXT_CANCELDELETE,
    ASSET_MENU_TEXT_FREEPAGESX,
    ASSET_MENU_TEXT_NOTE,
    ASSET_MENU_TEXT_FILENAME,
    ASSET_MENU_TEXT_PAGES,
    ASSET_MENU_TEXT_MORE,
    ASSET_MENU_TEXT_GAMEPAK,
    ASSET_MENU_TEXT_TIMES,
    ASSET_MENU_TEXT_GHOSTS,
    ASSET_MENU_TEXT_EMPTYSLOT,
    ASSET_MENU_TEXT_VIEWGHOSTS,
    ASSET_MENU_TEXT_PLEASEWAIT,
    ASSET_MENU_TEXT_GAMEERROR,
    ASSET_MENU_TEXT_RESTARTRACE,
    ASSET_MENU_TEXT_RESTARTCHALLENGE,
    ASSET_MENU_TEXT_ABANDONCHALLENGE,
    ASSET_MENU_TEXT_QUITTROPHYRACE,
    ASSET_MENU_TEXT_QUITTROPHYRACETITLE,
    ASSET_MENU_TEXT_QUITGAME,
    ASSET_MENU_TEXT_QUITGAMETITLE,
    ASSET_MENU_TEXT_PAUSEOPTIONS,
    ASSET_MENU_TEXT_OK,
    ASSET_MENU_TEXT_PLAYERSELECT,
    ASSET_MENU_TEXT_NUMBEROFRACERS,
    ASSET_MENU_TEXT_START,
    ASSET_MENU_TEXT_ROUNDONE,
    ASSET_MENU_TEXT_ROUNDTWO,
    ASSET_MENU_TEXT_ROUNDTHREE,
    ASSET_MENU_TEXT_ROUNDFOUR,
    ASSET_MENU_TEXT_ADVENTURE,
    ASSET_MENU_TEXT_ADVENTURETWO,
    ASSET_MENU_TEXT_TRACKS,
    ASSET_MENU_TEXT_TROPHYCEREMONY,
    ASSET_MENU_TEXT_ADVENTURE2,
    ASSET_MENU_TEXT_ADVENTURETWO2,
    ASSET_MENU_TEXT_CLEARALLCODESTITLE,
    ASSET_MENU_TEXT_CLEARALLCODESCONFIRM,
    ASSET_MENU_TEXT_CLEARALLCODESCANCEL,
    ASSET_MENU_TEXT_CONTROLLERNOTCONNECTED,
    ASSET_MENU_TEXT_CAUTION,
    ASSET_MENU_TEXT_RUMBLEPAKDETECTED_0,
    ASSET_MENU_TEXT_RUMBLEPAKDETECTED_1,
    ASSET_MENU_TEXT_RUMBLEPAKDETECTED_2,
    ASSET_MENU_TEXT_INSERTDEVICE_0,
    ASSET_MENU_TEXT_INSERTDEVICE_1,
    ASSET_MENU_TEXT_INSERTDEVICE_2,
    ASSET_MENU_TEXT_INSERTDEVICE_3,
    ASSET_MENU_TEXT_INSERTDEVICE_4,
    ASSET_MENU_TEXT_INSERTDEVICE_5,
    ASSET_MENU_TEXT_INSERTDEVICE_6,
    ASSET_MENU_TEXT_TURNOFFN64_0,
    ASSET_MENU_TEXT_TURNOFFN64_1,
    ASSET_MENU_TEXT_SAVEOPTIONS,
    ASSET_MENU_TEXT_CAUTIONMESSAGE_0,
    ASSET_MENU_TEXT_CAUTIONMESSAGE_1,
    ASSET_MENU_TEXT_CAUTIONMESSAGE_2,
    ASSET_MENU_TEXT_CAUTIONMESSAGE_3,
    ASSET_MENU_TEXT_CAUTIONMESSAGE_4,
    ASSET_MENU_TEXT_CAUTIONMESSAGE_5,
    ASSET_MENU_TEXT_CAUTIONMESSAGE_6,
    ASSET_MENU_TEXT_CAUTIONMESSAGE_7,
    ASSET_MENU_TEXT_CAUTIONMESSAGE_8,
    ASSET_MENU_TEXT_CAUTIONMESSAGE_9,
    ASSET_MENU_TEXT_CAUTIONMESSAGE_10,
    ASSET_MENU_TEXT_CANNOTSAVEGHOSTDATA_0,
    ASSET_MENU_TEXT_CANNOTSAVEGHOSTDATA_1,
    ASSET_MENU_TEXT_CANNOTSAVEGHOSTDATA_2,
    ASSET_MENU_TEXT_ENTERTROPHYRACE,
    ASSET_MENU_TEXT_GAMEPAKBONUSES,
    ASSET_MENU_TEXT_SUBTITLESON,
    ASSET_MENU_TEXT_SUBTITLESOFF,
    ASSET_MENU_TEXT_CORRUPTDATA_0,
    ASSET_MENU_TEXT_CORRUPTDATA_1,
    ASSET_MENU_TEXT_UNKNOWN_186,
    ASSET_MENU_TEXT_UNKNOWN_187,
    ASSET_MENU_TEXT_UNKNOWN_188,
    ASSET_MENU_TEXT_UNKNOWN_189,
    ASSET_MENU_TEXT_UNKNOWN_190,
    ASSET_MENU_TEXT_UNKNOWN_191
} AssetMenuTextIdsEnum;
typedef enum AssetScreensEnum {
    ASSET_SCREENS_COUNT
} AssetScreensEnum;
typedef enum AssetSpritesEnum {
    ASSET_SPRITE_MINIMAP_FOSSILCANYON,
    ASSET_SPRITE_MINIMAP_ANCIENTLAKE,
    ASSET_SPRITE_MINIMAP_PIRATELAGOON,
    ASSET_SPRITE_MINIMAP_WHALEBAY,
    ASSET_SPRITE_MINIMAP_SNOWBALLVALLEY,
    ASSET_SPRITE_MINIMAP_HOTTOPVOLCANO,
    ASSET_SPRITE_MINIMAP_CRESCENTISLAND,
    ASSET_SPRITE_MINIMAP_UNUSED,
    ASSET_SPRITE_MINIMAP_EVERFROSTPEAK,
    ASSET_SPRITE_MINIMAP_UNUSED2,
    ASSET_SPRITE_MINIMAP_WALRUSCOVE,
    ASSET_SPRITE_MINIMAP_UNUSED3,
    ASSET_SPRITE_MINIMAP_BOULDERCANYON,
    ASSET_SPRITE_MINIMAP_SMOKEYCASTLE,
    ASSET_SPRITE_MINIMAP_CENTRALAREA,
    ASSET_SPRITE_MINIMAP_FIREMOUNTAIN,
    ASSET_SPRITE_MINIMAP_SPACEPORTALPHA,
    ASSET_SPRITE_MINIMAP_SPACEDUSTALLEY,
    ASSET_SPRITE_MINIMAP_TREASURECAVES,
    ASSET_SPRITE_MINIMAP_GREENWOODVILLAGE,
    ASSET_SPRITE_MINIMAP_DARKMOONCAVERNS,
    ASSET_SPRITE_MINIMAP_STARCITY,
    ASSET_SPRITE_MINIMAP_WINDMILLPLAINS,
    ASSET_SPRITE_MINIMAP_FROSTYVILLAGE,
    ASSET_SPRITE_MINIMAP_DARKWATERBEACH,
    ASSET_SPRITE_MINIMAP_JUNGLEFALLS,
    ASSET_SPRITE_MINIMAP_ICICLEPYRAMID,
    ASSET_SPRITE_MINIMAP_HAUNTEDWOODS,
    ASSET_SPRITE_MINIMAP_BLUEY,
    ASSET_SPRITE_MINIMAP_BUBBLER,
    ASSET_SPRITE_MINIMAP_SMOKEY,
    ASSET_SPRITE_MINIMAP_TRICKYTOPS,
    ASSET_SPRITE_MINIMAP_WIZPIG1,
    ASSET_SPRITE_MINIMAP_WIZPIG2,
    ASSET_SPRITE_WEATHER_RAINDROP,
    ASSET_SPRITE_WEATHER_SNOWFLAKE,
    ASSET_SPRITE_OBJECTS_LENSFLARE1,
    ASSET_SPRITE_OBJECTS_LENSFLARE2,
    ASSET_SPRITE_OBJECTS_LENSFLARE3,
    ASSET_SPRITE_UNKNOWN_BROWNEGG,
    ASSET_SPRITE_PARTICLES_SMOKE,
    ASSET_SPRITE_PARTICLES_SMOKE2,
    ASSET_SPRITE_PARTICLES_BUBBLESSMALL,
    ASSET_SPRITE_PARTICLES_SMOKE3,
    ASSET_SPRITE_OBJECTS_BUBBLEWEAPON,
    ASSET_SPRITE_OBJECTS_SPARKLE,
    ASSET_SPRITE_OBJECTS_BOMBEXPLOSIONBLUE,
    ASSET_SPRITE_OBJECTS_BOMBEXPLOSIONYELLOW,
    ASSET_SPRITE_OBJECTS_BOMBEXPLOSIONRED,
    ASSET_SPRITE_OBJECTS_BOMBEXPLOSIONGREEN,
    ASSET_SPRITE_OBJECTS_BOMBEXPLOSIONCYAN,
    ASSET_SPRITE_OBJECTS_BOMBEXPLOSIONWHITE,
    ASSET_SPRITE_OBJECTS_BOMBEXPLOSIONORANGE,
    ASSET_SPRITE_OBJECTS_BOMBEXPLOSIONPURPLE,
    ASSET_SPRITE_OBJECTS_RAINBOW,
    ASSET_SPRITE_OBJECTS_EGG,
    ASSET_SPRITE_OBJECTS_BOMB,
    ASSET_SPRITE_OBJECTS_OILSLICK,
    ASSET_SPRITE_OBJECTS_EYESINDARK,
    ASSET_SPRITE_HUD_TIMERCOLON,
    ASSET_SPRITE_HUD_RETICALHOMING,
    ASSET_SPRITE_OBJECTS_DEBUGREDSPHERE,
    ASSET_SPRITE_HUD_FINISH,
    ASSET_SPRITE_HUD_GETREADY,
    ASSET_SPRITE_HUD_GO,
    ASSET_SPRITE_HUD_LAP,
    ASSET_SPRITE_HUD_FORWARDSLASH,
    ASSET_SPRITE_HUD_TIME,
    ASSET_SPRITE_HUD_PLACENUMBERS,
    ASSET_SPRITE_HUD_TIMERNUMBERS,
    ASSET_SPRITE_HUD_TIMERCOLORSMALL,
    ASSET_SPRITE_HUD_TIMERNUMBERSSMALL,
    ASSET_SPRITE_HUD_GOSMALL,
    ASSET_SPRITE_HUD_LAPSMALL,
    ASSET_SPRITE_HUD_GETREADY2,
    ASSET_SPRITE_HUD_FINALSMALL,
    ASSET_SPRITE_HUD_FINISHSMALL,
    ASSET_SPRITE_HUD_LAP2SMALL,
    ASSET_SPRITE_HUD_WAYSMALL,
    ASSET_SPRITE_HUD_WRONGSMALL,
    ASSET_SPRITE_OBJECTS_POSITIONARROW,
    ASSET_SPRITE_HUD_GOLDENBALLOONICON,
    ASSET_SPRITE_HUD_SILVERBALLOONICON,
    ASSET_SPRITE_OBJECTS_LEVELNAME,
    ASSET_SPRITE_MINIMAP_NPC,
    ASSET_SPRITE_MINIMAP_PLAYER,
    ASSET_SPRITE_HUD_WEAPONICONS,
    ASSET_SPRITE_HUD_WEAPONICONNUMBERS,
    ASSET_SPRITE_UNUSED_BETACHARACTERICON,
    ASSET_SPRITE_HUD_FINALLAPFLAG,
    ASSET_SPRITE_HUD_FINAL,
    ASSET_SPRITE_HUD_LAPLARGE,
    ASSET_SPRITE_HUD_LAP22,
    ASSET_SPRITE_HUD_WAY,
    ASSET_SPRITE_HUD_WRONG,
    ASSET_SPRITE_UNUSED_PROAMLOGO,
    ASSET_SPRITE_HUD_SPEEDOMETERARROW,
    ASSET_SPRITE_HUD_FIRSTPLACEONE,
    ASSET_SPRITE_HUD_FIRSTPLACEST,
    ASSET_SPRITE_OBJECTS_BALLOONSTRING,
    ASSET_SPRITE_UNKNOWN_FIREBALLUNKNOWN,
    ASSET_SPRITE_OBJECTS_FIREBALL,
    ASSET_SPRITE_OBJECTS_WIZGHOST,
    ASSET_SPRITE_UNKNOWN_UNKNOWNLIGHT,
    ASSET_SPRITE_UNKNOWN_SMALLSTAR,
    ASSET_SPRITE_OBJECTS_BUOY,
    ASSET_SPRITE_OBJECTS_SMARTIETREE,
    ASSET_SPRITE_OBJECTS_BEACHTREE,
    ASSET_SPRITE_OBJECTS_BLUEBERRYBUSH,
    ASSET_SPRITE_OBJECTS_RUBBERSNOWTREE,
    ASSET_SPRITE_OBJECTS_SKINNYSNOWTREE,
    ASSET_SPRITE_OBJECTS_XMASTREE,
    ASSET_SPRITE_OBJECTS_ALPINESNOWTREE,
    ASSET_SPRITE_OBJECTS_RUBBERTREE,
    ASSET_SPRITE_OBJECTS_PALMTREETOP,
    ASSET_SPRITE_OBJECTS_PALMPLANT,
    ASSET_SPRITE_OBJECTS_PALMTREETOPCHEA,
    ASSET_SPRITE_OBJECTS_FIRTREE,
    ASSET_SPRITE_OBJECTS_SPACETREE,
    ASSET_SPRITE_OBJECTS_LAMPPOST,
    ASSET_SPRITE_FLOWERS_WHITEBUTTERCUP,
    ASSET_SPRITE_FLOWERS_YELLOWBELLFLOWER,
    ASSET_SPRITE_FLOWERS_YELLOWBUTTERCUP,
    ASSET_SPRITE_FLOWERS_BLUEBUTTERCUP,
    ASSET_SPRITE_FLOWERS_WATERLILY,
    ASSET_SPRITE_OBJECTS_REEDNOLEAF,
    ASSET_SPRITE_OBJECTS_REEDLEAVES,
    ASSET_SPRITE_OBJECTS_READONELEAF,
    ASSET_SPRITE_OBJECTS_SNOWMANTOPHAT,
    ASSET_SPRITE_OBJECTS_BELL,
    ASSET_SPRITE_OBJECTS_SNOWMAN,
    ASSET_SPRITE_UNUSED_TORCHWITHEYES,
    ASSET_SPRITE_OBJECTS_DEBUGCAMERACONTROL,
    ASSET_SPRITE_UNUSED_DEBUGUNKNOWNEXIT,
    ASSET_SPRITE_UNUSED_BETAANCIENTLAKESIGN,
    ASSET_SPRITE_OBJECTS_DEBUGAUDIOSEQ,
    ASSET_SPRITE_OBJECTS_DEBUGANIMCAR,
    ASSET_SPRITE_OBJECTS_DEBUGSKYCONTROL,
    ASSET_SPRITE_OBJECTS_DEBUGORBRED,
    ASSET_SPRITE_OBJECTS_DEBUGORBYELLOW,
    ASSET_SPRITE_OBJECTS_DEBUGFOGCHANGER,
    ASSET_SPRITE_OBJECTS_DEBUGANIMATOR,
    ASSET_SPRITE_OBJECTS_DEBUGAUDIO,
    ASSET_SPRITE_OBJECTS_DEBUGAUDIOLINE,
    ASSET_SPRITE_OBJECTS_DEBUGAUDIOSEQLINE,
    ASSET_SPRITE_UNUSED_DEBUGUNKNOWNTRAFFICLIGHT,
    ASSET_SPRITE_OBJECTS_DEBUGAUDIOREVERB,
    ASSET_SPRITE_OBJECTS_BALLOONBOOST,
    ASSET_SPRITE_OBJECTS_BALLOONMISSLE,
    ASSET_SPRITE_OBJECTS_BALLOONTRAP,
    ASSET_SPRITE_OBJECTS_BALLOONSHIELD,
    ASSET_SPRITE_OBJECTS_BALLOONMAGNET,
    ASSET_SPRITE_UNUSED_BALLOONMISSLEGIFT,
    ASSET_SPRITE_UNUSED_BALLOONBOOSTGIFT,
    ASSET_SPRITE_OBJECTS_BALLOONGOLD,
    ASSET_SPRITE_OBJECTS_BALLOONSILVER,
    ASSET_SPRITE_OBJECTS_BANANA,
    ASSET_SPRITE_OBJECTS_SILVERCOIN,
    ASSET_SPRITE_OBJECTS_CHECKPOINTFLAG,
    ASSET_SPRITE_UNUSED_RAREWARECOIN,
    ASSET_SPRITE_UNUSED_SILVERCOINVERTICAL,
    ASSET_SPRITE_HUD_BANANAICON,
    ASSET_SPRITE_PARTICLES_SPARKLE,
    ASSET_SPRITE_OBJECTS_DEBUGEGGCREATOR,
    ASSET_SPRITE_UNUSED_BONUSGEM,
    ASSET_SPRITE_HUD_INDICATORICONCAUTION,
    ASSET_SPRITE_HUD_INDICATORICONDOWN,
    ASSET_SPRITE_HUD_INDICATORICONUTURN,
    ASSET_SPRITE_HUD_INDICATORICONTURN,
    ASSET_SPRITE_HUD_INDICATORICONSLIGHTTURN,
    ASSET_SPRITE_OBJECTS_SMOKEOBJECT,
    ASSET_SPRITE_OBJECTS_SMOKECLOUD,
    ASSET_SPRITE_OBJECTS_SMOKEGRASS,
    ASSET_SPRITE_OBJECTS_MIST,
    ASSET_SPRITE_OBJECTS_FLAMINGTORCH,
    ASSET_SPRITE_UNUSED_SPLASH,
    ASSET_SPRITE_UNUSED_WEAPONBALLOONPOP,
    ASSET_SPRITE_OBJECTS_LAVASPURT,
    ASSET_SPRITE_UNKNOWN_UNKNOWNSMALLPOP,
    ASSET_SPRITE_VEHICLE_PARTS_TYRE0,
    ASSET_SPRITE_VEHICLE_PARTS_TYRE1,
    ASSET_SPRITE_VEHICLE_PARTS_TYRE2,
    ASSET_SPRITE_VEHICLE_PARTS_TYRE3,
    ASSET_SPRITE_VEHICLE_PARTS_FAN0,
    ASSET_SPRITE_VEHICLE_PARTS_FAN1,
    ASSET_SPRITE_VEHICLE_PARTS_PROPELLER0,
    ASSET_SPRITE_VEHICLE_PARTS_PROPELLER1,
    ASSET_SPRITE_UNUSED_RARELETTERS,
    ASSET_SPRITE_OBJECTS_BOLTGLOW,
    ASSET_SPRITE_MENU_ICONTROPHY,
    ASSET_SPRITE_MENU_ICONKEY,
    ASSET_SPRITE_MENU_ICONTTAMULET,
    ASSET_SPRITE_MENU_ICONWIZPIGAMULET,
    ASSET_SPRITES_COUNT
} AssetSpritesEnum;
typedef enum AssetEmpty14Enum {
    ASSET_EMPTY_14_COUNT
} AssetEmpty14Enum;
typedef enum AssetMiscEnum {
    ASSET_MISC_0,
    ASSET_MISC_1,
    ASSET_MISC_2,
    ASSET_MISC_3,
    ASSET_MISC_4,
    ASSET_MISC_5,
    ASSET_MISC_6,
    ASSET_MISC_7,
    ASSET_MISC_8,
    ASSET_MISC_RACER_WEIGHT,
    ASSET_MISC_RACER_HANDLING,
    ASSET_MISC_RACER_UNUSED_11,
    ASSET_MISC_BALLOON_DATA,
    ASSET_MISC_13,
    ASSET_MISC_14,
    ASSET_MISC_15,
    ASSET_MISC_16,
    ASSET_MISC_17,
    ASSET_MISC_18,
    ASSET_MISC_RUMBLE_DATA,
    ASSET_MISC_20,
    ASSET_MISC_SHIELD_DATA,
    ASSET_MISC_MAGNET_DATA,
    ASSET_MISC_23,
    ASSET_MISC_GHOST_UNLOCK_TIMES,
    ASSET_MISC_CINEMATIC_RACE,
    ASSET_MISC_TRACKS_MENU_IDS,
    ASSET_MISC_HUB_AREA_IDS,
    ASSET_MISC_MAIN_TRACKS_IDS,
    ASSET_MISC_BATTLE_TRACKS_IDS,
    ASSET_MISC_BOSS_TRACKS_IDS,
    ASSET_MISC_CINEMATIC_TROPHY,
    ASSET_MISC_32,
    ASSET_MISC_RACERACCELERATION_UNKNOWN0,
    ASSET_MISC_RACERACCELERATION_DIDDY,
    ASSET_MISC_RACERACCELERATION_TT,
    ASSET_MISC_RACERACCELERATION_UNKNOWN1,
    ASSET_MISC_RACERACCELERATION_KRUNCH,
    ASSET_MISC_RACERACCELERATION_BUMPER,
    ASSET_MISC_RACERACCELERATION_TIPTUP,
    ASSET_MISC_RACERACCELERATION_CONKER,
    ASSET_MISC_RACERACCELERATION_TIMBER,
    ASSET_MISC_RACERACCELERATION_BANJO,
    ASSET_MISC_RACERACCELERATION_DRUMSTICK,
    ASSET_MISC_RACERACCELERATION_PIPSY,
    ASSET_MISC_RACERACCELERATION_UNKNOWN2,
    ASSET_MISC_46,
    ASSET_MISC_47,
    ASSET_MISC_48,
    ASSET_MISC_49,
    ASSET_MISC_50,
    ASSET_MISC_51,
    ASSET_MISC_52,
    ASSET_MISC_53,
    ASSET_MISC_54,
    ASSET_MISC_55,
    ASSET_MISC_RACER_HITBOX_SIZE,
    ASSET_MISC_57,
    ASSET_MISC_58,
    ASSET_MISC_59,
    ASSET_MISC_60,
    ASSET_MISC_61,
    ASSET_MISC_62,
    ASSET_MISC_63,
    ASSET_MISC_64,
    ASSET_MISC_MAGIC_CODES,
    ASSET_MISC_TITLE_SCREEN_DEMO_IDS,
    ASSET_MISC_67,
    ASSET_MISC_68,
    ASSET_MISC_69,
    ASSET_MISC_COUNT
} AssetMiscEnum;
typedef enum AssetLevelObjectMapsEnum {
    ASSET_LEVEL_OBJECT_MAPS_0,
    ASSET_LEVEL_OBJECT_MAPS_1,
    ASSET_LEVEL_OBJECT_MAPS_2,
    ASSET_LEVEL_OBJECT_MAPS_3,
    ASSET_LEVEL_OBJECT_MAPS_4,
    ASSET_LEVEL_OBJECT_MAPS_5,
    ASSET_LEVEL_OBJECT_MAPS_6,
    ASSET_LEVEL_OBJECT_MAPS_7,
    ASSET_LEVEL_OBJECT_MAPS_8,
    ASSET_LEVEL_OBJECT_MAPS_9,
    ASSET_LEVEL_OBJECT_MAPS_10,
    ASSET_LEVEL_OBJECT_MAPS_11,
    ASSET_LEVEL_OBJECT_MAPS_12,
    ASSET_LEVEL_OBJECT_MAPS_13,
    ASSET_LEVEL_OBJECT_MAPS_14,
    ASSET_LEVEL_OBJECT_MAPS_15,
    ASSET_LEVEL_OBJECT_MAPS_16,
    ASSET_LEVEL_OBJECT_MAPS_17,
    ASSET_LEVEL_OBJECT_MAPS_18,
    ASSET_LEVEL_OBJECT_MAPS_19,
    ASSET_LEVEL_OBJECT_MAPS_20,
    ASSET_LEVEL_OBJECT_MAPS_21,
    ASSET_LEVEL_OBJECT_MAPS_22,
    ASSET_LEVEL_OBJECT_MAPS_23,
    ASSET_LEVEL_OBJECT_MAPS_24,
    ASSET_LEVEL_OBJECT_MAPS_25,
    ASSET_LEVEL_OBJECT_MAPS_26,
    ASSET_LEVEL_OBJECT_MAPS_27,
    ASSET_LEVEL_OBJECT_MAPS_28,
    ASSET_LEVEL_OBJECT_MAPS_29,
    ASSET_LEVEL_OBJECT_MAPS_30,
    ASSET_LEVEL_OBJECT_MAPS_31,
    ASSET_LEVEL_OBJECT_MAPS_32,
    ASSET_LEVEL_OBJECT_MAPS_33,
    ASSET_LEVEL_OBJECT_MAPS_34,
    ASSET_LEVEL_OBJECT_MAPS_35,
    ASSET_LEVEL_OBJECT_MAPS_36,
    ASSET_LEVEL_OBJECT_MAPS_37,
    ASSET_LEVEL_OBJECT_MAPS_38,
    ASSET_LEVEL_OBJECT_MAPS_39,
    ASSET_LEVEL_OBJECT_MAPS_40,
    ASSET_LEVEL_OBJECT_MAPS_41,
    ASSET_LEVEL_OBJECT_MAPS_42,
    ASSET_LEVEL_OBJECT_MAPS_43,
    ASSET_LEVEL_OBJECT_MAPS_44,
    ASSET_LEVEL_OBJECT_MAPS_45,
    ASSET_LEVEL_OBJECT_MAPS_46,
    ASSET_LEVEL_OBJECT_MAPS_47,
    ASSET_LEVEL_OBJECT_MAPS_48,
    ASSET_LEVEL_OBJECT_MAPS_49,
    ASSET_LEVEL_OBJECT_MAPS_50,
    ASSET_LEVEL_OBJECT_MAPS_51,
    ASSET_LEVEL_OBJECT_MAPS_52,
    ASSET_LEVEL_OBJECT_MAPS_53,
    ASSET_LEVEL_OBJECT_MAPS_54,
    ASSET_LEVEL_OBJECT_MAPS_55,
    ASSET_LEVEL_OBJECT_MAPS_56,
    ASSET_LEVEL_OBJECT_MAPS_57,
    ASSET_LEVEL_OBJECT_MAPS_58,
    ASSET_LEVEL_OBJECT_MAPS_59,
    ASSET_LEVEL_OBJECT_MAPS_60,
    ASSET_LEVEL_OBJECT_MAPS_61,
    ASSET_LEVEL_OBJECT_MAPS_62,
    ASSET_LEVEL_OBJECT_MAPS_63,
    ASSET_LEVEL_OBJECT_MAPS_64,
    ASSET_LEVEL_OBJECT_MAPS_65,
    ASSET_LEVEL_OBJECT_MAPS_66,
    ASSET_LEVEL_OBJECT_MAPS_67,
    ASSET_LEVEL_OBJECT_MAPS_68,
    ASSET_LEVEL_OBJECT_MAPS_69,
    ASSET_LEVEL_OBJECT_MAPS_70,
    ASSET_LEVEL_OBJECT_MAPS_71,
    ASSET_LEVEL_OBJECT_MAPS_72,
    ASSET_LEVEL_OBJECT_MAPS_73,
    ASSET_LEVEL_OBJECT_MAPS_74,
    ASSET_LEVEL_OBJECT_MAPS_75,
    ASSET_LEVEL_OBJECT_MAPS_76,
    ASSET_LEVEL_OBJECT_MAPS_77,
    ASSET_LEVEL_OBJECT_MAPS_78,
    ASSET_LEVEL_OBJECT_MAPS_79,
    ASSET_LEVEL_OBJECT_MAPS_80,
    ASSET_LEVEL_OBJECT_MAPS_81,
    ASSET_LEVEL_OBJECT_MAPS_82,
    ASSET_LEVEL_OBJECT_MAPS_83,
    ASSET_LEVEL_OBJECT_MAPS_84,
    ASSET_LEVEL_OBJECT_MAPS_85,
    ASSET_LEVEL_OBJECT_MAPS_86,
    ASSET_LEVEL_OBJECT_MAPS_87,
    ASSET_LEVEL_OBJECT_MAPS_88,
    ASSET_LEVEL_OBJECT_MAPS_89,
    ASSET_LEVEL_OBJECT_MAPS_90,
    ASSET_LEVEL_OBJECT_MAPS_91,
    ASSET_LEVEL_OBJECT_MAPS_92,
    ASSET_LEVEL_OBJECT_MAPS_93,
    ASSET_LEVEL_OBJECT_MAPS_94,
    ASSET_LEVEL_OBJECT_MAPS_95,
    ASSET_LEVEL_OBJECT_MAPS_96,
    ASSET_LEVEL_OBJECT_MAPS_97,
    ASSET_LEVEL_OBJECT_MAPS_98,
    ASSET_LEVEL_OBJECT_MAPS_99,
    ASSET_LEVEL_OBJECT_MAPS_100,
    ASSET_LEVEL_OBJECT_MAPS_101,
    ASSET_LEVEL_OBJECT_MAPS_102,
    ASSET_LEVEL_OBJECT_MAPS_103,
    ASSET_LEVEL_OBJECT_MAPS_104,
    ASSET_LEVEL_OBJECT_MAPS_105,
    ASSET_LEVEL_OBJECT_MAPS_106,
    ASSET_LEVEL_OBJECT_MAPS_107,
    ASSET_LEVEL_OBJECT_MAPS_108,
    ASSET_LEVEL_OBJECT_MAPS_109,
    ASSET_LEVEL_OBJECT_MAPS_110,
    ASSET_LEVEL_OBJECT_MAPS_111,
    ASSET_LEVEL_OBJECT_MAPS_112,
    ASSET_LEVEL_OBJECT_MAPS_113,
    ASSET_LEVEL_OBJECT_MAPS_114,
    ASSET_LEVEL_OBJECT_MAPS_115,
    ASSET_LEVEL_OBJECT_MAPS_116,
    ASSET_LEVEL_OBJECT_MAPS_117,
    ASSET_LEVEL_OBJECT_MAPS_118,
    ASSET_LEVEL_OBJECT_MAPS_119,
    ASSET_LEVEL_OBJECT_MAPS_120,
    ASSET_LEVEL_OBJECT_MAPS_121,
    ASSET_LEVEL_OBJECT_MAPS_122,
    ASSET_LEVEL_OBJECT_MAPS_123,
    ASSET_LEVEL_OBJECT_MAPS_124,
    ASSET_LEVEL_OBJECT_MAPS_125,
    ASSET_LEVEL_OBJECT_MAPS_126,
    ASSET_LEVEL_OBJECT_MAPS_127,
    ASSET_LEVEL_OBJECT_MAPS_128,
    ASSET_LEVEL_OBJECT_MAPS_129,
    ASSET_LEVEL_OBJECT_MAPS_130,
    ASSET_LEVEL_OBJECT_MAPS_131,
    ASSET_LEVEL_OBJECT_MAPS_132,
    ASSET_LEVEL_OBJECT_MAPS_133,
    ASSET_LEVEL_OBJECT_MAPS_134,
    ASSET_LEVEL_OBJECT_MAPS_135,
    ASSET_LEVEL_OBJECT_MAPS_136,
    ASSET_LEVEL_OBJECT_MAPS_137,
    ASSET_LEVEL_OBJECT_MAPS_COUNT
} AssetLevelObjectMapsEnum;
typedef enum AssetLevelHeadersEnum {
    ASSET_LEVEL_CENTRALAREAHUB,
    ASSET_LEVEL_BLUEY1,
    ASSET_LEVEL_DRAGONFORESTHUB,
    ASSET_LEVEL_FOSSILCANYON,
    ASSET_LEVEL_PIRATELAGOON,
    ASSET_LEVEL_ANCIENTLAKE,
    ASSET_LEVEL_WALRUSCOVE,
    ASSET_LEVEL_HOTTOPVOLCANO,
    ASSET_LEVEL_WHALEBAY,
    ASSET_LEVEL_SNOWBALLVALLEY,
    ASSET_LEVEL_CRESCENTISLAND,
    ASSET_LEVEL_FIREMOUNTAIN,
    ASSET_LEVEL_DINODOMAINHUB,
    ASSET_LEVEL_EVERFROSTPEAK,
    ASSET_LEVEL_SHERBETISLANDHUB,
    ASSET_LEVEL_SPACEPORTALPHA,
    ASSET_LEVEL_HORSESHOEGULCH,
    ASSET_LEVEL_SPACEDUSTALLEY,
    ASSET_LEVEL_GREENWOODVILLAGE,
    ASSET_LEVEL_BOULDERCANYON,
    ASSET_LEVEL_WINDMILLPLAINS,
    ASSET_LEVEL_FRONTEND,
    ASSET_LEVEL_CHARACTERSELECT,
    ASSET_LEVEL_TITLESCREENSEQUENCE,
    ASSET_LEVEL_SNOWFLAKEMOUNTAINHUB,
    ASSET_LEVEL_SMOKEYCASTLE,
    ASSET_LEVEL_DARKWATERBEACH,
    ASSET_LEVEL_ICICLEPYRAMID,
    ASSET_LEVEL_FROSTYVILLAGE,
    ASSET_LEVEL_JUNGLEFALLS,
    ASSET_LEVEL_TREASURECAVES,
    ASSET_LEVEL_HAUNTEDWOODS,
    ASSET_LEVEL_DARKMOONCAVERNS,
    ASSET_LEVEL_STARCITY,
    ASSET_LEVEL_TROPHYRACE,
    ASSET_LEVEL_FUTUREFUNLANDHUB,
    ASSET_LEVEL_OPENINGSEQUENCE,
    ASSET_LEVEL_WIZPIG1,
    ASSET_LEVEL_TRICKYTOPS1,
    ASSET_LEVEL_OPTIONSBACKGROUND,
    ASSET_LEVEL_BUBBLER1,
    ASSET_LEVEL_SMOKEY1,
    ASSET_LEVEL_WIZPIGMOUTHSEQUENCE,
    ASSET_LEVEL_WIZPIGAMULETSEQUENCE,
    ASSET_LEVEL_TTAMULETSEQUENCE,
    ASSET_LEVEL_ROCKETSEQUENCE,
    ASSET_LEVEL_TRICKYTOPS2,
    ASSET_LEVEL_DINODOMAINTROPHYANIM,
    ASSET_LEVEL_SNOWFLAKEMOUNTAINTROPHYANIM,
    ASSET_LEVEL_SHERBETISLANDTROPHYANIM,
    ASSET_LEVEL_DRAGONFORESTTROPHYANIM,
    ASSET_LEVEL_FUTUREFUNLANDTROPHYANIM,
    ASSET_LEVEL_BLUEY2,
    ASSET_LEVEL_BUBBLER2,
    ASSET_LEVEL_SMOKEY2,
    ASSET_LEVEL_WIZPIG2,
    ASSET_LEVEL_PARTYSEQUENCE,
    ASSET_LEVEL_TRICKTOPSANIM,
    ASSET_LEVEL_SMOKEYANIM,
    ASSET_LEVEL_BLUEYANIM,
    ASSET_LEVEL_WIZPIG1ANIM,
    ASSET_LEVEL_BUBBLERANIM,
    ASSET_LEVEL_WIZPIG2ANIM,
    ASSET_LEVEL_LASTBIT,
    ASSET_LEVEL_LASTBITB,
    ASSET_LEVEL_HEADERS_COUNT
} AssetLevelHeadersEnum;
typedef enum AssetLevelNamesEnum {
    ASSET_LEVEL_CENTRALAREAHUB_NAME,
    ASSET_LEVEL_BLUEY1_NAME,
    ASSET_LEVEL_DRAGONFORESTHUB_NAME,
    ASSET_LEVEL_FOSSILCANYON_NAME,
    ASSET_LEVEL_PIRATELAGOON_NAME,
    ASSET_LEVEL_ANCIENTLAKE_NAME,
    ASSET_LEVEL_WALRUSCOVE_NAME,
    ASSET_LEVEL_HOTTOPVOLCANO_NAME,
    ASSET_LEVEL_WHALEBAY_NAME,
    ASSET_LEVEL_SNOWBALLVALLEY_NAME,
    ASSET_LEVEL_CRESCENTISLAND_NAME,
    ASSET_LEVEL_FIREMOUNTAIN_NAME,
    ASSET_LEVEL_DINODOMAINHUB_NAME,
    ASSET_LEVEL_EVERFROSTPEAK_NAME,
    ASSET_LEVEL_SHERBETISLANDHUB_NAME,
    ASSET_LEVEL_SPACEPORTALPHA_NAME,
    ASSET_LEVEL_HORSESHOEGULCH_NAME,
    ASSET_LEVEL_SPACEDUSTALLEY_NAME,
    ASSET_LEVEL_GREENWOODVILLAGE_NAME,
    ASSET_LEVEL_BOULDERCANYON_NAME,
    ASSET_LEVEL_WINDMILLPLAINS_NAME,
    ASSET_LEVEL_FRONTEND_NAME,
    ASSET_LEVEL_CHARACTERSELECT_NAME,
    ASSET_LEVEL_TITLESCREENSEQUENCE_NAME,
    ASSET_LEVEL_SNOWFLAKEMOUNTAINHUB_NAME,
    ASSET_LEVEL_SMOKEYCASTLE_NAME,
    ASSET_LEVEL_DARKWATERBEACH_NAME,
    ASSET_LEVEL_ICICLEPYRAMID_NAME,
    ASSET_LEVEL_FROSTYVILLAGE_NAME,
    ASSET_LEVEL_JUNGLEFALLS_NAME,
    ASSET_LEVEL_TREASURECAVES_NAME,
    ASSET_LEVEL_HAUNTEDWOODS_NAME,
    ASSET_LEVEL_DARKMOONCAVERNS_NAME,
    ASSET_LEVEL_STARCITY_NAME,
    ASSET_LEVEL_TROPHYRACE_NAME,
    ASSET_LEVEL_FUTUREFUNLANDHUB_NAME,
    ASSET_LEVEL_OPENINGSEQUENCE_NAME,
    ASSET_LEVEL_WIZPIG1_NAME,
    ASSET_LEVEL_TRICKYTOPS1_NAME,
    ASSET_LEVEL_OPTIONSBACKGROUND_NAME,
    ASSET_LEVEL_BUBBLER1_NAME,
    ASSET_LEVEL_SMOKEY1_NAME,
    ASSET_LEVEL_WIZPIGMOUTHSEQUENCE_NAME,
    ASSET_LEVEL_WIZPIGAMULETSEQUENCE_NAME,
    ASSET_LEVEL_TTAMULETSEQUENCE_NAME,
    ASSET_LEVEL_ROCKETSEQUENCE_NAME,
    ASSET_LEVEL_TRICKYTOPS2_NAME,
    ASSET_LEVEL_DINODOMAINTROPHYANIM_NAME,
    ASSET_LEVEL_SNOWFLAKEMOUNTAINTROPHYANIM_NAME,
    ASSET_LEVEL_SHERBETISLANDTROPHYANIM_NAME,
    ASSET_LEVEL_DRAGONFORESTTROPHYANIM_NAME,
    ASSET_LEVEL_FUTUREFUNLANDTROPHYANIM_NAME,
    ASSET_LEVEL_BLUEY2_NAME,
    ASSET_LEVEL_BUBBLER2_NAME,
    ASSET_LEVEL_SMOKEY2_NAME,
    ASSET_LEVEL_WIZPIG2_NAME,
    ASSET_LEVEL_PARTYSEQUENCE_NAME,
    ASSET_LEVEL_TRICKTOPSANIM_NAME,
    ASSET_LEVEL_SMOKEYANIM_NAME,
    ASSET_LEVEL_BLUEYANIM_NAME,
    ASSET_LEVEL_WIZPIG1ANIM_NAME,
    ASSET_LEVEL_BUBBLERANIM_NAME,
    ASSET_LEVEL_WIZPIG2ANIM_NAME,
    ASSET_LEVEL_LASTBIT_NAME,
    ASSET_LEVEL_LASTBITB_NAME,
    ASSET_LEVEL_NAMES_COUNT
} AssetLevelNamesEnum;
typedef enum AssetLevelModelsEnum {
    ASSET_LEVELMODEL_CENTRALAREAHUB,
    ASSET_LEVELMODEL_BLUEY,
    ASSET_LEVELMODEL_DRAGONFORESTHUB,
    ASSET_LEVELMODEL_FOSSILCANYON,
    ASSET_LEVELMODEL_PIRATELAGOON,
    ASSET_LEVELMODEL_ANCIENTLAKE,
    ASSET_LEVELMODEL_WALRUSCOVE,
    ASSET_LEVELMODEL_HOTTOPVOLCANO,
    ASSET_LEVELMODEL_WHALEBAY,
    ASSET_LEVELMODEL_SNOWBALLVALLEY,
    ASSET_LEVELMODEL_TEMPLETRACK,
    ASSET_LEVELMODEL_CRESCENTISLAND,
    ASSET_LEVELMODEL_FIREMOUNTAIN,
    ASSET_LEVELMODEL_DINODOMAINHUB,
    ASSET_LEVELMODEL_EVERFROSTPEAK,
    ASSET_LEVELMODEL_SHERBETISLANDHUB,
    ASSET_LEVELMODEL_FRONTEND,
    ASSET_LEVELMODEL_CHARACTERSELECT,
    ASSET_LEVELMODEL_SPACEPORTALPHA,
    ASSET_LEVELMODEL_HORSESHOEGULCH,
    ASSET_LEVELMODEL_GREENWOODVILLAGE,
    ASSET_LEVELMODEL_SPACEDUSTALLEY,
    ASSET_LEVELMODEL_TITLESCREEN,
    ASSET_LEVELMODEL_BOULDERCANYON,
    ASSET_LEVELMODEL_WINDMILLPLAINS,
    ASSET_LEVELMODEL_SNOWFLAKEMOUNTAINHUB,
    ASSET_LEVELMODEL_SMOKEYCASTLE,
    ASSET_LEVELMODEL_DARKWATERBEACH,
    ASSET_LEVELMODEL_ICICLEPYRAMID,
    ASSET_LEVELMODEL_FROSTYVILLAGE,
    ASSET_LEVELMODEL_JUNGLEFALLS,
    ASSET_LEVELMODEL_TREASURECAVES,
    ASSET_LEVELMODEL_HAUNTEDWOODS,
    ASSET_LEVELMODEL_DARKMOONCAVERNS,
    ASSET_LEVELMODEL_STARCITY,
    ASSET_LEVELMODEL_TROPHYRACE,
    ASSET_LEVELMODEL_FUTUREFUNLANDHUB,
    ASSET_LEVELMODEL_INTROSEQUENCE,
    ASSET_LEVELMODEL_SMOKEY,
    ASSET_LEVELMODEL_TRICKYTOPS,
    ASSET_LEVELMODEL_WIZPIGMOUTHSEQUENCE,
    ASSET_LEVELMODEL_ROCKETSEQUENCE,
    ASSET_LEVELMODEL_WIZPIG1,
    ASSET_LEVELMODEL_OCEANTRACK,
    ASSET_LEVELMODEL_VOLCANOTRACK,
    ASSET_LEVELMODEL_SNOWMOUNTAINTRACK,
    ASSET_LEVELMODEL_PARTYSEQUENCE,
    ASSET_LEVELMODEL_BLUEYANIMATION,
    ASSET_LEVELMODEL_WIZPIG1ANIMATION,
    ASSET_LEVELMODEL_BUBBLER,
    ASSET_LEVELMODEL_BUBBLERANIMATION,
    ASSET_LEVELMODEL_WIZPIG2ANIMATION,
    ASSET_LEVELMODEL_WIZPIG2,
    ASSET_LEVELMODEL_ENDINGPART1,
    ASSET_LEVELMODEL_ENDINGPART2,
    ASSET_LEVEL_MODELS_COUNT
} AssetLevelModelsEnum;
typedef enum AssetObjectModelsEnum {
    ASSET_OBJECTMODEL_DOME,
    ASSET_OBJECTMODEL_DOME1,
    ASSET_OBJECTMODEL_DOME2,
    ASSET_OBJECTMODEL_DOME3,
    ASSET_OBJECTMODEL_DOME4,
    ASSET_OBJECTMODEL_DOME5,
    ASSET_OBJECTMODEL_DOME6,
    ASSET_OBJECTMODEL_DOME7,
    ASSET_OBJECTMODEL_DOME8,
    ASSET_OBJECTMODEL_DOME9,
    ASSET_OBJECTMODEL_DOME10,
    ASSET_OBJECTMODEL_DOME11,
    ASSET_OBJECTMODEL_DOME12,
    ASSET_OBJECTMODEL_DOME13,
    ASSET_OBJECTMODEL_DOME14,
    ASSET_OBJECTMODEL_DOME15,
    ASSET_OBJECTMODEL_DOME16,
    ASSET_OBJECTMODEL_DOME17,
    ASSET_OBJECTMODEL_FIRSTPLACE,
    ASSET_OBJECTMODEL_DIDDYCAR_0,
    ASSET_OBJECTMODEL_DIDDYCAR_1,
    ASSET_OBJECTMODEL_DIDDYCAR_2,
    ASSET_OBJECTMODEL_DIDDYCAR_3,
    ASSET_OBJECTMODEL_DIDDYCAR_4,
    ASSET_OBJECTMODEL_DIDDYCAR_5,
    ASSET_OBJECTMODEL_SWCAR_0,
    ASSET_OBJECTMODEL_SWCAR_1,
    ASSET_OBJECTMODEL_SWCAR_2,
    ASSET_OBJECTMODEL_SWCAR_3,
    ASSET_OBJECTMODEL_SWCAR_4,
    ASSET_OBJECTMODEL_SWCAR_5,
    ASSET_OBJECTMODEL_BADGERCAR_0,
    ASSET_OBJECTMODEL_BADGERCAR_1,
    ASSET_OBJECTMODEL_BADGERCAR_2,
    ASSET_OBJECTMODEL_BADGERCAR_3,
    ASSET_OBJECTMODEL_BADGERCAR_4,
    ASSET_OBJECTMODEL_BADGERCAR_5,
    ASSET_OBJECTMODEL_TORTCAR_0,
    ASSET_OBJECTMODEL_TORTCAR_1,
    ASSET_OBJECTMODEL_TORTCAR_2,
    ASSET_OBJECTMODEL_TORTCAR_3,
    ASSET_OBJECTMODEL_TORTCAR_4,
    ASSET_OBJECTMODEL_TORTCAR_5,
    ASSET_OBJECTMODEL_KREMCAR_0,
    ASSET_OBJECTMODEL_KREMCAR_1,
    ASSET_OBJECTMODEL_KREMCAR_2,
    ASSET_OBJECTMODEL_KREMCAR_3,
    ASSET_OBJECTMODEL_KREMCAR_4,
    ASSET_OBJECTMODEL_KREMCAR_5,
    ASSET_OBJECTMODEL_TIGERCAR_0,
    ASSET_OBJECTMODEL_TIGERCAR_1,
    ASSET_OBJECTMODEL_TIGERCAR_2,
    ASSET_OBJECTMODEL_TIGERCAR_3,
    ASSET_OBJECTMODEL_TIGERCAR_4,
    ASSET_OBJECTMODEL_TIGERCAR_5,
    ASSET_OBJECTMODEL_CONKACAR_0,
    ASSET_OBJECTMODEL_CONKACAR_1,
    ASSET_OBJECTMODEL_CONKACAR_2,
    ASSET_OBJECTMODEL_CONKACAR_3,
    ASSET_OBJECTMODEL_CONKACAR_4,
    ASSET_OBJECTMODEL_CONKACAR_5,
    ASSET_OBJECTMODEL_BANJOCAR_0,
    ASSET_OBJECTMODEL_BANJOCAR_1,
    ASSET_OBJECTMODEL_BANJOCAR_2,
    ASSET_OBJECTMODEL_BANJOCAR_3,
    ASSET_OBJECTMODEL_BANJOCAR_4,
    ASSET_OBJECTMODEL_BANJOCAR_5,
    ASSET_OBJECTMODEL_CHICKENCAR_0,
    ASSET_OBJECTMODEL_CHICKENCAR_1,
    ASSET_OBJECTMODEL_CHICKENCAR_2,
    ASSET_OBJECTMODEL_CHICKENCAR_3,
    ASSET_OBJECTMODEL_CHICKENCAR_4,
    ASSET_OBJECTMODEL_CHICKENCAR_5,
    ASSET_OBJECTMODEL_MOUSECAR_0,
    ASSET_OBJECTMODEL_MOUSECAR_1,
    ASSET_OBJECTMODEL_MOUSECAR_2,
    ASSET_OBJECTMODEL_MOUSECAR_3,
    ASSET_OBJECTMODEL_MOUSECAR_4,
    ASSET_OBJECTMODEL_MOUSECAR_5,
    ASSET_OBJECTMODEL_TICKTOCKHOVER_0,
    ASSET_OBJECTMODEL_TICKTOCKHOVER_1,
    ASSET_OBJECTMODEL_TICKTOCKHOVER_2,
    ASSET_OBJECTMODEL_TICKTOCKHOVER_3,
    ASSET_OBJECTMODEL_TICKTOCKHOVER_4,
    ASSET_OBJECTMODEL_TICKTOCKHOVER_5,
    ASSET_OBJECTMODEL_KREMLINHOVER_0,
    ASSET_OBJECTMODEL_KREMLINHOVER_1,
    ASSET_OBJECTMODEL_KREMLINHOVER_2,
    ASSET_OBJECTMODEL_KREMLINHOVER_3,
    ASSET_OBJECTMODEL_KREMLINHOVER_4,
    ASSET_OBJECTMODEL_KREMLINHOVER_5,
    ASSET_OBJECTMODEL_BADGERHOVER_0,
    ASSET_OBJECTMODEL_BADGERHOVER_1,
    ASSET_OBJECTMODEL_BADGERHOVER_2,
    ASSET_OBJECTMODEL_BADGERHOVER_3,
    ASSET_OBJECTMODEL_BADGERHOVER_4,
    ASSET_OBJECTMODEL_BADGERHOVER_5,
    ASSET_OBJECTMODEL_CONKAHOVER_0,
    ASSET_OBJECTMODEL_CONKAHOVER_1,
    ASSET_OBJECTMODEL_CONKAHOVER_2,
    ASSET_OBJECTMODEL_CONKAHOVER_3,
    ASSET_OBJECTMODEL_CONKAHOVER_4,
    ASSET_OBJECTMODEL_CONKAHOVER_5,
    ASSET_OBJECTMODEL_TORTHOVER_0,
    ASSET_OBJECTMODEL_TORTHOVER_1,
    ASSET_OBJECTMODEL_TORTHOVER_2,
    ASSET_OBJECTMODEL_TORTHOVER_3,
    ASSET_OBJECTMODEL_TORTHOVER_4,
    ASSET_OBJECTMODEL_TORTHOVER_5,
    ASSET_OBJECTMODEL_BANJOHOVER_0,
    ASSET_OBJECTMODEL_BANJOHOVER_1,
    ASSET_OBJECTMODEL_BANJOHOVER_2,
    ASSET_OBJECTMODEL_BANJOHOVER_3,
    ASSET_OBJECTMODEL_BANJOHOVER_4,
    ASSET_OBJECTMODEL_BANJOHOVER_5,
    ASSET_OBJECTMODEL_TIGERHOVER_0,
    ASSET_OBJECTMODEL_TIGERHOVER_1,
    ASSET_OBJECTMODEL_TIGERHOVER_2,
    ASSET_OBJECTMODEL_TIGERHOVER_3,
    ASSET_OBJECTMODEL_TIGERHOVER_4,
    ASSET_OBJECTMODEL_TIGERHOVER_5,
    ASSET_OBJECTMODEL_CHICKENHOVER_0,
    ASSET_OBJECTMODEL_CHICKENHOVER_1,
    ASSET_OBJECTMODEL_CHICKENHOVER_2,
    ASSET_OBJECTMODEL_CHICKENHOVER_3,
    ASSET_OBJECTMODEL_CHICKENHOVER_4,
    ASSET_OBJECTMODEL_CHICKENHOVER_5,
    ASSET_OBJECTMODEL_MOUSEHOVER_0,
    ASSET_OBJECTMODEL_MOUSEHOVER_1,
    ASSET_OBJECTMODEL_MOUSEHOVER_2,
    ASSET_OBJECTMODEL_MOUSEHOVER_3,
    ASSET_OBJECTMODEL_MOUSEHOVER_4,
    ASSET_OBJECTMODEL_MOUSEHOVER_5,
    ASSET_OBJECTMODEL_DIDDYHOVER_0,
    ASSET_OBJECTMODEL_DIDDYHOVER_1,
    ASSET_OBJECTMODEL_DIDDYHOVER_2,
    ASSET_OBJECTMODEL_DIDDYHOVER_3,
    ASSET_OBJECTMODEL_DIDDYHOVER_4,
    ASSET_OBJECTMODEL_DIDDYHOVER_5,
    ASSET_OBJECTMODEL_DIDDYPLANE_0,
    ASSET_OBJECTMODEL_DIDDYPLANE_1,
    ASSET_OBJECTMODEL_DIDDYPLANE_2,
    ASSET_OBJECTMODEL_DIDDYPLANE_3,
    ASSET_OBJECTMODEL_DIDDYPLANE_4,
    ASSET_OBJECTMODEL_DIDDYPLANE_5,
    ASSET_OBJECTMODEL_TIGERANIMPLANE,
    ASSET_OBJECTMODEL_TICKTOCKPLANE_0,
    ASSET_OBJECTMODEL_TICKTOCKPLANE_1,
    ASSET_OBJECTMODEL_TICKTOCKPLANE_2,
    ASSET_OBJECTMODEL_TICKTOCKPLANE_3,
    ASSET_OBJECTMODEL_TICKTOCKPLANE_4,
    ASSET_OBJECTMODEL_TICKTOCKPLANE_5,
    ASSET_OBJECTMODEL_KREMPLANE_0,
    ASSET_OBJECTMODEL_KREMPLANE_1,
    ASSET_OBJECTMODEL_KREMPLANE_2,
    ASSET_OBJECTMODEL_KREMPLANE_3,
    ASSET_OBJECTMODEL_KREMPLANE_4,
    ASSET_OBJECTMODEL_KREMPLANE_5,
    ASSET_OBJECTMODEL_BADGERPLANE_0,
    ASSET_OBJECTMODEL_BADGERPLANE_1,
    ASSET_OBJECTMODEL_BADGERPLANE_2,
    ASSET_OBJECTMODEL_BADGERPLANE_3,
    ASSET_OBJECTMODEL_BADGERPLANE_4,
    ASSET_OBJECTMODEL_BADGERPLANE_5,
    ASSET_OBJECTMODEL_TORTPLANE_0,
    ASSET_OBJECTMODEL_TORTPLANE_1,
    ASSET_OBJECTMODEL_TORTPLANE_2,
    ASSET_OBJECTMODEL_TORTPLANE_3,
    ASSET_OBJECTMODEL_TORTPLANE_4,
    ASSET_OBJECTMODEL_TORTPLANE_5,
    ASSET_OBJECTMODEL_CONKA_0,
    ASSET_OBJECTMODEL_CONKA_1,
    ASSET_OBJECTMODEL_CONKA_2,
    ASSET_OBJECTMODEL_CONKA_3,
    ASSET_OBJECTMODEL_CONKA_4,
    ASSET_OBJECTMODEL_CONKA_5,
    ASSET_OBJECTMODEL_TIGPLANE_0,
    ASSET_OBJECTMODEL_TIGPLANE_1,
    ASSET_OBJECTMODEL_TIGPLANE_2,
    ASSET_OBJECTMODEL_TIGPLANE_3,
    ASSET_OBJECTMODEL_TIGPLANE_4,
    ASSET_OBJECTMODEL_TIGPLANE_5,
    ASSET_OBJECTMODEL_BANJOPLANE_0,
    ASSET_OBJECTMODEL_BANJOPLANE_1,
    ASSET_OBJECTMODEL_BANJOPLANE_2,
    ASSET_OBJECTMODEL_BANJOPLANE_3,
    ASSET_OBJECTMODEL_BANJOPLANE_4,
    ASSET_OBJECTMODEL_BANJOPLANE_5,
    ASSET_OBJECTMODEL_CHICKENPLANE_0,
    ASSET_OBJECTMODEL_CHICKENPLANE_1,
    ASSET_OBJECTMODEL_CHICKENPLANE_2,
    ASSET_OBJECTMODEL_CHICKENPLANE_3,
    ASSET_OBJECTMODEL_CHICKENPLANE_4,
    ASSET_OBJECTMODEL_CHICKENPLANE_5,
    ASSET_OBJECTMODEL_MOUSEPLANE_0,
    ASSET_OBJECTMODEL_MOUSEPLANE_1,
    ASSET_OBJECTMODEL_MOUSEPLANE_2,
    ASSET_OBJECTMODEL_MOUSEPLANE_3,
    ASSET_OBJECTMODEL_MOUSEPLANE_4,
    ASSET_OBJECTMODEL_MOUSEPLANE_5,
    ASSET_OBJECTMODEL_EMPTYPLANE,
    ASSET_OBJECTMODEL_EMPTYCAR,
    ASSET_OBJECTMODEL_EMPTYHOVER,
    ASSET_OBJECTMODEL_MAGICCARPET,
    ASSET_OBJECTMODEL_POLYGOLDBALOON_0,
    ASSET_OBJECTMODEL_POLYGOLDBALOON_1,
    ASSET_OBJECTMODEL_STOPWATCHMAN,
    ASSET_OBJECTMODEL_STOPWATCHSELECT,
    ASSET_OBJECTMODEL_PARKWARDEN,
    ASSET_OBJECTMODEL_ANIMGENIE2,
    ASSET_OBJECTMODEL_GENIEHEAD,
    ASSET_OBJECTMODEL_PIGBOSS,
    ASSET_OBJECTMODEL_PIGBOSS2,
    ASSET_OBJECTMODEL_WIZPIG,
    ASSET_OBJECTMODEL_PIGROCKETEER,
    ASSET_OBJECTMODEL_WIZPIGROCKET,
    ASSET_OBJECTMODEL_ROCKETBIT1,
    ASSET_OBJECTMODEL_ROCKETBIT2,
    ASSET_OBJECTMODEL_PIGBOULDER,
    ASSET_OBJECTMODEL_PIGBOULDER2,
    ASSET_OBJECTMODEL_PIGBOULDER3,
    ASSET_OBJECTMODEL_PIGBOULDER4,
    ASSET_OBJECTMODEL_PIGBOULDER5,
    ASSET_OBJECTMODEL_BIGPLANET,
    ASSET_OBJECTMODEL_WIZPIGSHIP,
    ASSET_OBJECTMODEL_TRICKYTOPS,
    ASSET_OBJECTMODEL_TRICKYANIM,
    ASSET_OBJECTMODEL_TRICKYANIM2,
    ASSET_OBJECTMODEL_TRICKYANIM3,
    ASSET_OBJECTMODEL_DRAGONBOSS,
    ASSET_OBJECTMODEL_DRAGONANIM,
    ASSET_OBJECTMODEL_TERRYBOSS,
    ASSET_OBJECTMODEL_WALRUS,
    ASSET_OBJECTMODEL_WALRUS_ANIM,
    ASSET_OBJECTMODEL_OCTOPUS,
    ASSET_OBJECTMODEL_STOPWATCHICON,
    ASSET_OBJECTMODEL_STOPWATCHHAND,
    ASSET_OBJECTMODEL_SNOWBALL,
    ASSET_OBJECTMODEL_SNOWBALL2,
    ASSET_OBJECTMODEL_DINOSAUR1,
    ASSET_OBJECTMODEL_DINOSAUR2,
    ASSET_OBJECTMODEL_DINOSAUR3,
    ASSET_OBJECTMODEL_SEAMONSTER,
    ASSET_OBJECTMODEL_WOODBLOCK,
    ASSET_OBJECTMODEL_WHALE,
    ASSET_OBJECTMODEL_LEVELDOOR_2,
    ASSET_OBJECTMODEL_LEVELDOOR_3,
    ASSET_OBJECTMODEL_LEVELDOOR_0,
    ASSET_OBJECTMODEL_LEVELDOOR_4,
    ASSET_OBJECTMODEL_LEVELDOOR_1,
    ASSET_OBJECTMODEL_LEVELDOOR_7,
    ASSET_OBJECTMODEL_LEVELDOOR_8,
    ASSET_OBJECTMODEL_LEVELDOOR_5,
    ASSET_OBJECTMODEL_LEVELDOOR_6,
    ASSET_OBJECTMODEL_SIGNS_0,
    ASSET_OBJECTMODEL_SIGNS_1,
    ASSET_OBJECTMODEL_SIGNS_2,
    ASSET_OBJECTMODEL_SIGNS_3,
    ASSET_OBJECTMODEL_LOG,
    ASSET_OBJECTMODEL_BOULDER,
    ASSET_OBJECTMODEL_AIRZIPPERS,
    ASSET_OBJECTMODEL_WATERZIPPERS,
    ASSET_OBJECTMODEL_GROUNDZIPPER2,
    ASSET_OBJECTMODEL_BETAAIRZIPPER,
    ASSET_OBJECTMODEL_DINOISLE,
    ASSET_OBJECTMODEL_BETABUMPERICON,
    ASSET_OBJECTMODEL_BETADRUMSTICKICON,
    ASSET_OBJECTMODEL_BETAKRUNCHICON,
    ASSET_OBJECTMODEL_BETAPIPSYICON,
    ASSET_OBJECTMODEL_BETATIPTUPICON,
    ASSET_OBJECTMODEL_BETAKRUNCHBALLOON,
    ASSET_OBJECTMODEL_BETABUMPERBALLOON,
    ASSET_OBJECTMODEL_BETATIPTUPBALLOON,
    ASSET_OBJECTMODEL_BETATIMBERBALLOON,
    ASSET_OBJECTMODEL_BETABANJOBALLOON,
    ASSET_OBJECTMODEL_BETADRUMSTICKBALLOON,
    ASSET_OBJECTMODEL_BETAPIPSYBALLOON,
    ASSET_OBJECTMODEL_SELECTIONSHADOW,
    ASSET_OBJECTMODEL_BETAPLAYER1BALLOON,
    ASSET_OBJECTMODEL_BETAPLAYER2BALLOON,
    ASSET_OBJECTMODEL_BETAPLAYER3BALLOON,
    ASSET_OBJECTMODEL_BETAPLAYER4BALLOON,
    ASSET_OBJECTMODEL_BADGERANIMWALK,
    ASSET_OBJECTMODEL_TIMBERDANCER,
    ASSET_OBJECTMODEL_TIPTUPDANCER,
    ASSET_OBJECTMODEL_RAREWARELOGO,
    ASSET_OBJECTMODEL_FROG_0,
    ASSET_OBJECTMODEL_FROG_1,
    ASSET_OBJECTMODEL_CHECKPOINT,
    ASSET_OBJECTMODEL_MIDIFADE,
    ASSET_OBJECTMODEL_MODECHANGE,
    ASSET_OBJECTMODEL_EXIT,
    ASSET_OBJECTMODEL_BONUS,
    ASSET_OBJECTMODEL_ANIMCAMERA,
    ASSET_OBJECTMODEL_ANIMATION,
    ASSET_OBJECTMODEL_RGBALIGHT_0,
    ASSET_OBJECTMODEL_RGBALIGHT_1,
    ASSET_OBJECTMODEL_RGBALIGHT_2,
    ASSET_OBJECTMODEL_RGBALIGHT_3,
    ASSET_OBJECTMODEL_N64LOGO,
    ASSET_OBJECTMODEL_WIDESCREEN,
    ASSET_OBJECTMODEL_ANIMDOME,
    ASSET_OBJECTMODEL_DIDDYSELECT,
    ASSET_OBJECTMODEL_ELECTRICITY,
    ASSET_OBJECTMODEL_KREMSELECT,
    ASSET_OBJECTMODEL_BADGERSELECT,
    ASSET_OBJECTMODEL_TORTSELECT,
    ASSET_OBJECTMODEL_BANJOSELECT,
    ASSET_OBJECTMODEL_TIGERSELECT,
    ASSET_OBJECTMODEL_CHICKSELECT,
    ASSET_OBJECTMODEL_MOUSESELECT,
    ASSET_OBJECTMODEL_CONKSELECT,
    ASSET_OBJECTMODEL_POSTFORPARTY,
    ASSET_OBJECTMODEL_LIGHTHOUSE,
    ASSET_OBJECTMODEL_LIGHTHOUSE1,
    ASSET_OBJECTMODEL_SELECTIONHILL,
    ASSET_OBJECTMODEL_RARELOGO,
    ASSET_OBJECTMODEL_WORLDKEY,
    ASSET_OBJECTMODEL_ANIMKEY,
    ASSET_OBJECTMODEL_ROCKETSIGNPOST_0,
    ASSET_OBJECTMODEL_ROCKETSIGNPOST_1,
    ASSET_OBJECTMODEL_ROCKETSIGNPOST_2,
    ASSET_OBJECTMODEL_ROCKETSIGNPOST_3,
    ASSET_OBJECTMODEL_ROCKETSIGNPOST_4,
    ASSET_OBJECTMODEL_MAGICRING,
    ASSET_OBJECTMODEL_LEEFAN,
    ASSET_OBJECTMODEL_SPACESHIP1,
    ASSET_OBJECTMODEL_SPACESHIP2,
    ASSET_OBJECTMODEL_SPACESHIP3,
    ASSET_OBJECTMODEL_MONORAIL,
    ASSET_OBJECTMODEL_BRIDGE,
    ASSET_OBJECTMODEL_PIRATESHIP,
    ASSET_OBJECTMODEL_WORLDGATE_0,
    ASSET_OBJECTMODEL_WORLDGATE_1,
    ASSET_OBJECTMODEL_WORLDGATE_2,
    ASSET_OBJECTMODEL_WORLDGATE_3,
    ASSET_OBJECTMODEL_BIGBOSSDOOR_0,
    ASSET_OBJECTMODEL_BIGBOSSDOOR_1,
    ASSET_OBJECTMODEL_CHALDOOR_0,
    ASSET_OBJECTMODEL_CHALDOOR_1,
    ASSET_OBJECTMODEL_BOSSDOOR_0,
    ASSET_OBJECTMODEL_BOSSDOOR_1,
    ASSET_OBJECTMODEL_BOSSDOOR_2,
    ASSET_OBJECTMODEL_SPACECOLUMN1,
    ASSET_OBJECTMODEL_SPACECOLUMN2,
    ASSET_OBJECTMODEL_SPACECOLUMN3,
    ASSET_OBJECTMODEL_TRACKSELECTFRAME,
    ASSET_OBJECTMODEL_WINDSAIL,
    ASSET_OBJECTMODEL_EFFECTBOX,
    ASSET_OBJECTMODEL_ASTEROID,
    ASSET_OBJECTMODEL_TROPHYCAB,
    ASSET_OBJECTMODEL_LASERBOLT,
    ASSET_OBJECTMODEL_TRACKSELECTFRAMEUNKNOWN,
    ASSET_OBJECTMODEL_TRACKSELECTFRAMECHALLENGE,
    ASSET_OBJECTMODEL_TRACKSELECTFRAMETROPHYRACE,
    ASSET_OBJECTMODEL_LETTER,
    ASSET_OBJECTMODEL_PIGHEADCOLOURS_0,
    ASSET_OBJECTMODEL_PIGHEADCOLOURS_1,
    ASSET_OBJECTMODEL_PIGHEADCOLOURS_2,
    ASSET_OBJECTMODEL_PIGHEADCOLOURS_3,
    ASSET_OBJECTMODEL_PIGHEADCOLOURS_4,
    ASSET_OBJECTMODEL_PTERODACTYL,
    ASSET_OBJECTMODEL_AMULETPIECE1,
    ASSET_OBJECTMODEL_AMULETPIECE2,
    ASSET_OBJECTMODEL_AMULETPIECE3,
    ASSET_OBJECTMODEL_AMULETPIECE4,
    ASSET_OBJECTMODEL_SWAMULET1,
    ASSET_OBJECTMODEL_SWAMULET2,
    ASSET_OBJECTMODEL_SWAMULET3,
    ASSET_OBJECTMODEL_SWAMULET4,
    ASSET_OBJECTMODEL_PIGFACEANIMATOR,
    ASSET_OBJECTMODEL_PILLAR,
    ASSET_OBJECTMODEL_BOULDERANIM,
    ASSET_OBJECTMODEL_HAYSTACK,
    ASSET_OBJECTMODEL_BETAPROAM64HOTAIRBALLOON,
    ASSET_OBJECTMODEL_MINISHIP,
    ASSET_OBJECTMODEL_GOLDTROPHY,
    ASSET_OBJECTMODEL_PARKTROPHY,
    ASSET_OBJECTMODEL_TICKTROPHY,
    ASSET_OBJECTMODEL_SPACEDOME,
    ASSET_OBJECTMODEL_MISSILE,
    ASSET_OBJECTMODEL_SHIELD_1,
    ASSET_OBJECTMODEL_SHIELD_0,
    ASSET_OBJECTMODEL_SHIELD_2,
    ASSET_OBJECTMODEL_TTDOOR_0,
    ASSET_OBJECTMODEL_TTDOOR_1,
    ASSET_OBJECTMODEL_TTDOOR_2,
    ASSET_OBJECTMODEL_PIGLOG,
    ASSET_OBJECTMODEL_KEITHPIGDOOR,
    ASSET_OBJECTMODEL_MAGNETFX,
    ASSET_OBJECT_MODELS_COUNT
} AssetObjectModelsEnum;
typedef enum AssetObjectAnimationsEnum {
    ASSET_OBJECT_ANIMATIONS_0,
    ASSET_OBJECT_ANIMATIONS_1,
    ASSET_OBJECT_ANIMATIONS_2,
    ASSET_OBJECT_ANIMATIONS_3,
    ASSET_OBJECT_ANIMATIONS_4,
    ASSET_OBJECT_ANIMATIONS_5,
    ASSET_OBJECT_ANIMATIONS_6,
    ASSET_OBJECT_ANIMATIONS_7,
    ASSET_OBJECT_ANIMATIONS_8,
    ASSET_OBJECT_ANIMATIONS_9,
    ASSET_OBJECT_ANIMATIONS_10,
    ASSET_OBJECT_ANIMATIONS_11,
    ASSET_OBJECT_ANIMATIONS_12,
    ASSET_OBJECT_ANIMATIONS_13,
    ASSET_OBJECT_ANIMATIONS_14,
    ASSET_OBJECT_ANIMATIONS_15,
    ASSET_OBJECT_ANIMATIONS_16,
    ASSET_OBJECT_ANIMATIONS_17,
    ASSET_OBJECT_ANIMATIONS_18,
    ASSET_OBJECT_ANIMATIONS_19,
    ASSET_OBJECT_ANIMATIONS_20,
    ASSET_OBJECT_ANIMATIONS_21,
    ASSET_OBJECT_ANIMATIONS_22,
    ASSET_OBJECT_ANIMATIONS_23,
    ASSET_OBJECT_ANIMATIONS_24,
    ASSET_OBJECT_ANIMATIONS_25,
    ASSET_OBJECT_ANIMATIONS_26,
    ASSET_OBJECT_ANIMATIONS_27,
    ASSET_OBJECT_ANIMATIONS_28,
    ASSET_OBJECT_ANIMATIONS_29,
    ASSET_OBJECT_ANIMATIONS_30,
    ASSET_OBJECT_ANIMATIONS_31,
    ASSET_OBJECT_ANIMATIONS_32,
    ASSET_OBJECT_ANIMATIONS_33,
    ASSET_OBJECT_ANIMATIONS_34,
    ASSET_OBJECT_ANIMATIONS_35,
    ASSET_OBJECT_ANIMATIONS_36,
    ASSET_OBJECT_ANIMATIONS_37,
    ASSET_OBJECT_ANIMATIONS_38,
    ASSET_OBJECT_ANIMATIONS_39,
    ASSET_OBJECT_ANIMATIONS_40,
    ASSET_OBJECT_ANIMATIONS_41,
    ASSET_OBJECT_ANIMATIONS_42,
    ASSET_OBJECT_ANIMATIONS_43,
    ASSET_OBJECT_ANIMATIONS_44,
    ASSET_OBJECT_ANIMATIONS_45,
    ASSET_OBJECT_ANIMATIONS_46,
    ASSET_OBJECT_ANIMATIONS_47,
    ASSET_OBJECT_ANIMATIONS_48,
    ASSET_OBJECT_ANIMATIONS_49,
    ASSET_OBJECT_ANIMATIONS_50,
    ASSET_OBJECT_ANIMATIONS_51,
    ASSET_OBJECT_ANIMATIONS_52,
    ASSET_OBJECT_ANIMATIONS_53,
    ASSET_OBJECT_ANIMATIONS_54,
    ASSET_OBJECT_ANIMATIONS_55,
    ASSET_OBJECT_ANIMATIONS_56,
    ASSET_OBJECT_ANIMATIONS_57,
    ASSET_OBJECT_ANIMATIONS_58,
    ASSET_OBJECT_ANIMATIONS_59,
    ASSET_OBJECT_ANIMATIONS_60,
    ASSET_OBJECT_ANIMATIONS_61,
    ASSET_OBJECT_ANIMATIONS_62,
    ASSET_OBJECT_ANIMATIONS_63,
    ASSET_OBJECT_ANIMATIONS_64,
    ASSET_OBJECT_ANIMATIONS_65,
    ASSET_OBJECT_ANIMATIONS_66,
    ASSET_OBJECT_ANIMATIONS_67,
    ASSET_OBJECT_ANIMATIONS_68,
    ASSET_OBJECT_ANIMATIONS_69,
    ASSET_OBJECT_ANIMATIONS_70,
    ASSET_OBJECT_ANIMATIONS_71,
    ASSET_OBJECT_ANIMATIONS_72,
    ASSET_OBJECT_ANIMATIONS_73,
    ASSET_OBJECT_ANIMATIONS_74,
    ASSET_OBJECT_ANIMATIONS_75,
    ASSET_OBJECT_ANIMATIONS_76,
    ASSET_OBJECT_ANIMATIONS_77,
    ASSET_OBJECT_ANIMATIONS_78,
    ASSET_OBJECT_ANIMATIONS_79,
    ASSET_OBJECT_ANIMATIONS_80,
    ASSET_OBJECT_ANIMATIONS_81,
    ASSET_OBJECT_ANIMATIONS_82,
    ASSET_OBJECT_ANIMATIONS_83,
    ASSET_OBJECT_ANIMATIONS_84,
    ASSET_OBJECT_ANIMATIONS_85,
    ASSET_OBJECT_ANIMATIONS_86,
    ASSET_OBJECT_ANIMATIONS_87,
    ASSET_OBJECT_ANIMATIONS_88,
    ASSET_OBJECT_ANIMATIONS_89,
    ASSET_OBJECT_ANIMATIONS_90,
    ASSET_OBJECT_ANIMATIONS_91,
    ASSET_OBJECT_ANIMATIONS_92,
    ASSET_OBJECT_ANIMATIONS_93,
    ASSET_OBJECT_ANIMATIONS_94,
    ASSET_OBJECT_ANIMATIONS_95,
    ASSET_OBJECT_ANIMATIONS_96,
    ASSET_OBJECT_ANIMATIONS_97,
    ASSET_OBJECT_ANIMATIONS_98,
    ASSET_OBJECT_ANIMATIONS_99,
    ASSET_OBJECT_ANIMATIONS_100,
    ASSET_OBJECT_ANIMATIONS_101,
    ASSET_OBJECT_ANIMATIONS_102,
    ASSET_OBJECT_ANIMATIONS_103,
    ASSET_OBJECT_ANIMATIONS_104,
    ASSET_OBJECT_ANIMATIONS_105,
    ASSET_OBJECT_ANIMATIONS_106,
    ASSET_OBJECT_ANIMATIONS_107,
    ASSET_OBJECT_ANIMATIONS_108,
    ASSET_OBJECT_ANIMATIONS_109,
    ASSET_OBJECT_ANIMATIONS_110,
    ASSET_OBJECT_ANIMATIONS_111,
    ASSET_OBJECT_ANIMATIONS_112,
    ASSET_OBJECT_ANIMATIONS_113,
    ASSET_OBJECT_ANIMATIONS_114,
    ASSET_OBJECT_ANIMATIONS_115,
    ASSET_OBJECT_ANIMATIONS_116,
    ASSET_OBJECT_ANIMATIONS_117,
    ASSET_OBJECT_ANIMATIONS_118,
    ASSET_OBJECT_ANIMATIONS_119,
    ASSET_OBJECT_ANIMATIONS_120,
    ASSET_OBJECT_ANIMATIONS_121,
    ASSET_OBJECT_ANIMATIONS_122,
    ASSET_OBJECT_ANIMATIONS_123,
    ASSET_OBJECT_ANIMATIONS_124,
    ASSET_OBJECT_ANIMATIONS_125,
    ASSET_OBJECT_ANIMATIONS_126,
    ASSET_OBJECT_ANIMATIONS_127,
    ASSET_OBJECT_ANIMATIONS_128,
    ASSET_OBJECT_ANIMATIONS_129,
    ASSET_OBJECT_ANIMATIONS_130,
    ASSET_OBJECT_ANIMATIONS_131,
    ASSET_OBJECT_ANIMATIONS_132,
    ASSET_OBJECT_ANIMATIONS_133,
    ASSET_OBJECT_ANIMATIONS_134,
    ASSET_OBJECT_ANIMATIONS_135,
    ASSET_OBJECT_ANIMATIONS_136,
    ASSET_OBJECT_ANIMATIONS_137,
    ASSET_OBJECT_ANIMATIONS_138,
    ASSET_OBJECT_ANIMATIONS_139,
    ASSET_OBJECT_ANIMATIONS_140,
    ASSET_OBJECT_ANIMATIONS_141,
    ASSET_OBJECT_ANIMATIONS_142,
    ASSET_OBJECT_ANIMATIONS_143,
    ASSET_OBJECT_ANIMATIONS_144,
    ASSET_OBJECT_ANIMATIONS_145,
    ASSET_OBJECT_ANIMATIONS_146,
    ASSET_OBJECT_ANIMATIONS_147,
    ASSET_OBJECT_ANIMATIONS_148,
    ASSET_OBJECT_ANIMATIONS_149,
    ASSET_OBJECT_ANIMATIONS_150,
    ASSET_OBJECT_ANIMATIONS_151,
    ASSET_OBJECT_ANIMATIONS_152,
    ASSET_OBJECT_ANIMATIONS_153,
    ASSET_OBJECT_ANIMATIONS_154,
    ASSET_OBJECT_ANIMATIONS_155,
    ASSET_OBJECT_ANIMATIONS_156,
    ASSET_OBJECT_ANIMATIONS_157,
    ASSET_OBJECT_ANIMATIONS_158,
    ASSET_OBJECT_ANIMATIONS_159,
    ASSET_OBJECT_ANIMATIONS_160,
    ASSET_OBJECT_ANIMATIONS_161,
    ASSET_OBJECT_ANIMATIONS_162,
    ASSET_OBJECT_ANIMATIONS_163,
    ASSET_OBJECT_ANIMATIONS_164,
    ASSET_OBJECT_ANIMATIONS_165,
    ASSET_OBJECT_ANIMATIONS_166,
    ASSET_OBJECT_ANIMATIONS_167,
    ASSET_OBJECT_ANIMATIONS_168,
    ASSET_OBJECT_ANIMATIONS_169,
    ASSET_OBJECT_ANIMATIONS_170,
    ASSET_OBJECT_ANIMATIONS_171,
    ASSET_OBJECT_ANIMATIONS_172,
    ASSET_OBJECT_ANIMATIONS_173,
    ASSET_OBJECT_ANIMATIONS_174,
    ASSET_OBJECT_ANIMATIONS_175,
    ASSET_OBJECT_ANIMATIONS_176,
    ASSET_OBJECT_ANIMATIONS_177,
    ASSET_OBJECT_ANIMATIONS_178,
    ASSET_OBJECT_ANIMATIONS_179,
    ASSET_OBJECT_ANIMATIONS_180,
    ASSET_OBJECT_ANIMATIONS_181,
    ASSET_OBJECT_ANIMATIONS_182,
    ASSET_OBJECT_ANIMATIONS_183,
    ASSET_OBJECT_ANIMATIONS_184,
    ASSET_OBJECT_ANIMATIONS_185,
    ASSET_OBJECT_ANIMATIONS_186,
    ASSET_OBJECT_ANIMATIONS_187,
    ASSET_OBJECT_ANIMATIONS_188,
    ASSET_OBJECT_ANIMATIONS_189,
    ASSET_OBJECT_ANIMATIONS_190,
    ASSET_OBJECT_ANIMATIONS_191,
    ASSET_OBJECT_ANIMATIONS_192,
    ASSET_OBJECT_ANIMATIONS_193,
    ASSET_OBJECT_ANIMATIONS_194,
    ASSET_OBJECT_ANIMATIONS_195,
    ASSET_OBJECT_ANIMATIONS_196,
    ASSET_OBJECT_ANIMATIONS_197,
    ASSET_OBJECT_ANIMATIONS_198,
    ASSET_OBJECT_ANIMATIONS_199,
    ASSET_OBJECT_ANIMATIONS_200,
    ASSET_OBJECT_ANIMATIONS_201,
    ASSET_OBJECT_ANIMATIONS_202,
    ASSET_OBJECT_ANIMATIONS_203,
    ASSET_OBJECT_ANIMATIONS_204,
    ASSET_OBJECT_ANIMATIONS_205,
    ASSET_OBJECT_ANIMATIONS_206,
    ASSET_OBJECT_ANIMATIONS_207,
    ASSET_OBJECT_ANIMATIONS_208,
    ASSET_OBJECT_ANIMATIONS_209,
    ASSET_OBJECT_ANIMATIONS_210,
    ASSET_OBJECT_ANIMATIONS_211,
    ASSET_OBJECT_ANIMATIONS_212,
    ASSET_OBJECT_ANIMATIONS_213,
    ASSET_OBJECT_ANIMATIONS_214,
    ASSET_OBJECT_ANIMATIONS_215,
    ASSET_OBJECT_ANIMATIONS_216,
    ASSET_OBJECT_ANIMATIONS_217,
    ASSET_OBJECT_ANIMATIONS_218,
    ASSET_OBJECT_ANIMATIONS_219,
    ASSET_OBJECT_ANIMATIONS_220,
    ASSET_OBJECT_ANIMATIONS_221,
    ASSET_OBJECT_ANIMATIONS_222,
    ASSET_OBJECT_ANIMATIONS_223,
    ASSET_OBJECT_ANIMATIONS_224,
    ASSET_OBJECT_ANIMATIONS_225,
    ASSET_OBJECT_ANIMATIONS_226,
    ASSET_OBJECT_ANIMATIONS_227,
    ASSET_OBJECT_ANIMATIONS_228,
    ASSET_OBJECT_ANIMATIONS_229,
    ASSET_OBJECT_ANIMATIONS_230,
    ASSET_OBJECT_ANIMATIONS_231,
    ASSET_OBJECT_ANIMATIONS_232,
    ASSET_OBJECT_ANIMATIONS_233,
    ASSET_OBJECT_ANIMATIONS_234,
    ASSET_OBJECT_ANIMATIONS_235,
    ASSET_OBJECT_ANIMATIONS_236,
    ASSET_OBJECT_ANIMATIONS_237,
    ASSET_OBJECT_ANIMATIONS_238,
    ASSET_OBJECT_ANIMATIONS_239,
    ASSET_OBJECT_ANIMATIONS_240,
    ASSET_OBJECT_ANIMATIONS_241,
    ASSET_OBJECT_ANIMATIONS_242,
    ASSET_OBJECT_ANIMATIONS_243,
    ASSET_OBJECT_ANIMATIONS_244,
    ASSET_OBJECT_ANIMATIONS_245,
    ASSET_OBJECT_ANIMATIONS_246,
    ASSET_OBJECT_ANIMATIONS_247,
    ASSET_OBJECT_ANIMATIONS_248,
    ASSET_OBJECT_ANIMATIONS_249,
    ASSET_OBJECT_ANIMATIONS_250,
    ASSET_OBJECT_ANIMATIONS_251,
    ASSET_OBJECT_ANIMATIONS_252,
    ASSET_OBJECT_ANIMATIONS_253,
    ASSET_OBJECT_ANIMATIONS_254,
    ASSET_OBJECT_ANIMATIONS_255,
    ASSET_OBJECT_ANIMATIONS_256,
    ASSET_OBJECT_ANIMATIONS_257,
    ASSET_OBJECT_ANIMATIONS_258,
    ASSET_OBJECT_ANIMATIONS_259,
    ASSET_OBJECT_ANIMATIONS_260,
    ASSET_OBJECT_ANIMATIONS_261,
    ASSET_OBJECT_ANIMATIONS_262,
    ASSET_OBJECT_ANIMATIONS_263,
    ASSET_OBJECT_ANIMATIONS_264,
    ASSET_OBJECT_ANIMATIONS_265,
    ASSET_OBJECT_ANIMATIONS_266,
    ASSET_OBJECT_ANIMATIONS_267,
    ASSET_OBJECT_ANIMATIONS_268,
    ASSET_OBJECT_ANIMATIONS_269,
    ASSET_OBJECT_ANIMATIONS_270,
    ASSET_OBJECT_ANIMATIONS_271,
    ASSET_OBJECT_ANIMATIONS_272,
    ASSET_OBJECT_ANIMATIONS_273,
    ASSET_OBJECT_ANIMATIONS_274,
    ASSET_OBJECT_ANIMATIONS_275,
    ASSET_OBJECT_ANIMATIONS_276,
    ASSET_OBJECT_ANIMATIONS_277,
    ASSET_OBJECT_ANIMATIONS_278,
    ASSET_OBJECT_ANIMATIONS_279,
    ASSET_OBJECT_ANIMATIONS_280,
    ASSET_OBJECT_ANIMATIONS_281,
    ASSET_OBJECT_ANIMATIONS_282,
    ASSET_OBJECT_ANIMATIONS_283,
    ASSET_OBJECT_ANIMATIONS_284,
    ASSET_OBJECT_ANIMATIONS_285,
    ASSET_OBJECT_ANIMATIONS_286,
    ASSET_OBJECT_ANIMATIONS_287,
    ASSET_OBJECT_ANIMATIONS_288,
    ASSET_OBJECT_ANIMATIONS_289,
    ASSET_OBJECT_ANIMATIONS_290,
    ASSET_OBJECT_ANIMATIONS_291,
    ASSET_OBJECT_ANIMATIONS_292,
    ASSET_OBJECT_ANIMATIONS_293,
    ASSET_OBJECT_ANIMATIONS_294,
    ASSET_OBJECT_ANIMATIONS_295,
    ASSET_OBJECT_ANIMATIONS_296,
    ASSET_OBJECT_ANIMATIONS_297,
    ASSET_OBJECT_ANIMATIONS_298,
    ASSET_OBJECT_ANIMATIONS_299,
    ASSET_OBJECT_ANIMATIONS_300,
    ASSET_OBJECT_ANIMATIONS_301,
    ASSET_OBJECT_ANIMATIONS_302,
    ASSET_OBJECT_ANIMATIONS_303,
    ASSET_OBJECT_ANIMATIONS_304,
    ASSET_OBJECT_ANIMATIONS_305,
    ASSET_OBJECT_ANIMATIONS_306,
    ASSET_OBJECT_ANIMATIONS_307,
    ASSET_OBJECT_ANIMATIONS_308,
    ASSET_OBJECT_ANIMATIONS_309,
    ASSET_OBJECT_ANIMATIONS_310,
    ASSET_OBJECT_ANIMATIONS_311,
    ASSET_OBJECT_ANIMATIONS_312,
    ASSET_OBJECT_ANIMATIONS_313,
    ASSET_OBJECT_ANIMATIONS_314,
    ASSET_OBJECT_ANIMATIONS_315,
    ASSET_OBJECT_ANIMATIONS_316,
    ASSET_OBJECT_ANIMATIONS_317,
    ASSET_OBJECT_ANIMATIONS_318,
    ASSET_OBJECT_ANIMATIONS_319,
    ASSET_OBJECT_ANIMATIONS_320,
    ASSET_OBJECT_ANIMATIONS_321,
    ASSET_OBJECT_ANIMATIONS_322,
    ASSET_OBJECT_ANIMATIONS_323,
    ASSET_OBJECT_ANIMATIONS_324,
    ASSET_OBJECT_ANIMATIONS_325,
    ASSET_OBJECT_ANIMATIONS_326,
    ASSET_OBJECT_ANIMATIONS_327,
    ASSET_OBJECT_ANIMATIONS_328,
    ASSET_OBJECT_ANIMATIONS_329,
    ASSET_OBJECT_ANIMATIONS_330,
    ASSET_OBJECT_ANIMATIONS_331,
    ASSET_OBJECT_ANIMATIONS_332,
    ASSET_OBJECT_ANIMATIONS_333,
    ASSET_OBJECT_ANIMATIONS_334,
    ASSET_OBJECT_ANIMATIONS_335,
    ASSET_OBJECT_ANIMATIONS_336,
    ASSET_OBJECT_ANIMATIONS_337,
    ASSET_OBJECT_ANIMATIONS_338,
    ASSET_OBJECT_ANIMATIONS_339,
    ASSET_OBJECT_ANIMATIONS_340,
    ASSET_OBJECT_ANIMATIONS_341,
    ASSET_OBJECT_ANIMATIONS_342,
    ASSET_OBJECT_ANIMATIONS_343,
    ASSET_OBJECT_ANIMATIONS_344,
    ASSET_OBJECT_ANIMATIONS_345,
    ASSET_OBJECT_ANIMATIONS_346,
    ASSET_OBJECT_ANIMATIONS_347,
    ASSET_OBJECT_ANIMATIONS_348,
    ASSET_OBJECT_ANIMATIONS_349,
    ASSET_OBJECT_ANIMATIONS_350,
    ASSET_OBJECT_ANIMATIONS_351,
    ASSET_OBJECT_ANIMATIONS_352,
    ASSET_OBJECT_ANIMATIONS_353,
    ASSET_OBJECT_ANIMATIONS_354,
    ASSET_OBJECT_ANIMATIONS_355,
    ASSET_OBJECT_ANIMATIONS_356,
    ASSET_OBJECT_ANIMATIONS_357,
    ASSET_OBJECT_ANIMATIONS_358,
    ASSET_OBJECT_ANIMATIONS_359,
    ASSET_OBJECT_ANIMATIONS_360,
    ASSET_OBJECT_ANIMATIONS_361,
    ASSET_OBJECT_ANIMATIONS_362,
    ASSET_OBJECT_ANIMATIONS_363,
    ASSET_OBJECT_ANIMATIONS_364,
    ASSET_OBJECT_ANIMATIONS_365,
    ASSET_OBJECT_ANIMATIONS_366,
    ASSET_OBJECT_ANIMATIONS_367,
    ASSET_OBJECT_ANIMATIONS_368,
    ASSET_OBJECT_ANIMATIONS_369,
    ASSET_OBJECT_ANIMATIONS_370,
    ASSET_OBJECT_ANIMATIONS_371,
    ASSET_OBJECT_ANIMATIONS_372,
    ASSET_OBJECT_ANIMATIONS_373,
    ASSET_OBJECT_ANIMATIONS_374,
    ASSET_OBJECT_ANIMATIONS_375,
    ASSET_OBJECT_ANIMATIONS_376,
    ASSET_OBJECT_ANIMATIONS_377,
    ASSET_OBJECT_ANIMATIONS_378,
    ASSET_OBJECT_ANIMATIONS_379,
    ASSET_OBJECT_ANIMATIONS_380,
    ASSET_OBJECT_ANIMATIONS_381,
    ASSET_OBJECT_ANIMATIONS_382,
    ASSET_OBJECT_ANIMATIONS_383,
    ASSET_OBJECT_ANIMATIONS_384,
    ASSET_OBJECT_ANIMATIONS_385,
    ASSET_OBJECT_ANIMATIONS_386,
    ASSET_OBJECT_ANIMATIONS_387,
    ASSET_OBJECT_ANIMATIONS_388,
    ASSET_OBJECT_ANIMATIONS_389,
    ASSET_OBJECT_ANIMATIONS_390,
    ASSET_OBJECT_ANIMATIONS_391,
    ASSET_OBJECT_ANIMATIONS_392,
    ASSET_OBJECT_ANIMATIONS_393,
    ASSET_OBJECT_ANIMATIONS_394,
    ASSET_OBJECT_ANIMATIONS_395,
    ASSET_OBJECT_ANIMATIONS_396,
    ASSET_OBJECT_ANIMATIONS_397,
    ASSET_OBJECT_ANIMATIONS_398,
    ASSET_OBJECT_ANIMATIONS_399,
    ASSET_OBJECT_ANIMATIONS_400,
    ASSET_OBJECT_ANIMATIONS_401,
    ASSET_OBJECT_ANIMATIONS_402,
    ASSET_OBJECT_ANIMATIONS_403,
    ASSET_OBJECT_ANIMATIONS_404,
    ASSET_OBJECT_ANIMATIONS_405,
    ASSET_OBJECT_ANIMATIONS_406,
    ASSET_OBJECT_ANIMATIONS_407,
    ASSET_OBJECT_ANIMATIONS_408,
    ASSET_OBJECT_ANIMATIONS_409,
    ASSET_OBJECT_ANIMATIONS_410,
    ASSET_OBJECT_ANIMATIONS_411,
    ASSET_OBJECT_ANIMATIONS_412,
    ASSET_OBJECT_ANIMATIONS_413,
    ASSET_OBJECT_ANIMATIONS_414,
    ASSET_OBJECT_ANIMATIONS_415,
    ASSET_OBJECT_ANIMATIONS_416,
    ASSET_OBJECT_ANIMATIONS_417,
    ASSET_OBJECT_ANIMATIONS_418,
    ASSET_OBJECT_ANIMATIONS_419,
    ASSET_OBJECT_ANIMATIONS_420,
    ASSET_OBJECT_ANIMATIONS_421,
    ASSET_OBJECT_ANIMATIONS_422,
    ASSET_OBJECT_ANIMATIONS_423,
    ASSET_OBJECT_ANIMATIONS_424,
    ASSET_OBJECT_ANIMATIONS_425,
    ASSET_OBJECT_ANIMATIONS_426,
    ASSET_OBJECT_ANIMATIONS_427,
    ASSET_OBJECT_ANIMATIONS_428,
    ASSET_OBJECT_ANIMATIONS_429,
    ASSET_OBJECT_ANIMATIONS_430,
    ASSET_OBJECT_ANIMATIONS_431,
    ASSET_OBJECT_ANIMATIONS_432,
    ASSET_OBJECT_ANIMATIONS_433,
    ASSET_OBJECT_ANIMATIONS_434,
    ASSET_OBJECT_ANIMATIONS_435,
    ASSET_OBJECT_ANIMATIONS_436,
    ASSET_OBJECT_ANIMATIONS_437,
    ASSET_OBJECT_ANIMATIONS_438,
    ASSET_OBJECT_ANIMATIONS_439,
    ASSET_OBJECT_ANIMATIONS_440,
    ASSET_OBJECT_ANIMATIONS_441,
    ASSET_OBJECT_ANIMATIONS_442,
    ASSET_OBJECT_ANIMATIONS_443,
    ASSET_OBJECT_ANIMATIONS_444,
    ASSET_OBJECT_ANIMATIONS_445,
    ASSET_OBJECT_ANIMATIONS_446,
    ASSET_OBJECT_ANIMATIONS_447,
    ASSET_OBJECT_ANIMATIONS_448,
    ASSET_OBJECT_ANIMATIONS_449,
    ASSET_OBJECT_ANIMATIONS_450,
    ASSET_OBJECT_ANIMATIONS_451,
    ASSET_OBJECT_ANIMATIONS_452,
    ASSET_OBJECT_ANIMATIONS_453,
    ASSET_OBJECT_ANIMATIONS_454,
    ASSET_OBJECT_ANIMATIONS_455,
    ASSET_OBJECT_ANIMATIONS_456,
    ASSET_OBJECT_ANIMATIONS_457,
    ASSET_OBJECT_ANIMATIONS_458,
    ASSET_OBJECT_ANIMATIONS_459,
    ASSET_OBJECT_ANIMATIONS_460,
    ASSET_OBJECT_ANIMATIONS_461,
    ASSET_OBJECT_ANIMATIONS_462,
    ASSET_OBJECT_ANIMATIONS_463,
    ASSET_OBJECT_ANIMATIONS_464,
    ASSET_OBJECT_ANIMATIONS_465,
    ASSET_OBJECT_ANIMATIONS_466,
    ASSET_OBJECT_ANIMATIONS_467,
    ASSET_OBJECT_ANIMATIONS_468,
    ASSET_OBJECT_ANIMATIONS_469,
    ASSET_OBJECT_ANIMATIONS_COUNT
} AssetObjectAnimationsEnum;
typedef enum AssetObjectsEnum {
    ASSET_OBJECT_DIDDYCAR,
    ASSET_OBJECT_SWCAR,
    ASSET_OBJECT_KREMCAR,
    ASSET_OBJECT_BADGERCAR,
    ASSET_OBJECT_TORTCAR,
    ASSET_OBJECT_CONKACAR,
    ASSET_OBJECT_TIGERCAR,
    ASSET_OBJECT_BANJOCAR,
    ASSET_OBJECT_CHICKENCAR,
    ASSET_OBJECT_MOUSECAR,
    ASSET_OBJECT_DIDDYHOVER,
    ASSET_OBJECT_TICKTOCKHOVER,
    ASSET_OBJECT_KREMLINHOVER,
    ASSET_OBJECT_BADGERHOVER,
    ASSET_OBJECT_TORTHOVER,
    ASSET_OBJECT_CONKAHOVER,
    ASSET_OBJECT_TIGERHOVER,
    ASSET_OBJECT_BANJOHOVER,
    ASSET_OBJECT_CHICKENHOVER,
    ASSET_OBJECT_MOUSEHOVER,
    ASSET_OBJECT_DIDDYPLANE,
    ASSET_OBJECT_TICKTOCKPLANE,
    ASSET_OBJECT_KREMPLANE,
    ASSET_OBJECT_BADGERPLANE,
    ASSET_OBJECT_TORTPLANE,
    ASSET_OBJECT_CONKA,
    ASSET_OBJECT_TIGPLANE,
    ASSET_OBJECT_BANJOPLANE,
    ASSET_OBJECT_CHICKENPLANE,
    ASSET_OBJECT_MOUSEPLANE,
    ASSET_OBJECT_FLYINGCARPET,
    ASSET_OBJECT_TIMBERDANCER,
    ASSET_OBJECT_CHICKENCHARACTE,
    ASSET_OBJECT_PIPSYDANCER,
    ASSET_OBJECT_BANJODANCER,
    ASSET_OBJECT_TICKTOCKDANCER,
    ASSET_OBJECT_WIZPIGSHIP,
    ASSET_OBJECT_CONKADANCER,
    ASSET_OBJECT_EMPTYHOVER,
    ASSET_OBJECT_STOPWATCHMAN,
    ASSET_OBJECT_STOPWATCHSELECT,
    ASSET_OBJECT_PARKWARDEN,
    ASSET_OBJECT_SMARTIETREE,
    ASSET_OBJECT_BLUEBERRYBUSH,
    ASSET_OBJECT_RUBBERSNOWTREE,
    ASSET_OBJECT_SKINNYSNOWTREE,
    ASSET_OBJECT_XMASTREE,
    ASSET_OBJECT_ALPINESNOWTREE,
    ASSET_OBJECT_RUBBERTREE,
    ASSET_OBJECT_BEACHTREE,
    ASSET_OBJECT_PALMTREETOP,
    ASSET_OBJECT_PALMPLANT,
    ASSET_OBJECT_PALMTREETOPCHEA,
    ASSET_OBJECT_FIRTREE,
    ASSET_OBJECT_SPACETREE,
    ASSET_OBJECT_LAMPPOST,
    ASSET_OBJECT_FLOWERS,
    ASSET_OBJECT_REEDS,
    ASSET_OBJECT_SMOKE,
    ASSET_OBJECT_DINOSAUR1,
    ASSET_OBJECT_DINOSAUR2,
    ASSET_OBJECT_DINOSAUR3,
    ASSET_OBJECT_WHALE,
    ASSET_OBJECT_SNOWMEN,
    ASSET_OBJECT_SIGNS,
    ASSET_OBJECT_FLAMINGTORCH,
    ASSET_OBJECT_MIST,
    ASSET_OBJECT_SNOWBALL,
    ASSET_OBJECT_BUOY,
    ASSET_OBJECT_PIRATESHIP,
    ASSET_OBJECT_LOG,
    ASSET_OBJECT_PIGLOG,
    ASSET_OBJECT_BOULDER,
    ASSET_OBJECT_AIRZIPPERS,
    ASSET_OBJECT_WATERZIPPERS,
    ASSET_OBJECT_LEVELDOOR,
    ASSET_OBJECT_KEITHPIGDOOR,
    ASSET_OBJECT_CHALDOOR,
    ASSET_OBJECT_BOSSDOOR,
    ASSET_OBJECT_BIGBOSSDOOR,
    ASSET_OBJECT_WORLDGATE,
    ASSET_OBJECT_TTDOOR,
    ASSET_OBJECT_RAMPSWITCH,
    ASSET_OBJECT_NOENTRYDOOR,
    ASSET_OBJECT_RAMPWHALE,
    ASSET_OBJECT_SEAMONSTER,
    ASSET_OBJECT_DINOISLE,
    ASSET_OBJECT_SKYCONTROL,
    ASSET_OBJECT_CHECKPOINT,
    ASSET_OBJECT_CHECKARROW,
    ASSET_OBJECT_MODECHANGE,
    ASSET_OBJECT_TRIGGER,
    ASSET_OBJECT_FOGCHANGER,
    ASSET_OBJECT_AINODE,
    ASSET_OBJECT_EXIT,
    ASSET_OBJECT_BONUS,
    ASSET_OBJECT_CAMERA_CONTROL,
    ASSET_OBJECT_SETUPPOINT,
    ASSET_OBJECT_ANIMATOR,
    ASSET_OBJECT_TEXSCROLL,
    ASSET_OBJECT_RGBALIGHT,
    ASSET_OBJECT_INTROCAM,
    ASSET_OBJECT_WEATHER,
    ASSET_OBJECT_LENSFLARE,
    ASSET_OBJECT_LENSFLARESWITCH,
    ASSET_OBJECT_INFOPOINT,
    ASSET_OBJECT_WAVEGENERATOR,
    ASSET_OBJECT_WAVEPOWER,
    ASSET_OBJECT_RANGETRIGGER,
    ASSET_OBJECT_LAVASPURT,
    ASSET_OBJECT_BOMBEXPLOSION,
    ASSET_OBJECT_WARDENSMOKE,
    ASSET_OBJECT_BUBBLER,
    ASSET_OBJECT_WEAPONBALLOON,
    ASSET_OBJECT_WBALLOONPOP,
    ASSET_OBJECT_MISSILEGLOW,
    ASSET_OBJECT_HOMINGGLOW,
    ASSET_OBJECT_MISSILE,
    ASSET_OBJECT_HOMING,
    ASSET_OBJECT_OILSLICK,
    ASSET_OBJECT_SMOKECLOUD,
    ASSET_OBJECT_BOMB,
    ASSET_OBJECT_BUBBLEWEAPON,
    ASSET_OBJECT_WORLDKEY,
    ASSET_OBJECT_COINCREATOR,
    ASSET_OBJECT_TREASURESUCKER,
    ASSET_OBJECT_COIN,
    ASSET_OBJECT_SILVERCOIN,
    ASSET_OBJECT_GOLDCOIN,
    ASSET_OBJECT_BONUSGEM,
    ASSET_OBJECT_COLLECTEGG,
    ASSET_OBJECT_EGGCREATOR,
    ASSET_OBJECT_CHARACTERFLAG,
    ASSET_OBJECT_ANIMATION,
    ASSET_OBJECT_OVERRIDEPOS,
    ASSET_OBJECT_ANIMCAMERA,
    ASSET_OBJECT_ANIMCAR,
    ASSET_OBJECT_ANIMDOME,
    ASSET_OBJECT_WIZGHOSTS,
    ASSET_OBJECT_N64LOGO,
    ASSET_OBJECT_ASTEROID,
    ASSET_OBJECT_PILLAR,
    ASSET_OBJECT_BOULDERANIM,
    ASSET_OBJECT_PIGHEADCOLOURS,
    ASSET_OBJECT_PIGFACEANIMATOR,
    ASSET_OBJECT_PTERODACTYL,
    ASSET_OBJECT_AMULETPIECE1,
    ASSET_OBJECT_AMULETPIECE2,
    ASSET_OBJECT_AMULETPIECE3,
    ASSET_OBJECT_AMULETPIECE4,
    ASSET_OBJECT_SWAMULET1,
    ASSET_OBJECT_SWAMULET2,
    ASSET_OBJECT_SWAMULET3,
    ASSET_OBJECT_SWAMULET4,
    ASSET_OBJECT_ANIMKEY,
    ASSET_OBJECT_SPACESHIP1,
    ASSET_OBJECT_MINISHIP,
    ASSET_OBJECT_MONORAIL,
    ASSET_OBJECT_SPACESHIP2,
    ASSET_OBJECT_SPACESHIP3,
    ASSET_OBJECT_LIGHTHOUSE,
    ASSET_OBJECT_ROCKETSIGNPOST,
    ASSET_OBJECT_LIGHTHOUSE1,
    ASSET_OBJECT_LIGHTHOUSE2,
    ASSET_OBJECT_SELECTIONHILL,
    ASSET_OBJECT_WIDESCREEN,
    ASSET_OBJECT_TIGERANIMPLANE,
    ASSET_OBJECT_BADGERANIMWALK,
    ASSET_OBJECT_TIMBERANIMCAR,
    ASSET_OBJECT_KREMSELECT,
    ASSET_OBJECT_CONKSELECT,
    ASSET_OBJECT_BADGERSELECT,
    ASSET_OBJECT_TORTSELECT,
    ASSET_OBJECT_TIGERSELECT,
    ASSET_OBJECT_DIDDYSELECT,
    ASSET_OBJECT_BANJOSELECT,
    ASSET_OBJECT_CHICKSELECT,
    ASSET_OBJECT_MOUSESELECT,
    ASSET_OBJECT_MAGICCARPET,
    ASSET_OBJECT_POLYGOLDBALOON,
    ASSET_OBJECT_ANIMGENIE,
    ASSET_OBJECT_ANIMGENIE3,
    ASSET_OBJECT_BUTTERFLYBAIT,
    ASSET_OBJECT_AUDIO,
    ASSET_OBJECT_AUDIOLINE,
    ASSET_OBJECT_AUDIOSEQLINE,
    ASSET_OBJECT_AUDIOSEQ,
    ASSET_OBJECT_AUDIOREVERB,
    ASSET_OBJECT_FRONTTYRE,
    ASSET_OBJECT_BACKTYRE,
    ASSET_OBJECT_PLANETYRE,
    ASSET_OBJECT_FAN,
    ASSET_OBJECT_JETENGINE,
    ASSET_OBJECT_GLOVE,
    ASSET_OBJECT_LEEFAN,
    ASSET_OBJECT_MAGICRING,
    ASSET_OBJECT_DOME,
    ASSET_OBJECT_DOME1,
    ASSET_OBJECT_DOME2,
    ASSET_OBJECT_DOME3,
    ASSET_OBJECT_DOME4,
    ASSET_OBJECT_DOME5,
    ASSET_OBJECT_DOME6,
    ASSET_OBJECT_DOME7,
    ASSET_OBJECT_DOME8,
    ASSET_OBJECT_DOME9,
    ASSET_OBJECT_DOME10,
    ASSET_OBJECT_DOME11,
    ASSET_OBJECT_DOME12,
    ASSET_OBJECT_DOME13,
    ASSET_OBJECT_DOME14,
    ASSET_OBJECT_DOME15,
    ASSET_OBJECT_DOME16,
    ASSET_OBJECT_DOME17,
    ASSET_OBJECT_SELECTIONSHADOW,
    ASSET_OBJECT_POSTFORPARTY,
    ASSET_OBJECT_RARELOGO,
    ASSET_OBJECT_SPARKLYTHING,
    ASSET_OBJECT_DOOROPENER,
    ASSET_OBJECT_ANIMDINOSAUR2,
    ASSET_OBJECT_TIMERANIMHOVER,
    ASSET_OBJECT_ANIMBADGERPLANE,
    ASSET_OBJECT_ANIMDINOSAUR1,
    ASSET_OBJECT_ANIMMOUSECAR,
    ASSET_OBJECT_ANIMTORT,
    ASSET_OBJECT_CHICKENANIMPLAN,
    ASSET_OBJECT_EMPTYHOVERANIM,
    ASSET_OBJECT_KREMANIM,
    ASSET_OBJECT_MOUSEHOVERANIM,
    ASSET_OBJECT_TORTRUNNER,
    ASSET_OBJECT_ANIMBANJOPLANE,
    ASSET_OBJECT_CONKAANIMCAR,
    ASSET_OBJECT_GBPARKWARDEN,
    ASSET_OBJECT_WIZPIG,
    ASSET_OBJECT_WIZPIGROCKET,
    ASSET_OBJECT_PIGBOSS,
    ASSET_OBJECT_PIGBOSS2,
    ASSET_OBJECT_PIGROCKETEER,
    ASSET_OBJECT_PARTICLES2,
    ASSET_OBJECT_PIGBOULDER,
    ASSET_OBJECT_BIGPLANET,
    ASSET_OBJECT_ROCKETBIT1,
    ASSET_OBJECT_ROCKETBIT2,
    ASSET_OBJECT_GENIEHEAD,
    ASSET_OBJECT_PIGBOULDER2,
    ASSET_OBJECT_PIGBOULDER3,
    ASSET_OBJECT_PIGBOULDER4,
    ASSET_OBJECT_PIGBOULDER5,
    ASSET_OBJECT_TRICKYTOPS,
    ASSET_OBJECT_TRICKYANIM,
    ASSET_OBJECT_TRICKYANIM2,
    ASSET_OBJECT_TRICKYANIM3,
    ASSET_OBJECT_WALRUS_ANIM,
    ASSET_OBJECT_TERRYBOSS,
    ASSET_OBJECT_DRAGONBOSS,
    ASSET_OBJECT_DRAGONANIM,
    ASSET_OBJECT_WALRUS,
    ASSET_OBJECT_SNOWBALLBOSS,
    ASSET_OBJECT_ANIMOCTO,
    ASSET_OBJECT_OCTOPUS,
    ASSET_OBJECT_GOLDBALOONSPRIT,
    ASSET_OBJECT_SPACECOLUMN1,
    ASSET_OBJECT_SPACECOLUMN2,
    ASSET_OBJECT_SPACECOLUMN3,
    ASSET_OBJECT_HAYSTACK,
    ASSET_OBJECT_ANIMGENIE2,
    ASSET_OBJECT_BRIGHTSTAR,
    ASSET_OBJECT_BUTTERFLY,
    ASSET_OBJECT_FISH,
    ASSET_OBJECT_FROG,
    ASSET_OBJECT_BOOST,
    ASSET_OBJECT_MAGNETFX,
    ASSET_OBJECT_STILLFROG,
    ASSET_OBJECT_STOPWATCHICON,
    ASSET_OBJECT_STOPWATCHHAND,
    ASSET_OBJECT_BRIDGE,
    ASSET_OBJECT_POSARROW,
    ASSET_OBJECT_HITTESTER,
    ASSET_OBJECT_MIDIFADE,
    ASSET_OBJECT_WINDSAIL,
    ASSET_OBJECT_EFFECTBOX,
    ASSET_OBJECT_TROPHYCAB,
    ASSET_OBJECT_FLYCOIN,
    ASSET_OBJECT_GOLDENBALLOON,
    ASSET_OBJECT_LASERBOLT,
    ASSET_OBJECT_LASERGUN,
    ASSET_OBJECT_BOLTGLOW,
    ASSET_OBJECT_GROUNDZIPPER,
    ASSET_OBJECT_PWSAFETELEPOINT,
    ASSET_OBJECT_HEADFORPOINT,
    ASSET_OBJECT_FIREBALLATTRACT,
    ASSET_OBJECT_FIREBALL,
    ASSET_OBJECT_OCTOBUBBLE,
    ASSET_OBJECT_OCTOBOMB,
    ASSET_OBJECT_GOLDTROPHY,
    ASSET_OBJECT_PARKTROPHY,
    ASSET_OBJECT_TICKTROPHY,
    ASSET_OBJECT_TROPHY,
    ASSET_OBJECT_TELEPORT,
    ASSET_OBJECT_SHIELD,
    ASSET_OBJECT_LIGHTNING,
    ASSET_OBJECT_MIDIFADEPOINT,
    ASSET_OBJECT_LEVELNAME,
    ASSET_OBJECT_MIDICHSET,
    ASSET_OBJECTS_COUNT
} AssetObjectsEnum;
typedef enum AssetLevelObjectTranslationTableEnum {
    ASSET_OBJECT_ID_DOME,
    ASSET_OBJECT_ID_KREMCAR,
    ASSET_OBJECT_ID_BADGERCAR,
    ASSET_OBJECT_ID_TORTCAR,
    ASSET_OBJECT_ID_CONKACAR,
    ASSET_OBJECT_ID_SMARTIETREE,
    ASSET_OBJECT_ID_FRONTTYRE,
    ASSET_OBJECT_ID_BACKTYRE,
    ASSET_OBJECT_ID_HITTESTER,
    ASSET_OBJECT_ID_WORLDGATE,
    ASSET_OBJECT_ID_MIDIFADE,
    ASSET_OBJECT_ID_PARKWARDEN,
    ASSET_OBJECT_ID_WARDENSMOKE,
    ASSET_OBJECT_ID_ANIMATOR,
    ASSET_OBJECT_ID_BOMB,
    ASSET_OBJECT_ID_FLOWERS,
    ASSET_OBJECT_ID_SMOKE,
    ASSET_OBJECT_ID_EXIT,
    ASSET_OBJECT_ID_CAMERA_CONTROL,
    ASSET_OBJECT_ID_WORLDKEY,
    ASSET_OBJECT_ID_SETUPPOINT,
    ASSET_OBJECT_ID_AUDIO,
    ASSET_OBJECT_ID_AUDIOLINE,
    ASSET_OBJECT_ID_DINOSAUR1,
    ASSET_OBJECT_ID_CHECKPOINT,
    ASSET_OBJECT_ID_LEVELDOOR,
    ASSET_OBJECT_ID_FOGCHANGER,
    ASSET_OBJECT_ID_AINODE,
    ASSET_OBJECT_ID_WEAPONBALLOON,
    ASSET_OBJECT_ID_MISSILE,
    ASSET_OBJECT_ID_DOME1,
    ASSET_OBJECT_ID_SNOWMEN,
    ASSET_OBJECT_ID_DOME2,
    ASSET_OBJECT_ID_SIGNS,
    ASSET_OBJECT_ID_REEDS,
    ASSET_OBJECT_ID_BEACHTREE,
    ASSET_OBJECT_ID_AUDIOSEQLINE,
    ASSET_OBJECT_ID_AUDIOSEQ,
    ASSET_OBJECT_ID_STOPWATCHICON,
    ASSET_OBJECT_ID_EFFECTBOX,
    ASSET_OBJECT_ID_COINCREATOR,
    ASSET_OBJECT_ID_TREASURESUCKER,
    ASSET_OBJECT_ID_BRIDGE,
    ASSET_OBJECT_ID_LAVASPURT,
    ASSET_OBJECT_ID_BOMBEXPLOSION,
    ASSET_OBJECT_ID_WBALLOONPOP,
    ASSET_OBJECT_ID_BUBBLEWEAPON,
    ASSET_OBJECT_ID_DOME5,
    ASSET_OBJECT_ID_DINOISLE,
    ASSET_OBJECT_ID_AUDIOREVERB,
    ASSET_OBJECT_ID_POSARROW,
    ASSET_OBJECT_ID_WINDSAIL,
    ASSET_OBJECT_ID_COLLECTEGG,
    ASSET_OBJECT_ID_SKYCONTROL,
    ASSET_OBJECT_ID_STOPWATCHHAND,
    ASSET_OBJECT_ID_KREMLINHOVER,
    ASSET_OBJECT_ID_BADGERHOVER,
    ASSET_OBJECT_ID_TORTHOVER,
    ASSET_OBJECT_ID_CONKAHOVER,
    ASSET_OBJECT_ID_DOME3,
    ASSET_OBJECT_ID_GLOVE,
    ASSET_OBJECT_ID_FLAMINGTORCH,
    ASSET_OBJECT_ID_MIST,
    ASSET_OBJECT_ID_DOME4,
    ASSET_OBJECT_ID_TEXSCROLL,
    ASSET_OBJECT_ID_FAN,
    ASSET_OBJECT_ID_KREMPLANE,
    ASSET_OBJECT_ID_BADGERPLANE,
    ASSET_OBJECT_ID_TORTPLANE,
    ASSET_OBJECT_ID_CONKA,
    ASSET_OBJECT_ID_LOG,
    ASSET_OBJECT_ID_MODECHANGE,
    ASSET_OBJECT_ID_JETENGINE,
    ASSET_OBJECT_ID_BLUEBERRYBUSH,
    ASSET_OBJECT_ID_RUBBERSNOWTREE,
    ASSET_OBJECT_ID_SKINNYSNOWTREE,
    ASSET_OBJECT_ID_XMASTREE,
    ASSET_OBJECT_ID_ALPINESNOWTREE,
    ASSET_OBJECT_ID_RUBBERTREE,
    ASSET_OBJECT_ID_BOULDER,
    ASSET_OBJECT_ID_STOPWATCHMAN,
    ASSET_OBJECT_ID_TIGERCAR,
    ASSET_OBJECT_ID_TROPHYCAB,
    ASSET_OBJECT_ID_COIN,
    ASSET_OBJECT_ID_BANJOCAR,
    ASSET_OBJECT_ID_CHICKENCAR,
    ASSET_OBJECT_ID_MOUSECAR,
    ASSET_OBJECT_ID_TIGERHOVER,
    ASSET_OBJECT_ID_BANJOHOVER,
    ASSET_OBJECT_ID_CHICKENHOVER,
    ASSET_OBJECT_ID_MOUSEHOVER,
    ASSET_OBJECT_ID_TIGPLANE,
    ASSET_OBJECT_ID_BANJOPLANE,
    ASSET_OBJECT_ID_CHICKENPLANE,
    ASSET_OBJECT_ID_MOUSEPLANE,
    ASSET_OBJECT_ID_EGGCREATOR,
    ASSET_OBJECT_ID_CHARACTERFLAG,
    ASSET_OBJECT_ID_FLYCOIN,
    ASSET_OBJECT_ID_GOLDENBALLOON,
    ASSET_OBJECT_ID_DOME6,
    ASSET_OBJECT_ID_DOME10,
    ASSET_OBJECT_ID_PALMTREETOP,
    ASSET_OBJECT_ID_WHALE,
    ASSET_OBJECT_ID_DINOSAUR2,
    ASSET_OBJECT_ID_DINOSAUR3,
    ASSET_OBJECT_ID_RGBALIGHT,
    ASSET_OBJECT_ID_PALMPLANT,
    ASSET_OBJECT_ID_SNOWBALL,
    ASSET_OBJECT_ID_BUOY,
    ASSET_OBJECT_ID_SILVERCOIN,
    ASSET_OBJECT_ID_WEATHER,
    ASSET_OBJECT_ID_AIRZIPPERS,
    ASSET_OBJECT_ID_FIRTREE,
    ASSET_OBJECT_ID_RAMPWHALE,
    ASSET_OBJECT_ID_RAMPSWITCH,
    ASSET_OBJECT_ID_SEAMONSTER,
    ASSET_OBJECT_ID_BONUSGEM,
    ASSET_OBJECT_ID_BONUS,
    ASSET_OBJECT_ID_DOME7,
    ASSET_OBJECT_ID_INTROCAM,
    ASSET_OBJECT_ID_MAGICCARPET,
    ASSET_OBJECT_ID_LENSFLARE,
    ASSET_OBJECT_ID_LENSFLARESWITCH,
    ASSET_OBJECT_ID_HAYSTACK,
    ASSET_OBJECT_ID_PILLAR,
    ASSET_OBJECT_ID_BOULDERANIM,
    ASSET_OBJECT_ID_BOOST,
    ASSET_OBJECT_ID_MONORAIL,
    ASSET_OBJECT_ID_TROPHY,
    ASSET_OBJECT_ID_GOLDTROPHY,
    ASSET_OBJECT_ID_OILSLICK,
    ASSET_OBJECT_ID_PIGHEADCOLOURS,
    ASSET_OBJECT_ID_DOME11,
    ASSET_OBJECT_ID_RARELOGO,
    ASSET_OBJECT_ID_CHECKARROW,
    ASSET_OBJECT_ID_BIGBOSSDOOR,
    ASSET_OBJECT_ID_FIREBALLATTRACT,
    ASSET_OBJECT_ID_FIREBALL,
    ASSET_OBJECT_ID_SNOWBALLBOSS,
    ASSET_OBJECT_ID_FROG,
    ASSET_OBJECT_ID_TICKTROPHY,
    ASSET_OBJECT_ID_SHIELD,
    ASSET_OBJECT_ID_SELECTIONSHADOW,
    ASSET_OBJECT_ID_BUBBLER,
    ASSET_OBJECT_ID_PLANETYRE,
    ASSET_OBJECT_ID_DOME8,
    ASSET_OBJECT_ID_PALMTREETOPCHEA,
    ASSET_OBJECT_ID_DOME9,
    ASSET_OBJECT_ID_ANIMATION,
    ASSET_OBJECT_ID_TIGERANIMPLANE,
    ASSET_OBJECT_ID_BADGERANIMWALK,
    ASSET_OBJECT_ID_ANIMCAMERA,
    ASSET_OBJECT_ID_TIMBERDANCER,
    ASSET_OBJECT_ID_PIPSYDANCER,
    ASSET_OBJECT_ID_EMPTYHOVER,
    ASSET_OBJECT_ID_ANIMDOME,
    ASSET_OBJECT_ID_TIMBERANIMCAR,
    ASSET_OBJECT_ID_NOENTRYDOOR,
    ASSET_OBJECT_ID_N64LOGO,
    ASSET_OBJECT_ID_WIZGHOSTS,
    ASSET_OBJECT_ID_KREMSELECT,
    ASSET_OBJECT_ID_BADGERSELECT,
    ASSET_OBJECT_ID_TORTSELECT,
    ASSET_OBJECT_ID_TIGERSELECT,
    ASSET_OBJECT_ID_BANJOSELECT,
    ASSET_OBJECT_ID_CHICKSELECT,
    ASSET_OBJECT_ID_MOUSESELECT,
    ASSET_OBJECT_ID_LEEFAN,
    ASSET_OBJECT_ID_GBPARKWARDEN,
    ASSET_OBJECT_ID_GOLDBALOONSPRIT,
    ASSET_OBJECT_ID_LIGHTHOUSE,
    ASSET_OBJECT_ID_SELECTIONHILL,
    ASSET_OBJECT_ID_WIDESCREEN,
    ASSET_OBJECT_ID_OVERRIDEPOS,
    ASSET_OBJECT_ID_ANIMCAR,
    ASSET_OBJECT_ID_TRIGGER,
    ASSET_OBJECT_ID_BOLTGLOW,
    ASSET_OBJECT_ID_POSTFORPARTY,
    ASSET_OBJECT_ID_SPARKLYTHING,
    ASSET_OBJECT_ID_ANIMDINOSAUR2,
    ASSET_OBJECT_ID_TIMERANIMHOVER,
    ASSET_OBJECT_ID_ANIMBADGERPLANE,
    ASSET_OBJECT_ID_ANIMDINOSAUR1,
    ASSET_OBJECT_ID_ANIMMOUSECAR,
    ASSET_OBJECT_ID_ANIMTORT,
    ASSET_OBJECT_ID_CHICKENANIMPLAN,
    ASSET_OBJECT_ID_EMPTYHOVERANIM,
    ASSET_OBJECT_ID_RANGETRIGGER,
    ASSET_OBJECT_ID_KREMANIM,
    ASSET_OBJECT_ID_MOUSEHOVERANIM,
    ASSET_OBJECT_ID_TORTRUNNER,
    ASSET_OBJECT_ID_ANIMBANJOPLANE,
    ASSET_OBJECT_ID_CONKSELECT,
    ASSET_OBJECT_ID_LASERGUN,
    ASSET_OBJECT_ID_CONKAANIMCAR,
    ASSET_OBJECT_ID_WAVEGENERATOR,
    ASSET_OBJECT_ID_WAVEPOWER,
    ASSET_OBJECT_ID_BUTTERFLY,
    ASSET_OBJECT_ID_LASERBOLT,
    ASSET_OBJECT_ID_FISH,
    ASSET_OBJECT_ID_ANIMGENIE,
    ASSET_OBJECT_ID_SPACESHIP1,
    ASSET_OBJECT_ID_SPACESHIP2,
    ASSET_OBJECT_ID_POLYGOLDBALOON,
    ASSET_OBJECT_ID_GROUNDZIPPER,
    ASSET_OBJECT_ID_ASTEROID,
    ASSET_OBJECT_ID_PIRATESHIP,
    ASSET_OBJECT_ID_BRIGHTSTAR,
    ASSET_OBJECT_ID_WATERZIPPERS,
    ASSET_OBJECT_ID_SPACESHIP3,
    ASSET_OBJECT_ID_DOME12,
    ASSET_OBJECT_ID_CHALDOOR,
    ASSET_OBJECT_ID_STILLFROG,
    ASSET_OBJECT_ID_PARKTROPHY,
    ASSET_OBJECT_ID_BUTTERFLYBAIT,
    ASSET_OBJECT_ID_BOSSDOOR,
    ASSET_OBJECT_ID_PWSAFETELEPOINT,
    ASSET_OBJECT_ID_TRICKYTOPS,
    ASSET_OBJECT_ID_FLYINGCARPET,
    ASSET_OBJECT_ID_DOME14,
    ASSET_OBJECT_ID_PIGBOSS,
    ASSET_OBJECT_ID_DOME13,
    ASSET_OBJECT_ID_DOME15,
    ASSET_OBJECT_ID_WALRUS,
    ASSET_OBJECT_ID_DRAGONBOSS,
    ASSET_OBJECT_ID_LAMPPOST,
    ASSET_OBJECT_ID_SPACETREE,
    ASSET_OBJECT_ID_MAGICRING,
    ASSET_OBJECT_ID_HEADFORPOINT,
    ASSET_OBJECT_ID_HOMING,
    ASSET_OBJECT_ID_SPACECOLUMN2,
    ASSET_OBJECT_ID_SPACECOLUMN3,
    ASSET_OBJECT_ID_OCTOPUS,
    ASSET_OBJECT_ID_PIGFACEANIMATOR,
    ASSET_OBJECT_ID_PTERODACTYL,
    ASSET_OBJECT_ID_SMOKECLOUD,
    ASSET_OBJECT_ID_DOME16,
    ASSET_OBJECT_ID_SWCAR,
    ASSET_OBJECT_ID_AMULETPIECE1,
    ASSET_OBJECT_ID_AMULETPIECE2,
    ASSET_OBJECT_ID_AMULETPIECE3,
    ASSET_OBJECT_ID_AMULETPIECE4,
    ASSET_OBJECT_ID_STOPWATCHSELECT,
    ASSET_OBJECT_ID_TICKTOCKHOVER,
    ASSET_OBJECT_ID_TICKTOCKPLANE,
    ASSET_OBJECT_ID_SWAMULET1,
    ASSET_OBJECT_ID_SWAMULET2,
    ASSET_OBJECT_ID_SWAMULET3,
    ASSET_OBJECT_ID_SWAMULET4,
    ASSET_OBJECT_ID_ANIMKEY,
    ASSET_OBJECT_ID_TELEPORT,
    ASSET_OBJECT_ID_DIDDYSELECT,
    ASSET_OBJECT_ID_ROCKETSIGNPOST,
    ASSET_OBJECT_ID_DIDDYHOVER,
    ASSET_OBJECT_ID_LIGHTHOUSE1,
    ASSET_OBJECT_ID_DIDDYCAR,
    ASSET_OBJECT_ID_ANIMGENIE2,
    ASSET_OBJECT_ID_DIDDYPLANE,
    ASSET_OBJECT_ID_BANJODANCER,
    ASSET_OBJECT_ID_SPACECOLUMN1,
    ASSET_OBJECT_ID_MISSILEGLOW,
    ASSET_OBJECT_ID_TERRYBOSS,
    ASSET_OBJECT_ID_HOMINGGLOW,
    ASSET_OBJECT_ID_TICKTOCKDANCER,
    ASSET_OBJECT_ID_CONKADANCER,
    ASSET_OBJECT_ID_GOLDCOIN,
    ASSET_OBJECT_ID_TTDOOR,
    ASSET_OBJECT_ID_MIDIFADEPOINT,
    ASSET_OBJECT_ID_WIZPIGSHIP,
    ASSET_OBJECT_ID_TRICKYANIM,
    ASSET_OBJECT_ID_DOOROPENER,
    ASSET_OBJECT_ID_MINISHIP,
    ASSET_OBJECT_ID_OCTOBUBBLE,
    ASSET_OBJECT_ID_DOME17,
    ASSET_OBJECT_ID_DRAGONANIM,
    ASSET_OBJECT_ID_ANIMOCTO,
    ASSET_OBJECT_ID_PIGBOSS2,
    ASSET_OBJECT_ID_WIZPIG,
    ASSET_OBJECT_ID_WALRUS_ANIM,
    ASSET_OBJECT_ID_PIGLOG,
    ASSET_OBJECT_ID_WIZPIGROCKET,
    ASSET_OBJECT_ID_KEITHPIGDOOR,
    ASSET_OBJECT_ID_LIGHTNING,
    ASSET_OBJECT_ID_MAGNETFX,
    ASSET_OBJECT_ID_PIGROCKETEER,
    ASSET_OBJECT_ID_PARTICLES2,
    ASSET_OBJECT_ID_PIGBOULDER,
    ASSET_OBJECT_ID_PIGBOULDER2,
    ASSET_OBJECT_ID_PIGBOULDER3,
    ASSET_OBJECT_ID_PIGBOULDER4,
    ASSET_OBJECT_ID_PIGBOULDER5,
    ASSET_OBJECT_ID_BIGPLANET,
    ASSET_OBJECT_ID_ROCKETBIT1,
    ASSET_OBJECT_ID_ROCKETBIT2,
    ASSET_OBJECT_ID_LEVELNAME,
    ASSET_OBJECT_ID_TRICKYANIM2,
    ASSET_OBJECT_ID_TRICKYANIM3,
    ASSET_OBJECT_ID_GENIEHEAD,
    ASSET_OBJECT_ID_OCTOBOMB,
    ASSET_OBJECT_ID_MIDICHSET,
    ASSET_OBJECT_ID_ANIMGENIE3,
    NULL_OBJECT_301_ID,
    ASSET_OBJECT_ID_LIGHTHOUSE2,
    ASSET_OBJECT_ID_CHICKENCHARACTE,
    ASSET_OBJECT_ID_INFOPOINT,
    ASSET_LEVEL_OBJECT_TRANSLATION_TABLE_COUNT
} AssetLevelObjectTranslationTableEnum;
typedef enum AssetEmpty37Enum {
    ASSET_EMPTY_37_COUNT
} AssetEmpty37Enum;
typedef enum AssetAudioEnum {
    ASSET_AUDIO_0,
    ASSET_AUDIO_1,
    ASSET_AUDIO_2,
    ASSET_AUDIO_3,
    ASSET_AUDIO_4,
    ASSET_AUDIO_5,
    ASSET_AUDIO_6,
    ASSET_AUDIO_7,
    ASSET_AUDIO_8,
    ASSET_AUDIO_9,
    ASSET_AUDIO_10,
    ASSET_AUDIO_11,
    ASSET_AUDIO_12,
    ASSET_AUDIO_COUNT
} AssetAudioEnum;
typedef enum AssetParticlesEnum {
    ASSET_PARTICLES_0,
    ASSET_PARTICLES_1,
    ASSET_PARTICLES_2,
    ASSET_PARTICLES_3,
    ASSET_PARTICLES_4,
    ASSET_PARTICLES_5,
    ASSET_PARTICLES_6,
    ASSET_PARTICLES_7,
    ASSET_PARTICLES_8,
    ASSET_PARTICLES_9,
    ASSET_PARTICLES_10,
    ASSET_PARTICLES_11,
    ASSET_PARTICLES_12,
    ASSET_PARTICLES_13,
    ASSET_PARTICLES_14,
    ASSET_PARTICLES_15,
    ASSET_PARTICLES_16,
    ASSET_PARTICLES_17,
    ASSET_PARTICLES_18,
    ASSET_PARTICLES_19,
    ASSET_PARTICLES_20,
    ASSET_PARTICLES_21,
    ASSET_PARTICLES_22,
    ASSET_PARTICLES_23,
    ASSET_PARTICLES_24,
    ASSET_PARTICLES_25,
    ASSET_PARTICLES_26,
    ASSET_PARTICLES_27,
    ASSET_PARTICLES_28,
    ASSET_PARTICLES_29,
    ASSET_PARTICLES_30,
    ASSET_PARTICLES_31,
    ASSET_PARTICLES_32,
    ASSET_PARTICLES_33,
    ASSET_PARTICLES_34,
    ASSET_PARTICLES_35,
    ASSET_PARTICLES_36,
    ASSET_PARTICLES_37,
    ASSET_PARTICLES_38,
    ASSET_PARTICLES_39,
    ASSET_PARTICLES_40,
    ASSET_PARTICLES_41,
    ASSET_PARTICLES_42,
    ASSET_PARTICLES_43,
    ASSET_PARTICLES_44,
    ASSET_PARTICLES_45,
    ASSET_PARTICLES_46,
    ASSET_PARTICLES_47,
    ASSET_PARTICLES_48,
    ASSET_PARTICLES_49,
    ASSET_PARTICLES_50,
    ASSET_PARTICLES_51,
    ASSET_PARTICLES_52,
    ASSET_PARTICLES_53,
    ASSET_PARTICLES_54,
    ASSET_PARTICLES_55,
    ASSET_PARTICLES_56,
    ASSET_PARTICLES_57,
    ASSET_PARTICLES_58,
    ASSET_PARTICLES_59,
    ASSET_PARTICLES_60,
    ASSET_PARTICLES_61,
    ASSET_PARTICLES_62,
    ASSET_PARTICLES_63,
    ASSET_PARTICLES_64,
    ASSET_PARTICLES_65,
    ASSET_PARTICLES_66,
    ASSET_PARTICLES_67,
    ASSET_PARTICLES_68,
    ASSET_PARTICLES_69,
    ASSET_PARTICLES_COUNT
} AssetParticlesEnum;
typedef enum AssetParticleBehaviorsEnum {
    ASSET_PARTICLE_BEHAVIORS_0,
    ASSET_PARTICLE_BEHAVIORS_1,
    ASSET_PARTICLE_BEHAVIORS_2,
    ASSET_PARTICLE_BEHAVIORS_3,
    ASSET_PARTICLE_BEHAVIORS_4,
    ASSET_PARTICLE_BEHAVIORS_5,
    ASSET_PARTICLE_BEHAVIORS_6,
    ASSET_PARTICLE_BEHAVIORS_7,
    ASSET_PARTICLE_BEHAVIORS_8,
    ASSET_PARTICLE_BEHAVIORS_9,
    ASSET_PARTICLE_BEHAVIORS_10,
    ASSET_PARTICLE_BEHAVIORS_11,
    ASSET_PARTICLE_BEHAVIORS_12,
    ASSET_PARTICLE_BEHAVIORS_13,
    ASSET_PARTICLE_BEHAVIORS_14,
    ASSET_PARTICLE_BEHAVIORS_15,
    ASSET_PARTICLE_BEHAVIORS_16,
    ASSET_PARTICLE_BEHAVIORS_17,
    ASSET_PARTICLE_BEHAVIORS_18,
    ASSET_PARTICLE_BEHAVIORS_19,
    ASSET_PARTICLE_BEHAVIORS_20,
    ASSET_PARTICLE_BEHAVIORS_21,
    ASSET_PARTICLE_BEHAVIORS_22,
    ASSET_PARTICLE_BEHAVIORS_23,
    ASSET_PARTICLE_BEHAVIORS_24,
    ASSET_PARTICLE_BEHAVIORS_25,
    ASSET_PARTICLE_BEHAVIORS_26,
    ASSET_PARTICLE_BEHAVIORS_27,
    ASSET_PARTICLE_BEHAVIORS_28,
    ASSET_PARTICLE_BEHAVIORS_29,
    ASSET_PARTICLE_BEHAVIORS_30,
    ASSET_PARTICLE_BEHAVIORS_31,
    ASSET_PARTICLE_BEHAVIORS_32,
    ASSET_PARTICLE_BEHAVIORS_33,
    ASSET_PARTICLE_BEHAVIORS_34,
    ASSET_PARTICLE_BEHAVIORS_35,
    ASSET_PARTICLE_BEHAVIORS_36,
    ASSET_PARTICLE_BEHAVIORS_37,
    ASSET_PARTICLE_BEHAVIORS_38,
    ASSET_PARTICLE_BEHAVIORS_39,
    ASSET_PARTICLE_BEHAVIORS_40,
    ASSET_PARTICLE_BEHAVIORS_41,
    ASSET_PARTICLE_BEHAVIORS_42,
    ASSET_PARTICLE_BEHAVIORS_43,
    ASSET_PARTICLE_BEHAVIORS_44,
    ASSET_PARTICLE_BEHAVIORS_45,
    ASSET_PARTICLE_BEHAVIORS_46,
    ASSET_PARTICLE_BEHAVIORS_47,
    ASSET_PARTICLE_BEHAVIORS_48,
    ASSET_PARTICLE_BEHAVIORS_49,
    ASSET_PARTICLE_BEHAVIORS_50,
    ASSET_PARTICLE_BEHAVIORS_51,
    ASSET_PARTICLE_BEHAVIORS_52,
    ASSET_PARTICLE_BEHAVIORS_53,
    ASSET_PARTICLE_BEHAVIORS_54,
    ASSET_PARTICLE_BEHAVIORS_55,
    ASSET_PARTICLE_BEHAVIORS_56,
    ASSET_PARTICLE_BEHAVIORS_57,
    ASSET_PARTICLE_BEHAVIORS_58,
    ASSET_PARTICLE_BEHAVIORS_59,
    ASSET_PARTICLE_BEHAVIORS_60,
    ASSET_PARTICLE_BEHAVIORS_61,
    ASSET_PARTICLE_BEHAVIORS_62,
    ASSET_PARTICLE_BEHAVIORS_63,
    ASSET_PARTICLE_BEHAVIORS_64,
    ASSET_PARTICLE_BEHAVIORS_65,
    ASSET_PARTICLE_BEHAVIORS_66,
    ASSET_PARTICLE_BEHAVIORS_67,
    ASSET_PARTICLE_BEHAVIORS_68,
    ASSET_PARTICLE_BEHAVIORS_69,
    ASSET_PARTICLE_BEHAVIORS_70,
    ASSET_PARTICLE_BEHAVIORS_71,
    ASSET_PARTICLE_BEHAVIORS_72,
    ASSET_PARTICLE_BEHAVIORS_73,
    ASSET_PARTICLE_BEHAVIORS_74,
    ASSET_PARTICLE_BEHAVIORS_COUNT
} AssetParticleBehaviorsEnum;
typedef enum AssetFontsEnum {
    ASSET_FONTS_FUNFONT,
    ASSET_FONTS_SMALLFONT,
    ASSET_FONTS_BIGFONT,
    ASSET_FONTS_SUBTITLEFONT,
    ASSET_FONTS_COUNT
} AssetFontsEnum;
typedef enum AssetTtghostsEnum {
    ASSET_TTGHOSTS_FOSSILCANYON,
    ASSET_TTGHOSTS_PIRATELAGOON,
    ASSET_TTGHOSTS_ANCIENTLAKE,
    ASSET_TTGHOSTS_WALRUSCOVE,
    ASSET_TTGHOSTS_HOTTOPVOLCANO,
    ASSET_TTGHOSTS_WHALEBAY,
    ASSET_TTGHOSTS_SNOWBALLVALLEY,
    ASSET_TTGHOSTS_CRESCENTISLAND,
    ASSET_TTGHOSTS_EVERFROSTPEAK,
    ASSET_TTGHOSTS_SPACEPORTALPHA,
    ASSET_TTGHOSTS_SPACEDUSTALLEY,
    ASSET_TTGHOSTS_GREENWOODVILLAGE,
    ASSET_TTGHOSTS_BOULDERCANYON,
    ASSET_TTGHOSTS_WINDMILLPLAINS,
    ASSET_TTGHOSTS_FROSTYVILLAGE,
    ASSET_TTGHOSTS_JUNGLEFALLS,
    ASSET_TTGHOSTS_TREASURECAVES,
    ASSET_TTGHOSTS_HAUNTEDWOODS,
    ASSET_TTGHOSTS_DARKMOONCAVERNS,
    ASSET_TTGHOSTS_STARCITY,
    ASSET_TTGHOSTS_COUNT
} AssetTtghostsEnum;
typedef AssetLevelHeadersEnum MapId;
typedef enum SpecialMapId {
    SPECIAL_MAP_ID_UNK_NEG10 = -10,
    SPECIAL_MAP_ID_UNK_NEG2 = -2,
    SPECIAL_MAP_ID_NO_LEVEL = -1,
} SpecialMapId;
typedef enum Character {
    CHARACTER_KRUNCH,
    CHARACTER_BUMPER,
    CHARACTER_TIPTUP,
    CHARACTER_CONKER,
    CHARACTER_TIMBER,
    CHARACTER_BANJO,
    CHARACTER_DRUMSTICK,
    CHARACTER_PIPSY,
    CHARACTER_TT,
    CHARACTER_DIDDY,
    NUMBER_OF_CHARACTERS
} Character;
typedef enum Vehicle {
    VEHICLE_CAR,
    VEHICLE_HOVERCRAFT,
    VEHICLE_PLANE,
    VEHICLE_FLYING_CAR,
    VEHICLE_LOOPDELOOP,
    VEHICLE_BOSSES,
    VEHICLE_TRICKY = VEHICLE_BOSSES,
    VEHICLE_BLUEY,
    VEHICLE_SMOKEY,
    VEHICLE_PTERODACTYL,
    VEHICLE_SNOWBALL,
    VEHICLE_CARPET,
    VEHICLE_BUBBLER,
    VEHICLE_WIZPIG,
    VEHICLE_ROCKET,
    VEHICLE_NO_OVERRIDE = -1,
    NUMBER_OF_VEHICLE_TYPES,
    NUMBER_OF_PLAYER_VEHICLES = 3
} Vehicle;
typedef enum CameraMode {
    CAMERA_CAR,
    CAMERA_PLANE,
    CAMERA_UNUSED,
    CAMERA_FIXED,
    CAMERA_HOVERCRAFT,
    CAMERA_FINISH_CHALLENGE,
    CAMERA_LOOP,
    CAMERA_FINISH_RACE
} CameraMode;
typedef enum Language { LANGUAGE_ENGLISH, LANGUAGE_GERMAN, LANGUAGE_FRENCH, LANGUAGE_JAPANESE } Language;
typedef enum World {
    WORLD_NONE = -1,
    WORLD_CENTRAL_AREA,
    WORLD_DINO_DOMAIN,
    WORLD_SHERBET_ISLAND,
    WORLD_SNOWFLAKE_MOUNTAIN,
    WORLD_DRAGON_FOREST,
    WORLD_FUTURE_FUN_LAND
} World;
typedef enum RaceType {
    RACETYPE_DEFAULT = 0,
    RACETYPE_UNK1 = 1,
    RACETYPE_HORSESHOE_GULCH = 3,
    RACETYPE_HUBWORLD = 5,
    RACETYPE_CUTSCENE_1 = 6,
    RACETYPE_CUTSCENE_2 = 7,
    RACETYPE_BOSS = 8,
    RACETYPE_CHALLENGE_BATTLE = 64,
    RACETYPE_CHALLENGE_BANANAS = 65,
    RACETYPE_CHALLENGE_EGGS = 66,
    RACETYPE_CHALLENGE = 0x40
} RaceType;
enum BossSetupTypes {
    BOSS_RACE_TRICKY1,
    BOSS_RACE_BLUEY1,
    BOSS_RACE_SMOKEY1,
    BOSS_RACE_TRICKY2,
    BOSS_RACE_BLUEY2,
    BOSS_RACE_BUBBLER1,
    BOSS_RACE_BUBBLER2,
    BOSS_RACE_SMOKEY2,
    BOSS_RACE_WIZPIG1,
    BOSS_RACE_WIZPIG2
};
typedef enum ObjectModelType {
    OBJECT_MODEL_TYPE_3D_MODEL,
    OBJECT_MODEL_TYPE_SPRITE_BILLBOARD,
    OBJECT_MODEL_TYPE_VEHICLE_PART,
    OBJECT_MODEL_TYPE_UNKNOWN3,
    OBJECT_MODEL_TYPE_MISC
} ObjectModelType;
typedef enum WarpFlag {
    WARP_FLAG_NORMAL = -1,
    WARP_FLAG_BOSS_1,
    WARP_FLAG_BOSS_2
} WarpFlag;
typedef enum BalloonType {
    BALLOON_TYPE_BOOST,
    BALLOON_TYPE_MISSILE,
    BALLOON_TYPE_TRAP,
    BALLOON_TYPE_SHIELD,
    BALLOON_TYPE_MAGNET
} BalloonType;
typedef enum HorizontalAlignmentFlags {
    HORZ_ALIGN_LEFT = 0,
    HORZ_ALIGN_RIGHT = 1,
    HORZ_ALIGN_CENTER = 4
} HorizontalAlignmentFlags;
typedef enum VerticalAlignmentFlags {
    VERT_ALIGN_TOP = 0,
    VERT_ALIGN_BOTTOM = 2,
    VERT_ALIGN_MIDDLE = 8
} VerticalAlignmentFlags;
typedef enum AlignmentFlags {
    ALIGN_TOP_LEFT = VERT_ALIGN_TOP | HORZ_ALIGN_LEFT,
    ALIGN_TOP_CENTER = VERT_ALIGN_TOP | HORZ_ALIGN_CENTER,
    ALIGN_TOP_RIGHT = VERT_ALIGN_TOP | HORZ_ALIGN_RIGHT,
    ALIGN_MIDDLE_LEFT = VERT_ALIGN_MIDDLE | HORZ_ALIGN_LEFT,
    ALIGN_MIDDLE_CENTER = VERT_ALIGN_MIDDLE | HORZ_ALIGN_CENTER,
    ALIGN_MIDDLE_RIGHT = VERT_ALIGN_MIDDLE | HORZ_ALIGN_RIGHT,
    ALIGN_BOTTOM_LEFT = VERT_ALIGN_BOTTOM | HORZ_ALIGN_LEFT,
    ALIGN_BOTTOM_CENTER = VERT_ALIGN_BOTTOM | HORZ_ALIGN_CENTER,
    ALIGN_BOTTOM_RIGHT = VERT_ALIGN_BOTTOM | HORZ_ALIGN_RIGHT
} AlignmentFlags;
typedef enum SurfaceType {
    SURFACE_DEFAULT,
    SURFACE_GRASS,
    SURFACE_SAND,
    SURFACE_ZIP_PAD,
    SURFACE_STONE,
    SURFACE_EGG_SPAWN,
    SURFACE_EGG_01,
    SURFACE_EGG_02,
    SURFACE_EGG_03,
    SURFACE_EGG_04,
    SURFACE_FROZEN_WATER,
    SURFACE_WATER_CALM,
    SURFACE_TAJ_PAD,
    SURFACE_SNOW,
    SURFACE_WATER_WAVY,
    SURFACE_WATER_UNK_F,
    SURFACE_UNK10,
    SURFACE_INVIS_WALL,
    SURFACE_UNK12,
    SURFACE_NONE = 255
} SurfaceType;
typedef struct ObjPropertyCommon {
    s32 unk0;
    s32 unk4;
} ObjPropertyCommon;
typedef struct ObjPropertyDistance {
    f32 radius;
    s32 unk4;
} ObjPropertyDistance;
typedef struct ObjPropertyTorchMist {
    s32 speed;
} ObjPropertyTorchMist;
typedef struct ObjPropertyBanana {
    s32 status;
    s16 intangibleTimer;
    s16 destroyTimer;
} ObjPropertyBanana;
typedef struct ObjPropertyName {
    f32 radius;
    s16 levelID;
    s16 opacity;
} ObjPropertyName;
typedef struct ObjPropertyProjectile {
    s32 timer;
    s32 unk4;
} ObjPropertyProjectile;
typedef struct ObjPropertyLog {
    s32 angleVel;
    s32 velocityY;
} ObjPropertyLog;
typedef struct ObjPropertyScenery {
    struct Object *interactObj;
    s16 hitTimer;
    s16 angleVel;
} ObjPropertyScenery;
typedef struct ObjPropertyFireball {
    struct Object *obj;
    s32 timer;
} ObjPropertyFireball;
typedef struct ObjPropertyWizPigShip {
    s32 unk0;
    s32 timer;
} ObjPropertyWizPigShip;
typedef struct ObjPropertyLaserbolt {
    s32 timer;
    struct Object_LaserGun *obj;
} ObjPropertyLaserbolt;
typedef struct ObjPropertyTrophyCabinet {
    s32 action;
    s32 trophy;
} ObjPropertyTrophyCabinet;
typedef struct ObjPropertyEggSpawner {
    struct Object *egg;
} ObjPropertyEggSpawner;
typedef struct ObjPropertyZipper {
    s32 radius;
} ObjPropertyZipper;
typedef struct ObjPropertyCharacterFlag {
    s32 playerID;
    s32 characterID;
} ObjPropertyCharacterFlag;
typedef struct ObjPropertyGoldenBalloon {
    s32 action;
    s32 timer;
} ObjPropertyGoldenBalloon;
typedef struct ObjPropertySilverCoin {
    s32 action;
    s32 timer;
} ObjPropertySilverCoin;
typedef struct ObjPropertyTT {
    s32 action;
    s32 timer;
} ObjPropertyTT;
typedef struct ObjPropertyTaj {
    s32 action;
    s32 timer;
} ObjPropertyTaj;
typedef struct ObjPropertyLavaSpurt {
    s32 actionTimer;
    s32 delayTimer;
} ObjPropertyLavaSpurt;
typedef struct ObjPropertyPosArrow {
    s32 playerID;
} ObjPropertyPosArrow;
typedef struct ObjPropertyAnimation {
    s32 action;
    s32 behaviourID;
} ObjPropertyAnimation;
typedef struct ObjPropertyAnimatedObject {
    s32 unk0;
    s32 unk4;
} ObjPropertyAnimatedObject;
typedef struct ObjPropertyInfoPoint {
    s32 radius;
    s32 visible;
} ObjPropertyInfoPoint;
typedef struct ObjPropertyBombExplosion {
    s32 timer;
    s32 opacity;
} ObjPropertyBombExplosion;
typedef struct ObjPropertyLighthouse {
    s32 active;
} ObjPropertyLighthouse;
typedef struct ObjPropertyDoor {
    s32 closeAngle;
    s32 openAngle;
} ObjPropertyDoor;
typedef struct ObjPropertyBridgeWhaleRamp {
    s32 unk0;
} ObjPropertyBridgeWhaleRamp;
typedef struct ObjPropertyRampSwitch {
    s32 unk0;
} ObjPropertyRampSwitch;
typedef struct ObjPropertySkyControl {
    s32 setting;
    s32 radius;
} ObjPropertySkyControl;
typedef struct ObjPropertyTreasureSucker {
    s32 playerID;
    s32 spawnTimer;
} ObjPropertyTreasureSucker;
typedef struct ObjPropertyTreasureBanana {
    s32 diff;
    struct Object_Racer *racer;
} ObjPropertyTreasureBanana;
typedef struct ObjPropertyFlyCoin {
    s32 diff;
    struct Object_Racer *racer;
} ObjPropertyFlyCoin;
typedef struct ObjPropertyBananaSpawner {
    s32 timer;
    s32 spawn;
} ObjPropertyBananaSpawner;
typedef struct ObjPropertyWorldKey {
    s32 keyID;
} ObjPropertyWorldKey;
typedef struct ObjPropertyWeaponBalloon {
    s32 balloonID;
    s32 particleTimer;
} ObjPropertyWeaponBalloon;
typedef struct ObjPropertyRacer {
    struct Object *unk0;
    s32 unk4;
} ObjPropertyRacer;
typedef struct ObjPropertySetupPoint {
    s32 racerIndex;
    u32 entranceID;
} ObjPropertySetupPoint;
typedef struct ObjPropertyWeapon {
    s32 decayTimer;
    u8 status;
    u8 submerged;
    s16 scale;
} ObjPropertyWeapon;
typedef struct ObjPropertyCamControl {
    s32 cameraID;
} ObjPropertyCamControl;
typedef struct ObjPropertyTimeTrial {
    s32 timestamp;
    struct ObjectHeader *header;
} ObjPropertyTimeTrial;
typedef struct ObjPropertyDinoWhale {
    s32 unk0;
} ObjPropertyDinoWhale;
typedef struct ObjPropertyBubbler {
    s32 unk0;
} ObjPropertyBubbler;
typedef struct ObjPropertyBoost {
    struct Object *obj;
    union {
        s32 indexes;
        struct {
            s32 racerIndex : 4;
            s32 vertIndex : 14;
            s32 trisIndex : 14;
        };
    };
} ObjPropertyBoost;
typedef struct ObjProperties {
    union {
        ObjPropertyCommon common;
        ObjPropertyDistance distance;
        ObjPropertyTorchMist torchMist;
        ObjPropertyBanana banana;
        ObjPropertyName levelName;
        ObjPropertyProjectile projectile;
        ObjPropertyLog log;
        ObjPropertyScenery scenery;
        ObjPropertyFireball fireball;
        ObjPropertyLaserbolt laserbolt;
        ObjPropertyTrophyCabinet trophyCabinet;
        ObjPropertyEggSpawner eggSpawner;
        ObjPropertyZipper zipper;
        ObjPropertyCharacterFlag characterFlag;
        ObjPropertyGoldenBalloon goldenBalloon;
        ObjPropertySilverCoin silverCoin;
        ObjPropertyTT tt;
        ObjPropertyTaj taj;
        ObjPropertyLavaSpurt lavaSpurt;
        ObjPropertyPosArrow posArrow;
        ObjPropertyAnimation animation;
        ObjPropertyWizPigShip wizpigship;
        ObjPropertyAnimatedObject animatedObj;
        ObjPropertyInfoPoint infoPoint;
        ObjPropertyBombExplosion bombExplosion;
        ObjPropertyLighthouse lighthouse;
        ObjPropertyDoor door;
        ObjPropertyBridgeWhaleRamp bridgeWhaleRamp;
        ObjPropertyRampSwitch rampSwitch;
        ObjPropertySkyControl skyControl;
        ObjPropertyTreasureSucker treasureSucker;
        ObjPropertyFlyCoin flyCoin;
        ObjPropertyBananaSpawner bananaSpawner;
        ObjPropertyWorldKey worldKey;
        ObjPropertyWeaponBalloon weaponBalloon;
        ObjPropertySetupPoint setupPoint;
        ObjPropertyWeapon weapon;
        ObjPropertyCamControl camControl;
        ObjPropertyTimeTrial timeTrial;
        ObjPropertyDinoWhale dinoWhale;
        ObjPropertyBubbler bubbler;
        ObjPropertyBoost boost;
    };
} ObjProperties;
typedef struct {
 short ob[3];
 unsigned short flag;
 short tc[2];
 unsigned char cn[4];
} Vtx_t;
typedef struct {
 short ob[3];
 unsigned short flag;
 short tc[2];
 signed char n[3];
 unsigned char a;
} Vtx_tn;
typedef union {
    Vtx_t v;
    Vtx_tn n;
    long long int force_structure_alignment;
} Vtx;
typedef struct {
 unsigned char flag;
 unsigned char v[3];
} Tri;
typedef long Mtx_t[4][4];
typedef union {
    Mtx_t m;
    long long int force_structure_alignment;
} Mtx;
typedef struct {
 short vscale[4];
 short vtrans[4];
} Vp_t;
typedef union {
    Vp_t vp;
    long long int force_structure_alignment;
} Vp;
typedef struct {
  unsigned char col[3];
  char pad1;
  unsigned char colc[3];
  char pad2;
  signed char dir[3];
  char pad3;
} Light_t;
typedef struct {
  unsigned char col[3];
  char pad1;
  unsigned char colc[3];
  char pad2;
} Ambient_t;
typedef struct {
  int x1,y1,x2,y2;
} Hilite_t;
typedef union {
    Light_t l;
    long long int force_structure_alignment[2];
} Light;
typedef union {
    Ambient_t l;
    long long int force_structure_alignment[1];
} Ambient;
typedef struct {
    Ambient a;
    Light l[7];
} Lightsn;
typedef struct {
    Ambient a;
    Light l[1];
} Lights0;
typedef struct {
    Ambient a;
    Light l[1];
} Lights1;
typedef struct {
    Ambient a;
    Light l[2];
} Lights2;
typedef struct {
    Ambient a;
    Light l[3];
} Lights3;
typedef struct {
    Ambient a;
    Light l[4];
} Lights4;
typedef struct {
    Ambient a;
    Light l[5];
} Lights5;
typedef struct {
    Ambient a;
    Light l[6];
} Lights6;
typedef struct {
    Ambient a;
    Light l[7];
} Lights7;
typedef struct {
    Light l[2];
} LookAt;
typedef union {
    Hilite_t h;
    long int force_structure_alignment[4];
} Hilite;
typedef struct {
 int cmd:8;
 unsigned int par:8;
 unsigned int len:16;
 unsigned int addr;
} Gdma;
typedef struct {
  int cmd:8;
  int pad:24;
  Tri tri;
} Gtri;
typedef struct {
  int cmd:8;
  int pad1:24;
  int pad2:24;
  unsigned char param:8;
} Gpopmtx;
typedef struct {
  int cmd:8;
  int pad0:8;
  int mw_index:8;
  int number:8;
  int pad1:8;
  int base:24;
} Gsegment;
typedef struct {
  int cmd:8;
  int pad0:8;
  int sft:8;
  int len:8;
  unsigned int data:32;
} GsetothermodeL;
typedef struct {
  int cmd:8;
  int pad0:8;
  int sft:8;
  int len:8;
  unsigned int data:32;
} GsetothermodeH;
typedef struct {
  unsigned char cmd;
  unsigned char lodscale;
  unsigned char tile;
  unsigned char on;
  unsigned short s;
  unsigned short t;
} Gtexture;
typedef struct {
  int cmd:8;
  int pad:24;
  Tri line;
} Gline3D;
typedef struct {
  int cmd:8;
  int pad1:24;
  short int pad2;
  short int scale;
} Gperspnorm;
typedef struct {
                int cmd:8;
                unsigned int fmt:3;
                unsigned int siz:2;
                unsigned int pad:7;
                unsigned int wd:12;
                unsigned int dram;
} Gsetimg;
typedef struct {
  int cmd:8;
  unsigned int muxs0:24;
  unsigned int muxs1:32;
} Gsetcombine;
typedef struct {
  int cmd:8;
  unsigned char pad;
  unsigned char prim_min_level;
  unsigned char prim_level;
  unsigned long color;
} Gsetcolor;
typedef struct {
  int cmd:8;
  int x0:10;
  int x0frac:2;
  int y0:10;
  int y0frac:2;
  unsigned int pad:8;
  int x1:10;
  int x1frac:2;
  int y1:10;
  int y1frac:2;
} Gfillrect;
typedef struct {
  int cmd:8;
  unsigned int fmt:3;
  unsigned int siz:2;
  unsigned int pad0:1;
  unsigned int line:9;
  unsigned int tmem:9;
  unsigned int pad1:5;
  unsigned int tile:3;
  unsigned int palette:4;
  unsigned int ct:1;
  unsigned int mt:1;
  unsigned int maskt:4;
  unsigned int shiftt:4;
  unsigned int cs:1;
  unsigned int ms:1;
  unsigned int masks:4;
  unsigned int shifts:4;
} Gsettile;
typedef struct {
  int cmd:8;
  unsigned int sl:12;
  unsigned int tl:12;
  int pad:5;
  unsigned int tile:3;
  unsigned int sh:12;
  unsigned int th:12;
} Gloadtile;
typedef Gloadtile Gloadblock;
typedef Gloadtile Gsettilesize;
typedef Gloadtile Gloadtlut;
typedef struct {
  unsigned int cmd:8;
  unsigned int xl:12;
  unsigned int yl:12;
  unsigned int pad1:5;
  unsigned int tile:3;
  unsigned int xh:12;
  unsigned int yh:12;
  unsigned int s:16;
  unsigned int t:16;
  unsigned int dsdx:16;
  unsigned int dtdy:16;
} Gtexrect;
typedef struct {
    unsigned long w0;
    unsigned long w1;
    unsigned long w2;
    unsigned long w3;
} TexRect;
typedef struct {
 unsigned int w0;
 unsigned int w1;
} Gwords;
typedef union {
 Gwords words;
 Gdma dma;
 Gtri tri;
 Gline3D line;
 Gpopmtx popmtx;
 Gsegment segment;
 GsetothermodeH setothermodeH;
 GsetothermodeL setothermodeL;
 Gtexture texture;
 Gperspnorm perspnorm;
 Gsetimg setimg;
 Gsetcombine setcombine;
 Gsetcolor setcolor;
 Gfillrect fillrect;
 Gsettile settile;
 Gloadtile loadtile;
 Gsettilesize settilesize;
 Gloadtlut loadtlut;
        long long int force_structure_alignment;
} Gfx;
typedef struct {
   unsigned int cmd:8;
 unsigned int flags:8;
 unsigned int gain:16;
 unsigned int addr;
} Aadpcm;
typedef struct {
   unsigned int cmd:8;
 unsigned int flags:8;
 unsigned int gain:16;
 unsigned int addr;
} Apolef;
typedef struct {
   unsigned int cmd:8;
 unsigned int flags:8;
 unsigned int pad1:16;
 unsigned int addr;
} Aenvelope;
typedef struct {
   unsigned int cmd:8;
 unsigned int pad1:8;
 unsigned int dmem:16;
 unsigned int pad2:16;
 unsigned int count:16;
} Aclearbuff;
typedef struct {
   unsigned int cmd:8;
 unsigned int pad1:8;
 unsigned int pad2:16;
 unsigned int inL:16;
        unsigned int inR:16;
} Ainterleave;
typedef struct {
   unsigned int cmd:8;
 unsigned int pad1:24;
 unsigned int addr;
} Aloadbuff;
typedef struct {
   unsigned int cmd:8;
 unsigned int flags:8;
 unsigned int pad1:16;
 unsigned int addr;
} Aenvmixer;
typedef struct {
   unsigned int cmd:8;
 unsigned int flags:8;
 unsigned int gain:16;
 unsigned int dmemi:16;
 unsigned int dmemo:16;
} Amixer;
typedef struct {
   unsigned int cmd:8;
 unsigned int flags:8;
 unsigned int dmem2:16;
 unsigned int addr;
} Apan;
typedef struct {
   unsigned int cmd:8;
 unsigned int flags:8;
 unsigned int pitch:16;
 unsigned int addr;
} Aresample;
typedef struct {
   unsigned int cmd:8;
 unsigned int flags:8;
 unsigned int pad1:16;
 unsigned int addr;
} Areverb;
typedef struct {
   unsigned int cmd:8;
 unsigned int pad1:24;
 unsigned int addr;
} Asavebuff;
typedef struct {
   unsigned int cmd:8;
 unsigned int pad1:24;
 unsigned int pad2:2;
 unsigned int number:4;
 unsigned int base:24;
} Asegment;
typedef struct {
   unsigned int cmd:8;
 unsigned int flags:8;
 unsigned int dmemin:16;
 unsigned int dmemout:16;
 unsigned int count:16;
} Asetbuff;
typedef struct {
   unsigned int cmd:8;
 unsigned int flags:8;
 unsigned int vol:16;
 unsigned int voltgt:16;
 unsigned int volrate:16;
} Asetvol;
typedef struct {
    unsigned int cmd:8;
    unsigned int pad1:8;
    unsigned int dmemin:16;
    unsigned int dmemout:16;
    unsigned int count:16;
} Admemmove;
typedef struct {
    unsigned int cmd:8;
    unsigned int pad1:8;
    unsigned int count:16;
    unsigned int addr;
} Aloadadpcm;
typedef struct {
    unsigned int cmd:8;
    unsigned int pad1:8;
    unsigned int pad2:16;
    unsigned int addr;
} Asetloop;
typedef struct {
 unsigned int w0;
 unsigned int w1;
} Awords;
typedef union {
 Awords words;
 Aadpcm adpcm;
        Apolef polef;
 Aclearbuff clearbuff;
 Aenvelope envelope;
        Ainterleave interleave;
 Aloadbuff loadbuff;
        Aenvmixer envmixer;
 Aresample resample;
 Areverb reverb;
 Asavebuff savebuff;
 Asegment segment;
 Asetbuff setbuff;
 Asetvol setvol;
        Admemmove dmemmove;
        Aloadadpcm loadadpcm;
        Amixer mixer;
        Asetloop setloop;
        long long int force_union_align;
} Acmd;
typedef short ADPCM_STATE[16];
typedef short POLEF_STATE[4];
typedef short RESAMPLE_STATE[16];
typedef short ENVMIX_STATE[40];
typedef s32 ALMicroTime;
typedef u8 ALPan;
typedef struct ALLink_s {
    struct ALLink_s *next;
    struct ALLink_s *prev;
} ALLink;
void alUnlink(ALLink *element);
void alLink(ALLink *element, ALLink *after);
typedef s32 (*ALDMAproc)(s32 addr, s32 len, void *state);
typedef ALDMAproc (*ALDMANew)(void *state);
void alCopy(void *src, void *dest, s32 len);
typedef struct {
    u8 *base;
    u8 *cur;
    s32 len;
    s32 count;
} ALHeap;
void alHeapInit(ALHeap *hp, u8 *base, s32 len);
void *alHeapDBAlloc(u8 *file, s32 line, ALHeap *hp, s32 num, s32 size);
s32 alHeapCheck(ALHeap *hp);
typedef u8 ALFxId;
typedef void *ALFxRef;
enum {AL_ADPCM_WAVE = 0,
         AL_RAW16_WAVE};
typedef struct {
    s32 order;
    s32 npredictors;
    s16 book[1];
} ALADPCMBook;
typedef struct {
    u32 start;
    u32 end;
    u32 count;
    ADPCM_STATE state;
} ALADPCMloop;
typedef struct {
    u32 start;
    u32 end;
    u32 count;
} ALRawLoop;
typedef struct {
    ALMicroTime attackTime;
    ALMicroTime decayTime;
    ALMicroTime releaseTime;
    u8 attackVolume;
    u8 decayVolume;
} ALEnvelope;
typedef struct {
    u8 velocityMin;
    u8 velocityMax;
    u8 keyMin;
    u8 keyMax;
    u8 keyBase;
    s8 detune;
} ALKeyMap;
typedef struct {
    ALADPCMloop *loop;
    ALADPCMBook *book;
} ALADPCMWaveInfo;
typedef struct {
    ALRawLoop *loop;
} ALRAWWaveInfo;
typedef struct ALWaveTable_s {
    u8 *base;
    s32 len;
    u8 type;
    u8 flags;
    union {
        ALADPCMWaveInfo adpcmWave;
        ALRAWWaveInfo rawWave;
    } waveInfo;
} ALWaveTable;
typedef struct ALSound_s {
    ALEnvelope *envelope;
    ALKeyMap *keyMap;
    ALWaveTable *wavetable;
    ALPan samplePan;
    u8 sampleVolume;
    u8 flags;
} ALSound;
typedef struct {
    u8 volume;
    ALPan pan;
    u8 priority;
    u8 flags;
    u8 tremType;
    u8 tremRate;
    u8 tremDepth;
    u8 tremDelay;
    u8 vibType;
    u8 vibRate;
    u8 vibDepth;
    u8 vibDelay;
    s16 bendRange;
    s16 soundCount;
    ALSound *soundArray[1];
} ALInstrument;
typedef struct ALBank_s {
    s16 instCount;
    u8 flags;
    u8 pad;
    s32 sampleRate;
    ALInstrument *percussion;
    ALInstrument *instArray[1];
} ALBank;
typedef struct {
    s16 revision;
    s16 bankCount;
    ALBank *bankArray[1];
} ALBankFile;
void alBnkfNew(ALBankFile *f, u8 *table);
typedef struct {
    u8 *offset;
    s32 len;
} ALSeqData;
typedef struct {
    s16 revision;
    s16 seqCount;
    ALSeqData seqArray[1];
} ALSeqFile;
void alSeqFileNew(ALSeqFile *f, u8 *base);
typedef ALMicroTime (*ALVoiceHandler)(void *);
typedef struct {
    s32 maxVVoices;
    s32 maxPVoices;
    s32 maxUpdates;
    s32 maxFXbusses;
    void *dmaproc;
    ALHeap *heap;
    s32 outputRate;
    ALFxId fxType[2];
    s32 *params;
} ALSynConfig;
typedef struct ALPlayer_s {
    struct ALPlayer_s *next;
    void *clientData;
    ALVoiceHandler handler;
    ALMicroTime callTime;
    s32 samplesLeft;
} ALPlayer;
typedef struct ALVoice_s {
    ALLink node;
    struct PVoice_s *pvoice;
    ALWaveTable *table;
    void *clientPrivate;
    s16 state;
    s16 priority;
    s16 fxBus;
    s16 unityPitch;
} ALVoice;
typedef struct ALVoiceConfig_s {
    s16 priority;
    s16 fxBus;
    u8 unityPitch;
} ALVoiceConfig;
typedef struct {
    ALPlayer *head;
    ALLink pFreeList;
    ALLink pAllocList;
    ALLink pLameList;
    s32 paramSamples;
    s32 curSamples;
    ALDMANew dma;
    ALHeap *heap;
    struct ALParam_s *paramList;
    struct ALMainBus_s *mainBus;
    struct ALAuxBus_s *auxBus;
    struct ALFilter_s *outputFilter;
    s32 numPVoices;
    s32 maxAuxBusses;
    s32 outputRate;
    s32 maxOutSamples;
} ALSynth;
void alSynNew(ALSynth *s, ALSynConfig *config);
void alSynDelete(ALSynth *s);
void alSynAddPlayer(ALSynth *s, ALPlayer *client);
void alSynRemovePlayer(ALSynth *s, ALPlayer *client);
s32 alSynAllocVoice(ALSynth *s, ALVoice *v, ALVoiceConfig *vc);
void alSynFreeVoice(ALSynth *s, ALVoice *voice);
void alSynStartVoice(ALSynth *s, ALVoice *voice, ALWaveTable *w);
void alSynStartVoiceParams(ALSynth *s, ALVoice *voice, ALWaveTable *w,
                              f32 pitch, s16 vol, ALPan pan, u8 fxmix,
                              ALMicroTime t);
void alSynStopVoice(ALSynth *s, ALVoice *voice);
void alSynSetVol(ALSynth *s, ALVoice *v, s16 vol, ALMicroTime delta);
void alSynSetPitch(ALSynth *s, ALVoice *voice, f32 ratio);
void alSynSetPan(ALSynth *s, ALVoice *voice, ALPan pan);
void alSynSetFXMix(ALSynth *s, ALVoice *voice, u8 fxmix);
void alSynSetPriority(ALSynth *s, ALVoice *voice, s16 priority);
s16 alSynGetPriority(ALSynth *s, ALVoice *voice);
ALFxRef *alSynAllocFX(ALSynth *s, s16 bus, ALSynConfig *c, ALHeap *hp);
ALFxRef alSynGetFXRef(ALSynth *s, s16 bus, s16 index);
void alSynFreeFX(ALSynth *s, ALFxRef *fx);
void alSynSetFXParam(ALSynth *s, ALFxRef fx, s16 paramID, void *param);
typedef struct {
    ALSynth drvr;
} ALGlobals;
extern ALGlobals *alGlobals;
void alInit(ALGlobals *glob, ALSynConfig *c);
void alClose(ALGlobals *glob);
Acmd *alAudioFrame(Acmd *cmdList, s32 *cmdLen, s16 *outBuf, s32 outLen);
enum ALMsg {
    AL_SEQ_REF_EVT,
    AL_SEQ_MIDI_EVT,
    AL_SEQP_MIDI_EVT,
    AL_TEMPO_EVT,
    AL_SEQ_END_EVT,
    AL_NOTE_END_EVT,
    AL_SEQP_ENV_EVT,
    AL_SEQP_META_EVT,
    AL_SEQP_PROG_EVT,
    AL_SEQP_API_EVT,
    AL_SEQP_VOL_EVT,
    AL_SEQP_LOOP_EVT,
    AL_SEQP_PRIORITY_EVT,
    AL_SEQP_SEQ_EVT,
    AL_SEQP_BANK_EVT,
    AL_SEQP_PLAY_EVT,
    AL_SEQP_STOP_EVT,
    AL_SEQP_STOPPING_EVT,
    AL_TRACK_END,
    AL_CSP_LOOPSTART,
    AL_CSP_LOOPEND,
    AL_CSP_NOTEOFF_EVT,
    AL_TREM_OSC_EVT,
    AL_VIB_OSC_EVT
};
enum AL_MIDIstatus {
    AL_MIDI_ChannelMask = 0x0F,
    AL_MIDI_StatusMask = 0xF0,
    AL_MIDI_ChannelVoice = 0x80,
    AL_MIDI_NoteOff = 0x80,
    AL_MIDI_NoteOn = 0x90,
    AL_MIDI_PolyKeyPressure = 0xA0,
    AL_MIDI_ControlChange = 0xB0,
    AL_MIDI_ChannelModeSelect = 0xB0,
    AL_MIDI_ProgramChange = 0xC0,
    AL_MIDI_ChannelPressure = 0xD0,
    AL_MIDI_PitchBendChange = 0xE0,
    AL_MIDI_SysEx = 0xF0,
    AL_MIDI_SystemCommon = 0xF1,
    AL_MIDI_TimeCodeQuarterFrame = 0xF1,
    AL_MIDI_SongPositionPointer = 0xF2,
    AL_MIDI_SongSelect = 0xF3,
    AL_MIDI_Undefined1 = 0xF4,
    AL_MIDI_Undefined2 = 0xF5,
    AL_MIDI_TuneRequest = 0xF6,
    AL_MIDI_EOX = 0xF7,
    AL_MIDI_SystemRealTime = 0xF8,
    AL_MIDI_TimingClock = 0xF8,
    AL_MIDI_Undefined3 = 0xF9,
    AL_MIDI_Start = 0xFA,
    AL_MIDI_Continue = 0xFB,
    AL_MIDI_Stop = 0xFC,
    AL_MIDI_Undefined4 = 0xFD,
    AL_MIDI_ActiveSensing = 0xFE,
    AL_MIDI_SystemReset = 0xFF,
    AL_MIDI_Meta = 0xFF
};
enum AL_MIDIctrl {
    AL_MIDI_VOLUME_CTRL = 0x07,
    AL_MIDI_UNK_8 = 0x08,
    AL_MIDI_PAN_CTRL = 0x0A,
    AL_MIDI_PRIORITY_CTRL = 0x10,
    AL_MIDI_FX_CTRL_0 = 0x14,
    AL_MIDI_FX_CTRL_1 = 0x15,
    AL_MIDI_FX_CTRL_2 = 0x16,
    AL_MIDI_FX_CTRL_3 = 0x17,
    AL_MIDI_FX_CTRL_4 = 0x18,
    AL_MIDI_FX_CTRL_5 = 0x19,
    AL_MIDI_FX_CTRL_6 = 0x1A,
    AL_MIDI_FX_CTRL_7 = 0x1B,
    AL_MIDI_FX_CTRL_8 = 0x1C,
    AL_MIDI_FX_CTRL_9 = 0x1D,
    AL_MIDI_SUSTAIN_CTRL = 0x40,
    AL_MIDI_FX1_CTRL = 0x5B,
    AL_MIDI_FX3_CTRL = 0x5D,
    AL_MIDI_UNK_5F = 0x5F,
    AL_MIDI_UNK_6A = 0x6A,
    AL_MIDI_UNK_6C = 0x6C
};
enum AL_MIDImeta {
    AL_MIDI_META_TEMPO = 0x51,
    AL_MIDI_META_EOT = 0x2f
};
typedef struct {
    u8 *curPtr;
    s32 lastTicks;
    s32 curTicks;
    s16 lastStatus;
} ALSeqMarker;
typedef struct {
    s32 ticks;
    u8 status;
    u8 byte1;
    u8 byte2;
    u32 duration;
} ALMIDIEvent;
typedef struct {
    s32 ticks;
    u8 status;
    u8 type;
    u8 len;
    u8 byte1;
    u8 byte2;
    u8 byte3;
} ALTempoEvent;
typedef struct {
    s32 ticks;
    u8 status;
    u8 type;
    u8 len;
} ALEndEvent;
typedef struct {
    struct ALVoice_s *voice;
} ALNoteEvent;
typedef struct {
    struct ALVoice_s *voice;
    ALMicroTime delta;
    u8 vol;
} ALVolumeEvent;
typedef struct {
    s16 vol;
} ALSeqpVolEvent;
typedef struct {
    ALSeqMarker *start;
    ALSeqMarker *end;
    s32 count;
} ALSeqpLoopEvent;
typedef struct {
    u8 chan;
    u8 priority;
} ALSeqpPriorityEvent;
typedef struct {
    void *seq;
} ALSeqpSeqEvent;
typedef struct {
    ALBank *bank;
} ALSeqpBankEvent;
typedef struct {
    struct ALVoiceState_s *vs;
    void *oscState;
    u8 chan;
} ALOscEvent;
typedef struct {
    s16 type;
    union {
        ALMIDIEvent midi;
        ALTempoEvent tempo;
        ALEndEvent end;
        ALNoteEvent note;
        ALVolumeEvent vol;
        ALSeqpLoopEvent loop;
        ALSeqpVolEvent spvol;
        ALSeqpPriorityEvent sppriority;
        ALSeqpSeqEvent spseq;
        ALSeqpBankEvent spbank;
        ALOscEvent osc;
    } msg;
} ALEvent;
typedef struct {
    ALLink node;
    ALMicroTime delta;
    ALEvent evt;
} ALEventListItem;
typedef struct {
    ALLink freeList;
    ALLink allocList;
    s32 eventCount;
} ALEventQueue;
void alEvtqNew(ALEventQueue *evtq, ALEventListItem *items,
                          s32 itemCount);
ALMicroTime alEvtqNextEvent(ALEventQueue *evtq, ALEvent *evt);
void alEvtqPostEvent(ALEventQueue *evtq, ALEvent *evt,
                                ALMicroTime delta);
void alEvtqFlush(ALEventQueue *evtq);
void alEvtqFlushType(ALEventQueue *evtq, s16 type);
typedef struct ALVoiceState_s {
    struct ALVoiceState_s *next;
    ALVoice voice;
    ALSound *sound;
    ALMicroTime envEndTime;
    f32 pitch;
    f32 vibrato;
    u8 envGain;
    u8 channel;
    u8 key;
    u8 velocity;
    u8 envPhase;
    u8 phase;
    u8 tremelo;
    u8 flags;
} ALVoiceState;
typedef struct {
    ALInstrument *instrument;
    s16 bendRange;
    ALFxId fxId;
    ALPan pan;
    u8 priority;
    u8 vol;
    u8 fxmix;
    u8 sustain;
    f32 pitchBend;
} ALChanState;
typedef struct {
    ALInstrument *instrument;
    s16 bendRange;
    ALFxId fxId;
    ALPan pan;
    u8 priority;
    u8 vol;
    u8 fxmix;
    u8 sustain;
    f32 pitchBend;
    u8 fade;
    u8 unk11;
} ALChanState_Custom;
typedef struct ALSeq_s {
    u8 *base;
    u8 *trackStart;
    u8 *curPtr;
    s32 lastTicks;
    s32 len;
    f32 qnpt;
    s16 division;
    s16 lastStatus;
} ALSeq;
typedef struct {
    u32 trackOffset[16];
    u32 division;
} ALCMidiHdr;
typedef struct ALCSeq_s {
    ALCMidiHdr *base;
    u32 validTracks;
    f32 qnpt;
    u32 lastTicks;
    u32 lastDeltaTicks;
    u32 deltaFlag;
    u8 *curLoc[16];
    u8 *curBUPtr[16];
    u8 curBULen[16];
    u8 lastStatus[16];
    u32 evtDeltaTicks[16];
} ALCSeq;
typedef struct {
    u32 validTracks;
    s32 lastTicks;
    u32 lastDeltaTicks;
    u8 *curLoc[16];
    u8 *curBUPtr[16];
    u8 curBULen[16];
    u8 lastStatus[16];
    u32 evtDeltaTicks[16];
} ALCSeqMarker;
typedef struct {
    s32 maxVoices;
    s32 maxEvents;
    u8 maxChannels;
    u8 debugFlags;
    ALHeap *heap;
    u8 voiceLimit;
    void *initOsc;
    void *updateOsc;
    void *stopOsc;
} ALSeqpConfig;
typedef ALMicroTime (*ALOscInit)(void **oscState,f32 *initVal, u8 oscType,
                                   u8 oscRate, u8 oscDepth, u8 oscDelay);
typedef ALMicroTime (*ALOscUpdate)(void *oscState, f32 *updateVal);
typedef void (*ALOscStop)(void *oscState);
typedef struct {
    ALPlayer node;
    ALSynth *drvr;
    ALSeq *target;
    ALMicroTime curTime;
    ALBank *bank;
    s32 uspt;
    s32 nextDelta;
    s32 state;
    u16 chanMask;
    s16 vol;
    u8 maxChannels;
    u8 debugFlags;
    ALEvent nextEvent;
    ALEventQueue evtq;
    ALMicroTime frameTime;
    ALChanState *chanState;
    ALVoiceState *vAllocHead;
    ALVoiceState *vAllocTail;
    ALVoiceState *vFreeList;
    u8 voiceLimit;
    u8 mappedVoices;
    u16 unk72;
    ALOscInit initOsc;
    ALOscUpdate updateOsc;
    ALOscStop stopOsc;
    ALSeqMarker *loopStart;
    ALSeqMarker *loopEnd;
    s32 loopCount;
} ALSeqPlayer;
typedef struct {
    ALPlayer node;
    ALSynth *drvr;
    ALCSeq *target;
    ALMicroTime curTime;
    ALBank *bank;
    s32 uspt;
    s32 nextDelta;
    s32 state;
    u16 chanMask;
    s16 vol;
    u8 maxChannels;
    u8 debugFlags;
    u8 unk36;
    u8 unk37;
    ALEvent nextEvent;
    ALEventQueue evtq;
    ALMicroTime frameTime;
    ALChanState *chanState;
    ALVoiceState *vAllocHead;
    ALVoiceState *vAllocTail;
    ALVoiceState *vFreeList;
    u8 voiceLimit;
    u8 mappedVoices;
    ALOscInit initOsc;
    ALOscUpdate updateOsc;
    ALOscStop stopOsc;
} ALCSPlayer;
typedef struct {
               ALPlayer node;
               ALSynth *drvr;
               ALCSeq *target;
               ALMicroTime curTime;
               ALBank *bank;
               s32 uspt;
               s32 nextDelta;
               s32 state;
               u16 chanMask;
               s16 vol;
               u8 maxChannels;
               u8 debugFlags;
               u8 unk36;
               u8 unk37;
               ALEvent nextEvent;
               ALEventQueue evtq;
               ALMicroTime frameTime;
               ALChanState_Custom *chanState;
               ALVoiceState *vAllocHead;
               ALVoiceState *vAllocTail;
               ALVoiceState *vFreeList;
               u8 voiceLimit;
               u8 mappedVoices;
               ALOscInit initOsc;
               ALOscUpdate updateOsc;
               ALOscStop stopOsc;
} ALCSPlayer_Custom;
void alSeqNew(ALSeq *seq, u8 *ptr, s32 len);
void alSeqNextEvent(ALSeq *seq, ALEvent *event);
s32 alSeqGetTicks(ALSeq *seq);
f32 alSeqTicksToSec(ALSeq *seq, s32 ticks, u32 tempo);
u32 alSeqSecToTicks(ALSeq *seq, f32 sec, u32 tempo);
void alSeqNewMarker(ALSeq *seq, ALSeqMarker *m, u32 ticks);
void alSeqSetLoc(ALSeq *seq, ALSeqMarker *marker);
void alSeqGetLoc(ALSeq *seq, ALSeqMarker *marker);
void alCSeqNew(ALCSeq *seq, u8 *ptr);
void alCSeqNextEvent(ALCSeq *seq,ALEvent *evt);
s32 alCSeqGetTicks(ALCSeq *seq);
f32 alCSeqTicksToSec(ALCSeq *seq, s32 ticks, u32 tempo);
u32 alCSeqSecToTicks(ALCSeq *seq, f32 sec, u32 tempo);
void alCSeqNewMarker(ALCSeq *seq, ALCSeqMarker *m, u32 ticks);
void alCSeqSetLoc(ALCSeq *seq, ALCSeqMarker *marker);
void alCSeqGetLoc(ALCSeq *seq, ALCSeqMarker *marker);
f32 alCents2Ratio(s32 cents);
void alSeqpNew(ALSeqPlayer *seqp, ALSeqpConfig *config);
void alSeqpDelete(ALSeqPlayer *seqp);
void alSeqpSetSeq(ALSeqPlayer *seqp, ALSeq *seq);
ALSeq *alSeqpGetSeq(ALSeqPlayer *seqp);
void alSeqpPlay(ALSeqPlayer *seqp);
void alSeqpStop(ALSeqPlayer *seqp);
s32 alSeqpGetState(ALSeqPlayer *seqp);
void alSeqpSetBank(ALSeqPlayer *seqp, ALBank *b);
void alSeqpSetTempo(ALSeqPlayer *seqp, s32 tempo);
s32 alSeqpGetTempo(ALSeqPlayer *seqp);
s16 alSeqpGetVol(ALSeqPlayer *seqp);
void alSeqpSetVol(ALSeqPlayer *seqp, s16 vol);
void alSeqpLoop(ALSeqPlayer *seqp, ALSeqMarker *start, ALSeqMarker *end, s32 count);
void alSeqpSetChlProgram(ALSeqPlayer *seqp, u8 chan, u8 prog);
s32 alSeqpGetChlProgram(ALSeqPlayer *seqp, u8 chan);
void alSeqpSetChlFXMix(ALSeqPlayer *seqp, u8 chan, u8 fxmix);
u8 alSeqpGetChlFXMix(ALSeqPlayer *seqp, u8 chan);
void alSeqpSetChlVol(ALSeqPlayer *seqp, u8 chan, u8 vol);
u8 alSeqpGetChlVol(ALSeqPlayer *seqp, u8 chan);
void alSeqpSetChlPan(ALSeqPlayer *seqp, u8 chan, ALPan pan);
ALPan alSeqpGetChlPan(ALSeqPlayer *seqp, u8 chan);
void alSeqpSetChlPriority(ALSeqPlayer *seqp, u8 chan, u8 priority);
u8 alSeqpGetChlPriority(ALSeqPlayer *seqp, u8 chan);
void alSeqpSendMidi(ALSeqPlayer *seqp, s32 ticks, u8 status, u8 byte1, u8 byte2);
void alCSPNew(ALCSPlayer *seqp, ALSeqpConfig *config);
void alCSPDelete(ALCSPlayer *seqp);
void alCSPSetSeq(ALCSPlayer *seqp, ALCSeq *seq);
ALCSeq *alCSPGetSeq(ALCSPlayer *seqp);
void alCSPPlay(ALCSPlayer *seqp);
void alCSPStop(ALCSPlayer *seqp);
s32 alCSPGetState(ALCSPlayer *seqp);
void alCSPSetBank(ALCSPlayer *seqp, ALBank *b);
void alCSPSetTempo(ALCSPlayer *seqp, s32 tempo);
s32 alCSPGetTempo(ALCSPlayer *seqp);
s16 alCSPGetVol(ALCSPlayer *seqp);
void alCSPSetVol(ALCSPlayer *seqp, s16 vol);
void alCSPSetChlProgram(ALCSPlayer *seqp, u8 chan, u8 prog);
s32 alCSPGetChlProgram(ALCSPlayer *seqp, u8 chan);
void alCSPSetChlFXMix(ALCSPlayer *seqp, u8 chan, u8 fxmix);
u8 alCSPGetChlFXMix(ALCSPlayer *seqp, u8 chan);
void alCSPSetChlPan(ALCSPlayer *seqp, u8 chan, ALPan pan);
ALPan alCSPGetChlPan(ALCSPlayer *seqp, u8 chan);
void alCSPSetChlVol(ALCSPlayer *seqp, u8 chan, u8 vol);
u8 alCSPGetChlVol(ALCSPlayer *seqp, u8 chan);
void alCSPSetChlPriority(ALCSPlayer *seqp, u8 chan, u8 priority);
u8 alCSPGetChlPriority(ALCSPlayer *seqp, u8 chan);
void alCSPSendMidi(ALCSPlayer *seqp, s32 ticks, u8 status,
                       u8 byte1, u8 byte2);
typedef struct {
    s32 maxSounds;
    s32 maxEvents;
    ALHeap *heap;
} ALSndpConfig;
typedef struct {
    ALPlayer node;
    ALEventQueue evtq;
    ALEvent nextEvent;
    ALSynth *drvr;
    s32 target;
    void *sndState;
    s32 maxSounds;
    ALMicroTime frameTime;
    ALMicroTime nextDelta;
    ALMicroTime curTime;
} ALSndPlayer;
typedef s16 ALSndId;
void alSndpNew(ALSndPlayer *sndp, ALSndpConfig *c);
void alSndpDelete(ALSndPlayer *sndp);
ALSndId alSndpAllocate(ALSndPlayer *sndp, ALSound *sound);
void alSndpDeallocate(ALSndPlayer *sndp, ALSndId id);
void alSndpSetSound(ALSndPlayer *sndp, ALSndId id);
ALSndId alSndpGetSound(ALSndPlayer *sndp);
void alSndpPlay(ALSndPlayer *sndp);
void alSndpPlayAt(ALSndPlayer *sndp, ALMicroTime delta);
void alSndpStop(ALSndPlayer *sndp);
void alSndpSetVol(ALSndPlayer *sndp, s16 vol);
void alSndpSetPitch(ALSndPlayer *sndp, f32 pitch);
void alSndpSetPan(ALSndPlayer *sndp, ALPan pan);
void alSndpSetPriority(ALSndPlayer *sndp, ALSndId id, u8 priority);
void alSndpSetFXMix(ALSndPlayer *sndp, u8 mix);
s32 alSndpGetState(ALSndPlayer *sndp);
enum SoundFlags {
    SOUND_FLAG_FINAL_IN_SEQUENCE = 1 << 0,
    SOUND_FLAG_LOOPED = 1 << 1,
    SOUND_FLAG_PLAYING = 1 << 2,
    SOUND_FLAG_RETRIGGER = 1 << 4,
    SOUND_FLAG_PITCH_SLIDE = 1 << 5
};
enum SoundStates {
    SOUND_STATE_NONE,
    SOUND_STATE_PLAYING,
    SOUND_STATE_STOPPING,
    SOUND_STATE_PREEMPT,
    SOUND_STATE_WAIT_VOICE,
    SOUND_STATE_INIT
};
typedef struct ALSoundState {
               struct ALSoundState *next;
               struct ALSoundState *prev;
               ALSound *sound;
               ALVoice voice;
               f32 slideMult;
               f32 pitch;
               struct ALSoundState **userHandle;
               s16 volume;
               u8 priority;
               s32 retries;
               ALPan pan;
               u8 fxmix;
               u8 flags;
               u8 state;
} ALSoundState;
typedef struct ALSoundState* SoundHandle;
typedef struct ALSoundStateLists {
               ALSoundState *allocHead;
               ALSoundState *allocTail;
               ALSoundState *freeHead;
  } ALSoundStateLists;
typedef struct SoundPlayer {
    ALPlayer node;
    ALEventQueue evtq;
    ALEvent nextEvent;
    ALSynth *drvr;
    ALSoundState *lastSoundState;
    ALSoundState *soundStatesArray;
    s32 maxSystemSoundChannels;
    s32 maxActiveSounds;
    s32 frameTime;
    ALMicroTime nextDelta;
    ALMicroTime curTime;
} SoundPlayer;
typedef union {
    ALEvent msg;
    struct {
        u16 type;
        ALSoundState *state;
        s32 param;
    } common;
    struct {
        s16 type;
        ALSoundState *state;
        s32 soundIndex;
        ALBank *bank;
    } retrigger;
} ALSndpEvent;
typedef struct audioMgrConfig_s{
               s32 maxSounds;
               s32 maxEvents;
               s32 maxChannels;
               ALHeap *heap;
               u16 numGroups;
} audioMgrConfig;
void sndp_set_global_volume(u32 volume);
s32 sndp_get_global_volume(void);
void sndp_set_active_sound_limit(s32 numSounds);
void sndp_init_player(audioMgrConfig *c);
ALMicroTime sndp_voice_handler(void *node);
void sndp_end(ALSoundState *state);
u16 sndp_get_state_counts(u16 *numFree, u16 *numAllocated);
void sndp_set_priority(ALSoundState *sndp, u8 priority);
ALSoundState *sndp_play(ALBank *bnk, s16 sndIndx, SoundHandle *handlePtr);
void sndp_stop_all_looped(void);
void sndp_set_param(SoundHandle soundMask, s16 type, u32 paramValue);
u16 sndp_get_group_volume(u8 groupID);
void sndp_set_group_volume(u8 groupID, u16 volume);
void sndp_apply_pitch_slide(ALSoundState *soundState);
void sndp_stop_with_flags(u8 flags);
void sndp_stop(SoundHandle state);
ALSoundState *sndp_allocate( ALBank *arg0, ALSound *sound);
void sndp_deallocate(ALSoundState *);
ALSoundState *sndp_play_with_priority(ALBank *bank, s16 sndIndx, u8 priority, SoundHandle *handlePtr);
void sndp_handle_event(SoundPlayer *sndp, ALSndpEvent *event);
typedef struct Vec4f {
    union {
        struct {
            f32 x;
            f32 y;
            f32 z;
            f32 w;
        };
        f32 f[4];
    };
} Vec4f;
typedef struct Vec3f {
    union {
        struct {
            f32 x;
            f32 y;
            f32 z;
        };
        f32 f[3];
    };
} Vec3f;
typedef struct Vec2f {
    union {
        struct {
            f32 x;
            f32 y;
        };
        f32 f[2];
    };
} Vec2f;
typedef struct Vec3s {
    union {
        struct {
            s16 y_rotation;
            s16 x_rotation;
            s16 z_rotation;
        };
        struct {
            s16 x;
            s16 y;
            s16 z;
        };
        s16 s[3];
    };
} Vec3s;
typedef struct Vec2s {
    union {
        struct {
            s16 y_rotation;
            s16 x_rotation;
        };
        struct {
            s16 x;
            s16 y;
        };
        s16 s[2];
    };
} Vec2s;
typedef struct Vec3i {
    union {
        struct {
            s32 x;
            s32 y;
            s32 z;
        };
        s32 i[3];
    };
} Vec3i;
typedef struct Vec2i {
    union {
        struct {
            s32 x;
            s32 y;
        };
        s32 i[2];
    };
} Vec2i;
typedef struct TextureHeader {
               u8 width;
               u8 height;
               u8 format;
               s8 posX;
               s8 posY;
               u8 numberOfInstances;
               s16 flags;
               s16 ciPaletteOffset;
               s16
        numberOfCommands;
               Gfx *cmd;
               u8 unk10;
               u8 unk11;
               u16
        numOfTextures;
               u16 frameAdvanceDelay;
               s16 textureSize;
               u8 unk18;
               u8 unk19;
               u8 unk1A;
               u8 unk1B;
               u8 unk1C;
               u8 isCompressed;
               u8 unk1E;
               u8 unk1F;
} TextureHeader;
typedef struct DrawTexture {
    TextureHeader *texture;
    s16 xOffset;
    s16 yOffset;
} DrawTexture;
typedef struct ShadowHeapProperties {
    TextureHeader *texture;
    s16 triCount;
    s16 vtxCount;
} ShadowHeapProperties;
typedef struct SpriteAsset {
               s16 baseTextureId;
               s16 numberOfFrames;
               Vec2s anchor;
               s32 unused_field;
               u8 frameTexOffsets[1];
} SpriteAsset;
typedef struct Sprite {
               s16 numberOfFrames;
               s16 numberOfTextures;
               s16 numberOfInstances;
               s16 drawFlags;
               TextureHeader **textures;
               Gfx *frames[1];
} Sprite;
typedef struct MenuElement {
               s16 left;
               s16 top;
               s16 center;
               s16 middle;
               s16 right;
               s16 bottom;
               u8 filterRed;
               u8 filterGreen;
               u8 filterBlue;
               u8 filterBlendFactor;
               u8 opacity;
               u8 textFont;
               u8 textAlignFlags;
               u8 elementType;
    union {
                   void *element;
                   char *asciiText;
                   TextureHeader *texture;
                   DrawTexture *drawTexture;
                   s32 *number;
                   u16 *numberU16;
                   s32 assetID;
    } t;
    union {
        struct {
                       s16 backgroundRed;
                       s16 backgroundGreen;
                       s16 backgroundBlue;
                       s16 backgroundAlpha;
        } background;
        struct {
                       s16 width;
                       s16 height;
                       s16 borderWidth;
                       s16 borderHeight;
        } texture;
    } details;
} MenuElement;
typedef struct Racer {
               u32 trophy_points;
               s8 best_times;
               s8 character;
               s8 starting_position;
               s8 unk7;
               u16 placements[4];
               u16 course_time;
               u16 lap_times[3];
} Racer;
typedef struct Settings4C {
    u8 courseID;
    u8 unk1;
    s8 mapID;
    u8 pad3[0xC];
    u8 entranceID;
} Settings4C;
typedef struct Settings {
                 s16 *balloonsPtr;
                 s32 *courseFlagsPtr;
                 u16 keys;
                 u16 unkA;
                 u16 bosses;
                 u16 trophies;
                 u32 cutsceneFlags;
                 u16 tajFlags;
                 u8 ttAmulet;
                 u8 wizpigAmulet;
                 u16 *flapInitialsPtr[3];
                 u16 *flapTimesPtr[3];
                 u16 *courseInitialsPtr[3];
                 u16 *courseTimesPtr[3];
                 u8 worldId;
                 u8 courseId;
                 u8 gNumRacers;
                 u8 newGame;
                 Settings4C *unk4C;
                 u32 filename;
                 Racer racers[8];
                 s8 timeTrialRacer;
                 s8 unk115[2];
                 s8 display_times;
} Settings;
typedef struct LevelHeader_70_18 {
    s32 unk0;
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
} LevelHeader_70_18;
typedef struct {
    union {
        struct {
            u8 r;
            u8 g;
            u8 b;
            u8 a;
        };
        u32 word;
    };
} ColourRGBA;
typedef struct LevelHeader_70 {
               s32 unk0;
               s32 unk4;
               s32 unk8;
               s32 unkC;
               ColourRGBA rgba;
               ColourRGBA rgba2;
               LevelHeader_70_18 unk18[1];
} LevelHeader_70;
typedef struct PulsatingLightDataFrame {
    u16 value;
    u16 time;
} PulsatingLightDataFrame;
typedef struct PulsatingLightData {
    u16 numberFrames;
    u16 currentFrame;
    u16 time;
    u16 totalTime;
    s32 outColorValue;
    PulsatingLightDataFrame frames[1];
} PulsatingLightData;
typedef struct ByteColour {
    u8 red;
    u8 green;
    u8 blue;
} ByteColour;
typedef struct LevelHeader {
               s8 world;
               u8 unk1;
               s8 unk2;
               s8 unk3;
               s8 unk4[4];
               f32 course_height;
               u8 unkC[10];
               u8 unk16[10];
               s8 *AILevelTable;
               u8 pad24[6];
               s8 unk2A[10];
               s16 geometry;
               s16 collectables;
               s16 skybox;
               s16 fogNear;
               s16 fogFar;
               s16 fogR;
               s16 fogG;
               s16 fogB;
               u8 unk44[0x5];
               s8 skyDome;
               s8 playerIndex;
               s8 laps;
               s8 race_type;
               s8 vehicle;
               s8 available_vehicles;
               s8 unk4F[3];
               u8 music;
               u8 unk53;
               u16 instruments;
               u8 waveSubdivisons;
               u8 unk57;
               u8 waveSineStep0;
               u8 waveSineBase0;
               s16 waveSineHeight0;
               u8 waveSineStep1;
               u8 waveSineBase1;
               s16 waveSineHeight1;
               s16 waveSeedSize;
               s16 wavePower;
               s16 unk64;
               s16 unk66;
               s16 waveTexID;
               u8 waveUVScaleX;
               u8 waveUVScaleY;
               s8 waveUVScrollX;
               s8 waveUVScrollY;
               s16 waveViewDist;
    union {
                   LevelHeader_70 *unk70[1];
        struct {
                       u8 wavesXlu;
                       u8 waveDoubleDensity;
        };
    };
               LevelHeader_70 *unk74[7];
               s16 weatherEnable;
               s16 weatherType;
               u8 weatherIntensity;
               u8 weatherOpacity;
               s16 weatherVelX;
               s16 weatherVelY;
               s16 weatherVelZ;
               s8 cameraFOV;
               u8 bgColorRed;
               u8 bgColorGreen;
               u8 bgColorBlue;
               u8 unkA0;
               u8 unkA1;
               s8 unkA2;
               s8 unkA3;
               TextureHeader *unkA4;
               s16 unkA8;
               s16 unkAA;
               PulsatingLightData *pulseLightData;
               s16 unkB0;
               u8 unkB2;
               u8 voiceLimit;
               ByteColour voidColour;
               u8 useVoid;
               s8 bossRaceID;
               u8 unkB9;
               s16 unkBA;
               u8 unkBC;
               s8 unkBD;
               u8 BGColourBottomR;
               u8 BGColourBottomG;
               u8 BGColourBottomB;
               u8 BGColourTopR;
               u8 BGColourTopG;
               u8 BGColourTopB;
} LevelHeader;
typedef struct {
               u32 unk00;
               u32 unk04;
               u32 unk08;
               f32 unk0C;
               u32 unk10;
               u32 unk14;
               f32 unk18;
               u32 unk1C;
               u32 unk20;
               u32 unk24;
               u32 unk28;
               u32 unk2C;
               u32 unk30;
               u32 unk34;
               u32 unk38;
               u32 unk3C;
               f32 unk40;
               f32 unk44;
               f32 unk48;
               u32 unk4C;
} dkr_wave_t;
typedef struct TextureInfo {
               TextureHeader *texture;
               u8 width;
               u8 height;
               u8 format;
               s8 surfaceType;
} TextureInfo;
typedef struct Vertex {
               s16 x;
               s16 y;
               s16 z;
               u8 r;
               u8 g;
               u8 b;
               u8 a;
} Vertex;
typedef struct TexCoords {
    union {
        struct {
            s16 u, v;
        };
        u32 texCoords;
    };
} TexCoords;
typedef struct Triangle {
    union {
        struct {
                       u8 flags;
                       u8 vi0;
                       u8 vi1;
                       u8 vi2;
        };
                   u32 vertices;
        u8 verticesArray[4];
    };
               TexCoords uv0;
               TexCoords uv1;
               TexCoords uv2;
} Triangle;
typedef struct TriangleBatchInfo {
               u8 textureIndex;
               s8 vertOverride;
               s16 verticesOffset;
               s16 facesOffset;
               u8 miscData;
               u8 texOffset;
               u32 flags;
} TriangleBatchInfo;
typedef struct ObjectModel_44 {
    union {
                   s32 *anim;
                   u8 *animData;
    };
               s32 animLength;
} ObjectModel_44;
typedef struct CollisionFacetPlanes {
    u16 basePlaneIndex;
    u16 edgeBisectorPlane[3];
} CollisionFacetPlanes;
typedef struct ObjectModel {
               TextureInfo *textures;
               Vertex *vertices;
               Triangle *triangles;
               CollisionFacetPlanes *collisionFacets;
               f32 *collisionPlanes;
               s16 *attachPoints;
               s16 numberOfAttachPoints;
               s16 unk1A;
               s16 *collisionSpheres;
               s16 collisionSpheresSize;
               s16 numberOfTextures;
               s16 numberOfVertices;
               s16 numberOfTriangles;
               s16 numberOfBatches;
               u8 pad2A[2];
               s32 fileSize;
               s16 references;
               s16 collisionFacetCount;
               u8 pad34[4];
               TriangleBatchInfo *batches;
               f32 unk3C;
               Vec3s *normals;
               ObjectModel_44 *animations;
               s16 numberOfAnimations;
               s16 numberOfAnimatedVertices;
               s32 *animatedVertexIndices;
               s16 hasAnimatedTexture;
               s16 texOffsetUpdateRate;
               u8 pad[0x2C];
} ObjectModel;
typedef struct ModelInstance {
               ObjectModel *objModel;
               Vertex *vertices[3];
               s16 animationID;
               s16 animationFrame;
               s16 animationFrameCount;
               s16 offsetX;
               s16 offsetY;
               s16 offsetZ;
               s16 headTilt;
               s8 modelType;
               s8 animationTaskNum;
               s8 animUpdateTimer;
} ModelInstance;
typedef struct LevelModelSegment {
               Vertex *vertices;
               Triangle *triangles;
               s32 unk8;
               TriangleBatchInfo *batches;
               s16 *unk10;
               CollisionFacetPlanes *collisionFacets;
               f32 *collisionPlanes;
               s16 numberOfVertices;
               s16 numberOfTriangles;
               s16 numberOfBatches;
    u8 pad22[0x06];
               s16 unk28;
               s8 unk2A;
               s8 hasWaves;
               Vertex *unk2C;
               s16 unk30;
               s16 unk32;
    s16 *unk34;
               s16 unk38;
    u8 pad3A[2];
               s32 unk3C;
               u8 numberofOpaqueBatches;
    u8 pad41[0x3];
} LevelModelSegment;
typedef struct LevelModelSegmentBoundingBox {
               s16 x1;
               s16 y1;
               s16 z1;
               s16 x2;
               s16 y2;
               s16 z2;
} LevelModelSegmentBoundingBox;
typedef struct BspTreeNode {
               s16 leftNode;
               s16 rightNode;
               u8 splitType;
               u8 segmentIndex;
               s16 splitValue;
} BspTreeNode;
typedef struct LevelModel {
               TextureInfo *textures;
               LevelModelSegment *segments;
               LevelModelSegmentBoundingBox *segmentsBoundingBoxes;
               u8 *unkC;
               u8 *segmentsBitfields;
               BspTreeNode *segmentsBspTree;
               s16 numberOfTextures;
               s16 numberOfSegments;
               s16 unk1C;
               s16 numberOfAnimatedTextures;
               s32 minimapSpriteIndex;
               u16 minimapRotation;
               u16 unk26;
               f32 minimapXScale;
               f32 minimapYScale;
               s16 minimapOffsetXAdv1;
               s16 minimapOffsetYAdv1;
               s16 minimapOffsetXAdv2;
               s16 minimapOffsetYAdv2;
               u32 minimapColor;
               s16 lowerXBounds;
               s16 upperXBounds;
               s16 lowerYBounds;
               s16 upperYBounds;
               s16 lowerZBounds;
               s16 upperZBounds;
               s32 modelSize;
} LevelModel;
typedef struct ObjHeaderParticleEntry {
               s32 upper;
               s32 lower;
} ObjHeaderParticleEntry;
typedef struct ObjectHeader24 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u16 unk6;
    union {
        u32 unk8;
        struct {
            u8 unk8A;
            u8 unk9;
            u8 unkA;
            u8 unkB;
        };
    };
    s16 homeX;
    s16 homeY;
    s16 homeZ;
    u16 radius;
    u16 unk14;
    u16 unk16;
} ObjectHeader24;
typedef struct ObjectHeader {
               s32 unk0;
               f32 shadowScale;
               f32 unk8;
               f32 scale;
               s32 *modelIds;
               s32 *vehiclePartIds;
               s8 *vehiclePartIndices;
               ObjHeaderParticleEntry *objectParticles;
    s32 pad20;
               ObjectHeader24 *unk24;
               f32 shadeAmbient;
               f32 shadeDiffuse;
               u16 flags;
               s16 shadowGroup;
               s16 unk34;
               s16 waterEffectGroup;
               s16 unk38;
               u8 unk3A;
               u8 unk3B;
               u8 unk3C;
               u8 shadeIntensityy;
               s16 shadeAngleY;
               s16 shadeAngleZ;
               s16 unk42;
               s16 unk44;
               s16 shadowBottom;
               s16 shadowTop;
               s16 shadowFadeMin;
               s16 shadowFadeMax;
               s16 drawDistance;
               s16 unk50;
               s8 unk52;
               s8 modelType;
               s8 behaviorId;
               s8 numberOfModelIds;
               s8 attachPointCount;
               s8 particleCount;
               s8 unk58;
               u8 pad59;
               s8 numLightSources;
               u8 unk5B;
               u8 unk5C;
               u8 unk5D;
               u8 pad5E[0x2];
               char internalName[16];
               u8 unk70;
               u8 directionalPointLighting;
               u8 unk72;
               u8 unk73;
               s8 unk74;
               s8 unk75;
               u8 unk76;
               u8 unk77;
} ObjectHeader;
typedef struct ObjectInteraction {
               struct Object *obj;
               f32 x_position;
               f32 y_position;
               f32 z_position;
               s8 hitboxRadius;
               u8 unk11;
               u8 pushForce;
               u8 distance;
               s16 flags;
               s8 unk16;
               s8 unk17;
               s32 pad[4];
} ObjectInteraction;
typedef struct ShadowData {
    f32 scale;
    TextureHeader *texture;
    s16 meshStart;
    s16 meshEnd;
    s16 unkC;
    s16 unkE;
} ShadowData;
typedef struct WaterEffect {
    f32 scale;
    TextureHeader *texture;
    s16 meshStart;
    s16 meshEnd;
    s16 textureFrame;
    s16 animationSpeed;
    s16 unk10;
    s16 unk12;
} WaterEffect;
typedef struct ShadeProperties {
               f32 unk0;
               u8 lightR;
               u8 lightG;
               u8 lightB;
               u8 lightIntensity;
               s16 lightDirX;
               s16 lightDirY;
               s16 lightDirZ;
               u8 secondaryLightR;
               u8 secondaryLightG;
               u8 secondaryLightB;
               u8 secondaryLightIntensity;
               s16 secondaryLightDirX;
               s16 secondaryLightDirY;
               s16 secondaryLightDirZ;
               u8 shadowR;
               u8 shadowG;
               u8 shadowB;
               u8 unk1B;
               s16 shadowDirX;
               s16 shadowDirY;
               s16 shadowDirZ;
               s16 unk22;
               s16 unk24;
               s16 unk26;
               f32 ambient;
               f32 diffuse;
} ShadeProperties;
typedef f32 FakeHalfMatrix[2][4];
typedef struct ObjectCollision {
    union {
                     MtxF matrices[4];
                     FakeHalfMatrix _matrices[8];
    };
                 struct Object *collidedObj;
                 u8 mtxFlip;
                 u8 pad[7];
} ObjectCollision;
typedef struct AttachPoint {
    s32 count;
    struct Object *obj[10];
    s8 *unk2C;
} AttachPoint;
typedef struct Object_LaserGun {
               s32 unk0;
               s32 unk4;
               s32 unk7;
               s16 fireTimer;
               s8 targeting;
               s8 fireRate;
               u8 laserDuration;
               u8 radius;
} Object_LaserGun;
typedef struct JingleState {
              s32 timer;
              s16 cooldown;
} JingleState;
typedef struct Object_Animator {
               s16 segmentId;
               s16 batchId;
               s16 speedFactorX;
               s16 speedFactorY;
               s16 xSpeed;
               s16 ySpeed;
} Object_Animator;
typedef struct Object_OverridePos {
               f32 x;
               f32 y;
               f32 z;
               struct Object *anim;
} Object_OverridePos;
typedef struct Object_WeaponBalloon {
              f32 scale;
              s16 respawnTime;
} Object_WeaponBalloon;
typedef struct Object_Weapon {
               struct Object *target;
               struct Object *owner;
               struct Object *hitObj;
               f32 checkpointDist;
               f32 forwardVel;
               s16 unk14;
               s16 unk16;
               u8 weaponID;
               s8 checkpoint;
               s16 unk1A;
               struct AudioPoint *soundMask;
} Object_Weapon;
typedef struct Object_Butterfly {
                Triangle triangles[8];
                Vertex vertices[12];
                TextureHeader *texture;
                u8 unkFC;
                u8 unkFD;
                u8 unkFE;
                u8 unkFF;
                struct Object *unk100;
                u16 unk104;
                s16 unk106;
                f32 unk108;
                f32 unk10C;
} Object_Butterfly;
typedef struct Object_Fish {
                Triangle triangles[8];
                Vertex vertices[12];
                TextureHeader *texture;
                u8 unkFC;
                u8 unkFD;
                s16 unkFE;
                s16 unk100;
                s16 unk102;
                s16 unk104;
                s16 unk106;
                f32 unk108;
                f32 unk10C;
                f32 unk110;
                f32 unk114;
                f32 unk118;
                f32 unk11C;
} Object_Fish;
typedef struct Object_Boost_Inner {
    Vec3f position;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
} Object_Boost_Inner;
typedef struct Object_Boost {
               Object_Boost_Inner carBoostData;
               Object_Boost_Inner hovercraftBoostData;
               Object_Boost_Inner flyingBoostData;
               s16 spriteId;
               s16 textureId;
               u8 unk70;
               u8 unk71;
               u8 unk72;
               s8 unk73;
               f32 unk74;
               Sprite *sprite;
               TextureHeader *tex;
} Object_Boost;
typedef struct Object_CollectEgg {
              u8 pad0[4];
              struct Object *spawnerObj;
              s16 hatchTimer;
              s8 racerID;
              s8 status;
} Object_CollectEgg;
typedef struct CharacterFlagModel {
               Triangle triangles[2];
               Vertex *vertices;
               TextureHeader *texture;
} CharacterFlagModel;
typedef struct Object_AudioLine {
               u8 unk0;
               u8 pad1;
               u16 soundID;
               u16 unk4;
               u16 unk6;
               union {
        struct {
            u8 unk8;
            u8 unk9;
            u8 unkA;
            u8 padB;
        } unk_struct;
        s32 unk8_word;
    } unk_union;
               u8 lineID;
               u8 unkD;
               u8 unkE;
               u8 unkF;
               u8 unk10;
               u8 unk11;
               u8 unk12;
} Object_AudioLine;
typedef struct Object_AudioReverb {
              u16 pad0;
              s16 magnitude;
              u8 lineID;
              u8 vertexIndex;
} Object_AudioReverb;
typedef struct Object_TexScroll {
              s16 textureIndex;
              s16 pad2;
              s16 unk4;
              s16 unk6;
              s16 unk8;
              s16 unkA;
} Object_TexScroll;
typedef struct Object_Frog {
               f32 homeX;
               f32 homeY;
               f32 homeZ;
               f32 homeRadius;
               f32 homeRadiusSquare;
               u8 action;
               u8 drumstick;
               s16 hopTimer;
               s8 hopFrame;
               s8 squishCooldown;
               s16 hopDirection;
               f32 forwardVel;
               f32 hopStartX;
               f32 hopStartZ;
               f32 hopTargetX;
               f32 hopTargetZ;
               f32 scaleY;
} Object_Frog;
typedef struct Object_Exit {
               f32 directionX;
               f32 directionY;
               f32 directionZ;
               f32 rotationDiff;
               s32 radius;
               s8 bossFlag;
} Object_Exit;
typedef struct Object_AiNode {
               struct Object *nodeObj[4];
               s16 distToNode[4];
               s8 directions[4];
} Object_AiNode;
typedef struct Object_Racer {
                s16 playerIndex;
                s8 racerIndex;
                s8 characterId;
                s32 unk4;
                f32 forwardVel;
                f32 animationSpeed;
                SoundHandle unk10;
                SoundHandle unk14;
                SoundHandle unk18;
                SoundHandle unk1C;
                SoundHandle unk20;
                struct AudioPoint *soundMask;
                u16 lastSoundID;
                u16 unk2A;
                f32 velocity;
                f32 lateral_velocity;
                f32 unk34;
                f32 ox1;
                f32 oy1;
                f32 oz1;
                f32 ox2;
                f32 oy2;
                f32 oz2;
                f32 ox3;
                f32 oy3;
                f32 oz3;
                f32 prev_x_position;
                f32 prev_y_position;
                f32 prev_z_position;
                f32 unk68;
                f32 unk6C;
                f32 unk70;
                f32 unk74;
                f32 carBobX;
                f32 carBobY;
                f32 carBobZ;
                f32 unk84;
                f32 unk88;
                f32 stretch_height;
                f32 stretch_height_cap;
                f32 camera_zoom;
                f32 unk98;
                f32 pitch;
                f32 roll;
                f32 yaw;
                f32 checkpoint_distance;
                f32 unkAC;
                f32 unkB0;
                f32 throttle;
                f32 brake;
                f32 unkBC;
                f32 buoyancy;
                f32 unkC4;
                f32 unkC8;
                f32 unkCC;
                f32 unkD0;
                f32 unkD4;
                f32 unkD8[12];
                struct Object *exitObj;
                s32 unk10C;
                s32 unk110;
                s32 unk114;
                struct VehicleSoundData *vehicleSound;
                f32 unk11C;
                f32 unk120;
                f32 unk124;
                s32 lap_times[5];
                s32 unk13C;
                struct Object *magnetTargetObj;
                struct Object *held_obj;
                struct Object *approachTarget;
                struct Object *zipperObj;
                struct Object *unk150;
                struct Object *unk154;
                struct Object *nodeCurrent;
                struct Object *challengeMarker;
                s16 y_rotation_offset;
                s16 x_rotation_offset;
                s16 z_rotation_offset;
                s16
        unk166;
                s16 unk168;
                s16 headAngle;
                s16 headAngleTarget;
                s16 unk16E;
                s16 unk170;
                s8 balloon_type;
                s8 balloon_quantity;
                s8 balloon_level;
                s8 magnetTimer;
                s16 unk176;
                SoundHandle magnetSoundMask;
                struct AudioPoint *shieldSoundMask;
                struct AudioPoint *bananaSoundMask;
                s8 magnetModelID;
                s8 bananas;
                u8 unk186;
                s8 attackType;
                s8 unk188;
                s8 shieldType;
                s16 unk18A;
                s16 unk18C;
                s16 shieldTimer;
                s16 courseCheckpoint;
                s8 nextCheckpoint;
                s8 lap;
                s8 countLap;
                s8 magnetLevel3;
                s16 cameraYaw;
                s16 unk198;
                s16 unk19A;
                s16 unk19C;
                s16 unk19E;
                s16 steerVisualRotation;
                s16 y_rotation_vel;
                s16 x_rotation_vel;
                s16 z_rotation_vel;
                s16 unk1A8;
                s16 racerOrder;
                s16 finishPosition;
                s16 racePosition;
                s16 unk1B0;
                s16 unk1B2;
                s32 unk1B4;
                s16 unk1B8;
                s16 unk1BA;
                s16 unk1BC;
                s16 unk1BE;
                s16 unk1C0;
                s16 unk1C2;
                s16 unk1C4;
                s16 unk1C6;
                u8 isOnAlternateRoute;
                u8 unk1C9;
                s8 unk1CA;
                s8 unk1CB;
                s8 aiSkill;
                u8 unk1CD;
                u8 unk1CE;
                s8 eggHudCounter;
                s8 spectateCamID;
                s8 unk1D1;
                s8 unk1D2;
                s8 boostTimer;
                s8 unk1D4;
                s8 unk1D5;
                s8 vehicleID;
                s8 vehicleIDPrev;
                s8 raceFinished;
                s8 unk1D9;
                u8 unk1DA;
                s8 spinout_timer;
                u8 wheel_surfaces[4];
                s8 trickType;
                s8 steerAngle;
                s8 groundedWheels;
                s8 unk1E3;
                s8 unk1E4;
                s8 waterTimer;
                s8 drift_direction;
                s8 miscAnimCounter;
                s8 unk1E8;
                s8 unk1E9;
                s8 unk1EA;
                s8 tapTimerR;
                s8 tappedR;
                s8 squish_timer;
                u8 unk1EE;
                u8 boost_sound;
                u8 unk1F0;
                u8 unk1F1;
                u8 unk1F2;
                u8 unk1F3;
                u8 startInput;
                u8 zipperDirCorrection;
                s8 unk1F6;
                u8 transparency;
                u8 indicator_type;
                s8 indicator_timer;
                s8 drifting;
                s8 unk1FB;
                u8 wrongWayCounter;
                s8 cameraIndex;
                u8 unk1FE;
                u8 unk1FF;
                s8 transitionTimer;
                s8 unk201;
                s8 silverCoinCount;
                s8 boostType;
                s16 bubbleTrapTimer;
                s16 unk206;
                s8 unk208;
                u8 unk209;
                u8 lightFlags;
                u8 unk20B;
                u8 throttleReleased;
                u8 unk20D;
                u16 delaySoundID;
                u8 delaySoundTimer;
                s8 unk211;
                s8 elevation;
                s8 unk213;
                s8 unk214;
                s8 unk215;
                u8 unk216;
                u8 unk217;
                SoundHandle weaponSoundMask;
                SoundHandle unk21C;
                SoundHandle unk220;
} Object_Racer;
typedef struct Object_Door {
               f32 homeY;
               struct AudioPoint *soundMask;
               s32 jingleTimer;
               s16 jingleCooldown;
               s8 doorID;
               u8 doorType;
               u8 balloonCount;
               u8 balloonCountUnused;
               u8 radius;
               s8 textID;
               s8 keyID;
               s8 openDir;
} Object_Door;
typedef struct Object_Trigger {
               f32 directionX;
               f32 directionY;
               f32 directionZ;
               f32 rotationDiff;
               s32 radius;
    union {
                   u8 vehicleID;
                   u8 unk14;
    };
} Object_Trigger;
typedef struct Object_Audio {
               u16 soundId;
               u16 range;
               u8 volume;
               u8 minVolume;
               u8 pitch;
               u8 unk7;
               struct AudioPoint *soundMask;
               u8 fastFalloff;
               u8 priority;
} Object_Audio;
typedef struct Object_MidiFade {
               s8 unk0;
               u8 unk1;
               u8 unk2;
               u16 unk4;
               s16 unk6;
               f32 unk8;
               f32 unkC;
               f32 unk10;
               f32 unk14;
               f32 unk18;
               f32 unk1C;
               f32 unk20;
               f32 unk24;
               f32 unk28;
               f32 unk2C;
               u8 unk2F[16];
               u8 unk40;
} Object_MidiFade;
typedef struct Object_MidiFadePoint {
               u16 unk0;
               u16 unk2;
               f32 unk4;
               f32 unk8;
               u8 unkC[16];
               u8 unk1C;
} Object_MidiFadePoint;
typedef struct Object_MidiChannelSet {
    u16 unk0;
    u8 unk2;
    u8 unk3;
} Object_MidiChannelSet;
typedef struct Object_Banana {
              s32 unk0;
              struct Object *spawner;
              s8 unk8;
              s8 droppedVehicleID;
} Object_Banana;
typedef struct Object_NPC {
               f32 unk0;
               f32 animFrameF;
               f32 unk8;
    union {
                   u8 nodeData[5];
        struct {
                       s8 nodeBack1;
                       u8 nodeCurrent;
                       u8 nodeBack2;
                       u8 nodeForward1;
                       u8 nodeForward2;
        };
    };
               u8 fogR;
               u8 fogG;
               u8 fogB;
               f32 forwardVel;
               f32 unk18;
               s16 unk1C;
               s16 unk1E;
               s16 fogNear;
               s16 fogFar;
               s32 unk24;
               s16 unk28;
               s16 unk2A;
               s32 unk2C;
               s32 unk30;
               u16 musicFade;
               s8 unk36;
} Object_NPC;
typedef struct Object_Bridge_WhaleRamp {
              f32 homeY;
              struct AudioPoint *soundMask;
} Object_Bridge_WhaleRamp;
typedef struct Object_Log {
               s16 unk0;
               u8 unk2;
               u8 unk3;
               u16 unk4;
               u16 unk6;
               u16 unk8;
               u16 unkA;
               u16 blockID;
               s8 unkE[2];
} Object_Log;
typedef struct Object_AnimatedObject {
               f32 unk0;
               f32 unk4;
               f32 unk8;
               f32 x;
               f32 y;
               f32 z;
               SoundHandle unk18;
               struct Object *unk1C;
               u32 soundMask;
               s16 currentSound;
               s16 unk26;
               s16 actorIndex;
               s16 startDelay;
               u8 loopType;
               u8 unk2D;
               u8 unk2E;
               s8 unk2F;
               s8 cameraID;
               s8 unk31;
               s8 unk32;
               s8 unk33;
               u8 unk34;
               u8 unk35;
               s16 pauseCounter;
               s8 soundID;
               s8 unk39;
               s8 unk3A;
               u8 unk3B;
               u8 unk3C;
               u8 unk3D;
               s8 unk3E;
               s8 unk3F;
               s8 unk40;
               s8 unk41;
               u8 unk42;
               s8 unk43;
               u8 unk44;
               s8 unk45;
} Object_AnimatedObject;
typedef struct ObjectTransform {
                 Vec3s rotation;
    union {
                     s16 flags;
                     s16 spriteID;
    };
                 f32 scale;
    union {
                     Vec3f position;
        struct {
                         f32 x_position;
                         f32 y_position;
                         f32 z_position;
        };
    };
} ObjectTransform;
typedef struct Object {
                 ObjectTransform trans;
                 s16 animFrame;
                 s16 numActiveEmitters;
                 f32 x_velocity;
                 f32 y_velocity;
                 f32 z_velocity;
                 f32 unk28;
                 s16 headerType;
                 s16 segmentID;
                 f32 distanceToCamera;
                 f32 unk34;
                 s8 unk38;
                 u8 opacity;
                 s8 modelIndex;
                 s8 animationID;
                 LevelObjectEntry *level_entry;
                 ObjectHeader *header;
                 Vertex *curVertData;
                 s16 behaviorId;
                 s16 objectID;
                 ObjectInteraction *interactObj;
                 ShadowData *shadow;
                 ShadeProperties *shading;
                 WaterEffect *waterEffect;
                 ObjectCollision *collisionData;
                 AttachPoint *attachPoints;
                 union {
        struct Object *animTarget;
        struct ObjectLight *light;
        Object_Log *log;
        Object_Boost *boost;
        JingleState *jingle_state;
        Object_Animator *animator;
        Object_WeaponBalloon *weapon_balloon;
        Object_Weapon *weapon;
        Object_Butterfly *butterfly;
        Object_Fish *fish;
        CharacterFlagModel *characterFlagModel;
        Object_CollectEgg *egg;
        Object_AudioLine *audio_line;
        Object_AudioReverb *audio_reverb;
        Object_TexScroll *tex_scroll;
        Object_Frog *frog;
        Object_Exit *exit;
        Object_Racer *racer;
        Object_Door *door;
        Object_Trigger *trigger;
        Object_Audio *audio;
        Object_MidiFade *midi_fade;
        Object_MidiFadePoint *midi_fade_point;
        Object_MidiChannelSet *midi_channel_set;
        Object_Banana *banana;
        Object_NPC *npc;
        Object_Bridge_WhaleRamp *bridge_whale_ramp;
        Object_LaserGun *lasergun;
        Object_AnimatedObject *animatedObject;
        Object_AiNode *ai_node;
        Object_OverridePos *override_pos;
        void *anyBehaviorData;
    };
                 union {
        ModelInstance **modelInstances;
        TextureHeader **textures;
        Sprite **sprites;
    };
                 struct ParticleEmitter *particleEmitter;
                 struct ObjectLight **lightData;
                 u32 particleEmittersEnabled;
                 ObjProperties properties;
} Object;
typedef struct unk800B2260_C {
    s32 unk0;
    s32 unk4;
    u8 pad8[0x24];
    s16 unk2C;
    u8 pad2E[0xC];
    s16 unk3A;
    u8 pad3C[0x8];
    void *unk44;
    u8 pad48[0x28];
    void *unk70;
    u8 unk74;
} unk800B2260_C;
typedef struct SegmentPropertiesObject {
                 s16 unk2C;
                 s16 segmentID;
                 f32 distanceToCamera;
                 f32 unk34;
                 s8 unk38;
                 u8 opacity;
                 s8 modelIndex;
                 s8 animationID;
} SegmentPropertiesObject;
typedef struct ObjectSegment {
                 ObjectTransform trans;
                 s16 animFrame;
                 s16 numActiveEmitters;
                 f32 x_velocity;
                 f32 y_velocity;
                 f32 z_velocity;
                 f32 unk28;
                 SegmentPropertiesObject object;
                 LevelObjectEntry *level_entry;
                 ObjectHeader *header;
} ObjectSegment;
typedef struct Object_LightData_UnkC_Unk44 {
    u8 pad0[8];
    Vertex *unk8;
} Object_LightData_UnkC_Unk44;
typedef struct Object_LightData_UnkC {
               ObjectTransform trans;
               u8 pad18[0x22];
               s16 unk3A;
               u8 pad3C[0x8];
               Object_LightData_UnkC_Unk44 *unk44;
               u8 pad48[0x14];
               s16 unk5C;
               u8 pad5E[0xE];
               u8 unk6C;
               u8 unk6D;
               u8 unk6E;
               u8 pad6F[0x6];
               u8 unk75;
               u8 pad76;
               s8 unk77;
} Object_LightData_UnkC;
typedef struct Object_LightData {
               u8 pad0[6];
               u8 unk6;
               u8 pad7[5];
               Object_LightData_UnkC **unkC;
} Object_LightData;
typedef struct GhostHeaderUnk0 {
    u8 levelID;
    u8 vehicleID;
} GhostHeaderUnk0;
typedef struct GhostHeader {
    union {
        GhostHeaderUnk0 unk0;
        s16 checksum;
    };
    union {
        struct {
            u8 characterID;
            u8 unk3;
        };
        s16 unk2;
    };
    union {
        struct {
            u8 unk4;
            s8 unk5;
        };
        s16 time;
    };
    s16 nodeCount;
} GhostHeader;
typedef struct GhostNode {
               s16 x;
               s16 y;
               s16 z;
               s16 zRotation;
               s16 xRotation;
               s16 yRotation;
} GhostNode;
typedef struct CollisionNode {
    u16 colPlaneIndex;
    u16 closestTri[3];
} CollisionNode;
typedef enum TextFonts {
    FONT_COLOURFUL,
    FONT_SMALL,
    FONT_LARGE,
    FONT_UNK_FF = 255
} TextFonts;
enum DialogueFlags {
    DIALOGUE_BOX_UNUSED_01 = 0x0001,
    DIALOGUE_BOX_VERTS = 0x4000,
    DIALOGUE_BOX_CLOSED = 0x7FFF,
    DIALOGUE_BOX_OPEN = 0x8000
};
typedef struct unk800C54E8 {
    u8 pad0[0xC];
    s16 unkC;
    s16 unkE;
    u8 pad10[9];
    u8 unk19;
} unk800C54E8;
typedef struct FontCharData {
    u8 textureID;
    u8 ulx;
    u8 width;
    u8 height;
    u8 s;
    u8 t;
    u8 lrx;
    u8 lry;
} FontCharData;
typedef struct FontData {
            s32 unk0;
            char name[28];
            u16 x;
            u16 y;
            u16 charWidth;
            u16 charHeight;
            u8 loadedFonts[24];
            s16 textureID[32];
            TextureHeader *texturePointers[32];
            FontCharData letter[96];
} FontData;
typedef struct DialogueBox {
           u8 unk00;
           u8 textNum;
           char *text;
           s16 x1;
           s16 y1;
           s16 x2;
           s16 y2;
           u8 textColourR;
           u8 textColourG;
           u8 textColourB;
           u8 textColourA;
           u8 textBGColourR;
           u8 textBGColourG;
           u8 textBGColourB;
           u8 textBGColourA;
           u8 opacity;
           u8 font;
           struct DialogueBox *nextBox;
} DialogueBox;
typedef struct DialogueTextElement {
           u8 unk0;
           u8 number;
           u8 unk2;
           u8 unk3;
           char *text;
           s16 posX;
           s16 posY;
           s16 offsetX;
           s16 offsetY;
           u8 textColourR;
           u8 textColourG;
           u8 textColourB;
           u8 textColourA;
           u8 textBGColourR;
           u8 textBGColourG;
           u8 textBGColourB;
           u8 textBGColourA;
           u8 opacity;
           u8 font;
           u16 flags;
           DialogueBox *nextBox;
} DialogueTextElement;
typedef struct DialogueBoxBackground {
    s16 xpos;
    s16 ypos;
    s16 x1;
    s16 y1;
    s16 x2;
    s16 y2;
    s16 width;
    s16 height;
    u8 backgroundColourR;
    u8 backgroundColourG;
    u8 backgroundColourB;
    u8 backgroundColourA;
    u8 textColourR;
    u8 textColourG;
    u8 textColourB;
    u8 textColourA;
    u8 textBGColourR;
    u8 textBGColourG;
    u8 textBGColourB;
    u8 textBGColourA;
    u8 opacity;
    u8 font;
    u16 flags;
    s16 textOffsetX;
    s16 textOffsetY;
    DialogueBox *textBox;
} DialogueBoxBackground;
typedef struct Asset46 {
    s32 unk0;
    s32 unk4;
    u8 unk8;
} Asset46;
void load_fonts(void);
void set_kerning(s32 setting);
void set_text_font(s32 fontID);
void set_text_colour(s32 red, s32 green, s32 blue, s32 alpha, s32 opacity);
void set_text_background_colour(s32 red, s32 green, s32 blue, s32 alpha);
void draw_text(Gfx** displayList, s32 xpos, s32 ypos, char *text, AlignmentFlags alignmentFlags);
void draw_dialogue_text_unused(Gfx **displayList, s32 dialogueBoxID, char *text, AlignmentFlags alignmentFlags);
void draw_dialogue_text_pos_unused(Gfx **displayList, s32 dialogueBoxID, s32 xpos, s32 ypos, char *text, AlignmentFlags alignmentFlags);
void set_current_dialogue_box_coords(s32 dialogueBoxID, s32 x1, s32 y1, s32 x2, s32 y2);
void set_dialogue_font(s32 dialogueBoxID, s32 font);
void set_current_dialogue_background_colour(s32 dialogueBoxID, s32 red, s32 green, s32 blue, s32 alpha);
void set_current_text_colour(s32 dialogueBoxID, s32 red, s32 green, s32 blue, s32 alpha, s32 opacity);
void set_current_text_background_colour(s32 dialogueBoxID, s32 red, s32 green, s32 blue, s32 alpha);
void move_dialogue_box_to_front(s32 dialogueBoxID, DialogueBox *dialogueBox);
void dialogue_clear(s32 dialogueBoxID);
void open_dialogue_box(s32 dialogueBoxID);
void dialogue_close(s32 dialogueBoxID);
void clear_dialogue_box_open_flag(s32 dialogueBoxID);
void render_dialogue_boxes(Gfx **dList, Mtx **mat, Vertex **verts);
void render_fill_rectangle(Gfx **dList, s32 ulx, s32 uly, s32 lrx, s32 lry);
void render_dialogue_box(Gfx **dList, Mtx **mat, Vertex **verts, s32 dialogueBoxID);
void parse_string_with_number(char *input, char *output, s32 number);
void s32_to_string(char **outString, s32 number);
void load_font(s32 fontID);
void unload_font(s32 fontID);
void render_text_string(Gfx **dList, DialogueBoxBackground *box, char *text, AlignmentFlags alignmentFlags,
                        f32 scisScale);
s32 get_text_width(char *text, s32 x, s32 font);
void *render_dialogue_text(s32 dialogueBoxID, s32 posX, s32 posY, char *text, s32 number, s32 flags);
void func_800C6464_C7064(void);
void func_800C663C_C723C(void);
void func_800C6870_C7470(void);
void func_800C67F4_C73F4(void);
s32 func_800C68CC_C74CC(u16 arg0);
void fontCreateDisplayList(Gfx *dList, Asset46 *asset, s32 width, s32 height);
s32 func_800C7744_C8344(Gfx **dList, u16 charIndex, s32 *outLeft, s32 *outTop, s32 *outRight, s32 *outBottom);
void func_800C7804_C8404(s32 arg0);
void fontConvertString(char *inString, char *outString);
void func_800C78E0_C84E0(void);
typedef s32 OSPri;
typedef s32 OSId;
typedef union {
    struct {
        f32 f_odd;
        f32 f_even;
    } f;
    f64 d;
} __OSfp;
typedef struct {
    u64 at, v0, v1, a0, a1, a2, a3;
    u64 t0, t1, t2, t3, t4, t5, t6, t7;
    u64 s0, s1, s2, s3, s4, s5, s6, s7;
    u64 t8, t9;
    u64 gp, sp, s8, ra;
    u64 lo, hi;
    u32 sr, pc, cause, badvaddr, rcp;
    u32 fpcsr;
    __OSfp fp0, fp2, fp4, fp6, fp8, fp10, fp12, fp14;
    __OSfp fp16, fp18, fp20, fp22, fp24, fp26, fp28, fp30;
} __OSThreadContext;
typedef struct {
    u32 flag;
    u32 count;
    u64 time;
} __OSThreadprofile_s;
typedef struct OSThread_s {
    struct OSThread_s *next;
    OSPri priority;
    struct OSThread_s **queue;
    struct OSThread_s *tlnext;
    u16 state;
    u16 flags;
    OSId id;
    int fp;
    __OSThreadprofile_s *thprof;
    __OSThreadContext context;
} OSThread;
extern void osCreateThread(OSThread *, OSId, void (*)(void *), void *, void *, OSPri);
extern void osDestroyThread(OSThread *);
extern void osYieldThread(void);
extern void osStartThread(OSThread *);
extern void osStopThread(OSThread *);
extern OSId osGetThreadId(OSThread *);
extern void osSetThreadPri(OSThread *, OSPri);
extern OSPri osGetThreadPri(OSThread *);
typedef u32 OSEvent;
typedef void *OSMesg;
typedef struct OSMesgQueue_s {
    OSThread *mtqueue;
    OSThread *fullqueue;
    s32 validCount;
    s32 first;
    s32 msgCount;
    OSMesg *msg;
} OSMesgQueue;
extern void osCreateMesgQueue(OSMesgQueue *, OSMesg *, s32);
extern s32 osSendMesg(OSMesgQueue *, OSMesg, s32);
extern s32 osJamMesg(OSMesgQueue *, OSMesg, s32);
extern s32 osRecvMesg(OSMesgQueue *, OSMesg *, s32);
extern void osSetEventMesg(OSEvent, OSMesgQueue *, OSMesg);
typedef struct {
 int status;
 OSMesgQueue *queue;
 int channel;
 u8 id[32];
 u8 label[32];
 int version;
 int dir_size;
 int inode_table;
 int minode_table;
 int dir_table;
 int inode_start_page;
 u8 banks;
 u8 activebank;
} OSPfs;
typedef struct {
 u32 file_size;
   u32 game_code;
   u16 company_code;
   char ext_name[4];
   char game_name[16];
} OSPfsState;
extern s32 osPfsInitPak(OSMesgQueue *, OSPfs *, int);
extern s32 osPfsRepairId(OSPfs *);
extern s32 osPfsInit(OSMesgQueue *, OSPfs *, int);
extern s32 osPfsReFormat(OSPfs *, OSMesgQueue *, int);
extern s32 osPfsChecker(OSPfs *);
extern s32 osPfsAllocateFile(OSPfs *, u16, u32, u8 *, u8 *, int, s32 *);
extern s32 osPfsFindFile(OSPfs *, u16, u32, u8 *, u8 *, s32 *);
extern s32 osPfsDeleteFile(OSPfs *, u16, u32, u8 *, u8 *);
extern s32 osPfsReadWriteFile(OSPfs *, s32, u8, int, int, u8 *);
extern s32 osPfsFileState(OSPfs *, s32, OSPfsState *);
extern s32 osPfsGetLabel(OSPfs *, u8 *, int *);
extern s32 osPfsSetLabel(OSPfs *, u8 *);
extern s32 osPfsIsPlug(OSMesgQueue *, u8 *);
extern s32 osPfsFreeBlocks(OSPfs *, s32 *);
extern s32 osPfsNumFiles(OSPfs *, s32 *, s32 *);
typedef enum {
    CONTROLLER_PAK_GOOD,
    CONTROLLER_PAK_NOT_FOUND,
    CONTROLLER_PAK_INCONSISTENT,
    CONTROLLER_PAK_WITH_BAD_ID,
    CONTROLLER_PAK_FULL,
    CONTROLLER_PAK_CHANGED,
    CONTROLLER_PAK_NO_ROOM_FOR_GHOSTS,
    CONTROLLER_PAK_RUMBLE_PAK_FOUND,
    CONTROLLER_PAK_SWITCH_TO_RUMBLE,
    CONTROLLER_PAK_BAD_DATA,
    CONTROLLER_PAK_NEED_SECOND_ADVENTURE
} SIDeviceStatus;
typedef enum {
    SAVE_FILE_TYPE_UNSET = -1,
    SAVE_FILE_TYPE_UNK0,
    SAVE_FILE_TYPE_CART_SAVE,
    SAVE_FILE_TYPE_CART_TIMES,
    SAVE_FILE_TYPE_CPAK_SAVE,
    SAVE_FILE_TYPE_CPAK_TIMES,
    SAVE_FILE_TYPE_CPAK_GHOST,
    SAVE_FILE_TYPE_CPAK_OTHER,
    SAVE_FILE_TYPE_ERASE,
    SAVE_FILE_TYPE_CPAK_EMPTY,
    SAVE_FILE_TYPE_UNK9,
    SAVE_FILE_TYPE_CART_BONUSES
} SaveFileType;
enum RumbleTypes {
    RUMBLE_TYPE_0,
    RUMBLE_TYPE_1,
    RUMBLE_TYPE_2,
    RUMBLE_TYPE_3,
    RUMBLE_TYPE_4,
    RUMBLE_TYPE_5,
    RUMBLE_TYPE_6,
    RUMBLE_TYPE_7,
    RUMBLE_TYPE_8,
    RUMBLE_TYPE_9,
    RUMBLE_TYPE_10,
    RUMBLE_TYPE_11,
    RUMBLE_TYPE_12,
    RUMBLE_TYPE_13,
    RUMBLE_TYPE_14,
    RUMBLE_TYPE_15,
    RUMBLE_TYPE_16,
    RUMBLE_TYPE_17,
    RUMBLE_TYPE_18,
    RUMBLE_TYPE_19,
    RUMBLE_TYPE_20,
};
typedef struct unk80075000_body {
    union {
        struct {
            u8 unk0;
            u8 unk1;
        };
        s16 unk0_hw;
    };
    union {
        struct {
            u8 unk2_b;
            u8 unk3_b;
        };
        s16 unk2;
    };
} unk80075000_body;
typedef struct unk80075000 {
    s32 signature;
    unk80075000_body data[1];
} unk80075000;
u8 input_get_id(s32 controllerIndex);
void rumble_init(u8 canRumble);
s32 rumble_exists(s16 controllerIndex);
void rumble_kill(void);
s32 get_game_data_file_size(void);
s32 get_time_data_file_size(void);
s32 read_game_data_from_controller_pak(s32 controllerIndex, char *fileExt, Settings *settings);
s32 write_game_data_to_controller_pak(s32 controllerIndex, Settings *arg1);
s32 read_time_data_from_controller_pak(s32 controllerIndex, char *fileExt, Settings *settings);
s32 write_time_data_to_controller_pak(s32 controllerIndex, Settings *arg1);
s32 write_save_data(s32 saveFileNum, Settings *settings);
s32 read_eeprom_data(Settings *settings, u8 flags);
s32 write_eeprom_data(Settings *settings, u8 flags);
s32 calculate_eeprom_settings_checksum(u64 eepromSettings);
s32 read_eeprom_settings(u64 *eepromSettings);
s32 write_eeprom_settings(u64 *eepromSettings);
s16 calculate_ghost_header_checksum(GhostHeader *ghostHeader);
void func_80074AA8(GhostHeader *ghostHeader, s16 characterID, s16 time, s16 nodeCount, u8 *dest);
s32 get_ghost_data_file_size(void);
SIDeviceStatus get_si_device_status(s32 controllerIndex);
s32 start_reading_controller_data(s32 controllerIndex);
SIDeviceStatus check_for_rumble_pak(s32 controllerIndex);
SIDeviceStatus repair_controller_pak(s32 controllerIndex);
SIDeviceStatus reformat_controller_pak(s32 controllerIndex);
s32 get_controller_pak_file_list(s32 controllerIndex, s32 maxNumOfFilesToGet, char **fileNames, char **fileExtensions, u32 *fileSizes, u8 *fileTypes);
void cpak_free_files(void);
s32 get_free_space(s32 controllerIndex, u32 *bytesFree, s32 *notesFree);
s32 delete_file(s32 controllerIndex, s32 fileNum);
s32 copy_controller_pak_data(s32 controllerIndex, s32 fileNumber, s32 secondControllerIndex);
SIDeviceStatus get_file_number(s32 controllerIndex, char *fileName, char *fileExt, s32 *fileNumber);
SIDeviceStatus read_data_from_controller_pak(s32 controllerIndex, s32 fileNum, u8 *data, s32 dataLength);
SIDeviceStatus write_controller_pak_file(s32 controllerIndex, s32 fileNumber, char *fileName, char *fileExt, u8 *dataToWrite, s32 fileSize);
SIDeviceStatus get_file_size(s32 controllerIndex, s32 fileNum, s32 *fileSize);
char *font_codes_to_string(char *inString, char *outString, s32 stringLength);
SaveFileType get_file_type(s32 controllerIndex, s32 fileNum);
void rumble_start(s16 controllerIndex, s16 strength, s16 timer);
void rumble_set(s16 controllerIndex, u8 type);
void rumble_set_fade(s16 controllerIndex, u8 type, f32 strength);
void rumble_update(s32 updateRate);
void init_controller_paks(void);
void func_80072E28(s32 arg0, u32 arg1);
s32 func_80072C54(s32 arg0);
void populate_settings_from_save_data(Settings *settings, u8 *saveData);
s32 read_save_file(s32 saveFileNum, Settings *settings);
void erase_save_file(s32 saveFileNum, Settings *settings);
SIDeviceStatus func_800756D4(s32 controllerIndex, u8 *levelIDs, u8 *vehicleIDs, u8 *characterIDs, u16 *checksumIDs);
SIDeviceStatus get_file_extension(s32 controllerIndex, s32 fileType, char *fileExt);
void func_80073588(Settings *settings, u8 *saveData, u8 arg2);
void func_800732E8(Settings *settings, u8 *saveData);
void func_800738A4(Settings *settings, u8 *saveData);
s32 func_80074B34(s32 controllerIndex, s16 levelId, s16 vehicleId, u16 *ghostCharacterId, s16 *ghostTime, s16 *ghostNodeCount, unk80075000 *ghostData);
char *string_to_font_codes(char *inString, char *outString, s32 stringLength);
SIDeviceStatus func_80074EB8(s32 controllerIndex, s16 levelId, s16 vehicleId, s16 ghostCharacterId, s16 ghostTime,
                             s16 ghostNodeCount, u8 *dest);
SIDeviceStatus func_80075000(s32 controllerIndex, s16 levelId, s16 vehicleId, s16 ghostCharacterId, s16 ghostTime,
                             s16 ghostNodeCount, unk80075000_body *ghostData);
s32 func_800753D8(s32 controllerIndex, s32 worldId);
void rumble_enable(s32 enable);
enum PauseMenuResults {
    PAUSE_NONE,
    PAUSE_CONTINUE,
    PAUSE_RESET,
    PAUSE_QUIT_LOBBY,
    PAUSE_OPT_4,
    PAUSE_QUIT_TRACKS,
    PAUSE_OPT_6,
    PAUSE_QUIT_CHALLENGE,
    PAUSE_QUIT_CHARSELECT = 12,
};
enum PostRaceCases {
    POSTRACE_NONE,
    POSTRACE_OPT_1,
    POSTRACE_OPT_2,
    POSTRACE_OPT_3,
    POSTRACE_OPT_4,
    POSTRACE_OPT_5,
    POSTRACE_OPT_6,
    POSTRACE_OPT_7,
    POSTRACE_OPT_8,
    POSTRACE_OPT_9,
    POSTRACE_OPT_10,
    POSTRACE_OPT_11,
    POSTRACE_OPT_12,
    POSTRACE_OPT_13
};
enum PostRaceRenderStates {
    POSTRACE_ENTER,
    POSTRACE_HOLD,
    POSTRACE_SLIDE_OUT,
    POSTRACE_SLIDE_END = 4,
};
enum PostRaceStages {
    POSTRACE_STAGE_BEGIN,
    POSTRACE_STAGE_SHRINK_VIEWPORT,
    POSTRACE_STAGE_RACE_TIMES,
    POSTRACE_STAGE_RACE_ORDER,
    POSTRACE_STAGE_ENTER_INITIALS,
    POSTRACE_STAGE_RACE_RECORDS,
    POSTRACE_STAGE_OPTIONS,
    POSTRACE_STAGE_FADE_OUT,
    POSTRACE_STAGE_END
};
enum SaveMenuStages {
    SAVEMENU_ENTER,
    SAVEMENU_WAIT,
    SAVEMENU_INIT_SOURCE,
    SAVEMENU_CHOOSE_SOURCE,
    SAVEMENU_INIT_DEST,
    SAVEMENU_CHOOSE_DEST,
    SAVEMENU_CONFIRM,
    SAVEMENU_WRITE
};
enum PakMenuStages {
    PAKMENU_CHOOSE,
    PAKMENU_CONFIRM,
    PAKMENU_WRITE
};
enum CheatMenuStages {
    CHEATMENU_CHOOSE,
    CHEATMENU_KEYBOARD,
    CHEATMENU_MESSAGE,
};
enum TrackmenuStages {
    TRACKMENU_MIRROR = -1,
    TRACKMENU_OPT_1,
    TRACKMENU_CHOOSE,
    TRACKMENU_OPT_2,
    TRACKMENU_OPT_3,
    TRACKMENU_OPT_4
};
enum AdventureSetupStages {
    ADVENTURESETUP_PREVIEW = -1,
    ADVENTURESETUP_VEHICLE,
    ADVENTURESETUP_CONFIRM
};
enum ResultsStages {
    RESULTS_ENTER = -1,
    RESULTS_SCORE,
    RESULTS_OPTIONS,
};
enum TitleScreenStages {
    TITLESCREEN_START,
    TITLESCREEN_NAME,
    TITLESCREEN_PRESS_START
};
enum RankingsStages {
    RANKINGS_ENTER,
    RANKINGS_SWAP,
    RANKINGS_ORDER,
    RANKINGS_EXIT
};
enum GhostMenuStages {
    GHOSTMENU_CHOOSE,
    GHOSTMENU_ERASE,
    GHOSTMENU_CONFIRM
};
enum DialogueMenuCases {
    DIALOGUE_TAJ,
    DIALOGUE_UNK_01,
    DIALOGUE_TT,
    DIALOGUE_CHALLENGE,
    DIALOGUE_TROPHY,
    DIALOGUE_RACERESULT
};
enum DialogIDsTaj {
    DIALOGUEPAGE_TAJ_CHALLENGE_WIN_3 = -8,
    DIALOGUEPAGE_TAJ_CHALLENGE_WIN_2 = -7,
    DIALOGUEPAGE_TAJ_CHALLENGE_WIN_1 = -6,
    DIALOGUEPAGE_TAJ_CHALLENGE_WIN = -5,
    DIALOGUEPAGE_TAJ_CHALLENGE_LOSE = -4,
    DIALOGUEPAGE_TAJ_CHALLENGE_PLANE = -3,
    DIALOGUEPAGE_TAJ_CHALLENGE_HOVER = -2,
    DIALOGUEPAGE_TAJ_CHALLENGE_CAR = -1,
    DIALOGUEPAGE_TAJ_TUTORIAL,
    DIALOGUEPAGE_TAJ_ROOT,
    DIALOGUEPAGE_TAJ_VEHICLE_SELECT,
    DIALOGUEPAGE_TAJ_CHALLENGES,
    DIALOGUEPAGE_TAJ_4,
    DIALOGUEPAGE_TAJ_5,
    DIALOGUEPAGE_TAJ_6,
    DIALOGUEPAGE_TAJ_7,
    DIALOGUEPAGE_TAJ_8,
    DIALOGUEPAGE_TAJ_VEHICLE_SELECT_2 = 98,
    DIALOGUEPAGE_TAJ_CHALLENGES_2
};
enum TrackMenuTypes {
    TRACKMENU_TYPE_INIT = -1,
    TRACKMENU_TYPE_RESET_CURSOR,
    TRACKMENU_TYPE_FREE,
    TRACKMENU_TYPE_LOAD_LEVEL
};
enum CharacterSelectStatus {
    CHARSELECT_STATUS_UNCONFIRMED,
    CHARSELECT_STATUS_CONFIRMED,
    CHARSELECT_STATUS_READY,
};
typedef enum Cheats {
    CHEAT_CONTROL_TT = 1 << 0,
    CHEAT_CONTROL_DRUMSTICK = 1 << 1,
    CHEAT_MIRRORED_TRACKS = 1 << 2,
    CHEAT_HIGH_SPEED_RACING = 1 << 3,
    CHEAT_BIG_CHARACTERS = 1 << 4,
    CHEAT_SMALL_CHARACTERS = 1 << 5,
    CHEAT_MUSIC_MENU = 1 << 6,
    CHEAT_START_WITH_10_BANANAS = 1 << 7,
    CHEAT_HORN_CHEAT = 1 << 8,
    CHEAT_PRINT_COORDS = 1 << 9,
    CHEAT_DISPLAY_CREDITS = 1 << 10,
    CHEAT_DISABLE_WEAPONS = 1 << 11,
    CHEAT_DISABLE_BANANAS = 1 << 12,
    CHEAT_BANANAS_REDUCE_SPEED = 1 << 13,
    CHEAT_NO_LIMIT_TO_BANANAS = 1 << 14,
    CHEAT_ALL_BALLOONS_ARE_RED = 1 << 15,
    CHEAT_ALL_BALLOONS_ARE_GREEN = 1 << 16,
    CHEAT_ALL_BALLOONS_ARE_BLUE = 1 << 17,
    CHEAT_ALL_BALLOONS_ARE_YELLOW = 1 << 18,
    CHEAT_ALL_BALLOONS_ARE_RAINBOW = 1 << 19,
    CHEAT_MAXIMUM_POWER_UP = 1 << 20,
    CHEAT_TURN_OFF_ZIPPERS = 1 << 21,
    CHEAT_SELECT_SAME_PLAYER = 1 << 22,
    CHEAT_FOUR_WHEEL_DRIVER = 1 << 23,
    CHEAT_TWO_PLAYER_ADVENTURE = 1 << 24,
    CHEAT_ULTIMATE_AI = 1 << 25,
    CHEAT_FREE_BALLOON = 1 << 26,
    CHEAT_EPC_LOCK_UP_DISPLAY = 1 << 27,
    CHEAT_ROM_CHECKSUM = 1 << 28,
    MAX_CHEATS = 32
} Cheats;
typedef enum MENU_ID {
    MENU_TITLE,
    MENU_LOGOS,
    MENU_UNUSED_2,
    MENU_CHARACTER_SELECT,
    MENU_UNUSED_4,
    MENU_TRACK_SELECT_ADVENTURE,
    MENU_FILE_SELECT,
    MENU_UNUSED_7,
    MENU_UNUSED_8,
    MENU_UNUSED_9,
    MENU_MAGIC_CODES,
    MENU_MAGIC_CODES_LIST,
    MENU_OPTIONS,
    MENU_AUDIO_OPTIONS,
    MENU_SAVE_OPTIONS,
    MENU_TRACK_SELECT,
    MENU_UNUSED_16,
    MENU_RESULTS,
    MENU_UNUSED_18,
    MENU_GAME_SELECT,
    MENU_TROPHY_RACE_ROUND,
    MENU_TROPHY_RACE_RANKINGS,
    MENU_UNUSED_22,
    MENU_NEWGAME_CINEMATIC,
    MENU_GHOST_DATA,
    MENU_CREDITS,
    MENU_BOOT,
    MENU_UNUSED_27,
    MENU_CAUTION
} MENU_ID;
enum MenuResult {
    MENU_RESULT_CONTINUE,
    MENU_RESULT_RETURN_TO_GAME,
    MENU_RESULT_UNK2,
    MENU_RESULT_UNK3,
    MENU_RESULT_UNK4,
    MENU_RESULT_TRACKS_MODE,
    MENU_RESULT_UNK6,
    MENU_RESULT_UNK7,
    MENU_RESULT_UNK8,
    MENU_RESULT_UNK9,
    MENU_RESULT_UNK10,
    MENU_RESULT_UNK11,
    MENU_RESULT_UNK12,
    MENU_RESULT_UNK13,
    MENU_RESULT_UNK14,
    MENU_RESULT_UNK15,
    MENU_RESULT_UNK16,
    MENU_RESULT_UNK17,
    MENU_RESULT_UNK18,
};
enum MenuResultFlags {
    MENU_RESULT_FLAGS_0,
    MENU_RESULT_FLAGS_1 = (1 << 0),
    MENU_RESULT_FLAGS_2 = (1 << 1),
    MENU_RESULT_FLAGS_4 = (1 << 2),
    MENU_RESULT_FLAGS_8 = (1 << 3),
    MENU_RESULT_FLAGS_10 = (1 << 4),
    MENU_RESULT_FLAGS_20 = (1 << 5),
    MENU_RESULT_FLAGS_40 = (1 << 6),
    MENU_RESULT_FLAGS_80 = (1 << 7),
    MENU_RESULT_FLAGS_100 = (1 << 8),
    MENU_RESULT_FLAGS_200 = (1 << 9),
};
enum TrackFinishBits {
    RACE_UNATTEMPTED,
    RACE_VISITED = (1 << 0),
    RACE_CLEARED = (1 << 1),
    RACE_CLEARED_SILVER_COINS = (1 << 2),
};
typedef enum PakError {
    PAK_ERROR_NONE,
    PAK_ERROR_FATAL,
    PAK_ERROR_FULL,
    PAK_ERROR_CORRUPT
} PakError;
typedef enum TitleDemoIndex {
    DEMO_LEVEL_ID,
    DEMO_PLAYER_COUNT,
    DEMO_CUTSCENE_ID,
    DEMO_INDEX_SIZE
} TitleDemoIndex;
typedef struct MenuAsset {
    ObjectTransform trans;
    s16 spriteOffset;
    s8 unk1A;
    s8 unk1B;
    s8 unk1C;
    s8 unk1D;
    s8 unk1E;
    s8 unk1F;
} MenuAsset;
typedef struct unk80080BC8 {
    Vertex *vertices[2];
    Triangle *triangles[2];
    TextureHeader *texture[2];
    s32 unk18[2];
} unk80080BC8;
typedef struct unk80126460 {
    MenuElement elem[2];
} unk80126460;
typedef struct unk801263C0 {
    s8 channelIndex;
    s8 unk1;
    union {
        struct {
            s8 unk2a;
            s8 unk3;
        };
        s16 unk2;
    };
} unk801263C0;
typedef struct unk80126C54 {
    union {
        struct {
            u8 unk0;
            u8 unk1;
            u8 unk2;
            u8 unk3;
        };
        s32 unk0_s32;
    };
} unk80126C54;
typedef struct unk800DF83C {
    char *unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
} unk800DF83C;
typedef struct unk800DFA3C {
            s16 x;
            s16 y;
            u8 red;
            u8 green;
            u8 blue;
            u8 alpha;
            u8 opacity;
            u8 font;
            s16 alignmentFlags;
            char *text;
} unk800DFA3C;
typedef struct ButtonElement {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    s16 borderWidth;
    s16 borderHeight;
    s16 colourMin;
    s16 colourMax;
} ButtonElement;
typedef struct ButtonTextElement {
    s16 x;
    s16 y;
    s16 width;
    s16 height;
    s16 borderWidth;
    s16 borderHeight;
    s16 textPos[8];
} ButtonTextElement;
typedef struct CharacterSelectData {
    s8 upInput[2];
    s8 downInput[2];
    s8 rightInput[4];
    s8 leftInput[4];
    s16 voiceID;
} CharacterSelectData;
typedef struct SavefileInfo {
    u8 isAdventure2;
    u8 isStarted;
    u16 balloonCount;
    char name[4];
    u32 pad8;
} SavefileInfo;
typedef struct MenuColour {
    u8 red;
    u8 green;
    u8 blue;
    u8 alpha;
    u8 opacity;
} MenuColour;
typedef struct unk80126A80 {
    u8 pad0[0x13];
    s8 highlight;
} unk80126A80;
typedef struct SaveFileData {
             u8 saveFileType;
             u8 unk1;
             u8 balloonCount;
             u8 adventureTwo;
             s16 compressedFilename;
             u8 controllerIndex;
             u8 saveFileNumber;
             char *saveFileExt;
             u32 fileSize;
} SaveFileData;
typedef struct unk80126878 {
             char *text;
             char *text2;
             s16 x;
             s16 y;
             s32 colourIndex;
} unk80126878;
typedef struct unk80069D20 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 pad6[6];
    f32 unkC;
    f32 unk10;
    f32 unk14;
} unk80069D20;
typedef struct unk8009CA602 {
    ObjectTransform trans;
    s16 unk18;
    s16 unk1A;
    s8 unk1C;
    s8 unk1D;
} unk8009CA602;
typedef struct TitleScreenDemos {
    s8 levelId;
    s8 numberOfPlayers;
    s8 cutsceneId;
} TitleScreenDemos;
typedef struct TrackRenderDetails {
             char *hubName;
             char *trackName;
             s16 xOff;
             s16 yOff;
             u8 visible;
             u8 opacity;
    union {
        struct {
                       u8 copyViewPort;
                       u8 border;
        };
                   u16 viewPort;
    };
} TrackRenderDetails;
extern s32 gShowControllerPakMenu;
extern u8 *__ROM_END;
s32 rand_range(s32, s32);
void menu_button_free(void);
void menu_geometry_end(void);
void reset_title_logo_scale(void);
void menu_init(u32 menuId);
s32 menu_loop(Gfx **currDisplayList, Mtx **currHudMat, Vertex **currHudVerts, Triangle **currHudTris, s32 updateRate);
void menu_timestamp_render(s32 frameCount, s32 xPos, s32 yPos, u8 red, u8 green, u8 blue, u8 fontID);
void postrace_offsets(MenuElement *elements, f32 in, f32 mid, f32 out, s32 textOffset, s32 timestampOffset);
void trackmenu_set_records(void);
void menu_missing_controller(Gfx **dList, s32 updateRate);
void menu_logos_screen_init(void);
s32 menu_logo_screen_loop(s32 updateRate);
void init_title_screen_variables(void);
void menu_title_screen_init(void);
void titlescreen_free(void);
void menu_options_init(void);
void optionscreen_render(s32 updateRate);
void optionscreen_free(void);
void menu_audio_options_init(void);
void soundoptions_free(void);
void menu_save_options_init(void);
SIDeviceStatus savemenu_check_space(s32 controllerIndex, s32 *pakState, SaveFileData *file, s32 *index, s32 fileSize,
                                    s32 arg5);
void savemenu_blank_save_destination(SaveFileData *file, s32 *fileIndex);
s32 savemenu_input_source(s32 buttonsPressed, s32 direction);
s32 savemenu_input_dest(s32 buttonsPressed, s32 direction);
s32 savemenu_input_confirm(s32 buttonsPressed, s32 arg1);
void savemenu_free(void);
void menu_boot_init(void);
void bootscreen_free(void);
void bootscreen_init_cpak(void);
void pakmenu_free(void);
void cheatmenu_free(void);
void menu_magic_codes_list_init(void);
void cheatlist_exclusive(s32 code, s32 cheatA, s32 cheatB);
void cheatlist_free(void);
void charselect_prev(s32 context, s32 *arg1);
void titlescreen_controller_assign(s32 controllerIndex);
void menu_character_select_init(void);
void charselect_render_text(s32 updateRate);
void charselect_move(s32 playerID, s8 *direction, s32 bounds, u16 menuPickSoundId, u16 menuPickFailedSoundId);
void charselect_free(void);
void menu_caution_init(void);
void caution_free(void);
void gameselect_free(void);
void menu_file_select_init(void);
void fileselect_render_element(s32 imageID, s32 xOffset, s32 yOffset, s32 red, s32 green, s32 blue, s32 opacity);
void fileselect_free(void);
void menu_init_vehicle_textures(void);
void menu_init_arrow_textures(void);
void menu_track_select_unload(void);
void trackmenu_timetrial_sound(s32 updateRate);
s32 trackmenu_staff_beaten(s32 mapId);
void menu_adventure_track_init(void);
void adventuretrack_free(void);
void menu_dialogue_end(void);
void menu_close_dialogue(void);
void menu_racer_portraits(void);
void postrace_music_fade(s32 updateRate);
void postrace_free(void);
void menu_results_init(void);
void results_free(void);
void filename_decompress(u32 compressedFilename, char *output, s32 length);
s32 filename_compress(char *filename, s32 length);
void filename_init(s32 titleY, s32 x, s32 y, s32 font, s32 *targetX, char *fileName, s32 fileNameLength);
void menu_unload_bigfont(void);
void trophyround_adventure(void);
void trophyround_render( s32 updateRate);
void trophyround_free(void);
void rankings_free(void);
s32 get_trophy_race_world_id(void);
void ghostmenu_free(void);
void cinematic_start(s8 *params, s32 arg1, s32 endFlags, s32 skipFlagsA, s32 skipFlagsB, s8 *portraits);
void menu_cinematic_init(void);
void cinematic_free(void);
void menu_credits_init(void);
void credits_fade(s32 x1, s32 y1, s32 x2, s32 y2, s32 a);
void credits_free(void);
void menu_camera_centre(void);
void reset_controller_sticks(void);
void reset_character_id_slots(void);
s32 get_save_file_index(void);
s32 get_track_id_to_load(void);
s8 get_character_id_from_slot(s32 slot);
s8 get_character_id_from_slot_unused(s32 slot);
s8 get_player_selected_vehicle(s32 playerNum);
void set_player_selected_vehicle(s32 playerNum, s32 index);
s8 *charselect_status(void);
s8 get_player_character(s32 controllerIndex);
void enable_tracks_mode(s32 boolean);
s32 is_in_tracks_mode(void);
void set_magic_code_flags(s32 flags);
s32 get_filtered_cheats(void);
s32 get_number_of_active_players(void);
s32 get_active_player_count(void);
s32 get_multiplayer_racer_count(void);
Settings **get_all_save_files_ptr(void);
void menu_assetgroup_free(s16 *assetGroup);
void menu_asset_free(s32 assetID);
void menu_assetgroup_load(s16 *textureIndex);
void menu_imagegroup_load(s16 *imageSet);
void menu_image_load(s32 imageID);
void menu_imagegroup_free(void);
void dialogue_npc_finish(s32 npcID);
void dialogue_try_close(void);
s32 npc_dialogue_loop(u32 dialogueOption);
void set_option_text_colour(s32 condition);
void render_dialogue_option(char *text, s32 yOffset, s32 optionID);
void handle_menu_joystick_input(void);
void set_next_taj_challenge_menu(s32 arg0);
void set_menu_id_if_option_equal(s32 IDToCheck, s32 IDToSet);
s32 taj_menu_loop(void);
s32 dialogue_race_defeat(void);
s32 trophy_race_cabinet_menu_loop(void);
void dialogue_open_stub(void);
void dialogue_close_stub(void);
f32 dialogue_ortho(DialogueBoxBackground *arg0, Gfx **dList, Mtx **mat, Vertex **verts);
u64 *get_eeprom_settings_pointer(void);
s32 set_eeprom_settings_value(u64 valueToSet);
s32 unset_eeprom_settings_value(u64 valueToUnset);
u64 get_eeprom_settings(void);
s32 get_language(void);
void set_language(s32 language);
s32 is_adventure_two_unlocked(void);
s32 is_in_adventure_two(void);
s32 is_in_two_player_adventure(void);
s32 is_tt_unlocked(void);
s32 is_drumstick_unlocked(void);
s32 menu_character_select_loop(s32 updateRate);
s32 menu_caution_loop(s32 updateRate);
void fileselect_input_erase( s32 updateRate);
s32 menu_adventure_track_loop(s32 updateRate);
void postrace_message(SIDeviceStatus status);
s32 menu_boot_loop(s32 updateRate);
void menu_magic_codes_init(void);
s32 menu_game_select_loop(s32 updateRate);
s32 menu_ghost_data_loop(s32 updateRate);
s32 menu_trophy_race_round_loop(s32 updateRate);
void pakmenu_render( s32 updateRate);
PakError check_for_controller_pak_errors(void);
void menu_pause_init(void);
s32 menu_pause_loop( Gfx **dl, s32 updateRate);
s32 menu_track_select_loop(s32 updateRate);
SIDeviceStatus savemenu_load_destinations(void);
s32 filename_enter(s32 updateRate);
s32 menu_file_select_loop(s32 updateRate);
s32 fileselect_input_root(s32 updateRate);
void charselect_music_channels(s32 updateRate);
void gameselect_render(s32 updateRate);
void func_80083098(f32);
void trackmenu_assets(s32);
void render_track_selection_viewport_border(ObjectModel *objMdl);
void adventuretrack_render( s32 updateRate, s32 arg1, s32 arg2);
void menu_trophy_race_round_init(void);
void charselect_new_player(void);
s32 menu_save_options_loop(s32 updateRate);
s32 menu_cinematic_loop(s32 updateRate);
s32 menu_magic_codes_list_loop(s32 updateRate);
void menu_trophy_race_rankings_init(void);
void cheatmenu_checksum(void);
s32 menu_trophy_race_rankings_loop(s32 updateRate);
s32 menu_results_loop(s32 updateRate);
s32 menu_options_loop(s32 updateRate);
void charselect_pick(void);
void charselect_input(s8 *activePlayers);
s32 menu_audio_options_loop(s32 updateRate);
void ghostmenu_generate(void);
void filename_render( s32 updateRate);
void charselect_assign_ai(s32 charSlot);
void menu_number_render(s32 number, s32 x, s32 y, s32 r, s32 g, s32 b, s32 a, s32 font, s32 alignment);
void menu_element_render(s32 elementID);
void menu_input(void);
SIDeviceStatus savemenu_load_sources(void);
void menu_asset_load(s32 assetID);
s32 savemenu_input_message(s32 buttonsPressed, s32 yAxis);
void savemenu_render_element(SaveFileData *file, s32 x, s32 y);
void trackmenu_render_2D(s32 x, s32 y, char *hubName, char *trackName, s32 rectOpacity, s32 imageId, s32 copyViewPort, DrawTexture *arg7, s32 arg8);
void pausemenu_render( s32 updateRate);
s32 menu_postrace(Gfx **dList, Mtx **matrices, Vertex **vertices, s32 updateRate);
void ghostmenu_render( s32 updateRate);
s32 ghostmenu_erase(s32 id);
void cheatmenu_render(s32 updateRate);
void cheatlist_render(s32 updateRate);
void trackmenu_track_view(s32 updateRate);
void savemenu_render( s32 updateRate);
void draw_menu_elements(s32 state, MenuElement *elems, f32 scale);
void fileselect_render( s32 updateRate);
void savemenu_render_error(SIDeviceStatus deviceStatus);
SIDeviceStatus savemenu_write(void);
void trackmenu_setup_render(s32 updateRate);
void rankings_render_order(s32 updateRate);
void results_render( s32 updateRate, f32 opacity);
void func_80092188(s32 updateRate);
SIDeviceStatus func_80087F14(s32 *controllerIndex, s32 xAxisDirection);
void postrace_start(s32 finishState, s32 worldID);
void load_menu_text(s32 language);
s32 menu_controller_pak_loop(s32 updateRate);
void menu_game_select_init(void);
void func_8008FF1C(s32 updateRate);
void trackmenu_input(s32 updateRate);
void filename_trim(char *input, char *output);
void menu_ghost_data_init(void);
void update_controller_sticks(void);
s32 tt_menu_loop(void);
void menu_track_select_init(void);
void dialogue_tt_gamestatus(void);
s32 menu_title_screen_loop(s32 updateRate);
s32 menu_magic_codes_loop(s32 updateRate);
s32 menu_credits_loop(s32 updateRate);
void func_8007FFEC(s32 numberOfPanels);
void set_gIntDisFlag(u8 setting);
void init_save_data(void);
void func_80080580(Gfx **dList, s32 startX, s32 startY, s32 width, s32 height, s32 borderWidth, s32 borderHeight,
                   s32 colour, TextureHeader *tex);
void fileselect_input_copy(s32 updateRate);
s32 func_8008F618(Gfx **dList, Mtx **mtx);
void func_80080BC8(Gfx **);
void func_80080E90(Gfx **dList, s32 startX, s32 startY, s32 width, s32 height, s32 borderWidth, s32 borderHeight,
                   s32 colour0, s32 colour1, s32 colour2, s32 colour3);
void func_80084854(s32 updateRate);
void func_80098774(s32);
void postrace_viewport( s32 updateRate);
void draw_text_with_shadow(s32 dialogueBoxID, s32 xPos1, s32 yPos1, s32 xPos2,
    s32 yPos2, char *text, AlignmentFlags alignment, s32 textColour, s32 alpha);
typedef enum MenuTextures {
           TEXTURE_UNK_00,
           TEXTURE_UNK_01,
           TEXTURE_UNK_02,
           TEXTURE_UNK_03,
           TEXTURE_UNK_04,
           TEXTURE_UNK_05,
           TEXTURE_UNK_06,
           TEXTURE_UNK_07,
           TEXTURE_UNK_08,
           TEXTURE_UNK_09,
           TEXTURE_UNK_0A,
           TEXTURE_UNK_0B,
           TEXTURE_UNK_0C,
           TEXTURE_UNK_0D,
           TEXTURE_BACKGROUND_DINO_DOMAIN_TOP,
           TEXTURE_BACKGROUND_DINO_DOMAIN_BOTTOM,
           TEXTURE_BACKGROUND_SHERBERT_ISLAND_TOP,
           TEXTURE_BACKGROUND_SHERBERT_ISLAND_BOTTOM,
           TEXTURE_BACKGROUND_SNOWFLAKE_MOUNTAIN_TOP,
           TEXTURE_BACKGROUND_SNOWFLAKE_MOUNTAIN_BOTTOM,
           TEXTURE_BACKGROUND_DRAGON_FOREST_TOP,
           TEXTURE_BACKGROUND_DRAGON_FOREST_BOTTOM,
           TEXTURE_BACKGROUND_FUTURE_FUN_LAND_TOP,
           TEXTURE_BACKGROUND_FUTURE_FUN_LAND_BOTTOM,
           TEXTURE_ICON_VEHICLE_CAR_TOP,
           TEXTURE_ICON_VEHICLE_CAR_BOTTOM,
           TEXTURE_ICON_VEHICLE_HOVERCRAFT_TOP,
           TEXTURE_ICON_VEHICLE_HOVERCRAFT_BOTTOM,
           TEXTURE_ICON_VEHICLE_PLANE_TOP,
           TEXTURE_ICON_VEHICLE_PLANE_BOTTOM,
           TEXTURE_ICON_VEHICLE_SELECT_CAR,
           TEXTURE_ICON_VEHICLE_SELECT_CAR_HIGHLIGHT,
           TEXTURE_ICON_VEHICLE_SELECT_HOVERCRAFT,
           TEXTURE_ICON_VEHICLE_SELECT_HOVERCRAFT_HIGHLIGHT,
           TEXTURE_ICON_VEHICLE_SELECT_PLANE,
           TEXTURE_ICON_VEHICLE_SELECT_PLANE_HIGHLIGHT,
           TEXTURE_ICON_TIMETRIAL_ON_TOP,
           TEXTURE_ICON_TIMETRIAL_ON_BOTTOM,
           TEXTURE_ICON_TIMETRIAL_OFF_TOP,
           TEXTURE_ICON_TIMETRIAL_OFF_BOTTOM,
           TEXTURE_ICON_TIMETRIAL_OPT_ON,
           TEXTURE_ICON_TIMETRIAL_OPT_OFF,
           TEXTURE_ICON_TIMETRIAL_OPT_ON_HIGHLIGHT,
           TEXTURE_ICON_TIMETRIAL_OPT_OFF_HIGHLIGHT,
           TEXTURE_ICON_PLAYER_1,
           TEXTURE_ICON_PLAYER_2,
           TEXTURE_ICON_PLAYER_3,
           TEXTURE_ICON_PLAYER_4,
           TEXTURE_ICON_VEHICLE_TITLE,
           TEXTURE_ICON_TT_TITLE,
           TEXTURE_ICON_PORTRAIT_KRUNCH,
           TEXTURE_ICON_PORTRAIT_DIDDY,
           TEXTURE_ICON_PORTRAIT_DRUMSTICK,
           TEXTURE_ICON_PORTRAIT_BUMPER,
           TEXTURE_ICON_PORTRAIT_BANJO,
           TEXTURE_ICON_PORTRAIT_CONKER,
           TEXTURE_ICON_PORTRAIT_TIPTUP,
           TEXTURE_ICON_PORTRAIT_TT,
           TEXTURE_ICON_PORTRAIT_PIPSY,
           TEXTURE_ICON_PORTRAIT_TIMBER,
           TEXTURE_ICON_ARROW_LEFT,
           TEXTURE_ICON_ARROW_UP,
           TEXTURE_ICON_ARROW_RIGHT,
           TEXTURE_ICON_ARROW_DOWN,
           TEXTURE_ICON_BALLOON_GOLD,
           TEXTURE_ICON_BALLOON_DIAMOND,
           TEXTURE_ICON_MARKER_CROSS,
           TEXTURE_SURFACE_BUTTON_WOOD,
           TEXTURE_UNK_44,
           TEXTURE_UNK_45,
           TEXTURE_ICON_SAVE_BIN,
           TEXTURE_ICON_SAVE_N64,
           TEXTURE_ICON_SAVE_TT,
           TEXTURE_ICON_SAVE_CPAK,
           TEXTURE_ICON_SAVE_FILECABINET,
           TEXTURE_ICON_SAVE_GHOSTS,
           TEXTURE_UNK_4C,
           TEXTURE_UNK_4D,
           TEXTURE_UNK_4E,
           TEXTURE_UNK_4F,
           TEXTURE_TITLE_SEGMENT_01,
           TEXTURE_TITLE_SEGMENT_02,
           TEXTURE_TITLE_SEGMENT_03,
           TEXTURE_TITLE_SEGMENT_04,
           TEXTURE_TITLE_SEGMENT_05,
           TEXTURE_TITLE_SEGMENT_06,
           TEXTURE_TITLE_SEGMENT_07,
           TEXTURE_TITLE_SEGMENT_08,
           TEXTURE_TITLE_SEGMENT_09,
           TEXTURE_TITLE_SEGMENT_10,
           TEXTURE_TITLE_SEGMENT_11,
           TEXTURE_UNK_5B,
           TEXTURE_UNK_5C,
           TEXTURE_UNK_5D,
           TEXTURE_ICON_TT_HEAD,
           TEXTURE_UNK_5F,
           TEXTURE_UNK_60,
           TEXTURE_UNK_61,
           TEXTURE_UNK_62,
           TEXTURE_UNK_63,
           TEXTURE_UNK_64,
           TEXTURE_UNK_65,
           TEXTURE_UNK_66,
           TEXTURE_UNK_67,
           TEXTURE_UNK_68,
           TEXTURE_UNK_69,
           TEXTURE_UNK_6A,
           TEXTURE_UNK_6B,
           TEXTURE_UNK_6C,
           TEXTURE_UNK_6D,
           TEXTURE_UNK_6E,
           TEXTURE_UNK_6F,
           TEXTURE_UNK_70,
           TEXTURE_UNK_71,
           TEXTURE_UNK_72,
           TEXTURE_UNK_73,
           TEXTURE_UNK_74,
           TEXTURE_UNK_75,
           TEXTURE_UNK_76,
           TEXTURE_UNK_77,
           TEXTURE_UNK_78,
           TEXTURE_UNK_79,
           TEXTURE_UNK_7A,
           TEXTURE_UNK_7B,
           TEXTURE_UNK_7C,
           TEXTURE_UNK_7D,
           TEXTURE_UNK_7E,
           TEXTURE_UNK_7F,
    NUM_MENU_TEXTURES
} MenuTextures;
void pi_init(void);
u32 *asset_table_load(u32 assetIndex);
s32 asset_load(u32 assetIndex, u32 address, s32 assetOffset, s32 size);
u8 *asset_rom_offset(u32 assetIndex, u32 assetOffset);
s32 asset_table_size(u32 assetIndex);
void dmacopy(u32 romOffset, u32 ramAddress, s32 numBytes);
void dmacopy_v1(u32 romOffset, u32 ramAddress, s32 numBytes);
typedef u32 OSIntMask;
typedef u32 OSHWIntr;
extern OSIntMask osGetIntMask(void);
extern OSIntMask osSetIntMask(OSIntMask);
typedef u32 OSPageMask;
extern void osMapTLB(s32, OSPageMask, void *, u32, u32, s32);
extern void osMapTLBRdb(void);
extern void osUnmapTLB(s32);
extern void osUnmapTLBAll(void);
extern void osSetTLBASID(s32);
typedef struct {
    u32 errStatus;
    void *dramAddr;
    void *C2Addr;
    u32 sectorSize;
    u32 C1ErrNum;
    u32 C1ErrSector[4];
} __OSBlockInfo;
typedef struct {
    u32 cmdType;
    u16 transferMode;
    u16 blockNum;
    s32 sectorNum;
    u32 devAddr;
    u32 bmCtlShadow;
    u32 seqCtlShadow;
    __OSBlockInfo block[2];
} __OSTranxInfo;
typedef struct OSPiHandle_s {
    struct OSPiHandle_s *next;
    u8 type;
    u8 latency;
    u8 pageSize;
    u8 relDuration;
    u8 pulse;
    u8 domain;
    u32 baseAddress;
    u32 speed;
    __OSTranxInfo transferInfo;
} OSPiHandle;
typedef struct {
    u8 type;
    u32 address;
} OSPiInfo;
typedef struct {
    u16 type;
    u8 pri;
    u8 status;
    OSMesgQueue *retQueue;
} OSIoMesgHdr;
typedef struct {
    OSIoMesgHdr hdr;
    void *dramAddr;
    u32 devAddr;
    u32 size;
    OSPiHandle *piHandle;
} OSIoMesg;
typedef struct {
    s32 active;
    OSThread *thread;
    OSMesgQueue *cmdQueue;
    OSMesgQueue *evtQueue;
    OSMesgQueue *acsQueue;
    s32 (*dma)(s32, u32, void *, u32);
    s32 (*edma)(OSPiHandle *, s32, u32, void *, u32);
} OSDevMgr;
extern OSPiHandle *__osPiTable;
extern u32 osPiGetStatus(void);
extern s32 osPiGetDeviceType(void);
extern s32 osPiWriteIo(u32, u32);
extern s32 osPiReadIo(u32, u32 *);
extern s32 osPiStartDma(OSIoMesg *, s32, s32, u32, void *, u32, OSMesgQueue *);
extern void osCreatePiManager(OSPri, OSMesgQueue *, OSMesg *, s32);
extern OSPiHandle *osCartRomInit(void);
extern OSPiHandle *osLeoDiskInit(void);
extern OSPiHandle *osDriveRomInit(void);
extern s32 osEPiDeviceType(OSPiHandle *, OSPiInfo *);
extern s32 osEPiWriteIo(OSPiHandle *, u32 , u32 );
extern s32 osEPiReadIo(OSPiHandle *, u32 , u32 *);
extern s32 osEPiStartDma(OSPiHandle *, OSIoMesg *, s32);
extern s32 osEPiLinkHandle(OSPiHandle *);
typedef struct {
    u32 ctrl;
    u32 width;
    u32 burst;
    u32 vSync;
    u32 hSync;
    u32 leap;
    u32 hStart;
    u32 xScale;
    u32 vCurrent;
} OSViCommonRegs;
typedef struct {
    u32 origin;
    u32 yScale;
    u32 vStart;
    u32 vBurst;
    u32 vIntr;
} OSViFieldRegs;
typedef struct {
    u8 type;
    OSViCommonRegs comRegs;
    OSViFieldRegs fldRegs[2];
} OSViMode;
extern OSViMode osViModeTable[];
extern OSViMode osViModeNtscLpn1;
extern OSViMode osViModeNtscLpf1;
extern OSViMode osViModeNtscLan1;
extern OSViMode osViModeNtscLaf1;
extern OSViMode osViModeNtscLpn2;
extern OSViMode osViModeNtscLpf2;
extern OSViMode osViModeNtscLan2;
extern OSViMode osViModeNtscLaf2;
extern OSViMode osViModeNtscHpn1;
extern OSViMode osViModeNtscHpf1;
extern OSViMode osViModeNtscHan1;
extern OSViMode osViModeNtscHaf1;
extern OSViMode osViModeNtscHpn2;
extern OSViMode osViModeNtscHpf2;
extern OSViMode osViModePalLpn1;
extern OSViMode osViModePalLpf1;
extern OSViMode osViModePalLan1;
extern OSViMode osViModePalLaf1;
extern OSViMode osViModePalLpn2;
extern OSViMode osViModePalLpf2;
extern OSViMode osViModePalLan2;
extern OSViMode osViModePalLaf2;
extern OSViMode osViModePalHpn1;
extern OSViMode osViModePalHpf1;
extern OSViMode osViModePalHan1;
extern OSViMode osViModePalHaf1;
extern OSViMode osViModePalHpn2;
extern OSViMode osViModePalHpf2;
extern OSViMode osViModeMpalLpn1;
extern OSViMode osViModeMpalLpf1;
extern OSViMode osViModeMpalLan1;
extern OSViMode osViModeMpalLaf1;
extern OSViMode osViModeMpalLpn2;
extern OSViMode osViModeMpalLpf2;
extern OSViMode osViModeMpalLan2;
extern OSViMode osViModeMpalLaf2;
extern OSViMode osViModeMpalHpn1;
extern OSViMode osViModeMpalHpf1;
extern OSViMode osViModeMpalHan1;
extern OSViMode osViModeMpalHaf1;
extern OSViMode osViModeMpalHpn2;
extern OSViMode osViModeMpalHpf2;
extern OSViMode osViModeFpalLpn1;
extern OSViMode osViModeFpalLpf1;
extern OSViMode osViModeFpalLan1;
extern OSViMode osViModeFpalLaf1;
extern OSViMode osViModeFpalLpn2;
extern OSViMode osViModeFpalLpf2;
extern OSViMode osViModeFpalLan2;
extern OSViMode osViModeFpalLaf2;
extern OSViMode osViModeFpalHpn1;
extern OSViMode osViModeFpalHpf1;
extern OSViMode osViModeFpalHan1;
extern OSViMode osViModeFpalHaf1;
extern OSViMode osViModeFpalHpn2;
extern OSViMode osViModeFpalHpf2;
extern u32 osViGetStatus(void);
extern u32 osViGetCurrentMode(void);
extern u32 osViGetCurrentLine(void);
extern u32 osViGetCurrentField(void);
extern void *osViGetCurrentFramebuffer(void);
extern void *osViGetNextFramebuffer(void);
extern void osViSetXScale(f32);
extern void osViSetYScale(f32);
extern void osViExtendVStart(u32);
extern void osViSetSpecialFeatures(u32);
extern void osViSetMode(OSViMode *);
extern void osViSetEvent(OSMesgQueue *, OSMesg, u32);
extern void osViSwapBuffer(void *);
extern void osViBlack(u8);
extern void osViFade(u8, u16);
extern void osViRepeatLine(u8);
extern void osCreateViManager(OSPri);
extern u32 osAiGetStatus(void);
extern u32 osAiGetLength(void);
extern s32 osAiSetFrequency(u32);
extern s32 osAiSetNextBuffer(void *, u32);
typedef u64 OSTime;
typedef struct OSTimer_s {
 struct OSTimer_s *next;
 struct OSTimer_s *prev;
 OSTime interval;
 OSTime value;
 OSMesgQueue *mq;
 OSMesg msg;
} OSTimer;
extern OSTime osGetTime(void);
extern void osSetTime(OSTime);
extern int osSetTimer(OSTimer *, OSTime, OSTime,
       OSMesgQueue *, OSMesg);
extern int osStopTimer(OSTimer *);
typedef struct {
 u16 type;
 u8 status;
 u8 errno;
}OSContStatus;
typedef struct {
 u16 button;
 s8 stick_x;
 s8 stick_y;
 u8 errno;
} OSContPad;
typedef struct {
 void *address;
 u8 databuffer[32];
        u8 addressCrc;
 u8 dataCrc;
 u8 errno;
} OSContRamIo;
extern s32 osContInit(OSMesgQueue *, u8 *, OSContStatus *);
extern s32 osContReset(OSMesgQueue *, OSContStatus *);
extern s32 osContStartQuery(OSMesgQueue *);
extern s32 osContStartReadData(OSMesgQueue *);
extern s32 osContSetCh(u8);
extern void osContGetQuery(OSContStatus *);
extern void osContGetReadData(OSContPad *);
typedef struct {
  u16 fixed1;
  u16 start_address;
  u8 nintendo_chr[0x30];
  u8 game_title[16];
  u16 company_code;
  u8 body_code;
  u8 cart_type;
  u8 rom_size;
  u8 ram_size;
  u8 country_code;
  u8 fixed2;
  u8 version;
  u8 isum;
  u16 sum;
} OSGbpakId;
extern s32 osGbpakInit(OSMesgQueue *, OSPfs *, int);
extern s32 osGbpakPower(OSPfs *, s32);
extern s32 osGbpakGetStatus(OSPfs *, u8 *);
extern s32 osGbpakReadWrite(OSPfs *, u16, u16, u8 *, u16);
extern s32 osGbpakReadId(OSPfs *, OSGbpakId *, u8 *);
extern s32 osGbpakCheckConnector(OSPfs *, u8 *);
typedef struct {
  OSMesgQueue *__mq;
  int __channel;
  s32 __mode;
  u8 cmd_status;
} OSVoiceHandle;
typedef struct {
  u16 warning;
  u16 answer_num;
  u16 voice_level;
  u16 voice_sn;
  u16 voice_time;
  u16 answer[5];
  u16 distance[5];
} OSVoiceData;
extern s32 osVoiceInit(OSMesgQueue *, OSVoiceHandle *, int);
extern s32 osVoiceCheckWord(u8 *data);
extern s32 osVoiceClearDictionary(OSVoiceHandle *, u8);
extern s32 osVoiceControlGain(OSVoiceHandle *, s32, s32);
extern s32 osVoiceSetWord(OSVoiceHandle *, u8 *);
extern s32 osVoiceStartReadData(OSVoiceHandle *);
extern s32 osVoiceStopReadData(OSVoiceHandle *);
extern s32 osVoiceGetReadData(OSVoiceHandle *, OSVoiceData *);
extern s32 osVoiceMaskDictionary(OSVoiceHandle *, u8 *, int);
extern void osVoiceCountSyllables(u8 *, u32 *);
extern void osInvalDCache(void *, s32);
extern void osInvalICache(void *, s32);
extern void osWritebackDCache(void *, s32);
extern void osWritebackDCacheAll(void);
typedef struct {
 u16 *histo_base;
 u32 histo_size;
 u32 *text_start;
 u32 *text_end;
} OSProf;
extern void osProfileInit(OSProf *, u32 profcnt);
extern void osProfileStart(u32);
extern void osProfileFlush(void);
extern void osProfileStop(void);
extern void osThreadProfileClear(OSId);
extern void osThreadProfileInit(void);
extern void osThreadProfileStart(void);
extern void osThreadProfileStop(void);
extern u32 osThreadProfileReadCount(OSId);
extern u32 osThreadProfileReadCountTh(OSThread*);
extern OSTime osThreadProfileReadTime(OSId);
extern OSTime osThreadProfileReadTimeTh(OSThread*);
extern u32 osGetCount(void);
extern s32 osRomType;
extern void *osRomBase;
extern s32 osTvType;
extern s32 osResetType;
extern s32 osCicId;
extern s32 osVersion;
extern u32 osMemSize;
extern s32 osAppNMIBuffer[];
extern u64 osClockRate;
extern OSIntMask __OSGlobalIntMask;
extern void osInitialize(void);
extern void osExit(void);
extern u32 osGetMemSize(void);
extern s32 osAfterPreNMI(void);
extern s32 osEepromProbe(OSMesgQueue *);
extern s32 osEepromRead(OSMesgQueue *, u8, u8 *);
extern s32 osEepromWrite(OSMesgQueue *, u8, u8 *);
extern s32 osEepromLongRead(OSMesgQueue *, u8, u8 *, int);
extern s32 osEepromLongWrite(OSMesgQueue *, u8, u8 *, int);
extern OSPiHandle *osFlashReInit(u8 latency, u8 pulse,
                 u8 page_size, u8 rel_duration, u32 start);
extern OSPiHandle *osFlashInit(void);
extern void osFlashReadStatus(u8 *flash_status);
extern void osFlashReadId(u32 *flash_type, u32 *flash_maker);
extern void osFlashClearStatus(void);
extern s32 osFlashAllErase(void);
extern s32 osFlashSectorErase(u32 page_num);
extern s32 osFlashWriteBuffer(OSIoMesg *mb, s32 priority,
                void *dramAddr, OSMesgQueue *mq);
extern s32 osFlashWriteArray(u32 page_num);
extern s32 osFlashReadArray(OSIoMesg *mb, s32 priority, u32 page_num,
                void *dramAddr, u32 n_pages, OSMesgQueue *mq);
extern void osFlashChange(u32 flash_num);
extern void osFlashAllEraseThrough(void);
extern void osFlashSectorEraseThrough(u32 page_num);
extern s32 osFlashCheckEraseEnd(void);
extern u32 osVirtualToPhysical(void *);
extern void * osPhysicalToVirtual(u32);
extern u32 osDpGetStatus(void);
extern void osDpSetStatus(u32);
extern void osDpGetCounters(u32 *);
extern s32 osDpSetNextBuffer(void *, u64);
extern void bcopy(const void *, void *, int);
extern int bcmp(const void *, const void *, int);
extern void bzero(void *, int);
extern int sprintf(char *s, const char *format, ...);
extern void osSyncPrintf(const char *fmt, ...);
typedef struct _Region_s {
 u8 *r_startBufferAddress;
 u8 *r_endAddress;
 s32 r_bufferSize;
 s32 r_bufferCount;
 u16 r_freeList;
 u16 r_alignSize;
} OSRegion;
extern void *osCreateRegion(void *, u32, u32, u32);
extern void *osMalloc(void *);
extern void osFree(void *, void *);
extern s32 osGetRegionBufCount(void *);
extern s32 osGetRegionBufSize(void *);
extern void rmonMain( void * );
extern void rmonPrintf( const char *, ... );
typedef struct {
 u32 type;
 u32 flags;
 u64 *ucode_boot;
 u32 ucode_boot_size;
 u64 *ucode;
 u32 ucode_size;
 u64 *ucode_data;
 u32 ucode_data_size;
 u64 *dram_stack;
 u32 dram_stack_size;
 u64 *output_buff;
 u64 *output_buff_size;
 u64 *data_ptr;
 u32 data_size;
 u64 *yield_data_ptr;
 u32 yield_data_size;
} OSTask_t;
typedef union {
    OSTask_t t;
    long long int force_structure_alignment;
} OSTask;
typedef u32 OSYieldResult;
extern void osSpTaskLoad(OSTask *tp);
extern void osSpTaskStartGo(OSTask *tp);
extern void osSpTaskYield(void);
extern OSYieldResult osSpTaskYielded(OSTask *tp);
typedef struct {
 unsigned char *base;
 int fmt, siz;
 int xsize, ysize;
 int lsize;
 int addr;
 int w, h;
 int s, t;
} Image;
typedef struct {
 float col[3];
 float pos[3];
 float a1, a2;
} PositionalLight;
extern int guLoadTextureBlockMipMap(Gfx **glist, unsigned char *tbuf, Image *im,
  unsigned char startTile, unsigned char pal, unsigned char cms,
  unsigned char cmt, unsigned char masks, unsigned char maskt,
  unsigned char shifts, unsigned char shiftt, unsigned char cfs,
  unsigned char cft);
extern int guGetDPLoadTextureTileSz (int ult, int lrt);
extern void guDPLoadTextureTile (Gfx *glistp, void *timg,
   int texl_fmt, int texl_size,
   int img_width, int img_height,
   int uls, int ult, int lrs, int lrt,
   int palette,
   int cms, int cmt,
   int masks, int maskt,
   int shifts, int shiftt);
extern void guMtxIdent(Mtx *m);
extern void guMtxIdentF(float mf[4][4]);
extern void guOrtho(Mtx *m, float l, float r, float b, float t,
      float n, float f, float scale);
extern void guOrthoF(float mf[4][4], float l, float r, float b, float t,
       float n, float f, float scale);
extern void guFrustum(Mtx *m, float l, float r, float b, float t,
        float n, float f, float scale);
extern void guFrustumF(float mf[4][4], float l, float r, float b, float t,
         float n, float f, float scale);
extern void guPerspective(Mtx *m, u16 *perspNorm, float fovy,
     float aspect, float near, float far, float scale);
extern void guPerspectiveF(float mf[4][4], u16 *perspNorm, float fovy,
      float aspect, float near, float far, float scale);
extern void guLookAt(Mtx *m,
   float xEye, float yEye, float zEye,
   float xAt, float yAt, float zAt,
   float xUp, float yUp, float zUp);
extern void guLookAtF(float mf[4][4], float xEye, float yEye, float zEye,
        float xAt, float yAt, float zAt,
        float xUp, float yUp, float zUp);
extern void guLookAtReflect(Mtx *m, LookAt *l,
   float xEye, float yEye, float zEye,
   float xAt, float yAt, float zAt,
   float xUp, float yUp, float zUp);
extern void guLookAtReflectF(float mf[4][4], LookAt *l,
        float xEye, float yEye, float zEye,
        float xAt, float yAt, float zAt,
        float xUp, float yUp, float zUp);
extern void guLookAtHilite(Mtx *m, LookAt *l, Hilite *h,
                float xEye, float yEye, float zEye,
                float xAt, float yAt, float zAt,
                float xUp, float yUp, float zUp,
                float xl1, float yl1, float zl1,
                float xl2, float yl2, float zl2,
  int twidth, int theight);
extern void guLookAtHiliteF(float mf[4][4], LookAt *l, Hilite *h,
  float xEye, float yEye, float zEye,
  float xAt, float yAt, float zAt,
  float xUp, float yUp, float zUp,
  float xl1, float yl1, float zl1,
  float xl2, float yl2, float zl2,
  int twidth, int theight);
extern void guLookAtStereo(Mtx *m,
   float xEye, float yEye, float zEye,
   float xAt, float yAt, float zAt,
   float xUp, float yUp, float zUp,
   float eyedist);
extern void guLookAtStereoF(float mf[4][4],
         float xEye, float yEye, float zEye,
         float xAt, float yAt, float zAt,
         float xUp, float yUp, float zUp,
   float eyedist);
extern void guRotate(Mtx *m, float a, float x, float y, float z);
extern void guRotateF(float mf[4][4], float a, float x, float y, float z);
extern void guRotateRPY(Mtx *m, float r, float p, float y);
extern void guRotateRPYF(float mf[4][4], float r, float p, float h);
extern void guAlign(Mtx *m, float a, float x, float y, float z);
extern void guAlignF(float mf[4][4], float a, float x, float y, float z);
extern void guScale(Mtx *m, float x, float y, float z);
extern void guScaleF(float mf[4][4], float x, float y, float z);
extern void guTranslate(Mtx *m, float x, float y, float z);
extern void guTranslateF(float mf[4][4], float x, float y, float z);
extern void guPosition(Mtx *m, float r, float p, float h, float s,
         float x, float y, float z);
extern void guPositionF(float mf[4][4], float r, float p, float h, float s,
   float x, float y, float z);
extern void guMtxF2L(float mf[4][4], Mtx *m);
extern void guMtxL2F(float mf[4][4], Mtx *m);
extern void guMtxCatF(float m[4][4], float n[4][4], float r[4][4]);
extern void guMtxCatL(Mtx *m, Mtx *n, Mtx *res);
extern void guMtxXFMF(float mf[4][4], float x, float y, float z,
        float *ox, float *oy, float *oz);
extern void guMtxXFML(Mtx *m, float x, float y, float z,
        float *ox, float *oy, float *oz);
extern void guNormalize(float *x, float *y, float *z);
void guPosLight(PositionalLight *pl, Light *l,
                float xOb, float yOb, float zOb);
void guPosLightHilite(PositionalLight *pl1, PositionalLight *pl2,
                Light *l1, Light *l2,
                LookAt *l, Hilite *h,
                float xEye, float yEye, float zEye,
                float xOb, float yOb, float zOb,
                float xUp, float yUp, float zUp,
                int twidth, int theight);
extern int guRandom(void);
extern float sinf(float angle);
extern float cosf(float angle);
extern signed short sins (unsigned short angle);
extern signed short coss (unsigned short angle);
extern float sqrtf(float value);
extern void guParseRdpDL(u64 *rdp_dl, u64 nbytes, u8 flags);
extern void guParseString(char *StringPointer, u64 nbytes);
extern void
guBlinkRdpDL(u64 *rdp_dl_in, u64 nbytes_in,
             u64 *rdp_dl_out, u64 *nbytes_out,
             u32 x, u32 y, u32 radius,
             u8 red, u8 green, u8 blue,
             u8 flags);
extern void guParseGbiDL(u64 *gbi_dl, u32 nbytes, u8 flags);
extern void guDumpGbiDL(OSTask *tp,u8 flags);
typedef struct {
    int dataSize;
    int dlType;
    int flags;
    u32 paddr;
} guDLPrintCB;
typedef struct {
    long type;
    long length;
    long magic;
    char userdata[(((4096)*6)-(3*sizeof(long)))];
} RamRomBuffer;
extern long long int rspbootTextStart[], rspbootTextEnd[];
extern long long int gspFast3DTextStart[], gspFast3DTextEnd[];
extern long long int gspFast3DDataStart[], gspFast3DDataEnd[];
extern long long int gspFast3D_dramTextStart[], gspFast3D_dramTextEnd[];
extern long long int gspFast3D_dramDataStart[], gspFast3D_dramDataEnd[];
extern long long int gspFast3D_fifoTextStart[], gspFast3D_fifoTextEnd[];
extern long long int gspFast3D_fifoDataStart[], gspFast3D_fifoDataEnd[];
extern long long int gspF3DNoNTextStart[], gspF3DNoNTextEnd[];
extern long long int gspF3DNoNDataStart[], gspF3DNoNDataEnd[];
extern long long int gspF3DNoN_dramTextStart[];
extern long long int gspF3DNoN_dramTextEnd[];
extern long long int gspF3DNoN_dramDataStart[];
extern long long int gspF3DNoN_dramDataEnd[];
extern long long int gspF3DNoN_fifoTextStart[];
extern long long int gspF3DNoN_fifoTextEnd[];
extern long long int gspF3DNoN_fifoDataStart[];
extern long long int gspF3DNoN_fifoDataEnd[];
extern long long int gspLine3DTextStart[], gspLine3DTextEnd[];
extern long long int gspLine3DDataStart[], gspLine3DDataEnd[];
extern long long int gspLine3D_dramTextStart[], gspLine3D_dramTextEnd[];
extern long long int gspLine3D_dramDataStart[], gspLine3D_dramDataEnd[];
extern long long int gspLine3D_fifoTextStart[], gspLine3D_fifoTextEnd[];
extern long long int gspLine3D_fifoDataStart[], gspLine3D_fifoDataEnd[];
extern long long int gspSprite2DTextStart[], gspSprite2DTextEnd[];
extern long long int gspSprite2DDataStart[], gspSprite2DDataEnd[];
extern long long int gspSprite2D_dramTextStart[], gspSprite2D_dramTextEnd[];
extern long long int gspSprite2D_dramDataStart[], gspSprite2D_dramDataEnd[];
extern long long int gspSprite2D_fifoTextStart[], gspSprite2D_fifoTextEnd[];
extern long long int gspSprite2D_fifoDataStart[], gspSprite2D_fifoDataEnd[];
extern long long int aspMainTextStart[], aspMainTextEnd[];
extern long long int aspMainDataStart[], aspMainDataEnd[];
extern long long int gspF3DEX_fifoTextStart[], gspF3DEX_fifoTextEnd[];
extern long long int gspF3DEX_fifoDataStart[], gspF3DEX_fifoDataEnd[];
extern long long int gspF3DEX_NoN_fifoTextStart[], gspF3DEX_NoN_fifoTextEnd[];
extern long long int gspF3DEX_NoN_fifoDataStart[], gspF3DEX_NoN_fifoDataEnd[];
extern long long int gspF3DLX_fifoTextStart[], gspF3DLX_fifoTextEnd[];
extern long long int gspF3DLX_fifoDataStart[], gspF3DLX_fifoDataEnd[];
extern long long int gspF3DLX_NoN_fifoTextStart[], gspF3DLX_NoN_fifoTextEnd[];
extern long long int gspF3DLX_NoN_fifoDataStart[], gspF3DLX_NoN_fifoDataEnd[];
extern long long int gspF3DLX_Rej_fifoTextStart[], gspF3DLX_Rej_fifoTextEnd[];
extern long long int gspF3DLX_Rej_fifoDataStart[], gspF3DLX_Rej_fifoDataEnd[];
extern long long int gspF3DLP_Rej_fifoTextStart[], gspF3DLP_Rej_fifoTextEnd[];
extern long long int gspF3DLP_Rej_fifoDataStart[], gspF3DLP_Rej_fifoDataEnd[];
extern long long int gspL3DEX_fifoTextStart[], gspL3DEX_fifoTextEnd[];
extern long long int gspL3DEX_fifoDataStart[], gspL3DEX_fifoDataEnd[];
extern long long int gspF3DEX2_fifoTextStart[], gspF3DEX2_fifoTextEnd[];
extern long long int gspF3DEX2_fifoDataStart[], gspF3DEX2_fifoDataEnd[];
extern long long int gspF3DEX2_NoN_fifoTextStart[],gspF3DEX2_NoN_fifoTextEnd[];
extern long long int gspF3DEX2_NoN_fifoDataStart[],gspF3DEX2_NoN_fifoDataEnd[];
extern long long int gspF3DEX2_Rej_fifoTextStart[],gspF3DEX2_Rej_fifoTextEnd[];
extern long long int gspF3DEX2_Rej_fifoDataStart[],gspF3DEX2_Rej_fifoDataEnd[];
extern long long int gspF3DLX2_Rej_fifoTextStart[],gspF3DLX2_Rej_fifoTextEnd[];
extern long long int gspF3DLX2_Rej_fifoDataStart[],gspF3DLX2_Rej_fifoDataEnd[];
extern long long int gspL3DEX2_fifoTextStart[], gspL3DEX2_fifoTextEnd[];
extern long long int gspL3DEX2_fifoDataStart[], gspL3DEX2_fifoDataEnd[];
extern long long int gspF3DEX2_xbusTextStart[], gspF3DEX2_xbusTextEnd[];
extern long long int gspF3DEX2_xbusDataStart[], gspF3DEX2_xbusDataEnd[];
extern long long int gspF3DEX2_NoN_xbusTextStart[],gspF3DEX2_NoN_xbusTextEnd[];
extern long long int gspF3DEX2_NoN_xbusDataStart[],gspF3DEX2_NoN_xbusDataEnd[];
extern long long int gspF3DEX2_Rej_xbusTextStart[],gspF3DEX2_Rej_xbusTextEnd[];
extern long long int gspF3DEX2_Rej_xbusDataStart[],gspF3DEX2_Rej_xbusDataEnd[];
extern long long int gspF3DLX2_Rej_xbusTextStart[],gspF3DLX2_Rej_xbusTextEnd[];
extern long long int gspF3DLX2_Rej_xbusDataStart[],gspF3DLX2_Rej_xbusDataEnd[];
extern long long int gspL3DEX2_xbusTextStart[], gspL3DEX2_xbusTextEnd[];
extern long long int gspL3DEX2_xbusDataStart[], gspL3DEX2_xbusDataEnd[];
typedef void (*OSErrorHandler)(s16, s16, ...);
OSErrorHandler osSetErrorHandler(OSErrorHandler);
typedef struct {
    u32 magic;
    u32 len;
    u32 *base;
    s32 startCount;
    s32 writeOffset;
} OSLog;
typedef struct {
    u32 magic;
    u32 timeStamp;
    u16 argCount;
    u16 eventID;
} OSLogItem;
typedef struct {
    u32 magic;
    u32 version;
} OSLogFileHdr;
void osCreateLog(OSLog *log, u32 *base, s32 len);
void osLogEvent(OSLog *log, s16 code, s16 numArgs, ...);
void osFlushLog(OSLog *log);
u32 osLogFloat(f32);
extern void osDelay(int count);
extern u32 __osSpGetStatus(void);
extern void __osSpSetStatus(u32);
extern s32 __osSpSetPc(u32);
extern s32 __osSpRawWriteIo(u32, u32);
extern s32 __osSpRawReadIo(u32, u32 *);
extern s32 __osSpRawStartDma(s32, u32, void *, u32);
typedef struct {
    short type;
    char misc[30];
} OSScMsg;
typedef struct OSScTask_s {
    struct OSScTask_s *next;
    u32 state;
    u32 flags;
    void *framebuffer;
    OSTask list;
    OSMesgQueue *msgQ;
    OSMesg msg;
    s32 unk58;
    s32 unk5C;
    s32 unk60;
    s32 unk64;
    s32 unk68;
    s32 unk6C;
} OSScTask;
typedef struct SCClient_s {
    u8 id;
    struct SCClient_s *next;
    OSMesgQueue *msgQ;
} OSScClient;
typedef struct {
    OSScMsg retraceMsg;
    OSScMsg prenmiMsg;
    OSMesgQueue interruptQ;
    OSMesg intBuf[8];
    OSMesgQueue cmdQ;
    OSMesg cmdMsgBuf[8];
    OSThread thread;
    OSScClient *clientList;
    OSScTask *audioListHead;
    OSScTask *gfxListHead;
    OSScTask *audioListTail;
    OSScTask *gfxListTail;
    OSScTask *curRSPTask;
    OSScTask *curRDPTask;
   OSScTask *unkTask;
    u32 frameCount;
    s32 doAudio;
} OSSched;
void osCreateScheduler(OSSched *s, void *stack, OSPri priority,
                                  u8 mode, u8 numFields);
void osScAddClient(OSSched *s, OSScClient *c, OSMesgQueue *msgQ, u8 id);
OSMesgQueue *osScGetInterruptQ(OSSched *s);
void func_80079760(OSSched *s);
void osScRemoveClient(OSSched *s, OSScClient *c);
OSMesgQueue *osScGetCmdQ(OSSched *s);
enum AudioVolumeBehaviour {
    VOLUME_NORMAL,
    VOLUME_LOWER,
    VOLUME_LOWER_AMBIENT,
    VOLUME_UNK03,
};
typedef struct SoundData {
 u16 soundBite;
 u8 volume;
 u8 minVolume;
 u8 pitch;
 u8 unk5;
 u16 range;
 u8 priority;
 u8 unk9;
} SoundData;
typedef struct MusicData {
    u8 volume;
    u8 tempo;
    u8 reverb;
} MusicData;
typedef struct DelayedSound {
               u16 soundId;
               s16 timer;
               SoundHandle *handlePtr;
} DelayedSound;
extern void set_voice_limit(ALCSPlayer *seqp, u8 voiceLimit);
extern void alCSPSetFadeIn(ALCSPlayer *seqp, u8 chan, ALPan pan);
extern void alFxReverbSet(u8 setting);
extern u8 alCSPGetFadeIn(ALCSPlayer *seqp, u8 chan);
void audio_init(OSSched *sc);
void sound_volume_reset(u8 skipReset);
void sound_volume_change(s32 behaviour);
void music_change_off(void);
void music_change_on(void);
void music_play(u8 seqID);
void music_voicelimit_set(u8 voiceLimit);
void music_voicelimit_change_off(void);
void music_voicelimit_change_on(void);
void music_jingle_voicelimit_set(u8 voiceLimit);
void music_fade(s32 time);
void music_volume_reset(void);
void sound_update_queue(u8 updateRate);
void sound_play_delayed(u16 soundId, SoundHandle *handlePtr, f32 delayTime);
void sound_clear_delayed(void);
u16 music_channel_get_mask(void);
void music_dynamic_set(u16 channelMask);
void music_channel_off(u8 channel);
s32 music_channel_active(s32 channel);
void music_channel_on(u8 channel);
void music_channel_pan_set(u8 channel, ALPan pan);
void music_channel_volume_set(u8 channel, u8 volume);
void music_channel_fade_set(u8 channel, ALPan fade);
u8 music_channel_fade(u8 channel);
void music_channel_reset_all(void);
void music_tempo_set_relative(f32 tempo);
void music_tempo_set(s32 tempo);
s16 music_tempo(void);
u8 music_is_playing(void);
void music_jingle_play_safe(u8 jingleID);
void sound_jingle_tempo_set(s32 tempo);
void music_stop(void);
u8 music_can_play(void);
void music_jingle_stop(void);
u8 music_current_sequence(void);
u8 music_jingle_current(void);
void music_volume_set(u8 volume);
void music_volume_config_set(u32 slider_val);
u8 music_volume(void);
s32 music_volume_config(void);
void music_jingle_volume_set(u8 arg0);
void music_jingle_pan_set(ALPan pan);
void music_jingle_play(u8 seqID);
u32 music_jingle_playing(void);
u16 sound_distance(u16 soundId);
void sound_play_spatial(u16 soundID, f32 x, f32 y, f32 z, SoundHandle *handlePtr);
void sound_play_direct(u16 soundID, SoundHandle *handlePtr);
u16 sound_count(void);
u8 music_sequence_count(void);
void sound_table_properties(SoundData **table, s32 *size, s32 *count);
u8 sound_is_looped(u16 soundID);
ALCSPlayer *sound_seqplayer_init(s32 maxVoices, s32 maxEvents);
void music_sequence_start(u8 seqID, ALCSPlayer *seqPlayer);
void music_sequence_stop(ALCSPlayer *seqPlayer);
void sound_reverb_set(u8 setting);
void func_80063A90(ALCSPlayer *seqp, u8 channel);
void sound_volume_set_relative(u16 soundID, SoundHandle soundHandle, u8 volume);
void music_sequence_init(ALCSPlayer *seqp, void *sequence, u8 *seqID, ALCSeq *seq);
void sound_play(u16 soundID, SoundHandle* handlePtr);
f32 music_animation_fraction(void);
enum SpriteAnimMode {
    SPRITE_ANIM_NORMALIZED,
    SPRITE_ANIM_FRAME_INDEX
};
enum ViewportCount {
    VIEWPORT_LAYOUT_1_PLAYER,
    VIEWPORT_LAYOUT_2_PLAYERS,
    VIEWPORT_LAYOUT_3_PLAYERS,
    VIEWPORT_LAYOUT_4_PLAYERS
};
enum ViewPortFlags {
    VIEWPORT_EXTRA_BG = 0x0001,
    VIEWPORT_UNK_02 = 0x0002,
    VIEWPORT_UNK_04 = 0x0004,
    VIEWPORT_X_CUSTOM = 0x0008,
    VIEWPORT_Y_CUSTOM = 0x0010,
    VIEWPORT_WIDTH_CUSTOM = 0x0020,
    VIEWPORT_HEIGHT_CUSTOM = 0x0040
};
typedef struct Camera {
                 ObjectTransform trans;
                 f32 cam_unk_18;
                 f32 boomLength;
                 f32 cam_unk_20;
                 f32 x_velocity;
                 f32 y_velocity;
                 f32 z_velocity;
                 f32 shakeMagnitude;
                 s16 cameraSegmentID;
                 s16 mode;
                 s16 pitch;
                 s8 shakeTimer;
                 u8 zoom;
                 u8 unk3C;
                 u8 unk3D;
                 u8 unk3E;
                 u8 unk3F;
                 ObjectHeader *header;
  } Camera;
typedef struct ScreenViewport {
               s32 x1;
               s32 y1;
               s32 x2;
               s32 y2;
               s32 posX;
               s32 posY;
               s32 width;
               s32 height;
               s32 scissorX1;
               s32 scissorY1;
               s32 scissorX2;
               s32 scissorY2;
               s32 flags;
} ScreenViewport;
void cam_set_zoom(s32 cameraID, s32 zoomLevel);
void enable_pal_viewport_height_adjust(s8 setting);
void cam_shake_off(void);
void cam_shake_on(void);
 f32 cam_get_fov(void);
void cam_set_fov(f32 camFieldOfView);
MtxF *mtx_get_modelmtx_s16(void);
s32 cam_get_viewport_layout(void);
s32 get_current_viewport(void);
void camera_init_tracks_menu(Gfx **dList, Mtx **mtxS);
f32 get_distance_to_active_camera(f32 xPos, f32 yPos, f32 zPos);
void camera_reset(s32 xPos, s32 yPos, s32 zPos, s32 angleZ, s32 angleX, s32 angleY);
void write_to_object_render_stack(s32 stackPos, f32 xPos, f32 yPos, f32 zPos, s16 arg4, s16 arg5, s16 arg6);
void disable_cutscene_camera(void);
s8 check_if_showing_cutscene_camera(void);
s32 cam_set_layout(s32 layoutID);
void set_active_camera(s32 num);
void camEnableUserView(s32 viewPortIndex, s32 arg1);
void camDisableUserView(s32 viewPortIndex, s32 arg1);
s32 check_viewport_background_flag(s32 viewPortIndex);
void viewport_menu_set(s32 viewPortIndex, s32 x1, s32 y1, s32 x2, s32 y2);
void set_viewport_properties(s32 viewPortIndex, s32 posX, s32 posY, s32 width, s32 height);
s32 copy_viewport_background_size_to_coords(s32 viewPortIndex, s32 *x1, s32 *y1, s32 *x2, s32 *y2);
void copy_viewport_frame_size_to_coords(s32 viewPortIndex, s32 *x1, s32 *y1, s32 *x2, s32 *y2);
void copy_framebuffer_size_to_coords(s32 *x1, s32 *y1, s32 *x2, s32 *y2);
void set_ortho_matrix_height(f32 value);
void mtx_ortho(Gfx **dList, Mtx **mtx);
void mtx_perspective(Gfx **dList, Mtx **mtx);
void viewport_rsp_set(Gfx **dList, s32 halfWidth, s32 halfHeight, s32 centerX, s32 centerY);
void viewport_reset(Gfx **dList);
void mtx_world_origin(Gfx **dList, Mtx **mtx);
void cam_set_sprite_anim_mode(s32 setting);
Camera *cam_get_active_camera_no_cutscenes(void);
Camera *cam_get_active_camera(void);
Camera *cam_get_cameras(void);
MtxF *get_projection_matrix_f32(void);
Mtx *get_projection_matrix_s16(void);
MtxF *get_camera_matrix(void);
f32 get_distance_to_camera(f32 x, f32 y, f32 z);
void set_camera_shake_by_distance(f32 x, f32 y, f32 z, f32 dist, f32 magnitude);
void set_camera_shake(f32 magnitude);
void func_80067D3C(Gfx **dList, Mtx **mats);
void render_ortho_triangle_image(Gfx **dList, Mtx **mtx, Vertex **vtx, ObjectSegment *segment, Sprite *sprite, s32 flags);
s32 render_sprite_billboard(Gfx **dList, Mtx **mtx, Vertex **vtx, Object *obj, Sprite *sprite, s32 flags);
s32 mtx_cam_push(Gfx **dList, Mtx **mtx, ObjectTransform *trans, f32 scaleY, f32 offsetY);
void viewport_scissor(Gfx **dList);
void mtx_pop(Gfx **dList);
void copy_viewports_to_stack(void);
void mtx_head_push(Gfx **dList, Mtx **mtx, ModelInstance *modInst, s16 headAngle);
void mtx_shear_push(Gfx **dList, Mtx **mtx, Object *obj, Object *objBase, f32 shear);
void cam_init(void);
void viewport_main(Gfx **dlist, Mtx **mats);
enum TransitionStatus {
    TRANSITION_LEVELSWAP = -1,
    TRANSITION_NONE,
    TRANSITION_ACTIVE
};
typedef struct FadeTransition {
             u8 type;
             u8 red;
             u8 green;
             u8 blue;
             u16 duration;
             u16 endTimer;
} FadeTransition;
void enable_new_screen_transitions(void);
void disable_new_screen_transitions(void);
u32 check_fadeout_transition(void);
void transition_end(void);
s32 transition_update(s32 updateRate);
void transition_render(Gfx **dList, Mtx **mtx, Vertex **vtx);
void transition_render_fullscreen(Gfx **dList, Mtx **mtx, Vertex **vtx);
void transition_render_barndoor_hor(Gfx **dList, Mtx **mtx, Vertex **vtx);
void transition_render_barndoor_vert(Gfx **dList, Mtx **mtx, Vertex **vtx);
void transition_render_barndoor_diag(Gfx **dList, Mtx **mtx, Vertex **vtx);
void transition_render_blank(Gfx **dList, Mtx **mtx, Vertex **vtx);
void transition_fullscreen_start(FadeTransition *transition);
void transition_init_blank(FadeTransition *transition);
void transition_update_fullscreen(s32 updateRate);
void transition_update_blank(s32 updateRate);
s32 transition_begin(FadeTransition *transition);
void transition_render_circle(Gfx **dList, Mtx **mtx, Vertex **vtx);
void transition_update_shape(s32 updateRate);
void transition_init_shape(FadeTransition *transition, s32 numVerts, s32 numTris, s16 *coords, u8 *nextPos,
                           u8 *targetPos, u8 *nextAlpha, u8 *targetAlpha, u8 *vertIndices);
void transition_update_circle(s32 updateRate);
void transition_render_waves(Gfx **dList, Mtx **mtx, Vertex **vtx);
void transition_init_circle(FadeTransition *transition);
typedef enum ActivePlayers {
    PLAYER_COMPUTER = -1,
    PLAYER_ONE,
    PLAYER_TWO,
    PLAYER_THREE,
    PLAYER_FOUR
} ActivePlayers;
typedef enum CameraZoom {
    ZOOM_MEDIUM,
    ZOOM_FAR,
    ZOOM_CLOSE,
    ZOOM_VERY_CLOSE
} CameraZoom;
typedef enum BoostSound {
    BOOST_NONE,
    BOOST_RACE_START,
    BOOST_SOUND_UNK2,
    BOOST_SOUND_UNK3,
    BOOST_SOUND_UNK4
} BoostSound;
typedef enum ObjectElevation {
    ELEVATION_LOW,
    ELEVATION_NORMAL,
    ELEVATION_HIGH,
    ELEVATION_HIGHEST
} ObjectElevation;
typedef enum BoostType {
    BOOST_SMALL,
    BOOST_MEDIUM,
    BOOST_LARGE,
    BOOST_UNK3,
    EMPOWER_BOOST,
    BOOST_SMALL_FAST = 4,
    BOOST_MEDIUM_FAST,
    BOOST_LARGE_FAST
} BoostType;
typedef enum AISkill {
    AI_MASTER,
    AI_EXPERT,
    AI_HARD,
    AI_MEDIUM,
    AI_EASY
} AISkill;
typedef enum AttackType {
    ATTACK_NONE,
    ATTACK_EXPLOSION,
    ATTACK_SPIN,
    ATTACK_UNK3,
    ATTACK_SQUISHED,
    ATTACK_FLUNG,
    ATTACK_BUBBLE
} AttackType;
typedef enum ShieldType {
    SHIELD_NONE,
    SHIELD_LEVEL1,
    SHIELD_LEVEL2,
    SHIELD_LEVEL3
} ShieldType;
typedef enum MagnetType {
    MAGNET_LEVEL1,
    MAGNET_LEVEL2,
    MAGNET_LEVEL3
} MagnetType;
typedef enum WeaponType {
    WEAPON_NONE = -1,
    WEAPON_ROCKET_HOMING,
    WEAPON_ROCKET,
    WEAPON_TRIPMINE,
    WEAPON_OIL_SLICK,
    WEAPON_NITRO_LEVEL_1,
    WEAPON_MAGNET_LEVEL_1,
    WEAPON_MAGNET_LEVEL_3,
    WEAPON_MAGNET_LEVEL_2,
    WEAPON_NITRO_LEVEL_2,
    WEAPON_UNK_09,
    WEAPON_BUBBLE_TRAP,
    WEAPON_UNK_11,
    WEAPON_SHIELD_LEVEL_1,
    WEAPON_SHIELD_LEVEL_2,
    WEAPON_SHIELD_LEVEL_3,
    WEAPON_NITRO_LEVEL_3,
    NUM_WEAPON_TYPES
} WeaponType;
typedef enum LightFlags {
    RACER_LIGHT_UNK00 = 0,
    RACER_LIGHT_TIMER = 0xF,
    RACER_LIGHT_UNK10 = (1 << 4),
    RACER_LIGHT_UNK20 = (1 << 5),
    RACER_LIGHT_NIGHT = (1 << 6),
    RACER_LIGHT_BRAKE = (1 << 7)
} LightFlags;
typedef enum RacerAIBehaviours {
    AI_EMPOWERED_BOOST,
    AI_GETS_BALLOON,
    AI_UNK_2,
    AI_BLUE_BALLOON
} RacerAIBehaviours;
typedef enum TajInteraction {
    TAJ_WANDER,
    TAJ_DIALOGUE,
    TAJ_TELEPORT,
} TajInteraction;
typedef enum RacerEggFlags {
    RACER_EGG_NONE,
    RACER_EGG_MASK = 0xF,
    RACER_EGG_HATCHING = (1 << 6),
    RACER_EGG_HELD = (1 << 7)
} RacerEggFlags;
typedef struct AIBehaviourTable {
    f32 unk0;
    f32 unk4;
    s8 percentages[4][4];
} AIBehaviourTable;
s32 roll_percent_chance(s32 chance);
void apply_plane_tilt_anim(s32 updateRate, Object *obj, Object_Racer *racer);
void racer_attack_handler_plane(Object *obj, Object_Racer *racer);
void update_carpet(s32 updateRate, f32 updateRateF, Object *obj, Object_Racer *racer);
void set_racer_tail_lights(Object_Racer *racer);
s32 should_taj_teleport(void);
void set_taj_status(TajInteraction status);
void slowly_reset_head_angle(Object_Racer *racer);
void func_80052988(Object *obj, Object_Racer *racer, s32 action, s32 arg3, s32 duration, s32 arg5, s32 flags, s32 arg7);
void handle_car_steering(Object_Racer *racer);
void func_800535C4(Object *obj, Object_Racer *racer);
void handle_car_velocity_control(Object_Racer *racer);
void play_char_horn_sound(Object *obj, Object_Racer *racer);
void racer_play_sound(Object *obj, s32 soundID);
void racer_play_sound_after_delay(Object *obj, s32 soundID, s32 delay);
void func_800575EC(Object *obj, Object_Racer *racer);
void handle_base_steering(Object_Racer *racer, s32 updateRate, f32 updateRateF);
void second_racer_camera_update(Object *obj, Object_Racer *racer, s32 mode, f32 updateRateF);
void get_timestamp_from_frames(s32 frameCount, s32 *minutes, s32 *seconds, s32 *hundredths);
void allocate_ghost_data(void);
void timetrial_reset_player_ghost(void);
void timetrial_swap_player_ghost(s32 mapID);
s32 timetrial_map_id(void);
s32 timetrial_load_player_ghost(s32 controllerID, s32 mapId, s16 arg2, s16 *characterID, s16 *time);
s32 load_tt_ghost(s32 ghostOffset, s32 size, s16 *outTime);
void timetrial_free_staff_ghost(void);
SIDeviceStatus timetrial_write_player_ghost(s32 controllerIndex, s32 mapId, s16 arg2, s16 arg3, s16 arg4);
s16 timetrial_ghost_full(void);
void disable_racer_input(void);
void racer_set_dialogue_camera(void);
void drm_checksum_balloon(void);
void drm_vehicle_traction(void);
s32 turn_head_towards_object(Object *obj, Object_Racer *racer, Object *targetObj, f32 distance);
void onscreen_ai_racer_physics(Object *obj, Object_Racer *racer, s32 arg2);
void racer_update_progress(Object_Racer *racer);
f32 handle_racer_top_speed(Object *obj, Object_Racer *racer);
void play_random_character_voice(Object *obj, s32 soundID, s32 range, s32 flags);
void apply_vehicle_rotation_offset(Object_Racer *obj, s32 max, s16 yRotation, s16 xRotation, s16 zRotation);
void set_position_goal_from_path(Object *obj, Object_Racer *racer, f32 *x, f32 *y, f32 *z);
void update_onscreen_AI_racer(Object *obj, Object_Racer *racer, s32 updateRate, f32 updateRateF);
void update_camera_hovercraft(f32 updateRate, Object *obj, Object_Racer *racer);
void update_camera_plane(f32 updateRate, Object *obj, Object_Racer *racer);
void update_camera_loop(f32 updateRateF, Object *obj, Object_Racer *racer);
void update_camera_car(f32 updateRate, Object *obj, Object_Racer *racer);
void update_camera_finish_challenge(f32 arg0, Object *obj, Object_Racer *racer);
void update_camera_finish_race(f32 arg0, Object *obj, Object_Racer *racer);
void update_camera_fixed(f32 updateRate, Object *obj, Object_Racer *racer);
void handle_racer_head_turning(Object *obj, Object_Racer *racer, s32 updateRate);
void racer_approach_object(Object *obj, Object_Racer *racer, f32 divisor);
void obj_init_racer(Object *obj, LevelObjectEntry_Racer *racer);
void racer_AI_pathing_inputs(Object *obj, Object_Racer *racer, s32 updateRate);
void increment_ai_behaviour_chances(Object *obj, Object_Racer *racer, s32 updateRate);
void onscreen_ai_racer_physics(Object *obj, Object_Racer *racer, s32 updateRate);
void update_player_camera(Object *obj, Object_Racer *racer, f32 updateRateF);
void racer_spinout_car(Object* obj, Object_Racer* racer, s32 updateRate, f32 updateRateF);
void racer_attack_handler_car(Object* obj, Object_Racer* racer, s32 updateRate);
void racer_attack_handler_hovercraft(Object* obj, Object_Racer* racer);
void racer_enter_door(Object_Racer *racer, s32 updateRate);
void func_8005250C(Object* obj, Object_Racer* racer, s32 updateRate);
void update_car_velocity_ground(Object* obj, Object_Racer* racer, s32 updateRate, f32 updateRateF);
f32 rotate_racer_in_water(Object *obj, Object_Racer *racer, Vec3f *pos, s8 arg3, s32 updateRate, s32 arg5, f32 arg6);
void update_AI_racer(Object* obj, Object_Racer* racer, s32 updateRate, f32 updateRateF);
void func_80042D20(Object *obj, Object_Racer *racer, s32 updateRate);
void handle_racer_items(Object *obj, Object_Racer *racer, s32 updateRate);
void drop_bananas(Object *obj, Object_Racer *racer, s32 number);
void update_player_racer(Object *obj, s32 updateRate);
void racer_update_eggs(Object **racerObjs);
void timetrial_ghost_write(Object *obj, s32 updateRate);
void func_80046524(s32 updateRate, f32 updateRateF, Object* obj, Object_Racer* racer);
void func_80053750(Object *objRacer, Object_Racer *racer, f32 updateRateF);
void func_80054FD0(Object *racerObj, Object_Racer *racer, s32 updateRate);
void func_8004F7F4(s32 updateRate, f32 updateRateF, Object* racerObj, Object_Racer* racer);
s32 timetrial_ghost_read(Object *obj);
void update_car_velocity_offground(Object *obj, Object_Racer *racer, s32, f32);
void func_80059208(Object* obj, Object_Racer* racer, s32 updateRate);
void func_80049794(s32 updateRate, f32 updateRateF, Object* obj, Object_Racer* racer);
void func_8004CC20(s32 updateRate, f32 updateRateF, Object *racerObj, Object_Racer *racer);
void racer_ai_challenge(Object *aiRacerObj, Object_Racer *aiRacer, s32 updateRate);
void racer_ai_eggs(Object *obj, Object_Racer *racer, s32 updateRate);
void func_80045C48(Object *obj, Object_Racer *racer, s32 updateRate);
void racer_activate_magnet(Object *obj, Object_Racer *racer, s32 updateRate);
Object *func_8005698C(Object *racerObj, Object_Racer *racer, f32 *outDistance);
void func_8005B818(Object *obj, Object_Racer *racer, s32 updateRate, f32 updateRateF);
void func_80050A28(Object *obj, Object_Racer *racer, s32 updateRate, f32 updateRateF);
typedef struct LevelGlobalData {
    s8 world;
    s8 raceType;
    s8 vehicles;
    s8 unk3;
    s16 unk4;
} LevelGlobalData;
enum NumberOfPlayers {
    ZERO_PLAYERS = -1,
    ONE_PLAYER = 0,
    TWO_PLAYERS = 1,
    THREE_PLAYERS = 2,
    FOUR_PLAYERS = 3
};
enum CutsceneIDs {
    CUTSCENE_ID_NONE = 0,
    CUTSCENE_ID_UNK_3 = 3,
    CUTSCENE_ID_UNK_5 = 5,
    CUTSCENE_ID_UNK_7 = 7,
    CUTSCENE_ID_UNK_A = 0x0A,
    CUTSCENE_ID_UNK_64 = 0x64
};
Vehicle leveltable_vehicle_default(s32 mapId);
s32 leveltable_vehicle_usable(s32 mapId);
s8 leveltable_type(s32 mapId);
s8 leveltable_world(s32 mapId);
s32 level_world_id(s32 worldId);
void level_count(s32 *outLevelCount, s32 *outWorldCount);
s32 level_is_race(void);
void level_music_start(f32 tempo);
s32 level_id(void);
u8 level_type(void);
LevelHeader *level_header(void);
u8 level_header_count(void);
char *level_name(s32 levelId);
void level_free(void);
void aitable_init(s8 *aiLevelTable);
void aitable_free(void);
AIBehaviourTable *aitable_get(void);
s8 race_is_adventure_2P(void);
void level_properties_push(s32 levelId, s32 entranceId, Vehicle vehicleId, s32 cutsceneId);
void level_properties_pop(s32 *levelId, s32 *entranceId, s32 *vehicleId, s32 *cutsceneId);
void level_properties_reset(void);
s16 level_properties_get(void);
s32 func_8006C300(void);
enum TextProperties {
    TEXT_NONE,
    TEXT_COL_R,
    TEXT_COL_G,
    TEXT_COL_B,
    TEXT_ALPHA,
    TEXT_FONT,
    TEXT_FLAGS
};
typedef struct GameTextTableStruct {
 char *entries[128];
 s32 *somethingElse;
} GameTextTableStruct;
typedef struct TextBox {
    s32 font;
    s32 left;
    s32 top;
    s32 right;
    s32 bottom;
    s32 textColRed;
    s32 textColGreen;
    s32 textColBlue;
    s32 textColAlpha;
    s32 textFlags;
    s32 textX;
    s32 textY;
    s32 lineHeight;
} TextBox;
void init_dialogue_text(void);
void free_message_box(void);
void set_subtitles(s32 setting);
void process_subtitles(s32 updateRate);
void load_game_text_table(void);
void free_game_text_table(void);
void set_textbox_display_value(s32 num);
void reset_delayed_text(void);
void set_delayed_text(s32 textID, f32 delay);
s32 textbox_visible(void);
void process_onscreen_textbox(s32 updateRate);
void find_next_subtitle(void);
s32 func_800C38B4(s32 arg0, TextBox *textbox);
void render_subtitles(void);
void set_current_text(s32 textID);
s32 dialogue_challenge_loop(void);
OSMesgQueue *si_mesg(void);
s32 input_init(void);
s32 input_update(s32 saveDataFlags, s32 updateRate);
void input_assign_players(void);
void charselect_assign_players(s8 *activePlayers);
u8 input_player_id(s32 player);
void input_swap_id(void);
u16 input_held(s32 player);
u32 input_pressed(s32 player);
u16 input_released(s32 player);
s32 input_clamp_stick_x(s32 player);
s32 input_clamp_stick_y(s32 player);
s8 input_clamp_stick_mag(s8 stickMag);
void drm_disable_input(void);
typedef enum StereoPanMode {
    STEREO,
    MONO,
    HEADPHONES
} StereoPanMode;
void set_stereo_pan_mode(s32 panMode);
s32 modify_panning(s32 pan);
typedef enum MemoryPools {
    POOL_MAIN,
    POOL_OBJECT,
    POOL_UNUSED_2,
    POOL_UNUSED_3,
    POOL_COUNT
} MemoryPools;
typedef enum MempoolFlags {
    SLOT_FREE = 0,
    SLOT_USED = (1 << 0),
    SLOT_LOCKED = (1 << 1),
    SLOT_SAFEGUARD = (1 << 2)
} MempoolFlags;
typedef struct MemoryPoolSlot {
           u8 *data;
           s32 size;
           s16 flags;
           s16 prevIndex;
           s16 nextIndex;
           s16 index;
           u32 colourTag;
} MemoryPoolSlot;
typedef struct MemoryPool {
           s32 maxNumSlots;
           s32 curNumSlots;
           MemoryPoolSlot *slots;
           s32 size;
} MemoryPool;
typedef struct FreeQueueSlot {
    void *dataAddress;
    u8 freeTimer;
} FreeQueueSlot;
typedef struct StackInfo {
    u32 var[5];
    u32 sp;
} StackInfo;
extern MemoryPoolSlot gMainMemoryPool;
void mempool_init_main(void);
MemoryPoolSlot *mempool_new_sub(s32 poolDataSize, s32 numSlots);
void *mempool_alloc_safe(s32 size, u32 colourTag);
MemoryPoolSlot *mempool_alloc(s32 size, u32 colourTag);
void *mempool_alloc_pool(MemoryPoolSlot *slots, s32 size);
void mempool_free_timer(s32 state);
void mempool_free(void *data);
void mempool_free_queue_clear(void);
void mempool_free_queue(void *dataAddress);
s32 mempool_locked_set(u8 *address);
s32 mempool_locked_unset(u8 *address);
s32 mempool_get_pool(u8 *address);
u8 *align16(u8 *address);
u8 *align8(u8 *address);
u8 *align4(u8 *address);
void mempool_print_tags_usb(void);
void mempool_print_tags_screen(void);
MemoryPoolSlot *mempool_init(MemoryPoolSlot *slots, s32 poolSize, s32 numSlots);
void mempool_slot_clear(MemoryPools poolIndex, s32 slotIndex);
s32 mempool_slot_assign(MemoryPools poolIndex, s32 slotIndex, s32 size, s32 slotIsTaken, s32 newSlotIsTaken,
                              u32 colourTag);
s32 get_memory_colour_tag_count(u32 colourTag);
void mempool_free_addr(u8 *address);
MemoryPoolSlot *mempool_slot_find(MemoryPools poolIndex, s32 size, u32 colourTag);
void *mempool_alloc_fixed(s32 size, u8 *address, u32 colorTag);
typedef struct RPYAngles {
    s16 z_rotation;
    s16 x_rotation;
    s16 y_rotation;
} RPYAngles;
s16 arctan2_f(f32 y, f32 x);
f32 coss_f(s16 angle);
f32 sins_f(s16 angle);
s32 coss_s16(s16 angle);
s32 sins_s16(s16 angle);
s32 sins_2(s16 angle);
void set_rng_seed(s32 num);
void save_rng_seed(void);
void load_rng_seed(void);
s32 get_rng_seed(void);
s32 rand_range(s32, s32);
void mtxf_to_mtxs(MtxF *mf, MtxS *mi);
void mtxf_transform_point(float mf[4][4], float x, float y, float z, float *ox, float *oy, float *oz);
void mtxf_transform_dir(MtxF *mf, Vec3f *in, Vec3f *out);
void mtxf_mul(MtxF *mat1, MtxF *mat2, MtxF *output);
void mtxf_to_mtx(MtxF *mf, Mtx *m);
void vec3s_reflect(Vec3s *vec, Vec3s *n);
void mtxs_transform_dir(MtxS *mi, Vec3s *vec);
void mtxf_from_transform(MtxF *mtx, ObjectTransform *trans);
void mtxf_scale_y(MtxF *input, f32 scale);
void mtxf_translate_y(MtxF *input, f32 offset);
void mtxf_from_inverse_transform(MtxF *mtx, ObjectTransform *trans);
void mtxf_billboard(MtxF *mtx, s32 angle, f32 scale, f32 scaleY);
void vec3s_rotate_rpy(RPYAngles *rotation, Vec3s *vec);
void vec3f_rotate(Vec3s *rotation, Vec3f *vec);
void vec3f_rotate_ypr(Vec3s *rotation, Vec3f *vec);
void vec3f_rotate_py(Vec3s *rotation, Vec3f *vec);
s32 tri2d_xz_contains_point(s32 x, s32 z, Vec3s *pointA, Vec3s *pointB, Vec3s *pointC);
void mtxf_from_translation(MtxF *mtx, f32 x, f32 y, f32 z);
void mtxf_from_scale(MtxF *mtx, f32 scaleX, f32 scaleY, f32 scaleZ);
s32 atan2s(s32 xDelta, s32 zDelta);
f32 area_triangle_2d(f32 x0, f32 z0, f32 x1, f32 z1, f32 x2, f32 z2);
void dmacopy_doubleword(void *src, void *dst, u32 end);
StackInfo *stack_pointer(void);
u32 interrupts_disable(void);
void interrupts_enable(u32 flags);
enum BananaBehaviour { BANANA_COLLECTED = -1, BANANA_IDLE, BANANA_DROPPED };
enum WeaponBehaviour {
    WEAPON_DROPPED,
    WEAPON_ARMED,
    WEAPON_TRIGGERED,
    WEAPON_DESTROY,
    WEAPON_STATUS_4,
    WEAPON_STATUS_5
};
enum DoorStatus { DOOR_CLOSING = -1, DOOR_CLOSED, DOOR_OPENING };
enum BossRaceWarps {
    WARP_STANDARD = -1,
    WARP_BOSS_FIRST,
    WARP_BOSS_REMATCH,
};
enum TajBehaviours {
    TAJ_MODE_ROAM,
    TAJ_MODE_APPROACH_PLAYER,
    TAJ_MODE_TURN_TOWARDS_PLAYER,
    TAJ_MODE_GREET_PLAYER,
    TAJ_MODE_DIALOGUE,
    TAJ_MODE_TRANSFORM_BEGIN,
    TAJ_MODE_TRANSFORM_END,
    TAJ_MODE_END_DIALOGUE,
    TAJ_MODE_END_DIALOGUE_CHALLENGE,
    TAJ_MODE_TELEPORT_TO_PLAYER_BEGIN = 10,
    TAJ_MODE_TELEPORT_TO_PLAYER_END,
    TAJ_MODE_SET_CHALLENGE = 15,
    TAJ_MODE_TELEPORT_AWAY_BEGIN = 20,
    TAJ_MODE_TELEPORT_AWAY_END,
    TAJ_MODE_RACE = 30,
    TAJ_MODE_UNK1F
};
enum TTBehaviours {
    TT_MODE_ROAM,
    TT_MODE_APPROACH_PLAYER,
    TT_MODE_TURN_TOWARDS_PLAYER,
    TT_MODE_DIALOGUE,
    TT_MODE_DIALOGUE_END
};
enum SilvereCoinBehaviours {
    SILVER_COIN_ACTIVE,
    SILVER_COIN_COLLECTED,
    SILVER_COIN_COLLECTED_PLAYER_2,
    SILVER_COIN_INACTIVE
};
enum EggPickupStatus { EGG_SPAWNED, EGG_COLLECTED, EGG_MOVING, EGG_IN_BASE, EGG_HATCHED };
enum FrogActions { FROG_IDLE, FROG_HOP, FROG_SQUISH, FROG_FLAT, FROG_UNSQUISH };
typedef struct VertexPosition {
               s16 x;
               s16 y;
               s16 z;
} VertexPosition;
extern Triangle D_800DCAA8[8];
extern VertexPosition D_800DCB28[6];
void obj_init_fireball_octoweapon(Object *obj, LevelObjectEntry_Fireball_Octoweapon *entry);
void obj_init_lasergun(Object *obj, LevelObjectEntry_Lasergun *entry);
void obj_init_laserbolt(Object *obj, LevelObjectEntry_Laserbolt *entry);
void obj_init_torch_mist(Object *obj, LevelObjectEntry_Torch_Mist *entry);
void obj_loop_torch_mist(Object *obj, s32 updateRate);
void obj_init_effectbox(Object *obj, LevelObjectEntry_EffectBox *entry);
void obj_init_trophycab(Object *obj, LevelObjectEntry_TrophyCab *entry);
void obj_init_collectegg(Object *obj, LevelObjectEntry_CollectEgg *entry);
void obj_init_eggcreator(Object *obj, LevelObjectEntry_EggCreator *entry);
void obj_loop_eggcreator(Object *obj, s32 updateRate);
void obj_init_lighthouse_rocketsignpost(Object *obj, LevelObjectEntry_Lighthouse_RocketSignpost *entry);
void obj_loop_rocketsignpost(Object *obj, s32 updateRate);
void obj_init_airzippers_waterzippers(Object *obj, LevelObjectEntry_AirZippers_WaterZippers *entry);
void obj_init_timetrialghost(Object *obj, LevelObjectEntry_TimeTrial_Ghost *entry);
void obj_loop_timetrialghost(Object *obj, s32 updateRate);
void obj_init_characterflag(Object *obj, LevelObjectEntry_CharacterFlag *entry);
void obj_loop_characterflag(Object *obj, s32 updateRate);
void obj_init_stopwatchman(Object *obj, LevelObjectEntry_StopWatchMan *entry);
void play_tt_voice_clip(u16 soundID, s32 interrupt);
void obj_init_lavaspurt(Object *obj, LevelObjectEntry_LavaSpurt *entry);
void obj_init_posarrow(Object *obj, LevelObjectEntry_PosArrow *entry);
void obj_init_animator(Object *obj, LevelObjectEntry_Animator *entry, s32 param);
void obj_loop_animobject(Object *obj, s32 updateRate);
void obj_loop_dooropener(Object *obj, s32 updateRate);
void obj_init_overridepos(Object *obj, LevelObjectEntry_OverridePos *entry);
void func_80037D60(s32 arg0, s32 arg1);
void obj_init_wizpigship(Object *obj, LevelObjectEntry_WizpigShip *entry);
void obj_init_hittester(Object *obj, LevelObjectEntry_HitTester *entry);
void obj_loop_hittester(Object *obj, s32 updateRate);
void obj_init_dynamic_lighting_object(Object *obj, LevelObjectEntry_DynamicLightingObject *entry);
void obj_init_unknown96(Object *obj, LevelObjectEntry_Unknown96 *entry);
void obj_init_snowball(Object *obj, LevelObjectEntry_Snowball *entry);
void func_80038330(s32 arg0, s32 arg1);
void obj_loop_animcamera(Object *obj, s32 updateRate);
void func_800387C0(s32 arg0, s32 arg1);
void obj_loop_animcar(Object *obj, s32 updateRate);
void obj_init_infopoint(Object *obj, LevelObjectEntry_InfoPoint *entry);
void obj_loop_infopoint(Object *obj, s32 updateRate);
void obj_init_smoke(Object *obj, LevelObjectEntry_Smoke *entry);
void obj_loop_smoke(Object *obj, s32 updateRate);
void obj_init_unknown25(Object *obj, LevelObjectEntry_Unknown25 *entry);
void obj_loop_unknown25(Object *obj, s32 updateRate);
void obj_init_wardensmoke(Object *obj, LevelObjectEntry_WardenSmoke *entry);
void obj_loop_wardensmoke(Object *obj, s32 updateRate);
void obj_init_teleport(Object *obj, LevelObjectEntry_Teleport *entry);
void obj_loop_teleport(Object *obj, s32 updateRate);
void obj_init_exit(Object *obj, LevelObjectEntry_Exit *entry);
void obj_init_cameracontrol(Object *obj, LevelObjectEntry_CameraControl *entry);
void obj_loop_cameracontrol(Object *obj, s32 updateRate);
void obj_init_setuppoint(Object *obj, LevelObjectEntry_SetupPoint *entry);
void obj_loop_setuppoint(Object *obj, s32 updateRate);
void obj_init_dino_whale(Object *obj, LevelObjectEntry_Dino_Whale *entry);
void obj_loop_dino_whale(Object *obj, s32 updateRate);
void obj_init_parkwarden(Object *obj, LevelObjectEntry_Parkwarden *entry);
void set_taj_voice_line(s16 soundID);
void play_taj_voice_clip(u16 soundID, s32 interrupt);
void obj_loop_gbparkwarden(Object *obj, s32 updateRate);
f32 get_npc_pos_y(void);
void obj_init_checkpoint(Object *obj, LevelObjectEntry_Checkpoint *entry, s32 arg2);
void obj_loop_checkpoint(Object *obj, s32 updateRate);
void obj_init_modechange(Object *obj, LevelObjectEntry_ModeChange *entry);
void obj_init_bonus(Object *obj, LevelObjectEntry_Bonus *entry);
void obj_init_ttdoor(Object *obj, LevelObjectEntry_TTDoor *entry);
void obj_init_bridge_whaleramp(Object *obj, LevelObjectEntry_Bridge_WhaleRamp *entry);
void obj_init_rampswitch(Object *obj, LevelObjectEntry_RampSwitch *entry);
void obj_loop_rampswitch(Object *obj, s32 updateRate);
void obj_init_seamonster(Object *obj, LevelObjectEntry_SeaMonster *entry);
void obj_loop_seamonster(Object *obj, s32 updateRate);
void obj_init_fogchanger(Object *obj, LevelObjectEntry_FogChanger *entry);
void obj_init_skycontrol(Object *obj, LevelObjectEntry_SkyControl *entry);
void obj_loop_skycontrol(Object *obj, s32 updateRate);
void obj_init_ainode(Object *obj, LevelObjectEntry_AiNode *entry);
void obj_loop_ainode(Object *obj, s32 updateRate);
void obj_init_treasuresucker(Object *obj, LevelObjectEntry_TreasureSucker *entry);
void obj_init_flycoin(Object *obj, LevelObjectEntry_FlyCoin *entry);
void obj_init_bananacreator(Object *obj, LevelObjectEntry_BananaCreator *entry);
void obj_init_banana(Object *obj, LevelObjectEntry_Banana *entry);
void obj_init_silvercoin_adv2(Object *obj, LevelObjectEntry_SilverCoinAdv2 *entry);
void obj_init_silvercoin(Object *obj, LevelObjectEntry_SilverCoin *entry);
void obj_init_worldkey(Object *obj, LevelObjectEntry_WorldKey *entry);
void obj_loop_worldkey(Object *worldKeyObj, s32 updateRate);
void obj_init_wballoonpop(Object *obj, LevelObjectEntry_WBalloonPop *entry);
void obj_loop_wballoonpop(Object *obj, s32 updateRate);
void obj_init_weapon(Object *obj, LevelObjectEntry_Weapon *entry);
void obj_loop_weapon(Object *obj, s32 updateRate);
void reset_rocket_sound_timer(void);
void decrease_rocket_sound_timer(void);
void obj_init_audioline(Object *obj, LevelObjectEntry_AudioLine *entry);
void obj_init_audioreverb(Object *obj, LevelObjectEntry_AudioReverb *entry);
void obj_init_texscroll(Object *obj, LevelObjectEntry_TexScroll *entry, s32 arg2);
void obj_init_rgbalight(Object *obj, LevelObjectEntry_RgbaLight *entry, s32 arg2);
void obj_init_buoy_pirateship(Object *obj, LevelObjectEntry_Buoy_PirateShip *entry, s32 arg2);
void obj_loop_buoy_pirateship(Object *obj, s32 updateRate);
void obj_init_log(Object *obj, LevelObjectEntry_Log *entry, s32 arg2);
void obj_init_wavegenerator(Object *obj, LevelObjectEntry_WaveGenerator *entry, s32 arg2);
void obj_init_midichset(Object *obj, LevelObjectEntry_Midichset *entry);
void obj_init_bubbler(Object *obj, LevelObjectEntry_Bubbler *entry);
void obj_loop_bubbler(Object *obj, s32 updateRate);
void obj_init_boost(Object *obj, LevelObjectEntry_Boost2 *entry);
void obj_init_unknown94(Object *obj, LevelObjectEntry_Unknown94 *entry, s32 arg2);
void obj_loop_unknown94(Object *obj, s32 updateRate);
void obj_init_rangetrigger(Object *obj, LevelObjectEntry_RangeTrigger *entry);
void obj_loop_rangetrigger(Object *obj, s32 updateRate);
void obj_init_frog(Object *obj, LevelObjectEntry_Frog *entry);
void obj_loop_pigrocketeer(Object *obj, s32 updateRate);
void obj_init_levelname(Object *obj, LevelObjectEntry_LevelName *entry);
void obj_loop_wizghosts(Object *obj, s32 updateRate);
void obj_loop_ttdoor(Object *obj, s32 updateRate);
void obj_loop_trophycab(Object *obj, s32 updateRate);
void obj_loop_wizpigship(Object *wizShipObj, s32 updateRate);
void obj_loop_silvercoin(Object *obj, s32 updateRate);
void obj_loop_bombexplosion(Object *obj, s32 updateRate);
void obj_loop_flycoin(Object *obj, s32 updateRate);
void obj_spawn_effect(f32 x, f32 y, f32 z, s32 objectID, s32 soundID, f32 scale, s32 arg6);
void obj_loop_stopwatchman(Object *obj, s32 updateRate);
void obj_loop_parkwarden(Object *obj, s32 updateRate);
void obj_loop_bridge_whaleramp(Object *obj, s32 updateRate);
void obj_loop_frog(Object *obj, s32 updateRate);
void obj_loop_levelname(Object *obj, s32 updateRate);
void obj_loop_banana(Object *obj, s32 updateRate);
void obj_loop_collectegg(Object *obj, s32 updateRate);
void obj_loop_weather(Object *obj, s32 updateRate);
void obj_init_groundzipper(Object *obj, LevelObjectEntry_GroundZipper *entry);
void obj_init_goldenballoon(Object *obj, LevelObjectEntry_GoldenBalloon *entry);
void obj_init_midifadepoint(Object *obj, LevelObjectEntry_MidiFadePoint *entry);
void obj_loop_trigger(Object *obj, s32 updateRate);
void obj_init_weather(Object *obj, LevelObjectEntry_Weather *entry);
void obj_loop_treasuresucker(Object *obj, s32 updateRate);
void obj_loop_log(Object *obj, s32 updateRate);
void obj_loop_modechange(Object *obj, s32 updateRate);
void obj_loop_bonus(Object *obj, s32 updateRate);
void obj_loop_fireball_octoweapon(Object *obj, s32 updateRate);
void obj_loop_lasergun(Object *obj, s32 updateRate);
void play_rocket_trailing_sound(Object *obj, struct Object_Weapon *weapon, u16 soundID);
void rocket_prevent_overshoot(Object *obj, s32 updateRate, Object_Weapon *rocket);
void homing_rocket_prevent_overshoot(Object *obj, s32 updateRate, Object_Weapon *rocket);
void func_8001F23C(Object *obj, LevelObjectEntry_Animation *animEntry);
void obj_loop_effectbox(Object *obj, s32 updateRate);
void func_8001EE74(void);
void obj_loop_door(Object *doorObj, s32 updateRate);
void obj_loop_fish(Object *fishObj, s32 updateRate);
void obj_loop_weaponballoon(Object *weaponBalloonObj, s32 updateRate);
void obj_loop_char_select(Object *charSelectObj, s32 updateRate);
void weapon_trap(Object *weaponObj, s32 updateRate);
void obj_init_butterfly(Object *butterflyObj, LevelObjectEntry_Butterfly *butterflyEntry, s32 param);
void obj_init_animation(Object *obj, LevelObjectEntry_Animation *entry, s32 arg2);
void obj_init_lensflareswitch(Object *obj, LevelObjectEntry_LensFlareSwitch *entry, s32 arg2);
void obj_loop_lavaspurt(Object *obj, s32 updateRate);
void obj_loop_vehicleanim(Object *obj, s32 updateRate);
void obj_loop_snowball(Object *obj, s32 updateRate);
void obj_loop_goldenballoon(Object *obj, s32 updateRate);
void obj_loop_groundzipper(Object *obj, s32 updateRate);
void obj_loop_laserbolt(Object *obj, s32 updateRate);
void obj_loop_posarrow(Object *obj, s32 updateRate);
void obj_loop_bananacreator(Object *obj, s32 updateRate);
void obj_loop_airzippers_waterzippers(Object *obj, s32 updateRate);
void obj_loop_exit(Object *obj, s32 updateRate);
void obj_loop_scenery(Object *obj, s32 updateRate);
void obj_init_trigger(Object *obj, LevelObjectEntry_Trigger *entry);
void obj_init_lensflare(Object *obj, LevelObjectEntry_LensFlare *entry);
void obj_init_weaponballoon(Object *obj, LevelObjectEntry_WeaponBalloon *entry);
void obj_init_door(Object *obj, LevelObjectEntry_Door *entry);
void obj_init_audio(Object *obj, LevelObjectEntry_Audio *entry);
void obj_init_bombexplosion(Object *obj, LevelObjectEntry_BombExplosion *entry);
void obj_init_scenery(Object *obj, LevelObjectEntry_Scenery *entry);
void weapon_projectile(Object *obj, s32 updateRate);
void obj_loop_texscroll(Object *obj, s32 updateRate);
void obj_loop_animator(Object *obj, s32 updateRate);
void calc_env_mapping_for_object(ObjectModel *, s16, s16, s16);
void obj_init_fish(Object *fishObj, LevelObjectEntry_Fish *fishEntry, s32 param);
void obj_init_midifade(Object *obj, LevelObjectEntry_MidiFade *entry);
void obj_loop_butterfly(Object *butterflyObj, s32 updateRate);
s32 ainode_find_nearest(f32 diffX, f32 diffY, f32 diffZ, s32 useElevation);
void func_8000CBF0(Object *, s32);
void try_to_collect_egg(Object *, Object_CollectEgg *);
s32 func_8001F3EC(s32);
s32 func_80021600(s32);
typedef enum AnimType {
    MODELTYPE_BASIC,
    MODELTYPE_SHADE,
    MODELTYPE_ANIMATED
} AnimType ;
typedef struct unk8011D624 {
    s32 unk0;
    ObjectModel *model;
} unk8011D624;
extern s32 gRenderSceneChecksum;
extern s32 gRenderSceneFuncLength;
void allocate_object_model_pools(void);
void model_anim_offset(s32 offset);
void func_80061C0C(Object* obj);
void free_3d_model(ModelInstance *modInst);
s32 model_anim_init(ObjectModel *model, s32 modelID);
s32 check_nearby_vertices(Vertex *vertices, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
ModelInstance *model_instance_init(ObjectModel *model, s32 flags);
ModelInstance *object_model_init(s32 modelID, s32 flags);
s32 func_80060C58(Vertex *vertices, s32 i1, s32 i2, s32 i3, s32 i4);
void free_model_data(ObjectModel *mdl);
void func_80060910(ObjectModel *);
s32 func_80060AC8(ObjectModel *mdl, s32 arg1, s32 arg2, s32 arg3, s32 *outBatchIndex, s32 *outVertexIndex);
s32 model_init_normals(ObjectModel *);
enum ParticleKind {
    PARTICLE_KIND_NONE = 0,
    PARTICLE_KIND_TRIANGLE = 1,
    PARTICLE_KIND_RECTANGLE = 2,
    PARTICLE_KIND_LINE = 3,
    PARTICLE_KIND_POINT = 4,
    PARTICLE_KIND_SPRITE = 128
};
enum ObjectEmitterFlags {
    OBJ_EMIT_NONE,
    OBJ_EMIT_1 = (1 << 0),
    OBJ_EMIT_2 = (1 << 1),
    OBJ_EMIT_3 = (1 << 2),
    OBJ_EMIT_4 = (1 << 3),
    OBJ_EMIT_5 = (1 << 4),
    OBJ_EMIT_6 = (1 << 5),
    OBJ_EMIT_7 = (1 << 6),
    OBJ_EMIT_8 = (1 << 7),
    OBJ_EMIT_9 = (1 << 8),
    OBJ_EMIT_10 = (1 << 9),
    OBJ_EMIT_11 = (1 << 10),
    OBJ_EMIT_12 = (1 << 11),
    OBJ_EMIT_13 = (1 << 12),
    OBJ_EMIT_14 = (1 << 13),
    OBJ_EMIT_15 = (1 << 14),
    OBJ_EMIT_16 = (1 << 15),
    OBJ_EMIT_17 = (1 << 16),
    OBJ_EMIT_18 = (1 << 17),
    OBJ_EMIT_19 = (1 << 18),
    OBJ_EMIT_20 = (1 << 19),
};
enum ParticleRandomizationFlags {
    PARTICLE_RANDOM_SOURCE_DISTANCE = (1 << 0),
    PARTICLE_RANDOM_SOURCE_YAW = (1 << 1),
    PARTICLE_RANDOM_SOURCE_PITCH = (1 << 2),
    PARTICLE_RANDOM_SOURCE_ROLL = (1 << 3),
    PARTICLE_RANDOM_EMISSION_SPEED = (1 << 4),
    PARTICLE_RANDOM_EMISSION_DIR_YAW = (1 << 5),
    PARTICLE_RANDOM_EMISSION_DIR_PITCH = (1 << 6),
    PARTICLE_RANDOM_EMISSION_DIR_ROLL = (1 << 7),
    PARTICLE_RANDOM_VELOCITY_X = (1 << 8),
    PARTICLE_RANDOM_VELOCITY_Y = (1 << 9),
    PARTICLE_RANDOM_VELOCITY_Z = (1 << 10),
    PARTICLE_RANDOM_YAW = (1 << 11),
    PARTICLE_RANDOM_PITCH = (1 << 12),
    PARTICLE_RANDOM_ROLL = (1 << 13),
    PARTCILE_RANDOM_YAW_VELOCITY = (1 << 14),
    PARTCILE_RANDOM_PITCH_VELOCITY = (1 << 15),
    PARTCILE_RANDOM_ROLL_VELOCITY = (1 << 16),
    PARTICLE_RANDOM_SCALE = (1 << 17),
    PARTICLE_RANDOM_SCALE_VELOCITY = (1 << 18),
    PARTICLE_RANDOM_MOVEMENT_PARAM = (1 << 19),
    PARTICLE_RANDOM_COLOUR_RED = (1 << 20),
    PARTICLE_RANDOM_COLOUR_GREEN = (1 << 21),
    PARTICLE_RANDOM_COLOUR_BLUE = (1 << 22),
    PARTICLE_RANDOM_COLOUR_ALPHA = (1 << 23),
};
enum ParticleBehaviorFlags {
    PARTICLE_FLAGS_NONE = 0,
    PARTICLE_SOURCE_OFFSET_ENABLED = (1 << 0),
    PARTICLE_SOURCE_ROTATION_ENABLED = (1 << 1),
    PARTICLE_SOURCE_EMITS_WITH_VELOCITY = (1 << 2),
    PARTICLE_ROTATING_DIRECTION = (1 << 3),
    PARTICLE_VELOCITY_RELATIVE_TO_PARENT = (1 << 4),
    PARTICLE_VELOCITY_ABSOLUTE = (1 << 5),
    PARTICLE_VELOCITY_SCALED_FROM_PARENT = (1 << 6),
    PARTICLE_ROTATION_ABSOLUTE = (1 << 7),
    PARTICLE_OVERRIDE_OPACITY_FROM_DESCRIPTOR = (1 << 8),
    PARTICLE_POINT_EMITTER_DISABLED = (1 << 9),
    PARTICLE_POINT = (1 << 10),
    PARTICLE_RANDOM_TEXTURE_FRAME = (1 << 11),
    PARTICLE_SCALE_VELOCITY_INHERITS_PARENT_SPEED = (1 << 12),
    PARTICLE_EMITTER_AWAITING_SPAWN = (1 << 13),
    PARTICLE_LINE = (1 << 14),
    PARTICLE_EMITTER_ENABLED = (1 << 15),
};
enum ParticleMovement {
    PARTICLE_MOVEMENT_NONE,
    PARTICLE_MOVEMENT_BASIC,
    PARTICLE_MOVEMENT_ACCELERATION,
    PARTICLE_MOVEMENT_ATTACHED_TO_PARENT,
    PARTICLE_MOVEMENT_BASIC_PARENT,
    PARTICLE_MOVEMENT_FORWARD,
};
enum ParticleDescriptorFlags {
    PARTICLE_TEXTURE_ANIM_FORWARD_ENABLED = (1 << 0),
    PARTICLE_TEXTURE_ANIM_BACKWARD_ENABLED = (1 << 1),
    PARTICLE_TEXTURE_ANIM_LOOP = (1 << 2),
    PARTICLE_CURRENT_ANIMATION_BACKWARD = (1 << 3),
    PARTICLE_F40_GRAVITY_1 = (1 << 4),
    PARTICLE_F40_GRAVITY_2 = (1 << 5),
    PARTICLE_F40_GRAVITY_3 = (1 << 6),
    PARTICLE_SHADED = (1 << 11),
    PARTICLE_DESC_FLAG_1000 = (1 << 12),
    PARTICLE_DESC_FLAG_2000 = (1 << 13),
    PARTICLE_LINE_ALONG_VELOCITY = (1 << 14),
    PARTICLE_UNK_FLAG_8000 = (1 << 15),
};
typedef struct ParticleDescriptor {
               u8 kind;
               u8 movementType;
               u16 flags;
               s16 textureID;
               s16 textureFrameStep;
               s16 lifeTime;
    union {
                   s16 lifeTimeRange;
        struct {
                       u16 lineOrientation : 6;
                       u16 line_unused_B : 6;
        };
                   u16 unused_point_field : 6;
    };
               u8 opacity;
               u8 opacityVel;
               s16 opacityTimer;
               f32 scale;
               ColourRGBA colour;
} ParticleDescriptor;
typedef struct ColorLoopEntry {
               s32 numEntries;
               u8 r;
               u8 g;
               u8 b;
               u8 a;
} ColorLoopEntry;
typedef struct ParticleBehaviour {
               s32 flags;
               Vec3f emitterPos;
               f32 sourceDistance;
               Vec3s sourceRotation;
               s16 maxParticlesFromSamePos;
               Vec3s sourceAngularVelocity;
               Vec3s emissionDirection;
               s16 maxParticlesInSameDir;
               Vec3s emissionDirAngularVelocity;
               Vec3f velocityModifier;
               f32 emissionSpeed;
               s16 spawnInterval;
               s16 burstCount;
               Vec3s rotation;
               Vec3s angularVelocity;
               f32 scale;
               f32 scaleVelocity;
               f32 movementParam;
               s32 randomizationFlags;
               s32 sourceDistanceRange;
               Vec3s sourceDirRange;
               Vec3s emissionDirRange;
               s32 emissionSpeedRange;
               Vec3i velocityModifierRange;
               Vec3s rotationRange;
               Vec3s angularVelocityRange;
               s32 scaleRange;
               s32 scaleVelocityRange;
               s32 movementParamRange;
               u8 colourRangeR;
               u8 colourRangeG;
               u8 colourRangeB;
               u8 colourRangeA;
               ColorLoopEntry *colourLoop;
} ParticleBehaviour;
typedef struct ParticleEmitter {
               ParticleBehaviour *behaviour;
               s16 flags;
    union {
               u8 sourceRotationCounter;
               u8 lineOpacity;
               u8 pointCount;
    };
    union {
               u8 emissionDirRotationCounter;
               u8 maxPointCount;
    };
               s16 descriptorID;
    union {
               s16 line_unused;
               s16 point_opacity;
               s16 timeFromLastSpawn;
    };
    union {
               Vec3f lineRefPoint;
               struct {
                       struct PointParticle **refPoints;
                       Vec2s pointSourceRotation;
                       Vec2s pointEmissionDirection;
            };
               struct {
                       Vec3s sourceRotation;
                       Vec3s emissionDirection;
        };
    };
               Vec3s position;
               s16 colourIndex;
} ParticleEmitter;
typedef struct ParticleModel {
               TextureHeader *texture;
               s16 vertexCount;
               s16 triangleCount;
               Vertex *vertices;
               Triangle *triangles;
} ParticleModel;
typedef struct Particle {
               ObjectTransform trans;
               s16 textureFrame;
               s16 textureFrameStep;
               Vec3f velocity;
               f32 scaleVelocity;
               s16 kind;
               s16 segmentID;
               f32 unk30;
               f32 unk34;
               u8 unk38;
               u8 movementType;
               s16 destroyTimer;
               Object *parentObj;
               s32 descFlags;
    union {
               ParticleModel *model;
               Sprite *sprite;
    };
               s16 unk_48;
               s16 brightness;
               Vec3f localPos;
    union {
               ParticleEmitter *lineEmitter;
               f32 forwardVel;
               f32 downAcceleration;
               f32 downOffset;
               f32 movementParam;
    };
               s16 opacity;
               s16 opacityVel;
               s16 opacityTimer;
               Vec3s angularVelocity;
    union {
               f32 gravity;
    struct {
               u8 lineCreationPhase;
               u8 line_unused_69;
               s8 lineOrientation;
               s8 line_unused_6B;
    };
    };
               ColourRGBA colour;
} Particle;
typedef struct PointParticle {
               Particle base;
               ParticleEmitter *pointEmitter;
               u8 pointIndex;
               u8 modelFrame;
               u8 unused_76;
               s8 meshRegenerated;
} PointParticle;
void reset_particles(void);
void reset_particles_with_assets(void);
void particle_free_dummy(void);
void free_particle_buffers(void);
void free_particle_vertices_triangles(void);
void free_particle_assets(void);
void init_triangle_particle_model(ParticleModel *model, Vertex **vtx, Triangle **triangles);
void init_rectangle_particle_model(ParticleModel *model, Vertex **vtx, Triangle **triangles);
void init_line_particle_model(ParticleModel *model, Vertex **vtx, Triangle **triangles);
void init_point_particle_model(ParticleModel *model, Vertex **vtx, Triangle **triangles);
void set_triangle_texture_coords(Particle *particle);
void set_rectangle_texture_coords(Particle *particle);
void emitter_init(ParticleEmitter *emitter, s32 behaviourID, s32 particleID);
void emitter_init_with_pos(ParticleEmitter *emitter, s32 behaviourID, s32 particleID, s16 posX, s16 posY, s16 posZ);
void obj_disable_emitter(Object *obj, s32 emitterIndex);
void emitter_cleanup(ParticleEmitter *emitter);
void delete_point_particle_from_sequence(PointParticle *particle);
void init_particle_assets(void);
void update_particle_texture_frame(Particle *particle);
void setup_particle_position(Particle *particle, Object *obj, ParticleEmitter *emitter, ParticleBehaviour *behaviour);
void particle_deallocate(Particle *particle);
void particle_update(Particle *particle, s32 updateRate);
void setup_particle_velocity(Particle *particle, Object *obj, ParticleEmitter *emitter, ParticleBehaviour *behaviour);
PointParticle *create_point_particle(Object *obj, ParticleEmitter *emitter);
Particle *particle_allocate(s32 kind);
void obj_trigger_emitter(Object *obj, ParticleEmitter *emitter);
Particle *create_general_particle(Object *obj, ParticleEmitter *emitter);
void obj_enable_emitter(Object *obj, s32 emitterIndex);
void emitter_change_settings(ParticleEmitter *emitter, s32 behaviourID, s32 particleID, s16 posX, s16 posY, s16 posZ);
void render_particle(Particle *particle, Gfx **dList, Mtx **mtx, Vertex **vtx, s32 flags);
void increase_emitter_opacity(Object *obj, s32 idx, s32 delta, s32 maxOpacity);
void decrease_emitter_opacity(Object *obj, s32 idx, s32 delta, s32 maxOpacity);
void obj_spawn_particle(Object *obj, s32 updateRate);
void regenerate_point_particles_mesh(PointParticle *obj);
void update_line_particle(Particle *particle);
void update_vehicle_particles(Object *racerObj, s32 updateRate);
Particle* create_line_particle(Object* obj, ParticleEmitter* emitter);
void scroll_particle_textures(s32 updateRate);
void init_particle_buffers(s32 maxTriangleParticles, s32 maxRectangleParticles, s32 maxSpriteParticles,
                           s32 maxLineParticles, s32 maxPointParticles, s32 unused_arg);
void move_particle_basic_parent(Particle *);
void move_particle_attached_to_parent(Particle *);
void move_particle_with_acceleration(Particle *);
void move_particle_basic(Particle *);
void move_particle_forward(Particle *);
enum ObjectBehaviours {
    BHV_NONE,
    BHV_RACER,
    BHV_SCENERY,
    BHV_FISH,
    BHV_ANIMATOR,
    BHV_WEAPON,
    BHV_SMOKE,
    BHV_EXIT,
    BHV_AUDIO,
    BHV_AUDIO_LINE,
    BHV_CAMERA_CONTROL,
    BHV_SETUP_POINT,
    BHV_DINO_WHALE,
    BHV_CHECKPOINT,
    BHV_DOOR,
    BHV_FOG_CHANGER,
    BHV_AINODE,
    BHV_WEAPON_BALLOON,
    BHV_WEAPON_2,
    BHV_AUDIO_LINE_2,
    BHV_UNK_14,
    BHV_UNK_15,
    BHV_BOMB_EXPLOSION,
    BHV_BALLOON_POP,
    BHV_UNK_18,
    BHV_UNK_19,
    BHV_SKY_CONTROL,
    BHV_AUDIO_REVERB,
    BHV_TORCH_MIST,
    BHV_TEXTURE_SCROLL,
    BHV_MODECHANGE,
    BHV_STOPWATCH_MAN,
    BHV_BANANA,
    BHV_LIGHT_RGBA,
    BHV_UNK_22,
    BHV_UNK_23,
    BHV_BUOY_PIRATE_SHIP,
    BHV_WEATHER,
    BHV_BRIDGE_WHALE_RAMP,
    BHV_RAMP_SWITCH,
    BHV_SEA_MONSTER,
    BHV_BONUS,
    BHV_UNK_2A,
    BHV_LENS_FLARE,
    BHV_LENS_FLARE_SWITCH,
    BHV_COLLECT_EGG,
    BHV_EGG_CREATOR,
    BHV_CHARACTER_FLAG,
    BHV_UNK_30,
    BHV_ANIMATION,
    BHV_ANIMATED_OBJECT,
    BHV_CAMERA_ANIMATION,
    BHV_INFO_POINT,
    BHV_CAR_ANIMATION,
    BHV_CHARACTER_SELECT,
    BHV_TRIGGER,
    BHV_VEHICLE_ANIMATION,
    BHV_ZIPPER_WATER,
    BHV_TIMETRIAL_GHOST,
    BHV_WAVE_GENERATOR,
    BHV_WAVE_POWER,
    BHV_BUTTERFLY,
    BHV_PARK_WARDEN,
    BHV_UNK_3F,
    BHV_WORLD_KEY,
    BHV_BANANA_SPAWNER,
    BHV_TREASURE_SUCKER,
    BHV_LOG,
    BHV_LAVA_SPURT,
    BHV_POS_ARROW,
    BHV_HIT_TESTER,
    BHV_MIDI_FADE,
    BHV_HIT_TESTER_2,
    BHV_EFFECT_BOX,
    BHV_TROPHY_CABINET,
    BHV_BUBBLER,
    BHV_FLY_COIN,
    BHV_GOLDEN_BALLOON,
    BHV_LASER_BOLT,
    BHV_LASER_GUN,
    BHV_PARK_WARDEN_2,
    BHV_ANIMATED_OBJECT_2,
    BHV_ZIPPER_GROUND,
    BHV_OVERRIDE_POS,
    BHV_WIZPIG_SHIP,
    BHV_ANIMATED_OBJECT_3,
    BHV_ANIMATED_OBJECT_4,
    BHV_TAJ_TELEPOINT,
    BHV_SILVER_COIN,
    BHV_BOOST,
    BHV_WARDEN_SMOKE,
    BHV_UNK_5B,
    BHV_UNK_5C,
    BHV_ZIPPER_AIR,
    BHV_UNK_5E,
    BHV_DYNAMIC_LIGHT_OBJECT_2,
    BHV_SNOWBALL,
    BHV_SNOWBALL_2,
    BHV_TELEPORT,
    BHV_ROCKET_SIGNPOST,
    BHV_ROCKET_SIGNPOST_2,
    BHV_SNOWBALL_3,
    BHV_SNOWBALL_4,
    BHV_HIT_TESTER_3,
    BHV_HIT_TESTER_4,
    BHV_RANGE_TRIGGER,
    BHV_UNK_6A,
    BHV_BOSS_HAZARD_TRIGGER,
    BHV_FIREBALL_OCTOWEAPON,
    BHV_FROG,
    BHV_SILVER_COIN_2,
    BHV_TT_DOOR,
    BHV_MIDI_FADE_POINT,
    BHV_DOOR_OPENER,
    BHV_UNK_72,
    BHV_PIG_ROCKETEER,
    BHV_FIREBALL_OCTOWEAPON_2,
    BHV_LEVEL_NAME,
    BHV_MIDI_CHANNEL_SET,
    BHV_WIZPIG_GHOSTS,
    BHV_UNK_78,
    BHV_UNK_79,
    BHV_UNK_7A,
    BHV_UNK_7B,
    BHV_UNK_7C,
    BHV_UNK_7D,
    BHV_UNK_7E,
    BHV_UNK_7F
};
enum ObjectInteractionFlags {
    INTERACT_FLAGS_NONE,
    INTERACT_FLAGS_SOLID = (1 << 0),
    INTERACT_FLAGS_TANGIBLE = (1 << 1),
    INTERACT_FLAGS_UNK_0004 = (1 << 2),
    INTERACT_FLAGS_PUSHING = (1 << 3),
    INTERACT_FLAGS_UNK_0010 = (1 << 4),
    INTERACT_FLAGS_UNK_0020 = (1 << 5),
    INTERACT_FLAGS_COLLIDED = (1 << 6),
    INTERACT_FLAGS_UNK_0080 = (1 << 7),
    INTERACT_FLAGS_UNK_0100 = (1 << 8),
    INTERACT_FLAGS_UNK_0200 = (1 << 9),
    INTERACT_FLAGS_UNK_0400 = (1 << 10),
    INTERACT_FLAGS_UNK_0800 = (1 << 11),
    INTERACT_FLAGS_UNK_1000 = (1 << 12),
    INTERACT_FLAGS_UNK_2000 = (1 << 13),
    INTERACT_FLAGS_UNK_4000 = (1 << 14),
    INTERACT_FLAGS_UNK_8000 = (1 << 15),
};
enum ObjectSpawnFlags {
    OBJECT_SPAWN_NONE,
    OBJECT_SPAWN_UNK01 = (1 << 0),
    OBJECT_SPAWN_UNK02 = (1 << 1),
    OBJECT_SPAWN_UNK04 = (1 << 2),
    OBJECT_SPAWN_UNK08 = (1 << 3),
    OBJECT_SPAWN_NO_LODS = (1 << 4)
};
enum ObjectHeaderFlags {
    OBJECT_HEADER_NONE,
    OBJECT_HEADER_UNK01 = (1 << 0),
    OBJECT_HEADER_UNK02 = (1 << 1),
    OBJECT_HEADER_UNK04 = (1 << 2),
    OBJECT_HEADER_UNK08 = (1 << 3),
    OBJECT_HEADER_UNK10 = (1 << 4),
    OBJECT_HEADER_NO_TIME_TRIAL = (1 << 5),
    OBJECT_HEADER_NO_MULTIPLATER = (1 << 6)
};
enum ObjectBehaviourFlags {
    OBJECT_BEHAVIOUR_NONE,
    OBJECT_BEHAVIOUR_SHADED = (1 << 0),
    OBJECT_BEHAVIOUR_SHADOW = (1 << 1),
    OBJECT_BEHAVIOUR_WATER_EFFECT = (1 << 2),
    OBJECT_BEHAVIOUR_ANIMATION = (1 << 3),
    OBJECT_BEHAVIOUR_INTERACTIVE = (1 << 4),
    OBJECT_BEHAVIOUR_COLLIDABLE = (1 << 5)
};
enum ContPakErrors {
    CONTPAK_ERROR_MISSING = -1,
    CONTPAK_ERROR_NONE,
    CONTPAK_ERROR_UNKNOWN,
    CONTPAK_ERROR_FULL,
    CONTPAK_ERROR_DAMAGED
};
enum TajChallengeReasons {
    CHALLENGE_END_FINISH,
    CHALLENGE_END_QUIT,
    CHALLENGE_END_OOB
};
typedef struct RacerShieldGfx {
    s16 x_position;
    s16 y_position;
    s16 z_position;
    s16 y_offset;
    f32 scale;
    f32 turnSpeed;
} RacerShieldGfx;
typedef struct BossRaceVehicles {
    s8 playerVehicle;
    s8 bossVehicle;
} BossRaceVehicles;
typedef struct CheckpointNode {
               f32 rotationXFrac;
               f32 rotationYFrac;
               f32 rotationZFrac;
               f32 unkC;
               f32 x;
               f32 y;
               f32 z;
               f32 scale;
               f32 distance;
               f32 altDistance;
               Object *obj;
               s16 checkpointID;
               s8 unk2E[4];
               s8 unk32[4];
               s8 unk36[4];
               s8 altRouteID;
               u8 unk3B;
} CheckpointNode;
typedef struct unk800179D0 {
    s32 unk0;
    Object *unk04;
    Object *unk08;
    f32 unk0C[12];
    u32 unk3C;
} unk800179D0;
typedef struct TTGhostTable {
    u8 mapId;
    u8 defaultVehicleId;
    s32 ghostOffset;
} TTGhostTable;
typedef struct ObjectTransformExt {
    ObjectTransform trans;
    s16 animFrame;
    s16 unk1A;
} ObjectTransformExt;
typedef struct ObjectTransform_800135B8 {
    ObjectTransform trans;
    s16 unk18;
} ObjectTransform_800135B8;
typedef struct unk800149C0 {
    u8 pad0[4];
    u8 unk4;
    u8 pad5;
    s16 unk6;
} unk800149C0;
typedef struct RacerFXData {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
} RacerFXData;
extern s32 osCicId;
Object *racerfx_get_boost(s32 boostID);
void allocate_object_pools(void);
void clear_object_pointers(void);
void free_all_objects(void);
s32 normalise_time(s32 timer);
void func_8000CBC0(void);
s32 func_8000CC20(Object *obj);
s32 get_contpak_error(void);
void instShowBearBar(void);
s8 func_8000E138(void);
s8 racetype_demo(void);
s8 is_race_started_by_player_two(void);
s8 is_player_two_in_control(void);
void toggle_lead_player_index(void);
void reset_lead_player_index(void);
s8 find_non_car_racers(void);
s8 check_if_silver_coin_race(void);
void despawn_player_racer(Object *obj, s32 vehicleID);
void set_time_trial_enabled(s32 status);
u8 is_time_trial_enabled(void);
u8 is_in_time_trial(void);
Object *get_object(s32 index);
Object **objGetObjList(s32 *arg0, s32 *cnt);
s32 obj_count(void);
s32 particle_count(void);
void add_particle_to_entity_list(Object *obj);
void free_object(Object *);
s32 obj_table_ids(void);
s32 obj_id_valid(s32 arg0);
void path_enable(void);
s32 get_race_countdown(void);
s32 get_race_start_timer(void);
void ignore_bounds_check(void);
void func_80012C30(void);
void func_80012C3C(Gfx **dList);
void func_80012C98(Gfx **dList);
void func_80012CE8(Gfx **dList);
void render_object(Gfx **dList, Mtx **mtx, Vertex **verts, Object *obj);
void object_undo_player_tumble(Object *obj);
void render_object_parts(Object *obj);
void unset_temp_model_transforms(Object *obj);
void obj_tick_anims(void);
u32 func_800179D0(void);
void set_taj_challenge_type(s32 vehicleID);
s16 get_taj_challenge_type(void);
Object *find_taj_object(void);
void race_finish_adventure(s32 unusedArg);
s16 race_finish_timer(void);
u32 get_balloon_cutscene_timer(void);
s32 timetrial_valid_player_ghost(void);
Object *timetrial_player_ghost(void);
s32 timetrial_staff_ghost_check(Object *obj);
Object *timetrial_ghost_staff(void);
s32 timetrial_staff_unbeaten(void);
SIDeviceStatus timetrial_save_player_ghost(s32 controllerIndex);
u8 has_ghost_to_save(void);
void set_ghost_none(void);
f32 racer_calc_distance_to_opponent(Object_Racer *racer1, Object_Racer *racer2);
CheckpointNode *get_checkpoint_node(s32 checkpointID);
CheckpointNode *find_next_checkpoint_node(s32 splinePos, s32 isAlternate);
s32 get_checkpoint_count(void);
Object **get_racer_objects(s32 *numRacers);
Object **get_racer_objects_by_port(s32 *numRacers);
Object **get_racer_objects_by_position(s32 *numRacers);
Object *get_racer_object(s32 index);
void debug_render_checkpoint_node(s32 checkpointID, s32 pathID, Gfx **dList, Mtx **mtx, Vertex **vtx);
Object *spectate_object(s32 cameraIndex);
void ainode_enable(void);
void ainode_tail_set(s32 nodeID);
Object *ainode_tail(s32 *nodeID);
Object *ainode_get(s32 nodeID);
void set_world_shading(f32 ambient, f32 diffuse, s16 angleX, s16 angleY, s16 angleZ);
void set_shading_properties(ShadeProperties *arg0, f32 ambient, f32 diffuse, s16 angleX, s16 angleY, s16 angleZ);
void obj_shade_fancy(ObjectModel *model, Object *object, s32 arg2, f32 intensity);
s32 *get_misc_asset(s32 index);
s32 is_bridge_raised(s32 index);
void start_bridge_timer(s32 index);
void obj_bridge_pos(s32 timing, f32 *x, f32 *y, f32 *z);
s16 cutscene_id(void);
void cutscene_id_set(s32 cutsceneID);
void func_8001E45C(s32 cutsceneID);
s32 get_object_list_index(void);
s8 func_8001F3B8(void);
void func_8001F3C8(s32 arg0);
void func_8001F450(void);
s32 func_800210CC(s8 arg0);
s8 func_800214C4(void);
f32 lerp(f32 *data, u32 index, f32 t);
void func_800228DC(s32 arg0, s32 arg1, s32 arg2);
void init_racer_for_challenge(s32 vehicleID);
s8 is_taj_challenge(void);
s32 func_80023568(void);
s8 obj_door_override(void);
void obj_door_open(s32 setting);
void run_object_init_func(Object *obj, void *entry, s32 param);
void run_object_loop_func(Object *obj, s32 updateRate);
s16 *func_80024594(s32 *currentCount, s32 *maxCount);
void func_800245B4(s16 arg0);
void object_do_player_tumble(Object *this);
f32 catmull_rom_interpolation(f32 *data, s32 index, f32 x);
f32 cubic_spline_interpolation(f32 *data, s32 index, f32 x, f32 *derivative);
s16 obj_elevation(f32 yPos);
void func_80021400(s32 arg0);
s32 timetrial_init_player_ghost(s32 playerID);
s32 move_object(Object *obj, f32 xPos, f32 yPos, f32 zPos);
Object *get_racer_object_by_port(s32 index);
void render_racer_shield(Gfx **dList, Mtx **mtx, Vertex **vtxList, Object *obj);
void render_racer_magnet(Gfx **dList, Mtx **mtx, Vertex **vtxList, Object *obj);
void update_envmap_position(f32 x, f32 y, f32 z);
s32 init_object_water_effect(Object *obj, WaterEffect *waterEffect);
s32 timetrial_load_staff_ghost(s32 mapId);
void render_3d_billboard(Object *obj);
void render_misc_model(Object *obj, Vertex *verts, u32 numVertices, Triangle *triangles, u32 numTriangles,
                       TextureHeader *tex, u32 flags, u32 texOffset, f32 scaleY);
void racerfx_free(void);
void func_80016BC4(Object *obj);
s32 ainode_register(Object *obj);
void obj_taj_create_balloon(s32 blockID, f32 x, f32 y, f32 z);
Object *racer_find_nearest_opponent_relative(Object_Racer *racer, s32 position, f32 *distance);
s32 obj_init_collision(Object *obj, ObjectCollision *colData);
void func_8000E4E8(s32 index);
void objFreeAssets(Object *obj, s32 count, s32 objType);
void obj_collision_transform(Object *obj);
s32 play_footstep_sounds(Object *obj, s32 arg1, s32 frame, s32 oddSoundId, s32 evenSoundId);
void render_3d_misc(Object *obj);
Object *spectate_nearest(Object *obj, s32 *cameraId);
s32 init_object_shadow(Object *obj, ShadowData *shadow);
s32 render_mesh(ObjectModel *objModel, Object *obj, s32 startIndex, s32 flags, s32 overrideVerts);
void render_bubble_trap(ObjectTransform *trans, Sprite *gfxData, Object *obj, s32 flags);
void gParticlePtrList_flush(void);
s32 init_object_shading(Object *obj, ShadeProperties *shadeData);
ObjectHeader *load_object_header(s32 index);
s32 obj_init_attachpoint(Object *);
void try_free_object_header(s32 index);
s32 get_object_property_size(Object *obj, void *obj64);
void light_setup_light_sources(Object *obj);
s32 init_object_interaction_data(Object *obj, ObjectInteraction *interactObj);
s32 obj_init_emitter(Object *obj, ParticleEmitter *emitter);
s32 obj_init_property_flags(s32 behaviorId);
void tt_ghost_beaten(s32 arg0, s16 *playerId);
void obj_init_animobject(Object *, Object *);
Object *obj_butterfly_node(f32 x, f32 y, f32 z, f32 maxDistCheck, s32 dontCheckYAxis);
void func_8002125C(Object *obj, LevelObjectEntry_Animation *entry, Object_AnimatedObject *animObj, s32 index);
void func_80021104(Object *obj, Object_AnimatedObject *animObj, LevelObjectEntry_Animation *entry);
s32 homing_rocket_get_next_direction(Object *obj, s32 checkpoint, u8 isOnAlternateRoute, s32 arg3, s32 arg4,
                                     f32 checkpointDist, f32 *outX, f32 *outY, f32 *outZ);
void func_80016500(Object *obj, Object_Racer *racer);
void track_spawn_objects(s32, s32);
u8 timetrial_init_staff_ghost(s32 trackId);
s8 set_course_finish_flags(Settings *settings);
void process_object_interactions(void);
void render_3d_model(Object *obj);
void mode_end_taj_race(s32 reason);
void ainode_update(void);
void func_8001E6EC(s8);
Object *obj_spawn_attachment(s32 objID);
void sort_objects_by_dist(s32 startIndex, s32 lastIndex);
void func_80016748(Object *obj0, Object *obj1);
void race_finish_time_trial(void);
s32 obj_dist_racer(f32 x, f32 y, f32 z, f32 radius, s32 is2dCheck, Object **sortObj);
void mode_init_taj_race(void);
void racerfx_update(s32 updateRate);
f32 catmull_rom_derivative(f32 *data, s32 index, f32 x);
void race_transition_adventure(s32 updateRate);
void func_8001E4C4(void);
void racerfx_alloc(s32 numberOfVertices, s32 numberOfTriangles);
s32 func_80014B50(s32 arg0, s32 arg1, f32 arg2, u32 arg3);
s32 ainode_find_next(s32 nodeId, s32 nextNodeId, s32 direction);
unk800179D0 *func_8001790C(Object *arg0, Object *arg1);
unk800179D0 *func_80017978(Object *obj1, Object *obj2);
s8 func_800214E4(Object *obj, s32 updateRate);
f32 lerp_and_get_derivative(f32 *data, u32 index, f32 t, f32 *derivative);
void race_check_finish(s32 updateRate);
void obj_shade_fast(ObjectModel *model, Object *obj, f32 intensity);
s32 obj_animate(Object *obj);
void calc_dynamic_lighting_for_object_1(Object *, ObjectModel *, s16, Object *, f32, f32);
void calc_dynamic_lighting_for_object_2(Object *, ObjectModel *, s16, f32);
void decrypt_magic_codes(s32 *data, s32 length);
s32 get_first_active_object(s32 *);
Object *spawn_object(LevelObjectEntryCommon *entry, s32);
s32 func_8001F460(Object *, s32, Object *);
void func_8000B750(Object *racerObj, s32 racerIndex, s32 vehicleIDPrev, s32 boostType, s32 arg4);
void func_80018CE0(Object *racerObj, f32 xPos, f32 yPos, f32 zPos, s32 updateRate);
s32 checkpoint_is_passed(s32 checkpointIndex, Object *obj, f32 objX, f32 objY, f32 objZ, f32 *checkpointDistance,
                         u8 *isOnAlternateRoute);
void obj_tex_animate(Object *, s32);
Object *find_furthest_telepoint(f32 x, f32 z);
void model_init_collision(ObjectModel *);
void set_temp_model_transforms(Object *);
void obj_destroy(Object *, s32);
void func_800135B8(Object *);
void track_setup_racers(Vehicle, u32, s32);
void checkpoint_update_all(void);
void spectate_update(void);
void func_8001E93C(void);
void func_80019808(s32 updateRate);
void func_80014090(Object *, s32);
void audspat_update_all(Object **, s32, s32);
void func_8001E89C(void);
CheckpointNode *func_800230D0(Object *, Object_Racer *);
void obj_update(s32 updateRate);
void func_800159C8(Object *, Object *);
void obj_door_number(ObjectModel *, Object *);
s16 func_8001CD28(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
f32 func_8001C6C4(Object_NPC *, Object *, f32, f32, s32);
s32 collision_objectmodel(Object *obj, s32 arg1, s32* arg2, Vec3f *arg3, f32* arg4, f32* arg5, s8* surface);
s32 func_80017A18(ObjectModel *, s32, s32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, f32 *, s8 *argA,
                  f32);
typedef struct
{
              f32 factor;
              u16 offset;
              u32 scale;
} __OSViScale;
typedef struct
{
              u16 state;
              u16 retraceCount;
              void *framep;
              OSViMode *modep;
              u32 control;
               OSMesgQueue *msgq;
               OSMesg msg;
               __OSViScale x;
               __OSViScale y;
} __OSViContext;
void __osViSwapContext(void);
extern __OSViContext *__osViCurr;
extern __OSViContext *__osViNext;
extern u32 __additional_scanline;
__OSViContext *__osViGetCurrentContext(void);
void __osViInit(void);
extern OSDevMgr __osViDevMgr;
typedef char *va_list;
typedef struct TexFontCoords {
    u8 u, v;
} TexFontCoords;
void sprintfSetSpacingCodes(s32 setting);
void debug_text_init(void);
void set_render_printf_colour(u8 red, u8 green, u8 blue, u8 alpha);
void set_render_printf_background_colour(u8 red, u8 green, u8 blue, u8 alpha);
void debug_text_background(Gfx **dList, u32 ulx, u32 uly, u32 lrx, u32 lry);
s32 debug_text_character(Gfx **dList, s32 asciiVal);
void debug_text_print(Gfx **dList);
void set_render_printf_position(u16 x, u16 y);
s32 render_printf(const char *format, ...);
void debug_text_bounds(void);
void debug_text_origin(void);
void debug_text_newline(void);
s32 debug_text_parse(Gfx**, char*);
int vsprintf(char *s, const char *fmt, va_list args);
typedef struct HudPresets2P {
    s16 assetID;
    s16 x;
    s16 y;
} HudPresets2P;
typedef struct HudPresets4P {
    s16 assetID;
    s16 xLeft;
    s16 y;
    s16 xRight;
} HudPresets4P;
typedef enum RaceFinishStages {
    HUD_RACEFINISH_MUTE,
    HUD_RACEFINISH_TEXT_IN,
    HUD_RACEFINISH_TEXT_OUT,
    HUD_RACEFINISH_IDLE
} RaceFinishStages;
typedef enum TimeTrialFinishStages {
    TIMETRIAL_FINISH_INIT,
    TIMETRIAL_FINISH_IN,
    TIMETRIAL_FINISH_SHOW,
    TIMETRIAL_FINISH_OUT,
    TIMETRIAL_FINISH_IDLE,
    TIMETRIAL_FINISH_IDLE_2
} TimeTrialFinishStages;
typedef enum WrongWayStages {
    WRONGWAY_HIDE,
    WRONGWAY_SHOW
} WrongWayStages;
typedef enum LapTextStages {
    LAPTEXT_IDLE,
    LAPTEXT_UNK1,
    LAPTEXT_UNK2,
    LAPTEXT_UNK3
} LapTextStages;
typedef enum LapTextDirection {
    LAPTEXT_IN = -1,
    LAPTEXT_OUT = 1
} LapTextDirection;
typedef enum WrongWayDirection {
    WRONGWAY_OUT = -1,
    WRONGWAY_IN = 1
} WrongWayDirection;
enum CourseIndicatorArrows {
    INDICATOR_NONE,
    INDICATOR_LEFT,
    INDICATOR_LEFT_SHARP,
    INDICATOR_LEFT_UTURN,
    INDICATOR_RIGHT,
    INDICATOR_RIGHT_SHARP,
    INDICATOR_RIGHT_UTURN,
    INDICATOR_UP,
    INDICATOR_DOWN,
    INDICATOR_EXCLAMATION
};
enum HudElementNames {
    HUD_ELEMENT_UNK_00,
    HUD_ELEMENT_UNK_01,
    HUD_ELEMENT_UNK_02,
    HUD_ELEMENT_UNK_03,
    HUD_ELEMENT_UNK_04,
    HUD_ELEMENT_UNK_05,
    HUD_ELEMENT_UNK_06,
    HUD_ELEMENT_UNK_07,
    HUD_ELEMENT_UNK_08,
    HUD_ELEMENT_UNK_09,
    HUD_ELEMENT_UNK_0A,
    HUD_ELEMENT_UNK_0B,
    HUD_ELEMENT_UNK_0C,
    HUD_ELEMENT_UNK_0D,
    HUD_ELEMENT_UNK_0E,
    HUD_ELEMENT_UNK_0F,
    HUD_ELEMENT_UNK_10,
    HUD_ELEMENT_UNK_11,
    HUD_ELEMENT_UNK_12,
    HUD_ELEMENT_UNK_13,
    HUD_ELEMENT_UNK_14,
    HUD_ELEMENT_UNK_15,
    HUD_ELEMENT_UNK_16,
    HUD_ELEMENT_UNK_17,
    HUD_ELEMENT_UNK_18,
    HUD_ELEMENT_UNK_19,
    HUD_ELEMENT_UNK_1A,
    HUD_ELEMENT_UNK_1B,
    HUD_ELEMENT_UNK_1C,
    HUD_ELEMENT_UNK_1D,
    HUD_ELEMENT_UNK_1E,
    HUD_ELEMENT_UNK_1F,
    HUD_ELEMENT_UNK_20,
    HUD_ELEMENT_UNK_21,
    HUD_ELEMENT_UNK_22,
    HUD_ELEMENT_UNK_23,
    HUD_ELEMENT_UNK_24,
    HUD_ELEMENT_UNK_25,
    HUD_ELEMENT_UNK_26,
    HUD_ELEMENT_UNK_27
};
enum HudTypes {
    HUD_RACE_POSITION,
    HUD_RACE_POSITION_END,
    HUD_WEAPON_DISPLAY,
    HUD_LAP_COUNT_LABEL,
    HUD_LAP_COUNT_CURRENT,
    HUD_LAP_COUNT_SEPERATOR,
    HUD_LAP_COUNT_TOTAL,
    HUD_BANANA_COUNT_ICON_SPIN,
    HUD_BANANA_COUNT_NUMBER_1,
    HUD_BANANA_COUNT_NUMBER_2,
    HUD_RACE_TIME_LABEL,
    HUD_RACE_TIME_NUMBER,
    HUD_RACE_START_GO,
    HUD_RACE_START_READY,
    HUD_RACE_END_FINISH,
    HUD_MINIMAP_MARKER,
    HUD_LAP_COUNT_FLAG,
    HUD_MAGNET_RETICLE,
    HUD_BANANA_COUNT_X,
    HUD_BALLOON_COUNT_ICON,
    HUD_BALLOON_COUNT_X,
    HUD_BALLOON_COUNT_NUMBER_1,
    HUD_BALLOON_COUNT_NUMBER_2,
    HUD_LAP_TIME_TEXT,
    HUD_TIME_TRIAL_LAP_TEXT,
    HUD_TIME_TRIAL_LAP_NUMBER,
    HUD_STOPWATCH_HANDS,
    HUD_BANANA_COUNT_ICON_STATIC,
    HUD_BANANA_COUNT_SPARKLE,
    HUD_LAP_TEXT_FINAL,
    HUD_LAP_TEXT_LAP,
    HUD_LAP_TEXT_TWO,
    HUD_TREASURE_METRE,
    HUD_COURSE_ARROWS,
    HUD_STOPWATCH,
    HUD_WRONGWAY_1,
    HUD_WRONGWAY_2,
    HUD_PRO_AM_LOGO,
    HUD_SPEEDOMETRE_ARROW,
    HUD_SPEEDOMETRE_0,
    HUD_SPEEDOMETRE_30,
    HUD_SPEEDOMETRE_60,
    HUD_SPEEDOMETRE_90,
    HUD_SPEEDOMETRE_120,
    HUD_SPEEDOMETRE_150,
    HUD_SPEEDOMETRE_BG,
    HUD_SILVER_COIN_TALLY,
    HUD_CHALLENGE_FINISH_POS_1,
    HUD_CHALLENGE_FINISH_POS_2,
    HUD_WEAPON_QUANTITY,
    HUD_CHALLENGE_PORTRAIT,
    HUD_EGG_CHALLENGE_ICON,
    HUD_BATTLE_BANANA_ICON,
    HUD_BATTLE_BANANA_X,
    HUD_BATTLE_BANANA_COUNT_1,
    HUD_BATTLE_BANANA_COUNT_2,
    HUD_RACE_FINISH_POS_1,
    HUD_TWO_PLAYER_ADV_PORTRAIT,
    HUD_RACE_FINISH_POS_2,
    HUD_ELEMENT_COUNT
};
enum HudAssets {
    HUD_ASSET_0,
    HUD_SPRITE_WEAPONS,
    HUD_ASSET_2,
    HUD_ASSET_3,
    HUD_ASSET_4,
    HUD_SPRITE_FINISH,
    HUD_ASSET_6,
    HUD_SPRITE_GO_BIG,
    HUD_SPRITE_BANANA_ANIM,
    HUD_ASSET_NUMBERS,
    HUD_ASSET_NUMBERS_SMALL,
    HUD_ASSET_SEPERATOR,
    HUD_ASSET_SEPERATOR_SMALL,
    HUD_ASSET_13,
    HUD_SPRITE_MAP_DOT,
    HUD_ASSET_15,
    HUD_SPRITE_CHEQUER_FLAG,
    HUD_SPRITE_RETICLE,
    HUD_ASSET_18,
    HUD_SPRITE_GOLD_BALLOON,
    HUD_ASSET_20,
    HUD_SPRITE_BANANA_STATIC,
    HUD_SPRITE_GET_READY,
    HUD_ASSET_23,
    HUD_SPRITE_LAP_FINAL,
    HUD_SPRITE_LAP_LAP,
    HUD_SPRITE_LAP_2,
    HUD_SPRITE_MAP_ARROW,
    HUD_ASSET_28,
    HUD_SPRITE_INDICATOR_EXCLAMATION,
    HUD_SPRITE_INDICATOR_DOWN,
    HUD_SPRITE_INDICATOR_U,
    HUD_SPRITE_INDICATOR_TURN_90,
    HUD_SPRITE_INDICATOR_TURN_45,
    HUD_ASSET_34,
    HUD_SPRITE_WRONG,
    HUD_SPRITE_WAY,
    HUD_SPRITE_GO_SMALL,
    HUD_SPRITE_LAP_LAP_SMALL,
    HUD_SPRITE_GET_READY_SMALL,
    HUD_SPRITE_PRO_AM,
    HUD_SPRITE_LAP_FINAL_SMALL,
    HUD_SPRITE_FINISH_SMALL,
    HUD_SPRITE_LAP_2_SMALL,
    HUD_SPRITE_WAY_SMALL,
    HUD_SPRITE_WRONG_SMALL,
    HUD_SPRITE_SPEEDOMETRE_ARROW,
    HUD_ASSET_47,
    HUD_ASSET_48,
    HUD_ASSET_49,
    HUD_ASSET_50,
    HUD_ASSET_51,
    HUD_ASSET_52,
    HUD_ASSET_53,
    HUD_ASSET_54,
    HUD_SPRITE_WEAPON_NUMBER,
    HUD_SPRITE_PORTRAIT,
    HUD_ASSET_57,
    HUD_ASSET_58,
    HUD_ASSET_59,
    HUD_ASSET_60,
    HUD_ASSET_61,
    HUD_ASSET_62,
    HUD_ASSET_63,
    HUD_ASSET_64,
    HUD_ASSET_65,
    HUD_ASSET_66,
    HUD_SPRITE_PLACE_1,
    HUD_SPRITE_PLACE_ST,
    HUD_SPRITE_BALLOON_DIAMOND
};
typedef struct HudElementBase {
    s16 y_rotation;
    s16 x_rotation;
    s16 z_rotation;
    s16 spriteID;
    f32 scale;
    f32 x;
    f32 y;
    f32 z;
    s16 spriteOffset;
} HudElementBase;
typedef struct HudElement_ChallengeEggs {
    s8 alphaTimer;
} HudElement_ChallengeEggs;
typedef struct HudElement_RaceStartGo {
    s8 musicStartTimer[4];
} HudElement_RaceStartGo;
typedef struct HudElement_BananaCountIconSpin {
    s8 spinCounter;
    s8 visualCounter;
} HudElement_BananaCountIconSpin;
typedef struct HudElement_BananaCountSparkle {
    s8 sparkleTimer;
    s8 sparkleCounter;
} HudElement_BananaCountSparkle;
typedef struct HudElement_SilverCoinTally {
    s8 soundPlayed;
    s8 soundTimer;
    s8 offsetY;
} HudElement_SilverCoinTally;
typedef struct HudElement_RaceFinishPos {
    s8 status;
    s8 textOutTimer;
    s8 textOutTicks;
    s8 targetPos;
} HudElement_RaceFinishPos;
typedef struct HudElement_RacePosition {
    s8 active;
    s8 scaleCounter;
    s8 baseScale;
} HudElement_RacePosition;
typedef struct HudElement_LapCountFlag {
    s8 visualCounter;
} HudElement_LapCountFlag;
typedef struct HudElement_LapText {
    s8 status;
    s8 direction;
    s8 targetPos;
    s8 soundPlayed;
} HudElement_LapText;
typedef struct HudElement_Timer {
    s8 minutes;
    s8 seconds;
    s8 hundredths;
    s8 unk1D;
} HudElement_Timer;
typedef struct HudElement_FinishText {
    s8 status;
    s8 fadeTimer;
    s8 unk1C;
    s8 targetPos;
} HudElement_FinishText;
typedef struct HudElement_WeaponDisplay {
    s8 hideTimer;
    s8 rotation;
    s8 scale;
    s8 prevLevel;
} HudElement_WeaponDisplay;
typedef struct HudElement_RaceTimeLabel {
    s8 hideTimer;
    s8 hundredths;
} HudElement_RaceTimeLabel;
typedef struct HudElement {
               Vec3s rotation;
               s16 spriteID;
               f32 scale;
               Vec3f pos;
               s16 spriteOffset;
               union {
        u8 filler[4];
        HudElement_ChallengeEggs challengeEggs;
        HudElement_RaceStartGo raceStartGo;
        HudElement_BananaCountIconSpin bananaCountIconSpin;
        HudElement_BananaCountSparkle bananaCountSparkle;
        HudElement_SilverCoinTally silverCoinTally;
        HudElement_RaceFinishPos raceFinishPos;
        HudElement_RacePosition racePosition;
        HudElement_LapCountFlag lapCountFlag;
        HudElement_LapText lapText;
        HudElement_Timer timer;
        HudElement_FinishText finishText;
        HudElement_WeaponDisplay weaponDisplay;
        HudElement_RaceTimeLabel raceTimeLabel;
    };
} HudElement;
typedef struct HudData {
               HudElement entry[HUD_ELEMENT_COUNT];
} HudData;
typedef struct HudAudio {
    u16 soundID;
    u8 volume;
    s8 volumeRamp;
    SoundHandle soundMask;
    s32 unk8;
    s8 playerIndex;
    s8 unkD;
    s8 unkE;
    s8 unkF;
} HudAudio;
typedef struct HudElements {
    void *entry[HUD_ELEMENT_COUNT];
} HudElements;
typedef struct HudDrawTexture {
    DrawTexture drawTexture;
    s32 unk8;
} HudDrawTexture;
extern u8 gGfxTaskYieldData[0xA00];
u8 race_starting(void);
void hud_audio_init(void);
void hud_main_race(s32 countdown, Object *obj, s32 updateRate);
void hud_main_eggs(s32 countdown, Object *obj, s32 updateRate);
void hud_main_boss(s32 countdown, Object *obj, s32 updateRate);
void hud_main_taj(s32 countdown, Object *obj, s32 updateRate);
void hud_speedometre_reset(void);
void hud_time_trial_message(s16 *playerID);
void hud_sound_play_delayed(u16 soundID, f32 delay, s32 playerIndex);
void hud_sound_stop(u16 soundID, s32 playerIndex);
void minimap_init(LevelModel *model);
s8 hud_setting(void);
void minimap_fade(s32 setting);
void minimap_opacity_set(s32 setting);
void func_800AB1C8(void);
void hud_visibility(u8 setting);
void hud_race_time(Object_Racer *racer, s32 updateRate);
void hud_wrong_way(Object_Racer *obj, s32 updateRate);
void hud_course_arrows(Object_Racer *racer, s32 updateRate);
void hud_main_hub(Object *obj, s32 updateRate);
void hud_render_player(Gfx **dList, Mtx **mtx, Vertex **vertexList, Object *obj, s32 updateRate);
void hud_weapon(Object *obj, s32 updateRate);
void hud_race_start(s32 countdown, s32 updateRate);
void hud_bananas(Object_Racer *racer, s32 updateRate);
void hud_race_finish_1player(Object_Racer *racer, s32 updateRate);
void hud_speedometre(Object *obj, s32 updateRate);
void hud_lap_count(Object_Racer *racer, s32 updateRate);
void hud_render_general(Gfx **dList, Mtx **mtx, Vertex **vtx, s32 updateRate);
void hud_init(s32 viewportCount);
void hud_main_battle(s32 countdown, Object *obj, s32 updateRate);
void hud_lives_render(Object_Racer *racer, s32 updateRate);
void hud_free(void);
void hud_stopwatch_face(u8, u8, u8, u8, u8);
void hud_audio_update(s32 updateRate);
void hud_silver_coins(Object_Racer *racer, s32 updateRate);
void hud_magnet_reticle(Object *racerObj);
void hud_time_trial_finish(Object_Racer *racer, s32 updateRate);
void hud_eggs_portrait(Object_Racer *racer, s32 updateRate);
void hud_draw_eggs(Object *racerObj, s32 updateRate);
void hud_race_position(Object_Racer *racer, s32 updateRate);
void hud_main_treasure(s32 countdown, Object *obj, s32 updateRate);
void hud_balloons(Object_Racer *racer);
void hud_treasure(Object_Racer *racer);
void minimap_marker_pos(f32 x, f32 z, f32 angleSin, f32 angleCos, f32 modelAspectRatio);
void hud_timer_render(s32 x, s32 y, s32 minutes, s32 seconds, s32 hundredths, s32 smallFont);
void hud_draw_model(ObjectModel *objModel);
void hud_element_render(Gfx **dList, Mtx **mtx, Vertex **vtxList, HudElement *hud);
void hud_main_time_trial(s32, Object*, s32);
void hud_race_finish_multiplayer(Object_Racer *racer, s32 updateRate);
void hud_battle_portraits(Object*, s32 updateRate);
void hud_init_element(void);
enum TextureRectangleFlags {
    TEXRECT_BILERP,
    TEXRECT_POINT = (1 << 0),
    TEXRECT_FLIP_X = (1 << 12),
    TEXRECT_FLIP_Y = (1 << 13),
};
typedef s32 (*BackgroundFunction)(Gfx **, Mtx **);
typedef struct DKR_OSTask {
    struct DKR_OSTask *next;
    u32 state;
    u32 flags;
    void *frameBuffer;
    OSTask_t task;
    OSMesgQueue *mesgQueue;
    OSMesg mesg;
    s32 unused58;
    s32 unused5C;
    s32 unused60;
    s32 unused64;
    u32 unk68;
    s32 unused6C;
} DKR_OSTask;
extern s16 gGfxTaskMesgNums[16];
extern s32 sBackgroundFillColour;
extern TextureHeader *gTexBGTex1;
extern TextureHeader *gTexBGTex2;
extern s32 gChequerBGEnabled;
extern s32 gGfxBufCounter;
extern s32 gGfxBufCounter2;
extern s32 gGfxTaskIsRunning;
extern long long int rspF3DDKRDramStart[], rspF3DDKRDramEnd[];
extern long long int rspF3DDKRXbusStart[], rspF3DDKRXbusEnd[];
extern long long int rspF3DDKRDataXbusStart[], rspF3DDKRDataXbusEnd[];
extern long long int rspF3DDKRFifoStart[], rspF3DDKRFifoEnd[];
extern long long int rspF3DDKRDataFifoStart[], rspF3DDKRDataFifoEnd[];
s32 gfxtask_wait(void);
void bgdraw_primcolour(u8 red, u8 green, u8 blue);
void bgdraw_fillcolour(s32 red, s32 green, s32 blue);
void rdp_init(Gfx **dList);
void rsp_init(Gfx **dList);
void gfxtask_init(OSSched *sc);
void bgdraw_texture_init(TextureHeader *tex1, TextureHeader *tex2, u32 shiftX);
void bgdraw_texture(Gfx **dList);
s32 gfxtask_run_xbus(Gfx* dlBegin, Gfx* dlEnd, s32 recvMesg);
void gfxtask_run_fifo(Gfx* dlBegin, Gfx* dlEnd, s32 recvMesg);
void texrect_draw(Gfx **dList, DrawTexture *element, s32 xPos, s32 yPos, u8 red, u8 green, u8 blue,
                               u8 alpha);
void bgdraw_chequer(Gfx** dList);
void bgdraw_render(Gfx **dList, Mtx **mtx, s32 drawBG);
void bgdraw_set_func(BackgroundFunction func);
void texrect_draw_scaled(Gfx **dList, DrawTexture *element, f32 xPos, f32 yPos, f32 xScale, f32 yScale, u32 colour, s32 flags);
enum CourseRecordNames {
    COURSE_FC_CAR,
    COURSE_FC_HOVER,
    COURSE_FC_PLANE,
    COURSE_PL_HOVER,
    COURSE_AL_CAR,
    COURSE_AL_HOVER,
    COURSE_AL_PLANE,
    COURSE_WC_CAR,
    COURSE_WC_HOVER,
    COURSE_HTV_HOVER,
    COURSE_HTV_PLANE,
    COURSE_WB_HOVER,
    COURSE_SV_CAR,
    COURSE_SV_HOVER,
    COURSE_CI_CAR,
    COURSE_CI_HOVER,
    COURSE_EP_CAR,
    COURSE_EP_HOVER,
    COURSE_EP_PLANE,
    COURSE_SPA_CAR,
    COURSE_SPA_HOVER,
    COURSE_SPA_PLANE,
    COURSE_SA_CAR,
    COURSE_SA_HOVER,
    COURSE_SA_PLANE,
    COURSE_GV_CAR,
    COURSE_GV_HOVER,
    COURSE_BC_HOVER,
    COURSE_WP_CAR,
    COURSE_WP_HOVER,
    COURSE_WP_PLANE,
    COURSE_FV_CAR,
    COURSE_FV_HOVER,
    COURSE_FV_PLANE,
    COURSE_JF_CAR,
    COURSE_JF_HOVER,
    COURSE_JF_PLANE,
    COURSE_TC_CAR,
    COURSE_TC_HOVER,
    COURSE_TC_PLANE,
    COURSE_HW_CAR,
    COURSE_HW_HOVER,
    COURSE_DMC_CAR,
    COURSE_DMC_HOVER,
    COURSE_SC_CAR,
    COURSE_SC_HOVER,
    COURSE_SC_PLANE,
    COURSE_RECORD_TOTAL
};
typedef struct SaveConfig {
    unsigned unlockedAdv2 : 1;
    unsigned unlockedDrumstick : 1;
    unsigned language : 2;
    unsigned courseAL : 1; unsigned courseFC : 1; unsigned courseJF : 1; unsigned courseHTV : 1; unsigned courseWB : 1; unsigned courseCI : 1; unsigned coursePL : 1; unsigned courseTC : 1; unsigned courseEP : 1; unsigned courseWC : 1; unsigned courseSV : 1; unsigned courseFV : 1; unsigned courseBC : 1; unsigned courseGV : 1; unsigned courseWP : 1; unsigned courseHW : 1; unsigned courseSA : 1; unsigned courseDMC : 1; unsigned courseSC : 1; unsigned courseSPA : 1;
    unsigned subtitles : 1;
    unsigned unk0 : 31;
} SaveConfig;
typedef struct SaveFile {
    unsigned checksum : 16;
    unsigned courseBluey1 : 2; unsigned courseFossilCanyon : 2; unsigned coursePirateLagoon : 2; unsigned courseAncientLake : 2; unsigned courseWalrusCove : 2; unsigned courseHotTopVolcano : 2; unsigned courseWhaleBay : 2; unsigned courseSnowballValley : 2; unsigned courseCrescentIsland : 2; unsigned courseFireMountain : 2; unsigned courseEverfrostPeak : 2; unsigned courseSpaceportAlpha : 2; unsigned courseSpacedustAlley : 2; unsigned courseGreenwoodVillage : 2; unsigned courseBoulderCanyon : 2; unsigned courseWindmillPlains : 2; unsigned courseSmokeyCastle : 2; unsigned courseDarkwaterBeach : 2; unsigned courseIciclePyramid : 2; unsigned courseFrostyVillage : 2; unsigned courseJungleFalls : 2; unsigned courseTreasureCaves : 2; unsigned courseHauntedWoods : 2; unsigned courseDarkmoonCaverns : 2; unsigned courseStarCity : 2; unsigned courseWizpig1 : 2; unsigned courseTricky1 : 2; unsigned courseBubbler1 : 2; unsigned courseSmokey1 : 2; unsigned courseTricky2 : 2; unsigned courseBluey2 : 2; unsigned courseBubbler2 : 2; unsigned courseSmokey2 : 2; unsigned courseWizpig2 : 2;
    unsigned tajFlags : 6;
    unsigned trophy1 : 2;
    unsigned trophy2 : 2;
    unsigned trophy3 : 2;
    unsigned trophy4 : 2;
    unsigned trophy5 : 2;
    unsigned bossWizpig1 : 1;
    unsigned bossTricky1 : 1;
    unsigned bossBubbler1 : 1;
    unsigned bossBluey1 : 1;
    unsigned bossSmokey1 : 1;
    unsigned bossWizpig2 : 1;
    unsigned bossTricky2 : 1;
    unsigned bossBubbler2 : 1;
    unsigned bossBluey2 : 1;
    unsigned bossSmokey2 : 1;
    unsigned bossUnused1 : 1;
    unsigned bossUnused2 : 1;
    unsigned balloonsTotal : 7;
    unsigned balloonsWorld1 : 7;
    unsigned balloonsWorld2 : 7;
    unsigned balloonsWorld3 : 7;
    unsigned balloonsWorld4 : 7;
    unsigned balloonsWorld5 : 7;
    unsigned amuletTT : 3;
    unsigned amuletWizpig : 3;
    unsigned flagsWorld0 : 16;
    unsigned flagsWorld1 : 16;
    unsigned flagsWorld2 : 16;
    unsigned flagsWorld3 : 16;
    unsigned flagsWorld4 : 16;
    unsigned flagsWorld5 : 16;
    unsigned keyWorld0 : 1;
    unsigned keyWorld1 : 1;
    unsigned keyWorld2 : 1;
    unsigned keyWorld3 : 1;
    unsigned keyWorld4 : 1;
    unsigned keyWorld5 : 1;
    unsigned keyWorld6 : 1;
    unsigned keyWorld7 : 1;
    unsigned sceneLighthouse : 1;
    unsigned sceneTTHelp : 1;
    unsigned sceneAdv2 : 1;
    unsigned sceneWorld1Boss1 : 1;
    unsigned sceneWorld2Boss1 : 1;
    unsigned sceneWorld3Boss1 : 1;
    unsigned sceneWorld4Boss1 : 1;
    unsigned sceneWorld5Boss1 : 1;
    unsigned sceneWorld1Boss2 : 1;
    unsigned sceneWorld2Boss2 : 1;
    unsigned sceneWorld3Boss2 : 1;
    unsigned sceneWorld4Boss2 : 1;
    unsigned sceneWorld5Boss2 : 1;
    unsigned sceneWizpigFace : 1;
    unsigned sceneWorld1Key : 1;
    unsigned sceneWorld2Key : 1;
    unsigned sceneWorld3Key : 1;
    unsigned sceneWorld4Key : 1;
    unsigned sceneWorld5Key : 1;
    unsigned name : 15;
} SaveFile;
typedef struct CourseRecords {
    u16 checksum;
    u16 padding;
    u32 courseTime[COURSE_RECORD_TOTAL];
} CourseRecords;
typedef struct SaveBuffer {
    SaveFile gameSave[3];
    SaveConfig config;
    CourseRecords fastLaps;
    CourseRecords courseTimes;
} SaveBuffer ;
enum RenderFlags {
    RENDER_NONE,
    RENDER_VEHICLE_PART = (1 << 0),
    RENDER_ANTI_ALIASING = (1 << 0),
    RENDER_Z_COMPARE = (1 << 1),
    RENDER_SEMI_TRANSPARENT = (1 << 2),
    RENDER_FOG_ACTIVE = (1 << 3),
    RENDER_CUTOUT = (1 << 4),
    RENDER_COLOUR_INDEX = (1 << 5),
    RENDER_CLAMP_X = (1 << 6),
    RENDER_CLAMP_Y = (1 << 7),
    RENDER_Z_UPDATE = (1 << 8),
    RENDER_HIDDEN = (1 << 8),
    RENDER_PRESERVE_COVERAGE = (1 << 9),
    RENDER_NO_COLLISION = (1 << 9),
    RENDER_LINE_SWAP = (1 << 10),
    RENDER_DECAL = (1 << 11),
    RENDER_UNK_0001000 = (1 << 12),
    RENDER_WATER = (1 << 13),
    RENDER_NO_SHADOW = (1 << 14),
    RENDER_ENVMAP = (1 << 15),
    RENDER_TEX_ANIM = (1 << 16),
    RENDER_UNK_0020000 = (1 << 17),
    RENDER_PULSING_LIGHTS = (1 << 18),
    RENDER_UNK_0080000 = (1 << 19),
    RENDER_UNK_0100000 = (1 << 20),
    RENDER_UNK_0200000 = (1 << 21),
    RENDER_UNK_0400000 = (1 << 22),
    RENDER_UNK_0800000 = (1 << 23),
    RENDER_UNK_1000000 = (1 << 24),
    RENDER_UNK_2000000 = (1 << 25),
    RENDER_UNK_4000000 = (1 << 26),
    RENDER_VTX_ALPHA = (1 << 27),
    RENDER_UNK_10000000 = (1 << 28),
    RENDER_UNK_20000000 = (1 << 29),
    RENDER_UNK_40000000 = (1 << 30),
    RENDER_UNK_80000000 = (1 << 31),
    RENDER_ALL = 0xFFFFFFFF
};
typedef enum TextureRenderModes {
    TRANSPARENT,
    OPAQUE,
    TRANSPARENT_2,
    OPAQUE_2
} TextureRenderModes;
typedef enum TransFlags {
    OBJ_FLAGS_NONE,
    OBJ_FLAGS_UNK_0001 = (1 << 0),
    OBJ_FLAGS_UNK_0002 = (1 << 1),
    OBJ_FLAGS_UNK_0004 = (1 << 2),
    OBJ_FLAGS_UNK_0008 = (1 << 3),
    OBJ_FLAGS_UNK_0010 = (1 << 4),
    OBJ_FLAGS_DESPAWN_TIME_TRIAL = (1 << 5),
    OBJ_FLAGS_DESPAWN_MULTIPLAYER = (1 << 6),
    OBJ_FLAGS_UNK_0080 = (1 << 7),
    OBJ_FLAGS_UNK_0100 = (1 << 8),
    OBJ_FLAGS_INVIS_PLAYER1 = (1 << 9),
    OBJ_FLAGS_INVIS_PLAYER2 = (1 << 10),
    OBJ_FLAGS_UNK_0800 = (1 << 11),
    OBJ_FLAGS_SHADOW_ONLY = (1 << 12),
    OBJ_FLAGS_UNK_2000 = (1 << 13),
    OBJ_FLAGS_INVISIBLE = (1 << 14),
    OBJ_FLAGS_PARTICLE = (1 << 15)
} TransFlags;
typedef enum HeaderFlags {
    HEADER_FLAGS_NONE,
    HEADER_FLAGS_UNK_0001 = (1 << 0),
    HEADER_FLAGS_WATER_EFFECT = (1 << 4),
    HEADER_FLAGS_UNK_0080 = (1 << 7),
} HeaderFlags;
typedef enum BasicRenderIDs {
    DRAW_BASIC_ZB_OFF,
    DRAW_BASIC_1CYCLE,
    DRAW_BASIC_2CYCLE,
    DRAW_BASIC_IDS
} BasicRenderIDs;
typedef struct TextureCacheEntry {
    s32 id;
    TextureHeader *texture;
} TextureCacheEntry;
typedef struct SpriteCacheEntry {
    s32 id;
    Sprite *sprite;
} SpriteCacheEntry;
typedef struct TempTexHeader {
           TextureHeader header;
           u32 uncompressedSize;
           u8 gzipLevel;
           u8 pad25[3];
} TempTexHeader;
void tex_disable_modes(s32 flags);
void tex_enable_modes(s32 flags);
s32 tex_get_table_2D(void);
s32 tex_get_table_3D(void);
s32 sprite_table_size(void);
void set_texture_colour_tag(s32 tagID);
void rendermode_reset(Gfx **dList);
void directional_lighting_on(void);
void directional_lighting_off(void);
void material_set_no_tex_offset(Gfx **dList, TextureHeader *texhead, u32 flags);
void sprite_opaque(s32 setting);
s32 tex_palette_id(s16 paletteID);
void material_set(Gfx **dList, TextureHeader *texhead, s32 flags, s32 texOffset);
void sprite_free(Sprite *sprite);
void tex_free(TextureHeader *tex);
void material_load_simple(Gfx **dList, s32 flags);
void tex_animate_texture(TextureHeader *texture, u32 *triangleBatchInfoFlags, s32 *arg2, s32 updateRate);
void func_8007F1E8(LevelHeader_70 *arg0);
void init_pulsating_light_data(PulsatingLightData *data);
void update_pulsating_light_data(PulsatingLightData *data, s32 timeDelta);
TextureHeader *set_animated_texture_header(TextureHeader *texHead, s32 offset);
TextureHeader *load_texture(s32 id);
s32 tex_asset_size(s32 id);
s32 tex_cache_asset_id(s32 cacheID);
s32 load_sprite_info(s32 spriteIndex, s32 *anchorXOut, s32 *anchorYOut, s32 *numFramesOut, s32 *formatOut,
                     s32 *sizeOut);
void gfx_init_basic_xlu(Gfx **dList, u32 index, u32 primitiveColor, u32 environmentColor);
void func_8007CA68(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3, s32 *arg4);
Sprite *tex_load_sprite(s32 spriteID, s32 arg1);
void tex_init_textures(void);
void material_set_blinking_lights(Gfx **dList, TextureHeader *texture_list, u32 flags,
                                  s32 texture_index);
void material_init(TextureHeader *tex, Gfx *_dList);
void sprite_init_frame(SpriteAsset *spriteAsset, Sprite *sprite, s32 frameId);
void bgload_init(void);
void bgload_kill(void);
s32 bgload_active(void);
void bgload_tick(void);
s32 bgload_timer(void);
s32 bgload_start(s32 levelId, s32 cutsceneId);
void thread30_bgload(void *arg);
typedef enum GameMode {
    GAMEMODE_INTRO = -1,
    GAMEMODE_INGAME,
    GAMEMODE_MENU,
    GAMEMODE_UNUSED_2,
    GAMEMODE_UNUSED_3,
    GAMEMODE_UNUSED_4,
    GAMEMODE_LOCKUP
} GameMode;
enum LevelLoadType {
    LEVEL_LOAD_NORMAL,
    LEVEL_LOAD_UNK1,
    LEVEL_LOAD_TROPHY_RACE,
    LEVEL_LOAD_LIGHTHOUSE_CUTSCENE,
    LEVEL_LOAD_FUTURE_FUN_LAND,
};
enum LevelLoadContext {
    LEVEL_CONTEXT_NONE,
    LEVEL_CONTEXT_TRACK_SELECT,
    LEVEL_CONTEXT_RESULTS,
    LEVEL_CONTEXT_TROPHY_ROUND,
    LEVEL_CONTEXT_TROPHY_RESULTS,
    LEVEL_CONTEXT_UNUSED,
    LEVEL_CONTEXT_CHARACTER_SELECT,
    LEVEL_CONTEXT_UNK7,
    LEVEL_CONTEXT_CREDITS
};
extern s32 gSaveDataFlags;
void thread3_main( void *unused);
void init_game(void);
void main_game_loop(void);
void load_next_ingame_level(s32 numPlayers, s32 trackID, Vehicle vehicle);
void load_level_game(s32 levelId, s32 numberOfPlayers, s32 entranceId, Vehicle vehicleId);
void unload_level_game(void);
void set_drumstick_unlock_transition(void);
void race_postrace_type(s32 finishState);
void func_8006D8F0(s32 arg0);
void func_8006D968(s8 *arg0);
GameMode get_game_mode(void);
void load_menu_with_level_background(s32 menuId, s32 levelId, s32 cutsceneId);
void set_level_default_vehicle(Vehicle vehicleID);
void set_vehicle_id_for_menu(Vehicle vehicleId);
Vehicle get_level_default_vehicle(void);
void load_level_menu(s32 levelId, s32 numberOfPlayers, s32 entranceId, Vehicle vehicleId, s32 cutsceneId);
void unload_level_menu(void);
void update_menu_scene(s32 updateRate);
void load_level_for_menu(s32 levelId, s32 numberOfPlayers, s32 cutsceneId);
void calc_and_alloc_heap_for_settings(void);
void init_racer_headers(void);
void clear_lap_records(Settings *settings, s32 flags);
void clear_game_progress(Settings *settings);
void reset_save_data(void);
Settings *get_settings(void);
s8 is_game_paused(void);
s8 is_postrace_viewport_active(void);
s32 is_reset_pressed(void);
s32 get_ingame_map_id(void);
void mark_to_read_flap_times(void);
void mark_to_read_course_times(void);
void mark_to_read_flap_and_course_times(void);
void mark_read_save_file(s32 saveFileIndex);
void mark_read_all_save_files(void);
void mark_to_write_flap_times(void);
void mark_to_write_course_times(void);
void mark_to_write_flap_and_course_times(void);
void force_mark_write_save_file(s32 saveFileIndex);
void safe_mark_write_save_file(s32 saveFileIndex);
void mark_save_file_to_erase(s32 saveFileIndex);
void mark_read_eeprom_settings(void);
void mark_write_eeprom_settings(void);
s32 drm_validate_dmem(void);
void level_transition_begin(s32 type);
void func_8006F20C(void);
void begin_trophy_race_teleport(void);
void begin_lighthouse_rocket_cutscene(void);
void begin_level_teleport(s32 levelID);
void set_pause_lockout_timer(u8 time);
void swap_lead_player(void);
void set_frame_blackout_timer(void);
void mode_intro(void);
s32 is_controller_missing(void);
s32 drm_validate_imem(void);
void mode_game(s32 updateRate);
void level_load(s32 levelId, s32 numberOfPlayers, s32 entranceId, Vehicle vehicleId, s32 cutsceneId);
void level_global_init(void);
void alloc_displaylist_heap(s32 numberOfPlayers);
void default_alloc_displaylist_heap(void);
void mode_menu(s32 updateRate);
enum ShadowUpdate { SHADOW_NONE, SHADOW_SCENERY, SHADOW_ACTORS };
typedef struct unk8011C8B8 {
               f32 x;
               f32 y;
               f32 z;
    union {
                   f32 w;
        struct {
                       s16 unkC;
                       s16 unkE;
        } s;
    } unkC_union;
} unk8011C8B8;
typedef struct unk8011B120 {
               f32 x;
               f32 y;
               f32 z;
               unk8011C8B8 *unkC;
} unk8011B120;
typedef struct unk8011B330 {
               f32 x;
               f32 y;
               f32 z;
               unk8011C8B8 *unkC;
               f32 unk10;
               f32 unk14;
               f32 unk18;
               f32 unk1C;
} unk8011B330;
typedef struct VoidMesh {
    Triangle *tris[2];
    Vertex *verts[2];
} VoidMesh;
typedef struct unk8011C238 {
    u8 unk0;
    u8 unk1;
    u8 unk2[8];
    s16 unkA;
} unk8011C238;
typedef struct unk8011D478 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s8 unk6;
    s8 unk7;
} unk8011D478;
typedef struct unk8011C3B8 {
               s16 x1;
               s16 y1;
               s16 z1;
               s16 x2;
               s16 y2;
               s16 z2;
               s16 x3;
               s16 y3;
               s16 z3;
               s16 unk12;
} unk8011C3B8;
typedef struct EnvironmentFog {
    s32 r;
    s32 g;
    s32 b;
    s32 near;
    s32 far;
} EnvironmentFog;
typedef struct EnvironmentFogCompact {
    u8 r;
    u8 g;
    u8 b;
    s16 near;
    s16 far;
} EnvironmentFogCompact;
typedef struct FogData {
    EnvironmentFog fog;
    EnvironmentFog addFog;
    EnvironmentFogCompact intendedFog;
    s32 switchTimer;
    Object *fogChanger;
} FogData;
typedef struct WaterProperties {
               f32 waveHeight;
               Vec3f rot;
               s8 type;
} WaterProperties;
s32 set_scene_viewport_num(s32 numPorts);
void void_free(void);
void skydome_spawn(s32 objectID);
void set_skydome_visbility(s32 renderSky);
void skydome_render(void);
void set_anti_aliasing(s32 setting);
void add_segment_to_order(s32 segmentIndex, s32 *segmentsOrderIndex, u8 *segmentsOrder);
s32 get_inside_segment_count_xz(s32 x, s32 z, s32 *arg2);
s32 get_inside_segment_count_xyz(s32 *arg0, s16 xPos1, s16 yPos1, s16 zPos1, s16 xPos2, s16 yPos2, s16 zPos2);
LevelModelSegment *block_get(s32 segmentID);
LevelModelSegmentBoundingBox *block_boundbox(s32 segmentID);
void set_collision_mode(s32 mode);
s32 get_collision_normal(f32 *outX, f32 *outY, f32 *outZ);
s32 func_8002B9BC(Object *obj, f32 *arg1, Vec3f *arg2, s32 arg3);
void func_8002C71C(LevelModelSegment *segment);
LevelModel *get_current_level_model(void);
void get_fog_settings(s32 playerID, s16 *near, s16 *far, u8 *r, u8 *g, u8 *b);
void reset_fog(s32 playerID);
void update_fog(s32 viewportCount, s32 updateRate);
void apply_fog(s32 playerID);
void compute_scene_camera_transform_matrix(void);
void track_tex_anim(s32 updateRate);
s32 check_if_inside_segment(Object *obj, s32 segmentIndex);
s32 get_level_segment_index_from_position(f32 xPos, f32 yPos, f32 zPos);
void traverse_segments_bsp_tree(s32 nodeIndex, s32 segmentIndex, s32 segmentIndex2, u8 *segmentsOrder,
                                s32 *segmentsOrderIndex);
void render_level_geometry_and_objects(void);
void watereffect_render(Object *obj, WaterEffect *effect);
void shadow_render(Object *obj, ShadowData *shadow);
s32 block_visible(LevelModelSegmentBoundingBox *bb);
s32 check_if_in_draw_range(Object *obj);
void func_8002C954(LevelModelSegment *segment, LevelModelSegmentBoundingBox *bbox, s32 arg2);
void trackbg_render_gradient(void);
void shadow_update(s32 group, s32 waterGroup, s32 updateRate);
void obj_loop_fogchanger(Object *obj);
void initialise_player_viewport_vars(s32 updateRate);
s32 get_wave_properties(f32 yPos, f32 *waterHeight, Vec3f *rotation);
void render_level_segment(s32 segmentId, s32 nonOpaque);
void render_scene(Gfx **dList, Mtx **mtx, Vertex **vtx, Triangle **tris, s32 updateRate);
void set_fog(s32 fogIdx, s16 near, s16 far, u8 red, u8 green, u8 blue);
void slowly_change_fog(s32 fogIdx, s32 red, s32 green, s32 blue, s32 near, s32 far, s32 switchTimer);
s32 func_8002FD74(f32 x0, f32 z0, f32 x1, f32 x2, s32 count, Vec4f *arg5);
void func_80026C14(s16 arg0, s16 arg1, s32 arg2);
void func_80026E54(s16 arg0, s8 *arg1, f32 arg2, f32 arg3);
void func_80026070(LevelModelSegmentBoundingBox *arg0, f32 arg1, f32 arg2, f32 arg3);
void func_80026430(LevelModelSegment *segment, f32 arg1, f32 arg2, f32 arg3);
void free_track(void);
void void_check(u8 *segmentIds, s32 numberOfSegments, s32 viewportIndex);
s32 func_80027568(void);
s32 track_init_collision(LevelModelSegment *);
s32 get_level_segment_waves(s32, f32 xIn, f32 zIn,
                  WaterProperties ***);
void ttcam_update(s32);
void trackbg_render_flashy(void);
void initialise_player_viewport_vars(s32);
void func_8002A31C(void);
void update_colour_cycle(LevelHeader_70 *arg0, s32 updateRate);
void waves_update(s32);
void waves_render(Gfx **, Mtx **, s32);
void func_8002DE30(Object *);
void shadow_generate(Object *, s32);
void func_8002E904(LevelModelSegment *, s32, s32 arg2);
void func_8002EEEC(s32 arg0);
void func_8002F2AC(void);
void func_8002F440(void);
f32 func_8002FA64(void);
s32 collision_get_y(s32 levelSegmentIndex, f32 xIn, f32 zIn, f32 *yOut);
void init_track(u32 geometry, u32 skybox, s32 numberOfPlayers, Vehicle vehicle, u32 entranceId, u32 collectables,
                u32 arg6);
void waves_init(LevelModel *, LevelHeader *, s32);
void void_init(s32);
void generate_track(s32 modelId);
void func_800304C8(unk8011C8B8 arg0[3]);
s32 void_generate_primitive(f32 *arg0, f32 *arg1, f32 arg2, f32 arg3);
s32 func_8002FF6C(s32, unk8011C8B8 *, s32, Vec2f *);
s32 func_800BDC80(s32, unk8011C3B8 *, unk8011C8B8 *, f32, f32, f32, f32);
enum LogicUpdateRates {
    LOGIC_NULL,
    LOGIC_60FPS,
    LOGIC_30FPS,
    LOGIC_20FPS,
    LOGIC_15FPS,
    LOGIC_12FPS,
    LOGIC_10FPS,
    LOGIC_5FPS = 12
};
enum VideoModes {
    VIDEO_MODE_LOWRES_LAN,
    VIDEO_MODE_LOWRES_LPN,
    VIDEO_MODE_MEDRES_LPN,
    VIDEO_MODE_MEDRES_LAN,
    VIDEO_MODE_HIGHRES_HPN,
    VIDEO_MODE_HIGHRES_HAN,
    VIDEO_MODE_HIGHRES_HPF,
    VIDEO_MODE_HIGHRES_HAF,
    VIDEO_MODE_LOWRES_MASK = 0,
    VIDEO_MODE_MIDRES_MASK = 2,
    VIDEO_MODE_HIGHRES_MASK = 4
};
extern s32 gVideoRefreshRate;
extern f32 gVideoAspectRatio;
extern u16 *gVideoDepthBuffer;
extern u16 *gVideoCurrFramebuffer;
extern u16 *gVideoLastFramebuffer;
extern u16 *gVideoCurrDepthBuffer;
extern u16 *gVideoLastDepthBuffer;
extern OSViMode osViModeNtscLpn1, osViModePalLpn1, osViModeMpalLpn1, osViModePalLan1, osViModeNtscLan1, osViModeMpalLan1;
typedef struct VideoModeResolution {
               s32 width;
               s32 height;
} VideoModeResolution;
extern VideoModeResolution gVideoModeResolutions[8];
void video_init(s32 videoModeIndex, OSSched *sc);
void fb_mode_set(s32 videoModeIndex);
s32 fb_size(void);
void fb_init_vi(void);
void fb_alloc(s32 index);
void video_delta_reset(void);
void func_8007AB24(u8 arg0);
s32 vi_refresh_rate(void);
void fb_swap(void);
void fb_memcpy(u8 *src, u8 *dest, s32 len);
s32 fb_update(s32 mesg);
char gCourseInitials[4];
char gFLapInitials[4];
s32 gAdventureSaveGhost;
Gfx *sMenuCurrDisplayList;
s32 gPreviousMenuID;
Mtx *sMenuCurrHudMat;
char **gTTSaveGhostPakErrorText;
Vertex *sMenuCurrHudVerts;
Triangle *sMenuCurrHudTris;
unk801263C0 gMenuSelectedCharacter;
unk801263C0 D_801263B8;
s32 gOptionBlinkTimer;
unk801263C0 gMenuCurrentCharacter;
s32 gIgnorePlayerInputTime;
 s32 sUnused_801263C8;
CharacterSelectData (*gCurrCharacterSelectData)[10];
s32 gTrackmenuLoadedLevel;
s8 gActivePlayersArray[4];
s32 gOpacityDecayTimer;
s8 gCharselectStatus[4];
s32 gMenuStage;
 s32 D_801263E4;
s8 gPlayersCharacterArray[8];
s8 gCharacterIdSlots[8];
s32 gRankingsPoints[8];
u8 gResultsPlayers[8];
u8 gRankingsPlayers[8];
u8 gResultsPlayerIDs[8];
u8 gRankingsPlayerIDs[8];
s8 gRankingsPortraitIDs[16];
u64 sEepromSettings;
f32 sBootScreenTimer;
s8 gControllersXAxisDelay[4];
s8 gControllersYAxisDelay[4];
s8 gControllersXAxisDirection[4];
MenuElement *gGameSelectElements;
s8 gControllersYAxisDirection[4];
s8 gControllersXAxis[4];
s8 gControllersYAxis[4];
s32 sUnused_80126470;
s32 gTrackSelectViewPortHalfX;
s32 gTrackSelectViewPortHalfY;
s32 gTrackSelectViewPortX;
s32 gTrackSelectViewportY;
s32 gFileCopy;
s32 gFileErase;
s32 gSaveFileIndex3;
s32 gSaveFileIndex2;
s32 gFileConfirm;
s32 gGhostMenuOption;
s32 D_8012649C;
SavefileInfo gSavefileInfo[4];
s32 gCpakGhostData;
s32 gGhostMenuTotal;
s8 gDialogueSubmenu;
u8 gGhostLevelIDsPak[6];
s8 sCurrentMenuID;
u8 gGhostCharacterIDsPak[6];
u8 gGhostVehicleIDsPak[6];
u16 gGhostChecksumIDsPak[6];
s8 sDialogueOptionMax;
u8 gGhostLevelIDsMenu[6];
s8 gDialogueOptionYOffset;
u8 gGhostCharacterIDsMenu[6];
s8 gDialogueItemSelection;
u8 gGhostVehicleIDsMenu[6];
u16 gGhostChecksumIDsMenu[6];
Settings *gSavefileData[4];
u8 gGhostWorldIDs[8];
s32 gMultiplayerSelectedNumberOfRacersCopy;
void *gMenuAssets[128];
u8 gMenuAssetActive[128];
s32 gTrackmenuType;
 s32 D_801267D4;
s32 gMenuButtons[5];
s8 *gCinematicParams;
s32 buttonsPressed[5];
s8 *gCinematicPortraits;
SoundHandle gMenuSoundMasks[4];
s16 gMenuStickX[5];
s32 gCinematicEnd;
 s8 sUnused_80126828;
 s32 D_8012682C;
s16 gMenuStickY[5];
s16 D_8012683A;
s32 gCinematicSkipA;
SoundHandle gTrackTTSoundMask;
s32 gCinematicSkipB;
SoundHandle D_80126848;
s32 gCinematicMusicChangeOff;
s32 *D_80126850;
s32 gMenuElementScaleTimer;
s32 gPostraceScaleIn;
s32 gPostraceScaleMiddle;
s32 gPostraceScaleOut;
s32 gTitleDemoIndex;
s16 gTitleDemoTimer;
s32 gTitleRevealTimer;
f32 gTitleAudioCounter;
s8 *sTitleScreenDemoIds;
unk80126878 D_80126878[8];
f32 D_801268D8;
 s32 D_801268DC;
s32 gOpeningNameID;
 s32 D_801268E4;
s16 gTrackSelectIDs[4][6];
s16 gFFLUnlocked;
 s32 D_8012691C;
 s32 D_80126920;
s32 gTrackSelectVertsFlip;
 s32 D_80126928;
 s32 D_8012692C;
TrackRenderDetails gTrackSelectRenderDetails[9];
s8 gPlayerSelectVehicle[4];
s8 gPlayerSelectConfirm[4];
s32 gTrackSelectCursorX;
s32 gTrackSelectCursorY;
char *gAudioOutputStrings[3];
f32 gTrackSelectX;
char *gMusicTestString;
f32 gTrackSelectY;
f32 gTrackSelectTargetX;
f32 gTrackSelectTargetY;
char *gTrackMenuHubName;
s32 gSelectedTrackX;
s32 gSelectedTrackY;
SoundHandle gSoundOptionMask;
s32 gSaveMenuOptionCountLower;
SaveFileData *gSaveMenuFilesDest;
s32 gSaveMenuOptionCountUpper;
SaveFileData *gSaveMenuFilesSource;
s32 gSaveMenuRumbleNag;
s32 gSaveMenuRumbleConnected;
s32 gSaveMenuSourceState;
s32 gSaveMenuDestState;
s32 sControllerPakNotesFree[4];
u8 sControllerPakIssueNotFound[4];
u8 sControllerPakFatalErrorFound[4];
u8 sControllerPakNoFreeSpace[4];
u8 sControllerPakBadData[4];
char *gMenuOptionText[8];
u8 sControllerPakDataPresent[4];
char *D_80126A64;
s32 gMenuOption;
s32 gSaveMenuRumbleNagSet;
char **gDeviceStatusStrings;
s32 gSaveMenuMessageLines;
s32 gSaveMenuMessageOption;
 s32 D_80126A7C;
unk80126A80 *gSaveMenuText[4];
s32 gPostRace1Player;
s32 gPostRaceTimer;
s32 gTracksSaveGhost;
 s32 D_80126A9C;
char *gBootPakData[16];
char *sCurrentControllerPakAllFileNames[16];
char *sCurrentControllerPakAllFileExtensions[16];
u8 sCurrentControllerPakAllFileTypes[16];
u32 sCurrentControllerPakNumberOfPages[16];
u32 sCurrentControllerPakFreePages;
s32 sControllerPakMenuNumberOfRows;
TextureHeader *gMenuMosaic1;
TextureHeader *gMenuMosaic2;
s32 gMenuMosaicShift;
s32 gCreditsControlDataIndex;
PakError sControllerPakError;
s32 D_80126BCC;
 s32 D_80126BD0;
s32 gSaveMenuOptionSource;
s32 D_80126BD8;
f32 gSaveMenuScrollSource;
s32 D_80126BE0;
s32 gSaveMenuOptionDest;
s32 D_80126BE8;
f32 gSaveMenuScrollDest;
char *gResultOptionText[8];
s32 gCpakWriteTimer;
s32 gResultOptionCount;
s32 gBootMenuTimer;
char **gPostRaceMessage;
s32 gBootMenuPhase;
s32 gPostRaceLineCount;
s8 gPostraceFinishState;
unk80080BC8 *gMenuGeometry;
u16 (*gCheatsAssetData)[30];
s32 gNameEntryStickHeld;
s32 gNumberOfCheats;
s32 gNameEntryStickX;
s16 gCheatInputCurrentRow;
s16 gCheatInputCurrentColumn;
s16 gCheatInputStringLength;
s16 gOptionsMenuItemIndex;
s32 gNameSelectionDone;
s16 gNewCheatID;
f32 gNameEntryOffsetX;
unk80126C54 gPostRaceOld;
char gCheatInput[20];
s32 *gNameEntryTargetX;
unk80126C54 gPostRace;
s32 gNumOnscreenMagicCodes;
char *gNameEntryString;
s32 gNameEntryAllowedLength;
s16 gUnlockedCheatIDs[32];
s32 gFileNew;
s8 gInAdvModeTrophyRace = 0;
f32 gTrackSelectWoodFrameHeightScale = 1.0f;
s32 gResetTitleScale = 1;
s32 gTitleScreenCurrentOption = 0;
s32 gMenuCurIndex = 0;
s32 unused_800DF464 = 4;
 s32 gMenuDisableObjAnim = 0;
s32 gMissingControllerDelay = 0;
s32 gCurrentMenuId = 0;
s32 unused_800DF474 = 0;
s32 gTrackSpecifiedWithTrackIdToLoad = 0;
s32 gMenuDelay = 0;
s32 gNumberOfReadyPlayers = 0;
s32 D_800DF484 = 0;
s32 gTitleScreenLoaded = 0;
 s32 unused_800DF48C = 0;
 s32 unused_800DF490 = 0;
s32 gIsInAdventureTwo = 0;
s32 gPlayerHasSeenCautionMenu = 0;
s32 *gMenuTextLangTable = 0;
char **gMenuText = 0;
u8 sMenuGuiColourR = 0xFF;
u8 sMenuGuiColourG = 0xFF;
u8 sMenuGuiColourB = 0xFF;
u8 sMenuGuiColourBlendFactor = 0;
s32 gMenuSpriteFlags = 0;
s32 gIsInTracksMode = 1;
s32 gNumberOfActivePlayers = 1;
s32 gIsInTwoPlayerAdventure = 0;
s32 gTrackIdForPreview = ASSET_LEVEL_CENTRALAREAHUB;
s32 gTrackSelectRow = 0;
s32 gSaveFileIndex = 0;
s32 unused_800DF4D0 = 0;
s32 gTrackIdToLoad = 0;
s8 unused_800DF4D8 = 1;
s8 gNextTajChallengeMenu = 0;
s8 gNeedToCloseDialogueBox = 0;
s8 gDoneTalkingToNPC[5] = {
    0,
    0,
    0,
    0,
    0
};
s8 gDialogueOptionTangible = 0;
s32 unused_800DF4F0[] = { 0x4000, 0x8000, 0x1000, 0x2000, 0x8000, 0x10, 0x400, 0x00 };
MenuAsset sMenuImageProperties[18] = {
    { { { { { 0, 0, 0 } } }, { 0x00 }, 1.0f, { { { { 0.0f, 0.0f, -32.0f } } } } }, 0, 0, 0, 0, 0, 0, 0 },
    { { { { { 0, 0, 0 } } }, { 0x01 }, 1.0f, { { { { 0.0f, 0.0f, -32.0f } } } } }, 0, 0, 0, 0, 0, 0, 0 },
    { { { { { 0, 0, 0 } } }, { 0x02 }, 1.0f, { { { { 0.0f, 0.0f, -32.0f } } } } }, 0, 0, 0, 0, 0, 0, 0 },
    { { { { { 0, 0, 0 } } }, { 0x03 }, 1.0f, { { { { 0.0f, 0.0f, -32.0f } } } } }, 0, 0, 0, 0, 0, 0, 0 },
    { { { { { 0, 0, 0 } } }, { 0x05 }, 0.215f, { { { { 0.0f, 0.0f, -500.0f } } } } }, 0, 0, 0, 0, 0, 0, 0 },
    { { { { { 0, 0, 0 } } }, { 0x06 }, 0.215f, { { { { 0.0f, 0.0f, -500.0f } } } } }, 0, 0, 0, 0, 0, 0, 0 },
    { { { { { 0, 0, 0 } } }, { 0x07 }, 0.215f, { { { { 0.0f, 0.0f, -500.0f } } } } }, 0, 0, 0, 0, 0, 0, 0 },
    { { { { { 0, 0, 0 } } }, { 0x04 }, 0.125f, { { { { 0.0f, -40.0f, -500.0f } } } } }, 0, 0, 0, 0, 0, 0, 0 },
    { { { { { 0, 0, 0 } } }, { 0x66 }, 0.75f, { { { { 0.0f, 0.0f, 0.0f } } } } }, 0, 0, 0, 0, 0, 0, 0 },
    { { { { { 0, 0, 0 } } }, { 0x67 }, 0.75f, { { { { 0.0f, 0.0f, 0.0f } } } } }, 0, 0, 0, 0, 0, 0, 0 },
    { { { { { 0, 0, 0 } } }, { 0x42 }, 1.0f, { { { { 0.0f, 0.0f, 0.0f } } } } }, 0, 0, 0, 0, 0, 0, 0 },
    { { { { { 0, 0, 0 } } }, { 0x40 }, 1.0f, { { { { 0.0f, 0.0f, 0.0f } } } } }, 0, 0, 0, 0, 0, 0, 0 },
    { { { { { 0, 0, 0 } } }, { 0x41 }, 1.0f, { { { { 0.0f, 0.0f, 0.0f } } } } }, 0, 0, 0, 0, 0, 0, 0 },
    { { { { { 0, 0, 0 } } }, { 0x4C }, 1.0f, { { { { 0.0f, 0.0f, 0.0f } } } } }, 0, 0, 0, 0, 0, 0, 0 },
    { { { { { 0, 0, 0 } } }, { 0x4D }, 1.0f, { { { { 0.0f, 0.0f, 0.0f } } } } }, 0, 0, 0, 0, 0, 0, 0 },
    { { { { { 0, 0, 0 } } }, { 0x4E }, 1.0f, { { { { 0.0f, 0.0f, 0.0f } } } } }, 0, 0, 0, 0, 0, 0, 0 },
    { { { { { 0, 0, 0 } } }, { 0x4F }, 1.0f, { { { { 0.0f, 0.0f, 0.0f } } } } }, 0, 0, 0, 0, 0, 0, 0 },
    { { { { { 0, 0, 0 } } }, { 0x68 }, 1.0f, { { { { 0.0f, 0.0f, 0.0f } } } } }, 0, 0, 0, 0, 0, 0, 0 },
};
s16 *gAssetsMenuElementIds[1] = { 0 };
s16 gMenuElementIdCount = 0;
s16 gMenuObjectsCount = 0;
MenuAsset *gMenuImages = 0;
s32 sMenuMusicVolume = 0x7F;
s32 sMenuGuiOpacity = 0xFF;
s32 unused_800DF768 = 1;
FadeTransition sMenuTransitionFadeInFast =
    { (0 & 0x3F) | (0 & 0xC0), 0, 0, 0, 10, 0xFFFF };
FadeTransition sMenuTransitionFadeIn =
    { (0 & 0x3F) | (0 & 0xC0), 0, 0, 0, 18, 0xFFFF };
FadeTransition sMenuTransitionFadeOut = { (0 & 0x3F) | ((1 << 7) & 0xC0), 0, 0, 0, 18, 0 };
 FadeTransition sMenuTransitionFadeInWhite =
    { (0 & 0x3F) | (0 & 0xC0), 255, 255, 255, 18, 0xFFFF };
 FadeTransition sMenuTransitionFadeOutWhite =
    { (0 & 0x3F) | ((1 << 7) & 0xC0), 255, 255, 255, 18, 0 };
s32 gPostraceState = POSTRACE_SLIDE_END;
MenuElement *gTrophyRankingsMenuElements = 0;
s32 gPostraceTextOffset = 0;
s32 gPostraceTimestampOffset = 0;
char *gTitleMenuStrings[3] = { 0, 0, 0 };
char gVersionDisplayText[20] = "VERSION XXXXXXXX";
s16 sGameTitleTileTextures[12] = { TEXTURE_TITLE_SEGMENT_01, TEXTURE_TITLE_SEGMENT_02, TEXTURE_TITLE_SEGMENT_03,
                                   TEXTURE_TITLE_SEGMENT_04, TEXTURE_TITLE_SEGMENT_05, TEXTURE_TITLE_SEGMENT_06,
                                   TEXTURE_TITLE_SEGMENT_07, TEXTURE_TITLE_SEGMENT_08, TEXTURE_TITLE_SEGMENT_09,
                                   TEXTURE_TITLE_SEGMENT_10, TEXTURE_TITLE_SEGMENT_11, -1 };
DrawTexture sGameTitleTileOffsets[12] = { { 0, -75, -32 }, { 0, -60, -32 }, { 0, -45, -32 },
                                          { 0, -30, -32 }, { 0, -15, -32 }, { 0, 0, -32 },
                                          { 0, 15, -32 }, { 0, 30, -32 }, { 0, 45, -32 },
                                          { 0, 60, -32 }, { 0, 75, -32 }, { 0, 0, 0 } };
unk800DF83C gTitleCinematicText[10] = {
    { "TIMBER", 14.0f, 14.5f, 16.5f, 17.0f, -80.0f, ((float)(240)) - 32.0f, ((float)320 / 2),
      ((float)(240)) - 32.0f, ((float)(320)) + 80.0f, ((float)(240)) - 32.0f },
    { "BUMPER", 19.0f, 19.5f, 21.5f, 22.0f, -80.0f, ((float)(240)) - 32.0f, ((float)320 / 2),
      ((float)(240)) - 32.0f, ((float)(320)) + 80.0f, ((float)(240)) - 32.0f },
    { "CONKER", 24.0f, 24.5f, 26.5f, 27.0f, -80.0f, ((float)(240)) - 32.0f, ((float)320 / 2),
      ((float)(240)) - 32.0f, ((float)(320)) + 80.0f, ((float)(240)) - 32.0f },
    { "TIPTUP", 29.0f, 29.5f, 31.5f, 32.0f, -80.0f, ((float)(240)) - 32.0f, ((float)320 / 2),
      ((float)(240)) - 32.0f, ((float)(320)) + 80.0f, ((float)(240)) - 32.0f },
    { "DRUMSTICK", 35.0f, 35.5f, 37.5f, 38.0f, -80.0f, ((float)(240)) - 32.0f, ((float)320 / 2),
      ((float)(240)) - 32.0f, ((float)(320)) + 80.0f, ((float)(240)) - 32.0f },
    { "PIPSY", 40.0f, 40.5f, 42.5f, 43.0f, -80.0f, ((float)(240)) - 32.0f, ((float)320 / 2),
      ((float)(240)) - 32.0f, ((float)(320)) + 80.0f, ((float)(240)) - 32.0f },
    { "BANJO", 45.0f, 45.5f, 47.5f, 48.0f, -80.0f, ((float)(240)) - 32.0f, ((float)320 / 2),
      ((float)(240)) - 32.0f, ((float)(320)) + 80.0f, ((float)(240)) - 32.0f },
    { "KRUNCH", 50.0f, 50.5f, 52.5f, 53.0f, -80.0f, ((float)(240)) - 32.0f, ((float)320 / 2),
      ((float)(240)) - 32.0f, ((float)(320)) + 80.0f, ((float)(240)) - 32.0f },
    { "WIZPIG", 57.5f, 58.0f, 60.0f, 60.5f, -80.0f, ((float)(240)) - 32.0f, ((float)320 / 2),
      ((float)(240)) - 32.0f, ((float)(320)) + 80.0f, ((float)(240)) - 32.0f },
    { "DIDDY", 63.5f, 64.0f, 66.0f, 66.5f, -80.0f, ((float)(240)) - 32.0f, ((float)320 / 2),
      ((float)(240)) - 32.0f, ((float)(320)) + 80.0f, ((float)(240)) - 32.0f }
};
s32 gTitleCinematicTextColourCount = 0;
u8 gTitleCinematicTextColours[] = {
    255, 255, 0, 255, 204,
    0, 255, 0, 255, 153,
    0, 255, 255, 255, 102,
    0, 0, 255, 255, 51
};
 u8 unused_800DFA0C[] = { 0, 0, 15, 120 };
char *gOptionMenuStrings[] = { 0, 0, 0, 0, 0, 0, 0 };
s16 gOptionMenuTextures[] = { 0x3D, 0x3C, 0x3F, 0x3E, 0x44, -1 };
s16 gOptionMenuImageIndices[] = { -1 };
unk800DFA3C gAudioMenuStrings[] = {
    { 160, 80, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0 },
    { 160, 104, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0 },
    { 160, 144, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0 },
    { 160, 192, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0 },
    { 161, 35, 0, 0, 0, 255, 128, ASSET_FONTS_BIGFONT, 12, 0 },
    { 160, 32, 255, 128, 255, 0, 255, ASSET_FONTS_BIGFONT, 12, 0 },
    { 160, 188, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};
s32 gMusicTestSongIndex = 0;
s32 gSfxVolumeSliderValue = 256;
s32 gMusicVolumeSliderValue = 256;
StereoPanMode gAudioOutputType = STEREO;
u32 gContPakSaveBgColours[4] = {
    ((u32)((64 << 24) | (64 << 16) | (255 << 8) | 255)),
    ((u32)((255 << 24) | (64 << 16) | (64 << 8) | 255)),
    ((u32)((255 << 24) | (208 << 16) | (64 << 8) | 255)),
    ((u32)((64 << 24) | (255 << 16) | (64 << 8) | 255))
};
SIDeviceStatus gDeviceStatus = CONTROLLER_PAK_GOOD;
s32 gControllerIndex = 0;
char *gContPakNotPresentStrings[6] = { 0, 0, 0, 0, 0, 0 };
char *gContPakCorruptDataRepairStrings[6] = { 0, 0, 0, 0, 0, 0 };
char *gContPakDamagedStrings[6] = { 0, 0, 0, 0, 0, 0 };
char *gContPakFullStrings[5] = { 0, 0, 0, 0, 0 };
char *gContPakDiffContStrings[7] = { 0, 0, 0, 0, 0, 0, 0 };
char *gContPakNoRoomForGhostsStrings[6] = { 0, 0, 0, 0, 0, 0 };
char *gContPakCorruptDataStrings[6] = { 0, 0, 0, 0, 0, 0 };
char *gContPakRumbleDetectedStrings[6] = { 0, 0, 0, 0, 0, 0 };
char *gContPakSwitchToRumbleStrings[6] = { 0, 0, 0, 0, 0, 0 };
char *gContPakNeed2ndAdvStrings[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
char **gContPakStrings[11] = { 0,
                               gContPakNotPresentStrings,
                               gContPakCorruptDataRepairStrings,
                               gContPakDamagedStrings,
                               gContPakFullStrings,
                               gContPakDiffContStrings,
                               gContPakNoRoomForGhostsStrings,
                               gContPakRumbleDetectedStrings,
                               gContPakSwitchToRumbleStrings,
                               gContPakCorruptDataStrings,
                               gContPakNeed2ndAdvStrings };
 DrawTexture unused_800DFC08[] = { { 0, 0, -1 } };
DrawTexture gDrawTexN64Icon[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gDrawTexTTIcon[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gDrawTexGhostIcon[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gDrawTexFileIcon[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gDrawTexContPakIcon[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gDrawTexTrashIcon[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
 s8 unused_800DFC70[] = { 0x40, 0x40, 0x04, 0x04, -1 };
s16 gSaveMenuObjectIndices[] = { 0x0024, 0x0025, 0x0018, 0x0019, 0x001A, 0x001B, 0x001C, 0x001D, 0x003D,
                                 0x003F, 0x003E, 0x003C, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047, 0x0048,
                                 0x0049, 0x004A, 0x004B, 0x0040, 0x0041, 0x0002, -1 };
s16 gSaveMenuImageIndices[] = { 0x000B, 0x000C, 0x0002, -1 };
MenuElement gControllerPakMenuElement[7] = {
    { 161, 32, 161, 33, 161, 32, 0, 0, 0, 255, 128, ASSET_FONTS_BIGFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { 160, 30, 160, 30, 160, 30, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { 160, 112, 160, 112, 160, 112, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { 160, 128, 160, 128, 160, 128, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { 160, 192, 160, 192, 160, 192, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { 160, 208, 160, 208, 160, 208, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ASSET_FONTS_FUNFONT, 0, 0, { 0 }, { { 0, 0, 0, 0 } } },
};
s32 gShowControllerPakMenu = 0;
s32 gActiveMagicCodes = 0;
s32 gUnlockedMagicCodes = 0;
char *gMagicCodeMenuStrings[5] = { 0, 0, 0, 0, 0 };
u8 gCharacterVolumes[10][2] = {
    { 0x0F, 0x64 }, { 0x0C, 0x07 }, { 0x09, 0x64 }, { 0x0A, 0x64 }, { 0x08, 0x64 },
    { 0x0B, 0x64 }, { 0x0D, 0x64 }, { 0x0E, 0x64 }, { 0x05, 0x64 }, { 0x04, 0x64 },
};
s16 gCharSelectObjectIndices[2] = { -1, 0 };
s16 gCharSelectImageIndices[2] = { -1, 0 };
CharacterSelectData gCharacterSelectBytesDefault[] = {
               { { 0xFF, 0xFF }, { 4, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF }, { 1, 2, 3, 0xFF }, 0x0000 },
              { { 0xFF, 0xFF }, { 5, 0xFF }, { 0, 0xFF, 0xFF, 0xFF }, { 2, 3, 0xFF, 0xFF }, 0x0009 },
               { { 0xFF, 0xFF }, { 6, 0xFF }, { 1, 0, 0xFF, 0xFF }, { 3, 0xFF, 0xFF, 0xFF }, 0x0001 },
              { { 0xFF, 0xFF }, { 7, 0xFF }, { 2, 1, 0, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF }, 0x0005 },
    { { 0, 0xFF }, { 0xFF, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF }, { 5, 6, 7, 0xFF }, 0x0003 },
               { { 1, 0xFF }, { 0xFF, 0xFF }, { 4, 0xFF, 0xFF, 0xFF }, { 6, 7, 0xFF, 0xFF }, 0x0002 },
    { { 2, 0xFF }, { 0xFF, 0xFF }, { 5, 4, 0xFF, 0xFF }, { 7, 0xFF, 0xFF, 0xFF }, 0x0007 },
               { { 3, 0xFF }, { 0xFF, 0xFF }, { 6, 5, 4, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF }, 0x0004 }
};
CharacterSelectData gCharacterSelectBytesDrumStick[] = {
               {
        { 0xFF, 0xFF }, { 4, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF }, { 1, 8, 2, 3 }, 0x0000 },
    { { 0xFF, 0xFF }, { 4, 5 }, { 0, 0xFF, 0xFF, 0xFF }, { 8, 2, 3, 0xFF }, 0x0009 },
    { { 0xFF, 0xFF }, { 6, 7 }, { 8, 1, 0, 0xFF }, { 3, 0xFF, 0xFF, 0xFF }, 0x0001 },
    { { 0xFF, 0xFF }, { 7, 0xFF }, { 2, 8, 1, 0 }, { 0xFF, 0xFF, 0xFF, 0xFF }, 0x0005 },
    { { 0, 1 }, { 0xFF, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF }, { 5, 6, 7, 0xFF }, 0x0003 },
    { { 1, 8 }, { 0xFF, 0xFF }, { 4, 0xFF, 0xFF, 0xFF }, { 6, 7, 0xFF, 0xFF }, 0x0002 },
    { { 8, 2 }, { 0xFF, 0xFF }, { 5, 4, 0xFF, 0xFF }, { 7, 0xFF, 0xFF, 0xFF }, 0x0007 },
    { { 2, 3 }, { 0xFF, 0xFF }, { 6, 5, 4, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF }, 0x0004 },
    { { 0xFF, 0xFF }, { 5, 6 }, { 1, 0, 0xFF, 0xFF }, { 2, 3, 0xFF, 0xFF }, 0x0006 }
};
CharacterSelectData gCharacterSelectBytesTT[] = {
               { { 0xFF, 0xFF }, { 4, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF }, { 1, 2, 3, 0xFF }, 0x0000 },
    { { 0xFF, 0xFF }, { 5, 8 }, { 0, 0xFF, 0xFF, 0xFF }, { 2, 3, 0xFF, 0xFF }, 0x0009 },
    { { 0xFF, 0xFF }, { 8, 6 }, { 1, 0, 0xFF, 0xFF }, { 3, 0xFF, 0xFF, 0xFF }, 0x0001 },
    { { 0xFF, 0xFF }, { 6, 7 }, { 2, 1, 0, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF }, 0x0005 },
    { { 0, 0xFF }, { 0xFF, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF }, { 5, 8, 6, 7 }, 0x0003 },
    { { 0, 1 }, { 0xFF, 0xFF }, { 4, 0xFF, 0xFF, 0xFF }, { 8, 6, 7, 0xFF }, 0x0002 },
    { { 2, 3 }, { 0xFF, 0xFF }, { 8, 5, 4, 0xFF }, { 7, 0xFF, 0xFF, 0xFF }, 0x0007 },
    { { 3, 0xFF }, { 0xFF, 0xFF }, { 6, 8, 5, 4 }, { 0xFF, 0xFF, 0xFF, 0xFF }, 0x0004 },
            { { 1, 2 }, { 0xFF, 0xFF }, { 5, 4, 0xFF, 0xFF }, { 6, 7, 0xFF, 0xFF }, 0x0008 }
};
CharacterSelectData gCharacterSelectBytesComplete[] = {
               {
        { 0xFF, 0xFF }, { 4, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF }, { 1, 8, 2, 3 }, 0x0000 },
    { { 0xFF, 0xFF }, { 5, 0xFF }, { 0, 0xFF, 0xFF, 0xFF }, { 8, 2, 3, 0xFF }, 0x0009 },
    { { 0xFF, 0xFF }, { 6, 0xFF }, { 8, 1, 0, 0xFF }, { 3, 0xFF, 0xFF, 0xFF }, 0x0001 },
    { { 0xFF, 0xFF }, { 7, 0xFF }, { 2, 8, 1, 0 }, { 0xFF, 0xFF, 0xFF, 0xFF }, 0x0005 },
    { { 0, 0xFF }, { 0xFF, 0xFF }, { 0xFF, 0xFF, 0xFF, 0xFF }, { 5, 9, 6, 7 }, 0x0003 },
    { { 1, 0xFF }, { 0xFF, 0xFF }, { 4, 0xFF, 0xFF, 0xFF }, { 9, 6, 7, 0xFF }, 0x0002 },
    { { 2, 0xFF }, { 0xFF, 0xFF }, { 9, 5, 4, 0xFF }, { 7, 0xFF, 0xFF, 0xFF }, 0x0007 },
    { { 3, 0xFF }, { 0xFF, 0xFF }, { 6, 9, 5, 4 }, { 0xFF, 0xFF, 0xFF, 0xFF }, 0x0004 },
    { { 0xFF, 0xFF }, { 9, 0xFF }, { 1, 0, 0xFF, 0xFF }, { 2, 3, 0xFF, 0xFF }, 0x0006 },
    { { 8, 0xFF }, { 5, 0xFF }, { 5, 4, 0xFF, 0xFF }, { 6, 7, 0xFF, 0xFF }, 0x0008 }
};
 s32 unused_800DFFCC = 0;
s32 gEnteredCharSelectFrom = 0;
 s32 unused_800DFFD4 = -1;
MenuElement gCautionMenuTextElements[14] = {
    { (320 / 2) + 1, 35, (320 / 2) + 1, 35, (320 / 2) + 1, 35, 0, 0, 0, 255, 128, ASSET_FONTS_BIGFONT, 12,0, { 0 }, { { 0, 0, 0, 0 } } },
    { (320 / 2), 32, (320 / 2), 32, (320 / 2), 32, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { (320 / 2), 72, (320 / 2), 68, (320 / 2), 72, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { (320 / 2), 86, (320 / 2), 82, (320 / 2), 86, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { (320 / 2), 100, (320 / 2), 96, (320 / 2), 100, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { (320 / 2), 114, (320 / 2), 110, (320 / 2), 114, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { (320 / 2), 128, (320 / 2), 124, (320 / 2), 128, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { (320 / 2), 142, (320 / 2), 138, (320 / 2), 142, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { (320 / 2), 156, (320 / 2), 152, (320 / 2), 156, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { (320 / 2), 156, (320 / 2), 166, (320 / 2), 156, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { (320 / 2), 186, (320 / 2), 180, (320 / 2), 186, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { (320 / 2), 200, (320 / 2), 194, (320 / 2), 200, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { (320 / 2), 200, (320 / 2), 208, (320 / 2), 200, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    {0},
};
MenuElement gGameSelectTextElemsNoAdv2[7] = {
    { (320 / 2) + 1, 35, (320 / 2) + 1, 35, (320 / 2) + 1, 35, 0, 0, 0, 255, 128, ASSET_FONTS_BIGFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { (320 / 2), 32, (320 / 2), 32, (320 / 2), 32, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { -96, 39, -96, 39, -96, 39, 176, 224, 192, 255, 255, ASSET_FONTS_FUNFONT, 0, 7, { 0 }, { { 192, 44, 4, 4 } } },
    { (320 / 2), 104, (320 / 2), 104, (320 / 2), 104, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { -96, -9, -96, -9, -96, -9, 176, 224, 192, 255, 255, ASSET_FONTS_FUNFONT, 0, 7, { 0 }, { { 192, 44, 4, 4 } } },
    { (320 / 2), 152, (320 / 2), 152, (320 / 2), 152, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    {0},
};
MenuElement gGameSelectTextElemsWithAdv2[9] = {
    { (320 / 2) + 1, 35, (320 / 2) + 1, 35, (320 / 2) + 1, 35, 0, 0, 0, 255, 128, ASSET_FONTS_BIGFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { (320 / 2), 32, (320 / 2), 32, (320 / 2), 32, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { -112, 55, -112, 55, -112, 55, 176, 224, 192, 255, 255, ASSET_FONTS_FUNFONT, 0, 7, { 0 }, { { 224, 44, 4, 4 } } },
    { (320 / 2), 88, (320 / 2), 88, (320 / 2), 88, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { -112, 7, -112, 7, -112, 7, 176, 224, 192, 255, 255, ASSET_FONTS_FUNFONT, 0, 7, { 0 }, { { 224, 44, 4, 4 } } },
    { (320 / 2), 136, (320 / 2), 136, (320 / 2), 136, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { -112, -41, -112, -41, -112, -41, 176, 224, 192, 255, 255, ASSET_FONTS_FUNFONT, 0, 7, { 0 }, { { 224, 44, 4, 4 } } },
    { (320 / 2), 184, (320 / 2), 184, (320 / 2), 184, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    {0},
};
s16 gFileSelectObjectIndices[6] = { 0x00, 0x43, 0x40, 0x41, 0x42, -1 };
s16 gFileSelectImageIndices[6] = { 0x00, 0x0B, 0x0C, 0x0A, -1, 0 };
char *gFilenames[3] = { 0, 0, 0 };
u16 unused_800E03BC[8] = {
    0x004C, 0x0070, 0x00F4, 0x0070, 0x004C, 0x00D0, 0x00F4, 0x00D0,
};
ButtonElement gFileSelectButtons[3] = {
    { 24, 81, 88, 64, 4, 4, ((((64)<<8) & 0xf800) | (((16)<<3) & 0x7c0) | (((0)>>2) & 0x3e) | ((0) & 0x1)), ((((255)<<8) & 0xf800) | (((255)<<3) & 0x7c0) | (((0)>>2) & 0x3e) | ((0) & 0x1)) },
    { 116, 81, 88, 64, 4, 4, ((((64)<<8) & 0xf800) | (((16)<<3) & 0x7c0) | (((0)>>2) & 0x3e) | ((0) & 0x1)), ((((255)<<8) & 0xf800) | (((255)<<3) & 0x7c0) | (((0)>>2) & 0x3e) | ((0) & 0x1)) },
    { 208, 81, 88, 64, 4, 4, ((((64)<<8) & 0xf800) | (((16)<<3) & 0x7c0) | (((0)>>2) & 0x3e) | ((0) & 0x1)), ((((255)<<8) & 0xf800) | (((255)<<3) & 0x7c0) | (((0)>>2) & 0x3e) | ((0) & 0x1)) },
};
s16 gFileSelectElementPos[10] = {
    44, 54,
    21, 25,
    44, 27,
    63, 25,
    45, 25
};
s32 gMultiplayerSelectedNumberOfRacers = 0;
s32 gTracksMenuTimeTrialHighlightIndex = 0;
s32 gTracksMenuAdventureHighlightIndex = 0;
DrawTexture gMenuSelectionArrowUp[2] = { { 0, -12, -8 }, { 0, 0, 0 } };
DrawTexture gMenuSelectionArrowLeft[2] = { { 0, -8, -12 }, { 0, 0, 0 } };
DrawTexture gMenuSelectionArrowDown[2] = { { 0, -12, -8 }, { 0, 0, 0 } };
DrawTexture gMenuSelectionArrowRight[2] = { { 0, -8, -12 }, { 0, 0, 0 } };
DrawTexture gRaceSelectionCarTex[3] = { { 0, 0, 0 }, { 0, 0, 32 }, { 0, 0, 0 } };
DrawTexture gRaceSelectionHoverTex[3] = { { 0, 0, 0 }, { 0, 0, 32 }, { 0, 0, 0 } };
DrawTexture gRaceSelectionPlaneTex[3] = { { 0, 0, 0 }, { 0, 0, 32 }, { 0, 0, 0 } };
DrawTexture gRaceSelectionTTOn[3] = { { 0, 0, 0 }, { 0, 0, 32 }, { 0, 0, 0 } };
DrawTexture gRaceSelectionTTOff[3] = { { 0, 0, 0 }, { 0, 0, 32 }, { 0, 0, 0 } };
DrawTexture gRaceSelectionCarOptHighlight[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gRaceSelectionCarOpt[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gRaceSelectionHoverOptHighlight[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gRaceSelectionHoverOpt[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gRaceSelectionPlaneOptHighlight[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gRaceSelectionPlaneOpt[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gRaceSelectionTTOnOptHighlight[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gRaceSelectionTTOffOptHighlight[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gRaceSelectionTTOnOpt[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gRaceSelectionTTOffOpt[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gRaceSelectionPlayer1Texture[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gRaceSelectionPlayer2Texture[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gRaceSelectionPlayer3Texture[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gRaceSelectionPlayer4Texture[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gRaceSelectionVehicleTitleTexture[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gRaceSelectionTTTitleTexture[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture D_800E05D4[4] = { { 0, 0, -48 }, { 0, 0, -16 }, { 0, 0, 16 }, { 0, 0, 0 } };
DrawTexture D_800E05F4[4] = { { 0, 0, -48 }, { 0, 0, -16 }, { 0, 0, 16 }, { 0, 0, 0 } };
DrawTexture gRaceSelectionTTTexture[2] = { { 0, -16, -16 }, { 0, 0, 0 } };
DrawTexture *gRaceSelectionImages[9] = {
    gRaceSelectionCarTex, gRaceSelectionCarOptHighlight, gRaceSelectionCarOpt,
    gRaceSelectionHoverTex, gRaceSelectionHoverOptHighlight, gRaceSelectionHoverOpt,
    gRaceSelectionPlaneTex, gRaceSelectionPlaneOptHighlight, gRaceSelectionPlaneOpt
};
DrawTexture *gTrackSelectTTImage[6] = { gRaceSelectionTTOff, gRaceSelectionTTOffOptHighlight, gRaceSelectionTTOffOpt,
                                        gRaceSelectionTTOn, gRaceSelectionTTOnOptHighlight, gRaceSelectionTTOnOpt };
DrawTexture *gTrackSelectPlayerImage[6] = { gRaceSelectionPlayer1Texture, gRaceSelectionPlayer2Texture,
                                            gRaceSelectionPlayer3Texture, gRaceSelectionPlayer4Texture,
                                            gRaceSelectionVehicleTitleTexture, gRaceSelectionTTTitleTexture };
DrawTexture *gMenuSelectionArrows[4] = { gMenuSelectionArrowUp, gMenuSelectionArrowLeft, gMenuSelectionArrowDown,
                                         gMenuSelectionArrowRight };
s16 gTracksMenuPlayerNamePositions[20] = {
    0x44, 0x72,
    0x44, 0x72, 0xCC, 0x72,
    0x21, 0x72, 0x88, 0x72, 0xEF, 0x72,
    0x21, 0x72, 0x66, 0x72, 0xAA, 0x72, 0xEF, 0x72,
};
s16 gTracksMenuVehicleNamePositions[10] = {
    0x68,
    0x21, 0xFB,
    0x27, 0x8E, 0xF5,
    0x27, 0x6C, 0xB0, 0xF5
};
s16 gTracksMenuArrowPositionsNTSC[8] = {
    0x0000, 0xFFC2, 0x0055, 0x0000, 0x0000, 0x003E, 0xFFAB, 0x0000,
};
s16 gTracksMenuArrowPositionsPAL[8] = {
    0x0000, 0xFFB6, 0x0055, 0x0000, 0x0000, 0x004A, 0xFFAB, 0x0000,
};
ButtonTextElement gTwoPlayerRacerCountMenu = {
    (320 / 2) - 80, 140, 160, 64, 4, 4, { 80, 20, 58, 40, 80, 40, 102, 40 }
};
ButtonElement gTracksMenuAdventureButton = { 80, 152, 160, 40, 4, 4, 80, 14 };
s16 gTracksMenuBgTextureIndices[15] = {
    0x0E, 0x0F, 0x00,
    0x10, 0x11, 0x20,
    0x12, 0x13, 0x00,
    0x14, 0x15, 0x20,
    0x16, 0x17, 0x20
};
TextureHeader *gTracksMenuBgTextures[10] = {
    0, 0,
    0, 0,
    0, 0,
    0, 0,
    0, 0
};
s16 gTTVoiceLines[53] = { -1,
                          -1,
                          SOUND_VOICE_TT_DRAGON_FOREST,
                          SOUND_VOICE_TT_FOSSIL_CANYON,
                          SOUND_VOICE_TT_PIRATE_LAGOON,
                          SOUND_VOICE_TT_ANCIENT_LAKE,
                          SOUND_VOICE_TT_WALRUS_COVE,
                          SOUND_VOICE_TT_HOT_TOP_VOLCANO,
                          SOUND_VOICE_TT_WHALE_BAY,
                          SOUND_VOICE_TT_SNOWBALL_VALLEY,
                          SOUND_VOICE_TT_CRESCENT_ISLAND,
                          SOUND_VOICE_TT_FIRE_MOUNTAIN,
                          SOUND_VOICE_TT_DINO_DOMAIN,
                          SOUND_VOICE_TT_EVERFROST_PEAK,
                          SOUND_VOICE_TT_SHERBET_ISLAND,
                          SOUND_VOICE_TT_SPACEPORT_ALPHA,
                          -1,
                          SOUND_VOICE_TT_SPACEDUST_VALLEY,
                          SOUND_VOICE_TT_GREENWOOD_VILLAGE,
                          SOUND_VOICE_TT_BOULDER_CANYON,
                          SOUND_VOICE_TT_WINDMILL_PLAINS,
                          -1,
                          -1,
                          -1,
                          SOUND_VOICE_TT_SNOWFLAKE_MOUNTAIN,
                          SOUND_VOICE_TT_SMOKEY_CASTLE,
                          SOUND_VOICE_TT_DARKWATER_BEACH,
                          SOUND_VOICE_TT_ICICLE_PYRAMID,
                          SOUND_VOICE_TT_FROSTY_VILLAGE,
                          SOUND_VOICE_TT_JUNGLE_FALLS,
                          SOUND_VOICE_TT_TREASURE_CAVES,
                          SOUND_VOICE_TT_HAUNTED_WOODS,
                          SOUND_VOICE_TT_DARKMOON_CAVERNS,
                          SOUND_VOICE_TT_STAR_CITY,
                          SOUND_VOICE_TT_TROPHY_RACE,
                          SOUND_VOICE_TT_FUTURE_FUN_LAND,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1,
                          -1 };
s16 gTrackSelectObjectIndices[14] = {
    0x05, 0x06, 0x07, 0x3D, 0x3C, 0x3F, 0x3E, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, -1
};
s16 gTrackSelectImageIndices[4] = { 0x04, 0x05, 0x06, -1 };
s16 gTrackSelectPreviewObjectIndices[36] = { 0x0004, 0x0000, 0x0001, 0x0002, 0x0003, 0x0018, 0x0019, 0x001A, 0x001B,
                                             0x001C, 0x001D, 0x0024, 0x0025, 0x0026, 0x0027, 0x0028, 0x0029, 0x002A,
                                             0x002B, 0x001E, 0x001F, 0x0020, 0x0021, 0x0022, 0x0023, 0x002C, 0x002D,
                                             0x002E, 0x002F, 0x0030, 0x0031, 0x0040, 0x0041, 0x0043, 0x0069, 0xFFFF
};
s16 gTrackSelectPreviewImageIndices[8] = { 0x07, 0x00, 0x01, 0x02, 0x03, 0x0B, 0x0C, -1 };
u8 gTrackSelectBgData[295] = {
    0, 0, 255, 255, 0, 1, 1, 255, 255, 0, 2, 0, 255, 255, 0, 3, 1, 255, 255, 0, 4, 0, 255, 255, 0,
    5, 1, 255, 255, 0, 6, 0, 255, 255, 0, 6, 2, 0, 64, 0, 7, 1, 255, 255, 0, 7, 3, 64, 128, 0,
    8, 0, 255, 255, 0, 8, 2, 128, 192, 32, 9, 1, 255, 255, 0, 9, 3, 192, 255, 32, 10, 2, 255, 255, 0,
    11, 3, 255, 255, 0, 12, 2, 255, 255, 32, 13, 3, 255, 255, 32, 14, 2, 255, 255, 0, 14, 4, 0, 64, 0,
    15, 3, 255, 255, 0, 15, 5, 64, 128, 0, 16, 2, 255, 255, 32, 16, 4, 128, 192, 0, 17, 3, 255, 255, 32,
    17, 5, 192, 255, 0, 18, 4, 255, 255, 0, 19, 5, 255, 255, 0, 20, 4, 255, 255, 0, 21, 5, 255, 255, 0,
    22, 4, 255, 255, 0, 22, 6, 0, 64, 0, 23, 5, 255, 255, 0, 23, 7, 64, 128, 0, 24, 4, 255, 255, 0,
    24, 6, 128, 192, 32, 25, 5, 255, 255, 0, 25, 7, 192, 255, 32, 26, 6, 255, 255, 0, 27, 7, 255, 255, 0,
    28, 6, 255, 255, 32, 29, 7, 255, 255, 32, 30, 6, 255, 255, 0, 30, 8, 0, 64, 0, 31, 7, 255, 255, 0,
    31, 9, 64, 128, 0, 32, 6, 255, 255, 32, 32, 8, 128, 192, 32, 33, 7, 255, 255, 32, 33, 9, 192, 255, 32,
    34, 8, 255, 255, 0, 35, 9, 255, 255, 0, 36, 8, 255, 255, 32, 37, 9, 255, 255, 32, 38, 8, 255, 255, 0,
    39, 9, 255, 255, 0, 40, 8, 255, 255, 32, 41, 9, 255, 255, 32, 255, 0, 0, 0, 0
};
Vertex *gTrackSelectBgVertices[2] = { 0, 0 };
Triangle *gTrackSelectBgTriangles[2] = { 0, 0 };
char *gQMarkPtr = "?";
s32 gIsInTracksMenu = 0;
s32 gTrackNameVoiceDelay = 0;
s32 gMenuOptionCap = 0;
s32 gMenuSubOption = 0;
s32 gLastPlayerWhoPaused = 0;
ColourRGBA gPlayerPauseBgColour[4] = {
    { { { 64, 64, 255, 160 } } },
    { { { 255, 64, 64, 160 } } },
    { { { 208, 192, 32, 176 } } },
    { { { 32, 192, 64, 176 } } },
};
ColourRGBA gPlayerPauseOptionsTextColour[4] = {
    { { { 0, 255, 0, 128 } } },
    { { { 0, 255, 0, 96 } } },
    { { { 0, 0, 255, 96 } } },
    { { { 0, 0, 255, 128 } } },
};
char *sBadControllerPakMenuText[5] = { 0, 0, 0, 0, 0 };
char *sControllerPakFullMenuText[5] = { 0, 0, 0, 0, 0 };
char *sNoControllerPakMenuText[5] = { 0, 0, 0, 0, 0 };
char *sCorruptDataMenuText[6] = { 0, 0, 0, 0, 0, 0 };
char *sInsertControllerPakMenuText[3] = { 0, 0, 0 };
s16 D_800E0A10[2] = { 0x0000, 0x0000 };
char *sInsertRumblePakMenuText[4] = { 0, 0, 0, 0 };
s16 gRaceResultsObjectIndices[14] = { 0x0005, 0x003B, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036,
                                      0x0039, 0x0037, 0x0038, 0x003A, 0x0000, 0x0001, 0xFFFF };
s16 gRaceResultsImageIndices[8] = { 0x0004, 0x0000, 0x0001, 0xFFFF, 0x0300, 0x0000, 0x0012, 0xFFFF };
DrawTexture gMenuPortraitKrunch[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gMenuPortraitDiddy[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gMenuPortraitDrumstick[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gMenuPortraitBumper[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gMenuPortraitBanjo[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gMenuPortraitConker[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gMenuPortraitTiptup[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gMenuPortraitTT[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gMenuPortraitPipsy[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture gMenuPortraitTimber[2] = { { 0, 0, 0 }, { 0, 0, 0 } };
DrawTexture *gRacerPortraits[10] = { gMenuPortraitKrunch, gMenuPortraitDiddy, gMenuPortraitDrumstick,
                                     gMenuPortraitBumper, gMenuPortraitBanjo, gMenuPortraitConker,
                                     gMenuPortraitTiptup, gMenuPortraitTT, gMenuPortraitPipsy,
                                     gMenuPortraitTimber };
s16 unused_800E0B18[74] = { 0x0140, 0x017C, 0x01B8, 0x01F4, 0x0230, 0x026C, 0x02A8, 0x02E4, 0x01E0, 0x0000, 0x0018,
                            0x0039, 0x005A, 0x007B, 0x009C, 0x00BD, 0x00DE, 0x00FF, 0x00A0, 0x0000, 0x0140, 0x01B8,
                            0x0230, 0x02A8, 0x01E0, 0x0000, 0x0018, 0x0065, 0x00B3, 0x0100, 0x00A0, 0x0000, 0x0140,
                            0x01F4, 0x02A8, 0x01E0, 0x0028, 0x008C, 0x00F0, 0x00A0, 0x01E0, 0x00C0, 0x00A0, 0x00C0,
                            0xFF60, 0x00C0, 0xFF80, 0xFFEC, 0xFFE4, 0xFFE6, 0x0050, 0xFFF8, 0xFFE4, 0xFFF4, 0xFFE4,
                            0x0006, 0xFFE4, 0x0018, 0x0050, 0x0008, 0x0000, 0x0078, 0x0000, 0x003C, 0x0000, 0x001E,
                            0x0000, 0x0384, 0x0000, 0x001E, 0x0000, 0x001E, 0x0000, 0x0384 };
char gFirstPlace[4] = "1ST";
char gSecondPlace[4] = "2ND";
char gThirdPlace[4] = "3RD";
char gFourthPlace[4] = "4TH";
char gFifthPlace[4] = "5TH";
char gSixthPlace[4] = "6TH";
char gSeventhPlace[4] = "7TH";
char gEighthPlace[4] = "8TH";
char *gRacePlacementsArray[8] = { gFirstPlace, gSecondPlace, gThirdPlace, gFourthPlace,
                                  gFifthPlace, gSixthPlace, gSeventhPlace, gEighthPlace };
MenuElement gRaceResultsMenuElements[8] = {
    { 352, 172, 32, 172, -288, 172, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, { { 0, 0, 0, 0 } } },
    { 452, 166, 132, 166, -188, 166, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { 560, 184, 240, 184, -80, 184, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { 452, 180, 132, 180, -188, 180, 255, 192, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 1, { 0 }, { { 0, 0, 0, 0 } } },
    { 452, 198, 132, 198, -188, 198, 255, 192, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 1, { 0 }, { { 0, 0, 0, 0 } } },
    { 452, 216, 132, 216, -188, 216, 255, 192, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 1, { 0 }, { { 0, 0, 0, 0 } } },
    { 560, 200, 240, 200, -80, 200, 128, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 1, { 0 }, { { 0, 0, 0, 0 } } },
    {0}
};
MenuElement gRaceOrderMenuElements[11] = {
    { 575, 172, 255, 172, -65, 172, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, { { 0, 0, 0, 0 } } },
    { 542, 172, 222, 172, -98, 172, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, { { 0, 0, 0, 0 } } },
    { 509, 172, 189, 172, -131, 172, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, { { 0, 0, 0, 0 } } },
    { 476, 172, 156, 172, -164, 172, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, { { 0, 0, 0, 0 } } },
    { 443, 172, 123, 172, -197, 172, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, { { 0, 0, 0, 0 } } },
    { 410, 172, 90, 172, -230, 172, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, { { 0, 0, 0, 0 } } },
    { 377, 172, 57, 172, -263, 172, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, { { 0, 0, 0, 0 } } },
    { 344, 172, 24, 172, -296, 166, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, { { 0, 0, 0, 0 } } },
    { 481, 166, 161, 166, -159, 166, 0, 0, 0, 255, 128, ASSET_FONTS_FUNFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { 479, 164, 159, 164, -161, 164, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    {0}
};
MenuElement gRecordTimesMenuElements[9] = {
    { 481, 174, 161, 174, -159, 174, 0, 0, 0, 255, 128, ASSET_FONTS_FUNFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { 479, 172, 159, 172, -161, 172, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { 368, 192, 48, 192, -272, 192, 255, 64, 64, 96, 255, ASSET_FONTS_FUNFONT, 8, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { 506, 187, 186, 187, -134, 187, 255, 192, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 1, { 0 }, { { 0, 0, 0, 0 } } },
    { 578, 192, 258, 192, -62, 192, 255, 128, 255, 96, 255, ASSET_FONTS_FUNFONT, 12, 0, { &gCourseInitials }, { { 0, 0, 0, 0 } } },
    { 368, 212, 48, 212, -272, 212, 255, 64, 64, 96, 255, ASSET_FONTS_FUNFONT, 8, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { 506, 207, 186, 207, -134, 207, 128, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 1, { 0 }, { { 0, 0, 0, 0 } } },
    { 578, 212, 258, 212, -62, 212, 255, 128, 255, 96, 255, ASSET_FONTS_FUNFONT, 12, 0, { &gFLapInitials }, { { 0, 0, 0, 0 } } }, {0}
};
u8 gFileNameValidChars[32] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ.?    ";
char gCurFilenameCharBeingDrawn = '\0';
s32 gEnterInitalsY = 192;
s32 gFilenameX = 160;
s32 gFilenameY = 120;
s32 gFilenameFont = ASSET_FONTS_BIGFONT;
s32 gNameEntryLength = 0;
s32 D_800E0FA4 = 0;
char gCheckAdvEnterInitials[] = "DKR";
s32 D_800E0FAC = 0;
s32 gIndexOfCurInputCharacter = 0;
s16 gAdvTrackInitObjectIndices[18] = { 0x0004, 0x0000, 0x0001, 0x0018, 0x0019, 0x001A, 0x001B, 0x001C, 0x001D,
                                       0x001E, 0x001F, 0x0020, 0x0021, 0x0022, 0x0023, 0x0030, 0x0069, -1
};
s16 gAdvTrackInitImageIndices[6] = { 7, 0, 1, 2, 3, -1 };
s32 gRankingPlayerCount = 8;
s32 gTrophyRaceWorldId = 0;
s32 gTrophyRaceRound = 0;
s32 gPrevTrophyRaceRound = 0;
u32 unused_800E0FF4[4] = { 0x01FFFFFF, 0x0012FFFF, 0x81FFFFFF, 0x00120000 };
s32 gTrophyRacePointsArray[8] = { 9, 7, 5, 3, 1, 0, 0, 0 };
s16 gTrophyRankingsObjectIndices[14] = { 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
                                         0x39, 0x3A, 0x3B, 0x00, 0x01, -1, 0x00 };
s16 gTrophyRaceImageIndices[3] = { 0, 1, -1 };
MenuElement gTrophyRankingsTitle[] = {
    { 320 + 160 + 1, 35, (320 / 2) + 1, 35, -159, 35, 0, 0, 0, 255, 128, ASSET_FONTS_BIGFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { 320 + 160, 32, (320 / 2), 32, -160, 32, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 12, 0, { 0 }, { { 0, 0, 0, 0 } } },
};
MenuElement gTrophyRankingsRacers[] = {
    { 64, -192, 64, 48, 64, 288, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, { { 0, 0, 0, 0 } } },
    { 32, -192, 32, 48, 32, 288, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 0, { gFirstPlace }, { { 0, 0, 0, 0 } } },
    { 130, -172, 130, 68, 130, 308, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 4, 2, { &gTrophyRacePointsArray[0] }, { { 0, 0, 0, 0 } } },
    { 64, -150, 64, 90, 64, 330, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, { { 0, 0, 0, 0 } } },
    { 32, -150, 32, 90, 32, 330, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 0, { gSecondPlace }, { { 0, 0, 0, 0 } } },
    { 130, -130, 130, 110, 130, 350, 255, 192, 255, 0, 255, ASSET_FONTS_FUNFONT, 4, 2, { &gTrophyRacePointsArray[1] }, { { 0, 0, 0, 0 } } },
    { 64, -108, 64, 132, 64, 372, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, { { 0, 0, 0, 0 } } },
    { 32, -108, 32, 132, 32, 372, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 0, { gThirdPlace }, { { 0, 0, 0, 0 } } },
    { 130, -88, 130, 152, 130, 392, 255, 128, 255, 0, 255, ASSET_FONTS_FUNFONT, 4, 2, { &gTrophyRacePointsArray[2] }, { { 0, 0, 0, 0 } } },
    { 64, -66, 64, 174, 64, 414, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, { { 0, 0, 0, 0 } } },
    { 32, -66, 32, 174, 32, 414, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 0, { gFourthPlace }, { { 0, 0, 0, 0 } } },
    { 130, -46, 130, 194, 130, 434, 255, 64, 255, 0, 255, ASSET_FONTS_FUNFONT, 4, 2, { &gTrophyRacePointsArray[3] }, { { 0, 0, 0, 0 } } },
    { 220, 288, 220, 48, 220, -192, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, { { 0, 0, 0, 0 } } },
    { 188, 288, 188, 48, 188, -192, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 0, { gFifthPlace }, { { 0, 0, 0, 0 } } },
    { 286, 308, 286, 68, 286, -172, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 4, 2, { &gTrophyRacePointsArray[4] }, { { 0, 0, 0, 0 } } },
    { 220, 330, 220, 90, 220, -160, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, { { 0, 0, 0, 0 } } },
    { 188, 330, 188, 90, 188, -150, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 0, { gSixthPlace }, { { 0, 0, 0, 0 } } },
    { 286, 350, 286, 110, 286, -130, 255, 192, 255, 0, 255, ASSET_FONTS_FUNFONT, 4, 2, { &gTrophyRacePointsArray[5] }, { { 0, 0, 0, 0 } } },
    { 220, 372, 220, 132, 220, -108, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, { { 0, 0, 0, 0 } } },
    { 188, 372, 188, 132, 188, -108, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 0, { gSeventhPlace }, { { 0, 0, 0, 0 } } },
    { 286, 392, 286, 152, 286, -88, 255, 128, 255, 0, 255, ASSET_FONTS_FUNFONT, 4, 2, { &gTrophyRacePointsArray[6] }, { { 0, 0, 0, 0 } } },
    { 220, 414, 220, 174, 220, -66, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 3, { &gMenuPortraitKrunch }, { { 0, 0, 0, 0 } } },
    { 188, 414, 188, 174, 188, -66, 255, 255, 255, 0, 255, ASSET_FONTS_FUNFONT, 0, 0, { gEighthPlace }, { { 0, 0, 0, 0 } } },
    { 286, 434, 286, 194, 286, -46, 255, 64, 255, 0, 255, ASSET_FONTS_FUNFONT, 4, 2, { &gTrophyRacePointsArray[7] }, { { 0, 0, 0, 0 } } },
    {0}
};
s16 gTrophyRankingsRawIconPositions[] = {
    0x0040, 0x0020, 0x0082, 0x0040, 0x0020, 0x0082, 0x0040, 0x0020, 0x0082, 0x0040, 0x0020, 0x0082, 0x00DC, 0x00BC,
    0x011E, 0x00DC, 0x00BC, 0x011E, 0x00DC, 0x00BC, 0x011E, 0x00DC, 0x00BC, 0x011E, 0x0030, 0x0030, 0x0044, 0x005A,
    0x005A, 0x006E, 0x0084, 0x0084, 0x0098, 0x00AE, 0x00AE, 0x00C2, 0x0030, 0x0030, 0x0044, 0x005A, 0x005A, 0x006E,
    0x0084, 0x0084, 0x0098, 0x00AE, 0x00AE, 0x00C2, 0x0038, 0x0038, 0x0040, 0x006A, 0x006A, 0x0072, 0x009C, 0x009C,
    0x00A4, 0x00CE, 0x00CE, 0x00D6, 0x0038, 0x0038, 0x0040, 0x006A, 0x006A, 0x0072, 0x009C, 0x009C, 0x00A4, 0x00CE,
    0x00CE, 0x00D6, 0x0040, 0x0020, 0x0082, 0x0040, 0x0020, 0x0082, 0x0040, 0x0020, 0x0082, 0x00DC, 0x00BC, 0x011E,
    0x00DC, 0x00BC, 0x011E, 0x00DC, 0x00BC, 0x011E, 0x0034, 0x0034, 0x0048, 0x006F, 0x006F, 0x0083, 0x00AA, 0x00AA,
    0x00BE, 0x0034, 0x0034, 0x0048, 0x006F, 0x006F, 0x0083, 0x00AA, 0x00AA, 0x00BE, 0x004C, 0x004C, 0x0054, 0x007E,
    0x007E, 0x0086, 0x00B0, 0x00B0, 0x00B8, 0x004C, 0x004C, 0x0054, 0x007E, 0x007E, 0x0086, 0x00B0, 0x00B0, 0x00B8,
    0x008C, 0x006C, 0x00CE, 0x008C, 0x006C, 0x00CE, 0x008C, 0x006C, 0x00CE, 0x008C, 0x006C, 0x00CE
};
s16 *gTrophyRankingsIconPositions[32] = { 0,
                                          0,
                                          0,
                                          0,
                                          &gTrophyRankingsRawIconPositions[126],
                                          &gTrophyRankingsRawIconPositions[90],
                                          &gTrophyRankingsRawIconPositions[126],
                                          &gTrophyRankingsRawIconPositions[24],
                                          0,
                                          0,
                                          &gTrophyRankingsRawIconPositions[72],
                                          &gTrophyRankingsRawIconPositions[90],
                                          0,
                                          0,
                                          &gTrophyRankingsRawIconPositions[0],
                                          &gTrophyRankingsRawIconPositions[24],
                                          0,
                                          0,
                                          0,
                                          0,
                                          &gTrophyRankingsRawIconPositions[126],
                                          &gTrophyRankingsRawIconPositions[108],
                                          &gTrophyRankingsRawIconPositions[126],
                                          &gTrophyRankingsRawIconPositions[48],
                                          0,
                                          0,
                                          &gTrophyRankingsRawIconPositions[72],
                                          &gTrophyRankingsRawIconPositions[108],
                                          0,
                                          0,
                                          &gTrophyRankingsRawIconPositions[0],
                                          &gTrophyRankingsRawIconPositions[48] };
DrawTexture gDrawTexDinoDomainGhostBg[] = { { 0, 0, 0 }, { 0, 64, 0 }, { 0, 128, 0 }, { 0, 192, 0 },
                                            { 0, 256, 0 }, { 0, 0, 32 }, { 0, 64, 32 }, { 0, 128, 32 },
                                            { 0, 192, 32 }, { 0, 256, 32 }, { 0, 0, 0 } };
DrawTexture gDrawTexSherbetIslandGhostBg[] = { { 0, 0, 0 }, { 0, 64, 0 }, { 0, 128, 0 },
                                               { 0, 192, 0 }, { 0, 256, 0 }, { 0, 0, 32 },
                                               { 0, 64, 32 }, { 0, 128, 32 }, { 0, 192, 32 },
                                               { 0, 256, 32 }, { 0, 0, 0 } };
DrawTexture gDrawTexSnowflakeMountainGhostBg[] = { { 0, 0, 0 }, { 0, 64, 0 }, { 0, 128, 0 },
                                                   { 0, 192, 0 }, { 0, 256, 0 }, { 0, 0, 32 },
                                                   { 0, 64, 32 }, { 0, 128, 32 }, { 0, 192, 32 },
                                                   { 0, 256, 32 }, { 0, 0, 0 } };
DrawTexture gDrawTexDragonForestGhostBg[] = { { 0, 0, 0 }, { 0, 64, 0 }, { 0, 128, 0 }, { 0, 192, 0 },
                                              { 0, 256, 0 }, { 0, 0, 32 }, { 0, 64, 32 }, { 0, 128, 32 },
                                              { 0, 192, 32 }, { 0, 256, 32 }, { 0, 0, 0 } };
DrawTexture gDrawTexFutureFunLandGhostBg[] = { { 0, 0, 0 }, { 0, 64, 0 }, { 0, 128, 0 },
                                               { 0, 192, 0 }, { 0, 256, 0 }, { 0, 0, 32 },
                                               { 0, 64, 32 }, { 0, 128, 32 }, { 0, 192, 32 },
                                               { 0, 256, 32 }, { 0, 0, 0 } };
DrawTexture *gDrawTexWorldBgs[5] = {
    gDrawTexDinoDomainGhostBg,
    gDrawTexSherbetIslandGhostBg,
    gDrawTexSnowflakeMountainGhostBg,
    gDrawTexDragonForestGhostBg,
    gDrawTexFutureFunLandGhostBg
};
s16 gGhostDataObjectIndices[34] = { 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
                                    0x1A, 0x1B, 0x1C, 0x1D, 0x32, 0x33, 0x34, 0x36, 0x35, 0x37, 0x38, 0x39,
                                    0x3A, 0x3B, 0x00, 0x01, 0x04, 0x3D, 0x3C, 0x3F, 0x3E, -1 };
s16 gGhostDataImageIndices[4] = { 0, 1, 7, -1 };
s16 gGhostDataElementPositions[10] = { 0x78, 0x12, 0x08, 0x06, 0xC0, 0x06, 0xD4, 0x1A, 0x78, 0x22 };
s16 gCinematicObjectIndices[12] = { 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, -1, 0 };
Gfx dCreditsFade[11] = {
    {{ ((unsigned int) (((unsigned int)(0xe7) & ((0x01 << (8)) - 1)) << (24))), 0 }},
    {{ ((unsigned int) (((unsigned int)((-65 -5)) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(20) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(2) & ((0x01 << (8)) - 1)) << (0))), (unsigned int)((0 << 20)) }},
    {{ ((unsigned int) (((unsigned int)((-65 -5)) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(16) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(1) & ((0x01 << (8)) - 1)) << (0))), (unsigned int)((0 << 16)) }},
    {{ ((unsigned int) (((unsigned int)((-65 -5)) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(14) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(2) & ((0x01 << (8)) - 1)) << (0))), (unsigned int)((0 << 14)) }},
    {{ ((unsigned int) (((unsigned int)((-65 -5)) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(17) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(2) & ((0x01 << (8)) - 1)) << (0))), (unsigned int)((0 << 17)) }},
    {{ ((unsigned int) (((unsigned int)((-65 -5)) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(19) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(1) & ((0x01 << (8)) - 1)) << (0))), (unsigned int)((0 << 19)) }},
    {{ ((unsigned int) (((unsigned int)((-65 -5)) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(12) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(2) & ((0x01 << (8)) - 1)) << (0))), (unsigned int)((2 << 12)) }},
    {{ ((unsigned int) (((unsigned int)((-65 -5)) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(9) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(3) & ((0x01 << (8)) - 1)) << (0))), (unsigned int)((6 << 9)) }},
    {{ ((unsigned int) (((unsigned int)((-65 -6)) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(2) & ((0x01 << (8)) - 1)) << (0))), (unsigned int)((0 << 0)) }},
    {{ ((unsigned int) (((unsigned int)((-65 -6)) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(3) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(29) & ((0x01 << (8)) - 1)) << (0))), (unsigned int)((0x40 | 0x300 | 0x4000 | 0 | (0) << 30 | (0) << 26 | (1) << 22 | (0) << 18) | (0x40 | 0x300 | 0x4000 | 0 | (0) << 28 | (0) << 24 | (1) << 20 | (0) << 16)) }},
    {{ ((unsigned int) (((unsigned int)((-65 -7)) & ((0x01 << (8)) - 1)) << (24))), 0 }},
};
s16 gCreditsObjectIndices[12] = {
    0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x003B, -1, 0
};
s16 gCreditsImageIndices[2] = { -1, 0 };
typedef struct CreditsBackgroundLevelData {
    s8 levelId;
    s8 unk1;
    s8 cutsceneId;
    s8 unk3;
} CreditsBackgroundLevelData;
s16 gCreditsControlData[] = {
    ((0x2000) | ((s16) (2.75 * 60.0))),
    0,
    ((0x2000) | ((s16) (2.75 * 60.0))),
    1, 2,
    ((0x2000) | ((s16) (2.75 * 60.0))),
    3, 4, 5, 6,
    ((0x4000)),
    ((0x2000) | ((s16) (2.75 * 60.0))),
    7, 8,
    ((0x2000) | ((s16) (2.75 * 60.0))),
    9, 10, 11, 12,
    ((0x3000) | ((s16) (2.75 * 60.0))),
    13, 14, 15,
    ((0x4000)),
    ((0x2000) | ((s16) (2.75 * 60.0))),
    16, 17,
    ((0x2000) | ((s16) (2.75 * 60.0))),
    18, 19,
    ((0x2000) | ((s16) (2.75 * 60.0))),
    20,
    ((0x4000)),
    ((0x2000) | ((s16) (2.75 * 60.0))),
    21, 22,
    ((0x2000) | ((s16) (2.75 * 60.0))),
    23, 24,
    ((0x2000) | ((s16) (2.75 * 60.0))),
    25, 26,
    ((0x4000)),
    ((0x2000) | ((s16) (2.75 * 60.0))),
    27, 28, 29, 30, 31,
    ((0x3000) | ((s16) (2.75 * 60.0))),
    32, 33, 34, 35,
    ((0x3000) | ((s16) (2.75 * 60.0))),
    36, 37, 38,
    ((0x4000)),
    ((0x2000) | ((s16) (2.75 * 60.0))),
    39, 40, 41, 42, 43,
    ((0x3000) | ((s16) (2.75 * 60.0))),
    44, 45, 46,
    ((0x3000) | ((s16) (2.75 * 60.0))),
    47, 48, 49,
    ((0x4000)),
    ((0x2000) | ((s16) (2.75 * 60.0))),
    50, 51, 52, 53, 54,
    ((0x3000) | ((s16) (2.75 * 60.0))),
    55, 56, 57, 58,
    ((0x3000) | ((s16) (2.75 * 60.0))),
    59, 60, 61, 62,
    ((0x4000)),
    ((0x2000) | ((s16) (2.75 * 60.0))),
    63, 64, 65,
    ((0x2000) | ((s16) (2.75 * 60.0))),
    66, 67, 68, 69, 70,
    ((0x2000) | ((s16) (2.75 * 60.0))),
    71, 72, 73,
    ((0x4000)),
    ((0x2000) | ((s16) (2.75 * 60.0))),
    74, 75,
    ((0x3000) | ((s16) (2.75 * 60.0))),
    76,
    ((0x3000) | ((s16) (2.75 * 60.0))),
    77,
    ((0x4000)),
    ((0x2000) | ((s16) (2.75 * 60.0))),
    78, 79,
    ((0x2000) | ((s16) (2.75 * 60.0))),
    80, 81,
    ((0x2000) | ((s16) (2.75 * 60.0))),
    82, 83,
    ((0x4000)),
    ((0x2000) | ((s16) (2.75 * 60.0))),
    84,
    ((0x2000) | ((s16) (4.5 * 60.0))),
    85, 86,
    ((0x4000)),
    ((0x1000)),
    0, 1, 2, 3,
    ((0x4000)),
    ((0x6000) | ((s16) (8.334 * 60.0))),
    4, 5, 6, 7,
    ((0x4000)),
    ((0x6000) | ((s16) (8.334 * 60.0))),
    8, 9, 10, 11,
    ((0x4000)),
    ((0x6000) | ((s16) (8.334 * 60.0))),
    12, 13, 14, 15,
    ((0x4000)),
    ((0x6000) | ((s16) (8.334 * 60.0))),
    16, 17, 18, 19,
    ((0x4000)),
    ((0x1000))
};
char *gCreditsArray[87] = {
    "CREDITS",
    "Software Director",
    "R.Harrison",
    "Software Engineers",
    "P.Mountain", "J.Pegg", "R.Gale",
    "Art Director",
    "K.Bayliss",
    "3D Artists",
    "L.Musgrave", "K.Rabbette", "D.Smith", "J.Christensen", "B.Smyth", "P.Cunningham",
    "Music",
    "D.Wise",
    "Sound Effects",
    "G.Norgate",
    "ALSO",
    "Additional Design",
    "M.Wakeley",
    "Documentation",
    "L.Loveday",
    "Liaison",
    "E.Hochberg",
    "Character Voices",
    "K.Bayliss", "J.Christensen", "E.Fischer", "K.Rabbette", "L.Ray", "L.Schuneman",
    "C.Seavor", "D.Smith", "J.Stamper", "K.Stamper", "C.Sutherland",
    "Rare Quality Assurance",
    "H.Ward", "G.Richards", "S.Farmer", "J.Williams", "D.Wong", "G.Jones", "M.Penny",
    "S.Brand", "S.Malpass", "A.Wilson",
    "NOA Thanks To",
    "M.Fukuda", "K.Lobb", "M.Kelbaugh", "A.Williams", "R.Johnson", "M.Forrest",
    "P.Sandhop", "H.Sterchi", "T.Hertzog", "D.Bridgham", "G.Richardson", "B.Smith",
    "NOA Thanks To",
    "NOA Tree House", "NOA Tree Branch",
    "NCL Thank You's",
    "K.Terasaki", "M.Goto", "H.Yamada",
    "Mario Club",
    "NOE Thank You's",
    "J.Kraft", "J.Bardakoff",
    "Special Thanks To",
    "J.Hochberg", "H.Lincoln", "M.Arakawa",
    "Game Director",
    "L.Schuneman",
    "Producer",
    "C.Stamper",
    "Executive Producer",
    "T.Stamper",
    0,
    0,
    0 };
char *gCreditsBestTimesArray[20] = {
                              "0:53:43", "1:21:55", "0:54:13", "1:22:48",
                              "1:04:11", "1:13:51", "1:25:01", "0:55:05",
                              "1:37:63", "1:56:60", "0:57:81", "1:28:01",
                              "1:51:15", "1:31:80", "2:03:16", "0:58:25",
                              "2:00:38", "2:05:68", "1:52:96", "1:55:00"
};
char *gCreditsLastMessageArray[5] = {
    "THE END?", "TO BE CONTINUED ...",
    "THE END",
    "NO CHEAT", "THIS TIME.",
};
s32 gCheatsInCreditsArray[21] = { CHEAT_BIG_CHARACTERS,
                                  CHEAT_SMALL_CHARACTERS,
                                  CHEAT_MUSIC_MENU,
                                  CHEAT_START_WITH_10_BANANAS,
                                  CHEAT_HORN_CHEAT,
                                  CHEAT_DISPLAY_CREDITS,
                                  CHEAT_DISABLE_WEAPONS,
                                  CHEAT_DISABLE_BANANAS,
                                  CHEAT_BANANAS_REDUCE_SPEED,
                                  CHEAT_NO_LIMIT_TO_BANANAS,
                                  CHEAT_ALL_BALLOONS_ARE_RED,
                                  CHEAT_ALL_BALLOONS_ARE_GREEN,
                                  CHEAT_ALL_BALLOONS_ARE_BLUE,
                                  CHEAT_ALL_BALLOONS_ARE_YELLOW,
                                  CHEAT_ALL_BALLOONS_ARE_RAINBOW,
                                  CHEAT_MAXIMUM_POWER_UP,
                                  CHEAT_TURN_OFF_ZIPPERS,
                                  CHEAT_SELECT_SAME_PLAYER,
                                  CHEAT_FOUR_WHEEL_DRIVER,
                                  CHEAT_TWO_PLAYER_ADVENTURE,
                                  CHEAT_ULTIMATE_AI };
s32 gViewingCreditsFromCheat = 0;
MenuElement gCreditsMenuElements[9] = {
    { 480, 104, 160, 104, -160, 104, 255, 0, 255, 48, 255, ASSET_FONTS_FUNFONT, 4, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { 480, 132, 160, 132, -160, 132, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 4, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { 480, 104, 160, 104, -160, 104, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 4, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { 480, 132, 160, 132, -160, 132, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 4, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { 480, 104, 160, 104, -160, 104, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 4, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { 480, 132, 160, 132, -160, 132, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 4, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { 480, 104, 160, 104, -160, 104, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 4, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { 480, 132, 160, 132, -160, 132, 255, 255, 255, 0, 255, ASSET_FONTS_BIGFONT, 4, 0, { 0 }, { { 0, 0, 0, 0 } } },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, { 0 }, { { 0, 0, 0, 0 } } },
};
Gfx dMenuHudSettings[] = {
    {{ ((unsigned int) (((unsigned int)(0xe7) & ((0x01 << (8)) - 1)) << (24))), 0 }},
    {{ ((unsigned int) (((unsigned int)((-65 -5)) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(16) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(1) & ((0x01 << (8)) - 1)) << (0))), (unsigned int)((0 << 16)) }},
    {{ ((unsigned int) (((unsigned int)((-65 -5)) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(14) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(2) & ((0x01 << (8)) - 1)) << (0))), (unsigned int)((0 << 14)) }},
    {{ ((unsigned int) (((unsigned int)((-65 -6)) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(2) & ((0x01 << (8)) - 1)) << (0))), (unsigned int)((0 << 0)) }},
    {{ ((unsigned int) (((unsigned int)((-65 -9)) & ((0x01 << (8)) - 1)) << (24))), (unsigned int)(0x00000001 | 0x00010000) }},
    {{ ((unsigned int) (((unsigned int)((-65 -7)) & ((0x01 << (8)) - 1)) << (24))), 0 }},
};
Gfx dMenuHudDrawModes[][2] = {
    {
        {{ ((unsigned int) (((unsigned int)(0xfc) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((((unsigned int) (((unsigned int)((31)) & ((0x01 << (4)) - 1)) << (20))) | ((unsigned int) (((unsigned int)((31)) & ((0x01 << (5)) - 1)) << (15))) | ((unsigned int) (((unsigned int)((7)) & ((0x01 << (3)) - 1)) << (12))) | ((unsigned int) (((unsigned int)((7)) & ((0x01 << (3)) - 1)) << (9)))) | (((unsigned int) (((unsigned int)((31)) & ((0x01 << (4)) - 1)) << (5))) | ((unsigned int) (((unsigned int)((31)) & ((0x01 << (5)) - 1)) << (0))))) & ((0x01 << (24)) - 1)) << (0))), (unsigned int)((((unsigned int) (((unsigned int)((31)) & ((0x01 << (4)) - 1)) << (28))) | ((unsigned int) (((unsigned int)((4)) & ((0x01 << (3)) - 1)) << (15))) | ((unsigned int) (((unsigned int)((7)) & ((0x01 << (3)) - 1)) << (12))) | ((unsigned int) (((unsigned int)((4)) & ((0x01 << (3)) - 1)) << (9)))) | (((unsigned int) (((unsigned int)((31)) & ((0x01 << (4)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((7)) & ((0x01 << (3)) - 1)) << (21))) | ((unsigned int) (((unsigned int)((7)) & ((0x01 << (3)) - 1)) << (18))) | ((unsigned int) (((unsigned int)((4)) & ((0x01 << (3)) - 1)) << (6))) | ((unsigned int) (((unsigned int)((7)) & ((0x01 << (3)) - 1)) << (3))) | ((unsigned int) (((unsigned int)((4)) & ((0x01 << (3)) - 1)) << (0))))) }},
        {{ ((unsigned int) (((unsigned int)(0xef) & ((0x01 << (8)) - 1)) << (24)))|((unsigned int) (((unsigned int)(15 | (0 << 23) | (0 << 17) | (0 << 16) | (6 << 9) | (0 << 8) | (0 << 6) | (0 << 4) | (0 << 20) | (0 << 14) | (0 << 12) | (0 << 19)) & ((0x01 << (24)) - 1)) << (0))), (unsigned int)((0 << 0) | (0 << 2) | 0x40 | 0x200 | 0x4000 | 0 | (0) << 30 | (0) << 26 | (1) << 22 | (0) << 18 | 0x40 | 0x200 | 0x4000 | 0 | (0) << 28 | (0) << 24 | (1) << 20 | (0) << 16) }},
    },
    {
        {{ ((unsigned int) (((unsigned int)(0xfc) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((((unsigned int) (((unsigned int)((1)) & ((0x01 << (4)) - 1)) << (20))) | ((unsigned int) (((unsigned int)((4)) & ((0x01 << (5)) - 1)) << (15))) | ((unsigned int) (((unsigned int)((1)) & ((0x01 << (3)) - 1)) << (12))) | ((unsigned int) (((unsigned int)((4)) & ((0x01 << (3)) - 1)) << (9)))) | (((unsigned int) (((unsigned int)((1)) & ((0x01 << (4)) - 1)) << (5))) | ((unsigned int) (((unsigned int)((4)) & ((0x01 << (5)) - 1)) << (0))))) & ((0x01 << (24)) - 1)) << (0))), (unsigned int)((((unsigned int) (((unsigned int)((31)) & ((0x01 << (4)) - 1)) << (28))) | ((unsigned int) (((unsigned int)((31)) & ((0x01 << (3)) - 1)) << (15))) | ((unsigned int) (((unsigned int)((7)) & ((0x01 << (3)) - 1)) << (12))) | ((unsigned int) (((unsigned int)((7)) & ((0x01 << (3)) - 1)) << (9)))) | (((unsigned int) (((unsigned int)((31)) & ((0x01 << (4)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((1)) & ((0x01 << (3)) - 1)) << (21))) | ((unsigned int) (((unsigned int)((4)) & ((0x01 << (3)) - 1)) << (18))) | ((unsigned int) (((unsigned int)((31)) & ((0x01 << (3)) - 1)) << (6))) | ((unsigned int) (((unsigned int)((7)) & ((0x01 << (3)) - 1)) << (3))) | ((unsigned int) (((unsigned int)((7)) & ((0x01 << (3)) - 1)) << (0))))) }},
        {{ ((unsigned int) (((unsigned int)(0xef) & ((0x01 << (8)) - 1)) << (24)))|((unsigned int) (((unsigned int)(15 | (0 << 23) | (0 << 17) | (0 << 16) | (6 << 9) | (0 << 8) | (0 << 6) | (0 << 4) | (0 << 20) | (0 << 14) | (2 << 12) | (1 << 19)) & ((0x01 << (24)) - 1)) << (0))), (unsigned int)((0 << 0) | (0 << 2) | 0x40 | 0x200 | 0x4000 | 0 | (0) << 30 | (0) << 26 | (1) << 22 | (0) << 18 | 0x40 | 0x200 | 0x4000 | 0 | (0) << 28 | (0) << 24 | (1) << 20 | (0) << 16) }},
    },
    {
        {{ ((unsigned int) (((unsigned int)(0xfc) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((((unsigned int) (((unsigned int)((31)) & ((0x01 << (4)) - 1)) << (20))) | ((unsigned int) (((unsigned int)((31)) & ((0x01 << (5)) - 1)) << (15))) | ((unsigned int) (((unsigned int)((7)) & ((0x01 << (3)) - 1)) << (12))) | ((unsigned int) (((unsigned int)((7)) & ((0x01 << (3)) - 1)) << (9)))) | (((unsigned int) (((unsigned int)((31)) & ((0x01 << (4)) - 1)) << (5))) | ((unsigned int) (((unsigned int)((31)) & ((0x01 << (5)) - 1)) << (0))))) & ((0x01 << (24)) - 1)) << (0))), (unsigned int)((((unsigned int) (((unsigned int)((31)) & ((0x01 << (4)) - 1)) << (28))) | ((unsigned int) (((unsigned int)((3)) & ((0x01 << (3)) - 1)) << (15))) | ((unsigned int) (((unsigned int)((7)) & ((0x01 << (3)) - 1)) << (12))) | ((unsigned int) (((unsigned int)((3)) & ((0x01 << (3)) - 1)) << (9)))) | (((unsigned int) (((unsigned int)((31)) & ((0x01 << (4)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((7)) & ((0x01 << (3)) - 1)) << (21))) | ((unsigned int) (((unsigned int)((7)) & ((0x01 << (3)) - 1)) << (18))) | ((unsigned int) (((unsigned int)((3)) & ((0x01 << (3)) - 1)) << (6))) | ((unsigned int) (((unsigned int)((7)) & ((0x01 << (3)) - 1)) << (3))) | ((unsigned int) (((unsigned int)((3)) & ((0x01 << (3)) - 1)) << (0))))) }},
        {{ ((unsigned int) (((unsigned int)(0xef) & ((0x01 << (8)) - 1)) << (24)))|((unsigned int) (((unsigned int)(15 | (0 << 23) | (0 << 17) | (0 << 16) | (6 << 9) | (0 << 8) | (0 << 6) | (0 << 4) | (0 << 20) | (0 << 14) | (0 << 12) | (0 << 19)) & ((0x01 << (24)) - 1)) << (0))), (unsigned int)((0 << 0) | (0 << 2) | 0x40 | 0x200 | 0x4000 | 0 | (0) << 30 | (0) << 26 | (1) << 22 | (0) << 18 | 0x40 | 0x200 | 0x4000 | 0 | (0) << 28 | (0) << 24 | (1) << 20 | (0) << 16) }},
    }
};
u8 gWoodPanelsIndices[32] = { 0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7, 8, 9, 10, 8,
                              10, 11, 12, 13, 14, 12, 14, 15, 16, 17, 18, 16, 18, 19, 0, 0 };
u8 gWoodPanelTexCoords[5][12] = { { 0, 0, 3, 0, 2, 1, 0, 0, 2, 1, 1, 1 },
                                  { 2, 1, 3, 0, 3, 3, 2, 1, 3, 3, 2, 2 },
                                  { 1, 2, 2, 2, 3, 3, 1, 2, 3, 3, 0, 3 },
                                  { 0, 0, 1, 1, 1, 2, 0, 0, 1, 2, 0, 3 },
                                  { 1, 1, 2, 1, 2, 2, 1, 1, 2, 2, 1, 2 } };
s8 gWoodPanelVertCoords[][4] = {
    { 0, 0, 0, 0 }, { 1, 0, 0, 0 }, { 1, -1, 0, -1 }, { 0, 1, 0, -1 }, { 1, -1, 0, -1 },
    { 1, 0, 0, 0 }, { 1, 0, -1, 0 }, { 1, -1, -1, 1 }, { 0, 1, -1, 1 }, { 1, -1, -1, 1 },
    { 1, 0, -1, 0 }, { 0, 0, -1, 0 }, { 0, 0, 0, 0 }, { 0, 1, 0, -1 }, { 0, 1, -1, 1 },
    { 0, 0, -1, 0 }, { 0, 1, 0, -1 }, { 1, -1, 0, -1 }, { 1, -1, -1, 1 }, { 0, 1, -1, 1 }
};
s16 gWoodPanelVertColours[5][4] = {
    { 216, 216, 216, 256 },
    { 176, 176, 176, 256 },
    { 96, 96, 96, 256 },
    { 136, 136, 136, 256 },
    { 256, 256, 256, 256 }
};
Vertex *gWoodPanelVertices[2] = { 0, 0 };
Triangle *gWoodPanelTriangles[2] = { 0, 0 };
s32 gMenuTrisFlip = 0;
s32 gWoodPanelCount = 0;
s32 gWoodPanelAllocCount = 0;
s32 gWoodPanelTexScaleU = 32;
s32 gWoodPanelTexScaleV = 32;
s16 D_800E1DC8[16] = { 1, 1, -1, 1, -1, 1, -1, -1, 1, -1, -1, -1, 1, 1, 1, -1 };
FadeTransition gFadeLogoToTitleScreen =
    { (0 & 0x3F) | (0 & 0xC0), 0, 0, 0, 120, 0xFFFF };
char gRareCopyrightString[24] = "(C) COPYRIGHT RARE 1997";
FadeTransition gFadeTitleScreenDemo = { (0 & 0x3F) | (0 & 0xC0), 0, 0, 0, 52, 0xFFFF };
char *gConPakAdvSavePrefix = " (ADV.";
void load_menu_text(s32 language) {
    char **menuText;
    char **temp;
    s32 langIndex;
    s32 size;
    char **fake;
    if (gMenuTextLangTable == 0) {
        gMenuTextLangTable = (s32 *) asset_table_load(ASSET_MENU_TEXT_TABLE);
    }
    switch (language) {
        case LANGUAGE_JAPANESE:
            langIndex = 4;
            break;
        case LANGUAGE_GERMAN:
            langIndex = 3;
            break;
        case LANGUAGE_FRENCH:
            langIndex = 2;
            break;
        default:
            langIndex = 1;
            break;
    }
    size = gMenuTextLangTable[langIndex + 1];
    langIndex = gMenuTextLangTable[langIndex];
    size -= langIndex;
    temp = gMenuText;
    if (temp == 0) {
        return;
    }
    asset_load(ASSET_MENU_TEXT, (u32) temp, langIndex, size);
    for (langIndex = 0; langIndex < gMenuTextLangTable[0]; langIndex++) {
        menuText = (char **) gMenuText[langIndex];
        if ((((s32) menuText) & 0xFFFFFFFF) == 0xFFFFFFFF) {
            gMenuText[langIndex] = 0;
        } else {
            gMenuText[langIndex] = &((char *) gMenuText)[(s32) (fake = menuText)];
        }
    }
    menuText = gMenuText;
    gAudioOutputStrings[0] = menuText[ASSET_MENU_TEXT_STEREO];
    gAudioOutputStrings[1] = menuText[ASSET_MENU_TEXT_MONO];
    gAudioOutputStrings[2] = menuText[ASSET_MENU_TEXT_HEADPHONES];
    gAudioMenuStrings[1].text = menuText[ASSET_MENU_TEXT_SFXVOLUME];
    gAudioMenuStrings[2].text = menuText[ASSET_MENU_TEXT_MUSICVOLUME];
    gAudioMenuStrings[3].text = menuText[ASSET_MENU_TEXT_RETURN];
    gAudioMenuStrings[4].text = menuText[ASSET_MENU_TEXT_AUDIOOPTIONS];
    gAudioMenuStrings[5].text = menuText[ASSET_MENU_TEXT_AUDIOOPTIONS];
    gMusicTestString = menuText[ASSET_MENU_TEXT_MUSICTEST];
    gMagicCodeMenuStrings[0] = menuText[ASSET_MENU_TEXT_ENTERCODE];
    gMagicCodeMenuStrings[1] = menuText[ASSET_MENU_TEXT_CLEARALLCODES];
    gMagicCodeMenuStrings[2] = menuText[ASSET_MENU_TEXT_CODELIST];
    gMagicCodeMenuStrings[3] = menuText[ASSET_MENU_TEXT_RETURN];
    gRaceResultsMenuElements[1].t.asciiText = menuText[ASSET_MENU_TEXT_LAPTIMES];
    gRaceResultsMenuElements[2].t.asciiText = menuText[ASSET_MENU_TEXT_OVERALLTIME];
    gRaceOrderMenuElements[8].t.asciiText = menuText[ASSET_MENU_TEXT_RACEORDER];
    gRaceOrderMenuElements[9].t.asciiText = menuText[ASSET_MENU_TEXT_RACEORDER];
    gRecordTimesMenuElements[0].t.asciiText = menuText[ASSET_MENU_TEXT_RECORDTIMES];
    gRecordTimesMenuElements[1].t.asciiText = menuText[ASSET_MENU_TEXT_RECORDTIMES];
    gRecordTimesMenuElements[2].t.asciiText = menuText[ASSET_MENU_TEXT_BESTTIME];
    gRecordTimesMenuElements[5].t.asciiText = menuText[ASSET_MENU_TEXT_BESTLAP];
    gOptionMenuStrings[0] = menuText[ASSET_MENU_TEXT_LANGUAGE];
    if (sEepromSettings & 0x2000000) {
        gOptionMenuStrings[1] = menuText[ASSET_MENU_TEXT_SUBTITLESON];
    } else {
        gOptionMenuStrings[1] = menuText[ASSET_MENU_TEXT_SUBTITLESOFF];
    }
    gOptionMenuStrings[2] = menuText[ASSET_MENU_TEXT_AUDIOOPTIONS];
    gOptionMenuStrings[3] = menuText[ASSET_MENU_TEXT_SAVEOPTIONS];
    gOptionMenuStrings[4] = menuText[ASSET_MENU_TEXT_MAGICCODES];
    gOptionMenuStrings[5] = menuText[ASSET_MENU_TEXT_RETURN];
    gFilenames[0] = menuText[ASSET_MENU_TEXT_GAMEA];
    gFilenames[1] = menuText[ASSET_MENU_TEXT_GAMEB];
    gFilenames[2] = menuText[ASSET_MENU_TEXT_GAMEC];
    gContPakNotPresentStrings[0] = menuText[ASSET_MENU_TEXT_CONTPAKX];
    gContPakNotPresentStrings[1] = menuText[ASSET_MENU_TEXT_CONTPAKNOTPRESENT];
    gContPakNotPresentStrings[3] = menuText[ASSET_MENU_TEXT_CANCEL];
    gContPakCorruptDataRepairStrings[0] = menuText[ASSET_MENU_TEXT_CONTPAKX];
    gContPakCorruptDataRepairStrings[1] = menuText[ASSET_MENU_TEXT_CONTPAKHASCORRUPTDATA_0];
    gContPakCorruptDataRepairStrings[3] = menuText[ASSET_MENU_TEXT_CONTPAKHASCORRUPTDATA_1];
    gContPakCorruptDataRepairStrings[4] = menuText[ASSET_MENU_TEXT_CANCEL];
    gContPakDamagedStrings[0] = menuText[ASSET_MENU_TEXT_CONTPAKX];
    gContPakDamagedStrings[1] = menuText[ASSET_MENU_TEXT_CONTPAKISDAMAGED_0];
    gContPakDamagedStrings[3] = menuText[ASSET_MENU_TEXT_CONTPAKISDAMAGED_1];
    gContPakDamagedStrings[4] = menuText[ASSET_MENU_TEXT_CANCEL];
    gContPakFullStrings[0] = menuText[ASSET_MENU_TEXT_CONTPAKX];
    gContPakFullStrings[1] = menuText[ASSET_MENU_TEXT_CONTPAKISFULL];
    gContPakFullStrings[3] = menuText[ASSET_MENU_TEXT_CONTINUE];
    gContPakDiffContStrings[0] = menuText[ASSET_MENU_TEXT_CONTPAKX];
    gContPakDiffContStrings[1] = menuText[ASSET_MENU_TEXT_CONTPAKDIFFERENT_0];
    gContPakDiffContStrings[2] = menuText[ASSET_MENU_TEXT_CONTPAKDIFFERENT_1];
    gContPakDiffContStrings[4] = menuText[ASSET_MENU_TEXT_CANCEL];
    gContPakNoRoomForGhostsStrings[0] = menuText[ASSET_MENU_TEXT_CONTPAKX];
    gContPakNoRoomForGhostsStrings[1] = menuText[ASSET_MENU_TEXT_CANNOTSTOREANYMOREGHOSTS_0];
    gContPakNoRoomForGhostsStrings[2] = menuText[ASSET_MENU_TEXT_CANNOTSTOREANYMOREGHOSTS_1];
    gContPakNoRoomForGhostsStrings[4] = menuText[ASSET_MENU_TEXT_CONTINUE];
    gContPakCorruptDataStrings[0] = menuText[ASSET_MENU_TEXT_CONTPAKX];
    gContPakCorruptDataStrings[1] = menuText[ASSET_MENU_TEXT_CORRUPTDATA_0];
    gContPakCorruptDataStrings[3] = menuText[ASSET_MENU_TEXT_TRYAGAIN];
    gContPakCorruptDataStrings[4] = menuText[ASSET_MENU_TEXT_CANCEL];
    gContPakRumbleDetectedStrings[0] = menuText[ASSET_MENU_TEXT_RUMBLEPAKDETECTED_0];
    gContPakRumbleDetectedStrings[1] = menuText[ASSET_MENU_TEXT_RUMBLEPAKDETECTED_1];
    gContPakRumbleDetectedStrings[2] = menuText[ASSET_MENU_TEXT_RUMBLEPAKDETECTED_2];
    gContPakRumbleDetectedStrings[4] = menuText[ASSET_MENU_TEXT_CONTINUE];
    gContPakSwitchToRumbleStrings[0] = menuText[ASSET_MENU_TEXT_INSERTDEVICE_0];
    gContPakSwitchToRumbleStrings[1] = menuText[ASSET_MENU_TEXT_INSERTDEVICE_1];
    gContPakSwitchToRumbleStrings[2] = menuText[ASSET_MENU_TEXT_INSERTDEVICE_2];
    gContPakSwitchToRumbleStrings[4] = menuText[ASSET_MENU_TEXT_CONTINUE];
    gContPakNeed2ndAdvStrings[0] = menuText[ASSET_MENU_TEXT_ADVTWOLOADERROR_0];
    gContPakNeed2ndAdvStrings[1] = menuText[ASSET_MENU_TEXT_ADVTWOLOADERROR_1];
    gContPakNeed2ndAdvStrings[2] = menuText[ASSET_MENU_TEXT_ADVTWOLOADERROR_2];
    gContPakNeed2ndAdvStrings[3] = menuText[ASSET_MENU_TEXT_ADVTWOLOADERROR_3];
    gContPakNeed2ndAdvStrings[4] = menuText[ASSET_MENU_TEXT_ADVTWOLOADERROR_4];
    gContPakNeed2ndAdvStrings[5] = menuText[ASSET_MENU_TEXT_ADVTWOLOADERROR_5];
    gContPakNeed2ndAdvStrings[7] = menuText[ASSET_MENU_TEXT_CONTINUE];
    gTitleMenuStrings[0] = menuText[ASSET_MENU_TEXT_START];
    gTitleMenuStrings[1] = menuText[ASSET_MENU_TEXT_OPTIONS];
    gGameSelectTextElemsNoAdv2[0].t.asciiText = menuText[ASSET_MENU_TEXT_GAMESELECT];
    gGameSelectTextElemsNoAdv2[1].t.asciiText = menuText[ASSET_MENU_TEXT_GAMESELECT];
    gGameSelectTextElemsNoAdv2[3].t.asciiText = menuText[ASSET_MENU_TEXT_ADVENTURE];
    gGameSelectTextElemsNoAdv2[5].t.asciiText = menuText[ASSET_MENU_TEXT_TRACKS];
    gGameSelectTextElemsWithAdv2[0].t.asciiText = menuText[ASSET_MENU_TEXT_GAMESELECT];
    gGameSelectTextElemsWithAdv2[1].t.asciiText = menuText[ASSET_MENU_TEXT_GAMESELECT];
    gGameSelectTextElemsWithAdv2[3].t.asciiText = menuText[ASSET_MENU_TEXT_ADVENTURE];
    gGameSelectTextElemsWithAdv2[5].t.asciiText = menuText[ASSET_MENU_TEXT_ADVENTURETWO];
    gGameSelectTextElemsWithAdv2[7].t.asciiText = menuText[ASSET_MENU_TEXT_TRACKS];
    sBadControllerPakMenuText[0] = menuText[ASSET_MENU_TEXT_BADCONTPAK];
    sControllerPakFullMenuText[0] = menuText[ASSET_MENU_TEXT_CONTPAKFULL];
    sNoControllerPakMenuText[0] = menuText[ASSET_MENU_TEXT_NOCONTPAK];
    sCorruptDataMenuText[0] = menuText[ASSET_MENU_TEXT_CORRUPTDATA_0];
    sCorruptDataMenuText[4] = 0;
    sCorruptDataMenuText[5] = 0;
    for (langIndex = 0; langIndex <= 2; langIndex++) {
        sBadControllerPakMenuText[langIndex + 1] = menuText[ASSET_MENU_TEXT_CANNOTSAVEGHOSTDATA_0 + langIndex];
        sControllerPakFullMenuText[langIndex + 1] = menuText[ASSET_MENU_TEXT_CANNOTSAVEGHOSTDATA_0 + langIndex];
        sNoControllerPakMenuText[langIndex + 1] = menuText[ASSET_MENU_TEXT_CANNOTSAVEGHOSTDATA_0 + langIndex];
        sCorruptDataMenuText[langIndex + 1] = menuText[ASSET_MENU_TEXT_CANNOTSAVEGHOSTDATA_0 + langIndex];
    }
    for (langIndex = 0; sCorruptDataMenuText[langIndex] != 0; langIndex++) {}
    sCorruptDataMenuText[langIndex] = menuText[ASSET_MENU_TEXT_CORRUPTDATA_1];
    sInsertControllerPakMenuText[0] = menuText[ASSET_MENU_TEXT_INSERTDEVICE_3];
    sInsertControllerPakMenuText[1] = menuText[ASSET_MENU_TEXT_INSERTDEVICE_4];
    sInsertControllerPakMenuText[2] = menuText[161];
    sInsertRumblePakMenuText[0] = menuText[162];
    sInsertRumblePakMenuText[1] = menuText[186];
    sInsertRumblePakMenuText[2] = menuText[187];
    gCautionMenuTextElements[0].t.asciiText = menuText[ASSET_MENU_TEXT_CAUTION];
    gCautionMenuTextElements[1].t.asciiText = menuText[ASSET_MENU_TEXT_CAUTION];
    for (langIndex = 0; langIndex <= 10; langIndex++) {
        gCautionMenuTextElements[langIndex + 2].t.element = menuText[ASSET_MENU_TEXT_CAUTIONMESSAGE_0 + langIndex];
    }
}
void menu_button_free(void) {
    if (gWoodPanelTriangles[0] != 0) {
        mempool_free(gWoodPanelTriangles[0]);
        gWoodPanelTriangles[0] = 0;
    }
    gWoodPanelTriangles[1] = 0;
    gMenuGeometry = 0;
    gWoodPanelVertices[0] = 0;
    gWoodPanelVertices[1] = 0;
    gWoodPanelCount = 0;
    gWoodPanelAllocCount = 0;
}
void func_8007FFEC(s32 numberOfPanels) {
    s32 triListIndex;
    s32 triItemIndex;
    s32 IndicesIndex;
    s32 panelIndex;
    s32 i;
    s32 triangleCount;
    s32 vertexSize;
    s32 menuGeometrySize;
    if (gMenuGeometry != 0) {
        menu_button_free();
    }
    gWoodPanelTexScaleU = 32;
    gWoodPanelTexScaleV = 32;
    menuGeometrySize = sizeof(unk80080BC8) * numberOfPanels;
    vertexSize = sizeof(Vertex) * (20 * numberOfPanels);
    triangleCount = sizeof(Triangle) * (10 * numberOfPanels);
    gWoodPanelTriangles[0] =
        (Triangle *) mempool_alloc_safe(((vertexSize + triangleCount) * 2) + menuGeometrySize, 0xFFFFFFFF);
    gWoodPanelTriangles[1] = (Triangle *) ((u32) gWoodPanelTriangles[0] + triangleCount);
    gMenuGeometry = (unk80080BC8 *) ((u32) gWoodPanelTriangles[1] + triangleCount);
    gWoodPanelVertices[0] = (Vertex *) ((u32) gMenuGeometry + menuGeometrySize);
    gWoodPanelVertices[1] = (Vertex *) ((u32) gWoodPanelVertices[0] + vertexSize);
    panelIndex = 0;
    triangleCount = 0;
    for (i = 0; i < numberOfPanels; i++) {
        gMenuGeometry[i].vertices[0] = &gWoodPanelVertices[0][panelIndex];
        gMenuGeometry[i].vertices[1] = &gWoodPanelVertices[1][panelIndex];
        gMenuGeometry[i].triangles[0] = &gWoodPanelTriangles[0][triangleCount];
        gMenuGeometry[i].triangles[1] = &gWoodPanelTriangles[1][triangleCount];
        gMenuGeometry[i].texture[0] = 0;
        gMenuGeometry[i].texture[1] = 0;
        gMenuGeometry[i].unk18[0] = 0;
        gMenuGeometry[i].unk18[1] = 0;
        panelIndex += 20;
        triangleCount += 10;
    }
    triItemIndex = 0;
    for (i = 0; i < numberOfPanels; i++) {
        panelIndex = 0;
        for (IndicesIndex = 0; IndicesIndex < 10; triItemIndex++, panelIndex += 3, IndicesIndex++) {
            for (triListIndex = 0; triListIndex < 2; triListIndex++) {
                gWoodPanelTriangles[triListIndex][triItemIndex].verticesArray[0] = 0x40;
                gWoodPanelTriangles[triListIndex][triItemIndex].verticesArray[1] = gWoodPanelsIndices[panelIndex];
                gWoodPanelTriangles[triListIndex][triItemIndex].verticesArray[2] = gWoodPanelsIndices[panelIndex + 1];
                gWoodPanelTriangles[triListIndex][triItemIndex].verticesArray[3] = gWoodPanelsIndices[panelIndex + 2];
                gWoodPanelTriangles[triListIndex][triItemIndex].uv0.u = 0;
                gWoodPanelTriangles[triListIndex][triItemIndex].uv0.v = 0;
                gWoodPanelTriangles[triListIndex][triItemIndex].uv1.u = 0;
                gWoodPanelTriangles[triListIndex][triItemIndex].uv1.v = 0;
                gWoodPanelTriangles[triListIndex][triItemIndex].uv2.u = 0;
                gWoodPanelTriangles[triListIndex][triItemIndex].uv2.v = 0;
            }
        }
    }
    gMenuTrisFlip = 0;
    gWoodPanelCount = 0;
    gWoodPanelAllocCount = numberOfPanels;
}
 void menu_button_uvs(f32 u, f32 v) {
    gWoodPanelTexScaleU = u * 32.0f;
    gWoodPanelTexScaleV = v * 32.0f;
}
void func_80080580(Gfx **dList, s32 startX, s32 startY, s32 width, s32 height, s32 borderWidth, s32 borderHeight,
                   s32 colour, TextureHeader *tex) {
    s32 uVals[4];
    s32 vVals[4];
    Vertex *vertices;
    Triangle *triangles;
    s32 i;
    s32 j;
    s32 r, g, b, a;
    s32 r0, g0, b0, a0;
    s8(*texCoords)[4];
    s16(*texColors)[4];
    u8(*woodPanelTexCoords)[12];
    s32 pad;
    gMenuGeometry[gWoodPanelCount].texture[gMenuTrisFlip] = tex;
    if (tex != 0) {
        woodPanelTexCoords = gWoodPanelTexCoords;
        uVals[0] = 0;
        uVals[1] = gWoodPanelTexScaleU * borderWidth;
        uVals[2] = (width - borderWidth) * gWoodPanelTexScaleU;
        uVals[3] = gWoodPanelTexScaleU * width;
        vVals[0] = 0;
        j = gWoodPanelTexScaleV;
        vVals[1] = j * borderHeight;
        vVals[2] = (height - borderHeight) * gWoodPanelTexScaleV;
        vVals[3] = gWoodPanelTexScaleV * height;
        triangles = gMenuGeometry[gWoodPanelCount].triangles[gMenuTrisFlip];
        for (i = 0; i < 10; i += 2) {
            if (1) {}
            if (1) {}
            if (1) {}
            triangles[0].uv0.u = uVals[(*woodPanelTexCoords)[0]];
            triangles[0].uv0.v = vVals[(*woodPanelTexCoords)[1]];
            triangles[0].uv1.u = uVals[(*woodPanelTexCoords)[2]];
            triangles[0].uv1.v = vVals[(*woodPanelTexCoords)[3]];
            triangles[0].uv2.u = uVals[(*woodPanelTexCoords)[4]];
            triangles[0].uv2.v = vVals[(*woodPanelTexCoords)[5]];
            triangles[1].uv0.u = uVals[(*woodPanelTexCoords)[6]];
            triangles[1].uv0.v = vVals[(*woodPanelTexCoords)[7]];
            triangles[1].uv1.u = uVals[(*woodPanelTexCoords)[8]];
            triangles[1].uv1.v = vVals[(*woodPanelTexCoords)[9]];
            triangles[1].uv2.u = uVals[(*woodPanelTexCoords)[10]];
            triangles[1].uv2.v = vVals[(*woodPanelTexCoords)[11]];
            woodPanelTexCoords += 1;
            triangles += 2;
        }
    }
    r0 = ((colour >> 24) & 0xFF);
    g0 = ((colour >> 16) & 0xFF);
    b0 = ((colour >> 8) & 0xFF);
    a0 = (colour & 0xFF);
    vertices = gMenuGeometry[gWoodPanelCount].vertices[gMenuTrisFlip];
    for (texColors = gWoodPanelVertColours, texCoords = gWoodPanelVertCoords, i = 0; i < 5; i++) {
        r = ((*texColors)[0] * r0) >> 8;
        g = ((*texColors)[1] * g0) >> 8;
        b = ((*texColors)[2] * b0) >> 8;
        a = ((*texColors)[3] * a0) >> 8;
        texColors += 1;
        for (j = 0; j < 4; j++) {
            vertices->x = startX;
            vertices->x += (*texCoords)[0] * width;
            vertices->x += (*texCoords)[1] * borderWidth;
            vertices->y = startY;
            vertices->y += (*texCoords)[2] * height;
            vertices->y += (*texCoords)[3] * borderHeight;
            vertices->z = 0;
            vertices->r = r;
            vertices->g = g;
            vertices->b = b;
            vertices->a = a;
            texCoords += 1;
            vertices++;
        }
    }
    if (dList != 0) {
        gMenuGeometry[gWoodPanelCount].unk18[gMenuTrisFlip] = 1;
        { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = (((unsigned int) (((unsigned int)((6)) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((0x00)) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)((0)) & ((0x01 << (16)) - 1)) << (0)))); _g->words.w1 = (unsigned int)(&dMenuHudSettings); };
        if (tex != 0) {
            { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = (((unsigned int) (((unsigned int)(7) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((2)) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)((2*8)) & ((0x01 << (16)) - 1)) << (0)))); _g->words.w1 = (unsigned int)((u32)(((char *)(&dMenuHudDrawModes[1])-0x80000000))); };
            { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = (((unsigned int) (((unsigned int)(7) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((tex->numberOfCommands)) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)((tex->numberOfCommands*8)) & ((0x01 << (16)) - 1)) << (0)))); _g->words.w1 = (unsigned int)((u32)(((char *)(tex->cmd)-0x80000000))); };
            i = 1;
        } else {
            { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = (((unsigned int) (((unsigned int)(7) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((2)) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)((2*8)) & ((0x01 << (16)) - 1)) << (0)))); _g->words.w1 = (unsigned int)((u32)(((char *)(&dMenuHudDrawModes[0])-0x80000000))); };
            i = 0;
        }
        { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = ((unsigned int) (((unsigned int)(0xe7) & ((0x01 << (8)) - 1)) << (24))); _g->words.w1 = 0; };
        { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = (((unsigned int) (((unsigned int)((4)) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((((20)-1)<<3|(((u32)((u32)(((char *)(gMenuGeometry[gWoodPanelCount].vertices[gMenuTrisFlip])-0x80000000))) & 6))|(0))) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)(((((20) * 8 + (20)) << 1) + 8)) & ((0x01 << (16)) - 1)) << (0)))); _g->words.w1 = (unsigned int)((u32)(((char *)(gMenuGeometry[gWoodPanelCount].vertices[gMenuTrisFlip])-0x80000000))); };
        { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = ((unsigned int) (((unsigned int)((((10) - 1) << 4) | (i)) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)(5) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(((10)*16)) & ((0x01 << (16)) - 1)) << (0))); _g->words.w1 = (unsigned int)((u32)(((char *)(gMenuGeometry[gWoodPanelCount].triangles[gMenuTrisFlip])-0x80000000))); };
        rendermode_reset(dList);
    } else {
        gMenuGeometry[gWoodPanelCount].unk18[gMenuTrisFlip] = 0;
    }
    gWoodPanelCount++;
}
void func_80080BC8(Gfx **dList) {
    s16 pad;
    s32 i;
    s32 var_t0;
    TextureHeader *tex;
    TextureHeader *lastTex;
    { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = (((unsigned int) (((unsigned int)((6)) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((0x00)) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)((0)) & ((0x01 << (16)) - 1)) << (0)))); _g->words.w1 = (unsigned int)(&dMenuHudSettings); };
    var_t0 = -1;
    lastTex = 0;
    for (i = 0; i < gWoodPanelCount; i++) {
        if (!gMenuGeometry[i].unk18[gMenuTrisFlip]) {
            tex = gMenuGeometry[i].texture[gMenuTrisFlip];
            if (tex != 0) {
                if (var_t0 != 1) {
                    var_t0 = 1;
                    { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = (((unsigned int) (((unsigned int)(7) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((2)) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)((2*8)) & ((0x01 << (16)) - 1)) << (0)))); _g->words.w1 = (unsigned int)((u32)(((char *)(&dMenuHudDrawModes[1])-0x80000000))); };
                }
                if (lastTex != tex) {
                    { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = (((unsigned int) (((unsigned int)(7) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((tex->numberOfCommands)) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)((tex->numberOfCommands*8)) & ((0x01 << (16)) - 1)) << (0)))); _g->words.w1 = (unsigned int)((u32)(((char *)(tex->cmd)-0x80000000))); };
                    lastTex = tex;
                }
            } else if (var_t0 != 0) {
                var_t0 = 0;
                { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = (((unsigned int) (((unsigned int)(7) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((2)) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)((2*8)) & ((0x01 << (16)) - 1)) << (0)))); _g->words.w1 = (unsigned int)((u32)(((char *)(&dMenuHudDrawModes[0])-0x80000000))); };
            }
            { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = ((unsigned int) (((unsigned int)(0xe7) & ((0x01 << (8)) - 1)) << (24))); _g->words.w1 = 0; };
            { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = (((unsigned int) (((unsigned int)((4)) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((((20)-1)<<3|(((u32)((u32)(((char *)(gMenuGeometry[i].vertices[gMenuTrisFlip])-0x80000000))) & 6))|(0))) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)(((((20) * 8 + (20)) << 1) + 8)) & ((0x01 << (16)) - 1)) << (0)))); _g->words.w1 = (unsigned int)((u32)(((char *)(gMenuGeometry[i].vertices[gMenuTrisFlip])-0x80000000))); };
            { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = ((unsigned int) (((unsigned int)((((10) - 1) << 4) | (var_t0)) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)(5) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(((10)*16)) & ((0x01 << (16)) - 1)) << (0))); _g->words.w1 = (unsigned int)((u32)(((char *)(gMenuGeometry[i].triangles[gMenuTrisFlip])-0x80000000))); };
        }
    }
    gWoodPanelCount = 0;
    gMenuTrisFlip = 1 - gMenuTrisFlip;
    rendermode_reset(dList);
}
void menu_geometry_end(void) {
    gWoodPanelCount = 0;
    gMenuTrisFlip = 1 - gMenuTrisFlip;
}
void func_80080E90(Gfx **dList, s32 startX, s32 startY, s32 width, s32 height, s32 borderWidth, s32 borderHeight,
                   s32 colour0, s32 colour1, s32 colour2, s32 colour3) {
    s32 temp_ra;
    s32 temp_t3;
    s32 temp_t4;
    s32 temp_t5;
    s32 recUly;
    s32 recUlx;
    s32 uly;
    s32 recLrx;
    s32 borderLineCount;
    s32 i;
    s32 recLry;
    s32 ulx;
    s32 y0Orig;
    s32 primColour;
    s32 j;
    s32 index;
    { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = (((unsigned int) (((unsigned int)((6)) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((0x00)) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)((0)) & ((0x01 << (16)) - 1)) << (0)))); _g->words.w1 = (unsigned int)(&dMenuHudSettings); };
    { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = (((unsigned int) (((unsigned int)(7) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((2)) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)((2*8)) & ((0x01 << (16)) - 1)) << (0)))); _g->words.w1 = (unsigned int)((u32)(((char *)(&dMenuHudDrawModes[2])-0x80000000))); };
    i = 0;
    while (i < 4) {
        index = i << 2;
        temp_t3 = D_800E1DC8[index + 0];
        temp_t4 = D_800E1DC8[index + 1];
        temp_t5 = D_800E1DC8[index + 2];
        temp_ra = D_800E1DC8[index + 3];
        ulx = startX;
        y0Orig = startY;
        uly = y0Orig;
        switch (i) {
            case 0:
                primColour = colour0;
                recLrx = startX + width;
                recLry = y0Orig + 1;
                borderLineCount = borderHeight;
                break;
            case 1:
                ulx = (startX + (u32) width) - 1;
                primColour = colour1;
                uly = y0Orig + 1;
                recLrx = startX + width;
                recLry = (y0Orig + height) - 1;
                borderLineCount = borderWidth;
                break;
            case 2:
                primColour = colour2;
                uly = (y0Orig + height) - 1;
                recLrx = startX + width;
                recLry = y0Orig + height;
                borderLineCount = borderHeight;
                break;
            default:
                primColour = colour3;
                uly = y0Orig + 1;
                recLrx = startX + 1;
                recLry = (y0Orig + height) - 1;
                borderLineCount = borderWidth;
                break;
        }
        { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = (((unsigned int) (((unsigned int)(0xfa) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (0)))); _g->words.w1 = (((unsigned int) (((unsigned int)(primColour >> 24) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(primColour >> 16) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)(primColour >> 8) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(primColour) & ((0x01 << (8)) - 1)) << (0)))); };
        for (j = 0; j < borderLineCount; j++) {
            if (recLrx >= 0 && recLry >= 0) {
                if (ulx < 0) {
                    recUlx = 0;
                } else {
                    recUlx = ulx;
                }
                if (uly < 0) {
                    recUly = 0;
                } else {
                    recUly = uly;
                }
                { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = (((unsigned int) (((unsigned int)(0xf6) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((recLrx)) & ((0x01 << (10)) - 1)) << (14))) | ((unsigned int) (((unsigned int)((recLry)) & ((0x01 << (10)) - 1)) << (2)))); _g->words.w1 = (((unsigned int) (((unsigned int)((recUlx)) & ((0x01 << (10)) - 1)) << (14))) | ((unsigned int) (((unsigned int)((recUly)) & ((0x01 << (10)) - 1)) << (2))));};
            }
            ulx += temp_t3;
            uly += temp_t4;
            recLrx += temp_t5;
            recLry += temp_ra;
        }
        i++;
    }
    { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = ((unsigned int) (((unsigned int)(0xe7) & ((0x01 << (8)) - 1)) << (24))); _g->words.w1 = 0; };
    { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = (((unsigned int) (((unsigned int)(0xfa) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (0)))); _g->words.w1 = (((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (0)))); };
    rendermode_reset(dList);
}
void init_save_data(void) {
    s32 numLevels;
    s32 numWorlds;
    s32 i;
    s32 courseFlagsPtrSize;
    s32 index;
    s32 saveFileSize;
    s32 offset;
    level_count(&numLevels, &numWorlds);
    courseFlagsPtrSize = numLevels * sizeof(s32);
    saveFileSize = courseFlagsPtrSize;
    saveFileSize += numWorlds * sizeof(s16);
    saveFileSize += sizeof(Settings);
    saveFileSize = (saveFileSize + 3) & ~3;
    *gSavefileData = mempool_alloc_safe(saveFileSize * (s32)(sizeof(gSavefileData) / sizeof(gSavefileData[0])), 0xFFFFFFFF);
    for (index = 0, offset = 0; index < (s32)(sizeof(gSavefileData) / sizeof(gSavefileData[0])); index++) {
        gSavefileData[index] = (Settings *) ((u8 *) *gSavefileData + offset);
        gSavefileData[index]->courseFlagsPtr = (s32 *) ((u8 *) gSavefileData[index] + sizeof(Settings));
        gSavefileData[index]->balloonsPtr = (s16 *) ((u8 *) gSavefileData[index]->courseFlagsPtr + courseFlagsPtrSize);
        offset += saveFileSize;
    }
    gCheatsAssetData = (u16(*)[30]) get_misc_asset(ASSET_MISC_MAGIC_CODES);
    gNumberOfCheats = (*gCheatsAssetData)[0];
    gMenuText = mempool_alloc_safe(1280 * sizeof(char *), 0xFFFFFFFF);
    load_menu_text(LANGUAGE_ENGLISH);
    for (i = 0; i < (s32)(sizeof(gMenuAssets) / sizeof(gMenuAssets[0])); i++) { gMenuAssets[i] = 0;
    }
}
void reset_title_logo_scale(void) {
    gResetTitleScale = 1;
}
void menu_init(u32 menuId) {
    s32 i;
    gCurrentMenuId = menuId;
    reset_controller_sticks();
    gIgnorePlayerInputTime = 1;
    gOptionBlinkTimer = 0;
    sUnused_801263C8 = 0;
    sUnused_80126828 = 0;
    for (i = 0; i < (s32)(sizeof(gMenuSoundMasks) / sizeof(gMenuSoundMasks[0])); i++) { gMenuSoundMasks[i] = 0; }
    music_stop();
    switch (gCurrentMenuId) {
        case MENU_LOGOS:
            menu_logos_screen_init();
            break;
        case MENU_TITLE:
            menu_title_screen_init();
            break;
        case MENU_OPTIONS:
            menu_options_init();
            break;
        case MENU_AUDIO_OPTIONS:
            menu_audio_options_init();
            break;
        case MENU_SAVE_OPTIONS:
            menu_save_options_init();
            break;
        case MENU_MAGIC_CODES:
            menu_magic_codes_init();
            break;
        case MENU_MAGIC_CODES_LIST:
            menu_magic_codes_list_init();
            break;
        case MENU_CHARACTER_SELECT:
            menu_character_select_init();
            break;
        case MENU_GAME_SELECT:
            menu_game_select_init();
            break;
        case MENU_FILE_SELECT:
            menu_file_select_init();
            break;
        case MENU_TRACK_SELECT:
            menu_track_select_init();
            break;
        case MENU_TRACK_SELECT_ADVENTURE:
            menu_adventure_track_init();
            break;
        case MENU_RESULTS:
            menu_results_init();
            break;
        case MENU_TROPHY_RACE_ROUND:
            menu_trophy_race_round_init();
            break;
        case MENU_TROPHY_RACE_RANKINGS:
            menu_trophy_race_rankings_init();
            break;
        case MENU_NEWGAME_CINEMATIC:
            menu_cinematic_init();
            break;
        case MENU_GHOST_DATA:
            menu_ghost_data_init();
            break;
        case MENU_CREDITS:
            menu_credits_init();
            break;
        case MENU_BOOT:
            menu_boot_init();
            break;
        case MENU_CAUTION:
            menu_caution_init();
            break;
    }
    sUnused_80126470 = 0xD000;
}
s32 menu_loop(Gfx **currDisplayList, Mtx **currHudMat, Vertex **currHudVerts, Triangle **currHudTris, s32 updateRate) {
    s32 ret;
    sMenuCurrDisplayList = *currDisplayList;
    sMenuCurrHudMat = *currHudMat;
    sMenuCurrHudVerts = *currHudVerts;
    sMenuCurrHudTris = *currHudTris;
    update_controller_sticks();
    switch (gCurrentMenuId) {
        case MENU_LOGOS:
            ret = menu_logo_screen_loop(updateRate);
            break;
        case MENU_TITLE:
            ret = menu_title_screen_loop(updateRate);
            break;
        case MENU_OPTIONS:
            ret = menu_options_loop(updateRate);
            break;
        case MENU_AUDIO_OPTIONS:
            ret = menu_audio_options_loop(updateRate);
            break;
        case MENU_SAVE_OPTIONS:
            ret = menu_save_options_loop(updateRate);
            break;
        case MENU_MAGIC_CODES:
            ret = menu_magic_codes_loop(updateRate);
            break;
        case MENU_MAGIC_CODES_LIST:
            ret = menu_magic_codes_list_loop(updateRate);
            break;
        case MENU_CHARACTER_SELECT:
            ret = menu_character_select_loop(updateRate);
            break;
        case MENU_FILE_SELECT:
            ret = menu_file_select_loop(updateRate);
            break;
        case MENU_GAME_SELECT:
            ret = menu_game_select_loop(updateRate);
            break;
        case MENU_TRACK_SELECT:
            ret = menu_track_select_loop(updateRate);
            break;
        case MENU_TRACK_SELECT_ADVENTURE:
            ret = menu_adventure_track_loop(updateRate);
            break;
        case MENU_RESULTS:
            ret = menu_results_loop(updateRate);
            break;
        case MENU_TROPHY_RACE_ROUND:
            ret = menu_trophy_race_round_loop(updateRate);
            break;
        case MENU_TROPHY_RACE_RANKINGS:
            ret = menu_trophy_race_rankings_loop(updateRate);
            break;
        case MENU_NEWGAME_CINEMATIC:
            ret = menu_cinematic_loop(updateRate);
            break;
        case MENU_GHOST_DATA:
            ret = menu_ghost_data_loop(updateRate);
            break;
        case MENU_CREDITS:
            ret = menu_credits_loop(updateRate);
            break;
        case MENU_BOOT:
            ret = menu_boot_loop(updateRate);
            break;
        case MENU_CAUTION:
            ret = menu_caution_loop(updateRate);
            break;
    }
    *currDisplayList = sMenuCurrDisplayList;
    *currHudMat = sMenuCurrHudMat;
    *currHudVerts = sMenuCurrHudVerts;
    *currHudTris = sMenuCurrHudTris;
    return ret;
}
void menu_timestamp_render(s32 frameCount, s32 xPos, s32 yPos, u8 red, u8 green, u8 blue, u8 fontID) {
    s32 minutes;
    s32 seconds;
    s32 hundredths;
    s32 xOffset1;
    s32 imageIndex2;
    s32 imageIndex;
    s32 xOffset2;
    s32 xOffset3;
    sMenuGuiColourR = red;
    sMenuGuiColourG = green;
    sMenuGuiColourB = blue;
    if (fontID == ASSET_FONTS_FUNFONT) {
        gMenuImages[0].trans.y_position = yPos;
        gMenuImages[1].trans.y_position = yPos - 2;
        imageIndex = 0;
        imageIndex2 = 1;
        xPos -= 39;
        xOffset1 = 12;
        xOffset2 = 11;
        xOffset3 = 10;
    } else {
        gMenuImages[2].trans.y_position = yPos;
        gMenuImages[3].trans.y_position = yPos - 1;
        imageIndex = 2;
        imageIndex2 = 3;
        xPos -= 28;
        xOffset1 = 9;
        xOffset2 = 9;
        xOffset3 = 5;
    }
    get_timestamp_from_frames(frameCount, &minutes, &seconds, &hundredths);
    cam_set_sprite_anim_mode(SPRITE_ANIM_FRAME_INDEX);
    sprite_opaque(0);
    gMenuImages[imageIndex].spriteOffset = minutes / 10;
    gMenuImages[imageIndex].trans.x_position = xPos;
    menu_element_render(imageIndex);
    xPos += xOffset1;
    gMenuImages[imageIndex].spriteOffset = minutes % 10;
    gMenuImages[imageIndex].trans.x_position = xPos;
    menu_element_render(imageIndex);
    xPos += xOffset2;
    gMenuImages[imageIndex2].trans.x_position = xPos;
    menu_element_render(imageIndex2);
    xPos += xOffset3;
    gMenuImages[imageIndex].spriteOffset = seconds / 10;
    gMenuImages[imageIndex].trans.x_position = xPos;
    menu_element_render(imageIndex);
    xPos += xOffset1;
    gMenuImages[imageIndex].spriteOffset = seconds % 10;
    gMenuImages[imageIndex].trans.x_position = xPos;
    menu_element_render(imageIndex);
    xPos += xOffset2;
    gMenuImages[imageIndex2].trans.x_position = xPos;
    menu_element_render(imageIndex2);
    xPos += xOffset3;
    gMenuImages[imageIndex].spriteOffset = hundredths / 10;
    gMenuImages[imageIndex].trans.x_position = xPos;
    menu_element_render(imageIndex);
    xPos += xOffset1;
    gMenuImages[imageIndex].spriteOffset = hundredths % 10;
    gMenuImages[imageIndex].trans.x_position = xPos;
    menu_element_render(imageIndex);
    cam_set_sprite_anim_mode(SPRITE_ANIM_NORMALIZED);
    sprite_opaque(1);
    sMenuGuiColourR = 255;
    sMenuGuiColourG = 255;
    sMenuGuiColourB = 255;
}
void menu_number_render(s32 number, s32 x, s32 y, s32 r, s32 g, s32 b, s32 a, s32 font, s32 alignment) {
    s32 strLen;
    s32 powerOfTen;
    s32 i;
    s32 hasProcessedDigit;
    s32 curDigit;
    s32 pad[2];
    u8 digits[10];
    strLen = 0;
    powerOfTen = 1000000000;
    hasProcessedDigit = 0;
    while (powerOfTen >= 10) {
        if (number >= powerOfTen) {
            curDigit = number / powerOfTen;
            number -= curDigit * powerOfTen;
            digits[strLen++] = curDigit;
            hasProcessedDigit = 1;
        } else if (hasProcessedDigit) {
            digits[strLen++] = 0;
        }
        powerOfTen /= 10;
    }
    digits[strLen++] = number;
    if (alignment & HORZ_ALIGN_CENTER) {
        x -= strLen * 12;
        x += 6;
    } else if (alignment & HORZ_ALIGN_RIGHT) {
        x -= (strLen * 11) >> 1;
    } else {
        x += 6;
    }
    if (alignment & VERT_ALIGN_MIDDLE) {
        y += 7;
    } else if (alignment & 0x10) {
        y -= 7;
    }
    sMenuGuiColourR = r;
    sMenuGuiColourG = g;
    sMenuGuiColourB = b;
    sMenuGuiOpacity = a;
    sprite_opaque(0);
    cam_set_sprite_anim_mode(SPRITE_ANIM_FRAME_INDEX);
    if (powerOfTen && number) {}
    gMenuImages[0].trans.y_position = y;
    for (i = 0; i < strLen; i++) {
        gMenuImages[0].trans.x_position = x;
        gMenuImages[0].spriteOffset = digits[i];
        menu_element_render(0);
        x += 12;
    }
    sprite_opaque(1);
    cam_set_sprite_anim_mode(SPRITE_ANIM_NORMALIZED);
    sMenuGuiColourR = 255;
    sMenuGuiColourG = 255;
    sMenuGuiColourB = 255;
    sMenuGuiOpacity = 255;
}
void postrace_offsets(MenuElement *elements, f32 in, f32 mid, f32 out, s32 textOffset, s32 timestampOffset) {
    gTrophyRankingsMenuElements = elements;
    gPostraceState = POSTRACE_ENTER;
    gPostraceScaleIn = in * 60.0f;
    gPostraceScaleMiddle = mid * 60.0f;
    gPostraceScaleOut = out * 60.0f;
    gMenuElementScaleTimer = 0;
    gPostraceTextOffset = textOffset;
    gPostraceTimestampOffset = timestampOffset;
    if (gPostraceScaleIn > 0) {
        sound_play(SOUND_WHOOSH1, 0);
    }
}
s32 postrace_render(s32 updateRate) {
    f32 scale;
    s32 ret;
    s32 i;
    s32 buttonsPressedAllPlayers;
    ret = MENU_RESULT_FLAGS_1;
    scale = -1.0f;
    buttonsPressedAllPlayers = 0;
    if (gPostraceState != POSTRACE_SLIDE_END) {
        if (gIgnorePlayerInputTime == 0) {
            for (i = 0; i < gNumberOfActivePlayers; i++) {
                buttonsPressedAllPlayers |= input_pressed(i);
            }
        }
        gMenuElementScaleTimer += updateRate;
        do {
            switch (gPostraceState) {
                case POSTRACE_ENTER:
                    if (buttonsPressedAllPlayers & (0x8000 | 0x1000)) {
                        gMenuElementScaleTimer = 0;
                        gPostraceState = POSTRACE_HOLD;
                        buttonsPressedAllPlayers = 0;
                    } else {
                        if (gMenuElementScaleTimer >= gPostraceScaleIn) {
                            gMenuElementScaleTimer -= gPostraceScaleIn;
                            gPostraceState = POSTRACE_HOLD;
                        } else {
                            scale = (f32) gMenuElementScaleTimer / (f32) gPostraceScaleIn;
                        }
                    }
                    break;
                case POSTRACE_HOLD:
                    if (gPostraceScaleMiddle < 0) {
                        gMenuElementScaleTimer = 0;
                    }
                    if (buttonsPressedAllPlayers & (0x8000 | 0x1000)) {
                        gMenuElementScaleTimer = 0;
                        gPostraceState = POSTRACE_SLIDE_OUT;
                        buttonsPressedAllPlayers = 0;
                        if (gPostraceScaleOut > gMenuElementScaleTimer) {
                            sound_play(SOUND_WHOOSH1, 0);
                        }
                    } else {
                        if (gMenuElementScaleTimer >= gPostraceScaleMiddle) {
                            gMenuElementScaleTimer -= gPostraceScaleMiddle;
                            gPostraceState = POSTRACE_SLIDE_OUT;
                            if (gMenuElementScaleTimer < gPostraceScaleOut) {
                                sound_play(SOUND_WHOOSH1, 0);
                            }
                        } else {
                            scale = (f32) gMenuElementScaleTimer / (f32) gPostraceScaleMiddle;
                        }
                    }
                    break;
                case POSTRACE_SLIDE_OUT:
                    if ((buttonsPressedAllPlayers & (0x8000 | 0x1000)) ||
                        (gMenuElementScaleTimer >= gPostraceScaleOut)) {
                        gPostraceState = POSTRACE_SLIDE_END;
                    } else {
                        scale = (f32) gMenuElementScaleTimer / (f32) gPostraceScaleOut;
                    }
                    break;
            }
        } while (scale < 0.0f && gPostraceState != POSTRACE_SLIDE_END);
        if (gPostraceState != POSTRACE_SLIDE_END) {
            draw_menu_elements(gPostraceState, gTrophyRankingsMenuElements, scale);
            ret = MENU_RESULT_CONTINUE;
        }
    }
    return ret;
}
void draw_menu_elements(s32 state, MenuElement *elems, f32 scale) {
    s32 shouldResetRenderSettings;
    s32 xPos, yPos;
    shouldResetRenderSettings = 0;
    if (state == 4) {
        return;
    }
    mtx_ortho(&sMenuCurrDisplayList, &sMenuCurrHudMat);
    while (elems->t.element != 0) {
        if ((elems->t.element != &D_80126850)) {
            if (state == ((elems->t.element != (&D_80126850)) * 0)) {
                xPos = ((s32) ((elems->center - elems->left) * scale)) + elems->left;
                yPos = ((s32) ((elems->middle - elems->top) * scale)) + elems->top;
            } else if (state == 1) {
                xPos = elems->center;
                yPos = elems->middle;
            } else {
                xPos = ((s32) ((elems->right - elems->center) * scale)) + elems->center;
                yPos = ((s32) ((elems->bottom - elems->middle) * scale)) + elems->middle;
            }
            switch (elems->elementType) {
                case 0:
                    set_text_background_colour(
                        elems->details.background.backgroundRed, elems->details.background.backgroundGreen,
                        elems->details.background.backgroundBlue, elems->details.background.backgroundAlpha);
                    set_text_colour(elems->filterRed, elems->filterGreen, elems->filterBlue, elems->filterBlendFactor,
                                    elems->opacity);
                    set_text_font(elems->textFont);
                    draw_text(&sMenuCurrDisplayList, xPos, yPos + gPostraceTextOffset, elems->t.asciiText,
                              elems->textAlignFlags);
                    break;
                case 1:
                    if (shouldResetRenderSettings) {
                        shouldResetRenderSettings = 0;
                        rendermode_reset(&sMenuCurrDisplayList);
                    }
                    sMenuGuiOpacity = elems->opacity;
                    menu_timestamp_render(*elems->t.numberU16, xPos - (320 / 2),
                                          (-yPos - gPostraceTimestampOffset) + (240 / 2), elems->filterRed,
                                          elems->filterGreen, elems->filterBlue, elems->textFont);
                    break;
                case 2:
                    if (shouldResetRenderSettings) {
                        shouldResetRenderSettings = 0;
                        rendermode_reset(&sMenuCurrDisplayList);
                    }
                    menu_number_render(*elems->t.number, xPos - (320 / 2),
                                       (-yPos - gPostraceTimestampOffset) + (240 / 2), elems->filterRed,
                                       elems->filterGreen, elems->filterBlue, elems->opacity, elems->textFont,
                                       elems->textAlignFlags);
                    break;
                case 3:
                    texrect_draw(&sMenuCurrDisplayList, elems->t.drawTexture, xPos, yPos + gPostraceTextOffset,
                                 elems->filterRed, elems->filterGreen, elems->filterBlue, elems->opacity);
                    shouldResetRenderSettings = 1;
                    break;
                case 4:
                    texrect_draw_scaled(&sMenuCurrDisplayList, elems->t.element, xPos, yPos + gPostraceTextOffset,
                                        elems->details.texture.width / 256.0f, elems->details.texture.height / 256.0f,
                                        (elems->filterRed << 24) | (elems->filterGreen << 16) |
                                            (elems->filterBlue << 8) | elems->opacity,
                                        elems->textAlignFlags);
                    shouldResetRenderSettings = 1;
                    break;
                case 5:
                    if (shouldResetRenderSettings) {
                        shouldResetRenderSettings = 0;
                        rendermode_reset(&sMenuCurrDisplayList);
                    }
                    cam_set_sprite_anim_mode(SPRITE_ANIM_FRAME_INDEX);
                    sprite_opaque(0);
                    gMenuImages[elems->t.assetID].trans.x_position = xPos - (320 / 2);
                    gMenuImages[elems->t.assetID].trans.y_position =
                        (-yPos - gPostraceTimestampOffset) + (240 / 2);
                    gMenuImages[elems->t.assetID].spriteOffset = elems->textFont;
                    gMenuImages[elems->t.assetID].trans.rotation.z = elems->details.background.backgroundRed;
                    gMenuImages[elems->t.assetID].trans.rotation.y = elems->details.background.backgroundGreen;
                    gMenuImages[elems->t.assetID].trans.rotation.x = elems->details.background.backgroundBlue;
                    gMenuImages[elems->t.assetID].trans.scale = elems->details.background.backgroundAlpha / 256.0f;
                    sMenuGuiColourR = elems->filterRed;
                    sMenuGuiColourG = elems->filterGreen;
                    sMenuGuiColourB = elems->filterBlue;
                    sMenuGuiColourBlendFactor = elems->filterBlendFactor;
                    sMenuGuiOpacity = elems->opacity;
                    menu_element_render(elems->t.assetID);
                    cam_set_sprite_anim_mode(SPRITE_ANIM_NORMALIZED);
                    sprite_opaque(1);
                    break;
                case 6:
                    func_80080E90(&sMenuCurrDisplayList, xPos, yPos + gPostraceTimestampOffset,
                                  elems->details.texture.width, elems->details.texture.height,
                                  elems->details.texture.borderWidth, elems->details.texture.borderHeight,
                                  elems->filterRed, elems->filterGreen, elems->filterBlue, elems->opacity);
                    break;
                case 7:
                    func_80080580(&sMenuCurrDisplayList, xPos, yPos + gPostraceTimestampOffset,
                                  elems->details.texture.width, elems->details.texture.height,
                                  elems->details.texture.borderWidth, elems->details.texture.borderHeight,
                                  (elems->filterRed << 24) | (elems->filterGreen << 16) | (elems->filterBlue << 8) |
                                      elems->opacity,
                                  elems->t.element);
                    break;
            }
        }
        elems++;
    }
    if (shouldResetRenderSettings) {
        rendermode_reset(&sMenuCurrDisplayList);
    }
    sMenuGuiColourR = 255;
    sMenuGuiColourG = 255;
    sMenuGuiColourB = 255;
    sMenuGuiColourBlendFactor = 0;
    sMenuGuiOpacity = 255;
}
void trackmenu_set_records(void) {
    s32 i;
    s32 numWorlds;
    s32 numLevels;
    Settings *settings;
    settings = get_settings();
    level_count(&numLevels, &numWorlds);
    for (i = 0; i < numLevels; i++) {
        settings->courseFlagsPtr[i] = RACE_UNATTEMPTED;
        for (numWorlds = 0; numWorlds < 3; numWorlds++) {
            settings->courseFlagsPtr[i] |= gSavefileData[numWorlds]->courseFlagsPtr[i];
        }
    }
    settings->trophies = 0;
    settings->keys = 0;
    settings->bosses = 0;
    settings->cutsceneFlags = 0;
    for (i = 0; i < 3; i++) {
        settings->trophies |= gSavefileData[i]->trophies;
        settings->keys |= gSavefileData[i]->keys;
        settings->bosses |= gSavefileData[i]->bosses;
        settings->cutsceneFlags |= gSavefileData[i]->cutsceneFlags;
    }
}
void menu_missing_controller(Gfx **dList, s32 updateRate) {
    s32 posY;
    gMissingControllerDelay += updateRate;
    if (gMissingControllerDelay & 0x10) {
        load_menu_text(get_language());
        set_text_font(ASSET_FONTS_FUNFONT);
        set_text_colour(255, 255, 255, 0, 0xFF);
        set_text_background_colour(0, 0, 0, 0);
        posY = 208;
        if (osTvType == 0) {
            posY = 234;
        }
        draw_text(dList, -0x8000, posY, gMenuText[ASSET_MENU_TEXT_CONTROLLERNOTCONNECTED], ALIGN_MIDDLE_CENTER);
    }
}
void menu_logos_screen_init(void) {
    gMenuDelay = 0;
    sBootScreenTimer = 16.0f;
    bgdraw_fillcolour(0, 0, 0);
    if (osTvType == 0) {
        viewport_menu_set(0, 0, 38, 320, 240 - 16);
        set_viewport_properties(0, 0x8000, 0x8000, 320, (240 + 44));
    } else {
        viewport_menu_set(0, 0, 40, 320, 240 - 44);
        set_viewport_properties(0, 0x8000, 0x8000, 320, 240);
    }
    copy_viewports_to_stack();
    camEnableUserView(0, 1);
}
s32 menu_logo_screen_loop(s32 updateRate) {
    s32 opacity;
    s32 yOffset;
    s32 yOffsetShadow;
    if (osTvType == 0) {
        yOffset = 26;
        if (sBootScreenTimer < 2.6f && gMenuDelay == 0) {
            transition_begin(&gFadeLogoToTitleScreen);
            gMenuDelay = 1;
        }
        sBootScreenTimer -= updateRate / 50.0f;
    } else {
        yOffset = 0;
        if (sBootScreenTimer < 2.17f && gMenuDelay == 0) {
            transition_begin(&gFadeLogoToTitleScreen);
            gMenuDelay = 1;
        }
        sBootScreenTimer -= updateRate / 60.0f;
    }
    if (sBootScreenTimer <= 0.0f) {
        camDisableUserView(0, 0);
        set_viewport_properties(0, 0x8000, 0x8000, 0x8000, 0x8000);
        init_title_screen_variables();
        menu_init(MENU_TITLE);
    }
    if (sBootScreenTimer < 8.5) {
        set_text_font(ASSET_FONTS_SMALLFONT);
        set_text_background_colour(0, 0, 0, 0);
        if ((sBootScreenTimer < 8.0) && (sBootScreenTimer >= 7.5)) {
            opacity = (8.0 - sBootScreenTimer) * 510.0;
        } else {
            if ((sBootScreenTimer < 7.5) && (sBootScreenTimer >= 7.0)) {
                opacity = (sBootScreenTimer - 7.0) * 510.0;
            } else {
                opacity = 0;
            }
        }
        if (opacity != 0) {
            set_text_colour(255, 255, 0, 255, opacity);
            draw_text(&sMenuCurrDisplayList, 159, yOffset + 212, gRareCopyrightString, ALIGN_MIDDLE_CENTER);
            draw_text(&sMenuCurrDisplayList, 161, yOffset + 212, gRareCopyrightString, ALIGN_MIDDLE_CENTER);
            draw_text(&sMenuCurrDisplayList, -0x8000, yOffset + 211, gRareCopyrightString, ALIGN_MIDDLE_CENTER);
            draw_text(&sMenuCurrDisplayList, -0x8000, yOffset + 213, gRareCopyrightString, ALIGN_MIDDLE_CENTER);
        }
        yOffsetShadow = yOffset + 212;
        if (sBootScreenTimer > 8.0) {
            opacity = (8.5 - sBootScreenTimer) * 510.0;
        } else {
            opacity = 0xFF;
        }
        set_text_colour(0xFF, 0xFF, 0xFF, 0xFF, opacity);
        draw_text(&sMenuCurrDisplayList, -0x8000, yOffsetShadow, gRareCopyrightString, ALIGN_MIDDLE_CENTER);
    }
    return MENU_RESULT_CONTINUE;
}
void init_title_screen_variables(void) {
    if (sEepromSettings & 2) {
        set_magic_code_flags(CHEAT_CONTROL_DRUMSTICK);
    }
    if ((sEepromSettings & 0xFFFFF0) == 0xFFFFF0) {
        set_magic_code_flags(CHEAT_CONTROL_TT);
    }
    if (sEepromSettings & 1) {
        gIsInAdventureTwo = 1;
    } else {
        gIsInAdventureTwo = 0;
    }
    if ((sEepromSettings & 0x2000000) == 0) {
        set_subtitles(0);
    }
    load_menu_text(get_language());
}
void func_80083098(f32 updateRateF) {
    f32 temp;
    f32 temp2;
    s32 didUpdate;
    s32 xPos;
    s32 yPos;
    s32 i;
    s32 j;
    char *text;
    unk800DF83C *introCharData;
    didUpdate = 0;
    xPos = 0;
    yPos = 0;
    text = 0;
    if (gOpeningNameID >= 10) {
        return;
    }
    introCharData = &gTitleCinematicText[gOpeningNameID];
    D_801268D8 += updateRateF;
    set_text_font(ASSET_FONTS_BIGFONT);
    set_text_background_colour(0, 0, 0, 0);
    i = 0;
    while (i < gTitleCinematicTextColourCount) {
        j = 5 * D_80126878[i].colourIndex;
        set_text_colour(gTitleCinematicTextColours[j + 0], gTitleCinematicTextColours[j + 1],
                        gTitleCinematicTextColours[j + 2], gTitleCinematicTextColours[j + 3],
                        gTitleCinematicTextColours[j + 4]);
        draw_text(&sMenuCurrDisplayList, D_80126878[i].x, D_80126878[i].y, D_80126878[i].text, ALIGN_MIDDLE_CENTER);
        D_80126878[i].colourIndex++;
        if (D_80126878[i].colourIndex >= 4) {
            gTitleCinematicTextColourCount--;
            for (j = i; j < gTitleCinematicTextColourCount; j++) {
                D_80126878[j].text = D_80126878[j + 1].text;
                D_80126878[j].x = D_80126878[j + 1].x;
                D_80126878[j].y = D_80126878[j + 1].y;
                D_80126878[j].colourIndex = D_80126878[j + 1].colourIndex;
            }
        } else {
            i++;
        }
    }
    if (introCharData->unk4 <= D_801268D8) {
        if (D_801268D8 < introCharData->unk8) {
            temp = (D_801268D8 - introCharData->unk4);
            temp2 = (introCharData->unk8 - introCharData->unk4);
            xPos = (introCharData->unk14 + (((introCharData->unk1C - introCharData->unk14) * temp) / temp2));
            yPos = (introCharData->unk18 + (((introCharData->unk20 - introCharData->unk18) * temp) / temp2));
            text = introCharData->unk0;
            didUpdate = 1;
        } else if (D_801268D8 <= introCharData->unkC) {
            xPos = introCharData->unk1C;
            yPos = introCharData->unk20;
            text = introCharData->unk0;
            didUpdate = 1;
        } else if (D_801268D8 < introCharData->unk10) {
            temp = (D_801268D8 - introCharData->unkC);
            temp2 = (introCharData->unk10 - introCharData->unkC);
            xPos = (introCharData->unk1C + (((introCharData->unk24 - introCharData->unk1C) * temp) / temp2));
            yPos = (introCharData->unk20 + (((introCharData->unk28 - introCharData->unk20) * temp) / temp2));
            text = introCharData->unk0;
            didUpdate = 1;
        } else {
            gOpeningNameID++;
        }
    }
    if (!didUpdate) {
        return;
    }
    if (gTitleCinematicTextColourCount < 4) {
        D_80126878[gTitleCinematicTextColourCount].colourIndex = 0;
        D_80126878[gTitleCinematicTextColourCount].text = text;
        D_80126878[gTitleCinematicTextColourCount].x = xPos;
        D_80126878[gTitleCinematicTextColourCount].y = yPos;
        gTitleCinematicTextColourCount++;
    }
    set_text_colour(255, 255, 255, 0, 255);
    draw_text(&sMenuCurrDisplayList, xPos, yPos, text, ALIGN_MIDDLE_CENTER);
}
void menu_title_screen_init(void) {
    s32 i;
    s32 numberOfPlayers;
    gTitleScreenLoaded = 1;
    gOptionBlinkTimer = 0;
    gMenuDelay = 0;
    reset_character_id_slots();
    gSaveFileIndex = 0;
    gTitleScreenCurrentOption = 0;
    gNumberOfActivePlayers = 4;
    input_assign_players();
    music_play(SEQUENCE_NONE2);
    sMenuMusicVolume = music_volume();
    if (gResetTitleScale) {
        gTitleRevealTimer = 0;
        gResetTitleScale = 0;
    } else {
        gTitleRevealTimer = 1;
    }
    gTitleAudioCounter = 0;
    gMenuStage = TITLESCREEN_START;
    menu_assetgroup_load(sGameTitleTileTextures);
    for (i = 0; i < (s32)(sizeof(sGameTitleTileOffsets) / sizeof(sGameTitleTileOffsets[0])) - 1; i++) {
        sGameTitleTileOffsets[i].texture = gMenuAssets[sGameTitleTileTextures[i]];
    }
    music_voicelimit_set(27);
    cam_shake_off();
    set_text_font(ASSET_FONTS_FUNFONT);
    load_font(ASSET_FONTS_BIGFONT);
    sound_volume_reset(0);
    set_time_trial_enabled(0);
    gTitleDemoIndex = 0;
    sTitleScreenDemoIds = (s8 *) get_misc_asset(ASSET_MISC_TITLE_SCREEN_DEMO_IDS);
    numberOfPlayers = sTitleScreenDemoIds[DEMO_PLAYER_COUNT];
    gTitleDemoTimer = 0;
    if (numberOfPlayers == -2) {
        numberOfPlayers = 0;
        gTitleDemoTimer = 600;
    }
    load_level_for_menu(sTitleScreenDemoIds[DEMO_LEVEL_ID], numberOfPlayers, sTitleScreenDemoIds[DEMO_CUTSCENE_ID]);
    D_801268D8 = 0;
    gOpeningNameID = 0;
    D_801268DC = 0;
    gTitleCinematicTextColourCount = 0;
    gOpacityDecayTimer = 0;
    gIsInTracksMode = 0;
}
void render_title_screen( s32 updateRate, f32 updateRateF) {
    u32 foo[2];
    s32 alpha;
    f32 scale;
    s32 i;
    s32 posY;
    if (gTitleRevealTimer) {
        mtx_ortho(&sMenuCurrDisplayList, &sMenuCurrHudMat);
        scale = (f32) gTitleRevealTimer * (1.0f / 32.0f);
        sMenuGuiOpacity = (gTitleRevealTimer * 8) - 1;
        cam_set_sprite_anim_mode(SPRITE_ANIM_NORMALIZED);
        if (scale != 1.0f) {
            texrect_draw_scaled(&sMenuCurrDisplayList, sGameTitleTileOffsets, ((float)320 / 2), 52.0f, scale,
                                scale, ((u32)((255 << 24) | (255 << 16) | (255 << 8) | 254)), TEXRECT_POINT);
        } else {
            texrect_draw(&sMenuCurrDisplayList, sGameTitleTileOffsets, (320 / 2), 52, 255, 255, 255, 255);
        }
        if (!is_controller_missing()) {
            i = 0;
            posY = (osTvType == 0) ? 240 - 22 : 240 - 48;
            set_text_font(ASSET_FONTS_FUNFONT);
            set_text_background_colour(0, 0, 0, 0);
            while (gTitleMenuStrings[i] != 0) {
                if (i == gTitleScreenCurrentOption) {
                    alpha = (gOptionBlinkTimer & 0x1F) << 4;
                    if (alpha > 255) {
                        alpha = 511 - alpha;
                    }
                } else {
                    alpha = 0;
                }
                set_text_colour(255, 255, 255, alpha, sMenuGuiOpacity);
                draw_text(&sMenuCurrDisplayList, -0x8000, posY, gTitleMenuStrings[i], ALIGN_MIDDLE_CENTER);
                posY += 16;
                i++;
            }
        }
    } else if (sTitleScreenDemoIds[gTitleDemoIndex] == sTitleScreenDemoIds[0]) {
        func_80083098(updateRateF);
    }
}
s32 menu_title_screen_loop(s32 updateRate) {
    s32 temp_v0_5;
    s32 sp28;
    s8 *demo;
    s32 contrIndex;
    f32 updateRateF;
    Camera *sp18;
    s8 playerCount;
    sp18 = cam_get_active_camera();
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    menu_input();
    if (osTvType == 0) {
        updateRateF = (f32) updateRate / 50.0f;
    } else {
        updateRateF = (f32) updateRate / 60.0f;
    }
    if (gMenuDelay < 20) {
        render_title_screen(updateRate, updateRateF);
    }
    if (gMenuDelay) {
        gMenuDelay += updateRate;
    }
    if (sTitleScreenDemoIds[gTitleDemoIndex] == sTitleScreenDemoIds[0]) {
        gOpacityDecayTimer += updateRate;
    }
    sp28 = 0;
    if (gTitleDemoTimer > 0) {
        gTitleDemoTimer -= updateRate;
        if (gTitleDemoTimer < 60 && gTitleDemoTimer + updateRate >= 60) {
            music_fade(-768);
            sp28 = 0;
            transition_begin(&gFadeTitleScreenDemo);
        }
        if (gTitleDemoTimer <= 0) {
            sp28 = 1;
        }
    } else {
        gTitleDemoTimer = 0;
    }
    if (gMenuDelay == 0 && (func_800214C4() || sp28)) {
        if (gTitleDemoTimer) {}
        gTitleDemoIndex += DEMO_INDEX_SIZE;
        demo = &sTitleScreenDemoIds[gTitleDemoIndex];
        if (demo[0] == -1) {
            gTitleDemoIndex = 0;
            demo = &sTitleScreenDemoIds[gTitleDemoIndex];
        }
        if (gTitleRevealTimer == 0) {
            gTitleRevealTimer = 1;
        }
        playerCount = demo[DEMO_PLAYER_COUNT];
        gTitleDemoTimer = 0;
        if (playerCount == -2) {
            playerCount = 0;
            gTitleDemoTimer = 1500;
        }
        load_level_for_menu(demo[DEMO_LEVEL_ID], playerCount, demo[DEMO_CUTSCENE_ID]);
        if (sTitleScreenDemoIds[gTitleDemoIndex] == sTitleScreenDemoIds[DEMO_LEVEL_ID]) {
            D_801268D8 = 0.0f;
            gOpeningNameID = 0;
            D_801268DC = 0;
            gTitleCinematicTextColourCount = 0;
            gOpacityDecayTimer = 0;
        }
    }
    if (gTitleRevealTimer) {
        if (gTitleRevealTimer < 32) {
            if (gTitleRevealTimer == 1) {
                sound_play(SOUND_WHOOSH1, 0);
            }
            gTitleRevealTimer += updateRate;
            if (gTitleRevealTimer >= 32) {
                gTitleRevealTimer = 32;
                sp18->shakeMagnitude = 8.0f;
                sound_play(SOUND_EXPLOSION, 0);
            }
        } else {
            if (gTitleAudioCounter < 6.0f) {
                gTitleAudioCounter += updateRateF;
                if (gTitleAudioCounter > 0.67f && gMenuStage == TITLESCREEN_START) {
                    sound_play(SOUND_VOICE_TT_DIDDY_KONG_RACING, 0);
                    gMenuStage = TITLESCREEN_NAME;
                } else if (gTitleAudioCounter > 2.83f && gMenuStage == TITLESCREEN_NAME) {
                    sound_play(SOUND_VOICE_TT_PRESS_START, 0);
                    gMenuStage = TITLESCREEN_PRESS_START;
                }
            }
        }
    }
    if (gTitleAudioCounter > 0.0f) {
        if (gTitleAudioCounter < 0.5f) {
            music_volume_set((s32) ((f32) sMenuMusicVolume * (1.0f - gTitleAudioCounter)));
        } else if (gTitleAudioCounter < 4.5f) {
            music_volume_set(((s32) sMenuMusicVolume >> 1));
        } else if (gTitleAudioCounter < 5.0f) {
            music_volume_set((s32) ((f32) sMenuMusicVolume * (gTitleAudioCounter - 4.0f)));
        } else {
            music_volume_set(*((s8 *) &sMenuMusicVolume + 3));
        }
    }
    if (gTitleRevealTimer == 0) {
        if (gMenuButtons[4] & (0x8000 | 0x1000)) {
            gTitleRevealTimer = 1;
        }
    } else if ((gMenuDelay == 0) && !is_controller_missing()) {
        s32 temp0 = gTitleScreenCurrentOption;
        if (gMenuStickY[4] < 0 && gTitleScreenCurrentOption < 1) {
            gTitleScreenCurrentOption++;
        }
        if (gMenuStickY[4] > 0 && gTitleScreenCurrentOption > 0) {
            gTitleScreenCurrentOption--;
        }
        if (temp0 != gTitleScreenCurrentOption) {
            sound_play(SOUND_MENU_PICK2,
                       (SoundHandle *) (s32 *) (0 * contrIndex));
        }
        if (gMenuButtons[4] & (0x8000 | 0x1000)) {
            for (contrIndex = 3; contrIndex > 0 && !(gMenuButtons[contrIndex] & (0x8000 | 0x1000));
                 contrIndex--) {}
            titlescreen_controller_assign(contrIndex);
            gMenuDelay = 1;
            transition_begin(&sMenuTransitionFadeIn);
            enable_new_screen_transitions();
            sound_play(SOUND_SELECT2, 0);
        }
    }
    if (gMenuDelay > 30) {
        titlescreen_free();
        disable_new_screen_transitions();
        if (gTitleScreenCurrentOption == 0) {
            sp28 = 0;
            if (is_drumstick_unlocked()) {
                sp28 = 1;
            }
            if (is_tt_unlocked()) {
                sp28 ^= 3;
            }
            load_level_for_menu(ASSET_LEVEL_CHARACTERSELECT, -1, sp28);
            charselect_prev(0, 0);
            menu_init(MENU_CHARACTER_SELECT);
            return MENU_RESULT_CONTINUE;
        }
        gMenuCurIndex = 0;
        load_level_for_menu(ASSET_LEVEL_OPTIONSBACKGROUND, -1, 0);
        menu_init(MENU_OPTIONS);
        return MENU_RESULT_CONTINUE;
    }
    gIgnorePlayerInputTime = 0;
    return MENU_RESULT_CONTINUE;
}
void titlescreen_free(void) {
    menu_assetgroup_free(sGameTitleTileTextures);
    music_voicelimit_set(16);
    cam_shake_on();
    unload_font(ASSET_FONTS_BIGFONT);
    sound_volume_reset(1);
}
void menu_options_init(void) {
    gOptionBlinkTimer = 0;
    gMenuDelay = 0;
    transition_begin(&sMenuTransitionFadeOut);
    load_font(ASSET_FONTS_BIGFONT);
    set_text_font(ASSET_FONTS_BIGFONT);
    music_voicelimit_set(24);
    music_play(SEQUENCE_MAIN_MENU);
    music_change_off();
}
void optionscreen_render( s32 updateRate) {
    s32 optionMenuTextIndex;
    s32 highlight;
    s32 yPos;
    set_text_font(ASSET_FONTS_BIGFONT);
    set_text_background_colour(0, 0, 0, 0);
    set_text_colour(0, 0, 0, 255, 128);
    draw_text(&sMenuCurrDisplayList, (320 / 2) + 1, 35, gMenuText[ASSET_MENU_TEXT_OPTIONS],
              ALIGN_MIDDLE_CENTER);
    set_text_colour(255, 255, 255, 0, 255);
    draw_text(&sMenuCurrDisplayList, (320 / 2), 32, gMenuText[ASSET_MENU_TEXT_OPTIONS],
              ALIGN_MIDDLE_CENTER);
    optionMenuTextIndex = 0;
    yPos = 76;
    set_text_font(ASSET_FONTS_FUNFONT);
    while (gOptionMenuStrings[optionMenuTextIndex] != 0) {
        if (optionMenuTextIndex == gMenuCurIndex) {
            highlight = gOptionBlinkTimer * 8;
            if (gOptionBlinkTimer >= 32) {
                highlight = 511 - highlight;
            }
        } else {
            highlight = 0;
        }
        set_text_colour(255, 255, 255, highlight, 255);
        draw_text(&sMenuCurrDisplayList, -0x8000, yPos, gOptionMenuStrings[optionMenuTextIndex],
                  ALIGN_MIDDLE_CENTER);
        optionMenuTextIndex++;
        yPos += 28;
    }
}
s32 menu_options_loop(s32 updateRate) {
    s32 buttonsPressed;
    s32 i;
    s32 pad0;
    s32 analogueX;
    s32 analogueY;
    s32 pad1;
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    if (gMenuDelay != 0) {
        if (gMenuDelay > 0) {
            gMenuDelay += updateRate;
        } else {
            gMenuDelay -= updateRate;
        }
    }
    if (gMenuDelay > -20 && gMenuDelay < 35) {
        optionscreen_render(updateRate);
    }
    buttonsPressed = 0;
    analogueX = 0;
    analogueY = 0;
    if (gIgnorePlayerInputTime == 0 && gMenuDelay == 0) {
        for (i = 0; i < 4; i++) {
            buttonsPressed |= input_pressed(i);
            analogueX += gControllersXAxisDirection[i];
            analogueY += gControllersYAxisDirection[i];
        }
    }
    if ((buttonsPressed & 0x4000) || ((buttonsPressed & (0x8000 | 0x1000)) && gMenuCurIndex == 5)) {
        music_fade(-128);
        gMenuDelay = -1;
        transition_begin(&sMenuTransitionFadeIn);
        sound_play(SOUND_MENU_BACK3, 0);
    } else if ((buttonsPressed & (0x8000 | 0x1000)) && gMenuCurIndex >= 2) {
        gMenuDelay = 31;
        sound_play(SOUND_SELECT2, 0);
    } else if (gMenuCurIndex == 0 && analogueX != 0) {
        s32 langVal = get_language();
        switch ((u64) langVal) {
            case LANGUAGE_ENGLISH:
                set_language(LANGUAGE_FRENCH);
                break;
            default:
                set_language(LANGUAGE_ENGLISH);
                break;
        }
        sound_play(SOUND_MENU_PICK2, 0);
    } else if (gMenuCurIndex == 1 && analogueX != 0) {
        if (sEepromSettings & 0x2000000) {
            sound_play(SOUND_MENU_PICK2, 0);
            unset_eeprom_settings_value(0x2000000);
            set_subtitles(0);
            gOptionMenuStrings[1] = gMenuText[ASSET_MENU_TEXT_SUBTITLESOFF];
        } else {
            sound_play(SOUND_MENU_PICK2, 0);
            set_eeprom_settings_value(0x2000000);
            set_subtitles(1);
            gOptionMenuStrings[1] = gMenuText[ASSET_MENU_TEXT_SUBTITLESON];
        }
    } else {
        s32 prevOption = gMenuCurIndex;
        if (analogueY < 0) {
            gMenuCurIndex++;
            if (gMenuCurIndex >= 6) {
                gMenuCurIndex = 5;
            }
        }
        if (analogueY > 0) {
            gMenuCurIndex--;
            if (gMenuCurIndex < 0) {
                gMenuCurIndex = 0;
            }
        }
        if (prevOption != gMenuCurIndex) {
            sound_play(SOUND_MENU_PICK2, 0);
        }
    }
    if (gMenuDelay > 30) {
        if (gMenuCurIndex == 2) {
            optionscreen_free();
            menu_init(MENU_AUDIO_OPTIONS);
            return MENU_RESULT_CONTINUE;
        }
        if (gMenuCurIndex == 3) {
            optionscreen_free();
            menu_init(MENU_SAVE_OPTIONS);
            return MENU_RESULT_CONTINUE;
        }
        optionscreen_free();
        menu_init(MENU_MAGIC_CODES);
        return MENU_RESULT_CONTINUE;
    }
    if (gMenuDelay < -30) {
        music_change_on();
        optionscreen_free();
        menu_init(MENU_TITLE);
        return MENU_RESULT_CONTINUE;
    }
    gIgnorePlayerInputTime = 0;
    return MENU_RESULT_CONTINUE;
}
void optionscreen_free(void) {
    unload_font(ASSET_FONTS_BIGFONT);
}
void menu_audio_options_init(void) {
    gOptionsMenuItemIndex = 0;
    gOptionBlinkTimer = 0;
    gMenuDelay = 0;
    gSoundOptionMask = 0;
    gOpacityDecayTimer = -1;
    menu_assetgroup_load(gOptionMenuTextures);
    menu_imagegroup_load(gOptionMenuImageIndices);
    menu_init_arrow_textures();
    transition_begin(&sMenuTransitionFadeOut);
    func_8007FFEC(2);
    gMusicVolumeSliderValue = music_volume_config();
    gSfxVolumeSliderValue = sndp_get_global_volume();
    if (gActiveMagicCodes & CHEAT_MUSIC_MENU) {
        gAudioMenuStrings[6].text = gMusicTestString;
        gAudioMenuStrings[3].y = 212;
        music_voicelimit_set(32);
        gMenuStage = 5;
    } else {
        gAudioMenuStrings[6].text = 0;
        gAudioMenuStrings[3].y = 192;
        gMenuStage = 4;
    }
    load_font(ASSET_FONTS_BIGFONT);
}
void func_80084854( s32 updateRate) {
    s32 i;
    s32 yOffset;
    s32 j;
    s32 temp;
    temp = gMusicTestSongIndex;
    for (i = 0; (gMusicTestString[i] < '0') || (gMusicTestString[i] > '9'); i++) {}
    j = temp / 10;
    gMusicTestString[i] = '0' + j;
    temp -= (j * 10);
    i++;
    gMusicTestString[i] = '0' + temp;
    temp = gOptionBlinkTimer * 8;
    if (temp >= 256) {
        temp = 511 - temp;
    }
    gAudioMenuStrings[0].text = gAudioOutputStrings[gAudioOutputType];
    mtx_ortho(&sMenuCurrDisplayList, &sMenuCurrHudMat);
    if (osTvType == 0) {
        yOffset = 101;
    } else {
        yOffset = 113;
    }
    func_80080580(0, -72, 120 - yOffset, 144, 14, 6, 4, ((u32)((255 << 24) | (192 << 16) | (64 << 8) | 255)),
                  (TextureHeader *) gMenuAssets[TEXTURE_UNK_44]);
    func_80080580(0, -72, 80 - yOffset, 144, 14, 6, 4, ((u32)((255 << 24) | (192 << 16) | (64 << 8) | 255)),
                  (TextureHeader *) gMenuAssets[TEXTURE_UNK_44]);
    func_80080BC8(&sMenuCurrDisplayList);
    dialogue_clear(7);
    set_current_dialogue_background_colour(7, 0, 0, 0, 255);
    set_current_dialogue_box_coords(7, 94, 117, 226, 123);
    render_dialogue_box(&sMenuCurrDisplayList, 0, 0, 7);
    set_current_dialogue_box_coords(7, 94, 157, 226, 163);
    render_dialogue_box(&sMenuCurrDisplayList, 0, 0, 7);
    texrect_draw(&sMenuCurrDisplayList, gMenuSelectionArrowLeft, (gSfxVolumeSliderValue >> 1) + 96, 120, 255, 255, 255,
                 255);
    texrect_draw(&sMenuCurrDisplayList, gMenuSelectionArrowLeft, (gMusicVolumeSliderValue >> 1) + 96, 160, 255, 255,
                 255, 255);
    rendermode_reset(&sMenuCurrDisplayList);
    set_text_background_colour(0, 0, 0, 0);
    j = 0;
    if (gMenuStage < 5) {
        i = gOptionsMenuItemIndex;
    } else if (gOptionsMenuItemIndex < 3) {
        i = gOptionsMenuItemIndex;
    } else if (gOptionsMenuItemIndex == 3) {
        i = 6;
    } else {
        i = 3;
    }
    for (; gAudioMenuStrings[j].text != 0; j++) {
        set_text_font(gAudioMenuStrings[j].font);
        if (j == i) {
            set_text_colour(255, 255, 255, temp, 255);
        } else {
            set_text_colour(gAudioMenuStrings[j].red, gAudioMenuStrings[j].green, gAudioMenuStrings[j].blue,
                            gAudioMenuStrings[j].alpha, gAudioMenuStrings[j].opacity);
        }
        draw_text(&sMenuCurrDisplayList, gAudioMenuStrings[j].x, gAudioMenuStrings[j].y, gAudioMenuStrings[j].text,
                  gAudioMenuStrings[j].alignmentFlags);
    }
}
s32 menu_audio_options_loop(s32 updateRate) {
    s32 i;
    u32 buttonsPressed;
    s32 contX;
    s32 contY;
    s32 contXAxis;
    s32 playSound;
    playSound = 0;
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    if (gMenuDelay != 0) {
        if (gMenuDelay > 0) {
            gMenuDelay += updateRate;
        } else {
            gMenuDelay -= updateRate;
        }
    }
    if (gMenuDelay > -20 && gMenuDelay < 20) {
        func_80084854(updateRate);
    }
    if (gIgnorePlayerInputTime == 0) {
        contX = 0;
        contY = 0;
        if (gMenuDelay == 0) {
            buttonsPressed = 0;
            contXAxis = 0;
            for (i = 0; i < 4; i++) {
                buttonsPressed |= input_pressed(i);
                contXAxis += input_clamp_stick_x(i);
                contX += gControllersXAxisDirection[i];
                contY += gControllersYAxisDirection[i];
            }
            if (contXAxis < 0) {
                contXAxis += 24;
                if (contXAxis > 0) {
                    contXAxis = 0;
                }
            } else {
                contXAxis -= 24;
                if (contXAxis < 0) {
                    contXAxis = 0;
                }
            }
            contXAxis >>= 2;
            if ((buttonsPressed & (0x8000 | 0x1000) && gMenuStage == gOptionsMenuItemIndex + 1) ||
                buttonsPressed & 0x4000) {
                gMenuDelay = -1;
                transition_begin(&sMenuTransitionFadeIn);
                if (gOpacityDecayTimer >= 0) {
                    music_fade(-128);
                }
                playSound = 3;
            } else if (contY < 0 && gOptionsMenuItemIndex < gMenuStage - 1) {
                gOptionsMenuItemIndex++;
                playSound = 1;
            } else if (contY > 0 && gOptionsMenuItemIndex > 0) {
                gOptionsMenuItemIndex--;
                playSound = 1;
            } else if (gOptionsMenuItemIndex == 0 && contX != 0) {
                if (contX < 0) {
                    gAudioOutputType--;
                } else {
                    gAudioOutputType++;
                }
                if (gAudioOutputType < 0) {
                    gAudioOutputType = HEADPHONES;
                }
                if (gAudioOutputType > HEADPHONES) {
                    gAudioOutputType = STEREO;
                }
                set_stereo_pan_mode(gAudioOutputType);
                playSound = 1;
            } else if (contXAxis && (gOptionsMenuItemIndex == 1 || gOptionsMenuItemIndex == 2)) {
                if (gOptionsMenuItemIndex == 1) {
                    gSfxVolumeSliderValue += contXAxis;
                    if (gSfxVolumeSliderValue < 0) {
                        gSfxVolumeSliderValue = 0;
                    } else if (gSfxVolumeSliderValue > 256) {
                        gSfxVolumeSliderValue = 256;
                    }
                    sndp_set_global_volume(gSfxVolumeSliderValue);
                } else if (gOptionsMenuItemIndex == 2) {
                    gMusicVolumeSliderValue += contXAxis;
                    if (gMusicVolumeSliderValue < 0) {
                        gMusicVolumeSliderValue = 0;
                    } else if (gMusicVolumeSliderValue > 256) {
                        gMusicVolumeSliderValue = 256;
                    }
                    music_volume_config_set(gMusicVolumeSliderValue);
                    if (!music_is_playing()) {
                        if (gOpacityDecayTimer >= 0) {
                            music_change_on();
                            music_play(gMusicTestSongIndex);
                        } else {
                            music_change_on();
                            music_voicelimit_set(24);
                            music_play(SEQUENCE_MAIN_MENU);
                            music_change_off();
                        }
                    }
                }
            } else if (gMenuStage >= 5 && gOptionsMenuItemIndex == 3) {
                if (contX < 0 && gMusicTestSongIndex > 0) {
                    gMusicTestSongIndex--;
                    playSound = 1;
                } else if (contX > 0) {
                    if (gMusicTestSongIndex < (music_sequence_count() - 1)) {
                        gMusicTestSongIndex++;
                        playSound = 1;
                    }
                }
                if (buttonsPressed & (0x8000 | 0x1000)) {
                    music_change_on();
                    music_voicelimit_set(24);
                    music_play(gMusicTestSongIndex);
                    gOpacityDecayTimer = gMusicTestSongIndex;
                }
            }
            if (gOptionsMenuItemIndex == 1) {
                if (gSoundOptionMask == 0) {
                    sound_play(SOUND_VOICE_DIDDY_POSITIVE5, &gSoundOptionMask);
                }
            } else if (gSoundOptionMask != 0) {
                sndp_stop(gSoundOptionMask);
            }
            if (playSound == 3) {
                sound_play(SOUND_MENU_BACK3, 0);
            } else if (playSound == 2) {
                sound_play(SOUND_SELECT2, 0);
            } else if (playSound == 1) {
                sound_play(SOUND_MENU_PICK2, 0);
            }
        }
    }
    if (gMenuDelay < -30) {
        soundoptions_free();
        menu_init(MENU_OPTIONS);
        return 0;
    }
    gIgnorePlayerInputTime = 0;
    return 0;
}
void soundoptions_free(void) {
    if (gSoundOptionMask != 0) {
        sndp_stop(gSoundOptionMask);
    }
    if (gOpacityDecayTimer >= 0) {
        music_voicelimit_set(24);
        music_play(SEQUENCE_MAIN_MENU);
        music_fade(0x100);
        music_change_off();
    }
    menu_assetgroup_free(gOptionMenuTextures);
    unload_font(ASSET_FONTS_BIGFONT);
}
void menu_save_options_init(void) {
    gSaveMenuRumbleNagSet = 1;
    gSaveMenuRumbleNag = 0;
    gSaveMenuSourceState = 1;
    gSaveMenuDestState = 1;
    gOptionsMenuItemIndex = 0;
    gOptionBlinkTimer = 0;
    gMenuDelay = 0;
    gMenuStage = SAVEMENU_WAIT;
    gOpacityDecayTimer = 0;
    D_80126A64 = (char *) mempool_alloc_safe(0x800, 0xFFFFFFFF);
    gSaveMenuFilesSource = (SaveFileData *) mempool_alloc_safe(0xA00, 0xFFFFFFFF);
    gSaveMenuFilesDest = &gSaveMenuFilesSource[80];
    gSaveMenuOptionCountUpper = 0;
    gSaveMenuOptionSource = 0;
    gSaveMenuScrollSource = 0.0f;
    gSaveMenuOptionCountLower = 0;
    gSaveMenuOptionDest = 0;
    gSaveMenuScrollDest = 0.0f;
    menu_assetgroup_load(gSaveMenuObjectIndices);
    menu_imagegroup_load(gSaveMenuImageIndices);
    func_8007FFEC(10);
    load_font(ASSET_FONTS_BIGFONT);
    gDrawTexN64Icon[0].texture = gMenuAssets[TEXTURE_ICON_SAVE_N64];
    gDrawTexTTIcon[0].texture = gMenuAssets[TEXTURE_ICON_SAVE_TT];
    gDrawTexGhostIcon[0].texture = gMenuAssets[TEXTURE_ICON_SAVE_GHOSTS];
    gDrawTexFileIcon[0].texture = gMenuAssets[TEXTURE_ICON_SAVE_FILECABINET];
    gDrawTexContPakIcon[0].texture = gMenuAssets[TEXTURE_ICON_SAVE_CPAK];
    gDrawTexTrashIcon[0].texture = gMenuAssets[TEXTURE_ICON_SAVE_BIN];
    menu_init_arrow_textures();
    mark_read_all_save_files();
    transition_begin(&sMenuTransitionFadeOut);
    rumble_enable(0);
}
void savemenu_render_element(SaveFileData *file, s32 x, s32 y) {
    s32 i;
    s32 firstDigit;
    s32 secondDigit;
    s32 spriteID;
    s32 colour;
    DrawTexture *drawTexture;
    char *text2;
    char *text;
    char buffer[16];
    TextureHeader *texture;
    s32 offsetY;
    spriteID = 11;
    switch (file->saveFileType) {
        case SAVE_FILE_TYPE_CART_SAVE:
            drawTexture = gDrawTexN64Icon;
            texture = gMenuAssets[TEXTURE_SURFACE_BUTTON_WOOD];
            colour = ((u32)((176 << 24) | (224 << 16) | (192 << 8) | 255));
            if (!gSavefileData[file->controllerIndex]->newGame) {
                filename_decompress(gSavefileData[file->controllerIndex]->filename, buffer, 3);
                filename_trim(buffer, buffer);
                text2 = buffer;
                firstDigit = *gSavefileData[file->controllerIndex]->balloonsPtr / 10;
                secondDigit = *gSavefileData[file->controllerIndex]->balloonsPtr - (firstDigit * 10);
                if (gSavefileData[file->controllerIndex]->cutsceneFlags & 4) {
                    spriteID = 12;
                }
            } else {
                text2 = gFilenames[file->controllerIndex];
            }
            text = gMenuText[ASSET_MENU_TEXT_GAMEPAK];
            break;
        case SAVE_FILE_TYPE_CART_TIMES:
            drawTexture = gDrawTexTTIcon;
            texture = gMenuAssets[TEXTURE_SURFACE_BUTTON_WOOD];
            colour = ((u32)((176 << 24) | (224 << 16) | (192 << 8) | 255));
            text2 = gMenuText[ASSET_MENU_TEXT_TIMES];
            text = gMenuText[ASSET_MENU_TEXT_GAMEPAK];
            break;
        case SAVE_FILE_TYPE_CPAK_SAVE:
            drawTexture = gDrawTexN64Icon;
            texture = gMenuAssets[TEXTURE_UNK_44];
            colour = gContPakSaveBgColours[file->controllerIndex];
            text2 = buffer;
            filename_decompress(file->compressedFilename, buffer, 3);
            for (i = 0; gConPakAdvSavePrefix[i] != '\0'; i++) {
                buffer[i + 3] = gConPakAdvSavePrefix[i];
            }
            buffer[i + 3] = file->saveFileExt[0];
            buffer[i + 4] = ')';
            buffer[i + 5] = '\0';
            text = gMenuText[ASSET_MENU_TEXT_CONTPAK1 + file->controllerIndex];
            firstDigit = file->balloonCount / 10;
            secondDigit = file->balloonCount % 10;
            if (file->adventureTwo) {
                spriteID = 12;
            }
            break;
        case SAVE_FILE_TYPE_CPAK_TIMES:
            drawTexture = gDrawTexTTIcon;
            texture = gMenuAssets[TEXTURE_UNK_44];
            colour = gContPakSaveBgColours[file->controllerIndex];
            text2 = file->saveFileExt;
            text = gMenuText[ASSET_MENU_TEXT_CONTPAK1 + file->controllerIndex];
            break;
        case SAVE_FILE_TYPE_CPAK_GHOST:
            drawTexture = gDrawTexGhostIcon;
            texture = gMenuAssets[TEXTURE_UNK_44];
            colour = gContPakSaveBgColours[file->controllerIndex];
            text2 = gMenuText[ASSET_MENU_TEXT_GHOSTS];
            text = gMenuText[ASSET_MENU_TEXT_CONTPAK1 + file->controllerIndex];
            break;
        case SAVE_FILE_TYPE_CPAK_OTHER:
            drawTexture = gDrawTexFileIcon;
            texture = gMenuAssets[TEXTURE_UNK_44];
            colour = gContPakSaveBgColours[file->controllerIndex];
            text2 = file->saveFileExt;
            text = gMenuText[ASSET_MENU_TEXT_CONTPAK1 + file->controllerIndex];
            break;
        case SAVE_FILE_TYPE_CPAK_EMPTY:
            drawTexture = gDrawTexContPakIcon;
            texture = gMenuAssets[TEXTURE_UNK_44];
            colour = gContPakSaveBgColours[file->controllerIndex];
            text2 = gMenuText[ASSET_MENU_TEXT_EMPTYSLOT];
            text = gMenuText[ASSET_MENU_TEXT_CONTPAK1 + file->controllerIndex];
            break;
        case SAVE_FILE_TYPE_UNK9:
            drawTexture = gDrawTexGhostIcon;
            texture = gMenuAssets[TEXTURE_UNK_45];
            colour = -1;
            text2 = gMenuText[ASSET_MENU_TEXT_VIEWGHOSTS];
            text = 0;
            break;
        case SAVE_FILE_TYPE_CART_BONUSES:
            drawTexture = gDrawTexN64Icon;
            text2 = gMenuText[ASSET_MENU_TEXT_GAMEPAKBONUSES];
            texture = gMenuAssets[TEXTURE_SURFACE_BUTTON_WOOD];
            colour = ((u32)((176 << 24) | (224 << 16) | (192 << 8) | 255));
            text = gMenuText[ASSET_MENU_TEXT_GAMEPAK];
            break;
        default:
            drawTexture = gDrawTexTrashIcon;
            texture = gMenuAssets[TEXTURE_UNK_45];
            colour = ((u32)((128 << 24) | (128 << 16) | (128 << 8) | 255));
            text2 = gMenuText[ASSET_MENU_TEXT_ERASE];
            text = 0;
            break;
    }
    func_80080580(&sMenuCurrDisplayList, x - 160, 120 - y, 160, 64, 4, 4, colour, texture);
    if (osTvType == 0) {
        y += 12;
    }
    if (file->saveFileType == SAVE_FILE_TYPE_CPAK_SAVE ||
        (file->saveFileType == SAVE_FILE_TYPE_CART_SAVE && gSavefileData[file->controllerIndex]->newGame == 0)) {
        if (osTvType == 0) {
            i = 134;
        } else {
            i = 120;
        }
        cam_set_sprite_anim_mode(SPRITE_ANIM_FRAME_INDEX);
        offsetY = (i - y);
        gMenuImages[2].trans.y_position = offsetY - 49;
        gMenuImages[spriteID].trans.y_position = offsetY - 24;
        sprite_opaque(0);
        gMenuImages[2].trans.x_position = x - (133 - 0);
        gMenuImages[2].spriteOffset = firstDigit;
        menu_element_render(2);
        gMenuImages[2].trans.x_position = x - (125 - 0);
        gMenuImages[2].spriteOffset = secondDigit;
        menu_element_render(2);
        sprite_opaque(1);
        gMenuImages[spriteID].trans.x_position = x - (128 - 0);
        menu_element_render(spriteID);
        cam_set_sprite_anim_mode(SPRITE_ANIM_NORMALIZED);
    }
    if (drawTexture != 0) {
        texrect_draw(&sMenuCurrDisplayList, drawTexture, x + (60 + 0), y + 6, 255, 255, 255, 255);
    }
    if (text != 0) {
        set_text_font(ASSET_FONTS_FUNFONT);
        set_text_colour(0, 0, 0, 255, 128);
        draw_text(&sMenuCurrDisplayList, x + (81 + 0), y + 1, text, ALIGN_MIDDLE_CENTER);
        set_text_colour(255, 64, 255, 64, 255);
        draw_text(&sMenuCurrDisplayList, x + (79 + 0), y - 1, text, ALIGN_MIDDLE_CENTER);
    }
    if (text2 != 0) {
        set_text_font(ASSET_FONTS_SMALLFONT);
        set_text_colour(0, 0, 0, 255, 160);
        draw_text(&sMenuCurrDisplayList, x + (80 + 1), y + 48, text2, ALIGN_TOP_CENTER);
        set_text_colour(255, 255, 255, 255, 255);
        draw_text(&sMenuCurrDisplayList, x + (79 + 1), y + 47, text2, ALIGN_TOP_CENTER);
    }
}
void savemenu_render( s32 updateRate) {
    s32 videoWidth;
    s32 temp;
    s32 offsetX;
    s32 x;
    s32 scroll;
    s32 drawUpperElements;
    s32 drawLowerElements;
    s32 drawPleaseWait;
    s32 drawOk;
    s32 drawDialogueBox;
    videoWidth = (fb_size() & 0xFFFF);
    drawUpperElements = 0;
    drawLowerElements = 0;
    drawPleaseWait = 0;
    drawOk = 0;
    drawDialogueBox = 0;
    switch (gMenuStage & 7) {
        case SAVEMENU_ENTER:
            break;
        case SAVEMENU_WAIT:
        case SAVEMENU_INIT_SOURCE:
            drawPleaseWait = 1;
            break;
        case SAVEMENU_CHOOSE_SOURCE:
        case SAVEMENU_INIT_DEST:
            drawUpperElements = 1;
            break;
        case SAVEMENU_CHOOSE_DEST:
            drawUpperElements = 1;
            drawLowerElements = 1;
            break;
        case SAVEMENU_CONFIRM:
            drawUpperElements = 1;
            drawLowerElements = 1;
            drawOk = 1;
            break;
        case SAVEMENU_WRITE:
            drawUpperElements = 1;
            drawLowerElements = 1;
            drawPleaseWait = 1;
            break;
    }
    if (gMenuStage & 8) {
        drawDialogueBox = 1;
    }
    mtx_ortho(&sMenuCurrDisplayList, &sMenuCurrHudMat);
    set_text_background_colour(0, 0, 0, 0);
    set_text_font(ASSET_FONTS_BIGFONT);
    set_text_colour(0, 0, 0, 255, 128);
    draw_text(&sMenuCurrDisplayList, (320 / 2) + 1, 35, gMenuText[ASSET_MENU_TEXT_SAVEOPTIONS],
              ALIGN_MIDDLE_CENTER);
    set_text_colour(255, 255, 255, 0, 255);
    draw_text(&sMenuCurrDisplayList, (320 / 2), 32, gMenuText[ASSET_MENU_TEXT_SAVEOPTIONS],
              ALIGN_MIDDLE_CENTER);
    if (drawLowerElements) {
        temp = (osTvType == 0) ? ((240 / 2) + 12) : (240 / 2);
        temp += ((s32) (gOptionBlinkTimer & 0x1F) >> 1);
        for (scroll = 0; scroll < 2; scroll += 1, temp += 16) {
            texrect_draw(&sMenuCurrDisplayList, gMenuSelectionArrowDown, (320 / 2), temp, 255, 255, 255, 255);
        }
    }
    if (drawUpperElements) {
        scroll = (s32) gSaveMenuScrollSource;
        temp = scroll;
        offsetX = 80 - (s32) ((gSaveMenuScrollSource - scroll) * 164.0f);
        x = offsetX;
        while (x < videoWidth && temp < gSaveMenuOptionCountUpper) {
            savemenu_render_element(&gSaveMenuFilesSource[temp], x, 64);
            x += 164;
            temp++;
        }
        temp = scroll;
        x = offsetX;
        while ((x > 0) && (temp > 0)) {
            temp--;
            x -= 164;
            savemenu_render_element(&gSaveMenuFilesSource[temp], x, 64);
        }
    }
    if (drawLowerElements) {
        scroll = (s32) gSaveMenuScrollDest;
        temp = scroll;
        offsetX = 80 - (s32) ((gSaveMenuScrollDest - (f32) scroll) * 164.0f);
        x = offsetX;
        while (x < videoWidth && temp < gSaveMenuOptionCountLower) {
            savemenu_render_element(&gSaveMenuFilesDest[temp], x, 144);
            x += 164;
            temp++;
        }
        temp = scroll;
        x = offsetX;
        while (x > 0 && temp > 0) {
            temp--;
            x -= 164;
            savemenu_render_element(&gSaveMenuFilesDest[temp], x, 144);
        }
    }
    set_text_font(ASSET_FONTS_BIGFONT);
    set_text_colour(255, 255, 255, 0, 255);
    if (drawOk) {
        draw_text(&sMenuCurrDisplayList, (320 / 2), 128, "OK?", ALIGN_MIDDLE_CENTER);
    }
    if (drawPleaseWait) {
        draw_text(&sMenuCurrDisplayList, (320 / 2), 128, gMenuText[ASSET_MENU_TEXT_PLEASEWAIT],
                  ALIGN_MIDDLE_CENTER);
    }
    if (drawDialogueBox) {
        render_dialogue_box(&sMenuCurrDisplayList, 0, 0, 7);
    }
    menu_geometry_end();
}
SIDeviceStatus savemenu_check_space(s32 controllerIndex, s32 *pakState, SaveFileData *file, s32 *index, s32 fileSize,
                                    s32 arg5) {
    SIDeviceStatus ret = CONTROLLER_PAK_GOOD;
    if (*pakState) {
        ret = get_free_space(controllerIndex, &file[*index].fileSize, &sControllerPakNotesFree[controllerIndex]);
        if (ret == CONTROLLER_PAK_GOOD) {
            if ((s32) file[*index].fileSize >= fileSize && sControllerPakNotesFree[controllerIndex] > 0) {
                file[*index].saveFileType = SAVE_FILE_TYPE_CPAK_EMPTY;
                file[*index].controllerIndex = controllerIndex;
                (*index)++;
            }
        } else {
            SIDeviceStatus status = ret & 0xFF;
            if (*pakState < 0 && status == CONTROLLER_PAK_RUMBLE_PAK_FOUND) {
                *pakState = 0;
                ret = CONTROLLER_PAK_GOOD;
            } else if (status != CONTROLLER_PAK_WITH_BAD_ID && status != CONTROLLER_PAK_INCONSISTENT &&
                       status != CONTROLLER_PAK_BAD_DATA) {
                ret = CONTROLLER_PAK_GOOD;
            }
        }
    }
    return ret;
}
void savemenu_blank_save_destination(SaveFileData *file, s32 *fileIndex) {
    s32 i;
    for (i = 0; i < 3; i++) {
        if (gSavefileData[i]->newGame) {
            file[*fileIndex].saveFileType = SAVE_FILE_TYPE_CART_SAVE;
            file[*fileIndex].unk1 = 0;
            file[*fileIndex].balloonCount = 0;
            file[*fileIndex].controllerIndex = i;
            file[*fileIndex].fileSize = get_game_data_file_size();
            (*fileIndex)++;
        }
    }
}
SIDeviceStatus savemenu_load_sources(void) {
    s32 numAttempts;
    s32 i;
    s32 fileIndex;
    SIDeviceStatus result;
    SIDeviceStatus temp;
    char *fileNames[16];
    char *fileExts[16];
    u8 fileTypes[16];
    Settings *settings;
    u32 fileSizes[16];
    char *temp_D_80126A64;
    settings = gSavefileData[3];
    gSaveMenuOptionCountUpper = 0;
    gSaveMenuOptionSource = 0;
    gSaveMenuScrollSource = 0.0f;
    for (i = 0; i < 3; i++) {
        if (!gSavefileData[i]->newGame) {
            gSaveMenuFilesSource[gSaveMenuOptionCountUpper].saveFileType = SAVE_FILE_TYPE_CART_SAVE;
            gSaveMenuFilesSource[gSaveMenuOptionCountUpper].unk1 = 1;
            gSaveMenuFilesSource[gSaveMenuOptionCountUpper].balloonCount = gSavefileData[i]->balloonsPtr[0];
            gSaveMenuFilesSource[gSaveMenuOptionCountUpper].controllerIndex = i;
            gSaveMenuFilesSource[gSaveMenuOptionCountUpper].fileSize = get_game_data_file_size();
            gSaveMenuOptionCountUpper++;
        }
    }
    gSaveMenuFilesSource[gSaveMenuOptionCountUpper].saveFileType = SAVE_FILE_TYPE_CART_TIMES;
    gSaveMenuFilesSource[gSaveMenuOptionCountUpper].unk1 = 1;
    gSaveMenuFilesSource[gSaveMenuOptionCountUpper++].fileSize = get_time_data_file_size();
    gSaveMenuFilesSource[gSaveMenuOptionCountUpper++].saveFileType = SAVE_FILE_TYPE_CART_BONUSES;
    temp_D_80126A64 = D_80126A64;
    do {
        numAttempts = 1;
        if (gSaveMenuSourceState != 0) {
            gSaveMenuRumbleConnected = 0;
            do {
                result = get_controller_pak_file_list(0, 16, fileNames, fileExts, fileSizes, fileTypes);
                temp = result & 0xFF;
                numAttempts++;
            } while (temp == CONTROLLER_PAK_CHANGED && numAttempts < 3);
            if (result == CONTROLLER_PAK_GOOD) {
                for (fileIndex = 0; fileIndex < 16; fileIndex++) {
                    if ((fileTypes[fileIndex] >= SAVE_FILE_TYPE_CPAK_SAVE) &&
                        (fileTypes[fileIndex] <= SAVE_FILE_TYPE_CPAK_OTHER)) {
                        sControllerPakNotesFree[0]--;
                        gSaveMenuFilesSource[gSaveMenuOptionCountUpper].saveFileType = fileTypes[fileIndex];
                        gSaveMenuFilesSource[gSaveMenuOptionCountUpper].controllerIndex = 0;
                        gSaveMenuFilesSource[gSaveMenuOptionCountUpper].saveFileNumber = fileIndex;
                        gSaveMenuFilesSource[gSaveMenuOptionCountUpper].fileSize = fileSizes[fileIndex];
                        if (fileTypes[fileIndex] == SAVE_FILE_TYPE_CPAK_SAVE) {
                            if (read_game_data_from_controller_pak(0, fileExts[fileIndex], settings) ==
                                CONTROLLER_PAK_GOOD) {
                                gSaveMenuFilesSource[gSaveMenuOptionCountUpper].saveFileExt = temp_D_80126A64;
                                temp_D_80126A64[0] = *fileExts[fileIndex];
                                temp_D_80126A64[1] = 0;
                                temp_D_80126A64 += 2;
                                gSaveMenuFilesSource[gSaveMenuOptionCountUpper].balloonCount = *settings->balloonsPtr;
                                gSaveMenuFilesSource[gSaveMenuOptionCountUpper].adventureTwo =
                                    (settings->cutsceneFlags & 4) != 0;
                                gSaveMenuFilesSource[gSaveMenuOptionCountUpper].compressedFilename = settings->filename;
                            } else {
                                gSaveMenuOptionCountUpper--;
                            }
                        } else {
                            temp = 0;
                            if ((fileTypes[fileIndex] == SAVE_FILE_TYPE_CPAK_OTHER) ||
                                (fileTypes[fileIndex] == SAVE_FILE_TYPE_CPAK_TIMES)) {
                                if (fileTypes[fileIndex] == SAVE_FILE_TYPE_CPAK_TIMES) {
                                    temp = CONTROLLER_PAK_BAD_DATA;
                                }
                                gSaveMenuFilesSource[gSaveMenuOptionCountUpper].saveFileExt = temp_D_80126A64;
                                while (fileNames[fileIndex][temp] != '\0') {
                                    *temp_D_80126A64 = fileNames[fileIndex][temp];
                                    temp++;
                                    temp_D_80126A64++;
                                }
                                if ((fileExts[fileIndex] != 0) && (fileExts[fileIndex][0] != '\0')) {
                                    *temp_D_80126A64 = '.';
                                    temp_D_80126A64++;
                                    temp = 0;
                                    while (fileExts[fileIndex][temp] != '\0') {
                                        *temp_D_80126A64 = fileExts[fileIndex][temp];
                                        temp_D_80126A64++;
                                        temp++;
                                    }
                                }
                                *temp_D_80126A64 = 0;
                                temp_D_80126A64++;
                            }
                        }
                        gSaveMenuOptionCountUpper++;
                    }
                }
                cpak_free_files();
            } else if (temp == CONTROLLER_PAK_RUMBLE_PAK_FOUND) {
                gSaveMenuRumbleConnected = 1;
                if (gSaveMenuSourceState < 0) {
                    result = CONTROLLER_PAK_GOOD;
                }
                if (gSaveMenuRumbleNagSet) {
                    gSaveMenuRumbleNag = 1;
                    gSaveMenuRumbleNagSet = 0;
                }
            } else if (temp == CONTROLLER_PAK_NOT_FOUND) {
                result = CONTROLLER_PAK_GOOD;
            } else if (gSaveMenuSourceState < 0 && temp == CONTROLLER_PAK_CHANGED) {
                numAttempts = 0;
            }
        }
    } while (numAttempts == 0);
    return result;
}
SIDeviceStatus savemenu_load_destinations(void) {
    SIDeviceStatus ret = CONTROLLER_PAK_GOOD;
    gSaveMenuOptionCountLower = 0;
    switch (gSaveMenuFilesSource[gSaveMenuOptionSource].saveFileType) {
        case SAVE_FILE_TYPE_CART_SAVE:
            mark_read_save_file(gSaveMenuFilesSource[gSaveMenuOptionSource].controllerIndex);
            savemenu_blank_save_destination(gSaveMenuFilesDest, &gSaveMenuOptionCountLower);
            ret = savemenu_check_space(0, &gSaveMenuSourceState, gSaveMenuFilesDest, &gSaveMenuOptionCountLower,
                                       get_game_data_file_size(), -1);
            break;
        case SAVE_FILE_TYPE_CART_TIMES:
            ret = savemenu_check_space(0, &gSaveMenuSourceState, gSaveMenuFilesDest, &gSaveMenuOptionCountLower,
                                       get_time_data_file_size(), -1);
            break;
        case SAVE_FILE_TYPE_CPAK_SAVE:
            savemenu_blank_save_destination(gSaveMenuFilesDest, &gSaveMenuOptionCountLower);
            ret = savemenu_check_space(1, &gSaveMenuDestState, gSaveMenuFilesDest, &gSaveMenuOptionCountLower,
                                       get_game_data_file_size(),
                                       gSaveMenuFilesSource[gSaveMenuOptionSource].controllerIndex);
            break;
        case SAVE_FILE_TYPE_CPAK_TIMES:
            gSaveMenuFilesDest[gSaveMenuOptionCountLower++].saveFileType = SAVE_FILE_TYPE_CART_TIMES;
            ret = savemenu_check_space(1, &gSaveMenuDestState, gSaveMenuFilesDest, &gSaveMenuOptionCountLower,
                                       get_time_data_file_size(),
                                       gSaveMenuFilesSource[gSaveMenuOptionSource].controllerIndex);
            break;
        case SAVE_FILE_TYPE_CPAK_GHOST:
            gSaveMenuFilesDest[gSaveMenuOptionCountLower++].saveFileType = SAVE_FILE_TYPE_UNK9;
            ret = savemenu_check_space(1, &gSaveMenuDestState, gSaveMenuFilesDest, &gSaveMenuOptionCountLower,
                                       get_ghost_data_file_size(),
                                       gSaveMenuFilesSource[gSaveMenuOptionSource].controllerIndex);
            break;
    }
    gSaveMenuFilesDest[gSaveMenuOptionCountLower++].saveFileType = SAVE_FILE_TYPE_ERASE;
    return ret;
}
void savemenu_move(s32 updateRate) {
    f32 optUpper, optLower;
    f32 lerpUpper, lerpLower;
    optUpper = gSaveMenuOptionSource;
    optLower = gSaveMenuOptionDest;
    while (updateRate > 0) {
        if (gSaveMenuOptionCountUpper > 0) {
            lerpUpper = optUpper - gSaveMenuScrollSource;
            gSaveMenuScrollSource += 0.1f * lerpUpper;
        }
        if (gMenuStage > SAVEMENU_ENTER && gSaveMenuOptionCountLower > 0) {
            lerpLower = optLower - gSaveMenuScrollDest;
            gSaveMenuScrollDest += 0.1f * lerpLower;
        }
        updateRate--;
    }
}
SIDeviceStatus savemenu_write(void) {
    s32 i;
    SIDeviceStatus ret;
    s32 pad[2];
    char fileExt[4];
    Settings *settings;
    settings = get_settings();
    switch (gSaveMenuFilesSource[gSaveMenuOptionSource].saveFileType) {
        case SAVE_FILE_TYPE_CART_SAVE:
            switch (gSaveMenuFilesDest[gSaveMenuOptionDest].saveFileType) {
                case SAVE_FILE_TYPE_CART_SAVE:
                    force_mark_write_save_file(gSaveMenuFilesDest[gSaveMenuOptionDest].controllerIndex);
                    gSavefileData[gSaveMenuFilesDest[gSaveMenuOptionDest].controllerIndex]->cutsceneFlags =
                        settings->cutsceneFlags;
                    gSavefileData[gSaveMenuFilesDest[gSaveMenuOptionDest].controllerIndex]->newGame = 0;
                    *gSavefileData[gSaveMenuFilesDest[gSaveMenuOptionDest].controllerIndex]->balloonsPtr =
                        *settings->balloonsPtr;
                    gSavefileData[gSaveMenuFilesDest[gSaveMenuOptionDest].controllerIndex]->filename =
                        settings->filename;
                    break;
                case SAVE_FILE_TYPE_CPAK_EMPTY:
                    ret = write_game_data_to_controller_pak(gSaveMenuFilesDest[gSaveMenuOptionDest].controllerIndex,
                                                            settings);
                    break;
                case SAVE_FILE_TYPE_ERASE:
                    mark_save_file_to_erase(gSaveMenuFilesSource[gSaveMenuOptionSource].controllerIndex);
                    gSavefileData[gSaveMenuFilesSource[gSaveMenuOptionSource].controllerIndex]->newGame = 1;
                    break;
            }
            break;
        case SAVE_FILE_TYPE_CART_TIMES:
            if (gSaveMenuFilesDest[gSaveMenuOptionDest].saveFileType != SAVE_FILE_TYPE_ERASE) {
                if (gSaveMenuFilesDest[gSaveMenuOptionDest].saveFileType == SAVE_FILE_TYPE_CPAK_EMPTY) {
                    ret = write_time_data_to_controller_pak(gSaveMenuFilesDest[gSaveMenuOptionDest].controllerIndex,
                                                            settings);
                }
            } else {
                clear_lap_records(settings, 3);
                mark_to_write_flap_and_course_times();
                unset_eeprom_settings_value(
                    0xFFFFF0);
                gActiveMagicCodes &= ~CHEAT_CONTROL_TT;
                gUnlockedMagicCodes &= ~CHEAT_CONTROL_TT;
            }
            break;
        case SAVE_FILE_TYPE_CPAK_SAVE:
            switch (gSaveMenuFilesDest[gSaveMenuOptionDest].saveFileType) {
                case SAVE_FILE_TYPE_CART_SAVE:
                    ret = read_game_data_from_controller_pak(
                        gSaveMenuFilesSource[gSaveMenuOptionSource].controllerIndex,
                        gSaveMenuFilesSource[gSaveMenuOptionSource].saveFileExt, settings);
                    if (settings->cutsceneFlags & 4 && !is_adventure_two_unlocked()) {
                        ret = CONTROLLER_PAK_NEED_SECOND_ADVENTURE;
                    }
                    if (ret == CONTROLLER_PAK_GOOD) {
                        force_mark_write_save_file(gSaveMenuFilesDest[gSaveMenuOptionDest].controllerIndex);
                        gSavefileData[gSaveMenuFilesDest[gSaveMenuOptionDest].controllerIndex]->cutsceneFlags =
                            settings->cutsceneFlags;
                        gSavefileData[gSaveMenuFilesDest[gSaveMenuOptionDest].controllerIndex]->newGame = 0;
                        *gSavefileData[gSaveMenuFilesDest[gSaveMenuOptionDest].controllerIndex]->balloonsPtr =
                            *settings->balloonsPtr;
                        gSavefileData[gSaveMenuFilesDest[gSaveMenuOptionDest].controllerIndex]->filename =
                            settings->filename;
                    }
                    break;
                case SAVE_FILE_TYPE_CPAK_EMPTY:
                    ret = read_game_data_from_controller_pak(
                        gSaveMenuFilesSource[gSaveMenuOptionSource].controllerIndex,
                        gSaveMenuFilesSource[gSaveMenuOptionSource].saveFileExt, gSavefileData[3]);
                    if (ret == CONTROLLER_PAK_GOOD) {
                        ret = write_game_data_to_controller_pak(gSaveMenuFilesDest[gSaveMenuOptionDest].controllerIndex,
                                                                gSavefileData[3]);
                    }
                    break;
                case SAVE_FILE_TYPE_ERASE:
                    ret = delete_file(gSaveMenuFilesSource[gSaveMenuOptionSource].controllerIndex,
                                      gSaveMenuFilesSource[gSaveMenuOptionSource].saveFileNumber);
                    break;
            }
            break;
        case SAVE_FILE_TYPE_CPAK_TIMES:
            for (i = 0; gSaveMenuFilesSource[gSaveMenuOptionSource].saveFileExt[i] != '\0'; i++) {}
            if (i > 0) {
                fileExt[0] = gSaveMenuFilesSource[gSaveMenuOptionSource].saveFileExt[i - 1];
            } else {
                fileExt[0] = 'A';
            }
            fileExt[1] = '\0';
            switch (gSaveMenuFilesDest[gSaveMenuOptionDest].saveFileType) {
                case SAVE_FILE_TYPE_CART_TIMES:
                    ret = read_time_data_from_controller_pak(
                        gSaveMenuFilesSource[gSaveMenuOptionSource].controllerIndex, fileExt, settings);
                    mark_to_write_flap_and_course_times();
                    break;
                case SAVE_FILE_TYPE_CPAK_EMPTY:
                    ret = read_time_data_from_controller_pak(
                        gSaveMenuFilesSource[gSaveMenuOptionSource].controllerIndex, fileExt, settings);
                    if (ret == CONTROLLER_PAK_GOOD) {
                        ret = write_time_data_to_controller_pak(gSaveMenuFilesDest[gSaveMenuOptionDest].controllerIndex,
                                                                settings);
                    }
                    mark_to_read_flap_and_course_times();
                    break;
                case SAVE_FILE_TYPE_ERASE:
                    ret = delete_file(gSaveMenuFilesSource[gSaveMenuOptionSource].controllerIndex,
                                      gSaveMenuFilesSource[gSaveMenuOptionSource].saveFileNumber);
                    break;
            }
            break;
        case SAVE_FILE_TYPE_CPAK_GHOST:
            if (gSaveMenuFilesDest[gSaveMenuOptionDest].saveFileType != SAVE_FILE_TYPE_ERASE) {
                if (gSaveMenuFilesDest[gSaveMenuOptionDest].saveFileType != SAVE_FILE_TYPE_CPAK_EMPTY) {
                    if (gSaveMenuFilesDest[gSaveMenuOptionDest].saveFileType == SAVE_FILE_TYPE_UNK9) {
                        gMenuDelay = 1;
                        gCpakGhostData = gSaveMenuFilesSource[gSaveMenuOptionSource].controllerIndex;
                    }
                } else {
                    ret = copy_controller_pak_data(gSaveMenuFilesSource[gSaveMenuOptionSource].controllerIndex,
                                                   gSaveMenuFilesSource[gSaveMenuOptionSource].saveFileNumber,
                                                   gSaveMenuFilesDest[gSaveMenuOptionDest].controllerIndex);
                }
            } else {
                ret = delete_file(gSaveMenuFilesSource[gSaveMenuOptionSource].controllerIndex,
                                  gSaveMenuFilesSource[gSaveMenuOptionSource].saveFileNumber);
            }
            break;
        case SAVE_FILE_TYPE_CPAK_OTHER:
            if (gSaveMenuFilesDest[gSaveMenuOptionDest].saveFileType == SAVE_FILE_TYPE_ERASE) {
                ret = delete_file(gSaveMenuFilesSource[gSaveMenuOptionSource].controllerIndex,
                                  gSaveMenuFilesSource[gSaveMenuOptionSource].saveFileNumber);
            }
            break;
        case SAVE_FILE_TYPE_CART_BONUSES:
            if (gSaveMenuFilesDest[gSaveMenuOptionDest].saveFileType == SAVE_FILE_TYPE_ERASE) {
                unset_eeprom_settings_value(
                    0xFFFFF3);
                gActiveMagicCodes &= ~(CHEAT_CONTROL_TT | CHEAT_CONTROL_DRUMSTICK);
                gUnlockedMagicCodes &= ~(CHEAT_CONTROL_TT | CHEAT_CONTROL_DRUMSTICK);
            }
            break;
        default:
            ret = CONTROLLER_PAK_GOOD;
            break;
    }
    return ret;
}
void savemenu_render_error(SIDeviceStatus deviceStatus) {
    s32 i;
    s32 j;
    s32 k;
    s32 y;
    char *text;
    gControllerIndex = (deviceStatus >> 30) & 3;
    deviceStatus &= 0x3FFFFFFF;
    gDeviceStatusStrings = gContPakStrings[deviceStatus];
    gDeviceStatus = deviceStatus;
    gSaveMenuMessageLines = 0;
    for (k = 0; gDeviceStatusStrings[k] != 0; k++) {}
    k++;
    for (; gDeviceStatusStrings[k] != 0; gSaveMenuMessageLines++, k++) {}
    gSaveMenuMessageOption = gSaveMenuMessageLines - 1;
    dialogue_clear(7);
    set_current_dialogue_box_coords(7, 40, (240 / 2) - (((k * 16) + 44) >> 1), 280,
                                    (((k * 16) + 44) >> 1) + (240 / 2));
    set_current_dialogue_background_colour(7, 0, 0, 0, 160);
    set_current_text_background_colour(7, 0, 0, 0, 0);
    set_dialogue_font(7, 2);
    set_current_text_colour(7, 255, 255, 255, 0, 255);
    text = gMenuText[ASSET_MENU_TEXT_PAKERROR];
    if (gDeviceStatusStrings == gContPakRumbleDetectedStrings ||
        gDeviceStatusStrings == gContPakSwitchToRumbleStrings) {
        text = gMenuText[ASSET_MENU_TEXT_CAUTION];
    } else if (gDeviceStatusStrings == gContPakNeed2ndAdvStrings) {
        text = gMenuText[ASSET_MENU_TEXT_GAMEERROR];
    }
    render_dialogue_text(7, -0x8000, 20, text, 1, ALIGN_MIDDLE_CENTER);
    y = 52;
    i = 0;
    set_dialogue_font(7, ASSET_FONTS_FUNFONT);
    for (; gDeviceStatusStrings[i] != 0; i++, y += 16) {
        render_dialogue_text(7, -0x8000, y, gDeviceStatusStrings[i], gControllerIndex + 1, ALIGN_MIDDLE_CENTER);
    }
    i++;
    y += 16;
    for (j = 0; gDeviceStatusStrings[i] != 0; i++, j++, y += 16) {
        gSaveMenuText[j] = render_dialogue_text(7, -0x8000, y, gDeviceStatusStrings[i], 1, ALIGN_MIDDLE_CENTER);
    }
    gMenuStage |= 8;
}
s32 savemenu_input_source(s32 buttonsPressed, s32 direction) {
    s32 ret;
    ret = 0;
    if (buttonsPressed & 0x4000) {
        gMenuStage = SAVEMENU_ENTER;
        if (gSaveMenuRumbleNag != gSaveMenuRumbleConnected) {
            savemenu_render_error(CONTROLLER_PAK_SWITCH_TO_RUMBLE);
        } else {
            sound_play(SOUND_MENU_BACK3, 0);
            ret = -1;
        }
    } else if (buttonsPressed & (0x8000 | 0x1000)) {
        sound_play(SOUND_SELECT2, 0);
        gMenuStage = SAVEMENU_INIT_DEST;
    } else if (direction < 0 && gSaveMenuOptionSource > 0) {
        sound_play(SOUND_MENU_PICK2, 0);
        gSaveMenuOptionSource--;
    } else if (direction > 0 && (gSaveMenuOptionSource < gSaveMenuOptionCountUpper - 1)) {
        sound_play(SOUND_MENU_PICK2, 0);
        gSaveMenuOptionSource++;
    }
    return ret;
}
s32 savemenu_input_dest(s32 buttonsPressed, s32 direction) {
    if (buttonsPressed & 0x4000) {
        sound_play(SOUND_MENU_BACK3, 0);
        gMenuStage = SAVEMENU_CHOOSE_SOURCE;
    } else if (buttonsPressed & (0x8000 | 0x1000)) {
        sound_play(SOUND_SELECT2, 0);
        gMenuStage = SAVEMENU_CONFIRM;
    } else if (direction < 0 && gSaveMenuOptionDest > 0) {
        sound_play(SOUND_MENU_PICK2, 0);
        gSaveMenuOptionDest--;
    } else if (direction > 0 && gSaveMenuOptionDest < gSaveMenuOptionCountLower - 1) {
        sound_play(SOUND_MENU_PICK2, 0);
        gSaveMenuOptionDest++;
    }
    return 0;
}
s32 savemenu_input_confirm(s32 buttonsPressed, s32 arg1) {
    if (buttonsPressed & 0x4000) {
        sound_play(SOUND_MENU_BACK3, 0);
        gMenuStage = SAVEMENU_CHOOSE_DEST;
    } else if (buttonsPressed & (0x8000 | 0x1000)) {
        sound_play(SOUND_SELECT2, 0);
        gMenuStage = SAVEMENU_WRITE;
        gOpacityDecayTimer = 0;
    }
    return 0;
}
s32 savemenu_input_message(s32 buttonsPressed, s32 yAxis) {
    s32 pad[2];
    s32 stage;
    s32 i;
    s32 highlight;
    highlight = gOptionBlinkTimer * 8;
    if (highlight > 255) {
        highlight = 511 - highlight;
    }
    stage = (gMenuStage & 7);
    for (i = 0; i < gSaveMenuMessageLines; i++) {
        if (i == gSaveMenuMessageOption) {
            gSaveMenuText[i]->highlight = highlight;
        } else {
            gSaveMenuText[i]->highlight = 0;
        }
    }
    if (buttonsPressed & 0x4000 || (buttonsPressed & (0x1000 | 0x8000) &&
                                      (u32) gSaveMenuMessageLines == (u32) (gSaveMenuMessageOption + 1))) {
        sound_play(SOUND_MENU_BACK3, 0);
        gMenuStage &= ~8;
        switch (stage) {
            case SAVEMENU_ENTER:
                if (!(buttonsPressed & (0x1000 | 0x8000))) {
                    gOpacityDecayTimer = 6;
                    gMenuStage = SAVEMENU_WAIT;
                }
                break;
            case SAVEMENU_INIT_SOURCE:
                switch (gDeviceStatus) {
                    case CONTROLLER_PAK_CHANGED:
                        gOpacityDecayTimer = 5;
                        gMenuStage = SAVEMENU_WAIT;
                        break;
                    case CONTROLLER_PAK_NOT_FOUND:
                    case CONTROLLER_PAK_INCONSISTENT:
                    case CONTROLLER_PAK_WITH_BAD_ID:
                    case CONTROLLER_PAK_BAD_DATA:
                        gSaveMenuSourceState = 0;
                        break;
                    case CONTROLLER_PAK_RUMBLE_PAK_FOUND:
                        gSaveMenuSourceState = -1;
                        break;
                    default:
                        gSaveMenuSourceState = 1;
                        break;
                }
                break;
            case SAVEMENU_INIT_DEST:
                switch (gDeviceStatus) {
                    case CONTROLLER_PAK_NOT_FOUND:
                    case CONTROLLER_PAK_CHANGED:
                        gOpacityDecayTimer = 5;
                        gMenuStage = SAVEMENU_WAIT;
                        break;
                    case CONTROLLER_PAK_INCONSISTENT:
                    case CONTROLLER_PAK_WITH_BAD_ID:
                    case CONTROLLER_PAK_BAD_DATA:
                        gSaveMenuDestState = 0;
                        break;
                    case CONTROLLER_PAK_RUMBLE_PAK_FOUND:
                        gSaveMenuDestState = -1;
                        break;
                    default:
                        gSaveMenuDestState = 1;
                        break;
                }
                break;
            case SAVEMENU_WRITE:
                switch (gDeviceStatus) {
                    case CONTROLLER_PAK_NOT_FOUND:
                    case CONTROLLER_PAK_INCONSISTENT:
                    case CONTROLLER_PAK_WITH_BAD_ID:
                    case CONTROLLER_PAK_CHANGED:
                    case CONTROLLER_PAK_RUMBLE_PAK_FOUND:
                        gOpacityDecayTimer = 5;
                        gMenuStage = SAVEMENU_WAIT;
                        break;
                    case CONTROLLER_PAK_BAD_DATA:
                    case CONTROLLER_PAK_NEED_SECOND_ADVENTURE:
                        gMenuStage = SAVEMENU_INIT_DEST;
                        break;
                }
                break;
        }
    } else if (buttonsPressed & (0x1000 | 0x8000)) {
        sound_play(SOUND_SELECT2, 0);
        gMenuStage &= ~8;
        switch (gDeviceStatus) {
            case CONTROLLER_PAK_WITH_BAD_ID:
                reformat_controller_pak(gControllerIndex);
                if (stage == SAVEMENU_INIT_DEST) {
                    gSaveMenuDestState = 0;
                } else if (stage == SAVEMENU_WRITE) {
                    gSaveMenuSourceState = 0;
                }
                break;
            case CONTROLLER_PAK_INCONSISTENT:
            case CONTROLLER_PAK_BAD_DATA:
                repair_controller_pak(gControllerIndex);
                if (stage == SAVEMENU_INIT_DEST) {
                    gSaveMenuDestState = 1;
                } else if (stage == SAVEMENU_INIT_SOURCE) {
                    gSaveMenuSourceState = 1;
                }
                break;
            case CONTROLLER_PAK_RUMBLE_PAK_FOUND:
                if (stage == SAVEMENU_INIT_DEST) {
                    gSaveMenuDestState = -1;
                } else {
                    gSaveMenuSourceState = -1;
                }
                break;
        }
    } else if (yAxis < 0 && gSaveMenuMessageOption < (gSaveMenuMessageLines - 1)) {
        sound_play(SOUND_MENU_PICK2, 0);
        gSaveMenuMessageOption++;
    } else if (yAxis > 0 && gSaveMenuMessageOption > 0) {
        sound_play(SOUND_MENU_PICK2, 0);
        gSaveMenuMessageOption--;
    }
    return 0;
}
s32 menu_save_options_loop(s32 updateRate) {
    SIDeviceStatus result;
    s32 buttonsPressed;
    s32 i;
    s32 yAxis;
    s32 xAxis;
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    if (gMenuDelay != 0) {
        if (gMenuDelay > 0) {
            gMenuDelay += updateRate;
        } else {
            gMenuDelay -= updateRate;
        }
    }
    if ((gMenuStage & 7) >= SAVEMENU_INIT_SOURCE) {
        savemenu_move(updateRate);
    }
    if (gMenuDelay > -20 && gMenuDelay < 20) {
        savemenu_render(updateRate);
    }
    if (gMenuDelay != 0) {
        if (gMenuDelay > 30) {
            savemenu_free();
            menu_init(MENU_GHOST_DATA);
        } else if (gMenuDelay < -30) {
            savemenu_free();
            menu_init(MENU_OPTIONS);
        }
        return 0;
    }
    buttonsPressed = 0;
    xAxis = 0;
    yAxis = 0;
    if (gIgnorePlayerInputTime == 0) {
        for (i = 0; i < 4; i++) {
            xAxis += gControllersXAxisDirection[i];
            yAxis += gControllersYAxisDirection[i];
            buttonsPressed |= input_pressed(i);
        }
    }
    if (gMenuStage & 8) {
        gMenuDelay = savemenu_input_message(buttonsPressed, yAxis);
    } else {
        switch (gMenuStage) {
            case SAVEMENU_ENTER:
                gMenuDelay = -1;
                break;
            case SAVEMENU_WAIT:
                gOpacityDecayTimer++;
                if (gOpacityDecayTimer > 10) {
                    gMenuStage = SAVEMENU_INIT_SOURCE;
                }
                break;
            case SAVEMENU_INIT_SOURCE:
                gSaveMenuOptionSource = 0;
                gSaveMenuScrollSource = 0.0f;
                result = savemenu_load_sources();
                if (result != CONTROLLER_PAK_GOOD) {
                    savemenu_render_error(result);
                } else {
                    gMenuStage = SAVEMENU_CHOOSE_SOURCE;
                }
                break;
            case SAVEMENU_CHOOSE_SOURCE:
                gMenuDelay = savemenu_input_source(buttonsPressed, xAxis);
                break;
            case SAVEMENU_INIT_DEST:
                gSaveMenuOptionDest = 0;
                gSaveMenuScrollDest = 0.0f;
                result = savemenu_load_destinations();
                if (result != CONTROLLER_PAK_GOOD) {
                    savemenu_render_error(result);
                } else {
                    gMenuStage = SAVEMENU_CHOOSE_DEST;
                }
                break;
            case SAVEMENU_CHOOSE_DEST:
                gMenuDelay = savemenu_input_dest(buttonsPressed, xAxis);
                break;
            case SAVEMENU_CONFIRM:
                gMenuDelay = savemenu_input_confirm(buttonsPressed, xAxis);
                break;
            case SAVEMENU_WRITE:
                gOpacityDecayTimer++;
                if (gOpacityDecayTimer > 3) {
                    result = savemenu_write();
                    if (result != CONTROLLER_PAK_GOOD) {
                        savemenu_render_error(result);
                    } else {
                        gOpacityDecayTimer = 6;
                        gMenuStage = SAVEMENU_WAIT;
                    }
                }
                break;
        }
        if (gMenuDelay) {
            transition_begin(&sMenuTransitionFadeIn);
        }
    }
    gIgnorePlayerInputTime = 0;
    return MENU_RESULT_CONTINUE;
}
void savemenu_free(void) {
    unload_font(ASSET_FONTS_BIGFONT);
    menu_button_free();
    menu_assetgroup_free(gSaveMenuObjectIndices);
    dialogue_clear(7);
    mempool_free((void *) gSaveMenuFilesSource);
    mempool_free((void *) D_80126A64);
    rumble_enable(1);
}
SIDeviceStatus func_80087F14(s32 *controllerIndex, s32 xAxisDirection) {
    s32 j;
    s32 k;
    s32 i;
    s32 pad;
    s32 paksWithStatusSuccess;
    s32 ret;
    u32 bytesFree;
    s32 notesFree;
    s32 paksWithNoFreeSpace;
    s32 paksWithFatalErrors;
    s32 paksWithBadData;
    paksWithFatalErrors = 0;
    paksWithNoFreeSpace = 0;
    paksWithBadData = 0;
    paksWithStatusSuccess = 0;
    for (i = 0; i <= 0; i++) {
        sControllerPakFatalErrorFound[i] = 0;
        sControllerPakNoFreeSpace[i] = 0;
        sControllerPakBadData[i] = 0;
        ret = get_free_space(i, &bytesFree, &notesFree);
        if (ret == CONTROLLER_PAK_GOOD) {
            sControllerPakIssueNotFound[i] = 1;
            if (bytesFree == 0 || notesFree == 0) {
                sControllerPakNoFreeSpace[i] = 1;
                if (sControllerPakDataPresent[i] == 0) {
                    paksWithNoFreeSpace++;
                }
            }
            paksWithStatusSuccess++;
        } else {
            ret &= 0xFF;
            sControllerPakIssueNotFound[i] = 0;
            if (ret == CONTROLLER_PAK_BAD_DATA) {
                sControllerPakBadData[i] = 1;
                paksWithBadData++;
            }
            if (ret == CONTROLLER_PAK_INCONSISTENT) {
                repair_controller_pak(i);
            }
            if (ret == CONTROLLER_PAK_WITH_BAD_ID) {
                sControllerPakFatalErrorFound[i] = 1;
                paksWithFatalErrors++;
            }
        }
    }
    if (paksWithStatusSuccess == 0 || paksWithFatalErrors != 0 || paksWithNoFreeSpace != 0 || paksWithBadData != 0) {
        return CONTROLLER_PAK_NOT_FOUND;
    }
    i = *controllerIndex;
    if (i < 0) {
        do {
            i++;
            if (i > 0) {
                i--;
            }
        } while (sControllerPakIssueNotFound[i] == 0);
    } else if (sControllerPakIssueNotFound[*controllerIndex] == 0 || xAxisDirection > 0) {
        do {
            i++;
            if (i > 0) {
                i--;
            }
        } while (sControllerPakIssueNotFound[i] == 0);
    } else if (xAxisDirection < 0) {
        do {
            i--;
            if (i < 0) {
                i++;
            }
        } while (sControllerPakIssueNotFound[i] == 0);
    }
    *controllerIndex = i;
    ret = get_controller_pak_file_list(*controllerIndex, 16, sCurrentControllerPakAllFileNames,
                                       sCurrentControllerPakAllFileExtensions, sCurrentControllerPakNumberOfPages,
                                       sCurrentControllerPakAllFileTypes);
    if (ret == CONTROLLER_PAK_GOOD) {
        for (i = 0; i < 16; i++) {
            sCurrentControllerPakNumberOfPages[i] /= (8 * 32);
            j = 0;
            if (sCurrentControllerPakAllFileNames[i] != 0) {
                k = 0;
                while (sCurrentControllerPakAllFileNames[i][k] != '\0') {
                    gBootPakData[i][j++] = sCurrentControllerPakAllFileNames[i][k++];
                }
                if (sCurrentControllerPakAllFileExtensions[i] != 0 &&
                    sCurrentControllerPakAllFileExtensions[i][0] != '\0') {
                    gBootPakData[i][j++] = '.';
                    k = 0;
                    while (sCurrentControllerPakAllFileExtensions[i][k] != '\0') {
                        gBootPakData[i][j++] = sCurrentControllerPakAllFileExtensions[i][k++];
                    }
                }
            }
            if (j == 0) {
                gBootPakData[i][j++] = '-';
            }
            gBootPakData[i][j] = '\0';
        }
        cpak_free_files();
        get_free_space(*controllerIndex, &sCurrentControllerPakFreePages, 0);
        sCurrentControllerPakFreePages /= (8 * 32);
    }
    return ret;
}
PakError check_for_controller_pak_errors(void) {
    s32 errorFound;
    s32 i;
    errorFound = 0;
    sControllerPakError = PAK_ERROR_NONE;
    for (i = 0; i <= 0 && errorFound == 0; i++) {
        if (sControllerPakFatalErrorFound[i]) {
            gControllerPakMenuElement[0].t.asciiText = gMenuText[ASSET_MENU_TEXT_PAKERROR];
            gControllerPakMenuElement[1].t.asciiText = gMenuText[ASSET_MENU_TEXT_PAKERROR];
            gControllerPakMenuElement[2].t.asciiText =
                gMenuText[ASSET_MENU_TEXT_CONTPAK1 + i];
            gControllerPakMenuElement[3].t.asciiText =
                gMenuText[ASSET_MENU_TEXT_CONTPAKISDAMAGED_0];
            gControllerPakMenuElement[4].t.asciiText = gMenuText[ASSET_MENU_TEXT_TURNOFFN64_0];
            gControllerPakMenuElement[5].t.asciiText =
                gMenuText[ASSET_MENU_TEXT_TURNOFFN64_1];
            sControllerPakError = PAK_ERROR_FATAL;
            errorFound = 1;
        } else if (sControllerPakNoFreeSpace[i] && sControllerPakDataPresent[i] == 0) {
            gControllerPakMenuElement[0].t.asciiText = gMenuText[ASSET_MENU_TEXT_CAUTION];
            gControllerPakMenuElement[1].t.asciiText = gMenuText[ASSET_MENU_TEXT_CAUTION];
            gControllerPakMenuElement[2].t.asciiText =
                gMenuText[ASSET_MENU_TEXT_CONTPAK1 + i];
            gControllerPakMenuElement[3].t.asciiText = gMenuText[ASSET_MENU_TEXT_CONTPAKFULL];
            gControllerPakMenuElement[4].t.asciiText = gMenuText[ASSET_MENU_TEXT_CONTINUE];
            gControllerPakMenuElement[5].t.asciiText = 0;
            sControllerPakDataPresent[i] = 1;
            sControllerPakError = PAK_ERROR_FULL;
            errorFound = 1;
        } else if (sControllerPakBadData[i]) {
            gControllerPakMenuElement[0].t.asciiText = gMenuText[ASSET_MENU_TEXT_CAUTION];
            gControllerPakMenuElement[1].t.asciiText = gMenuText[ASSET_MENU_TEXT_CAUTION];
            gControllerPakMenuElement[2].t.asciiText =
                gMenuText[ASSET_MENU_TEXT_CONTPAK1 + i];
            gControllerPakMenuElement[3].t.asciiText = gMenuText[ASSET_MENU_TEXT_CORRUPTDATA_0];
            gControllerPakMenuElement[4].t.asciiText = gMenuText[ASSET_MENU_TEXT_CORRUPTDATA_1];
            gControllerPakMenuElement[5].t.asciiText = 0;
            sControllerPakError = PAK_ERROR_CORRUPT;
            errorFound = 1;
        }
    }
    return sControllerPakError;
}
void menu_boot_init(void) {
    s32 i;
    transition_begin(&sMenuTransitionFadeOut);
    bgdraw_primcolour(0, 0, 0);
    menu_assetgroup_load(sGameTitleTileTextures);
    for (i = 0; i < (s32)(sizeof(sGameTitleTileOffsets) / sizeof(sGameTitleTileOffsets[0])) - 1; i++) {
        sGameTitleTileOffsets[i].texture = gMenuAssets[sGameTitleTileTextures[i]];
    }
    gBootMenuPhase = 0;
    gBootMenuTimer = 0;
}
s32 menu_boot_loop(s32 updateRate) {
    s32 out;
    s32 y;
    s32 offsetY;
    out = MENU_RESULT_CONTINUE;
    offsetY = (240 / 2);
    if (osTvType == 0) {
        offsetY = ((240 / 2) + 12);
    }
    y = offsetY;
    switch (gBootMenuPhase) {
        case 0:
            if (gBootMenuTimer < 32) {
                gBootMenuTimer += updateRate;
                if (gBootMenuTimer > 32) {
                    gBootMenuTimer = 32;
                }
            } else {
                bootscreen_init_cpak();
                gBootMenuPhase = 1;
            }
            break;
        case 1:
            if (gBootMenuTimer < 140) {
                gBootMenuTimer += updateRate;
                if (gBootMenuTimer > 140) {
                    gBootMenuTimer = 140;
                }
            } else {
                bootscreen_free();
                gBootMenuPhase = 2;
            }
            if (gBootMenuTimer > 128) {
                y = 300;
            }
            break;
        case 2:
            if (gMenuDelay && check_fadeout_transition() == 0) {
                transition_begin(&sMenuTransitionFadeInFast);
            }
            y = 300;
            out = menu_controller_pak_loop(updateRate);
            break;
    }
    if (y < 300) {
        texrect_draw(&sMenuCurrDisplayList, sGameTitleTileOffsets, (320 / 2), y, 255, 255, 255, 255);
        rendermode_reset(&sMenuCurrDisplayList);
    }
    return out;
}
void bootscreen_free(void) {
    menu_assetgroup_free((s16 *) sGameTitleTileTextures);
}
void bootscreen_init_cpak(void) {
    s32 i;
    gBootPakData[0] = mempool_alloc_safe(0x200, 0xFFFFFFFF);
    for (i = 1; i < (s32)(sizeof(gBootPakData) / sizeof(gBootPakData[0])); i++) {
        gBootPakData[i] = (char *) (((u32) gBootPakData[0]) + (i * (0x200 / (s32)(sizeof(gBootPakData) / sizeof(gBootPakData[0])))));
    }
    for (i = 0; i <= 0; i++) {
        sControllerPakDataPresent[i] = 0;
    }
    gCpakWriteTimer = 0;
    gMenuStage = PAKMENU_CHOOSE;
    gOptionBlinkTimer = 0;
    gMenuOption = -1;
    load_menu_text(get_language());
    if (func_80087F14(&gMenuOption, 0) == CONTROLLER_PAK_GOOD) {
        gMenuDelay = 0;
    } else if (check_for_controller_pak_errors() == PAK_ERROR_NONE) {
        gMenuDelay = 20;
    }
    if (sControllerPakError == PAK_ERROR_NONE && !gShowControllerPakMenu) {
        gMenuDelay = 20;
    }
    gMenuCurIndex = 0;
    gOpacityDecayTimer = 0;
    menu_asset_load(63);
    menu_init_arrow_textures();
    if (osTvType == 0) {
        sControllerPakMenuNumberOfRows = 8;
    } else {
        sControllerPakMenuNumberOfRows = 7;
    }
    load_font(ASSET_FONTS_BIGFONT);
    rumble_enable(0);
}
void pakmenu_render( s32 updateRate) {
    s32 highlight;
    s32 i;
    char *noteText;
    char *fileNameText;
    char *pagesText;
    s32 numberOfPages;
    s32 yPos = 0;
    set_text_background_colour(0, 0, 0, 0);
    highlight = gOptionBlinkTimer << 3;
    if (highlight >= 256) {
        highlight = 511 - highlight;
    }
    if (sControllerPakError != PAK_ERROR_NONE) {
        draw_menu_elements(1, gControllerPakMenuElement, 1.0f);
    } else if (gShowControllerPakMenu != 0) {
        set_text_font(ASSET_FONTS_BIGFONT);
        set_text_colour(0, 0, 0, 255, 128);
        draw_text(&sMenuCurrDisplayList, (320 / 2) + 1, 33, gMenuText[ASSET_MENU_TEXT_CONTPAK],
                  ALIGN_MIDDLE_CENTER);
        set_text_colour(255, 255, 255, 0, 255);
        draw_text(&sMenuCurrDisplayList, (320 / 2), 30, gMenuText[ASSET_MENU_TEXT_CONTPAK],
                  ALIGN_MIDDLE_CENTER);
        yPos += 48;
        dialogue_clear(6);
        set_current_dialogue_box_coords(6, 58, yPos, 262, yPos + 30);
        if (gMenuCurIndex == -1) {
            set_current_dialogue_background_colour(6, 255, 255, 255, (highlight >> 1) + 128);
        } else {
            set_current_dialogue_background_colour(6, 96, 192, 92, 224);
        }
        set_dialogue_font(6, ASSET_FONTS_FUNFONT);
        set_current_text_colour(6, 255, 255, 255, 0, 255);
        set_current_text_background_colour(6, 0, 0, 0, 0);
        render_dialogue_text(6, -0x8000, 2 - 0, gMenuText[ASSET_MENU_TEXT_CONTPAK1 + gMenuOption],
                             1, HORZ_ALIGN_CENTER);
        render_dialogue_text(6, -0x8000, 16 - 0, gMenuText[ASSET_MENU_TEXT_FREEPAGESX],
                             sCurrentControllerPakFreePages, HORZ_ALIGN_CENTER);
        render_dialogue_box(&sMenuCurrDisplayList, 0, 0, 6);
        yPos += 34;
        set_dialogue_font(6, ASSET_FONTS_SMALLFONT);
        set_current_text_background_colour(6, 0, 0, 0, 0);
        for (i = -1; i < sControllerPakMenuNumberOfRows; i++) {
            dialogue_clear(6);
            set_current_dialogue_box_coords(6, 28, yPos, 292, yPos + 14);
            if (i < 0) {
                set_current_dialogue_background_colour(6, 224, 48, 48, 224);
                set_current_text_colour(6, 224, 224, 48, 255, 255);
                noteText = gMenuText[ASSET_MENU_TEXT_NOTE];
                fileNameText = gMenuText[ASSET_MENU_TEXT_FILENAME];
                pagesText = gMenuText[ASSET_MENU_TEXT_PAGES];
                numberOfPages = 1;
            } else {
                if (gMenuCurIndex == (i + gOpacityDecayTimer)) {
                    set_current_dialogue_background_colour(6, 255, 255, 255, (highlight >> 1) + 128);
                } else {
                    set_current_dialogue_background_colour(6, 224, 224, 48, 224);
                }
                set_current_text_colour(6, 16, 16, 160, 255, 255);
                pagesText = noteText = "~";
                fileNameText = gBootPakData[gOpacityDecayTimer + i];
                numberOfPages = sCurrentControllerPakNumberOfPages[gOpacityDecayTimer + i];
            }
            render_dialogue_text(6, 26, 2, noteText, gOpacityDecayTimer + i + 1, HORZ_ALIGN_CENTER);
            render_dialogue_text(6, 56, 2, fileNameText, 1, HORZ_ALIGN_LEFT);
            render_dialogue_text(6, 240, 2, pagesText, numberOfPages, HORZ_ALIGN_CENTER);
            set_kerning(1);
            render_dialogue_box(&sMenuCurrDisplayList, 0, 0, 6);
            yPos += 16;
            set_kerning(0);
        }
        if (gOpacityDecayTimer < (16 - sControllerPakMenuNumberOfRows)) {
            if ((gOptionBlinkTimer & 8) != 0) {
                texrect_draw(&sMenuCurrDisplayList, gMenuSelectionArrowDown, (320 / 2), yPos + 8, 255, 255, 255,
                             255);
                rendermode_reset(&sMenuCurrDisplayList);
            }
        } else {
            set_text_font(ASSET_FONTS_FUNFONT);
            if (gMenuCurIndex == 16) {
                set_text_colour(255, 255, 255, highlight, 255);
            } else {
                set_text_colour(255, 255, 255, 0, 255);
            }
            draw_text(&sMenuCurrDisplayList, -0x8000, yPos, gMenuText[ASSET_MENU_TEXT_EXIT],
                      ALIGN_TOP_CENTER);
        }
        if (gMenuStage != PAKMENU_CHOOSE && gCpakWriteTimer == 0) {
            if (osTvType == 0) {
                yPos = 134;
            } else {
                yPos = (240 / 2);
            }
            dialogue_clear(6);
            set_dialogue_font(6, ASSET_FONTS_FUNFONT);
            set_current_dialogue_box_coords(6, 76, yPos - 28, 244, yPos + 28);
            set_current_dialogue_background_colour(6, 0, 0, 0, 160);
            yPos = 4;
            for (i = 0; i <= 2; i++) {
                if (i == 0) {
                    set_current_text_colour(6, 255, 0, 255, 64, 255);
                } else if (i == gMenuStage) {
                    set_current_text_colour(6, 255, 255, 255, highlight, 255);
                } else {
                    set_current_text_colour(6, 255, 255, 255, 0, 255);
                }
                render_dialogue_text(6, -0x8000, yPos, gMenuText[ASSET_MENU_TEXT_DELETENOTEX + i],
                                     gMenuCurIndex + 1, HORZ_ALIGN_CENTER);
                if (i != 0) {
                    yPos += 16;
                } else {
                    yPos += 20;
                }
            }
            render_dialogue_box(&sMenuCurrDisplayList, 0, 0, 6);
        }
        if (gCpakWriteTimer != 0) {
            set_text_colour(255, 255, 255, 0, 255);
            set_text_font(ASSET_FONTS_BIGFONT);
            draw_text(&sMenuCurrDisplayList, (320 / 2), 128, gMenuText[ASSET_MENU_TEXT_PLEASEWAIT],
                      ALIGN_MIDDLE_CENTER);
        }
    }
}
s32 menu_controller_pak_loop(s32 updateRate) {
    s32 i;
    s32 pressedButtons;
    s32 xStick;
    s32 yStick;
    s32 playMoveSound = 0;
    s32 playCancelSound = 0;
    s32 playSelectedSound = 0;
    s32 pad;
    s32 temp_v1_2;
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    if (gMenuDelay < 20) {
        pakmenu_render(updateRate);
    }
    if (gMenuDelay == 0) {
        pressedButtons = 0;
        xStick = 0;
        yStick = 0;
        for (i = 0; i < 4; i++) {
            pressedButtons |= input_pressed(i);
            xStick += gControllersXAxisDirection[i];
            yStick += gControllersYAxisDirection[i];
        }
        if (sControllerPakError != PAK_ERROR_NONE) {
            if (sControllerPakError != PAK_ERROR_FATAL && pressedButtons & (0x8000 | 0x1000)) {
                sound_play(SOUND_SELECT2, 0);
                if (func_80087F14(&gMenuOption, 0) == CONTROLLER_PAK_GOOD) {
                    sControllerPakError = PAK_ERROR_NONE;
                } else if (check_for_controller_pak_errors() == PAK_ERROR_NONE) {
                    gShowControllerPakMenu = 0;
                }
                if (sControllerPakError == PAK_ERROR_NONE && gShowControllerPakMenu == 0) {
                    playCancelSound = 1;
                    gMenuDelay = 1;
                    transition_begin(&sMenuTransitionFadeIn);
                }
            }
        } else {
            if (gMenuStage != PAKMENU_CHOOSE) {
                if (gCpakWriteTimer != 0) {
                    gCpakWriteTimer--;
                    if (gCpakWriteTimer == 0) {
                        if (delete_file(gMenuOption, gMenuCurIndex) != CONTROLLER_PAK_GOOD) {
                            playCancelSound = 1;
                            gMenuDelay = 1;
                            transition_begin(&sMenuTransitionFadeIn);
                        } else {
                            playSelectedSound = 1;
                            if (func_80087F14(&gMenuOption, xStick) != CONTROLLER_PAK_GOOD) {
                                playCancelSound = 1;
                                gMenuDelay = 1;
                                transition_begin(&sMenuTransitionFadeIn);
                            }
                        }
                        gMenuStage = PAKMENU_CHOOSE;
                    }
                } else if (pressedButtons & 0x4000) {
                    playCancelSound = 1;
                    gMenuStage = PAKMENU_CHOOSE;
                } else if (pressedButtons & (0x8000 | 0x1000)) {
                    if (gMenuStage == PAKMENU_CONFIRM) {
                        gCpakWriteTimer = 3;
                    } else {
                        playCancelSound = 1;
                        gMenuStage = PAKMENU_CHOOSE;
                    }
                } else if (yStick > 0 && gMenuStage > PAKMENU_CONFIRM) {
                    gMenuStage = PAKMENU_CONFIRM;
                    playMoveSound = 1;
                } else if (yStick < 0 && gMenuStage < PAKMENU_WRITE) {
                    gMenuStage = PAKMENU_WRITE;
                    playMoveSound = 1;
                }
            } else if (pressedButtons & 0x4000 ||
                       (gMenuCurIndex == 16 && pressedButtons & (0x8000 | 0x1000))) {
                playCancelSound = 1;
                gMenuDelay = 1;
                transition_begin(&sMenuTransitionFadeIn);
            } else {
                switch (gMenuCurIndex) {
                    case -1:
                        if (yStick < 0) {
                            if (!xStick) {}
                            gMenuCurIndex = 0;
                            playMoveSound = 1;
                        }
                        break;
                    case 16:
                        if (yStick > 0) {
                            gMenuCurIndex = 15;
                            playMoveSound = 1;
                        }
                        break;
                    default:
                        if (pressedButtons & (0x8000 | 0x1000)) {
                            if ((sCurrentControllerPakAllFileTypes[gMenuCurIndex] >= SAVE_FILE_TYPE_CPAK_SAVE) &&
                                (sCurrentControllerPakAllFileTypes[gMenuCurIndex] <= SAVE_FILE_TYPE_CPAK_OTHER)) {
                                gCpakWriteTimer = 0;
                                gMenuStage = PAKMENU_WRITE;
                                playSelectedSound = 1;
                            } else {
                                playCancelSound = 1;
                            }
                        } else {
                            if (yStick > 0) {
                                gMenuCurIndex--;
                                if (gMenuCurIndex < 0) {
                                    gMenuCurIndex = 0;
                                } else {
                                    playMoveSound = 1;
                                }
                            } else if (yStick < 0) {
                                gMenuCurIndex++;
                                playMoveSound = 1;
                            }
                        }
                        if (gMenuCurIndex >= (gOpacityDecayTimer + sControllerPakMenuNumberOfRows)) {
                            gOpacityDecayTimer = (gMenuCurIndex - sControllerPakMenuNumberOfRows) + 1;
                        }
                        if (gMenuCurIndex < gOpacityDecayTimer) {
                            gOpacityDecayTimer = gMenuCurIndex;
                        }
                        temp_v1_2 = 16 - sControllerPakMenuNumberOfRows;
                        if (temp_v1_2 < gOpacityDecayTimer) {
                            gOpacityDecayTimer = temp_v1_2;
                        }
                        if (gOpacityDecayTimer < 0) {
                            gOpacityDecayTimer = 0;
                        }
                        break;
                }
            }
        }
        if (playCancelSound) {
            sound_play(SOUND_MENU_BACK3, 0);
        } else if (playSelectedSound) {
            sound_play(SOUND_SELECT2, 0);
        } else if (playMoveSound) {
            sound_play(SOUND_MENU_PICK2, 0);
        }
    } else {
        gMenuDelay += updateRate;
        if (gMenuDelay >= 36) {
            pakmenu_free();
            menu_init(MENU_LOGOS);
            load_level_for_menu(ASSET_LEVEL_FRONTEND, ZERO_PLAYERS, 0x0);
        }
    }
    return 0;
}
void pakmenu_free(void) {
    menu_asset_free(TEXTURE_ICON_ARROW_DOWN);
    mempool_free(gBootPakData[0]);
    unload_font(ASSET_FONTS_BIGFONT);
    rumble_enable(1);
}
void menu_magic_codes_init(void) {
    gCheatInputCurrentRow = 0;
    gCheatInputCurrentColumn = 0;
    gOptionsMenuItemIndex = 0;
    gCheatInputStringLength = 0;
    sUnused_80126470 = 0;
    gNewCheatID = -1;
    gCheatInput[0] = '\0';
    gOptionBlinkTimer = 0;
    gMenuDelay = 0;
    gOpacityDecayTimer = 0;
    gMenuStage = CHEATMENU_CHOOSE;
    transition_begin(&sMenuTransitionFadeOut);
    set_current_dialogue_box_coords(7, 50, 50, 270, 132);
    set_current_dialogue_background_colour(7, 0, 0, 0, 128);
    dialogue_clear(7);
    load_font(ASSET_FONTS_BIGFONT);
}
void cheatmenu_render( s32 updateRate) {
    u16 *cheatData;
    s32 i, j;
    s32 highlight, highlight2, green;
    s32 xPos, yPos;
    char displayChar[2];
    s32 chr;
    s32 pad1;
    s32 offsetY;
    set_text_background_colour(0, 0, 0, 0);
    render_dialogue_box(&sMenuCurrDisplayList, 0, 0, 7);
    set_text_font(ASSET_FONTS_BIGFONT);
    set_text_colour(0, 0, 0, 255, 128);
    draw_text(&sMenuCurrDisplayList, (320 / 2) + 1, 35, gMenuText[ASSET_MENU_TEXT_MAGICCODES],
              ALIGN_MIDDLE_CENTER);
    set_text_colour(255, 255, 255, 0, 255);
    draw_text(&sMenuCurrDisplayList, (320 / 2), 32, gMenuText[ASSET_MENU_TEXT_MAGICCODES],
              ALIGN_MIDDLE_CENTER);
    chr = 'A';
    set_text_font(ASSET_FONTS_FUNFONT);
    set_text_colour(255, 255, 255, 0, 255);
    for (i = 0, yPos = 60; i < 4; i++, yPos += 22) {
        for (j = 0, xPos = 64; j < 7; j++, xPos += 32) {
            if (gOptionsMenuItemIndex == 5 && j == gCheatInputCurrentColumn && i == gCheatInputCurrentRow) {
                highlight = gOptionBlinkTimer * 8;
                if (highlight >= 256) {
                    highlight = 511 - highlight;
                }
                highlight >>= 1;
                highlight += 128;
                set_text_colour(128, 255, 192, highlight, 255);
            }
            if (chr <= 'Z') {
                displayChar[0] = chr;
                displayChar[1] = '\0';
                draw_text(&sMenuCurrDisplayList, xPos, yPos, displayChar, ALIGN_MIDDLE_CENTER);
            } else if (j == 5) {
                draw_text(&sMenuCurrDisplayList, xPos, yPos, "DEL", ALIGN_MIDDLE_CENTER);
            } else {
                draw_text(&sMenuCurrDisplayList, xPos, yPos, "OK", ALIGN_MIDDLE_CENTER);
            }
            if ((5 == gOptionsMenuItemIndex) && (j == gCheatInputCurrentColumn) && (i == gCheatInputCurrentRow)) {
                set_text_colour(255, 255, 255, 0, 255);
            }
            chr = (chr + 1) & 0xFF;
        }
    }
    highlight = gOptionBlinkTimer * 8;
    if (highlight > 255) {
        highlight = 511 - highlight;
    }
    set_text_font(ASSET_FONTS_FUNFONT);
    i = 0;
    offsetY = 164;
    yPos = 16;
    if (osTvType == 0) {
        yPos = 24;
    }
    while (gMagicCodeMenuStrings[i] != 0) {
        highlight2 = 0;
        if (i == gOptionsMenuItemIndex && gMenuStage == CHEATMENU_CHOOSE) {
            highlight2 = highlight;
        }
        set_text_colour(255, 255, 255, highlight2, 255);
        draw_text(&sMenuCurrDisplayList, -0x8000, offsetY, gMagicCodeMenuStrings[i], ALIGN_MIDDLE_CENTER);
        i++;
        offsetY += yPos;
    }
    set_text_font(ASSET_FONTS_FUNFONT);
    set_text_colour(255, 255, 128, 128, 255);
    set_text_background_colour(0, 0, 128, 128);
    if (gOptionsMenuItemIndex == 4) {
        if (gNewCheatID == -1) {
            draw_text(&sMenuCurrDisplayList, -0x8000, 144, gMenuText[ASSET_MENU_TEXT_BADCODE],
                      ALIGN_MIDDLE_CENTER);
        } else {
            cheatData = (*gCheatsAssetData) + 1;
            draw_text(&sMenuCurrDisplayList, -0x8000, 144,
                      &((char *) (*gCheatsAssetData))[cheatData[gNewCheatID + 1]], ALIGN_MIDDLE_CENTER);
        }
    } else if (5 == gOptionsMenuItemIndex) {
        draw_text(&sMenuCurrDisplayList, -0x8000, 144, gCheatInput, ALIGN_MIDDLE_CENTER);
    } else if (gOptionsMenuItemIndex == 6) {
        draw_text(&sMenuCurrDisplayList, -0x8000, 144, gMenuText[ASSET_MENU_TEXT_ALLCODESDELETED],
                  ALIGN_MIDDLE_CENTER);
    }
    if (gMenuStage != CHEATMENU_CHOOSE) {
        if (osTvType == 0) {
            offsetY = (240 / 2) + 14;
        } else {
            offsetY = (240 / 2);
        }
        dialogue_clear(6);
        set_dialogue_font(6, ASSET_FONTS_FUNFONT);
        set_current_dialogue_box_coords(6, 76, offsetY - 28, 244, offsetY + 28);
        set_current_dialogue_background_colour(6, 0, 0, 0, 160);
        offsetY = 4;
        for (i = 0; i < 3; i++) {
            green = 255;
            highlight2 = 0;
            if (i == 0) {
                green = 0;
                highlight2 = 64;
            } else if (i == gMenuStage) {
                highlight2 = highlight;
            }
            set_current_text_colour(6, 255, green, 255, highlight2, 255);
            render_dialogue_text(6, -0x8000, offsetY, gMenuText[148 + i], 1, HORZ_ALIGN_CENTER);
            if (i != 0) {
                offsetY += 16;
            } else {
                offsetY += 20;
            }
        }
        render_dialogue_box(&sMenuCurrDisplayList, 0, 0, 6);
    }
    if (get_filtered_cheats() & CHEAT_ROM_CHECKSUM) {
        cheatmenu_checksum();
    }
}
s32 menu_magic_codes_loop(s32 updateRate) {
    s32 i;
    s32 buttonsPressed;
    s32 xDir;
    s32 yDir;
    s32 someBool;
    s32 someBool2;
    s32 foundCheat;
    s32 menuDelay;
    s32 playBackSound;
    s32 playSelectSound;
    s32 playPickSound;
    s32 prevValue;
    char *cheatCodeText;
    u16 *cheatDataEntries;
    someBool = 0;
    someBool2 = 0;
    menuDelay = 0;
    foundCheat = 0;
    playBackSound = 0;
    playSelectSound = 0;
    playPickSound = 0;
    if (gOpacityDecayTimer != 0) {
        gOpacityDecayTimer -= updateRate;
        if (gOpacityDecayTimer < 0) {
            gOpacityDecayTimer = 0;
        }
    }
    if (gMenuDelay != 0) {
        if (gMenuDelay > 0) {
            gMenuDelay += updateRate;
        } else {
            gMenuDelay -= updateRate;
        }
    }
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    if (gMenuDelay > -20 && gMenuDelay < 20) {
        foundCheat = 0;
        cheatmenu_render(updateRate);
    }
    buttonsPressed = 0;
    xDir = 0;
    yDir = 0;
    if (gIgnorePlayerInputTime == 0 && gMenuDelay == 0) {
        for (i = 0; i < 4; i++) {
            buttonsPressed |= input_pressed(i);
            xDir += gControllersXAxisDirection[i];
            yDir += gControllersYAxisDirection[i];
        }
    }
    if (gOptionsMenuItemIndex == 4) {
        if (gOpacityDecayTimer == 0 || buttonsPressed & (0x8000 | 0x1000)) {
            gOptionsMenuItemIndex = 0;
        }
    } else if (gOptionsMenuItemIndex == 5) {
        prevValue = ((gCheatInputCurrentColumn & 0xF) * 16) | gCheatInputCurrentRow;
        if (xDir < 0) {
            gCheatInputCurrentColumn--;
            if (gCheatInputCurrentColumn < 0) {
                gCheatInputCurrentColumn = 6;
            }
        }
        if (xDir > 0) {
            gCheatInputCurrentColumn++;
            if (gCheatInputCurrentColumn > 6) {
                gCheatInputCurrentColumn = 0;
            }
        }
        if (yDir < 0) {
            gCheatInputCurrentRow++;
            if (gCheatInputCurrentRow > 3) {
                gCheatInputCurrentRow = 0;
            }
        }
        if (yDir > 0) {
            gCheatInputCurrentRow--;
            if (gCheatInputCurrentRow < 0) {
                gCheatInputCurrentRow = 3;
            }
        }
        if ((((gCheatInputCurrentColumn & 0xF) * 16) | gCheatInputCurrentRow) != prevValue) {
            playPickSound = 1;
        }
        if (buttonsPressed & 0x8000) {
            if (gCheatInputCurrentRow == 3 && gCheatInputCurrentColumn == 5) {
                someBool = 1;
            } else if (gCheatInputCurrentRow == 3 && gCheatInputCurrentColumn == 6) {
                someBool2 = 1;
            } else if (gCheatInputStringLength <= 18) {
                playSelectSound = 1;
                gCheatInput[gCheatInputStringLength] =
                    (gCheatInputCurrentRow * 7) + gCheatInputCurrentColumn + 'A';
                gCheatInputStringLength++;
                gCheatInput[gCheatInputStringLength] = '\0';
            }
        }
        if (buttonsPressed & 0x4000) {
            if (gCheatInputStringLength > 0) {
                someBool = 1;
            } else {
                gOptionsMenuItemIndex = 0;
            }
        }
        if (buttonsPressed & 0x1000) {
            someBool2 = 1;
        }
        if (someBool) {
            sound_play(SOUND_BOUNCE, 0);
            if (gCheatInputStringLength > 0) {
                gCheatInputStringLength--;
                gCheatInput[gCheatInputStringLength] = '\0';
            }
        }
        if (someBool2) {
            playSelectSound = 1;
            if (gCheatInputStringLength == 0) {
                gOptionsMenuItemIndex = 0;
            } else {
                cheatDataEntries = &(*gCheatsAssetData)[1];
                gNewCheatID = 0;
                while (gNewCheatID < gNumberOfCheats && foundCheat == 0) {
                    foundCheat = 1;
                    cheatCodeText = ((char *) (*gCheatsAssetData)) + cheatDataEntries[gNewCheatID * 3];
                    i = -1;
                    do {
                        i++;
                        if (cheatCodeText[i] != gCheatInput[i]) {
                            foundCheat = 0;
                        }
                        if (foundCheat == 0) {
                            break;
                        }
                    } while (cheatCodeText[i] != '\0' && gCheatInput[i] != '\0');
                    if (foundCheat) {
                        continue;
                    }
                    gNewCheatID += 1;
                }
                if (foundCheat == 0) {
                    gNewCheatID = -1;
                } else {
                    gUnlockedMagicCodes |= 1 << gNewCheatID;
                    gActiveMagicCodes |= 1 << gNewCheatID;
                    gNewCheatID *= 3;
                }
                gOptionsMenuItemIndex = 4;
                gOpacityDecayTimer = 240;
            }
        }
    } else if (gOptionsMenuItemIndex == 6) {
        if (gOpacityDecayTimer == 0 || buttonsPressed & (0x8000 | 0x1000)) {
            gOptionsMenuItemIndex = 1;
        }
    } else if (gMenuStage != CHEATMENU_CHOOSE) {
        if (buttonsPressed & (0x8000 | 0x1000)) {
            if (gMenuStage == CHEATMENU_KEYBOARD) {
                gActiveMagicCodes = 0;
                gOptionsMenuItemIndex = 6;
                playSelectSound = 1;
                gUnlockedMagicCodes &= CHEAT_CONTROL_TT | CHEAT_CONTROL_DRUMSTICK;
                gOpacityDecayTimer = 240;
            } else {
                playBackSound = 1;
            }
            gMenuStage = CHEATMENU_CHOOSE;
        } else if (buttonsPressed & 0x4000) {
            playBackSound = 1;
            gMenuStage = CHEATMENU_CHOOSE;
        } else if (yDir < 0 && gMenuStage == 1) {
            playPickSound = 1;
            gMenuStage = CHEATMENU_MESSAGE;
        } else if (yDir > 0 && gMenuStage == CHEATMENU_MESSAGE) {
            playPickSound = 1;
            gMenuStage = CHEATMENU_KEYBOARD;
        }
    } else {
        prevValue = gOptionsMenuItemIndex;
        if (yDir < 0) {
            gOptionsMenuItemIndex += 1;
            if (gOptionsMenuItemIndex > 3) {
                gOptionsMenuItemIndex = 3;
            }
        }
        if (yDir > 0) {
            gOptionsMenuItemIndex -= 1;
            if (gOptionsMenuItemIndex < 0) {
                gOptionsMenuItemIndex = 0;
            }
        }
        if (prevValue != gOptionsMenuItemIndex) {
            playPickSound = 1;
        }
        if (buttonsPressed & (0x8000 | 0x1000)) {
            playSelectSound = 1;
            if (gOptionsMenuItemIndex == 3) {
                menuDelay = -1;
            } else if (gOptionsMenuItemIndex == 0) {
                gCheatInputCurrentRow = 0;
                gCheatInputCurrentColumn = 0;
                gCheatInputStringLength = 0;
                gCheatInput[0] = '\0';
                gOptionsMenuItemIndex = 5;
            } else if (gOptionsMenuItemIndex == 1) {
                gMenuStage = CHEATMENU_MESSAGE;
            } else if (gOptionsMenuItemIndex == 2) {
                menuDelay = 1;
            }
        }
        if (buttonsPressed & (0x4000)) {
            menuDelay = -1;
        }
        if (menuDelay != 0) {
            if (menuDelay < 0) {
                playBackSound = 1;
            }
            gMenuDelay = menuDelay;
            transition_begin(&sMenuTransitionFadeIn);
        }
    }
    if (playBackSound) {
        sound_play(SOUND_MENU_BACK3, 0);
    } else if (playSelectSound) {
        sound_play(SOUND_SELECT2, 0);
    } else if (playPickSound) {
        sound_play(SOUND_MENU_PICK2, 0);
    }
    gIgnorePlayerInputTime = 0;
    if (gMenuDelay < -30 || gMenuDelay > 30) {
        cheatmenu_free();
        if (gMenuDelay < 0) {
            if (gActiveMagicCodes & CHEAT_DISPLAY_CREDITS) {
                music_change_on();
                gViewingCreditsFromCheat = 1;
                menu_init(MENU_CREDITS);
                gActiveMagicCodes &= ~CHEAT_DISPLAY_CREDITS;
            } else {
                menu_init(MENU_OPTIONS);
            }
        } else {
            menu_init(MENU_MAGIC_CODES_LIST);
        }
    }
    return MENU_RESULT_CONTINUE;
}
void cheatmenu_free(void) {
    unload_font(ASSET_FONTS_BIGFONT);
}
void menu_magic_codes_list_init(void) {
    gOptionBlinkTimer = 0;
    gMenuDelay = 0;
    gMenuStage = 0;
    gOptionsMenuItemIndex = 0;
    load_font(ASSET_FONTS_BIGFONT);
    menu_asset_load(63);
    menu_init_arrow_textures();
    transition_begin(&sMenuTransitionFadeOut);
    if (osTvType == 0) {
        gNumOnscreenMagicCodes = 11;
    } else {
        gNumOnscreenMagicCodes = 10;
    }
}
void cheatlist_render( s32 updateRate) {
    s32 i;
    s32 alpha;
    s32 yPos;
    s32 numOfUnlockedCheats;
    s32 code;
    u16 *cheatData;
    set_text_background_colour(0, 0, 0, 0);
    set_text_font(ASSET_FONTS_BIGFONT);
    set_text_colour(0, 0, 0, 255, 128);
    draw_text(&sMenuCurrDisplayList, (320 / 2) + 1, 35, gMenuText[ASSET_MENU_TEXT_MAGICCODESLIST],
              ALIGN_MIDDLE_CENTER);
    set_text_colour(255, 255, 255, 0, 255);
    draw_text(&sMenuCurrDisplayList, (320 / 2), 32, gMenuText[ASSET_MENU_TEXT_MAGICCODESLIST],
              ALIGN_MIDDLE_CENTER);
    for (i = 0, code = 1, numOfUnlockedCheats = 0; i < 32; i++, code <<= 1) {
        if (code & gUnlockedMagicCodes) {
            gUnlockedCheatIDs[numOfUnlockedCheats] = i;
            numOfUnlockedCheats += 1;
        }
    }
    yPos = 54;
    alpha = gOptionBlinkTimer * 8;
    if (alpha >= 256) {
        alpha = 511 - alpha;
    }
    set_text_font(ASSET_FONTS_FUNFONT);
    set_text_colour(255, 255, 255, 0, 255);
    for (i = gMenuStage, cheatData = (*gCheatsAssetData) + 1;
         (i < gMenuStage + gNumOnscreenMagicCodes) && (i < numOfUnlockedCheats); i++, yPos += 16) {
        if (i == gOptionsMenuItemIndex) {
            set_text_colour(255, 255, 255, alpha, 255);
        }
        draw_text(&sMenuCurrDisplayList, 48, yPos,
                  (char *) (*gCheatsAssetData) + cheatData[(gUnlockedCheatIDs[i] * 3) + 1], ALIGN_TOP_LEFT);
        if ((1 << gUnlockedCheatIDs[i]) & gActiveMagicCodes) {
            draw_text(&sMenuCurrDisplayList, 256, yPos, gMenuText[ASSET_MENU_TEXT_ON], ALIGN_TOP_LEFT);
        } else {
            draw_text(&sMenuCurrDisplayList, 256, yPos, gMenuText[ASSET_MENU_TEXT_OFF], ALIGN_TOP_LEFT);
        }
        if (i == gOptionsMenuItemIndex) {
            set_text_colour(255, 255, 255, 0, 255);
        }
    }
    if (i < gMenuStage + gNumOnscreenMagicCodes) {
        if (numOfUnlockedCheats == gOptionsMenuItemIndex) {
            set_text_colour(255, 255, 255, alpha, 255);
        }
        draw_text(&sMenuCurrDisplayList, -0x8000, yPos, gMenuText[ASSET_MENU_TEXT_RETURN],
                  ALIGN_TOP_CENTER);
        return;
    }
    if (gOptionBlinkTimer & 8) {
        texrect_draw(&sMenuCurrDisplayList, gMenuSelectionArrowDown, (320 / 2), yPos + 8, 255, 255, 255, 255);
    }
}
void cheatlist_exclusive(s32 code, s32 cheatA, s32 cheatB) {
    if ((code & cheatA) && (code & gActiveMagicCodes)) {
        gActiveMagicCodes &= ~cheatB;
    }
}
s32 menu_magic_codes_list_loop(s32 updateRate) {
    s32 previousMenuItemIndex;
    s32 xAxis;
    s32 yAxis;
    s32 delay;
    s32 buttonsPressed;
    s32 i;
    s32 numUnlockedCodes;
    s32 code;
    delay = 0;
    if (gMenuDelay != 0) {
        if (gMenuDelay > 0) {
            gMenuDelay += updateRate;
        } else {
            gMenuDelay -= updateRate;
        }
    }
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    if (gMenuDelay > -20 && gMenuDelay < 20) {
        cheatlist_render(updateRate);
    }
    buttonsPressed = 0;
    xAxis = 0;
    yAxis = 0;
    if (gIgnorePlayerInputTime == 0 && gMenuDelay == 0) {
        for (i = 0; i < 4; i++) {
            buttonsPressed |= input_pressed(i);
            xAxis += gControllersXAxisDirection[i];
            yAxis += gControllersYAxisDirection[i];
        }
    }
    for (i = 0, code = 1, numUnlockedCodes = 0; i < MAX_CHEATS; i++) {
        if (code & gUnlockedMagicCodes) {
            gUnlockedCheatIDs[numUnlockedCodes] = i;
            numUnlockedCodes++;
        }
        code <<= 1;
    }
    if ((xAxis < 0 || xAxis > 0) && numUnlockedCodes != gOptionsMenuItemIndex) {
        sound_play(SOUND_SELECT2, 0);
        code = 1 << gUnlockedCheatIDs[gOptionsMenuItemIndex];
        gActiveMagicCodes ^= code;
        cheatlist_exclusive(code, CHEAT_BIG_CHARACTERS, CHEAT_SMALL_CHARACTERS);
        cheatlist_exclusive(code, CHEAT_SMALL_CHARACTERS, CHEAT_BIG_CHARACTERS);
        cheatlist_exclusive(code, CHEAT_DISABLE_BANANAS,
                            CHEAT_NO_LIMIT_TO_BANANAS | CHEAT_BANANAS_REDUCE_SPEED | CHEAT_START_WITH_10_BANANAS);
        cheatlist_exclusive(code, CHEAT_NO_LIMIT_TO_BANANAS | CHEAT_BANANAS_REDUCE_SPEED | CHEAT_START_WITH_10_BANANAS,
                            CHEAT_DISABLE_BANANAS);
        cheatlist_exclusive(code, CHEAT_DISABLE_WEAPONS,
                            CHEAT_ALL_BALLOONS_ARE_RED | CHEAT_ALL_BALLOONS_ARE_GREEN | CHEAT_ALL_BALLOONS_ARE_BLUE |
                                CHEAT_ALL_BALLOONS_ARE_YELLOW | CHEAT_ALL_BALLOONS_ARE_RAINBOW |
                                CHEAT_MAXIMUM_POWER_UP);
        cheatlist_exclusive(code,
                            CHEAT_ALL_BALLOONS_ARE_RED | CHEAT_ALL_BALLOONS_ARE_GREEN | CHEAT_ALL_BALLOONS_ARE_BLUE |
                                CHEAT_ALL_BALLOONS_ARE_YELLOW | CHEAT_ALL_BALLOONS_ARE_RAINBOW | CHEAT_MAXIMUM_POWER_UP,
                            CHEAT_DISABLE_WEAPONS);
        cheatlist_exclusive(code, CHEAT_ALL_BALLOONS_ARE_RED,
                            CHEAT_ALL_BALLOONS_ARE_GREEN | CHEAT_ALL_BALLOONS_ARE_BLUE | CHEAT_ALL_BALLOONS_ARE_YELLOW |
                                CHEAT_ALL_BALLOONS_ARE_RAINBOW);
        cheatlist_exclusive(code, CHEAT_ALL_BALLOONS_ARE_GREEN,
                            CHEAT_ALL_BALLOONS_ARE_RED | CHEAT_ALL_BALLOONS_ARE_BLUE | CHEAT_ALL_BALLOONS_ARE_YELLOW |
                                CHEAT_ALL_BALLOONS_ARE_RAINBOW);
        cheatlist_exclusive(code, CHEAT_ALL_BALLOONS_ARE_BLUE,
                            CHEAT_ALL_BALLOONS_ARE_RED | CHEAT_ALL_BALLOONS_ARE_GREEN | CHEAT_ALL_BALLOONS_ARE_YELLOW |
                                CHEAT_ALL_BALLOONS_ARE_RAINBOW);
        cheatlist_exclusive(code, CHEAT_ALL_BALLOONS_ARE_YELLOW,
                            CHEAT_ALL_BALLOONS_ARE_RED | CHEAT_ALL_BALLOONS_ARE_GREEN | CHEAT_ALL_BALLOONS_ARE_BLUE |
                                CHEAT_ALL_BALLOONS_ARE_RAINBOW);
        cheatlist_exclusive(code, CHEAT_ALL_BALLOONS_ARE_RAINBOW,
                            CHEAT_ALL_BALLOONS_ARE_RED | CHEAT_ALL_BALLOONS_ARE_GREEN | CHEAT_ALL_BALLOONS_ARE_BLUE |
                                CHEAT_ALL_BALLOONS_ARE_YELLOW);
    }
    previousMenuItemIndex = gOptionsMenuItemIndex;
    if (yAxis < 0) {
        gOptionsMenuItemIndex++;
        if (numUnlockedCodes < gOptionsMenuItemIndex) {
            gOptionsMenuItemIndex = numUnlockedCodes;
        }
    }
    if (yAxis > 0) {
        gOptionsMenuItemIndex--;
        if (gOptionsMenuItemIndex < 0) {
            gOptionsMenuItemIndex = 0;
        }
    }
    if (gOptionsMenuItemIndex < gMenuStage) {
        gMenuStage = gOptionsMenuItemIndex;
    } else if (gOptionsMenuItemIndex >= (gMenuStage + gNumOnscreenMagicCodes)) {
        gMenuStage = (gOptionsMenuItemIndex - gNumOnscreenMagicCodes) + 1;
    }
    if (gOptionsMenuItemIndex != previousMenuItemIndex) {
        sound_play(SOUND_MENU_PICK2, 0);
    }
    if ((buttonsPressed & (0x8000 | 0x1000)) && (numUnlockedCodes == gOptionsMenuItemIndex)) {
        delay = -1;
    }
    if (buttonsPressed & 0x4000) {
        delay = -1;
    }
    if (delay != 0) {
        gMenuDelay = delay;
        transition_begin(&sMenuTransitionFadeIn);
        sound_play(SOUND_MENU_BACK3, 0);
    }
    if (gMenuDelay < -30) {
        cheatlist_free();
        menu_init(MENU_MAGIC_CODES);
        return MENU_RESULT_CONTINUE;
    }
    gIgnorePlayerInputTime = 0;
    return MENU_RESULT_CONTINUE;
}
void cheatlist_free(void) {
    menu_asset_free(TEXTURE_ICON_ARROW_DOWN);
    unload_font(ASSET_FONTS_BIGFONT);
}
void cheatmenu_checksum(void) {
    static u32 cksum = 0;
    static u32 calculated = 0;
    s32 blockOffs;
    s32 size;
    s32 numBytes, numLeft;
    s32 i;
    u8 *tempBuffer;
    if (!calculated) {
        numBytes = 0x1000;
        size = 0x5000;
        blockOffs = 0x1000;
        numLeft = (s32) &__ROM_END;
        numLeft -= 0x1000;
        tempBuffer = mempool_alloc_safe(size, 0x000000FF);
        while (numLeft != 0) {
            numBytes = numLeft;
            if (numBytes > size) {
                numBytes = size;
            }
            dmacopy(blockOffs, (u32) tempBuffer, numBytes);
            numLeft -= numBytes;
            for (i = 0; i < numBytes; i++) {
                cksum += tempBuffer[i];
            }
            blockOffs += numBytes;
        }
        mempool_free(tempBuffer);
        calculated = 1;
    }
    set_render_printf_background_colour(0, 0, 0, 128);
    set_render_printf_position(32, 136);
    numLeft = (s32) &__ROM_END;
    render_printf("ROM checksum %08X,%d\n", cksum, numLeft);
}
s32 gTrackSelectSound = 0;
s8 D_800E1E20[8] = { 0, -1, 1, 0, 0, 1, -1, 0 };
s8 gGameStatusVisible = 0;
s16 D_800E1E2C[10] = { 0x4C, 0x4D, 0x4E, 0x4F, 0x66, 0x67, 0x00, 0x42, -1, 0 };
s16 D_800E1E40[10] = { 0x0D, 0x0E, 0x0F, 0x10, 0x08, 0x09, 0x00, 0x0A, -1, 0 };
void charselect_prev(s32 context, s32 *arg1) {
    switch (context) {
        default:
            gEnteredCharSelectFrom = 0;
            return;
        case 1:
        case 3:
            gEnteredCharSelectFrom = 1;
            return;
        case 2:
            gEnteredCharSelectFrom = 2;
            unused_800DFFD4 = *arg1;
            return;
    }
}
void titlescreen_controller_assign(s32 controllerIndex) {
    s32 i;
    gNumberOfActivePlayers = 1;
    for (i = 0; i < (s32)(sizeof(gPlayersCharacterArray) / sizeof(gPlayersCharacterArray[0])); i++) {
        gPlayersCharacterArray[i] = (i == controllerIndex) ? 1 : -1;
    }
    for (i = 0; i < (s32)(sizeof(gActivePlayersArray) / sizeof(gActivePlayersArray[0])); i++) {
        gActivePlayersArray[i] = (i == controllerIndex) ? 1 : 0;
    }
}
void menu_character_select_init(void) {
    s32 breakTheLoop;
    s32 i;
    u8 *channelVolumes;
    breakTheLoop = 0;
    input_assign_players();
    if (is_drumstick_unlocked()) {
        if (is_tt_unlocked()) {
            gCurrCharacterSelectData = (CharacterSelectData(*)[10]) & gCharacterSelectBytesComplete;
        } else {
            gCurrCharacterSelectData = (CharacterSelectData(*)[10]) & gCharacterSelectBytesDrumStick;
        }
    } else if (is_tt_unlocked()) {
        gCurrCharacterSelectData = (CharacterSelectData(*)[10]) & gCharacterSelectBytesTT;
    } else {
        gCurrCharacterSelectData = (CharacterSelectData(*)[10]) & gCharacterSelectBytesDefault;
    }
    for (i = 0; i < (s32)(sizeof(gCharselectStatus) / sizeof(gCharselectStatus[0])); i++) {
        gCharselectStatus[i] = CHARSELECT_STATUS_UNCONFIRMED;
    }
    gNumberOfReadyPlayers = 0;
    gMenuDelay = 0;
    gOptionBlinkTimer = 0;
    D_800DF484 = 0;
    for (i = 0; i < (s32)(sizeof(gActivePlayersArray) / sizeof(gActivePlayersArray[0])) && !breakTheLoop; i++) {
        if (gActivePlayersArray[i] != 0) {
            breakTheLoop = 1;
            gMenuCurrentCharacter.channelIndex = (*gCurrCharacterSelectData)[gPlayersCharacterArray[i]].voiceID;
            gMenuCurrentCharacter.unk2 = 0x7F;
            gMenuCurrentCharacter.unk1 = 1;
        }
    }
    gMenuSelectedCharacter.channelIndex = -1;
    gMenuSelectedCharacter.unk2 = 0;
    gMenuSelectedCharacter.unk1 = 0;
    D_801263B8.channelIndex = -1;
    D_801263B8.unk2 = 0;
    D_801263B8.unk1 = 0;
    music_play(SEQUENCE_CHOOSE_YOUR_RACER);
    for (i = 0; i < 10; i++) {
        channelVolumes = gCharacterVolumes[i];
        if (i != gMenuCurrentCharacter.channelIndex) {
            music_channel_off(channelVolumes[0]);
            music_channel_off(channelVolumes[1]);
        }
    }
    music_channel_off(6);
    music_change_off();
    menu_assetgroup_load(gCharSelectObjectIndices);
    menu_imagegroup_load(gCharSelectImageIndices);
    transition_begin(&sMenuTransitionFadeOut);
    load_font(ASSET_FONTS_BIGFONT);
}
void charselect_render_text( s32 updateRate) {
    s32 yPos;
    if (gMenuDelay > -23 && gMenuDelay < 23) {
        set_text_font(ASSET_FONTS_BIGFONT);
        set_text_background_colour(0, 0, 0, 0);
        set_text_colour(0, 0, 0, 255, 128);
        draw_text(&sMenuCurrDisplayList, (320 / 2) + 1, 35, gMenuText[ASSET_MENU_TEXT_PLAYERSELECT],
                  ALIGN_MIDDLE_CENTER);
        set_text_colour(255, 255, 255, 0, 255);
        draw_text(&sMenuCurrDisplayList, (320 / 2), 32, gMenuText[ASSET_MENU_TEXT_PLAYERSELECT],
                  ALIGN_MIDDLE_CENTER);
        if (gNumberOfReadyPlayers == gNumberOfActivePlayers && gNumberOfActivePlayers > 0) {
            yPos = 208;
            if (osTvType == 0) {
                yPos = 234;
            }
            draw_text(&sMenuCurrDisplayList, (320 / 2), yPos, "OK?", ALIGN_MIDDLE_CENTER);
        }
        rendermode_reset(&sMenuCurrDisplayList);
        cam_set_fov(40.0f);
    }
}
void charselect_new_player(void) {
    s32 i;
    s32 j;
    s32 takenChar;
    s32 var_a2;
    for (i = 0; i < 4; i++) {
        if (!gActivePlayersArray[i]) {
            var_a2 = -1;
            if (gMenuButtons[i] & (0x8000 | 0x1000)) {
                do {
                    var_a2++;
                    takenChar = 1;
                    for (j = 0; (j < (s32)(sizeof(gActivePlayersArray) / sizeof(gActivePlayersArray[0]))) && takenChar; j++) {
                        if (gActivePlayersArray[j] && var_a2 == gPlayersCharacterArray[j]) {
                            takenChar = 0;
                        }
                    }
                } while (takenChar == 0);
                gPlayersCharacterArray[i] = var_a2;
                gActivePlayersArray[i] = 1;
                gNumberOfActivePlayers++;
                gMenuCurrentCharacter.channelIndex = (*gCurrCharacterSelectData)[gPlayersCharacterArray[i]].voiceID;
                gMenuCurrentCharacter.unk2 = 0;
                gMenuCurrentCharacter.unk1 = 20;
                sound_play(SOUND_SELECT2, 0);
            }
        }
    }
}
void charselect_pick(void) {
    s32 i;
    s32 characterSelected;
    s32 buttonsPressedAllPlayers;
    buttonsPressedAllPlayers = 0;
    for (i = 0; i < (s32)(sizeof(gActivePlayersArray) / sizeof(gActivePlayersArray[0])); i++) {
        if (gActivePlayersArray[i]) {
            buttonsPressedAllPlayers |= gMenuButtons[i];
        }
    }
    if (buttonsPressedAllPlayers & (0x8000 | 0x1000)) {
        gMenuDelay = 1;
        mark_read_all_save_files();
        transition_begin(&sMenuTransitionFadeIn);
        characterSelected = -1;
        for (i = 0; (i < 4) & (characterSelected < 0); i++) {
            if (gMenuButtons[i] & (0x8000 | 0x1000)) {
                characterSelected = i;
            }
        }
        if (gMenuSoundMasks[characterSelected] != 0) {
            sndp_stop(gMenuSoundMasks[characterSelected]);
        }
        sound_play((*gCurrCharacterSelectData)[gPlayersCharacterArray[characterSelected]].voiceID +
                       SOUND_VOICE_KRUNCH_POSITIVE6,
                   &gMenuSoundMasks[characterSelected]);
        if (gNumberOfActivePlayers > 2 ||
            (gNumberOfActivePlayers > 1 && !(gActiveMagicCodes & CHEAT_TWO_PLAYER_ADVENTURE)) ||
            gEnteredCharSelectFrom == 1) {
            music_fade(-128);
        }
    } else {
        for (i = 0; i < (s32)(sizeof(gActivePlayersArray) / sizeof(gActivePlayersArray[0])); i++) {
            if (gActivePlayersArray[i] && gCharselectStatus[i] != CHARSELECT_STATUS_UNCONFIRMED) {
                if (gMenuButtons[i] & 0x4000) {
                    gCharselectStatus[i] = CHARSELECT_STATUS_UNCONFIRMED;
                    gNumberOfReadyPlayers--;
                    if (gMenuSoundMasks[i] != 0) {
                        sndp_stop(gMenuSoundMasks[i]);
                    }
                    sound_play(((*gCurrCharacterSelectData)[gPlayersCharacterArray[i]].voiceID +
                                SOUND_VOICE_KRUNCH_EHH),
                               &gMenuSoundMasks[i]);
                }
            }
        }
    }
}
void charselect_input(s8 *activePlayers) {
    CharacterSelectData *charSelectData;
    s32 found;
    s32 i;
    s32 j;
    for (i = 0; i < 4; i++) {
        if (activePlayers[i] != 0) {
            if (gCharselectStatus[i] != CHARSELECT_STATUS_UNCONFIRMED) {
                if (gMenuButtons[i] & 0x4000) {
                    gCharselectStatus[i] = CHARSELECT_STATUS_UNCONFIRMED;
                    gNumberOfReadyPlayers -= 1;
                    if (gMenuSoundMasks[i] != 0) {
                        sndp_stop(gMenuSoundMasks[i]);
                    }
                    sound_play(((*gCurrCharacterSelectData)[gPlayersCharacterArray[i]].voiceID +
                                SOUND_VOICE_KRUNCH_EHH),
                               &gMenuSoundMasks[i]);
                }
            } else {
                if (gMenuButtons[i] & 0x4000) {
                    gNumberOfActivePlayers--;
                    gActivePlayersArray[i] = 0;
                    if (gNumberOfActivePlayers > 0) {
                        if (gMenuSelectedCharacter.channelIndex ==
                            (*gCurrCharacterSelectData)[gPlayersCharacterArray[i]].voiceID) {
                            if (gMenuCurrentCharacter.unk1 <= 0) {
                                for (found = 0, j = 0; j < (s32)(sizeof(gActivePlayersArray) / sizeof(gActivePlayersArray[0])) && !found; j++) {
                                    if (gActivePlayersArray[j]) {
                                        found = 1;
                                        gMenuCurrentCharacter.channelIndex =
                                            (*gCurrCharacterSelectData)[gPlayersCharacterArray[j]].voiceID;
                                        gMenuCurrentCharacter.unk2 = 0;
                                        gMenuCurrentCharacter.unk1 = 20;
                                    }
                                }
                            }
                        }
                    }
                    gPlayersCharacterArray[i] = -1;
                    if (gNumberOfActivePlayers <= 0) {
                        gMenuDelay = -1;
                        transition_begin(&sMenuTransitionFadeIn);
                    }
                } else if (gMenuButtons[i] & (0x8000 | 0x1000)) {
                    gCharselectStatus[i] = CHARSELECT_STATUS_CONFIRMED;
                    gNumberOfReadyPlayers++;
                    if (gMenuSoundMasks[i] != 0) {
                        sndp_stop(gMenuSoundMasks[i]);
                    }
                    sound_play(
                        ((*gCurrCharacterSelectData)[gPlayersCharacterArray[i]].voiceID + SOUND_VOICE_KRUNCH_SELECT),
                        &gMenuSoundMasks[i]);
                } else {
                    charSelectData = (*gCurrCharacterSelectData) + gPlayersCharacterArray[i];
                    if (gMenuStickY[i] > 0) {
                        charselect_move(i, charSelectData->upInput, (s32)(sizeof(charSelectData->upInput) / sizeof(charSelectData->upInput[0])),
                                        SOUND_MENU_PICK3, SOUND_HORN_DRUMSTICK);
                    } else if (gMenuStickY[i] < 0) {
                        charselect_move(i, charSelectData->downInput, (s32)(sizeof(charSelectData->downInput) / sizeof(charSelectData->downInput[0])),
                                        SOUND_MENU_PICK3, SOUND_HORN_DRUMSTICK);
                    } else if (gMenuStickX[i] < 0) {
                        charselect_move(i, charSelectData->rightInput, (s32)(sizeof(charSelectData->rightInput) / sizeof(charSelectData->rightInput[0])),
                                        SOUND_MENU_PICK3, SOUND_HORN_DRUMSTICK);
                    } else if (gMenuStickX[i] > 0) {
                        charselect_move(i, charSelectData->leftInput, (s32)(sizeof(charSelectData->leftInput) / sizeof(charSelectData->leftInput[0])),
                                        SOUND_MENU_PICK3, SOUND_HORN_DRUMSTICK);
                    }
                    if (charSelectData->voiceID != (*gCurrCharacterSelectData)[gPlayersCharacterArray[i]].voiceID) {
                        gMenuCurrentCharacter.channelIndex =
                            (*gCurrCharacterSelectData)[gPlayersCharacterArray[i]].voiceID;
                        gMenuCurrentCharacter.unk2 = 0;
                        gMenuCurrentCharacter.unk1 = 20;
                    }
                }
            }
        }
    }
}
void charselect_assign_ai(s32 charSlot) {
    s32 foundIt;
    s32 i, j;
    s32 numCharacters;
    numCharacters = 7;
    if (is_drumstick_unlocked()) {
        numCharacters++;
    }
    if (is_tt_unlocked()) {
        numCharacters++;
    }
    if (charSlot < 8) {
        foundIt = 0;
        for (i = 0; i < charSlot && !foundIt; i++) {
            if (gCharacterIdSlots[i] == CHARACTER_DIDDY) {
                foundIt = 1;
            }
        }
        if (!foundIt) {
            gCharacterIdSlots[charSlot] = CHARACTER_DIDDY;
            charSlot++;
        }
    }
    for (i = charSlot; i < 8; i++) {
        do {
            gCharacterIdSlots[i] = (*gCurrCharacterSelectData)[rand_range(0, numCharacters)].voiceID;
            for (j = 0, foundIt = 0; j < i; j++) {
                if (gCharacterIdSlots[j] == gCharacterIdSlots[i]) {
                    foundIt = 1;
                }
            }
        } while (foundIt);
    }
}
s32 menu_character_select_loop(s32 updateRate) {
    s32 i;
    s32 charSlot;
    s32 confirmOffset;
    s8 activePlayers[4];
    s32 j;
    charselect_render_text(updateRate);
    charselect_music_channels(updateRate);
    menu_input();
    for (i = 0; i < (s32)(sizeof(gCharselectStatus) / sizeof(gCharselectStatus[0])); i++) {
        if (gCharselectStatus[i] == CHARSELECT_STATUS_CONFIRMED) {
            gCharselectStatus[i] = CHARSELECT_STATUS_READY;
        }
    }
    gIgnorePlayerInputTime = 0;
    if (gMenuDelay == 0) {
        for (i = 0; i < (s32)(sizeof(gActivePlayersArray) / sizeof(gActivePlayersArray[0])); i++) { activePlayers[i] = gActivePlayersArray[i]; }
        charselect_new_player();
        if (gNumberOfReadyPlayers == gNumberOfActivePlayers) {
            charselect_pick();
        } else {
            charselect_input(activePlayers);
        }
        return MENU_RESULT_CONTINUE;
    } else if (gMenuDelay > 0) {
        gMenuDelay += updateRate;
        if (gMenuDelay > 30) {
            confirmOffset = 0;
            if (gEnteredCharSelectFrom == 0) {
                confirmOffset++;
                if (gActiveMagicCodes & CHEAT_TWO_PLAYER_ADVENTURE) {
                    confirmOffset++;
                }
            }
            charselect_free();
            charSlot = 0;
            for (j = 0; j < (s32)(sizeof(gActivePlayersArray) / sizeof(gActivePlayersArray[0])); j++) {
                if (gActivePlayersArray[j]) {
                    gCharacterIdSlots[charSlot] = (*gCurrCharacterSelectData)[gPlayersCharacterArray[j]].voiceID;
                    charSlot++;
                }
            }
            charselect_assign_ai(charSlot);
            charselect_assign_players(gActivePlayersArray);
            gIsInTracksMode = 1;
            if (confirmOffset >= gNumberOfActivePlayers) {
                music_change_off();
                load_level_for_menu(ASSET_LEVEL_OPTIONSBACKGROUND, -1, 0);
                if (gNumberOfActivePlayers == 1 && !gPlayerHasSeenCautionMenu) {
                    menu_init(MENU_CAUTION);
                } else {
                    menu_init(MENU_GAME_SELECT);
                }
            } else {
                music_change_on();
                trackmenu_set_records();
                init_racer_headers();
                menu_init(MENU_TRACK_SELECT);
            }
        }
    } else if (gMenuDelay < 0) {
        gMenuDelay -= updateRate;
        if (gMenuDelay < -30) {
            music_change_on();
            charselect_free();
            gNumberOfActivePlayers = 1;
            menu_init(MENU_TITLE);
        }
    }
    return MENU_RESULT_CONTINUE;
}
void charselect_move(s32 playerID, s8 *direction, s32 bounds, u16 menuPickSoundId, u16 menuPickFailedSoundId) {
    s32 sameCharSelected;
    s32 j;
    s32 i;
    j = 0;
    sameCharSelected = 1;
    while (sameCharSelected && j < bounds && direction[j] != -1) {
        sameCharSelected = 0;
        if (!(get_filtered_cheats() & CHEAT_SELECT_SAME_PLAYER)) {
            for (i = 0; i < 4 && !sameCharSelected; i++) {
                if (i != playerID && gPlayersCharacterArray[i] == direction[j]) {
                    sameCharSelected = 1;
                }
            }
            if (sameCharSelected) {
                j++;
            }
        }
    }
    if (!sameCharSelected) {
        gPlayersCharacterArray[playerID] = direction[j];
        sound_play(menuPickSoundId, 0);
    } else {
        sound_play(menuPickFailedSoundId, 0);
    }
}
void charselect_free(void) {
    menu_assetgroup_free(gCharSelectObjectIndices);
    mempool_free_timer(0);
    unload_font(ASSET_FONTS_BIGFONT);
    mempool_free_timer(2);
    gEnteredCharSelectFrom = 0;
}
void charselect_music_channels(s32 updateRate) {
    if (gMenuCurrentCharacter.unk1 > 0) {
        gMenuCurrentCharacter.unk1 -= updateRate;
        if (gMenuCurrentCharacter.unk1 <= 0) {
            if (D_801263B8.channelIndex >= 0) {
                music_channel_off(gCharacterVolumes[D_801263B8.channelIndex][0]);
                music_channel_off(gCharacterVolumes[0][D_801263B8.channelIndex * 2 + 1]);
            }
            D_801263B8.channelIndex = gMenuSelectedCharacter.channelIndex;
            if (gMenuSelectedCharacter.channelIndex >= 0) {
                D_801263B8.unk2 = gMenuSelectedCharacter.unk2;
            }
            gMenuSelectedCharacter.channelIndex = gMenuCurrentCharacter.channelIndex;
            if (gMenuSelectedCharacter.channelIndex >= 0) {
                gMenuSelectedCharacter.unk2 = gMenuCurrentCharacter.unk2;
                music_channel_on(gCharacterVolumes[gMenuSelectedCharacter.channelIndex][0]);
                music_channel_on(gCharacterVolumes[0][gMenuSelectedCharacter.channelIndex * 2 + 1]);
            }
        }
    }
    if (gMenuSelectedCharacter.channelIndex >= 0) {
        gMenuSelectedCharacter.unk2 += updateRate * 4;
        if (gMenuSelectedCharacter.unk2 > 127) {
            gMenuSelectedCharacter.unk2 = 127;
        }
        music_channel_fade_set(gCharacterVolumes[gMenuSelectedCharacter.channelIndex][0], gMenuSelectedCharacter.unk2);
        music_channel_fade_set(gCharacterVolumes[0][gMenuSelectedCharacter.channelIndex * 2 + 1],
                               gMenuSelectedCharacter.unk3);
    }
    if (D_801263B8.channelIndex >= 0) {
        D_801263B8.unk2 -= updateRate * 4;
        if (D_801263B8.channelIndex != gMenuSelectedCharacter.channelIndex) {
            if (D_801263B8.unk2 < 0) {
                music_channel_off(gCharacterVolumes[D_801263B8.channelIndex][0]);
                music_channel_off(gCharacterVolumes[0][D_801263B8.channelIndex * 2 + 1]);
            } else {
                music_channel_fade_set(gCharacterVolumes[D_801263B8.channelIndex][0], D_801263B8.unk2);
                music_channel_fade_set(gCharacterVolumes[0][D_801263B8.channelIndex * 2 + 1], D_801263B8.unk3);
            }
        }
        if (D_801263B8.unk2 < 0) {
            D_801263B8.channelIndex = -1;
        }
    }
}
void menu_caution_init(void) {
    gIgnorePlayerInputTime = 60;
    gMenuDelay = 0;
    load_font(ASSET_FONTS_BIGFONT);
    transition_begin(&sMenuTransitionFadeOut);
    gPlayerHasSeenCautionMenu = 1;
}
s32 menu_caution_loop(s32 updateRate) {
    if (gMenuDelay) {
        gMenuDelay += updateRate;
    } else if (gIgnorePlayerInputTime <= 0 && (input_pressed(PLAYER_ONE) & (0x8000 | 0x4000 | 0x1000))) {
        sound_play(SOUND_SELECT2, 0);
        gMenuDelay = 1;
        transition_begin(&sMenuTransitionFadeIn);
    }
    if (gMenuDelay < 20) {
        draw_menu_elements(1, gCautionMenuTextElements, 1.0f);
    }
    if (gMenuDelay > 30) {
        caution_free();
        menu_init(MENU_GAME_SELECT);
    }
    if (gIgnorePlayerInputTime > 0) {
        gIgnorePlayerInputTime -= updateRate;
    }
    return MENU_RESULT_CONTINUE;
}
void caution_free(void) {
    unload_font(ASSET_FONTS_BIGFONT);
}
void menu_game_select_init(void) {
    s32 i;
    gMenuDelay = 0;
    gOptionBlinkTimer = 0;
    gMenuCurIndex = 0;
    gMenuStage = 2;
    transition_begin(&sMenuTransitionFadeOut);
    mark_read_all_save_files();
    set_ghost_none();
    gOpacityDecayTimer = 1;
    menu_asset_load(67);
    func_8007FFEC(3);
    load_font(ASSET_FONTS_BIGFONT);
    music_play(SEQUENCE_CHOOSE_YOUR_RACER);
    for (i = 0; i < 10; i++) {
        if (i != gMenuSelectedCharacter.channelIndex) {
            music_channel_off(gCharacterVolumes[i][0]);
            music_channel_off(gCharacterVolumes[i][1]);
        }
    }
    music_channel_off(6);
    music_change_off();
    if (is_adventure_two_unlocked()) {
        gGameSelectElements = gGameSelectTextElemsWithAdv2;
        gMenuStage = 2;
    } else {
        gGameSelectElements = gGameSelectTextElemsNoAdv2;
        gMenuStage = 1;
    }
    for (i = 0; i <= gMenuStage; i++) {
        gGameSelectElements[((i ^ 0) * 2) + 2].t.texture = gMenuAssets[TEXTURE_SURFACE_BUTTON_WOOD];
    }
}
void gameselect_render( s32 updateRate) {
    s32 i;
    s32 filterBlendFactor;
    s32 fade;
    if (gMenuDelay > -22 && gMenuDelay < 22) {
        fade = gOptionBlinkTimer * 8;
        if (fade > 255) {
            fade = 511 - fade;
        }
        mtx_ortho(&sMenuCurrDisplayList, &sMenuCurrHudMat);
        for (i = 0; i <= gMenuStage; i++) {
            filterBlendFactor = 0;
            if (i == gMenuCurIndex) {
                filterBlendFactor = fade;
            }
            gGameSelectElements[((i ^ 0) * 2) + 3].filterBlendFactor = filterBlendFactor;
        }
        if (osTvType == 0) {
            gPostraceTextOffset = 12;
            gPostraceTimestampOffset = 0;
        } else {
            gPostraceTextOffset = 0;
            gPostraceTimestampOffset = 0;
        }
        draw_menu_elements(1, gGameSelectElements, 1.0f);
        func_80080BC8(&sMenuCurrDisplayList);
    }
}
s32 menu_game_select_loop(s32 updateRate) {
    s32 playerInputs;
    s32 playerYDir;
    s32 charSelectScene;
    charselect_music_channels(updateRate);
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    if (gOpacityDecayTimer) {
        gOpacityDecayTimer++;
        if (gOpacityDecayTimer >= 3) {
            trackmenu_set_records();
            gOpacityDecayTimer = 0;
        }
    }
    if (gMenuDelay != 0) {
        if (gMenuDelay < 0) {
            gMenuDelay -= updateRate;
        } else {
            gMenuDelay += updateRate;
        }
    }
    if (gMenuDelay > 30) {
        gameselect_free();
        if (gMenuCurIndex == gMenuStage) {
            music_change_on();
            gIsInTracksMode = 1;
            init_racer_headers();
            load_level_for_menu((s32) SPECIAL_MAP_ID_NO_LEVEL, -1, 0);
            menu_init(MENU_TRACK_SELECT);
        } else {
            gIsInAdventureTwo = gMenuCurIndex;
            gIsInTracksMode = 0;
            gPlayerSelectVehicle[PLAYER_ONE] = VEHICLE_CAR;
            set_level_default_vehicle(VEHICLE_CAR);
            menu_init(MENU_FILE_SELECT);
        }
        return MENU_RESULT_CONTINUE;
    } else if (gMenuDelay < -30) {
        gameselect_free();
        charSelectScene = 0;
        if (is_drumstick_unlocked()) {
            charSelectScene = 1;
        }
        if (is_tt_unlocked()) {
            charSelectScene ^= 3;
        }
        load_level_for_menu(ASSET_LEVEL_CHARACTERSELECT, -1, charSelectScene);
        charselect_prev(0, 0);
        menu_init(MENU_CHARACTER_SELECT);
        return MENU_RESULT_CONTINUE;
    } else {
        gameselect_render(updateRate);
        if ((gMenuDelay == 0) && (gOpacityDecayTimer == 0)) {
            playerInputs = input_pressed(PLAYER_ONE);
            playerYDir = gControllersYAxisDirection[0];
            if (gNumberOfActivePlayers == 2) {
                playerInputs |= input_pressed(1);
                playerYDir += gControllersYAxisDirection[1];
            }
            if (playerInputs & (0x8000 | 0x1000)) {
                if (gMenuCurIndex == gMenuStage) {
                    music_fade(-128);
                }
                transition_begin(&sMenuTransitionFadeIn);
                gMenuDelay = 1;
                sound_play(SOUND_SELECT2, 0);
            } else if (playerInputs & 0x4000) {
                transition_begin(&sMenuTransitionFadeIn);
                gMenuDelay = -1;
            } else {
                if (playerYDir < 0) {
                    if (gMenuCurIndex < gMenuStage) {
                        gMenuCurIndex++;
                        sound_play(SOUND_MENU_PICK2, 0);
                    }
                }
                if (playerYDir > 0) {
                    if (gMenuCurIndex > 0) {
                        gMenuCurIndex--;
                        sound_play(SOUND_MENU_PICK2, 0);
                    }
                }
            }
        }
        gIgnorePlayerInputTime = 0;
        return MENU_RESULT_CONTINUE;
    }
}
void gameselect_free(void) {
    unload_font(ASSET_FONTS_BIGFONT);
    menu_button_free();
    menu_asset_free(TEXTURE_SURFACE_BUTTON_WOOD);
}
void menu_file_select_init(void) {
    s32 i;
    s32 numLevels;
    s32 numWorlds;
    level_count(&numLevels, &numWorlds);
    menu_assetgroup_load(gFileSelectObjectIndices);
    menu_imagegroup_load(gFileSelectImageIndices);
    func_8007FFEC(6);
    mark_read_all_save_files();
    gOpacityDecayTimer = 1;
    gSaveFileIndex = 0;
    gMenuDelay = 0;
    gMenuStage = 0;
    gOptionBlinkTimer = 0;
    gFileCopy = 0;
    gFileErase = 0;
    gFileNew = 0;
    transition_begin(&sMenuTransitionFadeOut);
    load_font(ASSET_FONTS_BIGFONT);
    music_play(SEQUENCE_CHOOSE_YOUR_RACER);
    for (i = 0; i < 10; i++) {
        if (i != gMenuSelectedCharacter.channelIndex) {
            music_channel_off(gCharacterVolumes[i][0]);
            music_channel_off(gCharacterVolumes[i][1]);
        }
    }
    music_channel_off(6);
    music_change_off();
}
void fileselect_render_element(s32 imageID, s32 xOffset, s32 yOffset, s32 red, s32 green, s32 blue, s32 opacity) {
    s32 tempRed = sMenuGuiColourR;
    s32 tempGreen = sMenuGuiColourG;
    s32 tempBlue = sMenuGuiColourB;
    s32 tempOpacity = sMenuGuiOpacity;
    sMenuGuiColourR = red;
    sMenuGuiColourG = green;
    sMenuGuiColourB = blue;
    sMenuGuiOpacity = opacity;
    gMenuImages[imageID].trans.x_position = xOffset - 159;
    gMenuImages[imageID].trans.y_position = 119 - yOffset;
    menu_element_render(imageID);
    sMenuGuiColourR = tempRed;
    sMenuGuiColourG = tempGreen;
    sMenuGuiColourB = tempBlue;
    sMenuGuiOpacity = tempOpacity;
    gMenuImages[imageID].trans.x_position = xOffset - 161;
    gMenuImages[imageID].trans.y_position = 121 - yOffset;
    menu_element_render(imageID);
}
void fileselect_render( s32 updateRate) {
    s32 yPos;
    s32 var_s2;
    s32 glow;
    u32 colour;
    s32 i;
    s32 pad[3];
    char trimmedFilename[4];
    if (osTvType == 0) {
        yPos = 12;
    } else {
        yPos = 0;
    }
    menu_camera_centre();
    mtx_ortho(&sMenuCurrDisplayList, &sMenuCurrHudMat);
    for (i = 0; i < 3; i++) {
        if (gSavefileInfo[i].isAdventure2 == gIsInAdventureTwo || gSavefileInfo[i].isStarted == 0) {
            colour = ((u32)((176 << 24) | (224 << 16) | (192 << 8) | 255));
        } else {
            colour = ((u32)((106 << 24) | (144 << 16) | (115 << 8) | 255));
        }
        func_80080580(0, gFileSelectButtons[i].x - (320 / 2), (240 / 2) - gFileSelectButtons[i].y,
                      gFileSelectButtons[i].width, gFileSelectButtons[i].height, gFileSelectButtons[i].borderWidth,
                      gFileSelectButtons[i].borderHeight, colour, gMenuAssets[TEXTURE_SURFACE_BUTTON_WOOD]);
    }
    func_80080BC8(&sMenuCurrDisplayList);
    if (gOpacityDecayTimer == 0) {
        set_text_font(ASSET_FONTS_BIGFONT);
        set_text_background_colour(0, 0, 0, 0);
        for (i = 0; i < 3; i++) {
            if (gSavefileInfo[i].isStarted) {
                sprite_opaque(0);
                var_s2 = 11;
                if (gSavefileInfo[i].isAdventure2) {
                    var_s2 = 12;
                }
                fileselect_render_element(var_s2, gFileSelectButtons[i].x + gFileSelectElementPos[2],
                                          gFileSelectButtons[i].y + gFileSelectElementPos[3], 0, 0, 0, 128);
                cam_set_sprite_anim_mode(SPRITE_ANIM_FRAME_INDEX);
                gMenuImages->spriteOffset = gSavefileInfo[i].balloonCount / 10;
                fileselect_render_element(0, gFileSelectButtons[i].x + gFileSelectElementPos[6] - 6,
                                          gFileSelectButtons[i].y + gFileSelectElementPos[7], 0, 0, 0, 128);
                gMenuImages->spriteOffset = gSavefileInfo[i].balloonCount % 10;
                fileselect_render_element(0, gFileSelectButtons[i].x + gFileSelectElementPos[6] + 6,
                                          gFileSelectButtons[i].y + gFileSelectElementPos[7], 0, 0, 0, 128);
                cam_set_sprite_anim_mode(SPRITE_ANIM_NORMALIZED);
                sMenuGuiColourG = 64;
                sMenuGuiColourB = 64;
                fileselect_render_element(10, gFileSelectButtons[i].x + gFileSelectElementPos[8],
                                          gFileSelectButtons[i].y + gFileSelectElementPos[9], 0, 0, 0, 128);
                sMenuGuiColourG = 255;
                sMenuGuiColourB = 255;
                sprite_opaque(1);
            } else {
                set_text_colour(255, 255, 255, 64, 255);
                draw_text(&sMenuCurrDisplayList, gFileSelectButtons[i].x + gFileSelectElementPos[4],
                          gFileSelectButtons[i].y + gFileSelectElementPos[5] + yPos, gMenuText[ASSET_MENU_TEXT_NEW],
                          ALIGN_MIDDLE_CENTER);
            }
        }
    }
    glow = gOptionBlinkTimer * 8;
    if (glow > 255) {
        glow = 511 - glow;
    }
    set_text_font(ASSET_FONTS_FUNFONT);
    set_text_background_colour(0, 0, 0, 0);
    set_text_colour(255, 255, 255, 0, 255);
    for (i = 0; i < 3; i++) {
        var_s2 = 0;
        if (gFileCopy) {
            if (gFileConfirm == 0 && i == gSaveFileIndex3) {
                var_s2 = 1;
            } else if (gFileConfirm > 0 && i == gSaveFileIndex2) {
                var_s2 = 1;
            }
        } else if (gFileErase) {
            if (i == gSaveFileIndex3) {
                var_s2 = 1;
            }
        } else if (gMenuStage == 0 && i == gSaveFileIndex) {
            var_s2 = 1;
        }
        if (var_s2) {
            colour = glow | ~0xFF;
            func_80080E90(&sMenuCurrDisplayList, gFileSelectButtons[i].x, gFileSelectButtons[i].y + yPos,
                          gFileSelectButtons[i].width, gFileSelectButtons[i].height, gFileSelectButtons[i].borderWidth,
                          gFileSelectButtons[i].borderHeight, colour, colour, colour, colour);
        }
        if (!gFileNew || i != gSaveFileIndex) {
            filename_trim(gSavefileInfo[i].name, trimmedFilename);
            if (!gSavefileInfo[i].isStarted) {
                filename_trim(gFilenames[i], trimmedFilename);
            }
            if (trimmedFilename) {
                draw_text(&sMenuCurrDisplayList, gFileSelectButtons[i].x + gFileSelectElementPos[0],
                          gFileSelectButtons[i].y + gFileSelectElementPos[1] + yPos, trimmedFilename,
                          ALIGN_MIDDLE_CENTER);
            }
        }
    }
    set_text_font(ASSET_FONTS_BIGFONT);
    set_text_colour(0, 0, 0, 255, 128);
    draw_text(&sMenuCurrDisplayList, (320 / 2) + 1, 19, gMenuText[ASSET_MENU_TEXT_GAMESELECT + 112],
              ALIGN_TOP_CENTER);
    set_text_colour(255, 255, 255, 0, 255);
    draw_text(&sMenuCurrDisplayList, (320 / 2), 16, gMenuText[ASSET_MENU_TEXT_GAMESELECT + 112],
              ALIGN_TOP_CENTER);
    set_text_colour(255, 255, 255, 0, 255);
    yPos += 187;
    if (gFileCopy) {
        if (gFileConfirm == 0) {
            set_text_font(ASSET_FONTS_FUNFONT);
            draw_text(&sMenuCurrDisplayList, (320 / 2), yPos, gMenuText[ASSET_MENU_TEXT_GAMETOCOPY],
                      ALIGN_MIDDLE_CENTER);
        } else if (gFileConfirm == 1) {
            set_text_font(ASSET_FONTS_FUNFONT);
            draw_text(&sMenuCurrDisplayList, (320 / 2), yPos, gMenuText[ASSET_MENU_TEXT_GAMETOCOPYTO],
                      ALIGN_MIDDLE_CENTER);
        } else {
            draw_text(&sMenuCurrDisplayList, (320 / 2), yPos, "OK?", ALIGN_MIDDLE_CENTER);
        }
    } else if (gFileErase) {
        if (gFileConfirm == 0) {
            set_text_font(ASSET_FONTS_FUNFONT);
            draw_text(&sMenuCurrDisplayList, (320 / 2), yPos, gMenuText[ASSET_MENU_TEXT_GAMETOERASE],
                      ALIGN_MIDDLE_CENTER);
        } else {
            draw_text(&sMenuCurrDisplayList, (320 / 2), yPos, "OK?", ALIGN_MIDDLE_CENTER);
        }
    } else if (gFileNew == 0) {
        if (gMenuStage == 1) {
            set_text_colour(255, 255, 255, glow, 255);
        }
        draw_text(&sMenuCurrDisplayList, 90, yPos, gMenuText[ASSET_MENU_TEXT_COPY], ALIGN_MIDDLE_CENTER);
        if (gMenuStage == 2) {
            set_text_colour(255, 255, 255, glow, 255);
        } else {
            set_text_colour(255, 255, 255, 0, 255);
        }
        draw_text(&sMenuCurrDisplayList, 230, yPos, gMenuText[ASSET_MENU_TEXT_ERASE], ALIGN_MIDDLE_CENTER);
    }
}
s32 fileselect_input_root( s32 updateRate) {
    u32 buttonsPressed;
    s32 xAxisDirection;
    s32 yAxisDirection;
    s32 prevOption;
    u32 buttonsPressedPlayer2;
    buttonsPressed = input_pressed(PLAYER_ONE);
    xAxisDirection = gControllersXAxisDirection[PLAYER_ONE];
    yAxisDirection = gControllersYAxisDirection[PLAYER_ONE];
    if (gNumberOfActivePlayers == 2) {
        buttonsPressedPlayer2 = input_pressed(PLAYER_TWO);
        buttonsPressed |= buttonsPressedPlayer2;
        xAxisDirection += gControllersXAxisDirection[PLAYER_TWO];
        yAxisDirection += gControllersYAxisDirection[PLAYER_TWO];
    }
    if (buttonsPressed & (0x8000 | 0x1000)) {
        switch (gMenuStage) {
            case 0:
                if (gSavefileInfo[gSaveFileIndex].isStarted) {
                    if (gIsInAdventureTwo != gSavefileInfo[gSaveFileIndex].isAdventure2) {
                        sound_play(SOUND_HORN_DRUMSTICK, 0);
                        break;
                    }
                }
                sound_play(SOUND_SELECT2, 0);
                return 1;
            case 1:
                sound_play(SOUND_SELECT2, 0);
                gSaveFileIndex3 = gSaveFileIndex;
                gFileCopy = 1;
                gFileConfirm = 0;
                return 0;
            case 2:
                sound_play(SOUND_SELECT2, 0);
                gSaveFileIndex3 = gSaveFileIndex;
                gFileErase = 1;
                gFileConfirm = 0;
                return 0;
        }
    } else if (buttonsPressed & 0x4000) {
        return -1;
    }
    prevOption = (gMenuStage << 8) | gSaveFileIndex;
    if (gMenuStage == 0) {
        if (xAxisDirection < 0 && gSaveFileIndex > 0) {
            gSaveFileIndex--;
        }
        if (xAxisDirection > 0 && (gSaveFileIndex < 2)) {
            gSaveFileIndex++;
        }
        if (yAxisDirection < 0) {
            if (gSaveFileIndex >= 2) {
                gMenuStage = 2;
            } else {
                gMenuStage = 1;
            }
        }
    } else {
        if (xAxisDirection < 0 && gMenuStage == 2) {
            gMenuStage = 1;
        }
        if (xAxisDirection > 0 && gMenuStage == 1) {
            gMenuStage = 2;
        }
        if (yAxisDirection > 0) {
            if (gMenuStage == 1 && gSaveFileIndex >= 2) {
                gSaveFileIndex = 0;
            }
            if (gMenuStage == 2 && gSaveFileIndex <= 0) {
                gSaveFileIndex = 2;
            }
            gMenuStage = 0;
        }
    }
    if (prevOption != ((gMenuStage << 8) | gSaveFileIndex)) {
        sound_play(SOUND_MENU_PICK2, 0);
    }
    return 0;
}
void fileselect_input_copy( s32 updateRate) {
    s32 prevOption;
    u32 buttonsPressed;
    s32 xAxisDirection;
    s32 i;
    Settings *settings;
    u32 buttonsPressedPlayerTwo;
    settings = get_settings();
    buttonsPressed = input_pressed(PLAYER_ONE);
    xAxisDirection = gControllersXAxisDirection[PLAYER_ONE];
    if (gNumberOfActivePlayers == 2) {
        buttonsPressedPlayerTwo = input_pressed(PLAYER_TWO);
        buttonsPressed |= buttonsPressedPlayerTwo;
        xAxisDirection += gControllersXAxisDirection[PLAYER_TWO];
    }
    if (gFileConfirm == 0) {
        if (buttonsPressed & (0x4000)) {
            sound_play(SOUND_MENU_BACK3, 0);
            gFileCopy = 0;
            return;
        }
        if (buttonsPressed & (0x8000 | 0x1000)) {
            if (gSavefileInfo[gSaveFileIndex3].isStarted) {
                sound_play(SOUND_SELECT2, 0);
                mark_read_save_file(gSaveFileIndex3);
                gSaveFileIndex2 = gSaveFileIndex3;
                gFileConfirm = 1;
                return;
            }
            sound_play(SOUND_MENU_BACK3, 0);
            return;
        }
        prevOption = gSaveFileIndex3;
        if ((xAxisDirection < 0) && (gSaveFileIndex3 > 0)) {
            gSaveFileIndex3--;
        }
        if ((xAxisDirection > 0) && (gSaveFileIndex3 < 2)) {
            gSaveFileIndex3++;
        }
        if (prevOption != gSaveFileIndex3) {
            sound_play(SOUND_MENU_PICK2, 0);
        }
    } else if (gFileConfirm == 1) {
        if (buttonsPressed & 0x4000) {
            sound_play(SOUND_MENU_BACK3, 0);
            gSaveFileIndex3 = gSaveFileIndex2;
            gFileConfirm = 0;
            return;
        }
        if (buttonsPressed & (0x8000 | 0x1000)) {
            if (!gSavefileInfo[gSaveFileIndex2].isStarted) {
                sound_play(SOUND_SELECT2, 0);
                gFileConfirm = 2;
                return;
            }
            sound_play(SOUND_MENU_BACK3, 0);
            return;
        }
        prevOption = gSaveFileIndex2;
        if (xAxisDirection < 0 && gSaveFileIndex2 > 0) {
            gSaveFileIndex2--;
        }
        if (xAxisDirection > 0 && gSaveFileIndex2 < 2) {
            gSaveFileIndex2++;
        }
        if (prevOption != gSaveFileIndex2) {
            sound_play(SOUND_MENU_PICK2, 0);
        }
    } else {
        if (buttonsPressed & (0x8000 | 0x1000)) {
            sound_play(SOUND_SELECT2, 0);
            force_mark_write_save_file(gSaveFileIndex2);
            gSavefileInfo[gSaveFileIndex2].isAdventure2 = 0;
            gSavefileInfo[gSaveFileIndex2].isStarted = 1;
            gSavefileInfo[gSaveFileIndex2].balloonCount = *settings->balloonsPtr;
            if (settings->cutsceneFlags & 0x4) {
                gSavefileInfo[gSaveFileIndex2].isAdventure2 = 1;
            }
            for (i = 0; gSavefileInfo[gSaveFileIndex3].name[i] != '\0'; i++) {
                gSavefileInfo[gSaveFileIndex2].name[i] = gSavefileInfo[gSaveFileIndex3].name[i];
            }
            gSavefileInfo[gSaveFileIndex2].name[i] = '\0';
            gSaveFileIndex = gSaveFileIndex2;
            gMenuStage = 0;
            gFileCopy = 0;
        } else if (buttonsPressed & 0x4000) {
            sound_play(SOUND_MENU_BACK3, 0);
            gFileConfirm = 1;
        }
    }
}
void fileselect_input_erase( s32 updateRate) {
    s32 buttonsPressed;
    s32 controllerXAxisDirection;
    s32 prevOption;
    buttonsPressed = input_pressed(PLAYER_ONE);
    controllerXAxisDirection = gControllersXAxisDirection[0];
    if (gNumberOfActivePlayers == 2) {
        buttonsPressed |= input_pressed(PLAYER_TWO);
        controllerXAxisDirection += gControllersXAxisDirection[1];
    }
    if (gFileConfirm == 0) {
        if (buttonsPressed & 0x4000) {
            sound_play(SOUND_MENU_BACK3, 0);
            gFileErase = 0;
            return;
        } else if (buttonsPressed & (0x8000 | 0x1000)) {
            if (gSavefileInfo[gSaveFileIndex3].isStarted != 0) {
                sound_play(SOUND_SELECT2, 0);
                gFileConfirm = 1;
                return;
            }
            sound_play(SOUND_MENU_BACK3, 0);
            return;
        }
        prevOption = gSaveFileIndex3;
        if (controllerXAxisDirection < 0) {
            if (gSaveFileIndex3 > 0) {
                gSaveFileIndex3--;
            }
        }
        if (controllerXAxisDirection > 0) {
            if (gSaveFileIndex3 < 2) {
                gSaveFileIndex3++;
            }
        }
        if (gSaveFileIndex3 != prevOption) {
            sound_play(SOUND_MENU_PICK2, 0);
        }
    } else {
        if (buttonsPressed & (0x8000 | 0x1000)) {
            sound_play(SOUND_SELECT2, 0);
            mark_save_file_to_erase(gSaveFileIndex3);
            gSavefileInfo[gSaveFileIndex3].isAdventure2 = 0;
            gSavefileInfo[gSaveFileIndex3].isStarted = 0;
            gSavefileInfo[gSaveFileIndex3].balloonCount = 0;
            gSavefileInfo[gSaveFileIndex3].name[0] = 'D';
            gSavefileInfo[gSaveFileIndex3].name[1] = 'K';
            gSavefileInfo[gSaveFileIndex3].name[2] = 'R';
            gSavefileInfo[gSaveFileIndex3].name[3] = '\0';
            gSaveFileIndex = gSaveFileIndex3;
            gMenuStage = 0;
            gFileErase = 0;
        } else if (buttonsPressed & 0x4000) {
            sound_play(SOUND_MENU_BACK3, 0);
            gFileConfirm = 0;
        }
    }
}
s32 menu_file_select_loop(s32 updateRate) {
    s32 i;
    s32 currentMenuDelay;
    u32 buttonsPressed;
    Settings *settings;
    settings = get_settings();
    charselect_music_channels(updateRate);
    if (gOpacityDecayTimer) {
        gOpacityDecayTimer++;
        if (gOpacityDecayTimer >= 3) {
            for (i = 0; i < 3; i++) {
                gSavefileInfo[i].isAdventure2 = 0;
                if (gSavefileData[i]->newGame) {
                    gSavefileInfo[i].isStarted = 0;
                    gSavefileInfo[i].balloonCount = 0;
                    gSavefileInfo[i].name[0] = 'D';
                    gSavefileInfo[i].name[1] = 'K';
                    gSavefileInfo[i].name[2] = 'R';
                    gSavefileInfo[i].name[3] = '\0';
                } else {
                    if (gSavefileData[i]->cutsceneFlags & 0x4) {
                        gSavefileInfo[i].isAdventure2 = 1;
                    }
                    gSavefileInfo[i].isStarted = 1;
                    gSavefileInfo[i].balloonCount = *gSavefileData[i]->balloonsPtr;
                    filename_decompress(gSavefileData[i]->filename, gSavefileInfo[i].name, 3);
                }
            }
            gOpacityDecayTimer = 0;
        }
    }
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3f;
    if (gMenuDelay != 0) {
        if (gMenuDelay > 0) {
            gMenuDelay += updateRate;
        } else {
            gMenuDelay -= updateRate;
        }
    }
    if (gMenuDelay >= -20 && gMenuDelay <= 20) {
        fileselect_render(updateRate);
    }
    if (gMenuDelay == 0 && gOpacityDecayTimer == 0) {
        if (gFileCopy) {
            fileselect_input_copy(updateRate);
        } else if (gFileErase) {
            fileselect_input_erase(updateRate);
        } else if (gFileNew) {
            buttonsPressed = input_pressed(PLAYER_ONE);
            if (buttonsPressed & 0x4000 && gNameEntryLength == 0) {
                menu_unload_bigfont();
                gFileNew = 0;
                gSavefileInfo[i].name[0] = 'D';
                gSavefileInfo[i].name[1] = 'K';
                gSavefileInfo[i].name[2] = 'R';
                gSavefileInfo[i].name[3] = '\0';
            } else if (filename_enter(updateRate)) {
                menu_unload_bigfont();
                gFileNew = 0;
                gSavefileInfo[gSaveFileIndex].isAdventure2 = 0;
                if (gIsInAdventureTwo) {
                    gSavefileInfo[gSaveFileIndex].isAdventure2 = 1;
                }
                gSavefileInfo[gSaveFileIndex].isStarted = 1;
                gSavefileInfo[gSaveFileIndex].balloonCount = 0;
                settings->filename = filename_compress(gSavefileInfo[gSaveFileIndex].name, 3);
                mark_read_save_file(gSaveFileIndex);
                music_fade(-128);
                transition_begin(&sMenuTransitionFadeIn);
                gMenuDelay = 1;
            }
        } else {
            currentMenuDelay = fileselect_input_root(updateRate);
            if (currentMenuDelay != 0) {
                if (currentMenuDelay > 0) {
                    if (gSavefileInfo[gSaveFileIndex].isStarted != 0) {
                        sound_play(SOUND_SELECT2, 0);
                        mark_read_save_file(gSaveFileIndex);
                        music_fade(-128);
                    } else {
                        gFileNew = 1;
                        gIndexOfCurInputCharacter = 0;
                        i = 0;
                        if (osTvType == 0) {
                            i = 12;
                        }
                        filename_init(i + 187, gFileSelectButtons[gSaveFileIndex].x + gFileSelectElementPos[0],
                                      gFileSelectButtons[gSaveFileIndex].y + gFileSelectElementPos[1] + i, 0,
                                      &gIndexOfCurInputCharacter, gSavefileInfo[gSaveFileIndex].name, 3);
                        currentMenuDelay = 0;
                    }
                }
                if (currentMenuDelay != 0) {
                    transition_begin(&sMenuTransitionFadeIn);
                    gMenuDelay = currentMenuDelay;
                }
            }
        }
    }
    if (gMenuDelay > 35) {
        if (gActiveMagicCodes & CHEAT_FREE_BALLOON) {
            gActiveMagicCodes &= ~CHEAT_FREE_BALLOON;
            gUnlockedMagicCodes &= ~CHEAT_FREE_BALLOON;
            (*settings->balloonsPtr)++;
        }
        gIsInTwoPlayerAdventure = (gNumberOfActivePlayers == 2);
        if (gIsInTwoPlayerAdventure) {
            reset_lead_player_index();
        }
        gNumberOfActivePlayers = 1;
        D_800E0FAC = 1;
        fileselect_free();
        music_change_on();
        init_racer_headers();
        gTrophyRaceWorldId = 0;
        if (settings->newGame) {
            if (gIsInAdventureTwo) {
                settings->cutsceneFlags |= 0x4;
            }
            cinematic_start((s8 *) get_misc_asset(ASSET_MISC_CINEMATIC_RACE), 0, gNumberOfActivePlayers, 0, 0, 0);
            menu_init(MENU_NEWGAME_CINEMATIC);
            return MENU_RESULT_CONTINUE;
        }
        if (settings->cutsceneFlags & 0x4) {
            gIsInAdventureTwo = 1;
        } else {
            gIsInAdventureTwo = 0;
        }
        return gNumberOfActivePlayers;
    }
    if (gMenuDelay < -35) {
        fileselect_free();
        menu_init(MENU_GAME_SELECT);
        return MENU_RESULT_CONTINUE;
    } else {
        return MENU_RESULT_CONTINUE;
    }
}
void fileselect_free(void) {
    menu_assetgroup_free(gFileSelectObjectIndices);
    menu_button_free();
    unload_font(ASSET_FONTS_BIGFONT);
}
void menu_init_vehicle_textures(void) {
    gRaceSelectionCarTex[0].texture = gMenuAssets[TEXTURE_ICON_VEHICLE_CAR_TOP];
    gRaceSelectionCarTex[1].texture = gMenuAssets[TEXTURE_ICON_VEHICLE_CAR_BOTTOM];
    gRaceSelectionHoverTex[0].texture = gMenuAssets[TEXTURE_ICON_VEHICLE_HOVERCRAFT_TOP];
    gRaceSelectionHoverTex[1].texture = gMenuAssets[TEXTURE_ICON_VEHICLE_HOVERCRAFT_BOTTOM];
    gRaceSelectionPlaneTex[0].texture = gMenuAssets[TEXTURE_ICON_VEHICLE_PLANE_TOP];
    gRaceSelectionPlaneTex[1].texture = gMenuAssets[TEXTURE_ICON_VEHICLE_PLANE_BOTTOM];
}
void menu_init_arrow_textures(void) {
    gMenuSelectionArrowUp[0].texture = gMenuAssets[TEXTURE_ICON_ARROW_UP];
    gMenuSelectionArrowLeft[0].texture = gMenuAssets[TEXTURE_ICON_ARROW_LEFT];
    gMenuSelectionArrowDown[0].texture = gMenuAssets[TEXTURE_ICON_ARROW_DOWN];
    gMenuSelectionArrowRight[0].texture = gMenuAssets[TEXTURE_ICON_ARROW_RIGHT];
}
void menu_input(void) {
    s32 i;
    s32 buttonsHeld[4 + 1];
    if (gIgnorePlayerInputTime == 0) {
        for (i = 0; i < 4 + 1; i++) {
            buttonsHeld[i] = 0;
            gMenuStickX[i] = 0;
            gMenuStickY[i] = 0;
        }
        for (i = 0; i < 4; i++) {
            buttonsHeld[i] = input_held(i);
            gMenuStickX[i] = gControllersXAxisDirection[i];
            gMenuStickY[i] = gControllersYAxisDirection[i];
            if (i < gNumberOfActivePlayers) {
                buttonsHeld[4] |= buttonsHeld[i];
                gMenuStickX[4] += gControllersXAxisDirection[i];
                gMenuStickY[4] += gControllersYAxisDirection[i];
            }
        }
        for (i = 0; i < 4 + 1; i++) {
            gMenuButtons[i] = buttonsHeld[i] & ~buttonsPressed[i];
            buttonsPressed[i] = buttonsHeld[i];
        }
        return;
    }
    for (i = 0; i < 4 + 1; i++) {
        buttonsPressed[i] = (0x1000 | 0x4000 | 0x8000);
        gMenuButtons[i] = 0;
        gMenuStickX[i] = 0;
        gMenuStickY[i] = 0;
    }
}
 s32 trackmenu_active(void) {
    return gIsInTracksMenu;
}
void menu_track_select_init(void) {
    s32 levelCount;
    s32 worldCount;
    s32 sp74;
    s32 i;
    s32 j;
    s32 var_a0;
    Settings *settings;
    s8 *trackIds;
    load_font(ASSET_FONTS_BIGFONT);
    settings = get_settings();
    level_count(&levelCount, &worldCount);
    trackIds = (s8 *) get_misc_asset(ASSET_MISC_TRACKS_MENU_IDS);
    if (gTitleScreenLoaded != 0) {
        gTrackSelectCursorX = 0;
        gTrackSelectCursorY = 0;
        gTracksMenuTimeTrialHighlightIndex = 0;
        gTracksMenuAdventureHighlightIndex = 0;
        gTitleScreenLoaded = 0;
    }
    gTrackSelectViewPortX = fb_size();
    gTrackSelectViewportY = (gTrackSelectViewPortX >> 16) & 0xFFFF;
    gTrackSelectViewPortX = (gTrackSelectViewPortX & 0xFFFF);
    gTrackSelectViewPortHalfX = gTrackSelectViewPortX >> 1;
    gTrackSelectViewPortHalfY = gTrackSelectViewportY >> 1;
    gTrackSelectX = (f32) gTrackSelectCursorX * 320.0f;
    gTrackSelectY = (f32) gTrackSelectCursorY * (f32) -gTrackSelectViewportY;
    gSelectedTrackX = -1;
    gSelectedTrackY = -1;
    gTrackmenuLoadedLevel = -1;
    gOpacityDecayTimer = 32;
    gOptionBlinkTimer = 0;
    gTrackmenuType = TRACKMENU_TYPE_INIT;
    trackmenu_assets(0);
    transition_begin(&sMenuTransitionFadeOut);
    enable_new_screen_transitions();
    bgdraw_fillcolour(50, 105, 223);
    for (sp74 = 0; sp74 < 5; sp74++) {
        if (gTracksMenuBgTextureIndices[sp74 * 3] != -1) {
            menu_asset_load(gTracksMenuBgTextureIndices[sp74 * 3]);
            gTracksMenuBgTextures[sp74 << 1] = gMenuAssets[gTracksMenuBgTextureIndices[sp74 * 3]];
        } else {
            gTracksMenuBgTextures[sp74 << 1] = 0;
        }
        if (gTracksMenuBgTextureIndices[sp74 * 3 + 1] != -1) {
            menu_asset_load(gTracksMenuBgTextureIndices[sp74 * 3 + 1]);
            gTracksMenuBgTextures[(sp74 << 1) + 1] = gMenuAssets[gTracksMenuBgTextureIndices[sp74 * 3 + 1]];
        } else {
            gTracksMenuBgTextures[(sp74 << 1) + 1] = 0;
        }
    }
    i = 40;
    gTrackSelectBgTriangles[0] = mempool_alloc_safe(0xB40, 0xFFFF00FF);
    gTrackSelectBgTriangles[1] = gTrackSelectBgTriangles[0] + i;
    gTrackSelectBgVertices[0] = (Vertex *) (gTrackSelectBgTriangles[1] + i);
    gTrackSelectBgVertices[1] = gTrackSelectBgVertices[0] + i * 2;
    var_a0 = -160;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 80; j++) {
            gTrackSelectBgVertices[i][j].x = var_a0;
            gTrackSelectBgVertices[i][j].z = -0x400;
            gTrackSelectBgVertices[i][j].r = 255;
            gTrackSelectBgVertices[i][j].g = 255;
            gTrackSelectBgVertices[i][j].b = 255;
            var_a0 = -var_a0;
        }
    }
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 40; j++) {
            gTrackSelectBgTriangles[i][j].flags = 0x40;
            gTrackSelectBgTriangles[i][j].vi0 = 0;
            gTrackSelectBgTriangles[i][j].vi1 = 2;
            gTrackSelectBgTriangles[i][j].vi2 = 1;
            j++;
            gTrackSelectBgTriangles[i][j].flags = 0x40;
            gTrackSelectBgTriangles[i][j].vi0 = 1;
            gTrackSelectBgTriangles[i][j].vi1 = 2;
            gTrackSelectBgTriangles[i][j].vi2 = 3;
        }
    }
    gTrackSelectVertsFlip = 0;
    bgdraw_set_func(func_8008F618);
    viewport_menu_set(0, 80, gTrackSelectViewPortHalfY - (gTrackSelectViewPortHalfY >> 1), 240,
                      (gTrackSelectViewPortHalfY >> 1) + gTrackSelectViewPortHalfY);
    copy_viewports_to_stack();
    camEnableUserView(0, 0);
    gIsInTracksMenu = 1;
    menu_assetgroup_load(gTrackSelectObjectIndices);
    menu_imagegroup_load(gTrackSelectImageIndices);
    menu_init_arrow_textures();
    D_800E05D4[0].texture = (TextureHeader *) gMenuAssets[TEXTURE_UNK_08];
    D_800E05D4[1].texture = (TextureHeader *) gMenuAssets[TEXTURE_UNK_09];
    D_800E05D4[2].texture = (TextureHeader *) gMenuAssets[TEXTURE_UNK_0A];
    D_800E05F4[0].texture = (TextureHeader *) gMenuAssets[TEXTURE_UNK_0B];
    D_800E05F4[1].texture = (TextureHeader *) gMenuAssets[TEXTURE_UNK_0C];
    D_800E05F4[2].texture = (TextureHeader *) gMenuAssets[TEXTURE_UNK_0D];
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 6; j++) {
            gTrackSelectIDs[i][j] = -1;
            if (j == 0 && i < 4) {
                gTrackSelectIDs[i][j] = trackIds[((i * 6) + j)];
            } else if (j < 4) {
                if (trackIds[((i * 6) + j)] != -1 &&
                    (settings->courseFlagsPtr[trackIds[((i * 6) + j)]] & RACE_VISITED)) {
                    gTrackSelectIDs[i][j] = trackIds[((i * 6) + j)];
                }
            } else if (j == 4) {
                for (var_a0 = 0, sp74 = 0; (var_a0 < 4) ^ 0; var_a0++) {
                    if (trackIds[((i * 6) + var_a0)] != -1 &&
                        ((settings->courseFlagsPtr[trackIds[((i * 6) + var_a0)]] &
                          (RACE_CLEARED | RACE_CLEARED_SILVER_COINS)) == (RACE_CLEARED | RACE_CLEARED_SILVER_COINS))) {
                        sp74++;
                    }
                }
                if (sp74 == 4 && i != 4) {
                    if ((settings->bosses & (0x82 << i)) != (0x82 << i)) {
                        sp74 = 0;
                    }
                }
                if (sp74 == 4) {
                    gTrackSelectIDs[i][j] = trackIds[((i * 6) + j)];
                }
            } else if (j == 5 && (settings->keys & (1 << (i + 1)))) {
                gTrackSelectIDs[i][j] = trackIds[((i * 6) + j)];
            }
            if (is_adventure_two_unlocked()) {
                gTrackSelectIDs[i][j] = trackIds[((i * 6) + j)];
            }
        }
    }
    gTrackIdForPreview = gTrackSelectIDs[gTrackSelectCursorY][gTrackSelectCursorX];
    gTrackSelectRow = gTrackSelectCursorY + 1;
    if (gTrackIdForPreview == -1) {
        gTrackmenuLoadedLevel = gTrackSelectIDs[0][0];
        load_level_for_menu(gTrackmenuLoadedLevel, -1, 1);
        gTrackSelectRow = 1;
        gSelectedTrackX = 0;
        gSelectedTrackY = 0;
    }
    dialogue_clear(7);
    func_8007FFEC(2);
    gTrackTTSoundMask = 0;
    D_80126848 = 0;
    sMenuMusicVolume = 0;
    music_voicelimit_set(24);
    music_voicelimit_change_off();
    music_play(SEQUENCE_MAIN_MENU);
    music_volume_set(sMenuMusicVolume);
    music_change_off();
    set_gIntDisFlag(1);
    gIsInAdventureTwo = gTracksMenuAdventureHighlightIndex;
    gMultiplayerSelectedNumberOfRacersCopy = gMultiplayerSelectedNumberOfRacers;
}
void trackmenu_assets(s32 type) {
    Vehicle vehicle;
    s32 i;
    s32 newType;
    if (gTrackmenuType != TRACKMENU_TYPE_INIT && gTrackmenuType != TRACKMENU_TYPE_RESET_CURSOR &&
        gTrackmenuType == TRACKMENU_TYPE_FREE) {
        menu_assetgroup_free(gTrackSelectPreviewObjectIndices);
    }
    gTrackmenuType = type;
    newType = gTrackmenuType;
    if (newType > TRACKMENU_TYPE_INIT && newType <= TRACKMENU_TYPE_FREE) {
        switch (gTrackmenuType) {
            case TRACKMENU_TYPE_RESET_CURSOR:
                gTrackSelectTargetX = gTrackSelectX;
                gTrackSelectTargetY = gTrackSelectY;
                break;
            case TRACKMENU_TYPE_FREE:
                vehicle = leveltable_vehicle_default(gTrackIdForPreview);
                for (i = 0; i < gNumberOfActivePlayers; i++) {
                    gPlayerSelectConfirm[i] = 0;
                    gPlayerSelectVehicle[i] = vehicle;
                }
                gNumberOfReadyPlayers = 0;
                gTrackNameVoiceDelay = 1;
                menu_assetgroup_load(gTrackSelectPreviewObjectIndices);
                menu_imagegroup_load(gTrackSelectPreviewImageIndices);
                menu_init_vehicle_textures();
                gRaceSelectionTTOn[0].texture = gMenuAssets[TEXTURE_ICON_TIMETRIAL_ON_TOP];
                gRaceSelectionTTOn[1].texture = gMenuAssets[TEXTURE_ICON_TIMETRIAL_ON_BOTTOM];
                gRaceSelectionTTOff[0].texture = gMenuAssets[TEXTURE_ICON_TIMETRIAL_OFF_TOP];
                gRaceSelectionTTOff[1].texture = gMenuAssets[TEXTURE_ICON_TIMETRIAL_OFF_BOTTOM];
                gRaceSelectionCarOptHighlight[0].texture = gMenuAssets[TEXTURE_ICON_VEHICLE_SELECT_CAR_HIGHLIGHT];
                gRaceSelectionCarOpt[0].texture = gMenuAssets[TEXTURE_ICON_VEHICLE_SELECT_CAR];
                gRaceSelectionHoverOptHighlight[0].texture =
                    gMenuAssets[TEXTURE_ICON_VEHICLE_SELECT_HOVERCRAFT_HIGHLIGHT];
                gRaceSelectionHoverOpt[0].texture = gMenuAssets[TEXTURE_ICON_VEHICLE_SELECT_HOVERCRAFT];
                gRaceSelectionPlaneOptHighlight[0].texture = gMenuAssets[TEXTURE_ICON_VEHICLE_SELECT_PLANE_HIGHLIGHT];
                gRaceSelectionPlaneOpt[0].texture = gMenuAssets[TEXTURE_ICON_VEHICLE_SELECT_PLANE];
                gRaceSelectionTTOnOptHighlight[0].texture = gMenuAssets[TEXTURE_ICON_TIMETRIAL_OPT_ON];
                gRaceSelectionTTOffOptHighlight[0].texture = gMenuAssets[TEXTURE_ICON_TIMETRIAL_OPT_ON_HIGHLIGHT];
                gRaceSelectionTTOnOpt[0].texture = gMenuAssets[TEXTURE_ICON_TIMETRIAL_OPT_OFF];
                gRaceSelectionTTOffOpt[0].texture = gMenuAssets[TEXTURE_ICON_TIMETRIAL_OPT_OFF_HIGHLIGHT];
                gRaceSelectionPlayer1Texture[0].texture = gMenuAssets[TEXTURE_ICON_PLAYER_1];
                gRaceSelectionPlayer2Texture[0].texture = gMenuAssets[TEXTURE_ICON_PLAYER_2];
                gRaceSelectionPlayer3Texture[0].texture = gMenuAssets[TEXTURE_ICON_PLAYER_3];
                gRaceSelectionPlayer4Texture[0].texture = gMenuAssets[TEXTURE_ICON_PLAYER_4];
                gRaceSelectionVehicleTitleTexture[0].texture = gMenuAssets[TEXTURE_ICON_VEHICLE_TITLE];
                gRaceSelectionTTTitleTexture[0].texture = gMenuAssets[TEXTURE_ICON_TT_TITLE];
                gRaceSelectionTTTexture[0].texture = gMenuAssets[TEXTURE_UNK_69];
                break;
        }
    }
    gMenuDelay = 0;
}
s32 menu_track_select_loop(s32 updateRate) {
    s32 cutsceneId;
    Settings *settings;
    settings = get_settings();
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    if (bgload_active() == 0 && gMenuDelay != 0) {
        if (gMenuDelay < 0) {
            gMenuDelay -= updateRate;
        } else {
            gMenuDelay += updateRate;
        }
    }
    menu_input();
    { Gfx *_g = (Gfx *)(sMenuCurrDisplayList++); _g->words.w0 = ((unsigned int) (((unsigned int)((-65 -9)) & ((0x01 << (8)) - 1)) << (24))); _g->words.w1 = (unsigned int)(0x00001000); };
    switch (gTrackmenuType) {
        case TRACKMENU_TYPE_RESET_CURSOR:
            func_8008FF1C(updateRate);
            trackmenu_track_view(updateRate);
            trackmenu_input(updateRate);
            break;
        case TRACKMENU_TYPE_FREE:
            trackmenu_timetrial_sound(updateRate);
            trackmenu_setup_render(updateRate);
            func_80092188(updateRate);
            break;
    }
    if (sMenuMusicVolume < 0) {
        music_volume_set(0);
    } else {
        sMenuMusicVolume += updateRate * 2;
        if (sMenuMusicVolume >= 81) {
            sMenuMusicVolume = 80;
        }
        music_volume_set(sMenuMusicVolume);
    }
    if (gTrackmenuType <= TRACKMENU_TYPE_INIT) {
        menu_track_select_unload();
        gTrackSpecifiedWithTrackIdToLoad = 0;
        if (gNumberOfActivePlayers >= 3 ||
            (gNumberOfActivePlayers == 2 && !(gActiveMagicCodes & CHEAT_TWO_PLAYER_ADVENTURE))) {
            cutsceneId = 0;
            if (is_drumstick_unlocked()) {
                cutsceneId = 1;
            }
            if (is_tt_unlocked()) {
                cutsceneId ^= 3;
            }
            load_level_for_menu(ASSET_LEVEL_CHARACTERSELECT, -1, cutsceneId);
            charselect_prev(0, 0);
            menu_init(MENU_CHARACTER_SELECT);
            return MENU_RESULT_CONTINUE;
        }
        load_level_for_menu(ASSET_LEVEL_OPTIONSBACKGROUND, -1, 0);
        menu_init(MENU_GAME_SELECT);
        return MENU_RESULT_CONTINUE;
    }
    if (gTrackmenuType >= TRACKMENU_TYPE_LOAD_LEVEL) {
        menu_track_select_unload();
        if (gMultiplayerSelectedNumberOfRacersCopy != gMultiplayerSelectedNumberOfRacers) {
            for (cutsceneId = 0; cutsceneId < 8; cutsceneId++) {
                settings->racers[cutsceneId].starting_position = cutsceneId;
            }
        }
        if (gTrackSelectCursorX != 4) {
            gTrackSpecifiedWithTrackIdToLoad = 1;
            return gNumberOfActivePlayers;
        }
        gTrophyRaceWorldId = gTrackSelectCursorY + 1;
        gInAdvModeTrophyRace = 0;
        gTrophyRaceRound = 0;
        menu_init(MENU_TROPHY_RACE_ROUND);
        return MENU_RESULT_CONTINUE;
    }
    gIgnorePlayerInputTime = 0;
    return MENU_RESULT_CONTINUE;
}
void menu_track_select_unload(void) {
    s32 i;
    camDisableUserView(0, 0);
    menu_assetgroup_free(gTrackSelectObjectIndices);
    mempool_free_timer(0);
    mempool_free(gTrackSelectBgTriangles[0]);
    mempool_free_timer(2);
    for (i = 0; i < 15; i += 3) {
        if (gTracksMenuBgTextureIndices[i] != -1) {
            menu_asset_free(gTracksMenuBgTextureIndices[i]);
        }
        if (gTracksMenuBgTextureIndices[i + 1] != -1) {
            menu_asset_free(gTracksMenuBgTextureIndices[i + 1]);
        }
    }
    unload_font(ASSET_FONTS_BIGFONT);
    menu_button_free();
    music_change_on();
    music_voicelimit_change_on();
    music_stop();
    set_gIntDisFlag(0);
}
s32 func_8008F618(Gfx **dList, Mtx **mtx) {
    s32 sp7C;
    s32 yPos;
    s32 texU;
    s32 texV;
    s32 flags;
    s32 hasTexture;
    s32 index;
    s32 prevAlpha;
    s32 prevIndex;
    s32 numVertices;
    s32 temp;
    s32 temp2;
    Vertex *tempVertices;
    Triangle *triangles;
    Triangle *tempTriangles;
    Vertex *vertices;
    TextureHeader *bgTexture;
    s32 curIndex;
    numVertices = 0;
    camDisableUserView(0, 1);
    camera_init_tracks_menu(dList, mtx);
    mtx_ortho(dList, mtx);
    rendermode_reset(dList);
    { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = ((unsigned int) (((unsigned int)(0xe7) & ((0x01 << (8)) - 1)) << (24))); _g->words.w1 = 0; };
    sp7C = gTrackSelectX;
    temp2 = -gTrackSelectY;
    curIndex = temp2 / (gTrackSelectViewportY >> 3);
    if (curIndex >= 42) {
        return 1;
    }
    temp2 -= (curIndex * (gTrackSelectViewportY >> 3));
    yPos = gTrackSelectViewPortHalfY + temp2;
    { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = (((unsigned int) (((unsigned int)(0xfa) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (0)))); _g->words.w1 = (((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (0)))); };
    { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = ((unsigned int) (((unsigned int)(0xfb) & ((0x01 << (8)) - 1)) << (24))); _g->words.w1 = (unsigned int)((((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (0))))); };
    vertices = gTrackSelectBgVertices[gTrackSelectVertsFlip];
    triangles = gTrackSelectBgTriangles[gTrackSelectVertsFlip];
    for (index = 0; gTrackSelectBgData[index] < curIndex; index += 5) {}
    while ((yPos >= -gTrackSelectViewPortHalfY) && (gTrackSelectBgData[index] < 42) && (numVertices < 64)) {
        bgTexture = gTracksMenuBgTextures[gTrackSelectBgData[index + 1]];
        curIndex = gTrackSelectBgData[index];
        tempVertices = vertices;
        vertices++;
        vertices--;
        tempTriangles = triangles;
        vertices[0].y = yPos;
        vertices[0].a = gTrackSelectBgData[index + 2];
        vertices[1].y = yPos;
        vertices[1].a = gTrackSelectBgData[index + 2];
        prevIndex = gTrackSelectBgData[index + 2];
        vertices[2].y = yPos - (gTrackSelectViewportY >> 3);
        vertices[2].a = gTrackSelectBgData[index + 3];
        vertices[3].y = yPos - (gTrackSelectViewportY >> 3);
        vertices[3].a = gTrackSelectBgData[index + 3];
        vertices += 4;
        prevIndex += gTrackSelectBgData[index + 3];
        index += 4;
        if (bgTexture != 0) {
            texU = ((bgTexture->width - 1) & sp7C) << 5;
            texU += (gTrackSelectBgData[index] << 5);
            index++;
            texV = bgTexture->height << 5;
        }
        triangles[0].uv0.u = texU;
        triangles[0].uv0.v = 0;
        triangles[0].uv1.u = texU;
        triangles[0].uv1.v = texV;
        triangles[0].uv2.u = texU + 0x2800;
        triangles[0].uv2.v = 0;
        triangles[1].uv0.u = texU + 0x2800;
        triangles[1].uv0.v = 0;
        triangles[1].uv1.u = texU;
        triangles[1].uv1.v = texV;
        triangles[1].uv2.u = texU + 0x2800;
        triangles[1].uv2.v = texV;
        triangles += 2;
        if (bgTexture != 0) {
            hasTexture = 1;
        } else {
            hasTexture = 0;
        }
        if (prevIndex == 255 + 255) {
            flags = 0;
        } else {
            flags = RENDER_VTX_ALPHA | RENDER_Z_UPDATE;
        }
        material_set(dList, bgTexture, flags, 0);
        { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = (((unsigned int) (((unsigned int)((4)) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((((4)-1)<<3|(((u32)((u32)(((char *)(tempVertices)-0x80000000))) & 6))|(0))) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)(((((4) * 8 + (4)) << 1) + 8)) & ((0x01 << (16)) - 1)) << (0)))); _g->words.w1 = (unsigned int)((u32)(((char *)(tempVertices)-0x80000000))); };
        { Gfx *_g = (Gfx *)((*dList)++); _g->words.w0 = ((unsigned int) (((unsigned int)((((2) - 1) << 4) | (hasTexture)) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)(5) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(((2)*16)) & ((0x01 << (16)) - 1)) << (0))); _g->words.w1 = (unsigned int)((u32)(((char *)(tempTriangles)-0x80000000))); };
        prevIndex = gTrackSelectBgData[index];
        if (curIndex != prevIndex) {
            yPos -= (gTrackSelectViewportY >> 3);
        }
        numVertices += 4;
    }
    camEnableUserView(0, 1);
    return 0;
}
void trackmenu_render_2D(s32 x, s32 y, char *hubName, char *trackName, s32 rectOpacity, s32 imageId, s32 copyViewPort,
                         DrawTexture *arg7, s32 arg8) {
    s32 xTemp;
    s32 yTemp;
    s32 opacity;
    s32 i;
    s32 sp6C;
    s32 x1;
    s32 y1;
    s32 x2;
    s32 y2;
    f32 sp58;
    f32 sp54;
    s16 *offsets;
    s32 temp;
    sp6C = 0;
    xTemp = x + 160;
    yTemp = gTrackSelectViewPortHalfY - y;
    if (osTvType == 0) {
        sp6C = 12;
    }
    set_text_font(ASSET_FONTS_BIGFONT);
    set_text_background_colour(0, 0, 0, 0);
    if (gMenuDelay > 0) {
        opacity = 255 - (gMenuDelay * 16);
        if (opacity < 0) {
            opacity = 0;
        }
    } else {
        opacity = 255;
    }
    if (hubName != gTrackMenuHubName) {
        temp = (s32) level_name(level_world_id(WORLD_SNOWFLAKE_MOUNTAIN));
        if ((s32) hubName == temp) {
            set_kerning(1);
        }
        set_text_colour(0, 0, 0, 255, opacity / 2);
        draw_text(&sMenuCurrDisplayList, (320 / 2) + 1, (yTemp - sp6C) - 85, hubName, ALIGN_MIDDLE_CENTER);
        set_text_colour(255, 255, 255, 0, opacity);
        draw_text(&sMenuCurrDisplayList, (320 / 2), (yTemp - sp6C) - 88, hubName, ALIGN_MIDDLE_CENTER);
        gTrackMenuHubName = hubName;
        set_kerning(0);
    }
    set_text_colour(255, 255, 255, 0, opacity);
    draw_text(&sMenuCurrDisplayList, xTemp, sp6C + yTemp + 88, trackName, ALIGN_MIDDLE_CENTER);
    if (rectOpacity > 0) {
        if (((yTemp - (gTrackSelectViewportY >> 2)) < gTrackSelectViewportY) &&
            (((gTrackSelectViewportY >> 2) + yTemp) > 0)) {
            sp58 = 1.25f;
            sp54 = 1.25f;
            if (osTvType == 0) {
                sp54 *= 1.1;
            }
            temp = xTemp - 80;
            if (copyViewPort) {
                copy_viewport_frame_size_to_coords(0, &x1, &y1, &x2, &y2);
                temp = x1;
                sp58 = (x2 - temp) / 128.0f;
                sp54 = (y2 - y1) / 96.0f;
            } else {
                x2 = xTemp + 80;
            }
            x1 = temp;
            if (temp < 320 && xTemp > 0) {
                texrect_draw_scaled(&sMenuCurrDisplayList, arg7, xTemp, yTemp, sp58, sp54, (rectOpacity & 0xFF) | ~0xFF,
                                    TEXRECT_FLIP_X);
            }
            if (xTemp < 320 && x2 > 0) {
                texrect_draw_scaled(&sMenuCurrDisplayList, arg7, xTemp, yTemp, sp58, sp54, (rectOpacity & 0xFF) | ~0xFF,
                                    0);
            }
            rendermode_reset(&sMenuCurrDisplayList);
        }
    }
    gMenuImages[imageId].trans.x_position = x;
    gMenuImages[imageId].trans.y_position = y;
    if (osTvType == 0) {
        gTrackSelectWoodFrameHeightScale = 1.2f;
        offsets = gTracksMenuArrowPositionsPAL;
    } else {
        offsets = gTracksMenuArrowPositionsNTSC;
    }
    menu_element_render(imageId);
    gTrackSelectWoodFrameHeightScale = 1.0f;
    for (i = 0; i < 4; i++) {
        if ((1 << i) & arg8) {
            texrect_draw(&sMenuCurrDisplayList, gMenuSelectionArrows[i], offsets[(i << 1)] + xTemp + 1,
                         offsets[(i << 1) + 1] + yTemp + 1, 0, 0, 0, 128);
            texrect_draw(&sMenuCurrDisplayList, gMenuSelectionArrows[i], offsets[(i << 1)] + xTemp - 1,
                         offsets[(i << 1) + 1] + yTemp - 1, 255, 255, 255, 255);
        }
    }
    rendermode_reset(&sMenuCurrDisplayList);
}
void func_8008FF1C( s32 updateRate) {
    s32 i;
    char *trackName;
    char *hubName;
    s32 selectedTrack;
    s32 trackSelectX;
    s32 trackSelectY;
    char *levelName;
    s32 maxTrackY;
    s8 *trackMenuIds;
    Settings *settings;
    TrackRenderDetails *cur;
    s32 trackX;
    s32 trackY;
    s32 j;
    s32 startIndex;
    s16 temp;
    settings = get_settings();
    trackMenuIds = (s8 *) get_misc_asset(ASSET_MISC_TRACKS_MENU_IDS);
    if (gMenuDelay <= -23 || gMenuDelay >= 23) {
        return;
    }
    if (gFFLUnlocked == -1) {
        maxTrackY = 3;
    } else {
        maxTrackY = 4;
    }
    trackSelectX = (gTrackSelectX / 320);
    trackY = (gTrackSelectY / -gTrackSelectViewportY);
    trackSelectY = trackY - 1;
    startIndex = -1;
    for (i = startIndex, cur = gTrackSelectRenderDetails; i < 2; i++) {
        for (j = startIndex; j < 2; j++, cur++) {
            trackX = trackSelectX + j;
            trackY = trackSelectY;
            if (trackY < 0 || maxTrackY < trackY || trackX < 0 || trackX >= 6) {
                cur->visible = 0;
            } else {
                cur->visible = 1;
                levelName = level_name(level_world_id(trackY + 1));
                temp = (temp = gTrackSelectIDs[trackY][trackX]);
                selectedTrack = gTrackSelectIDs[trackY][trackX];
                cur->hubName = levelName;
                if (selectedTrack != -1) {
                    cur->trackName = level_name(trackMenuIds[((trackY * 6) + trackX)]);
                    if (trackX == 4) {
                        if ((((settings->trophies) >> (trackY * 2)) & 3) == 3) {
                            cur->visible = 2;
                        }
                    } else if ((settings->courseFlagsPtr[trackMenuIds[((trackY * 6) + trackX)]] & 2)) {
                        cur->visible = 2;
                    }
                } else {
                    cur->trackName = gQMarkPtr;
                }
                cur->xOff = ((trackX * 320) - gTrackSelectX);
                cur->yOff = ((-trackY * gTrackSelectViewportY) - gTrackSelectY);
                cur->opacity = 0xFF;
                if ((trackX == gSelectedTrackX) && (trackY == gSelectedTrackY)) {
                    cur->copyViewPort = (cur->copyViewPort & 0xFF) | 0x80;
                    if (gOpacityDecayTimer < 32) {
                        cur->opacity = gOpacityDecayTimer * 8;
                    }
                } else {
                    cur->copyViewPort = cur->copyViewPort & 0xFF7F;
                }
                cur->copyViewPort = cur->copyViewPort & 0xFF80;
                if (gMenuDelay == 0) {
                    if (trackY > 0) {
                        cur->copyViewPort = (((cur->copyViewPort & 0xFF) | 1) & 0x7F) | (cur->copyViewPort & 0xFF80);
                    }
                    if (trackX < 5) {
                        cur->copyViewPort = (((cur->copyViewPort & 0xFF) | 2) & 0x7F) | (cur->copyViewPort & 0xFF80);
                    }
                    if (trackY < maxTrackY) {
                        cur->copyViewPort = (((cur->copyViewPort & 0xFF) | 4) & 0x7F) | (cur->copyViewPort & 0xFF80);
                    }
                    if (trackX > 0) {
                        cur->copyViewPort = (((cur->copyViewPort & 0xFF) | 8) & 0x7F) | (cur->copyViewPort & 0xFF80);
                    }
                    if (trackX == 4 && trackY == 4) {
                        cur->copyViewPort = ((cur->copyViewPort & 0xFF & 0xFF) & 0x7D) | (cur->copyViewPort & 0xFF80);
                    }
                    if (trackX == 5 && trackY == 3) {
                        cur->copyViewPort = ((cur->copyViewPort & 0xFF & 0xFF) & 0x7B) | (cur->copyViewPort & 0xFF80);
                    }
                }
                if (trackX == 4) {
                    cur->border = 6;
                } else if (trackX == 5) {
                    cur->border = 5;
                } else {
                    cur->border = 4;
                }
            }
        }
        trackSelectY++;
    }
    camDisableUserView(0, 1);
    menu_camera_centre();
    mtx_ortho(&sMenuCurrDisplayList, &sMenuCurrHudMat);
    rendermode_reset(&sMenuCurrDisplayList);
    { Gfx *_g = (Gfx *)(sMenuCurrDisplayList++); _g->words.w0 = ((unsigned int) (((unsigned int)(0xe7) & ((0x01 << (8)) - 1)) << (24))); _g->words.w1 = 0; };
    D_80126928 = 64;
    D_8012692C = 32;
    gTrackMenuHubName = 0;
    for (i = 0; i < (s32)(sizeof(gTrackSelectRenderDetails) / sizeof(gTrackSelectRenderDetails[0])); i++) {
        if (gTrackSelectRenderDetails[i].visible != 0) {
            trackmenu_render_2D(gTrackSelectRenderDetails[i].xOff, gTrackSelectRenderDetails[i].yOff,
                                gTrackSelectRenderDetails[i].hubName, gTrackSelectRenderDetails[i].trackName,
                                gTrackSelectRenderDetails[i].opacity, gTrackSelectRenderDetails[i].border,
                                ((u32) gTrackSelectRenderDetails[i].viewPort) >> 0xF,
                                (gTrackSelectRenderDetails[i].visible == 1) ? D_800E05D4 : D_800E05F4,
                                gTrackSelectRenderDetails[i].copyViewPort & 0x7F);
        }
    }
    gTrackSelectVertsFlip = 1 - gTrackSelectVertsFlip;
}
void trackmenu_track_view(s32 updateRate) {
    s32 x1;
    s32 y1;
    s32 x2;
    s32 y2;
    s32 i;
    bgload_tick();
    for (i = 0; i < updateRate; i++) {
        gTrackSelectX += (gTrackSelectTargetX - gTrackSelectX) * 0.1;
        gTrackSelectY += (gTrackSelectTargetY - gTrackSelectY) * 0.1;
    }
    if (gOpacityDecayTimer == 32 && bgload_active() == 0) {
        if (gTrackIdForPreview == gTrackmenuLoadedLevel) {
            gSelectedTrackX = gTrackSelectCursorX;
            gSelectedTrackY = gTrackSelectCursorY;
        } else if (gTrackIdForPreview != gTrackmenuLoadedLevel && gTrackIdForPreview != -1 &&
                   bgload_start(gTrackIdForPreview, 1)) {
            gTrackmenuLoadedLevel = gTrackIdForPreview;
            gSelectedTrackX = gTrackSelectCursorX;
            gSelectedTrackY = gTrackSelectCursorY;
            set_level_default_vehicle(leveltable_vehicle_default(gTrackIdForPreview));
        }
    }
    x1 = ((gSelectedTrackX * 320) - gTrackSelectX) + ((float)320 / 2) - 80.0f;
    x2 = x1 + (320 / 2);
    y1 = gTrackSelectViewPortHalfY - ((gSelectedTrackY * -gTrackSelectViewportY) - gTrackSelectY) -
         (gTrackSelectViewportY >> 2);
    y2 = y1 + gTrackSelectViewPortHalfY;
    viewport_menu_set(0, x1, y1, x2, y2);
    copy_viewport_background_size_to_coords(0, &x1, &y1, &x2, &y2);
    camEnableUserView(0, 0);
}
void trackmenu_input(s32 updateRate) {
    s32 pad1[2];
    s32 scaleOffset;
    s32 pad2[2];
    s32 spaceWorldUnlocked;
    s32 centreY;
    s32 centreX;
    s32 menuDelay;
    s32 y2;
    s32 y1;
    menuDelay = gMenuDelay;
    if (gMenuDelay > 0) {
        if (gTrackSelectTargetX - gTrackSelectX > 4.0f || gTrackSelectTargetX - gTrackSelectX < -4.0f ||
            gTrackSelectTargetY - gTrackSelectY > 4.0f || gTrackSelectTargetY - gTrackSelectY < -4.0f) {
            gMenuDelay = 1;
        } else if (gTrackSelectSound) {
            sound_play(SOUND_SELECT2, 0);
            gTrackSelectSound = 0;
        }
        scaleOffset = gMenuDelay - 1;
        if (scaleOffset > 20) {
            scaleOffset = 20;
        }
        centreX = 160;
        centreY = gTrackSelectViewPortHalfY;
        if (scaleOffset < 20) {
            centreX += gTrackSelectTargetX - gTrackSelectX;
            centreY -= gTrackSelectTargetY - gTrackSelectY;
        }
        y2 = (((scaleOffset + 20) * gTrackSelectViewPortHalfY) / 40) + centreY;
        y1 = centreY - (((scaleOffset + 20) * gTrackSelectViewPortHalfY) / 40);
        viewport_menu_set(0, (centreX - (scaleOffset * 4)) - 80, y1, (scaleOffset * 4) + centreX + 80, y2);
        gMenuImages[4].trans.scale = (f32) (sMenuImageProperties[4].trans.scale * (1.0f + ((f32) scaleOffset / 20.0f)));
        gMenuImages[6].trans.scale = (f32) (sMenuImageProperties[6].trans.scale * (1.0f + ((f32) scaleOffset / 20.0f)));
        gMenuImages[5].trans.scale = (f32) (sMenuImageProperties[5].trans.scale * (1.0f + ((f32) scaleOffset / 20.0f)));
    }
    camEnableUserView(0, 0);
    if (bgload_active() == 0) {
        if (gMenuDelay < 0) {
            sMenuMusicVolume -= updateRate * 4;
        }
        if (gSelectedTrackX == gTrackSelectCursorX && gSelectedTrackY == gTrackSelectCursorY) {
            gOpacityDecayTimer -= updateRate;
            if (gOpacityDecayTimer < 0) {
                gOpacityDecayTimer = 0;
            }
        } else {
            gOpacityDecayTimer = gOpacityDecayTimer + updateRate;
            if (gOpacityDecayTimer > 32) {
                gOpacityDecayTimer = 32;
            }
        }
        if (gMenuDelay < -22) {
            bgdraw_set_func(0);
            gIsInTracksMenu = 0;
        }
        if (gMenuDelay > 30) {
            if (is_adventure_two_unlocked() && gTrackSelectCursorX != 5) {
                gMenuStage = TRACKMENU_MIRROR;
            } else {
                gMenuStage = TRACKMENU_OPT_1;
            }
            trackmenu_assets(TRACKMENU_TYPE_FREE);
        } else if (gMenuDelay < -30) {
            disable_new_screen_transitions();
            camDisableUserView(0, 0);
            trackmenu_assets(TRACKMENU_TYPE_INIT);
        }
    }
    if (menuDelay == 0) {
        spaceWorldUnlocked = gFFLUnlocked == -1 ? 3 : 4;
        if (gMenuButtons[4] & (0x8000 | 0x1000)) {
            if (gTrackIdForPreview != -1) {
                gMenuDelay = 1;
                gTrackIdToLoad = gTrackIdForPreview;
                gTrackSelectSound = 1;
            } else {
                sound_play(SOUND_UNK_6A, 0);
            }
        } else if (gMenuButtons[4] & 0x4000) {
            disable_new_screen_transitions();
            transition_begin(&sMenuTransitionFadeIn);
            enable_new_screen_transitions();
            gMenuDelay = -1;
        } else {
            s32 prevValue = gTrackSelectCursorX;
            s32 prevValue2 = gTrackSelectCursorY;
            if (gMenuStickX[4] < 0 && gTrackSelectCursorX > 0) {
                gTrackSelectCursorX--;
            }
            if (gMenuStickX[4] > 0 && gTrackSelectCursorX < 5) {
                gTrackSelectCursorX++;
            }
            if (gTrackSelectCursorY == 4 && gTrackSelectCursorX == 5) {
                gTrackSelectCursorX = 4;
            }
            if (gMenuStickX[4] == 0) {
                if (gMenuStickY[4] < 0 && gTrackSelectCursorY < spaceWorldUnlocked) {
                    gTrackSelectCursorY++;
                }
                if (gMenuStickY[4] > 0 && gTrackSelectCursorY > 0) {
                    gTrackSelectCursorY--;
                }
                if (gTrackSelectCursorX == 5 && gTrackSelectCursorY == 4) {
                    gTrackSelectCursorY = 3;
                }
            }
            if ((prevValue != gTrackSelectCursorX) || (gTrackSelectCursorY != prevValue2)) {
                sound_play(SOUND_MENU_PICK2, 0);
                gTrackIdForPreview = gTrackSelectIDs[gTrackSelectCursorY][gTrackSelectCursorX];
                gTrackSelectRow = gTrackSelectCursorY + 1;
                gTrackSelectTargetX = (gTrackSelectCursorX * 320);
                gTrackSelectTargetY = -(gTrackSelectCursorY * gTrackSelectViewportY);
            }
        }
    }
}
void trackmenu_timetrial_sound( s32 updateRate) {
    if (gMenuStage == TRACKMENU_CHOOSE && gTracksMenuTimeTrialHighlightIndex == 0 && gTrackTTSoundMask == 0) {
        sound_play(SOUND_VOICE_TT_SNORE, &gTrackTTSoundMask);
    }
}
void trackmenu_setup_render( s32 updateRate) {
    s32 k;
    s32 y;
    s32 temp2;
    s32 temp;
    s32 sp84;
    s32 regionOffset;
    s32 availableVehicleFlags;
    union {
        char buffer[4];
        s32 word;
    } filename;
    s32 sp74;
    Settings *settings;
    s32 i;
    s32 j;
    regionOffset = 0;
    filename.word = 0;
    sp74 = 0;
    settings = get_settings();
    if (osTvType == 0) {
        regionOffset = 12;
    }
    if (gNumberOfActivePlayers == 2 && gTrackSelectCursorX < 4 && gMenuStage > TRACKMENU_CHOOSE) {
        sp74 = 1;
    }
    camDisableUserView(0, 1);
    menu_camera_centre();
    mtx_ortho(&sMenuCurrDisplayList, &sMenuCurrHudMat);
    if (gMenuDelay < 0) {
        if (gSelectedTrackX == 4) {
            sp84 = 6;
        } else if (gSelectedTrackX == 5) {
            sp84 = 5;
        } else {
            sp84 = 4;
        }
        gMenuImages[sp84].trans.x_position = 0.0f;
        gMenuImages[sp84].trans.y_position = 0.0f;
        if (osTvType == 0) {
            gTrackSelectWoodFrameHeightScale = 1.2f;
        }
        menu_element_render(sp84);
        gTrackSelectWoodFrameHeightScale = 1.0f;
    }
    if (gMenuDelay >= -22 && gMenuDelay <= 30) {
        sMenuGuiOpacity = (gMenuDelay < 0) ? 255 + (gMenuDelay * 16) : 255;
        if (sMenuGuiOpacity < 0) {
            sMenuGuiOpacity = 0;
        }
        availableVehicleFlags = leveltable_vehicle_usable(gTrackIdForPreview);
        if (gNumberOfActivePlayers >= 2) {
            if (gTrackIdForPreview == ASSET_LEVEL_SPACEPORTALPHA) {
                availableVehicleFlags &= ~(1 << VEHICLE_HOVERCRAFT);
            }
            if (gTrackIdForPreview == ASSET_LEVEL_FROSTYVILLAGE) {
                availableVehicleFlags &= ~(1 << VEHICLE_PLANE);
            }
        }
        i = (s32) level_name(gTrackIdForPreview);
        set_text_font(ASSET_FONTS_BIGFONT);
        set_text_colour(192, 192, 255, 0, sMenuGuiOpacity);
        set_text_background_colour(0, 0, 0, 0);
        draw_text(&sMenuCurrDisplayList, -0x8000, 43, (char *) i, ALIGN_MIDDLE_CENTER);
        sp84 = gOptionBlinkTimer * 8;
        if (sp84 > 255) {
            sp84 = 511 - sp84;
        }
        set_current_dialogue_background_colour(7, 255, sp84, 0, sMenuGuiOpacity);
        if (gMenuStage == TRACKMENU_MIRROR ||
            (gMenuStage == TRACKMENU_OPT_2 && gTrackSelectCursorX == 4 && is_adventure_two_unlocked())) {
            temp2 = get_text_width(gMenuText[ASSET_MENU_TEXT_ADVENTURE2], 0, 0);
            k = get_text_width(gMenuText[ASSET_MENU_TEXT_ADVENTURETWO2], 0, 0);
            if (temp2 < k) {
                temp2 = k;
            }
            if (temp2 < gTracksMenuAdventureButton.width) {
                temp2 = gTracksMenuAdventureButton.width;
            } else {
                temp2 += 12;
            }
            func_80080580(&sMenuCurrDisplayList, -(temp2 >> 1), (240 / 2) - gTracksMenuAdventureButton.y,
                          temp2, gTracksMenuAdventureButton.height, gTracksMenuAdventureButton.borderWidth,
                          gTracksMenuAdventureButton.borderHeight, sMenuGuiOpacity + ((u32)((176 << 24) | (224 << 16) | (192 << 8) | 0)),
                          gMenuAssets[67]);
            menu_geometry_end();
            set_text_font(ASSET_FONTS_FUNFONT);
            for (temp = 0, temp2 = 0,
                y = gTracksMenuAdventureButton.colourMax + gTracksMenuAdventureButton.y + regionOffset + 1;
                 temp2 < 2; temp2++, temp++, y += 16) {
                for (j = 0, i = y; j < 4; j += 2, i -= 2) {
                    if (j == 0) {
                        set_text_colour(0, 0, 0, 255, sMenuGuiOpacity >> 1);
                    } else {
                        k = 0;
                        if (temp2 == gTracksMenuAdventureHighlightIndex) {
                            k = sp84;
                        }
                        set_text_colour(255, 255, 255, k, sMenuGuiOpacity);
                    }
                    draw_text(&sMenuCurrDisplayList, (320 / 2) + 1 - j, i,
                              gMenuText[ASSET_MENU_TEXT_ADVENTURE2 + temp], ALIGN_MIDDLE_CENTER);
                }
            }
        }
        if (gTrackSelectCursorX < 4) {
            set_text_font(ASSET_FONTS_FUNFONT);
            set_text_colour(255, 64, 64, 96, sMenuGuiOpacity);
            draw_text(&sMenuCurrDisplayList, 56, 72 + regionOffset, gMenuText[ASSET_MENU_TEXT_BESTTIME],
                      ALIGN_MIDDLE_LEFT);
            draw_text(&sMenuCurrDisplayList, 56, 92 + regionOffset, gMenuText[ASSET_MENU_TEXT_BESTLAP],
                      ALIGN_MIDDLE_LEFT);
            set_text_colour(255, 128, 255, 96, sMenuGuiOpacity);
            filename_decompress(settings->courseInitialsPtr[gPlayerSelectVehicle[0]][gTrackIdForPreview],
                                filename.buffer, 3);
            draw_text(&sMenuCurrDisplayList, 250, regionOffset + 72, filename.buffer, ALIGN_MIDDLE_CENTER);
            filename_decompress(settings->flapInitialsPtr[gPlayerSelectVehicle[0]][gTrackIdForPreview], filename.buffer,
                                3);
            draw_text(&sMenuCurrDisplayList, 250, regionOffset + 92, filename.buffer, ALIGN_MIDDLE_CENTER);
            menu_timestamp_render(settings->courseTimesPtr[gPlayerSelectVehicle[PLAYER_ONE]][gTrackIdForPreview], 22,
                                  53, 128, 255, 255, FONT_COLOURFUL);
            menu_timestamp_render(settings->flapTimesPtr[gPlayerSelectVehicle[PLAYER_ONE]][gTrackIdForPreview], 22, 33,
                                  255, 192, 255, FONT_COLOURFUL);
            if (gMenuStage != TRACKMENU_MIRROR) {
                if (gNumberOfActivePlayers == 1) {
                    set_current_dialogue_box_coords(7, 134, regionOffset + 112, 186, regionOffset + 137);
                    render_dialogue_box(&sMenuCurrDisplayList, 0, 0, 7);
                    if (gMenuStage <= TRACKMENU_OPT_1) {
                        texrect_draw(&sMenuCurrDisplayList, gRaceSelectionVehicleTitleTexture, 136, regionOffset + 114,
                                     255, 255, 255, sMenuGuiOpacity);
                    } else {
                        texrect_draw(&sMenuCurrDisplayList, gRaceSelectionTTTitleTexture, 136, regionOffset + 114, 255,
                                     255, 255, sMenuGuiOpacity);
                        for (k = 0, y = regionOffset + 151; k < 2; k++, y += 24) {
                            if (k == gTracksMenuTimeTrialHighlightIndex) {
                                texrect_draw(&sMenuCurrDisplayList, gTrackSelectTTImage[k * 3 + 1], 104, y, 255, 255,
                                             255, sMenuGuiOpacity);
                            } else {
                                texrect_draw(&sMenuCurrDisplayList, gTrackSelectTTImage[k * 3 + 2], 104, y, 255, 255,
                                             255, sMenuGuiOpacity);
                            }
                        }
                    }
                } else if (!sp74) {
                    y = gNumberOfActivePlayers;
                    j = ((y - 1) * y);
                    for (k = 0; (k < y) ^ 0; k++) {
                        if ((gNumberOfActivePlayers == 1 && k == gMenuStage) ||
                            (gNumberOfActivePlayers > 1 && gPlayerSelectConfirm[k] == 0)) {
                            set_current_dialogue_box_coords(7, gTracksMenuPlayerNamePositions[j] - 2,
                                                            gTracksMenuPlayerNamePositions[j + 1] + regionOffset - 2,
                                                            gTracksMenuPlayerNamePositions[j] + 50,
                                                            gTracksMenuPlayerNamePositions[j + 1] + regionOffset + 23);
                            render_dialogue_box(&sMenuCurrDisplayList, 0, 0, 7);
                        }
                        texrect_draw(
                            &sMenuCurrDisplayList, gTrackSelectPlayerImage[k], gTracksMenuPlayerNamePositions[j],
                            gTracksMenuPlayerNamePositions[j + 1] + regionOffset, 255, 255, 255, sMenuGuiOpacity);
                        j += 2;
                    }
                }
                if ((gNumberOfActivePlayers > 1 || gMenuStage == TRACKMENU_OPT_1) && !sp74) {
                    j = ((gNumberOfActivePlayers - 1) * gNumberOfActivePlayers) >> 1;
                    for (k = 0, y = regionOffset + 139; k < 3; k++) {
                        if ((1 << k) & availableVehicleFlags) {
                            for (temp2 = 0; temp2 < gNumberOfActivePlayers; temp2++) {
                                if (k == gPlayerSelectVehicle[temp2]) {
                                    texrect_draw(&sMenuCurrDisplayList, gRaceSelectionImages[(k * 3) + 1],
                                                 gTracksMenuVehicleNamePositions[j + temp2], y, 255, 255, 255,
                                                 sMenuGuiOpacity);
                                } else if (settings->courseFlagsPtr[gTrackIdForPreview] & 2) {
                                    texrect_draw(&sMenuCurrDisplayList, gRaceSelectionImages[(k * 3) + 2],
                                                 gTracksMenuVehicleNamePositions[j + temp2], y, 255, 255, 255,
                                                 sMenuGuiOpacity);
                                } else {
                                    texrect_draw(&sMenuCurrDisplayList, gRaceSelectionImages[(k * 3) + 2],
                                                 gTracksMenuVehicleNamePositions[j + temp2], y, 255, 255, 255,
                                                 (sMenuGuiOpacity / 2));
                                }
                            }
                            y += 24;
                        }
                    }
                }
                y = regionOffset + 139;
                if (gPlayerSelectVehicle[PLAYER_ONE] == 2) {
                    y += 2;
                }
                if (gNumberOfActivePlayers == 1) {
                    if (gMenuStage == TRACKMENU_OPT_1) {
                        texrect_draw(&sMenuCurrDisplayList, gRaceSelectionImages[gPlayerSelectVehicle[PLAYER_ONE] * 3],
                                     149, y, 255, 255, 255, sMenuGuiOpacity);
                    } else {
                        texrect_draw(&sMenuCurrDisplayList, gTrackSelectTTImage[gTracksMenuTimeTrialHighlightIndex * 3],
                                     149, regionOffset + 139, 255, 255, 255, sMenuGuiOpacity);
                    }
                }
                if (gNumberOfActivePlayers == 2 && !sp74) {
                    texrect_draw(&sMenuCurrDisplayList, gRaceSelectionImages[gPlayerSelectVehicle[PLAYER_ONE] * 3], 79,
                                 y, 255, 255, 255, sMenuGuiOpacity);
                    y = regionOffset + 139;
                    if (gPlayerSelectVehicle[PLAYER_TWO] == 2) {
                        y += 2;
                    }
                    texrect_draw(&sMenuCurrDisplayList, gRaceSelectionImages[gPlayerSelectVehicle[PLAYER_TWO] * 3], 176,
                                 y, 255, 255, 255, sMenuGuiOpacity);
                }
                rendermode_reset(&sMenuCurrDisplayList);
                if (gNumberOfActivePlayers <= 2 && !sp74) {
                    gMenuImages[7].trans.y_position = -52.0f;
                    if (gNumberOfActivePlayers == 1) {
                        gMenuImages[7].trans.x_position = 21.0f;
                        menu_element_render(7);
                    } else {
                        gMenuImages[7].trans.x_position = -48.0f;
                        menu_element_render(7);
                        gMenuImages[7].trans.x_position = 48.0f;
                        menu_element_render(7);
                    }
                }
                if (sp74) {
                    temp2 = get_text_width(gMenuText[ASSET_MENU_TEXT_NUMBEROFRACERS], 0, 0);
                    if ((gTwoPlayerRacerCountMenu.width - 12) < temp2) {
                        temp2 = temp2 + 12;
                    } else {
                        temp2 = gTwoPlayerRacerCountMenu.width;
                    }
                    func_80080580(&sMenuCurrDisplayList, -(temp2 >> 1), 120 - gTwoPlayerRacerCountMenu.y, temp2,
                                  gTwoPlayerRacerCountMenu.height, gTwoPlayerRacerCountMenu.borderWidth,
                                  gTwoPlayerRacerCountMenu.borderHeight, ((u32)((176 << 24) | (224 << 16) | (192 << 8) | 255)),
                                  gMenuAssets[67]);
                    menu_geometry_end();
                    set_text_font(ASSET_FONTS_FUNFONT);
                    set_text_colour(0, 0, 0, 255, 128);
                    draw_text(&sMenuCurrDisplayList,
                              gTwoPlayerRacerCountMenu.textPos[0] + gTwoPlayerRacerCountMenu.x + 1,
                              gTwoPlayerRacerCountMenu.textPos[1] + gTwoPlayerRacerCountMenu.y + regionOffset + 1,
                              gMenuText[ASSET_MENU_TEXT_NUMBEROFRACERS], ALIGN_MIDDLE_CENTER);
                    set_text_colour(255, 255, 255, 0, 255);
                    draw_text(&sMenuCurrDisplayList,
                              (gTwoPlayerRacerCountMenu.textPos[0] + gTwoPlayerRacerCountMenu.x) - 1,
                              (gTwoPlayerRacerCountMenu.textPos[1] + gTwoPlayerRacerCountMenu.y + regionOffset) - 1,
                              gMenuText[ASSET_MENU_TEXT_NUMBEROFRACERS], ALIGN_MIDDLE_CENTER);
                    cam_set_sprite_anim_mode(SPRITE_ANIM_FRAME_INDEX);
                    sprite_opaque(0);
                    for (temp2 = 0; temp2 < 3; temp2++) {
                        if (temp2 == gMultiplayerSelectedNumberOfRacers) {
                            if (gMenuStage <= TRACKMENU_OPT_2) {
                                sMenuGuiColourG = 255 - sp84;
                                sMenuGuiColourB = 255 - sp84;
                            } else {
                                sMenuGuiColourG = 0;
                                sMenuGuiColourB = 0;
                            }
                        }
                        gMenuImages[0].trans.x_position =
                            (gTwoPlayerRacerCountMenu.textPos[(temp2 << 1) + 2] + gTwoPlayerRacerCountMenu.x) - 160;
                        gMenuImages[0].trans.y_position =
                            (-gTwoPlayerRacerCountMenu.textPos[(temp2 << 1) + 2 + 1] - gTwoPlayerRacerCountMenu.y) +
                            120;
                        gMenuImages[0].spriteOffset = (temp2 << 1) + 2;
                        menu_element_render(0);
                        sMenuGuiColourG = 255;
                        sMenuGuiColourB = 255;
                    }
                    sprite_opaque(1);
                    cam_set_sprite_anim_mode(SPRITE_ANIM_NORMALIZED);
                }
            }
        }
        if (gTrackSelectCursorX < 4) {
            sprite_opaque(0);
            k = 11;
            if (gIsInAdventureTwo) {
                k = 12;
            }
            gMenuImages[k].trans.y_position = 42.0f;
            if ((settings->courseFlagsPtr[gTrackIdForPreview] & 2) || (is_adventure_two_unlocked())) {
                gMenuImages[k].trans.x_position = (f32) ((gIsInAdventureTwo * 2) - 128);
                menu_element_render(k);
            }
            if ((settings->courseFlagsPtr[gTrackIdForPreview] & 4) || (is_adventure_two_unlocked())) {
                gMenuImages[k].trans.x_position = (f32) ((gIsInAdventureTwo * 2) + 120);
                menu_element_render(k);
            }
            sprite_opaque(1);
        }
        if (gNumberOfActivePlayers == 1 && gMenuStage > TRACKMENU_MIRROR &&
            trackmenu_staff_beaten(gTrackIdForPreview) >= 0) {
            texrect_draw(&sMenuCurrDisplayList, gRaceSelectionTTTexture, 204, regionOffset + 122, 255, 255, 255,
                         sMenuGuiOpacity);
            rendermode_reset(&sMenuCurrDisplayList);
        }
        if (gTrackSelectCursorX != 5) {
            if ((gMenuStage == TRACKMENU_OPT_2 && !sp74) || (gMenuStage == TRACKMENU_OPT_3 && sp74) ||
                gMenuStage == TRACKMENU_OPT_4) {
                set_text_font(ASSET_FONTS_BIGFONT);
                set_text_colour(255, 255, 255, 0, sMenuGuiOpacity);
                if (gTrackSelectCursorX >= 4) {
                    regionOffset += 24;
                }
                draw_text(&sMenuCurrDisplayList, (320 / 2), regionOffset + 172, "OK?", ALIGN_MIDDLE_CENTER);
            }
        }
        sMenuGuiOpacity = 255;
    }
}
void func_80092188(s32 updateRate) {
    s32 yOffset2;
    s32 origVehicle;
    s32 availableVehicles;
    s32 xOffset;
    s32 yOffset;
    s32 i;
    s32 menuBackedOut;
    s32 menuSelected;
    s32 menuChanged;
    s32 menuDelay;
    Settings *settings;
    menuDelay = gMenuDelay;
    settings = get_settings();
    if (gTrackNameVoiceDelay != 0) {
        gTrackNameVoiceDelay += updateRate;
    }
    if (gTrackSelectCursorX == 5 && gMenuStage != 2) {
        gMenuStage = 2;
        if (gTrackSelectCursorX == 5) {
            set_current_text(gTrackSelectCursorY + ASSET_GAME_TEXT_60);
        }
    }
    if (gTrackSelectCursorX == 4 && gMenuStage != -1 && gMenuStage != 2) {
        gMenuStage = 2;
    }
    if (gTTVoiceLines[gTrackIdForPreview] != -1 && gTrackNameVoiceDelay >= 7) {
        sound_play(gTTVoiceLines[gTrackIdForPreview], 0);
        gTrackNameVoiceDelay = 0;
    }
    xOffset = gMenuDelay + 25;
    if (gMenuDelay < 0) {
        if (xOffset > 20) {
            xOffset = 20;
        }
        if (xOffset < 0) {
            xOffset = 0;
        }
        yOffset = ((xOffset + 20) * gTrackSelectViewPortHalfY) / 40;
        yOffset2 = yOffset + gTrackSelectViewPortHalfY;
        viewport_menu_set(0, 80 - (xOffset * 4), gTrackSelectViewPortHalfY - yOffset, (xOffset * 4) + 240, yOffset2);
        gMenuImages[4].trans.scale = sMenuImageProperties[4].trans.scale * (1.0f + ((f32) xOffset / 20.0f));
        gMenuImages[5].trans.scale = sMenuImageProperties[5].trans.scale * (1.0f + ((f32) xOffset / 20.0f));
        gMenuImages[6].trans.scale = sMenuImageProperties[6].trans.scale * (1.0f + ((f32) xOffset / 20.0f));
    }
    if (gMenuDelay > 0) {
        sMenuMusicVolume -= updateRate * 4;
    }
    if (gMenuDelay > 40) {
        trackmenu_assets(TRACKMENU_TYPE_LOAD_LEVEL);
    } else if (gMenuDelay < -30) {
        gOpacityDecayTimer = 0;
        trackmenu_assets(TRACKMENU_TYPE_RESET_CURSOR);
        viewport_menu_set(0, 80, gTrackSelectViewPortHalfY - (gTrackSelectViewPortHalfY >> 1), 240,
                          (gTrackSelectViewPortHalfY >> 1) + gTrackSelectViewPortHalfY);
    }
    camEnableUserView(0, 1);
    if (menuDelay == 0) {
        availableVehicles = leveltable_vehicle_usable(gTrackIdForPreview);
        if (gNumberOfActivePlayers >= 2) {
            if (gTrackIdForPreview == ASSET_LEVEL_SPACEPORTALPHA) {
                availableVehicles &= ~(1 << VEHICLE_HOVERCRAFT);
            }
            if (gTrackIdForPreview == ASSET_LEVEL_FROSTYVILLAGE) {
                availableVehicles &= ~(1 << VEHICLE_PLANE);
            }
        }
        menuBackedOut = 0;
        menuSelected = 0;
        menuChanged = 0;
        switch (gMenuStage) {
            case -1:
                if (gMenuButtons[4] & (0x8000 | 0x1000)) {
                    if (gTrackSelectCursorX == 4) {
                        gMenuStage = 2;
                    } else {
                        gMenuStage = 0;
                    }
                    menuSelected = 1;
                } else if (gMenuButtons[4] & 0x4000) {
                    gMenuDelay = -1;
                    menuBackedOut = 1;
                } else {
                    if (gMenuStickY[4] > 0 && gTracksMenuAdventureHighlightIndex != 0) {
                        gTracksMenuAdventureHighlightIndex = 0;
                        menuChanged = 1;
                    } else if ((gMenuStickY[4] < 0) && (gTracksMenuAdventureHighlightIndex == 0)) {
                        gTracksMenuAdventureHighlightIndex = 1;
                        menuChanged = 1;
                    }
                }
                break;
            case 0:
                for (i = 0; i < gNumberOfActivePlayers; i++) {
                    if (gMenuButtons[i] & 0x4000) {
                        menuBackedOut = 1;
                        if (gNumberOfReadyPlayers == 0) {
                            if (is_adventure_two_unlocked()) {
                                gMenuStage = -1;
                            } else {
                                gMenuDelay = -1;
                            }
                        } else if (gPlayerSelectConfirm[i] != 0) {
                            gNumberOfReadyPlayers--;
                            gPlayerSelectConfirm[i] = 0;
                        }
                    } else {
                        if (gMenuButtons[i] & (0x8000 | 0x1000)) {
                            if (gPlayerSelectConfirm[i] == 0) {
                                gPlayerSelectConfirm[i] = 1;
                                gNumberOfReadyPlayers++;
                                menuSelected = 1;
                            }
                        } else if (gPlayerSelectConfirm[i] == 0 && settings->courseFlagsPtr[gTrackIdForPreview] & 2) {
                            origVehicle = gPlayerSelectVehicle[i];
                            if (gMenuStickY[i] > 0) {
                                do {
                                    gPlayerSelectVehicle[i]--;
                                } while (((1 << gPlayerSelectVehicle[i]) & availableVehicles) == 0 &&
                                         gPlayerSelectVehicle[i] >= 0);
                            }
                            if (gMenuStickY[i] < 0) {
                                do {
                                    gPlayerSelectVehicle[i]++;
                                } while (((1 << gPlayerSelectVehicle[i]) & availableVehicles) == 0 &&
                                         gPlayerSelectVehicle[i] < 3);
                            }
                            if (origVehicle != gPlayerSelectVehicle[i]) {
                                if (gPlayerSelectVehicle[i] < 0 || gPlayerSelectVehicle[i] >= 3) {
                                    gPlayerSelectVehicle[i] = origVehicle;
                                } else {
                                    menuChanged = 1;
                                }
                            }
                        }
                    }
                }
                if (gNumberOfReadyPlayers == gNumberOfActivePlayers) {
                    menuBackedOut = 0;
                    menuSelected = 0;
                    menuChanged = 0;
                    if (gNumberOfActivePlayers >= 2) {
                        gMenuStage = 2;
                    } else {
                        gMenuStage = 1;
                    }
                    sound_play(SOUND_CAR_REV2, 0);
                }
                break;
            case 1:
                if (gMenuButtons[0] & (0x8000 | 0x1000)) {
                    gMenuStage = 2;
                    menuSelected = 1;
                } else if (gMenuButtons[0] & 0x4000) {
                    gPlayerSelectConfirm[0] = 0;
                    gNumberOfReadyPlayers = 0;
                    gMenuStage = 0;
                    menuBackedOut = 1;
                }
                if (gMenuStickY[0] > 0 && gTracksMenuTimeTrialHighlightIndex > 0) {
                    if (D_80126848 != 0) {
                        sndp_stop(D_80126848);
                    }
                    gTracksMenuTimeTrialHighlightIndex--;
                    menuChanged = 1;
                }
                if (gMenuStickY[0] < 0) {
                    if (gTracksMenuTimeTrialHighlightIndex <= 0) {
                        menuChanged = 1;
                        if (gTrackTTSoundMask != 0) {
                            sndp_stop(gTrackTTSoundMask);
                        }
                        if (rand_range(0, 255) >= 128) {
                            sound_play(SOUND_VOICE_TT_INTRO, &D_80126848);
                        } else {
                            sound_play(SOUND_VOICE_TT_GO_FOR_IT, &D_80126848);
                        }
                        gTracksMenuTimeTrialHighlightIndex++;
                    }
                }
                break;
            case 2:
            case 3:
                if (gMenuStage == 2 && gNumberOfActivePlayers == 2 && gTrackSelectCursorX < 4) {
                    if (gMenuButtons[4] & (0x8000 | 0x1000)) {
                        gMenuStage = 3;
                        menuSelected = 1;
                    } else if (gMenuButtons[4] & 0x4000) {
                        gMenuStage = 0;
                        gNumberOfReadyPlayers--;
                        if (gMenuButtons[0] & 0x4000) {
                            gPlayerSelectConfirm[0] = 0;
                        } else {
                            gPlayerSelectConfirm[1] = 0;
                        }
                        menuBackedOut = 1;
                    } else {
                        if (gMenuStickX[4] < 0 && gMultiplayerSelectedNumberOfRacers > 0) {
                            menuChanged = 1;
                            gMultiplayerSelectedNumberOfRacers--;
                        } else if (gMenuStickX[4] > 0 && gMultiplayerSelectedNumberOfRacers < 2) {
                            menuChanged = 1;
                            gMultiplayerSelectedNumberOfRacers++;
                        }
                    }
                } else if (gMenuButtons[4] & (0x8000 | 0x1000)) {
                    gMenuDelay = 1;
                    bgdraw_set_func(0);
                    gIsInTracksMenu = 0;
                    disable_new_screen_transitions();
                    transition_begin(&sMenuTransitionFadeIn);
                    if (gTrackSelectCursorX == 5) {
                        set_current_text(10000);
                    }
                    menuSelected = 1;
                } else if (gTrackSelectCursorX >= 4) {
                    if (gMenuButtons[4] & 0x4000) {
                        menuBackedOut = 1;
                        if ((gTrackSelectCursorX == 4) && (is_adventure_two_unlocked())) {
                            gMenuStage = -1;
                        } else {
                            gMenuDelay = -1;
                        }
                        if (gTrackSelectCursorX == 5) {
                            set_current_text(10000);
                        }
                    }
                } else if (gNumberOfActivePlayers == 1) {
                    if (gMenuButtons[0] & 0x4000) {
                        gMenuStage = 1;
                        menuBackedOut = 1;
                    }
                } else if (gNumberOfActivePlayers == 2) {
                    if (gMenuButtons[4] & 0x4000) {
                        gMenuStage = 2;
                        menuBackedOut = 1;
                    }
                } else {
                    for (i = 0; i < gNumberOfActivePlayers; i++) {
                        if (gMenuButtons[i] & 0x4000) {
                            gNumberOfReadyPlayers--;
                            gPlayerSelectConfirm[i] = 0;
                            gMenuStage = 0;
                            menuBackedOut = 1;
                        }
                    }
                }
                break;
        }
        if (menuBackedOut) {
            sound_play(SOUND_MENU_BACK3, 0);
        } else if (menuSelected) {
            sound_play(SOUND_SELECT2, 0);
        } else if (menuChanged) {
            sound_play(SOUND_MENU_PICK2, 0);
        }
        set_level_default_vehicle((enum Vehicle) * gPlayerSelectVehicle);
        if (gNumberOfActivePlayers >= 2 || gTrackSelectCursorX >= 4) {
            set_time_trial_enabled(0);
        } else {
            set_time_trial_enabled(gTracksMenuTimeTrialHighlightIndex);
        }
        gIsInAdventureTwo = gTracksMenuAdventureHighlightIndex;
    }
}
s32 trackmenu_staff_beaten(s32 mapId) {
    s8 *trackIdArray;
    s32 index;
    s32 temp;
    trackIdArray = (s8 *) get_misc_asset(ASSET_MISC_MAIN_TRACKS_IDS);
    index = 0;
    temp = -1;
    if (trackIdArray[0] != -1) {
        while (temp < 0) {
            if (mapId == (s32) trackIdArray[index]) {
                temp = index;
            }
            index++;
            if (trackIdArray[index] == -1) {
                break;
            }
        }
    }
    if (temp >= 0) {
        u64 temp2 = 0x10 << temp;
        if ((temp2 & sEepromSettings) == 0) {
            temp = -1;
        }
    }
    return temp;
}
void menu_adventure_track_init(void) {
    Settings *settings;
    s32 raceType;
    s32 mapId;
    s16 ttVoiceLine;
    settings = get_settings();
    gTrackIdForPreview = ASSET_LEVEL_CENTRALAREAHUB;
    gOptionBlinkTimer = 0;
    gMenuDelay = 0;
    mapId = settings->unk4C->mapID;
    gPlayerSelectVehicle[PLAYER_ONE] = leveltable_vehicle_default(mapId);
    raceType = leveltable_type(mapId);
    if (raceType == RACETYPE_HUBWORLD || raceType == RACETYPE_BOSS ||
        (!(raceType & RACETYPE_CHALLENGE) && (!(settings->courseFlagsPtr[mapId] & RACE_CLEARED)))) {
        ttVoiceLine = gTTVoiceLines[mapId];
        if (ttVoiceLine != -1) {
            sound_play_delayed(ttVoiceLine, 0, 1.0f);
        }
        gMenuStage = ADVENTURESETUP_PREVIEW;
    } else {
        ttVoiceLine = gTTVoiceLines[mapId];
        if (ttVoiceLine != -1) {
            sound_play_delayed(ttVoiceLine, 0, 0.5f);
        }
        music_voicelimit_set(24);
        music_play(SEQUENCE_MAIN_MENU);
        music_change_off();
        gMenuStage = ADVENTURESETUP_VEHICLE;
        menu_assetgroup_load(gAdvTrackInitObjectIndices);
        menu_imagegroup_load(gAdvTrackInitImageIndices);
        menu_init_vehicle_textures();
        gRaceSelectionCarOptHighlight[0].texture = gMenuAssets[TEXTURE_ICON_VEHICLE_SELECT_CAR_HIGHLIGHT];
        gRaceSelectionCarOpt[0].texture = gMenuAssets[TEXTURE_ICON_VEHICLE_SELECT_CAR];
        gRaceSelectionHoverOptHighlight[0].texture = gMenuAssets[TEXTURE_ICON_VEHICLE_SELECT_HOVERCRAFT_HIGHLIGHT];
        gRaceSelectionHoverOpt[0].texture = gMenuAssets[TEXTURE_ICON_VEHICLE_SELECT_HOVERCRAFT];
        gRaceSelectionPlaneOptHighlight[0].texture = gMenuAssets[TEXTURE_ICON_VEHICLE_SELECT_PLANE_HIGHLIGHT];
        gRaceSelectionPlaneOpt[0].texture = gMenuAssets[TEXTURE_ICON_VEHICLE_SELECT_PLANE];
        gRaceSelectionVehicleTitleTexture[0].texture = gMenuAssets[TEXTURE_ICON_VEHICLE_TITLE];
        gRaceSelectionTTTexture[0].texture = gMenuAssets[TEXTURE_UNK_69];
        transition_begin(&sMenuTransitionFadeOut);
        gOptionBlinkTimer = 0;
        gMenuDelay = 0;
        gTrackNameVoiceDelay = 30;
        load_font(ASSET_FONTS_BIGFONT);
        load_level_for_menu(mapId, -1, 1);
    }
    dialogue_clear(7);
    if (leveltable_type(mapId) & RACETYPE_CHALLENGE) {
        set_current_text(leveltable_world(mapId) + ASSET_GAME_TEXT_59);
    }
}
void adventuretrack_render( s32 updateRate, s32 arg1, s32 arg2) {
    s32 alpha;
    s32 y;
    s32 greenAmount;
    s32 i;
    s32 savedY;
    s32 yOffset;
    s32 mask;
    s32 mapID;
    char *filename;
    Settings *settings;
    char *levelName;
    filename = 0;
    settings = get_settings();
    yOffset = 0;
    if (osTvType == 0) {
        yOffset = 12;
    }
    mapID = ((Settings4C *) ((u8 *) settings->unk4C + gTrackIdForPreview))->mapID;
    { Gfx *_g = (Gfx *)(sMenuCurrDisplayList++); _g->words.w0 = ((unsigned int) (((unsigned int)((-65 -9)) & ((0x01 << (8)) - 1)) << (24))); _g->words.w1 = (unsigned int)(0x00001000); };
    menu_camera_centre();
    mtx_ortho(&sMenuCurrDisplayList, &sMenuCurrHudMat);
    if (gMenuDelay >= -20) {
        if (gMenuDelay <= 20) {
            mask = leveltable_vehicle_usable(mapID);
            levelName = level_name(mapID);
            set_text_font(FONT_LARGE);
            set_text_background_colour(0, 0, 0, 0);
            set_text_colour(0, 0, 0, 255, 128);
            draw_text(&sMenuCurrDisplayList, (320 / 2) + 1, 46, levelName, ALIGN_MIDDLE_CENTER);
            set_text_colour(255, 255, 255, 0, 255);
            draw_text(&sMenuCurrDisplayList, (320 / 2), 43, levelName, ALIGN_MIDDLE_CENTER);
            if (!(leveltable_type(mapID) & RACETYPE_CHALLENGE)) {
                if (arg2 == 0) {
                    if (is_time_trial_enabled()) {
                        if (trackmenu_staff_beaten(mapID) >= 0) {
                            texrect_draw(&sMenuCurrDisplayList, gRaceSelectionTTTexture, 240 - 36,
                                         yOffset + 122, 255, 255, 255, sMenuGuiOpacity);
                        }
                        set_text_font(ASSET_FONTS_FUNFONT);
                        set_text_colour(255, 64, 64, 96, 255);
                        draw_text(&sMenuCurrDisplayList, 56, yOffset + 72,
                                  gMenuText[ASSET_MENU_TEXT_BESTTIME], ALIGN_MIDDLE_LEFT);
                        draw_text(&sMenuCurrDisplayList, 56, yOffset + 92,
                                  gMenuText[ASSET_MENU_TEXT_BESTLAP], ALIGN_MIDDLE_LEFT);
                        set_text_colour(255, 128, 255, 96, 255);
                        filename_decompress(settings->courseInitialsPtr[gPlayerSelectVehicle[0]][mapID],
                                            (char *) &filename, 3);
                        draw_text(&sMenuCurrDisplayList, 250, yOffset + 72,
                                  (char *) &filename, ALIGN_MIDDLE_CENTER);
                        filename_decompress(settings->flapInitialsPtr[gPlayerSelectVehicle[0]][mapID],
                                            (char *) &filename, 3);
                        draw_text(&sMenuCurrDisplayList, 250, yOffset + 92,
                                  (char *) &filename, ALIGN_MIDDLE_CENTER);
                        menu_timestamp_render(settings->courseTimesPtr[gPlayerSelectVehicle[0]][mapID],
                                              22, 53, 128, 255, 255, 0);
                        menu_timestamp_render(settings->flapTimesPtr[gPlayerSelectVehicle[0]][mapID],
                                              22, 33, 255, 192, 255, 0);
                    }
                    greenAmount = gOptionBlinkTimer * 8;
                    if (greenAmount > 255) {
                        greenAmount = 511 - greenAmount;
                    }
                    set_current_dialogue_background_colour(7, 255, greenAmount, 0, 255);
                    set_current_dialogue_box_coords(7, 134, yOffset + 112, 186, yOffset + 137);
                    render_dialogue_box(&sMenuCurrDisplayList, 0, 0, 7);
                    texrect_draw(&sMenuCurrDisplayList, gRaceSelectionVehicleTitleTexture, 136, yOffset + 114, 255, 255,
                                 255, 255);
                    y = yOffset + 139;
                    savedY = y;
                    for (i = 0; i <= VEHICLE_PLANE; i++) {
                        alpha = (arg1 < 2 && leveltable_vehicle_default(mapID) != (Vehicle) i) ? 128 : 255;
                        if ((1 << i) & mask) {
                            if (i == gPlayerSelectVehicle[0]) {
                                texrect_draw(&sMenuCurrDisplayList, gRaceSelectionImages[i * 3 + 1], 104, y, 255, 255,
                                             255, 255);
                            } else {
                                texrect_draw(&sMenuCurrDisplayList, gRaceSelectionImages[i * 3 + 2], 104, y, 255, 255,
                                             255, alpha);
                            }
                            y += 24;
                        }
                    }
                    y = savedY;
                    if (gPlayerSelectVehicle[0] == 2) {
                        y += 2;
                    }
                    texrect_draw(&sMenuCurrDisplayList, gRaceSelectionImages[gPlayerSelectVehicle[0] * 3], 149, y, 255,
                                 255, 255, 255);
                    rendermode_reset(&sMenuCurrDisplayList);
                    gMenuImages[7].trans.x_position = 21.0f;
                    gMenuImages[7].trans.y_position = -52.0f;
                    menu_element_render(7);
                    if (gMenuStage != ADVENTURESETUP_VEHICLE) {
                        set_text_font(FONT_LARGE);
                        set_text_colour(255, 255, 255, 0, 255);
                        draw_text(&sMenuCurrDisplayList, (320 / 2), yOffset + 172, "OK?", ALIGN_MIDDLE_CENTER);
                    }
                } else {
                    set_text_font(FONT_LARGE);
                    set_text_background_colour(0, 0, 0, 0);
                    set_text_colour(255, 255, 255, 0, 255);
                    y = yOffset + 176;
                    if (get_language() == LANGUAGE_FRENCH) {
                        draw_text(&sMenuCurrDisplayList, (320 / 2), y, gMenuText[191], ALIGN_MIDDLE_CENTER);
                        y += 32;
                    }
                    draw_text(&sMenuCurrDisplayList, (320 / 2), y, gMenuText[ASSET_MENU_TEXT_SILVERCOIN],
                              ALIGN_MIDDLE_CENTER);
                    y += 32;
                    if (get_language() != LANGUAGE_FRENCH) {
                        draw_text(&sMenuCurrDisplayList, (320 / 2), y, gMenuText[191], ALIGN_MIDDLE_CENTER);
                    }
                }
            }
        }
    }
}
s32 menu_adventure_track_loop(s32 updateRate) {
    s32 vehicle;
    s32 vehicleFlags;
    s32 vehicle2;
    s32 challenge;
    s32 mapId;
    s32 sp20;
    s32 sp1C;
    Settings *settings;
    if (gMenuStage < ADVENTURESETUP_VEHICLE) {
        return gTrackIdForPreview | MENU_RESULT_FLAGS_80;
    }
    settings = get_settings();
    mapId = ((Settings4C *) ((u8 *) settings->unk4C + gTrackIdForPreview))->mapID;
    challenge = 0;
    sp1C = 0;
    if (settings->courseFlagsPtr[mapId] & RACE_CLEARED) {
        sp1C = 1;
    }
    if (settings->courseFlagsPtr[mapId] & RACE_CLEARED_SILVER_COINS) {
        sp1C = 2;
    }
    if (leveltable_type(mapId) & RACETYPE_CHALLENGE) {
        challenge = 1;
    }
    sp20 = 0;
    if (!is_time_trial_enabled()) {
        if (sp1C == 1) {
            if (settings->worldId == WORLD_FUTURE_FUN_LAND || (settings->bosses & (1 << settings->worldId))) {
                sp20 = 1;
            }
        }
    }
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    adventuretrack_render(updateRate, sp1C, sp20);
    if (sp1C < 2) {
        gPlayerSelectVehicle[PLAYER_ONE] = leveltable_vehicle_default(mapId);
    }
    vehicle = gPlayerSelectVehicle[PLAYER_ONE];
    vehicleFlags = leveltable_vehicle_usable(mapId);
    vehicle2 = vehicle;
    menu_input();
    if (gMenuDelay == 0) {
        if (gMenuStage != ADVENTURESETUP_VEHICLE || sp20 || challenge) {
            if (gMenuButtons[PLAYER_ONE] & (0x8000 | 0x1000)) {
                if (challenge) {
                    set_current_text(10000);
                }
                gMenuDelay = 1;
                transition_begin(&sMenuTransitionFadeIn);
                sound_play(SOUND_SELECT2, 0);
            } else if (gMenuButtons[PLAYER_ONE] & 0x4000) {
                sound_play(SOUND_MENU_BACK3, 0);
                if (sp20 || challenge) {
                    if (challenge) {
                        set_current_text(10000);
                    }
                    transition_begin(&sMenuTransitionFadeIn);
                    gMenuDelay = -1;
                } else {
                    gMenuStage = ADVENTURESETUP_VEHICLE;
                }
            }
        } else {
            if (gMenuButtons[PLAYER_ONE] & 0x4000) {
                sound_play(SOUND_MENU_BACK3, 0);
                transition_begin(&sMenuTransitionFadeIn);
                gMenuDelay = -1;
            } else if (gMenuButtons[PLAYER_ONE] & (0x8000 | 0x1000)) {
                gMenuStage = ADVENTURESETUP_CONFIRM;
                sound_play(SOUND_CAR_REV2, 0);
            } else if (sp1C >= 2) {
                if (gMenuStickY[PLAYER_ONE] > 0) {
                    do {
                        vehicle--;
                    } while (!((1 << vehicle) & vehicleFlags) && vehicle >= VEHICLE_CAR);
                }
                if (gMenuStickY[PLAYER_ONE] < 0) {
                    do {
                        vehicle++;
                    } while (!((1 << vehicle) & vehicleFlags) && vehicle <= VEHICLE_PLANE);
                }
                if (vehicle < VEHICLE_CAR || vehicle > VEHICLE_PLANE) {
                    vehicle = vehicle2;
                }
                if (vehicle != vehicle2) {
                    sound_play(SOUND_MENU_PICK2, 0);
                    gPlayerSelectVehicle[PLAYER_ONE] = vehicle;
                }
            }
        }
    } else {
        if (gMenuDelay < 0) {
            gMenuDelay = gMenuDelay - updateRate;
        } else {
            gMenuDelay = gMenuDelay + updateRate;
        }
        if (gMenuDelay > 30 || gMenuDelay < -30) {
            adventuretrack_free();
            if (gMenuDelay > 0) {
                return gTrackIdForPreview | 0x80;
            }
            return MENU_RESULT_UNK3 | 0x100;
        }
    }
    gIgnorePlayerInputTime = 0;
    return MENU_RESULT_CONTINUE;
}
void adventuretrack_free(void) {
    menu_assetgroup_free((s16 *) &gAdvTrackInitObjectIndices);
    unload_font(ASSET_FONTS_BIGFONT);
    music_change_on();
}
void menu_pause_init(void) {
    s32 raceType;
    s32 i;
    Settings *settings;
    rumble_init(0);
    settings = get_settings();
    gLastPlayerWhoPaused = -1;
    for (i = 0; (get_active_player_count() > i && gLastPlayerWhoPaused < 0); i++) {
        if (input_held(i) & 0x1000) {
            gLastPlayerWhoPaused = i;
        }
    }
    if (gLastPlayerWhoPaused < 0) {
        gLastPlayerWhoPaused = 0;
    }
    gMenuOptionText[0] = gMenuText[ASSET_MENU_TEXT_CONTINUE];
    gMenuOptionCap = 1;
    if (gTrophyRaceWorldId == 0) {
        raceType = leveltable_type(settings->courseId);
        if (settings->worldId == WORLD_CENTRAL_AREA && is_taj_challenge()) {
            gMenuOptionText[1] = gMenuText[ASSET_MENU_TEXT_ABANDONCHALLENGE];
            gMenuOptionCap = 2;
        } else if (settings->worldId > WORLD_CENTRAL_AREA && raceType != RACETYPE_BOSS) {
            if (raceType & RACETYPE_CHALLENGE) {
                gMenuOptionText[1] = gMenuText[ASSET_MENU_TEXT_RESTARTCHALLENGE];
                gMenuOptionText[2] = (!gIsInTracksMode) ? gMenuText[ASSET_MENU_TEXT_RETURNTOLOBBY]
                                                        : gMenuText[ASSET_MENU_TEXT_SELECTTRACK];
                gMenuOptionCap = 3;
            } else if (raceType == RACETYPE_DEFAULT) {
                gMenuOptionText[1] = gMenuText[ASSET_MENU_TEXT_RESTARTRACE];
                gMenuOptionText[2] = (!gIsInTracksMode) ? gMenuText[ASSET_MENU_TEXT_RETURNTOLOBBY]
                                                        : gMenuText[ASSET_MENU_TEXT_SELECTTRACK];
                gMenuOptionCap = 3;
            }
        } else if (gIsInTracksMode == 0 && raceType == RACETYPE_BOSS) {
            gMenuOptionText[1] = gMenuText[ASSET_MENU_TEXT_RESTARTRACE];
            gMenuOptionText[2] = gMenuText[ASSET_MENU_TEXT_RETURNTOLOBBY];
            gMenuOptionCap = 3;
        }
        if (gIsInTracksMode == 1 && gNumberOfActivePlayers == 1) {
            gMenuOptionText[gMenuOptionCap++] = gMenuText[ASSET_MENU_TEXT_SELECTCHARACTER];
        }
        gMenuOptionText[gMenuOptionCap++] = gMenuText[ASSET_MENU_TEXT_QUITGAME];
    } else {
        gMenuOptionText[gMenuOptionCap++] = gMenuText[ASSET_MENU_TEXT_QUITTROPHYRACE];
    }
    gMenuOption = 0;
    gOptionBlinkTimer = 0;
    gMenuDelay = 0;
    gIgnorePlayerInputTime = 1;
    gMenuSubOption = 0;
    reset_controller_sticks();
}
void pausemenu_render( s32 updateRate) {
    ColourRGBA *colour;
    s32 halfTemp;
    s32 halfX;
    s32 x;
    s32 temp;
    s32 textWidth;
    s32 i;
    s32 y;
    s32 alpha;
    for (i = 0, x = (320 / 2); i < gMenuOptionCap; i++) {
        textWidth = get_text_width(gMenuOptionText[i], 0, 0) + 8;
        if (x < textWidth) {
            x = textWidth;
        }
    }
    temp = (gMenuOptionCap * 16) + 28;
    if (osTvType == 0) {
        y = ((240 / 2) + 12);
    } else {
        y = (240 / 2);
    }
    clear_dialogue_box_open_flag(7);
    dialogue_clear(7);
    halfTemp = temp >> 1;
    halfX = x >> 1;
    set_current_dialogue_box_coords(7, (320 / 2) - halfX, y - halfTemp, (320 / 2) + halfX,
                                    halfTemp + y);
    colour = &gPlayerPauseBgColour[input_player_id(gLastPlayerWhoPaused)];
    set_current_dialogue_background_colour(7, colour->r, colour->g, colour->b, colour->a);
    set_dialogue_font(7, ASSET_FONTS_FUNFONT);
    set_current_text_background_colour(7, 128, 128, 255, 0);
    colour = &gPlayerPauseOptionsTextColour[input_player_id(gLastPlayerWhoPaused)];
    set_current_text_colour(7, colour->r, colour->g, colour->b, colour->a, 255);
    alpha = gOptionBlinkTimer * 8;
    if (alpha > 255) {
        alpha = 511 - alpha;
    }
    if (gMenuSubOption != 0) {
        i = halfTemp - 26;
        if (gTrophyRaceWorldId != 0) {
            render_dialogue_text(7, -0x8000, i + 8, gMenuText[ASSET_MENU_TEXT_QUITTROPHYRACETITLE], 1,
                                 ALIGN_MIDDLE_CENTER);
        } else {
            render_dialogue_text(7, -0x8000, i + 8, gMenuText[ASSET_MENU_TEXT_QUITGAMETITLE], 1,
                                 ALIGN_MIDDLE_CENTER);
        }
        if (gMenuSubOption == 1) {
            set_current_text_colour(7, 255, 255, 255, alpha, 255);
        } else {
            set_current_text_colour(7, 255, 255, 255, 0, 255);
        }
        render_dialogue_text(7, -0x8000, i + 28, gMenuText[ASSET_MENU_TEXT_OK], 1, ALIGN_MIDDLE_CENTER);
        if (gMenuSubOption == 2) {
            set_current_text_colour(7, 255, 255, 255, alpha, 255);
        } else {
            set_current_text_colour(7, 255, 255, 255, 0, 255);
        }
        render_dialogue_text(7, -0x8000, i + 44, gMenuText[ASSET_MENU_TEXT_CANCEL], 1, ALIGN_MIDDLE_CENTER);
    } else {
        i = gLastPlayerWhoPaused + 1;
        render_dialogue_text(7, -0x8000, 12, gMenuText[ASSET_MENU_TEXT_PAUSEOPTIONS], gLastPlayerWhoPaused + 1,
                             ALIGN_MIDDLE_CENTER);
        for (i = 0, y = 32; i < gMenuOptionCap; i++, y += 16) {
            if (i == gMenuOption) {
                set_current_text_colour(7, 255, 255, 255, alpha, 255);
            } else {
                set_current_text_colour(7, 255, 255, 255, 0, 255);
            }
            render_dialogue_text(7, -0x8000, y, gMenuOptionText[i], 1, ALIGN_MIDDLE_CENTER);
        }
    }
    open_dialogue_box(7);
}
s32 menu_pause_loop( Gfx **dl, s32 updateRate) {
    s8 temp;
    s32 playerId;
    s32 buttonsPressed;
    if (gMenuOptionCap == 0) {
        sound_volume_change(VOLUME_NORMAL);
        return PAUSE_NONE;
    }
    sound_volume_change(VOLUME_LOWER);
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    update_controller_sticks();
    buttonsPressed = 0;
    if (gIgnorePlayerInputTime == 0) {
        buttonsPressed = input_pressed(gLastPlayerWhoPaused);
    }
    if (gMenuDelay == 0) {
        if (gMenuSubOption != 0) {
            if (buttonsPressed & (0x8000 | 0x1000)) {
                sound_play(SOUND_SELECT2, 0);
                if (gMenuSubOption == 1) {
                    gMenuDelay = 1;
                } else {
                    gMenuSubOption = 0;
                }
            } else if (buttonsPressed & 0x4000) {
                sound_play(SOUND_SELECT2, 0);
                gMenuSubOption = 0;
            } else {
                temp = gMenuSubOption;
                playerId = gLastPlayerWhoPaused;
                if (gControllersYAxisDirection[playerId] != 0) {
                    gMenuSubOption = 3 - gMenuSubOption;
                }
                if (temp != gMenuSubOption) {
                    sound_play(SOUND_MENU_PICK2, 0);
                }
            }
        } else if (buttonsPressed & (0x8000 | 0x1000)) {
            sound_play(SOUND_SELECT2, 0);
            if (gMenuOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_QUITGAME] ||
                (gTrophyRaceWorldId != 0 &&
                 gMenuOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_QUITTROPHYRACE])) {
                gMenuSubOption = 2;
            } else {
                gMenuDelay = 1;
            }
        } else {
            temp = gMenuOption;
            playerId = gLastPlayerWhoPaused;
            buttonsPressed = gControllersYAxisDirection[playerId];
            if (buttonsPressed < 0) {
                gMenuOption++;
            }
            if (buttonsPressed > 0) {
                gMenuOption--;
            }
            if (gMenuOption < 0) {
                gMenuOption = gMenuOptionCap - 1;
            }
            if (gMenuOption >= gMenuOptionCap) {
                gMenuOption = 0;
            }
            if (temp != gMenuOption) {
                sound_play(SOUND_MENU_PICK2, 0);
            }
        }
    } else {
        gMenuDelay++;
        if (gMenuDelay >= 4) {
            menu_dialogue_end();
            if (gMenuSubOption == 1) {
                if (gTrophyRaceWorldId != 0) {
                    gTrophyRaceWorldId = 0;
                    if (gIsInTracksMode == 0) {
                        return PAUSE_QUIT_LOBBY;
                    }
                    return PAUSE_QUIT_TRACKS;
                }
                return PAUSE_OPT_4;
            }
            if (gMenuOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_CONTINUE]) {
                sound_volume_change(VOLUME_NORMAL);
                return PAUSE_CONTINUE;
            }
            if (gMenuOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_RESTARTRACE] ||
                gMenuOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_RESTARTCHALLENGE]) {
                if (gIsInTracksMode == 0 && gTTVoiceLines[get_ingame_map_id()] != -1) {
                    sound_play_delayed(gTTVoiceLines[get_ingame_map_id()], 0, 1.0f);
                }
                return PAUSE_RESET;
            }
            if (gMenuOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_RETURNTOLOBBY]) {
                return PAUSE_QUIT_LOBBY;
            }
            if (gMenuOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_SELECTTRACK]) {
                return PAUSE_QUIT_TRACKS;
            }
            if (gMenuOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_SELECTCHARACTER]) {
                return PAUSE_QUIT_CHARSELECT;
            }
            if (gMenuOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_ABANDONCHALLENGE]) {
                sound_volume_change(VOLUME_NORMAL);
                return PAUSE_QUIT_CHALLENGE;
            }
            return PAUSE_CONTINUE;
        }
    }
    pausemenu_render(updateRate);
    gIgnorePlayerInputTime = 0;
    return PAUSE_NONE;
}
void menu_dialogue_end(void) {
    rumble_init(1);
    dialogue_close(7);
    dialogue_clear(7);
    gMenuOptionCap = 0;
}
void menu_close_dialogue(void) {
    menu_dialogue_end();
}
void menu_racer_portraits(void) {
    gMenuPortraitKrunch[0].texture = gMenuAssets[TEXTURE_ICON_PORTRAIT_KRUNCH];
    gMenuPortraitDiddy[0].texture = gMenuAssets[TEXTURE_ICON_PORTRAIT_DIDDY];
    gMenuPortraitDrumstick[0].texture = gMenuAssets[TEXTURE_ICON_PORTRAIT_DRUMSTICK];
    gMenuPortraitBanjo[0].texture = gMenuAssets[TEXTURE_ICON_PORTRAIT_BANJO];
    gMenuPortraitBumper[0].texture = gMenuAssets[TEXTURE_ICON_PORTRAIT_BUMPER];
    gMenuPortraitConker[0].texture = gMenuAssets[TEXTURE_ICON_PORTRAIT_CONKER];
    gMenuPortraitTiptup[0].texture = gMenuAssets[TEXTURE_ICON_PORTRAIT_TIPTUP];
    gMenuPortraitTT[0].texture = gMenuAssets[TEXTURE_ICON_PORTRAIT_TT];
    gMenuPortraitPipsy[0].texture = gMenuAssets[TEXTURE_ICON_PORTRAIT_PIPSY];
    gMenuPortraitTimber[0].texture = gMenuAssets[TEXTURE_ICON_PORTRAIT_TIMBER];
}
void postrace_start(s32 finishState, s32 worldID) {
    s16 *var_v1;
    LevelHeader *header;
    rumble_init(0);
    header = level_header();
    gPostraceFinishState = finishState;
    if (is_in_two_player_adventure()) {
        set_scene_viewport_num(VIEWPORT_LAYOUT_1_PLAYER);
    }
    gPostRace1Player = 0;
    if (gNumberOfActivePlayers == 1 && gTrophyRaceWorldId == 0) {
        if (is_in_tracks_mode() == 1) {
            gResultOptionText[0] = gMenuText[ASSET_MENU_TEXT_TRYAGAIN];
            gResultOptionText[1] = gMenuText[ASSET_MENU_TEXT_SELECTTRACK];
            gResultOptionText[2] = gMenuText[ASSET_MENU_TEXT_SELECTCHARACTER];
            gResultOptionCount = 3;
            gPostRace1Player = 1;
        } else {
            if (finishState == 0) {
                gResultOptionText[0] = gMenuText[ASSET_MENU_TEXT_TRYAGAIN];
                gResultOptionCount = 1;
            } else {
                gResultOptionCount = 0;
            }
            gResultOptionText[gResultOptionCount] = gMenuText[ASSET_MENU_TEXT_RETURNTOLOBBY];
            gResultOptionCount++;
        }
        gResultOptionText[gResultOptionCount] = gMenuText[ASSET_MENU_TEXT_QUIT];
        gResultOptionCount++;
        gMenuStage = POSTRACE_STAGE_BEGIN;
    } else {
        gMenuStage = POSTRACE_STAGE_FADE_OUT;
    }
    gFileNew = 0;
    gOptionBlinkTimer = 0;
    gOpacityDecayTimer = 0;
    gMenuDelay = 0;
    gMenuCurIndex = 0;
    gMenuOption = 0;
    gIgnorePlayerInputTime = 1;
    gPostRace.unk0_s32 = -1;
    gMenuSubOption = 0;
    gPostRaceMessage = 0;
    gTracksSaveGhost = 0;
    if (header->race_type & RACETYPE_CHALLENGE) {
        gIgnorePlayerInputTime = normalise_time(240);
    }
    if (gPostraceFinishState) {
        gMenuStage = POSTRACE_STAGE_END;
        gMenuDelay = 100;
    }
    if (get_game_mode() != GAMEMODE_INGAME) {
        gMenuStage = POSTRACE_STAGE_FADE_OUT;
    }
    reset_controller_sticks();
    race_postrace_type(finishState);
    gTrackSelectViewPortX = fb_size();
    gTrackSelectViewportY = (gTrackSelectViewPortX >> 16) & 0xFFFF;
    gTrackSelectViewPortX = (gTrackSelectViewPortX & 0xFFFF);
    gTrackSelectViewPortHalfX = gTrackSelectViewPortX >> 1;
    gTrackSelectViewPortHalfY = gTrackSelectViewportY >> 1;
    if (gNumberOfActivePlayers == 1 && gTrophyRaceWorldId == 0) {
        gPostRace.unk0_s32 = 0;
        worldID = header->world - 1;
        var_v1 = &gTracksMenuBgTextureIndices[worldID * 3];
        if (var_v1[0] != -1) {
            menu_asset_load(var_v1[0]);
            gMenuMosaic1 = gMenuAssets[var_v1[0]];
        } else {
            gMenuMosaic1 = 0;
        }
        if (var_v1[1] != -1) {
            menu_asset_load(var_v1[1]);
            gMenuMosaic2 = gMenuAssets[var_v1[1]];
        } else {
            gMenuMosaic2 = 0;
        }
        gMenuMosaicShift = var_v1[2];
        if (get_game_mode() == GAMEMODE_INGAME) {
            bgdraw_texture_init(gMenuMosaic1, gMenuMosaic2, gMenuMosaicShift);
        }
        camEnableUserView(0, 1);
        viewport_menu_set(0, 0, 0, gTrackSelectViewPortX, gTrackSelectViewportY);
    }
    sound_volume_change(VOLUME_LOWER_AMBIENT);
}
void postrace_load(void) {
    s32 pad[2];
    Settings *settings;
    s16 temp_a0;
    s32 i;
    s32 j;
    if (gPostRace.unk0_s32 >= 0) {
        if (gPostRace.unk0_s32 < 10) {
            gPostRace.unk0_s32++;
            return;
        }
        temp_a0 = D_800E0A10[gPostRace.unk0_s32];
        if (temp_a0 == -1) {
            menu_imagegroup_load(gRaceResultsImageIndices);
            menu_racer_portraits();
            settings = get_settings();
            gRaceResultsMenuElements->t.element = gRacerPortraits[settings->racers[settings->timeTrialRacer].character];
            if (is_time_trial_enabled() == 0) {
                for (i = 0; i < 8; i++) {
                    for (j = 0; j < 8; j++) {
                        if (i == settings->racers[j].starting_position) {
                            gRaceOrderMenuElements[7 - i].t.element = gRacerPortraits[settings->racers[j].character];
                        }
                    }
                }
                if (is_in_two_player_adventure()) {
                    for (i = 0; i < 6; i++) {
                        gRaceOrderMenuElements[i + 1].t.element = gRaceOrderMenuElements[i + 2].t.element;
                    }
                    gRaceOrderMenuElements[7].t.element = &D_80126850;
                    gRaceOrderMenuElements[0].t.element = &D_80126850;
                }
            }
            gPostRace.unk0_s32 = -1;
            return;
        }
        menu_asset_load(temp_a0);
        gPostRace.unk0_s32++;
    }
}
void postrace_music_fade(s32 updateRate) {
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    gPostRaceTimer += updateRate;
    if (gOpacityDecayTimer >= 0) {
        gOpacityDecayTimer += updateRate;
        switch (gMenuCurIndex) {
            case 0:
                if (normalise_time(240) < gOpacityDecayTimer) {
                    music_fade(-256);
                    gMenuCurIndex = 1;
                }
                break;
            case 1:
                if (normalise_time(300) < gOpacityDecayTimer) {
                    music_voicelimit_set(24);
                    music_play(SEQUENCE_MAIN_MENU);
                    music_fade(256);
                }
                break;
        }
        if (normalise_time(300) < gOpacityDecayTimer) {
            gOpacityDecayTimer = -1;
        }
    }
}
void postrace_viewport( s32 updateRate) {
    s32 temp;
    s32 var_s3;
    Settings *settings;
    s32 sp50;
    s32 var_s2;
    s32 var_s0;
    s32 i;
    s32 sp40;
    s32 filterColour;
    s32 var_v0;
    settings = get_settings();
    if (gNumberOfActivePlayers == 1) {
        mtx_ortho(&sMenuCurrDisplayList, &sMenuCurrHudMat);
    }
    camDisableUserView(0, 1);
    var_s3 = gOptionBlinkTimer * 8;
    if (var_s3 > 255) {
        var_s3 = 511 - var_s3;
    }
    switch (gMenuStage) {
        case 1:
            var_s0 = gPostRaceTimer;
            if (var_s0 > 60) {
                var_s0 = 60;
            }
            var_s2 = ((gTrackSelectViewPortHalfY - ((gTrackSelectViewPortHalfY * 4) / 5)) * var_s0) / 60;
            temp = var_s2;
            sp50 =
                gTrackSelectViewportY - (((gTrackSelectViewPortHalfY - (gTrackSelectViewPortHalfY / 5)) * var_s0) / 60);
            var_v0 = (var_s0 * 80) / 60;
            viewport_menu_set(0, var_v0, temp, 320 - var_v0, sp50);
            gMenuImages[4].trans.x_position = 0.0f;
            gMenuImages[4].trans.y_position = gTrackSelectViewPortHalfY - ((var_s2 + sp50) >> 1);
            gMenuImages[4].trans.scale = sMenuImageProperties[4].trans.scale * (2.0f - (var_s0 / 60.0f));
            break;
        case 2:
            for (i = 0; i < 3; i++) {
                if (settings->display_times && settings->racers[PLAYER_ONE].best_times & (1 << i)) {
                    gRaceResultsMenuElements[i + 3].filterGreen = 192 - ((var_s3 * 3) >> 2);
                    gRaceResultsMenuElements[i + 3].filterBlue = 255 - var_s3;
                } else {
                    gRaceResultsMenuElements[i + 3].filterGreen = 192;
                    gRaceResultsMenuElements[i + 3].filterBlue = 255;
                }
            }
            if (settings->display_times && settings->racers[0].best_times & (1 << 7)) {
                gRaceResultsMenuElements[6].filterRed = (var_s3 >> 1) + 128;
                gRaceResultsMenuElements[6].filterGreen = 255 - var_s3;
                gRaceResultsMenuElements[6].filterBlue = 255 - var_s3;
            } else {
                gRaceResultsMenuElements[6].filterRed = 128;
                gRaceResultsMenuElements[6].filterGreen = 255;
                gRaceResultsMenuElements[6].filterBlue = 255;
            }
            break;
        case 3:
            for (i = 0; i < (s32)(sizeof(settings->racers) / sizeof(settings->racers[0])); i++) {
                filterColour = 255;
                sp40 = i;
                if (is_in_two_player_adventure()) {
                    sp40--;
                    if (sp40 == settings->racers[1].starting_position) {
                        filterColour = (var_s3 >> 1) + 128;
                    }
                }
                if (sp40 == settings->racers[0].starting_position) {
                    filterColour = (var_s3 >> 1) + 128;
                }
                gRaceOrderMenuElements[7 - i].filterRed = filterColour;
                gRaceOrderMenuElements[7 - i].filterGreen = filterColour;
                gRaceOrderMenuElements[7 - i].filterBlue = filterColour;
            }
            break;
        case 5:
            if (settings->display_times && settings->racers[0].best_times & (s8) ~(1 << 7)) {
                gRecordTimesMenuElements[6].filterRed = 255;
                gRecordTimesMenuElements[6].filterGreen = 192 - ((var_s3 * 3) >> 2);
                gRecordTimesMenuElements[6].filterBlue = 255 - var_s3;
            } else {
                gRecordTimesMenuElements[6].filterRed = 255;
                gRecordTimesMenuElements[6].filterGreen = 192;
                gRecordTimesMenuElements[6].filterBlue = 255;
            }
            if (settings->display_times && settings->racers[0].best_times & (1 << 7)) {
                gRecordTimesMenuElements[3].filterRed = (var_s3 >> 1) + 128;
                gRecordTimesMenuElements[3].filterGreen = 255 - var_s3;
                gRecordTimesMenuElements[3].filterBlue = 255 - var_s3;
            } else {
                gRecordTimesMenuElements[3].filterRed = 128;
                gRecordTimesMenuElements[3].filterGreen = 255;
                gRecordTimesMenuElements[3].filterBlue = 255;
            }
            break;
        case 6:
            clear_dialogue_box_open_flag(7);
            dialogue_clear(7);
            set_dialogue_font(7, FONT_COLOURFUL);
            set_current_text_background_colour(7, 0, 0, 0, 0);
            if (gTracksSaveGhost != 0) {
                var_s0 = 1;
            } else if (gPostRaceMessage != 0) {
                var_s0 = gPostRaceLineCount;
            } else {
                var_s0 = gResultOptionCount;
            }
            if (var_s0 >= 5) {
                var_v0 = 2;
                sp50 = 13;
            } else {
                var_v0 = 0;
                sp50 = 16;
            }
            var_s2 = ((var_s0 * sp50) + 1) >> 1;
            var_s0 = 192;
            if (osTvType == 0) {
                var_s0 = 218;
            }
            set_current_dialogue_box_coords(7, 0, var_s0 - var_s2 - var_v0 - 4, 320,
                                            var_s0 + var_s2 + var_v0 + 4);
            set_current_dialogue_background_colour(7, 64, 64, 255, 0);
            set_current_text_colour(7, 255, 0, 255, 64, 255);
            if (gTracksSaveGhost != 0) {
                render_dialogue_text(7, -0x8000, 12, gMenuText[ASSET_MENU_TEXT_PLEASEWAIT], 1, ALIGN_MIDDLE_CENTER);
            } else if (gPostRaceMessage != 0) {
                var_s2 = 12;
                for (var_s0 = 0; var_s0 < gPostRaceLineCount; var_s0++) {
                    render_dialogue_text(7, -0x8000, var_s2, gPostRaceMessage[var_s0], 1, ALIGN_MIDDLE_CENTER);
                    var_s2 += sp50;
                }
            } else {
                var_s2 -= 24;
                if (gMenuSubOption != 0) {
                    render_dialogue_text(7, -0x8000, var_s2 + 8, gMenuText[ASSET_MENU_TEXT_QUITGAMETITLE], 1,
                                         ALIGN_MIDDLE_CENTER);
                    var_s0 = 0;
                    if (gMenuSubOption == 1) {
                        var_s0 = var_s3;
                    }
                    set_current_text_colour(7, 255, 255, 255, var_s0, 255);
                    render_dialogue_text(7, -0x8000, var_s2 + 26, gMenuText[ASSET_MENU_TEXT_OK], 1,
                                         ALIGN_MIDDLE_CENTER);
                    var_s0 = 0;
                    if (gMenuSubOption == 2) {
                        var_s0 = var_s3;
                    }
                    set_current_text_colour(7, 255, 255, 255, var_s0, 255);
                    render_dialogue_text(7, -0x8000, var_s2 + 42, gMenuText[ASSET_MENU_TEXT_CANCEL], 1,
                                         ALIGN_MIDDLE_CENTER);
                } else {
                    for (var_s2 = 12, var_s0 = 0; var_s0 < gResultOptionCount; var_s0++) {
                        if (var_s0 == gMenuOption) {
                            set_current_text_colour(7, 255, 255, 255, var_s3, 255);
                        } else {
                            set_current_text_colour(7, 255, 255, 255, 0, 255);
                        }
                        render_dialogue_text(7, (320 / 2), var_s2, gResultOptionText[var_s0], 1,
                                             ALIGN_MIDDLE_CENTER);
                        var_s2 += sp50;
                    }
                }
            }
            open_dialogue_box(7);
            break;
    }
    if (get_game_mode() == GAMEMODE_INGAME && gNumberOfActivePlayers == 1) {
        if (gTrophyRaceWorldId == 0) {
            camEnableUserView(0, 1);
            if (osTvType == 0) {
                gTrackSelectWoodFrameHeightScale = 1.2f;
            }
            if (gMenuStage > 0) {
                menu_element_render(4);
            }
            gTrackSelectWoodFrameHeightScale = 1.0f;
        }
    }
}
void postrace_message(SIDeviceStatus status) {
    switch (status & 0xFF) {
        case CONTROLLER_PAK_NOT_FOUND:
        case CONTROLLER_PAK_CHANGED: gPostRaceMessage = sNoControllerPakMenuText;
            break;
        case CONTROLLER_PAK_FULL:
        case CONTROLLER_PAK_NO_ROOM_FOR_GHOSTS: gPostRaceMessage = sControllerPakFullMenuText;
            break;
        case CONTROLLER_PAK_RUMBLE_PAK_FOUND:
            gPostRaceMessage = sInsertControllerPakMenuText;
            break;
        case CONTROLLER_PAK_SWITCH_TO_RUMBLE:
            gPostRaceMessage = sInsertRumblePakMenuText;
            break;
        case CONTROLLER_PAK_BAD_DATA:
            gPostRaceMessage = sCorruptDataMenuText;
            break;
        default:
            gPostRaceMessage = sBadControllerPakMenuText;
            break;
    }
    for (gPostRaceLineCount = 0; gPostRaceMessage[gPostRaceLineCount] != 0; gPostRaceLineCount++) {}
}
s32 menu_postrace(Gfx **dList, Mtx **matrices, Vertex **vertices, s32 updateRate) {
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 i;
    s32 ret;
    s32 buttonsPressed;
    s32 prevMenuOption;
    s32 textOffsetY;
    s32 timeOffsetY;
    s32 numPlayers;
    Settings *settings;
    Racer *racer;
    char *chosenOption;
    sp54 = 0;
    sp50 = 0;
    sp4C = 0;
    ret = POSTRACE_NONE;
    sMenuCurrDisplayList = *dList;
    sMenuCurrHudMat = *matrices;
    sMenuCurrHudVerts = *vertices;
    settings = get_settings();
    if (osTvType == 0) {
        textOffsetY = 26;
        timeOffsetY = 12;
    } else {
        textOffsetY = 0;
        timeOffsetY = 0;
    }
    numPlayers = gNumberOfActivePlayers;
    if (is_in_two_player_adventure()) {
        numPlayers = 2;
    }
    if (gPostRace1Player) {
        if (has_ghost_to_save()) {
            gResultOptionText[gResultOptionCount - 1] = gMenuText[ASSET_MENU_TEXT_SAVEGHOST];
            gResultOptionText[gResultOptionCount] = gMenuText[ASSET_MENU_TEXT_QUIT];
            gResultOptionCount++;
        }
        gPostRace1Player = 0;
    }
    postrace_load();
    postrace_music_fade(updateRate);
    if (gMenuDelay < 20 && gPostraceFinishState == 0) {
        if (gPostRace.unk0_s32 < 0) {
            postrace_viewport(updateRate);
        }
    } else {
        bgdraw_texture_init(0, 0, 0);
    }
    update_controller_sticks();
    buttonsPressed = 0;
    if (gIgnorePlayerInputTime == 0 && gPostRace.unk0_s32 < 0) {
        for (i = 0; i < numPlayers; i++) {
            buttonsPressed |= input_pressed(i);
        }
    }
    switch (gMenuStage) {
        case POSTRACE_STAGE_BEGIN:
            if (buttonsPressed & (0x8000 | 0x1000)) {
                gMenuStage = POSTRACE_STAGE_SHRINK_VIEWPORT;
                gPostRaceTimer = 0;
            }
            break;
        case POSTRACE_STAGE_SHRINK_VIEWPORT:
            if (gPostRaceTimer > 60 || buttonsPressed & (0x8000 | 0x1000)) {
                viewport_menu_set(0, 80, gTrackSelectViewPortHalfY - ((gTrackSelectViewPortHalfY * 4) / 5),
                                  240, (gTrackSelectViewPortHalfY / 5) + gTrackSelectViewPortHalfY);
                gMenuImages[4].trans.x_position = 0.0f;
                gMenuImages[4].trans.y_position = 36.0f;
                gMenuImages[4].trans.scale = sMenuImageProperties[4].trans.scale;
                if (leveltable_type(settings->courseId) & RACETYPE_CHALLENGE) {
                    gMenuStage = POSTRACE_STAGE_OPTIONS;
                } else if (!settings->display_times) {
                    postrace_offsets(gRaceOrderMenuElements, 0.5f, 15.0f, 0.5f, textOffsetY, timeOffsetY);
                    gMenuStage = POSTRACE_STAGE_RACE_ORDER;
                } else {
                    racer = &settings->racers[settings->timeTrialRacer];
                    gRaceResultsMenuElements[3].t.numberU16 = &racer->lap_times[0];
                    gRaceResultsMenuElements[4].t.numberU16 = &racer->lap_times[1];
                    gRaceResultsMenuElements[5].t.numberU16 = &racer->lap_times[2];
                    gRaceResultsMenuElements[6].t.numberU16 = &racer->course_time;
                    postrace_offsets(gRaceResultsMenuElements, 0.5f, 15.0f, 0.5f, textOffsetY, timeOffsetY);
                    gMenuStage = POSTRACE_STAGE_RACE_TIMES;
                }
            }
            break;
        case POSTRACE_STAGE_RACE_TIMES:
            if (postrace_render(updateRate) != 0) {
                if (gTrophyRaceWorldId != 0) {
                    music_fade(-128);
                    transition_begin(&sMenuTransitionFadeIn);
                    gMenuStage = POSTRACE_STAGE_END;
                } else if (settings->display_times) {
                    gRecordTimesMenuElements[3].t.numberU16 =
                        &settings->courseTimesPtr[*gPlayerSelectVehicle][settings->courseId];
                    gRecordTimesMenuElements[6].t.numberU16 =
                        &settings->flapTimesPtr[*gPlayerSelectVehicle][settings->courseId];
                    filename_decompress(settings->courseInitialsPtr[*gPlayerSelectVehicle][settings->courseId],
                                        gCourseInitials, 3);
                    filename_decompress(settings->flapInitialsPtr[*gPlayerSelectVehicle][settings->courseId],
                                        gFLapInitials, 3);
                    if (settings->racers[0].best_times != 0) {
                        gMenuStage = POSTRACE_STAGE_ENTER_INITIALS;
                        if (gIsInTracksMode == 0 && D_800E0FAC != 0) {
                            filename_decompress(settings->filename, gCheckAdvEnterInitials, 3);
                            D_800E0FAC = 0;
                        }
                        filename_init(textOffsetY + 196, 160, textOffsetY + 120, 2, &D_800E0FA4, gCheckAdvEnterInitials,
                                      3);
                    } else {
                        postrace_offsets(gRecordTimesMenuElements, 0.5f, 15.0f, 0.5f, textOffsetY, timeOffsetY);
                        gMenuStage = POSTRACE_STAGE_RACE_RECORDS;
                    }
                } else {
                    gMenuStage = POSTRACE_STAGE_RACE_ORDER;
                    postrace_offsets(gRaceOrderMenuElements, 0.5f, 15.0f, 0.5f, textOffsetY, timeOffsetY);
                }
            }
            break;
        case POSTRACE_STAGE_RACE_ORDER:
            if (postrace_render(updateRate)) {
                gMenuStage = POSTRACE_STAGE_OPTIONS;
            }
            break;
        case POSTRACE_STAGE_ENTER_INITIALS:
            if (filename_enter(updateRate)) {
                if (settings->racers[0].best_times & 0x7F) {
                    settings->flapInitialsPtr[*gPlayerSelectVehicle][settings->courseId] =
                        filename_compress(gCheckAdvEnterInitials, 3);
                    filename_decompress(settings->flapInitialsPtr[*gPlayerSelectVehicle][settings->courseId],
                                        gFLapInitials, 3);
                }
                if (settings->racers[0].best_times & 0x80) {
                    settings->courseInitialsPtr[*gPlayerSelectVehicle][settings->courseId] =
                        filename_compress(gCheckAdvEnterInitials, 3);
                    filename_decompress(settings->courseInitialsPtr[*gPlayerSelectVehicle][settings->courseId],
                                        gCourseInitials, 3);
                }
                postrace_offsets(gRecordTimesMenuElements, 0.5f, 15.0f, 0.5f, textOffsetY, timeOffsetY);
                gMenuStage = POSTRACE_STAGE_RACE_RECORDS;
            }
            break;
        case POSTRACE_STAGE_RACE_RECORDS:
            if (postrace_render(updateRate)) {
                gMenuStage = POSTRACE_STAGE_OPTIONS;
            }
            break;
        case POSTRACE_STAGE_OPTIONS:
            if (gTracksSaveGhost) {
                gTracksSaveGhost++;
                if (gTracksSaveGhost >= 5) {
                    sound_volume_change(3);
                    sp54 = timetrial_save_player_ghost(0);
                    if ((sp54 & 0xFF) == 5) {
                        sp54 = timetrial_save_player_ghost(0);
                    }
                    sound_volume_change(2);
                    if (sp54) {
                        postrace_message(sp54);
                        sp54 = 1;
                    } else {
                        if (gPostRaceMessage == sInsertControllerPakMenuText) {
                            postrace_message(CONTROLLER_PAK_SWITCH_TO_RUMBLE);
                        } else {
                            gPostRaceMessage = 0;
                        }
                        gResultOptionText[gMenuOption] = gMenuText[28];
                        gMenuOption = 0;
                        gResultOptionCount -= 1;
                    }
                    gTracksSaveGhost = 0;
                }
            } else if (gPostRaceMessage != 0) {
                if (buttonsPressed & (0x8000 | 0x1000)) {
                    sp50 = 1;
                    if (gPostRaceMessage == sInsertControllerPakMenuText) {
                        gTracksSaveGhost = 1;
                    } else {
                        gPostRaceMessage = 0;
                    }
                } else if (buttonsPressed & 0x4000) {
                    gPostRaceMessage = 0;
                    sp54 = 1;
                }
            } else {
                if (gMenuSubOption != 0) {
                    if (buttonsPressed & (0x8000 | 0x1000)) {
                        if (gMenuSubOption == 1) {
                            sp50 = 1;
                            music_fade(-128);
                            transition_begin(&sMenuTransitionFadeIn);
                            gMenuStage = POSTRACE_STAGE_END;
                        } else {
                            sp54 = 1;
                            gMenuSubOption = 0;
                        }
                    } else {
                        prevMenuOption = gMenuSubOption;
                        if (buttonsPressed & 0x4000) {
                            sp54 = 1;
                            gMenuSubOption = 0;
                        } else {
                            for (i = 0; i < numPlayers; i++) {
                                if ((gControllersYAxisDirection[i] > 0) && (gMenuSubOption == 2)) {
                                    gMenuSubOption = 1;
                                }
                                if ((gControllersYAxisDirection[i] < 0) && (gMenuSubOption == 1)) {
                                    gMenuSubOption = 2;
                                }
                            }
                            if (prevMenuOption != gMenuSubOption) {
                                sp4C = 1;
                            }
                        }
                    }
                } else if (buttonsPressed & (0x8000 | 0x1000)) {
                    sp50 = 1;
                    chosenOption = gResultOptionText[gMenuOption];
                    if (chosenOption == gMenuText[ASSET_MENU_TEXT_SAVEGHOST]) {
                        gTracksSaveGhost = 1;
                    } else if (chosenOption == gMenuText[ASSET_MENU_TEXT_QUIT]) {
                        gMenuSubOption = 2;
                    } else {
                        music_fade(-128);
                        transition_begin(&sMenuTransitionFadeIn);
                        gMenuStage = POSTRACE_STAGE_END;
                    }
                } else {
                    prevMenuOption = gMenuOption;
                    for (i = 0; i < numPlayers; i++) {
                        if (gControllersYAxisDirection[i] < 0) {
                            if (gMenuOption < (gResultOptionCount - 1)) {
                                gMenuOption++;
                            }
                        }
                        if (gControllersYAxisDirection[i] > 0) {
                            if (gMenuOption > 0) {
                                gMenuOption--;
                            }
                        }
                    }
                    if (prevMenuOption != gMenuOption) {
                        sp4C = 1;
                    }
                }
            }
            if (sp54 != 0) {
                sound_play(SOUND_MENU_BACK3, 0);
            } else if (sp50 != 0) {
                sound_play(SOUND_SELECT2, 0);
            } else if (sp4C != 0) {
                sound_play(SOUND_MENU_PICK2, 0);
            }
            break;
        case POSTRACE_STAGE_FADE_OUT:
            if (buttonsPressed & (0x8000 | 0x1000)) {
                music_fade(-128);
                transition_begin(&sMenuTransitionFadeIn);
                gMenuStage = POSTRACE_STAGE_END;
            }
            break;
        case POSTRACE_STAGE_END:
            gMenuDelay += updateRate;
            if (gMenuDelay > 30) {
                if (settings->display_times) {
                    if (settings->racers[0].best_times & 0x7F) {
                        mark_to_write_flap_times();
                    }
                    if (settings->racers[0].best_times & 0x80) {
                        mark_to_write_course_times();
                    }
                }
                camDisableUserView(0, 0);
                postrace_free();
                dialogue_close(7);
                dialogue_clear(7);
                if (gPostraceFinishState >= 2) {
                    if (gPostraceFinishState == 9) {
                        cinematic_start((s8 *) get_misc_asset(ASSET_MISC_CINEMATIC_RACE), gPostraceFinishState,
                                        MENU_RESULT_FLAGS_100 | MENU_RESULT_FLAGS_2 | MENU_RESULT_FLAGS_4 |
                                            MENU_RESULT_FLAGS_8,
                                        0, 0, 0);
                    } else {
                        cinematic_start((s8 *) get_misc_asset(ASSET_MISC_CINEMATIC_RACE), gPostraceFinishState,
                                        MENU_RESULT_FLAGS_100 | MENU_RESULT_FLAGS_1, 0, 0, 0);
                    }
                    ret = POSTRACE_OPT_13;
                } else if (gTrophyRaceWorldId != 0) {
                    ret = POSTRACE_OPT_10;
                } else if (gNumberOfActivePlayers >= 2) {
                    ret = POSTRACE_OPT_8;
                } else {
                    chosenOption = gResultOptionText[gMenuOption];
                    if (chosenOption == gMenuText[ASSET_MENU_TEXT_TRYAGAIN]) {
                        if (!gIsInTracksMode && gTTVoiceLines[get_ingame_map_id()] != -1) {
                            sound_play_delayed(gTTVoiceLines[get_ingame_map_id()], 0, 1.0f);
                        }
                        ret = POSTRACE_OPT_2;
                    } else if (chosenOption == gMenuText[ASSET_MENU_TEXT_SELECTTRACK]) {
                        ret = POSTRACE_OPT_5;
                    } else if (chosenOption == gMenuText[ASSET_MENU_TEXT_SELECTCHARACTER]) {
                        ret = POSTRACE_OPT_12;
                    } else if (chosenOption == gMenuText[ASSET_MENU_TEXT_RETURNTOLOBBY]) {
                        ret = POSTRACE_OPT_1;
                    } else {
                        ret = POSTRACE_OPT_4;
                    }
                }
            }
            break;
    }
    if (gIgnorePlayerInputTime > 0) {
        gIgnorePlayerInputTime -= updateRate;
        if (gIgnorePlayerInputTime < 0) {
            gIgnorePlayerInputTime = 0;
        }
    }
    *dList = sMenuCurrDisplayList;
    *matrices = sMenuCurrHudMat;
    *vertices = sMenuCurrHudVerts;
    return ret;
}
void postrace_free(void) {
    s32 headerWorldTex;
    LevelHeader *header;
    header = level_header();
    menu_assetgroup_free(gRaceResultsObjectIndices);
    headerWorldTex = header->world - 1;
    if (gMenuMosaic1) {
        menu_asset_free(gTracksMenuBgTextureIndices[headerWorldTex * 3]);
    }
    gMenuMosaic1 = 0;
    if (gMenuMosaic2) {
        menu_asset_free(gTracksMenuBgTextureIndices[(headerWorldTex * 3) + 1]);
    }
    gMenuMosaic2 = 0;
    menu_unload_bigfont();
    sound_volume_change(VOLUME_NORMAL);
}
void menu_results_init(void) {
    Settings *settings;
    u16 *placements;
    s32 i;
    s8 startPos;
    settings = get_settings();
    gResultOptionText[0] = gMenuText[ASSET_MENU_TEXT_SELECTTRACK];
    gResultOptionText[1] = gMenuText[ASSET_MENU_TEXT_TRYAGAIN];
    gResultOptionText[2] = gMenuText[ASSET_MENU_TEXT_QUIT];
    gResultOptionCount = 3;
    for (i = 0; i < gNumberOfActivePlayers; i++) {
        startPos = settings->racers[i].starting_position;
        if (startPos < 4) {
            placements = settings->racers[i].placements;
            placements[startPos]++;
        }
    }
    gMenuStage = RESULTS_ENTER;
    gOptionBlinkTimer = 0;
    gOpacityDecayTimer = 0;
    gMenuDelay = 0;
    gMenuOption = 0;
    gIgnorePlayerInputTime = 1;
    gMenuSubOption = 0;
    menu_assetgroup_load(gRaceResultsObjectIndices);
    menu_imagegroup_load(gRaceResultsImageIndices);
    menu_racer_portraits();
    load_font(ASSET_FONTS_BIGFONT);
    transition_begin(&sMenuTransitionFadeOut);
    music_voicelimit_set(24);
    music_play(SEQUENCE_MAIN_MENU);
    music_fade(128);
}
void results_render( s32 updateRate, f32 opacity) {
    s32 x2;
    s32 y2;
    s32 offsetX;
    s32 spA0;
    s32 time;
    s32 offsetY;
    s32 hundredths;
    s32 tens;
    s32 pad;
    s32 i;
    s32 offsetX2;
    s32 timesToLoop;
    Settings *settings;
    settings = get_settings();
    offsetY = 0;
    if (osTvType == 0) {
        offsetY = 12;
    }
    mtx_ortho(&sMenuCurrDisplayList, &sMenuCurrHudMat);
    if (opacity < 0.0f) {
        opacity = 0.0f;
    }
    if (opacity > 1.0f) {
        opacity = 1.0f;
    }
    sMenuGuiOpacity = (1 - opacity) * 255;
    set_text_font(ASSET_FONTS_BIGFONT);
    set_text_background_colour(0, 0, 0, 0);
    set_text_colour(255, 255, 255, 0, sMenuGuiOpacity);
    draw_text(&sMenuCurrDisplayList, -0x8000, 34, gMenuText[ASSET_MENU_TEXT_RANKINGS], ALIGN_MIDDLE_CENTER);
    sMenuGuiOpacity = 255;
    offsetX2 = 64;
    if (gNumberOfActivePlayers == 4) {
        offsetX2 = 56;
    }
    offsetX = 160 - ((gNumberOfActivePlayers - 1) * (offsetX2 >> 1));
    x2 = offsetX;
    for (i = 0; i < gNumberOfActivePlayers; i++) {
        if (settings->racers[i].starting_position == 0) {
            if (gOptionBlinkTimer < 32) {
                spA0 = (gOptionBlinkTimer * 4) + 128;
            } else {
                spA0 = 0x17F - (gOptionBlinkTimer * 4);
            }
        } else {
            spA0 = 255;
        }
        texrect_draw(&sMenuCurrDisplayList, gRacerPortraits[settings->racers[i].character], x2 - 20,
                     54 - (s32) (240 * opacity), spA0, spA0, spA0, 255);
        x2 += offsetX2;
    }
    offsetX = offsetX + (s32) (320 * opacity);
    set_text_font(ASSET_FONTS_FUNFONT);
    y2 = 104;
    timesToLoop = 4;
    for (spA0 = 0; spA0 < timesToLoop; spA0++) {
        time = offsetX;
        x2 = offsetX;
        set_text_colour(0, 0, 0, 255, 255);
        draw_text(&sMenuCurrDisplayList, time - 32, y2 + offsetY + 4, gRacePlacementsArray[spA0], ALIGN_MIDDLE_CENTER);
        set_text_colour(255, 255, 192, 96, 255);
        draw_text(&sMenuCurrDisplayList, time - 34, y2 + offsetY + 2, gRacePlacementsArray[spA0], ALIGN_MIDDLE_CENTER);
        rendermode_reset(&sMenuCurrDisplayList);
        cam_set_sprite_anim_mode(SPRITE_ANIM_FRAME_INDEX);
        sprite_opaque(0);
        sMenuGuiColourR = 255;
        sMenuGuiColourG = 255 - 64 * spA0;
        sMenuGuiColourB = 255;
        sMenuGuiColourBlendFactor = 255;
        for (i = 0; i < gNumberOfActivePlayers; i++, x2 += offsetX2) {
            time = settings->racers[i].placements[spA0];
            if (time > 999) {
                time = 999;
            }
            hundredths = time / 100;
            time -= (hundredths * 100);
            tens = time / 10;
            time -= tens * 10;
            gMenuImages[0].trans.y_position = ((240 / 2) - y2);
            if (hundredths > 0) {
                gMenuImages[0].trans.x_position = (x2 - 172);
                gMenuImages[0].spriteOffset = hundredths;
                menu_element_render(0);
                gMenuImages[0].trans.x_position += 12.0f;
                gMenuImages[0].spriteOffset = tens;
                menu_element_render(0);
                gMenuImages[0].trans.x_position += 12.0f;
            } else if (tens > 0) {
                gMenuImages[0].trans.x_position = (x2 - 166);
                gMenuImages[0].spriteOffset = tens;
                menu_element_render(0);
                gMenuImages[0].trans.x_position += 12.0f;
            } else {
                gMenuImages[0].trans.x_position = (x2 - 160);
            }
            gMenuImages[0].spriteOffset = time;
            menu_element_render(0);
        }
        y2 += 17;
        cam_set_sprite_anim_mode(SPRITE_ANIM_NORMALIZED);
        sprite_opaque(1);
        sMenuGuiColourG = 255;
        sMenuGuiColourBlendFactor = 0;
    }
    if (gMenuStage >= RESULTS_OPTIONS) {
        y2 = gResultOptionCount * 8;
        clear_dialogue_box_open_flag(7);
        dialogue_clear(7);
        set_current_dialogue_box_coords(7, (320 / 2) - 80, (offsetY - y2) + 196, (320 / 2) + 80,
                                        y2 + offsetY + (240 - 36));
        set_current_dialogue_background_colour(7, 64, 64, 255, 0);
        set_dialogue_font(7, 0);
        set_current_text_background_colour(7, 0, 0, 0, 0);
        spA0 = gOptionBlinkTimer * 8;
        if (spA0 > 255) {
            spA0 = 511 - spA0;
        }
        if (gMenuSubOption != 0) {
            y2 -= 24;
            render_dialogue_text(7, -0x8000, y2 + 8, gMenuText[ASSET_MENU_TEXT_QUITGAMETITLE], 1,
                                 ALIGN_MIDDLE_CENTER);
            if (gMenuSubOption == 1) {
                set_current_text_colour(7, 255, 255, 255, spA0, 255);
            } else {
                set_current_text_colour(7, 255, 255, 255, 0, 255);
            }
            render_dialogue_text(7, -0x8000, y2 + 0x1A, gMenuText[ASSET_MENU_TEXT_OK], 1, ALIGN_MIDDLE_CENTER);
            if (gMenuSubOption == 2) {
                set_current_text_colour(7, 255, 255, 255, spA0, 255);
            } else {
                set_current_text_colour(7, 255, 255, 255, 0, 255);
            }
            render_dialogue_text(7, -0x8000, y2 + 0x2A, gMenuText[ASSET_MENU_TEXT_CANCEL], 1, ALIGN_MIDDLE_CENTER);
        } else {
            for (i = 0, y2 = 12; i < gResultOptionCount;) {
                if (i == gMenuOption) {
                    set_current_text_colour(7, 255, 255, 255, spA0, 255);
                } else {
                    set_current_text_colour(7, 255, 255, 255, 0, 255);
                }
                render_dialogue_text(7, 80, y2, gResultOptionText[i], 1, ALIGN_MIDDLE_CENTER);
                i++;
                y2 += 16;
            }
        }
        open_dialogue_box(7);
    }
}
s32 menu_results_loop(s32 updateRate) {
    s32 playBackSound;
    s32 playSelectSound;
    s32 playPickSound;
    s32 prevOption;
    playBackSound = 0;
    playSelectSound = 0;
    playPickSound = 0;
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    menu_input();
    if (gMenuStage <= RESULTS_SCORE) {
        gOpacityDecayTimer += updateRate;
        if (gOpacityDecayTimer >= 60) {
            gMenuStage = RESULTS_OPTIONS;
        } else if (gMenuStage < 0 && gOpacityDecayTimer > 20) {
            gMenuStage = RESULTS_SCORE;
            sound_play(SOUND_WHOOSH1, 0);
        }
    }
    if (gMenuDelay < 20) {
        if (gMenuStage <= RESULTS_SCORE) {
            if (gOpacityDecayTimer >= 20) {
                results_render(updateRate, 1.0f - ((f32) (gOpacityDecayTimer - 20) / 40.0f));
            }
        } else {
            results_render(updateRate, 0.0f);
        }
    }
    if (gMenuDelay == 0) {
        if (gMenuStage == RESULTS_SCORE) {
            if (gMenuButtons[4] & (0x8000 | 0x1000)) {
                gMenuStage = RESULTS_OPTIONS;
            }
        } else if (gMenuSubOption != 0) {
            if (gMenuButtons[4] & (0x8000 | 0x1000)) {
                if (gMenuSubOption == 1) {
                    playSelectSound = 1;
                    music_fade(-128);
                    transition_begin(&sMenuTransitionFadeIn);
                    gMenuDelay = 1;
                } else {
                    playBackSound = 1;
                    gMenuSubOption = 0;
                }
            } else if (gMenuButtons[4] & 0x4000) {
                playBackSound = 1;
                gMenuSubOption = 0;
            } else {
                prevOption = gMenuSubOption;
                if (gMenuStickY[4] > 0 && gMenuSubOption == 2) {
                    gMenuSubOption = 1;
                }
                if (gMenuStickY[4] < 0 && gMenuSubOption == 1) {
                    gMenuSubOption = 2;
                }
                if (prevOption != gMenuSubOption) {
                    playPickSound = 1;
                }
            }
        } else if (gMenuButtons[4] & (0x8000 | 0x1000)) {
            playSelectSound = 1;
            if (gResultOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_QUIT]) {
                gMenuSubOption = 2;
            } else {
                gMenuDelay = 1;
                transition_begin(&sMenuTransitionFadeIn);
                music_fade(-128);
            }
        } else {
            prevOption = gMenuOption;
            if (gMenuStickY[4] < 0 && gMenuOption < (gResultOptionCount - 1)) {
                gMenuOption++;
            }
            if (gMenuStickY[4] > 0 && gMenuOption > 0) {
                gMenuOption--;
            }
            if (prevOption != gMenuOption) {
                playPickSound = 1;
            }
        }
        if (playBackSound) {
            sound_play(SOUND_MENU_BACK3, 0);
        } else if (playSelectSound) {
            sound_play(SOUND_SELECT2, 0);
        } else if (playPickSound) {
            sound_play(SOUND_MENU_PICK2, 0);
        }
    } else {
        gMenuDelay += updateRate;
        if (gMenuDelay > 30) {
            results_free();
            dialogue_close(7);
            dialogue_clear(7);
            if (gResultOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_TRYAGAIN]) {
                return (MENU_RESULT_FLAGS_100 | MENU_RESULT_FLAGS_2);
            }
            if (gResultOptionText[gMenuOption] == gMenuText[ASSET_MENU_TEXT_SELECTTRACK]) {
                load_level_for_menu(SPECIAL_MAP_ID_NO_LEVEL, -1, 0);
                menu_init(MENU_TRACK_SELECT);
                return MENU_RESULT_CONTINUE;
            }
            return (MENU_RESULT_FLAGS_100 | MENU_RESULT_FLAGS_4);
        }
    }
    gIgnorePlayerInputTime = 0;
    return MENU_RESULT_CONTINUE;
}
void results_free(void) {
    menu_assetgroup_free(gRaceResultsObjectIndices);
    unload_font(ASSET_FONTS_BIGFONT);
}
void filename_decompress(u32 compressedFilename, char *output, s32 length) {
    s32 index;
    output[length] = '\0';
    for (index = length - 1; index >= 0;) {
        index--;
        output[index + 1] = gFileNameValidChars[compressedFilename & (sizeof(gFileNameValidChars) - 1)];
        compressedFilename /= sizeof(gFileNameValidChars);
    }
}
s32 filename_compress(char *filename, s32 length) {
    s32 i;
    u32 output;
    u8 processingChars;
    u8 currentChar;
    s32 charIndex;
    output = 0;
    processingChars = 1;
    for (i = 0; i < length; i++) {
        if (filename[i] == '\0') {
            processingChars = 0;
        }
        if (!processingChars) {
            currentChar = ' ';
            charIndex = 0;
        } else {
            currentChar = filename[i];
            charIndex = 0;
        }
        while (currentChar != gFileNameValidChars[charIndex]) {
            charIndex++;
            if (charIndex >= (s32) (sizeof(gFileNameValidChars) - 1)) {
                break;
            }
        }
        output *= sizeof(gFileNameValidChars);
        output |= charIndex & (sizeof(gFileNameValidChars) - 1);
    }
    return output;
}
void filename_trim(char *input, char *output) {
    s32 some_ptr;
    u32 zxChar;
    char *ptr_to_input;
    char new_var;
    s32 another_ptr;
    char *one_more_ptr;
    some_ptr = 0;
    if (*input != 0) {
        new_var = input[some_ptr];
        ptr_to_input = input;
        zxChar = new_var;
        do {
            another_ptr = some_ptr;
            if ((zxChar & 0xFFFFFFFF) == ' ') {
                zxChar = ptr_to_input[1];
                some_ptr++;
                ptr_to_input++;
                while ((zxChar & 0xFFFFFFFF) == ' ') {
                    some_ptr++;
                    zxChar = *(++ptr_to_input);
                }
                if ((zxChar != 0) && (another_ptr < some_ptr)) {
                    one_more_ptr = another_ptr + input;
                    do {
                        *(output++) = *(one_more_ptr++);
                    } while (++another_ptr < some_ptr);
                    zxChar = *ptr_to_input;
                }
            } else {
                *output = zxChar;
                zxChar = ptr_to_input[1];
                output++;
                some_ptr++;
                ptr_to_input++;
            }
        } while (zxChar != 0);
    }
    *output = '\0';
}
void filename_init(s32 titleY, s32 x, s32 y, s32 font, s32 *targetX, char *fileName, s32 fileNameLength) {
    gEnterInitalsY = titleY;
    gFilenameX = x;
    gFilenameY = y;
    gFilenameFont = font;
    gNameEntryTargetX = targetX;
    gNameEntryString = fileName;
    gNameEntryAllowedLength = fileNameLength;
    gNameEntryLength = 0;
    gNameEntryOffsetX = *gNameEntryTargetX;
    gNameSelectionDone = 0;
    gNameEntryStickX = 0;
    gNameEntryStickHeld = 0;
    load_font(ASSET_FONTS_BIGFONT);
}
void filename_render( s32 updateRate) {
    s32 xIncrement;
    s32 charIndexIncrement;
    s32 xStart;
    s32 charIndex;
    s32 x;
    s32 i;
    s32 startCharacterIndex;
    s32 y;
    char *trimmedTextPtr;
    char trimmedTextBuffer[4];
    startCharacterIndex = gNameEntryOffsetX;
    xStart = (320 / 2) - (s32) ((gNameEntryOffsetX - (f32) startCharacterIndex) * 40);
    set_text_background_colour(0, 0, 0, 0);
    set_text_font(ASSET_FONTS_FUNFONT);
    set_text_colour(0, 0, 0, 255, 128);
    draw_text(&sMenuCurrDisplayList, (320 / 2) + 2, gEnterInitalsY - 22,
              gMenuText[ASSET_MENU_TEXT_ENTERINITIALS], ALIGN_MIDDLE_CENTER);
    set_text_colour(255, 128, 255, 96, 255);
    draw_text(&sMenuCurrDisplayList, (320 / 2), gEnterInitalsY - 24, gMenuText[ASSET_MENU_TEXT_ENTERINITIALS],
              ALIGN_MIDDLE_CENTER);
    y = gEnterInitalsY;
    i = 0;
    while (i < 2) {
        x = xStart;
        charIndex = startCharacterIndex;
        if (i != 0) {
            x = xStart - 40;
            charIndex = startCharacterIndex - 1;
            xIncrement = -40;
            charIndexIncrement = -1;
        } else {
            xIncrement = 40;
            charIndexIncrement = 1;
        }
        while (x > -16 && x < 320 + 16) {
            if (charIndex < 0) {
                charIndex = 30;
            }
            if (charIndex > 30) {
                charIndex = 0;
            }
            if (charIndex == *gNameEntryTargetX) {
                set_text_colour(255, 255, 255, 0, 255);
            } else {
                set_text_colour(0, 0, 0, 128, 255);
            }
            if (charIndex < 28) {
                set_text_font(ASSET_FONTS_BIGFONT);
                gCurFilenameCharBeingDrawn = gFileNameValidChars[charIndex];
                draw_text(&sMenuCurrDisplayList, x, y, &gCurFilenameCharBeingDrawn, ALIGN_MIDDLE_CENTER);
            } else {
                set_text_font(ASSET_FONTS_FUNFONT);
                if (charIndex == 28) {
                    draw_text(&sMenuCurrDisplayList, x, y, "SP", ALIGN_MIDDLE_CENTER);
                } else if (charIndex == 29) {
                    draw_text(&sMenuCurrDisplayList, x, y, "DEL", ALIGN_MIDDLE_CENTER);
                } else {
                    draw_text(&sMenuCurrDisplayList, x, y, "OK", ALIGN_MIDDLE_CENTER);
                }
            }
            x += xIncrement;
            charIndex += charIndexIncrement;
        }
        i++;
    }
    trimmedTextPtr = trimmedTextBuffer;
    filename_trim(gNameEntryString, trimmedTextPtr);
    if (trimmedTextPtr != 0) {
        set_text_font(gFilenameFont);
        set_text_colour(0, 0, 0, 255, 128);
        draw_text(&sMenuCurrDisplayList, gFilenameX + 1, gFilenameY + 3, trimmedTextBuffer, ALIGN_MIDDLE_CENTER);
        set_text_colour(255, 255, 255, 0, 255);
        draw_text(&sMenuCurrDisplayList, gFilenameX, gFilenameY, trimmedTextBuffer, ALIGN_MIDDLE_CENTER);
    }
}
s32 filename_enter(s32 updateRate) {
    s32 prevOption;
    f32 targetXF;
    u32 buttonsPressed;
    f32 dist1;
    f32 dist2;
    f32 offsetVel;
    s32 *targetX;
    s32 i;
    s32 joytickXAxis;
    buttonsPressed = input_pressed(PLAYER_ONE);
    joytickXAxis = input_clamp_stick_x(PLAYER_ONE);
    if (joytickXAxis > -35 && (joytickXAxis < 35)) {
        joytickXAxis = 0;
    }
    if (joytickXAxis < 0) {
        if (gNameEntryStickX > -1) {
            gNameEntryStickHeld = 0;
            gNameEntryStickX = -1;
        }
        gNameEntryStickHeld += updateRate;
        if (updateRate != gNameEntryStickHeld) {
            if (gNameEntryStickHeld < 28) {
                joytickXAxis = 0;
            } else {
                gNameEntryStickHeld -= 6;
            }
        }
    } else if (joytickXAxis > 0) {
        if (gNameEntryStickX < 1) {
            gNameEntryStickHeld = 0;
            gNameEntryStickX = 1;
        }
        gNameEntryStickHeld += updateRate;
        if (updateRate != gNameEntryStickHeld) {
            if (gNameEntryStickHeld < 28) {
                joytickXAxis = 0;
            } else {
                gNameEntryStickHeld -= 6;
            }
        }
    } else {
        gNameEntryStickHeld = 0;
        gNameEntryStickX = 0;
    }
    targetX = gNameEntryTargetX;
    targetXF = *targetX;
    for (i = 0; i < updateRate; i++) {
        if (gNameEntryOffsetX <= targetXF) {
            dist1 = targetXF - gNameEntryOffsetX;
            dist2 = targetXF - (gNameEntryOffsetX + 31.0f);
        } else {
            dist1 = (targetXF + 31.0f) - gNameEntryOffsetX;
            dist2 = targetXF - gNameEntryOffsetX;
        }
        if ((dist1 * dist1) < (dist2 * dist2)) {
            offsetVel = dist1;
        } else {
            offsetVel = dist2;
        }
        gNameEntryOffsetX += offsetVel * 0.1f;
        if (gNameEntryOffsetX >= 31.0f) {
            do {
                gNameEntryOffsetX -= 31.0f;
            } while (gNameEntryOffsetX >= 31.0f);
        }
        if (gNameEntryOffsetX < 0.0f) {
            do {
                gNameEntryOffsetX += 31.0f;
            } while (gNameEntryOffsetX < 0.0f);
        }
    }
    if (gNameEntryLength < gNameEntryAllowedLength) {
        if (buttonsPressed & (0x8000 | 0x1000)) {
            if (*targetX < 29) {
                gNameEntryString[gNameEntryLength] = gFileNameValidChars[*targetX];
                gNameEntryLength++;
                gNameEntryString[gNameEntryLength] = '\0';
                sound_play(SOUND_SELECT2, 0);
                if (gNameEntryLength >= gNameEntryAllowedLength) {
                    *gNameEntryTargetX = 30;
                }
            } else if (*targetX == 29) {
                if (gNameEntryLength > 0) {
                    gNameEntryLength--;
                    gNameEntryString[gNameEntryLength] = '\0';
                }
                sound_play(SOUND_MENU_BACK3, 0);
            } else {
                if (gNameEntryLength != 0 || gNameEntryString[0] == '\0') {
                    for (i = gNameEntryLength; i < gNameEntryAllowedLength; i++) {
                        gNameEntryString[i] = 32;
                    }
                }
                gNameEntryString[gNameEntryAllowedLength] = '\0';
                sound_play(SOUND_SELECT2, 0);
                gNameSelectionDone = 1;
            }
        } else if (buttonsPressed & 0x4000) {
            if (gNameEntryLength > 0) {
                gNameEntryLength--;
            }
            gNameEntryString[gNameEntryLength] = '\0';
            sound_play(SOUND_MENU_BACK3, 0);
        } else {
            prevOption = *targetX;
            if (joytickXAxis < 0) {
                prevOption--;
            }
            if (joytickXAxis > 0) {
                prevOption++;
            }
            if (prevOption < 0) {
                prevOption = 30;
            }
            if (prevOption > 30) {
                prevOption = 0;
            }
            if (prevOption != *targetX) {
                sound_play(SOUND_MENU_PICK2, 0);
                *gNameEntryTargetX = prevOption;
            }
        }
    } else if (buttonsPressed & (0x8000 | 0x1000)) {
        sound_play(SOUND_SELECT2, 0);
        gNameSelectionDone = 1;
    } else if (buttonsPressed & 0x4000) {
        gNameEntryLength--;
        gNameEntryString[gNameEntryLength] = '\0';
        sound_play(SOUND_MENU_BACK3, 0);
    }
    filename_render(updateRate);
    return gNameSelectionDone;
}
void menu_unload_bigfont(void) {
    unload_font(ASSET_FONTS_BIGFONT);
}
void trophyround_adventure(void) {
    Settings *settings = get_settings();
    gTrophyRaceWorldId = settings->worldId;
    gTrophyRaceRound = 0;
    settings->unk4C->courseID = settings->courseId;
    settings->unk4C->entranceID = 0;
    settings->unk4C->unk1 = 0;
    gInAdvModeTrophyRace = 1;
    set_time_trial_enabled(0);
}
void menu_trophy_race_round_init(void) {
    s32 i;
    s32 index;
    Settings *settings;
    s8 *levelIds;
    settings = get_settings();
    levelIds = (s8 *) get_misc_asset(ASSET_MISC_TRACKS_MENU_IDS);
    if (gTrophyRaceRound == 0) {
        for (index = 0; index < 8; index++) {
            settings->racers[index].trophy_points = 0;
        }
    }
    do {
        index = levelIds[((gTrophyRaceWorldId - 1) * 6) + gTrophyRaceRound];
        if (index != -1) {
            continue;
        }
        index = (index + 1) & 3;
    } while (index == -1);
    for (i = 0; i < gNumberOfActivePlayers; i++) {
        gPlayerSelectVehicle[i] = leveltable_vehicle_default(index);
    }
    set_level_default_vehicle(leveltable_vehicle_default(index));
    load_level_for_menu(index, -1, 1);
    gMenuDelay = 0;
    gTrackNameVoiceDelay = 10;
    load_font(ASSET_FONTS_BIGFONT);
    music_voicelimit_set(24);
    music_play(SEQUENCE_MAIN_MENU);
    music_fade(256);
}
void trophyround_render( s32 updateRate) {
    s32 yPos;
    char *worldName;
    char *levelName;
    s8 *levelIds;
    levelIds = (s8 *) get_misc_asset(ASSET_MISC_TRACKS_MENU_IDS);
    if (osTvType == 0) {
        yPos = 18;
    } else {
        yPos = 0;
    }
    worldName = level_name(level_world_id(gTrophyRaceWorldId));
    levelName = level_name(levelIds[((gTrophyRaceWorldId - 1) * 6) + gTrophyRaceRound]);
    set_text_background_colour(0, 0, 0, 0);
    set_text_font(ASSET_FONTS_BIGFONT);
    set_text_colour(0, 0, 0, 255, 128);
    draw_text(&sMenuCurrDisplayList, (320 / 2) + 1, 35, (char *) worldName, ALIGN_MIDDLE_CENTER);
    draw_text(&sMenuCurrDisplayList, (320 / 2) + 1, 67, gMenuText[ASSET_MENU_TEXT_TROPHYRACE],
              ALIGN_MIDDLE_CENTER);
    set_text_colour(255, 255, 255, 0, 255);
    draw_text(&sMenuCurrDisplayList, (320 / 2), 32, (char *) worldName, ALIGN_MIDDLE_CENTER);
    draw_text(&sMenuCurrDisplayList, (320 / 2), 64, gMenuText[ASSET_MENU_TEXT_TROPHYRACE],
              ALIGN_MIDDLE_CENTER);
    draw_text(&sMenuCurrDisplayList, (320 / 2), yPos + 176,
              gMenuText[ASSET_MENU_TEXT_ROUNDONE + gTrophyRaceRound],
              ALIGN_MIDDLE_CENTER);
    draw_text(&sMenuCurrDisplayList, (320 / 2), yPos + 208, (char *) levelName, ALIGN_MIDDLE_CENTER);
}
s32 menu_trophy_race_round_loop(s32 updateRate) {
    s8 *trackMenuIds;
    s16 ttVoiceLine;
    s32 temp;
    trackMenuIds = (s8 *) get_misc_asset(ASSET_MISC_TRACKS_MENU_IDS);
    if (gTrackNameVoiceDelay != 0) {
        gTrackNameVoiceDelay -= updateRate;
        if (gTrackNameVoiceDelay <= 0) {
            temp = trackMenuIds[(((gTrophyRaceWorldId - 1) * 6) + gTrophyRaceRound)];
            ttVoiceLine = gTTVoiceLines[temp];
            if (ttVoiceLine != -1) {
                sound_play(ttVoiceLine, 0);
            }
            gTrackNameVoiceDelay = 0;
        }
    }
    if (gMenuDelay != 0) {
        gMenuDelay += updateRate;
    }
    if (gMenuDelay < 22) {
        trophyround_render(updateRate);
    }
    if ((gIgnorePlayerInputTime == 0) && (gMenuDelay == 0)) {
        menu_input();
        if ((gMenuButtons[4] & (0x8000 | 0x1000)) != 0) {
            transition_begin(&sMenuTransitionFadeIn);
            gMenuDelay = 1;
            music_fade(-128);
        }
    }
    if (gMenuDelay > 30) {
        trophyround_free();
        gTrackIdToLoad = trackMenuIds[(((gTrophyRaceWorldId - 1) * 6) + gTrophyRaceRound)];
        gTrackSpecifiedWithTrackIdToLoad = 1;
        return gNumberOfActivePlayers;
    }
    gIgnorePlayerInputTime = 0;
    return MENU_RESULT_CONTINUE;
}
void trophyround_free(void) {
    unload_font(ASSET_FONTS_BIGFONT);
}
void func_80098774(s32 isRankings) {
    Settings *settings;
    s16 **iconPositions;
    s16 *yPositions;
    s16 *xPositions;
    s32 yOffset;
    s32 menuElemIndex;
    s32 racerIndex;
    s32 temp;
    s32 greenAmount;
    char *titleText;
    settings = get_settings();
    titleText = (isRankings) ? gMenuText[ASSET_MENU_TEXT_RANKINGS] : gMenuText[ASSET_MENU_TEXT_RACEORDER];
    gTrophyRankingsTitle[0].t.asciiText = titleText;
    gTrophyRankingsTitle[1].t.asciiText = titleText;
    racerIndex = (gRankingPlayerCount - 1);
    racerIndex <<= 1;
    yOffset = 240;
    if (osTvType == 0) {
        racerIndex += 16;
        yOffset = 264;
    }
    iconPositions = gTrophyRankingsIconPositions;
    xPositions = gTrophyRankingsIconPositions[racerIndex++];
    yPositions = iconPositions[racerIndex];
    menuElemIndex = 2;
    if (xPositions != 0 && yPositions != 0) {
        for (racerIndex = 0; racerIndex < gRankingPlayerCount; racerIndex++) {
            for (temp = 0; temp < 3; temp++) {
                gTrophyRankingsTitle[menuElemIndex + temp].left = *xPositions;
                gTrophyRankingsTitle[menuElemIndex + temp].center = *xPositions;
                gTrophyRankingsTitle[menuElemIndex + temp].right = *xPositions;
                xPositions++;
                if ((gRankingPlayerCount >= 5) && (racerIndex >= (gRankingPlayerCount >> 1))) {
                    gTrophyRankingsTitle[menuElemIndex + temp].top = *yPositions - yOffset;
                    gTrophyRankingsTitle[menuElemIndex + temp].middle = *yPositions;
                    gTrophyRankingsTitle[menuElemIndex + temp].bottom = *yPositions + yOffset;
                    yPositions++;
                } else {
                    gTrophyRankingsTitle[menuElemIndex + temp].top = *yPositions + yOffset;
                    gTrophyRankingsTitle[menuElemIndex + temp].middle = *yPositions;
                    gTrophyRankingsTitle[menuElemIndex + temp].bottom = *yPositions - yOffset;
                    yPositions++;
                }
            }
            temp = gRankingPlayerCount & 3;
            if (temp) {
                temp = racerIndex;
                if (racerIndex >= 3) {
                    temp = racerIndex - 3;
                }
            } else {
                temp = racerIndex & 3;
            }
            greenAmount = 255 - (temp << 6);
            gTrophyRankingsTitle[menuElemIndex + 2].filterGreen = greenAmount;
            if (isRankings) {
                gTrophyRankingsTitle[menuElemIndex].t.drawTexture =
                    gRacerPortraits[settings->racers[gRankingsPlayerIDs[racerIndex]].character];
                gTrophyRankingsTitle[menuElemIndex + 2].t.element = &settings->racers[gRankingsPlayerIDs[racerIndex]];
            } else {
                gTrophyRankingsTitle[menuElemIndex].t.drawTexture =
                    gRacerPortraits[settings->racers[gResultsPlayerIDs[racerIndex]].character];
                gTrophyRankingsTitle[menuElemIndex + 2].t.number = &gTrophyRacePointsArray[racerIndex];
            }
            menuElemIndex += 3;
        }
    }
    gTrophyRankingsTitle[menuElemIndex].t.asciiText = 0;
}
void menu_trophy_race_rankings_init(void) {
    s32 i;
    s32 j;
    s32 ranking[8];
    s32 tempForSwap;
    Settings *settings;
    s8 *trackMenuIds;
    settings = get_settings();
    trackMenuIds = (s8 *) get_misc_asset(ASSET_MISC_TRACKS_MENU_IDS);
    gMenuStage = RANKINGS_ENTER;
    gMenuDelay = 0;
    gOptionBlinkTimer = 0;
    gOpacityDecayTimer = 0;
    reset_controller_sticks();
    menu_assetgroup_load(gTrophyRankingsObjectIndices);
    menu_imagegroup_load(gTrophyRaceImageIndices);
    gPrevTrophyRaceRound = gTrophyRaceRound;
    do {
        if (++gTrophyRaceRound >= 4) {
            break;
        }
    } while (trackMenuIds[((gTrophyRaceWorldId - 1) * 6) + gTrophyRaceRound] == -1);
    if (gTrophyRaceRound < 4) {
        gResultOptionText[0] = gMenuText[ASSET_MENU_TEXT_CONTINUE];
        gResultOptionText[1] = gMenuText[ASSET_MENU_TEXT_QUITTROPHYRACE];
        gResultOptionCount = 3;
    } else {
        gResultOptionText[0] = gMenuText[ASSET_MENU_TEXT_TROPHYCEREMONY];
        gResultOptionCount = 1;
    }
    gMenuOption = 0;
    menu_racer_portraits();
    if (gNumberOfActivePlayers > 2) {
        gRankingPlayerCount = gNumberOfActivePlayers;
    } else if ((gNumberOfActivePlayers == 2) || (is_in_two_player_adventure())) {
        gRankingPlayerCount = get_multiplayer_racer_count();
    } else {
        gRankingPlayerCount = 8;
    }
    for (i = 0; i < gRankingPlayerCount; i++) {
        for (j = 0; j < gRankingPlayerCount; j++) {
            if (i == settings->racers[j].starting_position) {
                gResultsPlayerIDs[i] = j;
                if (j < gNumberOfActivePlayers) {
                    gResultsPlayers[i] = 1;
                } else {
                    gResultsPlayers[i] = 0;
                }
            }
        }
    }
    for (i = 0; i < gRankingPlayerCount; i++) {
        gRankingsPoints[i] = gTrophyRacePointsArray[settings->racers[i].starting_position];
    }
    for (i = 0; i < gRankingPlayerCount; i++) {
        gRankingsPlayerIDs[i] = i;
        ranking[i] = settings->racers[i].trophy_points + gRankingsPoints[i];
    }
    for (i = gRankingPlayerCount - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (ranking[j] < ranking[j + 1]) {
                tempForSwap = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = tempForSwap;
                tempForSwap = gRankingsPlayerIDs[j];
                gRankingsPlayerIDs[j] = gRankingsPlayerIDs[j + 1];
                gRankingsPlayerIDs[j + 1] = tempForSwap;
            }
        }
    }
    if (is_in_two_player_adventure()) {
        j = 2;
    } else {
        j = gNumberOfActivePlayers;
    }
    for (i = 0; i < gRankingPlayerCount; i++) {
        if (gRankingsPlayerIDs[i] < j) {
            gRankingsPlayers[i] = 1;
        } else {
            gRankingsPlayers[i] = 0;
        }
    }
    load_font(ASSET_FONTS_BIGFONT);
    music_voicelimit_set(24);
    music_play(SEQUENCE_MAIN_MENU);
    music_fade(256);
    func_80098774(0);
    postrace_offsets(gTrophyRankingsTitle, 0.5f, 20.0f, 0.5f, 0, 0);
}
void rankings_render_order(s32 updateRate) {
    s32 highlight;
    s32 stage;
    s32 fade;
    s32 i;
    s32 pad;
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    highlight = gOptionBlinkTimer * 8;
    if (highlight > 255) {
        highlight = 511 - highlight;
    }
    for (i = 0; i < gRankingPlayerCount; i++) {
        fade = 255;
        if (gNumberOfActivePlayers < 3 && ((gMenuStage == POSTRACE_ENTER && gResultsPlayers[i]) ||
                                           (gMenuStage != POSTRACE_ENTER && gRankingsPlayers[i]))) {
            fade = (highlight >> 1) + 128;
        }
        gTrophyRankingsRacers[i * 3].filterRed = fade;
        gTrophyRankingsRacers[i * 3].filterGreen = fade;
        gTrophyRankingsRacers[i * 3].filterBlue = fade;
    }
    stage = gMenuStage;
    if (stage == RANKINGS_ORDER || stage == RANKINGS_EXIT) {
        draw_menu_elements(1, gTrophyRankingsTitle, 1.0f);
    }
}
s32 menu_trophy_race_rankings_loop(s32 updateRate) {
    s32 i;
    s32 temp6;
    s32 buttonsPressed;
    s32 prevOption;
    s32 ret;
    s8 *params;
    s32 sp34;
    s16 playSound;
    s16 temp7;
    Settings *settings;
    s32 temp0;
    ret = MENU_RESULT_CONTINUE;
    settings = get_settings();
    if (gMenuDelay > -20 && gMenuDelay < 20) {
        rankings_render_order(updateRate);
    }
    update_controller_sticks();
    switch (gMenuStage) {
        case POSTRACE_ENTER:
            if (postrace_render(updateRate)) {
                gMenuStage = RANKINGS_SWAP;
                func_80098774(1);
                postrace_offsets(gTrophyRankingsTitle, 0.5f, 0.0f, 0.0f, 0, 0);
            }
            break;
        case RANKINGS_SWAP:
            if (postrace_render(updateRate)) {
                gMenuStage = RANKINGS_ORDER;
                draw_menu_elements(1, gTrophyRankingsTitle, 1.0f);
            }
            break;
        case RANKINGS_ORDER:
            gOpacityDecayTimer += updateRate;
            if (gOpacityDecayTimer > 10) {
                gOpacityDecayTimer -= 10;
                playSound = 0;
                for (i = 0; i < gRankingPlayerCount; i++) {
                    if (gRankingsPoints[i] > 0) {
                        gRankingsPoints[i]--;
                        playSound = 1;
                        settings->racers[i].trophy_points++;
                    }
                }
                if (playSound) {
                    sound_play(SOUND_TING_HIGH, 0);
                }
            }
            buttonsPressed = 0;
            prevOption = gMenuOption;
            for (i = 0; i < gNumberOfActivePlayers; i++) {
                buttonsPressed |= input_pressed(i);
                if (gControllersYAxisDirection[i] < 0) {
                    gMenuOption++;
                }
                if (gControllersYAxisDirection[i] > 0) {
                    gMenuOption--;
                }
            }
            if (gMenuOption < 0) {
                gMenuOption = 0;
            }
            if (gMenuOption >= gResultOptionCount) {
                gMenuOption = gResultOptionCount - 1;
            }
            if (prevOption != gMenuOption) {
                sound_play(SOUND_MENU_PICK2, 0);
            }
            if (buttonsPressed & (0x8000 | 0x1000)) {
                music_fade(-128);
                transition_begin(&sMenuTransitionFadeIn);
                gMenuStage = RANKINGS_EXIT;
                for (i = 0; i < gRankingPlayerCount; i++) {
                    settings->racers[i].trophy_points += gRankingsPoints[i];
                }
            }
            break;
        case RANKINGS_EXIT:
            gMenuDelay += updateRate;
            if (gMenuDelay > 30) {
                rankings_free();
                dialogue_close(7);
                dialogue_clear(7);
                if (gTrophyRaceRound < 4) {
                    menu_init(MENU_TROPHY_RACE_ROUND);
                } else {
                    for (temp6 = 0, i = 0; i < gRankingPlayerCount; i++) {
                        if (gRankingsPlayers[i] != 0) {
                            temp7 = settings->racers[gRankingsPlayerIDs[i]].character;
                            if (temp6 == 0) {
                                sp34 = i;
                                gRankingsPortraitIDs[temp6++] = temp7;
                                continue;
                            }
                            if (settings->racers[gRankingsPlayerIDs[i]].trophy_points ==
                                settings->racers[gRankingsPlayerIDs[sp34]].trophy_points) {
                                gRankingsPortraitIDs[temp6++] = temp7;
                            }
                        }
                    }
                    if (gNumberOfActivePlayers == 1 && !is_in_two_player_adventure()) {
                        temp6 = 0;
                    }
                    gRankingsPortraitIDs[temp6] = -1;
                    if (gIsInTracksMode == 1) {
                        if (sp34 >= 3) {
                            menu_init(MENU_TRACK_SELECT);
                        } else {
                            ret = MENU_RESULT_FLAGS_100 | MENU_RESULT_TRACKS_MODE;
                        }
                    } else {
                        ret = MENU_RESULT_RETURN_TO_GAME;
                        settings->courseId = level_world_id(settings->worldId);
                        if (gInAdvModeTrophyRace) {
                            gInAdvModeTrophyRace = 0;
                            ret = settings->courseId | MENU_RESULT_FLAGS_200;
                            if (sp34 < 3) {
                                temp0 = settings->worldId - 1;
                                temp0 <<= 1;
                                prevOption = ((3 - sp34) & 3);
                                temp6 = (settings->trophies >> temp0) & 3;
                                if (temp6 < prevOption) {
                                    settings->trophies &= ~(3 << temp0);
                                    settings->trophies |= (prevOption << temp0);
                                    safe_mark_write_save_file(get_save_file_index());
                                }
                            }
                        }
                    }
                    if (sp34 < 3) {
                        params = (s8 *) get_misc_asset(ASSET_MISC_CINEMATIC_TROPHY);
                        temp0 = ((gTrophyRaceWorldId * 3) + sp34) - 3;
                        cinematic_start(params, temp0, ret, 0, 0, gRankingsPortraitIDs);
                        ret = MENU_RESULT_CONTINUE;
                        menu_init(MENU_NEWGAME_CINEMATIC);
                    }
                    gTrophyRaceWorldId = 0;
                }
            }
            break;
    }
    gIgnorePlayerInputTime = 0;
    return ret;
}
void rankings_free(void) {
    menu_assetgroup_free(gTrophyRankingsObjectIndices);
    unload_font(ASSET_FONTS_BIGFONT);
}
s32 get_trophy_race_world_id(void) {
    return gTrophyRaceWorldId;
}
void ghostmenu_generate(void) {
    u8 *mainTrackIds;
    s32 i;
    s32 j;
    u16 validIDs[4];
    u16 swap;
    u16 swapByte;
    s32 pad;
    gGhostMenuTotal = 0;
    mainTrackIds = (u8 *) get_misc_asset(ASSET_MISC_MAIN_TRACKS_IDS);
    for (i = 0; i < 6; i++) {
        if (gGhostLevelIDsPak[i] != 0xFF) {
            for (j = 0; mainTrackIds[j] != 0xFF && mainTrackIds[j] != gGhostLevelIDsPak[i]; j++) {}
            if (mainTrackIds[j] != 0xFF) {
                gGhostWorldIDs[gGhostMenuTotal] = i;
                validIDs[gGhostMenuTotal] = (j * 8) + gGhostVehicleIDsPak[i];
                gGhostMenuTotal++;
            }
        }
    }
    for (i = gGhostMenuTotal - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (validIDs[j + 1] < validIDs[j]) {
                swap = validIDs[j];
                validIDs[j] = validIDs[j + 1];
                validIDs[j + 1] = swap;
                swapByte = gGhostWorldIDs[j];
                gGhostWorldIDs[j] = gGhostWorldIDs[j + 1];
                gGhostWorldIDs[j + 1] = swapByte;
            }
        }
    }
    for (i = 0; i < gGhostMenuTotal; i++) {
        gGhostLevelIDsMenu[i] = gGhostLevelIDsPak[gGhostWorldIDs[i]];
        gGhostCharacterIDsMenu[i] = gGhostCharacterIDsPak[gGhostWorldIDs[i]];
        gGhostVehicleIDsMenu[i] = gGhostVehicleIDsPak[gGhostWorldIDs[i]];
        gGhostChecksumIDsMenu[i] = gGhostChecksumIDsPak[gGhostWorldIDs[i]];
    }
}
s32 ghostmenu_erase(s32 id) {
    s32 temp_s0;
    s32 result;
    s32 i;
    result = CONTROLLER_PAK_GOOD;
    if (id >= 0 && id < gGhostMenuTotal) {
        sound_play(SOUND_SELECT2, 0);
        temp_s0 = gGhostWorldIDs[id];
        result = func_800753D8(gCpakGhostData, temp_s0);
        if (result == CONTROLLER_PAK_GOOD) {
            gGhostLevelIDsPak[temp_s0] = 0xFF;
            gGhostMenuTotal--;
            for (i = id; i < gGhostMenuTotal; i++) {
                gGhostWorldIDs[i] = gGhostWorldIDs[i + 1];
                gGhostLevelIDsMenu[i] = gGhostLevelIDsMenu[i + 1];
                gGhostCharacterIDsMenu[i] = gGhostCharacterIDsMenu[i + 1];
                gGhostVehicleIDsMenu[i] = gGhostVehicleIDsMenu[i + 1];
                gGhostChecksumIDsMenu[i] = gGhostChecksumIDsMenu[i + 1];
            }
            for (i = 0; i < gGhostMenuTotal; i++) {
                if (temp_s0 < gGhostWorldIDs[i]) {
                    gGhostWorldIDs[i]--;
                }
            }
        }
    }
    return result;
}
void menu_ghost_data_init(void) {
    s32 i;
    SIDeviceStatus pakStatus;
    pakStatus = func_800756D4(gCpakGhostData, gGhostLevelIDsPak, gGhostVehicleIDsPak, gGhostCharacterIDsPak,
                              gGhostChecksumIDsPak);
    if (pakStatus == CONTROLLER_PAK_GOOD) {
        ghostmenu_generate();
    }
    menu_assetgroup_load(gGhostDataObjectIndices);
    menu_imagegroup_load(gGhostDataImageIndices);
    load_font(ASSET_FONTS_BIGFONT);
    for (i = 0; i < 5; i++) {
        gDrawTexDinoDomainGhostBg[i].texture = gMenuAssets[TEXTURE_BACKGROUND_DINO_DOMAIN_TOP];
        gDrawTexDinoDomainGhostBg[i + 5].texture = gMenuAssets[TEXTURE_BACKGROUND_DINO_DOMAIN_BOTTOM];
        gDrawTexSherbetIslandGhostBg[i + ((i & 1) * 5)].texture = gMenuAssets[TEXTURE_BACKGROUND_SHERBERT_ISLAND_TOP];
        gDrawTexSherbetIslandGhostBg[i + (((i & 1) ^ 1) * 5)].texture =
            gMenuAssets[TEXTURE_BACKGROUND_SHERBERT_ISLAND_BOTTOM];
        gDrawTexSnowflakeMountainGhostBg[i].texture = gMenuAssets[TEXTURE_BACKGROUND_SNOWFLAKE_MOUNTAIN_TOP];
        gDrawTexSnowflakeMountainGhostBg[i + 5].texture = gMenuAssets[TEXTURE_BACKGROUND_SNOWFLAKE_MOUNTAIN_BOTTOM];
        gDrawTexDragonForestGhostBg[i].texture = gMenuAssets[TEXTURE_BACKGROUND_DRAGON_FOREST_TOP];
        gDrawTexDragonForestGhostBg[i + 5].texture = gMenuAssets[TEXTURE_BACKGROUND_DRAGON_FOREST_BOTTOM];
        gDrawTexFutureFunLandGhostBg[i + ((i & 1) * 5)].texture = gMenuAssets[TEXTURE_BACKGROUND_FUTURE_FUN_LAND_TOP];
        gDrawTexFutureFunLandGhostBg[i + (((i & 1) ^ 1) * 5)].texture =
            gMenuAssets[TEXTURE_BACKGROUND_FUTURE_FUN_LAND_BOTTOM];
    }
    menu_init_vehicle_textures();
    menu_racer_portraits();
    menu_init_arrow_textures();
    gOptionBlinkTimer = 0;
    gMenuStage = 0;
    gOpacityDecayTimer = 0;
    gMenuDelay = 0;
    gGhostMenuOption = 0;
    if (pakStatus == CONTROLLER_PAK_GOOD) {
        transition_begin(&sMenuTransitionFadeOut);
        return;
    }
    gMenuDelay = 30;
}
void ghostmenu_render( s32 updateRate) {
    s32 currentWorldId;
    s32 numToDraw;
    s32 scroll;
    s32 i;
    s32 y;
    s32 highlight;
    s32 x;
    s32 heightAdjust;
    DrawTexture *vehicleSelectTex;
    char *levelName;
    char textBuffer[64];
    mtx_ortho(&sMenuCurrDisplayList, &sMenuCurrHudMat);
    if (osTvType == 0) {
        heightAdjust = 12;
    } else {
        heightAdjust = 0;
    }
    scroll = gOpacityDecayTimer;
    set_text_font(FONT_LARGE);
    set_text_background_colour(0, 0, 0, 0);
    set_text_colour(0, 0, 0, 255, 128);
    draw_text(&sMenuCurrDisplayList, (320 / 2) + 1, 35, gMenuText[ASSET_MENU_TEXT_GHOSTDATA],
              ALIGN_MIDDLE_CENTER);
    set_text_colour(255, 255, 255, 0, 255);
    draw_text(&sMenuCurrDisplayList, (320 / 2), 32, gMenuText[ASSET_MENU_TEXT_GHOSTDATA], ALIGN_MIDDLE_CENTER);
    y = 56;
    if (gGhostMenuTotal <= 0) {
        set_text_colour(255, 255, 255, 0, 255);
        draw_text(&sMenuCurrDisplayList, (320 / 2), heightAdjust + (240 / 2),
                  gMenuText[ASSET_MENU_TEXT_NOGHOSTSSAVED], ALIGN_MIDDLE_CENTER);
        return;
    }
    numToDraw = 3;
    highlight = gOptionBlinkTimer * 8;
    if (highlight > 255) {
        highlight = 511 - highlight;
    }
    highlight |= ~0xFF;
    set_text_font(FONT_SMALL);
    x = 40;
    while (scroll < gGhostMenuTotal && numToDraw > 0) {
        if (gGhostDataElementPositions[0]) {}
        currentWorldId = leveltable_world(gGhostLevelIDsMenu[scroll]) - 1;
        if (currentWorldId < 0 || currentWorldId >= WORLD_FUTURE_FUN_LAND) {
            currentWorldId = 0;
        }
        levelName = level_name(gGhostLevelIDsMenu[scroll]);
        for (i = 0; levelName[i] != '\0' && i < 63; i++) {
            textBuffer[i] = levelName[i];
            if (textBuffer[i] >= 'a' && textBuffer[i] <= 'z') {
                textBuffer[i] ^= 0x20;
            }
        }
        textBuffer[i] = '\0';
        texrect_draw_scaled(&sMenuCurrDisplayList, gDrawTexWorldBgs[currentWorldId], x, y, 0.75f, 0.8125f,
                            ((u32)((255 << 24) | (255 << 16) | (255 << 8) | 255)), 0);
        func_80080E90(&sMenuCurrDisplayList, 40, y, 240, 52, 4, 4, 32, 80, 176, 128);
        if (scroll == gGhostMenuOption) {
            func_80080E90(&sMenuCurrDisplayList, 40, y, 240, 52, 4, 4, highlight, highlight, highlight, highlight);
        }
        set_text_colour(0, 0, 0, 255, 255);
        for (i = 0; i < 4; i++) {
            draw_text(&sMenuCurrDisplayList,
                      gGhostDataElementPositions[0] + 40 + D_800E1E20[(i << 1)],
                      y + gGhostDataElementPositions[1] + D_800E1E20[(i << 1) + 1], textBuffer, ALIGN_MIDDLE_CENTER);
        }
        set_text_colour(200, 228, 80, 255, 255);
        draw_text(&sMenuCurrDisplayList, gGhostDataElementPositions[0] + 40,
                  gGhostDataElementPositions[1] + y, textBuffer, ALIGN_MIDDLE_CENTER);
        texrect_draw(&sMenuCurrDisplayList, gRacerPortraits[gGhostCharacterIDsMenu[scroll]],
                     gGhostDataElementPositions[2] + 40, gGhostDataElementPositions[3] + y, 255, 255, 255, 255);
        switch (gGhostVehicleIDsMenu[scroll]) {
            case 1:
                vehicleSelectTex = gRaceSelectionHoverTex;
                break;
            case 2:
                vehicleSelectTex = gRaceSelectionPlaneTex;
                break;
            default:
                vehicleSelectTex = gRaceSelectionCarTex;
                break;
        }
        texrect_draw_scaled(&sMenuCurrDisplayList, vehicleSelectTex, (gGhostDataElementPositions[4] + 40),
                            (gGhostDataElementPositions[5] + y), 0.625f, 0.625f, ((u32)((255 << 24) | (255 << 16) | (255 << 8) | 255)), 0);
        rendermode_reset(&sMenuCurrDisplayList);
        gMenuImages[7].trans.x_position = (gGhostDataElementPositions[6] - (240 / 2));
        gMenuImages[7].trans.y_position = ((-gGhostDataElementPositions[7] - y) + heightAdjust + (240 / 2));
        gMenuImages[7].trans.scale = 0.075f;
        menu_element_render(7);
        sMenuGuiOpacity = 128;
        menu_timestamp_render(gGhostChecksumIDsMenu[scroll], gGhostDataElementPositions[8] - ((240 / 2) - 1),
                              (-gGhostDataElementPositions[9] - y) + heightAdjust + ((240 / 2) - 1), 0, 0, 0,
                              FONT_COLOURFUL);
        sMenuGuiOpacity = 255;
        menu_timestamp_render(gGhostChecksumIDsMenu[scroll], gGhostDataElementPositions[8] - ((240 / 2) + 1),
                              (-gGhostDataElementPositions[9] - y) + heightAdjust + ((240 / 2) + 1), 255, 192,
                              255, FONT_COLOURFUL);
        scroll++;
        numToDraw--;
        y += 54;
    }
    highlight &= 0xFF;
    if (gMenuStage > GHOSTMENU_CHOOSE) {
        clear_dialogue_box_open_flag(7);
        dialogue_clear(7);
        set_current_dialogue_box_coords(7, 92, 102, 228, 138);
        set_current_dialogue_background_colour(7, 0, 0, 0, 192);
        set_dialogue_font(7, 0);
        set_current_text_background_colour(7, 0, 0, 0, 0);
        if (gMenuStage == GHOSTMENU_ERASE) {
            set_current_text_colour(7, 255, 255, 255, highlight, 255);
        } else {
            set_current_text_colour(7, 255, 255, 255, 0, 255);
        }
        render_dialogue_text(7, -0x8000, 12, gMenuText[ASSET_MENU_TEXT_ERASEGHOST], 1, ALIGN_MIDDLE_CENTER);
        if (gMenuStage == GHOSTMENU_CONFIRM) {
            set_current_text_colour(7, 255, 255, 255, highlight, 255);
        } else {
            set_current_text_colour(7, 255, 255, 255, 0, 255);
        }
        render_dialogue_text(7, -0x8000, 28, gMenuText[ASSET_MENU_TEXT_CANCEL], 1, ALIGN_MIDDLE_CENTER);
        render_dialogue_box(&sMenuCurrDisplayList, 0, 0, 7);
    }
    if (gOptionBlinkTimer & 0x10) {
        if ((gOpacityDecayTimer + 3) < gGhostMenuTotal) {
            texrect_draw(&sMenuCurrDisplayList, gMenuSelectionArrowDown, (320 / 2) + 1, y + 3, 0, 0, 0, 128);
            texrect_draw(&sMenuCurrDisplayList, gMenuSelectionArrowDown, (320 / 2) - 1, y + 1, 255, 255, 255,
                         255);
        }
        if (gOpacityDecayTimer > 0) {
            texrect_draw(&sMenuCurrDisplayList, gMenuSelectionArrowUp, (320 / 2) + 1, 54, 0, 0, 0, 128);
            texrect_draw(&sMenuCurrDisplayList, gMenuSelectionArrowUp, (320 / 2) - 1, 52, 255, 255, 255, 255);
        }
        rendermode_reset(&sMenuCurrDisplayList);
    }
}
s32 menu_ghost_data_loop(s32 updateRate) {
    s32 i;
    s32 pressedButtons;
    s32 xStick;
    s32 yStick;
    s32 prevOption;
    s32 unused;
    gOptionBlinkTimer = (gOptionBlinkTimer + updateRate) & 0x3F;
    if (gMenuDelay > -20 && gMenuDelay < 20) {
        ghostmenu_render(updateRate);
    }
    pressedButtons = 0;
    if (gMenuDelay) {
        if (gMenuDelay < 0) {
            gMenuDelay -= updateRate;
        } else {
            gMenuDelay += updateRate;
        }
    }
    xStick = 0;
    yStick = 0;
    if (!gIgnorePlayerInputTime && gMenuDelay == 0) {
        for (i = 0; i < 4; i++) {
            pressedButtons |= input_pressed(i);
            xStick += gControllersXAxisDirection[i];
            yStick += gControllersYAxisDirection[i];
        }
    }
    switch (gMenuStage) {
        case GHOSTMENU_CHOOSE:
            if ((pressedButtons & (0x1000 | 0x8000)) && gGhostMenuTotal > 0) {
                gMenuStage = GHOSTMENU_CONFIRM;
                sound_play(SOUND_SELECT2, 0);
            } else if (pressedButtons & 0x4000 ||
                       (pressedButtons & (0x1000 | 0x8000) && gGhostMenuTotal == 0)) {
                gMenuDelay = 1;
                transition_begin(&sMenuTransitionFadeIn);
                sound_play(SOUND_MENU_BACK3, 0);
            } else {
                prevOption = gGhostMenuOption;
                if (yStick < 0 && gGhostMenuOption < gGhostMenuTotal - 1) {
                    gGhostMenuOption++;
                    if (gGhostMenuOption >= gOpacityDecayTimer + 3) {
                        gOpacityDecayTimer = gGhostMenuOption - 2;
                    }
                }
                if (yStick > 0 && gGhostMenuOption > 0) {
                    gGhostMenuOption--;
                    if (gGhostMenuOption < gOpacityDecayTimer) {
                        gOpacityDecayTimer = gGhostMenuOption;
                    }
                }
                if (prevOption != gGhostMenuOption) {
                    sound_play(SOUND_MENU_PICK2, 0);
                }
            }
            break;
        case GHOSTMENU_ERASE:
            if (pressedButtons & 0x4000) {
                gMenuStage = GHOSTMENU_CHOOSE;
                sound_play(SOUND_MENU_BACK3, 0);
            } else {
                if (pressedButtons & (0x1000 | 0x8000)) {
                    if (ghostmenu_erase(gGhostMenuOption) == CONTROLLER_PAK_GOOD) {
                        if (gGhostMenuOption >= gGhostMenuTotal) {
                            gGhostMenuOption = gGhostMenuTotal - 1;
                        }
                        if (gGhostMenuOption < 0) {
                            gGhostMenuOption = 0;
                        }
                        if (gGhostMenuOption < gOpacityDecayTimer) {
                            gOpacityDecayTimer = gGhostMenuOption;
                        }
                        sound_play(SOUND_SELECT2, 0);
                    } else {
                        gMenuDelay = 1;
                        transition_begin(&sMenuTransitionFadeIn);
                        sound_play(SOUND_MENU_BACK3, 0);
                    }
                    gMenuStage = GHOSTMENU_CHOOSE;
                } else if (yStick < 0) {
                    gMenuStage = GHOSTMENU_CONFIRM;
                    sound_play(SOUND_MENU_PICK2, 0);
                }
            }
            break;
        case GHOSTMENU_CONFIRM:
            if (pressedButtons & (0x1000 | 0x8000 | 0x4000)) {
                gMenuStage = GHOSTMENU_CHOOSE;
                sound_play(SOUND_MENU_BACK3, 0);
            } else if (yStick > 0) {
                gMenuStage = GHOSTMENU_ERASE;
                sound_play(SOUND_MENU_PICK2, 0);
            }
            break;
    }
    gIgnorePlayerInputTime = 0;
    if (gMenuDelay > 30) {
        ghostmenu_free();
        menu_init(MENU_SAVE_OPTIONS);
    }
    return MENU_RESULT_CONTINUE;
}
void ghostmenu_free(void) {
    menu_assetgroup_free(gGhostDataObjectIndices);
    unload_font(ASSET_FONTS_BIGFONT);
}
void cinematic_start(s8 *params, s32 arg1, s32 endFlags, s32 skipFlagsA, s32 skipFlagsB, s8 *portraits) {
    s32 phi_v1;
    phi_v1 = 0;
    while (phi_v1 < arg1) {
        phi_v1++;
        while (-1 != *params) {
            params += 3;
        }
        params++;
    }
    if (phi_v1 == 0 && (s8 *) get_misc_asset(ASSET_MISC_CINEMATIC_RACE) == params) {
        gCinematicMusicChangeOff = 1;
    } else {
        gCinematicMusicChangeOff = 0;
    }
    gCinematicParams = params;
    gCinematicEnd = endFlags;
    gCinematicSkipA = skipFlagsA;
    gCinematicSkipB = skipFlagsB;
    gCinematicPortraits = portraits;
}
void menu_cinematic_init(void) {
    if (gCinematicPortraits != 0) {
        menu_assetgroup_load(gCinematicObjectIndices);
        menu_racer_portraits();
    }
    load_level_for_menu(gCinematicParams[0], gCinematicParams[1],
                        gCinematicParams[2]);
    gMenuDelay = 0;
    gMenuStage = 0;
}
s32 menu_cinematic_loop( s32 updateRate) {
    s32 i;
    s32 buttonsPressed;
    buttonsPressed = 0;
    if (gIgnorePlayerInputTime == 0) {
        for (i = 0; i < gNumberOfActivePlayers; i++) {
            buttonsPressed |= input_pressed(i);
        }
    }
    if (func_800214C4() != 0) {
        gCinematicParams += 3;
        if (gCinematicParams[0] > -1) {
            load_level_for_menu(gCinematicParams[0], gCinematicParams[1],
                                gCinematicParams[2]);
        } else {
            if (gCinematicMusicChangeOff) {
                music_change_off();
            }
            cinematic_free();
            return gCinematicEnd;
        }
    }
    if (gCinematicSkipA && buttonsPressed & (0x8000 | 0x1000)) {
        cinematic_free();
        return gCinematicSkipA;
    }
    if (gCinematicSkipB && (buttonsPressed & 0x4000)) {
        cinematic_free();
        return gCinematicSkipB;
    }
    if (gCinematicPortraits != 0) {
        for (i = 0; gCinematicPortraits[i] != -1; i++) {
            texrect_draw(&sMenuCurrDisplayList, gRacerPortraits[gCinematicPortraits[i]], 24, 16 + (44 * i), 255, 255,
                         255, 255);
        }
    }
    gIgnorePlayerInputTime = 0;
    return MENU_RESULT_CONTINUE;
}
void cinematic_free(void) {
    if (gCinematicPortraits != 0) {
        menu_assetgroup_free(gCinematicObjectIndices);
    }
}
void menu_credits_init(void) {
    s32 cheat;
    s32 cheatIndex;
    u16 *cheatOffsets;
    Settings *settings;
    settings = get_settings();
    gMenuDelay = 0;
    gCreditsControlDataIndex = 0;
    D_80126BCC = 0;
    gMenuStage = 0;
    gOpacityDecayTimer = 40;
    gMenuCurIndex = 0;
    D_80126BD0 = 0;
    D_80126BD8 = 0;
    D_80126BE0 = 0;
    bgdraw_fillcolour(0, 0, 0);
    if (osTvType == 0) {
        viewport_menu_set(0, 0, 38, 320, 224);
        set_viewport_properties(0, 0x8000, 0x8000, 320, (240 + 44));
    } else {
        viewport_menu_set(0, 0, 40, 320, 196);
        set_viewport_properties(0, 0x8000, 0x8000, 320, 240);
    }
    copy_viewports_to_stack();
    camEnableUserView(0, 1);
    menu_assetgroup_load(gCreditsObjectIndices);
    menu_imagegroup_load(gCreditsImageIndices);
    menu_racer_portraits();
    load_font(ASSET_FONTS_BIGFONT);
    music_voicelimit_set(24);
    gCreditsControlData[130] = ((0x1000));
    if (gViewingCreditsFromCheat) {
        music_play(SEQUENCE_DARKMOON_CAVERNS);
        gCreditsArray[84] = gCreditsLastMessageArray[2];
        gCreditsArray[85] = gCreditsLastMessageArray[3];
        gCreditsArray[86] = gCreditsLastMessageArray[4];
        gViewingCreditsFromCheat = 0;
    } else {
        if (settings->bosses & 0x20) {
            music_play(SEQUENCE_CRESCENT_ISLAND);
            gCreditsArray[84] = gCreditsLastMessageArray[1];
            gCreditsControlData[130] = ((0x6000) | ((s16) (8.334 * 60.0)));
            D_80126BCC = 9;
        } else {
            music_play(SEQUENCE_DARKMOON_CAVERNS);
            gCreditsArray[84] = gCreditsLastMessageArray[0];
        }
        cheat = gCheatsInCreditsArray[rand_range(0, sizeof(gCheatsInCreditsArray) / sizeof(s32) - 1)];
        cheatIndex = -1;
        while (cheat != 0) {
            cheat >>= 1;
            cheatIndex++;
        }
        cheatOffsets = *gCheatsAssetData + 1;
        gCreditsArray[85] =
            (char *) (*gCheatsAssetData) + (cheatOffsets)[(cheatIndex * 3) + 1];
        gCreditsArray[86] = (char *) (*gCheatsAssetData) + (cheatOffsets)[(cheatIndex * 3)];
    }
    music_change_off();
    enable_new_screen_transitions();
    set_gIntDisFlag(1);
}
void credits_fade(s32 x1, s32 y1, s32 x2, s32 y2, s32 a) {
    if (a > 255) {
        a = 255;
    }
    if (a < 0) {
        a = 0;
    }
    { Gfx *_g = (Gfx *)(sMenuCurrDisplayList++); _g->words.w0 = (((unsigned int) (((unsigned int)((6)) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((0x00)) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)((0)) & ((0x01 << (16)) - 1)) << (0)))); _g->words.w1 = (unsigned int)(dCreditsFade); };
    { Gfx *_g = (Gfx *)(sMenuCurrDisplayList++); _g->words.w0 = (((unsigned int) (((unsigned int)(0xfa) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (0)))); _g->words.w1 = (((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(a) & ((0x01 << (8)) - 1)) << (0)))); };
    { Gfx *_g = (Gfx *)(sMenuCurrDisplayList++); _g->words.w0 = ((unsigned int) (((unsigned int)(0xfc) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((((unsigned int) (((unsigned int)((31)) & ((0x01 << (4)) - 1)) << (20))) | ((unsigned int) (((unsigned int)((31)) & ((0x01 << (5)) - 1)) << (15))) | ((unsigned int) (((unsigned int)((7)) & ((0x01 << (3)) - 1)) << (12))) | ((unsigned int) (((unsigned int)((7)) & ((0x01 << (3)) - 1)) << (9)))) | (((unsigned int) (((unsigned int)((31)) & ((0x01 << (4)) - 1)) << (5))) | ((unsigned int) (((unsigned int)((31)) & ((0x01 << (5)) - 1)) << (0))))) & ((0x01 << (24)) - 1)) << (0))); _g->words.w1 = (unsigned int)((((unsigned int) (((unsigned int)((31)) & ((0x01 << (4)) - 1)) << (28))) | ((unsigned int) (((unsigned int)((3)) & ((0x01 << (3)) - 1)) << (15))) | ((unsigned int) (((unsigned int)((7)) & ((0x01 << (3)) - 1)) << (12))) | ((unsigned int) (((unsigned int)((3)) & ((0x01 << (3)) - 1)) << (9)))) | (((unsigned int) (((unsigned int)((31)) & ((0x01 << (4)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((7)) & ((0x01 << (3)) - 1)) << (21))) | ((unsigned int) (((unsigned int)((7)) & ((0x01 << (3)) - 1)) << (18))) | ((unsigned int) (((unsigned int)((3)) & ((0x01 << (3)) - 1)) << (6))) | ((unsigned int) (((unsigned int)((7)) & ((0x01 << (3)) - 1)) << (3))) | ((unsigned int) (((unsigned int)((3)) & ((0x01 << (3)) - 1)) << (0))))); };
    { Gfx *_g = (Gfx *)(sMenuCurrDisplayList++); _g->words.w0 = (((unsigned int) (((unsigned int)(0xf6) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((x1 + x2)) & ((0x01 << (10)) - 1)) << (14))) | ((unsigned int) (((unsigned int)((y1 + y2)) & ((0x01 << (10)) - 1)) << (2)))); _g->words.w1 = (((unsigned int) (((unsigned int)((x1)) & ((0x01 << (10)) - 1)) << (14))) | ((unsigned int) (((unsigned int)((y1)) & ((0x01 << (10)) - 1)) << (2))));};
    { Gfx *_g = (Gfx *)(sMenuCurrDisplayList++); _g->words.w0 = ((unsigned int) (((unsigned int)(0xe7) & ((0x01 << (8)) - 1)) << (24))); _g->words.w1 = 0; };
    { Gfx *_g = (Gfx *)(sMenuCurrDisplayList++); _g->words.w0 = (((unsigned int) (((unsigned int)(0xfa) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (0)))); _g->words.w1 = (((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (0)))); };
    rendermode_reset(&sMenuCurrDisplayList);
}
s32 menu_credits_loop(s32 updateRate) {
    s32 pad_sp7C[3];
    s32 nextIndex;
    s32 pad_sp70[2];
    s32 breakLoop;
    s32 isCreditsEnd;
    s32 pad_sp64;
    CreditsBackgroundLevelData *creditsBackgroundLevelData;
    s8 *mainTrackIds;
    s8 isShowingBestRaceTimes;
    CreditsBackgroundLevelData *tempBackgroundLevelData;
    s32 i;
    s32 textPos;
    s32 buttonsPressedAllPlayers;
    s32 controlDataLength;
    s32 creditsMenuElementIndex;
    s32 var_s5;
    s32 var_s4;
    s32 textLineHeight;
    s32 halvedFbSize;
    isCreditsEnd = 0;
    mainTrackIds = (s8 *) get_misc_asset(ASSET_MISC_MAIN_TRACKS_IDS);
    creditsBackgroundLevelData = (CreditsBackgroundLevelData *) get_misc_asset(ASSET_MISC_69);
    bgload_tick();
    if (gMenuDelay == 0) {
        disable_new_screen_transitions();
        transition_begin(0);
        enable_new_screen_transitions();
    }
    if (osTvType == 0) {
        credits_fade(0, 38, 320, 186, gOpacityDecayTimer * 8);
    } else {
        credits_fade(0, 40, 320, 156, gOpacityDecayTimer * 8);
    }
    if (gOpacityDecayTimer > 0) {
        gMenuCurIndex += updateRate << 8;
        if (gOpacityDecayTimer >= 40) {
            var_s4 = 0;
        } else {
            var_s4 = 40 - gOpacityDecayTimer;
        }
        var_s4 = (var_s4 * 5) + 72;
        var_s5 = gMenuCurIndex;
        halvedFbSize = fb_size();
        halvedFbSize >>= 17;
        halvedFbSize &= 0x7FFF;
        textPos = halvedFbSize;
        for (nextIndex = 0; nextIndex < (s32)(sizeof(gRacerPortraits) / sizeof(gRacerPortraits[0])); nextIndex++) {
            texrect_draw(&sMenuCurrDisplayList, gRacerPortraits[nextIndex], ((sins_s16(var_s5) * var_s4) >> 16) + 140,
                         (((coss_s16(var_s5) * var_s4) >> 16) + textPos) - 20, 255, 255, 255, 255);
            var_s5 += 0x1999;
        }
        rendermode_reset(&sMenuCurrDisplayList);
    }
    if (D_80126BE0 != 0) {
        D_80126BE0 = postrace_render(updateRate) == MENU_RESULT_CONTINUE;
    }
    if (D_80126BD8 == 0 && D_80126BE0 == 0) {
        breakLoop = 0;
        do {
            isShowingBestRaceTimes = (gCreditsControlData[gCreditsControlDataIndex] & 0xF000) ==
                                     (0x6000);
            switch (gCreditsControlData[gCreditsControlDataIndex] & 0xF000) {
                case (0x1000):
                    gCreditsControlDataIndex = 0;
                    isCreditsEnd = 1;
                    gIgnorePlayerInputTime = 0;
                    break;
                case (0x6000):
                case (0x2000):
                    D_80126BE8 =
                        gCreditsControlData[gCreditsControlDataIndex] & 0xFFFFFFFF & ~0xF000;
                    nextIndex = ++gCreditsControlDataIndex;
                    while ((gCreditsControlData[gCreditsControlDataIndex] & 0xF000) ==
                           (0)) {
                        gCreditsControlDataIndex++;
                    }
                    textPos = osTvType == 0 ? (240 / 2) + 14 : (240 / 2);
                    var_s5 = FONT_COLOURFUL;
                    textLineHeight = 20;
                    controlDataLength = gCreditsControlDataIndex - nextIndex;
                    if (controlDataLength == 1) {
                        textPos -= 14;
                        var_s5 = FONT_LARGE;
                    } else if (isShowingBestRaceTimes) {
                        textPos -= (controlDataLength * 16) - 3;
                        textLineHeight = 32;
                    } else {
                        textPos -= (controlDataLength * 16) - 8;
                    }
                    gCreditsMenuElements[0].left = 480;
                    if ((gCreditsControlData[gCreditsControlDataIndex] & 0xF000) ==
                        (0x3000)) {
                        gCreditsMenuElements[0].right = (320 / 2);
                    } else {
                        gCreditsMenuElements[0].right = -(320 / 2);
                    }
                    for (creditsMenuElementIndex = 0, var_s4 = nextIndex; var_s4 < gCreditsControlDataIndex; var_s4++) {
                        gCreditsMenuElements[creditsMenuElementIndex].top = textPos;
                        gCreditsMenuElements[creditsMenuElementIndex].middle = textPos;
                        gCreditsMenuElements[creditsMenuElementIndex].bottom = textPos;
                        if (isShowingBestRaceTimes) {
                            gCreditsMenuElements[creditsMenuElementIndex].textFont = FONT_COLOURFUL;
                            gCreditsMenuElements[creditsMenuElementIndex].filterGreen = 0;
                            gCreditsMenuElements[creditsMenuElementIndex].filterBlendFactor = 48;
                            gCreditsMenuElements[creditsMenuElementIndex].t.asciiText =
                                level_name(mainTrackIds[gCreditsControlData[var_s4]]);
                            creditsMenuElementIndex++;
                            gCreditsMenuElements[creditsMenuElementIndex].top = textPos + 14;
                            gCreditsMenuElements[creditsMenuElementIndex].middle = textPos + 14;
                            gCreditsMenuElements[creditsMenuElementIndex].bottom = textPos + 14;
                            gCreditsMenuElements[creditsMenuElementIndex].textFont = FONT_COLOURFUL;
                            gCreditsMenuElements[creditsMenuElementIndex].t.asciiText =
                                gCreditsBestTimesArray[gCreditsControlData[var_s4]];
                            creditsMenuElementIndex++;
                        } else {
                            if (creditsMenuElementIndex & 1) {
                                gCreditsMenuElements[creditsMenuElementIndex].filterGreen = 255;
                                gCreditsMenuElements[creditsMenuElementIndex].filterBlendFactor = 0;
                            }
                            gCreditsMenuElements[creditsMenuElementIndex].textFont = var_s5;
                            gCreditsMenuElements[creditsMenuElementIndex].t.asciiText =
                                gCreditsArray[gCreditsControlData[var_s4]];
                            creditsMenuElementIndex++;
                        }
                        var_s5 = FONT_LARGE;
                        textPos += textLineHeight;
                        textLineHeight = 32;
                    }
                    gCreditsMenuElements[creditsMenuElementIndex].t.element = 0;
                    postrace_offsets(gCreditsMenuElements, 0.5f, (f32) D_80126BE8 / 60.0f, 0.5f, 0, 0);
                    D_80126BE0 = postrace_render(0) == MENU_RESULT_CONTINUE;
                    breakLoop = 1;
                    break;
                case (0x3000):
                    D_80126BE8 =
                        gCreditsControlData[gCreditsControlDataIndex] & 0xFFFFFFFF & ~0xF000;
                    nextIndex = ++gCreditsControlDataIndex;
                    while ((gCreditsControlData[gCreditsControlDataIndex] & 0xF000) ==
                           (0)) {
                        gCreditsControlDataIndex++;
                    }
                    gCreditsMenuElements[0].left = (320 / 2);
                    if ((gCreditsControlData[gCreditsControlDataIndex] & 0xF000) ==
                        (0x3000)) {
                        gCreditsMenuElements[0].right = (320 / 2);
                    } else {
                        gCreditsMenuElements[0].right = -(320 / 2);
                    }
                    for (var_s4 = nextIndex; var_s4 < gCreditsControlDataIndex; var_s4++) {
                        gCreditsMenuElements[1 + var_s4 - nextIndex].t.asciiText =
                            gCreditsArray[gCreditsControlData[var_s4]];
                    }
                    gCreditsMenuElements[var_s4 - nextIndex + 1].t.asciiText = 0;
                    postrace_offsets(gCreditsMenuElements, 0.5f, (f32) D_80126BE8 / 60.0f, 0.5f, 0, 0);
                    D_80126BE0 = postrace_render(0) == MENU_RESULT_CONTINUE;
                    breakLoop = 1;
                    break;
                case (0x4000):
                    gCreditsControlDataIndex++;
                    D_80126BD8 = 1;
                    breakLoop = 1;
                    break;
                case (0x5000):
                    gCreditsControlDataIndex++;
                    break;
            }
        } while (breakLoop == 0);
    }
    buttonsPressedAllPlayers = 0;
    if (gIgnorePlayerInputTime == 0 && gMenuDelay == 0) {
        for (nextIndex = 0; nextIndex < 4; nextIndex++) {
            buttonsPressedAllPlayers |= input_pressed(nextIndex);
        }
    }
    switch (gMenuStage) {
        case 0:
            tempBackgroundLevelData = &creditsBackgroundLevelData[D_80126BCC];
            bgload_start(tempBackgroundLevelData->levelId, tempBackgroundLevelData->cutsceneId);
            gMenuStage = 1;
            gOpacityDecayTimer = 40;
            break;
        case 1:
            if (bgload_active() == 0) {
                gMenuStage = 2;
                gOptionBlinkTimer = 40;
                D_80126BD8 = 0;
            }
            break;
        case 2:
            gOptionBlinkTimer -= updateRate;
            gOpacityDecayTimer -= updateRate;
            if (gOptionBlinkTimer <= 0) {
                gOptionBlinkTimer += 600;
                gMenuStage = 3;
            }
            break;
        case 3:
            gOptionBlinkTimer -= updateRate;
            if (gOpacityDecayTimer > 0) {
                gOpacityDecayTimer -= updateRate;
            } else {
                gOpacityDecayTimer = 0;
            }
            if (gOptionBlinkTimer <= 0) {
                gOptionBlinkTimer = 40;
                gMenuStage = 4;
            }
            break;
        case 4:
            gOptionBlinkTimer -= updateRate;
            gOpacityDecayTimer += updateRate;
            if (gOptionBlinkTimer <= 0) {
                gMenuStage = 0;
                D_80126BCC++;
                if ((D_80126BCC + creditsBackgroundLevelData)->levelId < 0) {
                    D_80126BCC = 0;
                    gIgnorePlayerInputTime = 0;
                }
            }
            break;
    }
    if ((buttonsPressedAllPlayers & (0x8000 | 0x1000)) || (buttonsPressedAllPlayers & 0x4000) ||
        isCreditsEnd) {
        gMenuDelay = 1;
        disable_new_screen_transitions();
        transition_begin(&sMenuTransitionFadeIn);
        enable_new_screen_transitions();
        music_fade(-128);
    }
    if (gMenuDelay > 0) {
        gMenuDelay += updateRate;
        if (bgload_active() == 0 && gMenuDelay > 30) {
            music_change_on();
            credits_free();
            load_level_for_menu(ASSET_LEVEL_FRONTEND, ZERO_PLAYERS, 0x0);
            menu_init(MENU_LOGOS);
        }
    }
    return 0;
}
void credits_free(void) {
    music_voicelimit_set(18);
    disable_new_screen_transitions();
    camDisableUserView(0, 0);
    set_viewport_properties(0, 0x8000, 0x8000, 0x8000, 0x8000);
    menu_assetgroup_free(gCreditsObjectIndices);
    unload_font(ASSET_FONTS_BIGFONT);
    set_gIntDisFlag(0);
}
void menu_camera_centre(void) {
    Camera *cam;
    s16 angleY;
    s16 angleX;
    s16 angleZ;
    f32 posX;
    f32 posY;
    f32 posZ;
    cam_set_layout(VIEWPORT_LAYOUT_1_PLAYER);
    set_active_camera(0);
    cam = cam_get_active_camera();
    angleY = cam->trans.rotation.y_rotation;
    angleX = cam->trans.rotation.x_rotation;
    angleZ = cam->trans.rotation.z_rotation;
    posX = cam->trans.x_position;
    posY = cam->trans.y_position;
    posZ = cam->trans.z_position;
    cam->trans.rotation.z_rotation = 0;
    cam->trans.rotation.x_rotation = 0;
    cam->trans.rotation.y_rotation = 0x8000;
    cam->trans.x_position = -32.0f;
    cam->trans.y_position = -32.0f;
    cam->trans.z_position = -32.0f;
    update_envmap_position(0, 0, -1);
    viewport_main(&sMenuCurrDisplayList, &sMenuCurrHudMat);
    cam->trans.rotation.y_rotation = angleY;
    cam->trans.rotation.x_rotation = angleX;
    cam->trans.rotation.z_rotation = angleZ;
    cam->trans.x_position = posX;
    cam->trans.y_position = posY;
    cam->trans.z_position = posZ;
}
 void func_8009BE54(void) {
}
void reset_controller_sticks(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        gControllersXAxisDirection[i] = 0;
        gControllersYAxisDirection[i] = 0;
        gControllersXAxisDelay[i] = 0;
        gControllersYAxisDelay[i] = 0;
        gControllersXAxis[i] = 0;
        gControllersYAxis[i] = 0;
    }
}
void update_controller_sticks(void) {
    s32 XClamp, YClamp;
    s32 i;
    for (i = 0; i < 4; i++) {
        XClamp = input_clamp_stick_x(i);
        YClamp = input_clamp_stick_y(i);
        gControllersXAxisDirection[i] = 0;
        gControllersYAxisDirection[i] = 0;
        if (XClamp < -35 && gControllersXAxis[i] >= -35) {
            gControllersXAxisDirection[i] = -1;
            gControllersXAxisDelay[i] = 0;
        }
        if (XClamp > 35 && gControllersXAxis[i] <= 35) {
            gControllersXAxisDirection[i] = 1;
            gControllersXAxisDelay[i] = 0;
        }
        if (YClamp < -35 && gControllersYAxis[i] >= -35) {
            gControllersYAxisDirection[i] = -1;
            gControllersYAxisDelay[i] = 0;
        }
        if (YClamp > 35 && gControllersYAxis[i] <= 35) {
            gControllersYAxisDirection[i] = 1;
            gControllersYAxisDelay[i] = 0;
        }
        gControllersYAxis[i] = YClamp;
        if (gControllersYAxis[i] < -35) {
            gControllersYAxisDelay[i]++;
        } else if (gControllersYAxis[i] > 35) {
            gControllersYAxisDelay[i]++;
        } else {
            gControllersYAxisDelay[i] = 0;
        }
        if (gControllersYAxisDelay[i] > 15) {
            gControllersYAxis[i] = 0;
            gControllersYAxisDelay[i] = 0;
        }
        gControllersXAxis[i] = XClamp;
        if (gControllersXAxis[i] < -35) {
            gControllersXAxisDelay[i]++;
        } else if (gControllersXAxis[i] > 35) {
            gControllersXAxisDelay[i]++;
        } else {
            gControllersXAxisDelay[i] = 0;
        }
        if (gControllersXAxisDelay[i] > 15) {
            gControllersXAxis[i] = 0;
            gControllersXAxisDelay[i] = 0;
        }
    }
}
void reset_character_id_slots(void) {
    s32 i;
    gTrackSelectRow = 1;
    for (i = 0; i < 8; i++) {
        gCharacterIdSlots[i] = i;
    }
}
s32 get_save_file_index(void) {
    return gSaveFileIndex;
}
s32 get_track_id_to_load(void) {
    Settings *settings = get_settings();
    if (!gIsInTracksMode && gTrackSpecifiedWithTrackIdToLoad == 0) {
        if (settings->newGame) {
            return 0;
        } else {
            return settings->courseId;
        }
    }
    gTrackSpecifiedWithTrackIdToLoad = 0;
    return gTrackIdToLoad;
}
s8 get_character_id_from_slot(s32 slot) {
    return gCharacterIdSlots[slot];
}
s8 get_character_id_from_slot_unused(s32 slot) {
    return gCharacterIdSlots[slot];
}
s8 get_player_selected_vehicle(s32 playerNum) {
    return gPlayerSelectVehicle[playerNum];
}
void set_player_selected_vehicle(s32 playerNum, s32 index) {
    gPlayerSelectVehicle[playerNum] = index;
}
s8 *charselect_status(void) {
    return gCharselectStatus;
}
s8 get_player_character(s32 controllerIndex) {
    if (controllerIndex < 0 || controllerIndex >= 4) {
        return -1;
    }
    if (!gActivePlayersArray[controllerIndex]) {
        return -1;
    }
    return gPlayersCharacterArray[controllerIndex];
}
void enable_tracks_mode(s32 boolean) {
    gIsInTracksMode = boolean;
}
s32 is_in_tracks_mode(void) {
    return gIsInTracksMode;
}
void set_magic_code_flags(s32 flags) {
    gActiveMagicCodes |= flags;
    gUnlockedMagicCodes |= flags;
}
s32 get_filtered_cheats(void) {
    s32 cheats = gActiveMagicCodes;
    if (!gIsInTracksMode || is_time_trial_enabled()) {
        cheats &= (CHEAT_CONTROL_TT | CHEAT_CONTROL_DRUMSTICK | CHEAT_BIG_CHARACTERS | CHEAT_SMALL_CHARACTERS | CHEAT_HORN_CHEAT | CHEAT_SELECT_SAME_PLAYER | CHEAT_TWO_PLAYER_ADVENTURE | CHEAT_ULTIMATE_AI | CHEAT_EPC_LOCK_UP_DISPLAY | CHEAT_ROM_CHECKSUM);
    }
    if (!level_is_race()) {
        cheats &= ~CHEAT_MIRRORED_TRACKS;
    }
    if (leveltable_type(get_settings()->courseId) & RACETYPE_CHALLENGE) {
        cheats &= ~(CHEAT_START_WITH_10_BANANAS | CHEAT_DISABLE_BANANAS | CHEAT_DISABLE_WEAPONS | CHEAT_ALL_BALLOONS_ARE_RED | CHEAT_ALL_BALLOONS_ARE_GREEN | CHEAT_ALL_BALLOONS_ARE_BLUE | CHEAT_ALL_BALLOONS_ARE_YELLOW | CHEAT_ALL_BALLOONS_ARE_RAINBOW);
    }
    if (gIsInAdventureTwo && level_is_race()) {
        cheats |= CHEAT_MIRRORED_TRACKS;
    }
    return cheats;
}
s32 get_number_of_active_players(void) {
    return gNumberOfActivePlayers;
}
s32 get_active_player_count(void) {
    LevelHeader *header = level_header();
    if (gIsInTwoPlayerAdventure && !gIsInTracksMode) {
        if (header->race_type == RACETYPE_DEFAULT || header->race_type & RACETYPE_CHALLENGE) {
            return 2;
        }
    }
    return gNumberOfActivePlayers;
}
s32 get_multiplayer_racer_count(void) {
    if (!gIsInTracksMode) {
        return 6;
    }
    if (gTrophyRaceWorldId) {
        return 6;
    }
    return (gMultiplayerSelectedNumberOfRacers + 1) << 1;
}
Settings **get_all_save_files_ptr(void) {
    return (Settings **) gSavefileData;
}
 void menu_title_reset(void) {
    gTitleScreenLoaded = 0;
}
void menu_assetgroup_free(s16 *assetGroup) {
    s32 index = 0;
    while (assetGroup[index] != -1) {
        menu_asset_free(assetGroup[index++]);
    }
}
void menu_asset_free(s32 assetID) {
    if (gMenuAssetActive[assetID]) {
        if (gMenuAssets[assetID] != 0) {
            if (((*gAssetsMenuElementIds)[assetID] & 0xC000) == 0xC000 &&
                gMenuAssets[assetID] != 0) {
                mempool_free_timer(0);
                tex_free(gMenuAssets[assetID]);
                mempool_free_timer(2);
            } else {
                if ((*gAssetsMenuElementIds)[assetID] & 0x8000) {
                    sprite_free((Sprite *) (u32) gMenuAssets[assetID]);
                } else {
                    if ((*gAssetsMenuElementIds)[assetID] & 0x4000) {
                        free_object((Object *) (u32) gMenuAssets[assetID]);
                    } else {
                        free_3d_model((ModelInstance *) (u32) gMenuAssets[assetID]);
                    }
                }
            }
        }
        gMenuAssets[assetID] = 0;
        gMenuAssetActive[assetID] = 0;
        gMenuObjectsCount--;
        gParticlePtrList_flush();
    }
    if (gMenuObjectsCount == 0) {
        if (gMenuImages != 0) {
            mempool_free(gMenuImages);
            gMenuImages = 0;
        }
        if (*gAssetsMenuElementIds != 0) {
            mempool_free(*gAssetsMenuElementIds);
            *gAssetsMenuElementIds = 0;
            gMenuElementIdCount = 0;
        }
    }
}
void menu_assetgroup_load(s16 *textureIndex) {
    s32 index = 0;
    while (textureIndex[index] != -1) {
        menu_asset_load(textureIndex[index++]);
    }
}
void menu_asset_load(s32 assetID) {
    s32 i;
    LevelObjectEntryCommon entry;
    if (*gAssetsMenuElementIds == 0) {
        *gAssetsMenuElementIds = (s16 *) asset_table_load(ASSET_MENU_ELEMENT_IDS);
        for (gMenuElementIdCount = 0; (*gAssetsMenuElementIds)[gMenuElementIdCount] != -1; gMenuElementIdCount++) {}
        gMenuObjectsCount = 0;
        for (i = 0; i < gMenuElementIdCount; i++) {
            gMenuAssetActive[i] = 0;
        }
    }
    if (((!assetID) && (!assetID)) && (!assetID)) {
        ("loadFrontEndItem() - Item no %d out of range 0-%d\n", assetID, sizeof(gMenuAssetActive));
    }
    if (!gMenuAssetActive[assetID]) {
        i = (*gAssetsMenuElementIds)[assetID];
        if ((i & 0xC000) == 0xC000) {
            gMenuAssets[assetID] = load_texture(i & 0x3FFF);
        } else if (i & 0x8000) {
            gMenuAssets[assetID] = tex_load_sprite(i & 0x3FFF, 0);
        } else if (i & 0x4000) {
            if (gMenuElementIdCount) {}
            entry.objectID = i & 0xFFFF;
            entry.size = sizeof(LevelObjectEntryCommon);
            entry.x = 0;
            entry.y = 0;
            entry.z = 0;
            gMenuAssets[assetID] = spawn_object(&entry, OBJECT_SPAWN_NONE);
        } else {
            gMenuAssets[assetID] = object_model_init(i & 0x3FFF, 0);
        }
        gMenuAssetActive[assetID] = 1;
        gMenuObjectsCount++;
    }
}
void menu_imagegroup_load(s16 *imageSet) {
    s32 index = 0;
    while (imageSet[index] != -1) {
        menu_image_load(imageSet[index++]);
    }
}
void menu_image_load(s32 imageID) {
    if (gMenuImages == 0) {
        gMenuImages = mempool_alloc_safe(sizeof(MenuAsset) * 18, 0xFF0000FF);
    }
    gMenuImages[imageID].trans.rotation.x = sMenuImageProperties[imageID].trans.rotation.x;
    gMenuImages[imageID].trans.rotation.y = sMenuImageProperties[imageID].trans.rotation.y;
    gMenuImages[imageID].trans.rotation.z = sMenuImageProperties[imageID].trans.rotation.z;
    gMenuImages[imageID].trans.spriteID = sMenuImageProperties[imageID].trans.spriteID;
    gMenuImages[imageID].trans.x_position = sMenuImageProperties[imageID].trans.x_position;
    gMenuImages[imageID].trans.y_position = sMenuImageProperties[imageID].trans.y_position;
    gMenuImages[imageID].trans.z_position = sMenuImageProperties[imageID].trans.z_position;
    gMenuImages[imageID].trans.scale = sMenuImageProperties[imageID].trans.scale;
    gMenuImages[imageID].spriteOffset = sMenuImageProperties[imageID].spriteOffset;
    gMenuImages[imageID].unk1A = rand_range(0, 0xFFFF);
    gMenuImages[imageID].unk1B = rand_range(0, 0xFFFF);
    gMenuImages[imageID].unk1C = rand_range(0, 0xFFFF);
    gMenuImages[imageID].unk1D = sMenuImageProperties[imageID].unk1D;
}
 void menu_imagegroup_free(void) {
}
void menu_element_render(s32 elementID) {
    Object *object;
    MenuAsset *asset;
    Sprite *sprite;
    ModelInstance *model;
    if (gMenuAssets[gMenuImages[elementID].trans.spriteID] != 0) {
        if (((*gAssetsMenuElementIds)[gMenuImages[elementID].trans.spriteID] & 0xC000) !=
            0xC000) {
            if ((*gAssetsMenuElementIds)[gMenuImages[elementID].trans.spriteID] & 0x4000) {
                if (0) {}
                object = (Object *) gMenuAssets[gMenuImages[elementID].trans.spriteID];
                asset = (MenuAsset *) &gMenuImages[elementID];
                object->trans.rotation.y_rotation = asset->trans.rotation.y_rotation;
                object->trans.rotation.x_rotation = asset->trans.rotation.x_rotation;
                object->trans.rotation.z_rotation = asset->trans.rotation.z_rotation;
                object->trans.x_position = asset->trans.x_position;
                object->trans.y_position = asset->trans.y_position;
                object->trans.z_position = asset->trans.z_position;
                object->trans.scale = asset->trans.scale;
                if (gMenuDisableObjAnim == 0) {
                    object->animFrame = asset->unk1D;
                    object->modelIndex = asset->spriteOffset;
                }
                object->opacity = sMenuGuiOpacity;
                render_object(&sMenuCurrDisplayList, &sMenuCurrHudMat, &sMenuCurrHudVerts, object);
            } else {
                if ((*gAssetsMenuElementIds)[gMenuImages[elementID].trans.spriteID] & 0x8000) {
                    sprite = (Sprite *) gMenuAssets[gMenuImages[elementID].trans.spriteID];
                    { Gfx *_g = (Gfx *)(sMenuCurrDisplayList++); _g->words.w0 = (((unsigned int) (((unsigned int)(0xfa) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (0)))); _g->words.w1 = (((unsigned int) (((unsigned int)(sMenuGuiColourR) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(sMenuGuiColourG) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)(sMenuGuiColourB) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(sMenuGuiOpacity) & ((0x01 << (8)) - 1)) << (0)))); };
                    { Gfx *_g = (Gfx *)(sMenuCurrDisplayList++); _g->words.w0 = ((unsigned int) (((unsigned int)(0xfb) & ((0x01 << (8)) - 1)) << (24))); _g->words.w1 = (unsigned int)((((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (0))))); };
                    render_ortho_triangle_image(&sMenuCurrDisplayList, &sMenuCurrHudMat, &sMenuCurrHudVerts,
                                                (ObjectSegment *) (&gMenuImages[elementID]), sprite, gMenuSpriteFlags);
                    { Gfx *_g = (Gfx *)(sMenuCurrDisplayList++); _g->words.w0 = (((unsigned int) (((unsigned int)(0xfa) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (0)))); _g->words.w1 = (((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (0)))); };
                } else {
                    if (sMenuGuiOpacity < 255) {
                        { Gfx *_g = (Gfx *)(sMenuCurrDisplayList++); _g->words.w0 = (((unsigned int) (((unsigned int)(0xfa) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (0)))); _g->words.w1 = (((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(sMenuGuiOpacity) & ((0x01 << (8)) - 1)) << (0)))); };
                    } else {
                        { Gfx *_g = (Gfx *)(sMenuCurrDisplayList++); _g->words.w0 = (((unsigned int) (((unsigned int)(0xfa) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (0)))); _g->words.w1 = (((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (0)))); };
                    };
                    { Gfx *_g = (Gfx *)(sMenuCurrDisplayList++); _g->words.w0 = ((unsigned int) (((unsigned int)(0xfb) & ((0x01 << (8)) - 1)) << (24))); _g->words.w1 = (unsigned int)((((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (0))))); };
                    mtx_cam_push(&sMenuCurrDisplayList, &sMenuCurrHudMat, &gMenuImages[elementID].trans,
                                 gTrackSelectWoodFrameHeightScale, 0);
                    model = gMenuAssets[gMenuImages[elementID].trans.spriteID];
                    render_track_selection_viewport_border(model->objModel);
                    mtx_pop(&sMenuCurrDisplayList);
                    if (sMenuGuiOpacity < 255) {
                        { Gfx *_g = (Gfx *)(sMenuCurrDisplayList++); _g->words.w0 = (((unsigned int) (((unsigned int)(0xfa) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(0) & ((0x01 << (8)) - 1)) << (0)))); _g->words.w1 = (((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (8))) | ((unsigned int) (((unsigned int)(255) & ((0x01 << (8)) - 1)) << (0)))); };
                    }
                }
            }
        }
    }
}
void render_track_selection_viewport_border(ObjectModel *objMdl) {
    s32 pad1[4];
    s32 flags;
    s32 pad2[4];
    TextureHeader *tex;
    Triangle *tris;
    s32 triOffset;
    s32 vertOffset;
    Vertex *verts;
    s32 numVerts;
    s32 numTris;
    s32 texOffset;
    s32 texEnabled;
    s32 i;
    flags = RENDER_FOG_ACTIVE | RENDER_ANTI_ALIASING;
    if (sMenuGuiOpacity != 255) {
        flags = RENDER_FOG_ACTIVE | RENDER_SEMI_TRANSPARENT | RENDER_ANTI_ALIASING;
    }
    for (i = 0; i < objMdl->numberOfBatches; i++) {
        if (!(objMdl->batches[i].flags & RENDER_Z_UPDATE)) {
            vertOffset = objMdl->batches[i].verticesOffset;
            triOffset = objMdl->batches[i].facesOffset;
            numVerts = objMdl->batches[i + 1].verticesOffset - vertOffset;
            numTris = objMdl->batches[i + 1].facesOffset - triOffset;
            verts = &objMdl->vertices[vertOffset];
            tris = &objMdl->triangles[triOffset];
            if (objMdl->batches[i].textureIndex == -1) {
                tex = 0;
                texEnabled = 0;
                texOffset = 0;
            } else {
                tex = objMdl->textures[objMdl->batches[i].textureIndex].texture;
                texEnabled = 1;
                texOffset = objMdl->batches[i].texOffset << 14;
            }
            material_set(&sMenuCurrDisplayList, tex, flags, texOffset);
            { Gfx *_g = (Gfx *)(sMenuCurrDisplayList++); _g->words.w0 = (((unsigned int) (((unsigned int)((4)) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)((((numVerts)-1)<<3|(((u32)((u32)(((char *)(verts)-0x80000000))) & 6))|(0))) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)(((((numVerts) * 8 + (numVerts)) << 1) + 8)) & ((0x01 << (16)) - 1)) << (0)))); _g->words.w1 = (unsigned int)((u32)(((char *)(verts)-0x80000000))); };
            { Gfx *_g = (Gfx *)(sMenuCurrDisplayList++); _g->words.w0 = ((unsigned int) (((unsigned int)((((numTris) - 1) << 4) | (texEnabled)) & ((0x01 << (8)) - 1)) << (16))) | ((unsigned int) (((unsigned int)(5) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(((numTris)*16)) & ((0x01 << (16)) - 1)) << (0))); _g->words.w1 = (unsigned int)((u32)(((char *)(tris)-0x80000000))); };
        }
    }
}
void dialogue_npc_finish(s32 npcID) {
    if (gDoneTalkingToNPC[npcID] == 0) {
        if (npcID != 3) {
            sCurrentMenuID = 0;
            gDialogueSubmenu = 0;
        }
        gNeedToCloseDialogueBox = 1;
        gDoneTalkingToNPC[npcID] = 1;
    }
}
void dialogue_try_close(void) {
    if (gNeedToCloseDialogueBox) {
        gNeedToCloseDialogueBox = 0;
        dialogue_close(1);
        reset_controller_sticks();
    }
}
s32 npc_dialogue_loop(u32 dialogueOption) {
    s32 result;
    gDoneTalkingToNPC[dialogueOption] = 0;
    if ((textbox_visible() != 0) && (dialogueOption != DIALOGUE_CHALLENGE)) {
        return 0;
    }
    if (gNeedToCloseDialogueBox) {
        return 0;
    }
    if (dialogueOption != DIALOGUE_CHALLENGE) {
        set_pause_lockout_timer(1);
    }
    result = 0;
    update_controller_sticks();
    dialogue_clear(1);
    open_dialogue_box(1);
    set_current_dialogue_background_colour(1, 0, 0, 0, 128);
    func_8001F450();
    switch (dialogueOption) {
        case DIALOGUE_TAJ:
            result = taj_menu_loop();
            break;
        case DIALOGUE_TT:
            result = tt_menu_loop();
            break;
        case DIALOGUE_CHALLENGE:
            result = dialogue_challenge_loop();
            break;
        case DIALOGUE_TROPHY:
            result = trophy_race_cabinet_menu_loop();
            break;
        case DIALOGUE_RACERESULT:
            result = dialogue_race_defeat();
            break;
    }
    return result;
}
void set_option_text_colour(s32 condition) {
    if (condition == 0) {
        set_current_text_colour(1, 0, 0, 0x7F, 0x5A, 0xFF);
        if (gDialogueOptionTangible != 0) {
            set_current_text_colour(1, 0, 0, 0x7F, 0x5A, 0x78);
        }
    } else {
        set_current_text_colour(1, 0xCF, 0xCF, 0xCF, 0x5A, 0xFF);
    }
    gDialogueOptionTangible = (u8) 0;
}
void render_dialogue_option(char *text, s32 yOffset, s32 optionID) {
    set_option_text_colour(gDialogueSubmenu == sDialogueOptionMax);
    if (gDialogueSubmenu == sDialogueOptionMax) {
        gDialogueItemSelection = optionID;
    }
    render_dialogue_text(1, -0x8000, gDialogueOptionYOffset, text, 1, HORZ_ALIGN_CENTER);
    gDialogueOptionYOffset = (s8) (gDialogueOptionYOffset + yOffset);
    sDialogueOptionMax = (s8) (sDialogueOptionMax + 1);
}
void handle_menu_joystick_input(void) {
    if (gControllersYAxisDirection[0] < 0) {
        gDialogueSubmenu = gDialogueSubmenu + 1;
        sound_play(SOUND_MENU_PICK, 0);
    } else if (gControllersYAxisDirection[0] > 0) {
        gDialogueSubmenu = gDialogueSubmenu - 1;
        sound_play(SOUND_MENU_PICK, 0);
    }
    if (gDialogueSubmenu < 0) {
        gDialogueSubmenu = sDialogueOptionMax - 1;
    }
    if (gDialogueSubmenu >= sDialogueOptionMax) {
        gDialogueSubmenu = 0;
    }
}
 void func_8009D324(void) {
    unused_800DF4D8 = 0;
}
void set_next_taj_challenge_menu(s32 arg0) {
    gNextTajChallengeMenu = arg0;
}
void set_menu_id_if_option_equal(s32 IDToCheck, s32 IDToSet) {
    if (sCurrentMenuID == IDToCheck) {
        sCurrentMenuID = IDToSet;
    }
}
s32 taj_menu_loop(void) {
    s32 dialogueResult;
    s32 buttonsPressed;
    Settings *settings;
    settings = get_settings();
    if (gNextTajChallengeMenu && sCurrentMenuID == DIALOGUEPAGE_TAJ_TUTORIAL) {
        sCurrentMenuID = -gNextTajChallengeMenu;
    }
    if (sCurrentMenuID == DIALOGUEPAGE_TAJ_TUTORIAL) {
        sCurrentMenuID = DIALOGUEPAGE_TAJ_ROOT;
    }
    if (sCurrentMenuID >= DIALOGUEPAGE_TAJ_ROOT && sCurrentMenuID <= DIALOGUEPAGE_TAJ_CHALLENGES) {
        set_current_dialogue_box_coords(1, 24, 16, 184, 124);
        set_dialogue_font(1, ASSET_FONTS_FUNFONT);
    }
    dialogueResult = 0;
    buttonsPressed = input_pressed(PLAYER_ONE);
    sDialogueOptionMax = 0;
    switch (sCurrentMenuID) {
        case DIALOGUEPAGE_TAJ_VEHICLE_SELECT:
        case DIALOGUEPAGE_TAJ_VEHICLE_SELECT_2:
            render_dialogue_text(1, -0x8000, 6, gMenuText[ASSET_MENU_TEXT_VEHICLESELECT], 1,
                                 HORZ_ALIGN_CENTER);
            gDialogueOptionYOffset = 30;
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_CAR], 20, 0);
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_HOVERCRAFT], 20, 1);
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_PLANE], 20, 2);
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_MAINMENU], 20, 3);
            break;
        case DIALOGUEPAGE_TAJ_CHALLENGES:
        case DIALOGUEPAGE_TAJ_CHALLENGES_2:
            render_dialogue_text(1, -0x8000, 6, gMenuText[ASSET_MENU_TEXT_CHALLENGESELECT], 1,
                                 HORZ_ALIGN_CENTER);
            gDialogueOptionYOffset = 30;
            if (settings->tajFlags & 0x01) {
                gDialogueOptionTangible = settings->tajFlags & 0x08;
                render_dialogue_option(gMenuText[ASSET_MENU_TEXT_CARCHALLENGE], 20, 0);
            }
            if (settings->tajFlags & 0x02) {
                gDialogueOptionTangible = settings->tajFlags & 0x10;
                render_dialogue_option(gMenuText[ASSET_MENU_TEXT_HOVERCHALLENGE], 20, 1);
            }
            if (settings->tajFlags & 0x04) {
                gDialogueOptionTangible = settings->tajFlags & 0x20;
                render_dialogue_option(gMenuText[ASSET_MENU_TEXT_PLANECHALLENGE], 20, 2);
            }
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_MAINMENU], 20, 3);
            break;
    }
    switch (sCurrentMenuID) {
        case DIALOGUEPAGE_TAJ_TUTORIAL:
            set_current_text(ASSET_GAME_TEXT_7);
            sCurrentMenuID = DIALOGUEPAGE_TAJ_ROOT;
            unused_800DF4D8 = 1;
            break;
        case DIALOGUEPAGE_TAJ_ROOT:
            gNextTajChallengeMenu = 0;
            render_dialogue_text(1, -0x8000, 6, gMenuText[190], 1,
                                 HORZ_ALIGN_CENTER);
            gDialogueOptionYOffset = 30;
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_CHANGEVEHICLE], 20, 0);
            if (settings->tajFlags & (0x01 | 0x02 | 0x04)) {
                render_dialogue_option(gMenuText[ASSET_MENU_TEXT_CHALLENGES], 20, 1);
            }
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_RETURN], 20, 2);
            handle_menu_joystick_input();
            if (buttonsPressed & 0x4000) {
                dialogueResult = 3;
                sound_play(SOUND_MENU_BACK3, 0);
            } else if (buttonsPressed & 0x8000) {
                sound_play(SOUND_SELECT2, 0);
                switch (gDialogueItemSelection) {
                    case 1:
                        sCurrentMenuID = DIALOGUEPAGE_TAJ_CHALLENGES;
                        gDialogueSubmenu = 0;
                        play_taj_voice_clip(SOUND_VOICE_TAJ_CHALLENGE_MENU, 1);
                        break;
                    case 2:
                        dialogueResult = DIALOGUEPAGE_TAJ_CHALLENGES;
                        break;
                    case 0:
                        sCurrentMenuID = DIALOGUEPAGE_TAJ_VEHICLE_SELECT;
                        gDialogueSubmenu = 0;
                        play_taj_voice_clip(SOUND_VOICE_TAJ_SELECT_VEHICLE, 1);
                        break;
                }
            }
            break;
        case DIALOGUEPAGE_TAJ_VEHICLE_SELECT:
            handle_menu_joystick_input();
            if (buttonsPressed & 0x4000) {
                sound_play(SOUND_MENU_BACK3, 0);
                play_taj_voice_clip(SOUND_VOICE_TAJ_MENUBACK, 1);
                sCurrentMenuID = DIALOGUEPAGE_TAJ_ROOT;
                gDialogueSubmenu = 0;
            } else if (buttonsPressed & 0x8000) {
                if (gDialogueItemSelection != 3) {
                    dialogueResult = gDialogueItemSelection | 0x80;
                    sCurrentMenuID = DIALOGUEPAGE_TAJ_VEHICLE_SELECT_2;
                } else {
                    sCurrentMenuID = DIALOGUEPAGE_TAJ_ROOT;
                    gDialogueSubmenu = 0;
                    play_taj_voice_clip(SOUND_VOICE_TAJ_MENUBACK, 1);
                }
            }
            break;
        case DIALOGUEPAGE_TAJ_CHALLENGES:
            handle_menu_joystick_input();
            if ((buttonsPressed & 0x4000) || ((buttonsPressed & 0x8000) && (gDialogueItemSelection == 3))) {
                sound_play(SOUND_MENU_BACK3, 0);
                play_taj_voice_clip(SOUND_VOICE_TAJ_MENUBACK2, 1);
                sCurrentMenuID = DIALOGUEPAGE_TAJ_ROOT;
                gDialogueSubmenu = 3;
            } else if (buttonsPressed & 0x8000) {
                dialogueResult = gDialogueItemSelection | 0x40;
                sound_play(SOUND_SELECT2, 0);
                sCurrentMenuID = DIALOGUEPAGE_TAJ_CHALLENGES_2;
            }
            break;
        case DIALOGUEPAGE_TAJ_CHALLENGE_PLANE:
        case DIALOGUEPAGE_TAJ_CHALLENGE_HOVER:
        case DIALOGUEPAGE_TAJ_CHALLENGE_CAR:
            set_current_text(ASSET_GAME_TEXT_8 - sCurrentMenuID);
            sCurrentMenuID = DIALOGUEPAGE_TAJ_4;
            break;
        case DIALOGUEPAGE_TAJ_CHALLENGE_LOSE:
            set_current_text(ASSET_GAME_TEXT_17);
            gNextTajChallengeMenu = 0;
            sCurrentMenuID = DIALOGUEPAGE_TAJ_ROOT;
            gDialogueSubmenu = 3;
            break;
        case DIALOGUEPAGE_TAJ_CHALLENGE_WIN:
            set_current_text(ASSET_GAME_TEXT_21);
            gNextTajChallengeMenu = 0;
            sCurrentMenuID = DIALOGUEPAGE_TAJ_7;
            gDialogueSubmenu = 0;
            break;
        case DIALOGUEPAGE_TAJ_CHALLENGE_WIN_3:
        case DIALOGUEPAGE_TAJ_CHALLENGE_WIN_2:
        case DIALOGUEPAGE_TAJ_CHALLENGE_WIN_1:
            set_current_text(ASSET_GAME_TEXT_12 - sCurrentMenuID);
            sCurrentMenuID = DIALOGUEPAGE_TAJ_6;
            gDialogueSubmenu = 0;
            break;
        case DIALOGUEPAGE_TAJ_4:
            dialogueResult = (gNextTajChallengeMenu - 1) | 0x40;
            sCurrentMenuID = DIALOGUEPAGE_TAJ_5;
            dialogue_close(1);
            break;
        case DIALOGUEPAGE_TAJ_5:
            gNextTajChallengeMenu = 0;
            dialogue_close(1);
            break;
        case DIALOGUEPAGE_TAJ_6:
        case DIALOGUEPAGE_TAJ_7:
            dialogueResult = 4;
            if (sCurrentMenuID == DIALOGUEPAGE_TAJ_7) {
                dialogueResult = 3;
            }
            gNeedToCloseDialogueBox = 0;
            dialogue_close(1);
            gNextTajChallengeMenu = 0;
            sCurrentMenuID = DIALOGUEPAGE_TAJ_TUTORIAL;
            break;
    }
    return dialogueResult;
}
s32 dialogue_race_defeat(void) {
    s32 state;
    s32 playerInput;
    set_current_dialogue_box_coords(1, 24, 16, 184, 135);
    set_dialogue_font(1, ASSET_FONTS_FUNFONT);
    state = 0;
    playerInput = input_pressed(PLAYER_ONE);
    sDialogueOptionMax = 0;
    gNextTajChallengeMenu = 0;
    render_dialogue_text(1, -0x8000, 6, gMenuText[ASSET_MENU_TEXT_LOSETOTAJ_0], 1,
                         HORZ_ALIGN_CENTER);
    render_dialogue_text(1, -0x8000, 20, gMenuText[ASSET_MENU_TEXT_LOSETOTAJ_1], 1,
                         HORZ_ALIGN_CENTER);
    gDialogueOptionYOffset = 50;
    render_dialogue_option(gMenuText[ASSET_MENU_TEXT_TRYAGAIN], 20, 0);
    render_dialogue_option(gMenuText[ASSET_MENU_TEXT_EXIT], 20, 1);
    handle_menu_joystick_input();
    if (playerInput & 0x8000) {
        sound_play(SOUND_SELECT2, 0);
        switch (gDialogueItemSelection) {
            case 0:
                state = 1;
                break;
            case 1:
                state = 2;
                break;
        }
    }
    return state;
}
s32 tt_menu_loop(void) {
    s32 currentOption;
    s32 buttonsPressed;
    s32 i;
    s32 yPos1;
    u8 result;
    Settings *settings;
    settings = get_settings();
    if (is_in_two_player_adventure()) {
        settings->cutsceneFlags |= 0x2;
    }
    if (!(settings->cutsceneFlags & 0x2)) {
        sCurrentMenuID = 5;
    }
        if ((sCurrentMenuID != 4) && (sCurrentMenuID != 5)) {
        currentOption = 120;
        if (has_ghost_to_save()) {
            currentOption = 136;
        }
        set_current_dialogue_box_coords(1, 24, 16, 192, currentOption);
    } else {
        set_current_dialogue_box_coords(1, 24, 16, 184, 220);
    }
    set_dialogue_font(1, ASSET_FONTS_FUNFONT);
    currentOption = 0;
    buttonsPressed = input_pressed(PLAYER_ONE) << 0;
    sDialogueOptionMax = 0;
    gDialogueOptionYOffset = 32;
    switch (sCurrentMenuID) {
        case 0:
        case 10:
            render_dialogue_text(1, -0x8000, 6, gMenuText[189], 1,
                                 HORZ_ALIGN_CENTER);
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_STATUS], 20, 3);
            if (!is_in_two_player_adventure()) {
                if (is_time_trial_enabled()) {
                    render_dialogue_option(gMenuText[ASSET_MENU_TEXT_TIMETRIALON], 20, 0);
                } else {
                    render_dialogue_option(gMenuText[ASSET_MENU_TEXT_TIMETRIALOFF], 20, 0);
                }
                if (has_ghost_to_save()) {
                    render_dialogue_option(gMenuText[ASSET_MENU_TEXT_SAVEGHOST], 20, 1);
                }
            }
            render_dialogue_option(gMenuText[ASSET_MENU_TEXT_RETURN], 20, 2);
            handle_menu_joystick_input();
            if (gDialogueItemSelection == 0) {
                if (gControllersXAxisDirection[0] > 0) {
                    if (!is_time_trial_enabled()) {
                        play_tt_voice_clip(SOUND_VOICE_TT_TIME_TRIAL_ON, 1);
                    }
                    set_time_trial_enabled(1);
                } else if (gControllersXAxisDirection[0] < 0) {
                    if (is_time_trial_enabled() == 1) {
                        play_tt_voice_clip(SOUND_VOICE_TT_TIME_TRIAL_OFF, 1);
                    }
                    set_time_trial_enabled(0);
                }
            }
            if ((buttonsPressed & 0x8000) && (sCurrentMenuID != 10)) {
                if (gPreviousMenuID && !gPreviousMenuID && !gPreviousMenuID) {}
                switch (gDialogueItemSelection) {
                    case 1:
                        sound_play(SOUND_SELECT2, 0);
                        gAdventureSaveGhost = 0;
                        gPreviousMenuID = 0;
                        sCurrentMenuID = 8;
                        break;
                    case 3:
                        sound_play(SOUND_SELECT2, 0);
                        play_tt_voice_clip(SOUND_VOICE_TT_GAME_STATUS, 1);
                        menu_assetgroup_load(D_800E1E2C);
                        menu_imagegroup_load(D_800E1E40);
                        gGameStatusVisible = 1;
                        sCurrentMenuID = 4;
                        break;
                }
                currentOption = gDialogueItemSelection + 1;
            } else if (buttonsPressed & 0x4000) {
                sound_play(SOUND_MENU_BACK3, 0);
                currentOption = 3;
            }
            if (sCurrentMenuID == 4) {
                currentOption = 0;
            }
            if (currentOption == 3) {
                sCurrentMenuID = 10;
            }
            if (sCurrentMenuID == 10) {
                currentOption = 3;
            }
            break;
        case 1:
            i = 0;
            while (gTTSaveGhostPakErrorText[i] != 0) {
                i++;
            }
            yPos1 = 58;
            if (i > 0) {
                i--;
                yPos1 -= (i << 2 << 1);
                i = 0;
                while (gTTSaveGhostPakErrorText[i] != 0) {
                    render_dialogue_text(1, -0x8000, yPos1, gTTSaveGhostPakErrorText[i], 1, HORZ_ALIGN_CENTER);
                    yPos1 += 16;
                    i++;
                }
            }
            if (buttonsPressed & (0x8000 | 0x4000)) {
                sCurrentMenuID = 0;
            }
            break;
        case 4:
            if (buttonsPressed & (0x8000 | 0x4000)) {
                sCurrentMenuID = 0;
                gGameStatusVisible = 0;
                menu_assetgroup_free(D_800E1E2C);
                play_tt_voice_clip(SOUND_VOICE_TT_OKAY, 1);
            }
            break;
        case 5: {
            i = ASSET_MENU_TEXT_TTINTRO_0;
            while (gMenuText[i] != 0) {
                render_dialogue_text(1, -0x8000, 6 + ((i - 52) * 16), gMenuText[i], 1, HORZ_ALIGN_CENTER);
                i++;
            }
            if (buttonsPressed & (0x8000 | 0x4000)) {
                settings->cutsceneFlags |= 0x2;
                sCurrentMenuID = 0;
            }
        } break;
        case 6:
            render_dialogue_text(1, -0x8000, 34, gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_3], 1,
                                 HORZ_ALIGN_CENTER);
            render_dialogue_text(1, -0x8000, 50, gMenuText[ASSET_MENU_TEXT_INSERTDEVICE_4], 1,
                                 HORZ_ALIGN_CENTER);
            render_dialogue_text(1, -0x8000, 66, gMenuText[161], 1,
                                 HORZ_ALIGN_CENTER);
            if (buttonsPressed & (0x8000 | 0x1000)) {
                sound_play(SOUND_SELECT2, 0);
                gAdventureSaveGhost = 0;
                gPreviousMenuID = 7;
                sCurrentMenuID = 8;
            } else if (buttonsPressed & 0x4000) {
                sound_play(SOUND_MENU_BACK3, 0);
                sCurrentMenuID = 0;
            }
            break;
        case 7:
            render_dialogue_text(1, -0x8000, 34, gMenuText[162], 1,
                                 HORZ_ALIGN_CENTER);
            render_dialogue_text(1, -0x8000, 50, gMenuText[186], 1,
                                 HORZ_ALIGN_CENTER);
            render_dialogue_text(1, -0x8000, 66, gMenuText[187], 1,
                                 HORZ_ALIGN_CENTER);
            if (buttonsPressed & (0x8000 | 0x4000 | 0x1000)) {
                sCurrentMenuID = 0;
            }
            break;
        case 8:
            render_dialogue_text(1, -0x8000, 50, gMenuText[ASSET_MENU_TEXT_PLEASEWAIT], 1,
                                 HORZ_ALIGN_CENTER);
            gAdventureSaveGhost++;
            if (gAdventureSaveGhost >= 5) {
                result = timetrial_save_player_ghost(0);
                if (result == CONTROLLER_PAK_CHANGED) {
                    result = timetrial_save_player_ghost(0);
                }
                switch (result) {
                    case CONTROLLER_PAK_GOOD:
                        sCurrentMenuID = gPreviousMenuID;
                        break;
                    case CONTROLLER_PAK_RUMBLE_PAK_FOUND:
                        sCurrentMenuID = 6;
                        break;
                    case CONTROLLER_PAK_NOT_FOUND:
                        gTTSaveGhostPakErrorText = sNoControllerPakMenuText;
                        sCurrentMenuID = 1;
                        break;
                    case CONTROLLER_PAK_FULL:
                    case CONTROLLER_PAK_NO_ROOM_FOR_GHOSTS:
                        gTTSaveGhostPakErrorText = sControllerPakFullMenuText;
                        sCurrentMenuID = 1;
                        break;
                    case CONTROLLER_PAK_BAD_DATA:
                        gTTSaveGhostPakErrorText = sCorruptDataMenuText;
                        sCurrentMenuID = 1;
                        break;
                    case CONTROLLER_PAK_INCONSISTENT:
                    case CONTROLLER_PAK_WITH_BAD_ID:
                    case CONTROLLER_PAK_CHANGED:
                    case CONTROLLER_PAK_SWITCH_TO_RUMBLE:
                    default:
                        gTTSaveGhostPakErrorText = sBadControllerPakMenuText;
                        sCurrentMenuID = 1;
                        break;
                }
            }
            break;
    }
    if ((sCurrentMenuID == 1) || (sCurrentMenuID == 2) ||
        (sCurrentMenuID == 3)) {
        render_dialogue_text(1, -0x8000, 6, gMenuText[ASSET_MENU_TEXT_PAKERROR], 1, HORZ_ALIGN_CENTER);
    }
    return currentOption;
}
void dialogue_tt_gamestatus(void) {
    s32 numBalloonsTensDigit;
    s32 y;
    s32 i;
    s32 x;
    s32 numOfItem;
    Settings *settings;
    s32 flag;
    s16 tempX;
    if (gGameStatusVisible == 1) {
        gGameStatusVisible++;
        return;
    }
    settings = get_settings();
    cam_set_sprite_anim_mode(SPRITE_ANIM_FRAME_INDEX);
    if (osTvType == 0) {
        y = 10;
    } else {
        y = 20;
    }
    numOfItem = 8;
    if (settings->cutsceneFlags & 4) {
        numOfItem = 9;
    }
    tempX = -74;
    gMenuImages[numOfItem].trans.x_position = tempX;
    gMenuImages[numOfItem].trans.y_position = 65 - y;
    menu_element_render(numOfItem);
    sprite_opaque(0);
    tempX = -29;
    gMenuImages[0].trans.x_position = tempX;
    gMenuImages[0].trans.y_position = 98 - y;
    gMenuImages[0].trans.x_position -= 6.0f;
    flag = settings->balloonsPtr[0] / 10;
    numBalloonsTensDigit = flag;
    if (numBalloonsTensDigit) {
        gMenuImages[0].spriteOffset = numBalloonsTensDigit;
        menu_element_render(0);
        gMenuImages[0].trans.x_position += 12.0f;
    }
    gMenuImages[0].spriteOffset = settings->balloonsPtr[0] % 10;
    menu_element_render(0);
    tempX = -49;
    gMenuImages[10].trans.x_position = tempX;
    gMenuImages[10].trans.y_position = 98 - y;
    menu_element_render(10);
    sprite_opaque(1);
    y += 50;
    tempX = -89;
    gMenuImages[15].trans.x_position = tempX;
    gMenuImages[15].trans.y_position = 95 - y;
    gMenuImages[15].spriteOffset = settings->wizpigAmulet;
    menu_element_render(15);
    tempX = -29;
    gMenuImages[16].trans.x_position = tempX;
    gMenuImages[16].trans.y_position = 95 - y;
    gMenuImages[16].spriteOffset = settings->ttAmulet;
    menu_element_render(16);
    for (flag = 3, numOfItem = 0, i = 0; i < 16; flag <<= 2, i++) {
        if (flag == (settings->trophies & flag)) {
            numOfItem++;
        }
    }
    y += 50;
    for (x = 20, i = 0; i < 4; i++, x += 30) {
        gMenuImages[13].trans.x_position = (x - 124);
        gMenuImages[13].trans.y_position = (95 - y);
        if (i < numOfItem) {
            gMenuImages[13].spriteOffset = 1;
        } else {
            gMenuImages[13].spriteOffset = 0;
        }
        menu_element_render(13);
    }
    for (flag = 1, i = 0, numOfItem = 0; i < 16; flag <<= 1, i++) {
        if (flag == (settings->keys & flag)) {
            numOfItem++;
        }
    }
    y += 45;
    for (x = 20, i = 0; i < 4; i++, x += 30) {
        gMenuImages[14].trans.x_position = (x - 124);
        gMenuImages[14].trans.y_position = (95 - (y));
        if (i < numOfItem) {
            gMenuImages[14].spriteOffset = 1;
        } else {
            gMenuImages[14].spriteOffset = 0;
        }
        menu_element_render(14);
    }
    cam_set_sprite_anim_mode(SPRITE_ANIM_NORMALIZED);
}
s32 trophy_race_cabinet_menu_loop(void) {
    s32 currentOption;
    s32 buttonsPressed;
    set_current_dialogue_box_coords(1, 24, 16, 184, (240 / 2));
    set_dialogue_font(1, ASSET_FONTS_FUNFONT);
    currentOption = 0;
    buttonsPressed = input_pressed(PLAYER_ONE);
    render_dialogue_text(1, -0x8000, 6, gMenuText[ASSET_MENU_TEXT_TROPHYRACE], 1, HORZ_ALIGN_CENTER);
    if (gControllersYAxisDirection[0] < 0) {
        gDialogueSubmenu++;
    } else if (gControllersYAxisDirection[0] > 0) {
        gDialogueSubmenu--;
    }
    if (gDialogueSubmenu < 0) {
        gDialogueSubmenu = 0;
    }
    if (gDialogueSubmenu > 1) {
        gDialogueSubmenu = 1;
    }
    set_option_text_colour(gDialogueSubmenu == 0);
    render_dialogue_text(1, -0x8000, 30, gMenuText[ASSET_MENU_TEXT_ENTERTROPHYRACE], 1,
                         HORZ_ALIGN_CENTER);
    set_option_text_colour(gDialogueSubmenu == 1);
    render_dialogue_text(1, -0x8000, 50, gMenuText[ASSET_MENU_TEXT_EXIT], 1, HORZ_ALIGN_CENTER);
    if (buttonsPressed & 0x8000) {
        currentOption = gDialogueSubmenu + 1;
    }
    if (buttonsPressed & 0x4000) {
        currentOption = 2;
    }
    return currentOption;
}
void dialogue_open_stub(void) {
}
void dialogue_close_stub(void) {
}
f32 dialogue_ortho( DialogueBoxBackground *textbox, Gfx **dList, Mtx **mat, Vertex **verts) {
    sMenuCurrDisplayList = *dList;
    sMenuCurrHudMat = *mat;
    sMenuCurrHudVerts = *verts;
    mtx_ortho(&sMenuCurrDisplayList, &sMenuCurrHudMat);
    if (gGameStatusVisible && sCurrentMenuID == MENU_UNUSED_4) {
        dialogue_tt_gamestatus();
    }
    *dList = sMenuCurrDisplayList;
    *mat = sMenuCurrHudMat;
    *verts = sMenuCurrHudVerts;
    return 1;
}
u64 *get_eeprom_settings_pointer(void) {
    return &sEepromSettings;
}
s32 set_eeprom_settings_value(u64 valueToSet) {
    sEepromSettings |= valueToSet;
    mark_write_eeprom_settings();
    return 1;
}
s32 unset_eeprom_settings_value(u64 valueToUnset) {
    sEepromSettings &= ~valueToUnset;
    mark_write_eeprom_settings();
    return 1;
}
u64 get_eeprom_settings(void) {
    return sEepromSettings;
}
s32 get_language(void) {
    s32 language = LANGUAGE_ENGLISH;
    switch (sEepromSettings & 0xC) {
        case 4:
            language = LANGUAGE_GERMAN;
            break;
        case 8:
            language = LANGUAGE_FRENCH;
            break;
        case 12:
            language = LANGUAGE_JAPANESE;
            break;
    }
    return language;
}
void set_language(s32 language) {
    u64 langFlag = 0;
    switch (language) {
        case LANGUAGE_GERMAN:
            langFlag = 4;
            break;
        case LANGUAGE_FRENCH:
            langFlag = 8;
            break;
        case LANGUAGE_JAPANESE:
            langFlag = 12;
            break;
    }
    sEepromSettings &= ~0xC;
    sEepromSettings |= langFlag;
    load_menu_text(language);
    mark_write_eeprom_settings();
}
s32 is_adventure_two_unlocked(void) {
    return sEepromSettings & 1;
}
s32 is_in_adventure_two(void) {
    return gIsInAdventureTwo;
}
s32 is_in_two_player_adventure(void) {
    if (is_in_tracks_mode()) {
        return 0;
    }
    return gIsInTwoPlayerAdventure;
}
s32 is_tt_unlocked(void) {
    return gActiveMagicCodes & CHEAT_CONTROL_TT;
}
s32 is_drumstick_unlocked(void) {
    return gActiveMagicCodes & CHEAT_CONTROL_DRUMSTICK;
}
