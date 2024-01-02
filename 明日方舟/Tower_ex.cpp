#include"Tower_ex.h"
#include "SimpleAudioEngine.h"
#include"MainScene.h"
USING_NS_CC;

Scene* Tower_ex_Scene::createScene()
{
    return Tower_ex_Scene::create();
}

bool Tower_ex_Scene::init() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto BG = Sprite::create("Select_bg.jpg");
    BG->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(BG);
    // 创建按钮
    auto button = cocos2d::ui::Button::create("CloseNormal.png", "CloseSelected.png");
    button->setPosition(cocos2d::Vec2(15, 5 + origin.y + visibleSize.height - button->getContentSize().height));
    button->addTouchEventListener(CC_CALLBACK_2(Tower_ex_Scene::onButtonClicked, this));
    this->addChild(button);

    Tower01= MenuItemImage::create(
        "ami.jpg",
        "ami.jpg",
        CC_CALLBACK_1(Tower_ex_Scene::Tower,this));
    Tower01->setPosition(visibleSize.width / 5 + origin.x, 3 * (visibleSize.height / 4));
    auto menu1 = Menu::create(Tower01, NULL);
    menu1->setPosition(Vec2::ZERO);
    this->addChild(menu1, 1);

    Tower02 = MenuItemImage::create(
        "qieer.jpg",
        "qieer.jpg",
        CC_CALLBACK_1(Tower_ex_Scene::Tower,this));
    Tower02->setPosition(2*visibleSize.width / 5 + origin.x, 3 * (visibleSize.height / 4));
    auto menu2 = Menu::create(Tower02, NULL);
    menu2->setPosition(Vec2::ZERO);
    this->addChild(menu2, 1);

    Tower03 = MenuItemImage::create(
        "heijiao.jpg",
        "heijiao.jpg",
        CC_CALLBACK_1(Tower_ex_Scene::Tower, this));
    Tower03->setPosition(3 * visibleSize.width / 5 + origin.x, 3 * (visibleSize.height / 4));
    auto menu3 = Menu::create(Tower03, NULL);
    menu3->setPosition(Vec2::ZERO);
    this->addChild(menu3, 1);

    Tower04 = MenuItemImage::create(
        "jijing.jpg",
        "jijing.jpg",
        CC_CALLBACK_1(Tower_ex_Scene::Tower, this));
    Tower04->setPosition( visibleSize.width / 5 + origin.x, 1 * (visibleSize.height / 4));
    auto menu4 = Menu::create(Tower04, NULL);
    menu4->setPosition(Vec2::ZERO);
    this->addChild(menu4, 1);

    Tower05 = MenuItemImage::create(
        "hemo.jpg",
        "hemo.jpg",
        CC_CALLBACK_1(Tower_ex_Scene::Tower, this));
    Tower05->setPosition(2 * visibleSize.width / 5 + origin.x, 1 * (visibleSize.height / 4));
    auto menu5 = Menu::create(Tower05, NULL);
    menu5->setPosition(Vec2::ZERO);
    this->addChild(menu5, 1);

    Tower06 = MenuItemImage::create(
        "lapu.jpg",
        "lapu.jpg",
        CC_CALLBACK_1(Tower_ex_Scene::Tower, this));
    Tower06->setPosition(3 * visibleSize.width / 5 + origin.x, 1 * (visibleSize.height / 4));
    auto menu6 = Menu::create(Tower06, NULL);
    menu6->setPosition(Vec2::ZERO);
    this->addChild(menu6, 1);

    return true;
}

void Tower_ex_Scene::Tower(Ref* pSender) {
    auto menuItem = dynamic_cast<MenuItemImage*>(pSender); // 这样获取触发事件的MenuItemImage对象
    if (!menuItem) return; // 安全检查

    auto scaleToSmall = ScaleTo::create(0.1f, 0.9f); // 缩小到 90% 的大小
    auto scaleToNormal = ScaleTo::create(0.1f, 1.0f); // 恢复到原始大小
    auto sequence = Sequence::create(scaleToSmall, scaleToNormal, nullptr);
    // 将缩小动画关联到菜单项
    menuItem->runAction(sequence); // 这里应该使用menuItem，而不是T
    stopAllActions();
    if(menuItem== Tower01)
        Director::getInstance()->replaceScene(TransitionFade::create(1, MainScene::createScene()));
    else if (menuItem == Tower02)
        Director::getInstance()->replaceScene(TransitionFade::create(1, MainScene::createScene()));
    else if (menuItem == Tower03)
        Director::getInstance()->replaceScene(TransitionFade::create(1, MainScene::createScene()));
    else if (menuItem == Tower04)
        Director::getInstance()->replaceScene(TransitionFade::create(1, MainScene::createScene()));
    else if (menuItem == Tower05)
        Director::getInstance()->replaceScene(TransitionFade::create(1, MainScene::createScene()));
    else if (menuItem == Tower06)
        Director::getInstance()->replaceScene(TransitionFade::create(1, MainScene::createScene()));

}

void Tower_ex_Scene::onButtonClicked(Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
    // 检查触摸事件是否结束，也就是用户是否松开了按钮
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
        // 切换到主界面场景
        cocos2d::Director::getInstance()->replaceScene(TransitionFade::create(1, MainScene::createScene()));
    }
}


