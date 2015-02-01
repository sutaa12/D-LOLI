#include"Image.h"
#include"title.h"
#include"main.h"
#include"hitchk.h"
#include"KeyIN.h"
#ifndef _gamemain
#define _gamemain

class Gamemain{

public:
	//�R���X�g���N�^
	Gamemain();//�Ăяo�����̉摜�i�[
	//������
	int GameInit();//���W���Ȃǂ̏�����
	//�Q�[�����C��
	int Gmain();
	//�\���ʒu����
	void ChengeDisp();
	//�A�C�e���`��
	void DItem();
	//�J�E���g����
	void CountCheck();
	//�G�̏����z�u
	void SetEnemy();
	//�A�C�e���̏����z�u
	void SetItem();
	//����̏����z�u
	void SetPlate();
	//���b�Z�[�W�`�F�b�N
	void SetMessage();
	//�{�X�����蔻��
	void BossHIT();
	//����t���O�`�F�b�N
	void MFlagCheck();
	void AttackMODE();//�U���t���O��
	void WalkMODE();//�ړ���
	void JumpMODE();//�W�����v��
	void MutekiMODE();//�_���[�W���󂯂���
	void ShootMODE();//���ˎ�
	void WaitMODE();//�ҋ@��

	void GameDel();//�Q�[�����C��������
	//============================
	//�L�[�`�F�b�N
	void KeyCheck();
	//�v���C���[�̒e�`�F�b�N
	void PbulletCheck();
	//�d�͏���
	void GravityP();
	//����`�F�b�N
	void PlateCHECK();
	//�G�̕\��
	void EnemyD();
	//�e��łG�̕\��
	void EnemySD();
	//�e�̐i�s����
	void EbulletCheck();
	//HP����
	void HPstate();
	//�Q�[���I�[�o�[����
	void GameOver();
	//�����`�F�b�N
	void GASMOVEchk();
	//�{�X�̏���
	void BossMODE();
	//�{�X�̌�������
	void BossMIHP();
	//�{�X����G���o�鏈��
	void BossEnemy();
	//�{�X�̒e�̏���
	void BossBulletchk();
	//�{�X�̃��[�U�[����
	void BossRaser();
	//��������
	void Expl();
	//���S����
	void BossDead();
	//����~
	void StopMUSIC();
	//===============================

private:
	int Dispx;//�w�i�摜�̕`��ʒu
	int Count;//�Q�[���S�̂̃J�E���g�@�S�̂̃t���O�Ǘ�
	int Gravity;//�d��
	int GameFlag;//�Q�[���̐i�s�t���O
	int Pchk;//���ꂪ�������Ă��邩�`�F�b�N
	int AttackF;//�U���̃t���O
	int EHIT;//�G�Ɠ����Ă��邩�̃t���O
	int Damage;//�_���[�W�l�Ɖ񕜒l
	int Gas;//�K�\�����c��


	int MIDIMAINBGM;//BGM�n���h��
	int MIDIGAMEOVERBGM;//BGM�n���h��
	int MIDIBOSSBGM;//BGM�n���h��

	int AttackSE;//�U����
	int ShootSE;//���ˉ�
	int PDameSE;//�v���C���[�_���[�W
	int EnemyDeSE;//�G�̎��b��
	int EnemyDame;//�G�̃_���[�W
	int BossShootSE;//�{�X�̔��ˉ�
	int BossRaserSE;//�{�X�̃��[�U�[��
	int BossDeSE;//�{�X�_���[�W��
	int BossDeTSE;//�{�X���b��
	int BossLSE;//�΂���
	int ItemSE;//�A�C�e���K����

	kind Background;//�w�i�摜
	kind Plate;//����̉摜
	kind Player_Wait;//�v���C���[�摜
	kind Player_Walk;
	kind Player_Attack;
	kind Player_Jump;
	kind Player_Shot;//�v���C���[�̔���
	kind Player_Bullet;//�e
	kind Player_GASbar;//�K�\�����o�[�\��
	kind Player_GAMEOVER;//�Q�[���I�[�o�[�\��
	kind Player_HP;//HP�\��
	kind Enemy_Wait;//�G�摜
	kind Enemy_Shoot;
	kind Enemy_Bullet;//�G�̒e
	kind Enemy_Dead;//�G�̎��S�A�j��
	kind Message_Window;//���b�Z�[�W�摜
	kind BossG;//�{�X�摜
	kind BossM;//�{�X�摜�i��)
	kind BossN;//�{�X�摜(�@)
	kind BossE;//�{�X�摜(��)
	kind BossRa;//�{�X�̃��[�U�[
	kind BossBu;//�{�X�̒e
	kind Explasive;//����
	kind Item;//�A�C�e��

	Base Pbullet;//�v���C���[�̒e
	Base Player;//�v���C���[���W�ƃt���O
	Base *Enemy;//�G�̍��W�ƃt���O
	Base *EnemyS;//�G2�̍��W�ƃt���O
	Base *Ebullet;//�G�̒e�ƃt���O
	Base *Itemx;//�A�C�e���̍��W�t���O

	Base *PlateHIGH;//����̍��W�t���O
	Base *PlateSMALL;//����������
	Base *PlateLARGE;//�傫������

	Base GAMEOVER;//�Q�[���I�[�o�[�����\��
	Base Message;//���b�Z�[�W�\��

	Hchk Platechk;//�傫������̂����蔻��
	Hchk Enemychk;//�G�Ƃ̂����蔻��

	Base Jakuten;//�G�̎�_�̏��
	Base BossBullet;//�{�X�̒e�̏��
	Base Boss;//�{�X���
	Base BossR;//�{�X�̃��[�U�[���
	Base Info;//���\��
	Buffer Dbuff;//�`��p
	Base *Bakuha;//�����̈ʒu

	KeyIn KEYCHK;//�L�[���̓`�F�b�N
	
};


//=========================================================�}�N����`
#define Y_MAX 150//�n�ʂ̏��
#define Disp_max 500//��ʂ̈ړ����
#define Disp_min 100//��ʂ̍ŏ��ړ�
#define Map_Max 800//��ʒ[�̏��

#define Draw_max 7000//�}�b�v�̏��
#define Draw_min 0//�}�b�v�̍ŏ�

#define Walk_x 10//�ړ���

#define One_anim 40	//�ҋ@�A�j���[�V�����̋�؂�

#define Max_anim 3//�t���O�̃}�b�N�X
#define W_anim 0.4f//�t���O�̉��Z



#define Base_S 7//����������̐�
#define Base_H 4//�傫������̐�
#define Base_L 4//�����Ƒ傫������̐�
#define Jump_MAX 6//�W�����v�̍ő�l

#define EnemyMAX 14//�G�̐��̍ő�
#define EnemyShootMAX 11//���˂���G�̐��̍ő�
#define Enemy_Walkx 10//�G�̈ړ���
#define Enemy_Damage 2//�G�̍U����
#define Enemy_DShoot 3//�������̍U����

#define JumpUp 4//�W�����v�̉����x

#define EbulletLifeMAX 25//�G�̒e�̃��C�t�̍ő�l

#define STARTLIFE 3//�J�n���̃��C�t
#define STARTG 6//�J�n���̃K�X
#define GAS_MAX 12//�K�\�����̍ő�l
#define GAS_RH 4//�񕜒l

#define GAS_X 10//�K�\�����o�[�\���̂���
#define GAS_Y 10//HP�������ʒu
#define ATTACK_G 1//�U���̏���
#define SHOOT_G 3//���˂̏���
#define WALK_G 2//�����U���̏���
#define HP_X 270//HP�̂���
#define JakutenMAX 3//��_�̍ő吔

#define ITEM_MAX 10//�A�C�e���̐�


enum Move_MODE{
	M_Wait,M_Walk,M_Jump,M_Attack,M_Shoot,M_LIFEM
};
#endif

