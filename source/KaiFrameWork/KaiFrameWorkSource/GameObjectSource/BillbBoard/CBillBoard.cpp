
#include "../../../KaiFrameWorkHeader/GameObjectHeader/Billboard/CBillBoard.h"

//----------------------------------------------------
// ���S�����_�Ƃ������_���W���Z�b�g����֐��i�R�c��ԁj
//----------------------------------------------------
void CBillBoard::SetVertex()
{
	m_vertex[0].pos.x = -m_size.x / 2;
	m_vertex[0].pos.y = m_size.y / 2;
	m_vertex[0].pos.z = 0.0f;
	m_vertex[0].color = m_color;
	m_vertex[0].tu = 0.0f;
	m_vertex[0].tv = 0.0f;

	m_vertex[1].pos.x = m_size.x / 2;
	m_vertex[1].pos.y = m_size.y / 2;
	m_vertex[1].pos.z = 0.0f;
	m_vertex[1].color = m_color;
	m_vertex[1].tu = 1.0f;
	m_vertex[1].tv = 0.0f;

	m_vertex[2].pos.x = m_size.x / 2;
	m_vertex[2].pos.y = -m_size.y / 2;
	m_vertex[2].pos.z = 0.0f;
	m_vertex[2].color = m_color;
	m_vertex[2].tu = 1.0f;
	m_vertex[2].tv = 1.0f;

	m_vertex[3].pos.x = -m_size.x / 2;
	m_vertex[3].pos.y = -m_size.y / 2;
	m_vertex[3].pos.z = 0.0f;
	m_vertex[3].color = m_color;
	m_vertex[3].tu = 0.0f;
	m_vertex[3].tv = 1.0f;

}

//----------------------------------------------------
// ��������_���������_���W���Z�b�g����֐��i�Q�c��ԁj
//----------------------------------------------------
void CBillBoard::SetVertex( int windowX, int windowY )
{
	m_vertex[0].pos.x = -m_size.x / 2 - windowX / 2;
	m_vertex[0].pos.y = m_size.y / 2 + windowY / 2;
	m_vertex[0].pos.z = 0.0f;
	m_vertex[0].color = m_color;
	m_vertex[0].tu = 0.0f;
	m_vertex[0].tv = 0.0f;

	m_vertex[1].pos.x = m_size.x / 2 + windowX / 2;
	m_vertex[1].pos.y = m_size.y / 2 + windowY / 2;
	m_vertex[1].pos.z = 0.0f;
	m_vertex[1].color = m_color;
	m_vertex[1].tu = 1.0f;
	m_vertex[1].tv = 0.0f;

	m_vertex[2].pos.x = m_size.x / 2 + windowX / 2;
	m_vertex[2].pos.y = -m_size.y / 2 - windowY / 2;
	m_vertex[2].pos.z = 0.0f;
	m_vertex[2].color = m_color;
	m_vertex[2].tu = 1.0f;
	m_vertex[2].tv = 1.0f;

	m_vertex[3].pos.x = -m_size.x / 2 - windowX / 2;
	m_vertex[3].pos.y = -m_size.y / 2 - windowY / 2;
	m_vertex[3].pos.z = 0.0f;
	m_vertex[3].color = m_color;
	m_vertex[3].tu = 0.0f;
	m_vertex[3].tv = 1.0f;

}

//----------------------------------------------------
// �ʒu���Z�b�g
//----------------------------------------------------
void CBillBoard::SetPosition(float x,float y,float z)
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}

//----------------------------------------------------
// �r���{�[�h�̃Z�b�g
//----------------------------------------------------
void CBillBoard::SetBillboard( float xSize,float ySize,D3DCOLOR color )
{
	m_size.x = xSize;
	m_size.y = ySize;
	m_color = color;
	this->SetMaxAlfa( this->GetAlfa() );
	D3DXMatrixIdentity( &m_mtx );	
	this->SetVertex();
}

//----------------------------------------------------
// �r���{�[�h�̃Z�b�g
// �w�Ƃx���������傫��
//----------------------------------------------------
void CBillBoard::SetBillboard( float size,D3DCOLOR color )
{
	m_size.x = size;
	m_size.y = size;
	m_color = color;
	this->SetMaxAlfa( this->GetAlfa() );
	D3DXMatrixIdentity( &m_mtx );	
	this->SetVertex();
}

//----------------------------------------------------
// �X�V�������l�̃Z�b�g
//----------------------------------------------------
void CBillBoard::SetAlfa( int alfa )
{
	m_color = D3DCOLOR_ARGB( alfa,255,255,255 );
	m_vertex[0].color = m_color;
	m_vertex[1].color = m_color;
	m_vertex[2].color = m_color;
	m_vertex[3].color = m_color;
}

//----------------------------------------------------
// �X�V�������l�̃Z�b�g
//----------------------------------------------------
void CBillBoard::SetDiffuse( int alfa )
{
	int r,g,b;
	r = m_color >> 16;
	g = m_color >> 8;
	b = m_color >> 0;

	m_color = D3DCOLOR_ARGB( alfa,r,g,b );
	m_vertex[0].color = m_color;
	m_vertex[1].color = m_color;
	m_vertex[2].color = m_color;
	m_vertex[3].color = m_color;
}

//----------------------------------------------------
// �}�b�N�X���l�̃Z�b�g
//----------------------------------------------------
void CBillBoard::SetMaxAlfa( int maxAlfa )
{
	m_maxAlfa = maxAlfa;
}