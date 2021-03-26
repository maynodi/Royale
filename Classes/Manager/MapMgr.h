//
//  MapMgr.h
//  myTetris
//
//  Created by CD-hj0949 on 2021/03/22.
//

#pragma once

#include "cocos2d.h"
#include "Define.h"

class Blocks;

class MapMgr
{
public:
    static MapMgr* pInstance_;
    
private:
    std::vector<bool> isExisting_[MAP_HEIGHT];
    std::vector<cocos2d::Sprite*>  gridMapBlocks_[MAP_HEIGHT];
    Blocks* pCurBlocks_;
    std::list<struct Block*> newBlockList_; // 맵의 블록과 부딪힐 가능성있는 블록 리스트
    GAMESTATE gameState_;
    
public:
    static MapMgr* getInstance();
    static void destroyInstance();
    
public:
    void init();
    
public:
    void setIsDrop(bool isDrop);
    void setNullCurBlocks() { pCurBlocks_ = nullptr; }
    
public:
    GAMESTATE getGameState() { return gameState_; }
    
public:
    void makeNewBlocks(int blockType);
    void move(int dir);
    void rotate(int keyPressedCnt);
    void drop();
    void autoMoveDown();
    
public:
    bool checkUnderSomething(struct Block* block[]);
    void getMaxRowOfUnderBlock(int* dist);
    bool checkCanChange(float x, float y);
    
public:
    void includeGridMapBlocks(cocos2d::Sprite*);
    void checkIsExisting(cocos2d::Sprite* sprite, bool isExist); // 맵배열 중 블럭의 유무를 bool로 결정하고 배열에 표시해주는 함수
    
public:
    void reset();
    void checkLineFull(std::list<int>* list);
    void deleteLine(int row);
    
public:
    bool checkGameOver();
    
private:
    MapMgr();
    ~MapMgr();
};


