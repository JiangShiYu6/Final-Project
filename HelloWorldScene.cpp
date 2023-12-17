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

// on "init" you need to initialize your instance
//bool HelloWorld::init()
//{
    /*//////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    return true;*/
    /*
    if (!Scene::init())
    {
        return false;
    }
    numberOfLoadedRes = 0;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto background = Sprite::create("welcome01.jpg");
    background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
    addChild(background);
    // 定时更新，用于检测资源是否被加载完成，如果加载完成才跳入到正真的欢迎页面。
    schedule(CC_SCHEDULE_SELECTOR(HelloWorld::logic), 1.0f);


    return true;
}*/


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
    if (numberOfLoadedRes == 100)
    {
        unschedule(CC_SCHEDULE_SELECTOR(HelloWorld::loadSource));
        switchToWelcomeScene();
    }
}

void HelloWorld::switchToWelcomeScene()
{
    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, WelcomeScene::createScene()));
}



