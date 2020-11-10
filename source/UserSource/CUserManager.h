//----------------------------------------------------
// CUserManager 
//	���[�U�̊Ǘ��N���X
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
	// �R���X�g���N�^
	CUserManager	( void );
	CUserManager	( CONST CUserManager& userManager ){}	// �R�s�[�R���X�g���N�^�̋֎~
	CUserManager	operator=	( CONST CUserManager& userManager ){}	// �I�y���[�^�I�[�o���[�h�̋֎~

public:
	// �B��̃C���X�^���X�̎擾�ꏊ
	static CUserManager*	GetInstance	( void )
	{
		static CUserManager	pUserManager;
		return &pUserManager;
	}

	~CUserManager	( void );	// �f�X�g���N�^

public:
	//----------------------------------------------------
	// ������
	//----------------------------------------------------
	bool	Init			( void );
	bool	InitGameScore	( void );
	bool	Login			( void );	// ���O�C��

	//----------------------------------------------------
	// @name	SetGameScore
	// @content	�Q�[���X�R�A�̃Z�b�g
	// @param	pScore		�Q�[���ŏW�v�����X�R�A
	// @return	none
	// @date	2014/2/15
	//----------------------------------------------------
	void	SetGameScore	( CScore*	pScore );

	//----------------------------------------------------
	// �n�C�X�R�A�ƃX�R�A�̔�r
	//----------------------------------------------------
	bool	UpdateScore			( void );	// �X�R�A�̍X�V
	bool	RecordComparision	( void );	// ���R�[�h�̔�r
	bool	OnePipComparision	( void );	// �@�̖ڂ̔�r
	bool	TwoPipComparision	( void );	// �A�̖ڂ̔�r
	bool	ThreePipComparision	( void );	// �B�̖ڂ̔�r
	bool	FourPipComparision	( void );	// �C�̖ڔ�r
	bool	FivePipComparision	( void );	// �D�̖ڂ̔�r
	bool	SixPipComparision	( void );	// �E�̖ڂ̔�r
	bool	MaxChainComparision	( void );	// MaxChain�̔�r

};

#endif _C_USER_MANAGER_