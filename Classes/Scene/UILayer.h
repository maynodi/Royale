#pragma once

#include "cocos2d.h"

class UILayer : public cocos2d::LayerColor
{
private:
    int fontSize_;
    
public:
    static UILayer* create();
    
public:
    virtual bool init() override;
    
public:
    void createMenuLabel();
    virtual void update(float dt) override;
    void createLabel();
    void checkLabel();
    
    
public:
    UILayer();
    ~UILayer();
};


