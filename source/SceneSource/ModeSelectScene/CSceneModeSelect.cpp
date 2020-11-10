
#include "CSceneModeSelect.h"

//----------------------------------------------------
// 引数なしコンストラクタ
//----------------------------------------------------
CSceneModeSelect::CSceneModeSelect( void )
{
}

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CSceneModeSelect::CSceneModeSelect( CSceneChange* change ) : CSceneBase( change )
{
}

//----------------------------------------------------
// ロード
//----------------------------------------------------
bool CSceneModeSelect::Load( void )
{
	// カメラ・ライトをインスタンス化
	m_pDirectCamera = new CDirectCamera;
	m_pDirectLight = new CDirectLight;

	// 背景のマネージャクラス生成
	m_pModeSelectBackManager = new CModeSelectBackManager;

	// プレイヤのマネージャクラス生成
	m_pModeSelectPlayerManager = new CModeSelectPlayerManager;

	return true;
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CSceneModeSelect::~CSceneModeSelect( void )
{
	SAFE_DELETE( m_pDirectCamera );
	SAFE_DELETE( m_pDirectLight );
	SAFE_DELETE( m_pModeSelectBackManager );
	SAFE_DELETE( m_pModeSelectPlayerManager );
}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
void CSceneModeSelect::Initialize( void )
{
	m_pDirectCamera->Init( 800,600 );
	m_pDirectCamera->SetPosition( 5.0f, 20.0f, -10.0f );
	m_pDirectLight->Init();

	m_pModeSelectBackManager->Init();

	m_pModeSelectPlayerManager->Init();

	m_modeIndexNo = 1;
	m_eMode = modeAllay[ m_modeIndexNo ];

	m_isFade = false;
}

//----------------------------------------------------
// 処理
//----------------------------------------------------
void CSceneModeSelect::Run( void )
{
	CInputKeyboard::GetInstance()->Update();
	CJoyStick::GetInstance()->Update();

	// 右キー入力
	if( ( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_RIGHT ) || 
		CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_DPAD_RIGHT ) ) && 
		m_modeIndexNo < 3 &&
		m_pModeSelectBackManager->GetMessageBarStatus() == eMessageBarStatus::eMessageBarNormal )
	{	
		m_modeIndexNo ++;
		m_eMode = modeAllay[ m_modeIndexNo ];
		m_pModeSelectBackManager->RunKey( m_modeIndexNo );
		m_pModeSelectBackManager->SetMessageBarStatus( eMessageBarStatus::eMessageBarAnimation );
		m_pModeSelectPlayerManager->SetMovePlayerStatus( eModeSelectMovePlayerStatus::eModeSelectPlayerMoveRight );
	}
	
	// 左キー入力
	if( ( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_LEFT ) ||
		CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_DPAD_LEFT ) ) &&
		m_modeIndexNo > 0 && m_modeIndexNo < 4 &&
		m_pModeSelectBackManager->GetMessageBarStatus() == eMessageBarStatus::eMessageBarNormal) 
	{
		m_modeIndexNo --;
		m_eMode = modeAllay[ m_modeIndexNo ];
		m_pModeSelectBackManager->RunKey( m_modeIndexNo );
		m_pModeSelectBackManager->SetMessageBarStatus( eMessageBarStatus::eMessageBarAnimation );
		m_pModeSelectPlayerManager->SetMovePlayerStatus( eModeSelectMovePlayerStatus::eModeSelectPlayerMoveLeft );
	}

	// 上キー入力
	if( ( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_UP ) || 
		CJoyStick::GetInstance()->GetTriggerButton( 0 ,XINPUT_GAMEPAD_DPAD_UP ) ) &&
		( m_modeIndexNo == 1 || m_modeIndexNo == 5 ) &&
		m_pModeSelectBackManager->GetMessageBarStatus() == eMessageBarStatus::eMessageBarNormal)
	{
		if( m_modeIndexNo == 1 )
		{
			m_modeIndexNo = 4;
		}

		if( m_modeIndexNo == 5 )
		{
			m_modeIndexNo = 1;
		}
		m_eMode = modeAllay[ m_modeIndexNo ];
		m_pModeSelectBackManager->RunKey( m_modeIndexNo );
		m_pModeSelectBackManager->SetMessageBarStatus( eMessageBarStatus::eMessageBarAnimation );
		m_pModeSelectPlayerManager->SetMovePlayerStatus( eModeSelectMovePlayerStatus::eModeSelectPlayerMoveUp );
	}

	// 下キー入力
	if( ( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_DOWN ) ||
		CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_DPAD_DOWN ) ) &&
		( m_modeIndexNo == 1 || m_modeIndexNo == 4 ) &&
		m_pModeSelectBackManager->GetMessageBarStatus() == eMessageBarStatus::eMessageBarNormal)
	{
		if( m_modeIndexNo == 1 )
		{
			m_modeIndexNo = 5;
		}

		if( m_modeIndexNo == 4 )
		{
			m_modeIndexNo = 1;
		}
		m_eMode = modeAllay[ m_modeIndexNo ];
		m_pModeSelectBackManager->RunKey( m_modeIndexNo );
		m_pModeSelectBackManager->SetMessageBarStatus( eMessageBarStatus::eMessageBarAnimation );
		m_pModeSelectPlayerManager->SetMovePlayerStatus( eModeSelectMovePlayerStatus::eModeSelectPlayerMoveDown );
	}


	// シーンの切り替え
	if( ( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_SPACE ) ||
		CJoyStick::GetInstance()->GetTriggerButton( 0,XINPUT_GAMEPAD_A ) ) && 
		( m_eMode == eModeSelectState::eModeGamePlay ||
		m_eMode == eModeSelectState::eModeTitle ||
		m_eMode == eModeSelectState::eModeExit ||
		m_eMode == eModeSelectState::eModeRecord) )
	{
		m_isFade = true;
	}
	
	if( m_isFade == true )
	{
		// フェードアウトが終わったらシーンを切り替える
		if( m_pModeSelectBackManager->Fade() )
		{
			switch( m_eMode )
			{
			// ゲームプレイ
			case eModeSelectState::eModeGamePlay:
				mSceneChanger->ChangeScene( eSceneState::eSceneGame );	// 現在はゲームのシーンに遷移
				break;
		
			// タイトル
			case eModeSelectState::eModeTitle:
				mSceneChanger->ChangeScene( eSceneState::eSceneTitle );
				break;

			// スコア
			case eModeRecord:
				mSceneChanger->ChangeScene( eSceneState::eSceneHighScore );
				break;

			// 終了
			case eModeSelectState::eModeExit:
			SendMessage( CWindowSystem::GethWnd(),WM_CLOSE,0,0 );
				break;

			default:
				break;
			}
		}		
	}

	// 背景用マネージャー
	m_pModeSelectBackManager->Run();

	// プレイヤー用マネージャー
	m_pModeSelectPlayerManager->Run();


#ifdef _DEBUG
	// F1キーでデバッグシーンに戻る
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_F1 ) )
	{
		mSceneChanger->ChangeScene( eSceneState::eSceneDebug );
	}
#endif
}

//----------------------------------------------------	
// 描画
//----------------------------------------------------
void CSceneModeSelect::Draw( void )
{
	m_pModeSelectBackManager->Draw();
	m_pModeSelectPlayerManager->Draw();
	m_pModeSelectBackManager->DrawAlpha();
}

//----------------------------------------------------
// 終了
//----------------------------------------------------
void CSceneModeSelect::Finalize( void )
{
	m_pModeSelectBackManager->Uninit();
	m_pModeSelectPlayerManager->Uninit();
}
