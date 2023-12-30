#include "SimpleAudioEngine.h"
#include"baseMap.h"
#include "yuanshichong.h"
#include "xiaobing.h"
#include "dabing.h"
#include "dog.h"
#include"heijiao.h"
#include"amiya.h"
#include"lapu.h"
#include"hemo.h"
#include "ui/CocosGUI.h"
#include"MapSelect.h"
USING_NS_CC;




Scene* baseMap::createScene()
{
    return baseMap::create();
}

bool baseMap::init() {
    if (!Scene::init()) {
        return false;
    }

    // 设置游戏初始状态
    isPause = false;
    isWaveInProgress = false;
    point = 0;     //初始化对局分数
    coins = 0;     // 初始金币数量
    addCoins();    // 添加金币标签到场景
    // 创建并初始化血量和波数标签
    hpLabel = Label::createWithTTF("100", "fonts/Marker Felt.ttf", 24);
    hpLabel->setPosition(Vec2(600.0f, 710.0f));
    Wave_num = Label::createWithTTF("3/3", "fonts/Marker Felt.ttf", 24);
    Wave_num->setPosition(Vec2(460.0f, 710.0f));
    this->addChild(hpLabel, 1);
    this->addChild(Wave_num, 1);
    createPauseButton();
    //初始化总角色
    initCharacterVector();
    this->initCharacterIcons();
    




    return true;
}

// 地图相关
// 地图相关
void baseMap::loadMap(const std::string& mapFileName,cocos2d::Size winSize) {
    
    

    // 加载地图文件
    map = TMXTiledMap::create(mapFileName);
    

    // 获取并存储路径点对象组
    objects_road = map->getObjectGroup("road");
    objects_position01 = map->getObjectGroup("towers_yuan");
    objects_position02 = map->getObjectGroup("towers_jin");

    // 检查对象组是否存在
   

    // 加载并设置背景层
    bgLayer = map->getLayer("background");
    
    bgLayer->setAnchorPoint(Point(0.5f, 0.5f));
    bgLayer->setPosition(Point(winSize.width / 2, winSize.height / 2));

    this->addChild(map, -1); // 添加地图到当前场景
}

// 资源
void baseMap::updateCoins(float dt) {
    // 每次调用时增加一枚金币
    coins++;
    // 更新标签的文本来显示新的金币数量
    coinsLabel->setString("Coins: " + std::to_string(coins));
}

void baseMap::addCoins() {
    coins = 0;
    coinsLabel = cocos2d::Label::createWithTTF("Coins: 0", "fonts/Marker Felt.ttf", 24);
    coinsLabel->setPosition(cocos2d::Vec2(970, 185));
    this->addChild(coinsLabel);
    this->schedule(CC_SCHEDULE_SELECTOR(baseMap::updateCoins), 1.0f); // 每秒调用一次 updateCoins
}

//路径和点位
//初始化路径
void baseMap::initPointsVector(float off_position) {
    auto objectsValueMap = objects_road->getObjects(); // 获取所有路径点对象

    // 遍历每个对象并获取其坐标，添加到路径点向量中
    for (const auto& objectValue : objectsValueMap) {
        auto dict = objectValue.asValueMap();
        float x = dict["x"].asFloat();
        float y = dict["y"].asFloat() - off_position;
        auto pointNode = Node::create();
        pointNode->setPosition(Vec2(x, y)); // 设置节点位置
        pointsVector.pushBack(pointNode); // 将节点添加到向量中

    }
}

//初始化远程点位
void baseMap::initTowers_yuanVector(float off_position) {
    auto objectsValueMap = objects_position01->getObjects();

    for (const auto& objectValue : objectsValueMap) {
        auto dict = objectValue.asValueMap();
        float x = dict["x"].asFloat();
        float y = dict["y"].asFloat() - off_position;
        float width = dict["width"].asFloat();
        float height = dict["height"].asFloat();

        auto towerSpot = Node::create();
        towerSpot->setPosition(Vec2(x + width / 2, y + height / 2)); // 使点位居于对象的中心
        towerSpot->setContentSize(Size(width, height)); // 设置对象的大小
        tower_position_yuan.pushBack(towerSpot);
    }
}

//初始化近战点位
void baseMap::initTowers_jinVector(float off_position)
{
    auto objectsValueMap = objects_position02->getObjects();

    for (const auto& objectValue : objectsValueMap) {
        auto dict = objectValue.asValueMap();
        float x = dict["x"].asFloat();
        float y = dict["y"].asFloat() - off_position;
        float width = dict["width"].asFloat();
        float height = dict["height"].asFloat();

        auto towerSpot = Node::create();
        towerSpot->setPosition(Vec2(x + width / 2, y + height / 2)); // 使点位居于对象的中心
        towerSpot->setContentSize(Size(width, height)); // 设置对象的大小
        tower_position_jin.pushBack(towerSpot);
    }
}





void baseMap::removeActiveMonster(BaseMonster* monster) {
    if (!activeMonsters.empty()) {
        auto iter = std::find(activeMonsters.begin(), activeMonsters.end(), monster);
        if (iter != activeMonsters.end()) {
            activeMonsters.erase(iter);

            if (activeMonsters.empty() && isWaveInProgress) {
                // 当前波次的所有怪物都被移除
                currentWave++;
                isWaveInProgress = false;
            }
        }
    }
}

void baseMap::removeCharacters(BaseCharacter* monster) {
    if (!characters.empty()) {
        auto iter = std::find(characters.begin(), characters.end(), monster);
        if (iter != characters.end()) {
            characters.erase(iter);

        }
    }
}

void baseMap::initEnemyWaves() {
    
}



void baseMap::startEnemyWave(int waveNumber) {
    if (waveNumber >= wavesInfo.size()) {
        return; // 波次超出范围或已有波次正在进行
    }

    isWaveInProgress = true;
    
    this->unschedule("spawnMonster");
    // 定时生成这一波的怪物
    auto& wave = wavesInfo[waveNumber];
    this->schedule([this, waveNumber](float dt) {
        auto& wave = wavesInfo[waveNumber];
        spawnMonster(wave.monsterType);
        }, wave.spawnInterval, wave.count - 1, 0, "spawnMonster");
    

}




void baseMap::spawnMonster(std::string monsterType) {
    CCLOG("Spawning monster: %s", monsterType.c_str());
    BaseMonster* monster = nullptr;

    if (monsterType == "Shiyuanchong") {
        monster = Shiyuanchong::create(); // 创建Xiaobing
       
    }
    else if (monsterType == "Xiaobing") {
        monster = Xiaobing::create(); // 创建Xiaobing
       
    }
    else if (monsterType == "Dog") {
        monster = Dog::create(); // 创建Dog
       
    }

    if (monster) {
        
        monster->setMovementPath(pointsVector);
        monster->setPosition(pointsVector.at(0)->getPosition());
        this->addChild(monster, -1);
        activeMonsters.pushBack(monster);
    }

}

void baseMap::checkAndStartNextWave() {
    if (!isWaveInProgress && currentWave < wavesInfo.size()) {
        startEnemyWave(currentWave);
    }
}

void baseMap::update(float dt) {
    hpLabel->setString(std::to_string(10*HP_land));
    
    // 检查当前波次的怪物是否都已被消灭
    checkAndStartNextWave();

    Wave_num->setString(std::to_string(currentWave+1) + "/3");
}



//初始化角色动画集
void baseMap::initCharacterVector() {
    auto Characterheijiao = heijiao::create();
    heijiao::frameCache = SpriteFrameCache::getInstance();
    for (int i = 1; i <= 10; i++) {
        std::string frameName = StringUtils::format("heijiao_attack_%02d.png", i);
        heijiao::frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 40, 35)), frameName);
    }
    characters.pushBack(Characterheijiao);

    auto Characteramiya = amiya::create();
    amiya::frameCache = SpriteFrameCache::getInstance();
    for (int i = 1; i <= 13; i++) {
        std::string frameName = StringUtils::format("amiya_attack_%02d.png", i);
        amiya::frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 40, 35)), frameName);
    }
    characters.pushBack(Characteramiya);

    auto Characterlapu = lapu::create();
    lapu::frameCache = SpriteFrameCache::getInstance();
    for (int i = 1; i <= 7; i++) {
        std::string frameName = StringUtils::format("lapu_attack_%02d.png", i);
        lapu::frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 40, 35)), frameName);
    }
    characters.pushBack(Characterlapu);

    auto Characterhemo = heijiao::create();
    hemo::frameCache = SpriteFrameCache::getInstance();
    for (int i = 1; i <= 19; i++) {
        std::string frameName = StringUtils::format("hemo_attack_%02d.png", i);
        hemo::frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 40, 35)), frameName);
    }
    characters.pushBack(Characterhemo);

}

//初始化角色图标，其中包括放置角色逻辑
void baseMap::initCharacterIcons() {
    // 假设有一个角色图标数组amiya_attack_01.png
    std::vector<std::string> characterIcons = { "amiya_front.png","lapu_front.png","hemo_front.png","heijiao_front.png" };
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // 遍历角色图标数组
    for (int i = 0; i < characterIcons.size(); ++i) {
        auto icon = Sprite::create(characterIcons[i]);
        auto name = characterIcons[i];
        originalPosition=Vec2(970 - 74 * i, 100);
        icon->setPosition(Vec2(970 - 74 * i, 100));
        this->addChild(icon);
        
        // 为每个图标添加触摸事件监听器
        auto listener = EventListenerTouchOneByOne::create();
        
        listener->setSwallowTouches(true);

        listener->onTouchBegan = [icon,this](Touch* touch, Event* event) -> bool {
            if (isPause) {
                return false;
            }
            if (icon->getBoundingBox().containsPoint(touch->getLocation())) {
                icon->setOpacity(150); // 点击时变半透明
                return true;
            }
            return false;

        };

        listener->onTouchMoved = [icon, this](Touch* touch, Event* event) {
            if(!isPause)
            icon->setPosition(icon->getPosition() + touch->getDelta());
        };

        listener->onTouchEnded = [this,icon,name](Touch* touch, Event* event) {
            if (!isPause) {
                bool isPlaced = false;
                icon->setOpacity(255);
                if (name== "amiya_front.png" || name == "lapu_front.png" || name == "hemo_front.png") {
                    for (auto& towerSpot : tower_position_yuan) {
                        if (towerSpot->getBoundingBox().containsPoint(icon->getPosition())) {
                            isPlaced = true;
                            icon->setPosition(towerSpot->getPosition());
                            break;
                        }
                    }
                }
                else {
                    for (auto& towerSpot : tower_position_jin) {
                        if (towerSpot->getBoundingBox().containsPoint(icon->getPosition())) {
                            isPlaced = true;
                            icon->setPosition(towerSpot->getPosition());
                            break;
                        }
                    }
                }
                if (!isPlaced) {
                    icon->runAction(MoveTo::create(0.5, originalPosition));
                }
                else {
                    this->createCharacterAtPosition(icon->getPosition(), name);
                }
            }
        };

        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, icon);
        
    }
}

//在放置位置创建角色
void baseMap::createCharacterAtPosition(const Vec2& position, std::string name) {
    // 在这个位置创建角色
    if (name == "amiya_front.png") {
        auto character = amiya::create(); // 假设BaseCharacter有一个create方法
        character->setPosition(position);
        characters.pushBack(character);
        this->addChild(character);
    }
    else if (name == "heijiao_front.png") {
        auto character = heijiao::create(); // 假设BaseCharacter有一个create方法
        character->setPosition(position);
        characters.pushBack(character);
        this->addChild(character);
    }
    else if (name == "hemo_front.png") {
        auto character = hemo::create(); // 假设BaseCharacter有一个create方法
        character->setPosition(position);
        characters.pushBack(character);
        this->addChild(character);
    }
    else if (name == "lapu_front.png") {
        auto character = lapu::create(); // 假设BaseCharacter有一个create方法
        character->setPosition(position);
        characters.pushBack(character);
        this->addChild(character);
    }
    
}

//游戏结束判断
void baseMap::checkGameOver() {

    if (HP_land <= 0) {
        onGameOver();
    }
    else if (currentWave == 3 && activeMonsters.empty() && HP_land > 0)
    {
        onGameOver();
    }
    else
        return;
}

//游戏结束处理
void baseMap::onGameOver() {


    //std::string gameOverMessage = situation ? "Victory! Score: " + std::to_string(point) : "Defeat! Score: " + std::to_string(point);
    showExitModal();
    
    if (HP_land >= 100) {
        point = 3;
    }
    else if (HP_land < 100 && HP_land >= 70) {
        point = 2;
    }
    else if (HP_land < 70 && HP_land >0) {
        point = 1;
    }

    
    

}

// 暂停游戏
void baseMap::pauseGame(Ref* sender, ui::Widget::TouchEventType type) {
    
    if (type == ui::Widget::TouchEventType::ENDED) {
        // 检查游戏是否已经暂停
        if (!Director::getInstance()->isPaused()) {
            Director::getInstance()->pause();
            isPause = true;
            auto winSize = Director::getInstance()->getVisibleSize();
            auto modalLayer = LayerColor::create(Color4B(0, 0, 0, 100), winSize.width, winSize.height);
            modalLayer->setName("ModalLayer");

            // 使模态层接收所有触摸事件，阻止其他层的交互
            modalLayer->setTouchEnabled(true);
            modalLayer->setSwallowsTouches(true);

            auto resumeLabel = Label::createWithTTF("Resume", "fonts/Marker Felt.ttf", 24);
            resumeLabel->setPosition(modalLayer->getContentSize() / 2);

            // 为标签添加触摸事件监听器
            auto resumeListener = EventListenerTouchOneByOne::create();
            resumeListener->onTouchBegan = [this, resumeLabel](Touch* touch, Event* event) {
                if (resumeLabel->getBoundingBox().containsPoint(touch->getLocation())) {
                    this->resumeGame();
                    return true;
                }
                return false;
            };
            _eventDispatcher->addEventListenerWithSceneGraphPriority(resumeListener, resumeLabel);

            modalLayer->addChild(resumeLabel);

           

            auto exitLabel = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 24);
            exitLabel->setPosition(Vec2(490, 340)); // 设置合适的位置

            auto exitlistener = EventListenerTouchOneByOne::create();
            exitlistener->onTouchBegan = [this, exitLabel](Touch* touch, Event* event) {
                if (exitLabel->getBoundingBox().containsPoint(touch->getLocation())) {
                    this->showExitModal();
                    return true;
                }
                return false;
            };
            _eventDispatcher->addEventListenerWithSceneGraphPriority(exitlistener, exitLabel);
            
            modalLayer->addChild(exitLabel);

            this->addChild(modalLayer, INT_MAX);

            // 禁用暂停按钮
            auto pauseButton = dynamic_cast<ui::Button*>(this->getChildByName("PauseButton"));
            if (pauseButton) {
                pauseButton->setTouchEnabled(false);
                pauseButton->loadTextures("Pause_After.png", "Pause_After.png");
            }
            
        }
    }
}

// 恢复游戏
void baseMap::resumeGame() {
    Director::getInstance()->resume();
    isPause = false;
    // 移除模态层
    this->removeChildByName("ModalLayer");
    // 重新启用暂停按钮
    auto pauseButton = dynamic_cast<ui::Button*>(this->getChildByName("PauseButton"));
    if (pauseButton) {
        pauseButton->setTouchEnabled(true);
        pauseButton->loadTextures("Stop_Button.png", "Stop_Button.png");
    }
}

//创建暂停按钮
void baseMap::createPauseButton() {
    auto pauseButton = ui::Button::create("Stop_Button.png", "Stop_Button.png");
    pauseButton->setPosition(Vec2(965, 690));
    pauseButton->addTouchEventListener(CC_CALLBACK_2(baseMap::pauseGame, this));
    pauseButton->setName("PauseButton"); // 设置按钮的名称
    this->addChild(pauseButton, 1);
}

// 显示退出模态层
void baseMap::showExitModal() {
    this->removeChildByName("ModalLayer");
    auto Star1 = Sprite::create("star.png");
    Star1->setPosition(Vec2(150, 170));
    auto Star2 = Sprite::create("star.png");
    Star2->setPosition(Vec2(250, 170));
    auto Star3 = Sprite::create("star.png");
    Star3->setPosition(Vec2(350, 170));
    
    auto winSize = Director::getInstance()->getVisibleSize();
    auto modalLayer = LayerColor::create(Color4B(0, 0, 0, 100), winSize.width, winSize.height);
    modalLayer->setName("ExitModalLayer");
    auto backgroundSprite = Sprite::create("over.jpg"); 
    backgroundSprite->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    modalLayer->addChild(backgroundSprite);
    auto HERO = Sprite::create(); 
    HERO->setPosition(Vec2(18*winSize.width / 25, 9*winSize.height / 20)); 
    modalLayer->addChild(HERO);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);

    listener->onTouchBegan = [&](Touch* touch, Event* event) -> bool {
        Director::getInstance()->resume();
        Director::getInstance()->replaceScene(MapSelect::createScene());

        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, modalLayer);
    this->addChild(modalLayer, INT_MAX);

    switch (point) {
    case 3:
        HERO->setTexture("JJ_1.png");
        modalLayer->addChild(Star1);
        modalLayer->addChild(Star2);
        modalLayer->addChild(Star3);
        break;
    case 2:
        HERO->setTexture("LP_1.png");
        modalLayer->addChild(Star1);
        modalLayer->addChild(Star2);
       
    case 1:
        HERO->setTexture("AD_1.png");
        modalLayer->addChild(Star1);
        
        break;
    case 0:
        HERO->setTexture("HJ_1.png");
        
        break;
    default:
        return;
    }
        
}