
#include "../../KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
CResourceManager::~CResourceManager( void )
{
	this->Relese();
}

//----------------------------------------------------
// XFile�����[�h����Map�ɃZ�b�g���� 
//----------------------------------------------------
bool CResourceManager::LoadXFile( CONST LPSTR resourcePath )
{
	// ���Ƀ��[�h����Ă��邩�ǂ����`�F�b�N
	auto xFile = m_xFileResource.find( resourcePath );
	if( xFile != m_xFileResource.end() )
	{
		// ���Ƀ��[�h����Ă���Ȃ牽�����Ȃ�
		return false;
	}

	CResourceXFile*	workXFile = new CResourceXFile;
	if( !workXFile->Load( resourcePath ) )
	{
		m_xFileResource.insert( map< LPSTR, CResourceXFile* >::value_type( resourcePath, workXFile ) );
		return true;
	}

	return false;

}

//----------------------------------------------------
// XFile��Map����擾
//----------------------------------------------------
CResourceXFile*	CResourceManager::GetXFile( CONST LPSTR resourcePath )
{
	return m_xFileResource[resourcePath];
}

//----------------------------------------------------
// Texture�����[�h����Map�ɃZ�b�g����
//----------------------------------------------------
bool CResourceManager::LoadTexture( CONST LPSTR resourcePath )
{
	// ���Ƀ��[�h����Ă��邩�ǂ����`�F�b�N
	auto texture = m_texturerResource.find( resourcePath );
	if( texture != m_texturerResource.end() )
	{
		// ���Ƀ��[�h����Ă���Ȃ牽�����Ȃ�
		return false;
	}

	CResourceTexture* workTexture = new CResourceTexture;
	if( workTexture->Load( resourcePath ) )
	{
		m_texturerResource.insert( map< LPSTR, CResourceTexture* >::value_type( resourcePath, workTexture ) );
		return true;
	}
	return false;
}

//----------------------------------------------------
// Texture��Map����擾
//----------------------------------------------------
CResourceTexture* CResourceManager::GetTexture( CONST LPSTR resourcePath )
{
	return m_texturerResource[resourcePath];
}

//----------------------------------------------------
// XFont���쐬����Map�ɃZ�b�g����
//----------------------------------------------------
bool CResourceManager::CreateXFont( CONST UINT xFontNo, CONST UINT width, CONST UINT height )
{
	// ���ɍ쐬����Ă���ԍ����ǂ����`�F�b�N
	auto xFont = m_xFontResource.find( xFontNo );
	if( xFont != m_xFontResource.end() )
	{
		// ���ɍ쐬����Ă���Ȃ牽�����Ȃ�
		return false;
	}

	CResourceXFont* workXFont = new CResourceXFont;
	if( workXFont->Create( width, height ) == S_OK )
	{
		m_xFontResource.insert( map< UINT, CResourceXFont* >::value_type( xFontNo, workXFont ) );
		return true;
	}

	return false;

}

//----------------------------------------------------
// XFont�̎擾
//----------------------------------------------------
CResourceXFont*	CResourceManager::GetXFont( CONST UINT xFontNo )
{
	return m_xFontResource[ xFontNo ];
}

//----------------------------------------------------
// Map����S�����
//----------------------------------------------------
void CResourceManager::Relese( void )
{
	// XFile�̉��
	auto xFile = m_xFileResource.begin();	
	while( xFile != m_xFileResource.end() )
	{
		SAFE_DELETE( ( *xFile ).second );
		xFile ++;
	}

	// Texture�̉��
	auto texture = m_texturerResource.begin();
	while( texture != m_texturerResource.end() )
	{
		SAFE_DELETE( ( *texture ).second );
		texture ++;
	}

	// XFont�̉��
	auto xFont = m_xFontResource.begin();
	while( xFont != m_xFontResource.end() )
	{
		SAFE_DELETE( ( *xFont ).second );
		xFont ++;
	}
}

//----------------------------------------------------
// Map����w����
//----------------------------------------------------
void CResourceManager::Relese( CONST LPSTR resourcePath )
{

}
