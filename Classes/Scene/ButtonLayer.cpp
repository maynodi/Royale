#include "ButtonLayer.h"

#include "Define.h"

#include "TitleScene.h"

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
    Vector<Node*> children = pToolScene->getChildren();
    int Size = children.size();
    
    std::vector<cocos2d::Vec2> posVec;
    posVec.reserve(Size - 2); // toolmainlayer, buttonlayer 제외
    
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
    
    // 파일저장
    
    
}

void ButtonLayer::clickGoToMenuButton(Ref* pSender)
{
    Scene* pScene = TitleScene::create();
    Director::getInstance()->replaceScene(pScene);
}
