#include "SimpleAudioEngine.h"
#include"MapSelect.h"
#include"PlayScene.h"
#include"PlayScene01.h"
#include"PlayScene02.h"
#include"MainScene.h"
USING_NS_CC;

bool MapSelect::init() {
    if (!Scene::init()) 
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto Mysprite = Sprite::create("MAPS.jpg");
    Mysprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(Mysprite);
    // 创建一个按钮
    auto button = ui::Button::create("CloseNormal.png", "CloseSelected.png");
    button->setPosition(Vec2(15, 5+origin.y + visibleSize.height - button->getContentSize().height));
    button->addTouchEventListener(CC_CALLBACK_2(MapSelect::onButtonClicked, this));
    this->addChild(button);
    //地图1的菜单
    map_01_Item = MenuItemImage::create(
        "map_01_S.png",
        "map_01_S.png",
        CC_CALLBACK_1(MapSelect::menu_Map_01, this));
    map_01_Item->setPosition(visibleSize.width / 5 + origin.x, origin.y + (visibleSize.height / 2));
    auto menu1 = Menu::create(map_01_Item, NULL);
    menu1->setPosition(Vec2::ZERO);
    this->addChild(menu1, 1);
    //地图2的菜单
    map_02_Item = MenuItemImage::create(
        "map_2_S.png",
        "map_2_S.png",
        CC_CALLBACK_1(MapSelect::menu_Map_02, this));
    map_02_Item->setPosition(((visibleSize.width / 2)) + origin.x, origin.y+  (visibleSize.height / 2));
    auto menu2 = Menu::create(map_02_Item, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2, 1);
    onEnter();
    return true;
}
void MapSelect::onButtonClicked(Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
        // 切换到主界面场景

        cocos2d::Director::getInstance()->replaceScene(TransitionFade::create(1, MainScene::createScene()));
    }
}
void MapSelect::menu_Map_01(Ref* pSender) {
    Director::getInstance()->replaceScene(TransitionFade::create(2, PlayScene01::createScene()));
}
void MapSelect::menu_Map_02(Ref* pSender) {
    
        Director::getInstance()->replaceScene(TransitionFade::create(2, PlayScene02::createScene()));
    
   
}
void MapSelect::onEnter() {
    Scene::onEnter();

    // 读取用户的当前关卡进度
    int currentLevel = UserDefault::getInstance()->getIntegerForKey("currentLevel", 1);

    // 根据关卡进度启用或禁用第二关的选择按钮
    map_01_Item->setEnabled(true); // 第一关默认总是可用
    map_02_Item->setEnabled(currentLevel >= 2); // 第二关需要用户完成第一关
}

void MapSelect::unlockLevel() {
    
    map_02_Item->setEnabled(true);
}
MapSelect* MapSelect::getInstance() {
    static MapSelect instance;
    return &instance;
}