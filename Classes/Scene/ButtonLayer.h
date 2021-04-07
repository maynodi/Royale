#pragma once

#include "cocos2d.h"

class ButtonLayer : public cocos2d::LayerColor
{
private:
    int menuFontSize_;
    
public:
    static ButtonLayer* create();
    
public:
    virtual bool init() override;
    
private:
    void clickSaveButton(Ref* pSender);
    void clickGoToMenuButton(Ref* pSender);
    
public:
    ButtonLayer();
    ~ButtonLayer();
};


