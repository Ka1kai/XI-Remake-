//----------------------------------------------------
// CResourceManager 
//	リソースを管理・保持するクラス
//
// @date	2013/12/5
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_RESOURCE_MANAGER_H_
#define _C_RESOURCE_MANAGER_H_

#include <d3dx9.h>
#include <map>
#include <string>

#include "CResourceXFile.h"
#include "CResourceTexture.h"
#include "CResourceXFont.h"

#include "CResourcePath.hpp"

using namespace std;

class CResourceManager
{
private:
	CResourceManager()
	{
	}
	CResourceManager( CONST CResourceManager& obj ){}
	CResourceManager& operator=( CONST CResourceManager& obj ){}

public:
	//インスタンスの取得（シングルトン）
	static CResourceManager* GetInstance()
	{
		static CResourceManager resourceManager;
		return &resourceManager;
	}

private:
	map< LPSTR , CResourceTexture* >	m_texturerResource;
	map< LPSTR , CResourceXFile* >		m_xFileResource;
	map< UINT  , CResourceXFont* >		m_xFontResource;

public:
	// デストラクタ
	~CResourceManager	( void );

public:
	//----------------------------------------------------
	// @name	LoadXFile
	// @content	XFileをロードしてMapにセットする
	// @param	resourcePath	リソースのパス
	// @return	bool			成功か失敗
	// @date	2013/12/5
	//----------------------------------------------------
	bool		LoadXFile		( CONST LPSTR resourcePath );

	//----------------------------------------------------
	// @name	GetXFile
	// @content	MapからXFileの取得
	// @param	resourcePath		XFileのパス	
	// @return	CResourceXFile*		XFileのアドレス
	// @date	2013/12/5
	//----------------------------------------------------
	CResourceXFile*	GetXFile	( CONST LPSTR resourcePath );

	//----------------------------------------------------
	// @name	LoadTexture
	// @content	TextureをロードしてMapにセットする
	// @param	resourcePath	Textureのパス
	// @return	bool			成功か失敗	
	// @date	2013/12/5
	//----------------------------------------------------
	bool			LoadTexture		( CONST LPSTR resourcePath );

	//----------------------------------------------------
	// @name	GetTexture	
	// @content	Mapからテクスチャの取得
	// @param	resourcePath		Textureのパス
	// @return	CResourceTexture*	Textureのアドレス	
	// @date	2013/12/5
	//----------------------------------------------------
	CResourceTexture*	GetTexture	( CONST LPSTR resourcePath );

	//----------------------------------------------------
	// @name	CreateFont
	// @content	XFontを作成してMapにセットする
	// @param	xFontNo			どのXFontかを識別する番号
	// @param	width			横幅
	// @param	height			縦幅
	// @return	bool			成功か失敗
	// @date	2013/12/16
	//----------------------------------------------------
	bool		CreateXFont			( CONST UINT xFontNo, CONST UINT width, CONST UINT height );

	//----------------------------------------------------
	// @name	GetXFont
	// @content	XFontのインスタンスの取得
	// @param	xFontNo				Mapに格納しているxFontの番号
	// @return	CResourceXFont*		XFontのインスタンス
	// @date	2013/12/6
	// @update	2013/12/16			引数にNoを追加
	//----------------------------------------------------
	CResourceXFont*		GetXFont	( CONST UINT xFontNo );

	//----------------------------------------------------
	// @name	Relese
	// @content	Mapの情報を全てリリース
	// @param	none
	// @return	none	
	// @date	2013/12/5
	//----------------------------------------------------
	void	Relese				( void );

	//----------------------------------------------------
	// @name	Relese
	// @content	Mapの情報をファイルパスで指定解放
	// @param	resourcePath		ファイルのパス
	// @return	none	
	// @date	2013/12/5
	//----------------------------------------------------
	void	Relese				( CONST LPSTR resourcePath );

};

#endif _C_RESOURCE_MANAGER_H_