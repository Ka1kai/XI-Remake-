//----------------------------------------------------
// CModeSelectPlayerManager 
//	モードセレクト画面のプレイヤーのマネージャー
//	
// @date	2014/2/7
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_MODESELECT_PLAYER_MANAGER_
#define _C_MODESELECT_PLAYER_MANAGER_

#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/2D/C2DSprite.h"

//----------------------------------------------------
// モードセレクト用プレイヤー移動ステータス
//----------------------------------------------------

typedef enum EMoveSelectMovePlayerStatus
{
	eModeSelectPlayerMoveNone,
	eModeSelectPlayerMoveRight,
	eModeSelectPlayerMoveLeft,
	eModeSelectPlayerMoveUp,
	eModeSelectPlayerMoveDown,
}eModeSelectMovePlayerStatus;

class CModeSelectPlayerManager
{
private:
	C2DSprite*		m_pModeSelectPlayer;
	LPSTR			m_pResModeSelectPlayerPath;

	eModeSelectMovePlayerStatus		m_eMovePlayerStatus;
	float			m_moveValue;	// 動いた量

public:
	CModeSelectPlayerManager	( void );
	~CModeSelectPlayerManager	( void );

public:
	// プレイヤーのステータスをセット
	void	SetMovePlayerStatus		( CONST eModeSelectMovePlayerStatus playerStatus )
	{
		m_eMovePlayerStatus = playerStatus;
	}

	// プレイヤーのステータスを取得
	eModeSelectMovePlayerStatus GetMovePlayerStatus	( void )
	{
		return m_eMovePlayerStatus;
	}

public:
	bool	Init		( void );
	void	Run			( void );
	void	Draw		( void );
	bool	Uninit		( void );

public:
	void	MoveRight	( CONST float speed );
	void	MoveLeft	( CONST float speed );
	void	MoveUp		( CONST float speed );
	void	MoveDown	( CONST float speed );

};


#endif _C_MODESELECT_PLAYER_MANAGER_