#pragma once
#include"baseHero.h"
#include"cocos2d.h"
#include"baseMonster.h"
class lapu :public BaseCharacter {
public:
    bool init() override;
    void castSkill()override;
    void playAttackAnimation() override;
    void endSkill(float dt);
    void swordAnimation(BaseMonster* target);
    void levelup()override;
    bool isTargetInRange_mon(BaseMonster* target, float range);
    SpriteFrameCache* frameCache;
    // 设置可放置点位
    CREATE_FUNC(lapu);
};

