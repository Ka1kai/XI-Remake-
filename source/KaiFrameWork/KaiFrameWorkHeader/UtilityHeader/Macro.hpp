//----------------------------------------------------
// Macro 
//  DirectX�̎���}�N���֐��Q
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
// �|�C���^�̉��
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
// �|�C���^�z��̉��
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
// Relese���g�����|�C���^�̉��
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
// free���g�p���Ẵ|�C���^�̉��
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
// �s��̓����f�[�^���R�s�[ 
//----------------------------------------------------
inline	D3DXMATRIX*	CopyMatrix(D3DXMATRIX* pOut,CONST D3DXMATRIX* pIn)
{
	memcpy( pOut,pIn,sizeof(D3DXMATRIX) );
	return pOut;
}

//----------------------------------------------------
// ��]�s��݂̂̃R�s�[
//----------------------------------------------------
inline	D3DXMATRIX*	CopyRotationMatrix(D3DXMATRIX* pOut,CONST D3DXMATRIX* pIn)
{
	memcpy(pOut,pIn,sizeof(float)*12);
	return pOut;
}

//----------------------------------------------------
// @name	COMBINE_STRING
// @content	���������������STL��string�Ɋi�[���n��
// @param	num			������
// @param	str			������
// @param	...			������i�ψ����Ȃ̂ŉ��ł��j
// @return	std::string	��������������
// @date	2013/11/13
//----------------------------------------------------
inline std::string COMBINE_STRING	( int num, const char* str, ... )
{
	const char* p;
	std::string comStr;
	va_list args;		// �ψ������i�[���Ă��郊�X�g
	
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