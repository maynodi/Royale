//
//  Blocks_J.h
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#pragma once

#include "cocos2d.h"
#include "Blocks.h"

class Blocks_J : public Blocks
{
//private:
//   Block* blocks_[BLOCKCNT]; // Block을 4개 가지고 있는 변수

public:
    static Blocks_J* create();
    
public:
    virtual bool init() override;
    
//public:
//    virtual cocos2d::Sprite* getBlockSprite(int idx) override;    
    
public:
    Blocks_J();
    ~Blocks_J();
};


