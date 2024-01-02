#pragma once
#include"baseHero.h"
#include"baseMonster.h"
#include"cocos2d.h"


class amiya :public BaseCharacter {
public:
    bool init() override;
    void castSkill()override;
    void playAttackAnimation() override;
    void boomAnimation(BaseMonster* target);
    void levelup()override;
    bool isTargetInRange_mon(BaseMonster* target, float range);
    void findTargetInRange()override;
    CREATE_FUNC(amiya);
protected:
    SpriteFrameCache* frameCache;
};

