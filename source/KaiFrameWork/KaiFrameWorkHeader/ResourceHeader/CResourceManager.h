//----------------------------------------------------
// CResourceManager 
//	���\�[�X���Ǘ��E�ێ�����N���X
//
// @date	2013/12/5
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_RESOURCE_MANAGER_H_
#define _C_RESOURCE_MANAGER_H_

#include <d3dx9.h>
#include <map>
#include <string>

#include "CResourceXFile.h"
#include "CResourceTexture.h"
#include "CResourceXFont.h"

#include "CResourcePath.hpp"

using namespace std;

class CResourceManager
{
private:
	CResourceManager()
	{
	}
	CResourceManager( CONST CResourceManager& obj ){}
	CResourceManager& operator=( CONST CResourceManager& obj ){}

public:
	//�C���X�^���X�̎擾�i�V���O���g���j
	static CResourceManager* GetInstance()
	{
		static CResourceManager resourceManager;
		return &resourceManager;
	}

private:
	map< LPSTR , CResourceTexture* >	m_texturerResource;
	map< LPSTR , CResourceXFile* >		m_xFileResource;
	map< UINT  , CResourceXFont* >		m_xFontResource;

public:
	// �f�X�g���N�^
	~CResourceManager	( void );

public:
	//----------------------------------------------------
	// @name	LoadXFile
	// @content	XFile�����[�h����Map�ɃZ�b�g����
	// @param	resourcePath	���\�[�X�̃p�X
	// @return	bool			���������s
	// @date	2013/12/5
	//----------------------------------------------------
	bool		LoadXFile		( CONST LPSTR resourcePath );

	//----------------------------------------------------
	// @name	GetXFile
	// @content	Map����XFile�̎擾
	// @param	resourcePath		XFile�̃p�X	
	// @return	CResourceXFile*		XFile�̃A�h���X
	// @date	2013/12/5
	//----------------------------------------------------
	CResourceXFile*	GetXFile	( CONST LPSTR resourcePath );

	//----------------------------------------------------
	// @name	LoadTexture
	// @content	Texture�����[�h����Map�ɃZ�b�g����
	// @param	resourcePath	Texture�̃p�X
	// @return	bool			���������s	
	// @date	2013/12/5
	//----------------------------------------------------
	bool			LoadTexture		( CONST LPSTR resourcePath );

	//----------------------------------------------------
	// @name	GetTexture	
	// @content	Map����e�N�X�`���̎擾
	// @param	resourcePath		Texture�̃p�X
	// @return	CResourceTexture*	Texture�̃A�h���X	
	// @date	2013/12/5
	//----------------------------------------------------
	CResourceTexture*	GetTexture	( CONST LPSTR resourcePath );

	//----------------------------------------------------
	// @name	CreateFont
	// @content	XFont���쐬����Map�ɃZ�b�g����
	// @param	xFontNo			�ǂ�XFont�������ʂ���ԍ�
	// @param	width			����
	// @param	height			�c��
	// @return	bool			���������s
	// @date	2013/12/16
	//----------------------------------------------------
	bool		CreateXFont			( CONST UINT xFontNo, CONST UINT width, CONST UINT height );

	//----------------------------------------------------
	// @name	GetXFont
	// @content	XFont�̃C���X�^���X�̎擾
	// @param	xFontNo				Map�Ɋi�[���Ă���xFont�̔ԍ�
	// @return	CResourceXFont*		XFont�̃C���X�^���X
	// @date	2013/12/6
	// @update	2013/12/16			������No��ǉ�
	//----------------------------------------------------
	CResourceXFont*		GetXFont	( CONST UINT xFontNo );

	//----------------------------------------------------
	// @name	Relese
	// @content	Map�̏���S�ă����[�X
	// @param	none
	// @return	none	
	// @date	2013/12/5
	//----------------------------------------------------
	void	Relese				( void );

	//----------------------------------------------------
	// @name	Relese
	// @content	Map�̏����t�@�C���p�X�Ŏw����
	// @param	resourcePath		�t�@�C���̃p�X
	// @return	none	
	// @date	2013/12/5
	//----------------------------------------------------
	void	Relese				( CONST LPSTR resourcePath );

};

#endif _C_RESOURCE_MANAGER_H_