#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cscreen.h"
#include "Image.h"

#define DISP_OFF_SET_X  1
#define DISP_OFF_SET_Y  1
#define BUFF_X_MAX   1000      // �o�b�t�@����
#define BUFF_Y_MAX   300        // �o�b�t�@�c��
#define LOCATE2( x, y )      LOCATE( x+DISP_OFF_SET_X, y+DISP_OFF_SET_Y )

void Buffer::Init(ImageFile Buff)
{
	screenX=Buff.screenSizeX;
	screenY=Buff.screenSizeY;
	pImge= new CHAR_INFO[Buff.screenSizeY*BUFF_X_MAX];//�����\���p�o�b�t�@
	drawImge= new CHAR_INFO[Buff.screenSizeY*screenX];//�S�f�[�^�i�[�o�b�t�@

}

	void Buffer::SetMap(ImageFile Buff)
{
		for(int loopY=0; loopY<Buff.screenSizeY; loopY++ )
    {
		for(int loopX=0; loopX<screenX; loopX++ )
        {
			drawImge[(loopY * screenX)+loopX]=Buff.pImg[(loopY * Buff.screenSizeX)+loopX];//�O�}�b�v�R�s�[
		}
    }
}


void Buffer::SetBuf(ImageFile Buff,int x,int y,int plx)
{
	int loopX;
	int loopY;

	    // �o�b�t�@�I�[�o�[��h�����߂ɕK���s��
	if( (x> -1) && (x+Buff.screenSizeX < screenX ) 
		&& (y> -1) && (y<screenX  ))
    {
		for( loopY=0; loopY<Buff.screenSizeY; loopY++ )
    {

		for( loopX=0; loopX<Buff.screenSizeX; loopX++ )
        {
            // �A�h���X�v�Z
			if(Buff.pImg[(loopY *Buff.screenSizeX)+(loopX)].Attributes!=255)
			{
				drawImge[((loopY+y) * screenX)+(loopX+x+plx)]=Buff.pImg[(loopY * Buff.screenSizeX)+loopX];//�L�����i�[
			}
		}

    }
	}
}

	void Buffer::DrawBuf(ImageFile Buff,int plx)//�S����������
	{

		for(int loopY=0; loopY<BUFF_Y_MAX; loopY++ )
		{

		for(int loopX=0; loopX<BUFF_X_MAX; loopX++ )
        {
				pImge[(loopY * BUFF_X_MAX)+loopX]=drawImge[((loopY) * screenX)+(loopX+plx)];//�`��͈͊i�[
		}

  
	}
		HANDLE      hCOut;
		COORD       pos         = { 0, 0 };
		COORD       datSize     = { BUFF_X_MAX, Buff.screenSizeY };
		SMALL_RECT  windowRect  = { 0,0, BUFF_X_MAX, Buff.screenSizeY };

		hCOut = GetStdHandle( STD_OUTPUT_HANDLE );

		// �R���\�[���o�b�t�@�ɕ����ƐF�̏�������
		WriteConsoleOutput( hCOut, &pImge[0], datSize, pos, &windowRect );

	}



	void Buffer::SetBufD(ImageFile Buff,int x,int y,int plx)//�_���[�W�\���Z�b�g
{
	int loopX;
	int loopY;

	    // �o�b�t�@�I�[�o�[��h�����߂ɕK���s��
	if( (x> -1) && (x+Buff.screenSizeX < screenX ) 
		&& (y> -1) && (y<screenX  ))
    {
		for( loopY=0; loopY<Buff.screenSizeY; loopY++ )
    {

		for( loopX=0; loopX<Buff.screenSizeX; loopX++ )
        {
            // �A�h���X�v�Z
			if(Buff.pImg[(loopY *Buff.screenSizeX)+(loopX)].Attributes!=255)
			{
				drawImge[((loopY+y) * screenX)+(loopX+x+plx)].Attributes=170;//�L�����i�[
			}
		}

    }
	}
}


		void Buffer::SetBufED(ImageFile Buff,int x,int y,int plx)//�_���[�W�\���Z�b�g�G
{
	int loopX;
	int loopY;

	    // �o�b�t�@�I�[�o�[��h�����߂ɕK���s��
	if( (x> -1) && (x+Buff.screenSizeX < screenX ) 
		&& (y> -1) && (y<screenX  ))
    {
		for( loopY=0; loopY<Buff.screenSizeY; loopY++ )
    {

		for( loopX=0; loopX<Buff.screenSizeX; loopX++ )
        {
            // �A�h���X�v�Z
			if(Buff.pImg[(loopY *Buff.screenSizeX)+(loopX)].Attributes!=255)
			{
				drawImge[((loopY+y) * screenX)+(loopX+x+plx)].Attributes=238;//�L�����i�[
			}
		}

    }
	}
}

				void Buffer::SetBufM(ImageFile Buff,int x,int y,int plx)//�~���[�i�[
{
	int loopX;
	int loopY;

	    // �o�b�t�@�I�[�o�[��h�����߂ɕK���s��
	if( (x> -1) && (x+Buff.screenSizeX < screenX ) 
		&& (y> -1) && (y<screenX  ))
    {
		for( loopY=0; loopY<Buff.screenSizeY; loopY++ )
    {
			int LX=0;
		for( loopX=Buff.screenSizeX-1; loopX>=0; loopX-- )
        {

            // �A�h���X�v�Z
			if(Buff.pImg[(loopY *Buff.screenSizeX)+(loopX)].Attributes!=255)
			{
				drawImge[((loopY+y) * screenX)+(LX+x+plx)]=Buff.pImg[(loopY * Buff.screenSizeX)+loopX];//�L�����i�[
				
			}
			LX++;
		}

    }
	}
}

								void Buffer::SetBufMD(ImageFile Buff,int x,int y,int plx)//�~���[�i�[(�_���[�W�\��)
{
	int loopX;
	int loopY;

	    // �o�b�t�@�I�[�o�[��h�����߂ɕK���s��
	if( (x> -1) && (x+Buff.screenSizeX < screenX ) 
		&& (y> -1) && (y<screenX  ))
    {
		for( loopY=0; loopY<Buff.screenSizeY; loopY++ )
    {
			int LX=0;//�t�ɓ���Ă���
		for( loopX=Buff.screenSizeX-1; loopX>=0; loopX-- )
        {

            // �A�h���X�v�Z
			if(Buff.pImg[(loopY *Buff.screenSizeX)+(loopX)].Attributes!=255)
			{
				drawImge[((loopY+y) * screenX)+(LX+x+plx)].Attributes=170;//�L�����i�[
				
			}
			LX++;
		}

    }
	}
}

				void Buffer::SetBufState(ImageFile Buff,int x,int y,int plx,int num)//�X�e�[�^�X�p�o�b�t�@
{
	int loopX;
	int loopY;

	    // �o�b�t�@�I�[�o�[��h�����߂ɕK���s��
	if( (x> -1) && (x+Buff.screenSizeX < screenX ) 
		&& (y> -1) && (y<screenX  ))
    {
		for( loopY=0; loopY<Buff.screenSizeY; loopY++ )
    {

		for( loopX=0; loopX<(20*num); loopX++ )
        {
            // �A�h���X�v�Z
			if(Buff.pImg[(loopY *Buff.screenSizeX)+(loopX)].Attributes!=255)
			{
				drawImge[((loopY+y) * screenX)+(loopX+x+plx)]=Buff.pImg[(loopY * Buff.screenSizeX)+loopX];//�L�����i�[
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
			drawImge[(loopY * screenX)+loopX].Attributes=0;//�O�}�b�v�R�s�[
			drawImge[(loopY * screenX)+loopX-1].Attributes=0;//�O�}�b�v�R�s�[
		}
    }
}

			void Buffer::SetMapBHX(ImageFile Buff)
{
		for(int loopY=0; loopY<Buff.screenSizeY; loopY+=2 )
    {
		for(int loopX=0; loopX<screenX; loopX++ )
        {
			drawImge[(loopY * screenX)+loopX].Attributes=0;//�O�}�b�v�R�s�[
		}
    }
}
		void Buffer::SetMapB(ImageFile Buff)
{
		for(int loopY=0; loopY<Buff.screenSizeY; loopY++ )
    {
		for(int loopX=0; loopX<screenX; loopX++ )
        {
			drawImge[(loopY * screenX)+loopX].Attributes=0;//�O�}�b�v�R�s�[
		}
    }
}

					void Buffer::SetMapWX(ImageFile Buff)
{
		for(int loopY=0; loopY<Buff.screenSizeY; loopY+=2 )
    {
		for(int loopX=0; loopX<screenX; loopX++ )
        {
			drawImge[(loopY * screenX)+loopX].Attributes=34;//�O�}�b�v�R�s�[
		}
    }
}
		void Buffer::SetMapW(ImageFile Buff)
{
		for(int loopY=0; loopY<Buff.screenSizeY; loopY++ )
    {
		for(int loopX=0; loopX<screenX; loopX++ )
        {
			drawImge[(loopY * screenX)+loopX].Attributes=34;//�O�}�b�v�R�s�[
		}
    }
}