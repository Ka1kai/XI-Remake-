//----------------------------------------------------
// CPlayer 
//	�v���C���[�̃N���X
//
// @date	2013/12/4
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_PLAYER_H_
#define _C_PLAYER_H_

#include <d3dx9.h>
#include "../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/2D/C2DBillBoard.h"
#include "../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"
#include "../KaiFrameWork/KaiFrameWorkHeader/GameMathHeader/CCollision.h"
#include "../SceneSource/DebugScene/CDebugMode.h"

// �v���C���[�̃X�e�[�^�X
typedef enum ePlayerStatus
{
	eOnStage,			// �X�e�[�W�̏�ɂ�����
	eOnDiceAppear,		// �_�C�X���o�����Ă����ɂ�����
	eOnDiceAppearStart,	// �_�C�X���o�����Ă����ɂ�����
	eOnDiceDelete,		// �_�C�X�������Ă����ɂ�����
	eOnDiceDeleteStart, // �_�C�X�̏����n�߂̏�ɂ�����
	eOnDice,			// �_�C�X�̏�ɂ�����
};

// �v���C���[�̈ړ��̃X�e�[�^�X
typedef enum ePlayerMoveStatus
{
	eMoveDice,
	eMoveRight,
	eMoveLeft,
	eMoveFront,
	eMoveBack,
	eMoveNone
};

class CPlayer : public C2DSprite
{
private:
	THITAABB*			m_pAABB;		// �����蔻��pAABB
	ePlayerStatus		m_status;		// �v���C���[�̃X�e�[�^�X
	ePlayerMoveStatus	m_moveStatus;	// �v���C���[�̈ړ��X�e�[�^�X

public:
	// �����蔻��pAABB���Z�b�g
	void		SetAABB	( void )
	{
		m_pAABB->centerPos.x = this->GetXPos();
		m_pAABB->centerPos.y = this->GetYPos();
		m_pAABB->centerPos.z = this->GetZPos();
	}
	// �����蔻��pAABB���擾
	THITAABB*	GetAABB	( void )
	{
		return m_pAABB;
	}
	
	// �v���C���[�̃X�e�[�^�X���Z�b�g
	void		SetPlayerStatus			( ePlayerStatus status = ePlayerStatus::eOnDice )
	{
		m_status = status;
	}
	// �v���C���[�̃X�e�[�^�X���擾
	ePlayerStatus		GetPlayerStatus ( void )
	{
		return m_status;
	}

	// �v���C���[�̈ړ��X�e�[�^�X���Z�b�g
	void				SetMoveStatus	( ePlayerMoveStatus status = ePlayerMoveStatus::eMoveNone )
	{
		m_moveStatus = status;
	}
	// �v���C���[�̈ړ��X�e�[�^�X���擾
	ePlayerMoveStatus GetMoveStatus	( void )
	{
		return m_moveStatus;
	}

public:
	// �R���X�g���N�^
	CPlayer				( void );

	// �f�X�g���N�^
	virtual ~CPlayer	( void );

	// ������
	bool	Init		( void );
	bool	Uninit		( void );

	//----------------------------------------------------
	// �ړ�
	//----------------------------------------------------
	void	MoveFront	( CONST float speed );	// �O�ړ�
	void	MoveBack	( CONST float speed );	// ��ړ�
	void	MoveRight	( CONST float speed );	// �E�ړ�
	void	MoveLeft	( CONST float speed );	// ���ړ�
	void	MoveDown	( CONST float speed );	// �_�E������
	void	MoveUp		( CONST float speed );	// �A�b�v����

};

#endif _C_PLAYER_H_