#pragma once
#include "cocos2d.h"
#include"basemonster.h"
#include"baseHero.h"
#include "ui/CocosGUI.h"
struct WaveInfo {
    std::string monsterType; // 怪物类型
    int count;               // 这种怪物的数量
    float spawnInterval;     // 怪物生成的时间间隔

    WaveInfo(const std::string& type, int cnt, float interval)
        : monsterType(type), count(cnt), spawnInterval(interval) {}
};

class BaseMonster;
class baseMap : public cocos2d::Scene {
public:
    
    static cocos2d::Scene* createScene();

    virtual bool init();
    

    // 地图相关
    void loadMap(const std::string& mapFileName, cocos2d::Size winSize);
    

    // 资源
    void addCoins();
    void updateCoins(float dt);
    //void spendCoins(int amount);

    //路径和点位
    void initPointsVector(float offX);//初始化路径
    void initTowers_yuanVector(float off_position);//初始化远程点位
    void initTowers_jinVector(float off_position);//初始化近战点位

    // 炮塔管理
    void initCharacterVector();
    void initCharacterIcons(); // 初始化角色图标
    void createCharacterAtPosition(const Vec2& position, std::string name);
    bool isValidPosition(const Vec2& position, const std::string& name);

    //void placeTower(const Vec2& position, const std::string& towerType);//放置
    //void removeTower(const Vec2& position);//消除炮塔
    //void upgradeTower(const Vec2& position);//升级炮塔

    // 敌人波次
    
    virtual void startEnemyWave(int waveNumber);
    virtual void initEnemyWaves();
    virtual void spawnMonster(std::string monsterType);
    void checkAndStartNextWave(); 
    void update(float dt);
    
    Vector<BaseMonster*> monsters;
    Vector<BaseMonster*> activeMonsters;
    Vector<BaseCharacter*> characters;

    //怪物死亡
    void removeActiveMonster(BaseMonster* monster);
    void removeCharacters(BaseCharacter* monster);
   
    
    // 游戏状态
    void checkGameOver();
    void onGameOver();
    void pauseGame(Ref* sender, ui::Widget::TouchEventType type);
    void resumeGame();
    void createPauseButton();
    
    void showExitModal();
    
    // UI交互
    //void showTowerOptions(const Vec2& position);
    //void updateUI();
    CREATE_FUNC(baseMap);
    // 事件处理
    //void onEnemyKilled(Enemy* enemy);
    //void onTowerPlaced(Tower* tower);
    
    int HP_land; // 生命值
    void HP_off() {
        HP_land--;
    }
    int point;
    //void updateMonsters(float dt);
    cocos2d::Vector<Node*> pointsVector;//路径
    cocos2d::Vector<Node*> tower_position_jin;//近战
    cocos2d::Vector<Node*> tower_position_yuan;//远程
protected:
    bool isPause;
    cocos2d::Label* hpLabel;//地图血量
    cocos2d::Label* Wave_num;//剩余波数字
    bool isWaveInProgress;
    int coins; // 资源
    int currentWave;//怪物波数
    std::vector<WaveInfo> wavesInfo;
    cocos2d::Label* coinsLabel;//资源标签
    cocos2d::Label* CD;//倒计时标签
    cocos2d::TMXTiledMap* map;//地图
    cocos2d::TMXLayer* bgLayer;//地图背景
    cocos2d::TMXObjectGroup* objects_road;//怪物移动路径
    cocos2d::TMXObjectGroup* objects_position01;//远程放置点位
    cocos2d::TMXObjectGroup* objects_position02;//近战放置点位
    cocos2d::TMXObjectGroup* objects_coin;//
    Vec2 originalPosition;
    
   
    
   
};

