//----------------------------------------------------
// C2DSpriteRHW
//	2Dポリゴンを描画するためのもの
//  同次座標計算をしている
//
// @date	2013/8/10
// @author T.Kawashita
//----------------------------------------------------
#ifndef _C_2D_SPRITE_RHW_H_
#define _C_2D_SPRITE_RHW_H_

#include <d3dx9.h>

// Sprite(同次座標あり)頂点データ構造体
typedef struct TAGtSPRITERHW
{
	D3DXVECTOR3	pos;		// 頂点の座標
	float		rhw;		// スクリーン座標変換
	D3DCOLOR	diffuse;	// 頂点の色
	float		tu, tv;		// テクスチャ座標
}tagTSPRITERHW;

class C2DSpriteRHW
{
private:
	tagTSPRITERHW	m_vertex[4];	// 頂点データ

protected:
	D3DXVECTOR2		m_center;		// 中心座標
	D3DXVECTOR2		m_halfSize;		// 半分のサイズ
	D3DXVECTOR2		m_size;			// サイズ

public:
	C2DSpriteRHW			( void );				
	virtual	~C2DSpriteRHW	( void );	

	//----------------------------------------------------
	// 頂点座標の取得 
	//----------------------------------------------------
	tagTSPRITERHW*	GetVertex	( void )
	{
		return m_vertex;
	}

	//----------------------------------------------------
	// 中心座標をゲット
	//----------------------------------------------------
	D3DXVECTOR2*	GetCenter		( void )
	{
		return &m_center;
	}

	//----------------------------------------------------
	// 初期化
	//----------------------------------------------------
	bool			Init			( void );

public:
	//----------------------------------------------------
	// @name	SetVertexPos
	// @content	頂点座標のセット(中心座標とサイズを指定）
	// @param	centerX		中心X座標
	// @param	centerY		中心Y座標
	// @param	width		横幅
	// @param	height		縦幅
	// @return	none
	// @date	2013/8/10
	//----------------------------------------------------
	void		SetVertexPos	( CONST float centerX, CONST float centerY, CONST float width, CONST float height );
	
	//----------------------------------------------------
	// @name	SetVertexPos
	// @content	頂点座標のセット(中心座標を指定)
	// @param	centerX		中心X座標
	// @param	centerY		中心Y座標
	// @return	none
	// @date	2013/8/10
	//----------------------------------------------------
	void		SetVertexPos	( CONST float centerX, CONST float centerY );

	//----------------------------------------------------
	// @name	SetVertexPos
	// @content	頂点座標のセット(中心座標をD3DXVECTOR2型でセット)
	// @param	center		中心座標
	// @return	none
	// @date	2013/8/10
	//----------------------------------------------------
	void		SetVertexPos	( CONST D3DXVECTOR2* center );

	//----------------------------------------------------
	// @name	SetUV
	// @content	テクスチャ座標のセット
	// @param	none
	// @return	none
	// @date	2013/12/13
	//----------------------------------------------------
	void		SetUV		( void );

	//----------------------------------------------------
	// @name	SetUV
	// @content	テクスチャ座標のセット
	// @param	uPatern		横のパターン数
	// @param	vPatern		縦のパターン数
	// @param	uNum		横の番号
	// @param	vNum		縦の番号
	// @return	none
	// @date	2013/8/10
	//----------------------------------------------------
	void		SetUV		( CONST UINT uPatern, CONST UINT vPatern, CONST UINT uNum, CONST UINT vNum );
	
	//----------------------------------------------------
	// @name	SetDiffuse
	// @content	頂点の色セット
	// @param	r			赤値( 0 ～ 255 )
	// @param	g			緑値( 0 ～ 255 )
	// @param	b			青値( 0 ～ 255 )
	// @param	a			α値 ( 0 ～ 255 )
	// @return	none	
	// @date	2013/8/11
	// @update	2013/12/13	引数をUINT型に設定
	//----------------------------------------------------	
	void		SetDiffuse		( CONST UINT r, CONST UINT g, CONST UINT b, CONST UINT a );

	//----------------------------------------------------
	// α値の取得 
	//----------------------------------------------------
	int			GetAlpha	( void )
	{
		return ( m_vertex[0].diffuse >> 24 );
	}
	
};

#endif _C_2D_SPRITE_RHW_H_