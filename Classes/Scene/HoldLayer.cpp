//
//  MapLayer.cpp
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#include "HoldLayer.h"

#include "MapMgr.h"

#include "Define.h"
#include "BlocksSetting.h"

USING_NS_CC;

HoldLayer::HoldLayer()
    : blockType_(BLOCKTYPE::END)
    , isHold_(false)
{
}

HoldLayer::~HoldLayer()
{
}

HoldLayer* HoldLayer::create()
{
    HoldLayer* pRet = new(std::nothrow) HoldLayer;
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool HoldLayer::init()
{
    if(false == LayerColor::initWithColor(Color4B::WHITE))
    {
        return false;
    }
    
    this->setContentSize(Size(BLOCKLAYER_SIZE_X, BLOCKLAYER_SIZE_Y));
    this->setPosition(Vec2(BLOCKLAYER_POS_X, HOLDLAYER_POS_Y));
    
    return true;
}

void HoldLayer::ChangeHoldBlock(int type)
{
    if(true == isHold_)
        return;
    
    MapMgr::getInstance()->swapHoldBlock(blockType_);
    blockType_ = type;
    
    int childrenCnt = this->getChildrenCount();
    if(0 == childrenCnt)
    {
        // 스프라이트 최초로 생성
        Sprite* pSprite = nullptr;
        for(int i = 0; i < BLOCKCNT; ++i)
        {
            pSprite = Sprite::create("white.png");
            pSprite->setAnchorPoint(cocos2d::Vec2(1, 0));

            this->addChild(pSprite);
        }
    }
        
    Vector<Node*> children = this->getChildren();
    
    Color3B color = findHoldBlockColor();
    std::vector<int> locationVec = findHoldBlockLocation();
    
    int posX = 0;
    int posY = 0;
    int index = 0;
    for(int i = 0; i < children.size(); ++i)
    {
        children.at(i)->setColor(color);
        
        index = i * 2;
        posX = BLOCKSIZE * (locationVec[index] + initPos::holdBlockPos[POS_X]);
        posY = BLOCKSIZE * (locationVec[index + 1] + initPos::holdBlockPos[POS_Y]);
        
        children.at(i)->setPosition(posX, posY);
    }
    
    isHold_ = true;
}

cocos2d::Color3B HoldLayer::findHoldBlockColor()
{
    Color3B color = Color3B(0, 0, 0);
    switch (blockType_)
    {
        case BLOCKTYPE::J:
        {
            color = BLOCK_J_COLOR;
            break;
        }
        case BLOCKTYPE::I:
        {
            color = BLOCK_I_COLOR;
            break;
        }
        case BLOCKTYPE::S:
        {
            color = BLOCK_S_COLOR;
            break;
        }
        case BLOCKTYPE::T:
        {
            color = BLOCK_T_COLOR;
            break;
        }
        case BLOCKTYPE::O:
        {
            color = BLOCK_O_COLOR;
            break;
        }
        default:
            break;
    }

    return color;
}

std::vector<int> HoldLayer::findHoldBlockLocation()
{
    std::vector<int> locationVec;
    locationVec.resize(2 * BLOCKCNT);

    switch (blockType_)
    {
        case BLOCKTYPE::J:
        {
            int posX = 0;
            int posY = 0;
            int index = 0;

            for(int i = 0; i < BLOCKCNT; ++i)
            {
                index = i * 2;
                posX = location::J[POS_X][i];
                posY = location::J[POS_Y][i];

                locationVec[index] = posX;
                locationVec[index + 1] = posY;
            }
            break;
        }
        case BLOCKTYPE::I:
        {
            int posX = 0;
            int posY = 0;
            int index = 0;

            for(int i = 0; i < BLOCKCNT; ++i)
            {
                index = i * 2;
                posX = location::I[POS_X][i];
                posY = location::I[POS_Y][i];

                locationVec[index] = posX;
                locationVec[index + 1] = posY;
            }
            break;
        }
        case BLOCKTYPE::S:
        {
            int posX = 0;
            int posY = 0;
            int index = 0;
            for(int i = 0; i < BLOCKCNT; ++i)
            {
                index = i * 2;
                posX = location::S[POS_X][i];
                posY = location::S[POS_Y][i];

                locationVec[index] = posX;
                locationVec[index + 1] = posY;
            }
            break;
        }
        case BLOCKTYPE::T:
        {
            int posX = 0;
            int posY = 0;
            int index = 0;
            for(int i = 0; i < BLOCKCNT; ++i)
            {
                index = i * 2;
                posX = location::T[POS_X][i];
                posY = location::T[POS_Y][i];

                locationVec[index] = posX;
                locationVec[index + 1] = posY;
            }
            break;
        }
        case BLOCKTYPE::O:
        {
            int posX = 0;
            int posY = 0;
            int index = 0;
            for(int i = 0; i < BLOCKCNT; ++i)
            {
                index = i * 2;
                posX = location::O[POS_X][i];
                posY = location::O[POS_Y][i];

                locationVec[index] = posX;
                locationVec[index + 1] = posY;
            }
            break;
        }
        default:
            break;
    }

    return locationVec;
}
