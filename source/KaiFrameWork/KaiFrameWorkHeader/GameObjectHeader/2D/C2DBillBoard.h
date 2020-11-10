//----------------------------------------------------
// C2DBillBoard 
//	ビルボードのクラス
//
// @date	2013/12/18
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_2D_BILLBOARD_H_
#define _C_2D_BILLBOARD_H_

#include <Windows.h>
#include <d3dx9.h>

#include "C2DSprite.h"

// 自作色情報構造体
typedef struct TAGtCOLOR
{
	int		red;
	int		green;
	int		blue;
	int		alpha;
}tagTCOLOR;

class C2DBillBoard : public C2DSprite
{
private:
	tagTCOLOR			m_color;	// 色情報

public:
	// コンストラクタ
	C2DBillBoard		( void );

	// デストラクタ
	~C2DBillBoard		( void );

public:
	//----------------------------------------------------
	// @name	SetVertexColor
	// @content	色を頂点にセット
	// @param	none
	// @return	none
	// @date	2013/12/18
	//----------------------------------------------------	
	void	SetVertexColor	( void );

	//----------------------------------------------------
	// @name	SetColor
	// @content	色をまとめてセット
	// @param	r		赤値( 0 ~ 255 )
	// @param	g		緑値( 0 ~ 255 )
	// @param	b		青値( 0 ~ 255 )
	// @param	a		α値 ( 0 ~ 255 )
	// @return	none
	// @date	2013/12/18
	//----------------------------------------------------
	void	SetColor	( CONST UINT r, CONST UINT g, CONST UINT b, CONST UINT a );

	//----------------------------------------------------
	// @name	SetColor
	// @content	色の個別セット(　各色ごとにわかれている )
	// @param	color		色( 各色ごと 0 ~ 255 )
	// @return	none
	// @date	2013/12/18
	//----------------------------------------------------
	void SetColorRed	( CONST UINT red )
	{
		m_color.red = red;
		this->SetVertexColor();
	}
	void SetColorGreen	( CONST UINT green )
	{
		m_color.green = green;
		this->SetVertexColor();
	}
	void SetColorBlue	( CONST UINT blue )
	{
		m_color.blue = blue;
		this->SetVertexColor();
	}
	void SetColorAlfa	( CONST UINT alpfa )
	{
		m_color.alpha;
		this->SetVertexColor();
	}
	
	//----------------------------------------------------
	// @name	CalcWorldMtx
	// @content	ワールド行列をビルボード用の行列にセットする
	// @param	cameraView		カメラのビュー行列
	// @return	none
	// @date	2013/12/18
	//----------------------------------------------------
	void CalcWorldMtx	( CONST D3DXMATRIX* cameraView );

};

#endif _C_2D_BILLBOARD_H_