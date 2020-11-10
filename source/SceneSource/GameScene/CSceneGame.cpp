
#include "CSceneGame.h"


const int ConstGamePlayTime = 180;

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CSceneGame::CSceneGame( void )
{

}

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CSceneGame::CSceneGame( CSceneChange* change ) : CSceneBase( change ) 
{
}

//----------------------------------------------------
// ���[�h
//----------------------------------------------------
bool CSceneGame::Load( void )
{
	m_pDirectCamera	= new CDirectCamera;

	m_pDirectLight = new CDirectLight;

	// ���u�����h�̂��߂̔w�i�|���S��
	m_pBack = new C2DSpriteAlphaBlend;
	m_pTimeUP = new C2DSpriteRHW;
	m_pResTimeUpFilePath = TIMEUP_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResTimeUpFilePath );
	m_pPushEnter = new C2DSpriteRHW;
	m_pResPushEnterFilePath = TIMEUP_PUSHENTER_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResPushEnterFilePath );

	// Manager
	m_pGameStageManager = new CGameStageManager;
	m_pPauseManager = new CPauseManager;
	m_pTimeManager = new CTimeManager;
	m_pScoreManager = new CScoreManager;
	m_pDiceInfoManager = new CDiceInfoManager;
	m_pSnowObj = new CSnowObj;
	m_pSpaceParticle = new CSpaceParticle;

	// �^�C���A�b�v
	m_pTimeUP->SetVertexPos( 400.0f,280.0f,450.0f,180.0f );

	// PUSH ENTER
	m_pPushEnter->SetVertexPos( 600.0f,500.0f,256.0f,64.0f );

	CDiceObjManager::GetInstance()->SetDiceInfoManager( m_pDiceInfoManager );
	CPlayerManager::GetInstance()->SetDiceInfoManager( m_pDiceInfoManager );

#ifdef _DEBUG
	CDebugMode::Load();	// �f�o�b�O��ʂ̃��[�h
#endif

	return true;
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
CSceneGame::~CSceneGame( void )
{
	SAFE_DELETE( m_pDirectCamera );			// �J�����̉��
	SAFE_DELETE( m_pDirectLight );			// ���C�g�̉��
	SAFE_DELETE( m_pBack );					// ���u�����h�̂��߂̂���
	SAFE_DELETE( m_pTimeUP );				// �^�C���A�b�v
	SAFE_DELETE( m_pPushEnter );			// PUSH ENTER
	SAFE_DELETE( m_pGameStageManager );		// �w�i�̃}�l�[�W���[
	SAFE_DELETE( m_pTimeManager );			// �^�C���̃}�l�[�W���[
	SAFE_DELETE( m_pScoreManager );			// �X�R�A�̃}�l�[�W���[
	SAFE_DELETE( m_pDiceInfoManager );		// �_�C�XInfo�̃}�l�[�W���[
	SAFE_DELETE( m_pPauseManager );	//  �|�[�Y�{�^���̉��
	SAFE_DELETE( m_pSnowObj );				// ��
	SAFE_DELETE( m_pSpaceParticle );		// ��̃p�[�e�B�N��
}

//----------------------------------------------------
// ������
//----------------------------------------------------
void CSceneGame::Initialize( void )
{
	m_pDirectCamera->Init( 800, 640);
	m_pDirectCamera->SetPosition( 18.0f, 24.0f, -27.0f );
	m_pDirectCamera->SetAt( -2.0f, 0.0f,0.0f );

	m_pDirectLight->Switch( true );
	CPlayerManager::GetInstance()->BrightChange( true );	// �v���C���[�̐F�ύX
	m_pTimeManager->BrightChange( true );					// �^�C���̐F�ύX
	m_pScoreManager->BrightChange( true );					// �X�R�A�̐F�ύX
	m_pDiceInfoManager->BrightChange( true );				// INFO�̐F�ύX

	// �����̏�����
	CDiceRandSystem::GetInstance()->InitSeed();
	
	// �w�i�|���S��
	m_pBack->SetVertexPos( 400.0f,320.0f,800.0f,640.0f );
	m_pBack->SetDiffuse( 255,255,255,0 );


#ifdef _DEBUG
	CDebugMode::Init();
	CDebugMode::Set( m_pTimeManager->GetTime() );
#endif

	// Manager
	m_pGameStageManager->Init();
	CStageBlockManager::GetInstance()->Init();
	CStageBlockManager::GetInstance()->SetBlockPos();
	m_pPauseManager->Init();
	m_pTimeManager->Init( ConstGamePlayTime );
	m_pScoreManager->Init();
	m_pDiceInfoManager->Init();
	CPlayerManager::GetInstance()->Init();
	CPlayerManager::GetInstance()->SetCameraToMtx( m_pDirectCamera->GetView() );
	CDiceObjManager::GetInstance()->Init();

	// �`�F�C���̊Ǘ��N���X�ɃX�R�A�̃|�C���^���Z�b�g
	CChainManager::GetInstance()->SetScore( m_pScoreManager->GetScore() );

	m_eGamePlayStatus = GAMEPLAY_STATUS::GAME_PLAY;

}

//----------------------------------------------------
// �Q�[���V�[���̏I��
//----------------------------------------------------
void CSceneGame::Finalize( void )
{
}

//----------------------------------------------------
// �Q�[���V�[���̏���
//----------------------------------------------------
void CSceneGame::Run( void )
{
	// �f�o�C�X�̍X�V
	CInputKeyboard::GetInstance()->Update();
	CJoyStick::GetInstance()->Update();

	switch( m_eGamePlayStatus )
	{
		// �Q�[���v���C��
		case GAMEPLAY_STATUS::GAME_PLAY:
			CPlayerManager::GetInstance()->Run();
			m_pGameStageManager->Run();
			CDiceObjManager::GetInstance()->Run();
			m_pScoreManager->Run();
			m_pTimeManager->Run();
			this->ChangePause();		// �|�[�Y�؂�ւ�
			this->TimeUp();				// �^�C���A�b�v
			break;

		// �|�[�Y��
		case GAMEPLAY_STATUS::GAME_PAUSE:
			m_pPauseManager->Run();
			this->Pause();				// �|�[�Y��
			this->ChangePause();		// �|�[�Y�؂�ւ�
			break;

		// �^�C���A�b�v��
		case GAMEPLAY_STATUS::TIME_UP:
			if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_RETURN ) ||
				CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_A ) )
			{
				m_eGamePlayStatus = GAMEPLAY_STATUS::TIME_UP_FADE;
			}
			break;

		// �^�C���A�b�v�̃t�F�[�h
		case GAMEPLAY_STATUS::TIME_UP_FADE:
			this->TimeUpFade();
			break;

		// �|�[�Y�̃t�F�[�h
		case GAMEPLAY_STATUS::PAUSE_FADE:
			this->PauseFade();
			break;

#ifdef _DEBUG
		// �f�o�b�O���[�h��
		case GAMEPLAY_STATUS::DEBUG_MODE:
			CDebugMode::RunDebugMode();
			if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_F1 ) || CDebugMode::m_isDebugMode == false )
			{
				m_eGamePlayStatus = GAMEPLAY_STATUS::GAME_PLAY;
				return;
			}
			break;
#endif
	}

// �f�o�b�O���[�h�ɓ���
#ifdef _DEBUG
	CDebugMode::Run( m_pDirectCamera );
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_F1 ) && m_eGamePlayStatus != GAMEPLAY_STATUS::DEBUG_MODE )
	{
		CDebugMode::InitDebugMode();
		m_eGamePlayStatus = GAMEPLAY_STATUS::DEBUG_MODE;
	}

#endif
}

//----------------------------------------------------
// �`��
//----------------------------------------------------
void CSceneGame::Draw( void )
{
	m_pGameStageManager->Draw();	// �X�e�[�W

	// �_�C�X
	CDiceObjManager::GetInstance()->Draw( m_pDirectCamera->GetView() );

	// �v���C���[
	CPlayerManager::GetInstance()->Draw();

// �f�o�b�O���̂݃f�o�b�O���
#ifdef _DEBUG
	CDebugMode::Draw();
#endif

	switch( m_eGamePlayStatus )
	{
		// �Q�[���v���C��
		case GAMEPLAY_STATUS::GAME_PLAY:
			break;

		// �|�[�Y��
		case GAMEPLAY_STATUS::GAME_PAUSE:
			m_pPauseManager->Draw();
			break;

		// �|�[�Y�t�F�[�h��
		case GAMEPLAY_STATUS::PAUSE_FADE:
			m_pPauseManager->Draw();
			break;

		// �f�o�b�O��
#ifdef _DEBUG
		case GAMEPLAY_STATUS::DEBUG_MODE:
			CDebugMode::DrawDebugMode();
			break;
#endif 

		// �^�C���A�b�v��
		case GAMEPLAY_STATUS::TIME_UP:
			CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResTimeUpFilePath )->Get(), m_pTimeUP->GetVertex() );
//			CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResPushEnterFilePath )->Get() ,m_pPushEnter->GetVertex() );
			break;
	}
	m_pDiceInfoManager->Draw();	// Info
	m_pScoreManager->Draw();	// �X�R�A
	m_pTimeManager->Draw();		// �^�C��
		

	// �w�i�`��
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( NULL, m_pBack->GetVertex() );
}

//----------------------------------------------------
// �|�[�Y�؂�ւ�
//----------------------------------------------------
void CSceneGame::ChangePause( void )
{
	// ESCAPE�L�[�Ń|�[�Y�؂�ւ�
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_ESCAPE ) || 
		  CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_START ) )
	{
		bool isPause = false;

		// �|�[�Y�̃t���O���擾
		m_pPauseManager->SetIsPause();
		isPause = m_pPauseManager->GetIsPause();
	
		m_pDirectLight->Switch( !isPause );							// ���C�g�̃X�C�b�`�ύX
		CPlayerManager::GetInstance()->BrightChange( !isPause );	// �v���C���[�̐F�ύX
		m_pTimeManager->BrightChange( !isPause );					// �^�C���̐F�ύX
		m_pScoreManager->BrightChange( !isPause );					// �X�R�A�̐F�ύX
		m_pDiceInfoManager->BrightChange( !isPause );				// INFO�̐F�ύX

		if( m_eGamePlayStatus == GAMEPLAY_STATUS::GAME_PLAY )
		{
			m_pPauseManager->InitPause();
			m_eGamePlayStatus = GAMEPLAY_STATUS::GAME_PAUSE;
		}
		else if( m_eGamePlayStatus == GAMEPLAY_STATUS::GAME_PAUSE )
		{
			m_eGamePlayStatus = GAMEPLAY_STATUS::GAME_PLAY;
		}
	}
}

//----------------------------------------------------
// �|�[�Y
//----------------------------------------------------
void CSceneGame::Pause( void )
{
	// �|�[�Y����
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_RETURN ) || 
		CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_A  ) )
	{
		if( m_pPauseManager->GetPauseState() == ePauseStatus::RESUME )
		{
			bool isPause = false;

			m_pPauseManager->SetIsPause();
			isPause = m_pPauseManager->GetIsPause();
			m_pDirectLight->Switch( !isPause );							// ���C�g�̃X�C�b�`�ύX
			CPlayerManager::GetInstance()->BrightChange( !isPause );	// �v���C���[�̐F�ύX
			m_pTimeManager->BrightChange( !isPause );					// �^�C���̐F�ύX
			m_pScoreManager->BrightChange( !isPause );					// �X�R�A�̐F�ύX
			m_pDiceInfoManager->BrightChange( !isPause );				// INFO�̐F�ύX
			m_eGamePlayStatus = GAMEPLAY_STATUS::GAME_PLAY;
		}
		else 
		{
			// �t�F�[�h���ɐݒ肷��
			m_eGamePlayStatus = GAMEPLAY_STATUS::PAUSE_FADE;
		}
	}
}

//----------------------------------------------------
// �|�[�Y�̃t�F�[�h
//----------------------------------------------------
void CSceneGame::PauseFade( void )
{
	if( m_pBack->FadeOut( 3 ) )
	{
		// �t�F�[�h������̑J��
		switch( m_pPauseManager->GetPauseState() )
		{
		case RETRY:
			this->Initialize();
			break;

		case TITLE:
			mSceneChanger->ChangeScene( eSceneState::eSceneTitle );
			break;

		}		
	}
}

//----------------------------------------------------
// �^�C���A�b�v
//----------------------------------------------------
void CSceneGame::TimeUp( void )
{
	// �^�C���A�b�v����
	if( m_pTimeManager->TimeUP() == true )
	{
		m_pDirectLight->Switch( false );
		CPlayerManager::GetInstance()->BrightChange( false );	// �v���C���[�̐F�ύX
		m_pTimeManager->BrightChange( false );					// �^�C���̐F�ύX
		m_pScoreManager->BrightChange( false );					// �X�R�A�̐F�ύX
		m_pDiceInfoManager->BrightChange( false );				// INFO�̐F�ύX

		m_eGamePlayStatus = GAMEPLAY_STATUS::TIME_UP;
	}
}

//----------------------------------------------------
// �^�C���A�b�v�̃t�F�[�h
//----------------------------------------------------
void CSceneGame::TimeUpFade( void )
{
	if( m_pBack->FadeOut( 3 ) )
	{
		// �Q�[���̃X�R�A�����[�U�f�[�^�Ƃ��ĕۑ�
		CUserManager::GetInstance()->InitGameScore();
		CUserManager::GetInstance()->SetGameScore( m_pScoreManager->GetScore() );

		// �t�F�[�h���I�������V�[���؂�ւ�
		mSceneChanger->ChangeScene( eSceneState::eSceneResult );
	}
}