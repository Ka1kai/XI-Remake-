//----------------------------------------------------
// CSceneModeSelect 
//	モードセレクト画面
//	
// @date	2014/2/4
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_SCENE_MODESELECT_
#define _C_SCENE_MODESELECT_

#include "../../KaiFrameWork/KaiFrameWorkHeader/SceneHeader/CSceneBase.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/SceneHeader/CSceneChange.hpp"

#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9Camera.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9Light.h"

#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CInputKeyboard.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CJoyStick.hpp"

#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/CObjectBase.hpp"
#include "../../ManagerSource/ModeSelect/CModeSelectBackManager.h"
#include "../../ManagerSource/ModeSelect/CModeSelectPlayerManager.h"

//----------------------------------------------------
// モードセレクト用のステータス
//----------------------------------------------------
typedef enum 
{
	eModeTitle,
	eModeGamePlay,
	eModeOption,
	eModeExit,
	eModeRanking,
	eModeRecord,
}eModeSelectState;

const eModeSelectState modeAllay[6] ={ 
	eModeSelectState::eModeTitle,
	eModeSelectState::eModeGamePlay,
	eModeSelectState::eModeOption,
	eModeSelectState::eModeExit,
	eModeSelectState::eModeRanking,
	eModeSelectState::eModeRecord
};

class CSceneModeSelect : public CSceneBase
{
private:
	CDirectCamera*				m_pDirectCamera;
	CDirectLight*				m_pDirectLight;

	CModeSelectBackManager*		m_pModeSelectBackManager;
	CModeSelectPlayerManager*	m_pModeSelectPlayerManager;

	eModeSelectState			m_eMode;		// モード
	int							m_modeIndexNo;	// モードの添え字番号

	bool						m_isFade;		// フェードフラグ

public:
	CSceneModeSelect	( void );
	CSceneModeSelect	( CSceneChange* change );
	~CSceneModeSelect	( void );


public:
	void Initialize	( void ) override;
	void Finalize	( void ) override;
	void Run		( void ) override;
	void Draw		( void ) override;
	bool Load		( void ) override;


};


#endif _C_SCENE_MODESELECT_