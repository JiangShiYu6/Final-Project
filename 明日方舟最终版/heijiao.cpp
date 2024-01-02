#include "SimpleAudioEngine.h"
#include"heijiao.h"
USING_NS_CC; 



bool heijiao::init() {
    // 首先调用基类的初始化
    if (!BaseCharacter::init()) {
        return false;
    }
    wudi = false;
    jinoryuan = 0;
    if (level == 1)
        wudi_time = 7.5f;
    if (level == 2)
        wudi_time = 10.0f;
    if (level == 3)
        wudi_time = 12.5f;
    cost01 = 8;
    cost02 = 8;
    // 加载 heijiao 的纹理图像
    this->setTexture("heijiao_front.png");
    // 设置 heijiao 的初始属性
    this->initCharacterAttributes(100, 10, 70, 3);
    deleteButton->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2 + 30));
    healthBar->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2 + 20));
    if (!initManaBar("blue.png")) {
        return false;
    }
    
    frameCache = SpriteFrameCache::getInstance();
    for (int i = 1; i <= 10; i++) {
        std::string frameName = StringUtils::format("heijiao_attack_%02d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 200, 200)), frameName);
    }
    for (int i = 1; i <= 12; i++) {
       
        std::string frameName = StringUtils::format("HeiJiaoRight%d.png", i);
        frameCache->addSpriteFrame(SpriteFrame::create(frameName, Rect(0, 0, 200, 200)), frameName);
    }
    createSkillButton();
    createUpButton();
    this->schedule(CC_SCHEDULE_SELECTOR(BaseCharacter::updateMana), 1.0f);
    return true;
}

void heijiao::playAttackAnimation() {
    
    Vector<SpriteFrame*> attackFrames;
    if (level == 1) {
        for (int i = 1; i <= 10; ++i) { //攻击动画有10帧
            std::string frameName = StringUtils::format("heijiao_attack_%02d.png", i);
            
            auto frame = frameCache->getSpriteFrameByName(frameName);
            if (frame) {
                attackFrames.pushBack(frame);
            }
        }
        auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.3f); // 每帧间隔0.1秒
        auto attackAnimate = Animate::create(attackAnimation);

        this->runAction(RepeatForever::create(attackAnimate));
    }
    else {
        for (int i = 1; i <= 12; ++i) { //攻击动画有12帧
            std::string frameName = StringUtils::format("HeiJiaoRight%d.png", i);
            
            auto frame = frameCache->getSpriteFrameByName(frameName);
            if (frame) {
                attackFrames.pushBack(frame);
            }
        }
        auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.25f); // 每帧间隔0.1秒
        auto attackAnimate = Animate::create(attackAnimation);

        this->runAction(RepeatForever::create(attackAnimate));
    }

    

}

void heijiao::castSkill() {
    // 半透明效果
    wudi = true;
    auto fadeOut = FadeTo::create(0.5f, 128); // 逐渐变为半透明，持续时间为0.5秒
    auto fadeIn = FadeTo::create(0.5f, 255); // 逐渐恢复不透明，持续时间为0.5秒
    auto delay = DelayTime::create(7.5f); // 技能持续时间

    // 创建动画序列
    auto sequence = Sequence::create(fadeOut, delay, fadeIn, nullptr);
    this->runAction(sequence);
    this->schedule(CC_SCHEDULE_SELECTOR(heijiao::endSkill), wudi_time);
    
}

void heijiao::endSkill(float dt) {
    wudi = false;
}

void heijiao::levelup()
{
    if(level<3)
    level +=1;  //角色等级
    

    if (level == 2) {
        maxHp = 150.0f; // 初始血量为100
        currHp = maxHp; // 当前血量等于最大血量
        attackPower = 15.0f; // 攻击力为10
        attackRange = 80.0f; // 攻击范围为50
        this->setTexture("HeiJiaoRight1.png");
        
        
    }
    if (level == 3) {
        maxHp = 200.0f; // 初始血量为100
        currHp = maxHp; // 当前血量等于最大血量
        attackPower = 20.0f; // 攻击力为10
        attackRange = 80.0f; // 攻击范围为50
        this->setTexture("HeiJiaoRight1.png");
    }
    
}