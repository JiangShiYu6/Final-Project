#include "SoundManager.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h" 

using namespace CocosDenshion;
USING_NS_CC;

bool SoundManager::cheakEffectState()
{
	if (UserDefault::getInstance()->getIntegerForKey("backeffect", 1) == 1)
		return true;
	else
		return false;
}
void SoundManager::playclosehit()   //近战攻击音效
{
	if (cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/boss_efreeti_evillaugh.wav");
}
void SoundManager::playfarhit()   //远程攻击音效
{
	if (cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/boss_efreeti_evillaugh.wav");
}
void SoundManager::playQuestCompleted()   //战斗成功音效
{
	if (cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/boss_efreeti_evillaugh.wav");
}
void SoundManager::playQuestFailed()   //战斗失败音效
{
	if (cheakEffectState())
		SimpleAudioEngine::getInstance()->playEffect("sound/boss_efreeti_evillaugh.wav");
}