//----------------------------------------------------
// CDirectX9FrameWork Header
//�@DirectX9�̃t���[�����[�N
//
// @date	2013/4/27	
// @authro	T.Kawashita
//----------------------------------------------------
#ifndef _C_DIRECTX9_FRAMEWORK_H_
#define _C_DIRECTX9_FRAMEWORK_H_

// �����C���|�[�g
#include <windows.h>
#include <mmsystem.h>
#include <d3dx9.h>

// �O���C���|�[�g
#include "../../KaiFrameWorkHeader/WindowsHeader/CWindowSystem.h"
#include "../UtilityHeader/Macro.hpp"
#include "../DebugHeader/CDebugConsole.hpp"

// DX���C�u�����ǂݍ���
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")

class CDirectX9FrameWork
{
public:
	CDirectX9FrameWork		(void);
	~CDirectX9FrameWork		(void);

public:
	// �V���O���g���ŃO���[�o������
	static LPDIRECT3D9&	Getpd3d	( void )
	{
		static LPDIRECT3D9 m_pd3d;
		return m_pd3d;
	}

	// �V���O���g���Ńf�o�C�X�|�C���^���O���[�o������
	static LPDIRECT3DDEVICE9& Getpd3dDevice	( void )
	{
		static LPDIRECT3DDEVICE9 m_pd3dDevice;
		return m_pd3dDevice;
	}

public:
	//----------------------------------------------------
	// @name	Init
	// @content	DirectX9�̏�����
	// @param	none
	// @return	HRESULT	���������s
	// @date	2013/5/20
	//----------------------------------------------------	
	HRESULT Init	(void);

};

#endif _C_DIRECTX9_FRAMEWORK_H_
