//
//  MapLayer.cpp
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#include "BlockLayer.h"

#include "MapMgr.h"

#include "Define.h"
#include "BlocksSetting.h"

USING_NS_CC;

BlockLayer::BlockLayer()
    : nextBlockType_(BLOCKTYPE::END)
{
    nextBlocks_.reserve(BLOCKCNT);
}

BlockLayer::~BlockLayer()
{
}

BlockLayer* BlockLayer::create()
{
    BlockLayer* pRet = new(std::nothrow) BlockLayer;
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

bool BlockLayer::init()
{
    if(false == LayerColor::initWithColor(Color4B::WHITE))
    {
        return false;
    }
    
    this->setContentSize(Size(BLOCKLAYER_SIZE_X, BLOCKLAYER_SIZE_Y));
    this->setPosition(Vec2(BLOCKLAYER_POS_X, BLOCKLAYER_POS_Y));
    
    // 스프라이트 최초로 생성
    Sprite* pSprite = nullptr;
    for(int i = 0; i < BLOCKCNT; ++i)
    {
        pSprite = Sprite::create("white.png");        
        pSprite->setAnchorPoint(cocos2d::Vec2(1, 0));
        pSprite->setTag(NEXTBLOCK_TAG);
        
        nextBlocks_.emplace_back(pSprite);
        this->addChild(pSprite);
    }
    
    scheduleUpdate();
    
    return true;
}

void BlockLayer::update(float dt)
{
    checkChangeNextBlock();
}

void BlockLayer::checkChangeNextBlock()
{
    int nextBlock = MapMgr::getInstance()->getNextBlockType();
    
    if(nextBlockType_ == nextBlock)
        return;
        
    nextBlockType_ = nextBlock;
    
    Color3B color = findNextBlockColor();
    std::vector<int> locationVec = findNextBlockLocation();

    // 블럭 정보 다시 세팅
    int posX = 0;
    int posY = 0;
    int index = 0;
    
    for(int i = 0; i < BLOCKCNT; ++i)
    {
        nextBlocks_[i]->setColor(color);
     
        index = i * 2;
        posX = BLOCKSIZE * (locationVec[index] + initPos::nextBlockPos[POS_X]);
        posY = BLOCKSIZE * (locationVec[index + 1] + initPos::nextBlockPos[POS_Y]);
        
        nextBlocks_[i]->setPosition(posX, posY);
    }
    
    
}

cocos2d::Color3B BlockLayer::findNextBlockColor()
{
    Color3B color = Color3B(0, 0, 0);
    switch (nextBlockType_)
    {
        case BLOCKTYPE::J:
        {
            color = Color3B::ORANGE;
            break;
        }
        case BLOCKTYPE::I:
        {
            color = Color3B::YELLOW;
            break;
        }
        case BLOCKTYPE::S:
        {
            color = Color3B::MAGENTA;
            break;
        }
        case BLOCKTYPE::T:
        {
            color = Color3B::GRAY;
            break;
        }
        case BLOCKTYPE::O:
        {
            color = Color3B::GREEN;
            break;
        }
        default:
            break;
    }
    
    return color;
}

std::vector<int> BlockLayer::findNextBlockLocation()
{
    std::vector<int> locationVec;
    locationVec.resize(2 * BLOCKCNT);
    
    switch (nextBlockType_)
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
