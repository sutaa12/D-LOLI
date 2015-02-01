#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cscreen.h"
#include "Image.h"
#include "hitchk.h"

void Hchk::HchkInit(ImageFile Player,ImageFile Onemy)//あたり判定の初期化
{
	this->Pwidth=Player.screenSizeX;//プレイヤー座標
	this->Pheight=Player.screenSizeY;
	this->Owidth=Onemy.screenSizeX;//相手座標
	this->Oheight=Onemy.screenSizeY;
}



int Hchk::Hitcheck(int px,int plx,int py,int ox,int oy)//敵とプレイヤーの当たり判定
{
	if(px+plx+Pwidth-10>=ox&&py+Pheight>=oy&&ox+Owidth>=px+plx+10&&oy+Oheight>=py)//四角の当たり判定
	{

		if((py>=oy)||(py+Pheight<=oy+40&&px+plx+Pwidth<=ox+50)||(py+Pheight<=oy+40&&px+plx>=ox+Owidth-50))//敵のが上のとき
		{
			return -2;
		}
	if(py+Pheight<=oy+35)//敵のが下のとき
	{
		return 2;
	}
	if(px+plx>=ox)//敵のが後ろのとき
		{
		return -1;
		}
		if(px+plx<ox)//敵のが前のとき
		{
			return 1;

		}//if

	}//if
return 0;
}

int Hchk::HitcheckO(int px,int plx,int py,int ox,int oy)//足場の当たり判定
{

	if(px+plx+Pwidth-70>=ox&&py+Pheight>=oy&&py+Pheight<oy+10&&ox+Owidth>=px+plx+80)//足場と同じ座標かチェック　y座標はプレイヤー底辺と足場の高さ一緒でx軸が足場ない重なれば
	{
			return 1;//1を返す
	}
return 0;
}


int Hchk::HitcheckEB(int px,int plx,int py,int ox,int oy)//敵の弾とプレイヤーの当たり判定
{
	if(px+plx+Pwidth-70>=ox&&py+Pheight-10>=oy&&ox+Owidth>=px+plx+70&&oy+Oheight>=py)//四角の当たり判定
	{
						if((py+(Pheight/2)>=oy))//敵のが頭より上のとき
		{
			return -2;
		}
	if(px+plx>=ox)//敵のが後ろのとき
		{
		return -1;
		}
		if(px+plx<ox)//敵のが前のとき
		{
			return 1;

		}//if

	}//if
return 0;
}