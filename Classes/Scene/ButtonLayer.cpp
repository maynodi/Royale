#include "ButtonLayer.h"

#include "libjson.h"
#include <fstream>
#include <algorithm>
#include "Define.h"

#include "TitleScene.h"
#include "ToolMainLayer.h"

USING_NS_CC;

ButtonLayer::ButtonLayer()
: menuFontSize_(30)
{
}

ButtonLayer::~ButtonLayer()
{
}

ButtonLayer* ButtonLayer::create()
{
    ButtonLayer* pRet = new(std::nothrow) ButtonLayer;
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

bool ButtonLayer::init()
{
    if(false == LayerColor::initWithColor(Color4B::WHITE))
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    this->setContentSize(Size(visibleSize.width/2 , visibleSize.height));
    this->setAnchorPoint(Vec2(0, 0));
    this->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y));
    
    Label* saveLabel = Label::createWithTTF("Save", FONTPATH, menuFontSize_);
    Label* GoToMenuLabel = Label::createWithTTF("Go to Menu", FONTPATH, menuFontSize_);
    
    MenuItemLabel* saveMenuItem = MenuItemLabel::create(saveLabel, CC_CALLBACK_1(ButtonLayer::clickSaveButton,this));
    MenuItemLabel* GoToMenuItem = MenuItemLabel::create(GoToMenuLabel, CC_CALLBACK_1(ButtonLayer::clickGoToMenuButton,this));
    
    auto menu = Menu::create(GoToMenuItem, saveMenuItem, NULL);
    menu->setPosition(Vec2(150.f, 400.f));
    menu->alignItemsVertically();
    menu->alignItemsVerticallyWithPadding(400.f);
    menu->setColor(Color3B::BLACK);
    
    this->addChild(menu);
    return true;
}

void ButtonLayer::clickSaveButton(Ref* pSender)
{
    // 씬에 저장된 블럭의 위치를 저장
    // 저장할 때 blocksize만큼 나눠서 저장해야지..
    
    Scene* pToolScene = Director::getInstance()->getRunningScene();
    ToolMainLayer* pMainLayer = (ToolMainLayer*)pToolScene->getChildByTag(TOOL_MAIN_TAG);
    
    Vector<Node*> children = pToolScene->getChildren();
    int specialBlockCnt = pMainLayer->getBlockCnt();
    
    std::vector<cocos2d::Vec2> posVec;
    posVec.reserve(specialBlockCnt);
    
    for(auto& child : children)
    {
        if(TOOL_BLOCK_TAG == child->getTag())
        {
            Vec2 pos = child->getPosition();
            pos.x /= BLOCKSIZE;
            pos.y /= BLOCKSIZE;
            
            posVec.emplace_back(pos);
        }
    }
    
    Vector<Node*>::iterator iter = find_if(children.begin(), children.end(), [&](Node* node){
        return (TOOL_BLOCK_TAG == node->getTag());
    });
    
    // 데이터없으면 저장하지마
    if(children.end() == iter)
        return;
    
    // 파일저장
    JSONNode node;
    for(int i = 0; i < posVec.size(); ++i)
    {
        node.push_back(JSONNode("x" + std::to_string(i), posVec[i].x));
        node.push_back(JSONNode("y"+ std::to_string(i), posVec[i].y));
    }
    
    node.push_back(JSONNode("blockCnt", specialBlockCnt));
    
    std::fstream file;
    std::string filePath = FileUtils::getInstance()->getWritablePath() + "blockData.json";
    
    file.open (filePath.c_str (), std::ios::out);
    file<<node.write_formatted();
    file.close ();
    
}

void ButtonLayer::clickGoToMenuButton(Ref* pSender)
{
    Scene* pScene = TitleScene::create();
    Director::getInstance()->replaceScene(pScene);
}
