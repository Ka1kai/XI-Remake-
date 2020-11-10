//----------------------------------------------------
// CXFont 
//	DirectXを使用した文字作成
//
// @date	2013/6/20
// @update	2013/12/6
// @author	T.kawashita
//----------------------------------------------------
#ifndef _C_RESOURCE_XFONT_H_
#define _C_RESOURCE_XFONT_H_

#include <d3dx9.h>

#include "../DirectX9Header/CDirectX9FrameWork.h"
#include "../UtilityHeader/Macro.hpp"

class	CResourceXFont
{
private:
	LPD3DXFONT	m_pFont;
	D3DXCOLOR	m_color;

public:
	// コンストラクタ
	CResourceXFont	(void);

	// デストラクタ
	virtual ~CResourceXFont	(void);

	//----------------------------------------------------
	// @name	Create
	// @content	フォントの作成
	// @param	width		1文字の横幅
	// @param	height		1文字の高さ
	// @return	作成できたかどうか
	// @date	2013/6/20
	//----------------------------------------------------
	HRESULT Create( CONST UINT width, CONST UINT height );

	//----------------------------------------------------
	// @name	SetColor
	// @content	フォントの色の設定
	// @param	color		フォントの色
	// @return	none
	// @date	2013/12/6
	//----------------------------------------------------
	void	SetColor	( CONST D3DXCOLOR color );

	//----------------------------------------------------
	// @name	OutPutStringArgList
	// @content	可変引数に変換
	// @param	str			文字列
	// @param	argList		可変引数配列
	// @return	char*		変換した文字列
	// @date	2013/12/6
	//----------------------------------------------------
	inline char* OutPutStringArgList	( char* buff ,CONST LPSTR str, va_list argList );

	//----------------------------------------------------
	// @name	DrawColor
	// @content	カラーを変更しながらのテキストの描画
	// @param	xPos			X座標
	// @param	yPos			Y座標
	// @param	color			色情報
	// @param	str				描画したい文字列
	// @return	none
	// @date	2013/6/20
	// @update	2013/12/6		可変引数に変更
	//----------------------------------------------------
	void	DrawColor	( CONST long xPos, CONST long yPos, CONST D3DXCOLOR color, CONST LPSTR str,... );

	//----------------------------------------------------
	// @name	Draw
	// @content	テキストの描画
	// @param	xPos			X座標
	// @param	yPos			Y座標
	// @param	str				描画したい文字列
	// @return	none
	// @date	2013/12/6		
	//----------------------------------------------------
	void	Draw	( CONST long xPos, CONST long yPos, CONST LPSTR str,... );
};

#endif _C_RESOURCE_XFONT_H_