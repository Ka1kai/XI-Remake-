//----------------------------------------------------
// C2DSprite
//　2Dの板ポリゴン(3D座標)
//
// @date	2013/12/12
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_2D_SPRITE_H_
#define _C_2D_SPRITE_H_

#include <d3dx9.h>
#include "../CObjectBase.hpp"

// 頂点フォーマット
typedef struct TAGtSPRITE
{
	D3DXVECTOR3	pos;
	D3DCOLOR	diffuse;
	float		tu,tv;
}tagTSPRITE;

class C2DSprite : public CObjectBase
{
private:
	D3DXVECTOR3	m_pos;			// 位置座標
	D3DXVECTOR3	m_size;			// スプライトの大きさ

protected:
	tagTSPRITE	m_vertex[4];	// 頂点座標

public:
	// コンストラクタ
	C2DSprite			( void );

	// デストラクタ
	virtual ~C2DSprite	( void );

	//----------------------------------------------------
	// 頂点情報の取得
	//----------------------------------------------------
	tagTSPRITE*	GetVertex	( void )
	{
		return m_vertex;
	}

	//----------------------------------------------------
	// 位置情報の取得
	//----------------------------------------------------
	CONST D3DXVECTOR3*	GetPos		( void )
	{
		return &m_pos;
	}

	//----------------------------------------------------
	// スプライトの大きさの取得
	//----------------------------------------------------
	CONST D3DXVECTOR3*	GetSize		( void )
	{
		return &m_size;
	}

	//----------------------------------------------------
	// @name	SetSprite
	// @content	スプライトのセット
	// @param	pos		位置座標
	// @param	size	サイズ
	// @return	none
	// @date	2013/12/18
	//----------------------------------------------------
	bool	SetSprite		( CONST D3DXVECTOR3* pos, CONST D3DXVECTOR3* size );

	//----------------------------------------------------
	// @name	SetSpritePos
	// @content	スプライトの位置のセット(3次元空間上)
	// @param	x		x座標位置
	// @param	y		y座標位置
	// @param	z		z座標位置
	// @return	none
	// @date	2013/12/13
	//----------------------------------------------------
	void	SetSpritePos	( CONST float x, CONST float y, CONST float z );

	//----------------------------------------------------
	// @name	MoveSpritePos
	// @content	スプライトの位置移動
	// @param	x		X移動量
	// @return	y		y移動量
	// @date	z		z移動量
	// @update	2013/12/18
	//----------------------------------------------------
	void	MoveSpritePos	( CONST float x, CONST float y, CONST float z );

	//----------------------------------------------------
	// @name	MoveSpritePos
	// @content	スプライトの位置移動(vector指定)
	// @param	vec		位置ベクトル
	// @return	none
	// @date	2013/12/18
	//----------------------------------------------------
	void	MoveSpritePos	( CONST D3DXVECTOR3*	vec );

	//----------------------------------------------------
	// @name	SetSpritSize
	// @content	スプライトのサイズをセット
	// @param	xSize	横幅
	// @param	ySize	縦幅
	// @return	none
	// @date	2013/12/13
	//----------------------------------------------------
	void	SetSpriteSize	( CONST float xSize, CONST float ySize );

	//----------------------------------------------------
	// @name	SetVertexPos	
	// @content	頂点の位置のセット（サイズに依存）
	// @param	none
	// @return	none
	// @date	2013/12/13
	//----------------------------------------------------
	void	SetVertexPos	( void );

	//----------------------------------------------------
	// @name	SetUV	
	// @content	テクスチャ座標のセット
	// @param	none
	// @return	none
	// @date	2013/12/12
	//----------------------------------------------------
	void	SetUV			( void );

	//----------------------------------------------------
	// @name	SetUV
	// @content	テクスチャ座標のセット(パターン数を設定)
	// @param	uPatern		横パターン数
	// @param	vPatern		縦パターン数
	// @param	uNum		横の番号
	// @param	vNum		縦の番号
	// @return	none
	// @date	2013/12/13
	//----------------------------------------------------
	void	SetUV			( CONST UINT uPatern, CONST UINT vPatern, CONST UINT uNum, CONST UINT vNum );

	//----------------------------------------------------
	// @name	SetDiffuse
	// @content	頂点色の設定
	// @param	r		赤値( 0 ～ 255 )
	// @param	g		緑値( 0 ～ 255 )
	// @param	b		青値( 0 ～ 255 )
	// @param	a		α値( 0 ～ 255 )
	// @return	none	
	// @date	2014/1/128
	//----------------------------------------------------
	void	SetDiffuse		( CONST UINT r, CONST UINT g, CONST UINT b, CONST UINT a );

	//----------------------------------------------------
	// @name	CalcWorldMtx
	// @content	板ポリゴンの行列をワールド空間上の行列に変換
	// @param	none
	// @return	none
	// @date	2013/12/12
	//----------------------------------------------------
	void	CalcWorldMtx	( void );
};

#endif _C_2D_SPRITE_H_