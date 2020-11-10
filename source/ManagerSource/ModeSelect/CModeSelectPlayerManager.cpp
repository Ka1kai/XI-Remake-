
#include "CModeSelectPlayerManager.h"

const float PLAYER_MOVE_DEFAULT = 0.2f;

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CModeSelectPlayerManager::CModeSelectPlayerManager( void )
{
	// プレイヤーのインスタンス化
	m_pModeSelectPlayer = new C2DSprite;
	m_pResModeSelectPlayerPath = PLAYER_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResModeSelectPlayerPath );
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CModeSelectPlayerManager::~CModeSelectPlayerManager( void )
{
	SAFE_DELETE( m_pModeSelectPlayer );
}

//----------------------------------------------------
//初期化
//----------------------------------------------------
bool CModeSelectPlayerManager::Init( void )
{
	// プレイヤーの初期化
	m_pModeSelectPlayer->Init();
	m_pModeSelectPlayer->CalcWorldMtx();
	m_pModeSelectPlayer->SetSpritePos( -1.0f, 2.0f, 2.0f );
	m_pModeSelectPlayer->SetSpriteSize( 5.0f, 5.0f );
	m_pModeSelectPlayer->SetUV( 4, 4, 1, 1 );

	m_eMovePlayerStatus = eModeSelectMovePlayerStatus::eModeSelectPlayerMoveNone;
	m_moveValue = 0.0f;

	return true;
}

//----------------------------------------------------
// 終了
//----------------------------------------------------
bool CModeSelectPlayerManager::Uninit( void )
{
	return true;
}

//----------------------------------------------------
// 処理
//----------------------------------------------------
void CModeSelectPlayerManager::Run( void )
{
	
	switch( m_eMovePlayerStatus )
	{
	// 通常状態
	case eModeSelectMovePlayerStatus::eModeSelectPlayerMoveNone:
		break;

	// 左移動
	case eModeSelectMovePlayerStatus::eModeSelectPlayerMoveLeft:
		this->MoveLeft( PLAYER_MOVE_DEFAULT );
		m_pModeSelectPlayer->SetUV( 4, 4, 1, 3 );
		break;

	// 右移動
	case eModeSelectMovePlayerStatus::eModeSelectPlayerMoveRight:
		this->MoveRight( PLAYER_MOVE_DEFAULT );
		m_pModeSelectPlayer->SetUV( 4, 4, 1, 2 );
		break;

	// 上移動
	case eModeSelectMovePlayerStatus::eModeSelectPlayerMoveUp:
		this->MoveUp( PLAYER_MOVE_DEFAULT );
		m_pModeSelectPlayer->SetUV( 4, 4, 1, 4 );
		break;

	// 下移動
	case eModeSelectMovePlayerStatus::eModeSelectPlayerMoveDown:
		this->MoveDown( PLAYER_MOVE_DEFAULT );
		m_pModeSelectPlayer->SetUV( 4, 4, 1, 1 );
		break;

	}

}

//----------------------------------------------------
// 右移動
//----------------------------------------------------
void CModeSelectPlayerManager::MoveRight( CONST float speed )
{
	m_pModeSelectPlayer->MoveSpritePos( speed, 0.0f,0.0f );
	m_moveValue += speed;
	if( m_moveValue >= 4.0f ) 
	{
		m_moveValue = 0.0f;
		m_eMovePlayerStatus = eModeSelectMovePlayerStatus::eModeSelectPlayerMoveNone;
	}
}

//----------------------------------------------------
// 左移動
//----------------------------------------------------
void CModeSelectPlayerManager::MoveLeft( CONST float speed )
{
	m_pModeSelectPlayer->MoveSpritePos( -speed, 0.0f,0.0f );
	m_moveValue -= speed;
	if( m_moveValue <= -4.0f ) 
	{
		m_moveValue = 0.0f;
		m_eMovePlayerStatus = eModeSelectMovePlayerStatus::eModeSelectPlayerMoveNone;
	}
}

//----------------------------------------------------
// 上移動
//----------------------------------------------------
void CModeSelectPlayerManager::MoveUp( CONST float speed )
{
	m_pModeSelectPlayer->MoveSpritePos( 0.0f, 0.0f, speed );
	m_moveValue += speed;
	if( m_moveValue >= 4.0f ) 
	{
		m_moveValue = 0.0f;
		m_eMovePlayerStatus = eModeSelectMovePlayerStatus::eModeSelectPlayerMoveNone;
	}
}

//----------------------------------------------------
// 下移動
//----------------------------------------------------
void CModeSelectPlayerManager::MoveDown( CONST float speed )
{
	m_pModeSelectPlayer->MoveSpritePos( 0.0f, 0.0f, -speed );
	m_moveValue -= speed;
	if( m_moveValue <= -4.0f ) 
	{
		m_moveValue = 0.0f;
		m_eMovePlayerStatus = eModeSelectMovePlayerStatus::eModeSelectPlayerMoveNone;
	}
}

//----------------------------------------------------
// 描画
//----------------------------------------------------
void CModeSelectPlayerManager::Draw( void )
{
	// プレイヤー描画
	CDirectDrawSystem::GetInstance()->DrawSprite( CResourceManager::GetInstance()->GetTexture( m_pResModeSelectPlayerPath )->Get(), m_pModeSelectPlayer->GetVertex(), m_pModeSelectPlayer->GetWorldMtx() );
}