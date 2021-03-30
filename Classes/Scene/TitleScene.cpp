#include "TitleScene.h"
#include "SimpleAudioEngine.h"
#include "TitleLobbyLayer.h"

USING_NS_CC;

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

TitleScene* TitleScene::create()
{
    TitleScene* pRet = new(std::nothrow) TitleScene;
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

bool TitleScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    Layer* pLayer = TitleLobbyLayer::create();
    this->addChild(pLayer);
    
    return true;
}
