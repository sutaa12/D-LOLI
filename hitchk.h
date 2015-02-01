
#ifndef _HCK
#define _HCK
class Hchk{

public:
//敵とプレイヤーの当たり判定
	void HchkInit(ImageFile Player,ImageFile Onemy);//初期化
	int Hitcheck(int px,int plx,int py,int ox,int oy);//当たり判定
	int HitcheckEB(int px,int plx,int py,int ox,int oy);//当たり判定
	int HitcheckO(int px,int plx,int py,int ox,int oy);//当たり判定足場

private:
int Oheight;//対象の高さ
int Owidth;//対象の幅
int Pheight;//プレイヤーの高さ
int Pwidth;//プレイヤーの幅
CHAR_INFO *Pimage;
CHAR_INFO *Oimage;

};

#endif


