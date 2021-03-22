#pragma once

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
public:
    static GameScene* create();
    
public:
    virtual bool init() override;
    
public:
    GameScene();
    ~GameScene();
};
