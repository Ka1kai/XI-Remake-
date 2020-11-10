
#include "CTitleSoundManager.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CTitleSoundManager::CTitleSoundManager( void )
{
	m_pSound = new CXAudio2();
}

//----------------------------------------------------
// �f�X�g���N�^
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
// ������
//----------------------------------------------------
void CTitleSoundManager::Init( void )
{
	m_pSound->Init();

	m_pSound->LoadWav( TITLE_BGM,"resource/sound/title.wav");
	m_pSound->LoadWav( TITLE_BUTTON,"resource/sound/titleButton.wav");
}

//----------------------------------------------------
// ���Đ�
//----------------------------------------------------
void CTitleSoundManager::Play( const int soundNo,bool isLoop )
{
	m_pSound->Run( soundNo,1.0f,isLoop );
}

//----------------------------------------------------
// ����~
//----------------------------------------------------
void CTitleSoundManager::Stop( const int soundNo )
{
	m_pSound->Stop( soundNo );
}






