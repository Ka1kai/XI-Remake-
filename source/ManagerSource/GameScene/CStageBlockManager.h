//----------------------------------------------------
// CStageBlock
//	�X�e�[�W�̃_�C�X�̊Ǘ��N���X
//
// @date	2013/11/28
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_STAGE_BLOCK_MANAGER_H_
#define _C_STAGE_BLOCK_MANAGER_H_

#include <Windows.h>

#include "../../GameMathSource/CDiceRandSystem.h"
#include "../../ObjectSource/GameScene/CStageBlockObj.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/UtilityHeader/Macro.hpp"

#define BLOCK_SIZE			( 4.0f )	// �}�X�ڈ�̑傫��
#define BLOCK_MAXSIZE		( 12.0f )	// �X�e�[�W�̍ő�̑傫��
#define BLOCK_DEFAULT_NUM_X	( 7 )		// �f�t�H���g�̃X�e�[�W��X�}�X�ڐ�
#define BLOCK_DEFAULT_NUM_Y	( 1 )		// �f�t�H���g�̃X�e�[�W��Y�}�X�ڐ�
#define BLOCK_DEFAULT_NUM_Z	( 7 )		// �f�t�H���g�̃X�e�[�W��Z�}�X�ڐ�

// �f�t�H���g�̃X�e�[�W�̃u���b�N�̐�
#define BLOCK_DEFAULT_MAX_NUM	( BLOCK_DEFAULT_NUM_X * BLOCK_DEFAULT_NUM_Y * BLOCK_DEFAULT_NUM_Z )

class CStageBlockManager
{
private:
	CStageBlockObj	m_stageBlock[ BLOCK_DEFAULT_MAX_NUM ];		// �X�e�[�W�̃u���b�N�n�a�i

	USHORT	m_blockNum;				// �X�e�[�W�̃u���b�N��

	USHORT	m_xNum;					// �X�e�[�W�̃u���b�N��X�}�X�ڐ�
	USHORT	m_yNum;					// �X�e�[�W�̃u���b�N��Y�}�X�ڐ�
	USHORT	m_zNum;					// �X�e�[�W�̃u���b�N��Z�}�X�ڐ�

	// �R���X�g���N�^
	CStageBlockManager			( void );
	CStageBlockManager	( CONST CStageBlockManager& stageBlockManager ){}	// �R�s�[�R���X�g���N�^��h��
	CStageBlockManager	operator=	( CONST CStageBlockManager& stageBlockManager ){}	// �����o�̑����h��

public:
	// �C���X�^���X�擾�ꏊ
	static CStageBlockManager* GetInstance( void )
	{
		static CStageBlockManager stageBlockManager;
		return &stageBlockManager;
	}

	// �X�e�[�W�̃u���b�N�n�a�i�̎擾
	CStageBlockObj* GetStageBlock	( CONST UINT index )
	{

		return &m_stageBlock[ index ];
	}

public:
	//----------------------------------------------------
	// �}�X�ڐ��擾
	//----------------------------------------------------
	CONST USHORT	GetXNum		( void )
	{
		return m_xNum;
	}
	CONST USHORT	GetYNum		( void )
	{
		return m_yNum;
	}
	CONST USHORT	GetZNum		( void )
	{
		return m_zNum;
	}

private:
	float			m_xSize;				// �X�e�[�W�̃u���b�N�ő剡�T�C�Y
	float			m_ySize;				// �X�e�[�W�̃u���b�N�ő�c�T�C�Y
	float			m_zSize;				// �X�e�[�W�̃u���b�N�ő剜�s�T�C�Y

public:
	//----------------------------------------------------
	// �T�C�Y�擾
	//----------------------------------------------------
	CONST float	GetXSize	( void )
	{
		return m_xSize;
	}
	CONST float	GetYSize	( void )
	{
		return m_ySize;
	}
	CONST float	GetZSize	( void )
	{
		return m_zSize;
	}

public:
	
	// �f�X�g���N�^
	~CStageBlockManager			( void );

	//----------------------------------------------------
	// ������
	//----------------------------------------------------
	bool		Init		( void );

	//----------------------------------------------------
	// @name	SetStagePos
	// @content	�X�e�[�W�̃u���b�N�ʒu�����Z�b�g(�f�t�H���g�l)	
	// @param	none
	// @return	none
	// @date	2013/11/29
	//----------------------------------------------------
	void		SetBlockPos	( void );

	//----------------------------------------------------
	// @name	SetStagePos
	// @content	�X�e�[�W�̃u���b�N�ʒu�����Z�b�g	
	// @param	xNum		����
	// @param	yNum		����
	// @param	zNum		����
	// @return	none
	// @date	2013/11/29
	//----------------------------------------------------
	bool		SetBlockPos	( CONST UINT xNum, CONST UINT yNum, CONST UINT zNum );

	//----------------------------------------------------
	// @name	GetIndexToDicePos
	// @content	�u���b�N�̃C���f�b�N�X���_�C�X�̈ʒu����擾
	// @param	xPos		X���W
	// @param	zPos		Z���W
	// @return	UINT		�u���b�N�C���f�b�N�X�ԍ�
	// @date	2013/12/2
	// @update	2014/2/1	���� Y���W���͂����܂���
	//----------------------------------------------------
	CONST UINT GetIndexToDicePos	( CONST float xPos, CONST float zPos );

	//----------------------------------------------------
	// @name	GetIndexToPlayerPos
	// @content	�u���b�N�̃C���f�b�N�X���v���C���[�ʒu����擾
	// @param	xPos		X���W
	// @param	zPos		Z���W
	// @return	UINT		�u���b�N�C���f�b�N�X�ԍ�
	// @date	2014/2/1
	// @update
	//----------------------------------------------------
	CONST UINT GetIndexToPlayerPos	( CONST float xPos, CONST float zPos );

	//----------------------------------------------------
	// @name	GetPos
	// @content	�u���b�N�̈ʒu��Y��������ʒu�擾
	// @param	index			�Y����
	// @return	D3DXVECTOR3*
	// @date	2013/12/2
	//----------------------------------------------------
	D3DXVECTOR3*	GetPos	( UINT index )
	{
		return m_stageBlock[ index ].GetPosition();
	}

	//----------------------------------------------------
	// @name	GetBlockIndexRnd
	// @content	�����_���Ńu���b�N�̓Y�������擾
	// @param	none
	// @return	UINT	�ʒu���
	// @date	2013/12/2
	//----------------------------------------------------
	CONST UINT	GetBlockIndexRnd	( void )
	{
		unsigned int rnd = CDiceRandSystem::GetInstance()->GetPos( m_blockNum );
		return rnd;
	}

	//----------------------------------------------------
	// @name	GetDiceNum
	// @content	�X�e�[�W�̃u���b�N�̐����擾
	// @param	none
	// @return	UINT		�u���b�N�̍ő吔
	// @date	2013/12/2
	//----------------------------------------------------
	CONST UINT	GetDiceNum		( void )
	{
		return m_blockNum;
	}

	//----------------------------------------------------
	// @name	GetIsOnDice
	// @content	�u���b�N��Ƀ_�C�X�����邩�ǂ����擾
	// @param	diceNo		���ׂ����Y�����ԍ�
	// @return	bool		���邩�Ȃ���
	// @date	2013/12/2
	//----------------------------------------------------
	bool		GetIsOnDice	( CONST UINT diceNo  )
	{
		if( diceNo >= 0 )
			return m_stageBlock[ diceNo ].CheckOnDice();

		else 
			return 0;
	}

	//----------------------------------------------------
	// @name	SetBlockToDice
	// @content	�u���b�N�Ƀ_�C�X�̏����Z�b�g
	// @param	CDiceObj*		�_�C�X�{��
	// @param	diceNo			�_�C�X�̔ԍ�
	// @return	none
	// @date	2013/12/2
	//----------------------------------------------------
	void		SetBlockToDiceInfo	( CDiceObj* dice, int diceNo );

	//----------------------------------------------------
	// @name	SetIsOnDice
	// @content	�_�C�X������Ă��邩�ǂ����̃t���O���Z�b�g
	// @param	diceNo		�Z�b�g�������_�C�X�̔ԍ�
	// @param	isDice		true or false
	// @return	none 
	//----------------------------------------------------
	void		SetIsOnDice	( CONST UINT diceNo, bool isDice )
	{
		m_stageBlock[ diceNo ].SetIsOnDice( isDice );
	}
};


#endif _C_STAGE_BLOCK_MANAGER_H_