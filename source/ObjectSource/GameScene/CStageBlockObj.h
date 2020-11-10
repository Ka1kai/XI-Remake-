//----------------------------------------------------
// CStageBlockObj  
//	�X�e�[�W�̃u���b�N�I�u�W�F�N�g
//
// @date	2013/11/29
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_STAGE_BLOCK_OBJ_
#define _C_STAGE_BLOCK_OBJ_

#include "CDiceObj.h"

class CStageBlockObj
{
private:
	int				m_no;
	D3DXVECTOR3		m_pos;
	CDiceObj*		m_pDice;
	bool			m_isOnDice;
	bool			m_isOnPlayer;

public:
	// �R���X�g���N�^
	CStageBlockObj		( void );

	// �f�X�g���N�^
	~CStageBlockObj		( void );

	// ������
	bool		Init	( void );

public:

	//----------------------------------------------------
	// �ʒu�����擾
	//----------------------------------------------------
	D3DXVECTOR3* GetPosition		( void )
	{
		return &m_pos;
	}

	//----------------------------------------------------
	// �X�e�[�W�̃u���b�N�ɏ���Ă���_�C�X�̎擾 
	//----------------------------------------------------
	CDiceObj*		GetDice			( void )
	{
		return m_pDice;
	}

	//----------------------------------------------------
	// @name	CheckOnDice
	// @content	�_�C�X�����邩�ǂ����擾
	// @param	none	
	// @return	bool	���邩�Ȃ���
	// @date	2013/11/29
	//----------------------------------------------------
	bool		CheckOnDice		( void );

	//----------------------------------------------------
	// @name	CheckOnPlayer
	// @content	�v���C���[������Ă��邩�ǂ����擾
	// @param	none
	// @return	bool	����Ă��邩�ǂ���
	// @date	2014/1/30
	//----------------------------------------------------
	bool		CheckOnPlayer	( void );

	//----------------------------------------------------
	// @name	SetPostion
	// @content	�u���b�N�̃|�W�V�������Z�b�g
	// @param	x		X���W
	// @param	y		Y���W
	// @param	z		Z���W	
	// @return	none
	// @date	2013/11/29
	//----------------------------------------------------
	void		SetPosition		( float x, float y, float z );

	//----------------------------------------------------
	// @name	SetDice
	// @content	�_�C�X���Z�b�g
	// @param	dice	�Z�b�g�������_�C�X�̃I�u�W�F�N�g�̃|�C���^
	// @return	none
	// @date	2013/11/29
	//----------------------------------------------------
	void		SetDice			( CDiceObj*	dice );

	//----------------------------------------------------
	// @name	SetNo
	// @content	�ԍ��̃Z�b�g
	// @param	no		�Z�b�g�������ԍ�
	// @return	none
	// @date	2013/12/2
	//----------------------------------------------------
	void		SetNo			( CONST UINT no );

	//----------------------------------------------------
	// @name	SetIsOnDice
	// @content	�_�C�X������Ă��邩�ǂ����̃t���O���Z�b�g
	// @param	isDice		�t���O
	// @return	none
	// @date	2013/12/2
	//----------------------------------------------------
	void		SetIsOnDice		( CONST bool isDice );

	//----------------------------------------------------
	// @name	SetIsOnPlayer
	// @content	�v���C���[������Ă��邩�ǂ����̃t���O���Z�b�g
	// @param	isPlayer	�t���O
	// @return	none
	// @date	2014/1/30
	//----------------------------------------------------
	void		SetIsOnPlayer	( CONST bool isPlayer );

	//----------------------------------------------------
	// @name	Draw
	// @content	�X�e�[�W�̃u���b�N��`��
	// @param	none
	// @return	none
	// @date	2013/12/2
	//----------------------------------------------------
	void		Draw			( void );

};

#endif _C_STAGE_BLOCK_OBJ_