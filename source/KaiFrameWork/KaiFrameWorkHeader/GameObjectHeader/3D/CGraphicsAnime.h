//----------------------------------------------------
// CGraphicsAnime Header
//�@�A�j���[�V�����̃��f��
//
// @author T.Kawashita
//----------------------------------------------------
#ifndef _C_GRAPHICS_ANIME_H_
#define _C_GRAPHICS_ANIME_H_

#include "CDirectGraphics3DBase.h"

//----------------------------------------------------
// �̂̃p�[�c
//----------------------------------------------------
enum
{
	HIP,
	BODY,
	HEAD,
	ARMR0,
	ARML0,
	LEGR0,
	LEGL0,
	ARMR1,
	ARML1,
	LEGR1,
	LEGL1,
	PARTSMAX
};

//----------------------------------------------------
// �̂̍\����
//----------------------------------------------------
struct _3DObjectInitData
{
	int		parentObjectNo;
	int		ModelNo;
};

class CGraphicsAnime : public CDirectGraphics3DBase
{
private:
	D3DVECTOR			m_initPos;
	_3DObjectInitData	m_objData;

public:
	CGraphicsAnime			( void ){}
	virtual ~CGraphicsAnime	( void ){}

public:
	//----------------------------------------------------
	// model�ԍ��̃Z�b�g
	// @data	modelNo
	// @return	none
	//----------------------------------------------------
	void	SetModelNo		( CONST int modelNo )
	{
		m_objData.ModelNo = modelNo;
	}

	//----------------------------------------------------
	// �������W�̃Z�b�g 
	// @data	x y z
	// @return none
	//----------------------------------------------------
	void	SetInitPos			( CONST float x,CONST float y,CONST float z )
	{
		m_initPos.x = x;
		m_initPos.y = y;
		m_initPos.z = z;

		this->SetWorldMtx();
	}

	//----------------------------------------------------
	// ���[���h���W�ɏ������W�̃Z�b�g 
	// @data	none
	// @return	none
	//----------------------------------------------------
	void	SetWorldMtx		( void )
	{
		CDirectGraphics3DBase::SetWorldMtx( m_initPos.x,m_initPos.y,m_initPos.z );
		CDirectGraphics3DBase::SetLocalMtx( m_initPos.x,m_initPos.y,m_initPos.z );
	}

	//----------------------------------------------------
	// �e�̔ԍ��Z�b�g
	// @data	parentNo
	// @return	none
	//----------------------------------------------------
	void	SetParentNo		( CONST int parentNo )
	{
		m_objData.parentObjectNo = parentNo;
	}

	//----------------------------------------------------
	//�@�ԍ��擾 
	// @data	none
	// @return	CONST int
	//----------------------------------------------------
	CONST int GetModelNo	( void )
	{
		return m_objData.ModelNo;
	}

	//----------------------------------------------------
	// �e�̔ԍ��擾 
	// @data	none
	// @return	CONST int
	//----------------------------------------------------
	CONST int GetParentNo	( void )
	{
		return m_objData.parentObjectNo;
	}
};

#endif _C_GRAPHICS_ANIME_H_