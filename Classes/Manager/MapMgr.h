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
    std::vector<Blocks*>  blocks[MAP_HEIGHT];
    Blocks* pCurBlocks;
    
public:
    static MapMgr* getInstance();
    static void destroyInstance();
    
public:
    void init();
    
public:
    void setIsDrop(bool isDrop);
    
public:
    Blocks* makeNewBlocks();
    void move(int dir);
    void rotate(int dir, int keyPressedCnt);
    void drop();
    
private:
    MapMgr();
    ~MapMgr();
};


