//----------------------------------------------------
// C2DParticle 
// パーティクルする物体のBaseとなるクラス
//
// @date	2013/12/18
// @author  T.Kawashita
//----------------------------------------------------
#ifndef _C_2D_PARTICLE_H_
#define _C_2D_PARTICLE_H_

#include <Windows.h>
#include <d3dx9.h>
#include "C2DBillBoard.h"

class C2DParticle : public C2DBillBoard
{
private:
	D3DXVECTOR3 m_speed;	// パーティクルの進む速度
	D3DXVECTOR3 m_direct;	// パーティクルの進む方向
	int			m_life;		// 生存値
	float		m_rate;		// 倍率
	bool		m_isExist;	// 生存フラグ

public:
	// コンストラクタ
	C2DParticle();

	// デストラクタ
	~C2DParticle();

public:
	//----------------------------------------------------
	// @name	LifeDown
	// @content	ライフを下げる
	// @param	dist		下げる量
	// @return	none
	// @date	2013/12/18
	//----------------------------------------------------
	void		LifeDown	( CONST UINT dist )
	{
		m_life = m_life - dist;
		if( m_life <= 0 )
		{
			m_life = 0;
			m_isExist = false;
		}
	}

	//----------------------------------------------------
	// @name	GetExist
	// @content	生存フラグの取得	
	// @param	none 
	// @return	bool		生存フラグ
	// @date	2014/1/28
	//----------------------------------------------------
	bool		GetExist	( void )
	{
		return m_isExist;
	}

	//----------------------------------------------------
	// @name	GetLife
	// @content	現在ライフを取得
	// @param	none
	// @return	UINT		ライフ
	// @date	2013/12/18
	//----------------------------------------------------
	CONST UINT	GetLife		( void )
	{
		return m_life;
	}

	//----------------------------------------------------
	// @name	SetLife
	// @content	ライフをセット
	// @param	life		セットするライフ
	// @return	none
	// @date	2013/12/18
	//----------------------------------------------------	
	void		SetLife		( CONST UINT life )
	{
		m_life = life;	
	}

public:
	//----------------------------------------------------
	// @name	Move
	// @content	パーティクルの移動
	// @param	none
	// @return	none
	// @date	2013/12/18
	//----------------------------------------------------
	void		Move		( void );

	//----------------------------------------------------
	// α値の計算（ライフで考えている）
	// 倍率を求める
	//----------------------------------------------------
	/*void CalcAlfa		( void )
	{
		int alfa;

		m_rate = (float)this->GetMaxAlfa() / (float)m_life;
		alfa =(int)(m_rate * this->GetLife());
		this->SetAlfa( alfa );
	}*/


	//----------------------------------------------------
	// @name	SetParticle
	// @content	パーティクルのセット
	// @param	speed		速さ
	// @param	dir			向き
	// @param	life		ライフのｎ
	// @return	none
	// @date
	// @update
	//----------------------------------------------------	
	void SetParticle	( CONST D3DXVECTOR3* speed, CONST D3DXVECTOR3* dir, CONST UINT life );

};

#endif _C_2D_PARTICLE_H_