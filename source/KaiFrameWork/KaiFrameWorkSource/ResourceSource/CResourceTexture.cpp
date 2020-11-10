
#include "../../KaiFrameWorkHeader/ResourceHeader/CResourceTexture.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CResourceTexture::CResourceTexture( void )
{
	m_pTexture = nullptr;
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CResourceTexture::~CResourceTexture( void )
{
	SAFE_DELETE_RELESE( m_pTexture );
}

//----------------------------------------------------
// テクスチャのロード
//----------------------------------------------------
bool CResourceTexture::Load( CONST LPSTR filePath )
{
//デバイスハンドルをシングルトンで取得
	CONST LPDIRECT3DDEVICE9& pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
	
	DEBUG::PrintfColor(DEBUG::H_CYAN,"%s\n", filePath );

	// テクスチャロード
	if( FAILED( D3DXCreateTextureFromFile( pd3dDevice, filePath, &m_pTexture )))
	{	// ロード失敗	
		DEBUG::PrintfColor(DEBUG::H_RED," Load Texture Failed...\n" );
		return false;
	}

	DEBUG::PrintfColor( DEBUG::H_GREEN,"Load Texture Successfully \n" );
	return true;

}