#pragma once

#include "cocos2d.h"

class ToolMainLayer : public cocos2d::Layer
{
public:
    static ToolMainLayer* create();
    
public:
    virtual bool init() override;
    
public:
    virtual void update(float dt) override;
    void checkCollision(cocos2d::Vec2 mousePos);
    void createBlock(cocos2d::Vec2 pos);
    
public:
    void DrawRect();
    void onMouseUp(cocos2d::Event* event);
    
public:
    ToolMainLayer();
    ~ToolMainLayer();
};


