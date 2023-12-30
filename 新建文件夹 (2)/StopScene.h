#pragma once
#include "cocos2d.h"

class StopScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    cocos2d::MenuItemImage* backtoGameItem;              // 返回游戏界面项
    cocos2d::MenuItemImage* MapSelectItem;               // 返回选关界面项
    bool isScaling_01;                                   // 标志位，用于防止重复点击
    bool isScaling_02;                                   // 标志位，用于防止重复点击
    void MapSelectCallback(cocos2d::Ref* pSender);       //返回游戏界面
    void backtoGameCallback(cocos2d::Ref* pSender);      //返回选关界面
    
    CREATE_FUNC(StopScene);
};
