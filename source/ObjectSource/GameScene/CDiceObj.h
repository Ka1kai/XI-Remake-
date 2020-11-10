//----------------------------------------------------
// CDiceObj
//�@3D�̃T�C�R���I�u�W�F�N�g
//
// @date	2013/11/20
// @author  T.Kawashita
//----------------------------------------------------
#ifndef _C_DICE_OBJ_H_
#define _C_DICE_OBJ_H_

#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/3D/C3DObjectAlphaBlend.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/GameMathHeader/CCollision.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/UtilityHeader/Macro.hpp"

#define ROLL_RIGTH_PIP	( 1 )
#define ROLL_LEFT_PIP	( 2 )
#define ROLL_FRONT_PIP	( 3 )
#define ROLL_BACK_PIP	( 4 )
#define ROLL_HALFH_PIP	( 5 )	// ���E180����]
#define ROLL_HALFV_PIP	( 6 )	// �㉺180����]

//----------------------------------------------------
// �X�e�[�^�X���
//----------------------------------------------------
typedef enum DICE_STATUS
{
	e_statusNone = 0,		// �o�����Ă��Ȃ�
	e_statusStartAppear,	// �o�����i�o�����n��:����)
	e_statusAppear,			// �o�����i�o�����F�����Ȃ��j
	e_statusNormal,			// �ʏ���
	e_statusStartDelete,	// �������i�����n��:�����Ȃ�)
	e_statusDelete			// �������i�����Ă���:����)
};

class CDiceObj : public C3DObjectAlphaBlend
{
private:	
	int			m_no;					// ���ʔԍ�
	int			m_indexNo;				// �Y�����ԍ�
	int			m_chainNo;				// �`�F�C���ԍ�
	D3DXVECTOR3	m_size;					// �_�C�X�̃T�C�Y
	D3DXVECTOR3	m_logPos;				// �ۑ��s��
	D3DXMATRIX	m_rotTemp;				// �ۑ���]�s��
	short		m_dicePipAllay[7];		// �_�C�X�̖ڂ��ۑ����ꂽ�z��( �Y������0�Ԃ͓���ւ��p�̃��[�N )
	int			m_animeCnt;				// �A�j���[�V�����p
	DICE_STATUS m_status;				// �X�e�[�^�X
	DICE_STATUS m_beforStatus;			// �O��̃X�e�[�^�X
	THITAABB*	m_pAABB;				// �����蔻��pAABB
	bool		m_isDice;				// ��������Ă��邩�ǂ���
	bool		m_isChain;				// �`�F�C�������ǂ���

public:
	// ���ʔԍ����Z�b�g
	void		SetNo		( CONST short no )
	{
		m_no = no;
	}
	// ���ʔԍ����擾
	CONST short GetNo		( void )
	{
		return m_no;
	}

	// �`�F�C�����Ă��邩�ǂ������Z�b�g
	void		SetIsChain	( CONST bool isChain )
	{
		m_isChain = isChain;
	}
	// �`�F�C�����Ă��邩�ǂ������擾
	CONST bool	GetIsChain	( void )
	{
		return m_isChain;
	}

	// �`�F�C���ԍ��̃Z�b�g
	void		SetChainNo	( CONST UINT chainNo )
	{
		m_chainNo = chainNo;
	}
	// �`�F�C���ԍ��̎擾
	CONST UINT GetChainNo	( void )
	{
		return m_chainNo;
	}

	// �Y�����ԍ����Z�b�g
	void		SetIndexNo	( CONST short indexNo )
	{
		m_indexNo = indexNo;
	}
	// �Y�����ԍ����擾
	CONST short	GetIndexNo	( void )
	{
		return m_indexNo;
	}

	// ��������Ă��邩�ǂ������Z�b�g
	void		SetIsDice	( CONST bool isDice )
	{
		m_isDice = isDice;
	}
	// ��������Ă��邩�ǂ������擾
	bool		GetIsDice	( void )
	{
		return m_isDice;
	}
	
	// �X�e�[�^�X���Z�b�g
	void		SetStatus	( CONST DICE_STATUS status )
	{
		m_status = status;
	}
	// �X�e�[�^�X���擾
	CONST DICE_STATUS GetStatus	( void )
	{
		return m_status;
	}

	// �O��̃X�e�[�^�X���Z�b�g
	void		SetBeforStatus ( CONST DICE_STATUS status )
	{
		m_beforStatus = status;
	}

	// �O��̃X�e�[�^�X���擾
	CONST DICE_STATUS GetBeforStatus ( void )
	{
		return m_beforStatus;
	}

	// �T�C�Y���Z�b�g
	void		SetSize		( CONST D3DXVECTOR3* size )
	{
		m_size.x = size->x;
		m_size.y = size->y;
		m_size.z = size->z;
	}
	// �T�C�Y���擾
	CONST D3DXVECTOR3*	GetSize		( void )
	{
		return &m_size;
	}

	// �����蔻��pAABB���Z�b�g
	void		SetAABB		( void )
	{
		D3DXVECTOR3 aabbPos = D3DXVECTOR3( this->GetXPos(), this->GetYPos(), this->GetZPos() );
		m_pAABB = CCollision::GetInstance()->SetAABB( m_pAABB, &aabbPos, &m_size );
	}
	// �����蔻��pAABB���擾
	CONST THITAABB*	GetAABB		( void )
	{
		return m_pAABB;
	}

public:
	CDiceObj			( void );	// �R���X�g���N�^
	virtual ~CDiceObj	( void );	// �f�X�g���N�^
	void	Init		( void );	// ������
	void	Uninit		( void );	// �I������

// ��]�݂̂̂��߂̃��\�b�h
public:
	//----------------------------------------------------
	// @name	InitRoll
	// @content	��]���鎞�̏�����
	// @param	none
	// @return	bool	���������s
	// @date	2014/2/3
	//----------------------------------------------------
	bool	InitRoll	( void );

	//----------------------------------------------------
	// @name	RollX,Y,Z
	// @content	��]
	// @param	degree	��]��
	// @return	none
	// @date	2013/11/25
	//----------------------------------------------------
	void	RollX		( float degree );	// X����]
	void	RollY		( float degree );	// Y����]
	void	RollZ		( float degree );	// Z����]

public:
	//----------------------------------------------------
	// @name	MoveX,Z
	// @content	�ړ��{��]
	// @param	x		�����ړ������邽�߂�x��	
	// @param	y		�����ړ������邽�߂�y��
	// @param	z		�����ړ������邽�߂�z��
	// @param	rotDir	��]����������x�N�g��( 1.0, -1.0f )
	// @param	speed	�X�s�[�h��
	// @return	none
	// @date	2013/11/26
	//----------------------------------------------------
	void	MoveX		( float x, float y, float z, float rotDir, float speed );	// X��]
	void	MoveZ		( float x, float y, float z, float rotDir, float speed );	// Z��]


// �ʐ���p�̃��\�b�h
public:
	//----------------------------------------------------
	// @name	InitPip
	// @content	�ʔ���p�z��̏�����
	// @param	none
	// @return	bool	���������s
	// @date	2014/2/3
	//----------------------------------------------------
	bool	InitPip		( void );

	//----------------------------------------------------
	// @name	GetPip
	// @content	�T�C�R���̏�ʂ̔ԍ��擾 
	//			���T�C�R���̖ʔz��̓Y�����P����ʂƂ��Ă���
	// @param	none	
	// @return	short			��ʔԍ�
	// @date	2013/11/27
	//----------------------------------------------------
	CONST	short	GetPip			( void )
	{
		return m_dicePipAllay[1];
	}

	//----------------------------------------------------
	// @name	RollChangePip
	// @content	��]���������ɉ�]�����������ɂ����
	//			�_�C�X�̖ڂ�����I�ɕς���
	// @param	rollState		��]�X�e�[�^�X
	// @return	none
	// @date	2013/11/27
	//----------------------------------------------------	
	void			RollChangePip	( CONST USHORT rollState );

	//----------------------------------------------------
	// @name	RollYChangePip
	// @content	Y��]�݂̂̏ꍇ��]�����������ɂ����
	//			�_�C�X�̖ڂ�����I�ɕς���
	// @param	rollState		��]�X�e�[�^�X	
	// @return	none
	// @date	2013/11/27
	// @update
	//----------------------------------------------------
	void			RollYChangePip	( void );

	//----------------------------------------------------
	// @name	SetUpperFacePip
	// @content	��ʂ��Z�b�g
	// @param	upperFace	�Z�b�g��������ʂ̔ԍ�(�P�`�U�j	
	// @return	none
	// @date	2013/11/26
	//----------------------------------------------------
	void			SetUpperPip		( CONST UINT upperFace );

	//----------------------------------------------------
	// @name	SetAroundFace
	// @content	����̖ʂ��Z�b�g
	// @param	rollNum		��]������񐔁i�O�`�R�j
	// @return	none
	// @date	2013/11/27
	//----------------------------------------------------
	void			SetAroundPip	( CONST UINT rollNum );

	//----------------------------------------------------
	// @name	SetPip
	// @content	��ʂƎ���̖ʂ𓯎��ɃZ�b�g
	// @param	upperFace	�Z�b�g��������ʂ̔ԍ��i�P�`�U�j
	// @param	rollNum		��]������񐔁i�O�`�R�j
	// @return	none
	// @date	2013/11/27
	//----------------------------------------------------
	void			SetPip				( CONST UINT upperFace, CONST UINT rollNum );

	//----------------------------------------------------
	// @name	DownAnimation
	// @content	�����Ă�������
	// @param	downSpeed		�����鑬�x
	// @return	bool			�����؂���or��苗�����������ǂ���
	// @date	2013/12/4
	// @update	2013/12/4		�����Ɩ߂�l�ǉ�
	//----------------------------------------------------
	bool			DownAnimation		( CONST float downSpeed );

	//----------------------------------------------------
	// @name	UpAnimatiion
	// @content	�o�Ă��鏈��
	// @param	upSpeed			�o�Ă��鑬�x
	// @return	bool			�o�Ă���or��苗���o�Ă������ǂ���
	// @date	2013/12/4
	//----------------------------------------------------
	bool			UpAnimation			( CONST float upSpeed );
};

#endif _C_DICE_OBJ_H_