#include "SimpleAudioEngine.h"
#include"andeqieer.h"
USING_NS_CC;

bool andeqieer::init() {
    // 首先调用基类的初始化
    if (!BaseCharacter::init()) {
        return false;
    }
    jinoryuan = 1;
    cost01 = 8;
    cost02 = 8;
    // 加载 heijiao 的纹理图像
    this->setTexture("andeqieer_attack_01.png");
    // 设置 heijiao 的初始属性
    this->initCharacterAttributes(50, 30, 200, 1.6f);
    if (!initManaBar("blue.png")) {
        return false;
    }
    // ... 其他属性设置
    deleteButton->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2 + 30));
    healthBar->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2 + 20));
    frameCache = SpriteFrameCache::getInstance();
    for (int i = 1; i <=5; i++) {
        std::string frameName = StringUtils::format("andeqieer_attack_%02d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 200, 200)), frameName);
    }
    for (int i = 1; i <= 8; i++) {
        std::string frameName = StringUtils::format("AnDeRight%d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 200, 200)), frameName);
    }
    for (int i = 1; i <= 7; ++i) {  
        std::string frameName = StringUtils::format("boom%d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 400, 350)), frameName);
    }
    // 如果有特殊行为或动画，也可以在这里设置
    createSkillButton();
    createUpButton();
    return true;
}

void andeqieer::playAttackAnimation() {
    Vector<SpriteFrame*> attackFrames;
    if (level == 1) {

        for (int i = 1; i <= 5; ++i) {
            std::string frameName = StringUtils::format("andeqieer_attack_%02d.png", i);

            auto frame = frameCache->getSpriteFrameByName(frameName);
            if (frame) {
                attackFrames.pushBack(frame);
            }
        }
        this->setAnchorPoint(Vec2(0.5f, 0.5f));
        auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.3f); // 每帧间隔0.1秒
        auto attackAnimate = Animate::create(attackAnimation);

        this->runAction(RepeatForever::create(attackAnimate));
    }
    else {
        for (int i = 1; i <= 8; ++i) {
            std::string frameName = StringUtils::format("AnDeRight%d.png", i);
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
void andeqieer::endSkill(float dt) {
    attackCooldown = attackCooldown + 1.5f; // 将攻击范围重置为正常值
    // 其他需要在技能结束时重置的代码
    ifskillison = false;
}
void andeqieer::arrowAnimation()
{
    if (this == nullptr) {
        return; // 如果目标不存在，则直接返回
    }
    // 获取目标的位置
    Vec2 targetPosition = this->getPosition();

    // 加载爆炸动画的帧
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 7; ++i) {  //九张图片

        std::string frameName = StringUtils::format("boom%d.png", i);

        auto frame = frameCache->getSpriteFrameByName(frameName);
        if (frame) {
            frames.pushBack(frame);
        }
    }
    // 创建动画对象
    auto animation = Animation::createWithSpriteFrames(frames, 0.1f); // 假设每帧的间隔是0.1秒
    auto animate = Animate::create(animation);

    // 创建一个精灵来播放动画
    auto explosionSprite = Sprite::createWithSpriteFrame(frames.front());
    explosionSprite->setPosition(targetPosition);
    auto currentScene = dynamic_cast<baseMap*>(this->getScene());
    currentScene->addChild(explosionSprite, INT_MAX);

    // 播放动画，并在播放完毕后移除精灵
    auto removeSprite = CallFunc::create([explosionSprite]() {
        explosionSprite->removeFromParent();
        });
    explosionSprite->runAction(Sequence::create(animate, removeSprite, nullptr));
}
void andeqieer::castSkill()  //释放技能
{

        ifskillison = true;
        // 获取当前场景
        auto currentScene = dynamic_cast<baseMap*>(this->getScene());
        if (currentScene) {
            attackCooldown = attackCooldown - 1.5f;
            for (auto monster : currentScene->activeMonsters) {
                // 检查怪物是否在攻击范围内,而且到了攻击冷却时间！
                if (isTargetInRange_mon(monster, attackRange)) {
                    // 如果是，则攻击怪物并返回 true
                    monster->takedamage(100);
                    arrowAnimation();
                    break;
                }
            }
            this->schedule(CC_SCHEDULE_SELECTOR(andeqieer::endSkill), 7.5f);

        }
}
// 检查给定的目标是否在指定的攻击范围内             怪物目标
bool andeqieer::isTargetInRange_mon(BaseMonster* target, float range) {
    // 计算当前角色与目标之间的距离
    float distance = this->getPosition().distance(target->getPosition());
    // 如果距离小于或等于攻击范围，则目标在范围内
    return distance <= range;
}

void andeqieer::levelup() //升级效果
{

    if (level < 3)
        level += 1;  //角色等级

    if (level == 2) {

        attackPower = 25.0f; // 攻击力为10
        attackRange = 200.0f; // 攻击范围为50
        setTexture("AnDeRight1.png");

    }
    if (level == 3) {

        attackPower = 35.0f; // 攻击力为10
        attackRange = 225.0f; // 攻击范围为50
        setTexture("AnDeRight1.png");

    }

}
void andeqieer::findTargetInRange() {
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
                    // Monster = monster;//   
                     /*
                     auto bullet = Bullet::create();
                     bullet->setPosition(this->getPosition()); // 设置子弹的初始位置为阿米娅的位置
                     bullet->character = this; // 设置子弹的目标
                     bullet->monster = monster;
                     auto currentScene = dynamic_cast<baseMap*>(this->getScene());
                     bullet->scheduleUpdate();
                     currentScene->addChild(bullet); // 将子弹添加到场景中
                     bullet->getmove();*/
                     // 创建精灵
                    auto sprite = Sprite::create("arrow.png");
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