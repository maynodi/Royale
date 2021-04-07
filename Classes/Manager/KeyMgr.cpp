//
//  KeyMgr.cpp
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#include "KeyMgr.h"

#include "MapMgr.h"
#include "DataMgr.h"
#include "ParticleMgr.h"

#include "SimpleAudioEngine.h"

#include "MapLayer.h"
#include "holdLayer.h"

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

void KeyMgr::minusUpKeyPressedCnt()
{
    upKeyPressedCnt_ -= 1;
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
            // 소리
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("selection.wav");
            CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
            
            int posY = selectBox->getPositionY();
            posY += BLOCKSIZE;
            
            selectBox->setPositionY(posY);
            break;
        }
        case KEY::KEY_DOWN_ARROW:
        {
            // 소리
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("selection.wav");
            CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0.5f);
            
            int posY = selectBox->getPositionY();
            posY -= BLOCKSIZE;
            
            selectBox->setPositionY(posY);
            break;
        }
        case KEY::KEY_C:
        {
            int posY = (int)selectBox->getPositionY();
            int row = posY / BLOCKSIZE;
            
            // 라인 삭제 및 한줄아래이동
            MapMgr::getInstance()->deleteLine(row);
            MapMgr::getInstance()->lineGoDown(row);
            
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
    Blocks* pCurBlocks = MapMgr::getInstance()->getCurBlocks();
    if(nullptr == pCurBlocks)
        return;
    
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
            upKeyPressedCnt_ += 1;
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
            int itemCnt = DataMgr::getInstance()->getItemCnt();
            if(0 >= itemCnt)
                break;
            
            Scene* pScene = Director::getInstance()->getRunningScene();
            MapLayer* pMapLayer = (MapLayer*)pScene->getChildByTag(MAPLAYER_TAG);

            pMapLayer->pause();
            pMapLayer->createSelectBox();
            
            // 아이템 갯수 감소
            DataMgr::getInstance()->minusItemCnt();
            
            isItemKeyPressed_ = !isItemKeyPressed_;
            break;
        }
        case KEY::KEY_SHIFT:
        {
            Blocks* pCurBlocks = MapMgr::getInstance()->getCurBlocks();
            if(nullptr == pCurBlocks)
                break;
            
            Scene* pScene = Director::getInstance()->getRunningScene();
            HoldLayer* pHoldLayer = (HoldLayer*)pScene->getChildByTag(HOLDLAYER_TAG);
            
            int blockType = pCurBlocks->getCurBlockType();
            pHoldLayer->ChangeHoldBlock(blockType);
            break;
        }
        case KEY::KEY_0:
        {
            DataMgr::getInstance()->addItemCnt();
        }
        case KEY::KEY_1:
        {
            // smogtrap test
            Scene* pScene = Director::getInstance()->getRunningScene();
            MapLayer* pMapLayer = (MapLayer*)pScene->getChildByTag(MAPLAYER_TAG);

            Vec2 pos = {};
            for(int i = 0; i < 2; ++i)
            {
                pos.y = MAPLAYER_SIZE_Y / 2 - (i * 200);
                
                for(int j = 0; j< 5; ++j)
                {
                    pos.x = BLOCKSIZE + ((j+1) * 50);
                    ParticleMgr::getInstance()->particleSmog(pMapLayer, pos);
                }
            }
        }
        default:
            break;
    }
}

void KeyMgr::onKeyReleased(KEY keyCode, cocos2d::Event* event)
{
}
