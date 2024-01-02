#include "SimpleAudioEngine.h"
#include"lapu.h"
USING_NS_CC;



bool lapu::init() {
    // 首先调用基类的初始化
    if (!BaseCharacter::init()) {
        return false;
    }
    cost01 = 8;
    cost02 = 8;
    jinoryuan = 0;
    // 加载 heijiao 的纹理图像
    this->setTexture("lapu_front.png");
    // 设置 heijiao 的初始属性
    this->initCharacterAttributes(200, 30, 60, 1.4);
    deleteButton->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2 + 30));
    healthBar->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2 + 20));
    if (!initManaBar("blue.png")) {
        return false;
    }
    // ... 其他属性设置
    frameCache = SpriteFrameCache::getInstance();
    for (int i = 1; i <= 7; i++) {
        std::string frameName = StringUtils::format("lapu_attack_%02d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 200, 200)), frameName);
    }
    for (int i = 1; i <= 13; i++) {
        std::string frameName = StringUtils::format(" LaDogRight%d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 200, 200)), frameName);
    }
    for (int i = 1; i <= 4; ++i) {  //九张图片
        std::string frameName = StringUtils::format("lapu_skill%d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 200, 200)), frameName);
    }
    // 如果有特殊行为或动画，也可以在这里设置
    createSkillButton();
    createUpButton();
    return true;
}

void lapu::playAttackAnimation() {
    
    if (level == 1) {
        Vector<SpriteFrame*> attackFrames;
        for (int i = 1; i <= 7; ++i) { // 假设攻击动画有8帧
            std::string frameName = StringUtils::format("lapu_attack_%02d.png", i);
            auto frame = frameCache->getSpriteFrameByName(frameName);
            if (frame) {
                attackFrames.pushBack(frame);
            }
        }

        auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.2f); // 每帧间隔0.1秒
        auto attackAnimate = Animate::create(attackAnimation);
        this->runAction(RepeatForever::create(attackAnimate));
    }
    else {
        Vector<SpriteFrame*> attackFrames;
        for (int i = 1; i <= 13; ++i) { // 假设攻击动画有8帧
            std::string frameName = StringUtils::format("LaDogRight%d.png", i);
            auto frame = frameCache->getSpriteFrameByName(frameName);
            if (frame) {
                attackFrames.pushBack(frame);
            }
        }

        auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.1f); // 每帧间隔0.1秒
        auto attackAnimate = Animate::create(attackAnimation);
        this->runAction(RepeatForever::create(attackAnimate));
    }
    
}

void lapu::endSkill(float dt) {
    attackRange = attackRange - 10; // 将攻击范围重置为正常值
    // 其他需要在技能结束时重置的代码
}

void lapu::swordAnimation(BaseMonster* target)
{
    if (target == nullptr) {
        return; // 如果目标不存在，则直接返回
    }

    // 获取目标的位置
    Vec2 targetPosition = target->getPosition();

    // 加载爆炸动画的帧
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 4; ++i) {  //九张图片
        std::string frameName = StringUtils::format("lapu_skill%d.png", i);
        auto frame = frameCache->getSpriteFrameByName(frameName);
        if (frame) {
            frames.pushBack(frame);  // 将找到的帧添加到动画帧集合中
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
void lapu::castSkill()  //释放技能
{
        // 获取当前场景
        auto currentScene = dynamic_cast<baseMap*>(this->getScene());
        if (currentScene) {
            attackRange = attackRange + 10.0f;
            for (auto monster : currentScene->activeMonsters) {
                // 检查怪物是否在攻击范围内,而且到了攻击冷却时间！
                if (isTargetInRange_mon(monster, attackRange)) {
                    // 如果是，则攻击怪物并返回 true
                    swordAnimation(monster);
                    break;
                }
            }
            this->schedule(CC_SCHEDULE_SELECTOR(lapu::endSkill), 5.0f);
        }
}
bool lapu::isTargetInRange_mon(BaseMonster* target, float range) {
    // 计算当前角色与目标之间的距离
    float distance = this->getPosition().distance(target->getPosition());
    // 如果距离小于或等于攻击范围，则目标在范围内
    return distance <= range;
}
void lapu::levelup() {
    if (level < 3)
        level += 1;  //角色等级

    if (level == 2) {

        maxHp = 250;
        currHp = 250;
        attackRange = 75.0f; 
        setTexture("LaDogRight1.png");

    }
    if (level == 3) {

        maxHp = 300;
        currHp = 300;
        attackPower = 35.0f; 
        setTexture("LaDogRight1.png");

    }
}