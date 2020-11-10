
#include "CDiceObjManager.h"

const float DICE_ROLL_SPEED = 5.0f;		// �T�C�R���̉�]���x(90�x�ω������邽��90�ɂȂ�悤��)
const int  START_DICE_NUM = 10;			// �����̃T�C�R���̐� 
const int  MIN_DICE_NUM = 10;			// �X�e�[�W���̍Œ�_�C�X���i����ȏ㏭�Ȃ��Ȃ����狭���I�ɏo��������j
const int DICE_APPER_TIME = 90;			// ���̎��ԂŃ_�C�X�̏o��^�C�~���O���Ǘ�
const int DICE_APPER = 70;

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CDiceObjManager::CDiceObjManager( void )
{
	m_pDice = new CDiceObj[MAX_DICE_NUM];		// �T�C�R���̍ő吔����ɐ���
	m_pResDiceFilePath = DICE_XFILEPATH;
	CResourceManager::GetInstance()->LoadXFile( m_pResDiceFilePath );

	m_pMainDice = new TMAINDICE;				// ���C���̃T�C�R���̍\���̂��C���X�^���X��

	m_pSplitParticle = new CSplitParticle;		// �p�[�e�B�N��

	m_pDiceInfoManager = nullptr;
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
CDiceObjManager::~CDiceObjManager( void )
{
	SAFE_DELETE( m_pMainDice );

	SAFE_DELETE_ALLAY( m_pDice );
	SAFE_DELETE( m_pSplitParticle );
}

//----------------------------------------------------
// �`��
//----------------------------------------------------
void CDiceObjManager::Draw( CONST D3DXMATRIX* view )
{
	// �J�����O���[�h
	CDirectDrawSystem::GetInstance()->SetCallMode( true );
	
	for( int i = 0; i < MAX_DICE_NUM; ++ i )
	{
		if( m_pDice[i].GetIsDice() == true )
		{
			CDirectDrawSystem::GetInstance()->Draw3D( CResourceManager::GetInstance()->GetXFile( m_pResDiceFilePath ),m_pDice[i].GetWorldMtx(), m_pDice[i].GetColor() );
		}
	}

	// �p�[�e�B�N��
//	m_pSplitParticle->Draw( view );

}

//----------------------------------------------------
// ������
//----------------------------------------------------
void CDiceObjManager::Init( void )
{
	// �_�C�X�̃��b�V���f�[�^�擾
	TMESHDATA meshData;
	::ZeroMemory( &meshData, sizeof( TMESHDATA ) );
	CCollision::GetInstance()->GetMeshData( &meshData, CResourceManager::GetInstance()->GetXFile( DICE_XFILEPATH )->GetMesh() );

	// ��ɑS�ẴT�C�R����������
	for( int i = 0; i < MAX_DICE_NUM; ++ i )
	{
		m_pDice[i].Init();
		m_pDice[i].SetSize( &meshData.size );
	}

	// �����蔻��pAABB���쐬
	CDebugMode::m_pDiceBox[0].diceBox.CreateBox( m_pDice[0].GetSize() );
	CDebugMode::m_pDiceBox[0].diceBox.InitWorldMtx();
	CDebugMode::m_pDiceBox[0].diceBox.SetDiffuse( 0, 0, 0, 200 );
	CDebugMode::m_pDiceBox[0].diceBox.SetAmbient( 255, 0, 0, 255 );
	CDebugMode::m_pDiceBox[0].isDice = true;

	// ���C���̃T�C�R���̐ݒ�
	m_pMainDice->diceObj = &m_pDice[0];
	m_pDice[0].SetIsDice( true );

	// �����蔻��pAABB���쐬
	m_pDice[0].SetAABB();
	
	// �u���b�N�̏ꏊ�ԍ��擾
	UINT index = CStageBlockManager::GetInstance()->GetIndexToDicePos( m_pDice[0].GetXPos(), m_pDice[0].GetZPos() );
	m_pMainDice->diceObj->SetIndexNo( index );
	CStageBlockManager::GetInstance()->SetIsOnDice( index, true );
	m_pMainDice->rollState = eDiceRollState::DICE_ROLLSTATE_NONE;
	m_pMainDice->degree = 0.0f;
	m_pMainDice->diceObj->SetNo( 0 );
	m_pMainDice->diceObj->SetStatus( DICE_STATUS::e_statusNormal );
	m_pMainDice->halfSize = D3DXVECTOR3( m_pDice[0].GetSize()->x / 2, m_pDice[0].GetSize()->y / 2, m_pDice[0].GetSize()->z / 2);

	// �X�e�[�W�Ƀ��C���_�C�X�̏����Z�b�g
	CStageBlockManager::GetInstance()->SetBlockToDiceInfo( m_pMainDice->diceObj, m_pMainDice->diceObj->GetIndexNo() );

	// �C���t�H���Ƀ��C���_�C�X�̏����Z�b�g
	m_pDiceInfoManager->SetInfoDice( m_pMainDice->diceObj->GetWorldMtx() );
	
	m_diceNum = 1;
	m_appearTime = 0;

	// �X�e�[�W�ɏ����̃_�C�X���Z�b�g
	for( int i = 0; i < START_DICE_NUM; ++ i )
	{
		this->Appear();
	}

}

//----------------------------------------------------
// �I��
//----------------------------------------------------
void CDiceObjManager::Uninit( void )
{
}

//----------------------------------------------------
// ����
//----------------------------------------------------
void CDiceObjManager::Run()
{
	// �f�o�b�O
	this->Debug();	

	// �o���Ǘ�
	this->AppearManager();

	// �ړ���]
	this->MoveToRoll();


	// �_�C�X�̃A�j���[�V��������
	this->Animation();

	// �p�[�e�B�N������
	m_pSplitParticle->Move();
}

//----------------------------------------------------
// �f�o�b�O
//----------------------------------------------------
void CDiceObjManager::Debug( void )
{
#ifdef _DEBUG
	// �ړ�
	if( ( CInputKeyboard::GetInstance()->GetPressKeyState( VK_D ) ||
		CInputKeyboard::GetInstance()->GetPressKeyState( VK_A ) ||
		CInputKeyboard::GetInstance()->GetPressKeyState( VK_W ) ||
		CInputKeyboard::GetInstance()->GetPressKeyState( VK_S ) )  &&
		m_pMainDice->rollState == eDiceRollState::DICE_ROLLSTATE_NONE )
	{
		m_pMainDice->degree = 0.0f;
		m_pMainDice->diceObj->InitRoll();
		this->Move();
	}
#endif

	// �T�C�R���o��
	if( ( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_SPACE ) || 
		  CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_X ) ) 
		  && m_pMainDice->rollState == eDiceRollState::DICE_ROLLSTATE_NONE )
	{
		this->Appear();
	}

#ifdef _DEBUG
	// ���������������Ă���T�C�R����ύX����
	if( ( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_TAB ) ||
		CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_Y ) ) && m_pMainDice->rollState == eDiceRollState::DICE_ROLLSTATE_NONE )
	{
		for( int i = 0; i < MAX_DICE_NUM; ++ i )
		{
			if( m_pDice[i].GetIsDice() == true && m_pDice[i].GetStatus() == DICE_STATUS::e_statusNormal && &m_pDice[i] != m_pMainDice->diceObj )
			{
				m_pMainDice->diceObj = (&m_pDice[i]);		// ���C���̃_�C�X��ς���
				m_pMainDice->diceObj->SetIndexNo(m_pDice[i].GetIndexNo());
				m_pMainDice->halfSize = D3DXVECTOR3( m_pDice[i].GetSize()->x / 2, m_pDice[i].GetSize()->y / 2, m_pDice[i].GetSize()->z / 2 );
				break;
			}
		}
	}
#endif 

}

//----------------------------------------------------
// �ړ��̑J��
//----------------------------------------------------
void CDiceObjManager::Move( void )
{
	// �E�ړ�
	if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_D ) ||
		CJoyStick::GetInstance()->GetPressButton( 0, XINPUT_GAMEPAD_DPAD_RIGHT ))
	{
		this->MoveRight();
	}

	// ���ړ�
	else if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_A ) ||
		CJoyStick::GetInstance()->GetPressButton( 0, XINPUT_GAMEPAD_DPAD_LEFT ))
	{
		this->MoveLeft();
	}
	 
	// �O�i
	else if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_W ) ||
		CJoyStick::GetInstance()->GetPressButton( 0, XINPUT_GAMEPAD_DPAD_UP ))
	{
		this->MoveFront();
	}

	// ��i
	else if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_S ) ||
		CJoyStick::GetInstance()->GetPressButton( 0, XINPUT_GAMEPAD_DPAD_DOWN ))
	{
		this->MoveBack();
	}
}

//----------------------------------------------------
// �E�ړ�
//----------------------------------------------------
void CDiceObjManager::MoveRight( void )
{
	// �X�e�[�W�̉E�ɒB���Ă��Ȃ���
	if( m_pMainDice->diceObj->GetWorldMtx()->_41 < CStageBlockManager::GetInstance()->GetXSize() )
	{
		// �E�Ƀu���b�N���Ȃ�������
		if( CStageBlockManager::GetInstance()->GetIsOnDice( m_pMainDice->diceObj->GetIndexNo() + 1 ) == true &&
			CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() + 1 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
		{
			// �E�Ƀu���b�N������ꍇ�̓��C���̃_�C�X��ւ���
			m_pMainDice->diceObj = CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() + 1 )->GetDice();
			m_pMainDice->diceObj->SetIndexNo( m_pMainDice->diceObj->GetIndexNo() );
			m_pDiceInfoManager->SetInfoDice( m_pMainDice->diceObj->GetWorldMtx() );

			return;
		}

		// �E�̃_�C�X���������C�o�����n�ߒ���������O�̃_�C�X�������Ĉړ�������
		else if( CStageBlockManager::GetInstance()->GetIsOnDice( m_pMainDice->diceObj->GetIndexNo() + 1 ) == true &&
			   ( CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() + 1 )->GetDice()->GetStatus() ==DICE_STATUS::e_statusDelete ||
				 CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() + 1 )->GetDice()->GetStatus() ==DICE_STATUS::e_statusStartAppear ) )
		{
			CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() + 1 )->GetDice()->SetStatus( DICE_STATUS::e_statusNone );
			CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() + 1 )->GetDice()->SetBeforStatus( DICE_STATUS::e_statusDelete );
			CStageBlockManager::GetInstance()->GetStageBlock(  m_pMainDice->diceObj->GetIndexNo() + 1 )->GetDice()->SetIsDice( false );
			CStageBlockManager::GetInstance()->GetStageBlock(  m_pMainDice->diceObj->GetIndexNo() + 1 )->GetDice()->SetIsChain( false );
			CChainManager::GetInstance()->GetChain( CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() + 1 )->GetDice()->GetChainNo() )->chainDiceNum --;		
			if( CChainManager::GetInstance()->GetChain( CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() + 1 )->GetDice()->GetChainNo() )->chainDiceNum == 0 )
			{
				CChainManager::GetInstance()->GetChain( CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() + 1 )->GetDice()->GetChainNo() )->isChain = false;
			}	
		}
		m_pMainDice->degree = 0.0f;
		m_pMainDice->diceObj->InitRoll();

		UINT index = CStageBlockManager::GetInstance()->GetIndexToDicePos( m_pMainDice->diceObj->GetWorldMtx()->_41,
																			m_pMainDice->diceObj->GetWorldMtx()->_43 );
		CStageBlockManager::GetInstance()->SetIsOnDice( index, false );

		m_pMainDice->rollState = DICE_ROLLSTATE_RIGHT;
		m_pMainDice->diceObj->RollChangePip( m_pMainDice->rollState );
	}
}

//----------------------------------------------------
// ���ړ�
//----------------------------------------------------
void CDiceObjManager::MoveLeft( void )
{
	// �X�e�[�W�̍��ɒB���Ă��Ȃ����𔻒�
	if( m_pMainDice->diceObj->GetWorldMtx()->_41 > -CStageBlockManager::GetInstance()->GetXSize() )
	{
		if( CStageBlockManager::GetInstance()->GetIsOnDice( m_pMainDice->diceObj->GetIndexNo() - 1 ) == true &&
			CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() - 1 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal)
		{
			// ���Ƀu���b�N������ꍇ�̓��C���̃_�C�X��ւ���
			m_pMainDice->diceObj = CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() - 1 )->GetDice();
			m_pMainDice->diceObj->SetIndexNo(m_pMainDice->diceObj->GetIndexNo());
			m_pDiceInfoManager->SetInfoDice( m_pMainDice->diceObj->GetWorldMtx() );

			return;
		}

		// �O�̃_�C�X���������C�o�����n�ߒ���������O�̃_�C�X�������Ĉړ�������
		else if( CStageBlockManager::GetInstance()->GetIsOnDice( m_pMainDice->diceObj->GetIndexNo() - 1 ) == true &&
			   ( CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() - 1 )->GetDice()->GetStatus() ==DICE_STATUS::e_statusDelete ||
				 CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() - 1 )->GetDice()->GetStatus() ==DICE_STATUS::e_statusStartAppear ) )
		{
			CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() - 1 )->GetDice()->SetStatus( DICE_STATUS::e_statusNone );
			CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() - 1 )->GetDice()->SetBeforStatus( DICE_STATUS::e_statusDelete );
			CStageBlockManager::GetInstance()->GetStageBlock(  m_pMainDice->diceObj->GetIndexNo() - 1 )->GetDice()->SetIsDice( false );
			CStageBlockManager::GetInstance()->GetStageBlock(  m_pMainDice->diceObj->GetIndexNo() - 1 )->GetDice()->SetIsChain( false );
			CChainManager::GetInstance()->GetChain( CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() - 1 )->GetDice()->GetChainNo() )->chainDiceNum --;		
			if( CChainManager::GetInstance()->GetChain( CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() - 1 )->GetDice()->GetChainNo() )->chainDiceNum == 0 )
			{
				CChainManager::GetInstance()->GetChain( CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() - 1 )->GetDice()->GetChainNo() )->isChain = false;
			}	
		}
		m_pMainDice->degree = 0.0f;
		m_pMainDice->diceObj->InitRoll();

		UINT index = CStageBlockManager::GetInstance()->GetIndexToDicePos( m_pMainDice->diceObj->GetWorldMtx()->_41,
																			m_pMainDice->diceObj->GetWorldMtx()->_43 );
		CStageBlockManager::GetInstance()->SetIsOnDice( index, false );
		m_pMainDice->rollState = DICE_ROLLSTATE_LEFT;
		m_pMainDice->diceObj->RollChangePip( m_pMainDice->rollState );
	}
}

//----------------------------------------------------
// �O�ړ�
//----------------------------------------------------
void CDiceObjManager::MoveFront( void )
{
	// �X�e�[�W�̑O�ɒB���Ă��Ȃ���
	if( m_pMainDice->diceObj->GetWorldMtx()->_43 < CStageBlockManager::GetInstance()->GetXSize() )
	{
		if( CStageBlockManager::GetInstance()->GetIsOnDice( m_pMainDice->diceObj->GetIndexNo() - CStageBlockManager::GetInstance()->GetZNum() ) == true &&
			CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() - CStageBlockManager::GetInstance()->GetZNum()  )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
		{
			// �O�Ƀu���b�N������ꍇ�̓��C���̃_�C�X��ւ���
			m_pMainDice->diceObj = CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() - CStageBlockManager::GetInstance()->GetZNum() )->GetDice();
			m_pMainDice->diceObj->SetIndexNo(m_pMainDice->diceObj->GetIndexNo());
			m_pDiceInfoManager->SetInfoDice( m_pMainDice->diceObj->GetWorldMtx() );

			return;
		}
			
		// �O�̃_�C�X���������C�o�����n�ߒ���������O�̃_�C�X�������Ĉړ�������
		else if( CStageBlockManager::GetInstance()->GetIsOnDice( m_pMainDice->diceObj->GetIndexNo() - CStageBlockManager::GetInstance()->GetZNum() ) == true &&
			   ( CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() - CStageBlockManager::GetInstance()->GetZNum() )->GetDice()->GetStatus() ==DICE_STATUS::e_statusDelete ||
				 CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() - CStageBlockManager::GetInstance()->GetZNum() )->GetDice()->GetStatus() ==DICE_STATUS::e_statusStartAppear ) )
		{
			CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() - CStageBlockManager::GetInstance()->GetZNum() )->GetDice()->SetStatus( DICE_STATUS::e_statusNone );
			CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() - CStageBlockManager::GetInstance()->GetZNum() )->GetDice()->SetBeforStatus( DICE_STATUS::e_statusDelete );
			CStageBlockManager::GetInstance()->GetStageBlock(  m_pMainDice->diceObj->GetIndexNo() - CStageBlockManager::GetInstance()->GetZNum() )->GetDice()->SetIsDice( false );
			CStageBlockManager::GetInstance()->GetStageBlock(  m_pMainDice->diceObj->GetIndexNo() - CStageBlockManager::GetInstance()->GetZNum() )->GetDice()->SetIsChain( false );
			if( CChainManager::GetInstance()->GetChain( CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() - CStageBlockManager::GetInstance()->GetZNum() )->GetDice()->GetChainNo() )->chainDiceNum == 0 )
			{
				CChainManager::GetInstance()->GetChain( CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() - CStageBlockManager::GetInstance()->GetZNum() )->GetDice()->GetChainNo() )->isChain = false;
			}	

		}
		// ��]�ړ�
		m_pMainDice->degree = 0.0f;
		m_pMainDice->diceObj->InitRoll();

		UINT index = CStageBlockManager::GetInstance()->GetIndexToDicePos( m_pMainDice->diceObj->GetWorldMtx()->_41,
																			m_pMainDice->diceObj->GetWorldMtx()->_43 );
		CStageBlockManager::GetInstance()->SetIsOnDice( index, false );
		m_pMainDice->rollState = DICE_ROLLSTATE_FRONT;
		m_pMainDice->diceObj->RollChangePip( m_pMainDice->rollState );
	}
}

//----------------------------------------------------
// ��ړ�
//----------------------------------------------------
void CDiceObjManager::MoveBack( void )
{
	// �X�e�[�W�̌��ɒB���Ă��Ȃ����𔻒�
	if( m_pMainDice->diceObj->GetWorldMtx()->_43 > -CStageBlockManager::GetInstance()->GetZSize() )
	{
		if( CStageBlockManager::GetInstance()->GetIsOnDice( m_pMainDice->diceObj->GetIndexNo() + CStageBlockManager::GetInstance()->GetZNum() ) == true &&
			CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() + CStageBlockManager::GetInstance()->GetZNum()  )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
		{
			// ���Ƀu���b�N������ꍇ�̓��C���̃_�C�X��ւ���
			m_pMainDice->diceObj = CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() + CStageBlockManager::GetInstance()->GetZNum() )->GetDice();
			m_pMainDice->diceObj->SetIndexNo(m_pMainDice->diceObj->GetIndexNo());
			m_pDiceInfoManager->SetInfoDice( m_pMainDice->diceObj->GetWorldMtx() );

			return;
		}
		// ���̃_�C�X���������C�o�����n�ߒ���������O�̃_�C�X�������Ĉړ�������
		else if( CStageBlockManager::GetInstance()->GetIsOnDice( m_pMainDice->diceObj->GetIndexNo() + CStageBlockManager::GetInstance()->GetZNum() ) == true &&
			   ( CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() + CStageBlockManager::GetInstance()->GetZNum() )->GetDice()->GetStatus() ==DICE_STATUS::e_statusDelete ||
				 CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() + CStageBlockManager::GetInstance()->GetZNum() )->GetDice()->GetStatus() ==DICE_STATUS::e_statusStartAppear ) )
		{
			CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() + CStageBlockManager::GetInstance()->GetZNum() )->GetDice()->SetStatus( DICE_STATUS::e_statusNone );
			CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() + CStageBlockManager::GetInstance()->GetZNum() )->GetDice()->SetBeforStatus( DICE_STATUS::e_statusDelete );
			CStageBlockManager::GetInstance()->GetStageBlock(  m_pMainDice->diceObj->GetIndexNo() + CStageBlockManager::GetInstance()->GetZNum() )->GetDice()->SetIsDice( false );
			CStageBlockManager::GetInstance()->GetStageBlock(  m_pMainDice->diceObj->GetIndexNo() + CStageBlockManager::GetInstance()->GetZNum() )->GetDice()->SetIsChain( false );
			CChainManager::GetInstance()->GetChain( CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() + CStageBlockManager::GetInstance()->GetZNum() )->GetDice()->GetChainNo() )->chainDiceNum --;		
			if( CChainManager::GetInstance()->GetChain( CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() + CStageBlockManager::GetInstance()->GetZNum() )->GetDice()->GetChainNo() )->chainDiceNum == 0 )
			{
				CChainManager::GetInstance()->GetChain( CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() + CStageBlockManager::GetInstance()->GetZNum() )->GetDice()->GetChainNo() )->isChain = false;
			}		
		}
		m_pMainDice->degree = 0.0f;
		m_pMainDice->diceObj->InitRoll();

		UINT index = CStageBlockManager::GetInstance()->GetIndexToDicePos( m_pMainDice->diceObj->GetWorldMtx()->_41,
																			m_pMainDice->diceObj->GetWorldMtx()->_43 );
		CStageBlockManager::GetInstance()->SetIsOnDice( index, false );
		m_pMainDice->rollState = DICE_ROLLSTATE_BACK;
		m_pMainDice->diceObj->RollChangePip( m_pMainDice->rollState );
	}
}

//----------------------------------------------------
// �ړ��{��]
//----------------------------------------------------
void CDiceObjManager::MoveToRoll( void )
{
	switch( m_pMainDice->rollState )
	{
		case DICE_ROLLSTATE_RIGHT:
			m_pMainDice->degree += DICE_ROLL_SPEED;
			m_pMainDice->diceObj->MoveX( -m_pMainDice->halfSize.x, m_pMainDice->halfSize.y, 0.0f, -1.0f,m_pMainDice->degree );
			m_pMainDice->diceObj->SetAABB();
			// �����蔻��pAABB�̈ʒu���X�V
			CDebugMode::m_pDiceBox[m_pMainDice->diceObj->GetNo()].diceBox.SetWorldPos( m_pMainDice->diceObj->GetWorldMtx () );
	
			break;

		case DICE_ROLLSTATE_LEFT:
			m_pMainDice->degree += DICE_ROLL_SPEED;
			m_pMainDice->diceObj->MoveX( m_pMainDice->halfSize.x, m_pMainDice->halfSize.y, 0.0f, 1.0f, m_pMainDice->degree );
			m_pMainDice->diceObj->SetAABB();
			// �����蔻��pAABB�̈ʒu���X�V
			CDebugMode::m_pDiceBox[m_pMainDice->diceObj->GetNo()].diceBox.SetWorldPos( m_pMainDice->diceObj->GetWorldMtx () );

			break;

		case DICE_ROLLSTATE_FRONT:
			m_pMainDice->degree += DICE_ROLL_SPEED;
			m_pMainDice->diceObj->MoveZ( 0.0f, m_pMainDice->halfSize.x, -m_pMainDice->halfSize.y , 1.0f, m_pMainDice->degree );
			m_pMainDice->diceObj->SetAABB();
			// �����蔻��pAABB�̈ʒu���X�V
			CDebugMode::m_pDiceBox[m_pMainDice->diceObj->GetNo()].diceBox.SetWorldPos( m_pMainDice->diceObj->GetWorldMtx () );

			break;

		case DICE_ROLLSTATE_BACK:
			m_pMainDice->degree += DICE_ROLL_SPEED;
			m_pMainDice->diceObj->MoveZ( 0.0f, m_pMainDice->halfSize.x, m_pMainDice->halfSize.y , -1.0f, m_pMainDice->degree );			
			m_pMainDice->diceObj->SetAABB();
			// �����蔻��pAABB�̈ʒu���X�V
			CDebugMode::m_pDiceBox[m_pMainDice->diceObj->GetNo()].diceBox.SetWorldPos( m_pMainDice->diceObj->GetWorldMtx () );
	
			break;

		case DICE_ROLLSTATE_NONE:
			break;

	}

	// �p�x��90�x( 1�}�X���ړ������� )
	if( m_pMainDice->degree == 90 && m_pMainDice->rollState != DICE_ROLLSTATE_NONE )
	{
		m_pMainDice->rollState = DICE_ROLLSTATE_NONE;
		UINT index = CStageBlockManager::GetInstance()->GetIndexToDicePos( m_pMainDice->diceObj->GetWorldMtx()->_41, 
							   	 										   m_pMainDice->diceObj->GetWorldMtx()->_43 );
		m_pMainDice->diceObj->SetIndexNo( index );
		CStageBlockManager::GetInstance()->SetBlockToDiceInfo( m_pMainDice->diceObj, m_pMainDice->diceObj->GetIndexNo() );

		// �_�C�X��INFO����ύX
		m_pDiceInfoManager->SetInfoDice( m_pMainDice->diceObj->GetWorldMtx() );

		// �G�~�b�^�[
		m_pSplitParticle->Emitter( m_pMainDice->diceObj->GetXPos(), m_pMainDice->diceObj->GetYPos() - 2.0f, m_pMainDice->diceObj->GetZPos() );

		// ����
		CChainManager::GetInstance()->Chain( m_pMainDice->diceObj->GetIndexNo() );
	}

}

//----------------------------------------------------
// �_�C�X�o���Ǘ�
//----------------------------------------------------
void CDiceObjManager::AppearManager( void )
{
	// �Ǘ��p�ϐ��Ɏ��Ԃ𑫂�
	m_appearTime ++;

	// �X�e�[�W����ǂꂾ�������Ă��Ƃ肠���Œᐔ���͏o��������
	if( m_diceNum <= MIN_DICE_NUM )
	{
		this->Appear();
	}

	if( m_appearTime >= DICE_APPER_TIME )
	{
		_int64 ran = CXorShift::GetInstance()->GetRandom( 0 , 100 );
		if( ran >= DICE_APPER )
		{
			this->Appear();
			m_appearTime = 0;
		}
	}

}

//----------------------------------------------------
// �_�C�X�̏o��
//----------------------------------------------------
bool CDiceObjManager::Appear( void )
{
	// �o�����Ă��Ȃ��_�C�X�𔻒�
	UINT notAppearNo = 0;
	for( int i = 0; i < MAX_DICE_NUM; ++ i )
	{
  		if ( m_pDice[i].GetIsDice() == false )
		{
			notAppearNo = i;
			break;
		}

		// �S�����܂��Ă���ꍇ�͐����ł��Ȃ�(���ʂ̓Q�[���I�[�o�����C�Ƃ肠�����G���[��h�����߂Ɏ����j
		if( i == MAX_DICE_NUM )
		{
			return false;
		}
	}

	//�@�����_���Ƀu���b�N�̓Y�������擾
	UINT blockIndex = CStageBlockManager::GetInstance()->GetBlockIndexRnd();

	// �u���b�N���܂���������Ă��Ȃ����ǂ���
	if( CStageBlockManager::GetInstance()->GetIsOnDice( blockIndex ) == false )
	{
		m_diceNum ++;	// �_�C�X�̐��ǉ�

		// ���݂̃I�u�W�F�N�g�������Ă���s���������
		m_pDice[notAppearNo].InitWorldMtx();

		// �ʔ���z���ۑ�
		m_pDice[notAppearNo].InitPip();

		// �����_���ŏ�ʂ̖ڂƉ��ʂ̉�]�������߂�
		int upperFace = CDiceRandSystem::GetInstance()->GetUpperFace();
		int aroundNum = CDiceRandSystem::GetInstance()->GetAroundFace();

		// ��ʂ����ɃT�C�R���̏������Z�b�g
		m_pDice[ notAppearNo ].SetPip( upperFace, aroundNum ); 

		// �T�C�R���̈ʒu�Z�b�g
		D3DXVECTOR3	workVec;
		D3DXMATRIX  workMtx;
		D3DXMatrixIdentity( &workMtx );

		workVec = *CStageBlockManager::GetInstance()->GetPos( blockIndex );
		workMtx._41 = workVec.x;
		workMtx._42 = -4.0f;
		workMtx._43 = workVec.z;

		// ���ʔԍ��̃Z�b�g
		m_pDice[ notAppearNo ].SetNo( notAppearNo );

		// ��]�s��ƕ��s�ړ��s�����Z
		m_pDice[ notAppearNo ].CalcWorldMtx( m_pDice[ notAppearNo ].GetWorldMtx(),&workMtx );
		
		// �C���f�b�N�X�ԍ���ۑ�
		m_pDice[ notAppearNo ].SetIndexNo( blockIndex );

		// ���l�̐ݒ�
		m_pDice[ notAppearNo ].SetColor( 255,255,255,127 );

		// �o�����ɐݒ�
		m_pDice[ notAppearNo ].SetStatus( DICE_STATUS::e_statusStartAppear );

		m_pDice[ notAppearNo ].SetAABB();

		// �������ꂽ��X�e�[�W�ƃ_�C�X�ɐ������ꂽ�Ƃ��������Z�b�g
		m_pDice[ notAppearNo ].SetIsDice( true );
		CStageBlockManager::GetInstance()->SetBlockToDiceInfo( &m_pDice[ notAppearNo ], blockIndex );

		CDebugMode::m_pDiceBox[notAppearNo].diceBox.CreateBox( m_pDice[notAppearNo].GetSize() );
		CDebugMode::m_pDiceBox[notAppearNo].diceBox.InitWorldMtx();
		CDebugMode::m_pDiceBox[notAppearNo].diceBox.SetWorldMtx( m_pDice[notAppearNo].GetWorldMtx() );
		CDebugMode::m_pDiceBox[notAppearNo].diceBox.SetDiffuse( 0, 0, 0, 200 );
		CDebugMode::m_pDiceBox[notAppearNo].diceBox.SetAmbient( 255, 0, 0, 255 );
		CDebugMode::m_pDiceBox[notAppearNo].isDice = true;

		return true;
	}

	return false;
}

//----------------------------------------------------
// �_�C�X�̃A�j���[�V����
//----------------------------------------------------
void CDiceObjManager::Animation( void )
{
	for( int i = 0; i < MAX_DICE_NUM; ++ i )
	{
		if( m_pDice[i].GetIsDice() == true )
		{
			// �v���C���[�̌��ݒn����u���b�N�̓Y�����ԍ����擾����
			UINT playerIndex = CStageBlockManager::GetInstance()->GetIndexToPlayerPos( CPlayerManager::GetInstance()->GetPlayerPos()->x, 
																					   CPlayerManager::GetInstance()->GetPlayerPos()->z );
			switch( m_pDice[i].GetStatus() )
			{
			// �o�����ĐÎ~���Ă�����
			case DICE_STATUS::e_statusNormal:
				if( m_pDice[i].GetIndexNo() == playerIndex && 
					( CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceDeleteStart ||
					CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceAppear ) )
				{
					m_pMainDice->diceObj = &m_pDice[i];		// ���C���̃_�C�X�ύX
					CPlayerManager::GetInstance()->SetPlayerStatus( ePlayerStatus::eOnDice );
					// �v���C���[���_�C�X�̏�ɏ悹��
					CPlayerManager::GetInstance()->SetPlayerPos( CPlayerManager::GetInstance()->GetPlayerPos()->x, m_pDice[i].GetYPos() + 4.0f, CPlayerManager::GetInstance()->GetPlayerPos()->z );
					m_pDiceInfoManager->SetInfoDice( m_pMainDice->diceObj->GetWorldMtx() );
				}
				break;

			// �o�����n�߃A�j���[�V����
			case DICE_STATUS::e_statusStartAppear:
				// ���݂̓Y���������C���_�C�X�̓Y�����Ɠ�����������v���C���[�̏�Ԃ�J��
				if( m_pDice[i].GetIndexNo() == playerIndex &&
					( CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnStage ||
					CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceDelete ||
					CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceDeleteStart ||
					CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceAppear ||
					CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceAppearStart ) )
				{
					m_pMainDice->diceObj = &m_pDice[i];		// ���C���̃_�C�X�ύX
					CPlayerManager::GetInstance()->SetPlayerStatus( ePlayerStatus::eOnDiceAppearStart );
					// �v���C���[���_�C�X�̏�ɏ悹��
					CPlayerManager::GetInstance()->SetPlayerPos( CPlayerManager::GetInstance()->GetPlayerPos()->x, m_pDice[i].GetYPos() + 4.0f, CPlayerManager::GetInstance()->GetPlayerPos()->z );
					m_pDiceInfoManager->SetIsExist( true );
					m_pDiceInfoManager->SetInfoDice( m_pMainDice->diceObj->GetWorldMtx() );
				}

				// �o�����n�߃A�j���[�V�������I�������
				if( m_pDice[i].UpAnimation( DICE_UP_SPEED ) )
				{
					m_pDice[i].SetStatus( DICE_STATUS::e_statusAppear );
					m_pDice[i].SetBeforStatus( DICE_STATUS::e_statusStartAppear );

					// �_�C�X�̃A�j���[�V�������ς���������A�_�C�X�̏�ɂ���ꍇ�̓v���C���[�̃X�e�[�^�X��ς���
					if( m_pDice[i].GetIndexNo() == playerIndex )
					{
						CPlayerManager::GetInstance()->SetPlayerStatus( ePlayerStatus::eOnDiceAppear );
					}
				}
				CDebugMode::m_pDiceBox[m_pDice[i].GetNo()].diceBox.SetWorldMtx( m_pDice[m_pDice[i].GetNo()].GetWorldMtx() );
				m_pDice[i].SetAABB();
				break;

			// �o�����A�j���[�V����
			case DICE_STATUS::e_statusAppear:
				// �o�����A�j���[�V�����̏�Ƀ_�C�X�̏�ɂ���v���C���[���ړ����Ă�����_�C�X�̏�ɃZ�b�g
				if( m_pDice[i].GetIndexNo() == playerIndex && 
					( CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDice || 
					  CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceAppear ||
					  CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceAppearStart ||
					  CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceDeleteStart ||
					  CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceDelete ) )
				{

					m_pMainDice->diceObj = &m_pDice[i];		// ���C���̃_�C�X�ύX
					// �v���C���[�̏�Ԃ�J��
					CPlayerManager::GetInstance()->SetPlayerStatus( ePlayerStatus::eOnDiceAppear );
					// �v���C���[���_�C�X�̏�ɏ悹��
					CPlayerManager::GetInstance()->SetPlayerPos( CPlayerManager::GetInstance()->GetPlayerPos()->x, m_pDice[i].GetYPos() + 4.0f, CPlayerManager::GetInstance()->GetPlayerPos()->z );
					m_pDiceInfoManager->SetIsExist( true );
					m_pDiceInfoManager->SetInfoDice( m_pMainDice->diceObj->GetWorldMtx() );
				}

				// �o���A�j���[�V�������I�������
				if( m_pDice[i].UpAnimation( DICE_UP_SPEED ) )
				{
					m_pDice[i].SetStatus( DICE_STATUS::e_statusNormal );
					m_pDice[i].SetBeforStatus( DICE_STATUS::e_statusAppear );

					if( m_pDice[i].GetIndexNo() == playerIndex )
					{
						CPlayerManager::GetInstance()->SetPlayerStatus( ePlayerStatus::eOnDice );
					}
					
					// �X�e�[�W�̃u���b�N�̏�Ԃ�ύX
					CStageBlockManager::GetInstance()->SetIsOnDice( CStageBlockManager::GetInstance()->GetIndexToDicePos( m_pDice[i].GetXPos(), m_pDice[i].GetZPos() ), true );
				}
				CDebugMode::m_pDiceBox[m_pDice[i].GetNo()].diceBox.SetWorldMtx( m_pDice[m_pDice[i].GetNo()].GetWorldMtx() );
				m_pDice[i].SetAABB();
				break;

			// �����n�߃A�j���[�V����
			case DICE_STATUS::e_statusStartDelete:
				// �v���C���[�ƃ_�C�X�̓Y�����ԍ��������Ȃ�
				if( m_pDice[i].GetIndexNo() == playerIndex &&
					( CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDice ||
					CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceAppearStart ||
					CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceAppear ||
					CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceDeleteStart ||
					CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceDelete ) )
				{		
					m_pMainDice->diceObj = &m_pDice[i];		// ���C���̃_�C�X�ύX
					// �v���C���[�̏�Ԃ�J��
					CPlayerManager::GetInstance()->SetPlayerStatus( ePlayerStatus::eOnDiceDeleteStart );
					// �v���C���[���_�C�X�̏�ɏ悹��
					CPlayerManager::GetInstance()->SetPlayerPos( CPlayerManager::GetInstance()->GetPlayerPos()->x, m_pDice[i].GetYPos() + 4.0f, CPlayerManager::GetInstance()->GetPlayerPos()->z );
					m_pDiceInfoManager->SetIsExist( true );
					m_pDiceInfoManager->SetInfoDice( m_pMainDice->diceObj->GetWorldMtx() );
				}

				// �����n�߂̃A�j���[�V�������I�������
				if( m_pDice[i].DownAnimation( -DICE_DOWN_SPEED ) )
				{
					m_pDice[i].SetStatus( DICE_STATUS::e_statusDelete );
					m_pDice[i].SetBeforStatus( DICE_STATUS::e_statusStartDelete );

					// �v���C���[�̈ʒu����u���b�N�̓Y�����ԍ����擾����
					UINT playerIndex = CStageBlockManager::GetInstance()->GetIndexToPlayerPos( CPlayerManager::GetInstance()->GetPlayerPos()->x, 
		   																						CPlayerManager::GetInstance()->GetPlayerPos()->z );
					// �v���C���[�ƃ_�C�X�̓Y�����ԍ��������Ȃ�
					if( m_pDice[i].GetIndexNo() == playerIndex )
					{
						CPlayerManager::GetInstance()->SetPlayerStatus( ePlayerStatus::eOnDiceDelete );
						// �v���C���[���_�C�X�ɏ悹��
						CPlayerManager::GetInstance()->SetPlayerPos( CPlayerManager::GetInstance()->GetPlayerPos()->x, m_pDice[i].GetYPos() + 4.0f, CPlayerManager::GetInstance()->GetPlayerPos()->z );
						m_pDiceInfoManager->SetInfoDice( m_pMainDice->diceObj->GetWorldMtx() );	
					}
					CDebugMode::m_pDiceBox[m_pDice[i].GetNo()].diceBox.SetWorldMtx( m_pDice[m_pDice[i].GetNo()].GetWorldMtx() );
					m_pDice[i].SetAABB();
				}
				break;

			// �������A�j���[�V����
			case DICE_STATUS::e_statusDelete:
				// �v���C���[�ƃ_�C�X�̓Y�����ԍ��������Ȃ�
				if( m_pDice[i].GetIndexNo() == playerIndex &&
				 ( CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceAppearStart ||
				   CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceAppear ||
				   CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnStage ||
				   CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceDelete ||
				   CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceDeleteStart ) )
				{
					m_pMainDice->diceObj = &m_pDice[i];		// ���C���̃_�C�X�ύX
					// �v���C���[�̏�Ԃ�J��
					CPlayerManager::GetInstance()->SetPlayerStatus( ePlayerStatus::eOnDiceDelete );
					// �v���C���[���_�C�X�̏�ɏ悹��
					CPlayerManager::GetInstance()->SetPlayerPos( CPlayerManager::GetInstance()->GetPlayerPos()->x, m_pDice[i].GetYPos() + 4.0f, CPlayerManager::GetInstance()->GetPlayerPos()->z );
					m_pDiceInfoManager->SetIsExist( true );
					m_pDiceInfoManager->SetInfoDice( m_pMainDice->diceObj->GetWorldMtx() );
				}

				// �����A�j���[�V�������I�������
				if( m_pDice[i].DownAnimation( -DICE_DOWN_SPEED ) )
				{
					m_pDice[i].SetStatus( DICE_STATUS::e_statusNone );
					m_pDice[i].SetBeforStatus( DICE_STATUS::e_statusDelete );
					m_pDice[i].SetIsDice( false );	// �_�C�X�Ȃ��̏�Ԃɐݒ肷��
					m_pDice[i].SetIsChain( false );	// �`�F�C�����Ă��Ȃ���Ԃɐݒ肷��
					
					// �`�F�C���̃_�C�X�̌������炵�Ă����Ȃ��Ȃ�����`�F�C���I��
					CChainManager::GetInstance()->GetChain( m_pDice[i].GetChainNo() )->chainDiceNum --;
					if( CChainManager::GetInstance()->GetChain( m_pDice[i].GetChainNo() )->chainDiceNum == 0 )
					{
						CChainManager::GetInstance()->GetChain( m_pDice[i].GetChainNo() )->isChain = false;
					}

					// �v���C���[�̌��ݒn����u���b�N�̓Y�����ԍ����擾
					UINT playerIndex = CStageBlockManager::GetInstance()->GetIndexToPlayerPos( CPlayerManager::GetInstance()->GetPlayerPos()->x, 
																							   CPlayerManager::GetInstance()->GetPlayerPos()->z );

					// �v���C���[�̓Y�����ԍ��ƃ_�C�X��������������v���C���[�̃X�e�[�^�X�ύX
					if( m_pDice[i].GetIndexNo() == playerIndex )
					{
						CPlayerManager::GetInstance()->SetPlayerStatus( ePlayerStatus::eOnStage );
						m_pDiceInfoManager->SetIsExist( false );
					}

					// �X�e�[�W�ォ��_�C�X���폜
					CStageBlockManager::GetInstance()->SetIsOnDice( CStageBlockManager::GetInstance()->GetIndexToDicePos( m_pDice[i].GetXPos(), m_pDice[i].GetZPos() ), false );
					m_diceNum --;
				}
				CDebugMode::m_pDiceBox[m_pDice[i].GetNo()].diceBox.SetWorldMtx( m_pDice[m_pDice[i].GetNo()].GetWorldMtx() );
				m_pDice[i].SetAABB();
				break;
			}
		}
	}
}