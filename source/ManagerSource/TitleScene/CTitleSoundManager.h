//----------------------------------------------------
// CTitleSoundManager Header 
//　タイトルのサウンド管理クラス
//
// @author T.Kawashita
//----------------------------------------------------
#ifndef _C_TITLE_SOUND_MANAGER_H_
#define _C_TITLE_SOUND_MANAGER_H_

#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CXAudio2.h"

#define TITLE_BGM ( 0 )
#define TITLE_BUTTON ( 1 )

class CTitleSoundManager
{
private:
	CXAudio2		*m_pSound;

public:
	CTitleSoundManager	( void );
	~CTitleSoundManager ( void );

public:
	void		Init	( void );
	void		Play	( const int soundNo,bool isLoop );
	void		Stop	( const int soundNo );
	void		FadeOut ( void );

};

#endif _C_TITLE_SOUND_MANAGER_H_