
#include "CPauseManager.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CPauseManager::CPauseManager( void )
{
	// ポーズ背景
	m_pPauseBack = new C2DSpriteAlphaBlend;
	m_pResPauseBackFilePath = PAUSE_BACK_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResPauseBackFilePath ); 

	// ポーズ文字
	m_pPause = new C2DSpriteAlphaBlend;
	m_pResPauseFilePath = PAUSE_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResPauseFilePath );

	// リトライ文字
	m_pRetry = new C2DSpriteAlphaBlend;
	m_pResRetryFilePath = RETRY_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResRetryFilePath );

	// リジューム文字
	m_pResume = new C2DSpriteAlphaBlend;
	m_pResResumeFilePath = RESUME_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResResumeFilePath );

	// タイトル文字
	m_pTitle = new C2DSpriteAlphaBlend;
	m_pResTitleFilePath = BACKTITLE_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResTitleFilePath );

	// カーソル
	m_pCursol = new C2DSpriteRHW;
	m_pResCursolFilePath = CURSOL_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResCursolFilePath );

	// 選択エフェクト
	m_pPauseEffect = new C2DSpriteAlphaBlend( eFadeState::FADE_IN );
	m_pResPauseEffectFilePath = PAUSEEFFECT_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResPauseEffectFilePath );

}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CPauseManager::~CPauseManager( void )
{
	SAFE_DELETE( m_pPauseBack );	// ポーズの背景
	SAFE_DELETE( m_pPause );		// Pause
	SAFE_DELETE( m_pRetry );		// Retry
	SAFE_DELETE( m_pResume );		// Resume
	SAFE_DELETE( m_pTitle );		// Title
	SAFE_DELETE( m_pCursol );		// カーソル
	SAFE_DELETE( m_pPauseEffect );	// エフェクト
}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
void CPauseManager::Init( void )
{
	m_isPause = false;
	m_ePauseState = ePauseStatus::RESUME;

	m_pPauseBack->SetVertexPos( 400.0f, 300.0f, 400.0f, 240.0f );
	m_pPause->SetVertexPos( 400.0f,160.0f,250.0f,80.0f );
	m_pResume->SetVertexPos( 400.0f,250.0f,180.0f,40.0f );
	m_pRetry->SetVertexPos( 400.0f,300.0f,180.0f,40.0f );
	m_pTitle->SetVertexPos( 400.0f,350.0f,180.0f,40.0f );

	m_pPauseEffect->SetVertexPos( 400.0f,250.0f,190.0f,40.0f );
	m_pCursol->SetVertexPos( 270.0f, 250.0f, 48.0f, 48.0f );
	
}

//----------------------------------------------------
// ポーズに入るたびに初期化
//----------------------------------------------------
void CPauseManager::InitPause( void )
{
	m_ePauseState = ePauseStatus::RESUME;
	m_pPauseEffect->SetVertexPos( 400.0f,250.0f,190.0f,40.0f );
	m_pCursol->SetVertexPos( 270.0f, 250.0f, 48.0f, 48.0f );

}

//----------------------------------------------------
// 終了
//----------------------------------------------------
void CPauseManager::Uninit( void )
{
}

//----------------------------------------------------
// 処理
//----------------------------------------------------
void CPauseManager::Run()
{
	m_pPauseEffect->Fade( 255, 70, 5 );

	switch( m_ePauseState )
	{
	case RESUME:
		if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_UP ) ||
			CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_DPAD_UP ))
		{
			m_ePauseState = TITLE;
			m_pCursol->SetVertexPos( m_pCursol->GetCenter()->x,m_pTitle->GetCenter()->y );
			m_pPauseEffect->SetVertexPos( m_pPauseEffect->GetCenter()->x,m_pTitle->GetCenter()->y );		
		}
		if( CInputKeyboard::GetInstance()->GetTriggerKeyState(  VK_DOWN  ) ||
			CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_DPAD_DOWN ))
		{
			m_ePauseState = RETRY;
			m_pCursol->SetVertexPos( m_pCursol->GetCenter()->x,m_pRetry->GetCenter()->y );
			m_pPauseEffect->SetVertexPos( m_pPauseEffect->GetCenter()->x,m_pRetry->GetCenter()->y );
		}
		break;

	case RETRY:
		if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_UP ) || 
			CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_DPAD_UP ))
		{
			m_ePauseState = RESUME;
			m_pCursol->SetVertexPos( m_pCursol->GetCenter()->x,m_pResume->GetCenter()->y );
			m_pPauseEffect->SetVertexPos( m_pPauseEffect->GetCenter()->x,m_pResume->GetCenter()->y );
		}
		else if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_DOWN ) ||
				 CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_DPAD_DOWN ))
		{
			m_ePauseState = TITLE;
			m_pCursol->SetVertexPos( m_pCursol->GetCenter()->x,m_pTitle->GetCenter()->y );
			m_pPauseEffect->SetVertexPos( m_pPauseEffect->GetCenter()->x,m_pTitle->GetCenter()->y );
		}
		break;

	case TITLE:
		if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_UP ) || 
			CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_DPAD_UP ))
		{
			m_ePauseState = RETRY;
			m_pCursol->SetVertexPos( m_pCursol->GetCenter()->x,m_pRetry->GetCenter()->y );
			m_pPauseEffect->SetVertexPos( m_pPauseEffect->GetCenter()->x,m_pRetry->GetCenter()->y );
		}
		if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_DOWN ) ||
			CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_DPAD_DOWN ))
		{
			m_ePauseState = RESUME;
			m_pCursol->SetVertexPos( m_pCursol->GetCenter()->x,m_pResume->GetCenter()->y );
			m_pPauseEffect->SetVertexPos( m_pPauseEffect->GetCenter()->x,m_pResume->GetCenter()->y );
		}
		break;

	default:
		break;
	}
}

//----------------------------------------------------
// 描画
//----------------------------------------------------
void CPauseManager::Draw( void )
{
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResPauseBackFilePath )->Get(), m_pPauseBack->GetVertex() );
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResPauseFilePath )->Get(),m_pPause->GetVertex() );
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResResumeFilePath )->Get(),m_pResume->GetVertex() );
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResRetryFilePath )->Get(),m_pRetry->GetVertex() );
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResTitleFilePath )->Get(),m_pTitle->GetVertex() );
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResCursolFilePath )->Get(),m_pCursol->GetVertex() );
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResPauseEffectFilePath )->Get(),m_pPauseEffect->GetVertex() );
}




