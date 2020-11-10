//----------------------------------------------------
// CDebugMode 
//	ゲームのデバッグに使うシーン	
//
// @date	2014/1/13
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_DEBUG_MODE_H_
#define _C_DEBUG_MODE_H_

#include <Windows.h>

#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/2D/C2DSpriteAlphaBlend.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/3D/C3DObjectShape.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CInputKeyboard.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CJoyStick.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9Camera.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourcePath.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceXFont.h"

#define DEBUG_NUM					( 4 )
#define SELECT_DEBUG_NUM			( 6 )
#define DEFAULT_DEBUG_MODE_COLOR	D3DXCOLOR( 255, 255, 255, 255 )
#define SELECT_DEBUG_MODE_COLOR		D3DXCOLOR( 0, 255, 0, 255 )
#define CHEACK_DEBUG_MODE_COLOR		D3DXCOLOR( 255, 0, 0, 255 )

// デバッグのフォント
typedef struct tFONTINFO
{
	bool		cheack;
	D3DXCOLOR   color;
}TFONTINFO;

// デバッグのステータス
typedef enum DEBUGSTATUS
{
	FPS,
	COLLISION_BOX,
	GAME_TIME,
	EXIT_DEBUG
}eDebugStatus;

typedef struct tDEBUGDICEBOX
{
	bool				isDice;		// 生成されているか
	C3DObjectShape		diceBox;	// AABBボックス表示用本体
}TDEBUGDICEBOX;

class CDebugMode
{
public:
	// デバッグモード画面用2Dポリゴン
	static C2DSpriteRHW			m_pDebugMode;
	static LPSTR				m_pDebugModeTexturePath;

	// デバッグモード終了用フラグ
	static bool					m_isDebugMode;

	// 当たり判定確認用のボックス
	static C3DObjectShape		m_pPlayerBox;
	static TDEBUGDICEBOX		m_pDiceBox[49];

	// デバッグの値
	static float*				m_pFps;						// FPS
	static int*					m_pTime;					// ゲームの時間

	static TFONTINFO			m_font[ SELECT_DEBUG_NUM ];	// デバッグのフォント情報
	static int					m_fontIndex;				// デバッグの選択インデックス番号
	static bool					m_debugOnOff;				// デバッグのOnOFF機能があるもののフラグ

	// デバッグの項目を管理
	static int					m_leftRightIndexDir;		// 左右の向き
	static int					m_upDownIndexDir;			// 上下の向き
	static int					m_debugIndex;				// デバッグの項目インデックス番号
	static eDebugStatus			m_eDebugStatus;				// 現在の選択がどのデバッグの項目か

private:
	// 各種フラグ
	static bool					m_isCollisionBox;			// 当たり判定チェック用ボックス表示フラグ
	static bool					m_isFps;					// FPS表示フラグ

private:
	// コンストラクタ
	CDebugMode				( void );
	CDebugMode				( CONST CDebugMode& debugMode ){}	// コピーコンストラクタを防ぐ
	CDebugMode	operator=	( CONST CDebugMode& debugMode ){}	// メンバの代入を防ぐ

public:
	// デストラクタ
	~CDebugMode					( void );

	//----------------------------------------------------
	// 初期化
	//----------------------------------------------------
	static bool Load			( void );
	static bool	Init			( void );
	static void Set				( int* pTime );
	static bool InitDebugMode	( void );

	//----------------------------------------------------
	// 処理
	//----------------------------------------------------
	static void	Run				( CDirectCamera* camera );
	static void RunDebugMode	( void );
	static void	RunRight		( void );	// 右入力
	static void RunLeft			( void );	// 左入力
	static void	RunUp			( void );	// 上入力
	static void RunDown			( void );	// 下入力
	static void RunEnter		( void );	// Enter入力

	//----------------------------------------------------
	// 描画
	//----------------------------------------------------
	static void	Draw			( void );
	static void DrawDebugMode	( void );

	//----------------------------------------------------
	// 終了
	//----------------------------------------------------
	static bool	Uninit			 ( void );

	//----------------------------------------------------
	// @name	DebugONOFF
	// @content	デバッグのON/OFFの処理
	// @param	isOnOff		ON/OFF
	// @param	font*		fontデータ1
	// @param	font2*		fontデータ2
	// @return	none
	// @date	2014/1/22
	//----------------------------------------------------
	static void DebugONOFF		( bool isOnOff, TFONTINFO* font, TFONTINFO* font2 );

	//----------------------------------------------------
	// @name	DigitUpDown
	// @content	値の調整
	// @param	pOut		調整し終わった値	
	// @param	pDigit		調整したい値
	// @param	value		調整する量
	// @return	int*		調整し終わった値
	// @date	2014/1/22
	//----------------------------------------------------
	static int* DigitUpDown		( int* pOut, int* pDigit, int value );
};

#endif _C_DEBUG_MODE_H_