#pragma once
#include "cocos2d.h"
#include "basemonster.h"

class Dog : public BaseMonster {
public:
    virtual bool init() override;
    
    virtual void playMoveAnimation()override;
    virtual void playAttackAnimation()override;
    SpriteFrameCache* frameCache;
    CREATE_FUNC(Dog);
};