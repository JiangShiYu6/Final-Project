#pragma once
#include"baseHero.h"
#include"basemonster.h"
#include"cocos2d.h"

class andeqieer :public BaseCharacter {
    bool init() override;
    void castSkill()override;
    void playAttackAnimation() override;
    void arrowAnimation();
    void endSkill(float dt);
    void levelup()override;
    bool isTargetInRange_mon(BaseMonster* target, float range);
    SpriteFrameCache* frameCache;
    void findTargetInRange()override;
public:
    bool ifskillison=false;  //是否正在释放技能
    CREATE_FUNC(andeqieer);
};
