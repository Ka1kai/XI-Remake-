
#include "CSnowObj.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CSnowObj::CSnowObj()
{
	m_rand		= new CRandSystem();
	m_snow		= new C2DParticle[100]();
	for( int i  = 0; i < 100; ++ i )
	{
		m_snow[i].SetSprite( &D3DXVECTOR3( 10.0f, 0.0f, 0.0f ), &D3DXVECTOR3( 3.0f, 3.0f, 0.0f ) );
	}
	m_pResSnowFilePath = PARTICLE_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResSnowFilePath );
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CSnowObj::~CSnowObj()
{
	SAFE_DELETE_ALLAY( m_snow );
	SAFE_DELETE( m_rand );
}

//----------------------------------------------------
// エミッター
//----------------------------------------------------
void CSnowObj::Emitter	( void )
{
	if( m_rand->GetRand( 4 ) <= 2 )
	{
		D3DXVECTOR3 speed = D3DXVECTOR3( 0.0f,0.5f, 0.0f );
		D3DXVECTOR3 dir	= D3DXVECTOR3( 0.0f,-0.5f,0.0f );
		for( int i = 0; i < 100; i ++ ){
			if( m_snow[i].GetLife() <= 0 )
			{
				m_snow[i].SetSpritePos( 0.0f, 4.0f, 0.0f);
				m_snow[i].SetParticle ( &D3DXVECTOR3( 0.0f, 0.5f, 0.0f ), &D3DXVECTOR3( 0.0f, -0.5f, 0.0f ) , 2000 );
				break;
			}
		}
	}
}

//----------------------------------------------------
// 移動
//----------------------------------------------------
void CSnowObj::Move	( void )
{
	for( int i = 0; i < 100; ++ i )
	{
		if( m_snow[i].GetLife() > 0 )
		{
			m_snow[i].Move();
			// ライフを減らす
	/*		m_snow[i].LifeDown( m_rand->GetRand( 1,5 ));
			m_snow[i].SetAlfa( m_snow[i].GetAlfa() - 1 );
			if( m_snow[i].GetAlfa() <= 0 )
			{
				m_snow[i].SetLife( 0 );
			}
		}
		*/
		}
	}
}

//----------------------------------------------------
// 描画
//----------------------------------------------------
void CSnowObj::Draw( CDirectCamera* directCamera )
{
	for( int i = 0; i < 100; ++ i )
	{
		if( m_snow[i].GetLife() > 0 )
		{
			m_snow[i].CalcWorldMtx( directCamera->GetView() );
			CDirectDrawSystem::GetInstance()->DrawSprite( CResourceManager::GetInstance()->GetTexture( m_pResSnowFilePath )->Get(), m_snow[i].GetVertex(),m_snow[i].GetWorldMtx() );
		}
	}
}