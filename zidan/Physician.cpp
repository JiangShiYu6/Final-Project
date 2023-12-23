#include "Physician.h"

bool Milk::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	sprite = Sprite::createWithSpriteFrameName("arrow.png");  //箭矢的图片，记得添加
	addChild(sprite);
	return true;
}

void Milk::shoot()
{
	//SoundManager::playArrowRelease();  //不做子弹音效啦
	runAction(Sequence::create(bulletAction,  //子弹动作
		CallFuncN::create(CC_CALLBACK_0(Milk::removeBullet, this)),
		NULL));
}

void Milk::removeBullet()
{
	bool isMissed = true; //用于标记这个奶是否没有击中干员。
	auto instance = GameManager::getInstance();  //获取游戏管理器的实例。

	auto bulletRect = Rect(this->getPositionX() + this->getParent()->getPositionX() - this->getContentSize().width / 2, //创建一个矩形，代表子弹（箭）的当前位置和大小。这个矩形是基于箭的位置和它的sprite的尺寸计算得出的。
		this->getPositionY() + this->getParent()->getPositionY() - this->getContentSize().height / 2,
		this->sprite->getContentSize().width,
		this->sprite->getContentSize().height);

	auto handlerVector = instance->handlerVector;  //获取干员列表:

	for (int j = 0; j < handlerVector.size(); j++)   //遍历干员列表，检查每个干员是否被奶击中。
	{
		auto handler = handlerVector.at(j);
		auto handlerRect = handler->baseSprite->getBoundingBox();

		if (handlerRect.intersectsRect(bulletRect) && handler->getAttackByHandler())  //来检测干员的矩形区域是否与子弹的矩形区域相交，即是否发生碰撞（击中）。
		{
			auto currHp = handler->getCurrHp();  //根据奶的伤害值（getMaxForce()）和怪物的护甲值（getArmor()）计算怪物的新生命值。

			currHp = currHp - this->getMaxForce() + handler->getArmor();

			if (currHp <= 0) {
				currHp = 0;
			}
			handler->setCurrHp(currHp);

			handler->getHpBar()->setPercentage((currHp / handler->getMaxHp()) * 100);
			handler->getHurt();  //处理怪物受伤的逻辑。
			isMissed = false;  //击中了！
			if (currHp == 0) {
				handler->death();  //处理干员的死亡逻辑。
			}
			break;
		}
	}
	if (isMissed) {

		sprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("decal_arrow.png"));
		//即箭没有击中任何怪物），则改变箭的sprite为一个新的精灵帧（例如，击中地面的箭的图像），然后让它淡出并从父节点移除。  记得换图片！

		sprite->runAction(Sequence::create(FadeOut::create(1.0f)
			, CallFuncN::create(CC_CALLBACK_0(Bullet::removeFromParent, this))
			, NULL));             //创建一个序列动作来实现淡出效果并移除箭。
	}
	else {
		this->removeFromParent();    //如果击中了怪物，则直接调用this->removeFromParent()将箭从父节点移除。
	}
}
