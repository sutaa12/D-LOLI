#include"Image.h"
#include"title.h"
#include"base.h"
#include"main.h"
#include"hitchk.h"
#include"KeyIN.h"
#ifndef _ending
#define _ending
class Ending{
public:
Ending();//コンストラクタ

int endinit();//エンディング初期化
int endingmain();//エンディングのメイン
void endingDel();//エンディングの初期化
private:
	kind Player_Walk;//歩きモーション
	kind Player_Wait;//待機モーション
	kind EndBack;//エンディング用背景
	kind Logo;//エンディングロゴ用

	int Dispx;//背景画像の描画位置
	int Count;//ゲーム全体のカウント　全体のフラグ管理
	int EndFlag;//エンディングの流れの制御
	int ENDINGBGM;//エンディング用BGM

	Base Car;//車の情報
	Base Credit;//クレジット情報
	Base Player;//プレイヤー情報
	Base Logoinfo;//ロゴ情報

	Buffer Dbuff;//描画用

	KeyIn KEYCHK;//キー入力チェック
};
#endif

