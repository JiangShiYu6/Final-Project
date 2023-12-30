#include "SimpleAudioEngine.h"
#include"hemo.h"
USING_NS_CC;

cocos2d::SpriteFrameCache* hemo::frameCache = nullptr;
bool hemo::init() {
    // 首先调用基类的初始化
    if (!BaseCharacter::init()) {
        return false;
    }

    // 加载 heijiao 的纹理图像
    this->setTexture("hemo_front.png");
    // 设置 heijiao 的初始属性
    this->initCharacterAttributes(500, 10, 5, 500, 50);

    // ... 其他属性设置

    // 如果有特殊行为或动画，也可以在这里设置

    return true;
}

void hemo::playAttackAnimation() {
    Vector<SpriteFrame*> attackFrames;
    for (int i = 1; i <= 19; ++i) { // 假设攻击动画有8帧
        std::string frameName = StringUtils::format("hemo_attack_%02d.png", i);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        if (frame) {
            attackFrames.pushBack(frame);
        }
    }

    auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.1f); // 每帧间隔0.1秒
    auto attackAnimate = Animate::create(attackAnimation);

    this->runAction(Sequence::create(attackAnimate, CallFunc::create([&]() {
        // 攻击动画完成后的逻辑（如果有）
        }), nullptr));
}