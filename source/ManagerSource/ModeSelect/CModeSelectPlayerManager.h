//----------------------------------------------------
// CModeSelectPlayerManager 
//	���[�h�Z���N�g��ʂ̃v���C���[�̃}�l�[�W���[
//	
// @date	2014/2/7
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_MODESELECT_PLAYER_MANAGER_
#define _C_MODESELECT_PLAYER_MANAGER_

#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/2D/C2DSprite.h"

//----------------------------------------------------
// ���[�h�Z���N�g�p�v���C���[�ړ��X�e�[�^�X
//----------------------------------------------------

typedef enum EMoveSelectMovePlayerStatus
{
	eModeSelectPlayerMoveNone,
	eModeSelectPlayerMoveRight,
	eModeSelectPlayerMoveLeft,
	eModeSelectPlayerMoveUp,
	eModeSelectPlayerMoveDown,
}eModeSelectMovePlayerStatus;

class CModeSelectPlayerManager
{
private:
	C2DSprite*		m_pModeSelectPlayer;
	LPSTR			m_pResModeSelectPlayerPath;

	eModeSelectMovePlayerStatus		m_eMovePlayerStatus;
	float			m_moveValue;	// ��������

public:
	CModeSelectPlayerManager	( void );
	~CModeSelectPlayerManager	( void );

public:
	// �v���C���[�̃X�e�[�^�X���Z�b�g
	void	SetMovePlayerStatus		( CONST eModeSelectMovePlayerStatus playerStatus )
	{
		m_eMovePlayerStatus = playerStatus;
	}

	// �v���C���[�̃X�e�[�^�X���擾
	eModeSelectMovePlayerStatus GetMovePlayerStatus	( void )
	{
		return m_eMovePlayerStatus;
	}

public:
	bool	Init		( void );
	void	Run			( void );
	void	Draw		( void );
	bool	Uninit		( void );

public:
	void	MoveRight	( CONST float speed );
	void	MoveLeft	( CONST float speed );
	void	MoveUp		( CONST float speed );
	void	MoveDown	( CONST float speed );

};


#endif _C_MODESELECT_PLAYER_MANAGER_