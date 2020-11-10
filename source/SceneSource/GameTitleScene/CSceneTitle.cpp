
#include "CSceneTitle.h"

//----------------------------------------------------
// �^�C�g���V�[���̃R���X�g���N�^
//----------------------------------------------------
CSceneTitle::CSceneTitle( CSceneChange* change) : CSceneBase(change) 
{	
}

//----------------------------------------------------
// ���[�h
//----------------------------------------------------
bool CSceneTitle::Load( void )
{
	m_pDirectCamera = new CDirectCamera();
	m_pDirectCamera->Init(800,640);

	m_pDirectLight = new CDirectLight();

	// Manager�N���X
	m_pTitleBackManager = new CTitleBackManager();

	// user�̃Z�b�g
	CUserManager::GetInstance()->Login();
	DEBUG::PrintfColor(DEBUG::H_RED,"���[�U���O�C��\n");

	return true;
}

//----------------------------------------------------
// �^�C�g���V�[���̃f�X�g���N�^
//----------------------------------------------------
CSceneTitle::~CSceneTitle( void )
{
	SAFE_DELETE( m_pDirectCamera );			// �J�����̉��
	SAFE_DELETE( m_pDirectLight );			// ���C�g�̉��
	SAFE_DELETE( m_pTitleBackManager );		// �w�i�̃}�l�[�W���[�N���X���	

}

//----------------------------------------------------
// �^�C�g����ʂ̏�����
//----------------------------------------------------
void CSceneTitle::Initialize( void )
{	
	// Manager
	m_pTitleBackManager->Init();
}

//----------------------------------------------------
// �^�C�g���V�[���̏���
//----------------------------------------------------
void CSceneTitle::Run( void )
{
	CInputKeyboard::GetInstance()->Update();
	CJoyStick::GetInstance()->Update();
	
	m_pTitleBackManager->Run();			// �w�i����

	this->Draw();	// �`��


	// �X�^�[�g�{�^���������ꂽ��Q�[���X�^�[�g
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_SPACE ) ||
		CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_START ) )
	{
		m_pTitleBackManager->SetIsFade( true );
	}
	
	if( m_pTitleBackManager->GetIsFade() )
	{
		if( m_pTitleBackManager->Fade() )
		{
			mSceneChanger->ChangeScene( eSceneState::eSceneModeSelect );
		}
	}

// �f�o�b�O�̎��̂�F1�L�[����������f�o�b�O��ʂɖ߂�
#ifdef _DEBUG
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_F1 ) )
	{
		mSceneChanger->ChangeScene( eSceneState::eSceneDebug );
	}
#endif
}

//----------------------------------------------------
// �^�C�g����ʂ̕`��
//----------------------------------------------------
void CSceneTitle::Draw( void )
{
	m_pTitleBackManager->Draw();			// �w�i�`��
}

//----------------------------------------------------
// �^�C�g���V�[���̏I��
//----------------------------------------------------
void CSceneTitle::Finalize()
{

}
