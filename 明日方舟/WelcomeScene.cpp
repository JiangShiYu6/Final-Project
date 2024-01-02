#include "SimpleAudioEngine.h"
#include "WelcomeScene.h"
#include "MainScene.h"
USING_NS_CC;

Scene* WelcomeScene::createScene()
{
    return WelcomeScene::create();
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
bool WelcomeScene::init() {
   
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    replaceItem = MenuItemImage::create(
        "StartNormal.jpg",
        "StartNormal.jpg",
        CC_CALLBACK_1(WelcomeScene::menuReplaceCallback, this));
    replaceItem->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 8);
    

    auto menu = Menu::create(replaceItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
   
    auto Mysprite = Sprite::create("welcome02.jpg");
    if (Mysprite == nullptr)
    {
        problemLoading("'welcome02.jpg'");
    }
    else
    {
        Mysprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(Mysprite, 0);
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/helloworld.mp3", true);
    return true;
}

void WelcomeScene::menuReplaceCallback(Ref* pSender) {
    // 创建缩小动画
    auto scaleToSmall = ScaleTo::create(0.1f, 0.9f); // 缩小到 90% 的大小
    auto scaleToNormal = ScaleTo::create(0.1f, 1.0f); // 恢复到原始大小
    auto sequence = Sequence::create(scaleToSmall, scaleToNormal, nullptr);
    // 将缩小动画关联到菜单项
    replaceItem->runAction(sequence);
    stopAllActions();
    Director::getInstance()->replaceScene(TransitionFade::create(3, MainScene::createScene()));
}
