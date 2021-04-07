//
//  Block.h
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#pragma once

#include "cocos2d.h"

#include "Define.h"

typedef struct Block //최소 단위 1블럭 -> 얘가 4개 모여서 Blocks
{
    cocos2d::Sprite* pSprite_;
    int x_;
    int y_;
    
    Block(int x, int y)
        : x_(x), y_(y)
    {
        pSprite_ = cocos2d::Sprite::create("white.png");
        pSprite_->setPosition(cocos2d::Vec2(x_, y_));
        pSprite_->setAnchorPoint(cocos2d::Vec2(1, 0));
    }
    
    void setPos(cocos2d::Vec2 pos)
    {
        x_ = (int)pos.x;
        y_ = (int)pos.y;
    }
    
    void setPosY(float posY)
    {
        y_ = (int)posY;
    }
}BLOCK;

class Blocks
{
protected:
    //BLOCK* blocks_[BLOCKCNT]; // BLOCK을 4개 가지고 있는 변수
    std::vector<BLOCK*> blocks_;
    bool isDrop_;
    BLOCKTYPE blockType_;
    int dist_;
    std::vector<int> PreviewBlockDistVec_;
    
public:
    virtual bool init(cocos2d::Color3B color, int blockCnt) = 0;
    
public:
    cocos2d::Sprite* getBlockSprite(int idx) { return (blocks_[idx])->pSprite_; }
    int getCurBlockType() { return blockType_; }
    
public:
    void setIsDrop(bool isDrop) { isDrop_ = isDrop; }
    
public:
    void move(int dir);
    bool checkLimitedPos(int dir);
    virtual void rotate(int keyPressedCnt) = 0;
    bool checkLimitedRotate(cocos2d::Vec2* pos);
    void drop();
    void doWorkWhenIsUnderNothing();
    void changePos(cocos2d::Vec2 variance = cocos2d::Vec2::ZERO);
    void fixBlockPos();
    void autoMoveDown();
    
public:
    void checkPreviewBlocks();
    void setPosPreviewBlocks(int dist);
    void setRotatePreviewBlocks();
    
public:
    bool checkGameOverWhenCreate();
    
public:
    Blocks();
    virtual ~Blocks();
};


