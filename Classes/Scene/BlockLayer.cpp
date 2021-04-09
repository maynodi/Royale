//
//  MapLayer.cpp
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#include "BlockLayer.h"

#include "MapMgr.h"
#include "DataMgr.h"

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
    
    preSetting();
    
    scheduleUpdate();
    
    return true;
}

void BlockLayer::preSetting()
{
    Sprite* pSprite = nullptr;
    for(int type = 0; type < BLOCKTYPE::END; ++type)
    {
        int cnt = setNextBlockCnt(type);
        Color3B color = findNextBlockColor(type);
        
        findNextBlockLocation(type, cnt);
        
        std::vector<cocos2d::Sprite*> spriteVec;
        spriteVec.resize(cnt);
        
        for(int i = 0; i < cnt; ++i)
        {
            pSprite = Sprite::create("white.png");
            
            pSprite->setAnchorPoint(cocos2d::Vec2(1, 0));
            pSprite->setPosition(Vec2(BLOCKSIZE * (locationMap_[type][i].x + initPos::nextBlockPos[POS_X])
                                      , BLOCKSIZE * (locationMap_[type][i].y + initPos::nextBlockPos[POS_Y])));
            
            pSprite->setTag(NEXTBLOCK_TAG);
            pSprite->setColor(color);
            
            pSprite->retain();
            
            spriteVec[i] = pSprite;
        }
        
        poolMap_[type] = spriteVec;
    }
}

void BlockLayer::update(float dt)
{
    ChangeNextBlock();
}

int BlockLayer::setNextBlockCnt(int type)
{
    int cnt = 0;
    switch (type)
    {
        case BLOCKTYPE::SPECIAL:
        {
            cnt = DataMgr::getInstance()->getSpecialBlockCnt();
            return cnt;
        }
        default:
        {
            cnt = BLOCKCNT;
            return cnt;
        }
    }
}
void BlockLayer::ChangeNextBlock()
{
    Blocks* curBlock = MapMgr::getInstance()->getCurBlocks();
    if(nullptr != curBlock)
        return;
    
    // 이전 그리던거 release
    Vector<Node*> children = this->getChildren();
    for(auto& child : children)
    {
        if(nullptr == child->getParent())
            continue;
        
        child->removeFromParent();
    }
    
    std::list<int> nextBlockList = MapMgr::getInstance()->getNextBlockTypeList();
    std::list<int>::iterator iter = nextBlockList.begin();
    
    std::vector<cocos2d::Vec2> posVec = locationMap_[(*iter)];
    
    int blockCnt = poolMap_[(*iter)].size();
    
    for(int i = 0; i < blockCnt; ++i)
    {
        
        poolMap_[(*iter)][i]->setPosition(Vec2(BLOCKSIZE * (posVec[i].x + initPos::nextBlockPos[POS_X])
                                               , BLOCKSIZE * (posVec[i].y + initPos::nextBlockPos[POS_Y])));
        
        
        this->addChild(poolMap_[(*iter)][i]);
    }
}

cocos2d::Color3B BlockLayer::findNextBlockColor(int type)
{
    Color3B color = Color3B(0, 0, 0);
    switch (type)
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
        case BLOCKTYPE::SPECIAL:
        {
            color = Color3B::RED;
            break;
        }
        default:
            break;
    }
    
    return color;
}

void BlockLayer::findNextBlockLocation(int type, int blockCnt)
{
    locationMap_[type].resize(blockCnt);
    
    switch (type)
    {
        case BLOCKTYPE::J:
        {
            for(int i = 0; i < blockCnt; ++i)
            {
                int posX = location::J[POS_X][i];
                int posY = location::J[POS_Y][i];
                
                locationMap_[type][i] = cocos2d::Vec2(posX, posY);
            }
            break;
        }
        case BLOCKTYPE::I:
        {
            for(int i = 0; i < blockCnt; ++i)
            {
                int posX = location::I[POS_X][i];
                int posY = location::I[POS_Y][i];
                
                locationMap_[type][i] = cocos2d::Vec2(posX, posY);
            }
            break;
        }
        case BLOCKTYPE::S:
        {
            for(int i = 0; i < blockCnt; ++i)
            {
                int posX = location::S[POS_X][i];
                int posY = location::S[POS_Y][i];
                
                locationMap_[type][i] = cocos2d::Vec2(posX, posY);
            }
            break;
        }
        case BLOCKTYPE::T:
        {
            for(int i = 0; i < blockCnt; ++i)
            {
                int posX = location::T[POS_X][i];
                int posY = location::T[POS_Y][i];
                
                locationMap_[type][i] = cocos2d::Vec2(posX, posY);
            }
            break;
        }
        case BLOCKTYPE::O:
        {
            for(int i = 0; i < blockCnt; ++i)
            {
                int posX = location::O[POS_X][i];
                int posY = location::O[POS_Y][i];
                
                locationMap_[type][i] = cocos2d::Vec2(posX, posY);
            }
            break;
        }
        case BLOCKTYPE::SPECIAL:
        {
            std::vector<Vec2> posVec = DataMgr::getInstance()->getLoadInfoVec();
            
            for(int i = 0; i < blockCnt; ++i)
            {
                int posX = posVec[i].x;
                int posY = posVec[i].y;
                
                locationMap_[type][i] = cocos2d::Vec2(posX, posY);
            }
            
            break;
        }
        default:
            break;
    }
}
