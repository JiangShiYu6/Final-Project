#include "yuanshichong.h"
#include "xiaobing.h"
#include "dabing.h"
#include "dog.h"
#include "SimpleAudioEngine.h"
#include "PlayScene01.h"
USING_NS_CC;


cocos2d::Scene* PlayScene01::createScene() {

    return  PlayScene01::create();
}

bool PlayScene01::init() {
    if (!baseMap::init()) {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getWinSize();

    loadMap("map01.tmx",winSize);
    currentWave = 0;
    HP_land = 10;

    // 初始化路径点
    initPointsVector((map->getContentSize().height - visibleSize.height)); // 假设路径点偏移量为10
    // 初始化远程和近战炮塔的位置
    initTowers_yuanVector((map->getContentSize().height - visibleSize.height)); // 假设远程炮塔点位的偏移量为10
    initTowers_jinVector((map->getContentSize().height - visibleSize.height));  // 假设近战炮塔点位的偏移量为10

    // 初始化敌人波次信息
    this->initEnemyWaves();
    
    // 安排 update 方法定时调用
    
    this->schedule(CC_SCHEDULE_SELECTOR(baseMap::update), 0.1f);
    
    return true;
}

void PlayScene01::initEnemyWaves() {
    wavesInfo.push_back(WaveInfo("Dog", 3, 3.0f));                   // 第一波：3个Shiyuanchong，每2秒一个
    wavesInfo.push_back(WaveInfo("Xiaobing", 2, 5.0f));             // 第二波：2个Xiaobing，每1.5秒一个
    wavesInfo.push_back(WaveInfo("Shiyuanchong", 3, 2.0f));          // 第三波：3个Dog，每1秒一个
}




