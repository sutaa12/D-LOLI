#include<windows.h>
#include"CScreen.h"
#include"Image.h"
#include"base.h"
#include"main.h"
#include"gamemain.h"

Gamemain::Gamemain()//�R���X�g���N�^
{
	//�摜�p��
	this->Plate.anim(4,"DATA/Plate/BMP_DAT_");
	this->Background.anim(1,"DATA/Back/BMP_DAT_");
	this->Player_Wait.anim(2,"DATA/Player/Wait/BMP_DAT_");
	this->Player_Walk.anim(3,"DATA/Player/Walk/BMP_DAT_");
	this->Player_Jump.anim(4,"DATA/Player/Jump/BMP_DAT_");
	this->Player_Shot.anim(2,"DATA/Player/Shot/BMP_DAT_");
	this->Player_Bullet.anim(2,"DATA/Player/Bullet/BMP_DAT_");
	this->Player_Attack.anim(3,"DATA/Player/Attack/BMP_DAT_");
	this->Player_GASbar.anim(2,"DATA/Player/GASbar/BMP_DAT_");
	this->Player_GAMEOVER.anim(5,"DATA/Player/GameOver/BMP_DAT_");
	this->Player_HP.anim(2,"DATA/Player/HP/BMP_DAT_");
	this->Enemy_Wait.anim(2,"DATA/Enemy/Wait/BMP_DAT_");
	this->Enemy_Shoot.anim(2,"DATA/Enemy/Shoot/BMP_DAT_");
	this->Enemy_Bullet.anim(2,"DATA/Enemy/Bullet/BMP_DAT_");
	this->Enemy_Dead.anim(5,"DATA/Enemy/Dead/BMP_DAT_");
	
	this->Item.anim(2,"DATA/Item/BMP_DAT_");
	
	this->BossG.anim(1,"DATA/Boss/Head/BMP_DAT_");
	this->BossM.anim(4,"DATA/Boss/Head/MOUTH/BMP_DAT_");
	this->BossN.anim(4,"DATA/Boss/Head/NORSE/BMP_DAT_");
	this->BossE.anim(4,"DATA/Boss/Head/EYE/BMP_DAT_");
	this->BossBu.anim(1,"DATA/Boss/BossBullet/BMP_DAT_");
	this->BossRa.anim(1,"DATA/Boss/BossRaser/BMP_DAT_");
	this->Explasive.anim(7,"DATA/Boss/Explosion/BMP_DAT_");

	this->Message_Window.anim(3,"DATA/Message/BMP_DAT_");

	this->MIDIMAINBGM=OPENMIDI("DATA/BGM/Main.mid");//���y���J��
	this->MIDIGAMEOVERBGM=OPENMIDI("DATA/BGM/GameOver.mid");//�Q�[���I�[�o�[
	this->MIDIBOSSBGM=OPENMIDI("DATA/BGM/Boss.mid");//�{�X
	
	this->AttackSE=OPENWAVE("DATA/SE/Attack.wav");//�U����
	this->ShootSE=OPENWAVE("DATA/SE/Pshoot.wav");//���ˉ�
	this->PDameSE=OPENWAVE("DATA/SE/PlayerD.wav");//���ˉ�
	this->EnemyDeSE=OPENWAVE("DATA/SE/Tekisi.wav");//�G�̎��b��
	this->BossShootSE=OPENWAVE("DATA/SE/Bshoot.wav");//�{�X�̔��ˉ�
	this->BossRaserSE=OPENWAVE("DATA/SE/Braser.wav");
	this->BossDeSE=OPENWAVE("DATA/SE/BossDame.wav");//�G�̎��b��
	this->BossDeTSE=OPENWAVE("DATA/SE/BossDeath.wav");//�G�̎��b��
	this->EnemyDame=OPENWAVE("DATA/SE/EnemyD.wav");//�G�̎��b��
	this->BossLSE=OPENWAVE("DATA/SE/BossF.wav");//�G�̎��b��
	this->ItemSE=OPENWAVE("DATA/SE/ItemSE.wav");//�G�̎��b��



	this->Dbuff.Init(this->Background.animation[0]);
	
	this->Platechk.HchkInit(Player_Jump.animation[0],Plate.animation[0]);//�傫������`�F�b�N�p��
	
	this->PlateSMALL=new Base[Base_S];//����̐����ϐ��p��
	this->PlateHIGH=new Base[Base_H];//����̐����ϐ��p��
	this->PlateLARGE=new Base[Base_L];//����̐����ϐ��p��


	this->Itemx=new Base[ITEM_MAX];//�A�C�e���̐����ϐ��p��
	
	this->Enemy=new Base[EnemyMAX];//�G�̍��W�p��
	this->EnemyS=new Base[EnemyShootMAX];//�G�̍��W�p��
	this->Ebullet=new Base[EnemyShootMAX*2];//�G�̐���2�{�̒e�p��
	this->Enemychk.HchkInit(Player_Wait.animation[0],Enemy_Wait.animation[0]);//�G�Ƃ̂����蔻��p��
	this->Bakuha=new Base[JakutenMAX];//��_�������p��
}

int Gamemain::GameInit()//�Q�[���̏����^
{
	//�L�[��񏉊���
	this->KEYCHK.KeyInINIT();
	//�Q�[���̏��ύX
	this->GameFlag=GAMEMAIN_MAIN;
//�ʒu���
	this->Dispx=0;			//��ʂ̕\���ʒu
	this->Count=20;
	this->Gravity=6;//�d�͏�����

	//�v���C���[���
	this->Player.x=0;		//
	this->Player.y=Y_MAX;	//�v���C���[���W
	this->Player.POSFlag=0;//�����̏�����
	this->Player.Flag=0;//����t���O������
	this->Player.MFlag=0;//�����ȊO�̓���̏�����
	this->Player.DFlag=0.0f;//�����t���O������
	this->Player.LifeFlag=STARTLIFE;//���C�t������
	this->Gas=STARTG;//�K�\������
	this->AttackF=0;//1�̏ꍇ�U��
	this->Damage=0;//�_���[�W��
	this->EHIT=0;//�q�b�g������

	//�v���C���[�e�̏�񏉊���
	this->Pbullet.Flag=0;//�e�����˂���Ă��邩
	Pbullet.POSFlag=0;//�e�̔���
	this->Pbullet.MFlag=0;//�e�̓���
	this->Pbullet.x=0;
	this->Pbullet.y=0;

	this->SetEnemy();//�G�̔z�u������
	this->SetPlate();//����̏����z�u
	this->SetItem();//�A�C�e���̏����z�u

	//���b�Z�[�W�\��������
	this->Message.Flag=1;
	this->Message.MFlag=0;//���b�Z�[�W�̃A�j���[�V����������
	this->Message.Input(300,50);//���b�Z�[�W�\�����W

	//�Q�[���I�[�o�[�̏�����
	this->GAMEOVER.Flag=0;//�Q�[���I�[�o�[�̕`��t���O�̏�����
	this->GAMEOVER.MFlag=0;//�Q�[���I�[�o�[�̑���̏�����
	this->GAMEOVER.Input(400,50);//�ʒu�̏�����

	//�{�X���[�h�̏�����
	this->Boss.Flag=0;//���[�h�`�F�b�N
	this->Boss.MFlag=0;//�{�X�̃A�j���[�V����
	this->Boss.LifeFlag=3;//�{�X��HP
	this->BossBullet.Input(0,0);//�{�X�̒e���W
	this->BossBullet.LifeFlag=0;//�{�X�̒e���C�t
	this->Jakuten.Input(7795,240);//��_�̔z�u�̏ꍇ
	this->Jakuten.Flag=0;
	this->Boss.Input(7799,20);//�{�X�ʒu
	this->Info.Input(7650,240);//���\��
	this->BossR.Input(0,0);//���[�U�[��񏉊���
	this->BossR.LifeFlag=0;
	this->Boss.POSFlag=0;//�V�[���؂�ւ��t���O

	for(int i=0;i<JakutenMAX;i++)
	{
	this->Bakuha[i].Flag=0;//1�Ȃ甚��
	this->Bakuha[i].MFlag=0;//���̃^�C�~���O
	this->Bakuha[i].LifeFlag=0;//���j�̎���
	this->Bakuha[i].Input(0,0);//�ʒu
	}

	//���y������
	PLAYMIDI(this->MIDIMAINBGM,1);

//�����`��
		this->Dbuff.SetMapB(this->Background.animation[0]);
	setMflag( GameFlag);//�Q�[���t���O�Z�b�g
	return GAMEMAIN_MAIN;
}
//==========================================================================================================================================
int Gamemain::Gmain()//�Q�[�����C��
{
//==========================�`��ʒu����
	this->ChengeDisp();
//========================================

	//=====================================================================
	//����`�F�b�N
PlateCHECK();

//=========================================
//�A�C�e���`��
	this->DItem();

//=================================================
		//�{�X�t���O�`�F�b�N
	//===================================================================
	if(Dispx>=Draw_max-300&&Boss.Flag==0)
	{
		Message.Flag=1;//���b�Z�[�W�t���OON
		Boss.Flag=1;//�t���O����
		Enemy[0].LifeFlag=0;//�{�X�p�ɓG���m��
		Player.x=10;//���W���炷

		STOPMIDI(this->MIDIMAINBGM);
		PLAYWAVE(this->BossLSE,0);//�{�X�΂���
		PLAYMIDI(this->MIDIBOSSBGM,1);//�{�XBGM
	}
	if(this->Boss.Flag==1)//�t���O��1�Ȃ�
	{
	this->BossMODE();//�{�X����
	}
//==========�J�E���g�̐���
	this->CountCheck();

//===========================================
	//�Q�[���I�[�o�[�`�F�b�N
	if(GAMEOVER.Flag!=0)
	{
		this->GameOver();//�Q�[���I�[�o�[����
	}else{
//============�G�̕\��
	this->EnemyD();
	this->EnemySD();
//=============================================
		//==========�G�̒e����
	this->EbulletCheck();
//=====================================================

//===================����t���O�`�F�b�N=================
	this->MFlagCheck();
//=========================================
	//============================================
	//�������b�Z�[�W�\��
	if(Message.Flag!=0)
	{
		this->SetMessage();
	}else{
	//=====================================================
	//=====================�L�[���͐���
	this->KeyCheck();
//===========================================================================
	//�e�����˂���Ă��邩�`�F�b�N===================================
	this->PbulletCheck();
	//====================================================================
	//�o�[�\��
	this->HPstate();
	//==�Q�[���I�[�o�[�łȂ��ꍇ
	}
		}
	//�W�����v�̏d�͐���=================================
	this->GravityP();
//=========================================

this->KEYCHK.KeyInINIT();//�L�[��񏉊���

	//===========================================
	//�`�揈��
	this->Dbuff.DrawBuf(this->Background.animation[0],this->Dispx);
	if(GameFlag!=GAMEMAIN_MAIN)//�Q�[�����C���ȊO�Ȃ牽���Ȃ�ł������~�߂�
	{
		this->StopMUSIC();
	}
setMflag( GameFlag);
	return GAMEMAIN_MAIN;
}


//=====================================================================================================================================================
//�֐�


//===============================================
//�`��ʒu�ύX
void Gamemain::ChengeDisp()
{
	if(this->Player.x>Disp_max&&this->Dispx<Draw_max&&this->Boss.Flag==0)//��������������ʁ��[�ɍs������
	{
		Dispx+=Walk_x;//�w�i������
	if(this->Player.x>Disp_max)
	{
		this->Player.x-=Walk_x;//���W���߂�
	}
	}else{
		if(this->Player.x<Disp_min&&this->Dispx>Draw_min&&this->Boss.Flag==0)//��������������ԁ��[
		{
			Dispx-=Walk_x;//�߂�
			if(this->Player.x<Disp_min)
			{
				this->Player.x+=Walk_x;//�v���C���̍��W��߂�
			}
		}else{
		}
	}
	this->Dbuff.SetMap(this->Background.animation[0]);
}

//================================
//�A�C�e���`��
void Gamemain::DItem()
{
	for(int i=0;i<ITEM_MAX;i++)//�A�C�e�����`�F�b�N
	{
				if(this->Itemx[i].Flag!=0)//�A�C�e���t���O���O�łȂ��ꍇ
		{
		this->Enemychk.HchkInit(this->Player_Wait.animation[0],this->Item.animation[0]);
		this->EHIT=this->Enemychk.HitcheckEB(Player.x,Dispx,Player.y,Itemx[i].x,Itemx[i].y);//�������Ă��邩�`�F�b�N
		if(EHIT!=0&&EHIT!=-2)//�������Ă�����
		{
			if(Gas<12)//�K�\���P�Q��艺��������
			{
				PLAYWAVE(this->ItemSE,0);//�{�X�΂���
			this->Gas+=6;//�K�\��
			this->Itemx[i].Flag=0;//�t���O�O�ɂ���
			this->Itemx[i].LifeFlag=3;//�A�C�e���������鏈��
			}

		}

		if(this->Count>0&&this->Count<=20||this->Count>40&&this->Count<=60)
		{
			this->Dbuff.SetBuf(this->Item.animation[0],0,Itemx[i].y,Itemx[i].x);
		}else{
		this->Dbuff.SetBuf(this->Item.animation[1],0,Itemx[i].y,Itemx[i].x);
		}
		}
				if(this->Itemx[i].LifeFlag!=0&&this->Itemx[i].LifeFlag<=10)//���C�t���O����������
				{
				this->Dbuff.SetBufD(this->Item.animation[1],0,Itemx[i].y,Itemx[i].x);
				Itemx[i].LifeFlag--;//���C�t�t���O0
				}
	}
}

//===============================================
//�J�E���g�`�F�b�N
void Gamemain::CountCheck()
{
		if(this->Count>=0)//�J�E���g���[���ȉ��Ȃ�
	{
		this->Count++;//�J�E���g���v���X
	}
	if(this->Count>One_anim*2)//80�𒴂�����
	{
		this->Count=0;//�J�E���g���Z�b�g
	}
}

//============================================

//�L�[�t���O�`�F�b�N

void Gamemain::KeyCheck()
{
	this->KEYCHK.KeySet();//�L�[���͑҂�
	if(this->KEYCHK.KEY_END!=0x00)
	{
		STOPMIDI(this->MIDIBOSSBGM);
		STOPMIDI(this->MIDIMAINBGM);
		STOPMIDI(this->MIDIGAMEOVERBGM);
		this->GameFlag=TITLE_INIT;//ESC�Ń^�C�g����
	}else{
		if(Player.Flag==0)
	{
				//if(this->KEYCHK.KEY_S!=0x00)
				//{
				//	//Dispx=Draw_max-280;//�`��ʒu�����ύX
				//}else{
		if(this->KEYCHK.KEY_ENTER!=0x00)//�G���^�[
		{
		}else{
	if(this->KEYCHK.KEY_W!=0x00)//�W�����v
	{
		this->Player.Flag=M_Jump;//�W�����v�t���O
	}else{
		if(this->KEYCHK.KEY_SP!=0x00)//�U��
		{
			this->Player.Flag=M_Attack;//�A�^�b�N�t���O
		}else{
			if(this->KEYCHK.KEY_SHIFT!=0x00&&this->Gas!=0)//�e����//�K�X�͂O�ʊO
		{
			if(Pbullet.Flag==0&&Pbullet.MFlag==0)//�e�̃t���O���[�����`�F�b�N
			{
			this->Player.Flag=M_Shoot;
			}
		}else{
	if(this->KEYCHK.KEY_A!=0x00)//A�������Ă�����
	{
		this->Player.Flag=M_Walk;//�����t���O
		this->Player.POSFlag=1;//������
	}else{

	if(this->KEYCHK.KEY_D!=0x00)//D�������Ă�����
	{
		this->Player.Flag=M_Walk;//�����t���O
		this->Player.POSFlag=0;//�E����
	}else{//
		this->Player.Flag=M_Wait;
	}
	}
	}
		}//SP
	}//W
		}
		}
	//}
	}//ESC�ȊO
}
//=========================================================
//�e�̐i�s�ƃ`�F�b�N
void Gamemain::PbulletCheck()
{
		if(Pbullet.Flag!=0)
	{
		if(Pbullet.Flag==1)//���˂���Ă�����
		{
			Pbullet.Input((Player.x+Dispx+80),Player.y+80);
			Dbuff.SetBuf(Player_Bullet.animation[0],Pbullet.x,Pbullet.y,0);
			Pbullet.POSFlag=1;//�e�̔���ON
			Pbullet.Flag++;
		}
				if(Pbullet.Flag==One_anim-10)
		{
			Pbullet.Flag=0;//�t���O���Z�b�g
			Pbullet.POSFlag=0;//�e�̔���OFF
				}else{
		if(Pbullet.Flag>1)
		{
			Pbullet.x+=20;//�e�̐i�s
			Pbullet.Flag++;
			if(Count%2==0)//�J�E���g�ŕ\���ύX
			{
				Dbuff.SetBuf(Player_Bullet.animation[0],Pbullet.x,Pbullet.y,0);
			}else{
				Dbuff.SetBuf(Player_Bullet.animation[1],Pbullet.x,Pbullet.y,0);
			}
		}else{
		}
				}
	}
		if(Pbullet.MFlag!=0)
	{
		if(Pbullet.MFlag==1)//���˂���Ă�����(����)
		{
			Pbullet.Input((Player.x+Dispx+10),Player.y+80);
			Dbuff.SetBufM(Player_Bullet.animation[0],Pbullet.x,Pbullet.y,0);
			Pbullet.MFlag++;
			Pbullet.POSFlag=1;//�e�̔���ON
		}
				if(Pbullet.MFlag==One_anim-10)
		{
			Pbullet.MFlag=0;//�t���O���Z�b�g
			Pbullet.POSFlag=0;//�e�̔���OFF
				}else{
		if(Pbullet.MFlag>1)
		{
			Pbullet.x-=20;//�e�̐i�s
			Pbullet.MFlag++;
			if(Count%2==0)//�J�E���g�ŕ\���ύX
			{
				Dbuff.SetBufM(Player_Bullet.animation[1],Pbullet.x,Pbullet.y,0);
			}else{
				Dbuff.SetBufM(Player_Bullet.animation[0],Pbullet.x,Pbullet.y,0);
			}
		}else{
		}
				}
	}
}
//==================================================================
//�G�̏���
void Gamemain::EnemyD()
{
		//�G�Ƃ̂����蔻��`�F�b�N
	for(int i=0;i<EnemyMAX;i++)
	{
		if(Enemy[i].LifeFlag!=0&&Enemy[i].LifeFlag!=-1)//�t���O��0�łȂ����
			{
	this->Enemychk.HchkInit(Player_Wait.animation[0],Enemy_Wait.animation[0]);//�G�Ƃ̂����蔻��p��
	this->EHIT=this->Enemychk.Hitcheck(Player.x,Dispx,Player.y,Enemy[i].x,Enemy[i].y);//�������Ă��邩�`�F�b�N
	if(EHIT!=0&&EHIT!=-2)//�����肪0�ȊO�̏ꍇ
	{
		if(this->AttackF==1)//�U���t���O�������Ă���Ƃ�
		{
			if(this->Player.POSFlag!=0)//�������̏ꍇ
			{
				if(EHIT==-1)//�}�C�i�X�P�̏ꍇ
				{
		Enemy[i].LifeFlag=0;//�t���O0��
							PLAYWAVE(EnemyDame,0);
							PLAYWAVE(EnemyDeSE,0);
		Enemy[i].MFlag=1;//���S�t���O�I��
		Player.x+=Walk_x*2;//�߂�
		this->GASMOVEchk();//��������
				}else{
		this->AttackF=0;//�U���t���O0
		this->Player.Flag=M_LIFEM;//HP��������
		this->Player.MFlag=0;//�����̃t���O������
				}
			}else{//�E�����̏ꍇ
				if(EHIT==1)
				{
							Enemy[i].LifeFlag=0;//�t���O0��
							PLAYWAVE(EnemyDame,0);
							PLAYWAVE(EnemyDeSE,0);
							Enemy[i].MFlag=1;//���S�t���O�I��
							Player.x-=Walk_x*2;//�߂�
							this->GASMOVEchk();//��������
				}else{
		this->AttackF=0;
		if(this->Player.Flag!=M_LIFEM)//���������������ĂȂ��ꍇ
		{
			PLAYWAVE(PDameSE,0);
			this->Damage=Enemy_Damage;//-2�_���[�W
		}
		this->Player.Flag=M_LIFEM;//HP��������
		this->Player.MFlag=0;//�����̃t���O������
				}
			}//else
		}else{//�U���t���O�����ĂȂ��Ƃ�
			if(EHIT==2)//�G����̂Ƃ�
			{
							Enemy[i].LifeFlag=0;//�t���O0��
							Enemy[i].MFlag=1;//���S�t���O�I��
							PLAYWAVE(EnemyDame,0);
							PLAYWAVE(EnemyDeSE,0);
			}else{
					if(this->Player.POSFlag==1&&EHIT==1)//�������̏ꍇ�����肪���΂���̏ꍇ
			{
				Player.POSFlag=0;//�E������
			}
		if(this->Player.POSFlag==0&&EHIT==-1)//�E�����̏ꍇ�����肪���΂���̏ꍇ
			{
				Player.POSFlag=1;//��������
			}
				if(this->Player.Flag!=M_LIFEM)//���������������ĂȂ��ꍇ
		{
			PLAYWAVE(PDameSE,0);
			this->Damage=Enemy_Damage;//-2�_���[�W
		}
		this->Player.Flag=M_LIFEM;//HP��������
		this->Player.MFlag=0;//�����̃t���O������
			}
		}//
	}//EHIT
	if(this->Pbullet.POSFlag!=0)//�e���˃t���O�t���O�������Ă���Ƃ�
	{
		this->Enemychk.HchkInit(Player_Bullet.animation[0],Enemy_Wait.animation[0]);//�G�Ƃ̂����蔻��p��
	this->EHIT=this->Enemychk.Hitcheck(Pbullet.x-40,0,Pbullet.y,Enemy[i].x,Enemy[i].y);//�������Ă��邩�`�F�b�N
		if(EHIT!=0)//�����肪0�ȊO�̏ꍇ
		{

				Pbullet.MFlag=0;//�e�t���OOFF
				Pbullet.Flag=0;
				Pbullet.POSFlag=0;//���S�t���OOFF
		Enemy[i].LifeFlag=0;//�t���O0��
		PLAYWAVE(EnemyDame,0);
								PLAYWAVE(EnemyDeSE,0);
		Enemy[i].MFlag=1;//���S�t���O�I��
		}
	}
			}
	//============================================
	//�G�̎��b�A�j���[�V����
	if(Enemy[i].MFlag!=0)//�G�̃t���O�������Ă�����
	{
		if(Enemy[i].MFlag==9)
		{
			Enemy[i].MFlag=0;//�t���O0��
		}else{
		if(Enemy[i].MFlag>0)//�t���O��0�ȏ�
		{
			this->Dbuff.SetBuf(this->Enemy_Dead.animation[Enemy[i].MFlag/2],Enemy[i].x,Enemy[i].y,0);
			Enemy[i].MFlag++;
						if(Enemy[i].MFlag%2==0)
			{
				this->Dbuff.SetBufED(this->Enemy_Dead.animation[Enemy[i].MFlag/2],Enemy[i].x,Enemy[i].y,0);//���b��ʕ\��
			}
		}
		}
	}
//================================================
	//�G�̔z�u
	if(this->Enemy[i].LifeFlag!=0&&Enemy[i].LifeFlag!=-1)//�t���O�������Ă�����
	{
		if(this->Count<=One_anim)
					{
		this->Dbuff.SetBuf(this->Enemy_Wait.animation[0],Enemy[i].x,Enemy[i].y,0);
					}
										if(this->Count>One_anim)
					{
		this->Dbuff.SetBuf(this->Enemy_Wait.animation[1],Enemy[i].x,Enemy[i].y,0);
					}

	}
}
}


//==================================================================
//�e�����G�̏���
void Gamemain::EnemySD()
{
		//�G�Ƃ̂����蔻��`�F�b�N
	for(int i=0;i<EnemyShootMAX;i++)
	{
			if(EnemyS[i].LifeFlag!=0)//�t���O��0�łȂ����
			{
	this->Enemychk.HchkInit(Player_Wait.animation[0],Enemy_Wait.animation[0]);//�G�Ƃ̂����蔻��p��
	this->EHIT=this->Enemychk.Hitcheck(Player.x,Dispx,Player.y,EnemyS[i].x,EnemyS[i].y);//�������Ă��邩�`�F�b�N
	if(EHIT!=0&&EHIT!=-2)//�����肪0�ȊO�̏ꍇ
	{
		if(this->AttackF==1)//�U���t���O�������Ă���Ƃ�
		{
			if(this->Player.POSFlag!=0)//�������̏ꍇ
			{
				if(EHIT==-1)//�}�C�i�X�P�̏ꍇ
				{
		EnemyS[i].LifeFlag=0;//�t���O0��
		EnemyS[i].MFlag=1;//���S�t���O�I��
		PLAYWAVE(EnemyDame,0);
		PLAYWAVE(EnemyDeSE,0);
		Player.x+=Walk_x*2;//�߂�
		this->GASMOVEchk();//��������
				}else{
		this->AttackF=0;//�U���t���O0
		this->Player.Flag=M_LIFEM;//HP��������
		this->Player.MFlag=0;//�����̃t���O������
				}
			}else{//�E�����̏ꍇ
				if(EHIT==1)
				{
							EnemyS[i].LifeFlag=0;//�t���O0��
							EnemyS[i].MFlag=1;//���S�t���O�I��
							PLAYWAVE(EnemyDame,0);
							PLAYWAVE(EnemyDeSE,0);
							Player.x-=Walk_x*2;//�߂�
							this->GASMOVEchk();//��������
				}else{
		this->AttackF=0;//�U���t���O������
						if(this->Player.Flag!=M_LIFEM)//���������������ĂȂ��ꍇ
		{
			PLAYWAVE(PDameSE,0);
			this->Damage=Enemy_Damage;//-2�_���[�W
		}
		this->Player.Flag=M_LIFEM;//HP��������
		this->Player.MFlag=0;//�����̃t���O������
				}
			}//else
		}else{//�U���t���O�����ĂȂ��Ƃ�
			if(EHIT==2)//�G����̂Ƃ�
			{
							EnemyS[i].LifeFlag=0;//�t���O0��
							EnemyS[i].MFlag=1;//���S�t���O�I��
							PLAYWAVE(EnemyDame,0);
							PLAYWAVE(EnemyDeSE,0);
			}else{
					if(this->Player.POSFlag!=0&&EHIT==1)//�������̏ꍇ�����肪���΂���̏ꍇ
			{
				Player.POSFlag=0;//�E������
			}
		if(this->Player.POSFlag!=1&&EHIT==0)//�E�����̏ꍇ�����肪���΂���̏ꍇ
			{
				Player.POSFlag=1;//��������
			}
						if(this->Player.Flag!=M_LIFEM)//���������������ĂȂ��ꍇ
		{
			PLAYWAVE(PDameSE,0);
			this->Damage=Enemy_Damage;//-2�_���[�W
		}
		this->Player.Flag=M_LIFEM;//HP��������
		this->Player.MFlag=0;//�����̃t���O������
			}
		}//
	}//EHIT


	if(this->Pbullet.POSFlag!=0)//�e���˃t���O�t���O�������Ă���Ƃ�
	{
		this->Enemychk.HchkInit(Player_Bullet.animation[0],Enemy_Wait.animation[0]);//�G�Ƃ̂����蔻��p��
	this->EHIT=this->Enemychk.Hitcheck(Pbullet.x-40,0,Pbullet.y,EnemyS[i].x,EnemyS[i].y);//�������Ă��邩�`�F�b�N
		if(EHIT!=0)//�����肪0�ȊO�̏ꍇ
		{

				Pbullet.MFlag=0;//�e�t���OOFF
				Pbullet.Flag=0;
				Pbullet.POSFlag=0;//���S�t���OOFF
		EnemyS[i].LifeFlag=0;//�t���O0��
		EnemyS[i].MFlag=1;//���S�t���O�I��
		PLAYWAVE(EnemyDame,0);
		PLAYWAVE(EnemyDeSE,0);
		}
	}
			}
	//============================================
	//�G�̎��b�A�j���[�V����
	if(EnemyS[i].MFlag!=0)//�G�̃t���O�������Ă�����
	{
		if(EnemyS[i].MFlag==9)
		{
			EnemyS[i].MFlag=0;//�t���O0��
		}else{
		if(EnemyS[i].MFlag>0)//�t���O��0�ȏ�
		{
			this->Dbuff.SetBuf(this->Enemy_Dead.animation[EnemyS[i].MFlag/2],EnemyS[i].x,EnemyS[i].y,0);//���b��ʕ\��
			if(EnemyS[i].MFlag%2==0)
			{
				this->Dbuff.SetBufED(this->Enemy_Dead.animation[EnemyS[i].MFlag/2],EnemyS[i].x,EnemyS[i].y,0);//���b��ʕ\��
			}
			EnemyS[i].MFlag++;
		}
		}
	}
//================================================
	//�G�̔z�u
	if(this->EnemyS[i].LifeFlag!=0)//�t���O�������Ă�����
	{
		if(this->Count<=One_anim||this->Count>One_anim+20)//40�t���[���܂�
					{
		this->Dbuff.SetBuf(this->Enemy_Shoot.animation[0],EnemyS[i].x,EnemyS[i].y,0);
		}else{
		this->Dbuff.SetBuf(this->Enemy_Shoot.animation[1],EnemyS[i].x,EnemyS[i].y,0);
		}


		if(this->Count==One_anim)//40�t���[���ڂŒe����
		{
			for(int j=0;j<EnemyShootMAX*2;j++)//�󂢂Ă�e����
			{
				if(this->Ebullet[j].Flag==0)//�e���󂢂Ă��
				{
				this->Ebullet[j].Flag=1;//�t���O�I��
				this->Ebullet[j].Input(EnemyS[i].x-20,EnemyS[i].y+55);//�e�̍��W�ݒ�
				break;
				}
			}
		}


	}
}
}
//=================================================================
//�d�͏���
void Gamemain::GravityP()
{
	if(this->Player.y<Y_MAX&&Pchk==0)//�v���C���[���n�ʂ���̏ꍇ
	{
		Player.y+=Gravity;
	}
	if(Player.y>Y_MAX)//�n�ʂ�艺�̏ꍇ
	{
		Player.y=Y_MAX;//�n�ʂɍ��킹��
	}

}

//=========================================================
//�G�̒e�̏���
void Gamemain::EbulletCheck()
{
	for(int i=0;i<EnemyShootMAX*2;i++)//�e�̃t���O�������Ă��邩�`�F�b�N
		if(this->Ebullet[i].Flag==1)//�t���O��1�Ȃ�
		{
			if(Ebullet[i].LifeFlag!=0)//�t���O��0�ȊO�Ȃ�
			{
				if(Ebullet[i].LifeFlag<=8)//���C�t�����Ȃ��Ȃ�����~�܂�
				{
					this->Dbuff.SetBuf(Enemy_Bullet.animation[1],Ebullet[i].x,Ebullet[i].y,0);
				}else{
				Ebullet[i].x-=15;//�e�̐i�s
							this->Dbuff.SetBuf(Enemy_Bullet.animation[0],Ebullet[i].x,Ebullet[i].y,0);
				}
				Ebullet[i].LifeFlag--;//�e�̎���
			this->Enemychk.HchkInit(Player_Wait.animation[0],Enemy_Bullet.animation[0]);//�G�Ƃ̂����蔻��p��
			EHIT=this->Enemychk.HitcheckEB(Player.x,Dispx,Player.y,Ebullet[i].x,Ebullet[i].y);//�e�Ƃ̓����蔻��`�F�b�N
			if(EHIT!=0&&EHIT!=-2)//����艺���������Ă�����
			{
				if(this->Player.POSFlag==1&&EHIT==1)//�������̏ꍇ�����肪���΂���̏ꍇ
			{
				Player.POSFlag=0;//�E������
			}
								if(this->Player.Flag!=M_LIFEM)//���������������ĂȂ��ꍇ
		{
			PLAYWAVE(PDameSE,0);
			this->Damage=Enemy_DShoot;//-2�_���[�W
		}
		this->Player.Flag=M_LIFEM;//HP��������
		this->Player.MFlag=0;//�����̃t���O������
						Ebullet[i].LifeFlag=EbulletLifeMAX;//���C�t������
				Ebullet[i].Flag=0;//�t���O0��
			}
			}else{
				Ebullet[i].LifeFlag=EbulletLifeMAX;//���C�t������
				Ebullet[i].Flag=0;//�t���O0��
			}
		}
}

//================================================
//����`�F�b�N
void Gamemain::PlateCHECK()//����`�F�b�N
{
	Pchk=0;//������
		for(int i=0;i<Base_S;i++)
	{
		this->Platechk.HchkInit(Player_Jump.animation[0],Plate.animation[0]);//����`�F�b�N�p��
	this->Pchk=this->Platechk.HitcheckO(Player.x,Dispx,Player.y,PlateSMALL[i].x,PlateSMALL[i].y);
	if(Pchk!=0)
	{
		break;//���[�v������
	}
	}
			if(Pchk==0)
			{
		for(int i=0;i<Base_H;i++)
	{

		this->Platechk.HchkInit(Player_Jump.animation[0],Plate.animation[1]);//����`�F�b�N�p��
	this->Pchk=this->Platechk.HitcheckO(Player.x,Dispx,Player.y,PlateHIGH[i].x,PlateHIGH[i].y);
	
	if(Pchk!=0)
	{
		break;//���[�v������
	}
		}
		}
				if(Pchk==0)//����Ƃ������ĂȂ��ꍇ
				{
		for(int i=0;i<Base_L;i++)
		{
			this->Platechk.HchkInit(Player_Jump.animation[0],Plate.animation[2]);//�傫������`�F�b�N�p��
			this->Pchk=this->Platechk.HitcheckO(Player.x,Dispx,Player.y,PlateLARGE[i].x,PlateLARGE[i].y);
			
	if(Pchk!=0)
	{
		break;//���[�v������
	}
		}
				}

						for(int i=0;i<Base_H;i++)
						{
					this->Dbuff.SetBuf(this->Plate.animation[1],PlateHIGH[i].x,PlateHIGH[i].y,0);
						}
				for(int i=0;i<Base_L;i++)
		{
		this->Dbuff.SetBuf(this->Plate.animation[2],PlateLARGE[i].x,PlateLARGE[i].y,0);
		}
				for(int i=0;i<Base_S;i++)
	{
			this->Dbuff.SetBuf(this->Plate.animation[0],PlateSMALL[i].x,PlateSMALL[i].y,0);
	}
}

//===================================================================
//HP�o�[����
void Gamemain::HPstate()
{
	if(this->Damage!=0)//�_���[�W��0�ȊO
	{
		if(Gas!=0)	//HP�������Ă�����K�]���������邩�`�F�b�N
		{	//�K�\��������������K�\��������
		this->Gas-=Damage;//�_���[�W�����Z
		if(Gas<0)//0��艺�̏ꍇ
		{
			Gas=0;//0�ɂ���
		}
		}else{//�K�\�������Ȃ��ꍇHP�����炷
			Player.LifeFlag--;//���C�t����
			if(Player.LifeFlag==0)//���C�t���O�̏ꍇ
			{
				GAMEOVER.Flag=1;//�Q�[���I�[�o�[�t���O
			}else{
			Gas+=GAS_RH;//�K�\��//HP�����炵����K�\�������S��
			}
			//if(Player.LifeFlag<0)	//�����ă}�C�i�X�ɂȂ�����O�ɂ���
			//{
			//	Player.LifeFlag=0;
			//}
			//
		}
		Damage=0;//�_���[�W���Z�b�g

	
	//HP���[���̏ꍇ�Q�[���I�[�o�t���O�𗧂Ă�
	}
			if(Gas>GAS_MAX)//�K�\�����ʂ��ő�l�𒴂�����
		{
			Gas=GAS_MAX;//�K�\�����ʂ͍ő�̂܂�
		}
	//�K�\�����o�[�\��(12����ĂP�Q�܂łP�P�łP�P�܂ł̃o�[�\��)
		this->Dbuff.SetBuf(this->Player_GASbar.animation[0],GAS_X,GAS_Y,Dispx);//�K�\�����\��
	this->Dbuff.SetBufState(this->Player_GASbar.animation[1],GAS_X,GAS_Y,Dispx,this->Gas);
	for(int i=0; i<=80;i+=40)
	{
	this->Dbuff.SetBuf(this->Player_HP.animation[0],HP_X+i,GAS_Y,Dispx);//HP�\��
	}
	int j=0;
	for(int i=0; i<Player.LifeFlag;i++)
	{
		this->Dbuff.SetBuf(this->Player_HP.animation[1],HP_X+j,GAS_Y,Dispx);	//HP�o�[��\��(3����ꂽ��R�Q�łQ�ƕ\������)
		j+=40;
	}
}
//========================================================================
//�Q�[���I�[�o�[����

void Gamemain::GameOver()
{
							if(this->Count>0&&this->Count<=40)//�J�E���g�`�F�b�N
						{
			Dbuff.SetBuf(this->Player_GAMEOVER.animation[0],this->Player.x,this->Player.y,this->Dispx);
						}else{
			Dbuff.SetBuf(this->Player_GAMEOVER.animation[1],this->Player.x,this->Player.y,this->Dispx);
							}
							if(this->GAMEOVER.Flag<=60)//�t���O���O�܂�
							{	
							if(this->GAMEOVER.Flag>=30)//�Q�[���I�[�o�[�����\��
							{
			Dbuff.SetBuf(this->Player_GAMEOVER.animation[2],this->GAMEOVER.x-GAMEOVER.Flag,this->GAMEOVER.y,this->Dispx);
							}
														if(this->GAMEOVER.Flag>=40)//�Q�[���I�[�o�[�����\��
							{
			Dbuff.SetBuf(this->Player_GAMEOVER.animation[3],this->GAMEOVER.x,this->GAMEOVER.y+50,this->Dispx);
														}
																						if(this->GAMEOVER.Flag==10)
								{
									STOPMIDI(this->MIDIMAINBGM);
									STOPMIDI(this->MIDIBOSSBGM);
									PLAYMIDI(this->MIDIGAMEOVERBGM,0);//�Q�[���I�[�o�[����
								}
							GAMEOVER.Flag++;//�t���O���Z
}else{
	Dbuff.SetBuf(this->Player_GAMEOVER.animation[2],this->GAMEOVER.x-GAMEOVER.Flag,this->GAMEOVER.y,this->Dispx);
	Dbuff.SetBuf(this->Player_GAMEOVER.animation[3],this->GAMEOVER.x,this->GAMEOVER.y+50,this->Dispx);
	Dbuff.SetBuf(this->Player_GAMEOVER.animation[4],this->GAMEOVER.x,this->GAMEOVER.y+100,this->Dispx);
	//�J�E���g�ɉ����ăQ�[���I�[�o�[���[�V�����ύX

	//�L�[���̓`�F�b�N
	this->KEYCHK.KeySet();
	if(this->KEYCHK.KEY_S!=0x00||this->KEYCHK.KEY_sita!=0x00)
	{
		GAMEOVER.MFlag=1
			;//���݂̍��ڂ�����ɂ��炷
	}else{
		if(this->KEYCHK.KEY_W!=0x00||this->KEYCHK.KEY_ue!=0x00)//���݂̍��ڂ����ɂ��炷
	{
		GAMEOVER.MFlag=0;//���݂̍��ڂ�����ɂ��炷
	}else{
		if(this->KEYCHK.KEY_ENTER!=0x00||this->KEYCHK.KEY_SP!=0x00)
	{
		//CLOSEWAVE(WAVEBGM);
		switch(GAMEOVER.MFlag)	//���g���C�Ȃ�GAMEINIT//MENU�Ȃ烁�j���[�֖߂�
		{
		case 0:
			STOPMIDI(this->MIDIGAMEOVERBGM);
			GameFlag=GAMEMAIN_INIT;
			break;
		case 1:
			STOPMIDI(this->MIDIGAMEOVERBGM);
			GameFlag=TITLE_INIT;
			break;
		}
	}else{//ENTER
	}
	}
	}
	//�L�[���͂ɉ��������j���[�o�[�\��
		if(GAMEOVER.MFlag!=0)
		{
			Dbuff.SetBufD(this->Player_GAMEOVER.animation[4],this->GAMEOVER.x,this->GAMEOVER.y+100,this->Dispx);
		}else{
			Dbuff.SetBufD(this->Player_GAMEOVER.animation[3],this->GAMEOVER.x,this->GAMEOVER.y+50,this->Dispx);
		}

							}
}
//===============================================================
//�K�\��������`�F�b�N
	void Gamemain::GASMOVEchk()
	{
			if(Player.Flag==M_Attack&&Gas!=0)//�U���t���O�̏ꍇ
		{
			Damage=ATTACK_G;//�K�\��������
		}
			if(Player.Flag==M_Walk)//�����t���O�̏ꍇ
			{
				Damage=WALK_G;//�K�\��������
			}
	}



//=======================================================
//�{�X����
	void Gamemain::BossMODE()
	{
		if(Dispx<=Draw_max)//�`��ʒu��7000�ȉ��Ȃ�
		{
		Dispx++;//�`��ʒu�����ύX
		}
		if(Player.x<Draw_min+10)//�v���C���[�̍��W����ʊO�Ȃ�
		{
			Player.x=Draw_min+10;
		}
		//�{�X�\��
		if(Boss.LifeFlag!=0)//�{�X��HP��0�łȂ��ꍇ
		{
		if(Count%2==0)//��󏈗�
		{
	this->Dbuff.SetBuf(this->Plate.animation[3],Info.x,Info.y,0);
		}else{
				this->Dbuff.SetBufD(this->Plate.animation[3],Info.x,Info.y,0);
		}
						if(Message.Flag!=1&&Dispx<Draw_max-10)//���b�Z�[�W�t���O�������ĂȂ��{�X�͈̔͊O��������
						{
			Dispx=Draw_max-10;//�f�B�X�v�����ړ�
						}

		if(Message.Flag==1)//���b�Z�[�W�t���O1�̎�
		{
		if(Dispx>Draw_max-10)//�`��ʒu��6050�ȏ�Ȃ�
		{
			this->Message.Flag=0;//���b�Z�[�W�t���OOFF
			this->Message.MFlag=0;
		}
		}else{

		this->BossHIT();

		//========================================================================
		switch(Boss.LifeFlag)//�c�胉�C�t�ōU���`�Ԍ���
		{
			//======================================================================
		case 3://���̏���
		this->PlateSMALL[0].InputX(7050);
		this->PlateHIGH[0].InputX(7000);
			if(Enemy[0].LifeFlag==0&&Boss.MFlag==0)//�G�̃t���O��0���`�F�b�N
			{
				Enemy[0].LifeFlag=-1;	//�G�t���O���Ă�//�t���O�̓}�C�i�X
				Boss.MFlag=80;//�{�X�̓����t���O�𗧂Ă�
			}
			if(Enemy[0].LifeFlag==-1)
			{
				this->BossEnemy();//�{�X�̌�����G���o��
			}
			if(Enemy[0].LifeFlag==1)			//1�Ȃ�o��
			{
				Enemy[0].x-=15;//�i�s
			}
			this->Dbuff.SetBuf(BossN.animation[0],Boss.x,Boss.y,0);//�{�X�\��
			this->Dbuff.SetBuf(BossE.animation[0],Boss.x,Boss.y,0);//�{�X�\��
			if(Enemy[0].LifeFlag!=-1)
			{
				this->Dbuff.SetBuf(BossM.animation[0],Boss.x,Boss.y,0);//�{�X�\��
			}
			break;
			//======================================================================-
		case 2://�@�̏���
			Enemy[0].LifeFlag=0;
			if(BossBullet.LifeFlag==0&&Boss.MFlag==13)//�e�Ɠ����̃t���O���[���Ȃ�
			{
				PLAYWAVE(BossShootSE,0);
				BossBullet.LifeFlag=1;//�t���O�I��
				BossBullet.Input(7780,205);//�ʒu�Z�b�g
			}
			if(Boss.MFlag==0)
			{
				Boss.MFlag=80;
			}
				this->Dbuff.SetBuf(BossE.animation[0],Boss.x,Boss.y,0);//�{�X�\��
			this->Dbuff.SetBuf(BossM.animation[0],Boss.x,Boss.y,0);//�{�X�\��
			if(Boss.MFlag<=18)//20�ȉ��Ȃ�
			{
				this->Dbuff.SetBuf(BossN.animation[Boss.MFlag/6],Boss.x,Boss.y,0);//�{�X�\��
			}else{
				this->Dbuff.SetBuf(BossN.animation[0],Boss.x,Boss.y,0);//�{�X�\��
			}
		this->PlateSMALL[0].InputX(7000);//����Z�b�g
		this->PlateHIGH[0].InputX(7300);
			Info.InputY(160);
			Jakuten.InputY(150);
			break;
			//=============================================================================
		case 1://�ڂ̏���
			if(BossR.LifeFlag==0&&Boss.MFlag==0)//�e�Ɠ����̃t���O���[���Ȃ�
			{
				PLAYWAVE(BossRaserSE,0);
				BossR.LifeFlag=1;//�t���O�I��
				BossR.Input(6800,170);//�ʒu�Z�b�g
				Boss.MFlag=80;
			}
							this->Dbuff.SetBuf(BossN.animation[0],Boss.x,Boss.y,0);//�{�X�\��
			this->Dbuff.SetBuf(BossM.animation[0],Boss.x,Boss.y,0);//�{�X�\��
			if(BossR.LifeFlag!=0)//20�ȉ��Ȃ�
			{
				this->Dbuff.SetBuf(BossE.animation[2],Boss.x,Boss.y,0);//�{�X�\��
			}else{
				if(Boss.MFlag>=50)//20�ȉ��Ȃ�
			{
				this->Dbuff.SetBuf(BossE.animation[3],Boss.x,Boss.y,0);//�{�X�\��
			}else{
				if(Boss.MFlag<=20)
				{
					this->Dbuff.SetBuf(BossE.animation[1],Boss.x,Boss.y,0);//�{�X�\��
				}else{
					this->Dbuff.SetBuf(BossE.animation[0],Boss.x,Boss.y,0);//�{�X�\��
				}
							}
			}
		this->PlateSMALL[0].InputX(7000);
		this->PlateHIGH[0].InputX(7150);
		this->PlateLARGE[0].InputX(7400);
		//���[�U�[�`�F�b�N
		//���[�U���o��
			Info.InputY(140);
			Jakuten.InputY(130);
			break;
		//=================================================================================================================
		}
			//�{�X�{�̂̂����蔻��
			this->Enemychk.HchkInit(Player_Wait.animation[0],BossG.animation[0]);//�{�X�Ƃ̂����蔻��p��
			EHIT=this->Enemychk.HitcheckEB
				(Player.x,Dispx,Player.y,Boss.x,Boss.y);//�e�Ƃ̓����蔻��`�F�b�N
			if(EHIT!=0)//�������Ă�����
			{
				if(this->Player.POSFlag==1&&EHIT==1)//�������̏ꍇ�����肪���΂���̏ꍇ
				{
				Player.POSFlag=0;//�E������
				}
								if(this->Player.Flag!=M_LIFEM)//���������������ĂȂ��ꍇ
								{
									PLAYWAVE(PDameSE,0);
			this->Damage=Enemy_DShoot;//-2�_���[�W
								}
		this->Player.Flag=M_LIFEM;//HP��������
		this->Player.MFlag=0;//�����̃t���O������
			}

		}
		Boss.MFlag--;		//�{�X�̓����t���O����
		if(Boss.MFlag<0)//�����t���O���O�ȉ��̏ꍇ
		{
			Boss.MFlag=0;//0�Ƀ��Z�b�g
		}
				if(Enemy[0].LifeFlag==-1)
				{
					this->Dbuff.SetBuf(BossM.animation[(Boss.MFlag-71)/3],Boss.x,Boss.y,0);//�{�X�\��
					Dbuff.SetBuf(Enemy_Dead.animation[(Boss.MFlag-70)/2],Enemy[0].x,Enemy[0].y,0);
				}
				this->BossBulletchk();//�e�̔���`�F�b�N�ƕ\��
				this->BossRaser();
		}else{//�{�X�������Ă���Ƃ��̏���
					//CLOSEWAVE(WAVESEE);
					//CLOSEWAVE(WAVESE);
			this->BossDead();//���S����
			this->Message.Flag=1;//�{�X�����񂾂烁�b�Z�[�W
			if(this->Bakuha[2].Flag==2&&Boss.POSFlag==0)
			{
				STOPMIDI(this->MIDIBOSSBGM);//���y�I��
				
					this->Boss.POSFlag=1;//�{�X�̃V�[���؂�ւ�ON
					Boss.MFlag=30;
			}
			if(Boss.MFlag<=10&&Boss.POSFlag==1)
			{
				Boss.POSFlag=2;
			}
			if(Boss.MFlag==0&&Boss.POSFlag==2)
			{
		this->GameFlag=ENDING_INIT;
			}else{
			}
			//�{�X�̎��S�\��
					}
					this->Expl();//���j�\��
	//this->SetMessage();
	}

//===============================================================
	//�{�X��HP�������̏���
	void Gamemain::BossMIHP()
	{
		this->Bakuha[Boss.LifeFlag-1].Flag=1;//���j�t���O������
		this->Bakuha[Boss.LifeFlag-1].LifeFlag=0;//���j�t���O������
		this->Bakuha[Boss.LifeFlag-1].Input(Jakuten.x+30,Jakuten.y-15);//��_�̈ʒu�ɔ��j�Z�b�g
		if(Boss.LifeFlag==2)//�@�̏ꍇ
		{
			this->Bakuha[Boss.LifeFlag-1].Input(Jakuten.x+5,Jakuten.y+20);//��_�̈ʒu�ɔ��j�Z�b�g
		}
		if(Boss.LifeFlag==1)//�ڂ̏ꍇ
		{
			this->Bakuha[2].Flag=1;//������񔚔�
			this->Bakuha[1].Flag=1;
		}
		this->Boss.LifeFlag--;//HP������
		this->Boss.MFlag=20;
		this->Itemx[9].InputX(7100);
		this->Itemx[9].Flag=1;//�A�C�e�����o��
		this->Player.x-=Walk_x*3;//���������点��
	}
	//========================================================
	//���b�Z�[�W����
	void Gamemain::SetMessage()
	{
				if(this->Message.MFlag>=0)//0����Ȃ�
				{
			if(this->Message.MFlag>=10)//10����Ȃ�
			{
				this->KeyCheck();//�L�[�`�F�b�N
				if((this->KEYCHK.KEY_D!=0x00||this->KEYCHK.KEY_ENTER!=0x00)&&Boss.LifeFlag!=0)//�G���^�[�����ړ��ŏ����邪�{�X������ł鎞�͏����Ȃ�
				{
				//PLAYWAVE(WAVESE,1);
				this->Message.Flag=0;
				this->Message.MFlag=0;
				if(Boss.LifeFlag==0)
				{
					this->GameFlag=TITLE_INIT;//�^�C�g����������
				}
				this->Dbuff.SetMap(this->Background.animation[0]);
				}
				this->Dbuff.SetMapBHX(this->Background.animation[0]);
				if(Boss.LifeFlag==0)//�{�X�����񂾂�
				{
				this->Dbuff.SetBuf(this->Message_Window.animation[2],Message.x,Message.y,Dispx);//���b�Z�[�W�\��
				}else{
				if(Boss.Flag==1)//�{�X�t���O��1�Ȃ�
				{
				this->Dbuff.SetBuf(this->Message_Window.animation[1],Message.x,Message.y,Dispx);//���b�Z�[�W�\��
				}else{
				this->Dbuff.SetBuf(this->Message_Window.animation[0],Message.x,Message.y,0);//���b�Z�[�W�\��
				}
				}
			}else{
			if(this->Message.MFlag>=5)
			{
				this->Dbuff.SetMapBHX(this->Background.animation[0]);
			}else{
				this->Dbuff.SetMapBHX(this->Background.animation[0]);
			}
Message.MFlag++;
			}
			
		}
	}
//=========================================================================================
//�{�X���������蔻��
	void Gamemain::BossHIT()
	{
				this->Enemychk.HchkInit(Player_Wait.animation[0],Plate.animation[0]);//�G�Ƃ̂����蔻��p��
	this->EHIT=this->Enemychk.Hitcheck(Player.x,Dispx,Player.y,Jakuten.x,Jakuten.y);//�������Ă��邩�`�F�b�N
	if(EHIT!=0&&EHIT!=-2)//�����肪0�ȊO�̏ꍇ
	{
		if(this->AttackF==1)//�U���t���O�������Ă���Ƃ�
		{
			if(this->Player.POSFlag!=0)//�������̏ꍇ
			{
				if(EHIT==-1)//�}�C�i�X�P�̏ꍇ
				{
		BossMIHP();//���C�t����
							BossMIHP();//���C�t����
		Player.x+=Walk_x*2;//�߂�
		this->GASMOVEchk();//��������
				}else{
		this->AttackF=0;//�U���t���O0
		this->Player.Flag=M_LIFEM;//HP��������
		this->Player.MFlag=0;//�����̃t���O������
				}
			}else{//�E�����̏ꍇ
				if(EHIT==1)
				{
							BossMIHP();//���C�t����
							Player.x-=Walk_x*2;//�߂�
							this->GASMOVEchk();//��������
				}else{
		this->AttackF=0;
		if(this->Player.Flag!=M_LIFEM)//���������������ĂȂ��ꍇ
		{
			PLAYWAVE(PDameSE,0);
			this->Damage=Enemy_Damage;//-2�_���[�W
		}
		this->Player.Flag=M_LIFEM;//HP��������
		this->Player.MFlag=0;//�����̃t���O������
				}
			}//else
		}else{//�U���t���O�����ĂȂ��Ƃ�
			if(EHIT==2)//�G����̂Ƃ�
			{
							BossMIHP();//���C�t����
			}else{
					if(this->Player.POSFlag==1&&EHIT==1)//�������̏ꍇ�����肪���΂���̏ꍇ
			{
				Player.POSFlag=0;//�E������
			}
		if(this->Player.POSFlag==0&&EHIT==-1)//�E�����̏ꍇ�����肪���΂���̏ꍇ
			{
				Player.POSFlag=1;//��������
			}
				if(this->Player.Flag!=M_LIFEM)//���������������ĂȂ��ꍇ
		{
			PLAYWAVE(PDameSE,0);
			this->Damage=Enemy_Damage;//-2�_���[�W
		}
		this->Player.Flag=M_LIFEM;//HP��������
		this->Player.MFlag=0;//�����̃t���O������
			}
		}//
	}//EHIT

		if(this->Pbullet.POSFlag!=0)//�e���˃t���O�t���O�������Ă���Ƃ�
	{
		this->Enemychk.HchkInit(Player_Bullet.animation[0],Plate.animation[0]);//�G�Ƃ̂����蔻��p��
	this->EHIT=this->Enemychk.Hitcheck(Pbullet.x-40,0,Pbullet.y,Jakuten.x,Jakuten.y);//�������Ă��邩�`�F�b�N
		if(EHIT!=0)//�����肪0�ȊO�̏ꍇ
		{

				Pbullet.MFlag=0;//�e�t���OOFF
				Pbullet.Flag=0;
				Pbullet.POSFlag=0;//���S�t���OOFF
				BossMIHP();//���S�t���O�I��
		}
	}
	}



	//=================================================================
//�{�X����G���o������
	void Gamemain::BossEnemy()
	{
		if(Boss.MFlag<=80)//�t���O��80�ȉ��Ȃ�
		{
			if(Boss.MFlag==80)
			{
				Enemy[0].InputX(7750);//���W�Z�b�g
			}
			Enemy[0].x--;//�O�ɐi��
			if(Boss.MFlag<=70)//7�O�ȉ��Ȃ�
			{
				Enemy[0].LifeFlag=1;//���C�t�t���O�𗧂Ă�
			}
		}
	}

//�{�X�̒e�̃`�F�b�N
	//==================================================
	void Gamemain::BossBulletchk()
	{
		if(Boss.MFlag>14&&Boss.MFlag<=20)//�t���O���Q�O�ȉ��Ȃ�
		{
			BossBullet.LifeFlag=0;
		}
		if(BossBullet.LifeFlag!=0)//�t���O�������Ă�����
		{
			BossBullet.x-=20;
			this->Dbuff.SetBuf(BossBu.animation[0],BossBullet.x,BossBullet.y,0);//�\��
			this->Enemychk.HchkInit(this->Player_Wait.animation[0],this->BossBu.animation[0]);
			EHIT=Enemychk.HitcheckEB(Player.x,Dispx,Player.y,BossBullet.x,BossBullet.y);//�{�X�ƃv���C���[�̍��W�`�F�b�N
						if(EHIT!=0&&EHIT!=-2)//����艺���������Ă�����
			{
				if(this->Player.POSFlag==1&&EHIT==1)//�������̏ꍇ�����肪���΂���̏ꍇ
			{
				Player.POSFlag=0;//�E������
			}
								if(this->Player.Flag!=M_LIFEM)//���������������ĂȂ��ꍇ
		{
			PLAYWAVE(PDameSE,0);
			this->Damage=Enemy_DShoot+1;//-2�_���[�W
		}
		this->Player.Flag=M_LIFEM;//HP��������
		this->Player.MFlag=0;//�����̃t���O������
		BossBullet.LifeFlag=0;//�t���O0��
			}
			}else{
				BossBullet.LifeFlag=0;//�t���O0��
		}
	}

	//�{�X�̃��[�U�[����
	//=============================================================================
	void Gamemain::BossRaser()
	{
				if(Boss.MFlag<=60)
		{
			BossR.LifeFlag=0;
		}
		if(BossR.LifeFlag!=0)//�t���O�������Ă�����
		{
			this->Dbuff.SetBuf(BossRa.animation[0],BossR.x,BossR.y,0);//�\��
			this->Enemychk.HchkInit(this->Player_Wait.animation[0],this->BossRa.animation[0]);
			EHIT=Enemychk.HitcheckEB(Player.x,Dispx,Player.y,BossR.x,BossR.y);//�{�X�ƃv���C���[�̍��W�`�F�b�N
						if(EHIT!=0&&EHIT!=-2)//����艺���������Ă�����
			{
				if(this->Player.POSFlag==1&&EHIT==1)//�������̏ꍇ�����肪���΂���̏ꍇ
			{
				Player.POSFlag=0;//�E������
			}
								if(this->Player.Flag!=M_LIFEM)//���������������ĂȂ��ꍇ
		{
			PLAYWAVE(PDameSE,0);
			this->Damage=Enemy_DShoot+2;//-2�_���[�W
		}
		this->Player.Flag=M_LIFEM;//HP��������
		this->Player.MFlag=0;//�����̃t���O������
		BossR.LifeFlag=0;//�t���O0��
			}
			}else{
				BossR.LifeFlag=0;//�t���O0��
		}
	}

	//======================================================================
//��������
	void Gamemain::Expl()
	{
		for(int i=0;i<JakutenMAX;i++)
		{
			if(Bakuha[i].Flag==1)
			{
				if(Bakuha[i].LifeFlag==1&&Boss.LifeFlag>0)//���C�t��1�łO�ȏ�ɂȂ�����
				{
					PLAYWAVE(this->BossDeSE,0);
				}
				
					if(Bakuha[i].LifeFlag==1&&Boss.LifeFlag==0)//���C�t��1�łO�ȏ�ɂȂ�����
				{
					PLAYWAVE(this->BossDeTSE,0);
				}
				if(Bakuha[i].LifeFlag==30)//���C�t��30�ɂȂ�����
				{
					Bakuha[i].Flag=2;//���݂̂̃t���O
					Bakuha[i].LifeFlag=0;//�t���O���Z�b�g
				}else{
				this->Dbuff.SetBuf(this->Explasive.animation[Bakuha[i].LifeFlag/6],Bakuha[i].x,Bakuha[i].y,0);//���j�\��
				}
				Bakuha[i].LifeFlag++;//�i�s
			}else{
			if(Bakuha[i].Flag==2)//���̃t���O
			{
				if(Boss.MFlag%2==0)
				{
					this->Dbuff.SetBuf(this->Explasive.animation[5],Bakuha[i].x,Bakuha[i].y,0);//���j�\��
				}else{
					this->Dbuff.SetBuf(this->Explasive.animation[6],Bakuha[i].x,Bakuha[i].y,0);//���j�\��
				}
			}else{
			}
			}
		}
	}

	//�{�X�̎��S����
	//=================================================================================================

	void Gamemain::BossDead()
	{
		if(Count%2==0)
		{
			this->Dbuff.SetBuf(BossM.animation[0],Boss.x,Boss.y,0);//�{�X�\��
			this->Dbuff.SetBuf(BossE.animation[0],Boss.x,Boss.y,0);//�{�X�\��
			this->Dbuff.SetBuf(BossN.animation[0],Boss.x,Boss.y,0);//�{�X�\��
		}else{
			this->Dbuff.SetBufED(BossM.animation[0],Boss.x,Boss.y,0);//�{�X�\��
			this->Dbuff.SetBufED(BossE.animation[0],Boss.x,Boss.y,0);//�{�X�\��
			this->Dbuff.SetBufED(BossN.animation[0],Boss.x,Boss.y,0);//�{�X�\��
		}
		if(Boss.POSFlag==1)
		{
			this->Dbuff.SetMapWX(this->Background.animation[0]);
			Boss.MFlag--;
		}
		if(Boss.POSFlag==2)
		{
			this->Dbuff.SetMapW(this->Background.animation[0]);
			Boss.MFlag--;
		}
	}


	//==============================================================
	//�Q�[�����C���폜
	void Gamemain::GameDel()
	{
			this->Plate.Del();
	this->Background.Del();
	this->Player_Wait.Del();
	this->Player_Walk.Del();
	this->Player_Jump.Del();
	this->Player_Shot.Del();
	this->Player_Bullet.Del();
	this->Player_Attack.Del();
	this->Player_GASbar.Del();
	this->Player_GAMEOVER.Del();
	this->Player_HP.Del();
	this->Enemy_Wait.Del();
	this->Enemy_Shoot.Del();
	this->Enemy_Bullet.Del();
	this->Enemy_Dead.Del();
	
	this->Item.Del();
	
	this->BossG.Del();
	this->BossM.Del();
	this->BossN.Del();
	this->BossE.Del();
	this->BossBu.Del();
	this->BossRa.Del();
	this->Explasive.Del();

	this->Message_Window.Del();

	CLOSEMIDI(this->MIDIMAINBGM);//���y���J��
	CLOSEMIDI(this->MIDIGAMEOVERBGM);//�Q�[���I�[�o�[
	CLOSEMIDI(this->MIDIBOSSBGM);//�{�X

	CLOSEWAVE(AttackSE);//�U����
	CLOSEWAVE(ShootSE);//���ˉ�
	CLOSEWAVE(EnemyDeSE);//�G�̎��b��
	CLOSEWAVE(BossShootSE);//�{�X�̔��ˉ�
	CLOSEWAVE(BossRaserSE);
	CLOSEWAVE(BossDeSE);//�G�̎��b��
	CLOSEWAVE(BossDeTSE);//�G�̎��b��
	CLOSEWAVE(BossLSE);
	CLOSEWAVE(ItemSE);
	CLOSEWAVE(EnemyDame);
	CLOSEWAVE(PDameSE);
	}

