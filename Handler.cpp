#include"Handler.h"
#include"cocos2d.h"
#include "AppDelegate.h"
USING_NS_CC;
/*getInstance()
{
    if (instance == NULL)
        instance = new GameManager();
    return instance;
}*/
BaseHandler::BaseHandler()  //构造函数
    :isUpdateMenuShown(false)
{}
BaseHandler::~BaseHandler() {}  //析构函数
bool BaseHandler::init()  //初始化干员
{
    if (!Sprite::init())  // 调用基类（Sprite）的初始化方法
    {
        return false;  // 如果基类初始化失败，则返回false 
    }
    isUpdateMenuShown = false;  // 设置成员变量 isUpdateMenuShown 的初始值为 false ,控制干员是否在菜单显示
    return true;  //初始化成功，返回true
}
void BaseHandler::checkNearestMonster()  //找最近的怪物                                                                     需要修改！！！！！！
{
    auto instance = GameManager::getInstance();  //计算距离，                                                             这里需要gamemanger的类？
    auto monsterVector = instance->monsterVector;//全局Vector变量，用来存储当前关卡的敌人

    auto currMinDistant = this->scope;  //this是干员

    nearestMonster = NULL;
    for (int i = 0; i < monsterVector.size(); i++)
    {
        auto monster = monsterVector.at(i);
        double distance = this->getParent()->getPosition().getDistance(monster->baseSprite->getPosition());//算坐标距离

        if (distance < currMinDistant && monster->getAttackByTower()) { //当在塔的范围内，且怪物可以被攻击（某些地下怪物只有钻出地面可以被攻击）
            currMinDistant = distance;//设置最小距离，找到最近的怪物
            <pre name = "code" class = "cpp">            nearestMonster < span style = "font-family: Arial, Helvetica, sans-serif;" >= monster< / span>  
        }
    }

}
void BaseHandler::setListener()  //设置干员触摸时间
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(BaseHandler::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(BaseHandler::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, terrain);
}
bool BaseHandler::onTouchBegan(Touch* touch, Event* event)  //对触摸事件进行处理，开始触摸
{
    return true;
}
void BaseHandler::onTouchEnded(Touch* touch, Event* event)  //结束触摸                                      需要修改！！！！！！
{
    auto target = static_cast<Sprite*>(event->getCurrentTarget());

    Point locationInNode = target->convertTouchToNodeSpace(touch);

    Size size = target->getContentSize();
    Rect rect = Rect(0, 0, size.width, size.height);
    if (rect.containsPoint(locationInNode))//当触摸点在干员范围内（即点击干员，目前只能通过此方法来判断是否点击干员）
    {
        static_cast<BaseMap*>(this->getParent()->getParent())->playerState->showTowerInfo(getHandlerType());//调用父父布局（BaseMap)的PlayState层，显示防御塔信息
        if (isUpdateMenuShown)//如果干员升级界面已经显示，则隐藏，某种显示
        {
            hideUpdateMenu();
        }
        else {
            showUpdateMenu();
        }
    }
    else {//触摸点在外面则隐藏防御塔升级界面
        hideUpdateMenu();
    }
}
void BaseHandler::showHandlerInfo()  //显示塔的信息
{
    ;
}
void BaseHandler::sellHandler()  //出售干员                                                                   //需要修改！！！
{
    static_cast<Terrain*>(this->getParent())->terrain->setVisible(true);  /// 将当前对象的父对象（假设为Terrain类型）的terrain成员设为可见 
    static_cast<BaseMap*>(this->getParent()->getParent())->playerState->removeTowerInfo();  // 从当前对象的祖父对象（假设为BaseMap类型）中移除有关当前塔的信息
    static_cast<Terrain*>(this->getParent())->smokeEffect();  //在当前对象的父对象（假设为Terrain类型）上触发烟雾效果   改成什么效果呢？ 
    this->unscheduleAllCallbacks();  //取消当前对象上所有已安排的回调函数
    this->removeAllChildren();  //移除当前对象的所有子对象
    this->removeFromParent();  //将当前对象从其父对象中移除
}
void BaseHandler::setListener()  //监听器
{
    auto listener = EventListenerTouchOneByOne::create();  //创建一个监听器
    listener->onTouchBegan = CC_CALLBACK_2(BaseHandler::onTouchBegan, this);  //设置触摸开始时的回调函数
    listener->onTouchEnded = CC_CALLBACK_2(BaseHandler::onTouchEnded, this);  // 设置触摸结束时的回调函数
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, terrain);   // 将监听器添加到事件分发器中，具有场景图优先级
}
