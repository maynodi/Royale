//
//  MapLayer.cpp
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#include "MapLayer.h"

#include "MapMgr.h"
#include "KeyMgr.h"
#include "DataMgr.h"

#include "SimpleAudioEngine.h"
#include "Define.h"

#include "Blocks.h"

USING_NS_CC;

MapLayer::MapLayer()
    : time_(1.f)
    , isChange_(false)
    , selectBox_(nullptr)
{
}

MapLayer::~MapLayer()
{
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
    
    this->setContentSize(Size(MAPLAYER_SIZE_X, MAPLAYER_SIZE_Y));
    this->setPosition(Vec2(BLOCKSIZE, BLOCKSIZE));
    
    KeyMgr* pKeyMgr = KeyMgr::getInstance();
    this->addChild(pKeyMgr);
    
    // map grid
    DrawGridMap();
    
    // 소리
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("tetrisBGM.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.3f);
    
    return true;
}

void MapLayer::onEnter()
{
    Layer::onEnter();
    
    // 맨 처음 블럭 생성
    MapMgr::getInstance()->makeNewBlocks();
    
    schedule(schedule_selector(MapLayer::autoMoveDown), time_);
    this->scheduleUpdate();
}

void MapLayer::update(float dt)
{
    if(GAMESTATE::OVER == MapMgr::getInstance()->getGameState())
    {
        setGameOver();
    }
    
    MapMgr::getInstance()->update();
    if(true == isChange_)
    {
        changeSpeed();
    }
}

void MapLayer::setGameOver()
{
    // 소리
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("gameover.wav");
    
    unscheduleAllCallbacks();
    
    Vector<Node*> children = this->getChildren();
    for(auto& child : children)
    {
        if(BLOCKSPRITE_TAG == child->getTag())
        {
            child->setOpacity(125);
        }
    }
    
    Label* label1 = Label::createWithTTF("GAME", FONTPATH, 60);
    label1->setPosition(Vec2(MAX_WIDTH/2, MAX_HEIGHT/2 + 60));
    label1->setTextColor(Color4B::WHITE);
    this->addChild(label1);
    
    Label* label2 = Label::createWithTTF("OVER", FONTPATH, 60);
    label2->setPosition(Vec2(MAX_WIDTH/2, MAX_HEIGHT/2));
    label2->setTextColor(Color4B::WHITE);
    this->addChild(label2);
}

void MapLayer::changeSpeed()
{
    int level = DataMgr::getInstance()->getLevel();
    float time = time_ / level;
    
    unschedule(schedule_selector(MapLayer::autoMoveDown));
    schedule(schedule_selector(MapLayer::autoMoveDown), time);
    
    isChange_ = false;
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
    
    pNode->setOpacity(125);
    this->addChild(pNode);
}

void MapLayer::createSelectBox()
{
    selectBox_ = Sprite::create("white.png");
    selectBox_->setScale(16.f, 1.2f);
    selectBox_->setAnchorPoint(Vec2(0, 0));
    selectBox_->setPosition(Vec2(0, 0));
    
    selectBox_->setColor(SELECTBOX_COLOR);
    selectBox_->setOpacity(200);
    
    selectBox_->setTag(SELECTBOX_TAG);
    
    this->addChild(selectBox_);
}

void MapLayer::autoMoveDown(float dt)
{
    MapMgr::getInstance()->autoMoveDown();
}
