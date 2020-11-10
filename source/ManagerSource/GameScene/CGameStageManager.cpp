
#include "CGameStageManager.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CGameStageManager::CGameStageManager( void )
{
	m_pGround = new CObjectBase;
	m_pResGroundFilePath = GAME_STAGE_XFILEPATH;
	CResourceManager::GetInstance()->LoadXFile( m_pResGroundFilePath );

}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CGameStageManager::~CGameStageManager( void )
{
	SAFE_DELETE( m_pGround );
}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
void CGameStageManager::Init( void )
{
	m_pGround->Init();
}

//----------------------------------------------------
// 終了
//----------------------------------------------------
void CGameStageManager::Uninit( void )
{

}

//----------------------------------------------------
// 更新
//----------------------------------------------------
void CGameStageManager::Run( void )
{
}

//----------------------------------------------------
// 描画
//----------------------------------------------------
void CGameStageManager::Draw()
{
	CDirectDrawSystem::GetInstance()->SetCallMode( true );
	CDirectDrawSystem::GetInstance()->Draw3D( CResourceManager::GetInstance()->GetXFile( m_pResGroundFilePath ) ,m_pGround->GetWorldMtx() );
}

