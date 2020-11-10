//----------------------------------------------------
// CGraphicsAnime Header
//　アニメーションのモデル
//
// @author T.Kawashita
//----------------------------------------------------
#ifndef _C_GRAPHICS_ANIME_H_
#define _C_GRAPHICS_ANIME_H_

#include "CDirectGraphics3DBase.h"

//----------------------------------------------------
// 体のパーツ
//----------------------------------------------------
enum
{
	HIP,
	BODY,
	HEAD,
	ARMR0,
	ARML0,
	LEGR0,
	LEGL0,
	ARMR1,
	ARML1,
	LEGR1,
	LEGL1,
	PARTSMAX
};

//----------------------------------------------------
// 体の構造体
//----------------------------------------------------
struct _3DObjectInitData
{
	int		parentObjectNo;
	int		ModelNo;
};

class CGraphicsAnime : public CDirectGraphics3DBase
{
private:
	D3DVECTOR			m_initPos;
	_3DObjectInitData	m_objData;

public:
	CGraphicsAnime			( void ){}
	virtual ~CGraphicsAnime	( void ){}

public:
	//----------------------------------------------------
	// model番号のセット
	// @data	modelNo
	// @return	none
	//----------------------------------------------------
	void	SetModelNo		( CONST int modelNo )
	{
		m_objData.ModelNo = modelNo;
	}

	//----------------------------------------------------
	// 初期座標のセット 
	// @data	x y z
	// @return none
	//----------------------------------------------------
	void	SetInitPos			( CONST float x,CONST float y,CONST float z )
	{
		m_initPos.x = x;
		m_initPos.y = y;
		m_initPos.z = z;

		this->SetWorldMtx();
	}

	//----------------------------------------------------
	// ワールド座標に初期座標のセット 
	// @data	none
	// @return	none
	//----------------------------------------------------
	void	SetWorldMtx		( void )
	{
		CDirectGraphics3DBase::SetWorldMtx( m_initPos.x,m_initPos.y,m_initPos.z );
		CDirectGraphics3DBase::SetLocalMtx( m_initPos.x,m_initPos.y,m_initPos.z );
	}

	//----------------------------------------------------
	// 親の番号セット
	// @data	parentNo
	// @return	none
	//----------------------------------------------------
	void	SetParentNo		( CONST int parentNo )
	{
		m_objData.parentObjectNo = parentNo;
	}

	//----------------------------------------------------
	//　番号取得 
	// @data	none
	// @return	CONST int
	//----------------------------------------------------
	CONST int GetModelNo	( void )
	{
		return m_objData.ModelNo;
	}

	//----------------------------------------------------
	// 親の番号取得 
	// @data	none
	// @return	CONST int
	//----------------------------------------------------
	CONST int GetParentNo	( void )
	{
		return m_objData.parentObjectNo;
	}
};

#endif _C_GRAPHICS_ANIME_H_