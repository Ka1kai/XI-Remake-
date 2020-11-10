
#include "CModelViewBackManager.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CModelViewBackManager::CModelViewBackManager( void )
{
	m_pModelViewBack = new C2DSpriteAlphaBlend();
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
CModelViewBackManager::~CModelViewBackManager( void )
{
	if( m_pModelViewBack != NULL )
	{
		delete m_pModelViewBack;
		m_pModelViewBack = NULL;
	}
}

//----------------------------------------------------
// ������
//----------------------------------------------------
void CModelViewBackManager::Init( void )
{
	m_isFade = false;

	m_pModelViewBack->SetVertexPos( 400.0f,320.0f,800.0f,640.0f );
	m_pModelViewBack->SetDiffuse( 255,255,255,0 );
}


//----------------------------------------------------
// ����
//----------------------------------------------------
void CModelViewBackManager::Run( void )
{

}

//----------------------------------------------------
// �`��
//----------------------------------------------------
void CModelViewBackManager::Draw( void )
{
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( m_pModelViewBack->GetVertex() );
}

//----------------------------------------------------
// Fade
//----------------------------------------------------
bool CModelViewBackManager::Fade( void )
{
	if( m_pModelViewBack->FadeOut( 5 ) )
	{
		return true;
	}

	return false;
}
