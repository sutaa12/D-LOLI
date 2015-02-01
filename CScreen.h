#ifndef ___CSCREEN_H___
#define ___CSCREEN_H___

/**
 * @file	CScreen.h
 * @brief	Win32 console 擬似ESCシーケンス実装クラスヘッダ version 3.11
 *
 * @author	NH教務部 内藤時浩
 * @date	2002/-5/13 (月)
 * @date	2004/07/02 (金) NH教務部 浜谷浩彦
 * @date	2006/12/11 (月) NH教務部 浜谷浩彦 (Visual Studio 2005専用版)
 * @date	2007/04/10 (火) NH教務部 浜谷浩彦 (2005専用版と統合)
 * @date	2007/11/22 (土) NH教務部 浜谷浩彦 DirectX を Win32 API で代替
 * @date	2008/01/25 (金) NH教務部 浜谷浩彦 Wave でループ再生、再生中対応
 * @date	2008/02/01 (金) NH教務部 浜谷浩彦 MP3 対応
 */

// 読み込むライブラリをビルドモードによって変更する

#ifdef _DEBUG
#pragma comment(lib, "libcmtd.lib")
#pragma comment(lib, "libcpmtd.lib")
#pragma comment(linker, "/NODEFAULTLIB:LIBCD")
#pragma comment(linker, "/NODEFAULTLIB:LIBCPD")
#pragma comment(linker, "/NODEFAULTLIB:MSVCRTD")
#pragma comment(lib, "CScreenDeb.lib")
#else
#pragma comment(lib, "libcmt.lib")
#pragma comment(lib, "libcpmt.lib")
#pragma comment(linker, "/NODEFAULTLIB:LIBC")
#pragma comment(linker, "/NODEFAULTLIB:LIBCP")
#pragma comment(linker, "/NODEFAULTLIB:MSVCRT")
#pragma comment(lib, "CScreenRel.lib")
#endif

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "user32.lib")

/* =================================== */
/* =====       インクルード      ===== */
/* =================================== */

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <io.h>
#include <mmsystem.h>

#pragma warning(disable:4786)
#pragma warning(disable:4996)
#include <map>
#include <set>

typedef std::map<int, int> MAPINT2INT;
typedef std::set<int> SETINT;

/* =================================== */
/* =====        マクロ定義       ===== */
/* =================================== */

#define CURON()			__scr.Cursor(true)				///< カーソルを表示する
#define CUROFF()		__scr.Cursor(false)				///< カーソルを消去する
#define BACKCOLOR(n)	__scr.BackColor(n)				///< 背景色をつける
#define LOCATE(x,y)		__scr.Locate(x,y)				///< 任意の位置にカーソルを移動する
#define BEEP()			putch('\a')						///< BEEP 音を鳴らす
#define CURBASE(n)		__scr.LocateBase(n,n)			///< 原点座標設定

#define INITIAL_CURSOR_HEIGHT	(8)

#define KEY_CRLF				(0x0D)
#define KEY_ESC					(0x1B)
#define KEY_CURSOR				(0xE0)
#define KEY_UP					(0x48)
#define KEY_DOWN				(0x50)
#define KEY_RIGHT				(0x4D)
#define KEY_LEFT				(0x4B)

#define PK_ENTER				VK_RETURN
#define PK_ESC					VK_ESCAPE
#define PK_F1					VK_F1
#define PK_F2					VK_F2
#define PK_F3					VK_F3
#define PK_F4					VK_F4
#define PK_F5					VK_F5
#define PK_F6					VK_F6
#define PK_F7					VK_F7
#define PK_F8					VK_F8
#define PK_F9					VK_F9
#define PK_F10					VK_F10
#define PK_F11					VK_F11
#define PK_F12					VK_F12
#define PK_SP					VK_SPACE
#define PK_UP					VK_UP
#define PK_DOWN					VK_DOWN
#define PK_RIGHT				VK_RIGHT
#define PK_LEFT					VK_LEFT
#define PK_SHIFT				VK_SHIFT
#define PK_CTRL					VK_CONTROL
#define PK_ALT					VK_MENU
#define PK_BS					VK_BACK
#define PK_PAUSE				VK_PAUSE
#define PK_INS					VK_INSERT
#define PK_DEL					VK_DELETE
#define PK_TAB					VK_TAB
#define PK_NFER					VK_KANA		// [無変換]
#define PK_XFER					VK_CONVERT	// [変換]
#define PK_0					0x30
#define PK_1					0x31
#define PK_2					0x32
#define PK_3					0x33
#define PK_4					0x34
#define PK_5					0x35
#define PK_6					0x36
#define PK_7					0x37
#define PK_8					0x38
#define PK_9					0x39
#define PK_NUMPAD0				VK_NUMPAD0	// テンキーの[0]
#define PK_NUMPAD1				VK_NUMPAD1	// テンキーの[1]
#define PK_NUMPAD2				VK_NUMPAD2	// テンキーの[2]
#define PK_NUMPAD3				VK_NUMPAD3	// テンキーの[3]
#define PK_NUMPAD4				VK_NUMPAD4	// テンキーの[4]
#define PK_NUMPAD5				VK_NUMPAD5	// テンキーの[5]
#define PK_NUMPAD6				VK_NUMPAD6	// テンキーの[6]
#define PK_NUMPAD7				VK_NUMPAD7	// テンキーの[7]
#define PK_NUMPAD8				VK_NUMPAD8	// テンキーの[8]
#define PK_NUMPAD9				VK_NUMPAD9	// テンキーの[9]
#define PK_A					0x41
#define PK_B					0x42
#define PK_C					0x43
#define PK_D					0x44
#define PK_E					0x45
#define PK_F					0x46
#define PK_G					0x47
#define PK_H					0x48
#define PK_I					0x49
#define PK_J					0x4A
#define PK_K					0x4B
#define PK_L					0x4C
#define PK_M					0x4D
#define PK_N					0x4E
#define PK_O					0x4F
#define PK_P					0x50
#define PK_Q					0x51
#define PK_R					0x52
#define PK_S					0x53
#define PK_T					0x54
#define PK_U					0x55
#define PK_V					0x56
#define PK_W					0x57
#define PK_X					0x58
#define PK_Y					0x59
#define PK_Z					0x5A

#define PK_LT					0x0BC		// [,]
#define PK_GT					0x0BE		// [.]
#define PK_SLUSH				0x0BF		// [?]
#define PK_DOT					VK_DECIMAL	// テンキーの[.]
#define PK_DIV					VK_DIVIDE	// テンキーの[/]
#define PK_BSLUSH				0x0E2		// [_]

#define PK_SEMICOLON			0x0BB		// [;]
#define PK_ADD					VK_ADD		// テンキーの[+]
#define PK_COLON				0x0BA		// [:]
#define PK_MUL					VK_MULTIPLY	// テンキーの[*]
#define PK_RBRACE				0x0DD		// []]

#define PK_ATMARK				0x0C0		// [@]
#define PK_LBRACE				0x0DB		// [[]

#define PK_MINUS				0x0BD		// [-]
#define PK_SUB					VK_SUBTRACT	// テンキーの[-]
#define PK_XOR					0x0DE		// [^]
#define PK_YEN					0x0DC		// [\]

#define PK_KANJI				0x0F3		// [半角/全角]
#define PK_CAPS					0x0F0		// [英数][ひらがな]

#define PM_LEFT					VK_LBUTTON
#define PM_MID					VK_MBUTTON
#define PM_RIGHT				VK_RBUTTON
#define PM_CURX					0x0101
#define PM_CURY					0x0102

#define PJ1_XPOS				0x0110
#define PJ1_YPOS				0x0111
#define PJ1_ZPOS				0x0112
#define PJ1_BTNS				0x0117
#define PJ2_XPOS				0x0118
#define PJ2_YPOS				0x0119
#define PJ2_ZPOS				0x011a
#define PJ2_BTNS				0x011f
#define PJ_XPOS					PJ1_XPOS
#define PJ_YPOS					PJ1_YPOS
#define PJ_ZPOS					PJ1_ZPOS
#define PJ_BTNS					PJ1_BTNS

enum ESCCOLOR
{
	START_COLOR = 0,

	L_BLACK = START_COLOR,	///< 低輝度・黒色
	L_BLUE,					///< 低輝度・青色
	L_GREEN,				///< 低輝度・緑色
	L_CYAN,					///< 低輝度・水色
	L_RED,					///< 低輝度・赤色
	L_PURPLE,				///< 低輝度・紫色
	L_YELLOW,				///< 低輝度・黄色
	L_WHITE,				///< 低輝度・白色
	H_BLACK,				///< 高輝度・黒色
	H_BLUE,					///< 高輝度・青色
	H_GREEN,				///< 高輝度・緑色
	H_CYAN,					///< 高輝度・水色
	H_RED,					///< 高輝度・赤色
	H_PURPLE,				///< 高輝度・紫色
	H_YELLOW,				///< 高輝度・黄色
	H_WHITE,				///< 高輝度・白色

	BLACK = START_COLOR,	///< 黒色
	NAVY,					///< 濃紺色
	GREEN,					///< 緑色
	CYAN,					///< 水色
	RED,					///< 赤色
	PURPLE,					///< 赤紫色
	BROWN,					///< 茶色
	GRAY,					///< 淡灰色
	DARK,					///< 濃灰色
	BLUE,					///< 青色
	LIME,					///< 淡緑色 ライム
	SKYBLUE,				///< 空色
	CORAL,					///< サンゴ色、朱色、コーラル
	PINK,					///< ピンク、桃色
	YELLOW,					///< 黄色
	WHITE,					///< 白色

	INVALID_COLOR,
};

#define MAGENTA		PINK
#define L_MAGENTA	L_PURPLE
#define H_MAGENTA	H_PURPLE

#ifndef CONSOLE_FULLSCREEN
#define CONSOLE_FULLSCREEN			1	// fullscreen console
#define CONSOLE_FULLSCREEN_HARDWARE	2	// console owns the hardware
#endif // CONSOLE_FULLSCREEN

extern "C" {
typedef BOOL (WINAPI *SetConsoleDisplayModeEntry)(HANDLE, DWORD, DWORD*);
typedef HWND (WINAPI *GetConsoleWindowEntry)(VOID);
};

/**
 * @brief	クラス定義
 */
class CScreen
{
	/// ESCシーケンス用カラーコード設定(内部用)
	enum
	{
		ESC_BLACK  = 0,			///< 黒
		ESC_RED    = 1,			///< 赤
		ESC_GREEN  = 2,			///< 緑
		ESC_YELLOW = 3,			///< 黄
		ESC_BLUE   = 4,			///< 青
		ESC_PURPLE = 5,			///< 紫
		ESC_CYAN   = 6,			///< 水
		ESC_WHITE  = 7,			///< 白
		ESC_HIGH   = 8,			///< 高輝度
	};

private:
	bool IsPlatformWin32NT();
	WORD MakeColorAtrb(unsigned uText = WHITE, unsigned uBack = BLACK);
	void MakeColor(unsigned uText = INVALID_COLOR, unsigned uBack = INVALID_COLOR);
	void PutErr();
	HWND GetHwnd();
	void CleanupSound();

protected:

	HANDLE	m_hCOut;							///< コンソールアウトハンドル
	HANDLE	m_hCIn;								///< コンソール入力ハンドル
	CONSOLE_CURSOR_INFO	m_ccinfo;
	POINTS	m_ptBase;							///< コンソール原点座標

	bool	m_bWinNT;							///< NT系マシンで実行したのか?
	WORD	m_wForeColor;						///< 現在のフォントカラー
	WORD	m_wBackColor;						///< 現在のバックカラー

	DWORD	m_dwKeyMap[8];						///< キー押下状態
	COORD	m_crdMouse;							///< マウス カーソル座標
	SetConsoleDisplayModeEntry	SetConsoleDisplayMode;	///< ウィンドウ状態の設定
	GetConsoleWindowEntry	GetConsoleWindow;	///< ウィンドウ ハンドルの取得

	MAPINT2INT		m_mapWave;					///< Wave バッファ
	SETINT			m_setMIDI;					///< MIDI オブジェクト
	SETINT			m_setMP3;					///< MP3 オブジェクト

public:
	CScreen();
	virtual ~CScreen();

	void Cursor(bool bVisible = true, DWORD dwSize = 0);
	void Locate(int nXpos, int nYpos);
	void LocateBase(int nXpos, int nYpos);
	void Color(unsigned uText, unsigned uBack);
	void BackColor(unsigned uBack);
	void Clear(unsigned uText = INVALID_COLOR, unsigned uBack = INVALID_COLOR);
	int Inp(UINT uPort);
	bool FullScreen(bool bFull = true);
	void InpClear();
	int OpenWave(LPCTSTR pszPath);
	bool PlayWave(int nWaveHandle, bool bLoop = false);
	bool SetWaveVolume(int nWaveHandle, DWORD dwPercent);
	bool SetWavePan(int nWaveHandle, DWORD dwPan);
	bool StopWave(int nWaveHandle);
	bool CloseWave(int nWaveHandle);
	bool IsPlayingWave(int nWaveHandle);
	int OpenMIDI(LPCTSTR pszPath);
	bool PlayMIDI(int nMIDIHandle, bool bLoop = false);
	bool SetMIDIVolume(int nMIDIHandle, DWORD dwPercent);
	bool StopMIDI(int nMIDIHandle);
	bool CloseMIDI(int nMIDIHandle);
	bool IsPlayingMIDI(int nMIDIHandle);
	int OpenMP3(LPCTSTR pszPath);
	bool PlayMP3(int nMP3Handle, bool bLoop = false);
	bool SetMP3Volume(int nMP3Handle, DWORD dwPercent);
	bool StopMP3(int nMP3Handle);
	bool CloseMP3(int nMP3Handle);
	bool IsPlayingMP3(int nMP3Handle);
};

/* =================================== */
/* =====         外部参照        ===== */
/* =================================== */

extern CScreen __scr;					//< CScreen クラスの宣言

/**
 * @brief	キャプションを設定する
 *
 * @param	pszTitle [入力] 新しいタイトル
 */
inline void CAPTION(char* pszTitle)
{
	::SetConsoleTitleA(pszTitle);
}

/**
 * @brief	画面を消去する
 *
 * @param	uText [入力] 文字の色 (省略可)
 * @param	uBack [入力] 背景の色 (省略可)
 */
inline void CLS(unsigned uText = INVALID_COLOR, unsigned uBack = INVALID_COLOR)
{
	__scr.Color(uText, uBack);
	__scr.Clear();
}

#define SCREENCLS	CLS

/**
 * @brief	文字／背景の色を指定する
 *
 * @param	uText [入力] 文字の色
 * @param	uBack [入力] 背景の色 (省略可)
 */
inline void COLOR(unsigned uText, unsigned uBack = INVALID_COLOR)
{
	__scr.Color(uText, uBack);
}

/**
 * @brief	キー押下状態を調べる
 *
 * @param	uPort	[入力] キー／マウス ポート番号
 * @retval	TRUE	押されている
 * @retval	FALSE	押されていない
 */
inline int INP(unsigned uPort)
{
	return __scr.Inp(uPort);
}

/**
 * @brief	全画面表示に切り替える
 *
 * @param	bFull [入力] true; 全画面表示、false; ウィンドウ表示
 * @return	直前の画面状態
 */
inline bool FULL(bool bFull = true)
{
	return __scr.FullScreen(bFull);
}

/**
 * @brief	INKEY専用のキーボードバッファクリア
 */
inline void KEYCLEAR()
{
	while (kbhit())
		getch();
}

/**
 * @brief	キー入力があれば入力する
 *
 * @param	n [出力] 0 以外; キー、0; キー入力無し
 */
inline void INKEY(int& n)
{
	n = (kbhit()) ? getch() : 0;
}

/**
 * @brief	時間待ち
 *
 * @param	n [入力] 待ち時間(単位:ミリ秒)
 */
inline void WAIT(int n)
{
	clock_t tm = clock() + CLOCKS_PER_SEC * n / 1000;
	while (tm > clock())
		;
}

/**
 * @brief	INP()用キーボードバッファクリア
 */
inline void INPCLEAR()
{
	__scr.InpClear();
}

/**
 * @brief	実行ファイルのパスを取得
 *
 * @param	pszDir [入出力] 実行ファイルのパスを格納するバッファへのポインタ
 * @param	uLen [入力] バッファ長 (末尾 '\0' 含む文字数)
 * @return	パスの長さ ('\0' を含まない)
 */
int GETDIR(char* pszDir, unsigned uLen);

/**
 * @brief	ゲームパッド[←]押下状態取得
 *
 * @param	n [入力] 1; プレイヤー1 、2; プレイヤー2
 * @return	0以外; 押されている、0; 離されている
*/
inline int GPLEFT(int n = 1)
{
	int nXPos = INP((n == 1) ? PJ1_XPOS : PJ2_XPOS);
	if (nXPos < 0)
		return 0;
	return nXPos < 0x4000;
}

/**
 * @brief	ゲームパッド[→]押下状態取得
 *
 * @param	n [入力] 1; プレイヤー1 、2; プレイヤー2
 * @return	0以外; 押されている、0; 離されている
*/
inline int GPRIGHT(int n = 1)
{
	int nXPos = INP((n == 1) ? PJ1_XPOS : PJ2_XPOS);
	if (nXPos < 0)
		return 0;
	return nXPos > 0x0c000;
}

/**
 * @brief	ゲームパッド[↑]押下状態取得
 *
 * @param	n [入力] 1; プレイヤー1 、2; プレイヤー2
 * @return	0以外; 押されている、0; 離されている
*/
inline int GPUP(int n = 1)
{
	int nYPos = INP((n == 1) ? PJ1_YPOS : PJ2_YPOS);
	if (nYPos < 0)
		return 0;
	return nYPos < 0x4000;
}

/**
 * @brief	ゲームパッド[↓]押下状態取得
 *
 * @param	n [入力] 1; プレイヤー1 、2; プレイヤー2
 * @return	0以外; 押されている、0; 離されている
*/
inline int GPDOWN(int n = 1)
{
	int nYPos = INP((n == 1) ? PJ1_YPOS : PJ2_YPOS);
	if (nYPos < 0)
		return 0;
	return nYPos > 0x0c000;
}

/**
 * @brief	ゲームパッド ボタン1 押下状態取得
 *
 * @param	n [入力] 1; プレイヤー1 、2; プレイヤー2
 * @return	0以外; 押されている、0; 離されている
*/
inline int GPBTN1(int n = 1)
{
	int nBtn = INP((n == 1) ? PJ1_BTNS : PJ2_BTNS);
	if (nBtn < 0)
		return 0;
	return ((nBtn & JOY_BUTTON1) != 0);
}

/**
 * @brief	ゲームパッド ボタン2 押下状態取得
 *
 * @param	n [入力] 1; プレイヤー1 、2; プレイヤー2
 * @return	0以外; 押されている、0; 離されている
*/
inline int GPBTN2(int n = 1)
{
	int nBtn = INP((n == 1) ? PJ1_BTNS : PJ2_BTNS);
	if (nBtn < 0)
		return 0;
	return ((nBtn & JOY_BUTTON2) != 0);
}

/**
 * @brief	ゲームパッド ボタン3 押下状態取得
 *
 * @param	n [入力] 1; プレイヤー1 、2; プレイヤー2
 * @return	0以外; 押されている、0; 離されている
*/
inline int GPBTN3(int n = 1)
{
	int nBtn = INP((n == 1) ? PJ1_BTNS : PJ2_BTNS);
	if (nBtn < 0)
		return 0;
	return ((nBtn & JOY_BUTTON3) != 0);
}

/**
 * @brief	ゲームパッド ボタン4 押下状態取得
 *
 * @param	n [入力] 1; プレイヤー1 、2; プレイヤー2
 * @return	0以外; 押されている、0; 離されている
*/
inline int GPBTN4(int n = 1)
{
	int nBtn = INP((n == 1) ? PJ1_BTNS : PJ2_BTNS);
	if (nBtn < 0)
		return 0;
	return ((nBtn & JOY_BUTTON4) != 0);
}

/**
 * @brief	Wave ファイル オープン
 *
 * @param	pszPath [入力] Wave ファイル
 * @return	0以外; Wave ハンドル、0; オープン失敗
 */
inline int OPENWAVE(char* pszPath)
{
#ifdef UNICODE
	int nLen = (strlen(pszPath) + 1) * 2;
	LPWSTR pwsz = (LPWSTR)alloca(sizeof(WCHAR) * nLen);
	MultiByteToWideChar(CP_ACP, 0, pszPath, -1, pwsz, nLen);
	return __scr.OpenWave(pwsz);
#else
	return __scr.OpenWave(pszPath);
#endif // _UNICODE
}

/**
 * @brief	Wave 再生
 *
 * @param	nWaveHandle [入力] Wave ハンドル
 * @param	nLoop [入力] 1; 繰り返し再生、0; 1回のみ再生
 */
inline void PLAYWAVE(int nWaveHandle, int nLoop = 0)
{
	__scr.PlayWave(nWaveHandle, nLoop != 0);
}

/**
 * @brief	Wave ボリューム設定
 *
 * @param	nWaveHandle [入力] Wave ハンドル
 * @param	dwPercent [入力] ボリューム (0～100)
 */
inline void SETWAVEVOL(int nWaveHandle, DWORD dwPercent)
{
	__scr.SetWaveVolume(nWaveHandle, dwPercent);
}

/**
 * @brief	Wave 再生停止
 *
 * @param	nWaveHandle [入力] Wave ハンドル
 */
inline void STOPWAVE(int nWaveHandle)
{
	__scr.StopWave(nWaveHandle);
}

/**
 * @brief	Wave ファイル クローズ
 *
 * @param	nWaveHandle [入力] Wave ハンドル
 */
inline void CLOSEWAVE(int nWaveHandle)
{
	__scr.CloseWave(nWaveHandle);
}

/**
 * @brief	Wave 再生中チェック
 *
 * @param	nWaveHandle [入力] Wave ハンドル
 * @return	0以外; 再生中、0; 停止中
 */
inline int ISPLAYINGWAVE(int nWaveHandle)
{
	return (__scr.IsPlayingWave(nWaveHandle) == true);
}

/**
 * @brief	MIDI ファイル オープン
 *
 * @param	pszPath [入力] MIDI ファイル
 * @return	0以外; MIDI ハンドル、0; オープン失敗
 */
inline int OPENMIDI(char* pszPath)
{
#ifdef UNICODE
	int nLen = (strlen(pszPath) + 1) * 2;
	LPWSTR pwsz = (LPWSTR)alloca(sizeof(WCHAR) * nLen);
	MultiByteToWideChar(CP_ACP, 0, pszPath, -1, pwsz, nLen);
	return __scr.OpenMIDI(pwsz);
#else
	return __scr.OpenMIDI(pszPath);
#endif // _UNICODE
}

/**
 * @brief	MIDI 再生
 *
 * @param	nMIDIHandle [入力] MIDI ハンドル
 * @param	bLoop [入力] 1; 繰り返し再生、0; 1回のみ再生
 */
inline void PLAYMIDI(int nMIDIHandle, int nLoop = 0)
{
	__scr.PlayMIDI(nMIDIHandle, nLoop != 0);
}

/**
 * @brief	MIDI ボリューム設定
 *
 * @param	nMIDIHandle [入力] MIDI ハンドル
 * @param	dwPercent [入力] ボリューム (0～100)
 */
inline void SETMIDIVOL(int nMIDIHandle, DWORD dwPercent)
{
	__scr.SetMIDIVolume(nMIDIHandle, dwPercent);
}

/**
 * @brief	MIDI 再生停止
 *
 * @param	nMIDIHandle [入力] MIDI ハンドル
 */
inline void STOPMIDI(int nMIDIHandle)
{
	__scr.StopMIDI(nMIDIHandle);
}

/**
 * @brief	MIDI ファイル クローズ
 *
 * @param	nMIDIHandle [入力] MIDI ハンドル
 */
inline void CLOSEMIDI(int nMIDIHandle)
{
	__scr.CloseMIDI(nMIDIHandle);
}

/**
 * @brief	MIDI 再生中チェック
 *
 * @param	nMIDIHandle [入力] MIDI ハンドル
 * @return	0以外; 再生中、0; 停止中
 */
inline int ISPLAYINGMIDI(int nMIDIHandle)
{
	return (__scr.IsPlayingMIDI(nMIDIHandle) == true);
}

/**
 * @brief	MP3 ファイル オープン
 *
 * @param	pszPath [入力] MP3 ファイル
 * @return	0以外; MP3 ハンドル、0; オープン失敗
 */
inline int OPENMP3(char* pszPath)
{
#ifdef UNICODE
	int nLen = (strlen(pszPath) + 1) * 2;
	LPWSTR pwsz = (LPWSTR)alloca(sizeof(WCHAR) * nLen);
	MultiByteToWideChar(CP_ACP, 0, pszPath, -1, pwsz, nLen);
	return __scr.OpenMP3(pwsz);
#else
	return __scr.OpenMP3(pszPath);
#endif // _UNICODE
}

/**
 * @brief	MP3 再生
 *
 * @param	nMP3Handle [入力] MP3 ハンドル
 * @param	bLoop [入力] 1; 繰り返し再生、0; 1回のみ再生
 */
inline void PLAYMP3(int nMP3Handle, int nLoop = 0)
{
	__scr.PlayMP3(nMP3Handle, nLoop != 0);
}

/**
 * @brief	MP3 ボリューム設定
 *
 * @param	nMP3Handle [入力] MP3 ハンドル
 * @param	dwPercent [入力] ボリューム (0～100)
 */
inline void SETMP3VOL(int nMP3Handle, DWORD dwPercent)
{
	__scr.SetMP3Volume(nMP3Handle, dwPercent);
}

/**
 * @brief	MP3 再生停止
 *
 * @param	nMP3Handle [入力] MP3 ハンドル
 */
inline void STOPMP3(int nMP3Handle)
{
	__scr.StopMP3(nMP3Handle);
}

/**
 * @brief	MP3 ファイル クローズ
 *
 * @param	nMP3Handle [入力] MP3 ハンドル
 */
inline void CLOSEMP3(int nMP3Handle)
{
	__scr.CloseMP3(nMP3Handle);
}

/**
 * @brief	MP3 再生中チェック
 *
 * @param	nMP3Handle [入力] MP3 ハンドル
 * @return	0以外; 再生中、0; 停止中
 */
inline int ISPLAYINGMP3(int nMP3Handle)
{
	return (__scr.IsPlayingMP3(nMP3Handle) == true);
}

#endif	// ___CSCREEN_H___
#if 0

/* =================================== */
/* =====         修正遍歴        ===== */
/* =================================== */

	Version 1.00	2000/10/28 (土)
		・初版公開

	Version 1.00a	2000/11/03 (金)
		・ヘッダ識別子 __ を ___ に変更した。※ __ は C++ の予約語だったため

	Version 1.10	2001/11/10 (土)
		・Win9x系でも動作するようにOSのバージョンチェックによって
		　従来のESCシーケンスも使うように変更した。
		・マクロ定義を標準で定義した。
		・背景色指定を独立させた。
		・画面消去処理がおかしかったので修正した。
		・おまけでいくつかのマクロを設定しておいた。

		※学生テスト配布開始予定版(Windows2000/XP 使用学生フォロー用)
		※getch()が含まれているマクロ(KEYCLEAR, INKEY)があります。これを
		　使用すると、scanf()の動作がおかしくなります。注意!!!

	Version 1.11	2002/-1/26 (土) ---- 未公開
	Version 1.20	2002/-4/25 (木)
		・SCREENCLS()で色指定ができなかったのを修正した。
		・COLOR()で背景色が指定できなかったのを修正した。
		・[Enter][ESC][↑][↓][←][→]のキーコードをマクロ定義した。

	Version 2.00	2002/-5/13 (月)
		・グローバルオブジェクト CScreen scr; の記述が無くても正しく
		　コンパイルできるようにライブラリ化した。

	Version 2.01	2002/10/19 (土)
		・INP() を追加。

	Version 2.02	2002/11/22 (金)
		・INP() のマウス対応。

	Version 2.03	2002/12/26 (木)
		・INP() のジョイスティック／ゲームパッド対応。

	Version 2.04	2003/01/14 (火)
		・背景色に高輝度属性を指定可能にした。

	Version 2.05	2003/01/25 (土)
		・KEYCLEAR() / INKEY() / WAIT() を関数化。
		・GETDIR() / INPCLEAR() を追加。

	Version 2.06	2003/02/08 (土)
		・scr → __scr に変更。
		・PLAYWAVE() 等を追加。

	Version 2.07	2003/03/01 (土)
		・PLAYMIDI() 等を追加。

	Version 3.00	2003/03/10 (土)
		・PK_* にテンキーのコードを追加。

	Version 3.01	2003/07/10 (木)
		・ISPLAYINGWAVE() / ISPLAYINGMIDI() を追加。

	Version 3.02	2003/10/28 (火)
		・コンパイル時のオプションを変更。

	Version 3.03	2004/07/02 (金)
		・CPad for Borland C++ Compiler と Visual C++ のコマンドライン
		　コンパイラ (cl.exe) との組み合わせで使用可能にした。

	Version 3.08	2007/12/05 (水)
		・CURBASE 関数追加。

	Version 3.11	2003/01/30 (水)
		・PLAYMP3() 等を追加。
#endif
