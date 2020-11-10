//----------------------------------------------------
// CScore 
//	�X�R�A
//
// @date	2014/2/9
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_SCORE_H_
#define _C_SCORE_H_

#include <Windows.h>

class CScore
{
public:
	UINT	m_oneChainNum;		// �_�C�X�P����������
	UINT	m_twoChainNum;		// �_�C�X�Q����������
	UINT	m_threeChainNum;	// �_�C�X�R����������	
	UINT	m_fourChainNum;		// �_�C�X�S����������
	UINT	m_fiveChainNum;		// �_�C�X�T����������
	UINT	m_sixChainNum;		// �_�C�X�U����������
	UINT	m_chainNum;			// �R���{��
	UINT	m_maxLinkNum;		// �ő僊���N��
	UINT	m_record;			// �X�R�A

public:
	//----------------------------------------------------
	// �R���X�g���N�^
	//----------------------------------------------------
	CScore		( void )
	{
		m_oneChainNum = 0;
		m_twoChainNum = 0;
		m_threeChainNum = 0;
		m_fourChainNum = 0;
		m_fiveChainNum = 0;
		m_sixChainNum = 0;
		m_chainNum = 0;
		m_maxLinkNum = 0;
		m_record = 0;
	}

	//----------------------------------------------------
	// �f�X�g���N�^
	//----------------------------------------------------
	~CScore		( void )
	{
	}

public:
	//----------------------------------------------------
	// ������
	//----------------------------------------------------
	bool	Init			( void )
	{
		m_oneChainNum = 0;
		m_twoChainNum = 0;
		m_threeChainNum = 0;
		m_fourChainNum = 0;
		m_fiveChainNum = 0;
		m_sixChainNum = 0;
		m_chainNum = 0;
		m_maxLinkNum = 0;
		m_record = 0;

		return true;
	}

	//----------------------------------------------------
	// @name	PipScoreAdd
	// @content	��ʂɂ���ăX�R�A�W�v
	// @param	pip		���������
	// @param	diceNum	��������
	// @return	none
	// @date	2014/2/12
	//----------------------------------------------------
	void	PipScoreAdd		( CONST UINT pip, CONST UINT diceNum )
	{
		switch( pip )
		{
		case 1:
			m_oneChainNum += diceNum;
			break;
		case 2:
			m_twoChainNum += diceNum;
			break;
		case 3:
			m_threeChainNum += diceNum;
			break;
		case 4:
			m_fourChainNum += diceNum;
			break;
		case 5:
			m_fiveChainNum += diceNum;
			break;
		case 6:
			m_sixChainNum += diceNum;
			break;
		}
	}
};

#endif _C_SCORE_H_