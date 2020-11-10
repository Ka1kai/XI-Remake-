
#include "../../KaiFrameWorkHeader/DirectX9Header/CXAudio2.h"


//----------------------------------------------------
// �R���X�g���N�^ 
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

	m_volBGM = 1.0f;	//BGM���ʂ̏����ݒ�
	m_volSE = 1.0f;		//SE���ʂ̏����ݒ�
	m_stepBGM = 4;
	m_stepSE = 4;
}

//----------------------------------------------------
// �f�X�g���N�^ 
//----------------------------------------------------
CXAudio2::~CXAudio2( void )
{
	for( int i = 0; i < MAX_WAV; ++i )
	{
		Stop( i );		// �Ƃ肠�����Ȃ��X�g�b�v

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
// ������
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
// Wav�f�[�^�̓ǂݍ���
//----------------------------------------------------
boolean CXAudio2::LoadWav( CONST UINT index, CONST LPSTR fileName )
{
	// ���łɃf�[�^�������Ă���Ƃ�
	if( m_pWavBuffer[ index ] )
	{
		return false;
	}

	// �͈͊O�̂Ƃ�
	if( index >= MAX_WAV || index < 0 )
	{
		return false;
	}

	HMMIO hMmio=NULL;			// Windows�}���`���f�B�AAPI�̃n���h��(Windows�}���`���f�B�AAPI��WAV�t�@�C���֌W�̑���p��API)
	DWORD dwWavSize=0;			// WAV�t�@�C�����@WAV�f�[�^�̃T�C�Y�iWAV�t�@�C����WAV�f�[�^�Ő�߂��Ă���̂ŁA�قڃt�@�C���T�C�Y�Ɠ���j
	WAVEFORMATEX* pwfex;		// WAV�̃t�H�[�}�b�g ��j16�r�b�g�A44100Hz�A�X�e���I�Ȃ�
	MMCKINFO ckInfo;			// �`�����N���
	MMCKINFO riffckInfo;		// �ŏ㕔�`�����N�iRIFF�`�����N�j�ۑ��p
	PCMWAVEFORMAT pcmWaveForm;

	//WAV�t�@�C�����̃w�b�_�[���i���f�[�^�ȊO�j�̊m�F�Ɠǂݍ���
	hMmio = mmioOpenA( fileName, NULL, MMIO_ALLOCBUF | MMIO_READ );

	//�t�@�C���|�C���^��RIFF�`�����N�̐擪�ɃZ�b�g����
	mmioDescend( hMmio, &riffckInfo, NULL, 0 );
	
	// �t�@�C���|�C���^��'f' 'm' 't' ' ' �`�����N�ɃZ�b�g����
	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	
	mmioDescend( hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK );
	
	//�t�H�[�}�b�g��ǂݍ���
	mmioRead( hMmio, ( HPSTR ) &pcmWaveForm, sizeof( pcmWaveForm ) );
	
	pwfex = ( WAVEFORMATEX* )new CHAR[ sizeof( WAVEFORMATEX ) ];
	
	memcpy( pwfex, &pcmWaveForm, sizeof( pcmWaveForm ) );
	pwfex->cbSize = 0;	
	mmioAscend( hMmio, &ckInfo, 0 );

	// WAV�t�@�C�����̉��f�[�^�̓ǂݍ���	
	ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend( hMmio, &ckInfo, &riffckInfo, MMIO_FINDCHUNK );//�f�[�^�`�����N�ɃZ�b�g
	dwWavSize = ckInfo.cksize;

	m_pWavBuffer[ index ] = new BYTE[ dwWavSize ];	// ���I�m��

	mmioRead( hMmio, ( HPSTR )m_pWavBuffer[ index ], dwWavSize );
	//�\�[�X�{�C�X�Ƀf�[�^���l�ߍ���	
	if( FAILED( m_pXAudio2->CreateSourceVoice( &m_pSourceVoice[ index ], pwfex ) ) )
	{
		MessageBox(0,"�\�[�X�{�C�X�쐬���s",0,MB_OK);
		delete[] pwfex;
		return false;
	}

	delete[] pwfex;

	m_dwWavSize[ index ] = dwWavSize;

	m_reserveNumber ++;

	return true;;
}

//----------------------------------------------------
// Wav�f�[�^�̉�� 
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
// �T�E���h�̍Đ� 
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

	//���[�v�̐ݒ�
	if( isLoop ){
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	}

	if( FAILED( m_pSourceVoice[ index ]->SubmitSourceBuffer( &buffer ) ) )
	{
		MessageBox( NULL, "�\�[�X�{�C�X�ɃT�u�~�b�g���s", "", MB_OK );
		return false;
	}

	m_pSourceVoice[ index ]->Start( 0, XAUDIO2_COMMIT_NOW );

	return true;
}

//----------------------------------------------------
// �T�E���h�̒�~ 
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
// �T�E���h�̈ꎞ��~
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
// �T�E���h�̉��ʕύX 
//----------------------------------------------------
inline boolean CXAudio2::ChengeVolume( CONST UINT index, CONST FLOAT volume )
{
	m_pSourceVoice[ index ]->SetVolume( volume );

	return true;
}

//----------------------------------------------------
// �T�E���h�Ƀt�F�[�h�������Ē�~����B�����[�v�Ăяo���B
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
				fadeVol -= 0.125f;	//���[�v���Ƃɉ����鉹��
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
// BGM�̉��ʎ擾
//----------------------------------------------------
inline float CXAudio2::GetVolumeBGM( void )
{
	return m_volBGM;
}

//----------------------------------------------------
// SE�̉��ʎ擾
//----------------------------------------------------
inline float CXAudio2::GetVolumeSE( void )
{
	return m_volSE;
}

//----------------------------------------------------
// BGM�̉��ʂ��Z�b�g 
//----------------------------------------------------
inline float CXAudio2::SetVolumeBGM( FLOAT volume )
{
	m_volBGM = volume;
	return m_volBGM;
}

//----------------------------------------------------
// SE�̉��ʂ��Z�b�g
//----------------------------------------------------
inline float CXAudio2::SetVolumeSE( FLOAT volume )
{
	m_volSE = volume;
	return m_volSE;
}

//----------------------------------------------------
// BGM��step(�{��)��Get����
//----------------------------------------------------
inline int CXAudio2::GetStepBGM( void )
{
	return m_stepBGM;
}

//----------------------------------------------------
// SE��step(�{��)��Get���� 
//----------------------------------------------------
inline int CXAudio2::GetStepSE( void )
{
	return m_stepSE;
}

//----------------------------------------------------
// BGM��step(�{��)��Set����
//----------------------------------------------------
inline int CXAudio2::SetStepBGM( int step )
{
	m_stepBGM = step;
	return m_stepBGM;
}

//----------------------------------------------------
// SE��step(�{��)��Set����
//----------------------------------------------------
inline int CXAudio2::SetStepSE( int step )
{
	m_stepSE = step;
	return m_stepSE;
}

//----------------------------------------------------
// Fade�������Ē�~����T�E���h�̔ԍ����w������
//----------------------------------------------------
boolean CXAudio2::StopwithFade( CONST UINT index, int num )
{
	m_FadeFlag[ index ] = num;
	return true;
}
