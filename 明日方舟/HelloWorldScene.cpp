#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "WelcomeScene.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool HelloWorld::init()
{
    

    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto background = Sprite::create("welcome01.jpg");
    background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    addChild(background);

    // 创建进度条
    auto loadingBar = ui::LoadingBar::create("LoadingBarFile.png");
    loadingBar->setDirection(ui::LoadingBar::Direction::RIGHT);
    loadingBar->setPosition(Vec2(visibleSize.width / 2, 50));
    loadingBar->setPercent(0); // 初始化进度为0
    addChild(loadingBar);

    // 模拟资源加载，假设加载100个资源，每次加载一个资源，模拟进度增加
    schedule(CC_SCHEDULE_SELECTOR(HelloWorld::loadSource), 0.1f);

    return true;
}

void HelloWorld::loadSource(float dt)
{
    // 模拟资源加载
    numberOfLoadedRes++;

    // 更新进度条
    float progress = static_cast<float>(numberOfLoadedRes) / 100.0f; // 假设加载100个资源
    CCLOG("Loading Progress: %.2f%%", progress * 10);

    // 更新进度条的百分比
    auto loadingBar = dynamic_cast<ui::LoadingBar*>(getChildByTag(LoadingBarTag)); // 假设设置了LoadingBar的tag为LoadingBarTag
    if (loadingBar)
    {
        loadingBar->setPercent(progress * 100);
    }

    // 如果加载完成，切换到欢迎页面
    if (numberOfLoadedRes == 10)
    {
        unschedule(CC_SCHEDULE_SELECTOR(HelloWorld::loadSource));
        switchToWelcomeScene();
    }
}

void HelloWorld::switchToWelcomeScene()
{
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, WelcomeScene::createScene()));
}



