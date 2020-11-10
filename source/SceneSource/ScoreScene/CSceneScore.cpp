
#include "CSceneScore.h"

// １～６のテクスチャ
const int pipDigitNum = 4;
const float pipPosX = 150.0f;
const float pipPosY = 270.0f;
const float pipDistanceX = 300.0f;
const float pipDistanceY = 70.0f;
const float pipSizeX = 50.0f;
const float pipSizeY = 50.0f;
const float pipDigitDistanceX = 100.0f;

// スコア
const int scoreDigitNum = 7;
const float scoreValueXPos = 180.0f;
const float scoreValueYPos = 180.0f;
const float scoreValueWidth = 160.0f;
const float scoreValueHeight = 70.0f;
const float scoreDigitXPos = scoreValueXPos + 180.0f;
const float scoreDigitYPos = scoreValueYPos + 5.0f;
const float scoreDigitWidth = 50.0f;
const float scoreDigitDistanceX = 35.0f;
const float scoreDigitHeight = 50.0f;

// MaxChain
const int maxChainDigitNum = 4;
const float maxChainValueXPos = 180.0f;
const float maxChainValueYPos = 500.0f;
const float maxChainValueWidth = 220.0f;
const float maxChainValueHeight = 70.0f;
const float maxChainDigitDistanceX = 200.0f;

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CSceneScore::CSceneScore( void )
{
}

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CSceneScore::CSceneScore( CSceneChange* sceneChange ) : CSceneBase( sceneChange )
{
}


//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CSceneScore::~CSceneScore( void )
{
	SAFE_DELETE( m_pHighScoreValue );
	SAFE_DELETE( m_pScoreValue );
	SAFE_DELETE_ALLAY( m_pScoreDigit );
	SAFE_DELETE( m_pMaxChainValue );
	SAFE_DELETE_ALLAY( m_pMaxChainDigit );

	SAFE_DELETE( m_pOnePip );
	SAFE_DELETE_ALLAY( m_pOnePipDigit );
	SAFE_DELETE( m_pTwoPip );
	SAFE_DELETE_ALLAY( m_pTwoPipDigit );
	SAFE_DELETE( m_pThreePip );
	SAFE_DELETE_ALLAY( m_pThreePipDigit );
	SAFE_DELETE( m_pFourPip );
	SAFE_DELETE_ALLAY( m_pFourPipDigit );
	SAFE_DELETE( m_pFivePip );
	SAFE_DELETE_ALLAY( m_pFivePipDigit );
	SAFE_DELETE( m_pSixPip );
	SAFE_DELETE_ALLAY( m_pSixPipDigit );

//	SAFE_DELETE( m_pBack );
}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
void CSceneScore::Initialize( void )
{
	int score = 0;
	int scoreDigit = 0;

	m_scoreDigitNum = 0;
	m_maxChainDigitNum = 0;
	m_oneDigitNum = 0;
	m_twoDigitNum = 0;
	m_threeDigitNum = 0;
	m_fourDigitNum = 0;
	m_fiveDigitNum = 0;
	m_sixDigitNum = 0;

	// Result文字
	m_pHighScoreValue->SetVertexPos( 400.0f,70.0f,250.0f,120.0f );

	// Score
	m_pScoreValue->SetVertexPos( scoreValueXPos, scoreValueYPos, scoreValueWidth, scoreValueHeight );
	score = CUserManager::GetInstance()->GetHighScore()->m_record;
	for( int i = scoreDigitNum - 1; i == scoreDigitNum - 1 || score != 0; -- i )
	{
		m_scoreDigitNum ++;
		m_pScoreDigit[i].SetVertexPos( scoreDigitXPos + i * scoreDigitDistanceX, scoreDigitYPos, scoreDigitWidth, scoreDigitHeight );
		scoreDigit = score % 10;
		score = score / 10;
		m_pScoreDigit[i].SetUV( 10, 1, scoreDigit + 1, 1 );
	}

	// MaxChain
	m_pMaxChainValue->SetVertexPos( maxChainValueXPos, maxChainValueYPos, maxChainValueWidth, maxChainValueHeight );
	score = CUserManager::GetInstance()->GetHighScore()->m_chainNum;
	for( int i = maxChainDigitNum - 1; i == maxChainDigitNum - 1 || score != 0; -- i )
	{
		m_maxChainDigitNum ++;
		m_pMaxChainDigit[i].SetVertexPos( m_pMaxChainValue->GetCenter()->x + maxChainDigitDistanceX + i * scoreDigitDistanceX, m_pMaxChainValue->GetCenter()->y, scoreDigitWidth, scoreDigitHeight );
		scoreDigit = score % 10;
		score = score / 10;
		m_pMaxChainDigit[i].SetUV( 10, 1, scoreDigit + 1, 1 );
	}

	// 1
	m_pOnePip->SetVertexPos( pipPosX, pipPosY, pipSizeX, pipSizeY );
	score = CUserManager::GetInstance()->GetHighScore()->m_oneChainNum;
	for( int i = pipDigitNum - 1; i == pipDigitNum - 1 || score != 0; -- i )
	{
		m_oneDigitNum ++;
		m_pOnePipDigit[i].SetVertexPos( m_pOnePip->GetCenter()->x + pipDigitDistanceX + i * scoreDigitDistanceX, m_pOnePip->GetCenter()->y , scoreDigitWidth, scoreDigitHeight );
		scoreDigit = score % 10;
		score = score / 10;
		m_pOnePipDigit[i].SetUV( 10, 1, scoreDigit + 1, 1 );
	}

	// 2
	m_pTwoPip->SetVertexPos( pipPosX, pipPosY + pipDistanceY, pipSizeX, pipSizeY );
	score = CUserManager::GetInstance()->GetHighScore()->m_twoChainNum;
	for( int i = pipDigitNum - 1; i == pipDigitNum - 1 || score != 0; -- i )
	{
		m_twoDigitNum ++;
		m_pTwoPipDigit[i].SetVertexPos( m_pTwoPip->GetCenter()->x + pipDigitDistanceX + i * scoreDigitDistanceX, m_pTwoPip->GetCenter()->y , scoreDigitWidth, scoreDigitHeight );
		scoreDigit = score % 10;
		score = score / 10;
		m_pTwoPipDigit[i].SetUV( 10, 1, scoreDigit + 1, 1 );
	}

	m_pThreePip->SetVertexPos( pipPosX, pipPosY + pipDistanceY * 2, pipSizeX, pipSizeY );
	score = CUserManager::GetInstance()->GetHighScore()->m_threeChainNum;
	for( int i = pipDigitNum - 1; i == pipDigitNum - 1 || score != 0; -- i )
	{
		m_threeDigitNum ++;
		m_pThreePipDigit[i].SetVertexPos( m_pThreePip->GetCenter()->x + pipDigitDistanceX + i * scoreDigitDistanceX, m_pThreePip->GetCenter()->y , scoreDigitWidth, scoreDigitHeight );
		scoreDigit = score % 10;
		score = score / 10;
		m_pThreePipDigit[i].SetUV( 10, 1, scoreDigit + 1, 1 );
	}

	m_pFourPip->SetVertexPos( pipPosX + pipDistanceX, pipPosY, pipSizeX, pipSizeY );
	score = CUserManager::GetInstance()->GetHighScore()->m_fourChainNum;
	for( int i = pipDigitNum - 1; i == pipDigitNum - 1 || score != 0; -- i )
	{
		m_fourDigitNum ++;
		m_pFourPipDigit[i].SetVertexPos( m_pFourPip->GetCenter()->x + pipDigitDistanceX + i * scoreDigitDistanceX, m_pFourPip->GetCenter()->y , scoreDigitWidth, scoreDigitHeight );
		scoreDigit = score % 10;
		score = score / 10;
		m_pFourPipDigit[i].SetUV( 10, 1 , scoreDigit + 1, 1 );
	}

	m_pFivePip->SetVertexPos( pipPosX + pipDistanceX, pipPosY + pipDistanceY, pipSizeX, pipSizeY );
	score = CUserManager::GetInstance()->GetHighScore()->m_fiveChainNum;
	for( int i = pipDigitNum - 1; i == pipDigitNum - 1 || score != 0; -- i )
	{
		m_fiveDigitNum ++;
		m_pFivePipDigit[i].SetVertexPos( m_pFivePip->GetCenter()->x + pipDigitDistanceX + i * scoreDigitDistanceX, m_pFivePip->GetCenter()->y , scoreDigitWidth, scoreDigitHeight );
		scoreDigit = score % 10;
		score = score / 10;
		m_pFivePipDigit[i].SetUV( 10, 1, scoreDigit + 1, 1 );
	}

	m_pSixPip->SetVertexPos( pipPosX + pipDistanceX, pipPosY + pipDistanceY * 2, pipSizeX, pipSizeY );
	score = CUserManager::GetInstance()->GetHighScore()->m_sixChainNum;
	for( int i = pipDigitNum - 1;i == pipDigitNum - 1 || score != 0; -- i )
	{
		m_sixDigitNum ++;
		m_pSixPipDigit[i].SetVertexPos( m_pSixPip->GetCenter()->x + pipDigitDistanceX + i * scoreDigitDistanceX, m_pSixPip->GetCenter()->y , scoreDigitWidth, scoreDigitHeight );
		scoreDigit = score % 10;
		score = score / 10;
		m_pSixPipDigit[i].SetUV( 10, 1, scoreDigit + 1, 1 );
	}

	/*
	m_pPushEnter->SetVertexPos( 600.0f,550.0f,256.0f,64.0f );

	m_pBack->SetVertexPos(400.0f,320.0f,800.0f,640.0f );
	m_pBack->SetDiffuse( 255,255,255,0 );

	m_isFade = false;
	*/
}

//----------------------------------------------------
// 終了
//----------------------------------------------------
void CSceneScore::Finalize( void )
{
}

//----------------------------------------------------
// 更新
//----------------------------------------------------
void CSceneScore::Run( void )
{
	CInputKeyboard::GetInstance()->Update();
	CJoyStick::GetInstance()->Update();

	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_SPACE ) ||
		CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_A ) )
	{
		mSceneChanger->ChangeScene( eSceneState::eSceneModeSelect );
	}
}

//----------------------------------------------------
// 描画
//----------------------------------------------------
void CSceneScore::Draw( void )
{
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResHighScoreValueFilePath )->Get(),m_pHighScoreValue->GetVertex() );
	
	// Score
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResScoreValueFilePath )->Get(), m_pScoreValue->GetVertex() );
	for( int i = scoreDigitNum - 1; i > scoreDigitNum - 1 - m_scoreDigitNum; -- i )
	{
		CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResScoreDigitFilePath )->Get(), m_pScoreDigit[i].GetVertex() );
	}

	// MaxChain
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResMaxChainValueFilePath )->Get(), m_pMaxChainValue->GetVertex() );
	for( int i = maxChainDigitNum - 1; i > maxChainDigitNum - 1 - m_maxChainDigitNum; -- i )
	{
		CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResScoreDigitFilePath )->Get(), m_pMaxChainDigit[i].GetVertex() );
	}

	// 1～6
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResOneTextureFilePath )->Get(), m_pOnePip->GetVertex() );
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResTwoTextureFilePath )->Get(), m_pTwoPip->GetVertex() );
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResThreeTextureFilePath )->Get(), m_pThreePip->GetVertex() );
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResFourTextureFilePath )->Get(), m_pFourPip->GetVertex() );
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResFiveTextureFilePath )->Get(), m_pFivePip->GetVertex() );
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResSixTextureFilePath )->Get(), m_pSixPip->GetVertex() );
	for( int i = pipDigitNum - 1; i > pipDigitNum - 1 - m_oneDigitNum; -- i )
	{
		CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResScoreDigitFilePath )->Get(), m_pOnePipDigit[i].GetVertex() );
	}

	for( int i = pipDigitNum - 1; i > pipDigitNum - 1 - m_twoDigitNum; -- i)
	{
		CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResScoreDigitFilePath )->Get(), m_pTwoPipDigit[i].GetVertex() );
	}

	for( int i = pipDigitNum - 1; i > pipDigitNum - 1 - m_threeDigitNum; -- i )
	{
		CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResScoreDigitFilePath )->Get(), m_pThreePipDigit[i].GetVertex() );
	}

	for( int i = pipDigitNum - 1; i > pipDigitNum - 1 - m_fourDigitNum; -- i )
	{
		CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResScoreDigitFilePath )->Get(), m_pFourPipDigit[i].GetVertex() );
	}

	for( int i = pipDigitNum - 1; i > pipDigitNum - 1 - m_fiveDigitNum; -- i )
	{
		CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResScoreDigitFilePath )->Get(), m_pFivePipDigit[i].GetVertex() );
	}

	for( int i = pipDigitNum - 1; i > pipDigitNum - 1 - m_sixDigitNum; -- i )
	{
		CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResScoreDigitFilePath )->Get(), m_pSixPipDigit[i].GetVertex() );
	}

//	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( NULL,m_pBack->GetVertex() );

}

//----------------------------------------------------
// ロード
//----------------------------------------------------
bool CSceneScore::Load( void )
{
	// Result文字
	m_pHighScoreValue = new C2DSpriteRHW;
	m_pResHighScoreValueFilePath = SCORE_HIGHSCORE_VALUE_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResHighScoreValueFilePath );

	// 数字
	m_pResScoreDigitFilePath = RESULT_SCOREDIGIT_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResScoreDigitFilePath );

	// Score
	m_pScoreValue = new C2DSpriteRHW;
	m_pResScoreValueFilePath = RESULT_SCOREVALUE_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResScoreValueFilePath );
	m_pScoreDigit = new C2DSpriteRHW[scoreDigitNum];

	// MaxChain
	m_pMaxChainValue = new C2DSpriteRHW;
	m_pResMaxChainValueFilePath = RESULT_MAXCHAIN_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResMaxChainValueFilePath );
	m_pMaxChainDigit = new C2DSpriteRHW[maxChainDigitNum];

	// １～６
	m_pOnePip = new C2DSpriteRHW;
	m_pOnePipDigit = new C2DSpriteRHW[pipDigitNum];
	m_pTwoPip = new C2DSpriteRHW;
	m_pTwoPipDigit = new C2DSpriteRHW[pipDigitNum];
	m_pThreePip = new C2DSpriteRHW;
	m_pThreePipDigit = new C2DSpriteRHW[pipDigitNum];
	m_pFourPip = new C2DSpriteRHW;
	m_pFourPipDigit = new C2DSpriteRHW[pipDigitNum];
	m_pFivePip = new C2DSpriteRHW;
	m_pFivePipDigit = new C2DSpriteRHW[pipDigitNum];
	m_pSixPip = new C2DSpriteRHW;
	m_pSixPipDigit = new C2DSpriteRHW[pipDigitNum];

	m_pResOneTextureFilePath = RESULT_ONE_PNGPATH;
	m_pResTwoTextureFilePath = RESULT_TWO_PNGPATH;
	m_pResThreeTextureFilePath = RESULT_THREE_PNGPATH;
	m_pResFourTextureFilePath = RESULT_FOUR_PNGPATH;
	m_pResFiveTextureFilePath = RESULT_FIVE_PNGPATH;
	m_pResSixTextureFilePath = RESULT_SIX_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResOneTextureFilePath );
	CResourceManager::GetInstance()->LoadTexture( m_pResTwoTextureFilePath );
	CResourceManager::GetInstance()->LoadTexture( m_pResThreeTextureFilePath );
	CResourceManager::GetInstance()->LoadTexture( m_pResFourTextureFilePath );
	CResourceManager::GetInstance()->LoadTexture( m_pResFiveTextureFilePath );
	CResourceManager::GetInstance()->LoadTexture( m_pResSixTextureFilePath );

	return true;
}