//----------------------------------------------------
// CMySQLScoreManager
//	Scoreテーブルの管理クラス
//
// @date	2014/2/19
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_MYSQL_SCORE_MANAGER_H_
#define _C_MYSQL_SCORE_MANAGER_H_

#include "../MySQLSource/CMySQLManager.hpp"
#include "../KaiFrameWork/KaiFrameWorkHeader/UtilityHeader/Macro.hpp"
#include <string>
#include "../ObjectSource/CScore.hpp"

#pragma warning(disable : 4996)

// 使うテーブルの名前
#define SCORE_TABLE "score"

class CMySQLScoreManager
{
private:
	std::string m_scoreID;
	std::string m_userID;
	std::string	m_userName;

public:
	CMySQLScoreManager();			// コンストラクタ
	virtual ~CMySQLScoreManager();	// デストラクタ

	//----------------------------------------------------
	// ユーザ情報のセット
	//----------------------------------------------------
	void	SetUserInfo			( CONST std::string* userID, CONST std::string* userName )
	{
		m_userID = *userID;
		m_userName = *userName;
	}

public:
	//----------------------------------------------------
	// @name	UpdateHighScore
	// @content	ハイスコアの更新
	// @param	updateSql	更新したいSQL文
	// @return	bool		ハイスコアの更新が成功か失敗
	// @date	2014/2/19
	//----------------------------------------------------
	bool	UpdateHighScore		( CONST std::string* updateSql );

	//----------------------------------------------------
	// @name	GetTable
	// @content	スコアテーブルの取得
	// @param	
	// @return	CScore
	// @date	2014/2/19
	//----------------------------------------------------
	CScore*	GetScore			( CScore* score );

};

#endif _C_MYSQL_SCORE_MANAGER_H_