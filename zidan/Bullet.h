#ifndef _BULLET_H_
#define _BULLET_H_

//#include "SoundManager.h"
#include "cocos2d.h"
#include "GameManager.h"

USING_NS_CC;

class Bullet : public Sprite
{
public:
	Bullet();  //构造函数
	~Bullet();  //析构函数
	virtual bool init();  //宏
	CREATE_FUNC(Bullet);  //创建对象的静态方法，这样就可以用Bullet:create()来创建对象

protected:
	CC_SYNTHESIZE(int, maxForce, MaxForce);  //子弹伤害
	CC_SYNTHESIZE(int, bulletScope, BulletScope);//子弹范围
	CC_SYNTHESIZE(int, bulletType, BulletType);  //子弹类型
	CC_SYNTHESIZE(Spawn*, bulletAction, BulletAction);  //子弹动作
	Sprite* sprite;  //创建精灵
	virtual void shoot() {};  //发射
	virtual void removeBullet() {};  //子弹的移除
};

#endif