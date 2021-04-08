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
    
private:
    std::vector<cocos2d::Vec2> loadInfoVec_;
    int specialBlockCnt_;
    
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
    int getSpecialBlockCnt() { return specialBlockCnt_; }
    std::vector<cocos2d::Vec2> getLoadInfoVec() { return loadInfoVec_; }
    
public:
    bool updateData();
    void addScore(int score) { score_ += score; }
    void addLineCnt() { lineCnt_ += 1; }
    void addItemCnt() { itemCnt_ += 1; }
    void minusItemCnt() { itemCnt_ -= 1; }
    
public:
    bool loadData();
    
    
private:
    DataMgr();
    ~DataMgr();
};


