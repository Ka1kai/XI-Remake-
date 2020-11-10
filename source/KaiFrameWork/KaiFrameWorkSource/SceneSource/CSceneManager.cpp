
#include "../../KaiFrameWorkHeader/SceneHeader/CSceneManager.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CSceneManager::CSceneManager( eSceneState state )
{
//	m_pPthread = new CPthread();
	m_pScene = nullptr;

	m_nowScene  = eScene_None;
	m_nextScene = state;
	this->Update();
}

//----------------------------------------------------
// �����Ȃ��R���X�g���N�^
//----------------------------------------------------
CSceneManager::CSceneManager( void )
{
//	m_pPthread = new CPthread();

	m_pScene = nullptr;
	m_nextScene = eScene_None;
}

//----------------------------------------------------
// �f�X�g���N�^�@
//	���݂̃V�[���̃f�X�g���N�^���N��������
//----------------------------------------------------
CSceneManager::~CSceneManager()
{
	if( m_pScene != NULL )
	{
		m_pScene->Finalize();
		delete m_pScene;
		m_pScene = NULL;
	}

	// �X���b�h���I������Ă��Ȃ�������ҋ@
//	m_pPthread->Wait();

//	SAFE_DELETE( m_pPthread );
}

//----------------------------------------------------
// �X���b�h�̃��[�h
//----------------------------------------------------
void* CSceneManager::ThreadLoad( void* func )
{
	CSceneManager* sceneManager = (CSceneManager*)func;;
	
	sceneManager->Load();

	return 0;
}

//----------------------------------------------------
// ���[�h
//----------------------------------------------------
bool CSceneManager::Load( void )
{
	m_pScene->Load();
	m_pScene->Initialize();

	m_isLoad = true;

	return true;
}

//----------------------------------------------------
// ������
//----------------------------------------------------
void CSceneManager::Initialize( void )
{
    m_pScene->Initialize();
}

//----------------------------------------------------
// �I������
//----------------------------------------------------
void CSceneManager::Finalize()
{
	m_pScene->Finalize();
}

//----------------------------------------------------
// �V�[���؂�ւ�����
//----------------------------------------------------
void CSceneManager::Run( void )
{
	if( m_nextScene != m_nowScene )
	{    //���̃V�[�����Z�b�g����Ă�����
		if( m_pScene != NULL )
		{
			m_pScene->Finalize();	//���݂̃V�[���̏I�����������s
			m_isLoad = false;
			delete m_pScene;
		}

		this->Update();	// �V�[�����C���X�^���X��
	}

	if( m_isLoad == true )
	{
		m_pScene->Run(); //�V�[���̍X�V
	}
	else if( m_isLoad == false )
	{

	}
}

//----------------------------------------------------
// �V�[�����C���X�^���X��
//----------------------------------------------------
void CSceneManager::Update( void )
{
	//�V�[���ɂ���ď����𕪊�
    switch( m_nextScene )
	{       
		case eSceneState::eSceneGame:
			m_pScene = ( CSceneBase* ) new CSceneGame( this );
			break;
			
		case eSceneState::eSceneTitle:
			m_pScene = ( CSceneBase* ) new CSceneTitle( this );
			break;

		case eSceneState::eSceneModeSelect:
			m_pScene = ( CSceneBase* ) new CSceneModeSelect( this );
			break;

		case eSceneState::eSceneHighScore:
			m_pScene = ( CSceneBase* ) new CSceneScore( this );
			break;

		case eSceneState::eSceneModelView:
			m_pScene = ( CSceneBase* ) new CSceneModelView( this );
			break;

		case eSceneState::eSceneResult:
			m_pScene = ( CSceneBase* ) new CSceneResult( this );
			break;

		case eSceneState::eSceneDebug:
			m_pScene = ( CSceneBase* ) new CSceneDebug( this );
			break;

	}
    m_nextScene = eScene_None;		//���̃V�[�������N���A
	this->Load();
//	m_isLoad = false;
//	m_pPthread->Create( this->ThreadLoad, this );

}

//----------------------------------------------------
// �V�[�����Ƃɕ`��
//----------------------------------------------------
void CSceneManager::Draw( void )
{
	if( m_isLoad == true )
	{
		m_pScene->Draw(); //�V�[���̕`��
	}
	else if( m_isLoad == false )
	{
		// NowLoading�̕`��
		DrawLoading();
	}
}

//----------------------------------------------------
// ���̃V�[�����Z�b�g
//----------------------------------------------------
void CSceneManager::ChangeScene( eSceneState nextScene )
{
    m_nextScene = nextScene;    //���̃V�[�����Z�b�g����
}

//----------------------------------------------------
// NowLoading....
//----------------------------------------------------
void CSceneManager::DrawLoading( void )
{
}