#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

class BaseCharacter : public cocos2d::Sprite {

public:
    
    BaseCharacter();
    virtual ~BaseCharacter();
    bool init() override;
    
    // 初始化角色属性
    void initCharacterAttributes(float health, float attackPower,float range, float Cooldown);

    // 攻击动画
    virtual void playAttackAnimation() = 0;
    void update(float dt);
    virtual void findTargetInRange();
   
    // 受击动画
    void playHitAnimation();
    void takeDamage(float damage);
    void playDeathAnimationAndRemove();

    
    float getattackPower()const;
    float getCurrentMana() const {
        return currentMana;
    }
    void setCurrentMana(float mana) {
        currentMana = mana;
    }
    float gethp() {
        return currHp;
    }
    // 角色技能相关
    bool initManaBar(const std::string& manaBarImage);  // 初始化蓝条
    void updateMana(float dt);                          // 更新蓝条值
    void createSkillButton();                         //生成技能图标
    void showSkillButton();                            //显示技能图标
    void onManaBarClicked();                          // 蓝条点击事件处理
    virtual void castSkill() = 0;                     // 释放技能
    void onSkillButtonClicked(Ref* sender, ui::Widget::TouchEventType type);
    void startSkillCooldown(float dt);                  //技能冷却
    //角色升级相关
    virtual void levelup() {};        //升级开销
    void createUpButton();
    void onlevelupClicked(Ref* sender, ui::Widget::TouchEventType type);         // 升级点击事件处理
    int JorY() const{
        return jinoryuan;
     }
protected:
    ProgressTimer* manaBar;            // 技能条
    ui::Button* skillButton;          // 技能按钮
    int jinoryuan;                   //远程还是近战
    ui::Button* upButton;          // 升级按钮
    int level = 1;  //角色等级，初始为一级
    int cost01;  //放置费用
    int cost02;  //升级费用
    float currentMana;                // 当前蓝条值
    float maxMana;             // 最大蓝条值
    float attackRange;                // 攻击范围
    float attackCooldown;             // 攻击冷却时间
    float lastAttackTime;             // 上次攻击时间
    float maxHp;                      // 最大血量
    float currHp;                     // 当前血量
    float skill;                      //技能条
    float attackPower;                // 攻击力
    float CD;                         //角色撤销后下一次可放置该角色的时间间隔
    int coin_sp;                      //放置该角色所需要的资源
    Vec2 placementPosition;           // 角色的放置位置
    ProgressTimer* healthBar;         // 血条
    ProgressTimer* skillBar;          // 技能条
    ui::Button* deleteButton;
    void onDeleteButtonClicked(Ref* sender, ui::Widget::TouchEventType type);
    bool wudi;
    bool isAttacking;
    bool isPlaying;
};