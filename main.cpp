//======================================
//CP-11S-A02 09 ��؈���
//=========================================
//CP11 CP11SA02-09 20029�uHEW��o�ŔŁv
//
//���e:�^�C�g����AD�ňړ��A���̑O��W�L�[�ŊJ�n�@����ȊO���ƏI��
//AD�ňړ�W�ŃW�����vS�������ƃ{�X�܂ŃX�L�b�v	�V�t�g�L�[�ŉ������U�� �G���^�[�Ń^�C�g���ɖ߂�
//MIDI�̃n���h�������܂��������ł��Ȃ����ߏI���������I���ɂȂ邪�C���\��
//�U����G�̍U�����󂯂�ƃK�\�������[�^�����胁�[�^�[���Ȃ���HP���ւ�Ȃ��Ȃ�ƃQ�[���I�[�o�[
//���ȊO�قڊ���Cscreen�̃N���[�Y���������܂������Ȃ����߳���޳��API�ŏC���\��
//�]�T������Όo�ߎ��Ԃ̏����݂����̓���ă^�C���A�^�b�N�I�Ȃ̂�
//======================================
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include"CScreen.h"
#include"title.h"
#include"gamemain.h"
#include"ending.h"
#include"main.h"
//======================================
//�֐���`
int Gflag=1;
int Mflag=TITLE_INIT;
//======================================


void setMflag(int n)
{

	if(n<TITLE_INIT||n>ENDING_MAIN)
	{
		printf("�G���[\n");
		return;
	}
	Mflag=n;
}

int GetMflag(void)
{
	return Mflag;
}

void main(void)
{
	int starttime;
	int endtime;
	timeBeginPeriod(1);//�E�B���h�E�Y�̎��Ԃ��m��
	starttime=timeGetTime();//�X�^�[�g���Ԃ���
		Title title;
	Gamemain game;
	Ending End;
	while(Gflag)
	{
		endtime=timeGetTime();//�I�����Ԃɑ��
		if((endtime-starttime)>(1000/60))//����Ђ���1000/60�Ȃ�switch�Ɉڍs
		{
			starttime=endtime;//�X�^�[�g�^�C���ɏI�����ԑ��
			GetMflag();
	switch(Mflag)//�X�C�b�`�ŃL�[�̐���
		{
		case TITLE_INIT:
			title.TitleInit();
	break;
		case TITLE_MAIN:
			title.TitleMain();
	break;
		case GAMEMAIN_INIT:
			game.GameInit();
	break;
		case GAMEMAIN_MAIN:
			game.Gmain();
	break;
		case ENDING_INIT:
			End.endinit();
			break;
		case ENDING_MAIN:
			End.endingmain();
			break;
		case END:
			Gflag=0;
			break;

		}//switch
		}//if
		timeEndPeriod(1);//�E�B���h�E�Y���ԏK���̏I������CPU�ɋ󂫂����
	}//while
}//main
