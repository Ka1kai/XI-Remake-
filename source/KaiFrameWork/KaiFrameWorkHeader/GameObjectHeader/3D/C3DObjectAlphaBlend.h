//----------------------------------------------------
// C3DObjectAlphaBlend 
//	���u�����h����K�v������Object
//
// @date	2013/12/4
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_3D_OBJECT_ALPHABLEND_H_
#define _C_3D_OBJECT_ALPHABLEND_H_

#include <d3dx9.h>
#include "../CObjectBase.hpp"

class C3DObjectAlphaBlend : public CObjectBase
{
private:
	D3DXCOLOR	m_color;		// �F���

public:

	// �R���X�g���N�^
	C3DObjectAlphaBlend				( void );
	
	// �f�X�g���N�^
	virtual	~C3DObjectAlphaBlend	( void );

	//----------------------------------------------------
	// ������
	//----------------------------------------------------
	bool		Init	( void );

	//----------------------------------------------------
	// @name	SetColor	
	// @content	�F�̐ݒ�
	// @param	r		�Ԓl( 0 ~ 255 )
	// @param	g		�Βl( 0 ~ 255 )
	// @param	b		�l( 0 ~ 255 )
	// @return	none
	// @date	2013/12/17
	//----------------------------------------------------
	void		SetColor		( CONST UINT r, CONST UINT g, CONST UINT b, CONST UINT a );
	
	//----------------------------------------------------
	// @name	GetColor
	// @content	�F�̎擾
	// @param	none
	// @return	D3DXCOLOR*		�F���
	// @date	2013/12/4
	//----------------------------------------------------
	D3DXCOLOR*	GetColor		( void );

};

#endif _C_3D_OBJECT_ALPHABLEND_H_