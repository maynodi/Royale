//
//  Blocks_O.h
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#pragma once

#include "cocos2d.h"
#include "Blocks.h"

class Blocks_O : public Blocks
{
public:
    static Blocks_O* create(cocos2d::Color3B color, int blockCnt);
    
public:
    virtual bool init(cocos2d::Color3B color, int blockCnt) override;
    
public:
    virtual void rotate(int keyPressedCnt) override;
    
public:
    Blocks_O();
    virtual ~Blocks_O();
};


