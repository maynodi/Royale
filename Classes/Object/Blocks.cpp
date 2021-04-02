//
//  Block.cpp
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#include "Blocks.h"

#include "KeyMgr.h"
#include "MapMgr.h"

#include "SimpleAudioEngine.h"
#include <algorithm>

USING_NS_CC;

Blocks::Blocks()
    : isDrop_(false)
    , dist_(0)
{
    memset(blocks_, 0, sizeof(blocks_[0]) * BLOCKCNT);
    PreviewBlockDistVec_.reserve(BLOCKCNT);
}

Blocks::~Blocks()
{
    MapMgr::getInstance()->setNullCurBlocks();
    KeyMgr::getInstance()->setZeroUpKeyPressedCnt();
    
    for(auto& block : blocks_)
    {
        block->pSprite_->removeAllChildrenWithCleanup(true);
        //block->pSprite_->release();
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

    // preview block
    if(DIR_DOWN == dir)
    {
        for(auto& block : blocks_)
        {
            Node* previewNode = block->pSprite_->getChildByTag(BLOCKPREVIEW_TAG);
            float posY = previewNode->getPositionY();
            previewNode->setPositionY(posY + BLOCKSIZE);
        }
    }
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
                newPos = curPos + Vec2(-BLOCKSIZE, 0);
                break;
            case DIR_RIGHT:
                newPos = curPos + Vec2(BLOCKSIZE, 0);
                break;
            case DIR_DOWN:
                newPos = curPos + Vec2(0, -BLOCKSIZE);
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
        if(MIN_WIDTH > pos->x || MAX_WIDTH < pos->x
           || MIN_HEIGHT >= pos->y || MAX_HEIGHT <= pos->y)
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
    
    // 맵에서 안 보일 때는 스페이스바가 안 먹히게
    for(auto& block : blocks_)
    {
        if(MAX_HEIGHT <= block->y_)
        {
            isDrop_ = false;
            return;
        }
    }

    
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
        
        // 0되기 전까지는 계속 내려와야함
        for(auto& block : blocks_)
        {
            float posY = block->pSprite_->getPositionY();
            posY -= BLOCKSIZE;
            block->pSprite_->setPositionY(posY);
            block->setPosY(posY);
        }
        
        // preview draw
        setPosPreviewBlocks(dist_ - BLOCKSIZE);
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
        block->pSprite_->setPositionY(posY - BLOCKSIZE);
        block->setPosY(posY - BLOCKSIZE);
        
        PreviewBlockDistVec_.emplace_back(int(posY - BLOCKSIZE));
    }
    
    // preview draw
    int min = *min_element(PreviewBlockDistVec_.begin(), PreviewBlockDistVec_.end());
    setPosPreviewBlocks(min);
}

void Blocks::changePos(cocos2d::Vec2 variance)
{
    for(auto& block : blocks_)
    {
        Vec2 curPos = block->pSprite_->getPosition();
        PreviewBlockDistVec_.emplace_back(curPos.y);
        
        curPos += variance;
        block->pSprite_->setPosition(curPos);
        block->setPos(curPos);
    }

    checkPreviewBlocks();
}
 
void Blocks::fixBlockPos()
{
    for(auto& block : blocks_)
    {
        float posY = block->pSprite_->getPositionY();
        
        block->pSprite_->setPositionY(posY);
        block->setPosY(posY);
        
        MapMgr::getInstance()->includeGridMapBlocks(block->pSprite_);
        MapMgr::getInstance()->checkIsExisting(block->pSprite_, true);
    }
    
    //소리
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("drop.mp3");
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
            
            // 맵 안에 들어오면 보여라!
            if(MAX_HEIGHT > posY - BLOCKSIZE)
            {
                block->pSprite_->setVisible(true);
            }
        }
        
        // preview draw
        setPosPreviewBlocks(dist_ - BLOCKSIZE);
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
           
            PreviewBlockDistVec_.emplace_back(int(posY - BLOCKSIZE));
            
            // 맵 안에 들어오면 보여라!
            if(MAX_HEIGHT >= posY)
            {
                block->pSprite_->setVisible(true);
            }
        }
        
        // preview draw
        int min = *min_element(PreviewBlockDistVec_.begin(), PreviewBlockDistVec_.end());
        setPosPreviewBlocks(min);
    }
}

void Blocks::checkPreviewBlocks()
{
     // preview draw
    if(true == MapMgr::getInstance()->checkUnderSomething(blocks_))
    {
        MapMgr::getInstance()->getMaxRowOfUnderBlock(&dist_);
        setPosPreviewBlocks(dist_ - BLOCKSIZE);
    }
    else
    {
        if(true == PreviewBlockDistVec_.empty())
            return;
        
        int min = *min_element(PreviewBlockDistVec_.begin(), PreviewBlockDistVec_.end());
        setPosPreviewBlocks(min);
        
       PreviewBlockDistVec_.clear();
       PreviewBlockDistVec_.shrink_to_fit();
    }
}

void Blocks::setPosPreviewBlocks(int dist)
{
    for(int i = 0; i < BLOCKCNT; ++i)
    {
        Node* previewNode = blocks_[i]->pSprite_->getChildByTag(BLOCKPREVIEW_TAG);
        previewNode->setPositionY(-1 * dist);
    }
}

void Blocks::setRotatePreviewBlocks()
{
    for(auto& block : blocks_)
    {
        Node* previewNode = block->pSprite_->getChildByTag(BLOCKPREVIEW_TAG);
        float posY = previewNode->getPositionY();
        
        previewNode->setPositionY(posY + BLOCKSIZE);
    }
}

bool Blocks::checkGameOverWhenCreate()
{
    if(true == MapMgr::getInstance()->checkUnderSomething(blocks_))
    {
        MapMgr::getInstance()->getMaxRowOfUnderBlock(&dist_);
        if(BLOCKSIZE >= dist_)
            return true;
    }
    
    return false;
}
