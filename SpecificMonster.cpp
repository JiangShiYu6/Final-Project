#include "SpecificMonster.h"

USING_NS_CC;


Source_Lithina* Source_Lithina::createMonster(std::vector<Point> points)                //源石虫
{
	auto monster = new Source_Lithina();
	if (monster && monster->init())
	{

		monster->setPointsVector(points);
		monster->setMaxHp(480);
		monster->setCurrHp(480);
		//monster->setMoney(50);
		monster->setForce(30);
		monster->setArmor(0);
		monster->setAttackBySoldier(true);
		monster->setRunSpeed(35);
		monster->runNextPoint();  //移动到下一个点
		monster->autorelease();  
		return monster;
	}
	CC_SAFE_DELETE(monster);
	return NULL;
}
bool Source_Lithina::init()
{
	if (!BaseMonster::init())
	{
		return false;
	}
	setMonsterType(SourceLithina);
	setName("SourceLithina_");
	baseSprite = Sprite::createWithSpriteFrameName("2c42e5f8ab97573cfabd5a3d3c93a48.png");
	addChild(baseSprite);
	createAndSetHpBar();
	blood = Sprite::createWithSpriteFrameName("fx_blood_splat_green_0001.png");
	blood->setPosition(Point(baseSprite->getContentSize().width / 2, baseSprite->getContentSize().height / 2));
	baseSprite->addChild(blood);
	blood->setVisible(false);
	//lastState = stateNone;
	scheduleUpdate();
	setListener();
	return true;
}


_Soldier* _Soldier::createMonster(std::vector<Point> points)  //士兵
{
	auto monster = new _Soldier();
	if (monster && monster->init())
	{

		monster->setPointsVector(points);
		monster->setMaxHp(480);
		monster->setCurrHp(480);
		//monster->setMoney(50);
		monster->setForce(30);
		monster->setArmor(0);
		monster->setAttackBySoldier(true);
		monster->setRunSpeed(35);
		monster->runNextPoint();
		monster->autorelease();
		return monster;
	}
	CC_SAFE_DELETE(monster);
	return NULL;
}

bool _Soldier::init()
{
	if (!BaseMonster::init())
	{
		return false;
	}
	setMonsterType(Soldier);
	setName("Soldier_");
	baseSprite = Sprite::createWithSpriteFrameName("CanibalShamanMagic_0001.png");
	addChild(baseSprite);
	createAndSetHpBar();
	blood = Sprite::createWithSpriteFrameName("fx_blood_splat_green_0001.png");
	blood->setPosition(Point(baseSprite->getContentSize().width / 2, baseSprite->getContentSize().height / 2));
	baseSprite->addChild(blood);
	blood->setVisible(false);
	//lastState = stateNone;
	scheduleUpdate();
	setListener();
	return true;
}


_Dog* _Dog::createMonster(std::vector<Point> points)  //狗
{
	auto monster = new _Dog();
	if (monster && monster->init())
	{

		monster->setPointsVector(points);
		monster->setMaxHp(480);
		monster->setCurrHp(480);
		//monster->setMoney(50);
		monster->setForce(30);
		monster->setArmor(0);
		monster->setAttackBySoldier(true);
		monster->setRunSpeed(35);
		monster->runNextPoint();
		monster->autorelease();
		return monster;
	}
	CC_SAFE_DELETE(monster);
	return NULL;
}

bool _Dog::init()
{
	if (!BaseMonster::init())
	{
		return false;
	}
	setMonsterType(Dog);
	setName("Dog_");
	baseSprite = Sprite::createWithSpriteFrameName("CanibalShamanMagic_0001.png");
	addChild(baseSprite);
	createAndSetHpBar();
	blood = Sprite::createWithSpriteFrameName("fx_blood_splat_green_0001.png");
	blood->setPosition(Point(baseSprite->getContentSize().width / 2, baseSprite->getContentSize().height / 2));
	baseSprite->addChild(blood);
	blood->setVisible(false);
	//lastState = stateNone;
	scheduleUpdate();
	setListener();
	return true;
}

Shiled_Man* Shiled_Man::createMonster(std::vector<Point> points)   //盾兵
{
	auto monster = new Shiled_Man();
	if (monster && monster->init())
	{

		monster->setPointsVector(points);
		monster->setMaxHp(480);
		monster->setCurrHp(480);
		//monster->setMoney(50);
		monster->setForce(30);
		monster->setArmor(0);
		monster->setAttackBySoldier(true);
		monster->setRunSpeed(35);
		monster->runNextPoint();
		monster->autorelease();
		return monster;
	}
	CC_SAFE_DELETE(monster);
	return NULL;
}

bool Shiled_Man::init()
{
	if (!BaseMonster::init())
	{
		return false;
	}
	setMonsterType(ShiledMan);
	setName("ShiledMan_");
	baseSprite = Sprite::createWithSpriteFrameName("CanibalShamanMagic_0001.png");
	addChild(baseSprite);
	createAndSetHpBar();
	blood = Sprite::createWithSpriteFrameName("fx_blood_splat_green_0001.png");
	blood->setPosition(Point(baseSprite->getContentSize().width / 2, baseSprite->getContentSize().height / 2));
	baseSprite->addChild(blood);
	blood->setVisible(false);
	//lastState = stateNone;
	scheduleUpdate();
	setListener();
	return true;
}
