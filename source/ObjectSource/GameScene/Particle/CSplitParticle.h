//----------------------------------------------------
// CSplitParticle 
//	ダイスが動いた時に弾けるパーティクル
//
// @date	2014/1/27
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_SPLIT_PARTICLE_
#define _C_SPLIT_PARTICLE_

#include "../../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9Camera.h"
#include "../../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"
#include "../../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/2D/C2DParticle.h"
#include "../../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"
#include "../../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourcePath.hpp"

#include "../../../KaiFrameWork/KaiFrameWorkHeader/GameMathHeader/CXorShift.hpp"

#include "../../../KaiFrameWork/KaiFrameWorkHeader/UtilityHeader/Macro.hpp"

class CSplitParticle
{
private:
	LPSTR			m_pResParticle;
	C2DParticle*	m_pSplitPartcle;


public:
	// コンストラクタ
	CSplitParticle	( void );

	// デストラクタ
	~CSplitParticle	( void );

public:
	void Emitter	( CONST float xPos, CONST float yPos, CONST float zPos );
	void Move		( void );
	void Draw		( CONST D3DXMATRIX* view );

};


#endif _C_SPLIT_PARTICLE_