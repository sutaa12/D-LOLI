#include<windows.h>
#include"CScreen.h"
#include"Image.h"
#include"title.h"
#include"hitchk.h"
#include"main.h"


#define Y_MAX 150//地面の上限
#define Draw_max 800//画面の移動上限
#define Draw_min 0//マップの最少
#define Walk_x 15//移動量
#define Max_anim 3//フラグのマックス
#define W_anim 0.4f//フラグの加算
#define START_FLAG 1 //スタートのフラグ
#define One_anim 40	//待機アニメーションの区切り

enum Move_MODES{
	M_Wait,M_Walk
};//モーションのデファイン
Title::Title()
{
	this->MenuBack.FileRead("DATA/Menu/Back/BMP_DAT_",1);
		this->Player_Wait.anim(2,"DATA/Player/Wait/BMP_DAT_");
	this->Player_Walk.anim(3,"DATA/Player/Walk/BMP_DAT_");
		this->MenuButton.anim(3,"DATA/Menu/Button/BMP_DAT_");
		this->TITLEBGM=OPENWAVE("DATA/BGM/Title.wav");//タイトル音
		this->DOORSE=OPENWAVE("DATA/SE/Door.wav");

	MenuBack.ImageFileRead();//パレット情報ごと初期化
	MenuBack.ChangePalette();
	MenuBack.SetConsolePalatte();
		MenuBack.ChangeImageSize();
	MenuBack.SetWindowSize2(1000,1,1);
	MenuBack.ChangeImage();
	this->Dbuff.Init(this->MenuBack);
	this->Start.Input(0,0);
	this->Start.Flag=0;
	this->Door.HchkInit(Player_Wait.animation[0],MenuButton.animation[0]);
}

int Title::TitleInit()
{
	this->KEYCHK.KeyInINIT();//キー入力初期化
	this->Player.x=0;		//スタート位置
	this->Player.y=Y_MAX;	//プレイヤー座標
	this->Player.POSFlag=0;//向きの初期化
	this->Player.Flag=0;//動作フラグ初期化
	this->Player.MFlag=0;//歩き以外の動作の初期化
	this->Start.Flag=0;//１の場合スタート
	this->Dbuff.SetMap(this->MenuBack);
	this->Start.Input(800,100);
	Logo.Input(20,20);//ロゴの位置セット
	this->Dbuff.SetBuf(this->MenuButton.animation[2],this->Logo.x,this->Logo.y,0);
	this->Dbuff.SetBuf(this->MenuButton.animation[0],this->Start.x,this->Start.y,0);
	this->Dbuff.SetBuf(this->Player_Wait.animation[0],this->Player.x,this->Player.y,0);
	this->Dbuff.DrawBuf(this->MenuBack,0);
	this->Count=0;
	this->TitleFlag=TITLE_MAIN;
	PLAYWAVE(this->TITLEBGM,1);//初期再生
	setMflag( TitleFlag);
	return TITLE_MAIN;//次につなげる
}

int Title::TitleMain()
{

	this->KEYCHK.KeyInINIT();//キー入力初期化
		if(Start.Flag==-1)
	{
		if(this->Count>=0)//0より上なら
		{
			if(this->Count==20)
			{
				STOPWAVE(this->TITLEBGM);
				this->TitleFlag= GAMEMAIN_INIT;
			}else{
			if(this->Count>=10)
			{
				this->Dbuff.SetMapB(this->MenuBack);
			}else{
				this->Dbuff.SetMapBHX(this->MenuBack);
			}
			}
		}
					this->Count++;
	}else{
	this->Dbuff.SetMap(this->MenuBack);
	this->Dbuff.SetBuf(this->MenuButton.animation[2],this->Logo.x,this->Logo.y,0);
//==========カウントの制御
	if(this->Count>=0)//カウントがゼロ以下なら
	{
		this->Count++;//カウントをプラス
	}
	if(this->Count>One_anim*2)//80を超えたら
	{
		this->Count=0;//カウントリセット
	}
//========================================
	//========================================
	//当たり判定

	Start.Flag=Door.Hitcheck(Player.x,0,Player.y,Start.x,Start.y);//フラグが０じゃなかったら立つ
	if(Start.Flag!=0)
	{
		Start.Flag=START_FLAG;
		this->Dbuff.SetBuf(this->MenuButton.animation[1],this->Start.x,this->Start.y,0);
	}else{
		this->Dbuff.SetBuf(this->MenuButton.animation[0],this->Start.x,this->Start.y,0);
	}
	//===================================
//===================動作フラグチェック=================
	switch(this->Player.Flag)
	{
	case M_Walk://歩きの場合
					this->Player.DFlag+=W_anim;//アニメーションフラグ加算
			if(this->Player.DFlag>Max_anim)//アニメーション上限を超えたら
			{
				Player.DFlag=0;
			}//
		if(this->Player.POSFlag!=0)//右向きでなかったら(左向き)
		{
						this->Player.x-=Walk_x;//5戻る


			if(Player.x<Draw_min)
			{
				Player.x+=Walk_x;//マップ端で戻る処理
			}
			Dbuff.SetBufM(this->Player_Walk.animation[(int)this->Player.DFlag],this->Player.x,this->Player.y,0);
			Player.Flag=M_Wait;//0にセット
		}else{//(右向き)
						this->Player.x+=Walk_x;//5進む

			if(Player.x>Draw_max)//マップの端の場合戻る
			{
				Player.x-=Walk_x;
			}
			Dbuff.SetBuf(this->Player_Walk.animation[(int)this->Player.DFlag],this->Player.x,this->Player.y,0);
			Player.Flag=M_Wait;//0にセット
		}//
		break;//=======================================

					//============================待機
	case M_Wait:
		if(this->Player.POSFlag!=0)//左向きの場合
		{
			if(this->Count>0&&this->Count<=40)
			{
			Dbuff.SetBufM(this->Player_Wait.animation[0],this->Player.x,this->Player.y,0);
			}else{
			Dbuff.SetBufM(this->Player_Wait.animation[1],this->Player.x,this->Player.y,0);
			}
		}else{
						if(this->Count>0&&this->Count<=40)
						{
			Dbuff.SetBuf(this->Player_Wait.animation[0],this->Player.x,this->Player.y,0);
						}else{
			Dbuff.SetBuf(this->Player_Wait.animation[1],this->Player.x,this->Player.y,0);
						}
		}//else
	}//switch
//=========================================

		//=====================キー入力制御
	this->KEYCHK.KeySet();
			if(this->KEYCHK.KEY_END!=0x00)
		{
			TitleFlag=END;
		}else{
	if(this->KEYCHK.KEY_SHIFT!=0x00)
	{
	}else{
	if(Player.Flag==0)
	{
		if(this->KEYCHK.KEY_ENTER!=0x00||this->KEYCHK.KEY_W)
		{
			if(this->Start.Flag==START_FLAG)
			{
				PLAYWAVE(this->DOORSE,0);
				this->Count=0;//カウント初期化
				this->Start.Flag=-1;
			}else{
			}

		}else{
	if(this->KEYCHK.KEY_A!=0x00)
	{
		this->Player.Flag=M_Walk;//歩くフラグ
		this->Player.POSFlag=1;//左向き
	}else{
	if(this->KEYCHK.KEY_D!=0x00)
	{
		this->Player.Flag=M_Walk;//歩くフラグ
		this->Player.POSFlag=0;//右向き
	}else{//

		this->Player.Flag=M_Wait;
	}
	}
	}
		}
	}
	}
	}//-1か
//======================================

	this->Dbuff.DrawBuf(this->MenuBack,0);
setMflag( TitleFlag);//ゲームフラグセット
return TITLE_MAIN;
}

//===============================================================
//タイトル削除

void Title::titleDel()
{
		this->Player_Wait.Del();
		this->Player_Walk.Del();
		this->MenuButton.Del();
		CLOSEWAVE(this->TITLEBGM);//ボス
		CLOSEWAVE(this->DOORSE);
}