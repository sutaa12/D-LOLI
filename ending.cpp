#include<windows.h>
#include"CScreen.h"
#include"Image.h"
#include"base.h"
#include"main.h"
#include"ending.h"

#define Y_MAX 150//�n�ʂ̏��
#define Disp_max 2000//��ʂ̈ړ����
#define Walk_x 10//�ړ���
#define Max_anim 3//�t���O�̃}�b�N�X
#define W_anim 0.4f//�t���O�̉��Z
#define START_FLAG 1 //�X�^�[�g�̃t���O
#define One_anim 40	//�ҋ@�A�j���[�V�����̋�؂�

enum Move_MODES{
	M_Wait,M_Walk
};//���[�V�����̃f�t�@�C��


Ending::Ending()
{
	this->Player_Wait.anim(2,"DATA/Player/Wait/BMP_DAT_");
	this->Player_Walk.anim(3,"DATA/Player/Walk/BMP_DAT_");
	this->EndBack.anim(3,"DATA/Ending/BMP_DAT_");//�G���f�B���O�摜�p��
	this->Logo.anim(3,"DATA/Menu/Button/BMP_DAT_");
	this->ENDINGBGM=OPENMP3("DATA/BGM/ENDING.mp3");//�G���f�B���O

	this->Dbuff.Init(this->EndBack.animation[0]);
}
//�G���f�B���O������
//========================================================================
int Ending::endinit()
{
		Credit.Input(200,50);//�N���W�b�g�̍��W�Z�b�g
	Player.Input(0,Y_MAX);//�v���C���[�̍��W�Z�b�g
	Player.MFlag=M_Wait;//1�Ȃ�ړ�������ȊO�͑ҋ@
	Player.DFlag=0.0f;//�ړ��ʏ�����
	Dispx=0;//��ʍ��W�Z�b�g
	Car.Input(2000,155);//�Ԃ̍��W�Z�b�g
	EndFlag=ENDING_MAIN;//�G���f�B���O�̃t���O�Z�b�g
	Count=0;//�J�E���g�Z�b�g
	Logoinfo.Input(20,20);//���S�̈ʒu�Z�b�g
	this->KEYCHK.KeyInINIT();//�L�[���͏�����
	PLAYMP3(this->ENDINGBGM,0);
	setMflag(EndFlag);
	return ENDING_MAIN;
}

//�G���f�B���O�̃��C������
//==========================================================================
int Ending::endingmain()
{
	this->KEYCHK.KeyInINIT();//�L�[���͏�����

	this->Dbuff.SetMap(this->EndBack.animation[0]);//�w�i�Z�b�g
if(this->Count>=0)//�J�E���g���[���ȉ��Ȃ�
	{
		this->Count++;//�J�E���g���v���X
	}

	if(this->Count>One_anim*2)//80�𒴂�����
	{
		this->Count=0;//�J�E���g���Z�b�g
	}

if(Dispx>=0&&Dispx<=Disp_max&&Player.MFlag==M_Walk)//��ʈʒu��0����1000�܂łňړ��t���O�������Ă���΂Ȃ�
	{
		Dispx+=10;//10�ړ�
		Player.MFlag=M_Walk;//�ړ��t���O������
	}

	if(Dispx==0&&Count==One_anim/2)//�J�E���g�Əꏊ���O�Ȃ�
	{
		Player.MFlag=M_Walk;//�ړ��t���O������
	}
if(Dispx==Disp_max&&Player.MFlag==M_Walk)//��ʂ�1000�ő����Ă�����
	{
		Player.MFlag=M_Wait;//�߂�
	}
	this->Dbuff.SetBuf(this->Logo.animation[2],this->Logoinfo.x,this->Logoinfo.y,Dispx);
if(Dispx==Disp_max&&Player.MFlag==M_Wait&&Count==One_anim*2)
{
	STOPMP3(this->ENDINGBGM);
	EndFlag=TITLE_INIT;//�^�C�g����
}
		if(Car.x>=0)//�Ԃ̍��W���[���ɂȂ�܂�
		{
			if(Count%2==0)
			{
			this->Dbuff.SetBuf(EndBack.animation[1],Car.x,Car.y,0);//�ԕ`��
			}else{
				this->Dbuff.SetBuf(EndBack.animation[1],Car.x,Car.y+1,0);//�ԕ`��
			}
			Car.x-=Walk_x*2;
		}
//================================================================================
		switch(this->Player.MFlag)
		{
	case M_Walk://�����̏ꍇ
		
			this->Player.DFlag+=W_anim;//�A�j���[�V�����t���O���Z
					if(this->Player.DFlag>Max_anim)//�A�j���[�V��������𒴂�����
			{
				Player.DFlag=0;
			}//
			Dbuff.SetBuf(this->Player_Walk.animation[(int)this->Player.DFlag],this->Player.x,this->Player.y,Dispx);
			Player.Flag=M_Wait;//0�ɃZ�b�g
		break;//=======================================

					//============================�ҋ@
	case M_Wait:
						if(this->Count>0&&this->Count<=40)
						{
			Dbuff.SetBuf(this->Player_Wait.animation[0],this->Player.x,this->Player.y,Dispx);
						}else{
			Dbuff.SetBuf(this->Player_Wait.animation[1],this->Player.x,this->Player.y,Dispx);
						}

		}//switch

		this->KEYCHK.KeySet();
			if(this->KEYCHK.KEY_ENTER!=0x00)
			{
				STOPMP3(this->ENDINGBGM);
				EndFlag=TITLE_INIT;//�G���^�[�ŃX�L�b�v
			}

//===============================================================================================================
		this->Dbuff.SetBuf(EndBack.animation[2],Credit.x,Credit.y,Dispx);//���b�Z�[�W�\��
		this->Dbuff.DrawBuf(this->EndBack.animation[0],Dispx);//�S���`��
	setMflag(EndFlag);//������Z�b�g
	return ENDING_MAIN;
}

//======================================================================================
//�G���f�B���O������
void Ending::endingDel()
{
	this->Player_Wait.Del();
	this->Player_Walk.Del();
	this->EndBack.Del();//�G���f�B���O�摜�p��
	this->Logo.Del();
	CLOSEMIDI(this->ENDINGBGM);//�G���f�B���O
}
