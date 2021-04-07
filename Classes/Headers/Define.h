//
//  Define.h
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#pragma once

#define FONTPATH "fonts/arial.ttf"

#define MAPLAYER_TAG 0
#define BLOCKLAYER_TAG 1
#define UILAYER_TAG 2
#define HOLDLAYER_TAG 3
#define BLOCKSPRITE_TAG 4
#define BLOCKPREVIEW_TAG 5
#define NEXTBLOCK_TAG 6
#define ITEMSPRITE_TAG 7
#define SELECTBOX_TAG 8
#define TWISTSPRITE_TAG 9
#define SMOGSPRITE_TAG 10

#define TOOL_MAIN_TAG 0
#define TOOL_BUTTON_TAG 1
#define TOOL_BLOCK_TAG 2


#define BESTSCORE_TAG 0
#define SCORE_TAG 1
#define LEVEL_TAG 2
#define LINECOUNT_TAG 3
#define ITEMCOUNT_TAG 4

#define KEY cocos2d::EventKeyboard::KeyCode

#define MAP_WIDTH 15
#define MAP_HEIGHT 30

#define BLOCKSIZE 20
#define BLOCKCNT 4

#define MAPLAYER_SIZE_X (MAP_WIDTH + 2) * BLOCKSIZE
#define MAPLAYER_SIZE_Y (MAP_HEIGHT + 1) * BLOCKSIZE

#define MIN_HEIGHT 0                            // mapLayer pos가 (BLOCKSIZE, BLOCKSIZE)로 세팅됨
#define MAX_HEIGHT (BLOCKSIZE)*(MAP_HEIGHT)     // Block의 sprite는 mapLayer 기준으로 상대적인 값을 가짐
#define MIN_WIDTH BLOCKSIZE
#define MAX_WIDTH (BLOCKSIZE)*(MAP_WIDTH)

#define HALF_WIDTH (MAP_WIDTH / 2)

#define BLOCKLAYER_WIDTH 8
#define BLOCKLAYER_HEIGHT 4

#define BLOCKLAYER_SIZE_X (BLOCKLAYER_WIDTH + 2) * BLOCKSIZE
#define BLOCKLAYER_SIZE_Y (BLOCKLAYER_HEIGHT + 2) * BLOCKSIZE

#define BLOCKLAYER_POS_X (BLOCKSIZE + MAPLAYER_SIZE_X) + BLOCKSIZE
#define BLOCKLAYER_POS_Y (BLOCKSIZE + MAPLAYER_SIZE_Y) - (BLOCKLAYER_SIZE_Y * 1.5f)

#define HALF_BLOCKLAYER_WIDTH (BLOCKLAYER_WIDTH / 2)

#define HOLDLAYER_POS_Y (BLOCKSIZE + MAPLAYER_SIZE_Y) - (BLOCKLAYER_SIZE_Y * 3)

#define POS_X 0
#define POS_Y 1

#define DELETELINE_SCORE 100

#define SELECTBOX_COLOR cocos2d::Color3B(153, 102, 153) //팥
#define BLOCK_J_COLOR cocos2d::Color3B(153, 204, 255)  //파랑
#define BLOCK_I_COLOR cocos2d::Color3B(255, 204, 102)  //노랑
#define BLOCK_S_COLOR cocos2d::Color3B(255, 153, 204)  //연분홍
#define BLOCK_T_COLOR cocos2d::Color3B(204, 153, 255)  //연보라
#define BLOCK_O_COLOR cocos2d::Color3B(204, 255, 153)  //연두

enum DIR {DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN};
enum BLOCKTYPE { J, I, S, T, O, END};
enum GAMESTATE {PLAY, OVER, WIN};
enum ZORDER {EXPLOSION = 10, SMOG};
