//----------------------------------------------------
// C2DBillBoard 
//	�r���{�[�h�̃N���X
//
// @date	2013/12/18
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_2D_BILLBOARD_H_
#define _C_2D_BILLBOARD_H_

#include <Windows.h>
#include <d3dx9.h>

#include "C2DSprite.h"

// ����F���\����
typedef struct TAGtCOLOR
{
	int		red;
	int		green;
	int		blue;
	int		alpha;
}tagTCOLOR;

class C2DBillBoard : public C2DSprite
{
private:
	tagTCOLOR			m_color;	// �F���

public:
	// �R���X�g���N�^
	C2DBillBoard		( void );

	// �f�X�g���N�^
	~C2DBillBoard		( void );

public:
	//----------------------------------------------------
	// @name	SetVertexColor
	// @content	�F�𒸓_�ɃZ�b�g
	// @param	none
	// @return	none
	// @date	2013/12/18
	//----------------------------------------------------	
	void	SetVertexColor	( void );

	//----------------------------------------------------
	// @name	SetColor
	// @content	�F���܂Ƃ߂ăZ�b�g
	// @param	r		�Ԓl( 0 ~ 255 )
	// @param	g		�Βl( 0 ~ 255 )
	// @param	b		�l( 0 ~ 255 )
	// @param	a		���l ( 0 ~ 255 )
	// @return	none
	// @date	2013/12/18
	//----------------------------------------------------
	void	SetColor	( CONST UINT r, CONST UINT g, CONST UINT b, CONST UINT a );

	//----------------------------------------------------
	// @name	SetColor
	// @content	�F�̌ʃZ�b�g(�@�e�F���Ƃɂ킩��Ă��� )
	// @param	color		�F( �e�F���� 0 ~ 255 )
	// @return	none
	// @date	2013/12/18
	//----------------------------------------------------
	void SetColorRed	( CONST UINT red )
	{
		m_color.red = red;
		this->SetVertexColor();
	}
	void SetColorGreen	( CONST UINT green )
	{
		m_color.green = green;
		this->SetVertexColor();
	}
	void SetColorBlue	( CONST UINT blue )
	{
		m_color.blue = blue;
		this->SetVertexColor();
	}
	void SetColorAlfa	( CONST UINT alpfa )
	{
		m_color.alpha;
		this->SetVertexColor();
	}
	
	//----------------------------------------------------
	// @name	CalcWorldMtx
	// @content	���[���h�s����r���{�[�h�p�̍s��ɃZ�b�g����
	// @param	cameraView		�J�����̃r���[�s��
	// @return	none
	// @date	2013/12/18
	//----------------------------------------------------
	void CalcWorldMtx	( CONST D3DXMATRIX* cameraView );

};

#endif _C_2D_BILLBOARD_H_