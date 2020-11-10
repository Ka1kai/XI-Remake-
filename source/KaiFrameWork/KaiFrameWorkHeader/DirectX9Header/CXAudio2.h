//----------------------------------------------------
// CXAudio2 
//	XAudio2�̃N���X
//
// @date	2013/6/1
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_XAUDIO2_H_
#define _C_XAUDIO2_H_

#include <xaudio2.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

class CXAudio2
{
	enum{
		MAX_WAV			= 32,	// WAV�T�E���h�ő吔
	};

private:
	IXAudio2				*m_pXAudio2;
	IXAudio2MasteringVoice	*m_pMasteringVoice;
	IXAudio2SourceVoice		*m_pSourceVoice[ MAX_WAV ];
	BYTE					*m_pWavBuffer[ MAX_WAV ];		// �g�`�f�[�^�i�t�H�[�}�b�g�����܂܂Ȃ��A�����ɔg�`�f�[�^�̂݁j
	DWORD					m_dwWavSize[ MAX_WAV ];			// �g�`�f�[�^�̃T�C�Y
	int						m_iSoundIndex[ MAX_WAV ];		// ����ǂݍ��މ��̔ԍ�
	float					m_volBGM;
	float					m_volSE;
	int						m_stepBGM;
	int						m_stepSE;
	int						m_FadeFlag[ MAX_WAV ];
	int						m_reserveNumber;

public:
	CXAudio2				( void );
	virtual ~CXAudio2		( void );

	//----------------------------------------------------
	// @name	Init
	// @content	XAudio2�̏�����
	// @param	none
	// @return	HRESULT		���������s
	//----------------------------------------------------
	HRESULT Init			( void );

	//----------------------------------------------------
	// @name	LoadWav
	// @content	Wav�f�[�^�̓ǂݍ���
	// @param	index		�ǂݍ��ޏꏊ
	// @pram	fileName	�t�@�C���p�X
	// @return	boolean		���������s
	//----------------------------------------------------	
	boolean LoadWav			( CONST UINT index, const LPSTR fileName );

	//----------------------------------------------------
	// @name	Release
	// @content	Wav�f�[�^�̉��
	// @param	index		����ꏊ
	// @return	boolean		���������s
	//----------------------------------------------------
	boolean Release			( CONST UINT index );

	//----------------------------------------------------
	// @name	Run
	// @content	�T�E���h�̍Đ�
	// @param	index		�Đ�����T�E���h�ԍ�
	// @param	vol			�Đ����鉹��
	// @param	isLoop		���[�v�Đ����邩�̃t���O
	// @return	boolean		���������s
	//----------------------------------------------------
	boolean	Run				( CONST UINT index, CONST FLOAT vol, CONST bool isLoop );

	//----------------------------------------------------
	// @name	Stop
	// @content	�T�E���h�̒�~
	// @param	index		��~����T�E���h�ԍ�
	// @return	boolean		���������s
	//----------------------------------------------------
	boolean Stop			( CONST UINT index );

	//----------------------------------------------------
	// @name	Pause
	// @content	�T�E���h�̈ꎞ��~
	// @param	index		�ꎞ��~����T�E���h�ԍ�
	// @return	boolean		���������s
	//----------------------------------------------------
	boolean Pause			( CONST UINT index );

	//----------------------------------------------------
	// @name	ChangeVolume
	// @content	�T�E���h�̉��ʕύX
	// @param	index		���ʕύX����T�E���h�ԍ�
	// @return	volume		�Z�b�g���鉹�ʂ̒l
	// @date	boolean		���������s
	//----------------------------------------------------
	boolean ChengeVolume	( CONST UINT index, CONST FLOAT vol );

	//----------------------------------------------------
	// @name	StopwithFade
	// @content	Fade�������Ē�~����T�E���h�̔ԍ����w������
	// @param	index		�t�F�[�h���������Ē�~������T�E���h�ԍ�
	// @param	num			�t���O�̐���
	// @return	boolean		���������s
	//----------------------------------------------------	
	boolean StopwithFade	( CONST UINT index, CONST int num );

	//----------------------------------------------------
	// @name	FadeStopManager
	// @content	�T�E���h�Ƀt�F�[�h�������Ē�~����B�����[�v�Ăяo���B
	// @param	volume		����
	// @return	boolean		���������s
	//----------------------------------------------------
	boolean FadeStopManeger	( CONST FLOAT volume );

public:
	float GetVolumeBGM		( void );		// BGM�̎擾	
	float GetVolumeSE		( void );		// SE�̎擾
	float SetVolumeBGM		( float vol );	// BGM�̉��ʃZ�b�g
	float SetVolumeSE		( float vol );	// SE�̉��ʃZ�b�g
	int	  GetStepBGM		( void );		// BGM��step(�{��)��Get����
	int   GetStepSE			( void );		// SE��step(�{��)��Get����
	int   SetStepBGM		( int step );	// BGM��step(�{��)��Set����
	int   SetStepSE			( int step );	// SE��step(�{��)��Set����
};

#endif _C_XAUDIO2_H_