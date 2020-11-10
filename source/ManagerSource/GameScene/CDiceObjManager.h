//----------------------------------------------------
// CDiceObjManager
//　サイコロのオブジェクトの管理クラス
//
// @date	2013/11/20
// @authro	T.Kawashita
//----------------------------------------------------
#ifndef _C_DICE_OBJ_MANAGER_H_
#define _C_DICE_OBJ_MANAGER_H_

#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CInputKeyboard.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CJoyStick.hpp"
#include "../../GameMathSource/CDiceRandSystem.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/GameMathHeader/CCollision.h"
#include "../../SceneSource/DebugScene/CDebugMode.h"

#include "../../ObjectSource/GameScene/Particle/CSplitParticle.h"

#include "../../ObjectSource/GameScene/CDiceObj.h"
#include <list>

#include "CStageBlockManager.h"
#include "CChainManager.h"
#include "../../PlayerSource/CPlayerManager.h"
#include "../../ManagerSource/GameScene/CDiceInfoManager.h"

#define MAX_DICE_NUM		( 49 )		// サイコロの最大数(ステージ数によって変化させる)
#define DICE_DOWN_SPEED		( 0.005f )	// サイコロの出現と削除時のアニメの早さ
#define DICE_UP_SPEED		( 0.012f )	// サイコロ出現速度

// サイコロの回転向きステータス
enum eDiceRollState
{
	DICE_ROLLSTATE_NONE,
	DICE_ROLLSTATE_RIGHT,
	DICE_ROLLSTATE_LEFT,
	DICE_ROLLSTATE_FRONT,
	DICE_ROLLSTATE_BACK,
	DICE_ROLLSTATE_Y
};
	
typedef struct tagTMAINDICE
{
	CDiceObj*		diceObj;	// メインのサイコロのポインタのみを保存するためのもの
	eDiceRollState	rollState;	// 回転ステータス
	float			degree;		// 回転角度
	D3DXVECTOR3		halfSize;	// ダイスの半分のサイズ（移動の軸移動に使う）
}TMAINDICE;

class CDiceObjManager
{
private:
	TMAINDICE*				m_pMainDice;		// メインのサイコロ
	CSplitParticle*			m_pSplitParticle;	// サイコロが動いた時のパーティクル

	CDiceObjManager			( void );
	CDiceObjManager			( CONST CDiceObjManager& diceObjManager ){}
	CDiceObjManager	operator= ( CONST CDiceObjManager& diceObjManager ){}

public:
	// インスタンス取得場所
	static CDiceObjManager* GetInstance( void )
	{
		static CDiceObjManager	diceObjManager;
		return &diceObjManager;
	}

	//----------------------------------------------------
	// メインのダイスを取得
	//----------------------------------------------------
	TMAINDICE*			GetMainDice		( void )
	{
		return m_pMainDice;
	}

	//----------------------------------------------------
	// ダイスの先頭アドレスを取得
	//----------------------------------------------------
	CDiceObj*			GetDice			( void )
	{
		return m_pDice;
	}

// メンバ
private:
	CDiceObj*				m_pDice;			// サイコロ
	LPSTR					m_pResDiceFilePath;	// サイコロの画像
	int						m_diceNum;			// ダイスの数
	int						m_appearTime;		// ダイスの出現時間管理用

	CDiceInfoManager*		m_pDiceInfoManager;	// ダイスのインフォマネージャー

public:
	~CDiceObjManager		( void );			// デストラクタ

public:
	void		Draw		( CONST D3DXMATRIX* view );		// 描画
	void		Run			( void );						// 処理	
	void		Init		( void );						// 初期化
	void		Uninit		( void );						// 終了
	void		Debug		( void );						// デバッグ用

// サイコロのメイン処理
public:
	//----------------------------------------------------
	// 移動制御
	//----------------------------------------------------
	void		Move		( void );	// 移動の遷移
	void		MoveRight	( void );	// 右移動
	void		MoveLeft	( void );	// 左移動
	void		MoveFront	( void );	// 前移動
	void		MoveBack	( void );	// 後移動

	//----------------------------------------------------
	// @name	MoveToRoll
	// @content	サイコロの移動＋回転	
	// @param	none
	// @return	none
	// @date	2013/11/27
	//----------------------------------------------------
	void		MoveToRoll	( void );

	//----------------------------------------------------
	// @name	Appear
	// @content	ダイスの出現	
	// @param	none
	// @return	bool		出現できたか出来なかったか
	// @date	2013/11/27	
	// @update	2013/12/3	引数の追加
	//----------------------------------------------------
	bool		Appear			( void );

	//----------------------------------------------------
	// @name	AppearManager
	// @content	出現管理
	// @param	none	
	// @return	none
	// @date	2014/2/14
	//----------------------------------------------------
	void		AppearManager	( void );

	//----------------------------------------------------
	// @name	Animation
	// @content	ダイスのアニメーション
	// @param	none
	// @return	none
	// @date	2013/12/4
	//----------------------------------------------------
	void		Animation	( void );

	//----------------------------------------------------
	// @name	SetDiceInfoManager
	// @content	ダイスインフォマネージャーのアドレスをセット
	// @param	diceInfoManager	ダイスインフォのマネージャーのインスタンス
	// @return	none
	// @date	2014/2/10
	//----------------------------------------------------
	void		SetDiceInfoManager	( CDiceInfoManager* diceInfoManager )
	{
		m_pDiceInfoManager = diceInfoManager;
	}

};

#endif _C_DICE_OBJ_MANAGER_H_