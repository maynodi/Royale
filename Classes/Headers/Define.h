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
#define BLOCKSPRITE_TAG 3
#define BLOCKPREVIEW_TAG 4
#define NEXTBLOCK_TAG 5
#define ITEMSPRITE_TAG 6
#define SELECTBOX_TAG 7

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

#define BLOCKLAYER_WIDTH 6
#define BLOCKLAYER_HEIGHT 3

#define BLOCKLAYER_SIZE_X (BLOCKLAYER_WIDTH + 2) * BLOCKSIZE
#define BLOCKLAYER_SIZE_Y (BLOCKLAYER_HEIGHT + 2) * BLOCKSIZE

#define BLOCKLAYER_POS_X (BLOCKSIZE + MAPLAYER_SIZE_X) + BLOCKSIZE
#define BLOCKLAYER_POS_Y (BLOCKSIZE + MAPLAYER_SIZE_Y) - (BLOCKLAYER_SIZE_Y * 2)

#define HALF_BLOCKLAYER_WIDTH (BLOCKLAYER_WIDTH / 2)

#define POS_X 0
#define POS_Y 1

#define DELETELINE_SCORE 100

enum DIR {DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN};
enum BLOCKTYPE { J, I, S, T, O, END};
enum GAMESTATE {PLAY, OVER, WIN};
