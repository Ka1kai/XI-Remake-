/*************************************************************
*	@file   	CInputKeyboard.h
*	@brief  	CInputKeyboardクラスヘッダー
*	@note		特になし
*	@author		Tatsunori Aoyama
*	@date		2013/07/23
*************************************************************/

#ifndef _Include_CInputKeyboard_h_	// インクルードガード
#define _Include_CInputKeyboard_h_

//------------------------------------------------------------
// インクルード
//------------------------------------------------------------
#include<Windows.h>

//------------------------------------------------------------
// 定数、構造体定義
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
//	@brief	キーボード格納情報構造体
//	@note	特になし
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
//	@brief  キーボード入力管理クラス
//	@note	特になし
//	@author	Tatsunori Aoyama
//	@date	2013/07/23
------------------------------------------------------------*/
class CInputKeyboard
{
public:
	/// コンストラクタ
	CInputKeyboard()
	{
		ZeroMemory(&m_keyboardData,sizeof(TInputKeyboard) );
	};

	/// デストラクタ
	~CInputKeyboard(){};

	/*!-----------------------------------------------------------
	//	@brief		シングルトンによる実体呼び出し
	//	@note		特になし
	//	@param[in]	なし
	//	@return		なし
	//	@author		Tatsunori Aoyama
	//	@date		2013/07/23
	------------------------------------------------------------*/
	static	CInputKeyboard*	GetInstance()
	{
		static	CInputKeyboard	singleton;
		return &singleton;
	}

	/*!-----------------------------------------------------------
	//	@brief		キーボードの状態更新メソッド
	//	@note		特になし
	//	@param[in]	なし
	//	@return		なし
	//	@author		Tatsunori Aoyama
	//	@date		2013/07/23
	------------------------------------------------------------*/
	void	Update()
	{
		BYTE	keyLogState[MAX_KEY_CODE];

		//過去のキー情報をバーストコピー
		memcpy(keyLogState,m_keyboardData.m_pressState,sizeof(BYTE)*MAX_KEY_CODE);
		ZeroMemory(m_keyboardData.m_pressState,sizeof(BYTE)*MAX_KEY_CODE);
		//キーボードの入力状態を取得
		GetKeyboardState(m_keyboardData.m_pressState);

		//全キー情報チェック
		for(int	i=0;i<MAX_KEY_CODE;i++)
		{
			//トリガー、リリースの判定
			m_keyboardData.m_pressState[i] = m_keyboardData.m_pressState[i]&0x80;
			m_keyboardData.m_triggerState[i] = (m_keyboardData.m_pressState[i] ^ keyLogState[i]) & m_keyboardData.m_pressState[i];
			m_keyboardData.m_releaseState[i] = (m_keyboardData.m_pressState[i] ^ keyLogState[i]) & keyLogState[i];
		}
	}

	/*!-----------------------------------------------------------
	//	@brief		プレスキー取得
	//	@note		特になし
	//	@param[in]	keyCode	キーコード
	//	@return		なし
	//	@author		Tatsunori Aoyama
	//	@date		2013/07/23
	------------------------------------------------------------*/
	BYTE	GetPressKeyState(BYTE keyCode)
	{
		return m_keyboardData.m_pressState[keyCode];
	}

	/*!-----------------------------------------------------------
	//	@brief		トリガーキー取得
	//	@note		特になし
	//	@param[in]	keyCode	キーコード
	//	@return		なし
	//	@author		Tatsunori Aoyama
	//	@date		2013/07/23
	------------------------------------------------------------*/
	BYTE	GetTriggerKeyState(BYTE keyCode)
	{
		return m_keyboardData.m_triggerState[keyCode];
	}

	/*!-----------------------------------------------------------
	//	@brief		リリースキー取得
	//	@note		特になし
	//	@param[in]	keyCode	キーコード
	//	@return		なし
	//	@author		Tatsunori Aoyama
	//	@date		2013/07/23
	------------------------------------------------------------*/
	BYTE	GetReleaseKeyState(BYTE keyCode)
	{
		return m_keyboardData.m_releaseState[keyCode];
	}

private:	/// 定義
	static	const int	MAX_KEY_CODE = 256;

private:	/// キーボード格納情報
	TInputKeyboard		m_keyboardData;
};


//シングルトン定義
inline CInputKeyboard* sInputKeyManager()
{
	return CInputKeyboard::GetInstance();
}

#endif // _Include_CInputKeyboard_h_