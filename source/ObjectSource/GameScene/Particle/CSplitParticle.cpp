
#include "CSplitParticle.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CSplitParticle::CSplitParticle( void )
{
	m_pSplitPartcle = new C2DParticle[50];
	for( int i = 0; i < 50; ++ i )
	{
		m_pSplitPartcle[i].SetSprite( &D3DXVECTOR3( 1.0f, 1.0f, 1.0f ), &D3DXVECTOR3( 2.0f, 2.0f, 0.0f ) );
	}
	m_pResParticle = PARTICLE_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResParticle );
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CSplitParticle::~CSplitParticle( void )
{
	SAFE_DELETE_ALLAY( m_pSplitPartcle );
}

//----------------------------------------------------
// エミッター
//----------------------------------------------------
void CSplitParticle::Emitter( CONST float xPos, CONST float yPos, CONST float zPos )
{
	// 速度と方向
	D3DXVECTOR3 speed,dir;
	speed.x = 0.08f;
	speed.y = 0.0f;
	speed.z = 0.08f;

	for( int i = 0; i < 50; ++ i )
	{
		dir.x = (float)CXorShift::GetInstance()->GetRandom( -10, 10 ) / 100;
		dir.y = 0.0f;
		dir.z = (float)CXorShift::GetInstance()->GetRandom( -10, 10 ) / 100;

		m_pSplitPartcle[i].SetSpritePos( xPos, 0.0f, zPos );
		m_pSplitPartcle[i].SetParticle( &speed, &dir, 70 );
		m_pSplitPartcle[i].SetDiffuse( 255, 255, 0, 100 );
	}
}

//----------------------------------------------------
// 移動
//----------------------------------------------------
void CSplitParticle::Move( void )
{
	for( int i = 0; i < 50; ++ i )
	{
		if( m_pSplitPartcle[i].GetExist() == true )
		{
			m_pSplitPartcle[i].Move();
			m_pSplitPartcle[i].LifeDown( 1 );
		}
	}
}

//----------------------------------------------------
// 描画
//----------------------------------------------------
void CSplitParticle::Draw( CONST D3DXMATRIX* view )
{
	for( int i = 0; i < 50; ++ i )
	{
		if( m_pSplitPartcle[i].GetExist() == true )
		{
			m_pSplitPartcle[i].CalcWorldMtx( view );
			CDirectDrawSystem::GetInstance()->DrawSprite( CResourceManager::GetInstance()->GetTexture( m_pResParticle )->Get(), 
														  m_pSplitPartcle[i].GetVertex(),
														  m_pSplitPartcle[i].GetWorldMtx() );
		}
	}
}