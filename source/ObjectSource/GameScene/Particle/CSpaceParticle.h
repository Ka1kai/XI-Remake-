//----------------------------------------------------
// CSpaceParticle Header 
//　空間パーティクル
//
// @date	2013/8/26
// @author  T.Kawashita
//----------------------------------------------------
#ifndef _C_SPACE_PARTICLE_H_
#define _C_SPACE_PARTICLE_H_

#include "../../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/BillBoard/CParticle.h"
#include "../../../KaiFrameWork/KaiFrameWorkHeader/GameMathHeader/CRandSystem.hpp"
#include "../../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"
#include "../../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9Camera.h"
#include "../../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"

class CSpaceParticle
{
private:
	CRandSystem			*m_pRand;					// 乱数
	CParticle			*m_pSpaceParticle;			// パーティクルの粒子
	LPSTR				m_pSpacePatricleFilePath;	// ファイルパス
	
	int					m_spaceCnt;
	bool				m_isSpaceParticle;		

public:
	CSpaceParticle	( void );
	~CSpaceParticle ( void );

public:
	void Emitter	( void );
	void Move		( void );
	void Draw		( CDirectCamera* directCamera );
};

#endif _C_SPACE_PARTICLE_H_