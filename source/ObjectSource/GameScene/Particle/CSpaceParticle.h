//----------------------------------------------------
// CSpaceParticle Header 
//�@��ԃp�[�e�B�N��
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
	CRandSystem			*m_pRand;					// ����
	CParticle			*m_pSpaceParticle;			// �p�[�e�B�N���̗��q
	LPSTR				m_pSpacePatricleFilePath;	// �t�@�C���p�X
	
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