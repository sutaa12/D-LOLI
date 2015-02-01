//キー入力処理
#include<windows.h>
#include"CScreen.h"
#include"KeyIN.h"

void KeyIn::KeyInINIT()//キーの初期化
{
	this->KEY_W=0x00;
	this->KEY_A=0x00;
	this->KEY_D=0x00;
	this->KEY_S=0x00;
	this->KEY_SP=0x00;
	this->KEY_ENTER=0x00;
	this->KEY_SHIFT=0x00;
	this->KEY_END=0x00;
	this->KEY_ue=0x00;
	this->KEY_sita=0x00;
}

void KeyIn::KeySet()//キーのセット
{
	this->KEY_W=GetAsyncKeyState(PK_W);
	this->KEY_A=GetAsyncKeyState(PK_A);
	this->KEY_D=GetAsyncKeyState(PK_D);
	this->KEY_S=GetAsyncKeyState(PK_S);
	this->KEY_SP=GetAsyncKeyState(PK_SP);
	this->KEY_SHIFT=GetAsyncKeyState(PK_F);
	this->KEY_ENTER=GetAsyncKeyState(PK_ENTER);
	this->KEY_END=GetAsyncKeyState(PK_ESC);
	this->KEY_ue=GetAsyncKeyState(PK_UP);
	this->KEY_sita=GetAsyncKeyState(PK_DOWN);
}