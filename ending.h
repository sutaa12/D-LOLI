#include"Image.h"
#include"title.h"
#include"base.h"
#include"main.h"
#include"hitchk.h"
#include"KeyIN.h"
#ifndef _ending
#define _ending
class Ending{
public:
Ending();//�R���X�g���N�^

int endinit();//�G���f�B���O������
int endingmain();//�G���f�B���O�̃��C��
void endingDel();//�G���f�B���O�̏�����
private:
	kind Player_Walk;//�������[�V����
	kind Player_Wait;//�ҋ@���[�V����
	kind EndBack;//�G���f�B���O�p�w�i
	kind Logo;//�G���f�B���O���S�p

	int Dispx;//�w�i�摜�̕`��ʒu
	int Count;//�Q�[���S�̂̃J�E���g�@�S�̂̃t���O�Ǘ�
	int EndFlag;//�G���f�B���O�̗���̐���
	int ENDINGBGM;//�G���f�B���O�pBGM

	Base Car;//�Ԃ̏��
	Base Credit;//�N���W�b�g���
	Base Player;//�v���C���[���
	Base Logoinfo;//���S���

	Buffer Dbuff;//�`��p

	KeyIn KEYCHK;//�L�[���̓`�F�b�N
};
#endif

