#pragma once

#include "cocos2d.h"

class ToolScene : public cocos2d::Scene
{
public:
    static ToolScene* create();
    
public:
    virtual bool init() override;   
    
public:
    ToolScene();
    ~ToolScene();
};


