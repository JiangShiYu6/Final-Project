#include "SimpleAudioEngine.h"
#include "PlayScene.h"
USING_NS_CC;
// 获取屏幕的可见大小和原点坐标
// 创建场景的静态方法
Scene* PlayScene::createScene()
{
    return PlayScene::create();
}

// 初始化场景
bool PlayScene::init() {
    // 获取屏幕的可见大小和原点坐标
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto winSize = Director::getInstance()->getWinSize();
    HP_land = 100;

    // 加载并设置地图
    map = TMXTiledMap::create("map01.tmx");
    bgLayer = map->getLayer("background");
    bgLayer->setAnchorPoint(Point(0.5f, 0.5f));
    bgLayer->setPosition(Point(winSize.width / 2, winSize.height / 2));
    //倒计时
    CD = cocos2d::Label::createWithTTF("3", "fonts/Marker Felt.ttf", 240);
    CD->setPosition(cocos2d::Point(winSize.width / 2, winSize.height / 2));
    this->addChild(CD);
    //资源
    coinsLabel = cocos2d::Label::createWithTTF("Coins: 0", "fonts/Marker Felt.ttf", 24);
    coinsLabel->setPosition(cocos2d::Vec2(970, 185));
    this->addChild(coinsLabel);
    
   

    coins = 0; // 初始化金币数量
    this->schedule(CC_SCHEDULE_SELECTOR(PlayScene::updateCoins), 1.0f); // 每秒调用一次 updateCoins
    
    // 获取并存储路径点对象组
    objects_road = map->getObjectGroup("road");
    objects_position01 = map->getObjectGroup("towers_yuan");
    objects_position02=map->getObjectGroup("towers_jin");
    this->addChild(map, -1);

    // 初始化路径点
    initPointsVector((map->getContentSize().height - visibleSize.height) / 2);
    initTowers_yuanVector((map->getContentSize().height - visibleSize.height) / 2);
    
    // 创建粒子系统
    auto particleSystem = ParticleFireworks::create();
    particleSystem->setPosition(pointsVector.at(0)->getPosition());
    this->addChild(particleSystem);
    particleSystem->setAutoRemoveOnFinish(true); // 粒子播放完后自动从场景中移除

    Vector<FiniteTimeAction*> moveAction;
    for (int i = 1; i < pointsVector.size(); ++i) {
        moveAction.pushBack(MoveTo::create(0.2f, pointsVector.at(i)->getPosition()));
    }

    // 添加一个回调动作，在路径走完后移除光线
    auto removeEnemy = CallFunc::create([particleSystem]() {
        particleSystem->removeFromParent(); // 从父节点中移除敌人精灵
        });
    moveAction.pushBack(removeEnemy);

    // 敌人执行动作序列
    auto seq = Sequence::create(moveAction);
    particleSystem->runAction(seq);



    // 初始化倒计时为3秒
    countdown = 3;       
    enemyAppeared = false; // 初始化精灵未出现
    // 创建一个计时器，每1秒钟调用一次 updateCountdown 方法
    this->schedule(CC_SCHEDULE_SELECTOR(PlayScene::updateCountdown), 1.0f);

    

    auto towerIcon = Sprite::create("sheshou.png"); // 炮塔图标
    towerIcon->setPosition(Vec2(970, 100)); // 设置初始位置
    this->addChild(towerIcon);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [towerIcon](Touch* touch, Event* event) {
        if (towerIcon->getBoundingBox().containsPoint(touch->getLocation())) {
            // 当触摸开始在炮塔图标上时
            return true; // 捕获触摸事件
        }
        return false;
    };

    touchListener->onTouchMoved = [this, towerIcon](Touch* touch, Event* event) {
        // 更新炮塔图标的位置
        towerIcon->setPosition(towerIcon->getPosition() + touch->getDelta());
    };

    touchListener->onTouchEnded = [this, towerIcon](Touch* touch, Event* event) {
        bool isPlaced = false;
        for (auto& towerSpot : tower_position_yuan) {
            if (towerSpot->getBoundingBox().containsPoint(towerIcon->getPosition())) {
                auto tower = Sprite::create("sheshou.png");
                tower->setPosition(towerSpot->getPosition());
                this->addChild(tower);
                isPlaced = true;
                break;
            }
        }
        if (!isPlaced) {
            
            CCLOG("Tower was not placed");
        }
        towerIcon->setPosition(Vec2(970, 100));
    };
    

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, towerIcon);

    return true;
}

// 初始化路径点向量
void PlayScene::initPointsVector(float off_position)
{
    auto objectsValueMap = objects_road->getObjects(); // 获取所有路径点对象

    // 遍历每个对象并获取其坐标，添加到路径点向量中
    for (const auto& objectValue : objectsValueMap) {
        auto dict = objectValue.asValueMap();
        float x = dict["x"].asFloat();
        float y = dict["y"].asFloat()- off_position;
        auto pointNode = Node::create();
        pointNode->setPosition(Vec2(x, y)); // 设置节点位置
        pointsVector.pushBack(pointNode); // 将节点添加到向量中
    }
}

void PlayScene::initTowers_yuanVector(float off_position)
{
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

void PlayScene::updateCoins(float dt) {
    coins++; // 每次调用时增加一枚金币
    // 更新标签的文本来显示新的金币数量
    coinsLabel->setString("Coins: " + std::to_string(coins));
}

void PlayScene::updateCountdown(float dt) {
    if (countdown >= 0) {
        
        if (countdown == 0) {
            auto fadeOut = FadeOut::create(1.0f); // 渐隐效果，持续1秒
            auto removeCD = CallFunc::create([this]() {
                CD->removeFromParent(); // 从父节点中移除倒计时标签
                });
            CD->runAction(Sequence::create(fadeOut, removeCD, nullptr));


            // 播放警告声音
            //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("warning_sound.mp3");
            
      
            
        }

        CD->setString(std::to_string(countdown));
        countdown--; // 每次减少一秒
        
    }
   
    else if (!enemyAppeared) {
        // 当倒计时结束且精灵尚未出现时，创建精灵并开始它的移动
        auto enemy = Sprite::create("chongziguai.png");
        if (pointsVector.size() > 0) {
            enemy->setPosition(pointsVector.at(0)->getPosition());
        }
        this->addChild(enemy);

        // 创建动作序列使敌人沿路径移动
        Vector<FiniteTimeAction*> moveActions;
        for (int i = 1; i < pointsVector.size(); ++i) {
            moveActions.pushBack(MoveTo::create(1.0f, pointsVector.at(i)->getPosition()));
        }

        // 添加一个回调动作，在路径走完后移除敌人精灵
        auto removeEnemy = CallFunc::create([enemy]() {
            enemy->removeFromParent(); // 从父节点中移除敌人精灵
            });
        moveActions.pushBack(removeEnemy);

        // 敌人执行动作序列
        auto seq = Sequence::create(moveActions);
        enemy->runAction(seq);

        enemyAppeared = true; // 设置精灵已经出现
        this->unschedule(CC_SCHEDULE_SELECTOR(PlayScene::updateCountdown));
    }

   

   
    
}
