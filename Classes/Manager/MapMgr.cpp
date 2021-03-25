//
//  MapMgr.cpp
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#include "MapMgr.h"

#include "KeyMgr.h"


#include "Blocks.h"
#include "Blocks_J.h"
#include "Blocks_I.h"
#include "Blocks_S.h"
#include "Blocks_T.h"
#include "Blocks_O.h"

USING_NS_CC;

MapMgr* MapMgr::pInstance_ = nullptr;

MapMgr::MapMgr()
    : pCurBlocks_(nullptr)
{
    
}

MapMgr::~MapMgr()
{
    //블럭들 관련해서 해야하나?
}

MapMgr*  MapMgr::getInstance()
{
    if(nullptr == pInstance_)
    {
        pInstance_ = new(std::nothrow) MapMgr;
        pInstance_->init();
    }
    
    return pInstance_;
}

void MapMgr::destroyInstance()
{
    if(nullptr != pInstance_)
    {
        delete pInstance_;
        pInstance_ = nullptr;
    }
}

void MapMgr::init()
{
    for(int i = 0; i < MAP_HEIGHT; ++i)
    {
        gridMapBlocks_[i].resize(MAP_WIDTH, nullptr);
        isExisting_[i].resize(MAP_WIDTH, false);
    }

}

void MapMgr::setIsDrop(bool isDrop)
{
    if(nullptr == pCurBlocks_)
        return;
    
    pCurBlocks_->setIsDrop(isDrop);
}

void MapMgr::makeNewBlocks(int blockType)
{
    if(nullptr != pCurBlocks_)
        return;
    
    Blocks* pBlocks = nullptr;
    switch (blockType)
    {
        case BLOCKTYPE::J:
        {
            pBlocks = Blocks_J::create(Color3B::ORANGE);
            break;
        }
        case BLOCKTYPE::I:
        {
            pBlocks = Blocks_I::create(Color3B::YELLOW);
            break;
        }
        case BLOCKTYPE::S:
        {
            pBlocks = Blocks_S::create(Color3B::WHITE);
            break;
        }
        case BLOCKTYPE::T:
        {
            pBlocks = Blocks_T::create(Color3B::GRAY);
            break;
        }
        case BLOCKTYPE::O:
        {
            pBlocks = Blocks_O::create(Color3B::GREEN);
            break;
        }
        default:
            break;
    }
    
    pCurBlocks_ = pBlocks;
    
    // 스프라이트를 mapLayer에 자식으로 추가
    Scene* pCurScene = Director::getInstance()->getRunningScene();
    Node* mapLayer = pCurScene->getChildByTag(MAPLAYER_TAG);
    
    Sprite* pSprite = nullptr;
    for(int i = 0; i < BLOCKCNT; ++i)
    {
        pSprite = pCurBlocks_->getBlockSprite(i);
        mapLayer->addChild(pSprite);
    }
}

void MapMgr::move(int dir)
{
    if(nullptr == pCurBlocks_)
        return;
    
    pCurBlocks_->move(dir);
}

void MapMgr::rotate(int keyPressedCnt)
{
    if(nullptr == pCurBlocks_)
        return;
    
    pCurBlocks_->rotate(keyPressedCnt);
}

void MapMgr::drop()
{
    if(nullptr == pCurBlocks_)
        return;
    
    pCurBlocks_->drop();
}

void MapMgr::autoMoveDown()
{
    if(nullptr == pCurBlocks_)
        return;
    
    pCurBlocks_->autoMoveDown();
}

bool MapMgr::checkUnderSomething(Block* block[])
{
    // 일단, 접촉할 부분을 미리 골라내
    newBlockList_.clear();
    
    for(int i = 0; i < BLOCKCNT; ++i)
    {
        int exceptCnt = 0;
        for(int j = i; j< BLOCKCNT; ++j)
        {
            // 자기 자신인 경우
            if(block[i]->x_ == block[j]->x_
               && block[i]->y_ == block[j]->y_)
            {
                continue;
            }

            // 같은 열이 아닌 경우
            if(block[i]->x_ != block[j]->x_)
            {
                continue;
            }

            // 자신 아래에 블럭이 있는 경우
            if((block[i]->y_ - BLOCKCNT) == block[j]->y_)
            {
                exceptCnt += 1;
            }
        }
        
        if(0 == exceptCnt)
         {
             // 자신 아래에 블럭이 없는 경우!
             newBlockList_.emplace_back(block[i]);
         }
    }
    
    // 접촉 가능성 있는 블록만 for문을 통해, 맵 아래에 접촉될 블럭이 있는지를 조사한다.
    for(auto& newBlock : newBlockList_)
    {
        int colIndex = newBlock->x_ / BLOCKSIZE - 1;
        
        for(int i = 0; i < MAP_HEIGHT; ++i)
        {
            if(true == isExisting_[i][colIndex]) // 맵 아래에 블록이 있으면
            {
                return true;
            }
        }
    }
    
    return false;
}

void MapMgr::getMaxRowOfUnderBlock(int* dist)
{
    std::list<int> underBlock;
    for(auto& newBlock : newBlockList_)
    {
        int colIndex = newBlock->x_ / BLOCKSIZE - 1;
        int rowIndex = newBlock->y_ / BLOCKSIZE;
        
        for(int i = 0; i < MAP_HEIGHT; ++i)
        {
            if(false == isExisting_[i][colIndex])
                continue;
            
            int dist = rowIndex - i;
            underBlock.emplace_back(dist);
        }
    }
    
    underBlock.sort();
    *dist = underBlock.front() * BLOCKSIZE;
}

bool MapMgr::checkCanChange(float x, float y)
{
    int colIndex = x / BLOCKSIZE - 1;
    int rowIndex = y / BLOCKSIZE;
    
    if(true == isExisting_[rowIndex][colIndex])
    {
        return false;
    }
    
    return true;
}

void MapMgr::includeGridMapBlocks(cocos2d::Sprite* sprite)
{
    sprite->retain();
    
    Vec2 pos = sprite->getPosition();
    int rowIndex = pos.y / BLOCKSIZE;
    int colIndex = pos.x / BLOCKSIZE - 1;
    
    gridMapBlocks_[rowIndex][colIndex] = sprite;
    
}

void MapMgr::checkIsExisting(cocos2d::Sprite* sprite, bool isExist)
{
    Vec2 pos = sprite->getPosition();
    int rowIndex = pos.y / BLOCKSIZE;
    int colIndex = pos.x / BLOCKSIZE - 1;
    
    isExisting_[rowIndex][colIndex] = isExist;
}
