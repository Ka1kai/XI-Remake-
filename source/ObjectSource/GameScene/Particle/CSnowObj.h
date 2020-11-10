//----------------------------------------------------
// CSnowObj Class 
// ��̃I�u�W�F�N���X
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

// �萔
#define SNOW_CNT	( 100 )

class CSnowObj
{
private:
	CRandSystem			*m_rand;			// ����
	C2DParticle			*m_snow;			// �p�[�e�B�N���̗��q
	LPSTR				m_pResSnowFilePath;	// ��摜�̃t�@�C���p�X

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
	//�@��摜�擾 
	//----------------------------------------------------
	const CDirectResource2D* GetTexture (void)
	{
		return m_resSnow;
	}
	*/
	// �r���{�[�h�p�̍s��̎擾
	CONST D3DXMATRIX* GetMat( int snowNo )
	{
		return m_snow[snowNo].GetWorldMtx();
	}

	// �r���{�[�h�p�̒��_���̎擾
	tagTSPRITE* GetVertex( int snowNo )
	{
		return m_snow[snowNo].GetVertex();
	}
};