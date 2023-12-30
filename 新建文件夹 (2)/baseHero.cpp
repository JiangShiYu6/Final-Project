#include "SimpleAudioEngine.h"
#include"baseMap.h"
#include"baseHero.h"
#include"basemonster.h"

BaseCharacter::BaseCharacter() : currHp(0),maxHp(0), attackPower(0),blockCount(0) {}

BaseCharacter::~BaseCharacter() {}

bool BaseCharacter::init() {
    if (!Sprite::init()) {
        return false;
    }
    initMouseListener();
    // 初始化血条
    healthBar = ProgressTimer::create(Sprite::create("hp_bar.png"));
    healthBar->setType(ProgressTimer::Type::BAR);
    healthBar->setMidpoint(Vec2(0, 0.5));                           // 从左到右填充
    healthBar->setBarChangeRate(Vec2(1, 0));                        // 水平填充
    healthBar->setPercentage(100);                                 // 初始血量为100%
    healthBar->setPosition(Vec2(this->getContentSize().width / 2,
        this->getContentSize().height + 10));                      // 设置位置
    this->addChild(healthBar);                                     // 添加到角色节点
    this->scheduleUpdate();
    return true;
}

//属性
void BaseCharacter::initCharacterAttributes(float health, float attackPower, int blockCount,float range,float Cooldown) {
    this->maxHp = health;
    this->currHp = health;
    this->attackPower = attackPower;
    this->blockCount = blockCount;
    this->attackRange = range;
    this->lastAttackTime = 0;
    this->attackCooldown = Cooldown;
}


//受伤逻辑
void BaseCharacter::takeDamage(float damage) {
    currHp -= damage;
    if (currHp < 0) {
        currHp = 0;
    }
    
    //updateHealthDisplay();
    playHitAnimation();
    // 更新血条显示
    float healthPercentage = (currHp / maxHp) * 100;
    healthBar->setPercentage(healthPercentage);
    if (currHp <= 0) {
        // 当血量降至0时执行消失动画
        playDeathAnimationAndRemove();
    }
}

//受伤变红
void BaseCharacter::playHitAnimation() {
    // 创建一个变红的动作
    auto tintToRed = TintTo::create(0.1f, 255, 0, 0); // 持续时间0.1秒，颜色为红色

    // 创建一个动作，恢复到原始颜色
    auto tintToOriginal = TintTo::create(0.1f, 255, 255, 255); // 恢复时间和颜色

    // 创建一个序列动作，先变红，然后恢复原色
    auto sequence = Sequence::create(tintToRed, tintToOriginal, nullptr);

    // 运行这个动作
    this->runAction(sequence);
}

//死亡
void BaseCharacter::playDeathAnimationAndRemove() {
    // 创建一个渐隐动作
    auto fadeOut = FadeOut::create(1.0f); // 1.0秒的渐隐动画

    // 创建一个回调动作，在渐隐动作完成后移除角色
    auto removeSelf = CallFunc::create([this]() {
        this->removeFromParent();
        });

    // 创建一个序列动作，先渐隐，然后移除
    auto sequence = Sequence::create(fadeOut, removeSelf, nullptr);

    // 运行这个动作
    this->runAction(sequence);
}

//初始化鼠标事件
void BaseCharacter::initMouseListener() {
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(BaseCharacter::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void BaseCharacter::onMouseDown(Event* event) {
    EventMouse* e = (EventMouse*)event;
    auto currentMap = dynamic_cast<baseMap*>(this->getScene());
    if (currentMap) {
        currentMap->removeCharacters(this);
    }
    if (e->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
        // 当鼠标右键点击时，移除角色
        this->removeFromParent();
    }
   
}



bool BaseCharacter::findTargetInRange(float range) {
    auto currentScene = dynamic_cast<baseMap*>(this->getScene());
    if (currentScene) {
        for (auto monster : currentScene->activeMonsters) {
            float distance = this->getPosition().distance(monster->getPosition());
            if (distance <= range) {
                this->playAttackAnimation();
                monster->takedamage(getattackPower());
                return true; // 找到在攻击范围内的怪物
            }
        }
    }
    return false; // 没有找到在攻击范围内的怪物
}

void BaseCharacter::update(float dt) {
    if (Director::getInstance()->getTotalFrames() - lastAttackTime > attackCooldown) {
        // 检测攻击范围内的目标
        if (findTargetInRange(attackRange)) {
            // 执行攻击
            lastAttackTime = Director::getInstance()->getTotalFrames();
        }
        else {
            this->stopAllActions();
        }
    }
    
}

float BaseCharacter::getattackPower() {
    return this->attackPower;
}


