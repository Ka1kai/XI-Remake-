//----------------------------------------------------
// CDiceInfoObj 
//	ダイスINFO用のオブジェクト
//
// @date	2014/2/13
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_DICE_INFO_OBJ_H_
#define _C_DICE_INFO_OBJ_H_

#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/3D/C3DObjectAlphaBlend.h"

class CDiceInfoObj : public C3DObjectAlphaBlend
{
private:
	bool	m_isExist;

public:
	void	SetIsExist	( bool isExist )
	{
		m_isExist = isExist;
	}
	bool	GetIsExist	( void )
	{
		return m_isExist;
	}

public:
	CDiceInfoObj	( void );	// コンストラクタ
	~CDiceInfoObj	( void );	// デストラクタ

public:
	bool	Init			( void );	// 初期化
	void	CopyRotationMtx	( CONST D3DXMATRIX* worldMtx );	// 回転行列をコピーしてワールド行列にセット
};

#endif _C_DICE_INFO_OBJ_H_