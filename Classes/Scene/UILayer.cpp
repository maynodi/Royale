#include "UILayer.h"

#include "DataMgr.h"

#include "Define.h"

USING_NS_CC;

UILayer::UILayer()
    : fontSize_(15)
{
}

UILayer::~UILayer()
{
}

UILayer* UILayer::create()
{
    UILayer* pRet = new(std::nothrow) UILayer;
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

bool UILayer::init()
{
    if(false == LayerColor::initWithColor(Color4B::YELLOW))
    {
        return false;
    }
    
    this->setContentSize(Size(BLOCKLAYER_SIZE_X, MAPLAYER_SIZE_Y));
    this->setPosition(Vec2(BLOCKLAYER_POS_X, BLOCKSIZE));
    
    createLabel();
    
    scheduleUpdate();
    
    return true;
}

void UILayer::update(float dt)
{
    checkLabel();
}

void UILayer::createLabel()
{
    int halfSize = MAPLAYER_SIZE_Y / 2;
    
    std::vector<std::string> arrLabel = {"BestScore :", "Score :", "Level :", "Line Count :"};
    
    int posY = 0;
    Label* textLabel = nullptr;
    Label* dataLabel = nullptr;
    for(int i = 0; i < arrLabel.size(); ++i)
    {
        posY = halfSize - (100 + (30 * i));
        
        textLabel = Label::createWithTTF(arrLabel[i], FONTPATH, fontSize_);
        textLabel->setAnchorPoint(Vec2(0, 0));
        textLabel->setPosition(Vec2(BLOCKSIZE, posY));
        textLabel->setColor(Color3B::BLACK);
        
        this->addChild(textLabel);
        
        dataLabel = Label::createWithTTF("", FONTPATH, fontSize_);
        dataLabel->setAnchorPoint(Vec2(0, 0));
        dataLabel->setPosition(Vec2(BLOCKSIZE * 6, posY));
        dataLabel->setTag(i);
        dataLabel->setColor(Color3B::BLACK);
        
        this->addChild(dataLabel);
    }
}
void UILayer::checkLabel()
{
    int temp = DataMgr::getInstance()->getBestScore();
    static_cast<Label*>(getChildByTag(BESTSCORE_TAG))->setString(StringUtils::format("%d",temp));
    
    temp = DataMgr::getInstance()->getScore();
    static_cast<Label*>(getChildByTag(SCORE_TAG))->setString(StringUtils::format("%d",temp));
    
    temp = DataMgr::getInstance()->getLevel();
    static_cast<Label*>(getChildByTag(LEVEL_TAG))->setString(StringUtils::format("%d",temp));
    
    temp = DataMgr::getInstance()->getLineCnt();
    static_cast<Label*>(getChildByTag(LINECOUNT_TAG))->setString(StringUtils::format("%d",temp));
}
