#pragma once

#include "cocos2d.h"
#include "Blocks.h"

class SpecialBlock : public Blocks
{
private:
    std::vector<cocos2d::Vec2> posVec_;
    
public:
    static SpecialBlock* create(cocos2d::Color3B color);
    
public:
    virtual bool init(cocos2d::Color3B color, int blockCnt = 0) override;    
    
public:
    virtual void rotate(int keyPressedCnt) override;
    
public:
    SpecialBlock();
    virtual ~SpecialBlock();
};


