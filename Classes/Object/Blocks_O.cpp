//
//  Blocks_O.cpp
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#include "Blocks_O.h"

#include "BlocksSetting.h"

USING_NS_CC;

Blocks_O::Blocks_O()
{
}

Blocks_O::~Blocks_O()
{
}

Blocks_O* Blocks_O::create(cocos2d::Color3B color)
{
    Blocks_O* pRet = new(std::nothrow) Blocks_O;
    if (pRet && pRet->init(color))
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

bool Blocks_O::init(cocos2d::Color3B color)
{
    // BLOCK 초기화
    BLOCK* pBlock = nullptr;
    for(int i = 0; i < BLOCKCNT; ++i)
    {
        Vec2 pos = Vec2(BLOCKSIZE * (location::O[POS_X][i] + initPos::pos[POS_X])
                        , BLOCKSIZE * (location::O[POS_Y][i] + initPos::pos[POS_Y]));
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
    
    blockType_ = BLOCKTYPE::O;
    
    return true;
}

void Blocks_O::rotate(int keyPressedCnt)
{
    // 일단 미리 회전 후의 좌표를 계산해놓고
    Vec2 newPos[BLOCKCNT] = {};
    for(int i = 0; i < BLOCKCNT; ++i)
    {
        Vec2 curPos = blocks_[i]->pSprite_->getPosition();
        
        newPos[i].x = curPos.x + BLOCKSIZE * (posVariance::O[keyPressedCnt][(i * 2)]);
        newPos[i].y = curPos.y + BLOCKSIZE * (posVariance::O[keyPressedCnt][(i * 2) + 1]);
    }

    // 회전에 제한이 걸리는 위치인가?
    if(true == checkLimitedRotate(newPos))
        return;

   for(int i = 0; i < BLOCKCNT; ++i)
   {
       blocks_[i]->pSprite_->setPosition(newPos[i]);
       blocks_[i]->setPos(newPos[i]);
       
       PreviewBlockDistVec_.emplace_back(int(newPos[i].y));
   }
    
    checkPreviewBlocks();
}
