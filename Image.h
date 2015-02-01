//画像ファイルの格納と読み込みと表示

#ifndef _Image
#define _Image

class ImageFile{	//イメージファイルのクラス
	friend class Buffer;
	friend class kind;
	friend class Hchk;
public:
	//メンバ関数
	int     FileRead(char *ReadfileName,int i);//ファイル名読み込み
	int     ImageFileRead();//ファイル読み込み
	int     ChangePalette();//パレット情報の設定
	int     ChangeImageSize();//画像サイズを格納
	int     ChangeImage();//画像を格納
	void    FreeImage();//メモリ解放

	int SetWindowSize2( int sx, int fx, int fy );
	int     SetConsolePalatte();
int     SetConsoleStringAttributesBuffer( int posX, int posY);


private:
	//メンバ変数
	char    *fileName;
	int     point;      // 読み出し位置
    int     datSize;    // バッファサイズ
    char    *buf;       // バッファポインタ

    int         imgWidth, imgHight;         // 画像サイズ

    int         bufferSizeX, bufferSizeY;   // コンソールバッファサイズ
    int         screenSizeX, screenSizeY;   // コンソール画面サイズ

    int         paletteSize;                // パレット数

    COLORREF    palette[16];                // パレットデータ

    CHAR_INFO   *pImg;                      // 画像データ（文字と色）
};

class Buffer{
public:

	void Init(ImageFile Buff);//初期化
	void SetMap(ImageFile Buff);//マップデータ読み込み
	void SetBuf(ImageFile Buff,int x,int y,int plx);//画像サイズ　座標　描画バッファーに入れる
	void SetBufM(ImageFile Buff,int x,int y,int plx);//画像サイズ　座標　描画バッファーに入れる(逆向き)
	void SetBufD(ImageFile Buff,int x,int y,int plx);//ダメージ画像表現
	void SetBufED(ImageFile Buff,int x,int y,int plx);//敵のダメージ表現
	void SetBufMD(ImageFile Buff,int x,int y,int plx);//ダメージ表示(逆向き)
	void SetBufState(ImageFile Buff,int x,int y,int plx,int num);//ステータス用バッファ
	void DrawBuf(ImageFile Buf,int plx);//全部入れ替え
	void SetMapBHXY(ImageFile Buff);//黒線
	void SetMapBHX(ImageFile Buff);//黒線Xのみ
	void SetMapB(ImageFile Buff);//黒
	void SetMapWX(ImageFile Buff);//白線Xのみ
	void SetMapW(ImageFile Buff);//白
private:
	CHAR_INFO   *pImge;//マップデータのみ
	CHAR_INFO   *drawImge;//キャラクターなども入っている
	int screenX;//相手の画像サイズ格納
	int screenY;
	int plx;//プレイヤーの座標データにプラスされる座標
};

class kind{//キャラクターの状態を格納
public:
	void anim(int i,char *FName);//アニメーション用の画像格納
	void Del();//全て初期化

ImageFile *animation;
private:	
};

#endif