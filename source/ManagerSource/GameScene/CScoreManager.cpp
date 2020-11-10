
#include "CScoreManager.h"

const float ConstScoreValueXPos = 600.0f;
const float ConstScoreValueYPos = 20.0f;
const float ConstScoreValueXSize = 100.0f;
const float ConstScoreValueYSize = 22.0f;

const float ConstScoreDigitXPos = ConstScoreValueXPos - 65.0f;
const float ConstScoreDigitYPos = ConstScoreValueYPos + 30.0f;
const float ConstScoreDigitXSize = 38.0f;
const float ConstScoreDigitYSize = 38.0f;
const float COnstScoreDigitDistance = 24.0f;

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CScoreManager::CScoreManager( void )
{
	m_pScore = new CScore;

	m_pScoreValue = new C2DSpriteRHW;
	m_pResScoreValue = GAME_SCOREVALUE_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResScoreValue );

	m_pScoreDigit = new C2DSpriteRHW[SCORE_DIGIT_NUM];
	m_pResScoreDigit = GAME_SCOREDIGIT_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResScoreDigit );

}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CScoreManager::~CScoreManager( void )
{
	SAFE_DELETE( m_pScore );
	SAFE_DELETE( m_pScoreValue );
	SAFE_DELETE_ALLAY( m_pScoreDigit );
}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
bool CScoreManager::Init( void )
{
	m_pScore->Init();

	m_pScoreValue->SetVertexPos( ConstScoreValueXPos, ConstScoreValueYPos, ConstScoreValueXSize, ConstScoreValueYSize );
	
	// スコアの0000000
	for( int i = 0; i < SCORE_DIGIT_NUM; ++ i )
	{
		m_pScoreDigit[i].SetVertexPos( ConstScoreDigitXPos + ( COnstScoreDigitDistance * i ), ConstScoreDigitYPos, ConstScoreDigitXSize, ConstScoreDigitYSize );
		m_pScoreDigit[i].SetUV( 10, 1, 1, 1 );
	}
	
	return true;
}

//----------------------------------------------------
// 処理
//----------------------------------------------------
void CScoreManager::Run( void )
{
	int score = m_pScore->m_record;
	for( int i = SCORE_DIGIT_NUM - 1; i >= 0; -- i )
	{
		int scoreDigit = score % 10;
		score = score / 10;
		m_pScoreDigit[i].SetUV( 10, 1, scoreDigit + 1, 1 );
	}
}

//----------------------------------------------------
// 終了
//----------------------------------------------------
bool CScoreManager::Uninit( void )
{

	return true;
}

//----------------------------------------------------
// 描画
//----------------------------------------------------
void CScoreManager::Draw( void )
{
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResScoreValue )->Get(), m_pScoreValue->GetVertex() );

	for( int i = 0; i < SCORE_DIGIT_NUM; ++ i )
	{
		CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResScoreDigit )->Get(), m_pScoreDigit[i].GetVertex() );
	}
}
