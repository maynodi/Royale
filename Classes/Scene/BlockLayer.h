//
//  MapLayer.h
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#pragma once

#include "cocos2d.h"

class BlockLayer : public cocos2d::LayerColor
{
private:
    int nextBlockType_;
    std::map<int, std::vector<cocos2d::Vec2>> locationMap_; // 기본 위치
    std::map<int, std::vector<cocos2d::Sprite*>> poolMap_;    
    
public:
    static BlockLayer* create();
    
public:
    virtual bool init() override;
    void preSetting();
    
public:
    virtual void update(float dt) override;
    
public:
    int setNextBlockCnt(int type);
    cocos2d::Color3B findNextBlockColor(int type);
    void findNextBlockLocation(int type, int blockCnt);
    void ChangeNextBlock();
    
public:
    BlockLayer();
    ~BlockLayer();
};


