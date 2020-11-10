
#include "CModelViewStage.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CModelViewStage::CModelViewStage( void )
{
	m_pStage = new CDebugStage( 84 );
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CModelViewStage::~CModelViewStage( void )
{
	if( m_pStage != NULL )
	{
		delete m_pStage;
		m_pStage = NULL;
	}
}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
void CModelViewStage::Init( void )
{
	m_pStage->Init( 50.0f );
}

//----------------------------------------------------
// 描画
//----------------------------------------------------
void CModelViewStage::Draw( void )
{
	CDirectDrawSystem::GetInstance()->DrawDebugStage( m_pStage->GetLineNum() / 2,m_pStage->GetVertex() );
}



