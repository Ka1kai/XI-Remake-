
#include "CUserManager.h"

const std::string USER_ID = "1234abcd";
const std::string USER_PASS = "abcd1234";

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CUserManager::CUserManager( void )
{
	m_pHighScore = new CScore;
	m_pGameScore = new CScore;

	this->Init();

	m_isLogin = false;

	m_pSqlScoreManager = new CMySQLScoreManager;
	m_pSqlUserManager = new CMySQLUserManager;
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
CUserManager::~CUserManager( void )
{
	SAFE_DELETE( m_pHighScore );
	SAFE_DELETE( m_pGameScore );
	SAFE_DELETE( m_pSqlScoreManager );
	SAFE_DELETE( m_pSqlUserManager );
}

//----------------------------------------------------
// ������
//----------------------------------------------------
bool CUserManager::Init( void )
{
	m_pHighScore->Init();
	m_pGameScore->Init();

	return true;
}

//----------------------------------------------------
// ���O�C��
//----------------------------------------------------
bool CUserManager::Login( void )
{
	// ���Ƀ��O�C�����Ă��邩�ǂ���
	if( m_isLogin == false )
	{
		if( m_pSqlUserManager->Login( &USER_ID, &USER_PASS ) == false )
		{
			return false;
		}
	}

	// ���O�C����������USERID��USERPASS��ݒ肵�n�C�X�R�A�������o�ɃZ�b�g
	m_pSqlScoreManager->SetUserInfo( m_pSqlUserManager->GetIDUser(), m_pSqlUserManager->GetNameUser() );
	m_pHighScore = m_pSqlScoreManager->GetScore( m_pHighScore );
	return true;
}

//----------------------------------------------------
// �Q�[���̃X�R�A�̏�����
//----------------------------------------------------
bool CUserManager::InitGameScore( void )
{
	m_pGameScore->Init();

	return true;
}

//----------------------------------------------------
// �Q�[���X�R�A�̃Z�b�g
//----------------------------------------------------
void CUserManager::SetGameScore( CScore* pScore )
{
	::CopyMemory( m_pGameScore, pScore, sizeof( CScore ) );
}

//----------------------------------------------------
// �X�R�A�̍X�V
//----------------------------------------------------
bool CUserManager::UpdateScore( void )
{
	std::string updateColumn = "";
	char work[256] = "";
	bool isUpdate = false;

	// ���R�[�h
	if( this->RecordComparision() == true )
	{
		itoa( m_pHighScore->m_record ,work , 10 );
		updateColumn += COMBINE_STRING( 2, "record =" , work );  
		isUpdate = true;
	}

	// �@�̖�
	if( this->OnePipComparision() == true )
	{
		itoa( m_pHighScore->m_oneChainNum, work, 10 );
		if( isUpdate == false )
		{
			updateColumn += COMBINE_STRING( 2, "onePip =", work );
			isUpdate = true;
		}
		else
		{
			updateColumn += COMBINE_STRING( 2, ", onePip =", work );
		}
	}

	// �A�̖�
	if( this->TwoPipComparision() == true )
	{
		itoa( m_pHighScore->m_twoChainNum, work, 10 );
		if( isUpdate == false )
		{
			updateColumn += COMBINE_STRING( 2, "twoPip =", work );
			isUpdate = true;
		}
		else
		{
			updateColumn += COMBINE_STRING( 2, ", twoPip =", work );
		}
	}

	// �B�̖�
	if( this->ThreePipComparision() == true )
	{
		itoa( m_pHighScore->m_threeChainNum, work, 10 );
		if( isUpdate == false )
		{
			updateColumn += COMBINE_STRING( 2, "threePip =", work );
			isUpdate = true;
		}
		else
		{
			updateColumn += COMBINE_STRING( 2, ", threePip =", work );
		}
	}

	// �C�̖�
	if( this->FourPipComparision() == true )
	{
		itoa( m_pHighScore->m_fourChainNum, work, 10 );
		if( isUpdate == false )
		{
			updateColumn += COMBINE_STRING( 2, "fourPip =", work );
			isUpdate = true;
		}
		else
		{
			updateColumn += COMBINE_STRING( 2, ", fourPip =", work );
		}
	}

	// �D�̖�
	if( this->FivePipComparision() == true )
	{
		itoa( m_pHighScore->m_fiveChainNum, work, 10 );
		if( isUpdate == false )
		{
			updateColumn += COMBINE_STRING( 2, "fivePip =", work );
			isUpdate = true;
		}
		else
		{
			updateColumn += COMBINE_STRING( 2, ", fivePip =", work );
		}
	}

	// �E�̖�
	if( this->SixPipComparision() == true )
	{
		itoa( m_pHighScore->m_sixChainNum, work, 10 );
		if( isUpdate == false )
		{
			updateColumn += COMBINE_STRING( 2, "sixPip =", work );
			isUpdate = true;
		}
		else
		{
			updateColumn += COMBINE_STRING( 2, ", sixPip =", work );
		}
	}

	// �}�b�N�X�`�F�C��
	if( this->MaxChainComparision() == true )
	{
		itoa( m_pHighScore->m_chainNum, work, 10 );
		if( isUpdate == false )
		{
			updateColumn += COMBINE_STRING( 2 , "MaxChain =", work );
			isUpdate = true;
		}
		else
		{
			updateColumn += COMBINE_STRING( 2, ", MaxChain =", work );
		}
	}

	// �X�V�t���O��ON�Ȃ�X�V
	if( isUpdate == true )
		m_pSqlScoreManager->UpdateHighScore( &updateColumn );

	return true;
}

//----------------------------------------------------
// ���R�[�h�̔�r
//----------------------------------------------------
bool CUserManager::RecordComparision( void )
{
	if( m_pGameScore->m_record > m_pHighScore->m_record )
	{
		// �X�V
		m_pHighScore->m_record = m_pGameScore->m_record;
		return true;
	}
	return false;
}

//----------------------------------------------------
// �@�̖ڂ̔�r
//----------------------------------------------------
bool CUserManager::OnePipComparision( void )
{
	if( m_pGameScore->m_oneChainNum > m_pHighScore->m_oneChainNum )
	{
		// �X�V
		m_pHighScore->m_oneChainNum = m_pGameScore->m_oneChainNum;
		return true;
	}
	return false;
}

//----------------------------------------------------
// �A�̖ڂ̔�r
//----------------------------------------------------
bool CUserManager::TwoPipComparision( void )
{
	if( m_pGameScore->m_twoChainNum > m_pHighScore->m_twoChainNum )
	{
		// �X�V
		m_pHighScore->m_twoChainNum = m_pGameScore->m_twoChainNum;
		return true;
	}
	return false;
}

//----------------------------------------------------
// �B�̖ڂ̔�r
//----------------------------------------------------
bool CUserManager::ThreePipComparision( void )
{
	if( m_pGameScore->m_threeChainNum > m_pHighScore->m_threeChainNum )
	{
		// �X�V
		m_pHighScore->m_threeChainNum = m_pGameScore->m_threeChainNum;
		return true;
	}
	return false;
}

//----------------------------------------------------
// �C�̖ڂ̔�r
//----------------------------------------------------
bool CUserManager::FourPipComparision( void )
{
	if( m_pGameScore->m_fourChainNum > m_pHighScore->m_fourChainNum )
	{
		// �X�V
		m_pHighScore->m_fourChainNum = m_pGameScore->m_fourChainNum;
		return true;
	}
	return false;
}

//----------------------------------------------------
// �D�̖ڂ̔�r
//----------------------------------------------------
bool CUserManager::FivePipComparision( void )
{
	if( m_pGameScore->m_fiveChainNum > m_pHighScore->m_fiveChainNum )
	{
		// �X�V
		m_pHighScore->m_fiveChainNum = m_pGameScore->m_fiveChainNum;
		return true;
	}
	return false;
}

//----------------------------------------------------
// �E�̖ڂ̔�r
//----------------------------------------------------
bool CUserManager::SixPipComparision( void )
{
	if( m_pGameScore->m_sixChainNum > m_pHighScore->m_sixChainNum )
	{
		// �X�V
		m_pHighScore->m_sixChainNum = m_pGameScore->m_sixChainNum;
		return true;
	}
	return false;
}

//----------------------------------------------------
// �}�b�N�X�`�F�C���̔�r
//----------------------------------------------------
bool CUserManager::MaxChainComparision( void )
{
	if( m_pGameScore->m_chainNum > m_pHighScore->m_chainNum )
	{
		// �X�V
		m_pHighScore->m_chainNum = m_pGameScore->m_chainNum;
		return true;
	}
	return false;
}