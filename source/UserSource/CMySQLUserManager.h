//----------------------------------------------------
// CMySQLUserManager
//	������User�e�[�u���̊Ǘ��N���X
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

// �g���e�[�u���̖��O
#define USER_TABLE "User"

class CMySQLUserManager
{
private:
	std::string m_userID;	// UserID
	std::string m_id;		// User���ݒ肵��ID
	std::string m_pass;		// User���ݒ肵���p�X���[�h
	std::string m_userName;	// User�̖��O

public:
	// UserID�̎擾
	std::string*	GetIDUser	( void )
	{
		return &m_userID;
	}
	// UserName�̎擾
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
	// @content	���O�C��
	// @param	loginID		���O�C��ID
	// @param	loginPass	���O�C���p�X���[�h
	// @return	bool		���O�C�����������s
	// @date	2013/11/15
	//----------------------------------------------------
	bool Login ( CONST std::string* loginID, CONST std::string* loginPass );

	//----------------------------------------------------
	// @name	SignUp
	// @content	���[�U�̐V�K�o�^
	// @param	userID		�o�^���������[�UID	
	// @param	userPass	�o�^���������[�U�p�X���[�h
	// @return	bool		�o�^�̐��������s
	// @date	2013/11/15	
	//----------------------------------------------------
	bool SignUp	( CONST std::string* userID, CONST std::string* userPass );

};

#endif _C_MYSQL_USER_MANAGER_H_