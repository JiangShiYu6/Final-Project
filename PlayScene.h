#pragma once
#include "cocos2d.h"

class PlayScene : public cocos2d::Scene
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();
    void updateCoins(float dt); // 更新资源
    // implement the "static create()" method manually
    CREATE_FUNC(PlayScene);


private:
    cocos2d::Label* coinsLabel;
    cocos2d::Label* CD;
    cocos2d::TMXTiledMap* map;
    cocos2d::TMXLayer* bgLayer;
    cocos2d::TMXObjectGroup* objects_road;
    cocos2d::TMXObjectGroup* objects_position01;
    cocos2d::TMXObjectGroup* objects_position02;
    cocos2d::TMXObjectGroup* objects_coin;
    cocos2d::Vector<Node*> pointsVector;
    cocos2d::Vector<Node*> tower_position_jin;
    cocos2d::Vector<Node*> tower_position_yuan;
    void PlayScene::updateCountdown(float dt);
    int countdown;     // 倒计时
    bool enemyAppeared; // 记录精灵是否已经出现
    void initPointsVector(float offX);
    void initTowers_yuanVector(float off_position);
    void initTowers_jinVector(float off_position);
    int coins;//资源
    int HP_land;
};
