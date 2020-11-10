
#include "CSpaceParticle.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CSpaceParticle::CSpaceParticle( void )
{
	m_pRand	= new CRandSystem;
	m_pSpaceParticle	= new CParticle[100];
	m_pSpacePatricleFilePath = PARTICLE_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pSpacePatricleFilePath );

	m_isSpaceParticle = false;
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CSpaceParticle::~CSpaceParticle( void )
{
	if( m_pRand != NULL )
	{
		delete m_pRand;
		m_pRand = NULL;
	}

	if( m_pSpaceParticle != NULL )
	{
		delete[] m_pSpaceParticle;
		m_pSpaceParticle = NULL;
	}
}

//----------------------------------------------------
// エミッター
//----------------------------------------------------
void CSpaceParticle::Emitter( void )
{
	if( m_isSpaceParticle == false )
	{
		m_isSpaceParticle = true;
		m_spaceCnt = 100;

		int x,y,z;

		x = m_pRand->GetRand( 150,150,true );
		y = m_pRand->GetRand(80,30 );
		z = m_pRand->GetRand( 250,350 );
		for( int i = 0; i < 100; ++ i )
		{
			m_pSpaceParticle[i].SetLife( 1000 );
			m_pSpaceParticle[i].SetPosition( (float)x,(float)y,(float)z );
			m_pSpaceParticle[i].SetBillboard( 7.0f,D3DCOLOR_ARGB( 200,180,180,0 ) );
			m_pSpaceParticle[i].SetParticle( m_pRand->GetRand(1.0f),m_pRand->GetRand(1.0f),m_pRand->GetRand(1.0f),m_pRand->GetRand(1.0f),m_pRand->GetRand(1.0f),m_pRand->GetRand(1.0f));
		}
	}
}

//----------------------------------------------------
// 移動
//----------------------------------------------------
void CSpaceParticle::Move( void )
{
	for( int i = 0; i < 100; ++ i )
	{
		if( m_pSpaceParticle[i].GetLife() > 0 )
		{
			m_pSpaceParticle[i].Move();
			m_pSpaceParticle[i].LifeDown( m_pRand->GetRand( 1,5 ) );
			m_pSpaceParticle[i].SetDiffuse( m_pSpaceParticle[i].GetAlfa() - 2);
			if( m_pSpaceParticle[i].GetAlfa() <= 0 )
			{
				m_pSpaceParticle[i].SetLife( 0 );
				m_spaceCnt --;
			}
		}
	}

	if( m_spaceCnt <= 0 )
	{
		m_isSpaceParticle = false;
	}
}

//----------------------------------------------------
// 描画
//----------------------------------------------------
void CSpaceParticle::Draw( CDirectCamera* directCamera )
{
	for( int i = 0; i < 100; ++ i )
	{
		if( m_pSpaceParticle[i].GetLife() > 0 )
		{
			directCamera->SetBillBoardMtx( m_pSpaceParticle[i].GetMat(), m_pSpaceParticle[i].GetPos() );
			CDirectDrawSystem::GetInstance()->DrawParticle( CResourceManager::GetInstance()->GetTexture(m_pSpacePatricleFilePath)->Get(),m_pSpaceParticle[i].GetMat(),m_pSpaceParticle[i].GetVertex() );
		}
	}
}

