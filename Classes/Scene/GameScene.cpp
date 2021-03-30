#include "GameScene.h"

#include "Define.h"
#include "SimpleAudioEngine.h"

#include "MapMgr.h"
#include "KeyMgr.h"

#include "MapLayer.h"
#include "BlockLayer.h"
#include "UILayer.h"

USING_NS_CC;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
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
