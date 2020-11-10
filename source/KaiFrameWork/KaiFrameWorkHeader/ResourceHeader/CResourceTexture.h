//----------------------------------------------------
// CResourceTexture	 
//	2Dテクスチャー
//
// @date	2013/12/5
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_RESOURCE_TEXTURE_H_
#define _C_RESOURCE_TEXTURE_H_

#include <d3dx9.h>

#include "../DirectX9Header/CDirectX9FrameWork.h"
#include "../UtilityHeader/Macro.hpp"
#include "../DebugHeader/CDebugConsole.hpp"

class CResourceTexture
{
private:
	LPDIRECT3DTEXTURE9	m_pTexture;

public:
	// コンストラクタ
	CResourceTexture			( void );

	// デストラクタ
	virtual ~CResourceTexture	( void );

public:
	//----------------------------------------------------
	// @name	Load
	// @content	テクスチャーのロード
	// @param	filePath	ファイルパス
	// @return	bool		成功か失敗
	// @date	2013/12/5
	//----------------------------------------------------
	bool	Load		( CONST LPSTR filePath );

	//----------------------------------------------------
	// テクスチャデータ取得 
	//----------------------------------------------------
	CONST LPDIRECT3DTEXTURE9	Get	(void)
	{
		return m_pTexture;
	}
};


#endif _C_RESOURCE_TEXTURE_H_