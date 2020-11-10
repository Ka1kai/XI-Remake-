
#include "../../../KaiFrameWorkHeader/GameObjectHeader/3D/C3DObjectAlphaBlend.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
C3DObjectAlphaBlend::C3DObjectAlphaBlend( void )
{
	this->SetColor( 255,255,255,255 );
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
C3DObjectAlphaBlend::~C3DObjectAlphaBlend( void )
{
}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
bool C3DObjectAlphaBlend::Init( void )
{
	CObjectBase::Init();

	this->SetColor( 255,255,255,255 );

	return true;
}

//----------------------------------------------------
// 色の設定
//----------------------------------------------------
void C3DObjectAlphaBlend::SetColor( CONST UINT r, CONST UINT g, CONST UINT b, CONST UINT a )
{
	m_color.r = ( float )( r / 255.0f );
	m_color.g = ( float )( g / 255.0f );
	m_color.b = ( float )( b / 255.0f );
	m_color.a = ( float )( a / 255.0f );
}

//----------------------------------------------------
// 色の取得
//----------------------------------------------------
D3DXCOLOR* C3DObjectAlphaBlend::GetColor( void )
{
	return &m_color;
}