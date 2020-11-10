
#include "CUserManager.h"

const std::string USER_ID = "1234abcd";
const std::string USER_PASS = "abcd1234";

//----------------------------------------------------
// コンストラクタ
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
// デストラクタ
//----------------------------------------------------
CUserManager::~CUserManager( void )
{
	SAFE_DELETE( m_pHighScore );
	SAFE_DELETE( m_pGameScore );
	SAFE_DELETE( m_pSqlScoreManager );
	SAFE_DELETE( m_pSqlUserManager );
}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
bool CUserManager::Init( void )
{
	m_pHighScore->Init();
	m_pGameScore->Init();

	return true;
}

//----------------------------------------------------
// ログイン
//----------------------------------------------------
bool CUserManager::Login( void )
{
	// 既にログインしているかどうか
	if( m_isLogin == false )
	{
		if( m_pSqlUserManager->Login( &USER_ID, &USER_PASS ) == false )
		{
			return false;
		}
	}

	// ログイン成功時にUSERIDとUSERPASSを設定しハイスコアをメンバにセット
	m_pSqlScoreManager->SetUserInfo( m_pSqlUserManager->GetIDUser(), m_pSqlUserManager->GetNameUser() );
	m_pHighScore = m_pSqlScoreManager->GetScore( m_pHighScore );
	return true;
}

//----------------------------------------------------
// ゲームのスコアの初期化
//----------------------------------------------------
bool CUserManager::InitGameScore( void )
{
	m_pGameScore->Init();

	return true;
}

//----------------------------------------------------
// ゲームスコアのセット
//----------------------------------------------------
void CUserManager::SetGameScore( CScore* pScore )
{
	::CopyMemory( m_pGameScore, pScore, sizeof( CScore ) );
}

//----------------------------------------------------
// スコアの更新
//----------------------------------------------------
bool CUserManager::UpdateScore( void )
{
	std::string updateColumn = "";
	char work[256] = "";
	bool isUpdate = false;

	// レコード
	if( this->RecordComparision() == true )
	{
		itoa( m_pHighScore->m_record ,work , 10 );
		updateColumn += COMBINE_STRING( 2, "record =" , work );  
		isUpdate = true;
	}

	// ①の目
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

	// ②の目
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

	// ③の目
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

	// ④の目
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

	// ⑤の目
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

	// ⑥の目
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

	// マックスチェイン
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

	// 更新フラグがONなら更新
	if( isUpdate == true )
		m_pSqlScoreManager->UpdateHighScore( &updateColumn );

	return true;
}

//----------------------------------------------------
// レコードの比較
//----------------------------------------------------
bool CUserManager::RecordComparision( void )
{
	if( m_pGameScore->m_record > m_pHighScore->m_record )
	{
		// 更新
		m_pHighScore->m_record = m_pGameScore->m_record;
		return true;
	}
	return false;
}

//----------------------------------------------------
// ①の目の比較
//----------------------------------------------------
bool CUserManager::OnePipComparision( void )
{
	if( m_pGameScore->m_oneChainNum > m_pHighScore->m_oneChainNum )
	{
		// 更新
		m_pHighScore->m_oneChainNum = m_pGameScore->m_oneChainNum;
		return true;
	}
	return false;
}

//----------------------------------------------------
// ②の目の比較
//----------------------------------------------------
bool CUserManager::TwoPipComparision( void )
{
	if( m_pGameScore->m_twoChainNum > m_pHighScore->m_twoChainNum )
	{
		// 更新
		m_pHighScore->m_twoChainNum = m_pGameScore->m_twoChainNum;
		return true;
	}
	return false;
}

//----------------------------------------------------
// ③の目の比較
//----------------------------------------------------
bool CUserManager::ThreePipComparision( void )
{
	if( m_pGameScore->m_threeChainNum > m_pHighScore->m_threeChainNum )
	{
		// 更新
		m_pHighScore->m_threeChainNum = m_pGameScore->m_threeChainNum;
		return true;
	}
	return false;
}

//----------------------------------------------------
// ④の目の比較
//----------------------------------------------------
bool CUserManager::FourPipComparision( void )
{
	if( m_pGameScore->m_fourChainNum > m_pHighScore->m_fourChainNum )
	{
		// 更新
		m_pHighScore->m_fourChainNum = m_pGameScore->m_fourChainNum;
		return true;
	}
	return false;
}

//----------------------------------------------------
// ⑤の目の比較
//----------------------------------------------------
bool CUserManager::FivePipComparision( void )
{
	if( m_pGameScore->m_fiveChainNum > m_pHighScore->m_fiveChainNum )
	{
		// 更新
		m_pHighScore->m_fiveChainNum = m_pGameScore->m_fiveChainNum;
		return true;
	}
	return false;
}

//----------------------------------------------------
// ⑥の目の比較
//----------------------------------------------------
bool CUserManager::SixPipComparision( void )
{
	if( m_pGameScore->m_sixChainNum > m_pHighScore->m_sixChainNum )
	{
		// 更新
		m_pHighScore->m_sixChainNum = m_pGameScore->m_sixChainNum;
		return true;
	}
	return false;
}

//----------------------------------------------------
// マックスチェインの比較
//----------------------------------------------------
bool CUserManager::MaxChainComparision( void )
{
	if( m_pGameScore->m_chainNum > m_pHighScore->m_chainNum )
	{
		// 更新
		m_pHighScore->m_chainNum = m_pGameScore->m_chainNum;
		return true;
	}
	return false;
}