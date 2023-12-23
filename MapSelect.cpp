#include "SimpleAudioEngine.h"
#include"MapSelect.h"
#include"MainScene.h"
USING_NS_CC;

bool MapSelect::init() {
    if (!Scene::init()) 
        return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 创建一个按钮
    auto button = cocos2d::ui::Button::create("CloseNormal.png", "CloseSelected.png");
    button->setPosition(cocos2d::Vec2(15, 5+origin.y + visibleSize.height - button->getContentSize().height));
    button->addTouchEventListener(CC_CALLBACK_2(MapSelect::onButtonClicked, this));
    this->addChild(button);

    return true;
}
void MapSelect::onButtonClicked(Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
        // 切换到主界面场景

        cocos2d::Director::getInstance()->replaceScene(TransitionFade::create(1, MainScene::createScene()));
    }
}