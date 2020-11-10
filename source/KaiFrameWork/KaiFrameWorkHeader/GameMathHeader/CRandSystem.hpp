//----------------------------------------------------
// CRandSystem Header
//  �����̐����p�w�b�_�[
//
// @date	2013/8/10
// @author  T.Kawashita
//----------------------------------------------------
#ifndef _C_RAND_SYSTEM_H_
#define _C_RAND_SYSTEM_H_

#include <stdlib.h>
#include <time.h>

class CRandSystem
{
public:
	CRandSystem	(void)
	{	
		this->ChangeSeed();	// �V�[�h�̕ύX
	}
	~CRandSystem (void)
	{
	}

public:
	//----------------------------------------------------
	// @name	ChangeSeed
	// @content	�V�[�h�̕ύX�i�^�C���ŕύX�j
	// @param	none
	// @return	none
	// @date	2013/8/10
	//----------------------------------------------------
	void ChangeSeed	( void )
	{
		srand( (unsigned)time( NULL ) );
	}

	//----------------------------------------------------
	// @name	GetRand
	// @content	����͈̗͂������擾
	// @param	start		�͈͂̍ŏ�
	// @param	end			�͈͂̍Ō�
	// @return	const int	����
	// @date	2013/8/11
	//----------------------------------------------------	
	const int GetRand	( unsigned int start,unsigned int end )
	{
		return ( rand() % end - start + 1 ) + start;
	}

	//----------------------------------------------------
	// @name	GetRand
	// @content	�ő�l�̂ݎw�肵���������擾
	// @param	max			�����Ŏ擾�ł���ő吔
	// @return	const int	����
	// @date	2013/8/11
	//----------------------------------------------------
	const int GetRand	(  int max )
	{
		return ( rand() % max );
	}

	//----------------------------------------------------
	// @name	GetRand
	// @content	�|�̒l���܂߂��������擾
	// @param	max			�͈͂̍ő�l
	// @param	minus		�͈͂̍ŏ��l
	// @param	isMinus		�|���܂߂邩�ǂ���
	// @return	const int	����
	// @date	2013/8/11
	//----------------------------------------------------
	const int GetRand	( int max, int minus,bool isMinus )
	{
		return ( ( rand() % max ) - (rand() % minus) );
	}

	//----------------------------------------------------
	// @name	GetRand
	// @content	�|�̒l���܂߂��������擾�ifloat�^)
	// @param	max			�͈͂̍ő�l
	// @return	float		����
	// @date	2013/8/11
	//----------------------------------------------------
	const float GetRand ( float  max )
	{
		int value = (int)max * 10;
		value = value + 1;
		float value2 = (float)(rand() % value ) / 10.0f;
		float value3 = (float)(rand() % value ) / 10.0f;
		return value2 - value3;
	}

};

#endif _C_RAND_SYSTEM_H_