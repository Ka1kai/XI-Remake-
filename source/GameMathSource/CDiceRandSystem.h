//----------------------------------------------------
// CDiceRandSystem
//	�T�C�R���̗����̃V�X�e��
//
// @date	2013/11/28
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_DICE_RANDSYSTEM_H_
#define _C_DICE_RANDSYSTEM_H_

#include <Windows.h>
#include <time.h>
#include "../KaiFrameWork/KaiFrameWorkHeader/GameMathHeader/CXorShift.hpp"

#define RNDALLAY_NUM	( 100 )

//----------------------------------------------------
// �����p�̔z��
//----------------------------------------------------
// ��ʂ̗���
const UINT upperFaceRndAllay[ RNDALLAY_NUM ] =
{1,2,1,5,2,5,1,5,5,4,4,2,1,6,4,1,3,5,2,4,2,4,3,5,6,1,1,3,1,1,4,2,4,6,4,4,2,5,5,3,4,
 6,3,5,3,5,4,5,2,3,5,6,2,6,2,5,6,2,6,1,4,3,5,1,3,3,2,2,6,5,6,6,6,5,3,5,5,1,6,6,4,5,
 4,4,1,5,4,3,6,2,4,3,4,5,1,4,6,6,2,3};

// ���ʂ̉�]�p�̗���
const UINT aroundFaceRndAllay[ RNDALLAY_NUM ] =
{1,2,1,2,1,1,1,3,2,0,1,2,3,1,2,3,2,0,2,0,0,0,3,0,2,1,0,0,2,0,2,0,1,0,2,1,0,1,1,2,3,
 0,3,0,0,3,3,1,0,1,0,2,2,0,0,1,2,0,2,3,3,3,2,3,3,1,2,2,2,2,2,3,1,1,2,0,1,2,3,2,2,3,
 0,1,1,2,1,0,1,2,3,3,0,2,0,1,0,0,1,0};

class CDiceRandSystem
{
private:
	CDiceRandSystem(){}

public:
	// �f�X�g���N�^
	~CDiceRandSystem(){}

	// �V���O���g����`
	static CDiceRandSystem* GetInstance( void )
	{
		static CDiceRandSystem rndSystem;
		return &rndSystem;
	}

public:
	//----------------------------------------------------
	// @name	InitSeed
	// @content	Seed�̏�����
	// @param	none
	// @return	bool		���������s
	// @date	2013/11/29
	//----------------------------------------------------
	bool	InitSeed	( void )
	{
		CXorShift::GetInstance()->InitSeed(time(NULL));
		return true;
	}

private:
	//----------------------------------------------------
	// @name	GetAllayRnd	
	// @content	�z��̓Y�����p�̗������擾
	// @param	maxNum	�擾�����������̍ő�l
	// @return	UINT	�O�`maxNum�͈̗̔͂���
	// @date	2013/11/28
	//----------------------------------------------------
	UINT	GetAllayRnd	( CONST UINT maxNum )
	{
		// 0�`RNDALLAY_NUM�͈̗͂����擾
		return UINT(CXorShift::GetInstance()->GetRandom(0,maxNum - 1));		
	}

public:
	//----------------------------------------------------
	// @name	GetUpperFace
	// @content	��ʂ̖ʂ̔ԍ��̗����擾
	// @param	none
	// @return	UINT	��ʂ̖ʂ̖ڂ̗���(1�`6)
	// @date	2013/11/28
	//----------------------------------------------------
	CONST UINT GetUpperFace	( void )
	{
		unsigned int rnd = this->GetAllayRnd( RNDALLAY_NUM );

		return upperFaceRndAllay[ rnd ];
	}

	//----------------------------------------------------
	// @name	GetAroundFace
	// @content	���ʂ̉�]�������擾
	// @param	rnd		����(�͈�0�`RNDALLAY_NUM)
	// @return	UINT	���ʂ̉�]������(1�`3)
	// @date	2013/11/28
	//----------------------------------------------------
	CONST UINT GetAroundFace	( void )
	{
		unsigned int rnd = this->GetAllayRnd( RNDALLAY_NUM );

		return aroundFaceRndAllay[ rnd ];
	}

	//----------------------------------------------------
	// @name	GetPos
	// @content	�����_���Ń|�W�V�����̔z��̔ԍ��擾(�z����̍ő�l)
	// @param	maxAllay	�z����̓Y�����̍ő�l
	// @return	UINT		�����Y�����ԍ�
	// @date	2013/12/2
	//----------------------------------------------------
	CONST UINT GetPos			( CONST UINT maxAllay )
	{
		unsigned int rnd = this->GetAllayRnd( maxAllay );

		return rnd;
	}
};


#endif _C_DICE_RANDSYSTEM_H_