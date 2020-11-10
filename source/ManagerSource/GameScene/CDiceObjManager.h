//----------------------------------------------------
// CDiceObjManager
//�@�T�C�R���̃I�u�W�F�N�g�̊Ǘ��N���X
//
// @date	2013/11/20
// @authro	T.Kawashita
//----------------------------------------------------
#ifndef _C_DICE_OBJ_MANAGER_H_
#define _C_DICE_OBJ_MANAGER_H_

#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CInputKeyboard.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CJoyStick.hpp"
#include "../../GameMathSource/CDiceRandSystem.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/GameMathHeader/CCollision.h"
#include "../../SceneSource/DebugScene/CDebugMode.h"

#include "../../ObjectSource/GameScene/Particle/CSplitParticle.h"

#include "../../ObjectSource/GameScene/CDiceObj.h"
#include <list>

#include "CStageBlockManager.h"
#include "CChainManager.h"
#include "../../PlayerSource/CPlayerManager.h"
#include "../../ManagerSource/GameScene/CDiceInfoManager.h"

#define MAX_DICE_NUM		( 49 )		// �T�C�R���̍ő吔(�X�e�[�W���ɂ���ĕω�������)
#define DICE_DOWN_SPEED		( 0.005f )	// �T�C�R���̏o���ƍ폜���̃A�j���̑���
#define DICE_UP_SPEED		( 0.012f )	// �T�C�R���o�����x

// �T�C�R���̉�]�����X�e�[�^�X
enum eDiceRollState
{
	DICE_ROLLSTATE_NONE,
	DICE_ROLLSTATE_RIGHT,
	DICE_ROLLSTATE_LEFT,
	DICE_ROLLSTATE_FRONT,
	DICE_ROLLSTATE_BACK,
	DICE_ROLLSTATE_Y
};
	
typedef struct tagTMAINDICE
{
	CDiceObj*		diceObj;	// ���C���̃T�C�R���̃|�C���^�݂̂�ۑ����邽�߂̂���
	eDiceRollState	rollState;	// ��]�X�e�[�^�X
	float			degree;		// ��]�p�x
	D3DXVECTOR3		halfSize;	// �_�C�X�̔����̃T�C�Y�i�ړ��̎��ړ��Ɏg���j
}TMAINDICE;

class CDiceObjManager
{
private:
	TMAINDICE*				m_pMainDice;		// ���C���̃T�C�R��
	CSplitParticle*			m_pSplitParticle;	// �T�C�R�������������̃p�[�e�B�N��

	CDiceObjManager			( void );
	CDiceObjManager			( CONST CDiceObjManager& diceObjManager ){}
	CDiceObjManager	operator= ( CONST CDiceObjManager& diceObjManager ){}

public:
	// �C���X�^���X�擾�ꏊ
	static CDiceObjManager* GetInstance( void )
	{
		static CDiceObjManager	diceObjManager;
		return &diceObjManager;
	}

	//----------------------------------------------------
	// ���C���̃_�C�X���擾
	//----------------------------------------------------
	TMAINDICE*			GetMainDice		( void )
	{
		return m_pMainDice;
	}

	//----------------------------------------------------
	// �_�C�X�̐擪�A�h���X���擾
	//----------------------------------------------------
	CDiceObj*			GetDice			( void )
	{
		return m_pDice;
	}

// �����o
private:
	CDiceObj*				m_pDice;			// �T�C�R��
	LPSTR					m_pResDiceFilePath;	// �T�C�R���̉摜
	int						m_diceNum;			// �_�C�X�̐�
	int						m_appearTime;		// �_�C�X�̏o�����ԊǗ��p

	CDiceInfoManager*		m_pDiceInfoManager;	// �_�C�X�̃C���t�H�}�l�[�W���[

public:
	~CDiceObjManager		( void );			// �f�X�g���N�^

public:
	void		Draw		( CONST D3DXMATRIX* view );		// �`��
	void		Run			( void );						// ����	
	void		Init		( void );						// ������
	void		Uninit		( void );						// �I��
	void		Debug		( void );						// �f�o�b�O�p

// �T�C�R���̃��C������
public:
	//----------------------------------------------------
	// �ړ�����
	//----------------------------------------------------
	void		Move		( void );	// �ړ��̑J��
	void		MoveRight	( void );	// �E�ړ�
	void		MoveLeft	( void );	// ���ړ�
	void		MoveFront	( void );	// �O�ړ�
	void		MoveBack	( void );	// ��ړ�

	//----------------------------------------------------
	// @name	MoveToRoll
	// @content	�T�C�R���̈ړ��{��]	
	// @param	none
	// @return	none
	// @date	2013/11/27
	//----------------------------------------------------
	void		MoveToRoll	( void );

	//----------------------------------------------------
	// @name	Appear
	// @content	�_�C�X�̏o��	
	// @param	none
	// @return	bool		�o���ł������o���Ȃ�������
	// @date	2013/11/27	
	// @update	2013/12/3	�����̒ǉ�
	//----------------------------------------------------
	bool		Appear			( void );

	//----------------------------------------------------
	// @name	AppearManager
	// @content	�o���Ǘ�
	// @param	none	
	// @return	none
	// @date	2014/2/14
	//----------------------------------------------------
	void		AppearManager	( void );

	//----------------------------------------------------
	// @name	Animation
	// @content	�_�C�X�̃A�j���[�V����
	// @param	none
	// @return	none
	// @date	2013/12/4
	//----------------------------------------------------
	void		Animation	( void );

	//----------------------------------------------------
	// @name	SetDiceInfoManager
	// @content	�_�C�X�C���t�H�}�l�[�W���[�̃A�h���X���Z�b�g
	// @param	diceInfoManager	�_�C�X�C���t�H�̃}�l�[�W���[�̃C���X�^���X
	// @return	none
	// @date	2014/2/10
	//----------------------------------------------------
	void		SetDiceInfoManager	( CDiceInfoManager* diceInfoManager )
	{
		m_pDiceInfoManager = diceInfoManager;
	}

};

#endif _C_DICE_OBJ_MANAGER_H_