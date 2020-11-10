/*************************************************************
*	@file   	CInputMouse.h
*	@brief  	CInputMouseクラスヘッダー
*	@note		特になし
*	@author		Tatsunori Aoyama
*	@date		2013/07/31
*************************************************************/

#ifndef _Include_CInputMouse_h_	// インクルードガード
#define _Include_CInputMouse_h_

//------------------------------------------------------------
// インクルード
//------------------------------------------------------------
#include<Windows.h>
#include<queue>

//------------------------------------------------------------
// 定数、構造体定義
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
//	@brief  マウス入力管理クラス
//	@note	特になし
//	@author	Tatsunori Aoyama
//	@date	2013/07/31
------------------------------------------------------------*/
class CInputMouse
{
public:

	/// デストラクタ
	~CInputMouse()
	{

	}

	/*!-----------------------------------------------------------
	//	@brief		シングルトンによる呼び出し
	//	@note		特になし
	//	@param[in]	なし
	//	@return		自身の参照
	//	@author		Tatsunori Aoyama
	//	@date		2013/07/31
	------------------------------------------------------------*/
	static	CInputMouse*	GetInstance()
	{
		static	CInputMouse singleton;
		return &singleton;
	}

	/*!-----------------------------------------------------------
	//	@brief		ウィンドウハンドルセット
	//	@note		特になし
	//	@param[in]	なし
	//	@return		なし
	//	@author		Tatsunori Aoyama
	//	@date		2013/07/31
	------------------------------------------------------------*/
	void	SetWindowHandle(HWND hWnd)
	{
		m_hWnd = hWnd;
	}

	/*!-----------------------------------------------------------
	//	@brief		マウスの入力状態更新
	//	@note		特になし
	//	@param[in]	なし
	//	@return		なし
	//	@author		Tatsunori Aoyama
	//	@date		2013/07/31
	------------------------------------------------------------*/
	void	Update()
	{
		HWND hWnd = GetForegroundWindow();
		m_isNowActive = (m_hWnd!=hWnd)? FALSE : TRUE;

		//アクティブでなければreturn
		if( m_isNowActive == FALSE )
			return;
		//過去の入力状態にシフト
		m_inputState = m_inputState<<12;

		//現在の入力状態取得
		m_inputState |= (GetKeyState(VK_LBUTTON)&0x80)>>5;
		m_inputState |= (GetKeyState(VK_MBUTTON)&0x80)>>6;
		m_inputState |= (GetKeyState(VK_RBUTTON)&0x80)>>7;

		//トリガーリリース検出
		m_inputState |= ( (m_inputState<<4)^(m_inputState>>8)&(m_inputState<<4) )&0x70 ;
		m_inputState |= ( ( (m_inputState<<8)^(m_inputState>>4) )&(m_inputState>>4) )&0x700;
	}

	/*!-----------------------------------------------------------
	//	@brief		マウスホイールの更新
	//	@note		プロシージャで更新しないと精度がガタ落ち
	//	@param[in]	zDelta	ホイールの状態
	//	@return		なし
	//	@author		Tatsunori Aoyama
	//	@date		2013/08/01
	------------------------------------------------------------*/
	void	UpdateWheel(SHORT zDelta)
	{
		m_zQueue.push(zDelta/120);
	}

	/*!-----------------------------------------------------------
	//	@brief		マウスのスクリーン相対座標取得
	//	@note		特になし
	//	@param[out]	pPos	出力するマウスの移動相対座標
	//	@return		なし
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
	//	@brief		マウスのスクリーン絶対座標取得
	//	@note		特になし
	//	@param[in]	pPos	出力するマウスのスクリーン絶対座標
	//	@return		なし
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
	//	@brief		マウス座標の更新
	//	@note		特になし
	//	@param[in]	なし
	//	@return		なし
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
	//	@brief		マウスの中央ホイールの回転角度取得
	//	@note		特になし
	//	@param[in]	なし
	//	@return		ホイールの回転角度(-1or1)
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
	//	@brief		マウスの入力状態取得
	//	@note		特になし
	//	@param[in]	なし
	//	@return		入力状態のビット
	//	@author		Tatsunori Aoyama
	//	@date		2013/07/31
	------------------------------------------------------------*/
	BYTE	GetPressButton(SHORT mask)
	{
		return (BYTE)(m_inputState&mask);
	}

	/*!-----------------------------------------------------------
	//	@brief		マウスの入力状態取得
	//	@note		特になし
	//	@param[in]	なし
	//	@return		入力状態のビット
	//	@author		Tatsunori Aoyama
	//	@date		2013/07/31
	------------------------------------------------------------*/
	BYTE	GetTriggerButton(SHORT mask)
	{
		return (BYTE)( (m_inputState&mask)>>4 );
	}

	/*!-----------------------------------------------------------
	//	@brief		マウスの入力状態取得
	//	@note		特になし
	//	@param[in]	なし
	//	@return		入力状態のビット
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
	/// コンストラクタ
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