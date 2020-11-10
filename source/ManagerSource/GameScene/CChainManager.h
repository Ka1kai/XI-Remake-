//----------------------------------------------------
// CChainManager
//	�u���b�N���Ȃ��������̏���
//
// @date	2013/12/2
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_CHAIN_MANAGER_H_
#define _C_CHAIN_MANAGER_H_

#include <list>
#include <vector>
#include "../../ObjectSource/GameScene/CDiceObj.h"
#include "CStageBlockManager.h"
#include "../../PlayerSource/CPlayerManager.h"
#include "../../ObjectSource/CScore.hpp"

typedef struct TagChain
{
	bool	isChain;			// �`�F�C�������ǂ���
	UINT	chainNo;			// �`�F�C���ԍ�
	UINT	chainPip;			// �`�F�C�����Ă�����
	UINT	chainNum;			// �`�F�C�����Ă��鐔
	UINT	chainDiceNum;		// �`�F�C�����Ă���_�C�X�̐�
}tagChain;

class CChainManager
{
private:
	std::list< CDiceObj* >		m_connectDiceList;		// �q�������_�C�X�i�[�p���X�g
	tagChain	m_chain[50];							// �`�F�C���Ǘ��\���̔z��
	int		m_connectDiceNum;							// �Ȃ����Ă��鐔
	int		m_mainPip;									// ���C���_�C�X�̏�ʕۑ��p
	int		m_xNum;		
	int		m_yNum;
	int		m_zNum;
	bool	m_decisionBlock[BLOCK_DEFAULT_MAX_NUM];		// ���肵�����ǂ����̔z��

	CScore*	m_pScore;									// �X�R�A�Ǘ��N���X����󂯎��X�R�A�̃|�C���^

	// �R���X�g���N�^
	CChainManager	( void );
	CChainManager	( CONST CChainManager& chainManager ){}	// �R�s�[�R���X�g���N�^��h��
	CChainManager	operator=	( CONST CChainManager& chainManager ){}	// �����o�̑����h��


public:
	// �B��̃C���X�^���X�̎擾�ꏊ
	static CChainManager*	GetInstance	( void )
	{
		static CChainManager chainManager;
		return &chainManager;
	}

	// �f�X�g���N�^
	~CChainManager	( void );

	//----------------------------------------------------
	// �X�e�[�W�T�C�Y���Z�b�g
	//----------------------------------------------------
	void		SetSize					( void )
	{
		m_xNum = CStageBlockManager::GetInstance()->GetXNum();
		m_yNum = CStageBlockManager::GetInstance()->GetYNum();
		m_zNum = CStageBlockManager::GetInstance()->GetZNum();
	}

	//----------------------------------------------------
	// ������
	//----------------------------------------------------
	bool		Init					( void );

	//----------------------------------------------------
	// �X�R�A�̃|�C���^���Z�b�g
	//----------------------------------------------------
	void		SetScore				( CScore* score )
	{
		m_pScore = score;
	}

	//----------------------------------------------------
	// @name	SetStageBlockDiceStatus
	// @content	�u���b�N��̃_�C�X�̃X�e�[�^�X��ݒ�
	// @param	index		�ύX�������_�C�X�̃C���f�b�N�X�ԍ�
	// @return	none
	// @date	2013/12/9
	//----------------------------------------------------
	void		SetStageBlockDiceStatus	( CONST UINT index );

	//----------------------------------------------------
	// @name	Chain
	// @content	�Ȃ������Ƃ��̏���
	// @param	index		���C���u���b�N�̃C���f�b�N�X�ԍ�
	// @return	none
	// @date	2013/12/2
	// @update	2013/12/3
	//----------------------------------------------------
	void		Chain				( CONST UINT index );

public:
	//----------------------------------------------------
	// @name	CheckAround
	// @content	����̃_�C�X�Ƃ̔���(�ċA�֐�)
	// @param	index		�u���b�N�̃C���f�b�N�X�ԍ�
	// @return	none		
	// @date	2013/12/3
	//----------------------------------------------------
	int			CheckAround			( CONST UINT index );
	
	bool		CheckRight			( CONST UINT index );		// �E��������
	bool		CheckLeft			( CONST UINT index );		// ����������
	bool		CheckFront			( CONST UINT index );		// �O��������
	bool		CheckDown			( CONST UINT index );		// ���������

	//----------------------------------------------------
	// @name	CheckOne
	// @content	�P�̖ڂ��ǂ����𔻒�
	// @param	index		�������g�̃C���f�b�N�X�ԍ�
	// @return	none
	// @date	2014/2/4
	// @update	������ǉ��i�������g�͏����Ă͂����Ȃ��j
	//----------------------------------------------------
	void		CheckOne			( CONST UINT index );

	//----------------------------------------------------
	// @name	CheckChain
	// @content	����̖ʂ������Ă��邩�ǂ����`�F�b�N
	// @param	index		���ׂ����C���f�b�N�X�ԍ�	
	// @return	bool		�`�F�C�����Ă���
	// @date	2014/2/5
	//----------------------------------------------------
	bool		CheckChain			( CONST UINT index );

	//----------------------------------------------------
	// @name	CheckChain
	// @content	����̖ʂ����ׂ�����ʂŏ����Ă��邩�ǂ����`�F�b�N	
	// @param	index		���ׂ����C���f�b�N�X�ԍ�
	// @param	pip			���ׂ�����ʔԍ�
	// @return	bool		���ׂ�����ʔԍ��Ń`�F�C�����Ă���	
	// @date	2014/2/10
	//----------------------------------------------------
	bool		CheckChain			( CONST UINT index, CONST UINT pip );

	//----------------------------------------------------
	// �`�F�C���Ǘ��z����擾
	//----------------------------------------------------
	tagChain*	GetChain			( CONST UINT chainNo )
	{
		return &m_chain[ chainNo ];
	}
};



#endif _C_CHAIN_MANAGER_H_