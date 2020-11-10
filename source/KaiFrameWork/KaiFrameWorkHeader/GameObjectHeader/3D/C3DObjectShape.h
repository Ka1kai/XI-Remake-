//----------------------------------------------------
// 3DObjectShape 
//	�o��`��̂��߂̃w�b�_�[
//	�X�t�B�A�C�{�b�N�X
//
// @date	2013/7/10
// @author  T.Kawashita
//----------------------------------------------------
#ifndef _C_3D_OBJECT_SHAPE_H_
#define _C_3D_OBJECT_SHAPE_H_

#include <d3dx9.h>

#include "../../DirectX9Header/CDirectX9FrameWork.h"
#include "../CObjectBase.hpp"

class C3DObjectShape : public CObjectBase
{
private:
	LPD3DXMESH		m_pMesh;			// ���b�V���f�[�^
	D3DMATERIAL9	m_materials;		// �}�e���A���f�[�^

public:
	C3DObjectShape				( void );
	virtual ~C3DObjectShape		( void );

	//----------------------------------------------------
	// @name	CreateSphere
	// @content	�X�t�B�A�̐���
	// @param	radius		���a
	// @return	bool		�쐬�ł������o���Ȃ�������
	// @date	2013/7/10
	//----------------------------------------------------
	bool	CreateSphere	( CONST float radius );

	//----------------------------------------------------
	// @name	CreateBox
	// @content	�{�b�N�X�̐���
	// @param	size		�傫��
	// @return	bool		�쐬�ł������o���Ȃ�������
	// @date	2013/7/10
	//----------------------------------------------------
	bool	CreateBox		( CONST D3DXVECTOR3* size );

	//----------------------------------------------------
	// @name	SetDiffuse
	// @content	�f�B�t���[�Y�F�̐ݒ�
	// @param	r			�Ԓl( 0 �` 255 )
	// @param	g			�Βl( 0 �` 255 )
	// @param	b			�l( 0 �` 255 )
	// @param	a			���l	( 0 �` 255 )
	// @return	none
	// @date	2013/7/10
	// @update	2013/12/17	�����̒l��UINT�^�ɂ� 1.0����255�Ή�
	//----------------------------------------------------
	void	SetDiffuse		( CONST UINT r, CONST UINT g, CONST UINT b, CONST UINT a );

	//----------------------------------------------------
	// @name	SetAmbient
	// @content	�A���r�G���g�F�̐ݒ�
	// @param	r			�Ԓl( 0 �` 255 )
	// @param	g			�Βl( 0 �` 255 )
	// @param	b			�l( 0 �` 255 )
	// @param	a			���l	( 0 �` 255 )
	// @return	none
	// @date	2013/710
	// @update	2013/12/17	�����̒l��UINT�^�ɂ� 1.0����255�Ή�
	//----------------------------------------------------
	void	SetAmbient		( CONST UINT r, CONST UINT g, CONST UINT b, CONST UINT a );

	//----------------------------------------------------
	// ���b�V���f�[�^�̎擾
	// @data	none
	// @return	LPD3DXMESH
	//----------------------------------------------------
	CONST LPD3DXMESH	GetMesh	( void )
	{
		return m_pMesh;
	}

	//----------------------------------------------------
	// �}�e���A���f�[�^�̎擾
	// @data	none
	// @return	D3DMATRIAL9*
	//----------------------------------------------------
	CONST D3DMATERIAL9*	GetMaterial	( void )
	{
		return &m_materials;
	}
};

#endif _C_3D_OBJECT_SHAPE_H_