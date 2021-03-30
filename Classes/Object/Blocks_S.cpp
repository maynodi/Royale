//
//  Blocks_S.cpp
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#include "Blocks_S.h"

#include "BlocksSetting.h"

USING_NS_CC;

Blocks_S::Blocks_S()
{
}

Blocks_S::~Blocks_S()
{
}

Blocks_S* Blocks_S::create(cocos2d::Color3B color)
{
    Blocks_S* pRet = new(std::nothrow) Blocks_S;
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

bool Blocks_S::init(cocos2d::Color3B color)
{
    // BLOCK 초기화
    BLOCK* pBlock = nullptr;
    for(int i = 0; i < BLOCKCNT; ++i)
    {
        Vec2 pos = Vec2(BLOCKSIZE * (location::S[POS_X][i] + initPos::pos[POS_X])
                        , BLOCKSIZE * (location::S[POS_Y][i] + initPos::pos[POS_Y]));
        
        pBlock = new BLOCK(pos.x, pos.y);
        
        pBlock->pSprite_->setColor(color);
        blocks_[i] = pBlock;
        
        // preview Block
        Sprite* pPreviewSprite = Sprite::create("white.png");
        //pPreviewSprite->setScale(BLOCKSIZE, BLOCKSIZE);
        pPreviewSprite->setTag(BLOCKPREVIEW_TAG);
        pPreviewSprite->setAnchorPoint(Vec2(0, 0));
        pPreviewSprite->setOpacity(125);
        
        pBlock->pSprite_->addChild(pPreviewSprite);
    }
    
    blockType_ = BLOCKTYPE::S;
    
    return true;
}

void Blocks_S::rotate(int keyPressedCnt)
{
    // 일단 미리 회전 후의 좌표를 계산해놓고
    Vec2 newPos[BLOCKCNT] = {};
    for(int i = 0; i < BLOCKCNT; ++i)
    {
        Vec2 curPos = blocks_[i]->pSprite_->getPosition();
        
        newPos[i].x = curPos.x + BLOCKSIZE * (posVariance::S[keyPressedCnt][(i * 2)]);
        newPos[i].y = curPos.y + BLOCKSIZE * (posVariance::S[keyPressedCnt][(i * 2) + 1]);
    }

    // 회전에 제한이 걸리는 위치인가?
    if(true == checkLimitedRotate(newPos))
        return;

   for(int i = 0; i < BLOCKCNT; ++i)
   {
       blocks_[i]->pSprite_->setPosition(newPos[i]);
       blocks_[i]->setPos(newPos[i]);
       
       Node* previewNode = blocks_[i]->pSprite_->getChildByTag(BLOCKPREVIEW_TAG);
       float posY = previewNode->getPositionY();
       int limit = posY + newPos[i].y;
       
       if(MIN_HEIGHT > limit)
       {
           setRotatePreviewBlocks();
       }
   }
    
}
