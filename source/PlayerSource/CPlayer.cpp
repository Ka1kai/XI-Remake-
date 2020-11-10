
#include "CPlayer.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CPlayer::CPlayer( void )
{
	m_pAABB = new THITAABB;
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CPlayer::~CPlayer( void )
{
	SAFE_DELETE( m_pAABB );
}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
bool CPlayer::Init( void )
{
	// スプライトの設定
	this->SetSprite( &D3DXVECTOR3( 0.0f,4.0f,0.0f ), &D3DXVECTOR3( 5.0f, 4.0f, 0.0f ));
	this->SetUV( 4, 4, 1, 1 );

	// ダイスとの当たり判定用の仮想AABBを作成
	D3DXVECTOR3 aabbPos = D3DXVECTOR3( this->GetXPos() , this->GetYPos(), this->GetZPos() );
	D3DXVECTOR3 aabbSize = D3DXVECTOR3( 0.5f, 8.0f , 0.5f );
	m_pAABB = CCollision::GetInstance()->SetAABB( m_pAABB, &aabbPos, &aabbSize );

	// ステータス初期化
	m_status = ePlayerStatus::eOnDice;
	m_moveStatus = ePlayerMoveStatus::eMoveNone;
	
	return true;
}
//----------------------------------------------------
// 終了処理
//----------------------------------------------------
bool CPlayer::Uninit( void )
{
	return true;
}

//----------------------------------------------------
// 前移動
//----------------------------------------------------
void CPlayer::MoveFront( CONST float speed )
{
	MoveSpritePos( 0.0f, 0.0f, speed );
	this->SetUV( 4, 4, 1, 4 );

	// AABB位置更新
	this->SetAABB();
	CDebugMode::m_pPlayerBox.SetWorldPos( GetXPos(), GetYPos(), GetZPos() );
}

//----------------------------------------------------
// 後移動
//----------------------------------------------------
void CPlayer::MoveBack( CONST float speed )
{
	MoveSpritePos( 0.0f, 0.0f, -speed );
	this->SetUV( 4, 4, 1, 1 );

	// AABB位置更新
	this->SetAABB();
	CDebugMode::m_pPlayerBox.SetWorldPos( GetXPos(), GetYPos(), GetZPos() );
}

//----------------------------------------------------
// 右移動
//----------------------------------------------------
void CPlayer::MoveRight( CONST float speed )
{
	MoveSpritePos( speed, 0.0f, 0.0f );
	this->SetUV( 4, 4, 1, 2 );

	// AABB位置更新
	this->SetAABB();
	CDebugMode::m_pPlayerBox.SetWorldPos( GetXPos(), GetYPos(), GetZPos() );
}

//----------------------------------------------------
// 左移動
//----------------------------------------------------
void CPlayer::MoveLeft( CONST float speed )
{
	MoveSpritePos( -speed, 0.0f, 0.0f );
	this->SetUV( 4, 4, 1, 3 );
	
	// AABB位置更新
	this->SetAABB();
	CDebugMode::m_pPlayerBox.SetWorldPos( GetXPos(), GetYPos(), GetZPos() );

}

//----------------------------------------------------
// ダウン処理
//----------------------------------------------------
void CPlayer::MoveDown( CONST float speed )
{
	MoveSpritePos( 0.0f, -speed, 0.0f );

	// AABB位置更新
	this->SetAABB();
	CDebugMode::m_pPlayerBox.SetWorldPos( GetXPos(), GetYPos(), GetZPos() );
}

//----------------------------------------------------
// アップ処理
//----------------------------------------------------
void CPlayer::MoveUp( CONST float speed  )
{
	MoveSpritePos( 0.0f, speed, 0.0f );

	// AABB位置更新
	this->SetAABB();
	CDebugMode::m_pPlayerBox.SetWorldPos( GetXPos(), GetYPos(), GetZPos() );
}