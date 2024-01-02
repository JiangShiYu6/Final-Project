#include"dog.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;



bool Dog::init() {
    // 首先调用基类的初始化
    if (!BaseMonster::init()) {
        return false;
    }
    
    // 加载 dabing 的纹理图像
    this->setTexture("dog.png");

    // 设置 dabing 的初始属性
    this->initMonsterAttributes(120, 120, 50, 10, 2,2,30.0);
    
    frameCache = SpriteFrameCache::getInstance();
    for (int i = 1; i <= 5; ++i) { // 假设有6帧动画
        std::string frameName = StringUtils::format("dog_move_%02d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0.5, 0.5, 200, 200)), frameName);
    }
    for (int i = 1; i <= 8; ++i) { // 假设攻击动画有8帧
        std::string frameName = StringUtils::format("dog_attack_%02d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0.5, 0.5, 200, 200)), frameName);
    }
    // ... 其他属性设置

    // 如果有特殊行为或动画，也可以在这里设置
   
    return true; 
}
void Dog::playMoveAnimation() {
    // 创建一个动画帧数组
    Vector<SpriteFrame*> frames;
    for (int i = 1; i <= 5; ++i) {
        std::string frameName = StringUtils::format("dog_move_%02d.png", i);
        auto frame = frameCache->getSpriteFrameByName(frameName);
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

void Dog::playAttackAnimation() {
    // 创建攻击动画帧数组
    Vector<SpriteFrame*> attackFrames;
    for (int i = 1; i <= 8; ++i) {
        std::string frameName = StringUtils::format("dog_attack_%02d.png", i);
        
        auto frame = frameCache->getSpriteFrameByName(frameName);
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