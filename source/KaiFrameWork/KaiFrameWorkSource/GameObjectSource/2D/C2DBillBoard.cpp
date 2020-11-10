
#include "../../../KaiFrameWorkHeader/GameObjectHeader/2D/C2DBillBoard.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
C2DBillBoard::C2DBillBoard( void )
{
	m_color.red = 255;
	m_color.green = 255;
	m_color.blue = 255;
	m_color.alpha = 255;
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
C2DBillBoard::~C2DBillBoard( void )
{
}

//----------------------------------------------------
// �F�̃Z�b�g
//----------------------------------------------------
void C2DBillBoard::SetColor( CONST UINT r = 255, CONST UINT g = 255, CONST UINT b = 255, CONST UINT a = 255 )
{
	m_color.red = r;
	m_color.green = g;
	m_color.blue = b;
	m_color.alpha = a;

	// ���_�ɂ����f������
	this->SetVertexColor();
}

//----------------------------------------------------
// ���_�F�̃Z�b�g
//----------------------------------------------------
void C2DBillBoard::SetVertexColor( void )
{
	D3DCOLOR color = D3DCOLOR_RGBA( m_color.red, m_color.green, m_color.blue, m_color.alpha );
	m_vertex[0].diffuse = color;
	m_vertex[1].diffuse = color;
	m_vertex[2].diffuse = color;
	m_vertex[3].diffuse = color;
}

//----------------------------------------------------
// �|���S���̍s������[���h�s��(�r���{�[�h�p)�ɕϊ� 
//----------------------------------------------------
void C2DBillBoard::CalcWorldMtx( CONST D3DXMATRIX* cameraView )
{
	m_worldMtx._11 = cameraView->_11;
	m_worldMtx._12 = cameraView->_21;
	m_worldMtx._13 = cameraView->_31;
	m_worldMtx._21 = 0.0f;
	m_worldMtx._22 = 1.0f;
	m_worldMtx._23 = 0.0f;	
	m_worldMtx._31 = cameraView->_13;
	m_worldMtx._32 = cameraView->_23;
	m_worldMtx._33 = cameraView->_33;
	m_worldMtx._14 = 0.0f;
	m_worldMtx._24 = 0.0f;
	m_worldMtx._34 = 0.0f;
	m_worldMtx._44 = 1.0f;
}

