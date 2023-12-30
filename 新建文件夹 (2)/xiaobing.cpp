#include "xiaobing.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;


bool Xiaobing::init() {
    // 首先调用基类的初始化
    if (!BaseMonster::init()) {
        return false;
    }

    // 加载 dabing 的纹理图像
    this->setTexture("shibing.png");
    // 设置 dabing 的初始属性
    this->initMonsterAttributes(150, 150, 200, 50, 2,1,2);
    
    // ... 其他属性设置
     // 创建 xiaobing 实例
    
    frameCache = SpriteFrameCache::getInstance();
    for (int i = 1; i <= 7; ++i) { // 假设有6帧动画
        std::string frameName = StringUtils::format("shibing-move-%02d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0.5, 0.5, 200, 200)), frameName);
    }
    for (int i = 1; i <= 10; ++i) { // 假设攻击动画有8帧
        std::string frameName = StringUtils::format("shibing-attack-%02d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0.5, 0.5, 200, 200)), frameName);
    }
    // 如果有特殊行为或动画，也可以在这里设置

    return true;
}

void Xiaobing::playMoveAnimation() {
    // 创建一个动画帧数组
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 7; ++i) {
        std::string frameName = StringUtils::format("shibing-move-%02d.png", i);
        
        auto frame = Xiaobing::frameCache->getSpriteFrameByName(frameName);
        if (frame) {
            frames.pushBack(frame);
        }
    }

    // 创建动画
    auto animation = Animation::createWithSpriteFrames(frames,0.1f);
    auto animate = Animate::create(animation);

    // 运行动画
    this->runAction(RepeatForever::create(animate));
}

void Xiaobing::playAttackAnimation() {
    // 创建攻击动画帧数组
    Vector<SpriteFrame*> attackFrames;
    for (int i = 1; i <= 10; ++i) {
        std::string frameName = StringUtils::format("shibing-attack-%02d.png", i);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        if (frame) {
            attackFrames.pushBack(frame);
        }
    }

    // 创建攻击动画
    auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.1f);
    auto attackAnimate = Animate::create(attackAnimation);

    // 运行攻击动画
    this->runAction(RepeatForever::create(attackAnimate));
}