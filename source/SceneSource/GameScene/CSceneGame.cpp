
#include "CSceneGame.h"


const int ConstGamePlayTime = 180;

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CSceneGame::CSceneGame( void )
{

}

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CSceneGame::CSceneGame( CSceneChange* change ) : CSceneBase( change ) 
{
}

//----------------------------------------------------
// ロード
//----------------------------------------------------
bool CSceneGame::Load( void )
{
	m_pDirectCamera	= new CDirectCamera;

	m_pDirectLight = new CDirectLight;

	// αブレンドのための背景ポリゴン
	m_pBack = new C2DSpriteAlphaBlend;
	m_pTimeUP = new C2DSpriteRHW;
	m_pResTimeUpFilePath = TIMEUP_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResTimeUpFilePath );
	m_pPushEnter = new C2DSpriteRHW;
	m_pResPushEnterFilePath = TIMEUP_PUSHENTER_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResPushEnterFilePath );

	// Manager
	m_pGameStageManager = new CGameStageManager;
	m_pPauseManager = new CPauseManager;
	m_pTimeManager = new CTimeManager;
	m_pScoreManager = new CScoreManager;
	m_pDiceInfoManager = new CDiceInfoManager;
	m_pSnowObj = new CSnowObj;
	m_pSpaceParticle = new CSpaceParticle;

	// タイムアップ
	m_pTimeUP->SetVertexPos( 400.0f,280.0f,450.0f,180.0f );

	// PUSH ENTER
	m_pPushEnter->SetVertexPos( 600.0f,500.0f,256.0f,64.0f );

	CDiceObjManager::GetInstance()->SetDiceInfoManager( m_pDiceInfoManager );
	CPlayerManager::GetInstance()->SetDiceInfoManager( m_pDiceInfoManager );

#ifdef _DEBUG
	CDebugMode::Load();	// デバッグ画面のロード
#endif

	return true;
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CSceneGame::~CSceneGame( void )
{
	SAFE_DELETE( m_pDirectCamera );			// カメラの解放
	SAFE_DELETE( m_pDirectLight );			// ライトの解放
	SAFE_DELETE( m_pBack );					// αブレンドのためのもの
	SAFE_DELETE( m_pTimeUP );				// タイムアップ
	SAFE_DELETE( m_pPushEnter );			// PUSH ENTER
	SAFE_DELETE( m_pGameStageManager );		// 背景のマネージャー
	SAFE_DELETE( m_pTimeManager );			// タイムのマネージャー
	SAFE_DELETE( m_pScoreManager );			// スコアのマネージャー
	SAFE_DELETE( m_pDiceInfoManager );		// ダイスInfoのマネージャー
	SAFE_DELETE( m_pPauseManager );	//  ポーズボタンの解放
	SAFE_DELETE( m_pSnowObj );				// 雪
	SAFE_DELETE( m_pSpaceParticle );		// 雪のパーティクル
}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
void CSceneGame::Initialize( void )
{
	m_pDirectCamera->Init( 800, 640);
	m_pDirectCamera->SetPosition( 18.0f, 24.0f, -27.0f );
	m_pDirectCamera->SetAt( -2.0f, 0.0f,0.0f );

	m_pDirectLight->Switch( true );
	CPlayerManager::GetInstance()->BrightChange( true );	// プレイヤーの色変更
	m_pTimeManager->BrightChange( true );					// タイムの色変更
	m_pScoreManager->BrightChange( true );					// スコアの色変更
	m_pDiceInfoManager->BrightChange( true );				// INFOの色変更

	// 乱数の初期化
	CDiceRandSystem::GetInstance()->InitSeed();
	
	// 背景ポリゴン
	m_pBack->SetVertexPos( 400.0f,320.0f,800.0f,640.0f );
	m_pBack->SetDiffuse( 255,255,255,0 );


#ifdef _DEBUG
	CDebugMode::Init();
	CDebugMode::Set( m_pTimeManager->GetTime() );
#endif

	// Manager
	m_pGameStageManager->Init();
	CStageBlockManager::GetInstance()->Init();
	CStageBlockManager::GetInstance()->SetBlockPos();
	m_pPauseManager->Init();
	m_pTimeManager->Init( ConstGamePlayTime );
	m_pScoreManager->Init();
	m_pDiceInfoManager->Init();
	CPlayerManager::GetInstance()->Init();
	CPlayerManager::GetInstance()->SetCameraToMtx( m_pDirectCamera->GetView() );
	CDiceObjManager::GetInstance()->Init();

	// チェインの管理クラスにスコアのポインタをセット
	CChainManager::GetInstance()->SetScore( m_pScoreManager->GetScore() );

	m_eGamePlayStatus = GAMEPLAY_STATUS::GAME_PLAY;

}

//----------------------------------------------------
// ゲームシーンの終了
//----------------------------------------------------
void CSceneGame::Finalize( void )
{
}

//----------------------------------------------------
// ゲームシーンの処理
//----------------------------------------------------
void CSceneGame::Run( void )
{
	// デバイスの更新
	CInputKeyboard::GetInstance()->Update();
	CJoyStick::GetInstance()->Update();

	switch( m_eGamePlayStatus )
	{
		// ゲームプレイ中
		case GAMEPLAY_STATUS::GAME_PLAY:
			CPlayerManager::GetInstance()->Run();
			m_pGameStageManager->Run();
			CDiceObjManager::GetInstance()->Run();
			m_pScoreManager->Run();
			m_pTimeManager->Run();
			this->ChangePause();		// ポーズ切り替え
			this->TimeUp();				// タイムアップ
			break;

		// ポーズ中
		case GAMEPLAY_STATUS::GAME_PAUSE:
			m_pPauseManager->Run();
			this->Pause();				// ポーズ中
			this->ChangePause();		// ポーズ切り替え
			break;

		// タイムアップ中
		case GAMEPLAY_STATUS::TIME_UP:
			if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_RETURN ) ||
				CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_A ) )
			{
				m_eGamePlayStatus = GAMEPLAY_STATUS::TIME_UP_FADE;
			}
			break;

		// タイムアップのフェード
		case GAMEPLAY_STATUS::TIME_UP_FADE:
			this->TimeUpFade();
			break;

		// ポーズのフェード
		case GAMEPLAY_STATUS::PAUSE_FADE:
			this->PauseFade();
			break;

#ifdef _DEBUG
		// デバッグモード中
		case GAMEPLAY_STATUS::DEBUG_MODE:
			CDebugMode::RunDebugMode();
			if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_F1 ) || CDebugMode::m_isDebugMode == false )
			{
				m_eGamePlayStatus = GAMEPLAY_STATUS::GAME_PLAY;
				return;
			}
			break;
#endif
	}

// デバッグモードに入る
#ifdef _DEBUG
	CDebugMode::Run( m_pDirectCamera );
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_F1 ) && m_eGamePlayStatus != GAMEPLAY_STATUS::DEBUG_MODE )
	{
		CDebugMode::InitDebugMode();
		m_eGamePlayStatus = GAMEPLAY_STATUS::DEBUG_MODE;
	}

#endif
}

//----------------------------------------------------
// 描画
//----------------------------------------------------
void CSceneGame::Draw( void )
{
	m_pGameStageManager->Draw();	// ステージ

	// ダイス
	CDiceObjManager::GetInstance()->Draw( m_pDirectCamera->GetView() );

	// プレイヤー
	CPlayerManager::GetInstance()->Draw();

// デバッグ時のみデバッグ画面
#ifdef _DEBUG
	CDebugMode::Draw();
#endif

	switch( m_eGamePlayStatus )
	{
		// ゲームプレイ中
		case GAMEPLAY_STATUS::GAME_PLAY:
			break;

		// ポーズ中
		case GAMEPLAY_STATUS::GAME_PAUSE:
			m_pPauseManager->Draw();
			break;

		// ポーズフェード中
		case GAMEPLAY_STATUS::PAUSE_FADE:
			m_pPauseManager->Draw();
			break;

		// デバッグ中
#ifdef _DEBUG
		case GAMEPLAY_STATUS::DEBUG_MODE:
			CDebugMode::DrawDebugMode();
			break;
#endif 

		// タイムアップ中
		case GAMEPLAY_STATUS::TIME_UP:
			CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResTimeUpFilePath )->Get(), m_pTimeUP->GetVertex() );
//			CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResPushEnterFilePath )->Get() ,m_pPushEnter->GetVertex() );
			break;
	}
	m_pDiceInfoManager->Draw();	// Info
	m_pScoreManager->Draw();	// スコア
	m_pTimeManager->Draw();		// タイム
		

	// 背景描画
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( NULL, m_pBack->GetVertex() );
}

//----------------------------------------------------
// ポーズ切り替え
//----------------------------------------------------
void CSceneGame::ChangePause( void )
{
	// ESCAPEキーでポーズ切り替え
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_ESCAPE ) || 
		  CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_START ) )
	{
		bool isPause = false;

		// ポーズのフラグを取得
		m_pPauseManager->SetIsPause();
		isPause = m_pPauseManager->GetIsPause();
	
		m_pDirectLight->Switch( !isPause );							// ライトのスイッチ変更
		CPlayerManager::GetInstance()->BrightChange( !isPause );	// プレイヤーの色変更
		m_pTimeManager->BrightChange( !isPause );					// タイムの色変更
		m_pScoreManager->BrightChange( !isPause );					// スコアの色変更
		m_pDiceInfoManager->BrightChange( !isPause );				// INFOの色変更

		if( m_eGamePlayStatus == GAMEPLAY_STATUS::GAME_PLAY )
		{
			m_pPauseManager->InitPause();
			m_eGamePlayStatus = GAMEPLAY_STATUS::GAME_PAUSE;
		}
		else if( m_eGamePlayStatus == GAMEPLAY_STATUS::GAME_PAUSE )
		{
			m_eGamePlayStatus = GAMEPLAY_STATUS::GAME_PLAY;
		}
	}
}

//----------------------------------------------------
// ポーズ
//----------------------------------------------------
void CSceneGame::Pause( void )
{
	// ポーズ処理
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_RETURN ) || 
		CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_A  ) )
	{
		if( m_pPauseManager->GetPauseState() == ePauseStatus::RESUME )
		{
			bool isPause = false;

			m_pPauseManager->SetIsPause();
			isPause = m_pPauseManager->GetIsPause();
			m_pDirectLight->Switch( !isPause );							// ライトのスイッチ変更
			CPlayerManager::GetInstance()->BrightChange( !isPause );	// プレイヤーの色変更
			m_pTimeManager->BrightChange( !isPause );					// タイムの色変更
			m_pScoreManager->BrightChange( !isPause );					// スコアの色変更
			m_pDiceInfoManager->BrightChange( !isPause );				// INFOの色変更
			m_eGamePlayStatus = GAMEPLAY_STATUS::GAME_PLAY;
		}
		else 
		{
			// フェード中に設定する
			m_eGamePlayStatus = GAMEPLAY_STATUS::PAUSE_FADE;
		}
	}
}

//----------------------------------------------------
// ポーズのフェード
//----------------------------------------------------
void CSceneGame::PauseFade( void )
{
	if( m_pBack->FadeOut( 3 ) )
	{
		// フェードした後の遷移
		switch( m_pPauseManager->GetPauseState() )
		{
		case RETRY:
			this->Initialize();
			break;

		case TITLE:
			mSceneChanger->ChangeScene( eSceneState::eSceneTitle );
			break;

		}		
	}
}

//----------------------------------------------------
// タイムアップ
//----------------------------------------------------
void CSceneGame::TimeUp( void )
{
	// タイムアップ処理
	if( m_pTimeManager->TimeUP() == true )
	{
		m_pDirectLight->Switch( false );
		CPlayerManager::GetInstance()->BrightChange( false );	// プレイヤーの色変更
		m_pTimeManager->BrightChange( false );					// タイムの色変更
		m_pScoreManager->BrightChange( false );					// スコアの色変更
		m_pDiceInfoManager->BrightChange( false );				// INFOの色変更

		m_eGamePlayStatus = GAMEPLAY_STATUS::TIME_UP;
	}
}

//----------------------------------------------------
// タイムアップのフェード
//----------------------------------------------------
void CSceneGame::TimeUpFade( void )
{
	if( m_pBack->FadeOut( 3 ) )
	{
		// ゲームのスコアをユーザデータとして保存
		CUserManager::GetInstance()->InitGameScore();
		CUserManager::GetInstance()->SetGameScore( m_pScoreManager->GetScore() );

		// フェードが終わったらシーン切り替え
		mSceneChanger->ChangeScene( eSceneState::eSceneResult );
	}
}