//----------------------------------------------------
// CModelViewBackManager
//	モデルの背景の管理クラス
//
// @author T.Kawashita
//----------------------------------------------------
#ifndef _C_MODELVIEW_BACK_MANAGER_H_
#define _C_MODELVIEW_BACK_MANAGER_H_

#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/2D/C2DSpriteAlphaBlend.h"

#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"

class CModelViewBackManager
{
private:
	C2DSpriteAlphaBlend	*m_pModelViewBack;

private:
	bool					m_isFade;

public:
	CModelViewBackManager	( void );
	~CModelViewBackManager	( void );

public:
	void	Run		( void );
	void	Draw	( void );
	void	Init	( void );
	void	Uninit	( void );

public:
	//----------------------------------------------------
	// Fade
	// @data	none
	// @return	bool
	//----------------------------------------------------
	bool	Fade	( void );

	//----------------------------------------------------
	// フェードのフラグセット 
	// @data	isFade
	// @return	none
	//----------------------------------------------------
	void	SetIsFade	( bool isFade )
	{
		m_isFade = isFade;
	}

	//----------------------------------------------------
	// フェードのフラグゲット 
	// @data	none
	// @return	m_isFade
	//----------------------------------------------------
	bool	GetIsFade	( void )
	{
		return m_isFade;
	}

};

#endif _C_MODELVIEW_BACK_MANAGER_H_