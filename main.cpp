//======================================
//CP-11S-A02 09 鈴木愛忠
//=========================================
//CP11 CP11SA02-09 20029「HEW提出版版」
//
//内容:タイトルはADで移動、扉の前でWキーで開始　それ以外だと終了
//ADで移動WでジャンプSを押すとボスまでスキップ	シフトキーで遠距離攻撃 エンターでタイトルに戻る
//MIDIのハンドルがうまく初期化できないため終了が強制終了になるが修正予定
//攻撃や敵の攻撃を受けるとガソリンメータが減りメーターがないとHPがへりなくなるとゲームオーバー
//音以外ほぼ完成Cscreenのクローズ処理がうまくいかないためｳｨﾝﾄﾞｳｽﾞAPIで修正予定
//余裕があれば経過時間の処理みたいの入れてタイムアタック的なのを
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
//関数定義
int Gflag=1;
int Mflag=TITLE_INIT;
//======================================


void setMflag(int n)
{

	if(n<TITLE_INIT||n>ENDING_MAIN)
	{
		printf("エラー\n");
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
	timeBeginPeriod(1);//ウィンドウズの時間を確保
	starttime=timeGetTime();//スタート時間を代入
		Title title;
	Gamemain game;
	Ending End;
	while(Gflag)
	{
		endtime=timeGetTime();//終了時間に代入
		if((endtime-starttime)>(1000/60))//二つをひいて1000/60ならswitchに移行
		{
			starttime=endtime;//スタートタイムに終了時間代入
			GetMflag();
	switch(Mflag)//スイッチでキーの制御
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
		timeEndPeriod(1);//ウィンドウズ時間習得の終了処理CPUに空きを作る
	}//while
}//main
