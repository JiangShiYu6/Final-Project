#include "SimpleAudioEngine.h"
#include"baseMap.h"
#include"baseHero.h"
#include"basemonster.h"
const int SKILL_BUTTON_TAG = 1001;  //定义一个标签
const float SKILL_COOLDOWN_TIME = 5.0f;
BaseCharacter::BaseCharacter() : currHp(100),maxHp(100), attackPower(0) {}

BaseCharacter::~BaseCharacter() {}

bool BaseCharacter::init() {
    if (!Sprite::init()) {
        return false;
    }
    
    // 初始化血条
    healthBar = ProgressTimer::create(Sprite::create("hp_bar.png"));
   
    healthBar->setType(ProgressTimer::Type::BAR);
    healthBar->setMidpoint(Vec2(0, 0.5)); // 从左到右填充
    healthBar->setBarChangeRate(Vec2(1, 0)); // 水平填充
    healthBar->setPercentage(100); // 初始血量为100%
   
    this->addChild(healthBar); // 添加到角色节点
    deleteButton = ui::Button::create("CloseNormal.png", "CloseSelect.png");
   
    deleteButton->addTouchEventListener(CC_CALLBACK_2(BaseCharacter::onDeleteButtonClicked, this));
    this->addChild(deleteButton);
    this->schedule(CC_SCHEDULE_SELECTOR(BaseCharacter::update), 0.1f);
    

    return true;
}

//属性
void BaseCharacter::initCharacterAttributes(float health, float attackPower,float range,float Cooldown) {
    this->maxHp = health;
    this->currHp = health;
    this->attackPower = attackPower;
    this->attackRange = range;
    this->attackCooldown = Cooldown;
    this->lastAttackTime = 0;
    this->isAttacking = false;
    this->isPlaying = false;
}


//受伤逻辑
void BaseCharacter::takeDamage(float damage) {
    if (wudi)
        damage = 0;
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
        auto currentMap = dynamic_cast<baseMap*>(this->getScene());
        currentMap->removeCharacters(this);
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

void BaseCharacter::onDeleteButtonClicked(Ref* sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
        // 删除角色
        auto currentMap = dynamic_cast<baseMap*>(this->getScene());
        if (currentMap) {
            currentMap->removeCharacters(this);
            this->removeFromParent();
        }
    }
}

void BaseCharacter::findTargetInRange() {
    auto currentScene = dynamic_cast<baseMap*>(this->getScene());
    if (currentScene) {
        int currentFrame = Director::getInstance()->getTotalFrames();
        for (auto monster : currentScene->activeMonsters) {
            if (monster->gethp() <= 0)
                break;
            float distance = this->getPosition().distance(monster->getPosition());
            if (distance <= this->attackRange) {
                isAttacking = true;
                if(currentFrame - lastAttackTime >= attackCooldown) {
                    monster->takedamage(getattackPower());
                    lastAttackTime = currentFrame;  // 更新上次攻击的帧数

                }
               
                return;
                
            }
        }
        isAttacking = false;
        isPlaying = false;
    }
    
   
}

void BaseCharacter::update(float dt) {

    // 检测攻击范围内的目标
    if (currHp <= 0) {
        auto currentMap = dynamic_cast<baseMap*>(this->getScene());
        currentMap->removeCharacters(this);
        playDeathAnimationAndRemove();
    }
    findTargetInRange();

    if (!isPlaying) {
        if (isAttacking) {

            this->playAttackAnimation();
            isPlaying = true;
        }
        else {
            stopAllActions();
        }
    }
}  

float BaseCharacter::getattackPower() const{
    return this->attackPower;
}

bool BaseCharacter::initManaBar(const std::string& manaBarImage) {
    maxMana = 100; // 设置最大蓝条值
    currentMana = 0; // 初始蓝条值

    // 创建并初始化蓝条
    manaBar = ProgressTimer::create(Sprite::create(manaBarImage));
    manaBar->setType(ProgressTimer::Type::BAR);
    manaBar->setMidpoint(Vec2(0, 0.5)); // 从左到右填充
    manaBar->setBarChangeRate(Vec2(1, 0));
    manaBar->setPercentage(0); // 初始蓝条为0%
    manaBar->setPosition(Vec2(this->getContentSize().width / 2,
        this->getContentSize().height/2+10)); // 设置位置
    this->addChild(manaBar);

    // 设置每秒更新蓝条的定时器
    this->schedule(CC_SCHEDULE_SELECTOR(BaseCharacter::updateMana), 1.0f);

    // 添加点击事件监听
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [this](Touch* touch, Event* event) {
        if (manaBar->getBoundingBox().containsPoint(touch->getLocation())) {
            this->onManaBarClicked();
            return true;
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, manaBar);

    return true;
}

void BaseCharacter::onManaBarClicked() {
    if (currentMana >= maxMana) {
        this->castSkill();
        currentMana = 0; // 释放技能后重置蓝条值
        manaBar->setPercentage(0);
    }
}

void BaseCharacter::updateMana(float dt) {
    currentMana += 10; // 每秒增加10%
    if (currentMana > maxMana) {
        currentMana = maxMana;
        showSkillButton();  // 当技能条满时显示技能按钮
    }
    manaBar->setPercentage((currentMana / maxMana) * 100);
}

void BaseCharacter::createSkillButton() {
    skillButton = ui::Button::create("skill_button.png");
    skillButton->setPosition(Vec2(0, this->getContentSize().height / 2));
    skillButton->addTouchEventListener(CC_CALLBACK_2(BaseCharacter::onSkillButtonClicked, this));
    skillButton->setVisible(false);
    this->addChild(skillButton);
}

void BaseCharacter::showSkillButton() {
    if (currentMana >= maxMana) {
        skillButton->setVisible(true);
    }
}



void BaseCharacter::onSkillButtonClicked(Ref* sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
        if (currentMana >= maxMana) {
            castSkill();       // 实现技能效果
            currentMana = 0;   // 重置技能条
            manaBar->setPercentage(0);
            skillButton->setVisible(false);  // 隐藏技能按钮
            startSkillCooldown(SKILL_COOLDOWN_TIME); // 开始技能冷却
        }
    }
}

void BaseCharacter::startSkillCooldown(float cooldownTime) {
    // 冷却期间技能条不能增长
    this->unschedule(CC_SCHEDULE_SELECTOR(BaseCharacter::updateMana));

    // 设置一个定时器，在冷却时间结束后再次启用技能条的更新
    this->scheduleOnce([this](float dt) {
        // 重新启动技能条的更新
        this->schedule(CC_SCHEDULE_SELECTOR(BaseCharacter::updateMana), 1.0f);

        // 重新检查技能条是否已满，如果满了则显示技能按钮
        this->showSkillButton();
        }, cooldownTime, "cooldownTimer");
}

void BaseCharacter::createUpButton() {
    upButton = ui::Button::create("uplevel.png");
    upButton->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2 + 50));
    upButton->addTouchEventListener(CC_CALLBACK_2(BaseCharacter::onlevelupClicked, this));
    this->addChild(upButton);
}

void BaseCharacter::onlevelupClicked(Ref* sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
        auto currentMap = dynamic_cast<baseMap*>(this->getScene());
        if (!isAttacking&&currentMap->comsuption(cost02)) {
            levelup();       // 实现升级效果
            if (level == 3)
                upButton->setVisible(false);  // 隐藏技能按钮
        }
    }
}


