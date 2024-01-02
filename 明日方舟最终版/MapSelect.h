#pragma once
#include "ui/CocosGUI.h"
#include "cocos2d.h"


class MapSelect : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene() {
        return MapSelect::create();
    }
    static MapSelect* getInstance();
    cocos2d::MenuItemImage* map_01_Item;
    cocos2d::MenuItemImage* map_02_Item;
    virtual bool init();
    void onEnter() override;
    void unlockLevel();
    CREATE_FUNC(MapSelect);

private:
    int currentLevel;
    void onButtonClicked(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
    void menu_Map_01(Ref* pSender);
    void menu_Map_02(Ref* pSender);
};

