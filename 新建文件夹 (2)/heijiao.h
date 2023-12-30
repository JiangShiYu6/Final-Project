#pragma once
#include "cocos2d.h"
#include "baseHero.h"

class heijiao :public BaseCharacter {
public:
    virtual bool init() override;
    
    virtual void playAttackAnimation() override;
    static SpriteFrameCache* frameCache;
    
};
