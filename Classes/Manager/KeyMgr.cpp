//
//  KeyMgr.cpp
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#include "KeyMgr.h"

USING_NS_CC;

KeyMgr* KeyMgr::pInstance_ = nullptr;

KeyMgr::KeyMgr()
    : pListner_(nullptr)
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
        pInstance_->autorelease();
        pInstance_->init();
    }
    
    return pInstance_;
}

void KeyMgr::destroyInstance()
{
    if(nullptr != pInstance_)
    {
        delete pInstance_;
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

void KeyMgr::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    keyMap_[keyCode] = true;
}

void KeyMgr::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    keyMap_[keyCode] = false;
}
