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
    std::vector<cocos2d::Sprite*> nextBlocks_[2];
    
public:
    static BlockLayer* create();
    
public:
    virtual bool init() override;
    
public:
    virtual void update(float dt) override;
    void checkChangeNextBlock();
    cocos2d::Color3B findNextBlockColor();
    std::vector<int> findNextBlockLocation();
    
public:
    BlockLayer();
    ~BlockLayer();
};


