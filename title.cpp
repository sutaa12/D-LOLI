#include<windows.h>
#include"CScreen.h"
#include"Image.h"
#include"title.h"
#include"hitchk.h"
#include"main.h"


#define Y_MAX 150//�n�ʂ̏��
#define Draw_max 800//��ʂ̈ړ����
#define Draw_min 0//�}�b�v�̍ŏ�
#define Walk_x 15//�ړ���
#define Max_anim 3//�t���O�̃}�b�N�X
#define W_anim 0.4f//�t���O�̉��Z
#define START_FLAG 1 //�X�^�[�g�̃t���O
#define One_anim 40	//�ҋ@�A�j���[�V�����̋�؂�

enum Move_MODES{
	M_Wait,M_Walk
};//���[�V�����̃f�t�@�C��
Title::Title()
{
	this->MenuBack.FileRead("DATA/Menu/Back/BMP_DAT_",1);
		this->Player_Wait.anim(2,"DATA/Player/Wait/BMP_DAT_");
	this->Player_Walk.anim(3,"DATA/Player/Walk/BMP_DAT_");
		this->MenuButton.anim(3,"DATA/Menu/Button/BMP_DAT_");
		this->TITLEBGM=OPENWAVE("DATA/BGM/Title.wav");//�^�C�g����
		this->DOORSE=OPENWAVE("DATA/SE/Door.wav");

	MenuBack.ImageFileRead();//�p���b�g��񂲂Ə�����
	MenuBack.ChangePalette();
	MenuBack.SetConsolePalatte();
		MenuBack.ChangeImageSize();
	MenuBack.SetWindowSize2(1000,1,1);
	MenuBack.ChangeImage();
	this->Dbuff.Init(this->MenuBack);
	this->Start.Input(0,0);
	this->Start.Flag=0;
	this->Door.HchkInit(Player_Wait.animation[0],MenuButton.animation[0]);
}

int Title::TitleInit()
{
	this->KEYCHK.KeyInINIT();//�L�[���͏�����
	this->Player.x=0;		//�X�^�[�g�ʒu
	this->Player.y=Y_MAX;	//�v���C���[���W
	this->Player.POSFlag=0;//�����̏�����
	this->Player.Flag=0;//����t���O������
	this->Player.MFlag=0;//�����ȊO�̓���̏�����
	this->Start.Flag=0;//�P�̏ꍇ�X�^�[�g
	this->Dbuff.SetMap(this->MenuBack);
	this->Start.Input(800,100);
	Logo.Input(20,20);//���S�̈ʒu�Z�b�g
	this->Dbuff.SetBuf(this->MenuButton.animation[2],this->Logo.x,this->Logo.y,0);
	this->Dbuff.SetBuf(this->MenuButton.animation[0],this->Start.x,this->Start.y,0);
	this->Dbuff.SetBuf(this->Player_Wait.animation[0],this->Player.x,this->Player.y,0);
	this->Dbuff.DrawBuf(this->MenuBack,0);
	this->Count=0;
	this->TitleFlag=TITLE_MAIN;
	PLAYWAVE(this->TITLEBGM,1);//�����Đ�
	setMflag( TitleFlag);
	return TITLE_MAIN;//���ɂȂ���
}

int Title::TitleMain()
{

	this->KEYCHK.KeyInINIT();//�L�[���͏�����
		if(Start.Flag==-1)
	{
		if(this->Count>=0)//0����Ȃ�
		{
			if(this->Count==20)
			{
				STOPWAVE(this->TITLEBGM);
				this->TitleFlag= GAMEMAIN_INIT;
			}else{
			if(this->Count>=10)
			{
				this->Dbuff.SetMapB(this->MenuBack);
			}else{
				this->Dbuff.SetMapBHX(this->MenuBack);
			}
			}
		}
					this->Count++;
	}else{
	this->Dbuff.SetMap(this->MenuBack);
	this->Dbuff.SetBuf(this->MenuButton.animation[2],this->Logo.x,this->Logo.y,0);
//==========�J�E���g�̐���
	if(this->Count>=0)//�J�E���g���[���ȉ��Ȃ�
	{
		this->Count++;//�J�E���g���v���X
	}
	if(this->Count>One_anim*2)//80�𒴂�����
	{
		this->Count=0;//�J�E���g���Z�b�g
	}
//========================================
	//========================================
	//�����蔻��

	Start.Flag=Door.Hitcheck(Player.x,0,Player.y,Start.x,Start.y);//�t���O���O����Ȃ������痧��
	if(Start.Flag!=0)
	{
		Start.Flag=START_FLAG;
		this->Dbuff.SetBuf(this->MenuButton.animation[1],this->Start.x,this->Start.y,0);
	}else{
		this->Dbuff.SetBuf(this->MenuButton.animation[0],this->Start.x,this->Start.y,0);
	}
	//===================================
//===================����t���O�`�F�b�N=================
	switch(this->Player.Flag)
	{
	case M_Walk://�����̏ꍇ
					this->Player.DFlag+=W_anim;//�A�j���[�V�����t���O���Z
			if(this->Player.DFlag>Max_anim)//�A�j���[�V��������𒴂�����
			{
				Player.DFlag=0;
			}//
		if(this->Player.POSFlag!=0)//�E�����łȂ�������(������)
		{
						this->Player.x-=Walk_x;//5�߂�


			if(Player.x<Draw_min)
			{
				Player.x+=Walk_x;//�}�b�v�[�Ŗ߂鏈��
			}
			Dbuff.SetBufM(this->Player_Walk.animation[(int)this->Player.DFlag],this->Player.x,this->Player.y,0);
			Player.Flag=M_Wait;//0�ɃZ�b�g
		}else{//(�E����)
						this->Player.x+=Walk_x;//5�i��

			if(Player.x>Draw_max)//�}�b�v�̒[�̏ꍇ�߂�
			{
				Player.x-=Walk_x;
			}
			Dbuff.SetBuf(this->Player_Walk.animation[(int)this->Player.DFlag],this->Player.x,this->Player.y,0);
			Player.Flag=M_Wait;//0�ɃZ�b�g
		}//
		break;//=======================================

					//============================�ҋ@
	case M_Wait:
		if(this->Player.POSFlag!=0)//�������̏ꍇ
		{
			if(this->Count>0&&this->Count<=40)
			{
			Dbuff.SetBufM(this->Player_Wait.animation[0],this->Player.x,this->Player.y,0);
			}else{
			Dbuff.SetBufM(this->Player_Wait.animation[1],this->Player.x,this->Player.y,0);
			}
		}else{
						if(this->Count>0&&this->Count<=40)
						{
			Dbuff.SetBuf(this->Player_Wait.animation[0],this->Player.x,this->Player.y,0);
						}else{
			Dbuff.SetBuf(this->Player_Wait.animation[1],this->Player.x,this->Player.y,0);
						}
		}//else
	}//switch
//=========================================

		//=====================�L�[���͐���
	this->KEYCHK.KeySet();
			if(this->KEYCHK.KEY_END!=0x00)
		{
			TitleFlag=END;
		}else{
	if(this->KEYCHK.KEY_SHIFT!=0x00)
	{
	}else{
	if(Player.Flag==0)
	{
		if(this->KEYCHK.KEY_ENTER!=0x00||this->KEYCHK.KEY_W)
		{
			if(this->Start.Flag==START_FLAG)
			{
				PLAYWAVE(this->DOORSE,0);
				this->Count=0;//�J�E���g������
				this->Start.Flag=-1;
			}else{
			}

		}else{
	if(this->KEYCHK.KEY_A!=0x00)
	{
		this->Player.Flag=M_Walk;//�����t���O
		this->Player.POSFlag=1;//������
	}else{
	if(this->KEYCHK.KEY_D!=0x00)
	{
		this->Player.Flag=M_Walk;//�����t���O
		this->Player.POSFlag=0;//�E����
	}else{//

		this->Player.Flag=M_Wait;
	}
	}
	}
		}
	}
	}
	}//-1��
//======================================

	this->Dbuff.DrawBuf(this->MenuBack,0);
setMflag( TitleFlag);//�Q�[���t���O�Z�b�g
return TITLE_MAIN;
}

//===============================================================
//�^�C�g���폜

void Title::titleDel()
{
		this->Player_Wait.Del();
		this->Player_Walk.Del();
		this->MenuButton.Del();
		CLOSEWAVE(this->TITLEBGM);//�{�X
		CLOSEWAVE(this->DOORSE);
}