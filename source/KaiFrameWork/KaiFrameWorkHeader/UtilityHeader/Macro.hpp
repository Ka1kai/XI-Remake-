//----------------------------------------------------
// Macro 
//  DirectXの自作マクロ関数群
//
// @date	2013/9/15
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _MACRO_H_
#define _MACRO_H_

#include <d3dx9.h>
#include <stdio.h>
#include <string>
#include <stdarg.h>

//----------------------------------------------------
// ポインタの解放
//----------------------------------------------------
template<class T>
HRESULT SAFE_DELETE( T& t )
{
	if( t != nullptr )
	{
		delete t;
		t = nullptr;
		return S_OK;
	}

	return E_FAIL;
}

//----------------------------------------------------
// ポインタ配列の解放
//----------------------------------------------------
template<class T>
HRESULT SAFE_DELETE_ALLAY( T& t )
{
	if( t != nullptr )
	{
		delete[] t;
		t = nullptr;
		return S_OK;
	}

	return E_FAIL;
}

//----------------------------------------------------
// Releseを使ったポインタの解放
//----------------------------------------------------
template<class T>
HRESULT SAFE_DELETE_RELESE( T& t )
{
	if( t != nullptr )
	{
		t->Release();
		t = nullptr;
		return S_OK;
	}

	return E_FAIL;
}

//----------------------------------------------------
// freeを使用してのポインタの解放
//----------------------------------------------------
template<class T>
HRESULT SAFE_DELETE_FREE( T& t )
{
	if( t != nullptr )
	{
		free( t );
		t = nullptr;
		return S_OK;
	}

	return E_FAIL;
}

//----------------------------------------------------
// 行列の内部データをコピー 
//----------------------------------------------------
inline	D3DXMATRIX*	CopyMatrix(D3DXMATRIX* pOut,CONST D3DXMATRIX* pIn)
{
	memcpy( pOut,pIn,sizeof(D3DXMATRIX) );
	return pOut;
}

//----------------------------------------------------
// 回転行列のみのコピー
//----------------------------------------------------
inline	D3DXMATRIX*	CopyRotationMatrix(D3DXMATRIX* pOut,CONST D3DXMATRIX* pIn)
{
	memcpy(pOut,pIn,sizeof(float)*12);
	return pOut;
}

//----------------------------------------------------
// @name	COMBINE_STRING
// @content	文字列を結合してSTLのstringに格納し渡す
// @param	num			文字列数
// @param	str			文字列
// @param	...			文字列（可変引数なので何個でも）
// @return	std::string	結合した文字列
// @date	2013/11/13
//----------------------------------------------------
inline std::string COMBINE_STRING	( int num, const char* str, ... )
{
	const char* p;
	std::string comStr;
	va_list args;		// 可変引数を格納しているリスト
	
	va_start( args, str );
	p = str;
	
	for( int i = 0; i < num; ++ i  )
	{
		comStr.append( p );
		p = va_arg( args, const char*);
	}

	va_end( args );

	return comStr;
}


#endif _MACRO_H_