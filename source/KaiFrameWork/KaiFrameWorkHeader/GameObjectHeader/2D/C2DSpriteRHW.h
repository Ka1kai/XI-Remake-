//----------------------------------------------------
// C2DSpriteRHW
//	2D�|���S����`�悷�邽�߂̂���
//  �������W�v�Z�����Ă���
//
// @date	2013/8/10
// @author T.Kawashita
//----------------------------------------------------
#ifndef _C_2D_SPRITE_RHW_H_
#define _C_2D_SPRITE_RHW_H_

#include <d3dx9.h>

// Sprite(�������W����)���_�f�[�^�\����
typedef struct TAGtSPRITERHW
{
	D3DXVECTOR3	pos;		// ���_�̍��W
	float		rhw;		// �X�N���[�����W�ϊ�
	D3DCOLOR	diffuse;	// ���_�̐F
	float		tu, tv;		// �e�N�X�`�����W
}tagTSPRITERHW;

class C2DSpriteRHW
{
private:
	tagTSPRITERHW	m_vertex[4];	// ���_�f�[�^

protected:
	D3DXVECTOR2		m_center;		// ���S���W
	D3DXVECTOR2		m_halfSize;		// �����̃T�C�Y
	D3DXVECTOR2		m_size;			// �T�C�Y

public:
	C2DSpriteRHW			( void );				
	virtual	~C2DSpriteRHW	( void );	

	//----------------------------------------------------
	// ���_���W�̎擾 
	//----------------------------------------------------
	tagTSPRITERHW*	GetVertex	( void )
	{
		return m_vertex;
	}

	//----------------------------------------------------
	// ���S���W���Q�b�g
	//----------------------------------------------------
	D3DXVECTOR2*	GetCenter		( void )
	{
		return &m_center;
	}

	//----------------------------------------------------
	// ������
	//----------------------------------------------------
	bool			Init			( void );

public:
	//----------------------------------------------------
	// @name	SetVertexPos
	// @content	���_���W�̃Z�b�g(���S���W�ƃT�C�Y���w��j
	// @param	centerX		���SX���W
	// @param	centerY		���SY���W
	// @param	width		����
	// @param	height		�c��
	// @return	none
	// @date	2013/8/10
	//----------------------------------------------------
	void		SetVertexPos	( CONST float centerX, CONST float centerY, CONST float width, CONST float height );
	
	//----------------------------------------------------
	// @name	SetVertexPos
	// @content	���_���W�̃Z�b�g(���S���W���w��)
	// @param	centerX		���SX���W
	// @param	centerY		���SY���W
	// @return	none
	// @date	2013/8/10
	//----------------------------------------------------
	void		SetVertexPos	( CONST float centerX, CONST float centerY );

	//----------------------------------------------------
	// @name	SetVertexPos
	// @content	���_���W�̃Z�b�g(���S���W��D3DXVECTOR2�^�ŃZ�b�g)
	// @param	center		���S���W
	// @return	none
	// @date	2013/8/10
	//----------------------------------------------------
	void		SetVertexPos	( CONST D3DXVECTOR2* center );

	//----------------------------------------------------
	// @name	SetUV
	// @content	�e�N�X�`�����W�̃Z�b�g
	// @param	none
	// @return	none
	// @date	2013/12/13
	//----------------------------------------------------
	void		SetUV		( void );

	//----------------------------------------------------
	// @name	SetUV
	// @content	�e�N�X�`�����W�̃Z�b�g
	// @param	uPatern		���̃p�^�[����
	// @param	vPatern		�c�̃p�^�[����
	// @param	uNum		���̔ԍ�
	// @param	vNum		�c�̔ԍ�
	// @return	none
	// @date	2013/8/10
	//----------------------------------------------------
	void		SetUV		( CONST UINT uPatern, CONST UINT vPatern, CONST UINT uNum, CONST UINT vNum );
	
	//----------------------------------------------------
	// @name	SetDiffuse
	// @content	���_�̐F�Z�b�g
	// @param	r			�Ԓl( 0 �` 255 )
	// @param	g			�Βl( 0 �` 255 )
	// @param	b			�l( 0 �` 255 )
	// @param	a			���l ( 0 �` 255 )
	// @return	none	
	// @date	2013/8/11
	// @update	2013/12/13	������UINT�^�ɐݒ�
	//----------------------------------------------------	
	void		SetDiffuse		( CONST UINT r, CONST UINT g, CONST UINT b, CONST UINT a );

	//----------------------------------------------------
	// ���l�̎擾 
	//----------------------------------------------------
	int			GetAlpha	( void )
	{
		return ( m_vertex[0].diffuse >> 24 );
	}
	
};

#endif _C_2D_SPRITE_RHW_H_