#pragma once
#include "ui/CocosGUI.h"
#include "cocos2d.h"


class MapSelect : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene() {
        return MapSelect::create();
    }

    virtual bool init();
    CREATE_FUNC(MapSelect);

private:
    void onButtonClicked(Ref* sender, cocos2d::ui::Widget::TouchEventType type);
        
    
};

