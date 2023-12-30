#pragma once
#include "cocos2d.h"


USING_NS_CC;

class BaseCharacter : public cocos2d::Sprite {
public:
    
    BaseCharacter();
    virtual ~BaseCharacter();
    virtual bool init() override;
    CREATE_FUNC(BaseCharacter);

    // 初始化角色属性
    void initCharacterAttributes(float health, float attackPower, int blockCount, float range, float Cooldown);

    // 攻击动画
    virtual void playAttackAnimation(){}
    void update(float dt);
    bool findTargetInRange(float range);
   
    // 受击动画
    void playHitAnimation();
    void takeDamage(float damage);
    void playDeathAnimationAndRemove();

    // 技能
    //void activateSkill();
    //void onSkillBarFull();

    // 设置和获取可抵挡怪物的数量
    //void setBlockCount(int count);
    //int getBlockCount() const;
    float getattackPower();

private:
    float attackRange;                // 攻击范围
    float attackCooldown;             // 攻击冷却时间
    float lastAttackTime;             // 上次攻击时间
    float maxHp;                      // 最大血量
    float currHp;                     // 当前血量
    float skill;                      //技能条
    float attackPower;                // 攻击力
    int blockCount;                   // 可抵挡怪物的数量
    float CD;                         //角色撤销后下一次可放置该角色的时间间隔
    float range;                      //角色的攻击范围
    int coin_sp;                      //放置该角色所需要的资源
    Vec2 placementPosition;           // 角色的放置位置
    ProgressTimer* healthBar;         // 血条
    ProgressTimer* skillBar;          // 技能条
    void initMouseListener();         // 初始化鼠标监听器
    void onMouseDown(Event* event);   // 鼠标事件处理
    
};