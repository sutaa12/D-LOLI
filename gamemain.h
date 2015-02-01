#include"Image.h"
#include"title.h"
#include"main.h"
#include"hitchk.h"
#include"KeyIN.h"
#ifndef _gamemain
#define _gamemain

class Gamemain{

public:
	//コンストラクタ
	Gamemain();//呼び出し時の画像格納
	//初期化
	int GameInit();//座標情報などの初期化
	//ゲームメイン
	int Gmain();
	//表示位置処理
	void ChengeDisp();
	//アイテム描画
	void DItem();
	//カウント制御
	void CountCheck();
	//敵の初期配置
	void SetEnemy();
	//アイテムの初期配置
	void SetItem();
	//足場の初期配置
	void SetPlate();
	//メッセージチェック
	void SetMessage();
	//ボスあたり判定
	void BossHIT();
	//動作フラグチェック
	void MFlagCheck();
	void AttackMODE();//攻撃フラグ時
	void WalkMODE();//移動時
	void JumpMODE();//ジャンプ時
	void MutekiMODE();//ダメージを受けた時
	void ShootMODE();//発射時
	void WaitMODE();//待機時

	void GameDel();//ゲームメイン初期化
	//============================
	//キーチェック
	void KeyCheck();
	//プレイヤーの弾チェック
	void PbulletCheck();
	//重力処理
	void GravityP();
	//足場チェック
	void PlateCHECK();
	//敵の表示
	void EnemyD();
	//弾を打つ敵の表示
	void EnemySD();
	//弾の進行処理
	void EbulletCheck();
	//HP処理
	void HPstate();
	//ゲームオーバー処理
	void GameOver();
	//減少チェック
	void GASMOVEchk();
	//ボスの処理
	void BossMODE();
	//ボスの減少処理
	void BossMIHP();
	//ボスから敵が出る処理
	void BossEnemy();
	//ボスの弾の処理
	void BossBulletchk();
	//ボスのレーザー処理
	void BossRaser();
	//爆発処理
	void Expl();
	//死亡処理
	void BossDead();
	//音停止
	void StopMUSIC();
	//===============================

private:
	int Dispx;//背景画像の描画位置
	int Count;//ゲーム全体のカウント　全体のフラグ管理
	int Gravity;//重力
	int GameFlag;//ゲームの進行フラグ
	int Pchk;//足場が当たっているかチェック
	int AttackF;//攻撃のフラグ
	int EHIT;//敵と当っているかのフラグ
	int Damage;//ダメージ値と回復値
	int Gas;//ガソリン残量


	int MIDIMAINBGM;//BGMハンドル
	int MIDIGAMEOVERBGM;//BGMハンドル
	int MIDIBOSSBGM;//BGMハンドル

	int AttackSE;//攻撃音
	int ShootSE;//発射音
	int PDameSE;//プレイヤーダメージ
	int EnemyDeSE;//敵の脂肪音
	int EnemyDame;//敵のダメージ
	int BossShootSE;//ボスの発射音
	int BossRaserSE;//ボスのレーザー音
	int BossDeSE;//ボスダメージ音
	int BossDeTSE;//ボス脂肪音
	int BossLSE;//笑い声
	int ItemSE;//アイテム習得音

	kind Background;//背景画像
	kind Plate;//足場の画像
	kind Player_Wait;//プレイヤー画像
	kind Player_Walk;
	kind Player_Attack;
	kind Player_Jump;
	kind Player_Shot;//プレイヤーの発射
	kind Player_Bullet;//弾
	kind Player_GASbar;//ガソリンバー表示
	kind Player_GAMEOVER;//ゲームオーバー表示
	kind Player_HP;//HP表示
	kind Enemy_Wait;//敵画像
	kind Enemy_Shoot;
	kind Enemy_Bullet;//敵の弾
	kind Enemy_Dead;//敵の死亡アニメ
	kind Message_Window;//メッセージ画像
	kind BossG;//ボス画像
	kind BossM;//ボス画像（口)
	kind BossN;//ボス画像(鼻)
	kind BossE;//ボス画像(目)
	kind BossRa;//ボスのレーザー
	kind BossBu;//ボスの弾
	kind Explasive;//爆発
	kind Item;//アイテム

	Base Pbullet;//プレイヤーの弾
	Base Player;//プレイヤー座標とフラグ
	Base *Enemy;//敵の座標とフラグ
	Base *EnemyS;//敵2の座標とフラグ
	Base *Ebullet;//敵の弾とフラグ
	Base *Itemx;//アイテムの座標フラグ

	Base *PlateHIGH;//足場の座標フラグ
	Base *PlateSMALL;//小さい足場
	Base *PlateLARGE;//大きい足場

	Base GAMEOVER;//ゲームオーバー文字表示
	Base Message;//メッセージ表示

	Hchk Platechk;//大きい足場のあたり判定
	Hchk Enemychk;//敵とのあたり判定

	Base Jakuten;//敵の弱点の情報
	Base BossBullet;//ボスの弾の情報
	Base Boss;//ボス情報
	Base BossR;//ボスのレーザー情報
	Base Info;//矢印表示
	Buffer Dbuff;//描画用
	Base *Bakuha;//爆発の位置

	KeyIn KEYCHK;//キー入力チェック
	
};


//=========================================================マクロ定義
#define Y_MAX 150//地面の上限
#define Disp_max 500//画面の移動上限
#define Disp_min 100//画面の最少移動
#define Map_Max 800//画面端の上限

#define Draw_max 7000//マップの上限
#define Draw_min 0//マップの最少

#define Walk_x 10//移動量

#define One_anim 40	//待機アニメーションの区切り

#define Max_anim 3//フラグのマックス
#define W_anim 0.4f//フラグの加算



#define Base_S 7//小さい足場の数
#define Base_H 4//大きい足場の数
#define Base_L 4//もっと大きい足場の数
#define Jump_MAX 6//ジャンプの最大値

#define EnemyMAX 14//敵の数の最大
#define EnemyShootMAX 11//発射する敵の数の最大
#define Enemy_Walkx 10//敵の移動量
#define Enemy_Damage 2//敵の攻撃力
#define Enemy_DShoot 3//遠距離の攻撃力

#define JumpUp 4//ジャンプの加速度

#define EbulletLifeMAX 25//敵の弾のライフの最大値

#define STARTLIFE 3//開始時のライフ
#define STARTG 6//開始時のガス
#define GAS_MAX 12//ガソリンの最大値
#define GAS_RH 4//回復値

#define GAS_X 10//ガソリンバー表示のいち
#define GAS_Y 10//HPも同じ位置
#define ATTACK_G 1//攻撃の消費
#define SHOOT_G 3//発射の消費
#define WALK_G 2//歩き攻撃の消費
#define HP_X 270//HPのいち
#define JakutenMAX 3//弱点の最大数

#define ITEM_MAX 10//アイテムの数


enum Move_MODE{
	M_Wait,M_Walk,M_Jump,M_Attack,M_Shoot,M_LIFEM
};
#endif

