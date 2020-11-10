
#include "CMySQLScoreManager.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CMySQLScoreManager::CMySQLScoreManager( void )
{
	m_scoreID = "";
	m_userID = "";
	m_userName = "";
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CMySQLScoreManager::~CMySQLScoreManager( void )
{
}

//----------------------------------------------------
// ハイスコアの更新
//----------------------------------------------------
bool CMySQLScoreManager::UpdateHighScore( CONST std::string* updateSql )
{
	// MySQLと接続
	if( CMySQLManager::GetInstance()->ConnectDatabase() == true )
	{
		std::string conditionSql = COMBINE_STRING( 3,"userID = '", m_userID.c_str(), "'" );

		if( CMySQLManager::GetInstance()->Update( &(std::string)SCORE_TABLE, updateSql, &conditionSql ) == true )
		{
			// 更新成功
			CMySQLManager::GetInstance()->UnConnectionDatabase();
			return true;
		}
		CMySQLManager::GetInstance()->UnConnectionDatabase();	// MYSQLから切断
		return false;
	}
	// MySQL接続失敗
	return false;
}

//----------------------------------------------------
// スコアの取得
//----------------------------------------------------
CScore* CMySQLScoreManager::GetScore( CScore* score )
{
	// MySQLと接続
	if( CMySQLManager::GetInstance()->ConnectDatabase() == true )
	{	
		std::string columnSql = COMBINE_STRING( 1, "record,onePip,twoPip,threePip,fourPip,fivePip,sixPip,maxChain" );
		std::string conditionSql = COMBINE_STRING( 3,"userID = '", m_userID.c_str(), "'" );
		MYSQL_ROW field = nullptr;

		// テーブルからスコアを取得してメンバにセット
		field = CMySQLManager::GetInstance()->Search( field, &(std::string)SCORE_TABLE, &columnSql, &conditionSql);
		score->m_record = atoi(field[0]);
		score->m_oneChainNum = atoi(field[1]);
		score->m_twoChainNum = atoi(field[2]);
		score->m_threeChainNum = atoi(field[3]);
		score->m_fourChainNum = atoi(field[4] );
		score->m_fiveChainNum = atoi(field[5]);
		score->m_sixChainNum = atoi(field[6]);
		score->m_chainNum = atoi(field[7]);

		CMySQLManager::GetInstance()->UnConnectionDatabase();	// MYSQLから切断
		return score;		
	}

	// 接続失敗
	CMySQLManager::GetInstance()->UnConnectionDatabase();	// MYSQLから切断
	
	return score;
}