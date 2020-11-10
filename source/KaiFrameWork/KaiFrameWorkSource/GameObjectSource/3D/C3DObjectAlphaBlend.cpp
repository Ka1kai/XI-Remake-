
#include "../../../KaiFrameWorkHeader/GameObjectHeader/3D/C3DObjectAlphaBlend.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
C3DObjectAlphaBlend::C3DObjectAlphaBlend( void )
{
	this->SetColor( 255,255,255,255 );
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
C3DObjectAlphaBlend::~C3DObjectAlphaBlend( void )
{
}

//----------------------------------------------------
// ������
//----------------------------------------------------
bool C3DObjectAlphaBlend::Init( void )
{
	CObjectBase::Init();

	this->SetColor( 255,255,255,255 );

	return true;
}

//----------------------------------------------------
// �F�̐ݒ�
//----------------------------------------------------
void C3DObjectAlphaBlend::SetColor( CONST UINT r, CONST UINT g, CONST UINT b, CONST UINT a )
{
	m_color.r = ( float )( r / 255.0f );
	m_color.g = ( float )( g / 255.0f );
	m_color.b = ( float )( b / 255.0f );
	m_color.a = ( float )( a / 255.0f );
}

//----------------------------------------------------
// �F�̎擾
//----------------------------------------------------
D3DXCOLOR* C3DObjectAlphaBlend::GetColor( void )
{
	return &m_color;
}