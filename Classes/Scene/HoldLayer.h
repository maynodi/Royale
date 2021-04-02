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
public:
    static HoldLayer* create();
    
public:
    virtual bool init() override;
    
public:
    virtual void update(float dt) override;
    cocos2d::Color3B findNextBlockColor();
    std::vector<int> findNextBlockLocation();
    
public:
    HoldLayer();
    ~HoldLayer();
};


