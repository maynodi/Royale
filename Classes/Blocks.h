//
//  Block.h
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#pragma once

#include "cocos2d.h"

#include "Define.h"


struct Block //최소 단위 1블럭 -> 얘가 4개 모여서 Blocks
{
    cocos2d::Sprite* pSprite_;
    cocos2d::Vec2 pos_;
    
    Block(cocos2d::Vec2 pos)
        : pos_(pos)
    {
        pSprite_ = cocos2d::Sprite::create("white.png",cocos2d::Rect(0, 0, BLOCKSIZE, BLOCKSIZE));
        pSprite_->setPosition(pos_);
        pSprite_->setAnchorPoint(cocos2d::Vec2(1, 0));
    }
};

class Blocks
{
protected:
    Block* blocks_[BLOCKCNT]; // Block을 4개 가지고 있는 변수

public:
    virtual bool init() = 0;
    // 이동함수나 회전함수도 여기 =0으로 넣을까..?
    
//public:
//    virtual cocos2d::Sprite* getBlockSprite(int idx) = 0;
    
public:
    cocos2d::Sprite* getBlockSprite(int idx) { return blocks_[idx]->pSprite_; }
    
public:
    void move();
    
public:
    Blocks();
    ~Blocks();
};


