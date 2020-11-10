
#include "../../KaiFrameWorkHeader/DirectX9Header/CXAudio2.h"


//----------------------------------------------------
// コンストラクタ 
//----------------------------------------------------
CXAudio2::CXAudio2( void )
{
	m_pXAudio2 = NULL;
	m_pMasteringVoice = NULL;

	for( int i = 0; i < MAX_WAV; ++ i )
	{
		m_pSourceVoice[ i ] = NULL;
		m_pWavBuffer[ i ]	= NULL;
		m_dwWavSize[ i ]	= 0;
	}
	
	m_reserveNumber = 0;

	for(int i = 0; i < 10; i++)
	{
		m_FadeFlag[i] = 0;
	}

	m_volBGM = 1.0f;	//BGM音量の初期設定
	m_volSE = 1.0f;		//SE音量の初期設定
	m_stepBGM = 4;
	m_stepSE = 4;
}

//----------------------------------------------------
// デストラクタ 
//----------------------------------------------------
CXAudio2::~CXAudio2( void )
{
	for( int i = 0; i < MAX_WAV; ++i )
	{
		Stop( i );		// とりあえず曲をストップ

		if( m_pSourceVoice[ i ] != NULL )
		{
			m_pSourceVoice[ i ]->DestroyVoice();	
		}	

		if( m_pWavBuffer[ i ] != NULL )
		{
			delete m_pWavBuffer[ i ];
			m_pWavBuffer[ i ] = NULL;
		}
	}

	if( m_pXAudio2 != NULL )
	{
		m_pXAudio2->Release();
		m_pXAudio2 = NULL;
	}
}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
HRESULT CXAudio2::Init( void )
{
	CoInitializeEx( NULL, COINIT_MULTITHREADED );	

	if( FAILED( XAudio2Create( &m_pXAudio2, XAUDIO2_DEBUG_ENGINE ) ) )
	{
		CoUninitialize();
		return E_FAIL;
	}

	if( FAILED( m_pXAudio2->CreateMasteringVoice( &m_pMasteringVoice ) ) )
	{
		CoUninitialize();
		return E_FAIL;
	}

	return S_OK;
}

//----------------------------------------------------
// Wavデータの読み込み
//----------------------------------------------------
boolean CXAudio2::LoadWav( CONST UINT index, CONST LPSTR fileName )
{
	// すでにデータが入っているとき
	if( m_pWavBuffer[ index ] )
	{
		return false;
	}

	// 範囲外のとき
	if( index >= MAX_WAV || index < 0 )
	{
		return false;
	}

	HMMIO hMmio=NULL;			// WindowsマルチメディアAPIのハンドル(WindowsマルチメディアAPIはWAVファイル関係の操作用のAPI)
	DWORD dwWavSize=0;			// WAVファイル内　WAVデータのサイズ（WAVファイルはWAVデータで占められているので、ほぼファイルサイズと同一）
	WAVEFORMATEX* pwfex;		// WAVのフォーマット 例）16ビット、44100Hz、ステレオなど
	MMCKINFO ckInfo;			// チャンク情報
	MMCKINFO riffckInfo;		// 最上部チャンク（RIFFチャンク）保存用
	PCMWAVEFORMAT pcmWaveForm;

	//WAVファイル内のヘッダー情報（音データ以外）の確認と読み込み
	hMmio = mmioOpenA( fileName, NULL, MMIO_ALLOCBUF | MMIO_READ );

	//ファイルポインタをRIFFチャンクの先頭にセットする
	mmioDescend( hMmio, &riffckInfo, NULL, 0 );
	
	// ファイルポインタを'f' 'm' 't' ' ' チャンクにセットする
	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	
	mmioDescend( hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK );
	
	//フォーマットを読み込む
	mmioRead( hMmio, ( HPSTR ) &pcmWaveForm, sizeof( pcmWaveForm ) );
	
	pwfex = ( WAVEFORMATEX* )new CHAR[ sizeof( WAVEFORMATEX ) ];
	
	memcpy( pwfex, &pcmWaveForm, sizeof( pcmWaveForm ) );
	pwfex->cbSize = 0;	
	mmioAscend( hMmio, &ckInfo, 0 );

	// WAVファイル内の音データの読み込み	
	ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend( hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK );//データチャンクにセット
	dwWavSize = ckInfo.cksize;

	m_pWavBuffer[ index ] = new BYTE[ dwWavSize ];	// 動的確保

	mmioRead( hMmio, ( HPSTR )m_pWavBuffer[ index ], dwWavSize );
	//ソースボイスにデータを詰め込む	
	if( FAILED( m_pXAudio2->CreateSourceVoice( &m_pSourceVoice[ index ], pwfex ) ) )
	{
		MessageBox(0,"ソースボイス作成失敗",0,MB_OK);
		delete[] pwfex;
		return false;
	}

	delete[] pwfex;

	m_dwWavSize[ index ] = dwWavSize;

	m_reserveNumber ++;

	return true;;
}

//----------------------------------------------------
// Wavデータの解放 
//----------------------------------------------------
boolean CXAudio2::Release( CONST UINT index )
{
	if( m_pSourceVoice[ index ] != NULL )
	{
		m_pSourceVoice[ index ]->DestroyVoice();
		m_pSourceVoice[ index ] = NULL;
	}

	if( m_pWavBuffer[ index ] != NULL )
	{
		delete m_pWavBuffer[ index ];
		m_pWavBuffer[ index ] = NULL;
	}

	m_reserveNumber--;

	return true;
}

//----------------------------------------------------
// サウンドの再生 
//----------------------------------------------------
boolean CXAudio2::Run( CONST UINT index, CONST FLOAT volume, CONST bool isLoop )
{
	if( !m_pSourceVoice[ index ] )
	{
		return false;
	}

	m_pSourceVoice[ index ]->Stop( 0, 0 );
	m_pSourceVoice[ index ]->FlushSourceBuffers();
	m_pSourceVoice[ index ]->SetVolume( volume );
	
	XAUDIO2_BUFFER buffer = {0};

	buffer.pAudioData	= m_pWavBuffer[ index ];
	buffer.Flags		= XAUDIO2_END_OF_STREAM;
	buffer.AudioBytes	= m_dwWavSize[ index ];

	//ループの設定
	if( isLoop ){
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	if( FAILED( m_pSourceVoice[ index ]->SubmitSourceBuffer( &buffer ) ) )
	{
		MessageBox( NULL, "ソースボイスにサブミット失敗", "", MB_OK );
		return false;
	}

	m_pSourceVoice[ index ]->Start( 0, XAUDIO2_COMMIT_NOW );

	return true;
}

//----------------------------------------------------
// サウンドの停止 
//----------------------------------------------------
inline boolean CXAudio2::Stop( CONST UINT index )
{
	if( !m_pSourceVoice[ index ] )
	{
		return false;
	}

	m_pSourceVoice[ index ]->Stop( 0, 0 );
	m_pSourceVoice[ index ]->FlushSourceBuffers();

	return true;
}

//----------------------------------------------------
// サウンドの一時停止
//----------------------------------------------------
inline boolean CXAudio2::Pause( CONST UINT index )
{
	if( !m_pSourceVoice[ index ] )
	{
		return false;
	}

	m_pSourceVoice[ index ]->Stop( 0, 0 );

	return true;
}

//----------------------------------------------------
// サウンドの音量変更 
//----------------------------------------------------
inline boolean CXAudio2::ChengeVolume( CONST UINT index, CONST FLOAT volume )
{
	m_pSourceVoice[ index ]->SetVolume( volume );

	return true;
}

//----------------------------------------------------
// サウンドにフェードをかけて停止する。毎ループ呼び出す。
//----------------------------------------------------
boolean CXAudio2::FadeStopManeger( CONST FLOAT volume )
{
	static float fadeVol = volume;
	for(int i=0; i<MAX_WAV; i++)
	{
		if(m_FadeFlag[ i ] == 1)
		{
			m_pSourceVoice[ i ]->GetVolume(&fadeVol);
			
			if(fadeVol <= 0.0f)
			{
				Stop( i );
				m_FadeFlag[ i ] = 0;
			}
			else
			{
				fadeVol -= 0.125f;	//ループごとに下げる音量
				if( fadeVol < 0.0f)
				{
					fadeVol = 0.0f;
				}
				m_pSourceVoice[ i ]->SetVolume( volume );
			}
		}
	}
	return true;
}

//----------------------------------------------------
// BGMの音量取得
//----------------------------------------------------
inline float CXAudio2::GetVolumeBGM( void )
{
	return m_volBGM;
}

//----------------------------------------------------
// SEの音量取得
//----------------------------------------------------
inline float CXAudio2::GetVolumeSE( void )
{
	return m_volSE;
}

//----------------------------------------------------
// BGMの音量をセット 
//----------------------------------------------------
inline float CXAudio2::SetVolumeBGM( FLOAT volume )
{
	m_volBGM = volume;
	return m_volBGM;
}

//----------------------------------------------------
// SEの音量をセット
//----------------------------------------------------
inline float CXAudio2::SetVolumeSE( FLOAT volume )
{
	m_volSE = volume;
	return m_volSE;
}

//----------------------------------------------------
// BGMのstep(倍率)をGetする
//----------------------------------------------------
inline int CXAudio2::GetStepBGM( void )
{
	return m_stepBGM;
}

//----------------------------------------------------
// SEのstep(倍率)をGetする 
//----------------------------------------------------
inline int CXAudio2::GetStepSE( void )
{
	return m_stepSE;
}

//----------------------------------------------------
// BGMのstep(倍率)をSetする
//----------------------------------------------------
inline int CXAudio2::SetStepBGM( int step )
{
	m_stepBGM = step;
	return m_stepBGM;
}

//----------------------------------------------------
// SEのstep(倍率)をSetする
//----------------------------------------------------
inline int CXAudio2::SetStepSE( int step )
{
	m_stepSE = step;
	return m_stepSE;
}

//----------------------------------------------------
// Fadeをかけて停止するサウンドの番号を指示する
//----------------------------------------------------
boolean CXAudio2::StopwithFade( CONST UINT index, int num )
{
	m_FadeFlag[ index ] = num;
	return true;
}
