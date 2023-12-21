#ifndef _ARROW_H_
#define _ARROW_H_

#include "cocos2d.h"
#include "Bullet.h"

USING_NS_CC;

class Arrow : public Bullet  //箭矢，远程的安德切尔专用，目前先定义这一个，有时间再做其他子弹
{
public:
	virtual bool init();
	CREATE_FUNC(Arrow);  //宏
	void shoot();  //子弹攻击
	void removeBullet();  //子弹移除
};

#endif