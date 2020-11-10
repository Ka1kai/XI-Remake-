//----------------------------------------------------
// CXAudio2 
//	XAudio2のクラス
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
		MAX_WAV			= 32,	// WAVサウンド最大数
	};

private:
	IXAudio2				*m_pXAudio2;
	IXAudio2MasteringVoice	*m_pMasteringVoice;
	IXAudio2SourceVoice		*m_pSourceVoice[ MAX_WAV ];
	BYTE					*m_pWavBuffer[ MAX_WAV ];		// 波形データ（フォーマット等を含まない、純粋に波形データのみ）
	DWORD					m_dwWavSize[ MAX_WAV ];			// 波形データのサイズ
	int						m_iSoundIndex[ MAX_WAV ];		// 今回読み込む音の番号
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
	// @content	XAudio2の初期化
	// @param	none
	// @return	HRESULT		成功か失敗
	//----------------------------------------------------
	HRESULT Init			( void );

	//----------------------------------------------------
	// @name	LoadWav
	// @content	Wavデータの読み込み
	// @param	index		読み込む場所
	// @pram	fileName	ファイルパス
	// @return	boolean		成功か失敗
	//----------------------------------------------------	
	boolean LoadWav			( CONST UINT index, const LPSTR fileName );

	//----------------------------------------------------
	// @name	Release
	// @content	Wavデータの解放
	// @param	index		解放場所
	// @return	boolean		成功か失敗
	//----------------------------------------------------
	boolean Release			( CONST UINT index );

	//----------------------------------------------------
	// @name	Run
	// @content	サウンドの再生
	// @param	index		再生するサウンド番号
	// @param	vol			再生する音量
	// @param	isLoop		ループ再生するかのフラグ
	// @return	boolean		成功か失敗
	//----------------------------------------------------
	boolean	Run				( CONST UINT index, CONST FLOAT vol, CONST bool isLoop );

	//----------------------------------------------------
	// @name	Stop
	// @content	サウンドの停止
	// @param	index		停止するサウンド番号
	// @return	boolean		成功か失敗
	//----------------------------------------------------
	boolean Stop			( CONST UINT index );

	//----------------------------------------------------
	// @name	Pause
	// @content	サウンドの一時停止
	// @param	index		一時停止するサウンド番号
	// @return	boolean		成功か失敗
	//----------------------------------------------------
	boolean Pause			( CONST UINT index );

	//----------------------------------------------------
	// @name	ChangeVolume
	// @content	サウンドの音量変更
	// @param	index		音量変更するサウンド番号
	// @return	volume		セットする音量の値
	// @date	boolean		成功か失敗
	//----------------------------------------------------
	boolean ChengeVolume	( CONST UINT index, CONST FLOAT vol );

	//----------------------------------------------------
	// @name	StopwithFade
	// @content	Fadeをかけて停止するサウンドの番号を指示する
	// @param	index		フェードをかけｋて停止させるサウンド番号
	// @param	num			フラグの数字
	// @return	boolean		成功か失敗
	//----------------------------------------------------	
	boolean StopwithFade	( CONST UINT index, CONST int num );

	//----------------------------------------------------
	// @name	FadeStopManager
	// @content	サウンドにフェードをかけて停止する。毎ループ呼び出す。
	// @param	volume		音量
	// @return	boolean		成功か失敗
	//----------------------------------------------------
	boolean FadeStopManeger	( CONST FLOAT volume );

public:
	float GetVolumeBGM		( void );		// BGMの取得	
	float GetVolumeSE		( void );		// SEの取得
	float SetVolumeBGM		( float vol );	// BGMの音量セット
	float SetVolumeSE		( float vol );	// SEの音量セット
	int	  GetStepBGM		( void );		// BGMのstep(倍率)をGetする
	int   GetStepSE			( void );		// SEのstep(倍率)をGetする
	int   SetStepBGM		( int step );	// BGMのstep(倍率)をSetする
	int   SetStepSE			( int step );	// SEのstep(倍率)をSetする
};

#endif _C_XAUDIO2_H_