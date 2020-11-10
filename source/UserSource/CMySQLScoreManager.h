//----------------------------------------------------
// CMySQLScoreManager
//	Score�e�[�u���̊Ǘ��N���X
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

// �g���e�[�u���̖��O
#define SCORE_TABLE "score"

class CMySQLScoreManager
{
private:
	std::string m_scoreID;
	std::string m_userID;
	std::string	m_userName;

public:
	CMySQLScoreManager();			// �R���X�g���N�^
	virtual ~CMySQLScoreManager();	// �f�X�g���N�^

	//----------------------------------------------------
	// ���[�U���̃Z�b�g
	//----------------------------------------------------
	void	SetUserInfo			( CONST std::string* userID, CONST std::string* userName )
	{
		m_userID = *userID;
		m_userName = *userName;
	}

public:
	//----------------------------------------------------
	// @name	UpdateHighScore
	// @content	�n�C�X�R�A�̍X�V
	// @param	updateSql	�X�V������SQL��
	// @return	bool		�n�C�X�R�A�̍X�V�����������s
	// @date	2014/2/19
	//----------------------------------------------------
	bool	UpdateHighScore		( CONST std::string* updateSql );

	//----------------------------------------------------
	// @name	GetTable
	// @content	�X�R�A�e�[�u���̎擾
	// @param	
	// @return	CScore
	// @date	2014/2/19
	//----------------------------------------------------
	CScore*	GetScore			( CScore* score );

};

#endif _C_MYSQL_SCORE_MANAGER_H_