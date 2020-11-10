//----------------------------------------------------
// CPlayerManager 
//	プレイヤーの管理クラス
//
// @date	2013/12/12
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_PLAYER_MANAGER_H_
#define _C_PLAYER_MANAGER_H_

#include <d3dx9.h>
#include "CPlayer.h"

#include "../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CInputKeyboard.hpp"
#include "../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CJoyStick.hpp"
#include "../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"
#include "../SceneSource/DebugScene/CDebugMode.h"
#include "../ManagerSource/GameScene/CDiceObjManager.h"
#include "../ManagerSource/GameScene/CStageBlockManager.h"
#include "../ManagerSource/GameScene/CDiceInfoManager.h"

class CPlayerManager
{
private:
	CPlayer*			m_pPlayer;
	LPSTR				m_pPlayerFilePath;	// プレイヤーの画像ファイルパス
	CDiceInfoManager*	m_pDiceInfoManager;

	// コンストラクタ
	CPlayerManager	( void );
	CPlayerManager	( CONST CPlayerManager& playerManager ){}	// コピーコンストラクタ禁止
	CPlayerManager	operator= ( CONST CPlayerManager& playerManager ){}	// オペレータオーバロード禁止 

public:
	// インスタンス取得場所
	static CPlayerManager* GetInstance( void )
	{
		static CPlayerManager playerManager;
		return &playerManager;
	}

public:

	// デストラクタ
	~CPlayerManager	( void );

	//----------------------------------------------------
	// 初期化
	//----------------------------------------------------
	bool	Init	( void );

	//----------------------------------------------------
	// 終了
	//----------------------------------------------------
	bool	Uninit	( void );

	//----------------------------------------------------
	// 描画
	//----------------------------------------------------
	void	Draw	( void );

	//----------------------------------------------------
	// プレイヤーの処理
	//----------------------------------------------------
	void	Run		( void );

	//----------------------------------------------------
	// @name	Move
	// @content	プレイヤーの移動
	// @param	none
	// @return	none	
	// @date	2013/12/13
	//----------------------------------------------------
	void	Move		( void );

	//----------------------------------------------------
	// 各方向へ移動 
	//----------------------------------------------------
	void	MoveRight	( void );
	void	MoveLeft	( void );
	void	MoveFront	( void );
	void	MoveBack	( void );

	//----------------------------------------------------
	// @name	IsHitPlayerToDiceX,Z
	// @content プレイヤーとダイスの当たり判定
	// @param	distance		調整用値
	// @return	bool			当たっていない状態になったらtrue
	// @date	2014/1/30
	//----------------------------------------------------
	bool	IsHitPlayerToDiceX	( CONST float distance, CDiceObj* dice );
	bool	IsHitPlayerToDiceZ	( CONST float distance, CDiceObj* dice );

	//----------------------------------------------------
	// @name	Down
	// @content	プレイヤーの落下処理	
	// @param	none
	// @return	none
	// @date	2014/1/27
	//----------------------------------------------------
	void	Down		( void );

	//----------------------------------------------------
	// @name	Up
	// @content	プレイヤーの上昇処理	
	// @param	speed		速度
	// @return	none
	// @date	2014/1/31
	//----------------------------------------------------
	void	Up			( CONST float speed );

	//----------------------------------------------------
	// @name	SetCameraToMtx
	// @content	カメラの行列をプレイヤーの行列にセット
	// @param	view		カメラ行列
	// @return	none		
	// @date	2013/12/20
	// @update	2014/1/15	引数を一つに設定し直し
	// @update	2014/1/28	引数をなしに設定
	//----------------------------------------------------
	void	SetCameraToMtx	( CONST D3DXMATRIX* view );

	//----------------------------------------------------
	// @name	SetPlayerStatus
	// @content	プレイヤーのステータス変更
	// @param	playerStatus	変更したいステータス
	// @return	none	
	// @date	2014/1/31
	//----------------------------------------------------
	void	SetPlayerStatus	( CONST ePlayerStatus playerStatus )
	{
		m_pPlayer->SetPlayerStatus( playerStatus );
	}

	//----------------------------------------------------
	// @name	SetPlayerPos
	// @content	プレイヤーの位置変更
	// @param	xPos		X座標
	// @param	yPos		Y座標
	// @param	zPos		Z座標
	// @return	none
	// @date	2014/1/31
	//----------------------------------------------------
	void	SetPlayerPos	( CONST float xPos, CONST float yPos, CONST float zPos )
	{
		m_pPlayer->SetSpritePos( xPos, yPos, zPos );
	}

	//----------------------------------------------------
	// プレイヤーのステータス取得
	//----------------------------------------------------
	CONST ePlayerStatus GetPlayerStatus( void )
	{
		return m_pPlayer->GetPlayerStatus();
	}

	//----------------------------------------------------
	// プレイヤーの位置取得
	//----------------------------------------------------
	CONST D3DXVECTOR3* GetPlayerPos( void )
	{
		return m_pPlayer->GetPos();
	}

	//----------------------------------------------------
	// プレイヤーの色変更
	//----------------------------------------------------
	void BrightChange( bool isBright )
	{
		if( isBright == false )
		{
			m_pPlayer->SetDiffuse( 50, 50, 50, 255 );
		}
		else
		{
			m_pPlayer->SetDiffuse( 255, 255, 255, 255 );
		}
	}

	//----------------------------------------------------
	// ＩＮＦＯ用マネージャーのセット
	//----------------------------------------------------
	void SetDiceInfoManager	( CDiceInfoManager* diceInfoManager )
	{
		m_pDiceInfoManager = diceInfoManager;
	}
};


#endif _C_PLAYER_MANAGER_H_