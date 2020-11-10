
#include "CModeSelectBackManager.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CModeSelectBackManager::CModeSelectBackManager( void )
{
	// ���[�h�Z���N�g�̃X�e�[�W
	m_pModeSelectStage = new CObjectBase;
	m_pResModeSelectStageFilePath = MODE_STAGE_XFILEPATH;
	CResourceManager::GetInstance()->LoadXFile( m_pResModeSelectStageFilePath );

	// ���u�����h�p�摜
	m_pAlphaBlend = new C2DSpriteAlphaBlend;

	// ���j���[�̉摜
	m_pMenuValue = new C2DSpriteAlphaBlend;
	m_pResMenuValueFilePath = MODE_MENU_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResMenuValueFilePath );

	// ���b�Z�[�W�o�[
	m_pMessageBar = new CMessageBar;
	m_resIndexNo = 1;
	m_isBarAnimation = false;
	m_pResMessageBar[0] = MODE_TITLEMESSAGE_PNGPATH;
	m_pResMessageBar[1] = MODE_GAMEPLAYMESSAGE_PNGPATH;
	m_pResMessageBar[2] = MODE_OPTIONMESSAGE_PNGPATH;
	m_pResMessageBar[3] = MODE_EXITMESSAGE_PNGPATH;
	m_pResMessageBar[4] = MODE_RANKINGMESSAGE_PNGPATH;
	m_pResMessageBar[5] = MODE_RECORDMESSAGE_PNGPATH;

	for( int i = 0; i < 6; ++ i )
	{
		CResourceManager::GetInstance()->LoadTexture( m_pResMessageBar[i] );
	}
}

//----------------------------------------------------
// �f�X�g���N�^�@
//----------------------------------------------------
CModeSelectBackManager::~CModeSelectBackManager( void )
{
	SAFE_DELETE( m_pModeSelectStage );
	SAFE_DELETE( m_pAlphaBlend );
	SAFE_DELETE( m_pMenuValue );
	SAFE_DELETE( m_pMessageBar );
}

//----------------------------------------------------
// ������
//----------------------------------------------------
bool CModeSelectBackManager::Init( void )
{
	m_pModeSelectStage->Init();
	m_pModeSelectStage->SetWorldPos( -1.0f,0.0f, 2.0f );

	// ���u�����h�p�摜
	m_pAlphaBlend->SetVertexPos( 400.0f,320.0f,800.0f,640.0f );
	m_pAlphaBlend->SetDiffuse( 255,255,255,0 );

	// ���j���[�̉摜
	m_pMenuValue->Init();
	m_pMenuValue->SetVertexPos( 150.0f, 80.0f, 230.0f,120.0f );

	// ���b�Z�[�W�o�[
	m_pMessageBar->Init();
	m_pMessageBar->SetVertexPos( 550.0f,540.0f, 470.0f, 128.0f );
	m_eMessageBarStatus = eMessageBarStatus::eMessageBarNormal;

	return true;
}

//----------------------------------------------------
// ����
//----------------------------------------------------
void CModeSelectBackManager::Run( void )
{
	this->MessageBarAnimation();
}

//----------------------------------------------------
// �t�F�[�h�A�E�g����
//----------------------------------------------------
bool CModeSelectBackManager::Fade( void )
{
	if ( m_pAlphaBlend->FadeOut( 5 ) )
	{
		return true;
	}

	return false;
}

//----------------------------------------------------
// �L�[����
//----------------------------------------------------
void CModeSelectBackManager::RunKey( CONST UINT index )
{
	m_resIndexNo = index;	// �Y�����̔ԍ���Ή�������
	m_isBarAnimation = true;
}

//----------------------------------------------------
// �G���^�[�L�[����
//----------------------------------------------------
void CModeSelectBackManager::RunKeyEnter( void )
{
	m_isAlphaBlend  = true;
}

//----------------------------------------------------
// ���b�Z�[�W�o�[�̃A�j���[�V����
//----------------------------------------------------
bool CModeSelectBackManager::MessageBarAnimation( void )
{
	static bool isHide = false;

	// �A�j���[�V�����̃t���O��ON�ɂȂ�����
	if( m_isBarAnimation == true )
	{
		if( m_pMessageBar->RepositionRight( 1000.0f, 40.0f ) == true )
		{
			m_isBarAnimation = false;
			isHide = true;
		}
	}

	if( isHide == true )
	{
		if( m_pMessageBar->RepositionLeft( 550.0f, 40.0f ) == true )
		{
			isHide = false;
			// �A�j���[�V�������I�����
			m_eMessageBarStatus = eMessageBarStatus::eMessageBarNormal;
			return true;
		}
	}

	return false;
}

//----------------------------------------------------
// �`��
//----------------------------------------------------
void CModeSelectBackManager::Draw( void )
{
	CDirectDrawSystem::GetInstance()->Draw3D( CResourceManager::GetInstance()->GetXFile( m_pResModeSelectStageFilePath ), m_pModeSelectStage->GetWorldMtx() );

	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResMenuValueFilePath )->Get(), m_pMenuValue->GetVertex() );

	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pResMessageBar[m_resIndexNo] )->Get(), m_pMessageBar->GetVertex() );
}

//----------------------------------------------------
// ���u�����h�p�摜�̕`��
//----------------------------------------------------
void CModeSelectBackManager::DrawAlpha( void )
{
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( m_pAlphaBlend->GetVertex() );
}

//----------------------------------------------------
// �I��
//----------------------------------------------------
bool CModeSelectBackManager::Uninit( void )
{

	return true;
}