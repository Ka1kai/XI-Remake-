//----------------------------------------------------
// CMySQLBase
//	MySQL�ɂȂ��A��{�I��SQL�������s���邽�߂̂���
//
// @author  T.Kawashita
// @date	2013/11/11
//----------------------------------------------------
#ifndef _C_MYSQL_MANAGER_H_
#define _C_MYSQL_MANAGER_H_

#include <Windows.h>
#include <mysql.h>
#include <string>

// �f�[�^�x�[�X���
#define HOST_NAME ( NULL )
#define USER_NAME ( "Kaikai" )
#define PASS_WORD ( "tkwaterki7" )
#define DATA_BASE ( "XI_Remakedb" )
#define PORT_NUM  ( 0 )

class CMySQLManager
{
private:

	MYSQL* m_pMySql;
	MYSQL_RES*	m_pResult;

	// �R���X�g���N�^
	CMySQLManager	( void )
	{
		m_pMySql = mysql_init( NULL );
		// MySQL�̏������̐������ۂ�
		if( m_pMySql == NULL )
		{
			MessageBox( NULL,"MySQL���������s","InitError",MB_OK );
		}
		
	}
	CMySQLManager	( CONST CMySQLManager& mysqlManager );				// �R�s�[�R���X�g���N�^�֎~
	CMySQLManager	operator=	( CONST CMySQLManager& mysqlManager );	// �����o�̑����h��

public:
	// �f�X�g���N�^
	~CMySQLManager	( void )
	{
		mysql_server_end();		// MySQL���I��
	}

	//----------------------------------------------------
	// �C���X�^���X�̗B��̎擾�ꏊ
	//----------------------------------------------------
	static CMySQLManager* GetInstance ( void )
	{
		static CMySQLManager mysqlManager;
		return &mysqlManager;
	}
	
	//----------------------------------------------------
	// @name	ConnectDatabase
	// @content	�f�[�^�x�[�X�ւ̐ڑ�(�����Ȃ�)
	// @param	none
	// @return	bool		���������s
	// @date	2013/11/11
	//----------------------------------------------------
	bool ConnectDatabase		( void )
	{
		m_pMySql = mysql_init( NULL );
		if( mysql_real_connect( m_pMySql, HOST_NAME, USER_NAME, PASS_WORD, DATA_BASE, PORT_NUM,NULL, 0 ) == NULL )
		{
//			MessageBox( NULL, mysql_error( m_pMySql ), "MySQL�ڑ��G���[", MB_OK );
			return false;
		}

		return true;
	}

	//----------------------------------------------------
	// @name	ConnectDatabase
	// @content	�f�[�^�x�[�X�ւ̐ڑ�(��������)
	// @param	dataBase	�ڑ��������f�[�^�x�[�X��
	// @return	bool		���������s
	// @date	2013/11/11
	//----------------------------------------------------	
	bool ConnectDatabase		( CONST std::string dataBase )
	{
		m_pMySql = mysql_init( NULL );
		if( mysql_real_connect( m_pMySql, HOST_NAME, USER_NAME, PASS_WORD, dataBase.c_str(), PORT_NUM,NULL, 0 ) == NULL )
		{
			MessageBox( NULL, mysql_error( m_pMySql ), "MySQL�ڑ��G���[", MB_OK );
			return false;	// ���s
		}

		return true;		// ����
	}

	//----------------------------------------------------
	// @name	Search(�e�[�u�����݂̂̎w��)
	// @content	��������
	// @param	searchResultFd	�������ʂ�ۑ�����t�B�[���h
	// @param	table			�e�[�u����
	// @return	MYSQL_FIELD*	��������
	// @date	2013/11/11
	//----------------------------------------------------
	CONST MYSQL_FIELD* Search	( MYSQL_FIELD* searchResultFd, CONST std::string table )
	{
		std::string sql = "SELECT * FROM " + table;
		if( this->Query( sql ) == true )
		{
			m_pResult = mysql_store_result( m_pMySql );		// �������ʂ�ۑ�
			
			if( m_pResult == NULL || mysql_errno( m_pMySql ) != 0 )
			{
				return NULL;
			}

			// ���������ꍇ�͗�̏���MYSQL_FIELD�^�̕ϐ��ɃZ�b�g
			searchResultFd = mysql_fetch_field( m_pResult );
	
			return searchResultFd;
		}
	}

	//----------------------------------------------------
	// @name	Search(�e�[�u�����E�񖼁E�������j
	// @content	��������
	// @param	searchResultFd	�������ʂ�ۑ�����t�B�[���h
	// @param	table			�e�[�u����
	// @param	column			��
	// @param	condition		������
	// @return	MYSQL_FIELD*	��������
	// @date	2014/2/19
	//----------------------------------------------------
	CONST MYSQL_ROW Search	( MYSQL_ROW searchResultFd, CONST std::string* table, CONST std::string* column, CONST std::string* condition )
	{
		std::string sql = "SELECT " + *column + " FROM " + *table + " WHERE " + *condition;
		// �N�G�����s
		if( this->Query( sql ) == true )
		{
			m_pResult = mysql_store_result( m_pMySql );	// �������ʂ�ۑ�
			if( m_pResult == NULL || mysql_errno( m_pMySql ) != 0 )
			{
				// �����G���[
				return false;
			}

			// ���������ꍇ�͗�̏���MYSQL_FIELD�^�̕ϐ��ɃZ�b�g
			searchResultFd = mysql_fetch_row( m_pResult );

			return searchResultFd;
		}
		return searchResultFd;
	}

	//----------------------------------------------------
	// @name	Search(�e�[�u�����Ɨ񖼂��w��)
	// @content ��������
	// @param	fd			�������ʂ�ۑ�����t�B�[���h
	// @param	table		�e�[�u����
	// @param	column		��
	// @return	bool		���邩�ǂ���
	// @date	2013/11/11
	//----------------------------------------------------
	bool Search		(  CONST std::string table, CONST std::string condition )
	{
		std::string sql = "SELECT * FROM " + table + " WHERE " + condition + ";";
		if( this->Query( sql ) == true )
		{
			m_pResult = mysql_store_result( m_pMySql );
			if( m_pResult == NULL || mysql_errno( m_pMySql ) != 0 || m_pResult->row_count == 0 )
			{
				return false;
			}
			
			// ���ʂ̔j��
			mysql_free_result( m_pResult );
			return true;
		}

		return false;
	}

	//----------------------------------------------------
	// @name	CreateTable
	// @content	�e�[�u���̍쐬
	// @param	table	�e�[�u����
	// @return	bool	���������s
	// @date	2013/11/11
	// @comment	�������Ă��܂���B
	//----------------------------------------------------
	bool CreateTable			( CONST std::string table, CONST std::string )
	{
	}

	//----------------------------------------------------
	// @name	Insert
	// @content	��̒ǉ�
	// @param	table		�ǉ��������e�[�u����
	// @param	condition	����
	// @return	bool		���������s
	// @date	2013/11/11
	//----------------------------------------------------
	bool Insert					( CONST std::string table, std::string condision )
	{
		std::string sql = " INSERT INTO " + table + " VALUES ( " + condision + " ); " ;

		if( this->Query( sql ) == true )
		{
			// �ǉ�����
			return true;
		}
		
		// �ǉ����s
		return false;
	}

	//----------------------------------------------------
	// @name	Update
	// @content	�w���̍X�V
	// @param	table		�e�[�u����
	// @param	column		�w���
	// @param	condition	����
	// @return	bool		�X�V�ł������o���Ȃ�������
	// @date	2013/11/11
	//----------------------------------------------------
	bool Update					( CONST std::string* table, CONST std::string* column, CONST std::string* condition )
	{
		std::string sql = " UPDATE " + *table + " SET " +  *column + " WHERE " + *condition;
		if( this->Query( sql ) == true )
		{
			// �X�V
			return true;
		}

		// �X�V�ł��Ȃ�
		return false;
	}

	//----------------------------------------------------
	// @name	Query
	// @content	SQL���̎��s
	// @param	sql			sql��
	// @return	bool		���������s��
	// @date	2013/10/10
	//----------------------------------------------------
	bool Query					( CONST std::string sql )
	{
		mysql_query( m_pMySql, sql.c_str() );	// SQL���̎��s
		if( mysql_errno( m_pMySql ) != NULL )
		{
			MessageBox( NULL, mysql_error( m_pMySql ), "�N�G���̔��s���s", MB_OK );
			return false;
		}

		return true;		// �N�G�����s����
	}

	//----------------------------------------------------
	// @name	UnConnectionDatabase
	// @content	�f�[�^�x�[�X����̐ؒf
	// @param	none
	// @return	�ؒf�ł������o���Ȃ�������
	// @date	2013/11/11
	//----------------------------------------------------
	bool UnConnectionDatabase	( void )
	{
		if( m_pMySql != NULL )
		{
			mysql_close( m_pMySql );
		}
		return true;
	}

	//----------------------------------------------------
	// @name	DestroyResult
	// @content	���U���g���̔j��
	// @param	none
	// @return	bool	�j���ł������ǂ���
	// @date	2014/2/20
	// @update	none
	//----------------------------------------------------
	bool DestroyResult			( void )
	{
		mysql_free_result( m_pResult );		
	}
};

#endif	_C_MYSQL_BASE_H_