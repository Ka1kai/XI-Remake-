
#include "../../../KaiFrameWorkHeader/GameObjectHeader/3D/C3DObjectShape.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
C3DObjectShape::C3DObjectShape( void )
{
	::ZeroMemory( &m_pMesh, sizeof( LPD3DXMESH ) );
	::ZeroMemory( &m_materials, sizeof( D3DMATERIAL9 ) );
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
C3DObjectShape::~C3DObjectShape( void )
{
}

//----------------------------------------------------
// �X�t�B�A�̐���
//----------------------------------------------------
bool C3DObjectShape::CreateSphere( CONST float radius )
{
	// �f�o�C�X�̃|�C���^���擾
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	// �X�t�B�A�̐���
	if( D3DXCreateSphere( pd3dDevice, radius, 20, 20, &m_pMesh, NULL ) )
	{
		// �쐬�ł��Ȃ������ꍇ
		return false;
	}

	// Diffuse�̐F�̃Z�b�g
	this->SetDiffuse( 255,255,255,255 );

	// Ambient�F�̃Z�b�g
	this->SetAmbient( 255,255,255,255 );

	return true;
}

//----------------------------------------------------
// �{�b�N�X�̐���
//----------------------------------------------------
bool C3DObjectShape::CreateBox( CONST D3DXVECTOR3* size )
{
		// �f�o�C�X�̃|�C���^���擾
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	// �X�t�B�A�̐���
	if( D3DXCreateBox( pd3dDevice, size->x, size->y ,size->z, &m_pMesh, NULL ) )
	{
		// �쐬�ł��Ȃ������ꍇ
		return false;
	}

	// Diffuse�̐F�̃Z�b�g
	this->SetDiffuse( 255,255,255,255 );

	// Ambient�F�̃Z�b�g
	this->SetAmbient( 255,255,255,255 );

	return true;
}

//----------------------------------------------------
// Diffuse�F�Z�b�g
//----------------------------------------------------
void C3DObjectShape::SetDiffuse( CONST UINT r, CONST UINT b, CONST UINT g, CONST UINT a )
{
	m_materials.Diffuse.r = ( float )( r / 255.0f );
	m_materials.Diffuse.g = ( float )( g / 255.0f );
	m_materials.Diffuse.b = ( float )( b / 255.0f );
	m_materials.Diffuse.a = ( float )( a / 255.0f );
}

//----------------------------------------------------
// Ambient�F�Z�b�g
//----------------------------------------------------
void C3DObjectShape::SetAmbient( CONST UINT r, CONST UINT g, CONST UINT b, CONST UINT a )
{
	m_materials.Ambient.r = ( float )( r / 255.0f );
	m_materials.Ambient.g = ( float )( g / 255.0f );
	m_materials.Ambient.b = ( float )( b / 255.0f );
	m_materials.Ambient.a = ( float )( a / 255.0f );
}

