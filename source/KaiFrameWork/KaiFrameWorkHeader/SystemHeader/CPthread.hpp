//----------------------------------------------------
// CPthread
//	PThread�ł̃}���`�X���b�h
// 
// @date	2013/11/5
// @author  T.Kawashita
//----------------------------------------------------
#ifndef _C_PTHREAD_H_
#define _C_PTHREAD_H_

#include <windows.h>
/*
#include <pthread.h>

#pragma comment( lib, "pthreadVC2.lib" )

class CPthread
{
private:
	pthread_t	m_pThread;	// �X���b�h
	
public:
	//----------------------------------------------------
	// �R���X�g���N�^
	//----------------------------------------------------
	CPthread	( void ){}

	//----------------------------------------------------
	// �f�X�g���N�^
	//----------------------------------------------------
	~CPthread	( void ){}
	
	//----------------------------------------------------
	// @name	Create
	// @content	�X���b�h�̍쐬
	// @param	startThread		�X�^�[�g���������֐��|�C���^
	// @param	arg				�X���b�h�ɓn������
	// @return	bool			�쐬�ł�����
	// @date	2014/1/24
	//----------------------------------------------------
	bool	Create	( void* startThread(void * _info), void* arg )
	{
		pthread_create( &m_pThread, NULL, startThread, arg );
		
		return true;
	}

	//----------------------------------------------------
	// @name	Wait
	// @content	�X���b�h�ҋ@
	// @param	none
	// @return	bool		�X���b�h�ҋ@���ďI�������
	// @date	2014/1/24
	//----------------------------------------------------
	bool	Wait	( void )
	{
		pthread_join( m_pThread, NULL );

		return true;
	}

};
*/
#endif _C_PTHREAD_H_