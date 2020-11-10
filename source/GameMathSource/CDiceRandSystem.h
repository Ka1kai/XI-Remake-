//----------------------------------------------------
// CDiceRandSystem
//	サイコロの乱数のシステム
//
// @date	2013/11/28
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_DICE_RANDSYSTEM_H_
#define _C_DICE_RANDSYSTEM_H_

#include <Windows.h>
#include <time.h>
#include "../KaiFrameWork/KaiFrameWorkHeader/GameMathHeader/CXorShift.hpp"

#define RNDALLAY_NUM	( 100 )

//----------------------------------------------------
// 乱数用の配列
//----------------------------------------------------
// 上面の乱数
const UINT upperFaceRndAllay[ RNDALLAY_NUM ] =
{1,2,1,5,2,5,1,5,5,4,4,2,1,6,4,1,3,5,2,4,2,4,3,5,6,1,1,3,1,1,4,2,4,6,4,4,2,5,5,3,4,
 6,3,5,3,5,4,5,2,3,5,6,2,6,2,5,6,2,6,1,4,3,5,1,3,3,2,2,6,5,6,6,6,5,3,5,5,1,6,6,4,5,
 4,4,1,5,4,3,6,2,4,3,4,5,1,4,6,6,2,3};

// 横面の回転用の乱数
const UINT aroundFaceRndAllay[ RNDALLAY_NUM ] =
{1,2,1,2,1,1,1,3,2,0,1,2,3,1,2,3,2,0,2,0,0,0,3,0,2,1,0,0,2,0,2,0,1,0,2,1,0,1,1,2,3,
 0,3,0,0,3,3,1,0,1,0,2,2,0,0,1,2,0,2,3,3,3,2,3,3,1,2,2,2,2,2,3,1,1,2,0,1,2,3,2,2,3,
 0,1,1,2,1,0,1,2,3,3,0,2,0,1,0,0,1,0};

class CDiceRandSystem
{
private:
	CDiceRandSystem(){}

public:
	// デストラクタ
	~CDiceRandSystem(){}

	// シングルトン定義
	static CDiceRandSystem* GetInstance( void )
	{
		static CDiceRandSystem rndSystem;
		return &rndSystem;
	}

public:
	//----------------------------------------------------
	// @name	InitSeed
	// @content	Seedの初期化
	// @param	none
	// @return	bool		成功か失敗
	// @date	2013/11/29
	//----------------------------------------------------
	bool	InitSeed	( void )
	{
		CXorShift::GetInstance()->InitSeed(time(NULL));
		return true;
	}

private:
	//----------------------------------------------------
	// @name	GetAllayRnd	
	// @content	配列の添え字用の乱数を取得
	// @param	maxNum	取得したい乱数の最大値
	// @return	UINT	０～maxNumの範囲の乱数
	// @date	2013/11/28
	//----------------------------------------------------
	UINT	GetAllayRnd	( CONST UINT maxNum )
	{
		// 0～RNDALLAY_NUM範囲の乱数取得
		return UINT(CXorShift::GetInstance()->GetRandom(0,maxNum - 1));		
	}

public:
	//----------------------------------------------------
	// @name	GetUpperFace
	// @content	上面の面の番号の乱数取得
	// @param	none
	// @return	UINT	上面の面の目の乱数(1～6)
	// @date	2013/11/28
	//----------------------------------------------------
	CONST UINT GetUpperFace	( void )
	{
		unsigned int rnd = this->GetAllayRnd( RNDALLAY_NUM );

		return upperFaceRndAllay[ rnd ];
	}

	//----------------------------------------------------
	// @name	GetAroundFace
	// @content	横面の回転乱数を取得
	// @param	rnd		乱数(範囲0～RNDALLAY_NUM)
	// @return	UINT	横面の回転乱数数(1～3)
	// @date	2013/11/28
	//----------------------------------------------------
	CONST UINT GetAroundFace	( void )
	{
		unsigned int rnd = this->GetAllayRnd( RNDALLAY_NUM );

		return aroundFaceRndAllay[ rnd ];
	}

	//----------------------------------------------------
	// @name	GetPos
	// @content	ランダムでポジションの配列の番号取得(配列情報の最大値)
	// @param	maxAllay	配列情報の添え字の最大値
	// @return	UINT		乱数添え字番号
	// @date	2013/12/2
	//----------------------------------------------------
	CONST UINT GetPos			( CONST UINT maxAllay )
	{
		unsigned int rnd = this->GetAllayRnd( maxAllay );

		return rnd;
	}
};


#endif _C_DICE_RANDSYSTEM_H_