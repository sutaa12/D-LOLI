#include"CScreen.h"
#include<stdio.h>
#include "Image.h"

void kind::anim(int i,char *FName)//�摜���A�j���[�V�������ƂɊi�[
{
	animation=new ImageFile[i];
	for(int j=0;j<i;j++)
	{
		animation[j].FileRead(FName,j);
		animation[j].ImageFileRead();
		animation[j].ChangeImageSize();
		animation[j].ChangeImage();
	}
}
void kind::Del()
{
	delete []animation;
}