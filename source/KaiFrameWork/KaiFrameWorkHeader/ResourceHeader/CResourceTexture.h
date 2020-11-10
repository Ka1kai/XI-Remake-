//----------------------------------------------------
// CResourceTexture	 
//	2D�e�N�X�`���[
//
// @date	2013/12/5
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_RESOURCE_TEXTURE_H_
#define _C_RESOURCE_TEXTURE_H_

#include <d3dx9.h>

#include "../DirectX9Header/CDirectX9FrameWork.h"
#include "../UtilityHeader/Macro.hpp"
#include "../DebugHeader/CDebugConsole.hpp"

class CResourceTexture
{
private:
	LPDIRECT3DTEXTURE9	m_pTexture;

public:
	// �R���X�g���N�^
	CResourceTexture			( void );

	// �f�X�g���N�^
	virtual ~CResourceTexture	( void );

public:
	//----------------------------------------------------
	// @name	Load
	// @content	�e�N�X�`���[�̃��[�h
	// @param	filePath	�t�@�C���p�X
	// @return	bool		���������s
	// @date	2013/12/5
	//----------------------------------------------------
	bool	Load		( CONST LPSTR filePath );

	//----------------------------------------------------
	// �e�N�X�`���f�[�^�擾 
	//----------------------------------------------------
	CONST LPDIRECT3DTEXTURE9	Get	(void)
	{
		return m_pTexture;
	}
};


#endif _C_RESOURCE_TEXTURE_H_