//----------------------------------------------------
// CWindowSystem
// ウィンドウを作成 制御するクラス
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

#define WINDOW_MAX_X	( GetSystemMetrics(SM_CXSCREEN) )	// ウィンドウX最大幅
#define WINDOW_MAX_Y	( GetSystemMetrics(SM_CYSCREEN) )	// ウィンドウY最大幅

#define DEFAULT_WINDOW_X	640		// ウィンドウXサイズ初期値
#define DEFAULT_WINDOW_Y	480		// ウィンドウYサイズ初期値

#define WINDOW_CLASS_NAME	"DirectX"

class CWindowSystem
{
private:
	WNDCLASSEX	wc;
	MSG			msg;
	LPSTR		wndName;			// ウィンドウの名前

	short		screenWidth;		// スクリーンXサイズ
	short		screenHeight;		// スクリーンYサイズ

	POINT		clientSize;			// クライアントのサイズ

public:
	// コンストラクタ	
	CWindowSystem	( void );												// ウィンドウの大きさを指定しないウィンドウ作成
	CWindowSystem	( CONST UINT screenWidth, CONST UINT screenHeight );	// ウィンドウの大きさを指定してウィンドウ作成
	CWindowSystem	( CONST bool isFullScr );										// フルスクリーンモード用のウィンドウ作成

	// デストラクタ
	virtual		~CWindowSystem	( void )
	{
		timeEndPeriod(1);
	}

private:
	static		LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
	HRESULT		CreateWnd				( void );
	HRESULT		SetWindowClass			( void );
	void		SetClientSize			( void );				// クライアントサイズの設定

public:
	HRESULT		SetShowWindow		( void );
	BOOL		GetEventMessage		( void );
	BOOL		PeekEventMessage	( void );

public:
	// メッセージを取得
	INT	GetMessageWParam	( void )
	{
		return (int)msg.wParam;
	}

	// シングルトンでウィンドウのハンドルをグローバル制御
	static HWND&	GethWnd	( void )
	{
		static HWND hWnd;
		return hWnd;
	}

};

#endif	_C_WINDOW_SYSTEM_H_
