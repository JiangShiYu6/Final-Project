#include "SimpleAudioEngine.h"
#include"MapSelect.h"
#include"PlayScene.h"
#include"PlayScene01.h"
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
    map_01_Item->setPosition(visibleSize.width / 2 + origin.x, 4*(visibleSize.height / 8));
    auto menu1 = Menu::create(map_01_Item, NULL);
    menu1->setPosition(Vec2::ZERO);
    this->addChild(menu1, 1);
    map_02_Item = MenuItemImage::create(
        "map_02_S.png",
        "map_02_S.png",
        CC_CALLBACK_1(MapSelect::menu_Map_01, this));
    map_02_Item->setPosition((3*(visibleSize.width / 5)) + origin.x, 4 * (visibleSize.height / 8));
    auto menu2 = Menu::create(map_02_Item, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2, 1);

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
    Director::getInstance()->replaceScene(TransitionFade::create(2, PlayScene::createScene()));
}
void MapSelect::onEnter() {
    Scene::onEnter();
    currentLevel = UserDefault::getInstance()->getIntegerForKey("level", 1);

    // 根据关卡解锁情况更新按钮状态
    map_02_Item->setEnabled(currentLevel >= 2); // 假设2是第二关的关卡数
    // 你也可以修改按钮的外观来反映它们的状态
}
void MapSelect::unlockLevel(int level) {
    // 更新关卡数并保存
    currentLevel = level;
    UserDefault::getInstance()->setIntegerForKey("level", level);
    UserDefault::getInstance()->flush();
    // 更新界面
    // ...
}
