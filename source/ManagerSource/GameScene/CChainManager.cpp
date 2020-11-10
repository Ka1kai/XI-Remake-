
#include "CChainManager.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CChainManager::CChainManager( void )
{
	// チェイン管理配列を初期化
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
// デストラクタ
//----------------------------------------------------
CChainManager::~CChainManager( void )
{
}

//----------------------------------------------------
// 初期化（毎回）
//----------------------------------------------------
bool CChainManager::Init( void )
{
	m_connectDiceNum = 0;			// 繋がったダイスの数を初期化
	m_connectDiceList.clear();		// 繋がったダイスの格納用リスト初期化

	// 全て判定していない状態にする
	for( int i = 0; i < BLOCK_DEFAULT_MAX_NUM; ++ i )
	{
		m_decisionBlock[i] = false;
	}

	this->SetSize();

	return true;
}

//----------------------------------------------------
// ブロック上のダイスのステータスを設定
//----------------------------------------------------
void CChainManager::SetStageBlockDiceStatus( UINT index )
{
	CStageBlockManager::GetInstance()->GetStageBlock( index )->GetDice()->SetStatus( e_statusStartDelete );
}

//----------------------------------------------------
// Chain処理
//----------------------------------------------------
void CChainManager::Chain( CONST UINT index )
{
	// 初期化
	this->Init();

	// 現在のメインダイスの上面を取得
	m_mainPip = CStageBlockManager::GetInstance()->GetStageBlock(index)->GetDice()->GetPip();
	
	// 1の場合は特別な処理
	if( m_mainPip == 1 )
	{
		if( this->CheckChain( index ) == true )
		{
			int oneNum = 0;
			this->CheckOne( index );	// ステージ上の１の目を判定
			for( auto iterator = m_connectDiceList.begin(); iterator != m_connectDiceList.end(); ++ iterator )
			{
				(*iterator)->SetStatus( DICE_STATUS::e_statusStartDelete );	// 消えるアニメーションにする
				oneNum ++;
			}

			// スコア
			m_pScore->m_record += m_chain[ CStageBlockManager::GetInstance()->GetStageBlock(index)->GetDice()->GetChainNo() ].chainNum * oneNum;
		
			// １を消した数を更新
			m_pScore->PipScoreAdd( m_mainPip, oneNum );
		}
	}

	// 周りの面がチェインしていて上面が同じだったらこのダイスもチェイン中にする
	else if( this->CheckChain( index, m_mainPip ) == true )
	{
		int chainNo = CStageBlockManager::GetInstance()->GetStageBlock( index )->GetDice()->GetChainNo();

		// 自分自身のブロックは判定済みにしておく
		m_decisionBlock[ index ] = true;
		m_connectDiceNum ++;				
		m_connectDiceList.push_back( CStageBlockManager::GetInstance()->GetStageBlock( index )->GetDice() );

		// 周りのダイス（チェインしていない部分）判定
		this->CheckAround( index );

		// チェイン管理用配列の更新
		m_chain[ chainNo ].chainNum ++;
		m_chain[ chainNo ].chainDiceNum += m_connectDiceNum;

		// 消えるアニメーションに遷移させる
		for( auto iterator = m_connectDiceList.begin(); iterator != m_connectDiceList.end(); ++ iterator )
		{
			(*iterator)->SetChainNo( chainNo );	// チェイン番号をセット
			(*iterator)->SetIsChain( true );	// チェイン中に設定
			(*iterator)->SetStatus( DICE_STATUS::e_statusStartDelete );
			// プレイヤーの状態遷移
			CPlayerManager::GetInstance()->SetPlayerStatus( ePlayerStatus::eOnDiceDeleteStart );
		}
		// スコアの設定
		// スコア( 目 * ダイスの数 * チェイン数 + 1 )
		m_pScore->m_record += m_mainPip * m_chain[ chainNo ].chainDiceNum * m_chain[ chainNo ].chainNum;

		// 消した数更新
		m_pScore->PipScoreAdd( m_mainPip, 1 );

		// マックスチェイン数更新
		if( m_pScore->m_chainNum <= m_chain[chainNo].chainNum )
		{
			m_pScore->m_chainNum = m_chain[chainNo].chainNum;
		}
	}
	
	// 1以外の場合は繋がったダイスの数によって判定
	else 
	{
		// 自分自身のブロックは判定済みにしておく
		m_decisionBlock[ index ] = true;
		m_connectDiceNum ++;				
		m_connectDiceList.push_back( CStageBlockManager::GetInstance()->GetStageBlock( index )->GetDice() );

		// 周りのダイス判定
		this->CheckAround( index );

		// 繋がったダイスがメインダイスの上面より多い場合は消える
		if( m_mainPip <= m_connectDiceNum )
		{
			// チェイン管理配列にセット
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

			// 消えるアニメーションに遷移させる
			for( auto iterator = m_connectDiceList.begin(); iterator != m_connectDiceList.end(); ++ iterator )
			{
				(*iterator)->SetChainNo( chainNo );	// チェイン番号をセット
				(*iterator)->SetIsChain( true );	// チェイン中に設定
				(*iterator)->SetStatus( DICE_STATUS::e_statusStartDelete );
				
				// メインのダイスが消えるアニメーションに遷移したらプレイヤーの状態を変える
				if( (*iterator)->GetIndexNo() == CStageBlockManager::GetInstance()->GetStageBlock( index )->GetDice()->GetIndexNo() )
				{
					CPlayerManager::GetInstance()->SetPlayerStatus( ePlayerStatus::eOnDiceDeleteStart );
				}
			}

			// スコアの処理
			// スコア( 目 * ダイスの数 * チェイン数 + 1 )
			m_pScore->m_record += m_mainPip * m_chain[chainNo].chainDiceNum *  m_chain[chainNo].chainNum;

			// 消した数更新
			m_pScore->PipScoreAdd( m_mainPip, m_chain[chainNo].chainDiceNum );

			// マックスチェイン数更新
			if( m_pScore->m_chainNum <= m_chain[chainNo].chainNum )
			{
				m_pScore->m_chainNum = m_chain[chainNo].chainNum;
			}
		}
	}
}

//----------------------------------------------------
// 4方向とのダイスの判定(再帰関数)
//----------------------------------------------------
int CChainManager::CheckAround( CONST UINT index )
{
	// 右判定
	if( this->CheckRight( index ) )
	{
		this->CheckAround( index + 1 );
	}

	// 左のダイスとの判定
	if( this->CheckLeft( index ) ) 
	{
		this->CheckAround( index - 1 );
	}

	// 前のダイスとの判定
	if( this->CheckFront( index ) )
	{
		this->CheckAround( index - m_zNum );
	}

	// 後のダイスとの判定
	if( this->CheckDown( index ) )
	{
		this->CheckAround( index + m_zNum );
	}

	return true;

}

//----------------------------------------------------
// 右方向の判定
//----------------------------------------------------
bool CChainManager::CheckRight( UINT index )
{
	// 添え字が一番右ではないか，右にダイスがあるか，まだ判定していないブロックか,まだチェインしていないダイスかどうか判定
	if( index % m_xNum != m_xNum - 1 && CStageBlockManager::GetInstance()->GetIsOnDice( index + 1 ) == true && 
		m_decisionBlock[ index + 1 ] == false  && CStageBlockManager::GetInstance()->GetStageBlock( index + 1 )->GetDice()->GetIsChain() == false )
	{
		if( m_mainPip == CStageBlockManager::GetInstance()->GetStageBlock(index + 1)->GetDice()->GetPip() && 
			CStageBlockManager::GetInstance()->GetStageBlock( index + 1 )->GetDice()->GetStatus() == e_statusNormal )
		{		
			// 見つかった場合は判定済みにしカウントしてリストに追加
			m_decisionBlock[ index + 1 ] = true;
			m_connectDiceNum ++;
			m_connectDiceList.push_back( CStageBlockManager::GetInstance()->GetStageBlock( index + 1 )->GetDice() );
			return true;
		}
	}

	return false;
}

//----------------------------------------------------
// 左方向の判定
//----------------------------------------------------
bool CChainManager::CheckLeft( UINT index )
{
	// 添え字が一番左ではないか，左にダイスがあるか，まだ判定していないブロックか,まだチェインしていないかどうか判定
	if( index % m_xNum != 0 && CStageBlockManager::GetInstance()->GetIsOnDice( index - 1 ) == true &&
		m_decisionBlock[ index -1 ] == false && CStageBlockManager::GetInstance()->GetStageBlock( index - 1 )->GetDice()->GetIsChain() == false )
	{   // メインのダイスの上面と左のダイスの上面が同じかどうか，横のダイスが通常状態か判定
		if( m_mainPip == CStageBlockManager::GetInstance()->GetStageBlock( index - 1 )->GetDice()->GetPip() && 
			CStageBlockManager::GetInstance()->GetStageBlock( index - 1 )->GetDice()->GetStatus() == e_statusNormal )
		{		
			// 見つかった場合は判定済みにしカウントしてリストに追加
			m_decisionBlock[ index - 1 ] = true;
			m_connectDiceNum ++;
			m_connectDiceList.push_back( CStageBlockManager::GetInstance()->GetStageBlock( index - 1 )->GetDice() );
			return true;
		}
	}
	return false;
}

//----------------------------------------------------
// 前方向の判定
//----------------------------------------------------
bool CChainManager::CheckFront( UINT index )
{
	int workIndex = index;
	// メインダイスが一番前ではないか，前にダイスがあるか，まだ判定していないブロックか,まだチェインしていないかどうか判定
	if( workIndex - m_zNum >= -1  && CStageBlockManager::GetInstance()->GetIsOnDice( index - m_zNum ) == true && 
		m_decisionBlock[ index - m_zNum ] == false && CStageBlockManager::GetInstance()->GetStageBlock( index - m_zNum )->GetDice()->GetIsChain() == false )
	{
		if( m_mainPip == CStageBlockManager::GetInstance()->GetStageBlock( index - m_zNum )->GetDice()->GetPip() && 
			CStageBlockManager::GetInstance()->GetStageBlock( index - m_zNum )->GetDice()->GetStatus() == e_statusNormal )
		{		
			// 見つかった場合は判定済みにしカウントしてリストに追加
			m_decisionBlock[ index - m_zNum ] = true;
			m_connectDiceNum ++;
			m_connectDiceList.push_back( CStageBlockManager::GetInstance()->GetStageBlock( index - m_zNum )->GetDice() );
			return true;
		}
	}
	return false;
}

//----------------------------------------------------
// 後方向の判定
//----------------------------------------------------
bool CChainManager::CheckDown( UINT index )
{
	// メインダイスが一番後ではないか，後にダイスがあるか，まだ判定していないブロックか,まだチェインしていないか判定
	if( index + m_zNum < CStageBlockManager::GetInstance()->GetDiceNum()  && CStageBlockManager::GetInstance()->GetIsOnDice( index + m_zNum ) == true && 
		m_decisionBlock[ index + m_zNum ] == false && CStageBlockManager::GetInstance()->GetStageBlock( index + m_zNum )->GetDice()->GetIsChain() == false )
	{
		if( m_mainPip == CStageBlockManager::GetInstance()->GetStageBlock( index + m_zNum )->GetDice()->GetPip() && 
			CStageBlockManager::GetInstance()->GetStageBlock( index + m_zNum )->GetDice()->GetStatus() == e_statusNormal )
		{		
			// 見つかった場合は判定済みにしカウントしてリストに追加
			m_decisionBlock[ index + m_zNum ] = true;
			m_connectDiceNum ++;
			m_connectDiceList.push_back( CStageBlockManager::GetInstance()->GetStageBlock( index + m_zNum )->GetDice() );
			return true;
		}
	}

	return false;
}

//----------------------------------------------------
// １の目かどうかを判定
//----------------------------------------------------
void CChainManager::CheckOne( CONST UINT index )
{
	// ステージに置かれているダイスが１かどうか判定してリストに入れる
	for( int i = 0; i < MAX_DICE_NUM; ++ i )
	{
		// 自分の添え字は判定しない
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
// 周りの面がチェインしているかどうか判定
//----------------------------------------------------
bool CChainManager::CheckChain( CONST UINT index )
{
	// 右判定
	if( index % m_xNum != m_xNum - 1 &&
		CStageBlockManager::GetInstance()->GetIsOnDice( index + 1 ) == true &&
		CStageBlockManager::GetInstance()->GetStageBlock( index + 1 )->GetDice()->GetIsChain() == true )
	{
		return true;
	}

	// 左のダイスとの判定
	if(  index % m_xNum != 0 && 
		CStageBlockManager::GetInstance()->GetIsOnDice( index -1 ) == true &&
		CStageBlockManager::GetInstance()->GetStageBlock( index - 1 )->GetDice()->GetIsChain() == true ) 
	{
		return true;
	}

	// 前のダイスとの判定
	if( index - m_zNum >= -1 && 
		CStageBlockManager::GetInstance()->GetIsOnDice( index - m_zNum ) == true &&
		CStageBlockManager::GetInstance()->GetStageBlock( index - m_zNum )->GetDice()->GetIsChain() == true )
	{
		return true;
	}

	// 後のダイスとの判定
	if( index + m_zNum < CStageBlockManager::GetInstance()->GetDiceNum() == true &&
		CStageBlockManager::GetInstance()->GetIsOnDice( index + m_zNum ) == true &&
		CStageBlockManager::GetInstance()->GetStageBlock( index + m_zNum )->GetDice()->GetIsChain() == true )
	{
		return true;
	}

	return false;
}

//----------------------------------------------------
// 周り面が上面番号でチェインしているかどうか判定
//----------------------------------------------------
bool CChainManager::CheckChain( CONST UINT index, CONST UINT pip )
{
	// 右判定
	if( index % m_xNum != m_xNum - 1 &&
		CStageBlockManager::GetInstance()->GetIsOnDice( index + 1 ) == true &&
		CStageBlockManager::GetInstance()->GetStageBlock( index + 1 )->GetDice()->GetIsChain() == true &&
		CStageBlockManager::GetInstance()->GetStageBlock( index + 1 )->GetDice()->GetPip() == pip &&
		m_chain[CStageBlockManager::GetInstance()->GetStageBlock( index + 1 )->GetDice()->GetChainNo()].chainDiceNum + 1 >= pip )
	{
		CStageBlockManager::GetInstance()->GetStageBlock( index )->GetDice()->SetChainNo( m_chain[CStageBlockManager::GetInstance()->GetStageBlock( index + 1 )->GetDice()->GetChainNo()].chainNo );
		return true;
	}

	// 左のダイスとの判定
	if(  index % m_xNum != 0 && 
		CStageBlockManager::GetInstance()->GetIsOnDice( index -1 ) == true &&
		CStageBlockManager::GetInstance()->GetStageBlock( index - 1 )->GetDice()->GetIsChain() == true &&
		CStageBlockManager::GetInstance()->GetStageBlock( index - 1 )->GetDice()->GetPip() == pip &&
		m_chain[CStageBlockManager::GetInstance()->GetStageBlock( index - 1 )->GetDice()->GetChainNo()].chainDiceNum + 1 >= pip ) 
	{
		CStageBlockManager::GetInstance()->GetStageBlock( index )->GetDice()->SetChainNo( m_chain[CStageBlockManager::GetInstance()->GetStageBlock( index - 1 )->GetDice()->GetChainNo()].chainNo );
		return true;
	}

	// 前のダイスとの判定
	// －判定するためにキャスト
	if( (int)(index - m_zNum) >= -1 && 
		CStageBlockManager::GetInstance()->GetIsOnDice( index - m_zNum ) == true &&
		CStageBlockManager::GetInstance()->GetStageBlock( index - m_zNum )->GetDice()->GetIsChain() == true &&
		CStageBlockManager::GetInstance()->GetStageBlock( index - m_zNum )->GetDice()->GetPip() == pip &&
		m_chain[CStageBlockManager::GetInstance()->GetStageBlock( index - m_zNum )->GetDice()->GetChainNo()].chainDiceNum + 1 >= pip )
	{
		CStageBlockManager::GetInstance()->GetStageBlock( index )->GetDice()->SetChainNo( m_chain[CStageBlockManager::GetInstance()->GetStageBlock( index - m_zNum )->GetDice()->GetChainNo()].chainNo );
		return true;
	}

	// 後のダイスとの判定
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