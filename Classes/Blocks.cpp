//
//  Block.cpp
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#include "Blocks.h"

#include "KeyMgr.h"
#include "MapMgr.h"

USING_NS_CC;

Blocks::Blocks()
    : isDrop_(false)
    , dist_(0)
{
    memset(blocks_, 0, sizeof(blocks_[0]) * BLOCKCNT);
}

Blocks::~Blocks()
{
    MapMgr::getInstance()->setNullCurBlocks();
    KeyMgr::getInstance()->setZeroUpKeyPressedCnt();
    
    for(auto& block : blocks_)
    {
        block->pSprite_->release();
    }
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
    changePos(posVariance);
}

bool Blocks::checkLimitedPos(int dir)
{
    for(auto& block : blocks_)
    {
        Vec2 curPos = block->pSprite_->getPosition();
        
        // 양 옆이 벽
        if((DIR_LEFT == dir && MIN_WIDTH >= curPos.x)
           || (DIR_RIGHT == dir && MAX_WIDTH <= curPos.x)
           || (DIR_DOWN == dir && MIN_HEIGHT >= curPos.y))
        {
            changePos();
            return true;
        }
        
        // 양 옆 블록
        cocos2d::Vec2 newPos = {};
        switch (dir) {
            case DIR_LEFT:
                newPos = curPos + Vec2(-1, 0);
                break;
            case DIR_RIGHT:
                newPos = curPos + Vec2(1, 0);
                break;
            case DIR_DOWN:
                newPos = curPos + Vec2(0, -1);
                break;
            default:
                break;
        }
        
        if(false == MapMgr::getInstance()->checkCanChange(newPos.x, newPos.y))
        {
            changePos();
            return true;
        }
        
    }
    
    return false;
}

bool Blocks::checkLimitedRotate(cocos2d::Vec2* pos)
{
    for(int i = 0; i < BLOCKCNT; ++i)
    {
        if(MIN_WIDTH >= pos->x || MAX_WIDTH <= pos->x || MIN_HEIGHT >= pos->y)
        {
            KeyMgr::getInstance()->minusUpKeyPressedCnt();
            return true;
        }
        
        if(false == MapMgr::getInstance()->checkCanChange(pos->x, pos->y))
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
    
    
    // 2개 경우로 나눠야함
    if(true == MapMgr::getInstance()->checkUnderSomething(blocks_))
    {
        // 1. 아래 블록이 있는 경우   ========================================
        
       // 블럭 아래에 한개라도 블럭이 있다면 여기에 도착..
       // 상황에 맞게 세팅해줘야되 포스를
        
        MapMgr::getInstance()->getMaxRowOfUnderBlock(&dist_);
        
        dist_ -= BLOCKSIZE;
        if(0 >= dist_)
        {
            fixBlockPos();
            isDrop_ = false;
            delete this;
            return;
        }
        
        // ** 공통된 부분 **
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
    else
    {
        // 2. 아래 아무것도 없는 경우  ========================================
        doWorkWhenIsUnderNothing();        
    }
}

void Blocks::doWorkWhenIsUnderNothing()
{
    // y가 하나라도 0보다 작거나 같아지면 스돕 -> 그 위치에 박제
    // 포문돈다?
    for(auto& block : blocks_)
    {
        float posY = block->pSprite_->getPositionY();
        
        if(MIN_HEIGHT >= posY)
        {
            fixBlockPos();
            isDrop_ = false;
            delete this;
            return;
        }
    }
    
    // 0되기 전까지는 계속 내려와야함
    for(auto& block : blocks_)
     {
         float posY = block->pSprite_->getPositionY();
         posY -= BLOCKSIZE;
         block->pSprite_->setPositionY(posY);
         block->setPosY(posY);
     }
}

void Blocks::changePos(cocos2d::Vec2 variance)
{
    for(auto& block : blocks_)
    {
        Vec2 curPos = block->pSprite_->getPosition();
        
        curPos += variance;
        block->pSprite_->setPosition(curPos);
        block->setPos(curPos);
    }
}
 
void Blocks::fixBlockPos()
{
    for(auto& block : blocks_)
    {
        float posY = block->pSprite_->getPositionY();
        
        //블록이 아래에 있는 경우 혹시 모르니까 냅둠 필요업승면 삭제ㄱㄱ
        //int quotientY = posY / BLOCKSIZE;
        //posY = (quotientY) * BLOCKSIZE;
        
        block->pSprite_->setPositionY(posY);
        block->setPosY(posY);
        
        MapMgr::getInstance()->includeGridMapBlocks(block->pSprite_);
        MapMgr::getInstance()->checkIsExisting(block->pSprite_, true);
    }
    
}

void Blocks::autoMoveDown()
{
    if(true == isDrop_) //스페이스바 눌르면 이 함수는 작동 안하도록!
        return;
    
    // 1. 블록 있는 경우
    if(true == MapMgr::getInstance()->checkUnderSomething(blocks_))
    {
        MapMgr::getInstance()->getMaxRowOfUnderBlock(&dist_);
        
        dist_ -= BLOCKSIZE;
        if(0 >= dist_)
        {
            fixBlockPos();
            isDrop_ = false;
            delete this;
            return;
        }
        
        for(auto& block : blocks_)
        {
            float posY = block->pSprite_->getPositionY();
            block->pSprite_->setPositionY(posY - BLOCKSIZE);
            block->setPosY(posY - BLOCKSIZE);
        }
        
    }
    else // 2. 블록 없는 경우
    {
        for(auto& block : blocks_)
        {
            float posY = block->pSprite_->getPositionY();
            
            if(MIN_HEIGHT >= posY)
            {
                fixBlockPos();
                delete this;
                return;
            }
        }
        
        for(auto& block : blocks_)
        {
            float posY = block->pSprite_->getPositionY();
            block->pSprite_->setPositionY(posY - BLOCKSIZE);
            block->setPosY(posY - BLOCKSIZE);
        }
    }
}
