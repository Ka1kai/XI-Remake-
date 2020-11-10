
#include "CSceneTitle.h"

//----------------------------------------------------
// タイトルシーンのコンストラクタ
//----------------------------------------------------
CSceneTitle::CSceneTitle( CSceneChange* change) : CSceneBase(change) 
{	
}

//----------------------------------------------------
// ロード
//----------------------------------------------------
bool CSceneTitle::Load( void )
{
	m_pDirectCamera = new CDirectCamera();
	m_pDirectCamera->Init(800,640);

	m_pDirectLight = new CDirectLight();

	// Managerクラス
	m_pTitleBackManager = new CTitleBackManager();

	// userのセット
	CUserManager::GetInstance()->Login();
	DEBUG::PrintfColor(DEBUG::H_RED,"ユーザログイン\n");

	return true;
}

//----------------------------------------------------
// タイトルシーンのデストラクタ
//----------------------------------------------------
CSceneTitle::~CSceneTitle( void )
{
	SAFE_DELETE( m_pDirectCamera );			// カメラの解放
	SAFE_DELETE( m_pDirectLight );			// ライトの解放
	SAFE_DELETE( m_pTitleBackManager );		// 背景のマネージャークラス解放	

}

//----------------------------------------------------
// タイトル画面の初期化
//----------------------------------------------------
void CSceneTitle::Initialize( void )
{	
	// Manager
	m_pTitleBackManager->Init();
}

//----------------------------------------------------
// タイトルシーンの処理
//----------------------------------------------------
void CSceneTitle::Run( void )
{
	CInputKeyboard::GetInstance()->Update();
	CJoyStick::GetInstance()->Update();
	
	m_pTitleBackManager->Run();			// 背景処理

	this->Draw();	// 描画


	// スタートボタンが押されたらゲームスタート
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_SPACE ) ||
		CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_START ) )
	{
		m_pTitleBackManager->SetIsFade( true );
	}
	
	if( m_pTitleBackManager->GetIsFade() )
	{
		if( m_pTitleBackManager->Fade() )
		{
			mSceneChanger->ChangeScene( eSceneState::eSceneModeSelect );
		}
	}

// デバッグの時のみF1キーを押したらデバッグ画面に戻る
#ifdef _DEBUG
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_F1 ) )
	{
		mSceneChanger->ChangeScene( eSceneState::eSceneDebug );
	}
#endif
}

//----------------------------------------------------
// タイトル画面の描画
//----------------------------------------------------
void CSceneTitle::Draw( void )
{
	m_pTitleBackManager->Draw();			// 背景描画
}

//----------------------------------------------------
// タイトルシーンの終了
//----------------------------------------------------
void CSceneTitle::Finalize()
{

}
