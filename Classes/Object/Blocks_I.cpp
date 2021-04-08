//
//  Blocks_I.cpp
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#include "Blocks_I.h"

#include "BlocksSetting.h"

USING_NS_CC;

Blocks_I::Blocks_I()
{
}

Blocks_I::~Blocks_I()
{
}

Blocks_I* Blocks_I::create(cocos2d::Color3B color, int blockCnt)
{
    Blocks_I* pRet = new(std::nothrow) Blocks_I;
    if (pRet && pRet->init(color, blockCnt))
    {
        //pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool Blocks_I::init(cocos2d::Color3B color, int blockCnt)
{
    blockCnt_ = blockCnt;
    
    blocks_.resize(blockCnt_);
    
    // BLOCK 초기화
    BLOCK* pBlock = nullptr;
    for(int i = 0; i < blockCnt_; ++i)
    {
        Vec2 pos = Vec2(BLOCKSIZE * (location::I[POS_X][i] + initPos::pos[POS_X])
                        , BLOCKSIZE * (location::I[POS_Y][i] + initPos::pos[POS_Y]));
        pBlock = new BLOCK(pos.x, pos.y);
        
        pBlock->pSprite_->setColor(color);        
        blocks_[i] = pBlock;
        
        // preview Block
        Sprite* pPreviewSprite = Sprite::create("white.png");        
        pPreviewSprite->setTag(BLOCKPREVIEW_TAG);
        pPreviewSprite->setAnchorPoint(Vec2(0, 0));
        pPreviewSprite->setOpacity(125);
        
        pBlock->pSprite_->addChild(pPreviewSprite);
    }
    
    blockType_ = BLOCKTYPE::I;
    
    return true;
}

void Blocks_I::rotate(int keyPressedCnt)
{
    // 일단 미리 회전 후의 좌표를 계산해놓고
    std::vector<cocos2d::Vec2> newPosVec;
    newPosVec.resize(blockCnt_);
    
    for(int i = 0; i < blockCnt_; ++i)
    {
        Vec2 curPos = blocks_[i]->pSprite_->getPosition();
        
        int posX = curPos.x + BLOCKSIZE * (posVariance::I[keyPressedCnt][(i * 2)]);
        int posY = curPos.y + BLOCKSIZE * (posVariance::I[keyPressedCnt][(i * 2) + 1]);
        
        newPosVec[i] = Vec2(posX, posY);
    }

    // 회전에 제한이 걸리는 위치인가?
    if(true == checkLimitedRotate(newPosVec, blockCnt_))
        return;

    for(int i = 0; i < blockCnt_; ++i)
    {
        blocks_[i]->pSprite_->setPosition(newPosVec[i]);
        blocks_[i]->setPos(newPosVec[i]);
        
        PreviewBlockDistVec_.emplace_back(int(newPosVec[i].y));
    }
    
    checkPreviewBlocks();
}
