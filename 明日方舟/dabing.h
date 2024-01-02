#pragma once
#include "cocos2d.h"
#include "basemonster.h"

class Db : public BaseMonster {
public:
    virtual bool init() override;
    
    void playMoveAnimation()override;
    void playAttackAnimation()override;
    
    SpriteFrameCache* frameCache;
    CREATE_FUNC(Db);
};
