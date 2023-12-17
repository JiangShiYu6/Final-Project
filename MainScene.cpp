#include "SimpleAudioEngine.h"
#include"MainScene.h"
#include"PlayScene.h"
#include"MapSelect.h"
USING_NS_CC;

Scene* MainScene::createScene()
{
    return MainScene::create();
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}
bool MainScene::init() {

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto begin_play_Item = MenuItemImage::create(
        
        "guanqiaSelect.png",
        "guanqiaSelect.png",
        CC_CALLBACK_1(MainScene::menuReplaceCallback_map, this));
    begin_play_Item->setPosition(7*(visibleSize.width / 10) + origin.x, 6*(visibleSize.height / 8));

    auto menu01 = Menu::create(begin_play_Item, NULL);
    menu01->setPosition(Vec2::ZERO);
    this->addChild(menu01, 1);

    auto player_explain_Item = MenuItemImage::create(
        "renwuexplain.png",
        "renxuexplain.png",
        CC_CALLBACK_1(MainScene::menuReplaceCallback, this));
    player_explain_Item->setPosition(8 * (visibleSize.width / 10) + origin.x, 3 * (visibleSize.height / 8));

    auto menu02 = Menu::create(player_explain_Item, NULL);
    menu02->setPosition(Vec2::ZERO);
    this->addChild(menu02, 1);
    auto AMiYa= Sprite::create("amiya.png");
    AMiYa->setPosition(2 * (visibleSize.width / 10) + origin.x, 3 * (visibleSize.height / 8));
    this->addChild(AMiYa, 1);
    auto Mysprite = Sprite::create("background01.png");
    if (Mysprite == nullptr)
    {
        problemLoading("'background01.png'");
    }
    else
    {
        Mysprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        this->addChild(Mysprite, 0);
    }
    return true;
}

void MainScene::menuReplaceCallback(Ref* pSender) {
    Director::getInstance()->replaceScene(TransitionFade::create(3, MapSelect::createScene()));
}

void MainScene::menuReplaceCallback_map(Ref* pSender) {
    Director::getInstance()->replaceScene(TransitionFade::create(3, PlayScene::createScene()));
}