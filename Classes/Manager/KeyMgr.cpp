//
//  KeyMgr.cpp
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#include "KeyMgr.h"

#include "MapMgr.h"

USING_NS_CC;

KeyMgr* KeyMgr::pInstance_ = nullptr;

KeyMgr::KeyMgr()
    : pListner_(nullptr)
    , upKeyPressedCnt_(0)
{
    
}

KeyMgr::~KeyMgr()
{
    
}

KeyMgr*  KeyMgr::getInstance()
{
    if(nullptr == pInstance_)
    {
        pInstance_ = new(std::nothrow) KeyMgr;
        pInstance_->init();
    }
    
    return pInstance_;
}

void KeyMgr::destroyInstance()
{
    if(nullptr != pInstance_)
    {
        pInstance_->release();
        pInstance_ = nullptr;
    }
}

bool KeyMgr::init()
{
    pListner_ = EventListenerKeyboard::create();
    
    pListner_->onKeyPressed = CC_CALLBACK_2(KeyMgr::onKeyPressed,this);
    pListner_->onKeyReleased = CC_CALLBACK_2(KeyMgr::onKeyReleased,this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pListner_, this);
    
    return true;
}

void KeyMgr::onKeyPressed(KEY keyCode, cocos2d::Event* event)
{
    switch (keyCode) {
        case KEY::KEY_LEFT_ARROW:
        {
            MapMgr::getInstance()->move(DIR_LEFT);
            break;
        }
        case KEY::KEY_RIGHT_ARROW:
        {
            MapMgr::getInstance()->move(DIR_RIGHT);
            break;
        }
        case KEY::KEY_UP_ARROW: // 회전
        {
            if(3 < upKeyPressedCnt_)
            {
                upKeyPressedCnt_ = 0;
            }
            
            MapMgr::getInstance()->rotate(upKeyPressedCnt_);
            break;
        }
        case KEY::KEY_DOWN_ARROW:
        {
            MapMgr::getInstance()->move(DIR_DOWN);
            break;
        }
        case KEY::KEY_SPACE: // 쭉 내려오기
        {
            MapMgr::getInstance()->setIsDrop(true);
            break;
        }
        default:
            break;
    }
    
}

void KeyMgr::onKeyReleased(KEY keyCode, cocos2d::Event* event)
{
    switch (keyCode) {
        case KEY::KEY_UP_ARROW: // 회전
        {
            upKeyPressedCnt_ += 1;
            break;
        }
        default:
            break;
    }
}
