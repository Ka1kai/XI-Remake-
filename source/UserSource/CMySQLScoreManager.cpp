
#include "CMySQLScoreManager.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CMySQLScoreManager::CMySQLScoreManager( void )
{
	m_scoreID = "";
	m_userID = "";
	m_userName = "";
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
CMySQLScoreManager::~CMySQLScoreManager( void )
{
}

//----------------------------------------------------
// �n�C�X�R�A�̍X�V
//----------------------------------------------------
bool CMySQLScoreManager::UpdateHighScore( CONST std::string* updateSql )
{
	// MySQL�Ɛڑ�
	if( CMySQLManager::GetInstance()->ConnectDatabase() == true )
	{
		std::string conditionSql = COMBINE_STRING( 3,"userID = '", m_userID.c_str(), "'" );

		if( CMySQLManager::GetInstance()->Update( &(std::string)SCORE_TABLE, updateSql, &conditionSql ) == true )
		{
			// �X�V����
			CMySQLManager::GetInstance()->UnConnectionDatabase();
			return true;
		}
		CMySQLManager::GetInstance()->UnConnectionDatabase();	// MYSQL����ؒf
		return false;
	}
	// MySQL�ڑ����s
	return false;
}

//----------------------------------------------------
// �X�R�A�̎擾
//----------------------------------------------------
CScore* CMySQLScoreManager::GetScore( CScore* score )
{
	// MySQL�Ɛڑ�
	if( CMySQLManager::GetInstance()->ConnectDatabase() == true )
	{	
		std::string columnSql = COMBINE_STRING( 1, "record,onePip,twoPip,threePip,fourPip,fivePip,sixPip,maxChain" );
		std::string conditionSql = COMBINE_STRING( 3,"userID = '", m_userID.c_str(), "'" );
		MYSQL_ROW field = nullptr;

		// �e�[�u������X�R�A���擾���ă����o�ɃZ�b�g
		field = CMySQLManager::GetInstance()->Search( field, &(std::string)SCORE_TABLE, &columnSql, &conditionSql);
		score->m_record = atoi(field[0]);
		score->m_oneChainNum = atoi(field[1]);
		score->m_twoChainNum = atoi(field[2]);
		score->m_threeChainNum = atoi(field[3]);
		score->m_fourChainNum = atoi(field[4] );
		score->m_fiveChainNum = atoi(field[5]);
		score->m_sixChainNum = atoi(field[6]);
		score->m_chainNum = atoi(field[7]);

		CMySQLManager::GetInstance()->UnConnectionDatabase();	// MYSQL����ؒf
		return score;		
	}

	// �ڑ����s
	CMySQLManager::GetInstance()->UnConnectionDatabase();	// MYSQL����ؒf
	
	return score;
}