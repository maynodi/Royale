//
//  KeyMgr.h
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#pragma once

#include "cocos2d.h"

#include "Define.h"

class KeyMgr : public cocos2d::Node
{
private:
    bool isItemKeyPressed_;
    
public:
    static KeyMgr* pInstance_;

private:
    cocos2d::EventListenerKeyboard* pListner_;
    int upKeyPressedCnt_;
    
public:
    static KeyMgr* getInstance();
    static void destroyInstance();
    
public:
    virtual bool init() override;
    
public:
    bool getItemKeyPressed() { return isItemKeyPressed_; }
    
public:
    void setZeroUpKeyPressedCnt() { upKeyPressedCnt_ = 0; }
    void minusUpKeyPressedCnt();
    
public:
    void onKeyPressed(KEY keyCode, cocos2d::Event* event);
    void selectBoxControl(KEY keyCode);
    void blocksControl(KEY keyCode);    
    void onKeyReleased(KEY keyCode, cocos2d::Event* event);
    
private:
    KeyMgr();
    ~KeyMgr();
};


