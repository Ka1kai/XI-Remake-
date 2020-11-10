//----------------------------------------------------
// C2DParticle 
// �p�[�e�B�N�����镨�̂�Base�ƂȂ�N���X
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
	D3DXVECTOR3 m_speed;	// �p�[�e�B�N���̐i�ޑ��x
	D3DXVECTOR3 m_direct;	// �p�[�e�B�N���̐i�ޕ���
	int			m_life;		// �����l
	float		m_rate;		// �{��
	bool		m_isExist;	// �����t���O

public:
	// �R���X�g���N�^
	C2DParticle();

	// �f�X�g���N�^
	~C2DParticle();

public:
	//----------------------------------------------------
	// @name	LifeDown
	// @content	���C�t��������
	// @param	dist		�������
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
	// @content	�����t���O�̎擾	
	// @param	none 
	// @return	bool		�����t���O
	// @date	2014/1/28
	//----------------------------------------------------
	bool		GetExist	( void )
	{
		return m_isExist;
	}

	//----------------------------------------------------
	// @name	GetLife
	// @content	���݃��C�t���擾
	// @param	none
	// @return	UINT		���C�t
	// @date	2013/12/18
	//----------------------------------------------------
	CONST UINT	GetLife		( void )
	{
		return m_life;
	}

	//----------------------------------------------------
	// @name	SetLife
	// @content	���C�t���Z�b�g
	// @param	life		�Z�b�g���郉�C�t
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
	// @content	�p�[�e�B�N���̈ړ�
	// @param	none
	// @return	none
	// @date	2013/12/18
	//----------------------------------------------------
	void		Move		( void );

	//----------------------------------------------------
	// ���l�̌v�Z�i���C�t�ōl���Ă���j
	// �{�������߂�
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
	// @content	�p�[�e�B�N���̃Z�b�g
	// @param	speed		����
	// @param	dir			����
	// @param	life		���C�t�̂�
	// @return	none
	// @date
	// @update
	//----------------------------------------------------	
	void SetParticle	( CONST D3DXVECTOR3* speed, CONST D3DXVECTOR3* dir, CONST UINT life );

};

#endif _C_2D_PARTICLE_H_