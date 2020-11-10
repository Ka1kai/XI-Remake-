
#include "CModelViewBackManager.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CModelViewBackManager::CModelViewBackManager( void )
{
	m_pModelViewBack = new C2DSpriteAlphaBlend();
}

//----------------------------------------------------
// デストラクタ
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
// 初期化
//----------------------------------------------------
void CModelViewBackManager::Init( void )
{
	m_isFade = false;

	m_pModelViewBack->SetVertexPos( 400.0f,320.0f,800.0f,640.0f );
	m_pModelViewBack->SetDiffuse( 255,255,255,0 );
}


//----------------------------------------------------
// 処理
//----------------------------------------------------
void CModelViewBackManager::Run( void )
{

}

//----------------------------------------------------
// 描画
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
