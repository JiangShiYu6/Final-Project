#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
class Tower_ex_Scene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    void onButtonClicked(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    virtual bool init();
    cocos2d::MenuItemImage* Tower01;
    cocos2d::MenuItemImage* Tower02;
    cocos2d::MenuItemImage* Tower03;
    cocos2d::MenuItemImage* Tower04;
    cocos2d::MenuItemImage* Tower05;
    cocos2d::MenuItemImage* Tower06;
    void Tower(Ref* pSender);
    CREATE_FUNC(Tower_ex_Scene);
};
