//----------------------------------------------------
// CPlayerManager 
//	�v���C���[�̊Ǘ��N���X
//
// @date	2013/12/12
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_PLAYER_MANAGER_H_
#define _C_PLAYER_MANAGER_H_

#include <d3dx9.h>
#include "CPlayer.h"

#include "../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CInputKeyboard.hpp"
#include "../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CJoyStick.hpp"
#include "../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"
#include "../SceneSource/DebugScene/CDebugMode.h"
#include "../ManagerSource/GameScene/CDiceObjManager.h"
#include "../ManagerSource/GameScene/CStageBlockManager.h"
#include "../ManagerSource/GameScene/CDiceInfoManager.h"

class CPlayerManager
{
private:
	CPlayer*			m_pPlayer;
	LPSTR				m_pPlayerFilePath;	// �v���C���[�̉摜�t�@�C���p�X
	CDiceInfoManager*	m_pDiceInfoManager;

	// �R���X�g���N�^
	CPlayerManager	( void );
	CPlayerManager	( CONST CPlayerManager& playerManager ){}	// �R�s�[�R���X�g���N�^�֎~
	CPlayerManager	operator= ( CONST CPlayerManager& playerManager ){}	// �I�y���[�^�I�[�o���[�h�֎~ 

public:
	// �C���X�^���X�擾�ꏊ
	static CPlayerManager* GetInstance( void )
	{
		static CPlayerManager playerManager;
		return &playerManager;
	}

public:

	// �f�X�g���N�^
	~CPlayerManager	( void );

	//----------------------------------------------------
	// ������
	//----------------------------------------------------
	bool	Init	( void );

	//----------------------------------------------------
	// �I��
	//----------------------------------------------------
	bool	Uninit	( void );

	//----------------------------------------------------
	// �`��
	//----------------------------------------------------
	void	Draw	( void );

	//----------------------------------------------------
	// �v���C���[�̏���
	//----------------------------------------------------
	void	Run		( void );

	//----------------------------------------------------
	// @name	Move
	// @content	�v���C���[�̈ړ�
	// @param	none
	// @return	none	
	// @date	2013/12/13
	//----------------------------------------------------
	void	Move		( void );

	//----------------------------------------------------
	// �e�����ֈړ� 
	//----------------------------------------------------
	void	MoveRight	( void );
	void	MoveLeft	( void );
	void	MoveFront	( void );
	void	MoveBack	( void );

	//----------------------------------------------------
	// @name	IsHitPlayerToDiceX,Z
	// @content �v���C���[�ƃ_�C�X�̓����蔻��
	// @param	distance		�����p�l
	// @return	bool			�������Ă��Ȃ���ԂɂȂ�����true
	// @date	2014/1/30
	//----------------------------------------------------
	bool	IsHitPlayerToDiceX	( CONST float distance, CDiceObj* dice );
	bool	IsHitPlayerToDiceZ	( CONST float distance, CDiceObj* dice );

	//----------------------------------------------------
	// @name	Down
	// @content	�v���C���[�̗�������	
	// @param	none
	// @return	none
	// @date	2014/1/27
	//----------------------------------------------------
	void	Down		( void );

	//----------------------------------------------------
	// @name	Up
	// @content	�v���C���[�̏㏸����	
	// @param	speed		���x
	// @return	none
	// @date	2014/1/31
	//----------------------------------------------------
	void	Up			( CONST float speed );

	//----------------------------------------------------
	// @name	SetCameraToMtx
	// @content	�J�����̍s����v���C���[�̍s��ɃZ�b�g
	// @param	view		�J�����s��
	// @return	none		
	// @date	2013/12/20
	// @update	2014/1/15	��������ɐݒ肵����
	// @update	2014/1/28	�������Ȃ��ɐݒ�
	//----------------------------------------------------
	void	SetCameraToMtx	( CONST D3DXMATRIX* view );

	//----------------------------------------------------
	// @name	SetPlayerStatus
	// @content	�v���C���[�̃X�e�[�^�X�ύX
	// @param	playerStatus	�ύX�������X�e�[�^�X
	// @return	none	
	// @date	2014/1/31
	//----------------------------------------------------
	void	SetPlayerStatus	( CONST ePlayerStatus playerStatus )
	{
		m_pPlayer->SetPlayerStatus( playerStatus );
	}

	//----------------------------------------------------
	// @name	SetPlayerPos
	// @content	�v���C���[�̈ʒu�ύX
	// @param	xPos		X���W
	// @param	yPos		Y���W
	// @param	zPos		Z���W
	// @return	none
	// @date	2014/1/31
	//----------------------------------------------------
	void	SetPlayerPos	( CONST float xPos, CONST float yPos, CONST float zPos )
	{
		m_pPlayer->SetSpritePos( xPos, yPos, zPos );
	}

	//----------------------------------------------------
	// �v���C���[�̃X�e�[�^�X�擾
	//----------------------------------------------------
	CONST ePlayerStatus GetPlayerStatus( void )
	{
		return m_pPlayer->GetPlayerStatus();
	}

	//----------------------------------------------------
	// �v���C���[�̈ʒu�擾
	//----------------------------------------------------
	CONST D3DXVECTOR3* GetPlayerPos( void )
	{
		return m_pPlayer->GetPos();
	}

	//----------------------------------------------------
	// �v���C���[�̐F�ύX
	//----------------------------------------------------
	void BrightChange( bool isBright )
	{
		if( isBright == false )
		{
			m_pPlayer->SetDiffuse( 50, 50, 50, 255 );
		}
		else
		{
			m_pPlayer->SetDiffuse( 255, 255, 255, 255 );
		}
	}

	//----------------------------------------------------
	// �h�m�e�n�p�}�l�[�W���[�̃Z�b�g
	//----------------------------------------------------
	void SetDiceInfoManager	( CDiceInfoManager* diceInfoManager )
	{
		m_pDiceInfoManager = diceInfoManager;
	}
};


#endif _C_PLAYER_MANAGER_H_