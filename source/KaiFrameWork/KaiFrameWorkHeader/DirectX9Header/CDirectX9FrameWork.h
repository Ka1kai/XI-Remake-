//----------------------------------------------------
// CDirectX9FrameWork Header
//　DirectX9のフレームワーク
//
// @date	2013/4/27	
// @authro	T.Kawashita
//----------------------------------------------------
#ifndef _C_DIRECTX9_FRAMEWORK_H_
#define _C_DIRECTX9_FRAMEWORK_H_

// 内部インポート
#include <windows.h>
#include <mmsystem.h>
#include <d3dx9.h>

// 外部インポート
#include "../../KaiFrameWorkHeader/WindowsHeader/CWindowSystem.h"
#include "../UtilityHeader/Macro.hpp"
#include "../DebugHeader/CDebugConsole.hpp"

// DXライブラリ読み込み
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")

class CDirectX9FrameWork
{
public:
	CDirectX9FrameWork		(void);
	~CDirectX9FrameWork		(void);

public:
	// シングルトンでグローバル制御
	static LPDIRECT3D9&	Getpd3d	( void )
	{
		static LPDIRECT3D9 m_pd3d;
		return m_pd3d;
	}

	// シングルトンでデバイスポインタをグローバル制御
	static LPDIRECT3DDEVICE9& Getpd3dDevice	( void )
	{
		static LPDIRECT3DDEVICE9 m_pd3dDevice;
		return m_pd3dDevice;
	}

public:
	//----------------------------------------------------
	// @name	Init
	// @content	DirectX9の初期化
	// @param	none
	// @return	HRESULT	成功か失敗
	// @date	2013/5/20
	//----------------------------------------------------	
	HRESULT Init	(void);

};

#endif _C_DIRECTX9_FRAMEWORK_H_
