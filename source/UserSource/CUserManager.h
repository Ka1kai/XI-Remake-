//----------------------------------------------------
// CUserManager 
//	ユーザの管理クラス
//
// @date	2014/2/15
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_USER_MANAGER_
#define _C_USER_MANAGER_

#include <string>

#include "../KaiFrameWork/KaiFrameWorkHeader/UtilityHeader/Macro.hpp"

#include "CMySQLScoreManager.h"
#include "CMySQLUserManager.h"

#include "../ObjectSource/CScore.hpp"

class CUserManager
{
private:
	std::string		m_userID;
	std::string		m_userPass;

	CScore*			m_pHighScore;
	CScore*			m_pGameScore;

	bool			m_isLogin;

	CMySQLScoreManager*	m_pSqlScoreManager;
	CMySQLUserManager*  m_pSqlUserManager;

public:
	CScore*		GetGameScore	( void )
	{
		return m_pGameScore;
	}
	CScore*		GetHighScore	( void )
	{
		return m_pHighScore;
	}
private:
	// コンストラクタ
	CUserManager	( void );
	CUserManager	( CONST CUserManager& userManager ){}	// コピーコンストラクタの禁止
	CUserManager	operator=	( CONST CUserManager& userManager ){}	// オペレータオーバロードの禁止

public:
	// 唯一のインスタンスの取得場所
	static CUserManager*	GetInstance	( void )
	{
		static CUserManager	pUserManager;
		return &pUserManager;
	}

	~CUserManager	( void );	// デストラクタ

public:
	//----------------------------------------------------
	// 初期化
	//----------------------------------------------------
	bool	Init			( void );
	bool	InitGameScore	( void );
	bool	Login			( void );	// ログイン

	//----------------------------------------------------
	// @name	SetGameScore
	// @content	ゲームスコアのセット
	// @param	pScore		ゲームで集計したスコア
	// @return	none
	// @date	2014/2/15
	//----------------------------------------------------
	void	SetGameScore	( CScore*	pScore );

	//----------------------------------------------------
	// ハイスコアとスコアの比較
	//----------------------------------------------------
	bool	UpdateScore			( void );	// スコアの更新
	bool	RecordComparision	( void );	// レコードの比較
	bool	OnePipComparision	( void );	// ①の目の比較
	bool	TwoPipComparision	( void );	// ②の目の比較
	bool	ThreePipComparision	( void );	// ③の目の比較
	bool	FourPipComparision	( void );	// ④の目比較
	bool	FivePipComparision	( void );	// ⑤の目の比較
	bool	SixPipComparision	( void );	// ⑥の目の比較
	bool	MaxChainComparision	( void );	// MaxChainの比較

};

#endif _C_USER_MANAGER_