#pragma once

#include "cocos2d.h"

class TitleScene : public cocos2d::Scene
{
public:
    static TitleScene* create();
    
public:
    virtual bool init() override;
    
public:
    TitleScene();
    ~TitleScene();
};
