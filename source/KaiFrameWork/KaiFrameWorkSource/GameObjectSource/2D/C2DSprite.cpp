
#include "../../../KaiFrameWorkHeader/GameObjectHeader/2D/C2DSprite.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
C2DSprite::C2DSprite( void )
{
	m_pos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_size = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );

	// ���_���W�E�F��������
	for( int i = 0; i < 4; ++ i ){
		m_vertex[i].pos.x = 0.0f;
		m_vertex[i].pos.y = 0.0f;
		m_vertex[i].pos.z = 0.0f;
		m_vertex[i].diffuse = D3DCOLOR_RGBA( 255, 255, 255, 255);
	}

	// ���_�̃e�N�X�`���Z�b�g
	this->SetUV();
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
C2DSprite::~C2DSprite( void )
{
}

//----------------------------------------------------
// �X�v���C�g�̃Z�b�g
//----------------------------------------------------
bool C2DSprite::SetSprite( CONST D3DXVECTOR3* pos, CONST D3DXVECTOR3* size )
{
	// �X�v���C�g�̈ʒu�̃Z�b�g
	this->SetSpritePos( pos->x, pos->y, pos->z );

	// �T�C�Y�̃Z�b�g
	m_size.x = size->x;
	m_size.y = size->y;
	m_size.z = size->z;	// �����蔻��Ƃ��Ɏg�p����

	for( int i = 0; i < 4; ++ i )
	{
		m_vertex[i].diffuse = D3DCOLOR_RGBA( 255,255,255,255 );
	}

	// ���_���W���Z�b�g
	this->SetVertexPos();

	// �e�N�X�`�����W���Z�b�g
	this->SetUV();

	return true;
}

//----------------------------------------------------
// �X�v���C�g�ʒu�̃Z�b�g
//----------------------------------------------------
void C2DSprite::SetSpritePos( CONST float x, CONST float y, CONST float z )
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;

	// �s��ɂ��ݒ肵�Ă���
	this->SetWorldPos( &m_pos );
}

//----------------------------------------------------
// �X�v���C�g�ʒu�̈ړ�
//----------------------------------------------------
void C2DSprite::MoveSpritePos( CONST float x, CONST float y, CONST float z )
{
	m_pos.x = m_pos.x + x;
	m_pos.y = m_pos.y + y;
	m_pos.z = m_pos.z + z;

	this->SetWorldPos( &m_pos );
}

//----------------------------------------------------
// �X�v���C�g�ʒu�̈ړ�( vector�w�� )
//----------------------------------------------------
void C2DSprite::MoveSpritePos( CONST D3DXVECTOR3* vec )
{
	m_pos.x = vec->x;
	m_pos.y = vec->y;
	m_pos.z = vec->z;

	this->SetWorldPos( &m_pos );
}

//----------------------------------------------------
// �X�v���C�g�̑傫�����Z�b�g
//----------------------------------------------------
void C2DSprite::SetSpriteSize( CONST float xSize, CONST float ySize )
{
	m_size.x = xSize;
	m_size.y = ySize;

	SetVertexPos();
}

//----------------------------------------------------
// ���_�̍��W�Z�b�g
//----------------------------------------------------
void C2DSprite::SetVertexPos( void )
{
	m_vertex[0].pos.x = -m_size.x / 2;
	m_vertex[0].pos.y = m_size.y / 2;
	m_vertex[0].pos.z = 0.0f;

	m_vertex[1].pos.x = m_size.x / 2;
	m_vertex[1].pos.y = m_size.y / 2;
	m_vertex[1].pos.z = 0.0f;

	m_vertex[2].pos.x = m_size.x / 2;
	m_vertex[2].pos.y = -m_size.y / 2;
	m_vertex[2].pos.z = 0.0f;

	m_vertex[3].pos.x = -m_size.x / 2;
	m_vertex[3].pos.y = -m_size.y / 2;
	m_vertex[3].pos.z = 0.0f;
}

//----------------------------------------------------
// �e�N�X�`�����W�Z�b�g
//----------------------------------------------------
void C2DSprite::SetUV( void )
{
	m_vertex[0].tu = 0.0f;
	m_vertex[0].tv = 0.0f;
	m_vertex[1].tu = 1.0f;
	m_vertex[1].tv = 0.0f;
	m_vertex[2].tu = 1.0f;
	m_vertex[2].tv = 1.0f;
	m_vertex[3].tu = 0.0f;
	m_vertex[3].tv = 1.0f;
}

//----------------------------------------------------
// �e�N�X�`�����W�Z�b�g(UV�p�^�[����ݒ�)
//----------------------------------------------------
void C2DSprite::SetUV( CONST UINT uPatern, CONST UINT vPatern, CONST UINT uNum, CONST UINT vNum )
{
	m_vertex[0].tu = 1.0f / uPatern * ( uNum - 1 );
	m_vertex[0].tv = 1.0f / vPatern * ( vNum - 1 );

	m_vertex[1].tu = 1.0f / uPatern * uNum;
	m_vertex[1].tv = 1.0f / vPatern * ( vNum - 1 );

	m_vertex[2].tu = 1.0f / uPatern * uNum;
	m_vertex[2].tv = 1.0f / vPatern * vNum;

	m_vertex[3].tu = 1.0f / uPatern * ( uNum - 1 );
	m_vertex[3].tv = 1.0f / vPatern *  vNum;

}

//----------------------------------------------------
// ���_�F�̃Z�b�g
//----------------------------------------------------
void C2DSprite::SetDiffuse( CONST UINT r, CONST UINT g, CONST UINT b, CONST UINT a )
{
	for( int i = 0; i < 4; ++ i )
	{
		m_vertex[i].diffuse = D3DCOLOR_RGBA( r, g, b, a );
	}
}

//----------------------------------------------------
// �|���S���̍s������[���h�s��ɕϊ� 
//----------------------------------------------------
void C2DSprite::CalcWorldMtx( void )
{
	m_worldMtx._11 = 1.0f;
	m_worldMtx._12 = 0.0f;
	m_worldMtx._13 = 0.0f;
	m_worldMtx._21 = 0.0f;
	m_worldMtx._22 = 1.0f;
	m_worldMtx._23 = 0.0f;	
	m_worldMtx._31 = 0.0f;
	m_worldMtx._32 = 0.0f;
	m_worldMtx._33 = 1.0f;
	m_worldMtx._14 = 0.0f;
	m_worldMtx._24 = 0.0f;
	m_worldMtx._34 = 0.0f;
	m_worldMtx._44 = 1.0f;
}