//----------------------------------------------------
// CFpsControl
//	Fps�v�Z�E�i�[�E�����Ȃǂ��s��
// 
// @date	2013/5/8
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_FPSCONTROL_H_
#define _C_FPSCONTROL_H_

#include<Windows.h>

class CFpsControl
{
private:
	DWORD		m_execLastTime;	// �Ō�ɃQ�[��������������
	DWORD		m_fpsLastTime;	// �Ō��FPS���v����������
	DWORD		m_currentTime;	// �ŐV����
	int			m_countFrame;	// �`���(FPS�v���p)
	float		m_countFps;		// FPS�l�\���p

public:
	// �R���X�g���N�^
	CFpsControl	(void)
	{
		m_execLastTime = 0;
		m_fpsLastTime = 0;
		m_currentTime = 0;
		m_countFrame = 0;
		m_countFps = 0;

		// FPS�v�Z�ɕK�v�Ȏ��Ԃ��擾
		m_execLastTime = m_fpsLastTime = timeGetTime();
	
	}

	// �f�X�g���N�^
	virtual ~CFpsControl	(void){}

public:

	//----------------------------------------------------
	// @name	GetFps
	// @content	Fps�l�̎擾
	// @param	none
	// @return	float	FPS�l
	// @date	2013/5/8
	// @update	2013/11/6
	//----------------------------------------------------
	float* GetFPS			( void )
	{	
		return &m_countFps;
	}

	//----------------------------------------------------
	// @name	GetFrameCount
	// @content	�t���[�����̎擾
	// @param	none
	// @return	int		�t���[����
	// @date	2013/5/8
	// @update	2013/11/6
	//----------------------------------------------------
	int		GetFrameCount	( void )
	{	
		return m_countFrame;
	}

public:
	//----------------------------------------------------
	// @name	TuneFps
	// @content	FPS�̒���
	// @param	none
	// @return	bool	16ms��������true	
	// @date	2013/5/8
	// @update	2013/11/6
	//----------------------------------------------------
	bool	TuneFps			( void )
	{	
		while( 1 )
		{
			m_currentTime = timeGetTime();
			if( m_currentTime - m_execLastTime >= 1000 / 60 )
				break;
		}
		m_execLastTime = m_currentTime;
		
		return true;
	}

	//----------------------------------------------------
	// @name	CalcFps
	// @content	FPS�̌v�Z
	// @param	none
	// @return	bool	60FPS�̌v�Z
	// @date	2013/5/8
	// @update	2013/11/6
	//----------------------------------------------------
	bool	CalcFPS			( void )
	{	
		if( m_countFrame >= 60 )
		{
			m_countFps = ( m_countFrame * 1000 )/( (float)m_currentTime - m_fpsLastTime );
			m_fpsLastTime = timeGetTime();
			m_countFrame = 0;
		}

		m_countFrame ++;
		return true;
	}
};

#endif