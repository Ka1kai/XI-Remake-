//----------------------------------------------------
// CModeSelectBackManager 
//	���[�h�Z���N�g��ʂ̔w�i�}�l�[�W���[
//
// @date	2014/2/4
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_MODESELECT_BACK_MANAGER_
#define _C_MODESELECT_BACK_MANAGER_

#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourcePath.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/UtilityHeader/Macro.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CInputKeyboard.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CJoyStick.hpp"

#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/CObjectBase.hpp"
#include "../../ObjectSource/ModeSelect/CMessageBar.h"

typedef enum 
{
	eMessageBarNone,
	eMessageBarAnimation,
	eMessageBarNormal
}eMessageBarStatus;

class CModeSelectBackManager
{
private:
	CObjectBase*			m_pModeSelectStage;
	LPSTR					m_pResModeSelectStageFilePath;

	// ���u�����h�p
	C2DSpriteAlphaBlend*	m_pAlphaBlend;

	// ���j���[�̕���
	C2DSpriteAlphaBlend*	m_pMenuValue;
	LPSTR					m_pResMenuValueFilePath;

	// ���[�h�Z���N�g��ʂ̃��b�Z�[�W�o�[
	CMessageBar*			m_pMessageBar;
	LPSTR					m_pResMessageBar[6];
	int						m_resIndexNo;
	eMessageBarStatus		m_eMessageBarStatus;

	bool					m_isBarAnimation;
	bool					m_isAlphaBlend;

public:
	CModeSelectBackManager	( void );	// �R���X�g���N�^
	~CModeSelectBackManager	( void );	// �f�X�g���N�^

public:
	// ���b�Z�[�W�o�[�̃X�e�[�^�X�擾
	eMessageBarStatus		GetMessageBarStatus	( void )
	{
		return m_eMessageBarStatus;
	}

	// ���b�Z�[�W�o�[�̃X�e�[�^�X�Z�b�g
	void	SetMessageBarStatus	( CONST eMessageBarStatus messageBarStatus )
	{
		m_eMessageBarStatus = messageBarStatus;
	}

public:
	bool	Init			( void );	// ������
	void	Run				( void );	// ����
	void	Draw			( void );	// �`��
	void	DrawAlpha		( void );	// ���u�����h�p�摜�̕`��
	bool	Uninit			( void );	// �I��

public:
	void	RunKey				( CONST UINT index );	// �L�[����
	void	RunKeyEnter			( void );				// �G���^�[�L�[�����ꂽ��ĂԊ֐�

	bool	MessageBarAnimation	( void );				// ���b�Z�[�W�o�[�̃A�j���[�V����
	bool	Fade				( void );				// �t�F�[�h�A�E�g
};

#endif _C_MODESELECT_BACK_MANAGER_