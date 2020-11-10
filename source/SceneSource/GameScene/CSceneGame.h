	//----------------------------------------------------
// CSceneGame Header
//	ゲームシーン
//
//	@auter T.Kawashita
//----------------------------------------------------
#ifndef _C_SCENE_GAME_H_
#define _C_SCENE_GAME_H_

#include "../../KaiFrameWork/KaiFrameWorkHeader/SceneHeader/CSceneBase.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/SceneHeader/CSceneChange.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CInputKeyboard.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/CObjectBase.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9Camera.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9Light.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CJoyStick.hpp"

// Manager
#include "../../ManagerSource/GameScene/CGameStageManager.h"
#include "../../ManagerSource/GameScene/CStageBlockManager.h"
#include "../../ManagerSource/PauseScene/CPauseManager.h"
#include "../../ManagerSource/GameScene/CTimeManager.h"
#include "../../ManagerSource/GameScene/CScoreManager.h"
#include "../../ManagerSource/GameScene/CDiceInfoManager.h"
#include "../../ManagerSource/GameScene/CDiceObjManager.h"
#include "../../PlayerSource/CPlayerManager.h"
#include "../../UserSource/CUserManager.h"

#include "../DebugScene/CDebugMode.h"
#include "../../GameMathSource/CDiceRandSystem.h"

#include "../../ObjectSource/GameScene/Particle/CSnowObj.h"
#include "../../ObjectSource/GameScene/Particle/CSpaceParticle.h"

typedef enum GAMEPLAY_STATUS
{
	GAME_START,
	GAME_PLAY,
	GAME_PAUSE,
	PAUSE_FADE,
	TIME_UP,
	TIME_UP_FADE,
	DEBUG_MODE
}eGamePlayStatus;


class CSceneGame : public CSceneBase
{
private:
	CDirectCamera*			m_pDirectCamera;
	CDirectLight*			m_pDirectLight;
	C2DSpriteAlphaBlend*	m_pBack;				// 背景ポリゴン
	C2DSpriteRHW*			m_pTimeUP;
	LPSTR					m_pResTimeUpFilePath;
	C2DSpriteRHW*			m_pPushEnter;
	LPSTR					m_pResPushEnterFilePath;

private:	
	CGameStageManager*		m_pGameStageManager;
	CPauseManager*			m_pPauseManager;
	CTimeManager*			m_pTimeManager;
	CScoreManager*			m_pScoreManager;
	CDiceInfoManager*		m_pDiceInfoManager;

private:
	CSnowObj*				m_pSnowObj;	
	CSpaceParticle*			m_pSpaceParticle;

	// ゲームプレイ中のステータス
	eGamePlayStatus			m_eGamePlayStatus;

public:
    CSceneGame		( CSceneChange* change );
	CSceneGame		( void );
	~CSceneGame		( void );
    

public:
	void Initialize	( void ) override;		// 初期化処理
    void Finalize	( void ) override;		// 終了処理
    void Run		( void ) override;		// 更新処理
    void Draw		( void ) override;		// 描画処理
	bool Load		( void ) override;		// ロード処理

public:
	void Pause			( void );			// ポーズ中処理
	void ChangePause	( void );			// ポーズ切り替え
	void PauseFade		( void );			// ポーズからのフェード
	void TimeUp			( void );			// タイムアップ
	void TimeUpFade		( void );			// タイムアップのフェード
};

#endif _C_SCENE_GAME_H_