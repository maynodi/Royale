//
//  KeyMgr.cpp
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#include "KeyMgr.h"

#include "MapMgr.h"

#include "MapLayer.h"

USING_NS_CC;

KeyMgr* KeyMgr::pInstance_ = nullptr;

KeyMgr::KeyMgr()
    : pListner_(nullptr)
    , upKeyPressedCnt_(0)
    , isItemKeyPressed_(false)
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
    if(true == isItemKeyPressed_)
    {
        selectBoxControl(keyCode);
    }
    else
    {
        blocksControl(keyCode);
    }
}

void KeyMgr::selectBoxControl(KEY keyCode)
{
    Scene* pScene = Director::getInstance()->getRunningScene();
    MapLayer* pLayer = (MapLayer*)pScene->getChildByTag(MAPLAYER_TAG);
    
    Node* selectBox = pLayer->getChildByTag(SELECTBOX_TAG);
    
    switch (keyCode) {
        case KEY::KEY_UP_ARROW:
        {
            int posY = selectBox->getPositionY();
            posY += BLOCKSIZE;
            
            selectBox->setPositionY(posY);
            break;
        }
        case KEY::KEY_DOWN_ARROW:
        {
            int posY = selectBox->getPositionY();
            posY -= BLOCKSIZE;
            
            selectBox->setPositionY(posY);
            break;
        }
        case KEY::KEY_C:
        {
            selectBox->removeFromParent();
            pLayer->resume();
            
            isItemKeyPressed_ = !isItemKeyPressed_;
            break;
        }
        default:
            break;
    }
}

void KeyMgr::blocksControl(KEY keyCode)
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
        case KEY::KEY_C:
        {
            Scene* pScene = Director::getInstance()->getRunningScene();
            MapLayer* pLayer = (MapLayer*)pScene->getChildByTag(MAPLAYER_TAG);

            pLayer->pause();
            pLayer->createSelectBox();
            
            isItemKeyPressed_ = !isItemKeyPressed_;
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
