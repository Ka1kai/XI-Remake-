/*************************************************************
*	@file   	xorShift.h
*	@brief  	xorShift.クラスヘッダー
*	@note		特になし
*	@author		Tatsunori Aoyama
*	@date		2013/05/19
*************************************************************/

#ifndef _Include_CXorShift_h_	// インクルードガード
#define _Include_CXorShift_h_


/*!-----------------------------------------------------------
//	@class  CXorShift
//	@brief  Xorshifを使用した乱数クラス
//	@note	特になし
//	@author	Tatsunori Aoyama
//	@date	2013/05/19
------------------------------------------------------------*/
class CXorShift
{
public:
	/// デストラクタ
	~CXorShift(){}


	/*!-----------------------------------------------------------
	//	@brief		乱数のシード値設定
	//	@note		特になし
	//	@param[in]	setSeed 設定するシード値
	//	@return		なし
	//	@author		Tatsunori Aoyama
	//	@date		2013/05/19
	------------------------------------------------------------*/
	void	InitSeed( _int64 setSeed )
	{
		m_seed  = setSeed;
		m_z ^= m_seed;
		m_z ^= m_z >> 21;
		m_z ^= m_z << 35;
		m_z ^= m_z >> 4;
		m_w ^= m_z << 2;
		m_w *= 8943207074934384298LL;
		m_z *= 2685821657736338717LL;
	}

	/*!-----------------------------------------------------------
	//	@brief		乱数の取得
	//	@note		特になし
	//	@param[in]	なし
	//	@return		取得する乱数
	//	@author		Tatsunori Aoyama
	//	@date		2013/05/19
	------------------------------------------------------------*/
	_int64 GetRandom()
	{
		_int64 t=(m_x^(m_x<<11));
		m_x=m_y;
		m_y=m_z;
		m_z=m_w;
		return ( m_w=(m_w^(m_w>>19))^(t^(t>>8)) );
	}

	/*!-----------------------------------------------------------
	//	@brief		範囲乱数の取得
	//	@note		特になし
	//	@param[in]	min 最小値（範囲に含まれる）
	//	@param[in]	max 最大値（範$囲に含まれる）
	//	@return		取得する乱数
	//	@author		Tatsunori Aoyama
	//	@date		2013/05/19
	------------------------------------------------------------*/
	_int64 GetRandom(int min,int max)
	{
		_int64 rn = this->GetRandom();
		return (this->GetRandom()%(max+1-min) + min);
	}

	/*!-----------------------------------------------------------
	//	@brief		インスタンス取得
	//	@note		特になし
	//	@param[in]	なし
	//	@return		自身の参照
	//	@author		Tatsunori Aoyama
	//	@date		2013/05/19
	------------------------------------------------------------*/
	static	CXorShift*	GetInstance()
	{
		static	CXorShift	singleton;
		
		return &singleton;
	}

private:
	_int64 m_x;
	_int64 m_y;
	_int64 m_z;
	_int64 m_w; 
	_int64 m_seed;
private:
	/// コンストラクタ
	CXorShift()
	{
		m_x = 123456789;
		m_y = 362436069;
		m_z = 521288629;
		m_w = 88675123;
		m_seed = 1;
	};
};


//シングルトン定義
inline	CXorShift*	sXorShift()
{
	return CXorShift::GetInstance();
}



#endif // _Include_CXorShift_h_