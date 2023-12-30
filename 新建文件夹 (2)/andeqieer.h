#pragma once
#include"baseHero.h"
#include"cocos2d.h"

class andeqieer :public BaseCharacter {
    virtual bool init() override;

    virtual void playAttackAnimation() override;
    static SpriteFrameCache* frameCache;
    
};
