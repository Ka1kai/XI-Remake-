#include "CMySQLUserManager.h"


//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CMySQLUserManager::CMySQLUserManager( void )
{
	m_id = "";
	m_userID = "";
	m_pass = "";
	m_userName = "";
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
CMySQLUserManager::~CMySQLUserManager( void )
{
}

//----------------------------------------------------
// User�̃��O�C��
// ���O�C�����s����false���Ԃ�
//----------------------------------------------------
bool CMySQLUserManager::Login( CONST std::string* loginID, CONST std::string* loginPass )
{
	std::string sqlString;
	
	// Login�m�F�p��SQL���쐬
	sqlString = COMBINE_STRING( 5, "id = '", loginID->c_str(),  " ' AND pass = '", loginPass->c_str(), "'" );
	
	// MySQL�Ƃ̐ڑ�
	if( CMySQLManager::GetInstance()->ConnectDatabase() == true )
	{
		// �ڑ�����
		if( CMySQLManager::GetInstance()->Search( USER_TABLE, sqlString ))
		{
			// ���O�C���������Ƀp�X���[�h��ID��ۑ�
			m_id = *loginID;
			m_pass = *loginPass;

			// USERID�ƃp�X���[�h���擾
			std::string columnSql = COMBINE_STRING( 1, "userID, name" );
			std::string conditionSql = COMBINE_STRING( 3, "id = '", loginID->c_str(), "'" );
			MYSQL_ROW field = nullptr;
			field = CMySQLManager::GetInstance()->Search( field, &(std::string)USER_TABLE, &columnSql, &conditionSql );
			
			m_userID = field[0];
			m_userName = field[1];

			// SQL�̐ؒf
			CMySQLManager::GetInstance()->UnConnectionDatabase();
			return true;
		}

		CMySQLManager::GetInstance()->UnConnectionDatabase();	// �ؒf
		return false;
	}

	// MySQL�ڑ����s
	return false;
}

//----------------------------------------------------
// User�̐V�K�o�^
// ���łɓo�^����Ă���UserID�̏ꍇ��false���Ԃ�
//----------------------------------------------------
bool CMySQLUserManager::SignUp( CONST std::string* userID, CONST std::string* userPass )
{
	// DB�ɐڑ�
	if( CMySQLManager::GetInstance()->ConnectDatabase() )
	{
		// ���ɓo�^����Ă��邩�ǂ����m�F( User ID�Ŋm�F )
		std::string  sqlString = COMBINE_STRING( 3, "userID = '", userID->c_str(), "'" );
		if( !CMySQLManager::GetInstance()->Search( USER_TABLE, sqlString ) )
		{
			// �o�^����
			// �V�K�o�^���邽�߂�SQL���쐬
			sqlString = COMBINE_STRING( 9, "'", "00004", "' ,'", "aiueo", "', '", userID->c_str(), "', '", userPass->c_str(), "'" );
			if( CMySQLManager::GetInstance()->Insert( USER_TABLE, sqlString ) )
			{
				// �o�^����
				return true;
			}
			// �o�^���s
			CMySQLManager::GetInstance()->UnConnectionDatabase();
			return false;
		}
		// ���łɓo�^����Ă���
		CMySQLManager::GetInstance()->UnConnectionDatabase();
		
		// �������b�Z�[�W���o��

		return false;
	}
	
	// MySQL�ڑ����s
	return false;
}
