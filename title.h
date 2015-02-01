#include"Image.h"
#include"base.h"
#include"hitchk.h"
#include"KeyIN.h"
#ifndef _title
#define _title

class Title{
public:
	Title();
int TitleInit();
int TitleMain();
void titleDel();//タイトルの初期化
private:
	int Count;//カウント
	int	TitleFlag;//画面遷移の決定フラグ
	int TITLEBGM;//タイトルBGM
	int DOORSE;//ドア閉める音
ImageFile MenuBack;//メニュー画像読み込み
kind MenuButton;
kind Player_Wait;//待機モーション
kind Player_Walk;//歩きモーション
Base Player;//プレイヤー座標フラグ
Base Start;//ボタンの座標格納
Base Logo;//ロゴの座標
Buffer Dbuff;
Hchk Door;//ドアとの判定
KeyIn KEYCHK;//キーチェック

};

#endif


