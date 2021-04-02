#pragma once

#include "cocos2d.h"

class DataMgr
{
public:
    static DataMgr* pInstance_;
 
private:
    int bestScore_;
    int score_;
    int level_;
    int lineCnt_;
    int limitLineCnt_;
    int itemCnt_;
    
public:
    static DataMgr* getInstance();
    static void destroyInstance();
    
public:
    void init();
    
public:
    int getBestScore() { return bestScore_; }
    int getScore() { return score_; }
    int getLevel() { return level_; }
    int getLineCnt() { return lineCnt_; }
    int getItemCnt() { return itemCnt_; }

public:
    bool updateData();
    void addScore(int score) { score_ += score; }
    void addLineCnt() { lineCnt_ += 1; }
    void addItemCnt() { itemCnt_ += 1; }
    void minusItemCnt() { itemCnt_ -= 1; }
    
private:
    DataMgr();
    ~DataMgr();
};


