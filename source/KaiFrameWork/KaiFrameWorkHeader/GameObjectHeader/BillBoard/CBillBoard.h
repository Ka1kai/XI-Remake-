//----------------------------------------------------
// CBillBoard 
//	�r���{�[�h�̃N���X
//
// @date	2013/6/15
// @update	2013/12/12
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_BILLBOARD_H_
#define _C_BILLBOARD_H_

#include <Windows.h>
#include <d3dx9.h>

// ���_�t�H�[�}�b�g(�r���{�[�h�p)
typedef struct TAGtBILLBORDVERTEX
{
	D3DXVECTOR3 pos;
	D3DCOLOR	color;
	float		tu,tv;
}tagTBILLBORDVERTEX;

class CBillBoard
{
private:
	D3DXMATRIX			m_mtx;			// �r���{�[�h�p�̍s��
	D3DXVECTOR3			m_pos;			// �r���{�[�h�̈ʒu���W
	D3DXVECTOR3			m_size;			// �r���{�[�h�̃T�C�Y
	D3DCOLOR			m_color;		// �J���[�l
	int					m_maxAlfa;		// �J�n���̃��l

	tagTBILLBORDVERTEX	m_vertex[4];	// �r���{�[�h�̒��_���W

public:
	// �����Ȃ��R���X�g���N�^
	CBillBoard()
	{
		m_pos.x = 0.0f;
		m_pos.y = 0.0f;
		m_pos.z = 0.0f;
		D3DXMatrixIdentity( &m_mtx );	
	}

	// ������ݒ肷��R���X�g���N�^
	CBillBoard( float x, float y, float z, float xSize, float ySize, D3DCOLOR color)
	{
		m_pos.x = x;
		m_pos.y = y;
		m_pos.z = z;
		m_size.x = xSize;
		m_size.y = ySize;
		m_color = color;
		D3DXMatrixIdentity( &m_mtx );	
		this->SetVertex();
		m_maxAlfa = 255;	
	}

	// �f�X�g���N�^
	~CBillBoard(){}

public:
	// �r���{�[�h�p�̍s��̎擾
	D3DXMATRIX* GetMat()
	{
		return &m_mtx;
	}

	// �r���{�[�h�p�̒��_���̎擾
	const tagTBILLBORDVERTEX* GetVertex()
	{
		return m_vertex;
	}

	// �r���{�[�h�p���W�̎擾
	const D3DXVECTOR3* GetPos()
	{
		return &m_pos;
	}

public:
	// ���l�̎擾
	const int GetAlfa			( void )
	{
		return ( m_color >> 24 );
	}

	// ���l�̃Z�b�g
	void SetAlfa		( int alfa );
	void SetDiffuse		( int alfa );
	
	// �ő僿�l�̃Z�b�g
	void SetMaxAlfa		( int maxAlfa );
	const int GetMaxAlfa( void )
	{
		return m_maxAlfa;
	}

	void SetVertex		( void );										// ���_���W�̃Z�b�g
	void SetVertex		( int windowX,int windowY );					// ���_���W�̃Z�b�g�i���㌴�_�j
	void SetPosition	( const float x,const float y,const float z );	// �ʒu���Z�b�g
	void SetBillboard	( float xSize,float ySize,D3DCOLOR color);		// �r���{�[�h�̃Z�b�g
	void SetBillboard	( float size,D3DCOLOR color );					// �r���{�[�h�̃Z�b�g(�T�C�Y����)

};

#endif _C_BILLBOARD_H_