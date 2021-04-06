#pragma once

#include "cocos2d.h"

class ParticleMgr
{
public:
    static ParticleMgr* pInstance_;
    
public:
    static ParticleMgr* getInstance();
    static void destroyInstance();
    
public:
    void init();
    
public:
    void particleSmog(cocos2d::Node* node, cocos2d::Vec2 pos);
    void particleExplosion(cocos2d::Node* node, cocos2d::Vec2 pos, cocos2d::Color3B color);
    
private:
    ParticleMgr();
    ~ParticleMgr();
};


