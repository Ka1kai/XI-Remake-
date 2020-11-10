
#include "CDiceInfoManager.h"

const float ConstInfoXPos = 200.0f;
const float ConstInfoYPos = 70.0f;
const float ConstInfoXSize = 110.0f;
const float ConstInfoYSize = 110.0f;

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CDiceInfoManager::CDiceInfoManager( void )
{
	m_pInfo = new C2DSpriteRHW;
	m_pResInfoFilePath = GAME_DICEINFO_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pResInfoFilePath );

	m_pDiceInfo = new CDiceInfoObj;
	m_pResInfoDiceFilePath = DICE_XFILEPATH;
	CResourceManager::GetInstance()->LoadXFile( m_pResInfoDiceFilePath );
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
CDiceInfoManager::~CDiceInfoManager( void )
{
	SAFE_DELETE( m_pDiceInfo );
	SAFE_DELETE( m_pInfo );
}

//----------------------------------------------------
// ������
//----------------------------------------------------
bool CDiceInfoManager::Init( void )
{
	m_pInfo->SetVertexPos( ConstInfoXPos, ConstInfoYPos, ConstInfoXSize, ConstInfoYSize );

	m_pDiceInfo->Init();
	m_pDiceInfo->MoveWorldPos( -21.0f, 10.0f, 5.0f );

	return true;
}

//----------------------------------------------------
// �I��
//----------------------------------------------------
bool CDiceInfoManager::Uninit( void )
{

	return true;
}

//----------------------------------------------------
// �`�� 
//----------------------------------------------------
void CDiceInfoManager::Draw( void )
{
	// Info�̉摜
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture(  m_pResInfoFilePath )->Get(), m_pInfo->GetVertex() );

	// Info�p�̃_�C�X
	if( m_pDiceInfo->GetIsExist() == true )
	{
		CDirectDrawSystem::GetInstance()->Draw3D( CResourceManager::GetInstance()->GetXFile( m_pResInfoDiceFilePath ), m_pDiceInfo->GetWorldMtx() );
	}
}

//----------------------------------------------------
// �_�C�X�C���t�H�̃_�C�X�̃Z�b�g
//----------------------------------------------------
void CDiceInfoManager::SetInfoDice( CONST D3DXMATRIX* mainDiceWorldMtx )
{
	m_pDiceInfo->CopyRotationMtx( mainDiceWorldMtx );
}
