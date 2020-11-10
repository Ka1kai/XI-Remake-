//----------------------------------------------------
// CSceneManager Header 
//	Sceneを管理する
//
// @date	2013/6/15
// @author  T.Kawashita
//----------------------------------------------------
#ifndef _C_SCENE_MANAGER_H_
#define _C_SCENE_MANAGER_H_

#include "CSceneChange.hpp"
#include "CSceneBase.hpp"

#include "../../../SceneSource/GameScene/CSceneGame.h"
#include "../../../SceneSource/ResultScene/CSceneResult.h"
#include "../../../SceneSource/GameTitleScene/CSceneTitle.h"
#include "../../../SceneSource/ModeSelectScene/CSceneModeSelect.h"
#include "../../../SceneSource/ScoreScene/CSceneScore.h"
#include "../../../SceneSource/ModelViewScene/CSceneModelView.h"
#include "../../../SceneSource/DebugScene/CSceneDebug.h"

#include "../SystemHeader/CPthread.hpp"

class CSceneManager : public CSceneChange
{
private:
	CSceneBase* m_pScene;			// シーン管理変数
	eSceneState m_nowScene;			// 現在のシーン管理変数
    eSceneState m_nextScene;		// 次のシーン管理変数

	bool		m_isLoad;			// ロードフラグ
//	CPthread*	m_pPthread;			// ロード用スレッド

private:
	//----------------------------------------------------
	// Sceneをインスタンス化する
	//----------------------------------------------------
	void Update	(void);

public:
    CSceneManager	( eSceneState state );
	CSceneManager	( void );
	~CSceneManager	( void );

public:
    void   Initialize	( void );			// 初期化
    void   Finalize		( void );			// 終了処理
    void   Run			( void );			// 更新
    void   Draw			( void );			// 描画
	static void* ThreadLoad ( void* func );	// スレッドのためのロード関数
	bool   Load			( void );			// ロード
	void   DrawLoading	( void );			// nowloading描画

public:
    //----------------------------------------------------
	// シーン変更関数
	// @nextScene
	//----------------------------------------------------
	void ChangeScene( eSceneState NextScene ) override;
};

#endif _C_SCENE_MANAGER_H_