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
private:
    float time_;
    bool isChange_;
    cocos2d::Sprite* selectBox_;
    
public:
    static MapLayer* create();
    
public:
    virtual bool init() override;
    virtual void onEnter() override;
    
public:
    void setIsChange(bool isChange) { isChange_ = isChange; }
    
public:
    virtual void update(float dt) override;
    void setGameOver();
    void changeSpeed();
    void DrawGridMap();
    void createSelectBox();
    void autoMoveDown(float dt);
    
public:
    MapLayer();
    ~MapLayer();
};


