//
//  MapLayer.h
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#pragma once

#include "cocos2d.h"

class HoldLayer : public cocos2d::LayerColor
{
private:
    int blockType_;
    bool isHold_; // 블럭 당 한번만 홀드가 가능하게 할거야
    
public:
    static HoldLayer* create();
    
public:
    virtual bool init() override;
    
public:
    void setHold(bool isHold) { isHold_ = isHold; }
    
public:
    void ChangeHoldBlock(int type);
    cocos2d::Color3B findHoldBlockColor();
    std::vector<int> findHoldBlockLocation();
    
public:
    HoldLayer();
    ~HoldLayer();
};


