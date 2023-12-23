#pragma once
#include"cocos2d.h"
#include "main.h"
#include "AppDelegate.h"
#ifndef __HANDLER_H__
#define __HANDLER_H__
USING_NS_CC;

typedef enum {
    LaPuLanDe_1,  //一级拉普兰德
    LaPuLanDe_2,  //二级拉普兰德
    AnDeQieEr_1,  //一级安德切尔
    AnDeQieEr_2,  //二级安德切尔
    HeiJiao_1,  //一级黑角
    HeiJiao_2,  //二级黑角
    HeMou_1,  //一级赫默
    HeMou_2,  //二级赫默
    AMiYa_1,  //一级阿米娅
    AMiYa_2,  //一级阿米娅
    JiJing_1,  //一级极境
    JiJing_2,  //二级极境
    SoureStore,  //源石，一次性道具
}HandlerType;
class BaseHandler :public Sprite
{
public:
    BaseHandler();
    ~BaseHandler();
    virtual void updateHandler() {};//升级干员（基础升级）
    virtual void sellHandler();//售卖干员
    //virtual void removeHandler();//移除防御塔  //移出和售卖是不是可以一个意思？
    virtual bool init();//初始化干员
    CC_SYNTHESIZE(HandlerType, handlerType, HandlerType);  //干员种类
    CC_SYNTHESIZE(Terrain*, myTerrain, MyTerrain);  //建造点
    CC_SYNTHESIZE(std::string, towerName, TowerName); //名称
    CC_SYNTHESIZE(int, level, Level);//等级
    CC_SYNTHESIZE(float, scope, Scope);//范围
    CC_SYNTHESIZE(float, nextScope, NextScope);//升级后范围
    CC_SYNTHESIZE(float, rate, Rate);//攻击速度
    CC_SYNTHESIZE(int, force, Force);//攻击力
    CC_SYNTHESIZE(int, updateMoney, UpdateMoney);//升级所需金钱
    CC_SYNTHESIZE(int, buildMoney, BuildMoney);//售出时返还金钱
    //virtual void showHandlerInfo();//显示干员的信息
    bool isUpdateMenuShown;     //github新加的
    virtual void update1() {};//两种升级方向  //我们就做一种升级方向好了
    //virtual void update2() {};  //这种升级方向可以删掉
    //virtual void setRallyPoint(Point point) {};//兵营塔的设置集结点                        //删掉
protected:   //对于子女是public，对于外部是private
    virtual void checkNearestMonster();//检测附近敌人
    BaseMonster* nearestMonster;  //附近的敌人
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    virtual void showUpdateMenu() {};//显示升级选项
    virtual void hideUpdateMenu();//隐藏
    Sprite* terrain;//该塔的建造点
    void setListener();//设置某些监听事件，              干什么用的呢？
};

#endif  //#ifndef __HANDLER_H__