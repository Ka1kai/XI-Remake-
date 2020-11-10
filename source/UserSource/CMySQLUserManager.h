//----------------------------------------------------
// CMySQLUserManager
//	自分のUserテーブルの管理クラス
//
// @date	2013/11/14
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_MYSQL_USER_MANAGER_H_
#define _C_MYSQL_USER_MANAGER_H_

#include "../MySQLSource/CMySQLManager.hpp"
#include "../KaiFrameWork/KaiFrameWorkHeader/UtilityHeader/Macro.hpp"
#include <string>

#pragma warning(disable : 4996)

// 使うテーブルの名前
#define USER_TABLE "User"

class CMySQLUserManager
{
private:
	std::string m_userID;	// UserID
	std::string m_id;		// Userが設定したID
	std::string m_pass;		// Userが設定したパスワード
	std::string m_userName;	// Userの名前

public:
	// UserIDの取得
	std::string*	GetIDUser	( void )
	{
		return &m_userID;
	}
	// UserNameの取得
	std::string*	GetNameUser	( void )
	{
		return &m_userName;
	}

public:
	CMySQLUserManager();
	virtual ~CMySQLUserManager();

public:
	//----------------------------------------------------
	// @name	LoginChk
	// @content	ログイン
	// @param	loginID		ログインID
	// @param	loginPass	ログインパスワード
	// @return	bool		ログイン成功か失敗
	// @date	2013/11/15
	//----------------------------------------------------
	bool Login ( CONST std::string* loginID, CONST std::string* loginPass );

	//----------------------------------------------------
	// @name	SignUp
	// @content	ユーザの新規登録
	// @param	userID		登録したいユーザID	
	// @param	userPass	登録したいユーザパスワード
	// @return	bool		登録の成功か失敗
	// @date	2013/11/15	
	//----------------------------------------------------
	bool SignUp	( CONST std::string* userID, CONST std::string* userPass );

};

#endif _C_MYSQL_USER_MANAGER_H_