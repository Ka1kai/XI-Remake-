//----------------------------------------------------
// 3DObjectShape 
//	経常描画のためのヘッダー
//	スフィア，ボックス
//
// @date	2013/7/10
// @author  T.Kawashita
//----------------------------------------------------
#ifndef _C_3D_OBJECT_SHAPE_H_
#define _C_3D_OBJECT_SHAPE_H_

#include <d3dx9.h>

#include "../../DirectX9Header/CDirectX9FrameWork.h"
#include "../CObjectBase.hpp"

class C3DObjectShape : public CObjectBase
{
private:
	LPD3DXMESH		m_pMesh;			// メッシュデータ
	D3DMATERIAL9	m_materials;		// マテリアルデータ

public:
	C3DObjectShape				( void );
	virtual ~C3DObjectShape		( void );

	//----------------------------------------------------
	// @name	CreateSphere
	// @content	スフィアの生成
	// @param	radius		半径
	// @return	bool		作成できたか出来なかったか
	// @date	2013/7/10
	//----------------------------------------------------
	bool	CreateSphere	( CONST float radius );

	//----------------------------------------------------
	// @name	CreateBox
	// @content	ボックスの生成
	// @param	size		大きさ
	// @return	bool		作成できたか出来なかったか
	// @date	2013/7/10
	//----------------------------------------------------
	bool	CreateBox		( CONST D3DXVECTOR3* size );

	//----------------------------------------------------
	// @name	SetDiffuse
	// @content	ディフューズ色の設定
	// @param	r			赤値( 0 ～ 255 )
	// @param	g			緑値( 0 ～ 255 )
	// @param	b			青値( 0 ～ 255 )
	// @param	a			α値	( 0 ～ 255 )
	// @return	none
	// @date	2013/7/10
	// @update	2013/12/17	引数の値をUINT型にし 1.0から255対応
	//----------------------------------------------------
	void	SetDiffuse		( CONST UINT r, CONST UINT g, CONST UINT b, CONST UINT a );

	//----------------------------------------------------
	// @name	SetAmbient
	// @content	アンビエント色の設定
	// @param	r			赤値( 0 ～ 255 )
	// @param	g			緑値( 0 ～ 255 )
	// @param	b			青値( 0 ～ 255 )
	// @param	a			α値	( 0 ～ 255 )
	// @return	none
	// @date	2013/710
	// @update	2013/12/17	引数の値をUINT型にし 1.0から255対応
	//----------------------------------------------------
	void	SetAmbient		( CONST UINT r, CONST UINT g, CONST UINT b, CONST UINT a );

	//----------------------------------------------------
	// メッシュデータの取得
	// @data	none
	// @return	LPD3DXMESH
	//----------------------------------------------------
	CONST LPD3DXMESH	GetMesh	( void )
	{
		return m_pMesh;
	}

	//----------------------------------------------------
	// マテリアルデータの取得
	// @data	none
	// @return	D3DMATRIAL9*
	//----------------------------------------------------
	CONST D3DMATERIAL9*	GetMaterial	( void )
	{
		return &m_materials;
	}
};

#endif _C_3D_OBJECT_SHAPE_H_