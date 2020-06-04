#pragma once

//MAIN
#define SCREEN_WIDTH 272
#define SCREEN_HEIGHT 272
#define HUD_HEIGHT 50
#define MAP_HUD	61
#define MAX_FRAME_RATE 120
#define STATE_DESTROYED 99
#define TILESET_WIDTH 16
#define ENEMY_STATE_DESTROY	0

//CAM SCENE
#define SCENE2_SIMON_SWITCH_Y 260
#define CAMERA_SCENE2_X	16*16
#define CAMERA_SWITCHSCENE2_X 400
#define CAMERA_SWITCHSCENE2_Y 200
#define CAMERA_SWITCH_SCENE2_1_Y 10
#define SCENE3_SIMON_SWITCH_Y 250

//OBJECTS
#define ID_SIMON 1
#define ID_ZOMBIE 2
#define ID_SPEARKNIGHT 3
#define ID_BAT 4

//OBJECTS NO MOVE
#define ID_GROUND -1
#define ID_STAIR -2
#define ID_AREAACTIVE -3
#define ID_AREASWITCHCAM -4
#define ID_TORCH 11
#define ID_PORTAL 12
#define ID_CANDLE 13
#define ID_BRIDGE 14

//ITEMS
#define ID_SMALLHEART 20
#define ID_HEART 21
#define ID_WHIPUPGRADE	22
#define ID_DAGGERITEM 23
#define ID_BOOMERANGITEM 24
#define ID_AXEITEM 25
#define ID_MONEYBAG 26
#define ID_MONEYBAGWHITE 27
#define ID_MONEYBAGBLUE 28
#define ID_HOLYWATERITEM 29


//WEAPON
#define ID_WHIP	30
#define ID_DAGGER 31
#define ID_BOOMERANG 32
#define ID_AXE 33
#define ID_HOLYWATER 34

//EFFECT
#define TIME_FIRE	150
#define TIME_FIRE_ENEMY 150
#define ANI_DESTROY 901
#define WEAPON_SIMON_SIT_ATTACK 7.0f

//SCENE
#define SCENE_1 1
#define SCENE_2 2
#define SCENE_3 3
#define SCENE_4 4

#define KEY_1 1
#define KEY_2 2
#define KEY_3 3
#define KEY_4 4
#define KEY_5 5

#define RESET_SCENE_3_X
//RESET
#define START_X 0
#define START_Y 180

//MATH
#define PI 3.14

//STAIR
#define STAIR_SETBBOX_LEFT 10
#define STAIR_SETBBOX_RIGHT 12
#define STAIR_ANCHOR_SIMON 5


//MONEYBAG
#define MONEYBAG_GRAVITY			0.0005f
#define MONEYBAG_BBOX_WIDTH		13
#define MONEYBAG_BBOX_HEIGHT		10


//ID_ANI_WEAPON
#define ID_ANI_DAGGER_LEFT 1001
#define ID_ANI_DAGGER_RIGHT 703
#define ID_ANI_BOOMERANG_LEFT 1011
#define ID_ANI_BOOMERANG_RIGHT 1012
#define ID_ANI_AXE_RIGHT 1021
#define ID_ANI_AXE_LEFT 1022