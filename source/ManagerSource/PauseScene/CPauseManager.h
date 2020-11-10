//----------------------------------------------------
// CPauseManager Header 
//�@�|�[�Y�̊Ǘ��N���X
//
// @author T.Kawashita
//----------------------------------------------------
#ifndef _C_PAUSE_MANAGER_H_
#define _C_PAUSE_MANAGER_H_

#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CInputKeyboard.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CJoyStick.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"

#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/2D/C2DSpriteAlphaBlend.h"

typedef enum PAUSE_STATUS
{
	RESUME,
	RETRY,
	TITLE,
	GAMEOVER
}ePauseStatus;

class CPauseManager
{
private:
	C2DSpriteAlphaBlend		*m_pPauseBack;
	LPSTR					m_pResPauseBackFilePath;
	C2DSpriteAlphaBlend		*m_pPause;
	LPSTR					m_pResPauseFilePath;
	C2DSpriteAlphaBlend		*m_pRetry;
	LPSTR					m_pResRetryFilePath;
	C2DSpriteAlphaBlend		*m_pResume;
	LPSTR					m_pResResumeFilePath;
	C2DSpriteAlphaBlend		*m_pTitle;
	LPSTR					m_pResTitleFilePath;
	

	C2DSpriteRHW			*m_pCursol;
	LPSTR					m_pResCursolFilePath;
	C2DSpriteAlphaBlend		*m_pPauseEffect;
	LPSTR					m_pResPauseEffectFilePath;

private:
	bool					m_isPause;			// �|�[�Y�̃t���O
	ePauseStatus			m_ePauseState;		// �|�[�Y�̃X�e�[�^�X

public:	
	CPauseManager			( void );	// �R���X�g���N�^
	~CPauseManager			( void );	// �f�X�g���N�^

public:
	void	Draw			( void );
	void	Run				( void );
	void	Init			( void );
	void	InitPause		( void );
	void	Uninit			( void );

public:
	//----------------------------------------------------
	// @name	GetIsPause
	// @content	�|�[�Y�̃t���O
	// @param	none
	// @return	bool		�|�[�Y�����ǂ���
	// @date	2014/2/12
	//----------------------------------------------------
	bool		GetIsPause		( void )
	{
		return m_isPause;
	}

	//----------------------------------------------------
	// @name	SetisPause
	// @content	�|�[�Y�����ǂ����̃Z�b�g
	// @param	bool	�|�[�Y�����ǂ���
	// @return	none
	// @date	2014/2/12
	//----------------------------------------------------
	void		SetIsPause		( bool isPause )
	{
		m_isPause = isPause;
	}

	//----------------------------------------------------
	// @name	SetIsPause
	// @content	�|�[�Y�����ǂ����̃Z�b�g�i����ւ��j
	// @param	none
	// @return	none
	// @date	2014/2/12
	//----------------------------------------------------
	void		SetIsPause		( void )
	{
		m_isPause ^= true;
	}

	//----------------------------------------------------
	// @name	GetPauseState
	// @content	�|�[�Y�̃X�e�[�^�X���Z�b�g
	// @param	none	
	// @return	ePauseState		�|�[�Y�̃X�e�[�^�X
	// @date	2014/2/12
	//----------------------------------------------------
	ePauseStatus	GetPauseState	( void )
	{
		return m_ePauseState;
	}

};

#endif _C_PAUSE_MANAGER_H_