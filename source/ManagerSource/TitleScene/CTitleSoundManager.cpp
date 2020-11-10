
#include "CTitleSoundManager.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CTitleSoundManager::CTitleSoundManager( void )
{
	m_pSound = new CXAudio2();
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CTitleSoundManager::~CTitleSoundManager( void )
{
	if( m_pSound != NULL )
	{
		delete m_pSound;
		m_pSound = NULL;
	}
}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
void CTitleSoundManager::Init( void )
{
	m_pSound->Init();

	m_pSound->LoadWav( TITLE_BGM,"resource/sound/title.wav");
	m_pSound->LoadWav( TITLE_BUTTON,"resource/sound/titleButton.wav");
}

//----------------------------------------------------
// 音再生
//----------------------------------------------------
void CTitleSoundManager::Play( const int soundNo,bool isLoop )
{
	m_pSound->Run( soundNo,1.0f,isLoop );
}

//----------------------------------------------------
// 音停止
//----------------------------------------------------
void CTitleSoundManager::Stop( const int soundNo )
{
	m_pSound->Stop( soundNo );
}






