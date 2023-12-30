#include "dabing.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

bool Db::init() {
    // 首先调用基类的初始化
    if (!BaseMonster::init()) {
        return false;
    }

    // 加载 dabing 的纹理图像
    this->setTexture("zhongzhuang.png");

    // 设置 dabing 的初始属性
    this->initMonsterAttributes(250,250,200,30,4,1,3);
    
    frameCache = SpriteFrameCache::getInstance();
    for (int i = 1; i <= 5; ++i) { // 移动有5帧动画
        std::string frameName = StringUtils::format("zhongzhuang-move-%02d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0.5, 0.5, 100, 100)), frameName);
    }
    for (int i = 1; i <= 7; ++i) { // 攻击动画有7帧
        std::string frameName = StringUtils::format("zhongzhuang-attack-%02d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0.5, 0.5, 100, 100)), frameName);
    }
    // ... 其他属性设置

    // 如果有特殊行为或动画，也可以在这里设置

    return true;
}
void Db::playMoveAnimation() {
    // 创建一个动画帧数
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 5; ++i) {
        std::string frameName = StringUtils::format("zhongzhuang-move-%02d.png", i);
        
        auto frame = Db::frameCache->getSpriteFrameByName(frameName);
        if (frame) {
            frames.pushBack(frame);
        }
    }
    // 创建动画
    auto animation = Animation::createWithSpriteFrames(frames, 0.1f);
    auto animate = Animate::create(animation);

    // 运行动画
    this->runAction(RepeatForever::create(animate));
}

void Db::playAttackAnimation() {
    Vector<SpriteFrame*> attackFrames;
    for (int i = 1; i <= 7; ++i) { // 假设攻击动画有8帧
        std::string frameName = StringUtils::format("zhongzhuang-attack-%02d.png", i);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        if (frame) {
            attackFrames.pushBack(frame);
        }
    }

    auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.1f); // 每帧间隔0.1秒
    auto attackAnimate = Animate::create(attackAnimation);

    this->runAction(RepeatForever::create(attackAnimate));
}