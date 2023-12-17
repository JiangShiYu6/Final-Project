
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    static const int LoadingBarTag = 123;
    virtual bool init();

    // a selector callback
    void switchToWelcomeScene();
    void loadSource(float dt);
    void logic(float dt);
    int numberOfLoadedRes;

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};
#endif// __HELLOWORLD_SCENE_H__
