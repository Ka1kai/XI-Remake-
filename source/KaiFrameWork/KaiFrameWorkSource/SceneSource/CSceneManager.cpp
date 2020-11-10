
#include "../../KaiFrameWorkHeader/SceneHeader/CSceneManager.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CSceneManager::CSceneManager( eSceneState state )
{
//	m_pPthread = new CPthread();
	m_pScene = nullptr;

	m_nowScene  = eScene_None;
	m_nextScene = state;
	this->Update();
}

//----------------------------------------------------
// 引数なしコンストラクタ
//----------------------------------------------------
CSceneManager::CSceneManager( void )
{
//	m_pPthread = new CPthread();

	m_pScene = nullptr;
	m_nextScene = eScene_None;
}

//----------------------------------------------------
// デストラクタ　
//	現在のシーンのデストラクタを起動させる
//----------------------------------------------------
CSceneManager::~CSceneManager()
{
	if( m_pScene != NULL )
	{
		m_pScene->Finalize();
		delete m_pScene;
		m_pScene = NULL;
	}

	// スレッドが終了されていなかったら待機
//	m_pPthread->Wait();

//	SAFE_DELETE( m_pPthread );
}

//----------------------------------------------------
// スレッドのロード
//----------------------------------------------------
void* CSceneManager::ThreadLoad( void* func )
{
	CSceneManager* sceneManager = (CSceneManager*)func;;
	
	sceneManager->Load();

	return 0;
}

//----------------------------------------------------
// ロード
//----------------------------------------------------
bool CSceneManager::Load( void )
{
	m_pScene->Load();
	m_pScene->Initialize();

	m_isLoad = true;

	return true;
}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
void CSceneManager::Initialize( void )
{
    m_pScene->Initialize();
}

//----------------------------------------------------
// 終了処理
//----------------------------------------------------
void CSceneManager::Finalize()
{
	m_pScene->Finalize();
}

//----------------------------------------------------
// シーン切り替え処理
//----------------------------------------------------
void CSceneManager::Run( void )
{
	if( m_nextScene != m_nowScene )
	{    //次のシーンがセットされていたら
		if( m_pScene != NULL )
		{
			m_pScene->Finalize();	//現在のシーンの終了処理を実行
			m_isLoad = false;
			delete m_pScene;
		}

		this->Update();	// シーンをインスタンス化
	}

	if( m_isLoad == true )
	{
		m_pScene->Run(); //シーンの更新
	}
	else if( m_isLoad == false )
	{

	}
}

//----------------------------------------------------
// シーンをインスタンス化
//----------------------------------------------------
void CSceneManager::Update( void )
{
	//シーンによって処理を分岐
    switch( m_nextScene )
	{       
		case eSceneState::eSceneGame:
			m_pScene = ( CSceneBase* ) new CSceneGame( this );
			break;
			
		case eSceneState::eSceneTitle:
			m_pScene = ( CSceneBase* ) new CSceneTitle( this );
			break;

		case eSceneState::eSceneModeSelect:
			m_pScene = ( CSceneBase* ) new CSceneModeSelect( this );
			break;

		case eSceneState::eSceneHighScore:
			m_pScene = ( CSceneBase* ) new CSceneScore( this );
			break;

		case eSceneState::eSceneModelView:
			m_pScene = ( CSceneBase* ) new CSceneModelView( this );
			break;

		case eSceneState::eSceneResult:
			m_pScene = ( CSceneBase* ) new CSceneResult( this );
			break;

		case eSceneState::eSceneDebug:
			m_pScene = ( CSceneBase* ) new CSceneDebug( this );
			break;

	}
    m_nextScene = eScene_None;		//次のシーン情報をクリア
	this->Load();
//	m_isLoad = false;
//	m_pPthread->Create( this->ThreadLoad, this );

}

//----------------------------------------------------
// シーンごとに描画
//----------------------------------------------------
void CSceneManager::Draw( void )
{
	if( m_isLoad == true )
	{
		m_pScene->Draw(); //シーンの描画
	}
	else if( m_isLoad == false )
	{
		// NowLoadingの描画
		DrawLoading();
	}
}

//----------------------------------------------------
// 次のシーンをセット
//----------------------------------------------------
void CSceneManager::ChangeScene( eSceneState nextScene )
{
    m_nextScene = nextScene;    //次のシーンをセットする
}

//----------------------------------------------------
// NowLoading....
//----------------------------------------------------
void CSceneManager::DrawLoading( void )
{
}