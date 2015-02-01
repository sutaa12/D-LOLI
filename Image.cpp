#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cscreen.h"
#include "Image.h"

#define buffMove( buf, count )  count += strlen(buf+count) + 1

//�t�@�C�����`�F�b�N
int     ImageFile::FileRead( char *ReadfileName,int i)
	{
		fileName = new char[strlen(ReadfileName)+1];
		sprintf( fileName, "%s%d.txt",ReadfileName, i );
		return 0;
	}



// �t�@�C���f�[�^�ǂݍ���
//
//
//
int     ImageFile::ImageFileRead()
{
    FILE    *fp;    // �t�@�C���|�C���^
    int     fsize;  // �t�@�C���T�C�Y

    char    *buff;   // �f�[�^�̈�


    // �t�@�C���I�[�v��
    fp = fopen( fileName, "rt" );
    if( fp == NULL )
    {
        return  -1;
    }


    // �t�@�C���T�C�Y�擾
    fseek( fp, 0, SEEK_END );
    fsize = ftell( fp );
    fseek( fp, 0, SEEK_SET );


    // �f�[�^�̈�m��
	buff=new char[fsize];


    // �S�f�[�^�ǂݍ���
    fsize = fread( &buff[0], sizeof(char), fsize, fp );


    // �t�@�C���N���[�Y
    fclose( fp );


    // ���s�R�[�h�� , �𕶎���̋�؂�ɕϊ�
    for( int i=0; i<fsize; i++ )
    {
        if( (buff[i]) == 0x0A 
         || (buff[i]) == ',' )
        {
            (buff[i]) = 0x00;
        }
    }


    // �f�[�^�Z�b�g
    datSize = fsize;    // �o�b�t�@�T�C�Y�ݒ�
    buf     = buff;      // �f�[�^�̈�ݒ�

	point=0;
    return  1;
}

// �p���b�g�f�[�^�ݒ�
//
//
//
int ImageFile::ChangePalette()
{
    // �p���b�g�f�[�^
    COLORREF    palett[16];

    // �p���b�g��
    int         paletteSiz;

    // �F�f�[�^
    unsigned int r, g, b, a;

    // �f�[�^�o�b�t�@�i��Ɨp�j
    char    *buff;
    int     pcount;     // �o�b�t�@�A�h���X�ύX�p


    // �f�[�^�Z�b�g
    buff     = buf;
    pcount  = point; 


    // �p���b�g���擾
    sscanf( buff+pcount, "%d", &paletteSiz );
    buffMove( buff, pcount );
    pcount++;                       // ���s�X�L�b�v


    //�p���b�g�擾
    for( int j=0; j<paletteSiz; j++ )
	{
        // �ԃf�[�^�ǂݍ���
        sscanf( buff+pcount, "%d", &r );
        buffMove( buff, pcount );

        sscanf( buff+pcount, "%d", &g );
        buffMove( buff, pcount );

        sscanf( buff+pcount, "%d", &b );
        buffMove( buff, pcount );

        sscanf( buff+pcount, "%d", &a );
        buffMove( buff, pcount );

        // RGBA ����
        palett[j] = (a<<24) | (r<<16) | (g<<8) | b;

        pcount++;       // ���s�X�L�b�v
    }


    // �p���b�g�f�[�^�Z�b�g
    memcpy( palette, palett, sizeof(COLORREF)*16 );


    // �p���b�g���Z�b�g
    paletteSize = paletteSiz;     // �p���b�g���ݒ�
    point        = pcount;          // �e�L�X�g�f�[�^�̎g�p�ʒu�X�V

    return  1;
}



// �X�N���[���E�o�b�t�@�T�C�Y�v�Z
//
//
int ImageFile::ChangeImageSize()
{
    // �o�b�t�@�f�[�^�Ǘ��ϐ�
    char    *buff;
    int     pcount;

    // �摜�T�C�Y
    int xMax, yMax;

    // �o�b�t�@�f�[�^�Z�b�g
    buff     = buf;          // �o�b�t�@�A�h���X�Z�b�g
    pcount  = point;        // �o�b�t�@�g�p�ʒu�Z�b�g


    // �摜�T�C�Y�擾
    sscanf( buff+pcount, "%d", &xMax );
    buffMove( buff, pcount );
    sscanf( buf+pcount, "%d", &yMax );
    buffMove( buff, pcount );

    pcount++;   // ���s�X�L�b�v

    // �摜�T�C�Y�ݒ�
    imgWidth = xMax;
    imgHight = yMax;

    // �R���\�[���X�N���[���T�C�Y�ݒ�
    screenSizeX = xMax * 2;
    screenSizeY = yMax;

    // �R���\�[���o�b�t�@�T�C�Y�ݒ�
    bufferSizeX = xMax * 2 + 1;
    bufferSizeY = yMax     + 1;


    point = pcount;        // �o�b�t�@�g�p�ʒu�Z�b�g

    return 1;
}


//�摜�f�[�^�ɕϊ�
//
//
int ImageFile::ChangeImage()
{
    // �摜�f�[�^�̈�

    // �o�b�t�@�f�[�^�Ǘ��ϐ�
    char    *buff;
    int     pcount;

    int     colorNo;        // �J���[�ԍ�
    int     loopX, loopY;


    // �o�b�t�@�f�[�^�Z�b�g
    buff     = buf;          // �o�b�t�@�A�h���X�Z�b�g
    pcount  = point;        // �o�b�t�@�g�p�ʒu�Z�b�g


pImg=new CHAR_INFO[screenSizeY*screenSizeX ];

    // �f�[�^�ϊ�
    for( loopY=0; loopY<screenSizeY; loopY++ )
    {
        for( loopX=0; loopX<screenSizeX; loopX+=2 )
        {
            // �F�f�[�^���o��
            sscanf( buf+pcount, "%d", &colorNo );
            buffMove( buf, pcount );


            // �摜�f�[�^�i �����ƐF �j
                     // �����f�[�^�Z�b�g
   // �F  �f�[�^�Z�b�g
                     // �����f�[�^�Z�b�g
   // �F  �f�[�^�Z�b�g
			pImg[(loopY * screenSizeX)+(loopX+0)].Char.AsciiChar=' ';
			pImg[(loopY * screenSizeX)+(loopX+0)].Attributes     = (colorNo<<4) | colorNo;
			pImg[(loopY * screenSizeX)+(loopX+1)].Char.AsciiChar=' ';
			pImg[(loopY * screenSizeX)+(loopX+1)].Attributes     = (colorNo<<4) | colorNo;
        }

        pcount ++;  // ���s�R�[�h�X�L�b�v
    }

    // �o�b�t�@�Z�b�g

    point = pcount;        // �o�b�t�@�g�p�ʒu�Z�b�g

    return 1;
}


// �o���b�g�������ݏ���
//------------------------------------------------
// �R���\�[����ʂ̃p���b�g������������
// �Ԃ�l       int         true:����  false:�G���[
// ��P����     COLORREF *c �������ރp���b�g�f�[�^�̃A�h���X
//------------------------------------------------
int     ImageFile::SetConsolePalatte()
{

    BOOL        ret;
    HANDLE      hCOut;

    // �E�B���h�E�n���h���擾
    hCOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // �R���\�[�������p�ϐ�
    CONSOLE_SCREEN_BUFFER_INFOEX csbi;
    csbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

    // �R���\�[�����擾
    ret = GetConsoleScreenBufferInfoEx(hCOut, &csbi );

    // �I���W�i���p���b�g��������
    memcpy( &csbi.ColorTable[0], palette, sizeof(COLORREF) * 16 );

    // �I���W�i���p���b�g�ݒ�
    ret = SetConsoleScreenBufferInfoEx(hCOut, &csbi );

    return ret;
}



// �����f�[�^�ƃJ���[�f�[�^�̓�����������
//------------------------------------------------
// �R���\�[����ʂɒ��ڏ������ޏ���
// �Ԃ�l       int         true:����  false:�G���[
// ��P����     int         posX    �������ވʒu X
// ��Q����     int         posY    �������݈ʒu Y
// ��R����     int         width   �������ޕ�
// ��S����     int         Hight   �������ލ���
// ��T����     CHAR_INFO   *pImage �������ރf�[�^�̃A�h���X
//------------------------------------------------


int ImageFile::SetWindowSize2( int sx, int fx, int fy )
{
    BOOL        chk;
    BOOL        ret = true;                         // ����
    HANDLE      hCOut;                              // �n���h��
    COORD       coord      = {0,0};                 // �o�b�t�@�T�C�Y
    SMALL_RECT  windowRect = {0,0,0,0};             // ��ʃT�C�Y

    CONSOLE_FONT_INFOEX consoleFontInfoEx = { 0 };  // �t�H���g�T�C�Y


    // �o�b�t�@�T�C�Y�ݒ�
    coord.X = 1001;
    coord.Y = bufferSizeY;


    // ��ʃT�C�Y�E���ݒ�
    windowRect.Right  = sx;
    windowRect.Bottom = screenSizeY;


    // �n���h���擾
    hCOut = GetStdHandle( STD_OUTPUT_HANDLE );


    // �\���̃T�C�Y�ݒ�
    consoleFontInfoEx.cbSize = sizeof( CONSOLE_FONT_INFOEX );

    // ��ʏ��擾
    chk = GetCurrentConsoleFontEx( hCOut, 0, &consoleFontInfoEx );

    // �t�H���g�T�C�Y�ݒ�
    consoleFontInfoEx.dwFontSize.X = fx;
    consoleFontInfoEx.dwFontSize.Y = fy;

    // �t�H���g�T�C�Y�ύX
    chk = SetCurrentConsoleFontEx( hCOut, 0, &consoleFontInfoEx );
    // �G���[����
    if( chk == 0 )
    {
        printf( "�t�H���g�T�C�Y�ݒ莸�s\n" );
        ret = false;
    }


    // ��ʃo�b�t�@�T�C�Y�ݒ�
    chk = SetConsoleScreenBufferSize( hCOut, coord );
    // �G���[����
    if( chk == 0 )
    {
        printf( "��ʃo�b�t�@�T�C�Y�ݒ莸�s\n" );
        ret = false;
    }


    // ��ʃT�C�Y�ύX
    chk = SetConsoleWindowInfo( hCOut, TRUE, &windowRect );
    // �G���[����
    if( chk == 0 )
    {
        printf( "��ʃT�C�Y�ݒ莸�s\n" );
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

    // �R���\�[���o�b�t�@�ɕ����ƐF�̏�������
    ret = WriteConsoleOutput( hCOut, &pImg[0], datSize, pos, &windowRect );

    return ret;
}

void ImageFile::FreeImage()
{
	    // �̈���
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


