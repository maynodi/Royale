//
//  MapLayer.h
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#pragma once

#include "cocos2d.h"

class MapLayer : public cocos2d::Layer
{
public:
    static MapLayer* create();
    
public:
    virtual bool init() override;
    virtual void onEnter() override;
    
public:
    virtual void update(float dt) override;
    void DrawGridMap();
    void autoMoveDown(float dt);
    
public:
    MapLayer();
    ~MapLayer();
};


