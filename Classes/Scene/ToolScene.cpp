#include "ToolScene.h"

#include "Define.h"

#include "ToolMainLayer.h"
#include "ButtonLayer.h"

USING_NS_CC;

ToolScene::ToolScene()
{
}

ToolScene::~ToolScene()
{
}

ToolScene* ToolScene::create()
{
    ToolScene* pRet = new(std::nothrow) ToolScene;
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

bool ToolScene::init()
{
    if(false == Scene::init())
    {
        return false;
    }
    
    Layer* pLayer = nullptr;
    pLayer = ToolMainLayer::create();
    pLayer->setTag(TOOL_MAIN_TAG);
    this->addChild(pLayer);

    pLayer = ButtonLayer::create();
    pLayer->setTag(TOOL_BUTTON_TAG);
    this->addChild(pLayer);
    
    return true;
}
