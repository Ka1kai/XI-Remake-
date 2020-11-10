//----------------------------------------------------
// CTimeManager Header 
//　タイムの管理クラス
//
// @author T.Kawashita
//----------------------------------------------------
#ifndef _C_TIME_MANAGER_H_
#define _C_TIME_MANAGER_H_ 

#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/2D/C2DSpriteRHW.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"

class CTimeManager
{
private:
	LPSTR			m_pResTimeFilePath;
	C2DSpriteRHW	*m_pTime;

	LPSTR			m_pResTimeDigitFilePath;
	C2DSpriteRHW	*m_pTimeDigit;

private:
	int				m_time;			

public:
	// 時間のアドレス取得
	int*	GetTime	( void )
	{
		return &m_time;
	}

public:
	CTimeManager	( void );
	~CTimeManager	( void );


public:
	void		Draw	( void );
	void		Init	( CONST UINT time );
	void		Run		( void );
	bool		TimeUP	( void );

public:
	void		BrightChange	( bool isBright )
	{
		if( isBright == true )
		{
			m_pTime->SetDiffuse( 255, 255, 255, 255 );
			for( int i = 0; i < 5; ++ i ){
				m_pTimeDigit[i].SetDiffuse( 255, 255, 255, 255 );
			}
		}
		else
		{
			m_pTime->SetDiffuse( 100, 100, 100, 255 );
			for( int i = 0; i < 5; ++ i ){
				m_pTimeDigit[i].SetDiffuse( 100, 100, 100, 255 );
			}

		}
	}
};

#endif _C_TIME_MANAGER_H_