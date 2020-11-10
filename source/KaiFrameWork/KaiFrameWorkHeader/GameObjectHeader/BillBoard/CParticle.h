//----------------------------------------------------
// CParticle 
// パーティクルする物体のBaseとなるクラス
//
// @date	2013/8/25
// @author  T.Kawashita
//----------------------------------------------------
#ifndef _C_PARTICLE_H_
#define _C_PARTICLE_H_

#include <Windows.h>
#include <d3dx9.h>
#include "CBillBoard.h"

class CParticle:public CBillBoard
{
private:
	D3DXVECTOR3 m_speed;	// パーティクルの進む速度
	D3DXVECTOR3 m_direct;	// パーティクルの進む方向
	int			m_life;		// 生存値
	float		m_rate;		// 倍率

public:
	// コンストラクタ
	CParticle()
	{
		m_speed.x = 0.0f;
		m_speed.y = 0.0f;
		m_speed.z = 0.0f;
		m_direct.x = 0.0f;
		m_direct.y = 0.0f;
		m_direct.z = 0.0f;
		m_life = 0;
		m_rate = (float)(this->GetAlfa() / 255);
	}
	CParticle(float xSpeed,float ySpeed,float zSpeed,float xDirect,float yDirect,float zDirect,int life,int alfa)
	{
		m_speed.x = xSpeed;
		m_speed.y = ySpeed;
		m_speed.z = zSpeed;
		m_direct.x = xDirect;
		m_direct.y = yDirect;
		m_direct.z = zDirect;
		m_life = life;
		m_rate = (float)(this->GetAlfa() / life);
	}
	~CParticle(){}

public:
	// ライフを減らす
	void LifeDown ( int dist )
	{
		m_life = m_life - dist;
	}

	// ライフを取得
	const int GetLife	()
	{
		return m_life;
	}

	//----------------------------------------------------
	// ライフのセット
	//----------------------------------------------------
	void SetLife		( int life )
	{
		m_life = life;	
	}

	//----------------------------------------------------
	// α値の計算（ライフで考えている）
	// 倍率を求める
	//----------------------------------------------------
	void CalcAlfa		( void )
	{
		int alfa;

		m_rate = (float)this->GetMaxAlfa() / (float)m_life;
		alfa =(int)(m_rate * this->GetLife());
		this->SetAlfa( alfa );
	}

	//----------------------------------------------------
	//　パーティクル移動 
	//----------------------------------------------------
	void Move			( void )
	{
		D3DXVECTOR3 move;	// 移動用work

		move.x = this->GetPos()->x + m_speed.x * m_direct.x;
		move.y = this->GetPos()->y + m_speed.y * m_direct.y;
		move.z = this->GetPos()->z + m_speed.z * m_direct.z;

		this->SetPosition( move.x,move.y,move.z );
	}

	//----------------------------------------------------
	// パーティクルのセット 
	//----------------------------------------------------
	void SetParticle	( float xSpeed,float ySpeed,float zSpeed,float xDirect,float yDirect,float zDirect )
	{
		m_speed.x = xSpeed;
		m_speed.y = ySpeed;
		m_speed.z = zSpeed;
		m_direct.x = xDirect;
		m_direct.y = yDirect;
		m_direct.z = zDirect;	
	}

};

#endif _C_PARTICLE_H_