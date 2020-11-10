//----------------------------------------------------
// CRandSystem Header
//  乱数の生成用ヘッダー
//
// @date	2013/8/10
// @author  T.Kawashita
//----------------------------------------------------
#ifndef _C_RAND_SYSTEM_H_
#define _C_RAND_SYSTEM_H_

#include <stdlib.h>
#include <time.h>

class CRandSystem
{
public:
	CRandSystem	(void)
	{	
		this->ChangeSeed();	// シードの変更
	}
	~CRandSystem (void)
	{
	}

public:
	//----------------------------------------------------
	// @name	ChangeSeed
	// @content	シードの変更（タイムで変更）
	// @param	none
	// @return	none
	// @date	2013/8/10
	//----------------------------------------------------
	void ChangeSeed	( void )
	{
		srand( (unsigned)time( NULL ) );
	}

	//----------------------------------------------------
	// @name	GetRand
	// @content	ある範囲の乱数を取得
	// @param	start		範囲の最初
	// @param	end			範囲の最後
	// @return	const int	乱数
	// @date	2013/8/11
	//----------------------------------------------------	
	const int GetRand	( unsigned int start,unsigned int end )
	{
		return ( rand() % end - start + 1 ) + start;
	}

	//----------------------------------------------------
	// @name	GetRand
	// @content	最大値のみ指定した乱数を取得
	// @param	max			乱数で取得できる最大数
	// @return	const int	乱数
	// @date	2013/8/11
	//----------------------------------------------------
	const int GetRand	(  int max )
	{
		return ( rand() % max );
	}

	//----------------------------------------------------
	// @name	GetRand
	// @content	－の値を含めた乱数を取得
	// @param	max			範囲の最大値
	// @param	minus		範囲の最小値
	// @param	isMinus		－を含めるかどうか
	// @return	const int	乱数
	// @date	2013/8/11
	//----------------------------------------------------
	const int GetRand	( int max, int minus,bool isMinus )
	{
		return ( ( rand() % max ) - (rand() % minus) );
	}

	//----------------------------------------------------
	// @name	GetRand
	// @content	－の値を含めた乱数を取得（float型)
	// @param	max			範囲の最大値
	// @return	float		乱数
	// @date	2013/8/11
	//----------------------------------------------------
	const float GetRand ( float  max )
	{
		int value = (int)max * 10;
		value = value + 1;
		float value2 = (float)(rand() % value ) / 10.0f;
		float value3 = (float)(rand() % value ) / 10.0f;
		return value2 - value3;
	}

};

#endif _C_RAND_SYSTEM_H_