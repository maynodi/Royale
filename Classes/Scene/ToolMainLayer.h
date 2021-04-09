#pragma once

#include "cocos2d.h"

class ToolMainLayer : public cocos2d::Layer
{
private:
    int blockCnt_;
    std::vector<bool> isExisting_[4]; // 4x4 배열
    
public:
    static ToolMainLayer* create();
    
public:
    virtual bool init() override;
    
public:
    int getBlockCnt() { return blockCnt_; }
    
public:
    void checkCollision(cocos2d::Vec2 mousePos);
    void createBlock(cocos2d::Vec2 pos);
    
public:
    void DrawRect();
    void onMouseUp(cocos2d::Event* event);
    
public:
    ToolMainLayer();
    ~ToolMainLayer();
};


