#pragma once
#include "cocos2d.h"
#include "baseHero.h"

class heijiao :public BaseCharacter {
public:
    bool init() override;
    void castSkill()override;
    void endSkill(float dt);
    void playAttackAnimation() override;
    void levelup()override;

     SpriteFrameCache* frameCache;
     CREATE_FUNC(heijiao);
protected:
    float wudi_time;

    
};
