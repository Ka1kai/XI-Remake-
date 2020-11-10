//----------------------------------------------------
// CJoystick
//	JoyStick実装
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
#define XINPUT_GAMEPAD_DPAD_UP          0x0001		// 十字キー上
#define XINPUT_GAMEPAD_DPAD_DOWN        0x0002		// 十字キー下
#define XINPUT_GAMEPAD_DPAD_LEFT        0x0004		// 十字キー左
#define XINPUT_GAMEPAD_DPAD_RIGHT       0x0008		// 十字キー右
#define XINPUT_GAMEPAD_START            0x0010		// スタートボタン
#define XINPUT_GAMEPAD_BACK             0x0020		// 戻るボタン
#define XINPUT_GAMEPAD_LEFT_THUMB       0x0040		// L3ボタン（左スティック押し込み）
#define XINPUT_GAMEPAD_RIGHT_THUMB      0x0080		// R3ボタン（右スティック押し込み）
#define XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100		// L1ボタン
#define XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200		// R1ボタン
#define XINPUT_GAMEPAD_A                0x1000		// Aボタン
#define XINPUT_GAMEPAD_B                0x2000		// Bボタン
#define XINPUT_GAMEPAD_X                0x4000		// Xボタン
#define XINPUT_GAMEPAD_Y                0x8000		// Yボタン
*/

typedef struct tagTXINPUTJOYSTICK
{
	UINT				id;				// ジョイスティックの番号
    XINPUT_STATE		inputState;		// 入力状態
	XINPUT_VIBRATION	vibration;		// 振動状態
	WORD				triggerState;	// トリガー状態
	WORD				releaseState;	// リリース状態

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
	// インスタンス取得場所
	static CJoyStick*	GetInstance()
	{
		static CJoyStick	joyStick;
		return &joyStick;
	}

	//----------------------------------------------------
	// @name	Update
	// @content	ジョイスティックの更新
	// @param	none
	// @return	none
	// @date	2013/12/8
	//----------------------------------------------------
	void	Update		( void )
	{
		DWORD dwResult;
		for( DWORD i = 0; i < MAX_JOYSTICK; ++ i )
		{
			// バイブレーション初期化
			this->UpdateVibration( i );

			// キー情報初期化
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

				// ボタンのトリガー検出
				m_joyStick[i].triggerState = (m_joyStick[i].inputState.Gamepad.wButtons ^ logInputState) & m_joyStick[i].inputState.Gamepad.wButtons;
				
				// ボタンのリリース検出
				m_joyStick[i].releaseState = (m_joyStick[i].inputState.Gamepad.wButtons ^ logInputState) & logInputState;

			}
		}
	}

	//----------------------------------------------------
	// @name	UpdateVibration
	// @content	バイブレーションの更新
	// @param	joyStickID		ジョイスティックID
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
	// @content	指定したボタンのプレスキー状態取得
	// @param	joyStickID		ジョイスティックID
	// @param	buttonID		ボタンID
	// @return	DWORD			押したボタン番号のプレス状態
	// @date	2013/12/8
	//----------------------------------------------------
	DWORD	GetPressButton		( CONST UINT joyStickID, DWORD buttonID )
	{
		return ( m_joyStick[ joyStickID ].inputState.Gamepad.wButtons ) &buttonID;
	}

	//----------------------------------------------------
	// @name	GetTriggerButton
	// @content	指定したボタンのトリガーキー状態取得
	// @param	joyStickID		ジョイスティックID
	// @param	buttonID		ボタンID
	// @return	DWORD			押したボタン番号のトリガー状態
	// @date	2013/12/8
	//----------------------------------------------------
	DWORD	GetTriggerButton	( CONST UINT joyStickID, DWORD buttonID )
	{
		return ( m_joyStick[ joyStickID ].triggerState ) &buttonID;
	}

	//----------------------------------------------------
	// @name	GetReleaseButton
	// @content	指定したボタンのリリースキー状態取得
	// @param	joyStickID		ジョイスティックID
	// @param	buttonID		ボタンID
	// @return	DWORD			押したボタン番号のリリース状態
	// @date	2013/12/8
	//----------------------------------------------------
	DWORD	GetReleaseButton	( CONST UINT joyStickID, DWORD buttonID )
	{
		return ( m_joyStick[ joyStickID ].releaseState ) & buttonID;
	}

	//----------------------------------------------------
	// @name	Vibration
	// @content	バイブレーション
	// @param	joyStickID		ジョイスティックID
	// @param	leftVibRate		左振動の値(0～65535)
	// @param	rigthVibRate	右振動の値(0～65535)
	// @none	
	// @date	2013/12/8
	//----------------------------------------------------
	void	Vibration			( CONST UINT joyStickID, USHORT leftVibRate, USHORT rightVibRate )
	{
		// オーバーフローの禁止
		leftVibRate &= 0xFFFF;
		rightVibRate &= 0xFFFF;

		m_joyStick[ joyStickID ].vibration.wLeftMotorSpeed = min( 65535, leftVibRate + m_joyStick[ joyStickID ].vibration.wLeftMotorSpeed );
		m_joyStick[ joyStickID ].vibration.wRightMotorSpeed = min( 65535, rightVibRate + m_joyStick[ joyStickID ].vibration.wRightMotorSpeed );
	}

};




#endif _C_JOYSTICK_H_
