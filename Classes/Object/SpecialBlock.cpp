#include "SpecialBlock.h"

#include "DataMgr.h"

#include "BlocksSetting.h"

USING_NS_CC;

SpecialBlock::SpecialBlock()
{
}

SpecialBlock::~SpecialBlock()
{
}

SpecialBlock* SpecialBlock::create(cocos2d::Color3B color)
{
    SpecialBlock* pRet = new(std::nothrow) SpecialBlock;
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

bool SpecialBlock::init(cocos2d::Color3B color, int blockCnt)
{
    blockCnt_ = DataMgr::getInstance()->getSpecialBlockCnt();
    posVec_ = DataMgr::getInstance()->getLoadInfoVec();
    
    blocks_.resize(blockCnt_);
    
    BLOCK* pBlock = nullptr;
    for(int i = 0; i < blockCnt_; ++i)
    {
        Vec2 pos = Vec2(BLOCKSIZE * (posVec_[i].x + initPos::pos[POS_X])
                        , BLOCKSIZE * (posVec_[i].y + initPos::pos[POS_Y]));
        
        
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
    
    blockType_ = BLOCKTYPE::SPECIAL;
    
    return true;
}

void SpecialBlock::rotate(int keyPressedCnt)
{
    // 일단 미리 회전 후의 좌표를 계산해놓고
    std::vector<cocos2d::Vec2> newPosVec;
    newPosVec.reserve(blockCnt_);
    
    Mat4 mat;
    Mat4::createRotationZ(ROT_Z_ANGLE, &mat);
    for(int i = 0; i < blockCnt_; ++i)
    {
        // 원점에서 이동한 거리
        Vec2 pos = blocks_[i]->pSprite_->getPosition();

        pos.x -= BLOCKSIZE * posVec_[i].x;
        pos.y -= BLOCKSIZE * posVec_[i].y;
        
        Vec4 pos3 = Vec4( posVec_[i].x, posVec_[i].y, 0, 1);
        Vec4 newpos = mat * pos3;

        newpos.x = floor(newpos.x + 0.5f);
        newpos.y = floor(newpos.y + 0.5f);
        
        // 원점에 대한 기본 좌표 변경
        posVec_[i].x = newpos.x;
        posVec_[i].y = newpos.y;

        newpos *= BLOCKSIZE;

        newPosVec.emplace_back(Vec2(pos.x + newpos.x, pos.y + newpos.y));
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
