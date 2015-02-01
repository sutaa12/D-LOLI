#include<windows.h>
#include"CScreen.h"
#include"Image.h"
#include"base.h"
#include"main.h"
#include"gamemain.h"


	//何が何でも終了
	//===========================================================================
	void Gamemain::StopMUSIC()
	{
	STOPMIDI(MIDIMAINBGM);
	STOPMIDI(MIDIGAMEOVERBGM);//ゲームオーバー
	STOPMIDI(MIDIBOSSBGM);//ボス
	
	STOPWAVE(AttackSE);//攻撃音
	STOPWAVE(ShootSE);//発射音
	STOPWAVE(EnemyDeSE);//敵の脂肪音
	STOPWAVE(BossShootSE);//ボスの発射音
	STOPWAVE(BossRaserSE);
	STOPWAVE(BossDeSE);//敵の脂肪音
	STOPWAVE(BossDeTSE);//敵の脂肪音
	STOPWAVE(BossLSE);
	STOPWAVE(ItemSE);
	STOPWAVE(EnemyDame);
	STOPWAVE(PDameSE);
	}