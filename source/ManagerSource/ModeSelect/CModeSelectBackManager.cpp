
#include "CModeSelectBackManager.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CModeSelectBackManager::CModeSelectBackManager( void )
{
	// モードセレクトのステージ
	m_pModeSelectStage = new CObjectBase;
	m_pResModeSelectStageFilePath = MODE_STAGE_XFILEPATH;
	CResourceManager::GetInstance()->LoadXFile( m_pResModeSelectStageFilePath );

	// αブレンド用画像
	m_pAlphaBlend = new C2DSpriteAlphaBlend;

	// メニューの画像
	m_pMenuValue = new C2DSpriteAlphaBlend;
	m_pResMenuValueFilePath = MODE_MENU_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResMenuValueFilePath );

	// メッセージバー
	m_pMessageBar = new CMessageBar;
	m_resIndexNo = 1;
	m_isBarAnimation = false;
	m_pResMessageBar[0] = MODE_TITLEMESSAGE_PNGPATH;
	m_pResMessageBar[1] = MODE_GAMEPLAYMESSAGE_PNGPATH;
	m_pResMessageBar[2] = MODE_OPTIONMESSAGE_PNGPATH;
	m_pResMessageBar[3] = MODE_EXITMESSAGE_PNGPATH;
	m_pResMessageBar[4] = MODE_RANKINGMESSAGE_PNGPATH;
	m_pResMessageBar[5] = MODE_RECORDMESSAGE_PNGPATH;

	for( int i = 0; i < 6; ++ i )
	{
		CResourceManager::GetInstance()->LoadTexture( m_pResMessageBar[i] );
	}
}

//----------------------------------------------------
// デストラクタ　
//----------------------------------------------------
CModeSelectBackManager::~CModeSelectBackManager( void )
{
	SAFE_DELETE( m_pModeSelectStage );
	SAFE_DELETE( m_pAlphaBlend );
	SAFE_DELETE( m_pMenuValue );
	SAFE_DELETE( m_pMessageBar );
}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
bool CModeSelectBackManager::Init( void )
{
	m_pModeSelectStage->Init();
	m_pModeSelectStage->SetWorldPos( -1.0f,0.0f, 2.0f );

	// αブレンド用画像
	m_pAlphaBlend->SetVertexPos( 400.0f,320.0f,800.0f,640.0f );
	m_pAlphaBlend->SetDiffuse( 255,255,255,0 );

	// メニューの画像
	m_pMenuValue->Init();
	m_pMenuValue->SetVertexPos( 150.0f, 80.0f, 230.0f,120.0f );

	// メッセージバー
	m_pMessageBar->Init();
	m_pMessageBar->SetVertexPos( 550.0f,540.0f, 470.0f, 128.0f );
	m_eMessageBarStatus = eMessageBarStatus::eMessageBarNormal;

	return true;
}

//----------------------------------------------------
// 処理
//----------------------------------------------------
void CModeSelectBackManager::Run( void )
{
	this->MessageBarAnimation();
}

//----------------------------------------------------
// フェードアウト処理
//----------------------------------------------------
bool CModeSelectBackManager::Fade( void )
{
	if ( m_pAlphaBlend->FadeOut( 5 ) )
	{
		return true;
	}

	return false;
}

//----------------------------------------------------
// キー入力
//----------------------------------------------------
void CModeSelectBackManager::RunKey( CONST UINT index )
{
	m_resIndexNo = index;	// 添え字の番号を対応させる
	m_isBarAnimation = true;
}

//----------------------------------------------------
// エンターキー入力
//----------------------------------------------------
void CModeSelectBackManager::RunKeyEnter( void )
{
	m_isAlphaBlend  = true;
}

//----------------------------------------------------
// メッセージバーのアニメーション
//----------------------------------------------------
bool CModeSelectBackManager::MessageBarAnimation( void )
{
	static bool isHide = false;

	// アニメーションのフラグがONになったら
	if( m_isBarAnimation == true )
	{
		if( m_pMessageBar->RepositionRight( 1000.0f, 40.0f ) == true )
		{
			m_isBarAnimation = false;
			isHide = true;
		}
	}

	if( isHide == true )
	{
		if( m_pMessageBar->RepositionLeft( 550.0f, 40.0f ) == true )
		{
			isHide = false;
			// アニメーションが終わった
			m_eMessageBarStatus = eMessageBarStatus::eMessageBarNormal;
			return true;
		}
	}

	return false;
}

//----------------------------------------------------
// 描画
//----------------------------------------------------
void CModeSelectBackManager::Draw( void )
{
	CDirectDrawSystem::GetInstance()->Draw3D( CResourceManager::GetInstance()->GetXFile( m_pResModeSelectStageFilePath ), m_pModeSelectStage->GetWorldMtx() );

	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResMenuValueFilePath )->Get(), m_pMenuValue->GetVertex() );

	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResMessageBar[m_resIndexNo] )->Get(), m_pMessageBar->GetVertex() );
}

//----------------------------------------------------
// αブレンド用画像の描画
//----------------------------------------------------
void CModeSelectBackManager::DrawAlpha( void )
{
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( m_pAlphaBlend->GetVertex() );
}

//----------------------------------------------------
// 終了
//----------------------------------------------------
bool CModeSelectBackManager::Uninit( void )
{

	return true;
}