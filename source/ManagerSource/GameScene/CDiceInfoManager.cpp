
#include "CDiceInfoManager.h"

const float ConstInfoXPos = 200.0f;
const float ConstInfoYPos = 70.0f;
const float ConstInfoXSize = 110.0f;
const float ConstInfoYSize = 110.0f;

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CDiceInfoManager::CDiceInfoManager( void )
{
	m_pInfo = new C2DSpriteRHW;
	m_pResInfoFilePath = GAME_DICEINFO_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResInfoFilePath );

	m_pDiceInfo = new CDiceInfoObj;
	m_pResInfoDiceFilePath = DICE_XFILEPATH;
	CResourceManager::GetInstance()->LoadXFile( m_pResInfoDiceFilePath );
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CDiceInfoManager::~CDiceInfoManager( void )
{
	SAFE_DELETE( m_pDiceInfo );
	SAFE_DELETE( m_pInfo );
}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
bool CDiceInfoManager::Init( void )
{
	m_pInfo->SetVertexPos( ConstInfoXPos, ConstInfoYPos, ConstInfoXSize, ConstInfoYSize );

	m_pDiceInfo->Init();
	m_pDiceInfo->MoveWorldPos( -21.0f, 10.0f, 5.0f );

	return true;
}

//----------------------------------------------------
// 終了
//----------------------------------------------------
bool CDiceInfoManager::Uninit( void )
{

	return true;
}

//----------------------------------------------------
// 描画 
//----------------------------------------------------
void CDiceInfoManager::Draw( void )
{
	// Infoの画像
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture(  m_pResInfoFilePath )->Get(), m_pInfo->GetVertex() );

	// Info用のダイス
	if( m_pDiceInfo->GetIsExist() == true )
	{
		CDirectDrawSystem::GetInstance()->Draw3D( CResourceManager::GetInstance()->GetXFile( m_pResInfoDiceFilePath ), m_pDiceInfo->GetWorldMtx() );
	}
}

//----------------------------------------------------
// ダイスインフォのダイスのセット
//----------------------------------------------------
void CDiceInfoManager::SetInfoDice( CONST D3DXMATRIX* mainDiceWorldMtx )
{
	m_pDiceInfo->CopyRotationMtx( mainDiceWorldMtx );
}
