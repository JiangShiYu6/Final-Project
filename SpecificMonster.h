#ifndef _WINGRIDER_H_
#define _WINGRIDER_H_

#include "BaseMonster.h"
#include "cocos2d.h"
USING_NS_CC;

class Source_Lithina : public BaseMonster  //埭坒單
{
public:
	virtual bool init() override;
	static Source_Lithina* createMonster(std::vector<Point> points);
};
class _Soldier : public BaseMonster  //苤條
{
public:
	virtual bool init() override;
	static _Soldier* createMonster(std::vector<Point> points);
};
class _Dog : public BaseMonster  //僩
{
public:
	virtual bool init() override;
	static _Dog* createMonster(std::vector<Point> points);
};
class Shiled_Man : public BaseMonster  //嗎條
{
public:
	virtual bool init() override;
	static Shiled_Man* createMonster(std::vector<Point> points);
};

#endif
