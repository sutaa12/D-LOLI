#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cscreen.h"
#include "Image.h"

#define buffMove( buf, count )  count += strlen(buf+count) + 1

//ファイル名チェック
int     ImageFile::FileRead( char *ReadfileName,int i)
	{
		fileName = new char[strlen(ReadfileName)+1];
		sprintf( fileName, "%s%d.txt",ReadfileName, i );
		return 0;
	}



// ファイルデータ読み込み
//
//
//
int     ImageFile::ImageFileRead()
{
    FILE    *fp;    // ファイルポインタ
    int     fsize;  // ファイルサイズ

    char    *buff;   // データ領域


    // ファイルオープン
    fp = fopen( fileName, "rt" );
    if( fp == NULL )
    {
        return  -1;
    }


    // ファイルサイズ取得
    fseek( fp, 0, SEEK_END );
    fsize = ftell( fp );
    fseek( fp, 0, SEEK_SET );


    // データ領域確保
	buff=new char[fsize];


    // 全データ読み込み
    fsize = fread( &buff[0], sizeof(char), fsize, fp );


    // ファイルクローズ
    fclose( fp );


    // 改行コードと , を文字列の区切りに変換
    for( int i=0; i<fsize; i++ )
    {
        if( (buff[i]) == 0x0A 
         || (buff[i]) == ',' )
        {
            (buff[i]) = 0x00;
        }
    }


    // データセット
    datSize = fsize;    // バッファサイズ設定
    buf     = buff;      // データ領域設定

	point=0;
    return  1;
}

// パレットデータ設定
//
//
//
int ImageFile::ChangePalette()
{
    // パレットデータ
    COLORREF    palett[16];

    // パレット数
    int         paletteSiz;

    // 色データ
    unsigned int r, g, b, a;

    // データバッファ（作業用）
    char    *buff;
    int     pcount;     // バッファアドレス変更用


    // データセット
    buff     = buf;
    pcount  = point; 


    // パレット数取得
    sscanf( buff+pcount, "%d", &paletteSiz );
    buffMove( buff, pcount );
    pcount++;                       // 改行スキップ


    //パレット取得
    for( int j=0; j<paletteSiz; j++ )
	{
        // 赤データ読み込み
        sscanf( buff+pcount, "%d", &r );
        buffMove( buff, pcount );

        sscanf( buff+pcount, "%d", &g );
        buffMove( buff, pcount );

        sscanf( buff+pcount, "%d", &b );
        buffMove( buff, pcount );

        sscanf( buff+pcount, "%d", &a );
        buffMove( buff, pcount );

        // RGBA 合成
        palett[j] = (a<<24) | (r<<16) | (g<<8) | b;

        pcount++;       // 改行スキップ
    }


    // パレットデータセット
    memcpy( palette, palett, sizeof(COLORREF)*16 );


    // パレット数セット
    paletteSize = paletteSiz;     // パレット数設定
    point        = pcount;          // テキストデータの使用位置更新

    return  1;
}



// スクリーン・バッファサイズ計算
//
//
int ImageFile::ChangeImageSize()
{
    // バッファデータ管理変数
    char    *buff;
    int     pcount;

    // 画像サイズ
    int xMax, yMax;

    // バッファデータセット
    buff     = buf;          // バッファアドレスセット
    pcount  = point;        // バッファ使用位置セット


    // 画像サイズ取得
    sscanf( buff+pcount, "%d", &xMax );
    buffMove( buff, pcount );
    sscanf( buf+pcount, "%d", &yMax );
    buffMove( buff, pcount );

    pcount++;   // 改行スキップ

    // 画像サイズ設定
    imgWidth = xMax;
    imgHight = yMax;

    // コンソールスクリーンサイズ設定
    screenSizeX = xMax * 2;
    screenSizeY = yMax;

    // コンソールバッファサイズ設定
    bufferSizeX = xMax * 2 + 1;
    bufferSizeY = yMax     + 1;


    point = pcount;        // バッファ使用位置セット

    return 1;
}


//画像データに変換
//
//
int ImageFile::ChangeImage()
{
    // 画像データ領域

    // バッファデータ管理変数
    char    *buff;
    int     pcount;

    int     colorNo;        // カラー番号
    int     loopX, loopY;


    // バッファデータセット
    buff     = buf;          // バッファアドレスセット
    pcount  = point;        // バッファ使用位置セット


pImg=new CHAR_INFO[screenSizeY*screenSizeX ];

    // データ変換
    for( loopY=0; loopY<screenSizeY; loopY++ )
    {
        for( loopX=0; loopX<screenSizeX; loopX+=2 )
        {
            // 色データ取り出し
            sscanf( buf+pcount, "%d", &colorNo );
            buffMove( buf, pcount );


            // 画像データ（ 文字と色 ）
                     // 文字データセット
   // 色  データセット
                     // 文字データセット
   // 色  データセット
			pImg[(loopY * screenSizeX)+(loopX+0)].Char.AsciiChar=' ';
			pImg[(loopY * screenSizeX)+(loopX+0)].Attributes     = (colorNo<<4) | colorNo;
			pImg[(loopY * screenSizeX)+(loopX+1)].Char.AsciiChar=' ';
			pImg[(loopY * screenSizeX)+(loopX+1)].Attributes     = (colorNo<<4) | colorNo;
        }

        pcount ++;  // 改行コードスキップ
    }

    // バッファセット

    point = pcount;        // バッファ使用位置セット

    return 1;
}


// バレット書き込み処理
//------------------------------------------------
// コンソール画面のパレット書き換え処理
// 返り値       int         true:正常  false:エラー
// 第１引数     COLORREF *c 書き込むパレットデータのアドレス
//------------------------------------------------
int     ImageFile::SetConsolePalatte()
{

    BOOL        ret;
    HANDLE      hCOut;

    // ウィンドウハンドル取得
    hCOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // コンソール処理用変数
    CONSOLE_SCREEN_BUFFER_INFOEX csbi;
    csbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

    // コンソール情報取得
    ret = GetConsoleScreenBufferInfoEx(hCOut, &csbi );

    // オリジナルパレット書き換え
    memcpy( &csbi.ColorTable[0], palette, sizeof(COLORREF) * 16 );

    // オリジナルパレット設定
    ret = SetConsoleScreenBufferInfoEx(hCOut, &csbi );

    return ret;
}



// 文字データとカラーデータの同時書き込み
//------------------------------------------------
// コンソール画面に直接書き込む処理
// 返り値       int         true:正常  false:エラー
// 第１引数     int         posX    書き込む位置 X
// 第２引数     int         posY    書き込み位置 Y
// 第３引数     int         width   書き込む幅
// 第４引数     int         Hight   書き込む高さ
// 第５引数     CHAR_INFO   *pImage 書き込むデータのアドレス
//------------------------------------------------


int ImageFile::SetWindowSize2( int sx, int fx, int fy )
{
    BOOL        chk;
    BOOL        ret = true;                         // 結果
    HANDLE      hCOut;                              // ハンドル
    COORD       coord      = {0,0};                 // バッファサイズ
    SMALL_RECT  windowRect = {0,0,0,0};             // 画面サイズ

    CONSOLE_FONT_INFOEX consoleFontInfoEx = { 0 };  // フォントサイズ


    // バッファサイズ設定
    coord.X = 1001;
    coord.Y = bufferSizeY;


    // 画面サイズ右下設定
    windowRect.Right  = sx;
    windowRect.Bottom = screenSizeY;


    // ハンドル取得
    hCOut = GetStdHandle( STD_OUTPUT_HANDLE );


    // 構造体サイズ設定
    consoleFontInfoEx.cbSize = sizeof( CONSOLE_FONT_INFOEX );

    // 画面情報取得
    chk = GetCurrentConsoleFontEx( hCOut, 0, &consoleFontInfoEx );

    // フォントサイズ設定
    consoleFontInfoEx.dwFontSize.X = fx;
    consoleFontInfoEx.dwFontSize.Y = fy;

    // フォントサイズ変更
    chk = SetCurrentConsoleFontEx( hCOut, 0, &consoleFontInfoEx );
    // エラー処理
    if( chk == 0 )
    {
        printf( "フォントサイズ設定失敗\n" );
        ret = false;
    }


    // 画面バッファサイズ設定
    chk = SetConsoleScreenBufferSize( hCOut, coord );
    // エラー処理
    if( chk == 0 )
    {
        printf( "画面バッファサイズ設定失敗\n" );
        ret = false;
    }


    // 画面サイズ変更
    chk = SetConsoleWindowInfo( hCOut, TRUE, &windowRect );
    // エラー処理
    if( chk == 0 )
    {
        printf( "画面サイズ設定失敗\n" );
        ret = false;
    }

    return  ret;
}


int     ImageFile::SetConsoleStringAttributesBuffer( int posX, int posY)
{
    BOOL        ret;
    HANDLE      hCOut;
    COORD       pos         = { posX, posY };
    COORD       datSize     = { screenSizeX, screenSizeY };
    SMALL_RECT  windowRect  = { 0,0, screenSizeX, screenSizeY };

    hCOut = GetStdHandle( STD_OUTPUT_HANDLE );

    // コンソールバッファに文字と色の書き込み
    ret = WriteConsoleOutput( hCOut, &pImg[0], datSize, pos, &windowRect );

    return ret;
}

void ImageFile::FreeImage()
{
	    // 領域解放
    if( pImg != NULL )
    {
        delete []pImg;
        pImg = NULL;
    }

    if( buf != NULL )
    {
        delete []buf;
        buf = NULL;
    }

}


