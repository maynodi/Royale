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
            pBlocks = Blocks_J::create();
            break;
        }
        case BLOCKTYPE::I:
        {
            pBlocks = Blocks_I::create();
            break;
        }
        case BLOCKTYPE::S:
        {
            pBlocks = Blocks_S::create();
            break;
        }
        case BLOCKTYPE::T:
        {
            pBlocks = Blocks_T::create();
            break;
        }
        case BLOCKTYPE::O:
        {
            pBlocks = Blocks_O::create();
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
