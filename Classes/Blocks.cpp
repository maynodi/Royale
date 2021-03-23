//
//  Block.cpp
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#include "Blocks.h"

#include "KeyMgr.h"
#include "MapMgr.h"

#include "Define.h"

USING_NS_CC;

Blocks::Blocks()
    : isDrop_(false)
    , downSpeed_(4)
{
    memset(blocks_, 0, sizeof(blocks_[0]) * BLOCKCNT);
}

Blocks::~Blocks()
{
    MapMgr::getInstance()->setNullCurBlocks();
    for(auto& a : blocks_)
        a->pSprite_->release();
}

void Blocks::move(int dir)
{
    // 더 이상 못 가는 곳인가?
    if(true == checkLimitedPos(dir))
        return;
    
    Vec2 posVariance = {};
    switch (dir) {
        case DIR_LEFT:
            posVariance = Vec2(-1, 0);
            break;
        case DIR_RIGHT:
            posVariance = Vec2(1, 0);
            break;
        case DIR_DOWN:
            posVariance = Vec2(0, -1);
            break;
        default:
            break;
    }
    
    posVariance *= BLOCKSIZE;
    fixPos(posVariance);
}

bool Blocks::checkLimitedPos(int dir)
{
    for(auto& block : blocks_)
    {
        Vec2 curPos = block->pSprite_->getPosition();
        
        if((DIR_LEFT == dir && MIN_WIDTH >= curPos.x)
           || (DIR_RIGHT == dir && MAX_WIDTH <= curPos.x)
           || (DIR_DOWN == dir && MIN_HEIGHT >= curPos.y))
        {
            fixPos();
            return true;
        }
    }
    
    return false;
}

bool Blocks::checkLimintedRotate(cocos2d::Vec2* pos)
{
    for(int i = 0; i < BLOCKCNT; ++i)
    {
        if(MIN_WIDTH >= pos->x || MAX_WIDTH <= pos->x || MIN_HEIGHT >= pos->y)
        {
            KeyMgr::getInstance()->minusUpKeyPressedCnt();
            return true;
        }
     
        pos += i;
    }
    
    return false;
}

void Blocks::drop()
{
    if(false == isDrop_)
        return;
    
    // 2개로 나눠야함
    // 1. 아래 블록이 있는 경우
    
    
    
    
    
    // 2. 아래 아무것도 없는 경우
    // y가 하나라도 0보다 작거나 같아지면 스돕 -> 그 위치에 박제
    // 포문돈다?
    for(auto& block : blocks_)
    {
        float posY = block->pSprite_->getPositionY();
        
        if(MIN_HEIGHT >= posY)
        {
            fixPosY();
            isDrop_ = false;
            delete this;
            return;
        }
    }
    
    // 0되기 전까지는 계속 내려와야함
    // 계속 내려오려면 얘가 계속 업뎃타야되는데..
    // 업뎃을 돌수 있는 곳 맵레이어 , 겜신
    for(auto& block : blocks_)
     {
         float posY = block->pSprite_->getPositionY();
         posY -= BLOCKSIZE;
         block->pSprite_->setPositionY(posY);
         block->setPosY(posY);
     }
}

void Blocks::fixPos(cocos2d::Vec2 variance)
{
    for(auto& block : blocks_)
    {
        Vec2 curPos = block->pSprite_->getPosition();
        
        curPos += variance;
        block->pSprite_->setPosition(curPos);
        block->setPos(curPos);
    }
}
 
void Blocks::fixPosY()
{
    for(auto& block : blocks_)
    {
        float posY = block->pSprite_->getPositionY();
        
        int quotientY = posY / BLOCKSIZE;

        posY = (quotientY) * BLOCKSIZE;
        
        block->pSprite_->setPositionY(posY);
        block->setPosY(posY);
        
        MapMgr::getInstance()->includeGridMapBlocks(block->pSprite_);
    }
    
}

void Blocks::autoMoveDown()
{
    if(true == isDrop_) //스페이스바 눌르면 이 함수는 작동 안하도록!
        return;
    
    for(auto& block : blocks_)
    {
        float posY = block->pSprite_->getPositionY();
        
        if(MIN_HEIGHT >= posY)
        {
            fixPosY();
            delete this;
            return;
        }
    }
    
    for(auto& block : blocks_)
    {
        float posY = block->pSprite_->getPositionY();
        block->pSprite_->setPositionY(posY - (BLOCKSIZE >> downSpeed_));
        block->setPosY(posY - (BLOCKSIZE >> downSpeed_));
    }
}
