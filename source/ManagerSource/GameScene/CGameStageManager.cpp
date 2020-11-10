
#include "CGameStageManager.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CGameStageManager::CGameStageManager( void )
{
	m_pGround = new CObjectBase;
	m_pResGroundFilePath = GAME_STAGE_XFILEPATH;
	CResourceManager::GetInstance()->LoadXFile( m_pResGroundFilePath );

}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
CGameStageManager::~CGameStageManager( void )
{
	SAFE_DELETE( m_pGround );
}

//----------------------------------------------------
// ������
//----------------------------------------------------
void CGameStageManager::Init( void )
{
	m_pGround->Init();
}

//----------------------------------------------------
// �I��
//----------------------------------------------------
void CGameStageManager::Uninit( void )
{

}

//----------------------------------------------------
// �X�V
//----------------------------------------------------
void CGameStageManager::Run( void )
{
}

//----------------------------------------------------
// �`��
//----------------------------------------------------
void CGameStageManager::Draw()
{
	CDirectDrawSystem::GetInstance()->SetCallMode( true );
	CDirectDrawSystem::GetInstance()->Draw3D( CResourceManager::GetInstance()->GetXFile( m_pResGroundFilePath ) ,m_pGround->GetWorldMtx() );
}

