#include "SimpleAudioEngine.h"
#include"andeqieer.h"
#include"basemonster.h"
USING_NS_CC;
bool andeqieer::init() {
    // 首先调用基类的初始化
    if (!BaseCharacter::init()) {
        return false;
    }

    // 加载 heijiao 的纹理图像
    this->setTexture("安德切尔-正面.png");
    // 设置 heijiao 的初始属性
    this->initCharacterAttributes(500, 10, 5, 500, 50);

    // ... 其他属性设置

    // 如果有特殊行为或动画，也可以在这里设置

    return true;
}

void andeqieer::playAttackAnimation() {

}