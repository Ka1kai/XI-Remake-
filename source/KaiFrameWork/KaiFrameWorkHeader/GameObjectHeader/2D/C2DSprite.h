//----------------------------------------------------
// C2DSprite
//�@2D�̔|���S��(3D���W)
//
// @date	2013/12/12
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_2D_SPRITE_H_
#define _C_2D_SPRITE_H_

#include <d3dx9.h>
#include "../CObjectBase.hpp"

// ���_�t�H�[�}�b�g
typedef struct TAGtSPRITE
{
	D3DXVECTOR3	pos;
	D3DCOLOR	diffuse;
	float		tu,tv;
}tagTSPRITE;

class C2DSprite : public CObjectBase
{
private:
	D3DXVECTOR3	m_pos;			// �ʒu���W
	D3DXVECTOR3	m_size;			// �X�v���C�g�̑傫��

protected:
	tagTSPRITE	m_vertex[4];	// ���_���W

public:
	// �R���X�g���N�^
	C2DSprite			( void );

	// �f�X�g���N�^
	virtual ~C2DSprite	( void );

	//----------------------------------------------------
	// ���_���̎擾
	//----------------------------------------------------
	tagTSPRITE*	GetVertex	( void )
	{
		return m_vertex;
	}

	//----------------------------------------------------
	// �ʒu���̎擾
	//----------------------------------------------------
	CONST D3DXVECTOR3*	GetPos		( void )
	{
		return &m_pos;
	}

	//----------------------------------------------------
	// �X�v���C�g�̑傫���̎擾
	//----------------------------------------------------
	CONST D3DXVECTOR3*	GetSize		( void )
	{
		return &m_size;
	}

	//----------------------------------------------------
	// @name	SetSprite
	// @content	�X�v���C�g�̃Z�b�g
	// @param	pos		�ʒu���W
	// @param	size	�T�C�Y
	// @return	none
	// @date	2013/12/18
	//----------------------------------------------------
	bool	SetSprite		( CONST D3DXVECTOR3* pos, CONST D3DXVECTOR3* size );

	//----------------------------------------------------
	// @name	SetSpritePos
	// @content	�X�v���C�g�̈ʒu�̃Z�b�g(3������ԏ�)
	// @param	x		x���W�ʒu
	// @param	y		y���W�ʒu
	// @param	z		z���W�ʒu
	// @return	none
	// @date	2013/12/13
	//----------------------------------------------------
	void	SetSpritePos	( CONST float x, CONST float y, CONST float z );

	//----------------------------------------------------
	// @name	MoveSpritePos
	// @content	�X�v���C�g�̈ʒu�ړ�
	// @param	x		X�ړ���
	// @return	y		y�ړ���
	// @date	z		z�ړ���
	// @update	2013/12/18
	//----------------------------------------------------
	void	MoveSpritePos	( CONST float x, CONST float y, CONST float z );

	//----------------------------------------------------
	// @name	MoveSpritePos
	// @content	�X�v���C�g�̈ʒu�ړ�(vector�w��)
	// @param	vec		�ʒu�x�N�g��
	// @return	none
	// @date	2013/12/18
	//----------------------------------------------------
	void	MoveSpritePos	( CONST D3DXVECTOR3*	vec );

	//----------------------------------------------------
	// @name	SetSpritSize
	// @content	�X�v���C�g�̃T�C�Y���Z�b�g
	// @param	xSize	����
	// @param	ySize	�c��
	// @return	none
	// @date	2013/12/13
	//----------------------------------------------------
	void	SetSpriteSize	( CONST float xSize, CONST float ySize );

	//----------------------------------------------------
	// @name	SetVertexPos	
	// @content	���_�̈ʒu�̃Z�b�g�i�T�C�Y�Ɉˑ��j
	// @param	none
	// @return	none
	// @date	2013/12/13
	//----------------------------------------------------
	void	SetVertexPos	( void );

	//----------------------------------------------------
	// @name	SetUV	
	// @content	�e�N�X�`�����W�̃Z�b�g
	// @param	none
	// @return	none
	// @date	2013/12/12
	//----------------------------------------------------
	void	SetUV			( void );

	//----------------------------------------------------
	// @name	SetUV
	// @content	�e�N�X�`�����W�̃Z�b�g(�p�^�[������ݒ�)
	// @param	uPatern		���p�^�[����
	// @param	vPatern		�c�p�^�[����
	// @param	uNum		���̔ԍ�
	// @param	vNum		�c�̔ԍ�
	// @return	none
	// @date	2013/12/13
	//----------------------------------------------------
	void	SetUV			( CONST UINT uPatern, CONST UINT vPatern, CONST UINT uNum, CONST UINT vNum );

	//----------------------------------------------------
	// @name	SetDiffuse
	// @content	���_�F�̐ݒ�
	// @param	r		�Ԓl( 0 �` 255 )
	// @param	g		�Βl( 0 �` 255 )
	// @param	b		�l( 0 �` 255 )
	// @param	a		���l( 0 �` 255 )
	// @return	none	
	// @date	2014/1/128
	//----------------------------------------------------
	void	SetDiffuse		( CONST UINT r, CONST UINT g, CONST UINT b, CONST UINT a );

	//----------------------------------------------------
	// @name	CalcWorldMtx
	// @content	�|���S���̍s������[���h��ԏ�̍s��ɕϊ�
	// @param	none
	// @return	none
	// @date	2013/12/12
	//----------------------------------------------------
	void	CalcWorldMtx	( void );
};

#endif _C_2D_SPRITE_H_