//----------------------------------------------------
// CSnowObj Class 
// 雪のオブジェクラス
//
// @author T.Kawashita
//----------------------------------------------------
#pragma once

#include <Windows.h>
#include <d3dx9.h>

#include "../../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/2D/C2DParticle.h"
#include "../../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"
#include "../../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9Camera.h"
#include "../../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"

#include "../../../KaiFrameWork/KaiFrameWorkHeader/GameMathHeader/CRandSystem.hpp"

// 定数
#define SNOW_CNT	( 100 )

class CSnowObj
{
private:
	CRandSystem			*m_rand;			// 乱数
	C2DParticle			*m_snow;			// パーティクルの粒子
	LPSTR				m_pResSnowFilePath;	// 雪画像のファイルパス

public:
	CSnowObj();
	~CSnowObj();

public:
	void Emitter ( void );
	void Move	 ( void );
	void Draw	 ( CDirectCamera* directCamera );

public:
	/*
	//----------------------------------------------------
	//　雪画像取得 
	//----------------------------------------------------
	const CDirectResource2D* GetTexture (void)
	{
		return m_resSnow;
	}
	*/
	// ビルボード用の行列の取得
	CONST D3DXMATRIX* GetMat( int snowNo )
	{
		return m_snow[snowNo].GetWorldMtx();
	}

	// ビルボード用の頂点情報の取得
	tagTSPRITE* GetVertex( int snowNo )
	{
		return m_snow[snowNo].GetVertex();
	}
};