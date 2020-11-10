//----------------------------------------------------
// CStageBlockObj  
//	ステージのブロックオブジェクト
//
// @date	2013/11/29
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_STAGE_BLOCK_OBJ_
#define _C_STAGE_BLOCK_OBJ_

#include "CDiceObj.h"

class CStageBlockObj
{
private:
	int				m_no;
	D3DXVECTOR3		m_pos;
	CDiceObj*		m_pDice;
	bool			m_isOnDice;
	bool			m_isOnPlayer;

public:
	// コンストラクタ
	CStageBlockObj		( void );

	// デストラクタ
	~CStageBlockObj		( void );

	// 初期化
	bool		Init	( void );

public:

	//----------------------------------------------------
	// 位置情報を取得
	//----------------------------------------------------
	D3DXVECTOR3* GetPosition		( void )
	{
		return &m_pos;
	}

	//----------------------------------------------------
	// ステージのブロックに乗っているダイスの取得 
	//----------------------------------------------------
	CDiceObj*		GetDice			( void )
	{
		return m_pDice;
	}

	//----------------------------------------------------
	// @name	CheckOnDice
	// @content	ダイスがあるかどうか取得
	// @param	none	
	// @return	bool	あるかないか
	// @date	2013/11/29
	//----------------------------------------------------
	bool		CheckOnDice		( void );

	//----------------------------------------------------
	// @name	CheckOnPlayer
	// @content	プレイヤーが乗っているかどうか取得
	// @param	none
	// @return	bool	乗っているかどうか
	// @date	2014/1/30
	//----------------------------------------------------
	bool		CheckOnPlayer	( void );

	//----------------------------------------------------
	// @name	SetPostion
	// @content	ブロックのポジションをセット
	// @param	x		X座標
	// @param	y		Y座標
	// @param	z		Z座標	
	// @return	none
	// @date	2013/11/29
	//----------------------------------------------------
	void		SetPosition		( float x, float y, float z );

	//----------------------------------------------------
	// @name	SetDice
	// @content	ダイスをセット
	// @param	dice	セットしたいダイスのオブジェクトのポインタ
	// @return	none
	// @date	2013/11/29
	//----------------------------------------------------
	void		SetDice			( CDiceObj*	dice );

	//----------------------------------------------------
	// @name	SetNo
	// @content	番号のセット
	// @param	no		セットしたい番号
	// @return	none
	// @date	2013/12/2
	//----------------------------------------------------
	void		SetNo			( CONST UINT no );

	//----------------------------------------------------
	// @name	SetIsOnDice
	// @content	ダイスが乗っているかどうかのフラグをセット
	// @param	isDice		フラグ
	// @return	none
	// @date	2013/12/2
	//----------------------------------------------------
	void		SetIsOnDice		( CONST bool isDice );

	//----------------------------------------------------
	// @name	SetIsOnPlayer
	// @content	プレイヤーが乗っているかどうかのフラグをセット
	// @param	isPlayer	フラグ
	// @return	none
	// @date	2014/1/30
	//----------------------------------------------------
	void		SetIsOnPlayer	( CONST bool isPlayer );

	//----------------------------------------------------
	// @name	Draw
	// @content	ステージのブロックを描画
	// @param	none
	// @return	none
	// @date	2013/12/2
	//----------------------------------------------------
	void		Draw			( void );

};

#endif _C_STAGE_BLOCK_OBJ_