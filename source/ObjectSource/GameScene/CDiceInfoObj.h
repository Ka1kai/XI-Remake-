//----------------------------------------------------
// CDiceInfoObj 
//	�_�C�XINFO�p�̃I�u�W�F�N�g
//
// @date	2014/2/13
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_DICE_INFO_OBJ_H_
#define _C_DICE_INFO_OBJ_H_

#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/3D/C3DObjectAlphaBlend.h"

class CDiceInfoObj : public C3DObjectAlphaBlend
{
private:
	bool	m_isExist;

public:
	void	SetIsExist	( bool isExist )
	{
		m_isExist = isExist;
	}
	bool	GetIsExist	( void )
	{
		return m_isExist;
	}

public:
	CDiceInfoObj	( void );	// �R���X�g���N�^
	~CDiceInfoObj	( void );	// �f�X�g���N�^

public:
	bool	Init			( void );	// ������
	void	CopyRotationMtx	( CONST D3DXMATRIX* worldMtx );	// ��]�s����R�s�[���ă��[���h�s��ɃZ�b�g
};

#endif _C_DICE_INFO_OBJ_H_