/*************************************************************
*	@file   	CInputKeyboard.h
*	@brief  	CInputKeyboard�N���X�w�b�_�[
*	@note		���ɂȂ�
*	@author		Tatsunori Aoyama
*	@date		2013/07/23
*************************************************************/

#ifndef _Include_CInputKeyboard_h_	// �C���N���[�h�K�[�h
#define _Include_CInputKeyboard_h_

//------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------
#include<Windows.h>

//------------------------------------------------------------
// �萔�A�\���̒�`
//------------------------------------------------------------
enum
{
	VK_A = 'A',
	VK_B,
	VK_C,
	VK_D,
	VK_E,
	VK_F,
	VK_G,
	VK_H,
	VK_I,
	VK_J,
	VK_K,
	VK_L,
	VK_M,
	VK_N,
	VK_O,
	VK_P,
	VK_Q,
	VK_R,
	VK_S,
	VK_T,
	VK_U,
	VK_V,
	VK_W,
	VK_X,
	VK_Y,
	VK_Z,
};


/*!-----------------------------------------------------------
//	@struct	TKeyboardState
//	@brief	�L�[�{�[�h�i�[���\����
//	@note	���ɂȂ�
//	@author	Tatsunori Aoyama
//	@date	2013/07/23
------------------------------------------------------------*/
typedef struct tagTInputKeyboard
{
	BYTE	m_pressState[256];
	BYTE	m_triggerState[256];
	BYTE	m_releaseState[256];
}TInputKeyboard;

/*!-----------------------------------------------------------
//	@class  CInputKeyboard
//	@brief  �L�[�{�[�h���͊Ǘ��N���X
//	@note	���ɂȂ�
//	@author	Tatsunori Aoyama
//	@date	2013/07/23
------------------------------------------------------------*/
class CInputKeyboard
{
public:
	/// �R���X�g���N�^
	CInputKeyboard()
	{
		ZeroMemory(&m_keyboardData,sizeof(TInputKeyboard) );
	};

	/// �f�X�g���N�^
	~CInputKeyboard(){};

	/*!-----------------------------------------------------------
	//	@brief		�V���O���g���ɂ����̌Ăяo��
	//	@note		���ɂȂ�
	//	@param[in]	�Ȃ�
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/07/23
	------------------------------------------------------------*/
	static	CInputKeyboard*	GetInstance()
	{
		static	CInputKeyboard	singleton;
		return &singleton;
	}

	/*!-----------------------------------------------------------
	//	@brief		�L�[�{�[�h�̏�ԍX�V���\�b�h
	//	@note		���ɂȂ�
	//	@param[in]	�Ȃ�
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/07/23
	------------------------------------------------------------*/
	void	Update()
	{
		BYTE	keyLogState[MAX_KEY_CODE];

		//�ߋ��̃L�[�����o�[�X�g�R�s�[
		memcpy(keyLogState,m_keyboardData.m_pressState,sizeof(BYTE)*MAX_KEY_CODE);
		ZeroMemory(m_keyboardData.m_pressState,sizeof(BYTE)*MAX_KEY_CODE);
		//�L�[�{�[�h�̓��͏�Ԃ��擾
		GetKeyboardState(m_keyboardData.m_pressState);

		//�S�L�[���`�F�b�N
		for(int	i=0;i<MAX_KEY_CODE;i++)
		{
			//�g���K�[�A�����[�X�̔���
			m_keyboardData.m_pressState[i] = m_keyboardData.m_pressState[i]&0x80;
			m_keyboardData.m_triggerState[i] = (m_keyboardData.m_pressState[i] ^ keyLogState[i]) & m_keyboardData.m_pressState[i];
			m_keyboardData.m_releaseState[i] = (m_keyboardData.m_pressState[i] ^ keyLogState[i]) & keyLogState[i];
		}
	}

	/*!-----------------------------------------------------------
	//	@brief		�v���X�L�[�擾
	//	@note		���ɂȂ�
	//	@param[in]	keyCode	�L�[�R�[�h
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/07/23
	------------------------------------------------------------*/
	BYTE	GetPressKeyState(BYTE keyCode)
	{
		return m_keyboardData.m_pressState[keyCode];
	}

	/*!-----------------------------------------------------------
	//	@brief		�g���K�[�L�[�擾
	//	@note		���ɂȂ�
	//	@param[in]	keyCode	�L�[�R�[�h
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/07/23
	------------------------------------------------------------*/
	BYTE	GetTriggerKeyState(BYTE keyCode)
	{
		return m_keyboardData.m_triggerState[keyCode];
	}

	/*!-----------------------------------------------------------
	//	@brief		�����[�X�L�[�擾
	//	@note		���ɂȂ�
	//	@param[in]	keyCode	�L�[�R�[�h
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/07/23
	------------------------------------------------------------*/
	BYTE	GetReleaseKeyState(BYTE keyCode)
	{
		return m_keyboardData.m_releaseState[keyCode];
	}

private:	/// ��`
	static	const int	MAX_KEY_CODE = 256;

private:	/// �L�[�{�[�h�i�[���
	TInputKeyboard		m_keyboardData;
};


//�V���O���g����`
inline CInputKeyboard* sInputKeyManager()
{
	return CInputKeyboard::GetInstance();
}

#endif // _Include_CInputKeyboard_h_