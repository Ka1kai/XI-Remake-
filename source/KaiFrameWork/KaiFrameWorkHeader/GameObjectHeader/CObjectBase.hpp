//----------------------------------------------------
// CObjectBase 
//	Objectの基底クラス(2D 3D両方対応)
//
// @date	2013/12/12
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_OBJECT_BASE_H_
#define _C_OBJECT_BASE_H_

#include <d3dx9.h>

class CObjectBase
{
protected:
	D3DXMATRIX	m_worldMtx;		// ワールド座標

public:
	// コンストラクタ
	CObjectBase				( void )
	{
		D3DXMatrixIdentity( &m_worldMtx );
	}

	// デストラクタ
	virtual ~CObjectBase	( void ){}

public:
	//----------------------------------------------------
	// 初期化
	//----------------------------------------------------
	bool	Init		( void )
	{
		this->InitWorldMtx();

		return true;
	}

	//----------------------------------------------------
	// ワールド行列の取得
	//----------------------------------------------------
	CONST D3DXMATRIX*	GetWorldMtx	( void )
	{
		return &m_worldMtx;
	}

	//----------------------------------------------------
	// ワールド行列を単位行列化
	//----------------------------------------------------
	void InitWorldMtx	( void )
	{
		D3DXMatrixIdentity( &m_worldMtx );
	}

	//----------------------------------------------------
	// @name	SetWorldMtx
	// @content	ワールド行列のセット
	// @param	pInMtx		セットしたいワールド行列
	// @return	none
	// @date	2014/1/27
	//----------------------------------------------------
	void SetWorldMtx	( CONST D3DXMATRIX* pInMtx )
	{
		memcpy( &m_worldMtx, pInMtx, sizeof(D3DXMATRIX) );
	}

	//----------------------------------------------------
	// @name	SetWorldPos
	// @content	ワールド座標のセット	
	// @param	xPos		X座標
	// @param	yPos		Y座標
	// @param	zPos		Z座標
	// @return	none
	// @date	2013/12/12
	//----------------------------------------------------
	void SetWorldPos	( CONST float xPos, CONST float yPos, CONST float zPos )
	{
		m_worldMtx._41 = xPos;
		m_worldMtx._42 = yPos;
		m_worldMtx._43 = zPos;
	}

	//----------------------------------------------------
	// @name	SetWorldPos
	// @content	ワールド座標のセット
	// @param	vec			座標を指定したベクトル
	// @return	none
	// @date	2013/12/18
	//----------------------------------------------------
	void SetWorldPos	( CONST D3DXVECTOR3* vec )
	{
		m_worldMtx._41 = vec->x;
		m_worldMtx._42 = vec->y;
		m_worldMtx._43 = vec->z;
	}

	//----------------------------------------------------
	// @name	SetWorldPos
	// @content	ワールド座標のセット
	// @param	mtx			ワールド座標行列
	// @return	none
	// @date	2014/1/17
	//----------------------------------------------------
	void SetWorldPos	( CONST D3DXMATRIX*	mtx )
	{
		m_worldMtx._41 = mtx->_41;
		m_worldMtx._42 = mtx->_42;
		m_worldMtx._43 = mtx->_43;
	}

	//----------------------------------------------------
	// @name	CalcWorldMtx	
	// @content	2つの行列を混ぜてワールド座標行列に変換
	// @param	mtx1		行列１
	// @param	mtx2		行列２
	// @return	none
	// @date	2013/12/12
	//----------------------------------------------------
	void CalcWorldMtx	( CONST  D3DXMATRIX* mtx1, CONST D3DXMATRIX* mtx2 )
	{
		D3DXMatrixMultiply( &m_worldMtx, mtx1, mtx2 );
	}

	//----------------------------------------------------
	// @name	MoveWorldPos
	// @content ベクトルを指定してワールド座標を移動
	// @param	vec			ベクトル
	// @return	none
	// @date	2013/12/12
	//----------------------------------------------------
	void MoveWorldPos	( CONST D3DXVECTOR3* vec )
	{
		m_worldMtx._41 += vec->x;
		m_worldMtx._42 += vec->y;
		m_worldMtx._43 += vec->z;
	}

	//----------------------------------------------------
	// @name	MoveWorldPos
	// @content	座標を指定してワールド座標を移動
	// @param	x			足すX座標量
	// @param	y			足すY座標量
	// @param	z			足すZ座標量
	// @return	none
	// @date	2013/12/12
	//----------------------------------------------------
	void MoveWorldPos	( CONST float x, CONST float y, CONST float z )
	{
		m_worldMtx._41 += x;
		m_worldMtx._42 += y;
		m_worldMtx._43 += z;
	}

	//----------------------------------------------------
	// 座標の取得
	//----------------------------------------------------
	CONST float GetXPos( void )
	{
		return m_worldMtx._41;
	}
	CONST float GetYPos( void )
	{
		return m_worldMtx._42;
	}
	CONST float GetZPos( void )
	{
		return m_worldMtx._43;
	}
};

#endif _C_OBJECT_BASE_H_