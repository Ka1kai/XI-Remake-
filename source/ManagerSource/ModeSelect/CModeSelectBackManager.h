//----------------------------------------------------
// CModeSelectBackManager 
//	モードセレクト画面の背景マネージャー
//
// @date	2014/2/4
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_MODESELECT_BACK_MANAGER_
#define _C_MODESELECT_BACK_MANAGER_

#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourcePath.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/UtilityHeader/Macro.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CInputKeyboard.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CJoyStick.hpp"

#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/CObjectBase.hpp"
#include "../../ObjectSource/ModeSelect/CMessageBar.h"

typedef enum 
{
	eMessageBarNone,
	eMessageBarAnimation,
	eMessageBarNormal
}eMessageBarStatus;

class CModeSelectBackManager
{
private:
	CObjectBase*			m_pModeSelectStage;
	LPSTR					m_pResModeSelectStageFilePath;

	// αブレンド用
	C2DSpriteAlphaBlend*	m_pAlphaBlend;

	// メニューの文字
	C2DSpriteAlphaBlend*	m_pMenuValue;
	LPSTR					m_pResMenuValueFilePath;

	// モードセレクト画面のメッセージバー
	CMessageBar*			m_pMessageBar;
	LPSTR					m_pResMessageBar[6];
	int						m_resIndexNo;
	eMessageBarStatus		m_eMessageBarStatus;

	bool					m_isBarAnimation;
	bool					m_isAlphaBlend;

public:
	CModeSelectBackManager	( void );	// コンストラクタ
	~CModeSelectBackManager	( void );	// デストラクタ

public:
	// メッセージバーのステータス取得
	eMessageBarStatus		GetMessageBarStatus	( void )
	{
		return m_eMessageBarStatus;
	}

	// メッセージバーのステータスセット
	void	SetMessageBarStatus	( CONST eMessageBarStatus messageBarStatus )
	{
		m_eMessageBarStatus = messageBarStatus;
	}

public:
	bool	Init			( void );	// 初期化
	void	Run				( void );	// 処理
	void	Draw			( void );	// 描画
	void	DrawAlpha		( void );	// αブレンド用画像の描画
	bool	Uninit			( void );	// 終了

public:
	void	RunKey				( CONST UINT index );	// キー入力
	void	RunKeyEnter			( void );				// エンターキー押されたら呼ぶ関数

	bool	MessageBarAnimation	( void );				// メッセージバーのアニメーション
	bool	Fade				( void );				// フェードアウト
};

#endif _C_MODESELECT_BACK_MANAGER_