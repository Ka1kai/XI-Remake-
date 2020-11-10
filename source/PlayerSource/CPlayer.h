//----------------------------------------------------
// CPlayer 
//	プレイヤーのクラス
//
// @date	2013/12/4
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_PLAYER_H_
#define _C_PLAYER_H_

#include <d3dx9.h>
#include "../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/2D/C2DBillBoard.h"
#include "../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"
#include "../KaiFrameWork/KaiFrameWorkHeader/GameMathHeader/CCollision.h"
#include "../SceneSource/DebugScene/CDebugMode.h"

// プレイヤーのステータス
typedef enum ePlayerStatus
{
	eOnStage,			// ステージの上にいる状態
	eOnDiceAppear,		// ダイスが出現している上にいる状態
	eOnDiceAppearStart,	// ダイスが出現している上にいる状態
	eOnDiceDelete,		// ダイスが消えている上にいる状態
	eOnDiceDeleteStart, // ダイスの消え始めの上にいる状態
	eOnDice,			// ダイスの上にいる状態
};

// プレイヤーの移動のステータス
typedef enum ePlayerMoveStatus
{
	eMoveDice,
	eMoveRight,
	eMoveLeft,
	eMoveFront,
	eMoveBack,
	eMoveNone
};

class CPlayer : public C2DSprite
{
private:
	THITAABB*			m_pAABB;		// 当たり判定用AABB
	ePlayerStatus		m_status;		// プレイヤーのステータス
	ePlayerMoveStatus	m_moveStatus;	// プレイヤーの移動ステータス

public:
	// 当たり判定用AABBをセット
	void		SetAABB	( void )
	{
		m_pAABB->centerPos.x = this->GetXPos();
		m_pAABB->centerPos.y = this->GetYPos();
		m_pAABB->centerPos.z = this->GetZPos();
	}
	// 当たり判定用AABBを取得
	THITAABB*	GetAABB	( void )
	{
		return m_pAABB;
	}
	
	// プレイヤーのステータスをセット
	void		SetPlayerStatus			( ePlayerStatus status = ePlayerStatus::eOnDice )
	{
		m_status = status;
	}
	// プレイヤーのステータスを取得
	ePlayerStatus		GetPlayerStatus ( void )
	{
		return m_status;
	}

	// プレイヤーの移動ステータスをセット
	void				SetMoveStatus	( ePlayerMoveStatus status = ePlayerMoveStatus::eMoveNone )
	{
		m_moveStatus = status;
	}
	// プレイヤーの移動ステータスを取得
	ePlayerMoveStatus GetMoveStatus	( void )
	{
		return m_moveStatus;
	}

public:
	// コンストラクタ
	CPlayer				( void );

	// デストラクタ
	virtual ~CPlayer	( void );

	// 初期化
	bool	Init		( void );
	bool	Uninit		( void );

	//----------------------------------------------------
	// 移動
	//----------------------------------------------------
	void	MoveFront	( CONST float speed );	// 前移動
	void	MoveBack	( CONST float speed );	// 後移動
	void	MoveRight	( CONST float speed );	// 右移動
	void	MoveLeft	( CONST float speed );	// 左移動
	void	MoveDown	( CONST float speed );	// ダウン処理
	void	MoveUp		( CONST float speed );	// アップ処理

};

#endif _C_PLAYER_H_