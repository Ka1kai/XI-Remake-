//----------------------------------------------------
// CResourceXFile
//	Xファイルリソース
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
	LPD3DXMESH			m_pMesh;				// メッシュ格納場所
	DWORD				m_materialsCount;		// メッシュのマテリアル情報の数（32bit符号なし整数）
	LPD3DXBUFFER		m_pMaterialsBuffer;		// マテリアル情報の取得場所	
	LPDIRECT3DTEXTURE9	*m_pMeshTexture;		// テクスチャ格納場所
	D3DMATERIAL9		*m_pMeshMaterials;		// 個々のマテリアル情報

public:
	CResourceXFile	( void );
	virtual ~CResourceXFile	( void );

public:
	HRESULT		SetMaterials	( void );			// マテリアル設定関数
	HRESULT		Load			( CONST LPSTR filePath );	// Xファイルロード関数
	void		Destroy			( void );			// Xファイル情報解放関数

public:
	//----------------------------------------------------
	// マテリアルの情報の数取得 
	//----------------------------------------------------
	CONST DWORD			GetMaterialCount( void )
	{
		return m_materialsCount;
	}
	
	//----------------------------------------------------
	// 個々のマテリアル情報取得
	//----------------------------------------------------
	CONST D3DMATERIAL9* GetMeshMaterial	( void )
	{ 
		return m_pMeshMaterials;
	} 

	//----------------------------------------------------
	// テクスチャ情報取得 
	//----------------------------------------------------
	CONST LPDIRECT3DTEXTURE9* GetMeshTexture	( void )
	{ 
		return m_pMeshTexture;
	}
	
	//----------------------------------------------------
	// メッシュ情報取得
	//----------------------------------------------------
	CONST LPD3DXMESH	GetMesh	( void )	
	{ 
		return m_pMesh;
	}


};

#endif _C_RESOURCE_XFILE_H_