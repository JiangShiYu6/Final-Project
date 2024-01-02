#include"basemonster.h"

bool BaseMonster::init() {
	if (!Sprite::init()) {
		return false;
	}
	// 调度 action 方法，例如每0.1秒调用一次
	
	this->schedule(CC_SCHEDULE_SELECTOR(BaseMonster::action), 0.1f);
	
	return true;
	
}

void BaseMonster::takedamage(float damage) {
	if (damage <= 0) {
		damage = 0;
	}
	float real_damage = damage / this->defence;
	this->cur_Hp -= real_damage;
	if (this->cur_Hp > 0) {
		// 创建一个变红的动作
		auto tintToRed = TintTo::create(0.1f, 255, 0, 0); // 持续时间0.1秒，颜色为红色

		// 创建一个动作，恢复到原始颜色
		auto tintToOriginal = TintTo::create(0.1f, 255, 255, 255); // 恢复时间和颜色

		// 创建一个序列动作，先变红，然后恢复原色
		auto sequence = Sequence::create(tintToRed, tintToOriginal, nullptr);

		// 运行这个动作
		this->runAction(sequence);
	}
}

void BaseMonster::checkNearbyHeroes() {
	auto currentMap = dynamic_cast<baseMap*>(this->getScene());
	if (!currentMap) {
		return;
	}

	int currentFrame = Director::getInstance()->getTotalFrames();

	// 遍历所有角色
	for (auto& character : currentMap->characters) {
		if (character->gethp() <= 0||character->JorY()==1) {
			break;
		}
		float distance = this->getPosition().distance(character->getPosition());

		// 检查是否在攻击范围内，并且检查攻击冷却是否完成
		if (distance <= this->range ) {
			
			Attack();  // 改变怪物状态，准备攻击
			if (currentFrame - lastAttackTime >= attackCooldown) {
				character->takeDamage(this->force);
				lastAttackTime = currentFrame;  // 更新上次攻击的帧数
				
			}
			else {
				isAttackAnimationPlaying = true;

			}
			return;
		}
	}
	this->StopAttak();
	
}

void BaseMonster::action(float dt) {
	// 检查是否到达终点或血量为0
	if (cur_Hp <= 0) {
		stopAllActions();
		disappear();
		return;
	}


	// 检查周围是否存在英雄
	checkNearbyHeroes();
	
	// 如果怪物正在攻击，则播放攻击动画
	if (isAttacking) {
		
		if (!isAttackAnimationPlaying) {
			if (isMoving) {
				this->stopAllActions();
				isMoving = false;
			}
			playAttackAnimation();
			isAttackAnimationPlaying = true;
		}
		
	}
	// 否则，执行移动逻辑
	else {
		
		if (isAttackAnimationPlaying) {
			this->stopAllActions();
			isAttackAnimationPlaying = false;
		}
		if (!isMoving) {
			playMoveAnimation();
			isMoving = true;
		}
		
		// 获取当前目标点
		auto targetPoint = movementPath[currentPathIndex];

		// 计算移动向量
		Vec2 direction = (targetPoint - this->getPosition()).getNormalized();
		float moveDistance = speed * dt * 10;
		Vec2 newPoint = this->getPosition() + direction * moveDistance;

		// 设置怪物新的位置
		this->setPosition(newPoint);


		// 检查是否到达当前目标点
		if (newPoint.distance(targetPoint) < moveDistance) {

			currentPathIndex++;

			if (currentPathIndex >= movementPath.size()) {
				// 如果到达路径末尾，调用到达终点的逻辑
				reachDestination();
				disappear();
			}
		}
	}
}



void BaseMonster::disappear() {
	auto currentMap = dynamic_cast<baseMap*>(this->getScene());
	if (currentMap) {
		currentMap->removeActiveMonster(this);  // 从activeMonsters数组中移除
		this->removeFromParent();  // 从场景中移除怪物
	}
	
}

void BaseMonster::reachDestination() {
	
	auto currentMap = dynamic_cast<baseMap*>(this->getScene());
	if (currentMap) {
		currentMap->HP_off();
	}
}



void BaseMonster::update(float dt) {
	// 在这里调用action方法
	this->action(dt);
}
