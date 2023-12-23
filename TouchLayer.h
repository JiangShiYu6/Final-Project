#ifndef _TOUCH_LAYER_H_
#define _TOUCH_LAYER_H_

#include "cocos2d.h"
#include "Handler.h"


USING_NS_CC;

class TouchLayer :public Layer
{
public:
	virtual bool init();   // 宏，辅助创建TouchLayer对象 
	CREATE_FUNC(TouchLayer);
	EventListenerTouchOneByOne* PlaceListener;   //放置监听器
	EventListenerTouchOneByOne* RetreatListener;  //撤退监听器
	EventListenerTouchOneByOne* LevelupListener;  //升级监听器
	//EventListenerTouchOneByOne* Freezelistener;
	//EventListenerTouchOneByOne* Dynamitelistener;  //炸药监听器
	//EventListenerTouchOneByOne* FiereBalllistener;   如果有机会可以实现源石

	void setDynamiteTouchShield();  
	void removeDynamiteTouchShield();
	bool onDynamiteTouchBegan(Touch* touch, Event* event);
	void onDynamiteTouchEnded(Touch* touch, Event* event);

	void setRallyFlagTouchShield();
	void removeRallyFlagTouchShield();
	bool onRallyFlagTouchBegan(Touch* touch, Event* event);
	void onRallyFlagTouchEnded(Touch* touch, Event* event);

	void setSoldierTouchShield();
	void removeSoldierTouchShield();
	bool onSoldierTouchBegan(Touch* touch, Event* event);
	void onSoldierTouchEnded(Touch* touch, Event* event);

	void setFreezeTouchShield();
	void removeFreezeTouchShield();
	bool onFreezeTouchBegan(Touch* touch, Event* event);
	void onFreezeTouchEnded(Touch* touch, Event* event);

	void setFireBallTouchShield();
	void removeFireBallTouchShield();
	bool onFireBallTouchBegan(Touch* touch, Event* event);
	void onFireBallTouchEnded(Touch* touch, Event* event);

	void removeTouchShield();
	void setTouchShield();

	BaseTower* tower;
	void addRallyFlag(Point location);
	void addWrongPlace(Point location);

	bool isFlag;
	bool onPlaceBegan(Touch* touch, Event* event);   //放置监听器
	void onPlaceEnded(Touch* touch, Event* event);
	void onPlaceMoved(Touch* touch, Event* event);
	Size winSize;
	bool isMoved;
	RallyCircle* rallyCircle;
	void removeAllListener();
};

#endif