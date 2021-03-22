//
//  MapLayer.cpp
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#include "MapLayer.h"

#include "MapMgr.h"
#include "KeyMgr.h"

#include "Define.h"

#include "Blocks.h"

USING_NS_CC;

MapLayer::MapLayer()
{
    
}

MapLayer::~MapLayer()
{
    MapMgr::destroyInstance();
    KeyMgr::destroyInstance();
}

MapLayer* MapLayer::create()
{
    MapLayer* pRet = new(std::nothrow) MapLayer;
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool MapLayer::init()
{
    if(false == Layer::init())
    {
        return false;
    }
    
    this->setContentSize(Size(MAP_WIDTH * BLOCKSIZE, MAP_HEIGHT * BLOCKSIZE));
    this->setPosition(Vec2(BLOCKSIZE, BLOCKSIZE));
    
    //map grid
    DrawGridMap();
 
    //------------------------------------ 나중에 위에서 떨어지게 해야함..
    Blocks* pBlocks = MapMgr::getInstance()->makeNewBlocks();
    
    Sprite* pSprite = nullptr;
    for(int i = 0; i < BLOCKCNT; ++i)
    {
        pSprite = pBlocks->getBlockSprite(i);
            
        this->addChild(pSprite);
    }
    //------------------------------------

    
    this->scheduleUpdate();
    
    return true;
}

void MapLayer::update(float dt)
{
    MapMgr::getInstance()->move();
}

void MapLayer::DrawGridMap()
{
    DrawNode* pNode = DrawNode::create();
    
    for(int i = 0; i < MAP_WIDTH + 1; ++i)
    {
        pNode->drawLine(Vec2(i * BLOCKSIZE, 0), Vec2(i * BLOCKSIZE, MAP_HEIGHT * BLOCKSIZE), Color4F::WHITE);
    }
    
    for(int i = 0; i < MAP_HEIGHT + 1; ++i)
    {
        pNode->drawLine(Vec2(0, i * BLOCKSIZE), Vec2(MAP_WIDTH * BLOCKSIZE, i * BLOCKSIZE), Color4F::WHITE);
    }
    
    this->addChild(pNode);
}
