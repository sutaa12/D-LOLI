#include<windows.h>
#include"CScreen.h"
#include"Image.h"
#include"base.h"
#include"main.h"
#include"gamemain.h"

Gamemain::Gamemain()//コンストラクタ
{
	//画像用意
	this->Plate.anim(4,"DATA/Plate/BMP_DAT_");
	this->Background.anim(1,"DATA/Back/BMP_DAT_");
	this->Player_Wait.anim(2,"DATA/Player/Wait/BMP_DAT_");
	this->Player_Walk.anim(3,"DATA/Player/Walk/BMP_DAT_");
	this->Player_Jump.anim(4,"DATA/Player/Jump/BMP_DAT_");
	this->Player_Shot.anim(2,"DATA/Player/Shot/BMP_DAT_");
	this->Player_Bullet.anim(2,"DATA/Player/Bullet/BMP_DAT_");
	this->Player_Attack.anim(3,"DATA/Player/Attack/BMP_DAT_");
	this->Player_GASbar.anim(2,"DATA/Player/GASbar/BMP_DAT_");
	this->Player_GAMEOVER.anim(5,"DATA/Player/GameOver/BMP_DAT_");
	this->Player_HP.anim(2,"DATA/Player/HP/BMP_DAT_");
	this->Enemy_Wait.anim(2,"DATA/Enemy/Wait/BMP_DAT_");
	this->Enemy_Shoot.anim(2,"DATA/Enemy/Shoot/BMP_DAT_");
	this->Enemy_Bullet.anim(2,"DATA/Enemy/Bullet/BMP_DAT_");
	this->Enemy_Dead.anim(5,"DATA/Enemy/Dead/BMP_DAT_");
	
	this->Item.anim(2,"DATA/Item/BMP_DAT_");
	
	this->BossG.anim(1,"DATA/Boss/Head/BMP_DAT_");
	this->BossM.anim(4,"DATA/Boss/Head/MOUTH/BMP_DAT_");
	this->BossN.anim(4,"DATA/Boss/Head/NORSE/BMP_DAT_");
	this->BossE.anim(4,"DATA/Boss/Head/EYE/BMP_DAT_");
	this->BossBu.anim(1,"DATA/Boss/BossBullet/BMP_DAT_");
	this->BossRa.anim(1,"DATA/Boss/BossRaser/BMP_DAT_");
	this->Explasive.anim(7,"DATA/Boss/Explosion/BMP_DAT_");

	this->Message_Window.anim(3,"DATA/Message/BMP_DAT_");

	this->MIDIMAINBGM=OPENMIDI("DATA/BGM/Main.mid");//音楽を開く
	this->MIDIGAMEOVERBGM=OPENMIDI("DATA/BGM/GameOver.mid");//ゲームオーバー
	this->MIDIBOSSBGM=OPENMIDI("DATA/BGM/Boss.mid");//ボス
	
	this->AttackSE=OPENWAVE("DATA/SE/Attack.wav");//攻撃音
	this->ShootSE=OPENWAVE("DATA/SE/Pshoot.wav");//発射音
	this->PDameSE=OPENWAVE("DATA/SE/PlayerD.wav");//発射音
	this->EnemyDeSE=OPENWAVE("DATA/SE/Tekisi.wav");//敵の脂肪音
	this->BossShootSE=OPENWAVE("DATA/SE/Bshoot.wav");//ボスの発射音
	this->BossRaserSE=OPENWAVE("DATA/SE/Braser.wav");
	this->BossDeSE=OPENWAVE("DATA/SE/BossDame.wav");//敵の脂肪音
	this->BossDeTSE=OPENWAVE("DATA/SE/BossDeath.wav");//敵の脂肪音
	this->EnemyDame=OPENWAVE("DATA/SE/EnemyD.wav");//敵の脂肪音
	this->BossLSE=OPENWAVE("DATA/SE/BossF.wav");//敵の脂肪音
	this->ItemSE=OPENWAVE("DATA/SE/ItemSE.wav");//敵の脂肪音



	this->Dbuff.Init(this->Background.animation[0]);
	
	this->Platechk.HchkInit(Player_Jump.animation[0],Plate.animation[0]);//大きい足場チェック用意
	
	this->PlateSMALL=new Base[Base_S];//足場の数分変数用意
	this->PlateHIGH=new Base[Base_H];//足場の数分変数用意
	this->PlateLARGE=new Base[Base_L];//足場の数分変数用意


	this->Itemx=new Base[ITEM_MAX];//アイテムの数分変数用意
	
	this->Enemy=new Base[EnemyMAX];//敵の座標用意
	this->EnemyS=new Base[EnemyShootMAX];//敵の座標用意
	this->Ebullet=new Base[EnemyShootMAX*2];//敵の数の2倍の弾用意
	this->Enemychk.HchkInit(Player_Wait.animation[0],Enemy_Wait.animation[0]);//敵とのあたり判定用意
	this->Bakuha=new Base[JakutenMAX];//弱点分爆発用意
}

int Gamemain::GameInit()//ゲームの初期型
{
	//キー情報初期化
	this->KEYCHK.KeyInINIT();
	//ゲームの情報変更
	this->GameFlag=GAMEMAIN_MAIN;
//位置情報
	this->Dispx=0;			//画面の表示位置
	this->Count=20;
	this->Gravity=6;//重力初期化

	//プレイヤー情報
	this->Player.x=0;		//
	this->Player.y=Y_MAX;	//プレイヤー座標
	this->Player.POSFlag=0;//向きの初期化
	this->Player.Flag=0;//動作フラグ初期化
	this->Player.MFlag=0;//歩き以外の動作の初期化
	this->Player.DFlag=0.0f;//歩きフラグ初期化
	this->Player.LifeFlag=STARTLIFE;//ライフ初期化
	this->Gas=STARTG;//ガソリン量
	this->AttackF=0;//1の場合攻撃
	this->Damage=0;//ダメージ量
	this->EHIT=0;//ヒット初期化

	//プレイヤー弾の情報初期化
	this->Pbullet.Flag=0;//弾が発射されているか
	Pbullet.POSFlag=0;//弾の判定
	this->Pbullet.MFlag=0;//弾の動き
	this->Pbullet.x=0;
	this->Pbullet.y=0;

	this->SetEnemy();//敵の配置初期化
	this->SetPlate();//足場の初期配置
	this->SetItem();//アイテムの初期配置

	//メッセージ表示初期化
	this->Message.Flag=1;
	this->Message.MFlag=0;//メッセージのアニメーション初期化
	this->Message.Input(300,50);//メッセージ表示座標

	//ゲームオーバーの初期化
	this->GAMEOVER.Flag=0;//ゲームオーバーの描画フラグの初期化
	this->GAMEOVER.MFlag=0;//ゲームオーバーの操作の初期化
	this->GAMEOVER.Input(400,50);//位置の初期化

	//ボスモードの初期化
	this->Boss.Flag=0;//モードチェック
	this->Boss.MFlag=0;//ボスのアニメーション
	this->Boss.LifeFlag=3;//ボスのHP
	this->BossBullet.Input(0,0);//ボスの弾座標
	this->BossBullet.LifeFlag=0;//ボスの弾ライフ
	this->Jakuten.Input(7795,240);//弱点の配置の場合
	this->Jakuten.Flag=0;
	this->Boss.Input(7799,20);//ボス位置
	this->Info.Input(7650,240);//矢印表示
	this->BossR.Input(0,0);//レーザー情報初期化
	this->BossR.LifeFlag=0;
	this->Boss.POSFlag=0;//シーン切り替えフラグ

	for(int i=0;i<JakutenMAX;i++)
	{
	this->Bakuha[i].Flag=0;//1なら爆発
	this->Bakuha[i].MFlag=0;//煙のタイミング
	this->Bakuha[i].LifeFlag=0;//爆破の時間
	this->Bakuha[i].Input(0,0);//位置
	}

	//音楽初期化
	PLAYMIDI(this->MIDIMAINBGM,1);

//初期描画
		this->Dbuff.SetMapB(this->Background.animation[0]);
	setMflag( GameFlag);//ゲームフラグセット
	return GAMEMAIN_MAIN;
}
//==========================================================================================================================================
int Gamemain::Gmain()//ゲームメイン
{
//==========================描画位置決定
	this->ChengeDisp();
//========================================

	//=====================================================================
	//足場チェック
PlateCHECK();

//=========================================
//アイテム描画
	this->DItem();

//=================================================
		//ボスフラグチェック
	//===================================================================
	if(Dispx>=Draw_max-300&&Boss.Flag==0)
	{
		Message.Flag=1;//メッセージフラグON
		Boss.Flag=1;//フラグ立つ
		Enemy[0].LifeFlag=0;//ボス用に敵を確保
		Player.x=10;//座標ずらす

		STOPMIDI(this->MIDIMAINBGM);
		PLAYWAVE(this->BossLSE,0);//ボス笑い声
		PLAYMIDI(this->MIDIBOSSBGM,1);//ボスBGM
	}
	if(this->Boss.Flag==1)//フラグが1なら
	{
	this->BossMODE();//ボス処理
	}
//==========カウントの制御
	this->CountCheck();

//===========================================
	//ゲームオーバーチェック
	if(GAMEOVER.Flag!=0)
	{
		this->GameOver();//ゲームオーバー処理
	}else{
//============敵の表示
	this->EnemyD();
	this->EnemySD();
//=============================================
		//==========敵の弾処理
	this->EbulletCheck();
//=====================================================

//===================動作フラグチェック=================
	this->MFlagCheck();
//=========================================
	//============================================
	//初期メッセージ表示
	if(Message.Flag!=0)
	{
		this->SetMessage();
	}else{
	//=====================================================
	//=====================キー入力制御
	this->KeyCheck();
//===========================================================================
	//弾が発射されているかチェック===================================
	this->PbulletCheck();
	//====================================================================
	//バー表示
	this->HPstate();
	//==ゲームオーバーでない場合
	}
		}
	//ジャンプの重力制御=================================
	this->GravityP();
//=========================================

this->KEYCHK.KeyInINIT();//キー情報初期化

	//===========================================
	//描画処理
	this->Dbuff.DrawBuf(this->Background.animation[0],this->Dispx);
	if(GameFlag!=GAMEMAIN_MAIN)//ゲームメイン以外なら何がなんでも音を止める
	{
		this->StopMUSIC();
	}
setMflag( GameFlag);
	return GAMEMAIN_MAIN;
}


//=====================================================================================================================================================
//関数


//===============================================
//描画位置変更
void Gamemain::ChengeDisp()
{
	if(this->Player.x>Disp_max&&this->Dispx<Draw_max&&this->Boss.Flag==0)//歩いた距離が画面→端に行ったら
	{
		Dispx+=Walk_x;//背景が動く
	if(this->Player.x>Disp_max)
	{
		this->Player.x-=Walk_x;//座標が戻る
	}
	}else{
		if(this->Player.x<Disp_min&&this->Dispx>Draw_min&&this->Boss.Flag==0)//歩いた距離が一番←端
		{
			Dispx-=Walk_x;//戻る
			if(this->Player.x<Disp_min)
			{
				this->Player.x+=Walk_x;//プレイヤの座標を戻す
			}
		}else{
		}
	}
	this->Dbuff.SetMap(this->Background.animation[0]);
}

//================================
//アイテム描画
void Gamemain::DItem()
{
	for(int i=0;i<ITEM_MAX;i++)//アイテム数チェック
	{
				if(this->Itemx[i].Flag!=0)//アイテムフラグが０でない場合
		{
		this->Enemychk.HchkInit(this->Player_Wait.animation[0],this->Item.animation[0]);
		this->EHIT=this->Enemychk.HitcheckEB(Player.x,Dispx,Player.y,Itemx[i].x,Itemx[i].y);//当たっているかチェック
		if(EHIT!=0&&EHIT!=-2)//当たっていたら
		{
			if(Gas<12)//ガソが１２より下だったら
			{
				PLAYWAVE(this->ItemSE,0);//ボス笑い声
			this->Gas+=6;//ガソ回復
			this->Itemx[i].Flag=0;//フラグ０にする
			this->Itemx[i].LifeFlag=3;//アイテムが消える処理
			}

		}

		if(this->Count>0&&this->Count<=20||this->Count>40&&this->Count<=60)
		{
			this->Dbuff.SetBuf(this->Item.animation[0],0,Itemx[i].y,Itemx[i].x);
		}else{
		this->Dbuff.SetBuf(this->Item.animation[1],0,Itemx[i].y,Itemx[i].x);
		}
		}
				if(this->Itemx[i].LifeFlag!=0&&this->Itemx[i].LifeFlag<=10)//ライフラグが立ったら
				{
				this->Dbuff.SetBufD(this->Item.animation[1],0,Itemx[i].y,Itemx[i].x);
				Itemx[i].LifeFlag--;//ライフフラグ0
				}
	}
}

//===============================================
//カウントチェック
void Gamemain::CountCheck()
{
		if(this->Count>=0)//カウントがゼロ以下なら
	{
		this->Count++;//カウントをプラス
	}
	if(this->Count>One_anim*2)//80を超えたら
	{
		this->Count=0;//カウントリセット
	}
}

//============================================

//キーフラグチェック

void Gamemain::KeyCheck()
{
	this->KEYCHK.KeySet();//キー入力待ち
	if(this->KEYCHK.KEY_END!=0x00)
	{
		STOPMIDI(this->MIDIBOSSBGM);
		STOPMIDI(this->MIDIMAINBGM);
		STOPMIDI(this->MIDIGAMEOVERBGM);
		this->GameFlag=TITLE_INIT;//ESCでタイトルへ
	}else{
		if(Player.Flag==0)
	{
				//if(this->KEYCHK.KEY_S!=0x00)
				//{
				//	//Dispx=Draw_max-280;//描画位置強制変更
				//}else{
		if(this->KEYCHK.KEY_ENTER!=0x00)//エンター
		{
		}else{
	if(this->KEYCHK.KEY_W!=0x00)//ジャンプ
	{
		this->Player.Flag=M_Jump;//ジャンプフラグ
	}else{
		if(this->KEYCHK.KEY_SP!=0x00)//攻撃
		{
			this->Player.Flag=M_Attack;//アタックフラグ
		}else{
			if(this->KEYCHK.KEY_SHIFT!=0x00&&this->Gas!=0)//弾発射//ガスは０位外
		{
			if(Pbullet.Flag==0&&Pbullet.MFlag==0)//弾のフラグがゼロかチェック
			{
			this->Player.Flag=M_Shoot;
			}
		}else{
	if(this->KEYCHK.KEY_A!=0x00)//Aを押していたら
	{
		this->Player.Flag=M_Walk;//歩くフラグ
		this->Player.POSFlag=1;//左向き
	}else{

	if(this->KEYCHK.KEY_D!=0x00)//Dを押していたら
	{
		this->Player.Flag=M_Walk;//歩くフラグ
		this->Player.POSFlag=0;//右向き
	}else{//
		this->Player.Flag=M_Wait;
	}
	}
	}
		}//SP
	}//W
		}
		}
	//}
	}//ESC以外
}
//=========================================================
//弾の進行とチェック
void Gamemain::PbulletCheck()
{
		if(Pbullet.Flag!=0)
	{
		if(Pbullet.Flag==1)//発射されていたら
		{
			Pbullet.Input((Player.x+Dispx+80),Player.y+80);
			Dbuff.SetBuf(Player_Bullet.animation[0],Pbullet.x,Pbullet.y,0);
			Pbullet.POSFlag=1;//弾の判定ON
			Pbullet.Flag++;
		}
				if(Pbullet.Flag==One_anim-10)
		{
			Pbullet.Flag=0;//フラグリセット
			Pbullet.POSFlag=0;//弾の判定OFF
				}else{
		if(Pbullet.Flag>1)
		{
			Pbullet.x+=20;//弾の進行
			Pbullet.Flag++;
			if(Count%2==0)//カウントで表示変更
			{
				Dbuff.SetBuf(Player_Bullet.animation[0],Pbullet.x,Pbullet.y,0);
			}else{
				Dbuff.SetBuf(Player_Bullet.animation[1],Pbullet.x,Pbullet.y,0);
			}
		}else{
		}
				}
	}
		if(Pbullet.MFlag!=0)
	{
		if(Pbullet.MFlag==1)//発射されていたら(左側)
		{
			Pbullet.Input((Player.x+Dispx+10),Player.y+80);
			Dbuff.SetBufM(Player_Bullet.animation[0],Pbullet.x,Pbullet.y,0);
			Pbullet.MFlag++;
			Pbullet.POSFlag=1;//弾の判定ON
		}
				if(Pbullet.MFlag==One_anim-10)
		{
			Pbullet.MFlag=0;//フラグリセット
			Pbullet.POSFlag=0;//弾の判定OFF
				}else{
		if(Pbullet.MFlag>1)
		{
			Pbullet.x-=20;//弾の進行
			Pbullet.MFlag++;
			if(Count%2==0)//カウントで表示変更
			{
				Dbuff.SetBufM(Player_Bullet.animation[1],Pbullet.x,Pbullet.y,0);
			}else{
				Dbuff.SetBufM(Player_Bullet.animation[0],Pbullet.x,Pbullet.y,0);
			}
		}else{
		}
				}
	}
}
//==================================================================
//敵の処理
void Gamemain::EnemyD()
{
		//敵とのあたり判定チェック
	for(int i=0;i<EnemyMAX;i++)
	{
		if(Enemy[i].LifeFlag!=0&&Enemy[i].LifeFlag!=-1)//フラグが0でなければ
			{
	this->Enemychk.HchkInit(Player_Wait.animation[0],Enemy_Wait.animation[0]);//敵とのあたり判定用意
	this->EHIT=this->Enemychk.Hitcheck(Player.x,Dispx,Player.y,Enemy[i].x,Enemy[i].y);//当たっているかチェック
	if(EHIT!=0&&EHIT!=-2)//あたりが0以外の場合
	{
		if(this->AttackF==1)//攻撃フラグがたっているとき
		{
			if(this->Player.POSFlag!=0)//左向きの場合
			{
				if(EHIT==-1)//マイナス１の場合
				{
		Enemy[i].LifeFlag=0;//フラグ0に
							PLAYWAVE(EnemyDame,0);
							PLAYWAVE(EnemyDeSE,0);
		Enemy[i].MFlag=1;//死亡フラグオン
		Player.x+=Walk_x*2;//戻る
		this->GASMOVEchk();//減少処理
				}else{
		this->AttackF=0;//攻撃フラグ0
		this->Player.Flag=M_LIFEM;//HP減少処理
		this->Player.MFlag=0;//動きのフラグ初期化
				}
			}else{//右向きの場合
				if(EHIT==1)
				{
							Enemy[i].LifeFlag=0;//フラグ0に
							PLAYWAVE(EnemyDame,0);
							PLAYWAVE(EnemyDeSE,0);
							Enemy[i].MFlag=1;//死亡フラグオン
							Player.x-=Walk_x*2;//戻る
							this->GASMOVEchk();//減少処理
				}else{
		this->AttackF=0;
		if(this->Player.Flag!=M_LIFEM)//減少処理が入ってない場合
		{
			PLAYWAVE(PDameSE,0);
			this->Damage=Enemy_Damage;//-2ダメージ
		}
		this->Player.Flag=M_LIFEM;//HP減少処理
		this->Player.MFlag=0;//動きのフラグ初期化
				}
			}//else
		}else{//攻撃フラグたってないとき
			if(EHIT==2)//敵より上のとき
			{
							Enemy[i].LifeFlag=0;//フラグ0に
							Enemy[i].MFlag=1;//死亡フラグオン
							PLAYWAVE(EnemyDame,0);
							PLAYWAVE(EnemyDeSE,0);
			}else{
					if(this->Player.POSFlag==1&&EHIT==1)//左向きの場合かつ判定が反対からの場合
			{
				Player.POSFlag=0;//右向きに
			}
		if(this->Player.POSFlag==0&&EHIT==-1)//右向きの場合かつ判定が反対からの場合
			{
				Player.POSFlag=1;//左向きに
			}
				if(this->Player.Flag!=M_LIFEM)//減少処理が入ってない場合
		{
			PLAYWAVE(PDameSE,0);
			this->Damage=Enemy_Damage;//-2ダメージ
		}
		this->Player.Flag=M_LIFEM;//HP減少処理
		this->Player.MFlag=0;//動きのフラグ初期化
			}
		}//
	}//EHIT
	if(this->Pbullet.POSFlag!=0)//弾発射フラグフラグがたっているとき
	{
		this->Enemychk.HchkInit(Player_Bullet.animation[0],Enemy_Wait.animation[0]);//敵とのあたり判定用意
	this->EHIT=this->Enemychk.Hitcheck(Pbullet.x-40,0,Pbullet.y,Enemy[i].x,Enemy[i].y);//当たっているかチェック
		if(EHIT!=0)//あたりが0以外の場合
		{

				Pbullet.MFlag=0;//弾フラグOFF
				Pbullet.Flag=0;
				Pbullet.POSFlag=0;//死亡フラグOFF
		Enemy[i].LifeFlag=0;//フラグ0に
		PLAYWAVE(EnemyDame,0);
								PLAYWAVE(EnemyDeSE,0);
		Enemy[i].MFlag=1;//死亡フラグオン
		}
	}
			}
	//============================================
	//敵の脂肪アニメーション
	if(Enemy[i].MFlag!=0)//敵のフラグが入っていたら
	{
		if(Enemy[i].MFlag==9)
		{
			Enemy[i].MFlag=0;//フラグ0に
		}else{
		if(Enemy[i].MFlag>0)//フラグが0以上
		{
			this->Dbuff.SetBuf(this->Enemy_Dead.animation[Enemy[i].MFlag/2],Enemy[i].x,Enemy[i].y,0);
			Enemy[i].MFlag++;
						if(Enemy[i].MFlag%2==0)
			{
				this->Dbuff.SetBufED(this->Enemy_Dead.animation[Enemy[i].MFlag/2],Enemy[i].x,Enemy[i].y,0);//脂肪画面表示
			}
		}
		}
	}
//================================================
	//敵の配置
	if(this->Enemy[i].LifeFlag!=0&&Enemy[i].LifeFlag!=-1)//フラグがたっていたら
	{
		if(this->Count<=One_anim)
					{
		this->Dbuff.SetBuf(this->Enemy_Wait.animation[0],Enemy[i].x,Enemy[i].y,0);
					}
										if(this->Count>One_anim)
					{
		this->Dbuff.SetBuf(this->Enemy_Wait.animation[1],Enemy[i].x,Enemy[i].y,0);
					}

	}
}
}


//==================================================================
//弾を撃つ敵の処理
void Gamemain::EnemySD()
{
		//敵とのあたり判定チェック
	for(int i=0;i<EnemyShootMAX;i++)
	{
			if(EnemyS[i].LifeFlag!=0)//フラグが0でなければ
			{
	this->Enemychk.HchkInit(Player_Wait.animation[0],Enemy_Wait.animation[0]);//敵とのあたり判定用意
	this->EHIT=this->Enemychk.Hitcheck(Player.x,Dispx,Player.y,EnemyS[i].x,EnemyS[i].y);//当たっているかチェック
	if(EHIT!=0&&EHIT!=-2)//あたりが0以外の場合
	{
		if(this->AttackF==1)//攻撃フラグがたっているとき
		{
			if(this->Player.POSFlag!=0)//左向きの場合
			{
				if(EHIT==-1)//マイナス１の場合
				{
		EnemyS[i].LifeFlag=0;//フラグ0に
		EnemyS[i].MFlag=1;//死亡フラグオン
		PLAYWAVE(EnemyDame,0);
		PLAYWAVE(EnemyDeSE,0);
		Player.x+=Walk_x*2;//戻る
		this->GASMOVEchk();//減少処理
				}else{
		this->AttackF=0;//攻撃フラグ0
		this->Player.Flag=M_LIFEM;//HP減少処理
		this->Player.MFlag=0;//動きのフラグ初期化
				}
			}else{//右向きの場合
				if(EHIT==1)
				{
							EnemyS[i].LifeFlag=0;//フラグ0に
							EnemyS[i].MFlag=1;//死亡フラグオン
							PLAYWAVE(EnemyDame,0);
							PLAYWAVE(EnemyDeSE,0);
							Player.x-=Walk_x*2;//戻る
							this->GASMOVEchk();//減少処理
				}else{
		this->AttackF=0;//攻撃フラグ初期化
						if(this->Player.Flag!=M_LIFEM)//減少処理が入ってない場合
		{
			PLAYWAVE(PDameSE,0);
			this->Damage=Enemy_Damage;//-2ダメージ
		}
		this->Player.Flag=M_LIFEM;//HP減少処理
		this->Player.MFlag=0;//動きのフラグ初期化
				}
			}//else
		}else{//攻撃フラグたってないとき
			if(EHIT==2)//敵より上のとき
			{
							EnemyS[i].LifeFlag=0;//フラグ0に
							EnemyS[i].MFlag=1;//死亡フラグオン
							PLAYWAVE(EnemyDame,0);
							PLAYWAVE(EnemyDeSE,0);
			}else{
					if(this->Player.POSFlag!=0&&EHIT==1)//左向きの場合かつ判定が反対からの場合
			{
				Player.POSFlag=0;//右向きに
			}
		if(this->Player.POSFlag!=1&&EHIT==0)//右向きの場合かつ判定が反対からの場合
			{
				Player.POSFlag=1;//左向きに
			}
						if(this->Player.Flag!=M_LIFEM)//減少処理が入ってない場合
		{
			PLAYWAVE(PDameSE,0);
			this->Damage=Enemy_Damage;//-2ダメージ
		}
		this->Player.Flag=M_LIFEM;//HP減少処理
		this->Player.MFlag=0;//動きのフラグ初期化
			}
		}//
	}//EHIT


	if(this->Pbullet.POSFlag!=0)//弾発射フラグフラグがたっているとき
	{
		this->Enemychk.HchkInit(Player_Bullet.animation[0],Enemy_Wait.animation[0]);//敵とのあたり判定用意
	this->EHIT=this->Enemychk.Hitcheck(Pbullet.x-40,0,Pbullet.y,EnemyS[i].x,EnemyS[i].y);//当たっているかチェック
		if(EHIT!=0)//あたりが0以外の場合
		{

				Pbullet.MFlag=0;//弾フラグOFF
				Pbullet.Flag=0;
				Pbullet.POSFlag=0;//死亡フラグOFF
		EnemyS[i].LifeFlag=0;//フラグ0に
		EnemyS[i].MFlag=1;//死亡フラグオン
		PLAYWAVE(EnemyDame,0);
		PLAYWAVE(EnemyDeSE,0);
		}
	}
			}
	//============================================
	//敵の脂肪アニメーション
	if(EnemyS[i].MFlag!=0)//敵のフラグが入っていたら
	{
		if(EnemyS[i].MFlag==9)
		{
			EnemyS[i].MFlag=0;//フラグ0に
		}else{
		if(EnemyS[i].MFlag>0)//フラグが0以上
		{
			this->Dbuff.SetBuf(this->Enemy_Dead.animation[EnemyS[i].MFlag/2],EnemyS[i].x,EnemyS[i].y,0);//脂肪画面表示
			if(EnemyS[i].MFlag%2==0)
			{
				this->Dbuff.SetBufED(this->Enemy_Dead.animation[EnemyS[i].MFlag/2],EnemyS[i].x,EnemyS[i].y,0);//脂肪画面表示
			}
			EnemyS[i].MFlag++;
		}
		}
	}
//================================================
	//敵の配置
	if(this->EnemyS[i].LifeFlag!=0)//フラグがたっていたら
	{
		if(this->Count<=One_anim||this->Count>One_anim+20)//40フレームまで
					{
		this->Dbuff.SetBuf(this->Enemy_Shoot.animation[0],EnemyS[i].x,EnemyS[i].y,0);
		}else{
		this->Dbuff.SetBuf(this->Enemy_Shoot.animation[1],EnemyS[i].x,EnemyS[i].y,0);
		}


		if(this->Count==One_anim)//40フレーム目で弾発射
		{
			for(int j=0;j<EnemyShootMAX*2;j++)//空いてる弾検索
			{
				if(this->Ebullet[j].Flag==0)//弾が空いてれば
				{
				this->Ebullet[j].Flag=1;//フラグオン
				this->Ebullet[j].Input(EnemyS[i].x-20,EnemyS[i].y+55);//弾の座標設定
				break;
				}
			}
		}


	}
}
}
//=================================================================
//重力処理
void Gamemain::GravityP()
{
	if(this->Player.y<Y_MAX&&Pchk==0)//プレイヤーが地面より上の場合
	{
		Player.y+=Gravity;
	}
	if(Player.y>Y_MAX)//地面より下の場合
	{
		Player.y=Y_MAX;//地面に合わせる
	}

}

//=========================================================
//敵の弾の処理
void Gamemain::EbulletCheck()
{
	for(int i=0;i<EnemyShootMAX*2;i++)//弾のフラグがたっているかチェック
		if(this->Ebullet[i].Flag==1)//フラグが1なら
		{
			if(Ebullet[i].LifeFlag!=0)//フラグが0以外なら
			{
				if(Ebullet[i].LifeFlag<=8)//ライフが少なくなったら止まる
				{
					this->Dbuff.SetBuf(Enemy_Bullet.animation[1],Ebullet[i].x,Ebullet[i].y,0);
				}else{
				Ebullet[i].x-=15;//弾の進行
							this->Dbuff.SetBuf(Enemy_Bullet.animation[0],Ebullet[i].x,Ebullet[i].y,0);
				}
				Ebullet[i].LifeFlag--;//弾の寿命
			this->Enemychk.HchkInit(Player_Wait.animation[0],Enemy_Bullet.animation[0]);//敵とのあたり判定用意
			EHIT=this->Enemychk.HitcheckEB(Player.x,Dispx,Player.y,Ebullet[i].x,Ebullet[i].y);//弾との当たり判定チェック
			if(EHIT!=0&&EHIT!=-2)//頭より下か当たっていたら
			{
				if(this->Player.POSFlag==1&&EHIT==1)//左向きの場合かつ判定が反対からの場合
			{
				Player.POSFlag=0;//右向きに
			}
								if(this->Player.Flag!=M_LIFEM)//減少処理が入ってない場合
		{
			PLAYWAVE(PDameSE,0);
			this->Damage=Enemy_DShoot;//-2ダメージ
		}
		this->Player.Flag=M_LIFEM;//HP減少処理
		this->Player.MFlag=0;//動きのフラグ初期化
						Ebullet[i].LifeFlag=EbulletLifeMAX;//ライフ初期化
				Ebullet[i].Flag=0;//フラグ0に
			}
			}else{
				Ebullet[i].LifeFlag=EbulletLifeMAX;//ライフ初期化
				Ebullet[i].Flag=0;//フラグ0に
			}
		}
}

//================================================
//足場チェック
void Gamemain::PlateCHECK()//足場チェック
{
	Pchk=0;//初期化
		for(int i=0;i<Base_S;i++)
	{
		this->Platechk.HchkInit(Player_Jump.animation[0],Plate.animation[0]);//足場チェック用意
	this->Pchk=this->Platechk.HitcheckO(Player.x,Dispx,Player.y,PlateSMALL[i].x,PlateSMALL[i].y);
	if(Pchk!=0)
	{
		break;//ループ抜ける
	}
	}
			if(Pchk==0)
			{
		for(int i=0;i<Base_H;i++)
	{

		this->Platechk.HchkInit(Player_Jump.animation[0],Plate.animation[1]);//足場チェック用意
	this->Pchk=this->Platechk.HitcheckO(Player.x,Dispx,Player.y,PlateHIGH[i].x,PlateHIGH[i].y);
	
	if(Pchk!=0)
	{
		break;//ループ抜ける
	}
		}
		}
				if(Pchk==0)//足場とあたってない場合
				{
		for(int i=0;i<Base_L;i++)
		{
			this->Platechk.HchkInit(Player_Jump.animation[0],Plate.animation[2]);//大きい足場チェック用意
			this->Pchk=this->Platechk.HitcheckO(Player.x,Dispx,Player.y,PlateLARGE[i].x,PlateLARGE[i].y);
			
	if(Pchk!=0)
	{
		break;//ループ抜ける
	}
		}
				}

						for(int i=0;i<Base_H;i++)
						{
					this->Dbuff.SetBuf(this->Plate.animation[1],PlateHIGH[i].x,PlateHIGH[i].y,0);
						}
				for(int i=0;i<Base_L;i++)
		{
		this->Dbuff.SetBuf(this->Plate.animation[2],PlateLARGE[i].x,PlateLARGE[i].y,0);
		}
				for(int i=0;i<Base_S;i++)
	{
			this->Dbuff.SetBuf(this->Plate.animation[0],PlateSMALL[i].x,PlateSMALL[i].y,0);
	}
}

//===================================================================
//HPバー処理
void Gamemain::HPstate()
{
	if(this->Damage!=0)//ダメージが0以外
	{
		if(Gas!=0)	//HPが減っていたらガゾリンがあるかチェック
		{	//ガソリンがあったらガソリン減少
		this->Gas-=Damage;//ダメージを加算
		if(Gas<0)//0より下の場合
		{
			Gas=0;//0にする
		}
		}else{//ガソリンがない場合HPを減らす
			Player.LifeFlag--;//ライフ減少
			if(Player.LifeFlag==0)//ライフが０の場合
			{
				GAMEOVER.Flag=1;//ゲームオーバーフラグ
			}else{
			Gas+=GAS_RH;//ガソ回復//HPを減らしたらガソリンが４回復
			}
			//if(Player.LifeFlag<0)	//減ってマイナスになったら０にする
			//{
			//	Player.LifeFlag=0;
			//}
			//
		}
		Damage=0;//ダメージリセット

	
	//HPがゼロの場合ゲームオーバフラグを立てる
	}
			if(Gas>GAS_MAX)//ガソリン量が最大値を超えたら
		{
			Gas=GAS_MAX;//ガソリン量は最大のまま
		}
	//ガソリンバー表示(12入れて１２まで１１で１１までのバー表示)
		this->Dbuff.SetBuf(this->Player_GASbar.animation[0],GAS_X,GAS_Y,Dispx);//ガソリン表示
	this->Dbuff.SetBufState(this->Player_GASbar.animation[1],GAS_X,GAS_Y,Dispx,this->Gas);
	for(int i=0; i<=80;i+=40)
	{
	this->Dbuff.SetBuf(this->Player_HP.animation[0],HP_X+i,GAS_Y,Dispx);//HP表示
	}
	int j=0;
	for(int i=0; i<Player.LifeFlag;i++)
	{
		this->Dbuff.SetBuf(this->Player_HP.animation[1],HP_X+j,GAS_Y,Dispx);	//HPバーを表示(3を入れたら３個２で２個と表示する)
		j+=40;
	}
}
//========================================================================
//ゲームオーバー処理

void Gamemain::GameOver()
{
							if(this->Count>0&&this->Count<=40)//カウントチェック
						{
			Dbuff.SetBuf(this->Player_GAMEOVER.animation[0],this->Player.x,this->Player.y,this->Dispx);
						}else{
			Dbuff.SetBuf(this->Player_GAMEOVER.animation[1],this->Player.x,this->Player.y,this->Dispx);
							}
							if(this->GAMEOVER.Flag<=60)//フラグが０まで
							{	
							if(this->GAMEOVER.Flag>=30)//ゲームオーバー文字表示
							{
			Dbuff.SetBuf(this->Player_GAMEOVER.animation[2],this->GAMEOVER.x-GAMEOVER.Flag,this->GAMEOVER.y,this->Dispx);
							}
														if(this->GAMEOVER.Flag>=40)//ゲームオーバー文字表示
							{
			Dbuff.SetBuf(this->Player_GAMEOVER.animation[3],this->GAMEOVER.x,this->GAMEOVER.y+50,this->Dispx);
														}
																						if(this->GAMEOVER.Flag==10)
								{
									STOPMIDI(this->MIDIMAINBGM);
									STOPMIDI(this->MIDIBOSSBGM);
									PLAYMIDI(this->MIDIGAMEOVERBGM,0);//ゲームオーバー処理
								}
							GAMEOVER.Flag++;//フラグ加算
}else{
	Dbuff.SetBuf(this->Player_GAMEOVER.animation[2],this->GAMEOVER.x-GAMEOVER.Flag,this->GAMEOVER.y,this->Dispx);
	Dbuff.SetBuf(this->Player_GAMEOVER.animation[3],this->GAMEOVER.x,this->GAMEOVER.y+50,this->Dispx);
	Dbuff.SetBuf(this->Player_GAMEOVER.animation[4],this->GAMEOVER.x,this->GAMEOVER.y+100,this->Dispx);
	//カウントに応じてゲームオーバーモーション変更

	//キー入力チェック
	this->KEYCHK.KeySet();
	if(this->KEYCHK.KEY_S!=0x00||this->KEYCHK.KEY_sita!=0x00)
	{
		GAMEOVER.MFlag=1
			;//現在の項目を一つ下にずらす
	}else{
		if(this->KEYCHK.KEY_W!=0x00||this->KEYCHK.KEY_ue!=0x00)//現在の項目を一つ上にずらす
	{
		GAMEOVER.MFlag=0;//現在の項目を一つ下にずらす
	}else{
		if(this->KEYCHK.KEY_ENTER!=0x00||this->KEYCHK.KEY_SP!=0x00)
	{
		//CLOSEWAVE(WAVEBGM);
		switch(GAMEOVER.MFlag)	//リトライならGAMEINIT//MENUならメニューへ戻る
		{
		case 0:
			STOPMIDI(this->MIDIGAMEOVERBGM);
			GameFlag=GAMEMAIN_INIT;
			break;
		case 1:
			STOPMIDI(this->MIDIGAMEOVERBGM);
			GameFlag=TITLE_INIT;
			break;
		}
	}else{//ENTER
	}
	}
	}
	//キー入力に応じたメニューバー表示
		if(GAMEOVER.MFlag!=0)
		{
			Dbuff.SetBufD(this->Player_GAMEOVER.animation[4],this->GAMEOVER.x,this->GAMEOVER.y+100,this->Dispx);
		}else{
			Dbuff.SetBufD(this->Player_GAMEOVER.animation[3],this->GAMEOVER.x,this->GAMEOVER.y+50,this->Dispx);
		}

							}
}
//===============================================================
//ガソリン消費チェック
	void Gamemain::GASMOVEchk()
	{
			if(Player.Flag==M_Attack&&Gas!=0)//攻撃フラグの場合
		{
			Damage=ATTACK_G;//ガソリン消費
		}
			if(Player.Flag==M_Walk)//歩きフラグの場合
			{
				Damage=WALK_G;//ガソリン消費
			}
	}



//=======================================================
//ボス処理
	void Gamemain::BossMODE()
	{
		if(Dispx<=Draw_max)//描画位置が7000以下なら
		{
		Dispx++;//描画位置強制変更
		}
		if(Player.x<Draw_min+10)//プレイヤーの座標が画面外なら
		{
			Player.x=Draw_min+10;
		}
		//ボス表示
		if(Boss.LifeFlag!=0)//ボスのHPが0でない場合
		{
		if(Count%2==0)//矢印処理
		{
	this->Dbuff.SetBuf(this->Plate.animation[3],Info.x,Info.y,0);
		}else{
				this->Dbuff.SetBufD(this->Plate.animation[3],Info.x,Info.y,0);
		}
						if(Message.Flag!=1&&Dispx<Draw_max-10)//メッセージフラグが立ってなくボスの範囲外だったら
						{
			Dispx=Draw_max-10;//ディスプ強制移動
						}

		if(Message.Flag==1)//メッセージフラグ1の時
		{
		if(Dispx>Draw_max-10)//描画位置が6050以上なら
		{
			this->Message.Flag=0;//メッセージフラグOFF
			this->Message.MFlag=0;
		}
		}else{

		this->BossHIT();

		//========================================================================
		switch(Boss.LifeFlag)//残りライフで攻撃形態決定
		{
			//======================================================================
		case 3://口の処理
		this->PlateSMALL[0].InputX(7050);
		this->PlateHIGH[0].InputX(7000);
			if(Enemy[0].LifeFlag==0&&Boss.MFlag==0)//敵のフラグが0かチェック
			{
				Enemy[0].LifeFlag=-1;	//敵フラグ立てる//フラグはマイナス
				Boss.MFlag=80;//ボスの動きフラグを立てる
			}
			if(Enemy[0].LifeFlag==-1)
			{
				this->BossEnemy();//ボスの口から敵を出す
			}
			if(Enemy[0].LifeFlag==1)			//1なら出現
			{
				Enemy[0].x-=15;//進行
			}
			this->Dbuff.SetBuf(BossN.animation[0],Boss.x,Boss.y,0);//ボス表示
			this->Dbuff.SetBuf(BossE.animation[0],Boss.x,Boss.y,0);//ボス表示
			if(Enemy[0].LifeFlag!=-1)
			{
				this->Dbuff.SetBuf(BossM.animation[0],Boss.x,Boss.y,0);//ボス表示
			}
			break;
			//======================================================================-
		case 2://鼻の処理
			Enemy[0].LifeFlag=0;
			if(BossBullet.LifeFlag==0&&Boss.MFlag==13)//弾と動きのフラグがゼロなら
			{
				PLAYWAVE(BossShootSE,0);
				BossBullet.LifeFlag=1;//フラグオン
				BossBullet.Input(7780,205);//位置セット
			}
			if(Boss.MFlag==0)
			{
				Boss.MFlag=80;
			}
				this->Dbuff.SetBuf(BossE.animation[0],Boss.x,Boss.y,0);//ボス表示
			this->Dbuff.SetBuf(BossM.animation[0],Boss.x,Boss.y,0);//ボス表示
			if(Boss.MFlag<=18)//20以下なら
			{
				this->Dbuff.SetBuf(BossN.animation[Boss.MFlag/6],Boss.x,Boss.y,0);//ボス表示
			}else{
				this->Dbuff.SetBuf(BossN.animation[0],Boss.x,Boss.y,0);//ボス表示
			}
		this->PlateSMALL[0].InputX(7000);//足場セット
		this->PlateHIGH[0].InputX(7300);
			Info.InputY(160);
			Jakuten.InputY(150);
			break;
			//=============================================================================
		case 1://目の処理
			if(BossR.LifeFlag==0&&Boss.MFlag==0)//弾と動きのフラグがゼロなら
			{
				PLAYWAVE(BossRaserSE,0);
				BossR.LifeFlag=1;//フラグオン
				BossR.Input(6800,170);//位置セット
				Boss.MFlag=80;
			}
							this->Dbuff.SetBuf(BossN.animation[0],Boss.x,Boss.y,0);//ボス表示
			this->Dbuff.SetBuf(BossM.animation[0],Boss.x,Boss.y,0);//ボス表示
			if(BossR.LifeFlag!=0)//20以下なら
			{
				this->Dbuff.SetBuf(BossE.animation[2],Boss.x,Boss.y,0);//ボス表示
			}else{
				if(Boss.MFlag>=50)//20以下なら
			{
				this->Dbuff.SetBuf(BossE.animation[3],Boss.x,Boss.y,0);//ボス表示
			}else{
				if(Boss.MFlag<=20)
				{
					this->Dbuff.SetBuf(BossE.animation[1],Boss.x,Boss.y,0);//ボス表示
				}else{
					this->Dbuff.SetBuf(BossE.animation[0],Boss.x,Boss.y,0);//ボス表示
				}
							}
			}
		this->PlateSMALL[0].InputX(7000);
		this->PlateHIGH[0].InputX(7150);
		this->PlateLARGE[0].InputX(7400);
		//レーザーチェック
		//レーザを出す
			Info.InputY(140);
			Jakuten.InputY(130);
			break;
		//=================================================================================================================
		}
			//ボス本体のあたり判定
			this->Enemychk.HchkInit(Player_Wait.animation[0],BossG.animation[0]);//ボスとのあたり判定用意
			EHIT=this->Enemychk.HitcheckEB
				(Player.x,Dispx,Player.y,Boss.x,Boss.y);//弾との当たり判定チェック
			if(EHIT!=0)//当たっていたら
			{
				if(this->Player.POSFlag==1&&EHIT==1)//左向きの場合かつ判定が反対からの場合
				{
				Player.POSFlag=0;//右向きに
				}
								if(this->Player.Flag!=M_LIFEM)//減少処理が入ってない場合
								{
									PLAYWAVE(PDameSE,0);
			this->Damage=Enemy_DShoot;//-2ダメージ
								}
		this->Player.Flag=M_LIFEM;//HP減少処理
		this->Player.MFlag=0;//動きのフラグ初期化
			}

		}
		Boss.MFlag--;		//ボスの動きフラグ減少
		if(Boss.MFlag<0)//動きフラグが０以下の場合
		{
			Boss.MFlag=0;//0にリセット
		}
				if(Enemy[0].LifeFlag==-1)
				{
					this->Dbuff.SetBuf(BossM.animation[(Boss.MFlag-71)/3],Boss.x,Boss.y,0);//ボス表示
					Dbuff.SetBuf(Enemy_Dead.animation[(Boss.MFlag-70)/2],Enemy[0].x,Enemy[0].y,0);
				}
				this->BossBulletchk();//弾の判定チェックと表示
				this->BossRaser();
		}else{//ボスが生きているときの処理
					//CLOSEWAVE(WAVESEE);
					//CLOSEWAVE(WAVESE);
			this->BossDead();//死亡処理
			this->Message.Flag=1;//ボスが死んだらメッセージ
			if(this->Bakuha[2].Flag==2&&Boss.POSFlag==0)
			{
				STOPMIDI(this->MIDIBOSSBGM);//音楽終了
				
					this->Boss.POSFlag=1;//ボスのシーン切り替えON
					Boss.MFlag=30;
			}
			if(Boss.MFlag<=10&&Boss.POSFlag==1)
			{
				Boss.POSFlag=2;
			}
			if(Boss.MFlag==0&&Boss.POSFlag==2)
			{
		this->GameFlag=ENDING_INIT;
			}else{
			}
			//ボスの死亡表示
					}
					this->Expl();//爆破表示
	//this->SetMessage();
	}

//===============================================================
	//ボスのHP減少時の処理
	void Gamemain::BossMIHP()
	{
		this->Bakuha[Boss.LifeFlag-1].Flag=1;//爆破フラグがたつ
		this->Bakuha[Boss.LifeFlag-1].LifeFlag=0;//爆破フラグがたつ
		this->Bakuha[Boss.LifeFlag-1].Input(Jakuten.x+30,Jakuten.y-15);//弱点の位置に爆破セット
		if(Boss.LifeFlag==2)//鼻の場合
		{
			this->Bakuha[Boss.LifeFlag-1].Input(Jakuten.x+5,Jakuten.y+20);//弱点の位置に爆破セット
		}
		if(Boss.LifeFlag==1)//目の場合
		{
			this->Bakuha[2].Flag=1;//もう一回爆発
			this->Bakuha[1].Flag=1;
		}
		this->Boss.LifeFlag--;//HPが減る
		this->Boss.MFlag=20;
		this->Itemx[9].InputX(7100);
		this->Itemx[9].Flag=1;//アイテムが出る
		this->Player.x-=Walk_x*3;//少し下がらせる
	}
	//========================================================
	//メッセージ処理
	void Gamemain::SetMessage()
	{
				if(this->Message.MFlag>=0)//0より上なら
				{
			if(this->Message.MFlag>=10)//10より上なら
			{
				this->KeyCheck();//キーチェック
				if((this->KEYCHK.KEY_D!=0x00||this->KEYCHK.KEY_ENTER!=0x00)&&Boss.LifeFlag!=0)//エンターか横移動で消えるがボスが死んでる時は消せない
				{
				//PLAYWAVE(WAVESE,1);
				this->Message.Flag=0;
				this->Message.MFlag=0;
				if(Boss.LifeFlag==0)
				{
					this->GameFlag=TITLE_INIT;//タイトル初期化へ
				}
				this->Dbuff.SetMap(this->Background.animation[0]);
				}
				this->Dbuff.SetMapBHX(this->Background.animation[0]);
				if(Boss.LifeFlag==0)//ボスが死んだら
				{
				this->Dbuff.SetBuf(this->Message_Window.animation[2],Message.x,Message.y,Dispx);//メッセージ表示
				}else{
				if(Boss.Flag==1)//ボスフラグが1なら
				{
				this->Dbuff.SetBuf(this->Message_Window.animation[1],Message.x,Message.y,Dispx);//メッセージ表示
				}else{
				this->Dbuff.SetBuf(this->Message_Window.animation[0],Message.x,Message.y,0);//メッセージ表示
				}
				}
			}else{
			if(this->Message.MFlag>=5)
			{
				this->Dbuff.SetMapBHX(this->Background.animation[0]);
			}else{
				this->Dbuff.SetMapBHX(this->Background.animation[0]);
			}
Message.MFlag++;
			}
			
		}
	}
//=========================================================================================
//ボス処理あたり判定
	void Gamemain::BossHIT()
	{
				this->Enemychk.HchkInit(Player_Wait.animation[0],Plate.animation[0]);//敵とのあたり判定用意
	this->EHIT=this->Enemychk.Hitcheck(Player.x,Dispx,Player.y,Jakuten.x,Jakuten.y);//当たっているかチェック
	if(EHIT!=0&&EHIT!=-2)//あたりが0以外の場合
	{
		if(this->AttackF==1)//攻撃フラグがたっているとき
		{
			if(this->Player.POSFlag!=0)//左向きの場合
			{
				if(EHIT==-1)//マイナス１の場合
				{
		BossMIHP();//ライフ現象
							BossMIHP();//ライフ現象
		Player.x+=Walk_x*2;//戻る
		this->GASMOVEchk();//減少処理
				}else{
		this->AttackF=0;//攻撃フラグ0
		this->Player.Flag=M_LIFEM;//HP減少処理
		this->Player.MFlag=0;//動きのフラグ初期化
				}
			}else{//右向きの場合
				if(EHIT==1)
				{
							BossMIHP();//ライフ現象
							Player.x-=Walk_x*2;//戻る
							this->GASMOVEchk();//減少処理
				}else{
		this->AttackF=0;
		if(this->Player.Flag!=M_LIFEM)//減少処理が入ってない場合
		{
			PLAYWAVE(PDameSE,0);
			this->Damage=Enemy_Damage;//-2ダメージ
		}
		this->Player.Flag=M_LIFEM;//HP減少処理
		this->Player.MFlag=0;//動きのフラグ初期化
				}
			}//else
		}else{//攻撃フラグたってないとき
			if(EHIT==2)//敵より上のとき
			{
							BossMIHP();//ライフ現象
			}else{
					if(this->Player.POSFlag==1&&EHIT==1)//左向きの場合かつ判定が反対からの場合
			{
				Player.POSFlag=0;//右向きに
			}
		if(this->Player.POSFlag==0&&EHIT==-1)//右向きの場合かつ判定が反対からの場合
			{
				Player.POSFlag=1;//左向きに
			}
				if(this->Player.Flag!=M_LIFEM)//減少処理が入ってない場合
		{
			PLAYWAVE(PDameSE,0);
			this->Damage=Enemy_Damage;//-2ダメージ
		}
		this->Player.Flag=M_LIFEM;//HP減少処理
		this->Player.MFlag=0;//動きのフラグ初期化
			}
		}//
	}//EHIT

		if(this->Pbullet.POSFlag!=0)//弾発射フラグフラグがたっているとき
	{
		this->Enemychk.HchkInit(Player_Bullet.animation[0],Plate.animation[0]);//敵とのあたり判定用意
	this->EHIT=this->Enemychk.Hitcheck(Pbullet.x-40,0,Pbullet.y,Jakuten.x,Jakuten.y);//当たっているかチェック
		if(EHIT!=0)//あたりが0以外の場合
		{

				Pbullet.MFlag=0;//弾フラグOFF
				Pbullet.Flag=0;
				Pbullet.POSFlag=0;//死亡フラグOFF
				BossMIHP();//死亡フラグオン
		}
	}
	}



	//=================================================================
//ボスから敵を出す処理
	void Gamemain::BossEnemy()
	{
		if(Boss.MFlag<=80)//フラグが80以下なら
		{
			if(Boss.MFlag==80)
			{
				Enemy[0].InputX(7750);//座標セット
			}
			Enemy[0].x--;//前に進む
			if(Boss.MFlag<=70)//7０以下なら
			{
				Enemy[0].LifeFlag=1;//ライフフラグを立てる
			}
		}
	}

//ボスの弾のチェック
	//==================================================
	void Gamemain::BossBulletchk()
	{
		if(Boss.MFlag>14&&Boss.MFlag<=20)//フラグが２０以下なら
		{
			BossBullet.LifeFlag=0;
		}
		if(BossBullet.LifeFlag!=0)//フラグが立っていたら
		{
			BossBullet.x-=20;
			this->Dbuff.SetBuf(BossBu.animation[0],BossBullet.x,BossBullet.y,0);//表示
			this->Enemychk.HchkInit(this->Player_Wait.animation[0],this->BossBu.animation[0]);
			EHIT=Enemychk.HitcheckEB(Player.x,Dispx,Player.y,BossBullet.x,BossBullet.y);//ボスとプレイヤーの座標チェック
						if(EHIT!=0&&EHIT!=-2)//頭より下か当たっていたら
			{
				if(this->Player.POSFlag==1&&EHIT==1)//左向きの場合かつ判定が反対からの場合
			{
				Player.POSFlag=0;//右向きに
			}
								if(this->Player.Flag!=M_LIFEM)//減少処理が入ってない場合
		{
			PLAYWAVE(PDameSE,0);
			this->Damage=Enemy_DShoot+1;//-2ダメージ
		}
		this->Player.Flag=M_LIFEM;//HP減少処理
		this->Player.MFlag=0;//動きのフラグ初期化
		BossBullet.LifeFlag=0;//フラグ0に
			}
			}else{
				BossBullet.LifeFlag=0;//フラグ0に
		}
	}

	//ボスのレーザー処理
	//=============================================================================
	void Gamemain::BossRaser()
	{
				if(Boss.MFlag<=60)
		{
			BossR.LifeFlag=0;
		}
		if(BossR.LifeFlag!=0)//フラグが立っていたら
		{
			this->Dbuff.SetBuf(BossRa.animation[0],BossR.x,BossR.y,0);//表示
			this->Enemychk.HchkInit(this->Player_Wait.animation[0],this->BossRa.animation[0]);
			EHIT=Enemychk.HitcheckEB(Player.x,Dispx,Player.y,BossR.x,BossR.y);//ボスとプレイヤーの座標チェック
						if(EHIT!=0&&EHIT!=-2)//頭より下か当たっていたら
			{
				if(this->Player.POSFlag==1&&EHIT==1)//左向きの場合かつ判定が反対からの場合
			{
				Player.POSFlag=0;//右向きに
			}
								if(this->Player.Flag!=M_LIFEM)//減少処理が入ってない場合
		{
			PLAYWAVE(PDameSE,0);
			this->Damage=Enemy_DShoot+2;//-2ダメージ
		}
		this->Player.Flag=M_LIFEM;//HP減少処理
		this->Player.MFlag=0;//動きのフラグ初期化
		BossR.LifeFlag=0;//フラグ0に
			}
			}else{
				BossR.LifeFlag=0;//フラグ0に
		}
	}

	//======================================================================
//爆発処理
	void Gamemain::Expl()
	{
		for(int i=0;i<JakutenMAX;i++)
		{
			if(Bakuha[i].Flag==1)
			{
				if(Bakuha[i].LifeFlag==1&&Boss.LifeFlag>0)//ライフが1で０以上になったら
				{
					PLAYWAVE(this->BossDeSE,0);
				}
				
					if(Bakuha[i].LifeFlag==1&&Boss.LifeFlag==0)//ライフが1で０以上になったら
				{
					PLAYWAVE(this->BossDeTSE,0);
				}
				if(Bakuha[i].LifeFlag==30)//ライフが30になったら
				{
					Bakuha[i].Flag=2;//煙のみのフラグ
					Bakuha[i].LifeFlag=0;//フラグリセット
				}else{
				this->Dbuff.SetBuf(this->Explasive.animation[Bakuha[i].LifeFlag/6],Bakuha[i].x,Bakuha[i].y,0);//爆破表示
				}
				Bakuha[i].LifeFlag++;//進行
			}else{
			if(Bakuha[i].Flag==2)//煙のフラグ
			{
				if(Boss.MFlag%2==0)
				{
					this->Dbuff.SetBuf(this->Explasive.animation[5],Bakuha[i].x,Bakuha[i].y,0);//爆破表示
				}else{
					this->Dbuff.SetBuf(this->Explasive.animation[6],Bakuha[i].x,Bakuha[i].y,0);//爆破表示
				}
			}else{
			}
			}
		}
	}

	//ボスの死亡処理
	//=================================================================================================

	void Gamemain::BossDead()
	{
		if(Count%2==0)
		{
			this->Dbuff.SetBuf(BossM.animation[0],Boss.x,Boss.y,0);//ボス表示
			this->Dbuff.SetBuf(BossE.animation[0],Boss.x,Boss.y,0);//ボス表示
			this->Dbuff.SetBuf(BossN.animation[0],Boss.x,Boss.y,0);//ボス表示
		}else{
			this->Dbuff.SetBufED(BossM.animation[0],Boss.x,Boss.y,0);//ボス表示
			this->Dbuff.SetBufED(BossE.animation[0],Boss.x,Boss.y,0);//ボス表示
			this->Dbuff.SetBufED(BossN.animation[0],Boss.x,Boss.y,0);//ボス表示
		}
		if(Boss.POSFlag==1)
		{
			this->Dbuff.SetMapWX(this->Background.animation[0]);
			Boss.MFlag--;
		}
		if(Boss.POSFlag==2)
		{
			this->Dbuff.SetMapW(this->Background.animation[0]);
			Boss.MFlag--;
		}
	}


	//==============================================================
	//ゲームメイン削除
	void Gamemain::GameDel()
	{
			this->Plate.Del();
	this->Background.Del();
	this->Player_Wait.Del();
	this->Player_Walk.Del();
	this->Player_Jump.Del();
	this->Player_Shot.Del();
	this->Player_Bullet.Del();
	this->Player_Attack.Del();
	this->Player_GASbar.Del();
	this->Player_GAMEOVER.Del();
	this->Player_HP.Del();
	this->Enemy_Wait.Del();
	this->Enemy_Shoot.Del();
	this->Enemy_Bullet.Del();
	this->Enemy_Dead.Del();
	
	this->Item.Del();
	
	this->BossG.Del();
	this->BossM.Del();
	this->BossN.Del();
	this->BossE.Del();
	this->BossBu.Del();
	this->BossRa.Del();
	this->Explasive.Del();

	this->Message_Window.Del();

	CLOSEMIDI(this->MIDIMAINBGM);//音楽を開く
	CLOSEMIDI(this->MIDIGAMEOVERBGM);//ゲームオーバー
	CLOSEMIDI(this->MIDIBOSSBGM);//ボス

	CLOSEWAVE(AttackSE);//攻撃音
	CLOSEWAVE(ShootSE);//発射音
	CLOSEWAVE(EnemyDeSE);//敵の脂肪音
	CLOSEWAVE(BossShootSE);//ボスの発射音
	CLOSEWAVE(BossRaserSE);
	CLOSEWAVE(BossDeSE);//敵の脂肪音
	CLOSEWAVE(BossDeTSE);//敵の脂肪音
	CLOSEWAVE(BossLSE);
	CLOSEWAVE(ItemSE);
	CLOSEWAVE(EnemyDame);
	CLOSEWAVE(PDameSE);
	}

