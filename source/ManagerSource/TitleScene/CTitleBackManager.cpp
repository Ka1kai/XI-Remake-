
#include "CTitleBackManager.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CTitleBackManager::CTitleBackManager( void )
{	
	// ���u�����h
	m_pAlphaBlend = new C2DSpriteAlphaBlend;

	// �^�C�g���w�i
	m_pTitleBack = new C2DSpriteAlphaBlend;
	m_pResTitleBackFilePath = TITLE_BACK_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResTitleBackFilePath );

	// �^�C�g�����S
	m_pTitleLogo = new C2DSpriteAlphaBlend;
	m_pResTitleLogoFilePath = TITLELOG_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResTitleLogoFilePath );

	// Re:make
	m_pTitleRemake = new C2DSpriteAlphaBlend;
	m_pResTitleRemakeFilePath = TITLE_REMAKE_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResTitleRemakeFilePath );

	// PUSH START PLAY
	m_pPushStartPlay = new C2DSpriteAlphaBlend( eFadeState::FADE_OUT );
	m_pResPushStartPlayFilePath = PUSHSTART_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResPushStartPlayFilePath );
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
CTitleBackManager::~CTitleBackManager( void )
{
	SAFE_DELETE( m_pAlphaBlend );			// ���u�����h
	SAFE_DELETE( m_pTitleBack );			// �^�C�g���w�i
	SAFE_DELETE( m_pPushStartPlay );		// PUSH START PLAY
	SAFE_DELETE( m_pTitleLogo );			// �^�C�g�����S
	SAFE_DELETE( m_pTitleRemake );			// Remake
}

//----------------------------------------------------
// ������
//----------------------------------------------------
void CTitleBackManager::Init( void )
{
	m_isFade = false;

	m_pTitleBack->SetVertexPos( 400.0f, 320.0f, 800.0f, 640.0f );

	m_pAlphaBlend->SetVertexPos( 400.0f,320.0f,800.0f,640.0f );
	m_pAlphaBlend->SetDiffuse( 255,255,255,0 );

	m_pPushStartPlay->SetVertexPos( 400.0f, 480.0f, 320.0f, 50.0f );
	m_pPushStartPlay->SetDiffuse( 255,255,255,255 );

	m_pTitleLogo->SetVertexPos( 400.0f,140.0f,400.0f,200.0f );

	m_pTitleRemake->SetVertexPos( 400.0f, 250.0f, 220.0f, 60.0f );
}

//----------------------------------------------------
// ����
//----------------------------------------------------
void CTitleBackManager::Run( void )
{
	// PUSH START �̃t�F�[�h�C���ƃt�F�[�h�A�E�g
	m_pPushStartPlay->Fade( 255,80, 5 );
}

//----------------------------------------------------
// �t�F�[�h�A�E�g�G�t�F�N�g
//----------------------------------------------------
bool CTitleBackManager::Fade( void )
{
	if ( m_pAlphaBlend->FadeOut( 5 ) )
	{
		return true;
	}

	return false;
}


//----------------------------------------------------
// �`��
//----------------------------------------------------
void CTitleBackManager::Draw( void )
{
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResTitleBackFilePath )->Get(), m_pTitleBack->GetVertex() );
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResTitleLogoFilePath )->Get(),m_pTitleLogo->GetVertex() );
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResTitleRemakeFilePath )->Get(), m_pTitleRemake->GetVertex() );
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResPushStartPlayFilePath )->Get(), m_pPushStartPlay->GetVertex() );
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( m_pAlphaBlend->GetVertex() );	// �G�t�F�N�g�`��
}