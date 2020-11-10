//----------------------------------------------------
// CXFont 
//	DirectX���g�p���������쐬
//
// @date	2013/6/20
// @update	2013/12/6
// @author	T.kawashita
//----------------------------------------------------
#ifndef _C_RESOURCE_XFONT_H_
#define _C_RESOURCE_XFONT_H_

#include <d3dx9.h>

#include "../DirectX9Header/CDirectX9FrameWork.h"
#include "../UtilityHeader/Macro.hpp"

class	CResourceXFont
{
private:
	LPD3DXFONT	m_pFont;
	D3DXCOLOR	m_color;

public:
	// �R���X�g���N�^
	CResourceXFont	(void);

	// �f�X�g���N�^
	virtual ~CResourceXFont	(void);

	//----------------------------------------------------
	// @name	Create
	// @content	�t�H���g�̍쐬
	// @param	width		1�����̉���
	// @param	height		1�����̍���
	// @return	�쐬�ł������ǂ���
	// @date	2013/6/20
	//----------------------------------------------------
	HRESULT Create( CONST UINT width, CONST UINT height );

	//----------------------------------------------------
	// @name	SetColor
	// @content	�t�H���g�̐F�̐ݒ�
	// @param	color		�t�H���g�̐F
	// @return	none
	// @date	2013/12/6
	//----------------------------------------------------
	void	SetColor	( CONST D3DXCOLOR color );

	//----------------------------------------------------
	// @name	OutPutStringArgList
	// @content	�ψ����ɕϊ�
	// @param	str			������
	// @param	argList		�ψ����z��
	// @return	char*		�ϊ�����������
	// @date	2013/12/6
	//----------------------------------------------------
	inline char* OutPutStringArgList	( char* buff ,CONST LPSTR str, va_list argList );

	//----------------------------------------------------
	// @name	DrawColor
	// @content	�J���[��ύX���Ȃ���̃e�L�X�g�̕`��
	// @param	xPos			X���W
	// @param	yPos			Y���W
	// @param	color			�F���
	// @param	str				�`�悵����������
	// @return	none
	// @date	2013/6/20
	// @update	2013/12/6		�ψ����ɕύX
	//----------------------------------------------------
	void	DrawColor	( CONST long xPos, CONST long yPos, CONST D3DXCOLOR color, CONST LPSTR str,... );

	//----------------------------------------------------
	// @name	Draw
	// @content	�e�L�X�g�̕`��
	// @param	xPos			X���W
	// @param	yPos			Y���W
	// @param	str				�`�悵����������
	// @return	none
	// @date	2013/12/6		
	//----------------------------------------------------
	void	Draw	( CONST long xPos, CONST long yPos, CONST LPSTR str,... );
};

#endif _C_RESOURCE_XFONT_H_