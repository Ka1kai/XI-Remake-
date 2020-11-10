//----------------------------------------------------
// CTitleBackManager Header
//	タイトルの背景処理の管理クラス
//
// @author T.Kawashita
//----------------------------------------------------
#ifndef _C_TITLE_BACK_MANAGER_H_
#define _C_TITLE_BACK_MANAGER_H_

#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/2D/C2DSpriteAlphaBlend.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/CObjectBase.hpp"

#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"

class CTitleBackManager
{
private:
	C2DSpriteAlphaBlend*		m_pAlphaBlend;

	C2DSpriteAlphaBlend*		m_pTitleBack;
	LPSTR						m_pResTitleBackFilePath;

	C2DSpriteAlphaBlend*		m_pPushStartPlay;
	LPSTR						m_pResPushStartPlayFilePath;

	C2DSpriteAlphaBlend*		m_pTitleLogo;
	LPSTR						m_pResTitleLogoFilePath;		

	C2DSpriteAlphaBlend*		m_pTitleRemake;
	LPSTR						m_pResTitleRemakeFilePath;

private:
	bool						m_isFade;	// フェードのフラグ

public:
	CTitleBackManager	( void );
	~CTitleBackManager	( void );

public:
	void	Run			( void );
	void	Draw		( void );
	void	Init		( void );
	void	Uninit		( void );

	//----------------------------------------------------
	// Titleのフェード
	//----------------------------------------------------
	bool	Fade		( void );

	//----------------------------------------------------
	// Fadeフラグのセット 
	// @data	isFade
	// return	none
	//----------------------------------------------------
	void	SetIsFade	( bool isFade )
	{
		m_isFade = isFade;
	}

	//----------------------------------------------------
	// Fadeフラグのゲット
	// @data	none
	// @return	isFade 
	//----------------------------------------------------
	bool	GetIsFade	( void )
	{
		return m_isFade;
	}
	
};

#endif _C_TITLE_BACK_MANAGER_H_