
#include "CModeSelectPlayerManager.h"

const float PLAYER_MOVE_DEFAULT = 0.2f;

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CModeSelectPlayerManager::CModeSelectPlayerManager( void )
{
	// �v���C���[�̃C���X�^���X��
	m_pModeSelectPlayer = new C2DSprite;
	m_pResModeSelectPlayerPath = PLAYER_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResModeSelectPlayerPath );
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
CModeSelectPlayerManager::~CModeSelectPlayerManager( void )
{
	SAFE_DELETE( m_pModeSelectPlayer );
}

//----------------------------------------------------
//������
//----------------------------------------------------
bool CModeSelectPlayerManager::Init( void )
{
	// �v���C���[�̏�����
	m_pModeSelectPlayer->Init();
	m_pModeSelectPlayer->CalcWorldMtx();
	m_pModeSelectPlayer->SetSpritePos( -1.0f, 2.0f, 2.0f );
	m_pModeSelectPlayer->SetSpriteSize( 5.0f, 5.0f );
	m_pModeSelectPlayer->SetUV( 4, 4, 1, 1 );

	m_eMovePlayerStatus = eModeSelectMovePlayerStatus::eModeSelectPlayerMoveNone;
	m_moveValue = 0.0f;

	return true;
}

//----------------------------------------------------
// �I��
//----------------------------------------------------
bool CModeSelectPlayerManager::Uninit( void )
{
	return true;
}

//----------------------------------------------------
// ����
//----------------------------------------------------
void CModeSelectPlayerManager::Run( void )
{
	
	switch( m_eMovePlayerStatus )
	{
	// �ʏ���
	case eModeSelectMovePlayerStatus::eModeSelectPlayerMoveNone:
		break;

	// ���ړ�
	case eModeSelectMovePlayerStatus::eModeSelectPlayerMoveLeft:
		this->MoveLeft( PLAYER_MOVE_DEFAULT );
		m_pModeSelectPlayer->SetUV( 4, 4, 1, 3 );
		break;

	// �E�ړ�
	case eModeSelectMovePlayerStatus::eModeSelectPlayerMoveRight:
		this->MoveRight( PLAYER_MOVE_DEFAULT );
		m_pModeSelectPlayer->SetUV( 4, 4, 1, 2 );
		break;

	// ��ړ�
	case eModeSelectMovePlayerStatus::eModeSelectPlayerMoveUp:
		this->MoveUp( PLAYER_MOVE_DEFAULT );
		m_pModeSelectPlayer->SetUV( 4, 4, 1, 4 );
		break;

	// ���ړ�
	case eModeSelectMovePlayerStatus::eModeSelectPlayerMoveDown:
		this->MoveDown( PLAYER_MOVE_DEFAULT );
		m_pModeSelectPlayer->SetUV( 4, 4, 1, 1 );
		break;

	}

}

//----------------------------------------------------
// �E�ړ�
//----------------------------------------------------
void CModeSelectPlayerManager::MoveRight( CONST float speed )
{
	m_pModeSelectPlayer->MoveSpritePos( speed, 0.0f,0.0f );
	m_moveValue += speed;
	if( m_moveValue >= 4.0f ) 
	{
		m_moveValue = 0.0f;
		m_eMovePlayerStatus = eModeSelectMovePlayerStatus::eModeSelectPlayerMoveNone;
	}
}

//----------------------------------------------------
// ���ړ�
//----------------------------------------------------
void CModeSelectPlayerManager::MoveLeft( CONST float speed )
{
	m_pModeSelectPlayer->MoveSpritePos( -speed, 0.0f,0.0f );
	m_moveValue -= speed;
	if( m_moveValue <= -4.0f ) 
	{
		m_moveValue = 0.0f;
		m_eMovePlayerStatus = eModeSelectMovePlayerStatus::eModeSelectPlayerMoveNone;
	}
}

//----------------------------------------------------
// ��ړ�
//----------------------------------------------------
void CModeSelectPlayerManager::MoveUp( CONST float speed )
{
	m_pModeSelectPlayer->MoveSpritePos( 0.0f, 0.0f, speed );
	m_moveValue += speed;
	if( m_moveValue >= 4.0f ) 
	{
		m_moveValue = 0.0f;
		m_eMovePlayerStatus = eModeSelectMovePlayerStatus::eModeSelectPlayerMoveNone;
	}
}

//----------------------------------------------------
// ���ړ�
//----------------------------------------------------
void CModeSelectPlayerManager::MoveDown( CONST float speed )
{
	m_pModeSelectPlayer->MoveSpritePos( 0.0f, 0.0f, -speed );
	m_moveValue -= speed;
	if( m_moveValue <= -4.0f ) 
	{
		m_moveValue = 0.0f;
		m_eMovePlayerStatus = eModeSelectMovePlayerStatus::eModeSelectPlayerMoveNone;
	}
}

//----------------------------------------------------
// �`��
//----------------------------------------------------
void CModeSelectPlayerManager::Draw( void )
{
	// �v���C���[�`��
	CDirectDrawSystem::GetInstance()->DrawSprite( CResourceManager::GetInstance()->GetTexture( m_pResModeSelectPlayerPath )->Get(), m_pModeSelectPlayer->GetVertex(), m_pModeSelectPlayer->GetWorldMtx() );
}