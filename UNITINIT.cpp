#include<windows.h>
#include"CScreen.h"
#include"Image.h"
#include"base.h"
#include"main.h"
#include"gamemain.h"
//�����z�u
void Gamemain::SetEnemy()//�G�z�u
{
		//�G�̏�����
			int x=1500;//�G��x��
	for(int i=0;i<EnemyMAX;i++)
	{
	this->Enemy[i].Input(x,220);//�G�̏����z�u
	Enemy[i].MFlag=0;//���S�A�j���[�V�����t���O
	this->Enemy[i].LifeFlag=1;//�t���O�I��
	this->Enemy[i].DFlag=0.0f;//�ړ��t���O
	x+=600;//���W�ړ�
	}
	Enemy[0].InputX(1300);
	Enemy[1].InputX(2400);
	Enemy[2].InputX(2700);
	Enemy[3].InputX(3150);
	Enemy[4].Input(4100,160);
	Enemy[5].Input(4300,160);//HIGH�ɏ���Ă�
	Enemy[6].InputX(4600);
	Enemy[7].InputX(5100);
	Enemy[8].InputX(5900);
	Enemy[9].Input(6000,130);
	Enemy[10].InputX(1500);
	Enemy[11].InputX(6700);
	Enemy[12].InputX(6750);
	Enemy[13].InputX(6400);
//===============================================================
	//�e��łG�̏�����
				x=1300;//�G��x��
	for(int i=0;i<EnemyShootMAX;i++)
	{
	this->EnemyS[i].Input(x,220);//�G�̏����z�u
	EnemyS[i].MFlag=0;//���S�A�j���[�V�����t���O
	this->EnemyS[i].LifeFlag=1;//�t���O�I��
	this->EnemyS[i].DFlag=0.0f;//�ړ��t���O
	this->EnemyS[i].Flag=0;//�t���O��ON�Ȃ�e���o��
	x+=600;//���W�ړ�
	}
	EnemyS[0].InputX(2100);
	EnemyS[1].Input(3200,100);//��ԍ����Ƃ�
	EnemyS[2].InputX(3600);
	EnemyS[3].Input(4500,130);
	EnemyS[4].Input(5100,100);
	EnemyS[5].InputX(4750);
	EnemyS[6].Input(5600,190);
	EnemyS[7].Input(6100,190);
	EnemyS[8].InputX(6500);
	EnemyS[9].InputX(6800);
	EnemyS[10].InputX(6900);


//�G�̒e�̏�����
	for(int i=0;i<EnemyShootMAX*2;i++)
	{
		this->Ebullet[i].Flag=0;//�t���O������
		this->Ebullet[i].Input(0,0);//���W������
		this->Ebullet[i].LifeFlag=EbulletLifeMAX;//�e�̃��C�t������
	}
}

//====================================
void Gamemain::SetItem()//�A�C�e���z�u
{
	for(int i=0;i<ITEM_MAX;i++)
	{
		this->Itemx[i].Flag=1;//�A�C�e���t���O���Z�b�g
		this->Itemx[i].Input(1000,230);//�A�C�e���t���O
		this->Itemx[i].LifeFlag=0;
	}
	this->Itemx[0].Input(1600,140);
	  Itemx[1].Input(2900,140);
	  Itemx[2].InputX(4700);
	  Itemx[3].Input(4800,140);
	  Itemx[4].Input(5900,140);
	  Itemx[5].InputX(6000);
	  Itemx[6].InputX(6300);
	  Itemx[7].InputX(6600);
	  Itemx[8].InputX(6900);
	  Itemx[9].InputX(6850);
}
//===================================
void Gamemain::SetPlate()//����z�u
{
		//����̏�����
	this->PlateSMALL[0].Input(1000,260);
		  PlateSMALL[1].Input(2100,260);
		  PlateSMALL[2].Input(3200,170);
		  PlateSMALL[3].Input(3900,260);
		  PlateSMALL[4].Input(5100,170);
		  PlateSMALL[5].Input(5600,260);
		  PlateSMALL[6].Input(6050,260);
	this->PlateHIGH[0].Input(1200,230);
		  PlateHIGH[1].Input(2300,230);
		  PlateHIGH[2].Input(4100,230);
		  PlateHIGH[3].Input(4300,230);
	this->PlateLARGE[0].Input(1500,200);
		  PlateLARGE[1].Input(2600,200);
		  PlateLARGE[2].Input(4500,200);
		  PlateLARGE[3].Input(5900,200);
		  this->Pchk=0;//1�̏ꍇ�����Ȃ�
}

//===================================