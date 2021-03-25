//
//  Blocks_S.h
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#pragma once

#include "cocos2d.h"
#include "Blocks.h"

class Blocks_S : public Blocks
{
public:
    static Blocks_S* create(cocos2d::Color3B color);
    
public:
    virtual bool init(cocos2d::Color3B color) override;
    
public:
    virtual void rotate(int keyPressedCnt) override;
    
public:
    Blocks_S();
    virtual ~Blocks_S();
};


