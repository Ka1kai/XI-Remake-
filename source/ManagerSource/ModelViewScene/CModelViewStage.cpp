
#include "CModelViewStage.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CModelViewStage::CModelViewStage( void )
{
	m_pStage = new CDebugStage( 84 );
}

//----------------------------------------------------
// �f�X�g���N�^
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
// ������
//----------------------------------------------------
void CModelViewStage::Init( void )
{
	m_pStage->Init( 50.0f );
}

//----------------------------------------------------
// �`��
//----------------------------------------------------
void CModelViewStage::Draw( void )
{
	CDirectDrawSystem::GetInstance()->DrawDebugStage( m_pStage->GetLineNum() / 2,m_pStage->GetVertex() );
}



