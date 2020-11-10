//----------------------------------------------------
// CJoystick
//	JoyStick����
//
// @date	2013/12/8
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_JOYSTICK_H_
#define _C_JOYSTICK_H_

#include <Windows.h>
#include <XInput.h>
#pragma comment(lib,"xinput.lib")
#pragma comment(lib,"Xinput9_1_0.lib")

#define INPUT_DEADZONE  ( 0.24f * FLOAT(0x7FFF) )
#define MAX_JOYSTICK	( 4 )

/*
#define XINPUT_GAMEPAD_DPAD_UP          0x0001		// �\���L�[��
#define XINPUT_GAMEPAD_DPAD_DOWN        0x0002		// �\���L�[��
#define XINPUT_GAMEPAD_DPAD_LEFT        0x0004		// �\���L�[��
#define XINPUT_GAMEPAD_DPAD_RIGHT       0x0008		// �\���L�[�E
#define XINPUT_GAMEPAD_START            0x0010		// �X�^�[�g�{�^��
#define XINPUT_GAMEPAD_BACK             0x0020		// �߂�{�^��
#define XINPUT_GAMEPAD_LEFT_THUMB       0x0040		// L3�{�^���i���X�e�B�b�N�������݁j
#define XINPUT_GAMEPAD_RIGHT_THUMB      0x0080		// R3�{�^���i�E�X�e�B�b�N�������݁j
#define XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100		// L1�{�^��
#define XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200		// R1�{�^��
#define XINPUT_GAMEPAD_A                0x1000		// A�{�^��
#define XINPUT_GAMEPAD_B                0x2000		// B�{�^��
#define XINPUT_GAMEPAD_X                0x4000		// X�{�^��
#define XINPUT_GAMEPAD_Y                0x8000		// Y�{�^��
*/

typedef struct tagTXINPUTJOYSTICK
{
	UINT				id;				// �W���C�X�e�B�b�N�̔ԍ�
    XINPUT_STATE		inputState;		// ���͏��
	XINPUT_VIBRATION	vibration;		// �U�����
	WORD				triggerState;	// �g���K�[���
	WORD				releaseState;	// �����[�X���

}TXINPUTJOYSTICK;

class CJoyStick
{
private:
	CJoyStick	( void )
	{
		::ZeroMemory( &m_joyStick,sizeof( m_joyStick ) );
	}
	CJoyStick	( CONST CJoyStick& joyStick ){}
	CJoyStick&	operator= ( CONST CJoyStick& joyStick ){}

private:
	TXINPUTJOYSTICK	m_joyStick[ MAX_JOYSTICK ];

public:
	// �C���X�^���X�擾�ꏊ
	static CJoyStick*	GetInstance()
	{
		static CJoyStick	joyStick;
		return &joyStick;
	}

	//----------------------------------------------------
	// @name	Update
	// @content	�W���C�X�e�B�b�N�̍X�V
	// @param	none
	// @return	none
	// @date	2013/12/8
	//----------------------------------------------------
	void	Update		( void )
	{
		DWORD dwResult;
		for( DWORD i = 0; i < MAX_JOYSTICK; ++ i )
		{
			// �o�C�u���[�V����������
			this->UpdateVibration( i );

			// �L�[��񏉊���
			WORD logInputState		= m_joyStick[i].inputState.Gamepad.wButtons;
	//		WORD logAxisState		= m_joyStick[i].m_pressAxis;
	//		BYTE logTriggerState	= m_joyStick[i].m_triggerPress;

			::ZeroMemory( &m_joyStick[i].inputState, sizeof(XINPUT_STATE) );	

			// Simply get the state of the controller from XInput.
			dwResult = XInputGetState( i, &m_joyStick[i].inputState );
			if( dwResult == ERROR_SUCCESS )
			{
				// Controller is connected
				if( -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < m_joyStick[i].inputState.Gamepad.sThumbLX &&
					-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < m_joyStick[i].inputState.Gamepad.sThumbLY &&
					m_joyStick[i].inputState.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE  &&
					m_joyStick[i].inputState.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE )
				{
					m_joyStick[i].inputState.Gamepad.sThumbLX = 0;
					m_joyStick[i].inputState.Gamepad.sThumbLY = 0;
				}

				if( -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE < m_joyStick[i].inputState.Gamepad.sThumbRX &&
					-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE < m_joyStick[i].inputState.Gamepad.sThumbRY &&
					m_joyStick[i].inputState.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
					m_joyStick[i].inputState.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE )
				{
					m_joyStick[i].inputState.Gamepad.sThumbRX = 0;
					m_joyStick[i].inputState.Gamepad.sThumbRY = 0;
				}

				// �{�^���̃g���K�[���o
				m_joyStick[i].triggerState = (m_joyStick[i].inputState.Gamepad.wButtons ^ logInputState) & m_joyStick[i].inputState.Gamepad.wButtons;
				
				// �{�^���̃����[�X���o
				m_joyStick[i].releaseState = (m_joyStick[i].inputState.Gamepad.wButtons ^ logInputState) & logInputState;

			}
		}
	}

	//----------------------------------------------------
	// @name	UpdateVibration
	// @content	�o�C�u���[�V�����̍X�V
	// @param	joyStickID		�W���C�X�e�B�b�NID
	// @return	none
	// @date	2013/12/8
	//----------------------------------------------------
	void	UpdateVibration		( CONST UINT joyStickID )
	{
		XInputSetState( joyStickID, &m_joyStick[ joyStickID ].vibration );
		m_joyStick[ joyStickID ].vibration.wLeftMotorSpeed = 0;
		m_joyStick[ joyStickID ].vibration.wRightMotorSpeed = 0;
	}

	//----------------------------------------------------
	// @name	GetPressButton
	// @content	�w�肵���{�^���̃v���X�L�[��Ԏ擾
	// @param	joyStickID		�W���C�X�e�B�b�NID
	// @param	buttonID		�{�^��ID
	// @return	DWORD			�������{�^���ԍ��̃v���X���
	// @date	2013/12/8
	//----------------------------------------------------
	DWORD	GetPressButton		( CONST UINT joyStickID, DWORD buttonID )
	{
		return ( m_joyStick[ joyStickID ].inputState.Gamepad.wButtons ) &buttonID;
	}

	//----------------------------------------------------
	// @name	GetTriggerButton
	// @content	�w�肵���{�^���̃g���K�[�L�[��Ԏ擾
	// @param	joyStickID		�W���C�X�e�B�b�NID
	// @param	buttonID		�{�^��ID
	// @return	DWORD			�������{�^���ԍ��̃g���K�[���
	// @date	2013/12/8
	//----------------------------------------------------
	DWORD	GetTriggerButton	( CONST UINT joyStickID, DWORD buttonID )
	{
		return ( m_joyStick[ joyStickID ].triggerState ) &buttonID;
	}

	//----------------------------------------------------
	// @name	GetReleaseButton
	// @content	�w�肵���{�^���̃����[�X�L�[��Ԏ擾
	// @param	joyStickID		�W���C�X�e�B�b�NID
	// @param	buttonID		�{�^��ID
	// @return	DWORD			�������{�^���ԍ��̃����[�X���
	// @date	2013/12/8
	//----------------------------------------------------
	DWORD	GetReleaseButton	( CONST UINT joyStickID, DWORD buttonID )
	{
		return ( m_joyStick[ joyStickID ].releaseState ) & buttonID;
	}

	//----------------------------------------------------
	// @name	Vibration
	// @content	�o�C�u���[�V����
	// @param	joyStickID		�W���C�X�e�B�b�NID
	// @param	leftVibRate		���U���̒l(0�`65535)
	// @param	rigthVibRate	�E�U���̒l(0�`65535)
	// @none	
	// @date	2013/12/8
	//----------------------------------------------------
	void	Vibration			( CONST UINT joyStickID, USHORT leftVibRate, USHORT rightVibRate )
	{
		// �I�[�o�[�t���[�̋֎~
		leftVibRate &= 0xFFFF;
		rightVibRate &= 0xFFFF;

		m_joyStick[ joyStickID ].vibration.wLeftMotorSpeed = min( 65535, leftVibRate + m_joyStick[ joyStickID ].vibration.wLeftMotorSpeed );
		m_joyStick[ joyStickID ].vibration.wRightMotorSpeed = min( 65535, rightVibRate + m_joyStick[ joyStickID ].vibration.wRightMotorSpeed );
	}

};




#endif _C_JOYSTICK_H_
