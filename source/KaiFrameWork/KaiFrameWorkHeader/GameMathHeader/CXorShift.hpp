/*************************************************************
*	@file   	xorShift.h
*	@brief  	xorShift.�N���X�w�b�_�[
*	@note		���ɂȂ�
*	@author		Tatsunori Aoyama
*	@date		2013/05/19
*************************************************************/

#ifndef _Include_CXorShift_h_	// �C���N���[�h�K�[�h
#define _Include_CXorShift_h_


/*!-----------------------------------------------------------
//	@class  CXorShift
//	@brief  Xorshif���g�p���������N���X
//	@note	���ɂȂ�
//	@author	Tatsunori Aoyama
//	@date	2013/05/19
------------------------------------------------------------*/
class CXorShift
{
public:
	/// �f�X�g���N�^
	~CXorShift(){}


	/*!-----------------------------------------------------------
	//	@brief		�����̃V�[�h�l�ݒ�
	//	@note		���ɂȂ�
	//	@param[in]	setSeed �ݒ肷��V�[�h�l
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/05/19
	------------------------------------------------------------*/
	void	InitSeed( _int64 setSeed )
	{
		m_seed  = setSeed;
		m_z ^= m_seed;
		m_z ^= m_z >> 21;
		m_z ^= m_z << 35;
		m_z ^= m_z >> 4;
		m_w ^= m_z << 2;
		m_w *= 8943207074934384298LL;
		m_z *= 2685821657736338717LL;
	}

	/*!-----------------------------------------------------------
	//	@brief		�����̎擾
	//	@note		���ɂȂ�
	//	@param[in]	�Ȃ�
	//	@return		�擾���闐��
	//	@author		Tatsunori Aoyama
	//	@date		2013/05/19
	------------------------------------------------------------*/
	_int64 GetRandom()
	{
		_int64 t=(m_x^(m_x<<11));
		m_x=m_y;
		m_y=m_z;
		m_z=m_w;
		return ( m_w=(m_w^(m_w>>19))^(t^(t>>8)) );
	}

	/*!-----------------------------------------------------------
	//	@brief		�͈͗����̎擾
	//	@note		���ɂȂ�
	//	@param[in]	min �ŏ��l�i�͈͂Ɋ܂܂��j
	//	@param[in]	max �ő�l�i��$�͂Ɋ܂܂��j
	//	@return		�擾���闐��
	//	@author		Tatsunori Aoyama
	//	@date		2013/05/19
	------------------------------------------------------------*/
	_int64 GetRandom(int min,int max)
	{
		_int64 rn = this->GetRandom();
		return (this->GetRandom()%(max+1-min) + min);
	}

	/*!-----------------------------------------------------------
	//	@brief		�C���X�^���X�擾
	//	@note		���ɂȂ�
	//	@param[in]	�Ȃ�
	//	@return		���g�̎Q��
	//	@author		Tatsunori Aoyama
	//	@date		2013/05/19
	------------------------------------------------------------*/
	static	CXorShift*	GetInstance()
	{
		static	CXorShift	singleton;
		
		return &singleton;
	}

private:
	_int64 m_x;
	_int64 m_y;
	_int64 m_z;
	_int64 m_w; 
	_int64 m_seed;
private:
	/// �R���X�g���N�^
	CXorShift()
	{
		m_x = 123456789;
		m_y = 362436069;
		m_z = 521288629;
		m_w = 88675123;
		m_seed = 1;
	};
};


//�V���O���g����`
inline	CXorShift*	sXorShift()
{
	return CXorShift::GetInstance();
}



#endif // _Include_CXorShift_h_