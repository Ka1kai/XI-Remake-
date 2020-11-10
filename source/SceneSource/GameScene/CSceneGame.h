	//----------------------------------------------------
// CSceneGame Header
//	�Q�[���V�[��
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
	C2DSpriteAlphaBlend*	m_pBack;				// �w�i�|���S��
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

	// �Q�[���v���C���̃X�e�[�^�X
	eGamePlayStatus			m_eGamePlayStatus;

public:
    CSceneGame		( CSceneChange* change );
	CSceneGame		( void );
	~CSceneGame		( void );
    

public:
	void Initialize	( void ) override;		// ����������
    void Finalize	( void ) override;		// �I������
    void Run		( void ) override;		// �X�V����
    void Draw		( void ) override;		// �`�揈��
	bool Load		( void ) override;		// ���[�h����

public:
	void Pause			( void );			// �|�[�Y������
	void ChangePause	( void );			// �|�[�Y�؂�ւ�
	void PauseFade		( void );			// �|�[�Y����̃t�F�[�h
	void TimeUp			( void );			// �^�C���A�b�v
	void TimeUpFade		( void );			// �^�C���A�b�v�̃t�F�[�h
};

#endif _C_SCENE_GAME_H_