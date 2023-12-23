#pragma once
#include "cocos2d.h"

class MainScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void menuReplaceCallback_map(cocos2d::Ref* pSender);
    void menuReplaceCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
};

