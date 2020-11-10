
#include "CSceneModeSelect.h"

//----------------------------------------------------
// �����Ȃ��R���X�g���N�^
//----------------------------------------------------
CSceneModeSelect::CSceneModeSelect( void )
{
}

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CSceneModeSelect::CSceneModeSelect( CSceneChange* change ) : CSceneBase( change )
{
}

//----------------------------------------------------
// ���[�h
//----------------------------------------------------
bool CSceneModeSelect::Load( void )
{
	// �J�����E���C�g���C���X�^���X��
	m_pDirectCamera = new CDirectCamera;
	m_pDirectLight = new CDirectLight;

	// �w�i�̃}�l�[�W���N���X����
	m_pModeSelectBackManager = new CModeSelectBackManager;

	// �v���C���̃}�l�[�W���N���X����
	m_pModeSelectPlayerManager = new CModeSelectPlayerManager;

	return true;
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
CSceneModeSelect::~CSceneModeSelect( void )
{
	SAFE_DELETE( m_pDirectCamera );
	SAFE_DELETE( m_pDirectLight );
	SAFE_DELETE( m_pModeSelectBackManager );
	SAFE_DELETE( m_pModeSelectPlayerManager );
}

//----------------------------------------------------
// ������
//----------------------------------------------------
void CSceneModeSelect::Initialize( void )
{
	m_pDirectCamera->Init( 800,600 );
	m_pDirectCamera->SetPosition( 5.0f, 20.0f, -10.0f );
	m_pDirectLight->Init();

	m_pModeSelectBackManager->Init();

	m_pModeSelectPlayerManager->Init();

	m_modeIndexNo = 1;
	m_eMode = modeAllay[ m_modeIndexNo ];

	m_isFade = false;
}

//----------------------------------------------------
// ����
//----------------------------------------------------
void CSceneModeSelect::Run( void )
{
	CInputKeyboard::GetInstance()->Update();
	CJoyStick::GetInstance()->Update();

	// �E�L�[����
	if( ( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_RIGHT ) || 
		CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_DPAD_RIGHT ) ) && 
		m_modeIndexNo < 3 &&
		m_pModeSelectBackManager->GetMessageBarStatus() == eMessageBarStatus::eMessageBarNormal )
	{	
		m_modeIndexNo ++;
		m_eMode = modeAllay[ m_modeIndexNo ];
		m_pModeSelectBackManager->RunKey( m_modeIndexNo );
		m_pModeSelectBackManager->SetMessageBarStatus( eMessageBarStatus::eMessageBarAnimation );
		m_pModeSelectPlayerManager->SetMovePlayerStatus( eModeSelectMovePlayerStatus::eModeSelectPlayerMoveRight );
	}
	
	// ���L�[����
	if( ( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_LEFT ) ||
		CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_DPAD_LEFT ) ) &&
		m_modeIndexNo > 0 && m_modeIndexNo < 4 &&
		m_pModeSelectBackManager->GetMessageBarStatus() == eMessageBarStatus::eMessageBarNormal) 
	{
		m_modeIndexNo --;
		m_eMode = modeAllay[ m_modeIndexNo ];
		m_pModeSelectBackManager->RunKey( m_modeIndexNo );
		m_pModeSelectBackManager->SetMessageBarStatus( eMessageBarStatus::eMessageBarAnimation );
		m_pModeSelectPlayerManager->SetMovePlayerStatus( eModeSelectMovePlayerStatus::eModeSelectPlayerMoveLeft );
	}

	// ��L�[����
	if( ( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_UP ) || 
		CJoyStick::GetInstance()->GetTriggerButton( 0 ,XINPUT_GAMEPAD_DPAD_UP ) ) &&
		( m_modeIndexNo == 1 || m_modeIndexNo == 5 ) &&
		m_pModeSelectBackManager->GetMessageBarStatus() == eMessageBarStatus::eMessageBarNormal)
	{
		if( m_modeIndexNo == 1 )
		{
			m_modeIndexNo = 4;
		}

		if( m_modeIndexNo == 5 )
		{
			m_modeIndexNo = 1;
		}
		m_eMode = modeAllay[ m_modeIndexNo ];
		m_pModeSelectBackManager->RunKey( m_modeIndexNo );
		m_pModeSelectBackManager->SetMessageBarStatus( eMessageBarStatus::eMessageBarAnimation );
		m_pModeSelectPlayerManager->SetMovePlayerStatus( eModeSelectMovePlayerStatus::eModeSelectPlayerMoveUp );
	}

	// ���L�[����
	if( ( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_DOWN ) ||
		CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_DPAD_DOWN ) ) &&
		( m_modeIndexNo == 1 || m_modeIndexNo == 4 ) &&
		m_pModeSelectBackManager->GetMessageBarStatus() == eMessageBarStatus::eMessageBarNormal)
	{
		if( m_modeIndexNo == 1 )
		{
			m_modeIndexNo = 5;
		}

		if( m_modeIndexNo == 4 )
		{
			m_modeIndexNo = 1;
		}
		m_eMode = modeAllay[ m_modeIndexNo ];
		m_pModeSelectBackManager->RunKey( m_modeIndexNo );
		m_pModeSelectBackManager->SetMessageBarStatus( eMessageBarStatus::eMessageBarAnimation );
		m_pModeSelectPlayerManager->SetMovePlayerStatus( eModeSelectMovePlayerStatus::eModeSelectPlayerMoveDown );
	}


	// �V�[���̐؂�ւ�
	if( ( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_SPACE ) ||
		CJoyStick::GetInstance()->GetTriggerButton( 0,XINPUT_GAMEPAD_A ) ) && 
		( m_eMode == eModeSelectState::eModeGamePlay ||
		m_eMode == eModeSelectState::eModeTitle ||
		m_eMode == eModeSelectState::eModeExit ||
		m_eMode == eModeSelectState::eModeRecord) )
	{
		m_isFade = true;
	}
	
	if( m_isFade == true )
	{
		// �t�F�[�h�A�E�g���I�������V�[����؂�ւ���
		if( m_pModeSelectBackManager->Fade() )
		{
			switch( m_eMode )
			{
			// �Q�[���v���C
			case eModeSelectState::eModeGamePlay:
				mSceneChanger->ChangeScene( eSceneState::eSceneGame );	// ���݂̓Q�[���̃V�[���ɑJ��
				break;
		
			// �^�C�g��
			case eModeSelectState::eModeTitle:
				mSceneChanger->ChangeScene( eSceneState::eSceneTitle );
				break;

			// �X�R�A
			case eModeRecord:
				mSceneChanger->ChangeScene( eSceneState::eSceneHighScore );
				break;

			// �I��
			case eModeSelectState::eModeExit:
			SendMessage( CWindowSystem::GethWnd(),WM_CLOSE,0,0 );
				break;

			default:
				break;
			}
		}		
	}

	// �w�i�p�}�l�[�W���[
	m_pModeSelectBackManager->Run();

	// �v���C���[�p�}�l�[�W���[
	m_pModeSelectPlayerManager->Run();


#ifdef _DEBUG
	// F1�L�[�Ńf�o�b�O�V�[���ɖ߂�
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_F1 ) )
	{
		mSceneChanger->ChangeScene( eSceneState::eSceneDebug );
	}
#endif
}

//----------------------------------------------------	
// �`��
//----------------------------------------------------
void CSceneModeSelect::Draw( void )
{
	m_pModeSelectBackManager->Draw();
	m_pModeSelectPlayerManager->Draw();
	m_pModeSelectBackManager->DrawAlpha();
}

//----------------------------------------------------
// �I��
//----------------------------------------------------
void CSceneModeSelect::Finalize( void )
{
	m_pModeSelectBackManager->Uninit();
	m_pModeSelectPlayerManager->Uninit();
}
