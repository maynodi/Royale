//
//  Blocks_J.cpp
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#include "Blocks_J.h"

#include "BlocksSetting.h"

USING_NS_CC;

Blocks_J::Blocks_J()
{
}

Blocks_J::~Blocks_J()
{
}

Blocks_J* Blocks_J::create(cocos2d::Color3B color)
{
    Blocks_J* pRet = new(std::nothrow) Blocks_J;
    if (pRet && pRet->init(color))
    {
        //pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool Blocks_J::init(cocos2d::Color3B color)
{
     //Blocks 초기화
    Block* pBlock = nullptr;
    for(int i = 0; i < BLOCKCNT; ++i)
    {
        Vec2 pos = Vec2(BLOCKSIZE * (location::J[POS_X][i] + initPos::pos[POS_X])
                        , BLOCKSIZE * (location::J[POS_Y][i] + initPos::pos[POS_Y]));
        pBlock = new Block(pos.x, pos.y);

        pBlock->pSprite_->setColor(color);
        blocks_[i] = pBlock;
    }

    blockType_ = BLOCKTYPE::J;
    
    return true;
}

void Blocks_J::rotate(int keyPressedCnt)
{
    // 2개로 나눠야함
    // 1. 아래 블록이 있는 경우
    // 얜 안나눠도 되겟는디..?
    
    
    

    // 2. 아래 아무것도 없는 경우
    // 일단 미리 회전 후의 좌표를 계산해놓고
    Vec2 newPos[BLOCKCNT] = {};
    for(int i = 0; i < BLOCKCNT; ++i)
    {
        Vec2 curPos = blocks_[i]->pSprite_->getPosition();
       
        newPos[i].x = curPos.x + BLOCKSIZE * (posVariance::J[keyPressedCnt][(i * 2)]);
        newPos[i].y = curPos.y + BLOCKSIZE * (posVariance::J[keyPressedCnt][(i * 2) + 1]);
    }

    // 회전에 제한이 걸리는 위치인가?
    if(true == checkLimitedRotate(newPos))
        return;

   for(int i = 0; i < BLOCKCNT; ++i)
   {
       blocks_[i]->pSprite_->setPosition(newPos[i]);
       blocks_[i]->setPos(newPos[i]);
   }
}
