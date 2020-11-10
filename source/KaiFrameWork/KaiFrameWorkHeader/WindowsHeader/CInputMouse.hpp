/*************************************************************
*	@file   	CInputMouse.h
*	@brief  	CInputMouse�N���X�w�b�_�[
*	@note		���ɂȂ�
*	@author		Tatsunori Aoyama
*	@date		2013/07/31
*************************************************************/

#ifndef _Include_CInputMouse_h_	// �C���N���[�h�K�[�h
#define _Include_CInputMouse_h_

//------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------
#include<Windows.h>
#include<queue>

//------------------------------------------------------------
// �萔�A�\���̒�`
//------------------------------------------------------------
namespace MOUSECODE
{
	namespace PRESS
	{
		enum
		{
			LEFT	= 0x0000004,
			MIDDLE	= 0x0000002,
			RIGHT	= 0x0000001,		
		};
	}

	namespace TRIGGER
	{
		enum
		{
			LEFT	= 0x0000040,
			MIDDLE	= 0x0000020,
			RIGHT	= 0x0000010,		
		};
	}

	namespace RELEASE
	{
		enum
		{
			LEFT	= 0x0000400,
			MIDDLE	= 0x0000200,
			RIGHT	= 0x0000100,
		};
	}
}

/*!-----------------------------------------------------------
//	@class  CInputMouse
//	@brief  �}�E�X���͊Ǘ��N���X
//	@note	���ɂȂ�
//	@author	Tatsunori Aoyama
//	@date	2013/07/31
------------------------------------------------------------*/
class CInputMouse
{
public:

	/// �f�X�g���N�^
	~CInputMouse()
	{

	}

	/*!-----------------------------------------------------------
	//	@brief		�V���O���g���ɂ��Ăяo��
	//	@note		���ɂȂ�
	//	@param[in]	�Ȃ�
	//	@return		���g�̎Q��
	//	@author		Tatsunori Aoyama
	//	@date		2013/07/31
	------------------------------------------------------------*/
	static	CInputMouse*	GetInstance()
	{
		static	CInputMouse singleton;
		return &singleton;
	}

	/*!-----------------------------------------------------------
	//	@brief		�E�B���h�E�n���h���Z�b�g
	//	@note		���ɂȂ�
	//	@param[in]	�Ȃ�
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/07/31
	------------------------------------------------------------*/
	void	SetWindowHandle(HWND hWnd)
	{
		m_hWnd = hWnd;
	}

	/*!-----------------------------------------------------------
	//	@brief		�}�E�X�̓��͏�ԍX�V
	//	@note		���ɂȂ�
	//	@param[in]	�Ȃ�
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/07/31
	------------------------------------------------------------*/
	void	Update()
	{
		HWND hWnd = GetForegroundWindow();
		m_isNowActive = (m_hWnd!=hWnd)? FALSE : TRUE;

		//�A�N�e�B�u�łȂ����return
		if( m_isNowActive == FALSE )
			return;
		//�ߋ��̓��͏�ԂɃV�t�g
		m_inputState = m_inputState<<12;

		//���݂̓��͏�Ԏ擾
		m_inputState |= (GetKeyState(VK_LBUTTON)&0x80)>>5;
		m_inputState |= (GetKeyState(VK_MBUTTON)&0x80)>>6;
		m_inputState |= (GetKeyState(VK_RBUTTON)&0x80)>>7;

		//�g���K�[�����[�X���o
		m_inputState |= ( (m_inputState<<4)^(m_inputState>>8)&(m_inputState<<4) )&0x70 ;
		m_inputState |= ( ( (m_inputState<<8)^(m_inputState>>4) )&(m_inputState>>4) )&0x700;
	}

	/*!-----------------------------------------------------------
	//	@brief		�}�E�X�z�C�[���̍X�V
	//	@note		�v���V�[�W���ōX�V���Ȃ��Ɛ��x���K�^����
	//	@param[in]	zDelta	�z�C�[���̏��
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/08/01
	------------------------------------------------------------*/
	void	UpdateWheel(SHORT zDelta)
	{
		m_zQueue.push(zDelta/120);
	}

	/*!-----------------------------------------------------------
	//	@brief		�}�E�X�̃X�N���[�����΍��W�擾
	//	@note		���ɂȂ�
	//	@param[out]	pPos	�o�͂���}�E�X�̈ړ����΍��W
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/08/05
	------------------------------------------------------------*/
	void	GetRelativeCursorPos(LPPOINT pPos)
	{
		this->UpdateCursorPos();
		pPos->x = m_nowCursorPos.x-m_logCursorPos.x;
		pPos->y = m_nowCursorPos.y-m_logCursorPos.y;
	}

	/*!-----------------------------------------------------------
	//	@brief		�}�E�X�̃X�N���[����΍��W�擾
	//	@note		���ɂȂ�
	//	@param[in]	pPos	�o�͂���}�E�X�̃X�N���[����΍��W
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/08/01
	------------------------------------------------------------*/
	void	GetAbsoluteCursorPos(LPPOINT pPos)
	{
		this->UpdateCursorPos();
		pPos->x = m_nowCursorPos.x;
		pPos->y = m_nowCursorPos.y;
	}

	/*!-----------------------------------------------------------
	//	@brief		�}�E�X���W�̍X�V
	//	@note		���ɂȂ�
	//	@param[in]	�Ȃ�
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/08/05
	------------------------------------------------------------*/
	void	UpdateCursorPos()
	{
		if( m_isNowActive == FALSE)
			return;

		m_logCursorPos.x = m_nowCursorPos.x;
		m_logCursorPos.y = m_nowCursorPos.y;

		::GetCursorPos(&m_nowCursorPos);
		ScreenToClient(m_hWnd,&m_nowCursorPos);
	}

	/*!-----------------------------------------------------------
	//	@brief		�}�E�X�̒����z�C�[���̉�]�p�x�擾
	//	@note		���ɂȂ�
	//	@param[in]	�Ȃ�
	//	@return		�z�C�[���̉�]�p�x(-1or1)
	//	@author		Tatsunori Aoyama
	//	@date		2013/08/01
	------------------------------------------------------------*/
	SHORT	GetWheelRotation()
	{
		if( m_zQueue.empty() )
			return 0;

		SHORT rtn = m_zQueue.back();
		m_zQueue.pop();

		return rtn;
	}

	/*!-----------------------------------------------------------
	//	@brief		�}�E�X�̓��͏�Ԏ擾
	//	@note		���ɂȂ�
	//	@param[in]	�Ȃ�
	//	@return		���͏�Ԃ̃r�b�g
	//	@author		Tatsunori Aoyama
	//	@date		2013/07/31
	------------------------------------------------------------*/
	BYTE	GetPressButton(SHORT mask)
	{
		return (BYTE)(m_inputState&mask);
	}

	/*!-----------------------------------------------------------
	//	@brief		�}�E�X�̓��͏�Ԏ擾
	//	@note		���ɂȂ�
	//	@param[in]	�Ȃ�
	//	@return		���͏�Ԃ̃r�b�g
	//	@author		Tatsunori Aoyama
	//	@date		2013/07/31
	------------------------------------------------------------*/
	BYTE	GetTriggerButton(SHORT mask)
	{
		return (BYTE)( (m_inputState&mask)>>4 );
	}

	/*!-----------------------------------------------------------
	//	@brief		�}�E�X�̓��͏�Ԏ擾
	//	@note		���ɂȂ�
	//	@param[in]	�Ȃ�
	//	@return		���͏�Ԃ̃r�b�g
	//	@author		Tatsunori Aoyama
	//	@date		2013/07/31
	------------------------------------------------------------*/
	BYTE	GetReleaseButton(SHORT mask)
	{
		return (BYTE)( (m_inputState&mask)>>8 );
	}

private:
	HWND	m_hWnd;
	BOOL	m_isNowActive;
	SHORT	m_inputState;
	POINT	m_logCursorPos;
	POINT	m_nowCursorPos;
	std::queue<SHORT>	m_zQueue;

private:
	/// �R���X�g���N�^
	CInputMouse()
	{
		m_hWnd = NULL;
		m_isNowActive = TRUE;
		m_nowCursorPos.x = 0;
		m_nowCursorPos.y = 0;
		m_logCursorPos.x = 0;
		m_logCursorPos.y = 0;
		m_inputState	= 0;
	}
};


inline	CInputMouse*	sInputMouseMgr()
{
	return CInputMouse::GetInstance();
}

#endif // _Include_CInputMouse_h_