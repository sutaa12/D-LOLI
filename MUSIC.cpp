#include<windows.h>
#include"CScreen.h"
#include"Image.h"
#include"base.h"
#include"main.h"
#include"gamemain.h"


	//�������ł��I��
	//===========================================================================
	void Gamemain::StopMUSIC()
	{
	STOPMIDI(MIDIMAINBGM);
	STOPMIDI(MIDIGAMEOVERBGM);//�Q�[���I�[�o�[
	STOPMIDI(MIDIBOSSBGM);//�{�X
	
	STOPWAVE(AttackSE);//�U����
	STOPWAVE(ShootSE);//���ˉ�
	STOPWAVE(EnemyDeSE);//�G�̎��b��
	STOPWAVE(BossShootSE);//�{�X�̔��ˉ�
	STOPWAVE(BossRaserSE);
	STOPWAVE(BossDeSE);//�G�̎��b��
	STOPWAVE(BossDeTSE);//�G�̎��b��
	STOPWAVE(BossLSE);
	STOPWAVE(ItemSE);
	STOPWAVE(EnemyDame);
	STOPWAVE(PDameSE);
	}