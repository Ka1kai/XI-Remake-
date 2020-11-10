//----------------------------------------------------
// CFpsControl
//	Fps計算・格納・調整などを行う
// 
// @date	2013/5/8
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_FPSCONTROL_H_
#define _C_FPSCONTROL_H_

#include<Windows.h>

class CFpsControl
{
private:
	DWORD		m_execLastTime;	// 最後にゲーム処理した時間
	DWORD		m_fpsLastTime;	// 最後にFPSを計測した時間
	DWORD		m_currentTime;	// 最新時間
	int			m_countFrame;	// 描画回数(FPS計測用)
	float		m_countFps;		// FPS値表示用

public:
	// コンストラクタ
	CFpsControl	(void)
	{
		m_execLastTime = 0;
		m_fpsLastTime = 0;
		m_currentTime = 0;
		m_countFrame = 0;
		m_countFps = 0;

		// FPS計算に必要な時間を取得
		m_execLastTime = m_fpsLastTime = timeGetTime();
	
	}

	// デストラクタ
	virtual ~CFpsControl	(void){}

public:

	//----------------------------------------------------
	// @name	GetFps
	// @content	Fps値の取得
	// @param	none
	// @return	float	FPS値
	// @date	2013/5/8
	// @update	2013/11/6
	//----------------------------------------------------
	float* GetFPS			( void )
	{	
		return &m_countFps;
	}

	//----------------------------------------------------
	// @name	GetFrameCount
	// @content	フレーム数の取得
	// @param	none
	// @return	int		フレーム数
	// @date	2013/5/8
	// @update	2013/11/6
	//----------------------------------------------------
	int		GetFrameCount	( void )
	{	
		return m_countFrame;
	}

public:
	//----------------------------------------------------
	// @name	TuneFps
	// @content	FPSの調整
	// @param	none
	// @return	bool	16msたったらtrue	
	// @date	2013/5/8
	// @update	2013/11/6
	//----------------------------------------------------
	bool	TuneFps			( void )
	{	
		while( 1 )
		{
			m_currentTime = timeGetTime();
			if( m_currentTime - m_execLastTime >= 1000 / 60 )
				break;
		}
		m_execLastTime = m_currentTime;
		
		return true;
	}

	//----------------------------------------------------
	// @name	CalcFps
	// @content	FPSの計算
	// @param	none
	// @return	bool	60FPSの計算
	// @date	2013/5/8
	// @update	2013/11/6
	//----------------------------------------------------
	bool	CalcFPS			( void )
	{	
		if( m_countFrame >= 60 )
		{
			m_countFps = ( m_countFrame * 1000 )/( (float)m_currentTime - m_fpsLastTime );
			m_fpsLastTime = timeGetTime();
			m_countFrame = 0;
		}

		m_countFrame ++;
		return true;
	}
};

#endif