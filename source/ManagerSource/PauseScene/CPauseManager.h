//----------------------------------------------------
// CPauseManager Header 
//　ポーズの管理クラス
//
// @author T.Kawashita
//----------------------------------------------------
#ifndef _C_PAUSE_MANAGER_H_
#define _C_PAUSE_MANAGER_H_

#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CInputKeyboard.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CJoyStick.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"

#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/2D/C2DSpriteAlphaBlend.h"

typedef enum PAUSE_STATUS
{
	RESUME,
	RETRY,
	TITLE,
	GAMEOVER
}ePauseStatus;

class CPauseManager
{
private:
	C2DSpriteAlphaBlend		*m_pPauseBack;
	LPSTR					m_pResPauseBackFilePath;
	C2DSpriteAlphaBlend		*m_pPause;
	LPSTR					m_pResPauseFilePath;
	C2DSpriteAlphaBlend		*m_pRetry;
	LPSTR					m_pResRetryFilePath;
	C2DSpriteAlphaBlend		*m_pResume;
	LPSTR					m_pResResumeFilePath;
	C2DSpriteAlphaBlend		*m_pTitle;
	LPSTR					m_pResTitleFilePath;
	

	C2DSpriteRHW			*m_pCursol;
	LPSTR					m_pResCursolFilePath;
	C2DSpriteAlphaBlend		*m_pPauseEffect;
	LPSTR					m_pResPauseEffectFilePath;

private:
	bool					m_isPause;			// ポーズのフラグ
	ePauseStatus			m_ePauseState;		// ポーズのステータス

public:	
	CPauseManager			( void );	// コンストラクタ
	~CPauseManager			( void );	// デストラクタ

public:
	void	Draw			( void );
	void	Run				( void );
	void	Init			( void );
	void	InitPause		( void );
	void	Uninit			( void );

public:
	//----------------------------------------------------
	// @name	GetIsPause
	// @content	ポーズのフラグ
	// @param	none
	// @return	bool		ポーズ中かどうか
	// @date	2014/2/12
	//----------------------------------------------------
	bool		GetIsPause		( void )
	{
		return m_isPause;
	}

	//----------------------------------------------------
	// @name	SetisPause
	// @content	ポーズ中かどうかのセット
	// @param	bool	ポーズ中かどうか
	// @return	none
	// @date	2014/2/12
	//----------------------------------------------------
	void		SetIsPause		( bool isPause )
	{
		m_isPause = isPause;
	}

	//----------------------------------------------------
	// @name	SetIsPause
	// @content	ポーズ中かどうかのセット（入れ替え）
	// @param	none
	// @return	none
	// @date	2014/2/12
	//----------------------------------------------------
	void		SetIsPause		( void )
	{
		m_isPause ^= true;
	}

	//----------------------------------------------------
	// @name	GetPauseState
	// @content	ポーズのステータスをセット
	// @param	none	
	// @return	ePauseState		ポーズのステータス
	// @date	2014/2/12
	//----------------------------------------------------
	ePauseStatus	GetPauseState	( void )
	{
		return m_ePauseState;
	}

};

#endif _C_PAUSE_MANAGER_H_