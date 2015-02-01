#include<windows.h>
#include"CScreen.h"
#include"Image.h"
#include"base.h"
#include"main.h"
#include"ending.h"

#define Y_MAX 150//地面の上限
#define Disp_max 2000//画面の移動上限
#define Walk_x 10//移動量
#define Max_anim 3//フラグのマックス
#define W_anim 0.4f//フラグの加算
#define START_FLAG 1 //スタートのフラグ
#define One_anim 40	//待機アニメーションの区切り

enum Move_MODES{
	M_Wait,M_Walk
};//モーションのデファイン


Ending::Ending()
{
	this->Player_Wait.anim(2,"DATA/Player/Wait/BMP_DAT_");
	this->Player_Walk.anim(3,"DATA/Player/Walk/BMP_DAT_");
	this->EndBack.anim(3,"DATA/Ending/BMP_DAT_");//エンディング画像用意
	this->Logo.anim(3,"DATA/Menu/Button/BMP_DAT_");
	this->ENDINGBGM=OPENMP3("DATA/BGM/ENDING.mp3");//エンディング

	this->Dbuff.Init(this->EndBack.animation[0]);
}
//エンディング初期化
//========================================================================
int Ending::endinit()
{
		Credit.Input(200,50);//クレジットの座標セット
	Player.Input(0,Y_MAX);//プレイヤーの座標セット
	Player.MFlag=M_Wait;//1なら移動しそれ以外は待機
	Player.DFlag=0.0f;//移動量初期化
	Dispx=0;//画面座標セット
	Car.Input(2000,155);//車の座標セット
	EndFlag=ENDING_MAIN;//エンディングのフラグセット
	Count=0;//カウントセット
	Logoinfo.Input(20,20);//ロゴの位置セット
	this->KEYCHK.KeyInINIT();//キー入力初期化
	PLAYMP3(this->ENDINGBGM,0);
	setMflag(EndFlag);
	return ENDING_MAIN;
}

//エンディングのメイン処理
//==========================================================================
int Ending::endingmain()
{
	this->KEYCHK.KeyInINIT();//キー入力初期化

	this->Dbuff.SetMap(this->EndBack.animation[0]);//背景セット
if(this->Count>=0)//カウントがゼロ以下なら
	{
		this->Count++;//カウントをプラス
	}

	if(this->Count>One_anim*2)//80を超えたら
	{
		this->Count=0;//カウントリセット
	}

if(Dispx>=0&&Dispx<=Disp_max&&Player.MFlag==M_Walk)//画面位置が0から1000までで移動フラグが立っていればなら
	{
		Dispx+=10;//10移動
		Player.MFlag=M_Walk;//移動フラグがたつ
	}

	if(Dispx==0&&Count==One_anim/2)//カウントと場所が０なら
	{
		Player.MFlag=M_Walk;//移動フラグがたつ
	}
if(Dispx==Disp_max&&Player.MFlag==M_Walk)//画面が1000で走っていたら
	{
		Player.MFlag=M_Wait;//戻す
	}
	this->Dbuff.SetBuf(this->Logo.animation[2],this->Logoinfo.x,this->Logoinfo.y,Dispx);
if(Dispx==Disp_max&&Player.MFlag==M_Wait&&Count==One_anim*2)
{
	STOPMP3(this->ENDINGBGM);
	EndFlag=TITLE_INIT;//タイトルへ
}
		if(Car.x>=0)//車の座標がゼロになるまで
		{
			if(Count%2==0)
			{
			this->Dbuff.SetBuf(EndBack.animation[1],Car.x,Car.y,0);//車描画
			}else{
				this->Dbuff.SetBuf(EndBack.animation[1],Car.x,Car.y+1,0);//車描画
			}
			Car.x-=Walk_x*2;
		}
//================================================================================
		switch(this->Player.MFlag)
		{
	case M_Walk://歩きの場合
		
			this->Player.DFlag+=W_anim;//アニメーションフラグ加算
					if(this->Player.DFlag>Max_anim)//アニメーション上限を超えたら
			{
				Player.DFlag=0;
			}//
			Dbuff.SetBuf(this->Player_Walk.animation[(int)this->Player.DFlag],this->Player.x,this->Player.y,Dispx);
			Player.Flag=M_Wait;//0にセット
		break;//=======================================

					//============================待機
	case M_Wait:
						if(this->Count>0&&this->Count<=40)
						{
			Dbuff.SetBuf(this->Player_Wait.animation[0],this->Player.x,this->Player.y,Dispx);
						}else{
			Dbuff.SetBuf(this->Player_Wait.animation[1],this->Player.x,this->Player.y,Dispx);
						}

		}//switch

		this->KEYCHK.KeySet();
			if(this->KEYCHK.KEY_ENTER!=0x00)
			{
				STOPMP3(this->ENDINGBGM);
				EndFlag=TITLE_INIT;//エンターでスキップ
			}

//===============================================================================================================
		this->Dbuff.SetBuf(EndBack.animation[2],Credit.x,Credit.y,Dispx);//メッセージ表示
		this->Dbuff.DrawBuf(this->EndBack.animation[0],Dispx);//全部描画
	setMflag(EndFlag);//流れをセット
	return ENDING_MAIN;
}

//======================================================================================
//エンディング初期化
void Ending::endingDel()
{
	this->Player_Wait.Del();
	this->Player_Walk.Del();
	this->EndBack.Del();//エンディング画像用意
	this->Logo.Del();
	CLOSEMIDI(this->ENDINGBGM);//エンディング
}
