#pragma once
#include "cocos2d.h"

class WelcomeScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    cocos2d::MenuItemImage* replaceItem; // 菜单项
    bool isScaling; // 标志位，用于防止重复点击
    void menuReplaceCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(WelcomeScene);
};

