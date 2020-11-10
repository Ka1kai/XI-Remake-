//----------------------------------------------------
// CWindowSystem
// �E�B���h�E���쐬 ���䂷��N���X
// 
// @date	2013/4/25
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_WINDOW_SYSTEM_H_
#define _C_WINDOW_SYSTEM_H_

#include <windows.h>
#include "../../../GameInfo.h"
#include "../DebugHeader/CDebugConsole.hpp"

#pragma	comment(lib,"winmm.lib")

#define WINDOW_MAX_X	( GetSystemMetrics(SM_CXSCREEN) )	// �E�B���h�EX�ő啝
#define WINDOW_MAX_Y	( GetSystemMetrics(SM_CYSCREEN) )	// �E�B���h�EY�ő啝

#define DEFAULT_WINDOW_X	640		// �E�B���h�EX�T�C�Y�����l
#define DEFAULT_WINDOW_Y	480		// �E�B���h�EY�T�C�Y�����l

#define WINDOW_CLASS_NAME	"DirectX"

class CWindowSystem
{
private:
	WNDCLASSEX	wc;
	MSG			msg;
	LPSTR		wndName;			// �E�B���h�E�̖��O

	short		screenWidth;		// �X�N���[��X�T�C�Y
	short		screenHeight;		// �X�N���[��Y�T�C�Y

	POINT		clientSize;			// �N���C�A���g�̃T�C�Y

public:
	// �R���X�g���N�^	
	CWindowSystem	( void );												// �E�B���h�E�̑傫�����w�肵�Ȃ��E�B���h�E�쐬
	CWindowSystem	( CONST UINT screenWidth, CONST UINT screenHeight );	// �E�B���h�E�̑傫�����w�肵�ăE�B���h�E�쐬
	CWindowSystem	( CONST bool isFullScr );										// �t���X�N���[�����[�h�p�̃E�B���h�E�쐬

	// �f�X�g���N�^
	virtual		~CWindowSystem	( void )
	{
		timeEndPeriod(1);
	}

private:
	static		LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
	HRESULT		CreateWnd				( void );
	HRESULT		SetWindowClass			( void );
	void		SetClientSize			( void );				// �N���C�A���g�T�C�Y�̐ݒ�

public:
	HRESULT		SetShowWindow		( void );
	BOOL		GetEventMessage		( void );
	BOOL		PeekEventMessage	( void );

public:
	// ���b�Z�[�W���擾
	INT	GetMessageWParam	( void )
	{
		return (int)msg.wParam;
	}

	// �V���O���g���ŃE�B���h�E�̃n���h�����O���[�o������
	static HWND&	GethWnd	( void )
	{
		static HWND hWnd;
		return hWnd;
	}

};

#endif	_C_WINDOW_SYSTEM_H_
