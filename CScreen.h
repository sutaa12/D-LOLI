#ifndef ___CSCREEN_H___
#define ___CSCREEN_H___

/**
 * @file	CScreen.h
 * @brief	Win32 console �[��ESC�V�[�P���X�����N���X�w�b�_ version 3.11
 *
 * @author	NH������ �������_
 * @date	2002/-5/13 (��)
 * @date	2004/07/02 (��) NH������ �l�J�_�F
 * @date	2006/12/11 (��) NH������ �l�J�_�F (Visual Studio 2005��p��)
 * @date	2007/04/10 (��) NH������ �l�J�_�F (2005��p�łƓ���)
 * @date	2007/11/22 (�y) NH������ �l�J�_�F DirectX �� Win32 API �ő��
 * @date	2008/01/25 (��) NH������ �l�J�_�F Wave �Ń��[�v�Đ��A�Đ����Ή�
 * @date	2008/02/01 (��) NH������ �l�J�_�F MP3 �Ή�
 */

// �ǂݍ��ރ��C�u�������r���h���[�h�ɂ���ĕύX����

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
/* =====       �C���N���[�h      ===== */
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
/* =====        �}�N����`       ===== */
/* =================================== */

#define CURON()			__scr.Cursor(true)				///< �J�[�\����\������
#define CUROFF()		__scr.Cursor(false)				///< �J�[�\������������
#define BACKCOLOR(n)	__scr.BackColor(n)				///< �w�i�F������
#define LOCATE(x,y)		__scr.Locate(x,y)				///< �C�ӂ̈ʒu�ɃJ�[�\�����ړ�����
#define BEEP()			putch('\a')						///< BEEP ����炷
#define CURBASE(n)		__scr.LocateBase(n,n)			///< ���_���W�ݒ�

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
#define PK_NFER					VK_KANA		// [���ϊ�]
#define PK_XFER					VK_CONVERT	// [�ϊ�]
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
#define PK_NUMPAD0				VK_NUMPAD0	// �e���L�[��[0]
#define PK_NUMPAD1				VK_NUMPAD1	// �e���L�[��[1]
#define PK_NUMPAD2				VK_NUMPAD2	// �e���L�[��[2]
#define PK_NUMPAD3				VK_NUMPAD3	// �e���L�[��[3]
#define PK_NUMPAD4				VK_NUMPAD4	// �e���L�[��[4]
#define PK_NUMPAD5				VK_NUMPAD5	// �e���L�[��[5]
#define PK_NUMPAD6				VK_NUMPAD6	// �e���L�[��[6]
#define PK_NUMPAD7				VK_NUMPAD7	// �e���L�[��[7]
#define PK_NUMPAD8				VK_NUMPAD8	// �e���L�[��[8]
#define PK_NUMPAD9				VK_NUMPAD9	// �e���L�[��[9]
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
#define PK_DOT					VK_DECIMAL	// �e���L�[��[.]
#define PK_DIV					VK_DIVIDE	// �e���L�[��[/]
#define PK_BSLUSH				0x0E2		// [_]

#define PK_SEMICOLON			0x0BB		// [;]
#define PK_ADD					VK_ADD		// �e���L�[��[+]
#define PK_COLON				0x0BA		// [:]
#define PK_MUL					VK_MULTIPLY	// �e���L�[��[*]
#define PK_RBRACE				0x0DD		// []]

#define PK_ATMARK				0x0C0		// [@]
#define PK_LBRACE				0x0DB		// [[]

#define PK_MINUS				0x0BD		// [-]
#define PK_SUB					VK_SUBTRACT	// �e���L�[��[-]
#define PK_XOR					0x0DE		// [^]
#define PK_YEN					0x0DC		// [\]

#define PK_KANJI				0x0F3		// [���p/�S�p]
#define PK_CAPS					0x0F0		// [�p��][�Ђ炪��]

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

	L_BLACK = START_COLOR,	///< ��P�x�E���F
	L_BLUE,					///< ��P�x�E�F
	L_GREEN,				///< ��P�x�E�ΐF
	L_CYAN,					///< ��P�x�E���F
	L_RED,					///< ��P�x�E�ԐF
	L_PURPLE,				///< ��P�x�E���F
	L_YELLOW,				///< ��P�x�E���F
	L_WHITE,				///< ��P�x�E���F
	H_BLACK,				///< ���P�x�E���F
	H_BLUE,					///< ���P�x�E�F
	H_GREEN,				///< ���P�x�E�ΐF
	H_CYAN,					///< ���P�x�E���F
	H_RED,					///< ���P�x�E�ԐF
	H_PURPLE,				///< ���P�x�E���F
	H_YELLOW,				///< ���P�x�E���F
	H_WHITE,				///< ���P�x�E���F

	BLACK = START_COLOR,	///< ���F
	NAVY,					///< �Z���F
	GREEN,					///< �ΐF
	CYAN,					///< ���F
	RED,					///< �ԐF
	PURPLE,					///< �Ԏ��F
	BROWN,					///< ���F
	GRAY,					///< �W�D�F
	DARK,					///< �Z�D�F
	BLUE,					///< �F
	LIME,					///< �W�ΐF ���C��
	SKYBLUE,				///< ��F
	CORAL,					///< �T���S�F�A��F�A�R�[����
	PINK,					///< �s���N�A���F
	YELLOW,					///< ���F
	WHITE,					///< ���F

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
 * @brief	�N���X��`
 */
class CScreen
{
	/// ESC�V�[�P���X�p�J���[�R�[�h�ݒ�(�����p)
	enum
	{
		ESC_BLACK  = 0,			///< ��
		ESC_RED    = 1,			///< ��
		ESC_GREEN  = 2,			///< ��
		ESC_YELLOW = 3,			///< ��
		ESC_BLUE   = 4,			///< ��
		ESC_PURPLE = 5,			///< ��
		ESC_CYAN   = 6,			///< ��
		ESC_WHITE  = 7,			///< ��
		ESC_HIGH   = 8,			///< ���P�x
	};

private:
	bool IsPlatformWin32NT();
	WORD MakeColorAtrb(unsigned uText = WHITE, unsigned uBack = BLACK);
	void MakeColor(unsigned uText = INVALID_COLOR, unsigned uBack = INVALID_COLOR);
	void PutErr();
	HWND GetHwnd();
	void CleanupSound();

protected:

	HANDLE	m_hCOut;							///< �R���\�[���A�E�g�n���h��
	HANDLE	m_hCIn;								///< �R���\�[�����̓n���h��
	CONSOLE_CURSOR_INFO	m_ccinfo;
	POINTS	m_ptBase;							///< �R���\�[�����_���W

	bool	m_bWinNT;							///< NT�n�}�V���Ŏ��s�����̂�?
	WORD	m_wForeColor;						///< ���݂̃t�H���g�J���[
	WORD	m_wBackColor;						///< ���݂̃o�b�N�J���[

	DWORD	m_dwKeyMap[8];						///< �L�[�������
	COORD	m_crdMouse;							///< �}�E�X �J�[�\�����W
	SetConsoleDisplayModeEntry	SetConsoleDisplayMode;	///< �E�B���h�E��Ԃ̐ݒ�
	GetConsoleWindowEntry	GetConsoleWindow;	///< �E�B���h�E �n���h���̎擾

	MAPINT2INT		m_mapWave;					///< Wave �o�b�t�@
	SETINT			m_setMIDI;					///< MIDI �I�u�W�F�N�g
	SETINT			m_setMP3;					///< MP3 �I�u�W�F�N�g

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
/* =====         �O���Q��        ===== */
/* =================================== */

extern CScreen __scr;					//< CScreen �N���X�̐錾

/**
 * @brief	�L���v�V������ݒ肷��
 *
 * @param	pszTitle [����] �V�����^�C�g��
 */
inline void CAPTION(char* pszTitle)
{
	::SetConsoleTitleA(pszTitle);
}

/**
 * @brief	��ʂ���������
 *
 * @param	uText [����] �����̐F (�ȗ���)
 * @param	uBack [����] �w�i�̐F (�ȗ���)
 */
inline void CLS(unsigned uText = INVALID_COLOR, unsigned uBack = INVALID_COLOR)
{
	__scr.Color(uText, uBack);
	__scr.Clear();
}

#define SCREENCLS	CLS

/**
 * @brief	�����^�w�i�̐F���w�肷��
 *
 * @param	uText [����] �����̐F
 * @param	uBack [����] �w�i�̐F (�ȗ���)
 */
inline void COLOR(unsigned uText, unsigned uBack = INVALID_COLOR)
{
	__scr.Color(uText, uBack);
}

/**
 * @brief	�L�[������Ԃ𒲂ׂ�
 *
 * @param	uPort	[����] �L�[�^�}�E�X �|�[�g�ԍ�
 * @retval	TRUE	������Ă���
 * @retval	FALSE	������Ă��Ȃ�
 */
inline int INP(unsigned uPort)
{
	return __scr.Inp(uPort);
}

/**
 * @brief	�S��ʕ\���ɐ؂�ւ���
 *
 * @param	bFull [����] true; �S��ʕ\���Afalse; �E�B���h�E�\��
 * @return	���O�̉�ʏ��
 */
inline bool FULL(bool bFull = true)
{
	return __scr.FullScreen(bFull);
}

/**
 * @brief	INKEY��p�̃L�[�{�[�h�o�b�t�@�N���A
 */
inline void KEYCLEAR()
{
	while (kbhit())
		getch();
}

/**
 * @brief	�L�[���͂�����Γ��͂���
 *
 * @param	n [�o��] 0 �ȊO; �L�[�A0; �L�[���͖���
 */
inline void INKEY(int& n)
{
	n = (kbhit()) ? getch() : 0;
}

/**
 * @brief	���ԑ҂�
 *
 * @param	n [����] �҂�����(�P��:�~���b)
 */
inline void WAIT(int n)
{
	clock_t tm = clock() + CLOCKS_PER_SEC * n / 1000;
	while (tm > clock())
		;
}

/**
 * @brief	INP()�p�L�[�{�[�h�o�b�t�@�N���A
 */
inline void INPCLEAR()
{
	__scr.InpClear();
}

/**
 * @brief	���s�t�@�C���̃p�X���擾
 *
 * @param	pszDir [���o��] ���s�t�@�C���̃p�X���i�[����o�b�t�@�ւ̃|�C���^
 * @param	uLen [����] �o�b�t�@�� (���� '\0' �܂ޕ�����)
 * @return	�p�X�̒��� ('\0' ���܂܂Ȃ�)
 */
int GETDIR(char* pszDir, unsigned uLen);

/**
 * @brief	�Q�[���p�b�h[��]������Ԏ擾
 *
 * @param	n [����] 1; �v���C���[1 �A2; �v���C���[2
 * @return	0�ȊO; ������Ă���A0; ������Ă���
*/
inline int GPLEFT(int n = 1)
{
	int nXPos = INP((n == 1) ? PJ1_XPOS : PJ2_XPOS);
	if (nXPos < 0)
		return 0;
	return nXPos < 0x4000;
}

/**
 * @brief	�Q�[���p�b�h[��]������Ԏ擾
 *
 * @param	n [����] 1; �v���C���[1 �A2; �v���C���[2
 * @return	0�ȊO; ������Ă���A0; ������Ă���
*/
inline int GPRIGHT(int n = 1)
{
	int nXPos = INP((n == 1) ? PJ1_XPOS : PJ2_XPOS);
	if (nXPos < 0)
		return 0;
	return nXPos > 0x0c000;
}

/**
 * @brief	�Q�[���p�b�h[��]������Ԏ擾
 *
 * @param	n [����] 1; �v���C���[1 �A2; �v���C���[2
 * @return	0�ȊO; ������Ă���A0; ������Ă���
*/
inline int GPUP(int n = 1)
{
	int nYPos = INP((n == 1) ? PJ1_YPOS : PJ2_YPOS);
	if (nYPos < 0)
		return 0;
	return nYPos < 0x4000;
}

/**
 * @brief	�Q�[���p�b�h[��]������Ԏ擾
 *
 * @param	n [����] 1; �v���C���[1 �A2; �v���C���[2
 * @return	0�ȊO; ������Ă���A0; ������Ă���
*/
inline int GPDOWN(int n = 1)
{
	int nYPos = INP((n == 1) ? PJ1_YPOS : PJ2_YPOS);
	if (nYPos < 0)
		return 0;
	return nYPos > 0x0c000;
}

/**
 * @brief	�Q�[���p�b�h �{�^��1 ������Ԏ擾
 *
 * @param	n [����] 1; �v���C���[1 �A2; �v���C���[2
 * @return	0�ȊO; ������Ă���A0; ������Ă���
*/
inline int GPBTN1(int n = 1)
{
	int nBtn = INP((n == 1) ? PJ1_BTNS : PJ2_BTNS);
	if (nBtn < 0)
		return 0;
	return ((nBtn & JOY_BUTTON1) != 0);
}

/**
 * @brief	�Q�[���p�b�h �{�^��2 ������Ԏ擾
 *
 * @param	n [����] 1; �v���C���[1 �A2; �v���C���[2
 * @return	0�ȊO; ������Ă���A0; ������Ă���
*/
inline int GPBTN2(int n = 1)
{
	int nBtn = INP((n == 1) ? PJ1_BTNS : PJ2_BTNS);
	if (nBtn < 0)
		return 0;
	return ((nBtn & JOY_BUTTON2) != 0);
}

/**
 * @brief	�Q�[���p�b�h �{�^��3 ������Ԏ擾
 *
 * @param	n [����] 1; �v���C���[1 �A2; �v���C���[2
 * @return	0�ȊO; ������Ă���A0; ������Ă���
*/
inline int GPBTN3(int n = 1)
{
	int nBtn = INP((n == 1) ? PJ1_BTNS : PJ2_BTNS);
	if (nBtn < 0)
		return 0;
	return ((nBtn & JOY_BUTTON3) != 0);
}

/**
 * @brief	�Q�[���p�b�h �{�^��4 ������Ԏ擾
 *
 * @param	n [����] 1; �v���C���[1 �A2; �v���C���[2
 * @return	0�ȊO; ������Ă���A0; ������Ă���
*/
inline int GPBTN4(int n = 1)
{
	int nBtn = INP((n == 1) ? PJ1_BTNS : PJ2_BTNS);
	if (nBtn < 0)
		return 0;
	return ((nBtn & JOY_BUTTON4) != 0);
}

/**
 * @brief	Wave �t�@�C�� �I�[�v��
 *
 * @param	pszPath [����] Wave �t�@�C��
 * @return	0�ȊO; Wave �n���h���A0; �I�[�v�����s
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
 * @brief	Wave �Đ�
 *
 * @param	nWaveHandle [����] Wave �n���h��
 * @param	nLoop [����] 1; �J��Ԃ��Đ��A0; 1��̂ݍĐ�
 */
inline void PLAYWAVE(int nWaveHandle, int nLoop = 0)
{
	__scr.PlayWave(nWaveHandle, nLoop != 0);
}

/**
 * @brief	Wave �{�����[���ݒ�
 *
 * @param	nWaveHandle [����] Wave �n���h��
 * @param	dwPercent [����] �{�����[�� (0�`100)
 */
inline void SETWAVEVOL(int nWaveHandle, DWORD dwPercent)
{
	__scr.SetWaveVolume(nWaveHandle, dwPercent);
}

/**
 * @brief	Wave �Đ���~
 *
 * @param	nWaveHandle [����] Wave �n���h��
 */
inline void STOPWAVE(int nWaveHandle)
{
	__scr.StopWave(nWaveHandle);
}

/**
 * @brief	Wave �t�@�C�� �N���[�Y
 *
 * @param	nWaveHandle [����] Wave �n���h��
 */
inline void CLOSEWAVE(int nWaveHandle)
{
	__scr.CloseWave(nWaveHandle);
}

/**
 * @brief	Wave �Đ����`�F�b�N
 *
 * @param	nWaveHandle [����] Wave �n���h��
 * @return	0�ȊO; �Đ����A0; ��~��
 */
inline int ISPLAYINGWAVE(int nWaveHandle)
{
	return (__scr.IsPlayingWave(nWaveHandle) == true);
}

/**
 * @brief	MIDI �t�@�C�� �I�[�v��
 *
 * @param	pszPath [����] MIDI �t�@�C��
 * @return	0�ȊO; MIDI �n���h���A0; �I�[�v�����s
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
 * @brief	MIDI �Đ�
 *
 * @param	nMIDIHandle [����] MIDI �n���h��
 * @param	bLoop [����] 1; �J��Ԃ��Đ��A0; 1��̂ݍĐ�
 */
inline void PLAYMIDI(int nMIDIHandle, int nLoop = 0)
{
	__scr.PlayMIDI(nMIDIHandle, nLoop != 0);
}

/**
 * @brief	MIDI �{�����[���ݒ�
 *
 * @param	nMIDIHandle [����] MIDI �n���h��
 * @param	dwPercent [����] �{�����[�� (0�`100)
 */
inline void SETMIDIVOL(int nMIDIHandle, DWORD dwPercent)
{
	__scr.SetMIDIVolume(nMIDIHandle, dwPercent);
}

/**
 * @brief	MIDI �Đ���~
 *
 * @param	nMIDIHandle [����] MIDI �n���h��
 */
inline void STOPMIDI(int nMIDIHandle)
{
	__scr.StopMIDI(nMIDIHandle);
}

/**
 * @brief	MIDI �t�@�C�� �N���[�Y
 *
 * @param	nMIDIHandle [����] MIDI �n���h��
 */
inline void CLOSEMIDI(int nMIDIHandle)
{
	__scr.CloseMIDI(nMIDIHandle);
}

/**
 * @brief	MIDI �Đ����`�F�b�N
 *
 * @param	nMIDIHandle [����] MIDI �n���h��
 * @return	0�ȊO; �Đ����A0; ��~��
 */
inline int ISPLAYINGMIDI(int nMIDIHandle)
{
	return (__scr.IsPlayingMIDI(nMIDIHandle) == true);
}

/**
 * @brief	MP3 �t�@�C�� �I�[�v��
 *
 * @param	pszPath [����] MP3 �t�@�C��
 * @return	0�ȊO; MP3 �n���h���A0; �I�[�v�����s
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
 * @brief	MP3 �Đ�
 *
 * @param	nMP3Handle [����] MP3 �n���h��
 * @param	bLoop [����] 1; �J��Ԃ��Đ��A0; 1��̂ݍĐ�
 */
inline void PLAYMP3(int nMP3Handle, int nLoop = 0)
{
	__scr.PlayMP3(nMP3Handle, nLoop != 0);
}

/**
 * @brief	MP3 �{�����[���ݒ�
 *
 * @param	nMP3Handle [����] MP3 �n���h��
 * @param	dwPercent [����] �{�����[�� (0�`100)
 */
inline void SETMP3VOL(int nMP3Handle, DWORD dwPercent)
{
	__scr.SetMP3Volume(nMP3Handle, dwPercent);
}

/**
 * @brief	MP3 �Đ���~
 *
 * @param	nMP3Handle [����] MP3 �n���h��
 */
inline void STOPMP3(int nMP3Handle)
{
	__scr.StopMP3(nMP3Handle);
}

/**
 * @brief	MP3 �t�@�C�� �N���[�Y
 *
 * @param	nMP3Handle [����] MP3 �n���h��
 */
inline void CLOSEMP3(int nMP3Handle)
{
	__scr.CloseMP3(nMP3Handle);
}

/**
 * @brief	MP3 �Đ����`�F�b�N
 *
 * @param	nMP3Handle [����] MP3 �n���h��
 * @return	0�ȊO; �Đ����A0; ��~��
 */
inline int ISPLAYINGMP3(int nMP3Handle)
{
	return (__scr.IsPlayingMP3(nMP3Handle) == true);
}

#endif	// ___CSCREEN_H___
#if 0

/* =================================== */
/* =====         �C���՗�        ===== */
/* =================================== */

	Version 1.00	2000/10/28 (�y)
		�E���Ō��J

	Version 1.00a	2000/11/03 (��)
		�E�w�b�_���ʎq __ �� ___ �ɕύX�����B�� __ �� C++ �̗\��ꂾ��������

	Version 1.10	2001/11/10 (�y)
		�EWin9x�n�ł����삷��悤��OS�̃o�[�W�����`�F�b�N�ɂ����
		�@�]����ESC�V�[�P���X���g���悤�ɕύX�����B
		�E�}�N����`��W���Œ�`�����B
		�E�w�i�F�w���Ɨ��������B
		�E��ʏ����������������������̂ŏC�������B
		�E���܂��ł������̃}�N����ݒ肵�Ă������B

		���w���e�X�g�z�z�J�n�\���(Windows2000/XP �g�p�w���t�H���[�p)
		��getch()���܂܂�Ă���}�N��(KEYCLEAR, INKEY)������܂��B�����
		�@�g�p����ƁAscanf()�̓��삪���������Ȃ�܂��B����!!!

	Version 1.11	2002/-1/26 (�y) ---- �����J
	Version 1.20	2002/-4/25 (��)
		�ESCREENCLS()�ŐF�w�肪�ł��Ȃ������̂��C�������B
		�ECOLOR()�Ŕw�i�F���w��ł��Ȃ������̂��C�������B
		�E[Enter][ESC][��][��][��][��]�̃L�[�R�[�h���}�N����`�����B

	Version 2.00	2002/-5/13 (��)
		�E�O���[�o���I�u�W�F�N�g CScreen scr; �̋L�q�������Ă�������
		�@�R���p�C���ł���悤�Ƀ��C�u�����������B

	Version 2.01	2002/10/19 (�y)
		�EINP() ��ǉ��B

	Version 2.02	2002/11/22 (��)
		�EINP() �̃}�E�X�Ή��B

	Version 2.03	2002/12/26 (��)
		�EINP() �̃W���C�X�e�B�b�N�^�Q�[���p�b�h�Ή��B

	Version 2.04	2003/01/14 (��)
		�E�w�i�F�ɍ��P�x�������w��\�ɂ����B

	Version 2.05	2003/01/25 (�y)
		�EKEYCLEAR() / INKEY() / WAIT() ���֐����B
		�EGETDIR() / INPCLEAR() ��ǉ��B

	Version 2.06	2003/02/08 (�y)
		�Escr �� __scr �ɕύX�B
		�EPLAYWAVE() ����ǉ��B

	Version 2.07	2003/03/01 (�y)
		�EPLAYMIDI() ����ǉ��B

	Version 3.00	2003/03/10 (�y)
		�EPK_* �Ƀe���L�[�̃R�[�h��ǉ��B

	Version 3.01	2003/07/10 (��)
		�EISPLAYINGWAVE() / ISPLAYINGMIDI() ��ǉ��B

	Version 3.02	2003/10/28 (��)
		�E�R���p�C�����̃I�v�V������ύX�B

	Version 3.03	2004/07/02 (��)
		�ECPad for Borland C++ Compiler �� Visual C++ �̃R�}���h���C��
		�@�R���p�C�� (cl.exe) �Ƃ̑g�ݍ��킹�Ŏg�p�\�ɂ����B

	Version 3.08	2007/12/05 (��)
		�ECURBASE �֐��ǉ��B

	Version 3.11	2003/01/30 (��)
		�EPLAYMP3() ����ǉ��B
#endif
