
#include "../../KaiFrameWorkHeader/ResourceHeader/CResourceXFont.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CResourceXFont::CResourceXFont( void )
{
	m_pFont = nullptr;
	m_color = D3DXCOLOR( 255,255,255,255 );
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CResourceXFont::~CResourceXFont( void )
{
	SAFE_DELETE_RELESE( m_pFont );
}

//----------------------------------------------------
// XFontの作成
//----------------------------------------------------
HRESULT CResourceXFont::Create( CONST UINT width, CONST UINT height )
{
	LPDIRECT3DDEVICE9& pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	if( D3DXCreateFont(pd3dDevice,
					height,
					width,
					FW_MEDIUM,
					NULL,
					FALSE,
					SHIFTJIS_CHARSET,
					OUT_DEFAULT_PRECIS,
					PROOF_QUALITY,
					FIXED_PITCH | FF_MODERN,
					"MSPゴシック",
					&m_pFont) ) 
	{
		DEBUG::PrintfColor( DEBUG::H_RED, "Create Font Failed...\n" );
		return E_FAIL;
	}

	DEBUG::PrintfColor(DEBUG::H_PURPLE, "Create Font Successfully\n" );
	return S_OK;

}

//----------------------------------------------------
// 色の設定
//----------------------------------------------------
void CResourceXFont::SetColor( CONST D3DXCOLOR color )
{
	m_color = color;

}

//----------------------------------------------------
// 可変引数に変換
//----------------------------------------------------
inline char* CResourceXFont::OutPutStringArgList( char* buff, CONST LPSTR str, va_list argList )
{
	char buf[2048];
	_vsnprintf_s( buf, _countof(buf), str, argList );
	OutputDebugStringA( buf );

	::CopyMemory( buff, buf, sizeof( buf ) );

	return buff;
}

//----------------------------------------------------
// 色を変更しながらテキストの描画
//----------------------------------------------------
void CResourceXFont::DrawColor( CONST long xPos, CONST long yPos, CONST D3DXCOLOR color, CONST LPSTR str, ... )
{
	RECT	rect = { xPos, yPos, 0, 0 };
	char	buf[2048];
	::ZeroMemory( buf, sizeof( buf ) );
	va_list args;
	
	// カラーの変更
	m_color = color;

	va_start( args, str );
	this->OutPutStringArgList( buf, str, args );
		
	m_pFont->DrawTextA( NULL, buf, -1, &rect, DT_CALCRECT, NULL );
	m_pFont->DrawTextA( NULL, buf, -1, &rect, DT_LEFT | DT_BOTTOM, color );
		
	va_end( args );
}

//----------------------------------------------------
// テキストの描画
//----------------------------------------------------
void CResourceXFont::Draw( CONST long xPos, CONST long yPos, CONST LPSTR str, ... )
{
	RECT	rect = { xPos, yPos, 0, 0 };
	char	buf[1024];
	::ZeroMemory( buf,sizeof( buf ) );
	va_list args;

	va_start( args, str );
	this->OutPutStringArgList( buf, str, args );

	m_pFont->DrawTextA( NULL, buf, -1, &rect, DT_CALCRECT, NULL );
	m_pFont->DrawTextA( NULL, buf, -1, &rect, DT_LEFT | DT_BOTTOM, m_color );
		
	va_end( args );
}