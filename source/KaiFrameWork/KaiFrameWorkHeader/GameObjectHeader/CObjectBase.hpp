//----------------------------------------------------
// CObjectBase 
//	Object�̊��N���X(2D 3D�����Ή�)
//
// @date	2013/12/12
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_OBJECT_BASE_H_
#define _C_OBJECT_BASE_H_

#include <d3dx9.h>

class CObjectBase
{
protected:
	D3DXMATRIX	m_worldMtx;		// ���[���h���W

public:
	// �R���X�g���N�^
	CObjectBase				( void )
	{
		D3DXMatrixIdentity( &m_worldMtx );
	}

	// �f�X�g���N�^
	virtual ~CObjectBase	( void ){}

public:
	//----------------------------------------------------
	// ������
	//----------------------------------------------------
	bool	Init		( void )
	{
		this->InitWorldMtx();

		return true;
	}

	//----------------------------------------------------
	// ���[���h�s��̎擾
	//----------------------------------------------------
	CONST D3DXMATRIX*	GetWorldMtx	( void )
	{
		return &m_worldMtx;
	}

	//----------------------------------------------------
	// ���[���h�s���P�ʍs��
	//----------------------------------------------------
	void InitWorldMtx	( void )
	{
		D3DXMatrixIdentity( &m_worldMtx );
	}

	//----------------------------------------------------
	// @name	SetWorldMtx
	// @content	���[���h�s��̃Z�b�g
	// @param	pInMtx		�Z�b�g���������[���h�s��
	// @return	none
	// @date	2014/1/27
	//----------------------------------------------------
	void SetWorldMtx	( CONST D3DXMATRIX* pInMtx )
	{
		memcpy( &m_worldMtx, pInMtx, sizeof(D3DXMATRIX) );
	}

	//----------------------------------------------------
	// @name	SetWorldPos
	// @content	���[���h���W�̃Z�b�g	
	// @param	xPos		X���W
	// @param	yPos		Y���W
	// @param	zPos		Z���W
	// @return	none
	// @date	2013/12/12
	//----------------------------------------------------
	void SetWorldPos	( CONST float xPos, CONST float yPos, CONST float zPos )
	{
		m_worldMtx._41 = xPos;
		m_worldMtx._42 = yPos;
		m_worldMtx._43 = zPos;
	}

	//----------------------------------------------------
	// @name	SetWorldPos
	// @content	���[���h���W�̃Z�b�g
	// @param	vec			���W���w�肵���x�N�g��
	// @return	none
	// @date	2013/12/18
	//----------------------------------------------------
	void SetWorldPos	( CONST D3DXVECTOR3* vec )
	{
		m_worldMtx._41 = vec->x;
		m_worldMtx._42 = vec->y;
		m_worldMtx._43 = vec->z;
	}

	//----------------------------------------------------
	// @name	SetWorldPos
	// @content	���[���h���W�̃Z�b�g
	// @param	mtx			���[���h���W�s��
	// @return	none
	// @date	2014/1/17
	//----------------------------------------------------
	void SetWorldPos	( CONST D3DXMATRIX*	mtx )
	{
		m_worldMtx._41 = mtx->_41;
		m_worldMtx._42 = mtx->_42;
		m_worldMtx._43 = mtx->_43;
	}

	//----------------------------------------------------
	// @name	CalcWorldMtx	
	// @content	2�̍s��������ă��[���h���W�s��ɕϊ�
	// @param	mtx1		�s��P
	// @param	mtx2		�s��Q
	// @return	none
	// @date	2013/12/12
	//----------------------------------------------------
	void CalcWorldMtx	( CONST  D3DXMATRIX* mtx1, CONST D3DXMATRIX* mtx2 )
	{
		D3DXMatrixMultiply( &m_worldMtx, mtx1, mtx2 );
	}

	//----------------------------------------------------
	// @name	MoveWorldPos
	// @content �x�N�g�����w�肵�ă��[���h���W���ړ�
	// @param	vec			�x�N�g��
	// @return	none
	// @date	2013/12/12
	//----------------------------------------------------
	void MoveWorldPos	( CONST D3DXVECTOR3* vec )
	{
		m_worldMtx._41 += vec->x;
		m_worldMtx._42 += vec->y;
		m_worldMtx._43 += vec->z;
	}

	//----------------------------------------------------
	// @name	MoveWorldPos
	// @content	���W���w�肵�ă��[���h���W���ړ�
	// @param	x			����X���W��
	// @param	y			����Y���W��
	// @param	z			����Z���W��
	// @return	none
	// @date	2013/12/12
	//----------------------------------------------------
	void MoveWorldPos	( CONST float x, CONST float y, CONST float z )
	{
		m_worldMtx._41 += x;
		m_worldMtx._42 += y;
		m_worldMtx._43 += z;
	}

	//----------------------------------------------------
	// ���W�̎擾
	//----------------------------------------------------
	CONST float GetXPos( void )
	{
		return m_worldMtx._41;
	}
	CONST float GetYPos( void )
	{
		return m_worldMtx._42;
	}
	CONST float GetZPos( void )
	{
		return m_worldMtx._43;
	}
};

#endif _C_OBJECT_BASE_H_