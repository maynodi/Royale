#include "GameScene.h"

#include "MapMgr.h"
#include "KeyMgr.h"
#include "DataMgr.h"

#include "Define.h"
#include "SimpleAudioEngine.h"

#include "MapLayer.h"
#include "BlockLayer.h"
#include "UILayer.h"

USING_NS_CC;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
    save();
    
    MapMgr::destroyInstance();
    KeyMgr::destroyInstance();
    DataMgr::destroyInstance();
}

GameScene* GameScene::create()
{
    GameScene* pRet = new(std::nothrow) GameScene;
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

bool GameScene::init()
{
    if ( false == Scene::init() )
    {
        return false;
    }
	
    srand(time(NULL));
    
    Layer* pLayer = MapLayer::create();
    pLayer->setTag(MAPLAYER_TAG);
    this->addChild(pLayer);
    
    pLayer = UILayer::create();
    pLayer->setTag(UILAYER_TAG);
    this->addChild(pLayer);
    
    pLayer = BlockLayer::create();
    pLayer->setTag(BLOCKLAYER_TAG);
    this->addChild(pLayer);
    
    return true;
}

void GameScene::save()
{
    int bestScore = DataMgr::getInstance()->getBestScore();
    int score = DataMgr::getInstance()->getScore();
    
    if(score >= bestScore)
    {
        bestScore = score;
    }
       
    UserDefault::getInstance()->setIntegerForKey("bestScore", bestScore);
    
    UserDefault::getInstance()->flush();
}
