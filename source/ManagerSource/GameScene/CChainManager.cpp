
#include "CChainManager.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CChainManager::CChainManager( void )
{
	// �`�F�C���Ǘ��z���������
	for( int i = 0; i < 50; ++ i )
	{
		m_chain[i].isChain = false;
		m_chain[i].chainNo = 0;
		m_chain[i].chainNum = 0;
		m_chain[i].chainPip = 0;
	}
	 
	this->Init();
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
CChainManager::~CChainManager( void )
{
}

//----------------------------------------------------
// �������i����j
//----------------------------------------------------
bool CChainManager::Init( void )
{
	m_connectDiceNum = 0;			// �q�������_�C�X�̐���������
	m_connectDiceList.clear();		// �q�������_�C�X�̊i�[�p���X�g������

	// �S�Ĕ��肵�Ă��Ȃ���Ԃɂ���
	for( int i = 0; i < BLOCK_DEFAULT_MAX_NUM; ++ i )
	{
		m_decisionBlock[i] = false;
	}

	this->SetSize();

	return true;
}

//----------------------------------------------------
// �u���b�N��̃_�C�X�̃X�e�[�^�X��ݒ�
//----------------------------------------------------
void CChainManager::SetStageBlockDiceStatus( UINT index )
{
	CStageBlockManager::GetInstance()->GetStageBlock( index )->GetDice()->SetStatus( e_statusStartDelete );
}

//----------------------------------------------------
// Chain����
//----------------------------------------------------
void CChainManager::Chain( CONST UINT index )
{
	// ������
	this->Init();

	// ���݂̃��C���_�C�X�̏�ʂ��擾
	m_mainPip = CStageBlockManager::GetInstance()->GetStageBlock(index)->GetDice()->GetPip();
	
	// 1�̏ꍇ�͓��ʂȏ���
	if( m_mainPip == 1 )
	{
		if( this->CheckChain( index ) == true )
		{
			int oneNum = 0;
			this->CheckOne( index );	// �X�e�[�W��̂P�̖ڂ𔻒�
			for( auto iterator = m_connectDiceList.begin(); iterator != m_connectDiceList.end(); ++ iterator )
			{
				(*iterator)->SetStatus( DICE_STATUS::e_statusStartDelete );	// ������A�j���[�V�����ɂ���
				oneNum ++;
			}

			// �X�R�A
			m_pScore->m_record += m_chain[ CStageBlockManager::GetInstance()->GetStageBlock(index)->GetDice()->GetChainNo() ].chainNum * oneNum;
		
			// �P�������������X�V
			m_pScore->PipScoreAdd( m_mainPip, oneNum );
		}
	}

	// ����̖ʂ��`�F�C�����Ă��ď�ʂ������������炱�̃_�C�X���`�F�C�����ɂ���
	else if( this->CheckChain( index, m_mainPip ) == true )
	{
		int chainNo = CStageBlockManager::GetInstance()->GetStageBlock( index )->GetDice()->GetChainNo();

		// �������g�̃u���b�N�͔���ς݂ɂ��Ă���
		m_decisionBlock[ index ] = true;
		m_connectDiceNum ++;				
		m_connectDiceList.push_back( CStageBlockManager::GetInstance()->GetStageBlock( index )->GetDice() );

		// ����̃_�C�X�i�`�F�C�����Ă��Ȃ������j����
		this->CheckAround( index );

		// �`�F�C���Ǘ��p�z��̍X�V
		m_chain[ chainNo ].chainNum ++;
		m_chain[ chainNo ].chainDiceNum += m_connectDiceNum;

		// ������A�j���[�V�����ɑJ�ڂ�����
		for( auto iterator = m_connectDiceList.begin(); iterator != m_connectDiceList.end(); ++ iterator )
		{
			(*iterator)->SetChainNo( chainNo );	// �`�F�C���ԍ����Z�b�g
			(*iterator)->SetIsChain( true );	// �`�F�C�����ɐݒ�
			(*iterator)->SetStatus( DICE_STATUS::e_statusStartDelete );
			// �v���C���[�̏�ԑJ��
			CPlayerManager::GetInstance()->SetPlayerStatus( ePlayerStatus::eOnDiceDeleteStart );
		}
		// �X�R�A�̐ݒ�
		// �X�R�A( �� * �_�C�X�̐� * �`�F�C���� + 1 )
		m_pScore->m_record += m_mainPip * m_chain[ chainNo ].chainDiceNum * m_chain[ chainNo ].chainNum;

		// ���������X�V
		m_pScore->PipScoreAdd( m_mainPip, 1 );

		// �}�b�N�X�`�F�C�����X�V
		if( m_pScore->m_chainNum <= m_chain[chainNo].chainNum )
		{
			m_pScore->m_chainNum = m_chain[chainNo].chainNum;
		}
	}
	
	// 1�ȊO�̏ꍇ�͌q�������_�C�X�̐��ɂ���Ĕ���
	else 
	{
		// �������g�̃u���b�N�͔���ς݂ɂ��Ă���
		m_decisionBlock[ index ] = true;
		m_connectDiceNum ++;				
		m_connectDiceList.push_back( CStageBlockManager::GetInstance()->GetStageBlock( index )->GetDice() );

		// ����̃_�C�X����
		this->CheckAround( index );

		// �q�������_�C�X�����C���_�C�X�̏�ʂ�葽���ꍇ�͏�����
		if( m_mainPip <= m_connectDiceNum )
		{
			// �`�F�C���Ǘ��z��ɃZ�b�g
			int chainNo;
			for( chainNo = 0; chainNo < 50; ++ chainNo )
			{
				if( m_chain[chainNo].isChain == false )
					break;
			}
			m_chain[chainNo].isChain = true;
			m_chain[chainNo].chainNo = chainNo;
			m_chain[chainNo].chainPip = m_mainPip;
			m_chain[chainNo].chainDiceNum = m_connectDiceNum;
			m_chain[chainNo].chainNum = 1;

			// ������A�j���[�V�����ɑJ�ڂ�����
			for( auto iterator = m_connectDiceList.begin(); iterator != m_connectDiceList.end(); ++ iterator )
			{
				(*iterator)->SetChainNo( chainNo );	// �`�F�C���ԍ����Z�b�g
				(*iterator)->SetIsChain( true );	// �`�F�C�����ɐݒ�
				(*iterator)->SetStatus( DICE_STATUS::e_statusStartDelete );
				
				// ���C���̃_�C�X��������A�j���[�V�����ɑJ�ڂ�����v���C���[�̏�Ԃ�ς���
				if( (*iterator)->GetIndexNo() == CStageBlockManager::GetInstance()->GetStageBlock( index )->GetDice()->GetIndexNo() )
				{
					CPlayerManager::GetInstance()->SetPlayerStatus( ePlayerStatus::eOnDiceDeleteStart );
				}
			}

			// �X�R�A�̏���
			// �X�R�A( �� * �_�C�X�̐� * �`�F�C���� + 1 )
			m_pScore->m_record += m_mainPip * m_chain[chainNo].chainDiceNum *  m_chain[chainNo].chainNum;

			// ���������X�V
			m_pScore->PipScoreAdd( m_mainPip, m_chain[chainNo].chainDiceNum );

			// �}�b�N�X�`�F�C�����X�V
			if( m_pScore->m_chainNum <= m_chain[chainNo].chainNum )
			{
				m_pScore->m_chainNum = m_chain[chainNo].chainNum;
			}
		}
	}
}

//----------------------------------------------------
// 4�����Ƃ̃_�C�X�̔���(�ċA�֐�)
//----------------------------------------------------
int CChainManager::CheckAround( CONST UINT index )
{
	// �E����
	if( this->CheckRight( index ) )
	{
		this->CheckAround( index + 1 );
	}

	// ���̃_�C�X�Ƃ̔���
	if( this->CheckLeft( index ) ) 
	{
		this->CheckAround( index - 1 );
	}

	// �O�̃_�C�X�Ƃ̔���
	if( this->CheckFront( index ) )
	{
		this->CheckAround( index - m_zNum );
	}

	// ��̃_�C�X�Ƃ̔���
	if( this->CheckDown( index ) )
	{
		this->CheckAround( index + m_zNum );
	}

	return true;

}

//----------------------------------------------------
// �E�����̔���
//----------------------------------------------------
bool CChainManager::CheckRight( UINT index )
{
	// �Y��������ԉE�ł͂Ȃ����C�E�Ƀ_�C�X�����邩�C�܂����肵�Ă��Ȃ��u���b�N��,�܂��`�F�C�����Ă��Ȃ��_�C�X���ǂ�������
	if( index % m_xNum != m_xNum - 1 && CStageBlockManager::GetInstance()->GetIsOnDice( index + 1 ) == true && 
		m_decisionBlock[ index + 1 ] == false  && CStageBlockManager::GetInstance()->GetStageBlock( index + 1 )->GetDice()->GetIsChain() == false )
	{
		if( m_mainPip == CStageBlockManager::GetInstance()->GetStageBlock(index + 1)->GetDice()->GetPip() && 
			CStageBlockManager::GetInstance()->GetStageBlock( index + 1 )->GetDice()->GetStatus() == e_statusNormal )
		{		
			// ���������ꍇ�͔���ς݂ɂ��J�E���g���ă��X�g�ɒǉ�
			m_decisionBlock[ index + 1 ] = true;
			m_connectDiceNum ++;
			m_connectDiceList.push_back( CStageBlockManager::GetInstance()->GetStageBlock( index + 1 )->GetDice() );
			return true;
		}
	}

	return false;
}

//----------------------------------------------------
// �������̔���
//----------------------------------------------------
bool CChainManager::CheckLeft( UINT index )
{
	// �Y��������ԍ��ł͂Ȃ����C���Ƀ_�C�X�����邩�C�܂����肵�Ă��Ȃ��u���b�N��,�܂��`�F�C�����Ă��Ȃ����ǂ�������
	if( index % m_xNum != 0 && CStageBlockManager::GetInstance()->GetIsOnDice( index - 1 ) == true &&
		m_decisionBlock[ index -1 ] == false && CStageBlockManager::GetInstance()->GetStageBlock( index - 1 )->GetDice()->GetIsChain() == false )
	{   // ���C���̃_�C�X�̏�ʂƍ��̃_�C�X�̏�ʂ��������ǂ����C���̃_�C�X���ʏ��Ԃ�����
		if( m_mainPip == CStageBlockManager::GetInstance()->GetStageBlock( index - 1 )->GetDice()->GetPip() && 
			CStageBlockManager::GetInstance()->GetStageBlock( index - 1 )->GetDice()->GetStatus() == e_statusNormal )
		{		
			// ���������ꍇ�͔���ς݂ɂ��J�E���g���ă��X�g�ɒǉ�
			m_decisionBlock[ index - 1 ] = true;
			m_connectDiceNum ++;
			m_connectDiceList.push_back( CStageBlockManager::GetInstance()->GetStageBlock( index - 1 )->GetDice() );
			return true;
		}
	}
	return false;
}

//----------------------------------------------------
// �O�����̔���
//----------------------------------------------------
bool CChainManager::CheckFront( UINT index )
{
	int workIndex = index;
	// ���C���_�C�X����ԑO�ł͂Ȃ����C�O�Ƀ_�C�X�����邩�C�܂����肵�Ă��Ȃ��u���b�N��,�܂��`�F�C�����Ă��Ȃ����ǂ�������
	if( workIndex - m_zNum >= -1  && CStageBlockManager::GetInstance()->GetIsOnDice( index - m_zNum ) == true && 
		m_decisionBlock[ index - m_zNum ] == false && CStageBlockManager::GetInstance()->GetStageBlock( index - m_zNum )->GetDice()->GetIsChain() == false )
	{
		if( m_mainPip == CStageBlockManager::GetInstance()->GetStageBlock( index - m_zNum )->GetDice()->GetPip() && 
			CStageBlockManager::GetInstance()->GetStageBlock( index - m_zNum )->GetDice()->GetStatus() == e_statusNormal )
		{		
			// ���������ꍇ�͔���ς݂ɂ��J�E���g���ă��X�g�ɒǉ�
			m_decisionBlock[ index - m_zNum ] = true;
			m_connectDiceNum ++;
			m_connectDiceList.push_back( CStageBlockManager::GetInstance()->GetStageBlock( index - m_zNum )->GetDice() );
			return true;
		}
	}
	return false;
}

//----------------------------------------------------
// ������̔���
//----------------------------------------------------
bool CChainManager::CheckDown( UINT index )
{
	// ���C���_�C�X����Ԍ�ł͂Ȃ����C��Ƀ_�C�X�����邩�C�܂����肵�Ă��Ȃ��u���b�N��,�܂��`�F�C�����Ă��Ȃ�������
	if( index + m_zNum < CStageBlockManager::GetInstance()->GetDiceNum()  && CStageBlockManager::GetInstance()->GetIsOnDice( index + m_zNum ) == true && 
		m_decisionBlock[ index + m_zNum ] == false && CStageBlockManager::GetInstance()->GetStageBlock( index + m_zNum )->GetDice()->GetIsChain() == false )
	{
		if( m_mainPip == CStageBlockManager::GetInstance()->GetStageBlock( index + m_zNum )->GetDice()->GetPip() && 
			CStageBlockManager::GetInstance()->GetStageBlock( index + m_zNum )->GetDice()->GetStatus() == e_statusNormal )
		{		
			// ���������ꍇ�͔���ς݂ɂ��J�E���g���ă��X�g�ɒǉ�
			m_decisionBlock[ index + m_zNum ] = true;
			m_connectDiceNum ++;
			m_connectDiceList.push_back( CStageBlockManager::GetInstance()->GetStageBlock( index + m_zNum )->GetDice() );
			return true;
		}
	}

	return false;
}

//----------------------------------------------------
// �P�̖ڂ��ǂ����𔻒�
//----------------------------------------------------
void CChainManager::CheckOne( CONST UINT index )
{
	// �X�e�[�W�ɒu����Ă���_�C�X���P���ǂ������肵�ă��X�g�ɓ����
	for( int i = 0; i < MAX_DICE_NUM; ++ i )
	{
		// �����̓Y�����͔��肵�Ȃ�
		if( index == i )
			continue;

		if( CStageBlockManager::GetInstance()->GetIsOnDice( i ) == true &&
			CStageBlockManager::GetInstance()->GetStageBlock( i )->GetDice()->GetIsDice() == true &&
			CStageBlockManager::GetInstance()->GetStageBlock( i )->GetDice()->GetPip() == 1 )
		{
			m_connectDiceList.push_back( CStageBlockManager::GetInstance()->GetStageBlock( i )->GetDice() );
		}
	}
}

//----------------------------------------------------
// ����̖ʂ��`�F�C�����Ă��邩�ǂ�������
//----------------------------------------------------
bool CChainManager::CheckChain( CONST UINT index )
{
	// �E����
	if( index % m_xNum != m_xNum - 1 &&
		CStageBlockManager::GetInstance()->GetIsOnDice( index + 1 ) == true &&
		CStageBlockManager::GetInstance()->GetStageBlock( index + 1 )->GetDice()->GetIsChain() == true )
	{
		return true;
	}

	// ���̃_�C�X�Ƃ̔���
	if(  index % m_xNum != 0 && 
		CStageBlockManager::GetInstance()->GetIsOnDice( index -1 ) == true &&
		CStageBlockManager::GetInstance()->GetStageBlock( index - 1 )->GetDice()->GetIsChain() == true ) 
	{
		return true;
	}

	// �O�̃_�C�X�Ƃ̔���
	if( index - m_zNum >= -1 && 
		CStageBlockManager::GetInstance()->GetIsOnDice( index - m_zNum ) == true &&
		CStageBlockManager::GetInstance()->GetStageBlock( index - m_zNum )->GetDice()->GetIsChain() == true )
	{
		return true;
	}

	// ��̃_�C�X�Ƃ̔���
	if( index + m_zNum < CStageBlockManager::GetInstance()->GetDiceNum() == true &&
		CStageBlockManager::GetInstance()->GetIsOnDice( index + m_zNum ) == true &&
		CStageBlockManager::GetInstance()->GetStageBlock( index + m_zNum )->GetDice()->GetIsChain() == true )
	{
		return true;
	}

	return false;
}

//----------------------------------------------------
// ����ʂ���ʔԍ��Ń`�F�C�����Ă��邩�ǂ�������
//----------------------------------------------------
bool CChainManager::CheckChain( CONST UINT index, CONST UINT pip )
{
	// �E����
	if( index % m_xNum != m_xNum - 1 &&
		CStageBlockManager::GetInstance()->GetIsOnDice( index + 1 ) == true &&
		CStageBlockManager::GetInstance()->GetStageBlock( index + 1 )->GetDice()->GetIsChain() == true &&
		CStageBlockManager::GetInstance()->GetStageBlock( index + 1 )->GetDice()->GetPip() == pip &&
		m_chain[CStageBlockManager::GetInstance()->GetStageBlock( index + 1 )->GetDice()->GetChainNo()].chainDiceNum + 1 >= pip )
	{
		CStageBlockManager::GetInstance()->GetStageBlock( index )->GetDice()->SetChainNo( m_chain[CStageBlockManager::GetInstance()->GetStageBlock( index + 1 )->GetDice()->GetChainNo()].chainNo );
		return true;
	}

	// ���̃_�C�X�Ƃ̔���
	if(  index % m_xNum != 0 && 
		CStageBlockManager::GetInstance()->GetIsOnDice( index -1 ) == true &&
		CStageBlockManager::GetInstance()->GetStageBlock( index - 1 )->GetDice()->GetIsChain() == true &&
		CStageBlockManager::GetInstance()->GetStageBlock( index - 1 )->GetDice()->GetPip() == pip &&
		m_chain[CStageBlockManager::GetInstance()->GetStageBlock( index - 1 )->GetDice()->GetChainNo()].chainDiceNum + 1 >= pip ) 
	{
		CStageBlockManager::GetInstance()->GetStageBlock( index )->GetDice()->SetChainNo( m_chain[CStageBlockManager::GetInstance()->GetStageBlock( index - 1 )->GetDice()->GetChainNo()].chainNo );
		return true;
	}

	// �O�̃_�C�X�Ƃ̔���
	// �|���肷�邽�߂ɃL���X�g
	if( (int)(index - m_zNum) >= -1 && 
		CStageBlockManager::GetInstance()->GetIsOnDice( index - m_zNum ) == true &&
		CStageBlockManager::GetInstance()->GetStageBlock( index - m_zNum )->GetDice()->GetIsChain() == true &&
		CStageBlockManager::GetInstance()->GetStageBlock( index - m_zNum )->GetDice()->GetPip() == pip &&
		m_chain[CStageBlockManager::GetInstance()->GetStageBlock( index - m_zNum )->GetDice()->GetChainNo()].chainDiceNum + 1 >= pip )
	{
		CStageBlockManager::GetInstance()->GetStageBlock( index )->GetDice()->SetChainNo( m_chain[CStageBlockManager::GetInstance()->GetStageBlock( index - m_zNum )->GetDice()->GetChainNo()].chainNo );
		return true;
	}

	// ��̃_�C�X�Ƃ̔���
	if( index + m_zNum < CStageBlockManager::GetInstance()->GetDiceNum() == true &&
		CStageBlockManager::GetInstance()->GetIsOnDice( index + m_zNum ) == true &&
		CStageBlockManager::GetInstance()->GetStageBlock( index + m_zNum )->GetDice()->GetIsChain() == true &&
		CStageBlockManager::GetInstance()->GetStageBlock( index + m_zNum )->GetDice()->GetPip() == pip && 
		m_chain[CStageBlockManager::GetInstance()->GetStageBlock( index + m_zNum )->GetDice()->GetChainNo()].chainDiceNum + 1 >= pip )
	{
		CStageBlockManager::GetInstance()->GetStageBlock( index )->GetDice()->SetChainNo( m_chain[CStageBlockManager::GetInstance()->GetStageBlock( index + m_zNum )->GetDice()->GetChainNo()].chainNo );
		return true;
	}
	return false;
}