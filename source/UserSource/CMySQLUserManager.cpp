#include "CMySQLUserManager.h"


//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CMySQLUserManager::CMySQLUserManager( void )
{
	m_id = "";
	m_userID = "";
	m_pass = "";
	m_userName = "";
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CMySQLUserManager::~CMySQLUserManager( void )
{
}

//----------------------------------------------------
// Userのログイン
// ログイン失敗時はfalseが返る
//----------------------------------------------------
bool CMySQLUserManager::Login( CONST std::string* loginID, CONST std::string* loginPass )
{
	std::string sqlString;
	
	// Login確認用のSQL文作成
	sqlString = COMBINE_STRING( 5, "id = '", loginID->c_str(),  " ' AND pass = '", loginPass->c_str(), "'" );
	
	// MySQLとの接続
	if( CMySQLManager::GetInstance()->ConnectDatabase() == true )
	{
		// 接続成功
		if( CMySQLManager::GetInstance()->Search( USER_TABLE, sqlString ))
		{
			// ログイン成功時にパスワードとIDを保存
			m_id = *loginID;
			m_pass = *loginPass;

			// USERIDとパスワードも取得
			std::string columnSql = COMBINE_STRING( 1, "userID, name" );
			std::string conditionSql = COMBINE_STRING( 3, "id = '", loginID->c_str(), "'" );
			MYSQL_ROW field = nullptr;
			field = CMySQLManager::GetInstance()->Search( field, &(std::string)USER_TABLE, &columnSql, &conditionSql );
			
			m_userID = field[0];
			m_userName = field[1];

			// SQLの切断
			CMySQLManager::GetInstance()->UnConnectionDatabase();
			return true;
		}

		CMySQLManager::GetInstance()->UnConnectionDatabase();	// 切断
		return false;
	}

	// MySQL接続失敗
	return false;
}

//----------------------------------------------------
// Userの新規登録
// すでに登録されているUserIDの場合はfalseが返る
//----------------------------------------------------
bool CMySQLUserManager::SignUp( CONST std::string* userID, CONST std::string* userPass )
{
	// DBに接続
	if( CMySQLManager::GetInstance()->ConnectDatabase() )
	{
		// 既に登録されているかどうか確認( User IDで確認 )
		std::string  sqlString = COMBINE_STRING( 3, "userID = '", userID->c_str(), "'" );
		if( !CMySQLManager::GetInstance()->Search( USER_TABLE, sqlString ) )
		{
			// 登録処理
			// 新規登録するためのSQLを作成
			sqlString = COMBINE_STRING( 9, "'", "00004", "' ,'", "aiueo", "', '", userID->c_str(), "', '", userPass->c_str(), "'" );
			if( CMySQLManager::GetInstance()->Insert( USER_TABLE, sqlString ) )
			{
				// 登録成功
				return true;
			}
			// 登録失敗
			CMySQLManager::GetInstance()->UnConnectionDatabase();
			return false;
		}
		// すでに登録されている
		CMySQLManager::GetInstance()->UnConnectionDatabase();
		
		// 何かメッセージを出す

		return false;
	}
	
	// MySQL接続失敗
	return false;
}
