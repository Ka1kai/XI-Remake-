
#include "CTimeManager.h"

const float ConstTimeValueXPos = 380.0f;
const float ConstTimeValueYpos = 20.0f;
const float ConstTimeValueXSize = 110.0f;
const float ConstTimeValueYSize = 22.0f;

const float ConstTimeDigitXPos = ConstTimeValueXPos - 40.0f;
const float ConstTimeDigitYpos = ConstTimeValueYpos + 30.0f;
const float ConstTimeDigitXSize = 38.0f;
const float ConstTimeDigitYSize = 38.0f;
const float ConstTimeDigitDistance = 24.0f;

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CTimeManager::CTimeManager( void )
{
	m_pResTimeFilePath = TIME_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResTimeFilePath );
	m_pTime = new C2DSpriteRHW;

	m_pResTimeDigitFilePath = TIMEDIGIT_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResTimeDigitFilePath );
	m_pTimeDigit = new C2DSpriteRHW[5];
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CTimeManager::~CTimeManager( void )
{
	SAFE_DELETE( m_pTime );
	SAFE_DELETE_ALLAY( m_pTimeDigit );
}


//----------------------------------------------------
// 描画
//----------------------------------------------------
void CTimeManager::Draw()
{
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResTimeFilePath )->Get(),m_pTime->GetVertex() );
	for( int i = 0; i < 5; ++ i )
	{
		CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResTimeDigitFilePath )->Get(),m_pTimeDigit[i].GetVertex() );
	}
}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
void CTimeManager::Init( CONST UINT time )
{
	m_pTime->SetVertexPos( ConstTimeValueXPos, ConstTimeValueYpos, ConstTimeValueXSize, ConstTimeValueYSize );

	// 00:00
	for( int i = 0; i < 5; ++ i )
	{
		m_pTimeDigit[i].SetVertexPos( ConstTimeDigitXPos + ( ConstTimeDigitDistance * i ), ConstTimeDigitYpos, ConstTimeDigitXSize, ConstTimeDigitYSize );

		m_pTimeDigit[i].SetUV( 11,1,1,1 );	
	}

	m_pTimeDigit[2].SetUV( 11, 1, 11, 1 );

	m_time = time * 60;
}


//----------------------------------------------------
// 処理
//----------------------------------------------------
void CTimeManager::Run( void )
{
	m_time --;

	int time = m_time / 60;

//	m_pTimeDigit[0].SetUV( 11, 1, ( ( time ) + 1 ), 1  );		// 10分
	m_pTimeDigit[1].SetUV( 11,1,( ( time / 60 ) + 1 ), 1 );		// 1分
	m_pTimeDigit[3].SetUV( 11,1,( time % 60 / 10 ) + 1 , 1 );	// 10秒
	m_pTimeDigit[4].SetUV( 11,1,( time % 60 % 10 ) + 1, 1 );	// 1秒
}

//----------------------------------------------------
// タイムアップ処理
//----------------------------------------------------
bool CTimeManager::TimeUP( void )
{
	if( m_time == 0 )
	{
		return true;
	}
	return false;
}


