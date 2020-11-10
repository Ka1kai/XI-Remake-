
#include "CPlayerManager.h"

const float ConstPlayerSpeed = 0.2f;
const float ConstPlayerToDiceDistanceX = 0.5f;
const float ConstPlayerToDiceDistanceZ = 0.3f;

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CPlayerManager::CPlayerManager( void )
{
	m_pPlayer = new CPlayer;

	m_pPlayerFilePath = PLAYER_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pPlayerFilePath );
}

//----------------------------------------------------
// �f�X�g���N�^ 
//----------------------------------------------------
CPlayerManager::~CPlayerManager( void )
{
	SAFE_DELETE_ALLAY( m_pPlayer );
}

//----------------------------------------------------
// ������
//----------------------------------------------------
bool CPlayerManager::Init( void )
{
	m_pPlayer->Init();

	// �����蔻��p�f�[�^�쐬(�_�C�X�́�)
	CDebugMode::m_pPlayerBox.CreateBox( &m_pPlayer->GetAABB()->size );
	CDebugMode::m_pPlayerBox.Init();
	CDebugMode::m_pPlayerBox.SetDiffuse( 0, 0, 0, 150 );
	CDebugMode::m_pPlayerBox.SetAmbient( 0, 0, 255, 0 );

	return true;
}

//----------------------------------------------------
// �I��
//----------------------------------------------------
bool CPlayerManager::Uninit( void )
{
	return true;
}

//----------------------------------------------------
// �`��
//----------------------------------------------------
void CPlayerManager::Draw( void )
{
	CDirectDrawSystem::GetInstance()->DrawSprite( CResourceManager::GetInstance()->GetTexture( m_pPlayerFilePath )->Get(),m_pPlayer->GetVertex(),m_pPlayer->GetWorldMtx() );
}

//----------------------------------------------------
// ����
//----------------------------------------------------
void CPlayerManager::Run( void )
{
	this->Move();

	switch( m_pPlayer->GetPlayerStatus() )
	{
	case ePlayerStatus::eOnStage:
		break;

	// �_�C�X�����n�ߒ�
	case ePlayerStatus::eOnDiceDeleteStart:
		this->Down();
		break;

	// �_�C�X������
	case ePlayerStatus::eOnDiceDelete:
		break;

	// �_�C�X�o����
	case ePlayerStatus::eOnDiceAppear:
		this->Up( DICE_UP_SPEED );
		break;
	}
}

//----------------------------------------------------
// �ړ�
//----------------------------------------------------
void CPlayerManager::Move( void )
{
	// �O�ړ�
	if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_UP ) || 
		CJoyStick::GetInstance()->GetPressButton( 0, XINPUT_GAMEPAD_DPAD_UP ))
	{
		this->MoveFront();
	}

	// ��ړ�
	if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_DOWN ) ||
		CJoyStick::GetInstance()->GetPressButton( 0, XINPUT_GAMEPAD_DPAD_DOWN ) )
	{
		this->MoveBack();
	}

	// �E�ړ�
	if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_RIGHT ) ||
		CJoyStick::GetInstance()->GetPressButton( 0, XINPUT_GAMEPAD_DPAD_RIGHT ) )
	{
		this->MoveRight();
	}

	// ���ړ�
	if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_LEFT ) ||
		CJoyStick::GetInstance()->GetPressButton( 0, XINPUT_GAMEPAD_DPAD_LEFT ) )
	{
		this->MoveLeft();
	}
}

//----------------------------------------------------
// �O�ړ� 
//----------------------------------------------------
void CPlayerManager::MoveFront( void )
{
	// �X�e�[�W�̈�ԑO�Ƃ̔���
	if( m_pPlayer->GetZPos() <= CStageBlockManager::GetInstance()->GetZSize() )
	{
		// �v���C���[�̃C���f�b�N�X�ԍ��擾
		UINT playerIndex = CStageBlockManager::GetInstance()->GetIndexToPlayerPos( m_pPlayer->GetXPos(), m_pPlayer->GetZPos() );

		// �v���C���[�̏�Ԃɂ���đO�ړ��̓�����ς���
		switch( m_pPlayer->GetPlayerStatus() )
		{
		// �_�C�X��
		case ePlayerStatus::eOnDice:
			// ���ړ����Ă�����O�ɂ͓����Ȃ�
			if( CDiceObjManager::GetInstance()->GetMainDice()->rollState == DICE_ROLLSTATE_BACK )
			{
				break;
			}
			// �_�C�X�̑O�̕��܂ňړ�������
			if( this->IsHitPlayerToDiceZ( ConstPlayerToDiceDistanceZ + 0.2f, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true ) 
			{
				// �_�C�X���ړ�����������v���C���[����яo�Ȃ��悤�ɐݒ�
				if( CDiceObjManager::GetInstance()->GetMainDice()->rollState != eDiceRollState::DICE_ROLLSTATE_NONE )
				{
					break;
				}
				else if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 7 ) == false ||
						 CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 7 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
				{
					// �O�Ƀ_�C�X���Ȃ��ꍇ�̓_�C�X�ړ�
					CDiceObjManager::GetInstance()->MoveFront();
					m_pPlayer->SetMoveStatus( ePlayerMoveStatus::eMoveFront );
				}
				else if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 7 ) == true &&
					   ( CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 7 )->GetDice()->GetStatus() == DICE_STATUS::e_statusStartAppear || 
						 CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 7 )->GetDice()->GetStatus() == DICE_STATUS::e_statusDelete ) )
				{
					// �O�̃_�C�X���o�����n�߂������͏�������������_�C�X�ړ�
					CDiceObjManager::GetInstance()->MoveFront();
					m_pPlayer->SetMoveStatus( ePlayerMoveStatus::eMoveFront );				
				}
			}
		
			m_pPlayer->MoveFront( ConstPlayerSpeed );			// �ړ�

			break;

		// �o�����n��
		case ePlayerStatus::eOnDiceAppearStart:
			// �o�����n�ߒ��Ƀ_�C�X�̑O�̕��܂ňړ�������
			if( this->IsHitPlayerToDiceZ( ConstPlayerToDiceDistanceZ + 0.2f, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true ) 
			{
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 7 ) == false )
				{
					// �_�C�X���O�ɂȂ��ꍇ�̓X�e�[�W�ɂ̂���
					m_pPlayer->SetSpritePos( m_pPlayer->GetXPos(), 0.0f, m_pPlayer->GetZPos() );
					m_pPlayer->SetPlayerStatus( ePlayerStatus::eOnStage );	// �X�e�[�W�̏㔻��ɂ���
					m_pDiceInfoManager->SetIsExist( false );
				}
				else if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex -7 ) == true &&
					     CStageBlockManager::GetInstance()->GetStageBlock( playerIndex -7 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
				{
					// �_�C�X���O�ɂ����ă_�C�X���ʏ��Ԃ̏ꍇ�͈ړ��ł��Ȃ�
					break;
				}
			}
			m_pPlayer->MoveFront( ConstPlayerSpeed );			// �ړ�
			break;

		// �o����
		case ePlayerStatus::eOnDiceAppear:
			// �o�����Ƀ_�C�X�̑O�̕��܂ňړ�������
			if( this->IsHitPlayerToDiceZ( ConstPlayerToDiceDistanceZ + 0.2f, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true ) 
			{
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 7 ) == false )
				{
					break;
				}
			}
			m_pPlayer->MoveFront( ConstPlayerSpeed );			// �ړ�
			break;

		// �����n��
		case ePlayerStatus::eOnDiceDeleteStart:
			// �����n�ߒ��Ƀ_�C�X�̑O�̕��܂ňړ�������
			if( this->IsHitPlayerToDiceZ( ConstPlayerToDiceDistanceZ + 0.2f, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 7 ) == false )
				{
					// �������Ȃ�
					break;
				}
			}
			m_pPlayer->MoveFront( ConstPlayerSpeed );			// �ړ�
			break;
		
		/// ������
		case ePlayerStatus::eOnDiceDelete:
			// �������Ƀ_�C�X�̑O�̕��܂ňړ�������
			if( this->IsHitPlayerToDiceZ( ConstPlayerToDiceDistanceZ + 0.2f, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true ) 
			{
				// �O�Ƀ_�C�X���Ȃ��ꍇ�̓X�e�[�W�ɏ悹��
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 7 ) == false )
				{
					m_pPlayer->SetSpritePos( m_pPlayer->GetXPos(), 0.0f, m_pPlayer->GetZPos() );
					m_pPlayer->SetPlayerStatus( ePlayerStatus::eOnStage );	// �X�e�[�W�̏㔻��ɂ���
					m_pDiceInfoManager->SetIsExist( false );
				}

				// �O�̃_�C�X�̏�Ԃɂ���Ĉړ������Ȃ�
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 7 ) == true &&
					CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 7 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
				{
					break;
				}
			}
			m_pPlayer->MoveFront( ConstPlayerSpeed );			// �ړ�
		break;	
		
		// �X�e�[�W��ɂ���
		case ePlayerStatus::eOnStage:	
			// �v���C���[����ԑO�̗�ɂ�����ړ��̂�
			if( playerIndex <= 6  )
			{	
				m_pPlayer->MoveFront( ConstPlayerSpeed );
				break;
			}

			// �����ڂ̑O�Ƀ_�C�X������Έړ��ł��Ȃ�
			if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 7 ) == true && 
				CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 7 )->GetDice()->GetIsDice() == true &&
				CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 7 )->GetDice()->GetStatus() != DICE_STATUS::e_statusStartAppear &&
				CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 7 )->GetDice()->GetStatus() != DICE_STATUS::e_statusDelete )
			{
				if( !this->IsHitPlayerToDiceZ( ConstPlayerToDiceDistanceZ, CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 7 )->GetDice() ) )
				{
					// �ڂ̑O�Ƀ_�C�X���������瓮�����Ȃ�
					break;
				}
			}
			m_pPlayer->MoveFront( ConstPlayerSpeed );				// �ړ�
			break;

		default:
			break;
		}
	}

}

//----------------------------------------------------
// ��ړ� 
//----------------------------------------------------
void CPlayerManager::MoveBack( void )
{
	// �X�e�[�W�̈�Ԍ��Ƃ̔���
	if( m_pPlayer->GetZPos() >= -CStageBlockManager::GetInstance()->GetZSize() )
	{
		// �v���C���[�̃C���f�b�N�X�ԍ��擾
		UINT playerIndex = CStageBlockManager::GetInstance()->GetIndexToPlayerPos( m_pPlayer->GetXPos(), m_pPlayer->GetZPos() );

		// �v���C���[�̏�Ԃɂ���Č�ړ��̓�����ς���
		switch( m_pPlayer->GetPlayerStatus() )
		{
		// �_�C�X��
		case ePlayerStatus::eOnDice:	
			if( CDiceObjManager::GetInstance()->GetMainDice()->rollState == DICE_ROLLSTATE_FRONT )
			{
				break;
			}
			// �_�C�X�̌��܂ňړ�������
			if( this->IsHitPlayerToDiceZ ( -ConstPlayerToDiceDistanceZ + -0.2f, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				// �_�C�X���ړ����̏ꍇ�͔�яo�Ȃ��悤�ɂ���
				if( CDiceObjManager::GetInstance()->GetMainDice()->rollState != eDiceRollState::DICE_ROLLSTATE_NONE )
				{
					break;
				}
				else if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 7 ) == false ||
						 CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 7 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
				{
					// �_�C�X�����ɂȂ��ꍇ�̓_�C�X���ړ�
					CDiceObjManager::GetInstance()->MoveBack();
					m_pPlayer->SetMoveStatus( ePlayerMoveStatus::eMoveBack );
				}
				else if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 7 ) == true && 
					   ( CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 7 )->GetDice()->GetStatus() == DICE_STATUS::e_statusStartAppear ||
						 CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 7 )->GetDice()->GetStatus() == DICE_STATUS::e_statusDelete ) )
				{
					// ���̃_�C�X���o�����n�߂������͏�������������ړ��\
					CDiceObjManager::GetInstance()->MoveBack();
					m_pPlayer->SetMoveStatus( ePlayerMoveStatus::eMoveBack );
				}
			}

			m_pPlayer->MoveBack( ConstPlayerSpeed );	// �ړ�
			break;
		
		// �o�����n��
		case ePlayerStatus::eOnDiceAppearStart:		
			// �o�����n�ߒ��Ƀ_�C�X�̌��̕��܂ňړ�������
			if( this->IsHitPlayerToDiceZ ( -ConstPlayerToDiceDistanceZ + - 0.2f, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 7 ) == false )
				{
					// ���Ƀ_�C�X���Ȃ��ꍇ�̓X�e�[�W�ɂ̂���
					m_pPlayer->SetSpritePos( m_pPlayer->GetXPos(), 0.0f, m_pPlayer->GetZPos() );
					m_pPlayer->SetPlayerStatus( ePlayerStatus::eOnStage );	// �X�e�[�W�̏㔻��ɂ���
					m_pDiceInfoManager->SetIsExist( false );
				}
				else if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex ) == true &&
						 CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 7 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
				{
					// ���Ƀ_�C�X�������Ēʏ��Ԃ̏ꍇ�͓������Ȃ�
					break;
				}	
			}
			m_pPlayer->MoveBack( ConstPlayerSpeed );	// �ړ�	
			break;

		// �o����
		case ePlayerStatus::eOnDiceAppear:
			// �o�����Ƀ_�C�X�̌��̕��܂ňړ�������
			if( this->IsHitPlayerToDiceZ ( -ConstPlayerToDiceDistanceZ + -0.2f, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				// �u���b�N�����ɂȂ��ꍇ�͓����Ȃ����������Ȃ�
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 7 ) == false )
				{
					break;
				}
			}
			m_pPlayer->MoveBack( ConstPlayerSpeed );	// �ړ�	
			break;

		// �����n��
		case ePlayerStatus::eOnDiceDeleteStart:
			// �������Ƀ_�C�X�̌��̕��܂ňړ�������
			if( this->IsHitPlayerToDiceZ ( -ConstPlayerToDiceDistanceZ + -0.2f, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 7 ) == false )
				{
					break;
				}
			}
			m_pPlayer->MoveBack( ConstPlayerSpeed );
			break;

		// ������
		case ePlayerStatus::eOnDiceDelete:
			// �������Ƀ_�C�X�̌��̕��܂ňړ�������
			if( this->IsHitPlayerToDiceZ ( -ConstPlayerToDiceDistanceZ + -0.2f, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				// ���Ƀ_�C�X���Ȃ��ꍇ�̓X�e�[�W�ɂ̂���
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 7 ) == false )
				{
					m_pPlayer->SetSpritePos( m_pPlayer->GetXPos(), 0.0f, m_pPlayer->GetZPos() );
					m_pPlayer->SetPlayerStatus( ePlayerStatus::eOnStage );	// �X�e�[�W�̏㔻��ɂ���
					m_pDiceInfoManager->SetIsExist( false );
				}

				// ���̃_�C�X�̏�Ԃɂ���Ĉړ������Ȃ�
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 7 ) == true &&
					CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 7 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
				{
					break;
				}
			}
			m_pPlayer->MoveBack( ConstPlayerSpeed );
			break;

		// �X�e�[�W��
		case ePlayerStatus::eOnStage:
			// �v���C���[����Ԍ�̗�ɂ�����
			if( playerIndex >= 42  )
			{
				m_pPlayer->MoveBack( ConstPlayerSpeed );
				break;
			}

			// �������Ƀ_�C�X�������
			if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 7 ) == true && 
				CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 7 )->GetDice()->GetIsDice() == true &&
				CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 7 )->GetDice()->GetStatus() != DICE_STATUS::e_statusStartAppear &&
				CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 7 )->GetDice()->GetStatus() != DICE_STATUS::e_statusDelete )
			{
				if( !this->IsHitPlayerToDiceZ( -ConstPlayerToDiceDistanceZ, CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 7 )->GetDice() ) )
				{
					// ���Ƀ_�C�X���������瓮�����Ȃ�
					break;
				}
				
			}
			// �ړ�
			m_pPlayer->MoveBack( ConstPlayerSpeed );
			break;

		default:
			break;
		}
	}
}

//----------------------------------------------------
// �E�ړ� 
//----------------------------------------------------
void CPlayerManager::MoveRight( void )
{
	// �X�e�[�W�̉E�[���ǂ���
	if( m_pPlayer->GetXPos() <= CStageBlockManager::GetInstance()->GetXSize() )
	{
		// �v���C���[�̃C���f�b�N�X�ԍ��擾
		UINT playerIndex = CStageBlockManager::GetInstance()->GetIndexToPlayerPos( m_pPlayer->GetXPos(), m_pPlayer->GetZPos() );

		switch( m_pPlayer->GetPlayerStatus() )
		{
		// �_�C�X��
		case ePlayerStatus::eOnDice:
			if( CDiceObjManager::GetInstance()->GetMainDice()->rollState == DICE_ROLLSTATE_LEFT )
			{
				break;
			}
			// �_�C�X�̉E�̕��܂ňړ������画��
			if( this->IsHitPlayerToDiceX( ConstPlayerToDiceDistanceX, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				// �_�C�X���ړ����̏ꍇ�͔�яo���Ȃ��悤�ɐݒ�
				if( CDiceObjManager::GetInstance()->GetMainDice()->rollState != eDiceRollState::DICE_ROLLSTATE_NONE )	
				{
					break;
				}
				else if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 1 ) == false ||
						 CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 1 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )

				{
					// �E�Ƀ_�C�X���Ȃ��ꍇ�̓_�C�X�ړ�
					CDiceObjManager::GetInstance()->MoveRight();
					m_pPlayer->SetMoveStatus( ePlayerMoveStatus::eMoveRight  );
				}
				else if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 1 ) == true && 
					( CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 1 )->GetDice()->GetStatus() == DICE_STATUS::e_statusStartAppear ||
					  CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 1 )->GetDice()->GetStatus() == DICE_STATUS::e_statusDelete ) )
				{
					// �_�C�X���E�ɂ����ďo�����n�߂������͏�������������ړ��\
					CDiceObjManager::GetInstance()->MoveRight();
					m_pPlayer->SetMoveStatus( ePlayerMoveStatus::eMoveRight  );
				}
			}
			m_pPlayer->MoveRight( ConstPlayerSpeed );		// �ړ�
			break;

		// �o�����n��
		case ePlayerStatus::eOnDiceAppearStart:
			// �o�����n�ߒ��Ƀ_�C�X�̉E�̕��܂ňړ�������
			if( this->IsHitPlayerToDiceX( ConstPlayerToDiceDistanceX, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 1 ) == false )
				{
					// �E�Ƀ_�C�X���Ȃ��ꍇ�̓X�e�[�W�ɂ̂���
					m_pPlayer->SetSpritePos( m_pPlayer->GetXPos(), 0.0f, m_pPlayer->GetZPos() );
					m_pPlayer->SetPlayerStatus( ePlayerStatus::eOnStage );	// �X�e�[�W�̏㔻��ɂ���
					m_pDiceInfoManager->SetIsExist( false );
				}
				else if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 1 ) == true &&
						 CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 1 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
				{
					// �E�Ƀ_�C�X�������Ēʏ��Ԃ̏ꍇ�͓������Ȃ�
					break;
				}
			}
			m_pPlayer->MoveRight( ConstPlayerSpeed );		// �ړ�
			break;
		
		// �o����
		case ePlayerStatus::eOnDiceAppear:			
			// �o�����Ƀ_�C�X�̉E�̕��܂ňړ�������
			if( this->IsHitPlayerToDiceX( ConstPlayerToDiceDistanceX, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				// �E�Ƀu���b�N���Ȃ������瓮���Ȃ����������Ȃ�
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 1 ) == false )
				{
					break;
				}
			}
			m_pPlayer->MoveRight( ConstPlayerSpeed );		// �ړ�	
			break;

		// �����n��
		case ePlayerStatus::eOnDiceDeleteStart:
			// �����n�ߒ��Ƀ_�C�X�̉E�̕��܂ňړ�������
			if( this->IsHitPlayerToDiceX( ConstPlayerToDiceDistanceX, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 1 ) == false )
				{
					break;
				}
			}

			m_pPlayer->MoveRight( ConstPlayerSpeed );		// �ړ�
			break;

		// ������
		case ePlayerStatus::eOnDiceDelete:
			// �������Ƀ_�C�X�̉E�̕��܂ňړ�������
			if( this->IsHitPlayerToDiceX( ConstPlayerToDiceDistanceX, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				// �E�Ƀ_�C�X���Ȃ��ꍇ�̓X�e�[�W�ɂ̂���
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 1 ) == false )
				{
					m_pPlayer->SetSpritePos( m_pPlayer->GetXPos(), 0.0f, m_pPlayer->GetZPos() );
					m_pPlayer->SetPlayerStatus( ePlayerStatus::eOnStage );	// �X�e�[�W�̏㔻��ɂ���
					m_pDiceInfoManager->SetIsExist( false );
				}

				// �E�̃_�C�X�̏�Ԃɂ���Ĉړ������Ȃ�
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 1 ) == true &&
					CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 1 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
				{
					break;
				}
			}
			m_pPlayer->MoveRight( ConstPlayerSpeed );		// �ړ�
			break;

		// �X�e�[�W��
		case ePlayerStatus::eOnStage:	
			// �v���C���[����ԉE��ɂ����画�肵�Ȃ�
			if( ( ( playerIndex + 1 ) % 7 ) == 0 )
			{
				m_pPlayer->MoveRight( ConstPlayerSpeed );
				break;
			}

			// �����E�Ƀ_�C�X�������
			if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 1 ) == true && 
				CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 1 )->GetDice()->GetIsDice() == true &&
				CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 1 )->GetDice()->GetStatus() != DICE_STATUS::e_statusStartAppear &&
				CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 1 )->GetDice()->GetStatus() != DICE_STATUS::e_statusDelete )
			{
				if( !this->IsHitPlayerToDiceX( ConstPlayerToDiceDistanceX + 1.5f, CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 1 )->GetDice() ) )
				{
					// �E�Ƀ_�C�X���������瓮�����Ȃ�
					break;
				}
			}
			// �ړ�
			m_pPlayer->MoveRight( ConstPlayerSpeed );

		default:
			break;
		}
	}
}

//----------------------------------------------------
// ���ړ�
//----------------------------------------------------
void CPlayerManager::MoveLeft( void )
{
	// �X�e�[�W�̍��[�Ƃ̔���
	if( m_pPlayer->GetXPos() >= -CStageBlockManager::GetInstance()->GetXSize() )
	{
		// �v���C���[�̃C���f�b�N�X�ԍ��擾
		UINT playerIndex = CStageBlockManager::GetInstance()->GetIndexToPlayerPos( m_pPlayer->GetXPos(), m_pPlayer->GetZPos() );

		switch( m_pPlayer->GetPlayerStatus() )
		{
		// �_�C�X��
		case ePlayerStatus::eOnDice:
			if( CDiceObjManager::GetInstance()->GetMainDice()->rollState == DICE_ROLLSTATE_RIGHT )
			{
				break;
			}
			// �_�C�X�̍��̕��܂ňړ������画��
			if( this->IsHitPlayerToDiceX( -ConstPlayerToDiceDistanceX, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{					
				// �_�C�X���ړ����̏ꍇ�͔�яo�Ȃ��悤�ɐݒ�
				if( CDiceObjManager::GetInstance()->GetMainDice()->rollState != eDiceRollState::DICE_ROLLSTATE_NONE )
				{	
					break;
				}
				else if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 1 ) == false ||
						 CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 1 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
				{
					// ���Ƀ_�C�X���Ȃ��ꍇ�̓_�C�X���ړ�
					CDiceObjManager::GetInstance()->MoveLeft();
					m_pPlayer->SetMoveStatus( ePlayerMoveStatus::eMoveLeft );
				}
				else if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 1 ) == true &&
					   ( CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 1 )->GetDice()->GetStatus() == DICE_STATUS::e_statusStartAppear ||
					     CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 1 )->GetDice()->GetStatus() == DICE_STATUS::e_statusDelete ) )
				{
					// ���̃_�C�X���o�����n�߂������͏�������������ړ��\
					CDiceObjManager::GetInstance()->MoveLeft();
					m_pPlayer->SetMoveStatus( ePlayerMoveStatus::eMoveLeft );
				}
			}
			m_pPlayer->MoveLeft( ConstPlayerSpeed );	// �ړ�
			break;

		// �o�����n��
		case ePlayerStatus::eOnDiceAppearStart:
			// �o�����n�ߒ��Ƀ_�C�X�̍��̕��܂ňړ�������
			if( this->IsHitPlayerToDiceX( -ConstPlayerToDiceDistanceX, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 1 ) == false )
				{
					// ���Ƀ_�C�X���Ȃ��ꍇ�̓X�e�[�W�ɂ̂���
					m_pPlayer->SetSpritePos( m_pPlayer->GetXPos(), 0.0f, m_pPlayer->GetZPos() );
					m_pPlayer->SetPlayerStatus( ePlayerStatus::eOnStage );	// �X�e�[�W�̏㔻��ɂ���
					m_pDiceInfoManager->SetIsExist( false );
				}
				else if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 1 ) == true &&
						 CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 1 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
				{
					// ���Ƀ_�C�X�������Ēʏ��Ԃ̏ꍇ�͓������Ȃ�
					break;
				}
			}
			m_pPlayer->MoveLeft( ConstPlayerSpeed );	// �ړ�			
			break;

		// �o����
		case ePlayerStatus::eOnDiceAppear:
			// �o�����Ƀ_�C�X�̍��̕��܂ňړ�������
			if( this->IsHitPlayerToDiceX( -ConstPlayerToDiceDistanceX, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				// ���Ƀu���b�N���Ȃ���Γ����Ȃ����������Ȃ�
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 1 ) == false )
				{
					break;
				}
			}
			m_pPlayer->MoveLeft( ConstPlayerSpeed );	// �ړ�
			break;

		// �����n��
		case ePlayerStatus::eOnDiceDeleteStart:
			// �����n�ߒ��Ƀ_�C�X�̍��̕��܂ňړ�������
			if( this->IsHitPlayerToDiceX( -ConstPlayerToDiceDistanceX, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 1 ) == false )
				{
					break;
				}
			}
			m_pPlayer->MoveLeft( ConstPlayerSpeed );	// �ړ�		
			break;

		// ������
		case ePlayerStatus::eOnDiceDelete:
			// �������Ƀ_�C�X�̍��̕��܂ňړ�������
			if( this->IsHitPlayerToDiceX( -ConstPlayerToDiceDistanceX, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				// ���Ƀ_�C�X���Ȃ��ꍇ�̓X�e�[�W�ɏ悹��
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 1 ) == false )
				{
					m_pPlayer->SetSpritePos( m_pPlayer->GetXPos(), 0.0f, m_pPlayer->GetZPos() );
					m_pPlayer->SetPlayerStatus( ePlayerStatus::eOnStage );	// �X�e�[�W�̏㔻��ɂ���
					m_pDiceInfoManager->SetIsExist( false );
				}

				// ���̃_�C�X�̏�Ԃɂ���Ĉړ������Ȃ�
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 1 ) == true &&
					CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 1 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
				{
					break;
				}
			}
			m_pPlayer->MoveLeft( ConstPlayerSpeed );	// �ړ�		
			break;

		case ePlayerStatus::eOnStage:

			// �v���C���[����ԍ���ɂ����画�肵�Ȃ�
			if( playerIndex % 7 == 0 )
			{
				m_pPlayer->MoveLeft( ConstPlayerSpeed );
				break;
			}

			// �������Ƀ_�C�X�������
			if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 1 ) == true && 
				CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 1 )->GetDice()->GetIsDice() == true &&
				CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 1 )->GetDice()->GetStatus() != DICE_STATUS::e_statusStartAppear &&
				CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 1 )->GetDice()->GetStatus() != DICE_STATUS::e_statusDelete ) 
			{
				if( !this->IsHitPlayerToDiceX( -ConstPlayerToDiceDistanceX + -1.5f, CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 1 )->GetDice() ) )
				{
					// ���Ƀ_�C�X���������瓮�����Ȃ�
					break;
				}
			}
			// �ړ�
			m_pPlayer->MoveLeft( ConstPlayerSpeed );

		default:
			break;
		}
	}
}

//----------------------------------------------------
// �v���C���[�ƃ_�C�X�̔���(X����)
//----------------------------------------------------
bool CPlayerManager::IsHitPlayerToDiceX( CONST  float distance, CDiceObj* dice )
{
	// ��������炵�Ă���
	THITAABB playerAABB;
	::CopyMemory( &playerAABB, m_pPlayer->GetAABB(), sizeof( THITAABB ) );
	playerAABB.centerPos.x += distance;
	
	// �_�C�X�̈������܂ňړ�������
	if( !CCollision::GetInstance()->IsHitAABB( &playerAABB, dice->GetAABB() ) )
	{
		// �������Ă��Ȃ���ԂɂȂ���
		return true;
	}

	// �������Ă���
	return false;
}

//----------------------------------------------------
// �v���C���[�ƃ_�C�X�̔���(Z����)
//----------------------------------------------------
bool CPlayerManager::IsHitPlayerToDiceZ( CONST  float distance, CDiceObj* dice  )
{
	// ��������炵�Ă���
	THITAABB playerAABB;
	::CopyMemory( &playerAABB, m_pPlayer->GetAABB(), sizeof( THITAABB ) );
	playerAABB.centerPos.z += distance;
	
	// �_�C�X�̈������܂ňړ�������
	if( !CCollision::GetInstance()->IsHitAABB( &playerAABB, dice->GetAABB() ) )
	{
		// �������Ă��Ȃ���ԂɂȂ���
		return true;
	}

	// �������Ă�����
	return false;
}

//----------------------------------------------------
// �v���C���[�̗���
//----------------------------------------------------
void CPlayerManager::Down( void )
{
	m_pPlayer->MoveDown( DICE_DOWN_SPEED );
}

//----------------------------------------------------
// �v���C���[�̏㏸
//----------------------------------------------------
void CPlayerManager::Up( CONST float speed )
{
	m_pPlayer->MoveUp( DICE_UP_SPEED );
}

//----------------------------------------------------
// �J�����̏����v���C���[�̍s��ɃZ�b�g
//----------------------------------------------------
void CPlayerManager::SetCameraToMtx( CONST D3DXMATRIX* view )
{
	m_pPlayer->CalcWorldMtx( );
}