//
//  MapMgr.cpp
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#include "MapMgr.h"

#include "KeyMgr.h"
#include "DataMgr.h"

#include <algorithm>

#include "Blocks_J.h"
#include "Blocks_I.h"
#include "Blocks_S.h"
#include "Blocks_T.h"
#include "Blocks_O.h"

USING_NS_CC;

MapMgr* MapMgr::pInstance_ = nullptr;

MapMgr::MapMgr()
    : pCurBlocks_(nullptr)
    , gameState_(PLAY)
    , nextBlockType_(BLOCKTYPE::S)
{
    
}

MapMgr::~MapMgr()
{
    //블럭들 관련해서 해야하나?
}

MapMgr*  MapMgr::getInstance()
{
    if(nullptr == pInstance_)
    {
        pInstance_ = new(std::nothrow) MapMgr;
        pInstance_->init();
    }
    
    return pInstance_;
}

void MapMgr::destroyInstance()
{
    if(nullptr != pInstance_)
    {
        delete pInstance_;
        pInstance_ = nullptr;
    }
}

void MapMgr::init()
{
    for(int i = 0; i < MAP_HEIGHT; ++i)
    {
        gridMapBlocks_[i].resize(MAP_WIDTH, nullptr);
        isExisting_[i].resize(MAP_WIDTH, false);
    }
    
}

void MapMgr::setIsDrop(bool isDrop)
{
    if(nullptr == pCurBlocks_)
        return;
    
    pCurBlocks_->setIsDrop(isDrop);
}

void MapMgr::makeNewBlocks()
{
    if(nullptr != pCurBlocks_)
        return;
    
    Blocks* pBlocks = nullptr;
    switch (nextBlockType_)
    {
        case BLOCKTYPE::J:
        {
            pBlocks = Blocks_J::create(Color3B::ORANGE);
            break;
        }
        case BLOCKTYPE::I:
        {
            pBlocks = Blocks_I::create(Color3B::YELLOW);
            break;
        }
        case BLOCKTYPE::S:
        {
            pBlocks = Blocks_S::create(Color3B::MAGENTA);
            break;
        }
        case BLOCKTYPE::T:
        {
            pBlocks = Blocks_T::create(Color3B::GRAY);
            break;
        }
        case BLOCKTYPE::O:
        {
            pBlocks = Blocks_O::create(Color3B::GREEN);
            break;
        }
        default:
            break;
    }
    
    pCurBlocks_ = pBlocks;
    nextBlockType_ = rand() % BLOCKTYPE::END;
    
    // 스프라이트를 mapLayer에 자식으로 추가
    Scene* pCurScene = Director::getInstance()->getRunningScene();
    Node* mapLayer = pCurScene->getChildByTag(MAPLAYER_TAG);
    
    Sprite* pSprite = nullptr;
    for(int i = 0; i < BLOCKCNT; ++i)
    {
        pSprite = pCurBlocks_->getBlockSprite(i);
        pSprite->Node::setVisible(false);
        pSprite->setTag(BLOCKSPRITE_TAG);
        
        mapLayer->addChild(pSprite);
    }
}

void MapMgr::update()
{
    reset();
    
    if(true == DataMgr::getInstance()->updateData())
    {
        addLine();
    }
    
    makeNewBlocks();
    
    pCurBlocks_->checkPreviewBlocks();
    pCurBlocks_->drop();
}

void MapMgr::addLine()
{
    // 레벨업을 하면 이전 레벨의 수만큼 라인이 추가된다.
    int curLevel = DataMgr::getInstance()->getLevel();
    int addLineCnt = (curLevel - 1) * 2;
    
    // 먼저 있는 거부터 이동시키자
    // 맨 꼭대기 인덱스가 필요해
    int maxRow = 0;
    maxRow = getMaxRowOfExistingBlocetMksInMap();
    
    if(0 < maxRow)
    {
        if(MAP_HEIGHT - 1 <= maxRow)
        {
            gameState_ = OVER;
            return;
        }
        
        // 맨 위부터 이동시킨다
        for(int row = maxRow; row >= 0; --row)
        {
            for(int col = 0; col < MAP_WIDTH; ++col)
            {
                gridMapBlocks_[row + addLineCnt][col] = gridMapBlocks_[row][col];
                gridMapBlocks_[row][col] = nullptr;
                
                if(nullptr != gridMapBlocks_[row + addLineCnt][col])
                {
                    int posY = (int)gridMapBlocks_[row + addLineCnt][col]->getPositionY();
                    posY += (BLOCKSIZE * addLineCnt);
                    gridMapBlocks_[row + addLineCnt][col]->setPositionY(posY);
                }
                
                isExisting_[row + addLineCnt][col] = isExisting_[row][col];
                isExisting_[row][col] = false;
            }
        }
    }
        
    // 라인 추가
    // 스프라이트 만들어서 하나씩 다 넣어주고
    // 스프라이트 위치 정해주고, 앵커도
    // 색깔랜덤
    
    Scene* pCurScene = Director::getInstance()->getRunningScene();
    Node* mapLayer = pCurScene->getChildByTag(MAPLAYER_TAG);
    
    float posX = 0;
    float posY = 0;
    for(int i = 0; i < addLineCnt; ++i)
    {
        int randomBlank = rand() % MAP_WIDTH;
        
        for(int j = 0; j < MAP_WIDTH; ++j)
        {
            if(randomBlank == j) // 한줄에 한칸은 빈칸으로 하기위한 코드
                continue;
            
            //위치
            posX = (j + 1) * BLOCKSIZE;
            posY = i * BLOCKSIZE;
            
            Sprite* pSprite = pSprite = Sprite::create("white.png");
            pSprite->setPosition(Vec2(posX, posY));
            pSprite->setAnchorPoint(Vec2(1, 0));
            pSprite->setColor(Color3B::GRAY);
            pSprite->setTag(BLOCKSPRITE_TAG);
            
            mapLayer->addChild(pSprite);
            
            gridMapBlocks_[i][j] = pSprite;
            isExisting_[i][j] = true;
        }
    }
    
}

int MapMgr::getMaxRowOfExistingBlocetMksInMap()
{
    for(int i = MAP_HEIGHT - 1; i > 0; --i)
    {
        for(int j = 0; j < MAP_WIDTH; ++j)
        {
            if(true == isExisting_[i][j])
            {
                return i;
            }
        }
    }
    
    return 0;
}

void MapMgr::move(int dir)
{
    if(nullptr == pCurBlocks_)
        return;
    
    // 아직 맵에 다 안 들어왔으면 움직이지마
    for(int i = 0; i < BLOCKCNT; ++i)
    {
        int posY = (int)pCurBlocks_->getBlockSprite(i)->getPositionY();
        if(MAX_HEIGHT <= posY)
        {
            return;
        }
    }
    
    pCurBlocks_->move(dir);
}

void MapMgr::rotate(int keyPressedCnt)
{
    if(nullptr == pCurBlocks_)
        return;
    
    pCurBlocks_->rotate(keyPressedCnt);
}

//void MapMgr::drop()
//{
//    //if(nullptr == pCurBlocks_)
//    //    return;
//
//    pCurBlocks_->drop();
//}

void MapMgr::autoMoveDown()
{
    if(nullptr == pCurBlocks_)
        return;
    
    pCurBlocks_->autoMoveDown();
}

bool MapMgr::checkUnderSomething(BLOCK* block[])
{
    // 일단, 접촉할 부분을 미리 골라내
    newBlockList_.clear();
    
    for(int i = 0; i < BLOCKCNT; ++i)
    {
        int exceptCnt = 0;
        for(int j = i; j< BLOCKCNT; ++j)
        {
            // 자기 자신인 경우
            if(block[i]->x_ == block[j]->x_
               && block[i]->y_ == block[j]->y_)
            {
                continue;
            }

            // 같은 열이 아닌 경우
            if(block[i]->x_ != block[j]->x_)
            {
                continue;
            }

            // 자신 아래에 블럭이 있는 경우
            if((block[i]->y_ - BLOCKCNT) == block[j]->y_)
            {
                exceptCnt += 1;
            }
        }
        
        if(0 == exceptCnt)
         {
             // 자신 아래에 블럭이 없는 경우!
             newBlockList_.emplace_back(block[i]);
         }
    }
    
    // 접촉 가능성 있는 블록만 for문을 통해, 맵 아래에 접촉될 블럭이 있는지를 조사한다.
    for(auto& newBlock : newBlockList_)
    {
        int colIndex = newBlock->x_ / BLOCKSIZE - 1;
        int rowIndex = newBlock->y_ / BLOCKSIZE;
        
        for(int i = 0; i < rowIndex; ++i)
        {
            if(true == isExisting_[i][colIndex]) // 맵 아래에 블록이 있으면
            {
                return true;
            }
        }
    }
    
    return false;
}

void MapMgr::getMaxRowOfUnderBlock(int* dist)
{
    std::vector<int> underBlock;
    int blankCnt = 0;
    
    for(auto& newBlock : newBlockList_)
    {
        int colIndex = newBlock->x_ / BLOCKSIZE - 1;
        int rowIndex = newBlock->y_ / BLOCKSIZE;
        
        for(int i = 0; i < rowIndex; ++i)
        {
            if(false == isExisting_[i][colIndex])
            {
                blankCnt += 1;
                continue;
            }
            
            int dist = rowIndex - i;
            underBlock.emplace_back(dist);
        }
        
        // j 의 경우
        if(rowIndex == blankCnt)
        {
            underBlock.emplace_back(rowIndex + 1);
            blankCnt = 0;
        }
    }
    
    int minDist = (*min_element(underBlock.begin(), underBlock.end())) * BLOCKSIZE;
    *dist = minDist;
}

bool MapMgr::checkCanChange(float x, float y)
{
    int colIndex = x / BLOCKSIZE - 1;
    int rowIndex = y / BLOCKSIZE;
    
    if(true == isExisting_[rowIndex][colIndex])
    {
        return false;
    }
    
    return true;
}

void MapMgr::includeGridMapBlocks(cocos2d::Sprite* sprite)
{
    sprite->retain();
    
    Vec2 pos = sprite->getPosition();
    int rowIndex = pos.y / BLOCKSIZE;
    int colIndex = pos.x / BLOCKSIZE - 1;
    
    // 게임 오버 체크 -> 더이상 맵 배열에 넣을 수 없을 때
    if(MAP_HEIGHT <= rowIndex)
    {
        gameState_ = OVER;
        return;
    }
    
    gridMapBlocks_[rowIndex][colIndex] = sprite;
    
}

void MapMgr::checkIsExisting(cocos2d::Sprite* sprite, bool isExist)
{
    Vec2 pos = sprite->getPosition();
    int rowIndex = pos.y / BLOCKSIZE;
    int colIndex = pos.x / BLOCKSIZE - 1;
    
    if(MAP_HEIGHT <= rowIndex)
    {
        gameState_ = OVER;
        return;
    }
    
    isExisting_[rowIndex][colIndex] = isExist;
}

void MapMgr::reset()
{
    if(nullptr != pCurBlocks_)
        return;
    
    std::list<int> rowList;
    checkLineFull(&rowList);
    
    if(true == rowList.empty())
        return;
    
    
    rowList.reverse();
    
    // 라인 삭제
    for(auto& row : rowList)
    {
        deleteLine(row);
        
        //한 줄 내려오기
        for(int i = row + 1; i< MAP_HEIGHT; ++i)
        {
            if(MIN_HEIGHT > i -1)
                continue;
                    
            for(int col = 0; col< MAP_WIDTH; ++col)
            {
                gridMapBlocks_[i - 1][col] = gridMapBlocks_[i][col];
                gridMapBlocks_[i][col] = nullptr;
                
                
                if(nullptr != gridMapBlocks_[i - 1][col])
                 {
                     int posY = gridMapBlocks_[i - 1][col]->getPositionY();
                     posY -= BLOCKSIZE;
                     gridMapBlocks_[i - 1][col]->setPositionY(posY);
                 }
                
                isExisting_[i - 1][col] = isExisting_[i][col];
                isExisting_[i][col] = false;
            }
        }
    }
    
    // 게임오버 체크
    if(true == checkGameOver())
    {
        gameState_ = OVER;
    }
}

void MapMgr::checkLineFull(std::list<int>* list)
{
    // 어느 라인이 없어질 라인인지 체크해서 변수에 넣어준다
    for(int row = 0; row< MAP_HEIGHT; ++row)
    {
        int cnt = 0;
        for(int col = 0; col< MAP_WIDTH; ++col)
        {
            if(false == isExisting_[row][col])
                break;
            
            cnt += 1;
        }
        
        if(MAP_WIDTH == cnt)
        {
            list->emplace_back(row);
        }
    }
}

void MapMgr::deleteLine(int row)
{
    for(int i = 0; i < MAP_WIDTH; ++i)
    {
        gridMapBlocks_[row][i]->removeFromParent();
        gridMapBlocks_[row][i] = nullptr;
        
        isExisting_[row][i] = false;
    }
    
    // 점수 체크
    DataMgr::getInstance()->addScore(DELETELINE_SCORE);
    // 라인 수 체크
    DataMgr::getInstance()->setLineCnt();
}

bool MapMgr::checkGameOver()
{
    if(nullptr != pCurBlocks_)
        return false;
    
    // 마지막 칸이 다 찬 경우
    int blockCnt = std::count(isExisting_[MAP_HEIGHT - 1].begin(), isExisting_[MAP_HEIGHT - 1].end(), true);
    if(MAP_WIDTH == blockCnt)
    {
        return true;
    }
    
    return false;
}
