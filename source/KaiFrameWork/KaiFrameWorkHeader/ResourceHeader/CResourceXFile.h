//----------------------------------------------------
// CResourceXFile
//	X�t�@�C�����\�[�X
//
// @date	2013/8/3
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_RESOURCE_XFILE_H_
#define _C_RESOURCE_XFILE_H_

#include <d3dx9.h>

#include "../DirectX9Header/CDirectX9FrameWork.h"
#include "../UtilityHeader/Macro.hpp"
#include "../DebugHeader/CDebugConsole.hpp"


class CResourceXFile
{
private:
	LPD3DXMESH			m_pMesh;				// ���b�V���i�[�ꏊ
	DWORD				m_materialsCount;		// ���b�V���̃}�e���A�����̐��i32bit�����Ȃ������j
	LPD3DXBUFFER		m_pMaterialsBuffer;		// �}�e���A�����̎擾�ꏊ	
	LPDIRECT3DTEXTURE9	*m_pMeshTexture;		// �e�N�X�`���i�[�ꏊ
	D3DMATERIAL9		*m_pMeshMaterials;		// �X�̃}�e���A�����

public:
	CResourceXFile	( void );
	virtual ~CResourceXFile	( void );

public:
	HRESULT		SetMaterials	( void );			// �}�e���A���ݒ�֐�
	HRESULT		Load			( CONST LPSTR filePath );	// X�t�@�C�����[�h�֐�
	void		Destroy			( void );			// X�t�@�C��������֐�

public:
	//----------------------------------------------------
	// �}�e���A���̏��̐��擾 
	//----------------------------------------------------
	CONST DWORD			GetMaterialCount( void )
	{
		return m_materialsCount;
	}
	
	//----------------------------------------------------
	// �X�̃}�e���A�����擾
	//----------------------------------------------------
	CONST D3DMATERIAL9* GetMeshMaterial	( void )
	{ 
		return m_pMeshMaterials;
	} 

	//----------------------------------------------------
	// �e�N�X�`�����擾 
	//----------------------------------------------------
	CONST LPDIRECT3DTEXTURE9* GetMeshTexture	( void )
	{ 
		return m_pMeshTexture;
	}
	
	//----------------------------------------------------
	// ���b�V�����擾
	//----------------------------------------------------
	CONST LPD3DXMESH	GetMesh	( void )	
	{ 
		return m_pMesh;
	}


};

#endif _C_RESOURCE_XFILE_H_