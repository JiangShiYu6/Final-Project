#ifndef _BASE_MONSTER_H_
#define _BASE_MONSTER_H_

#include "cocos2d.h"

USING_NS_CC;
typedef enum {
	stateNone = 0, //无状态
	stateWalkRight, //向右走走状态
	stateWalkLeft, //向左走
	stateWalkUp, //向上走
	stateWalkDown, //向下走
	stateAttackLeft,  //向左攻击
	stateAttackRight, //向右攻击
	stateDeath,//死亡
	//stateFrozen  //冻结
}MonsterState;

typedef enum {
	SourceLithina,  //源石虫
	Soldier,  //小兵
	Dog,  //狗
	ShiledMan,  //盾兵
}MonsterName;

class BaseMonster : public Sprite
{
public:
	BaseMonster();
	~BaseMonster();
	virtual bool init() override;
	CREATE_FUNC(BaseMonster);
	Sprite* baseSprite;
	//冒血，受击特效
	virtual void death();
	//死
	//virtual void explosion();  
	CC_SYNTHESIZE(std::vector<Point>, pointsVector, PointsVector);  //路径点
	CC_SYNTHESIZE(bool, attackBySoldier, AttackBySoldier);  //是否被干员近战攻击
	CC_SYNTHESIZE(MonsterName, monsterType, MonsterType);  //怪物类型
	CC_SYNTHESIZE(bool, attackByHandler, AttackByHandler);  //是否被干员远程攻击  
	CC_SYNTHESIZE(bool, isAttacking, IsAttacking);  //是否正在攻击
	CC_SYNTHESIZE(float, runSpeed, RunSpeed);  //移动速度
	CC_SYNTHESIZE(float, maxHp, MaxHp);  //最大血量
	CC_SYNTHESIZE(float, currHp, CurrHp);  //当前血量
	CC_SYNTHESIZE(float, force, Force);  //攻击力
	CC_SYNTHESIZE(float, armor, Armor);  //防御力
	CC_SYNTHESIZE(float, hpPercentage, HpPercentage);  //血量百分比
	//CC_SYNTHESIZE(MonsterState, state, State);  
	//CC_SYNTHESIZE(int, money, Money);
	CC_SYNTHESIZE_READONLY(ProgressTimer*, hpBar, HpBar);  //生命条
	virtual void stopWalking();  //停止移动
	virtual void restartWalking();  //重新开始移动
	//virtual void slowRunSpeed(float dt, float dis);  //降低速度
	Point getNextPoint();  //获取下一个路径
	virtual void frozen();  //冻结
	virtual void refrozen(float dt);  //解冻
private:

protected:
	void setMonsterZorder(int yOrder);  //设置怪物z轴顺序
	int pointCounter;  //路径点计数器
	Sprite* hpBgSprite;  //生命值背景精灵
	Point currPoint();  //当前点
	Point nextPoint();  //下一个点
	Point tempNextPoint;  //临时的下一个点
	void runNextPoint();  //移动到下一个点
	void createAndSetHpBar();  //创建并设置生命条

	bool onTouchBegan(Touch* touch, Event* event);  //监听器触摸事件开始
	void onTouchEnded(Touch* touch, Event* event);  //监听器触摸事件结束

	virtual void update(float dt);
	//CC_SYNTHESIZE(bool, isSlowed, IsSlowed);

	Sprite* blood;                                       //? ? ? ? ? ? 
	//MonsterState tempState;
	//MonsterState lastState;
	void stopMonsterAnimation();  //停止之前动画
	//Sprite* ice;
	//void showInfo();  //显示怪物信息
	void setListener();  //监听器
};
#endif