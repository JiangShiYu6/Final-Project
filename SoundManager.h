#ifndef _SOUND_MANAGER_H_
#define _SOUND_MANAGER_H_

class SoundManager
{
public:
	//static void playClickEffect();
	//static void playIncomingWave();
	//static void playNextWaveReady();

	//音效
	//static void playTowerMenu();
	//static void playShipOpen();
	//static void playWinStars();
	//近战干员以及怪物攻击音效
	static void playclosehit();
	//static void playTowerUpdate();
	//static void playTowerSell();
	//远程干员攻击音效
	static void playfarhit();
	//static void playTotemShot();
	//static void playTotemSpirits();
	//static void playTotemWeakness();
	//陨石
	//static void playFireballHit();
	//static void playFireballUnleash();
	//关卡结束
	static void playQuestCompleted();  //战斗成功音效
	static void playQuestFailed();   //战斗失败音效
	//技能
	//static void playReinforcement();
	//static void playCash();
	//static void playFreeze();
	//static void playHearts();
public:
	//static void playWelcomeBackMusic();
	//static void playJungleBattle();
	//static void playDesertBattle();
	//static void playGameTheme1();
public:
	//BOSS 100
	//static void playEfreetiLaugh();
	//static void playEfreetiClap();
	//static void playEfreetiDeath();
private:
	static bool cheakEffectState();  //
};

#endif