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
    
    KeyMgr* pKeyMgr = KeyMgr::getInstance();
    this->addChild(pKeyMgr);
    
    //map grid
    DrawGridMap();
    
    return true;
}

void MapLayer::onEnter()
{
    Layer::onEnter();
    
    // 맨 처음 블럭 생성
    MapMgr::getInstance()->makeNewBlocks(BLOCKTYPE::S);
    
    schedule(schedule_selector(MapLayer::autoMoveDown), 1.f);
    this->scheduleUpdate();
}

void MapLayer::update(float dt)
{
    MapMgr::getInstance()->makeNewBlocks(rand() % BLOCKTYPE::END);
    MapMgr::getInstance()->drop();
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

void MapLayer::autoMoveDown(float dt)
{
    MapMgr::getInstance()->autoMoveDown();
}
