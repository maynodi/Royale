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
    static Blocks_O* create();
    
public:
    virtual bool init() override;
    
public:
    virtual void rotate(int dir, int keyPressedCnt) override;
    
public:
    Blocks_O();
    virtual ~Blocks_O();
};


