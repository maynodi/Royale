//
//  TitleLobbyLayer.h
//  NewGame
//
//  Created by CD-hj0949 on 2021/03/11.
//

#pragma once

#include "cocos2d.h"

class TitleLobbyLayer : public cocos2d::Layer
{
private:
    int menuFontSize_;
    
public:
    static TitleLobbyLayer* create();
    
public:
    virtual bool init() override;
    
private:
    void newPlayMenuClick(Ref* pSender);
    void loadPlayMenuClick(Ref* pSender);
    void loadMenuClick(Ref* pSender);
    void toolMenuClick(Ref* pSender);
    
public:
    TitleLobbyLayer();
    ~TitleLobbyLayer();
};


