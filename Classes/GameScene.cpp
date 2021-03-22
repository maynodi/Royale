#include "GameScene.h"

#include "SimpleAudioEngine.h"

#include "MapLayer.h"

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
    this->addChild(pLayer);
    
    return true;
}
