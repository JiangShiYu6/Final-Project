#include "SimpleAudioEngine.h"
#include"amiya.h"
#include"baseMap.h"
USING_NS_CC;


bool amiya::init() {
    // 首先调用基类的初始化
    if (!BaseCharacter::init()) {
        return false;
    }
    cost01 = 8;
    cost02 = 8;
    jinoryuan = 1;
    // 加载 heijiao 的纹理图像
    this->setTexture("amiya_attack_01.png");
    
    // 设置 heijiao 的初始属性
    this->initCharacterAttributes(500, 20, 150, 50);
    deleteButton->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height/2 +30));
    healthBar->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height/2+20));
    // ... 其他属性设置
    if (!initManaBar("blue.png")) {
        return false;
    }
    // 如果有特殊行为或动画，也可以在这里设置
    frameCache = SpriteFrameCache::getInstance();
    for (int i = 1; i <= 13; i++) {
        std::string frameName = StringUtils::format("amiya_attack_%02d.png", i);
        amiya::frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 200, 200)), frameName);
    }
    for (int i = 3; i <= 15; i++) {
        std::string frameName = StringUtils::format("AmiyaRight%d.png", i);
        amiya::frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 200, 200)), frameName);
    }
    createSkillButton();
    createUpButton();
    return true;
}

void amiya::playAttackAnimation() {
    Vector<SpriteFrame*> attackFrames;
    if (level == 1) {
        
        for (int i = 1; i <= 13; ++i) {
            std::string frameName = StringUtils::format("amiya_attack_%02d.png", i);
            
            auto frame = frameCache->getSpriteFrameByName(frameName);
            if (frame) {
                attackFrames.pushBack(frame);
            }
        }
        this->setAnchorPoint(Vec2(0.5f, 0.5f));
        auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.1f); // 每帧间隔0.1秒
        auto attackAnimate = Animate::create(attackAnimation);

        this->runAction(RepeatForever::create(attackAnimate));
    }
    else {
        for (int i = 3; i <= 15; ++i) {
            std::string frameName = StringUtils::format("AmiyaRight%d.png", i);
            auto frame = frameCache->getSpriteFrameByName(frameName);
            if (frame) {
                attackFrames.pushBack(frame);
            }
        }

        auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.2f); // 每帧间隔0.1秒
        auto attackAnimate = Animate::create(attackAnimation);

        this->runAction(RepeatForever::create(attackAnimate));
    }
}
void amiya::castSkill()
{
    auto currentScene = dynamic_cast<baseMap*>(this->getScene());
    if (currentScene) {
        // 遍历场景中的所有活动怪物
        
        for (auto monster : currentScene->activeMonsters) {
           
            if (isTargetInRange_mon(monster, attackRange)) {
               
                monster->takedamage(50);
                boomAnimation(monster);
                return;
            }
           
            
        }
    }
}

void amiya::boomAnimation(BaseMonster* target)
{
    if (target == nullptr) {
        return; // 如果目标不存在，则直接返回
    }

    

    // 创建精灵
    auto sprite = Sprite::create("baozha.png");
    sprite->setPosition(target->getPosition()); // 设置精灵的起始位置，x 和 y 是您希望精灵出现的坐标
    sprite->setScale(0); // 初始缩放为0（完全缩小）

    // 创建缩放动作，从小到大
    auto scaleUp = ScaleTo::create(1.0f, 1.0f); // 动作持续时间为1秒，缩放到原始大小

    // 创建渐隐动作
    auto fadeOut = FadeOut::create(1.0f); // 1秒内渐隐消失

    // 创建一个回调动作，在动画结束后移除精灵
    auto removeSprite = CallFunc::create([sprite]() {
        sprite->removeFromParent();
        });

    
    auto sequence = Sequence::create(scaleUp, fadeOut, removeSprite, nullptr);

    // 运行动作
    sprite->runAction(sequence);

    auto currentScene = dynamic_cast<baseMap*>(this->getScene());
    currentScene->addChild(sprite,INT_MAX);
}

// 检查给定的目标是否在指定的攻击范围内             怪物目标
bool amiya::isTargetInRange_mon(BaseMonster* target, float range) {
    // 计算当前角色与目标之间的距离
    float distance = this->getPosition().distance(target->getPosition());
    // 如果距离小于或等于攻击范围，则目标在范围内
    return distance <= range;
}

void amiya::levelup() {
    
    
    if (level < 3)
        level += 1;  //角色等级
   
    if (level == 2) {
       
        attackPower = 25.0f; // 攻击力为10
        attackRange = 200.0f; // 攻击范围为50
        setTexture("AmiyaRight1.png");
        
    }
    if (level == 3) {
       
        attackPower = 35.0f; // 攻击力为10
        attackRange = 225.0f; // 攻击范围为50
        setTexture("AmiyaRight1.png");
        
    }
    
}
void amiya::findTargetInRange() {
    auto currentScene = dynamic_cast<baseMap*>(this->getScene());
    if (currentScene) {
        int currentFrame = Director::getInstance()->getTotalFrames();
        for (auto monster : currentScene->activeMonsters) {
            if (monster->gethp() <= 0)
                break;
            float distance = this->getPosition().distance(monster->getPosition());
            if (distance <= this->attackRange) {
                isAttacking = true;
                if (currentFrame - lastAttackTime >= attackCooldown) {
                
                     // 创建精灵
                    auto sprite = Sprite::create("magic.png");
                    sprite->setPosition(this->getPosition()); // 设置起始位置
                    
                    auto scene = Director::getInstance()->getRunningScene();
                   
                    scene->addChild(sprite); // 将精灵添加到当前运行的场景

                    // 目标位置
                    Vec2 targetPosition = monster->getPosition();

                    // 创建移动动作
                    auto moveTo = MoveTo::create(1.0f, targetPosition); // 2秒内移动到目标位置

                    // 创建回调动作，在移动完成后执行
                    auto removeSprite = CallFunc::create([sprite]() {
                        sprite->removeFromParentAndCleanup(true);
                        });

                    // 创建序列动作，先移动，然后执行回调
                    auto sequence = Sequence::create(moveTo, removeSprite, nullptr);

                    // 执行序列动作
                    sprite->runAction(sequence);

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