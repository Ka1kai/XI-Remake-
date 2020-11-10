//----------------------------------------------------
// CPthread
//	PThreadでのマルチスレッド
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
	pthread_t	m_pThread;	// スレッド
	
public:
	//----------------------------------------------------
	// コンストラクタ
	//----------------------------------------------------
	CPthread	( void ){}

	//----------------------------------------------------
	// デストラクタ
	//----------------------------------------------------
	~CPthread	( void ){}
	
	//----------------------------------------------------
	// @name	Create
	// @content	スレッドの作成
	// @param	startThread		スタートさせたい関数ポインタ
	// @param	arg				スレッドに渡す引数
	// @return	bool			作成できたら
	// @date	2014/1/24
	//----------------------------------------------------
	bool	Create	( void* startThread(void * _info), void* arg )
	{
		pthread_create( &m_pThread, NULL, startThread, arg );
		
		return true;
	}

	//----------------------------------------------------
	// @name	Wait
	// @content	スレッド待機
	// @param	none
	// @return	bool		スレッド待機して終わったら
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