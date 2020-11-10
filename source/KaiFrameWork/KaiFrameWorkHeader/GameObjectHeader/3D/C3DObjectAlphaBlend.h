//----------------------------------------------------
// C3DObjectAlphaBlend 
//	αブレンドする必要があるObject
//
// @date	2013/12/4
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_3D_OBJECT_ALPHABLEND_H_
#define _C_3D_OBJECT_ALPHABLEND_H_

#include <d3dx9.h>
#include "../CObjectBase.hpp"

class C3DObjectAlphaBlend : public CObjectBase
{
private:
	D3DXCOLOR	m_color;		// 色情報

public:

	// コンストラクタ
	C3DObjectAlphaBlend				( void );
	
	// デストラクタ
	virtual	~C3DObjectAlphaBlend	( void );

	//----------------------------------------------------
	// 初期化
	//----------------------------------------------------
	bool		Init	( void );

	//----------------------------------------------------
	// @name	SetColor	
	// @content	色の設定
	// @param	r		赤値( 0 ~ 255 )
	// @param	g		緑値( 0 ~ 255 )
	// @param	b		青値( 0 ~ 255 )
	// @return	none
	// @date	2013/12/17
	//----------------------------------------------------
	void		SetColor		( CONST UINT r, CONST UINT g, CONST UINT b, CONST UINT a );
	
	//----------------------------------------------------
	// @name	GetColor
	// @content	色の取得
	// @param	none
	// @return	D3DXCOLOR*		色情報
	// @date	2013/12/4
	//----------------------------------------------------
	D3DXCOLOR*	GetColor		( void );

};

#endif _C_3D_OBJECT_ALPHABLEND_H_