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
   
}

void MapMgr::setIsDrop(bool isDrop)
{
    pCurBlocks->setIsDrop(isDrop);
}

Blocks* MapMgr::makeNewBlocks()
{
    // enum으로 분기를 태워야되남...
    Blocks* pBlocks = Blocks_J::create();
    pCurBlocks = pBlocks;
    
    return pCurBlocks;
}

void MapMgr::move(int dir)
{
    pCurBlocks->move(dir);
}

void MapMgr::rotate(int dir, int keyPressedCnt)
{
    pCurBlocks->rotate(dir, keyPressedCnt);
}

void MapMgr::drop()
{
    pCurBlocks->drop();
}
