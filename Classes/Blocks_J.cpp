//
//  Blocks_J.cpp
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#include "Blocks_J.h"

#include "BlocksSetting.h"

USING_NS_CC;

Blocks_J::Blocks_J()
{
    //memset(blocks_, 0, sizeof(blocks_) * BLOCKCNT);
}

Blocks_J::~Blocks_J()
{
    //delete this;
}

Blocks_J* Blocks_J::create()
{
    Blocks_J* pRet = new(std::nothrow) Blocks_J;
    if (pRet && pRet->init())
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

bool Blocks_J::init()
{
    // Blocks 초기화
    Block* pBlock = nullptr;
    for(int i = 0; i < BLOCKCNT; ++i)
    {
        Vec2 pos = Vec2(BLOCKSIZE * (location::location_J[0][i] + 2), BLOCKSIZE * (location::location_J[1][i] + 2));
        pBlock = new Block(pos);
        
        blocks_[i] = pBlock;
    }
  
    return true;
}

//cocos2d::Sprite* Blocks_J::getBlockSprite(int idx)
//{
//    return blocks_[idx]->pSprite_;
//}
