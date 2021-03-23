//
//  MapMgr.cpp
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#include "MapMgr.h"

#include "Blocks.h"
#include "Blocks_J.h"

USING_NS_CC;

MapMgr* MapMgr::pInstance_ = nullptr;

MapMgr::MapMgr()
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

Blocks* MapMgr::makeNewBlocks()
{
    // enum으로 분기를 태워야되남...
    Blocks* pBlocks = Blocks_J::create();
    pCurBlocks_ = pBlocks;
    
    return pCurBlocks_;
}

void MapMgr::move(int dir)
{
    if(nullptr == pCurBlocks_)
        return;
    
    pCurBlocks_->move(dir);
}

void MapMgr::rotate(int dir, int keyPressedCnt)
{
    if(nullptr == pCurBlocks_)
        return;
    
    pCurBlocks_->rotate(dir, keyPressedCnt);
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

void MapMgr::includeGridMapBlocks(cocos2d::Sprite* sprite)
{
    sprite->retain();
    
    Vec2 pos = sprite->getPosition();
    int rowIndex = pos.y / BLOCKSIZE - 1;
    int colIndex = pos.x / BLOCKSIZE - 1;
    
    gridMapBlocks_[rowIndex][colIndex] = sprite;
    
}
