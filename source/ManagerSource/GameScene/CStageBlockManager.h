//----------------------------------------------------
// CStageBlock
//	ステージのダイスの管理クラス
//
// @date	2013/11/28
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_STAGE_BLOCK_MANAGER_H_
#define _C_STAGE_BLOCK_MANAGER_H_

#include <Windows.h>

#include "../../GameMathSource/CDiceRandSystem.h"
#include "../../ObjectSource/GameScene/CStageBlockObj.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/UtilityHeader/Macro.hpp"

#define BLOCK_SIZE			( 4.0f )	// マス目一つの大きさ
#define BLOCK_MAXSIZE		( 12.0f )	// ステージの最大の大きさ
#define BLOCK_DEFAULT_NUM_X	( 7 )		// デフォルトのステージのXマス目数
#define BLOCK_DEFAULT_NUM_Y	( 1 )		// デフォルトのステージのYマス目数
#define BLOCK_DEFAULT_NUM_Z	( 7 )		// デフォルトのステージのZマス目数

// デフォルトのステージのブロックの数
#define BLOCK_DEFAULT_MAX_NUM	( BLOCK_DEFAULT_NUM_X * BLOCK_DEFAULT_NUM_Y * BLOCK_DEFAULT_NUM_Z )

class CStageBlockManager
{
private:
	CStageBlockObj	m_stageBlock[ BLOCK_DEFAULT_MAX_NUM ];		// ステージのブロックＯＢＪ

	USHORT	m_blockNum;				// ステージのブロック数

	USHORT	m_xNum;					// ステージのブロックのXマス目数
	USHORT	m_yNum;					// ステージのブロックのYマス目数
	USHORT	m_zNum;					// ステージのブロックのZマス目数

	// コンストラクタ
	CStageBlockManager			( void );
	CStageBlockManager	( CONST CStageBlockManager& stageBlockManager ){}	// コピーコンストラクタを防ぐ
	CStageBlockManager	operator=	( CONST CStageBlockManager& stageBlockManager ){}	// メンバの代入を防ぐ

public:
	// インスタンス取得場所
	static CStageBlockManager* GetInstance( void )
	{
		static CStageBlockManager stageBlockManager;
		return &stageBlockManager;
	}

	// ステージのブロックＯＢＪの取得
	CStageBlockObj* GetStageBlock	( CONST UINT index )
	{

		return &m_stageBlock[ index ];
	}

public:
	//----------------------------------------------------
	// マス目数取得
	//----------------------------------------------------
	CONST USHORT	GetXNum		( void )
	{
		return m_xNum;
	}
	CONST USHORT	GetYNum		( void )
	{
		return m_yNum;
	}
	CONST USHORT	GetZNum		( void )
	{
		return m_zNum;
	}

private:
	float			m_xSize;				// ステージのブロック最大横サイズ
	float			m_ySize;				// ステージのブロック最大縦サイズ
	float			m_zSize;				// ステージのブロック最大奥行サイズ

public:
	//----------------------------------------------------
	// サイズ取得
	//----------------------------------------------------
	CONST float	GetXSize	( void )
	{
		return m_xSize;
	}
	CONST float	GetYSize	( void )
	{
		return m_ySize;
	}
	CONST float	GetZSize	( void )
	{
		return m_zSize;
	}

public:
	
	// デストラクタ
	~CStageBlockManager			( void );

	//----------------------------------------------------
	// 初期化
	//----------------------------------------------------
	bool		Init		( void );

	//----------------------------------------------------
	// @name	SetStagePos
	// @content	ステージのブロック位置情報をセット(デフォルト値)	
	// @param	none
	// @return	none
	// @date	2013/11/29
	//----------------------------------------------------
	void		SetBlockPos	( void );

	//----------------------------------------------------
	// @name	SetStagePos
	// @content	ステージのブロック位置情報をセット	
	// @param	xNum		横数
	// @param	yNum		高さ
	// @param	zNum		奥数
	// @return	none
	// @date	2013/11/29
	//----------------------------------------------------
	bool		SetBlockPos	( CONST UINT xNum, CONST UINT yNum, CONST UINT zNum );

	//----------------------------------------------------
	// @name	GetIndexToDicePos
	// @content	ブロックのインデックスをダイスの位置から取得
	// @param	xPos		X座標
	// @param	zPos		Z座標
	// @return	UINT		ブロックインデックス番号
	// @date	2013/12/2
	// @update	2014/2/1	引数 Y座標をはずしました
	//----------------------------------------------------
	CONST UINT GetIndexToDicePos	( CONST float xPos, CONST float zPos );

	//----------------------------------------------------
	// @name	GetIndexToPlayerPos
	// @content	ブロックのインデックスをプレイヤー位置から取得
	// @param	xPos		X座標
	// @param	zPos		Z座標
	// @return	UINT		ブロックインデックス番号
	// @date	2014/2/1
	// @update
	//----------------------------------------------------
	CONST UINT GetIndexToPlayerPos	( CONST float xPos, CONST float zPos );

	//----------------------------------------------------
	// @name	GetPos
	// @content	ブロックの位置を添え字から位置取得
	// @param	index			添え字
	// @return	D3DXVECTOR3*
	// @date	2013/12/2
	//----------------------------------------------------
	D3DXVECTOR3*	GetPos	( UINT index )
	{
		return m_stageBlock[ index ].GetPosition();
	}

	//----------------------------------------------------
	// @name	GetBlockIndexRnd
	// @content	ランダムでブロックの添え字を取得
	// @param	none
	// @return	UINT	位置情報
	// @date	2013/12/2
	//----------------------------------------------------
	CONST UINT	GetBlockIndexRnd	( void )
	{
		unsigned int rnd = CDiceRandSystem::GetInstance()->GetPos( m_blockNum );
		return rnd;
	}

	//----------------------------------------------------
	// @name	GetDiceNum
	// @content	ステージのブロックの数を取得
	// @param	none
	// @return	UINT		ブロックの最大数
	// @date	2013/12/2
	//----------------------------------------------------
	CONST UINT	GetDiceNum		( void )
	{
		return m_blockNum;
	}

	//----------------------------------------------------
	// @name	GetIsOnDice
	// @content	ブロック上にダイスがあるかどうか取得
	// @param	diceNo		調べたい添え字番号
	// @return	bool		あるかないか
	// @date	2013/12/2
	//----------------------------------------------------
	bool		GetIsOnDice	( CONST UINT diceNo  )
	{
		if( diceNo >= 0 )
			return m_stageBlock[ diceNo ].CheckOnDice();

		else 
			return 0;
	}

	//----------------------------------------------------
	// @name	SetBlockToDice
	// @content	ブロックにダイスの情報をセット
	// @param	CDiceObj*		ダイス本体
	// @param	diceNo			ダイスの番号
	// @return	none
	// @date	2013/12/2
	//----------------------------------------------------
	void		SetBlockToDiceInfo	( CDiceObj* dice, int diceNo );

	//----------------------------------------------------
	// @name	SetIsOnDice
	// @content	ダイスが乗っているかどうかのフラグをセット
	// @param	diceNo		セットしたいダイスの番号
	// @param	isDice		true or false
	// @return	none 
	//----------------------------------------------------
	void		SetIsOnDice	( CONST UINT diceNo, bool isDice )
	{
		m_stageBlock[ diceNo ].SetIsOnDice( isDice );
	}
};


#endif _C_STAGE_BLOCK_MANAGER_H_