//----------------------------------------------------
// CScore 
//	スコア
//
// @date	2014/2/9
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_SCORE_H_
#define _C_SCORE_H_

#include <Windows.h>

class CScore
{
public:
	UINT	m_oneChainNum;		// ダイス１を消した回数
	UINT	m_twoChainNum;		// ダイス２を消した回数
	UINT	m_threeChainNum;	// ダイス３を消した回数	
	UINT	m_fourChainNum;		// ダイス４を消した回数
	UINT	m_fiveChainNum;		// ダイス５を消した回数
	UINT	m_sixChainNum;		// ダイス６を消した回数
	UINT	m_chainNum;			// コンボ回数
	UINT	m_maxLinkNum;		// 最大リンク回数
	UINT	m_record;			// スコア

public:
	//----------------------------------------------------
	// コンストラクタ
	//----------------------------------------------------
	CScore		( void )
	{
		m_oneChainNum = 0;
		m_twoChainNum = 0;
		m_threeChainNum = 0;
		m_fourChainNum = 0;
		m_fiveChainNum = 0;
		m_sixChainNum = 0;
		m_chainNum = 0;
		m_maxLinkNum = 0;
		m_record = 0;
	}

	//----------------------------------------------------
	// デストラクタ
	//----------------------------------------------------
	~CScore		( void )
	{
	}

public:
	//----------------------------------------------------
	// 初期化
	//----------------------------------------------------
	bool	Init			( void )
	{
		m_oneChainNum = 0;
		m_twoChainNum = 0;
		m_threeChainNum = 0;
		m_fourChainNum = 0;
		m_fiveChainNum = 0;
		m_sixChainNum = 0;
		m_chainNum = 0;
		m_maxLinkNum = 0;
		m_record = 0;

		return true;
	}

	//----------------------------------------------------
	// @name	PipScoreAdd
	// @content	上面によってスコア集計
	// @param	pip		消した上面
	// @param	diceNum	消した数
	// @return	none
	// @date	2014/2/12
	//----------------------------------------------------
	void	PipScoreAdd		( CONST UINT pip, CONST UINT diceNum )
	{
		switch( pip )
		{
		case 1:
			m_oneChainNum += diceNum;
			break;
		case 2:
			m_twoChainNum += diceNum;
			break;
		case 3:
			m_threeChainNum += diceNum;
			break;
		case 4:
			m_fourChainNum += diceNum;
			break;
		case 5:
			m_fiveChainNum += diceNum;
			break;
		case 6:
			m_sixChainNum += diceNum;
			break;
		}
	}
};

#endif _C_SCORE_H_