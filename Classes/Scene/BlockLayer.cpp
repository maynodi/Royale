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
    
    for(int arr = 0; arr < 2; ++arr)
    {
        nextBlocks_[arr].reserve(BLOCKCNT);
        
        for(int i = 0; i < BLOCKCNT; ++i)
        {
            pSprite = Sprite::create("white.png");
            pSprite->setAnchorPoint(cocos2d::Vec2(1, 0));
            pSprite->setTag(NEXTBLOCK_TAG);
            
            nextBlocks_[arr].emplace_back(pSprite);
            this->addChild(pSprite);
        }
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
    std::list<int> list = MapMgr::getInstance()->getNextBlockTypeList();
    std::list<int>::iterator iter = list.begin();
    
    int posX = 0;
    int posY = 0;
    int index = 0;
    int arrCnt = 0;
    for(; iter != list.end(); ++iter)
    {
        if(2 < list.size())
            continue;
        
        nextBlockType_ = *iter;
        
        Color3B color = findNextBlockColor();
        std::vector<int> locationVec = findNextBlockLocation();
        
        for(int i = 0; i < BLOCKCNT; ++i)
        {
            nextBlocks_[arrCnt][i]->setColor(color);
            
            index = i * 2;
            posX = BLOCKSIZE * (locationVec[index] + initPos::nextBlockPos[POS_X] + (arrCnt * 5));
            posY = BLOCKSIZE * (locationVec[index + 1] + initPos::nextBlockPos[POS_Y]);
            
            nextBlocks_[arrCnt][i]->setPosition(posX, posY);
        }
        
        arrCnt += 1;
    }
}

cocos2d::Color3B BlockLayer::findNextBlockColor()
{
    Color3B color = Color3B(0, 0, 0);
    switch (nextBlockType_)
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
