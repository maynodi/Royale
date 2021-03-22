//
//  Block.cpp
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#include "Blocks.h"

#include "KeyMgr.h"

#include "Define.h"

USING_NS_CC;

Blocks::Blocks()
{
}

Blocks::~Blocks()
{    
}

void Blocks::move()
{
//    bool isLeft = KeyMgr::getInstance()->getIsPressed(KEY::KEY_LEFT_ARROW);
//    bool isRight = KeyMgr::getInstance()->getIsPressed(KEY::KEY_RIGHT_ARROW);
//    bool isUp= KeyMgr::getInstance()->getIsPressed(KEY::KEY_UP_ARROW);
//    bool isDown = KeyMgr::getInstance()->getIsPressed(KEY::KEY_DOWN_ARROW);
//
//    Vec2 posVariance = {};
//    if(true == isLeft)
//    {
//        posVariance = Vec2(-1, 0);
//    }
//    else if(true == isRight)
//    {
//        posVariance = Vec2(1, 0);
//    }
//    else if(true == isUp)
//    {
//        //회전
//    }
//    else if(true == isDown)
//    {
//        posVariance = Vec2(0, -1);
//    }
//
//    posVariance *= BLOCKSIZE;
//    for(int i = 0; i < BLOCKCNT; ++i)
//    {
//        Vec2 curPos = blocks_[i]->pSprite_->getPosition();
//        Vec2 newPos = Vec2(curPos.x + posVariance.x, curPos.y + posVariance.y);
//
//        blocks_[i]->pSprite_->setPosition(newPos);
//    }
    
}
