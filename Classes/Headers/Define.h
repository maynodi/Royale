//
//  Define.h
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#pragma once

#define FONTPATH "fonts/arial.ttf"

#define MAPLAYER_TAG 0
#define BLOCKSPRITE_TAG 1
#define BLOCKPREVIEW_TAG 2

#define KEY cocos2d::EventKeyboard::KeyCode

#define MAP_WIDTH 10
#define MAP_HEIGHT 30

#define BLOCKSIZE 20
#define BLOCKCNT 4

#define MIN_HEIGHT 0                            // mapLayer pos가 (BLOCKSIZE, BLOCKSIZE)로 세팅됨
#define MAX_HEIGHT (BLOCKSIZE)*(MAP_HEIGHT)     // Block의 sprite는 mapLayer 기준으로 상대적인 값을 가짐
#define MIN_WIDTH BLOCKSIZE
#define MAX_WIDTH (BLOCKSIZE)*(MAP_WIDTH)

#define HALF_WIDTH (MAP_WIDTH / 2)


#define POS_X 0
#define POS_Y 1

enum DIR {DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN};
enum BLOCKTYPE { J, I, S, T, O, END};
enum GAMESTATE {PLAY, OVER, WIN};
