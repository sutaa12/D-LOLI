#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cscreen.h"
#include "Image.h"

#define DISP_OFF_SET_X  1
#define DISP_OFF_SET_Y  1
#define BUFF_X_MAX   1000      // バッファ横数
#define BUFF_Y_MAX   300        // バッファ縦数
#define LOCATE2( x, y )      LOCATE( x+DISP_OFF_SET_X, y+DISP_OFF_SET_Y )

void Buffer::Init(ImageFile Buff)
{
	screenX=Buff.screenSizeX;
	screenY=Buff.screenSizeY;
	pImge= new CHAR_INFO[Buff.screenSizeY*BUFF_X_MAX];//部分表示用バッファ
	drawImge= new CHAR_INFO[Buff.screenSizeY*screenX];//全データ格納バッファ

}

	void Buffer::SetMap(ImageFile Buff)
{
		for(int loopY=0; loopY<Buff.screenSizeY; loopY++ )
    {
		for(int loopX=0; loopX<screenX; loopX++ )
        {
			drawImge[(loopY * screenX)+loopX]=Buff.pImg[(loopY * Buff.screenSizeX)+loopX];//前マップコピー
		}
    }
}


void Buffer::SetBuf(ImageFile Buff,int x,int y,int plx)
{
	int loopX;
	int loopY;

	    // バッファオーバーを防ぐために必ず行う
	if( (x> -1) && (x+Buff.screenSizeX < screenX ) 
		&& (y> -1) && (y<screenX  ))
    {
		for( loopY=0; loopY<Buff.screenSizeY; loopY++ )
    {

		for( loopX=0; loopX<Buff.screenSizeX; loopX++ )
        {
            // アドレス計算
			if(Buff.pImg[(loopY *Buff.screenSizeX)+(loopX)].Attributes!=255)
			{
				drawImge[((loopY+y) * screenX)+(loopX+x+plx)]=Buff.pImg[(loopY * Buff.screenSizeX)+loopX];//キャラ格納
			}
		}

    }
	}
}

	void Buffer::DrawBuf(ImageFile Buff,int plx)//全部書き換え
	{

		for(int loopY=0; loopY<BUFF_Y_MAX; loopY++ )
		{

		for(int loopX=0; loopX<BUFF_X_MAX; loopX++ )
        {
				pImge[(loopY * BUFF_X_MAX)+loopX]=drawImge[((loopY) * screenX)+(loopX+plx)];//描画範囲格納
		}

  
	}
		HANDLE      hCOut;
		COORD       pos         = { 0, 0 };
		COORD       datSize     = { BUFF_X_MAX, Buff.screenSizeY };
		SMALL_RECT  windowRect  = { 0,0, BUFF_X_MAX, Buff.screenSizeY };

		hCOut = GetStdHandle( STD_OUTPUT_HANDLE );

		// コンソールバッファに文字と色の書き込み
		WriteConsoleOutput( hCOut, &pImge[0], datSize, pos, &windowRect );

	}



	void Buffer::SetBufD(ImageFile Buff,int x,int y,int plx)//ダメージ表現セット
{
	int loopX;
	int loopY;

	    // バッファオーバーを防ぐために必ず行う
	if( (x> -1) && (x+Buff.screenSizeX < screenX ) 
		&& (y> -1) && (y<screenX  ))
    {
		for( loopY=0; loopY<Buff.screenSizeY; loopY++ )
    {

		for( loopX=0; loopX<Buff.screenSizeX; loopX++ )
        {
            // アドレス計算
			if(Buff.pImg[(loopY *Buff.screenSizeX)+(loopX)].Attributes!=255)
			{
				drawImge[((loopY+y) * screenX)+(loopX+x+plx)].Attributes=170;//キャラ格納
			}
		}

    }
	}
}


		void Buffer::SetBufED(ImageFile Buff,int x,int y,int plx)//ダメージ表現セット敵
{
	int loopX;
	int loopY;

	    // バッファオーバーを防ぐために必ず行う
	if( (x> -1) && (x+Buff.screenSizeX < screenX ) 
		&& (y> -1) && (y<screenX  ))
    {
		for( loopY=0; loopY<Buff.screenSizeY; loopY++ )
    {

		for( loopX=0; loopX<Buff.screenSizeX; loopX++ )
        {
            // アドレス計算
			if(Buff.pImg[(loopY *Buff.screenSizeX)+(loopX)].Attributes!=255)
			{
				drawImge[((loopY+y) * screenX)+(loopX+x+plx)].Attributes=238;//キャラ格納
			}
		}

    }
	}
}

				void Buffer::SetBufM(ImageFile Buff,int x,int y,int plx)//ミラー格納
{
	int loopX;
	int loopY;

	    // バッファオーバーを防ぐために必ず行う
	if( (x> -1) && (x+Buff.screenSizeX < screenX ) 
		&& (y> -1) && (y<screenX  ))
    {
		for( loopY=0; loopY<Buff.screenSizeY; loopY++ )
    {
			int LX=0;
		for( loopX=Buff.screenSizeX-1; loopX>=0; loopX-- )
        {

            // アドレス計算
			if(Buff.pImg[(loopY *Buff.screenSizeX)+(loopX)].Attributes!=255)
			{
				drawImge[((loopY+y) * screenX)+(LX+x+plx)]=Buff.pImg[(loopY * Buff.screenSizeX)+loopX];//キャラ格納
				
			}
			LX++;
		}

    }
	}
}

								void Buffer::SetBufMD(ImageFile Buff,int x,int y,int plx)//ミラー格納(ダメージ表示)
{
	int loopX;
	int loopY;

	    // バッファオーバーを防ぐために必ず行う
	if( (x> -1) && (x+Buff.screenSizeX < screenX ) 
		&& (y> -1) && (y<screenX  ))
    {
		for( loopY=0; loopY<Buff.screenSizeY; loopY++ )
    {
			int LX=0;//逆に入れていく
		for( loopX=Buff.screenSizeX-1; loopX>=0; loopX-- )
        {

            // アドレス計算
			if(Buff.pImg[(loopY *Buff.screenSizeX)+(loopX)].Attributes!=255)
			{
				drawImge[((loopY+y) * screenX)+(LX+x+plx)].Attributes=170;//キャラ格納
				
			}
			LX++;
		}

    }
	}
}

				void Buffer::SetBufState(ImageFile Buff,int x,int y,int plx,int num)//ステータス用バッファ
{
	int loopX;
	int loopY;

	    // バッファオーバーを防ぐために必ず行う
	if( (x> -1) && (x+Buff.screenSizeX < screenX ) 
		&& (y> -1) && (y<screenX  ))
    {
		for( loopY=0; loopY<Buff.screenSizeY; loopY++ )
    {

		for( loopX=0; loopX<(20*num); loopX++ )
        {
            // アドレス計算
			if(Buff.pImg[(loopY *Buff.screenSizeX)+(loopX)].Attributes!=255)
			{
				drawImge[((loopY+y) * screenX)+(loopX+x+plx)]=Buff.pImg[(loopY * Buff.screenSizeX)+loopX];//キャラ格納
			}
		}

    }
	}
}

	void Buffer::SetMapBHXY(ImageFile Buff)
{
		for(int loopY=0; loopY<Buff.screenSizeY; loopY+=2 )
    {
		for(int loopX=0; loopX<screenX; loopX+=4 )
        {
			drawImge[(loopY * screenX)+loopX].Attributes=0;//前マップコピー
			drawImge[(loopY * screenX)+loopX-1].Attributes=0;//前マップコピー
		}
    }
}

			void Buffer::SetMapBHX(ImageFile Buff)
{
		for(int loopY=0; loopY<Buff.screenSizeY; loopY+=2 )
    {
		for(int loopX=0; loopX<screenX; loopX++ )
        {
			drawImge[(loopY * screenX)+loopX].Attributes=0;//前マップコピー
		}
    }
}
		void Buffer::SetMapB(ImageFile Buff)
{
		for(int loopY=0; loopY<Buff.screenSizeY; loopY++ )
    {
		for(int loopX=0; loopX<screenX; loopX++ )
        {
			drawImge[(loopY * screenX)+loopX].Attributes=0;//前マップコピー
		}
    }
}

					void Buffer::SetMapWX(ImageFile Buff)
{
		for(int loopY=0; loopY<Buff.screenSizeY; loopY+=2 )
    {
		for(int loopX=0; loopX<screenX; loopX++ )
        {
			drawImge[(loopY * screenX)+loopX].Attributes=34;//前マップコピー
		}
    }
}
		void Buffer::SetMapW(ImageFile Buff)
{
		for(int loopY=0; loopY<Buff.screenSizeY; loopY++ )
    {
		for(int loopX=0; loopX<screenX; loopX++ )
        {
			drawImge[(loopY * screenX)+loopX].Attributes=34;//前マップコピー
		}
    }
}