#include"Image.h"
#include"base.h"
#include"hitchk.h"
#include"KeyIN.h"
#ifndef _title
#define _title

class Title{
public:
	Title();
int TitleInit();
int TitleMain();
void titleDel();//�^�C�g���̏�����
private:
	int Count;//�J�E���g
	int	TitleFlag;//��ʑJ�ڂ̌���t���O
	int TITLEBGM;//�^�C�g��BGM
	int DOORSE;//�h�A�߂鉹
ImageFile MenuBack;//���j���[�摜�ǂݍ���
kind MenuButton;
kind Player_Wait;//�ҋ@���[�V����
kind Player_Walk;//�������[�V����
Base Player;//�v���C���[���W�t���O
Base Start;//�{�^���̍��W�i�[
Base Logo;//���S�̍��W
Buffer Dbuff;
Hchk Door;//�h�A�Ƃ̔���
KeyIn KEYCHK;//�L�[�`�F�b�N

};

#endif


