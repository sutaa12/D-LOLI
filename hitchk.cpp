#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cscreen.h"
#include "Image.h"
#include "hitchk.h"

void Hchk::HchkInit(ImageFile Player,ImageFile Onemy)//�����蔻��̏�����
{
	this->Pwidth=Player.screenSizeX;//�v���C���[���W
	this->Pheight=Player.screenSizeY;
	this->Owidth=Onemy.screenSizeX;//������W
	this->Oheight=Onemy.screenSizeY;
}



int Hchk::Hitcheck(int px,int plx,int py,int ox,int oy)//�G�ƃv���C���[�̓����蔻��
{
	if(px+plx+Pwidth-10>=ox&&py+Pheight>=oy&&ox+Owidth>=px+plx+10&&oy+Oheight>=py)//�l�p�̓����蔻��
	{

		if((py>=oy)||(py+Pheight<=oy+40&&px+plx+Pwidth<=ox+50)||(py+Pheight<=oy+40&&px+plx>=ox+Owidth-50))//�G�̂���̂Ƃ�
		{
			return -2;
		}
	if(py+Pheight<=oy+35)//�G�̂����̂Ƃ�
	{
		return 2;
	}
	if(px+plx>=ox)//�G�̂����̂Ƃ�
		{
		return -1;
		}
		if(px+plx<ox)//�G�̂��O�̂Ƃ�
		{
			return 1;

		}//if

	}//if
return 0;
}

int Hchk::HitcheckO(int px,int plx,int py,int ox,int oy)//����̓����蔻��
{

	if(px+plx+Pwidth-70>=ox&&py+Pheight>=oy&&py+Pheight<oy+10&&ox+Owidth>=px+plx+80)//����Ɠ������W���`�F�b�N�@y���W�̓v���C���[��ӂƑ���̍����ꏏ��x��������Ȃ��d�Ȃ��
	{
			return 1;//1��Ԃ�
	}
return 0;
}


int Hchk::HitcheckEB(int px,int plx,int py,int ox,int oy)//�G�̒e�ƃv���C���[�̓����蔻��
{
	if(px+plx+Pwidth-70>=ox&&py+Pheight-10>=oy&&ox+Owidth>=px+plx+70&&oy+Oheight>=py)//�l�p�̓����蔻��
	{
						if((py+(Pheight/2)>=oy))//�G�̂�������̂Ƃ�
		{
			return -2;
		}
	if(px+plx>=ox)//�G�̂����̂Ƃ�
		{
		return -1;
		}
		if(px+plx<ox)//�G�̂��O�̂Ƃ�
		{
			return 1;

		}//if

	}//if
return 0;
}