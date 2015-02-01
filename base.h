#ifndef _base
#define _base

//座標とフラグの格納クラス
class Base{
	//コンストラクタ
public:
	Base();
	void InputX(int px);//座標格納
	void InputY(int py);
	void Input(int px,int py);

	int x;
	int y;
	int Flag;//動作の確定フラグ（歩きのみ)
	int MFlag;//動作の確定フラグ(歩き以外)
	int POSFlag;//向きのフラグ
	int LifeFlag;//生存フラグ
	float DFlag;//小数点を使うフラグ 型変換で切り捨てでアニメーションするとか
};
#endif