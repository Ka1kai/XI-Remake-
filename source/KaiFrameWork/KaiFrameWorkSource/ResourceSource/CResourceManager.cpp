
#include "../../KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CResourceManager::~CResourceManager( void )
{
	this->Relese();
}

//----------------------------------------------------
// XFileをロードしてMapにセットする 
//----------------------------------------------------
bool CResourceManager::LoadXFile( CONST LPSTR resourcePath )
{
	// 既にロードされているかどうかチェック
	auto xFile = m_xFileResource.find( resourcePath );
	if( xFile != m_xFileResource.end() )
	{
		// 既にロードされているなら何もしない
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
// XFileをMapから取得
//----------------------------------------------------
CResourceXFile*	CResourceManager::GetXFile( CONST LPSTR resourcePath )
{
	return m_xFileResource[resourcePath];
}

//----------------------------------------------------
// TextureをロードしてMapにセットする
//----------------------------------------------------
bool CResourceManager::LoadTexture( CONST LPSTR resourcePath )
{
	// 既にロードされているかどうかチェック
	auto texture = m_texturerResource.find( resourcePath );
	if( texture != m_texturerResource.end() )
	{
		// 既にロードされているなら何もしない
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
// TextureをMapから取得
//----------------------------------------------------
CResourceTexture* CResourceManager::GetTexture( CONST LPSTR resourcePath )
{
	return m_texturerResource[resourcePath];
}

//----------------------------------------------------
// XFontを作成してMapにセットする
//----------------------------------------------------
bool CResourceManager::CreateXFont( CONST UINT xFontNo, CONST UINT width, CONST UINT height )
{
	// 既に作成されている番号かどうかチェック
	auto xFont = m_xFontResource.find( xFontNo );
	if( xFont != m_xFontResource.end() )
	{
		// 既に作成されているなら何もしない
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
// XFontの取得
//----------------------------------------------------
CResourceXFont*	CResourceManager::GetXFont( CONST UINT xFontNo )
{
	return m_xFontResource[ xFontNo ];
}

//----------------------------------------------------
// Mapから全件解放
//----------------------------------------------------
void CResourceManager::Relese( void )
{
	// XFileの解放
	auto xFile = m_xFileResource.begin();	
	while( xFile != m_xFileResource.end() )
	{
		SAFE_DELETE( ( *xFile ).second );
		xFile ++;
	}

	// Textureの解放
	auto texture = m_texturerResource.begin();
	while( texture != m_texturerResource.end() )
	{
		SAFE_DELETE( ( *texture ).second );
		texture ++;
	}

	// XFontの解放
	auto xFont = m_xFontResource.begin();
	while( xFont != m_xFontResource.end() )
	{
		SAFE_DELETE( ( *xFont ).second );
		xFont ++;
	}
}

//----------------------------------------------------
// Mapから指定解放
//----------------------------------------------------
void CResourceManager::Relese( CONST LPSTR resourcePath )
{

}
