
#include "../../../KaiFrameWorkHeader/GameObjectHeader/2D/C2DSpriteRHW.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
C2DSpriteRHW::C2DSpriteRHW( void )
{
	// ���_���W�E�F��������
	for( int i = 0; i < 4; ++ i ){
		m_vertex[i].pos.x = 0.0f;
		m_vertex[i].pos.y = 0.0f;
		m_vertex[i].pos.z = 0.0f;
		m_vertex[i].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		m_vertex[i].rhw = 1.0f;
	}

	m_center.x = 0.0f;
	m_center.y = 0.0f;

	m_size.x = 0.0f;
	m_size.y = 0.0f;

	m_halfSize.x = 0.0f;
	m_halfSize.y = 0.0f;

	// �e�N�X�`�����W������
	this->SetUV( 1,1,1,1 );
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
C2DSpriteRHW::~C2DSpriteRHW( void )
{
}

//----------------------------------------------------
// ������
//----------------------------------------------------
bool C2DSpriteRHW::Init( void )
{
	// ���_���W�E�F��������
	for( int i = 0; i < 4; ++ i ){
		m_vertex[i].pos.x = 0.0f;
		m_vertex[i].pos.y = 0.0f;
		m_vertex[i].pos.z = 0.0f;
		m_vertex[i].diffuse = D3DCOLOR_RGBA(255,255,255,255);
		m_vertex[i].rhw = 1.0f;
	}

	m_center.x = 0.0f;
	m_center.y = 0.0f;

	m_size.x = 0.0f;
	m_size.y = 0.0f;

	// �e�N�X�`�����W������
	this->SetUV( 1,1,1,1 );

	return true;
}

//----------------------------------------------------	
// �X�v���C�g���_���W�̃Z�b�g
//----------------------------------------------------
void C2DSpriteRHW::SetVertexPos( CONST float centerX, CONST float centerY, CONST float width, CONST float height )
{
	m_halfSize.x = width / 2;
	m_halfSize.y = height / 2;

	m_vertex[0].pos.x = centerX - m_halfSize.x;
	m_vertex[0].pos.y = centerY - m_halfSize.y;
	m_vertex[1].pos.x = centerX + m_halfSize.x;
	m_vertex[1].pos.y = centerY - m_halfSize.y;
	m_vertex[2].pos.x = centerX - m_halfSize.x;
	m_vertex[2].pos.y = centerY + m_halfSize.y;
	m_vertex[3].pos.x = centerX + m_halfSize.x;
	m_vertex[3].pos.y = centerY + m_halfSize.y;

	m_center.x = centerX;
	m_center.y = centerY;
	m_size.x = width;
	m_size.y = height;
}

//----------------------------------------------------
// �X�v���C�g���_���W�̃Z�b�g
//----------------------------------------------------
void C2DSpriteRHW::SetVertexPos( CONST float centerX, CONST float centerY )
{
	m_vertex[0].pos.x = centerX - m_halfSize.x;
	m_vertex[0].pos.y = centerY - m_halfSize.y;
	m_vertex[1].pos.x = centerX + m_halfSize.x;
	m_vertex[1].pos.y = centerY - m_halfSize.y;
	m_vertex[2].pos.x = centerX - m_halfSize.x;
	m_vertex[2].pos.y = centerY + m_halfSize.y;
	m_vertex[3].pos.x = centerX + m_halfSize.x;
	m_vertex[3].pos.y = centerY + m_halfSize.y;

};

//----------------------------------------------------
// �X�v���C�g���_���W�̃Z�b�g
//----------------------------------------------------
void C2DSpriteRHW::SetVertexPos( CONST D3DXVECTOR2* center )
{
	m_vertex[0].pos.x = center->x - m_halfSize.x;
	m_vertex[0].pos.y = center->y - m_halfSize.y;
	m_vertex[1].pos.x = center->x + m_halfSize.x;
	m_vertex[1].pos.y = center->y - m_halfSize.y;
	m_vertex[2].pos.x = center->x - m_halfSize.x;
	m_vertex[2].pos.y = center->y + m_halfSize.y;
	m_vertex[3].pos.x = center->x + m_halfSize.x;
	m_vertex[3].pos.y = center->y + m_halfSize.y;

}

//----------------------------------------------------
// �e�N�X�`�����W�Z�b�g(�摜��1�p�^�[��)
//----------------------------------------------------
void C2DSpriteRHW::SetUV( void )
{
	m_vertex[0].tu = 0.0f;
	m_vertex[0].tv = 0.0f;
	m_vertex[1].tu = 1.0f;
	m_vertex[1].tv = 0.0f;
	m_vertex[2].tu = 0.0f;
	m_vertex[2].tv = 1.0f;
	m_vertex[3].tu = 1.0f;
	m_vertex[3].tv = 1.0f;
}

//----------------------------------------------------
// �e�N�X�`�����W�Z�b�g(UV�p�^�[����ݒ�)
//----------------------------------------------------
void C2DSpriteRHW::SetUV( CONST UINT uPatern, CONST UINT vPatern, CONST UINT uNum, CONST UINT vNum )
{
	m_vertex[0].tu = 1.0f / uPatern * ( uNum - 1 );
	m_vertex[0].tv = 1.0f / vPatern * ( vNum - 1 );

	m_vertex[1].tu = 1.0f / uPatern * uNum;
	m_vertex[1].tv = 1.0f / vPatern * ( vNum - 1 );

	m_vertex[2].tu = 1.0f / uPatern * ( uNum - 1 );
	m_vertex[2].tv = 1.0f / vPatern *  vNum;

	m_vertex[3].tu = 1.0f / uPatern * uNum;
	m_vertex[3].tv = 1.0f / vPatern * vNum;
}

//----------------------------------------------------
// �f�B�t���[�Y�F�̃Z�b�g
//----------------------------------------------------
void C2DSpriteRHW::SetDiffuse( CONST UINT r, CONST UINT g, CONST UINT b, CONST UINT a )
{
	for( int i = 0; i < 4; ++ i ){
		m_vertex[i].diffuse = D3DCOLOR_RGBA( r, g, b, a );
	}
}

