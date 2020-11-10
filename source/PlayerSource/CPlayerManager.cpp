
#include "CPlayerManager.h"

const float ConstPlayerSpeed = 0.2f;
const float ConstPlayerToDiceDistanceX = 0.5f;
const float ConstPlayerToDiceDistanceZ = 0.3f;

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CPlayerManager::CPlayerManager( void )
{
	m_pPlayer = new CPlayer;

	m_pPlayerFilePath = PLAYER_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pPlayerFilePath );
}

//----------------------------------------------------
// デストラクタ 
//----------------------------------------------------
CPlayerManager::~CPlayerManager( void )
{
	SAFE_DELETE_ALLAY( m_pPlayer );
}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
bool CPlayerManager::Init( void )
{
	m_pPlayer->Init();

	// 当たり判定用データ作成(ダイスの↑)
	CDebugMode::m_pPlayerBox.CreateBox( &m_pPlayer->GetAABB()->size );
	CDebugMode::m_pPlayerBox.Init();
	CDebugMode::m_pPlayerBox.SetDiffuse( 0, 0, 0, 150 );
	CDebugMode::m_pPlayerBox.SetAmbient( 0, 0, 255, 0 );

	return true;
}

//----------------------------------------------------
// 終了
//----------------------------------------------------
bool CPlayerManager::Uninit( void )
{
	return true;
}

//----------------------------------------------------
// 描画
//----------------------------------------------------
void CPlayerManager::Draw( void )
{
	CDirectDrawSystem::GetInstance()->DrawSprite( CResourceManager::GetInstance()->GetTexture( m_pPlayerFilePath )->Get(),m_pPlayer->GetVertex(),m_pPlayer->GetWorldMtx() );
}

//----------------------------------------------------
// 処理
//----------------------------------------------------
void CPlayerManager::Run( void )
{
	this->Move();

	switch( m_pPlayer->GetPlayerStatus() )
	{
	case ePlayerStatus::eOnStage:
		break;

	// ダイス消え始め中
	case ePlayerStatus::eOnDiceDeleteStart:
		this->Down();
		break;

	// ダイス消え中
	case ePlayerStatus::eOnDiceDelete:
		break;

	// ダイス出現中
	case ePlayerStatus::eOnDiceAppear:
		this->Up( DICE_UP_SPEED );
		break;
	}
}

//----------------------------------------------------
// 移動
//----------------------------------------------------
void CPlayerManager::Move( void )
{
	// 前移動
	if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_UP ) || 
		CJoyStick::GetInstance()->GetPressButton( 0, XINPUT_GAMEPAD_DPAD_UP ))
	{
		this->MoveFront();
	}

	// 後移動
	if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_DOWN ) ||
		CJoyStick::GetInstance()->GetPressButton( 0, XINPUT_GAMEPAD_DPAD_DOWN ) )
	{
		this->MoveBack();
	}

	// 右移動
	if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_RIGHT ) ||
		CJoyStick::GetInstance()->GetPressButton( 0, XINPUT_GAMEPAD_DPAD_RIGHT ) )
	{
		this->MoveRight();
	}

	// 左移動
	if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_LEFT ) ||
		CJoyStick::GetInstance()->GetPressButton( 0, XINPUT_GAMEPAD_DPAD_LEFT ) )
	{
		this->MoveLeft();
	}
}

//----------------------------------------------------
// 前移動 
//----------------------------------------------------
void CPlayerManager::MoveFront( void )
{
	// ステージの一番前との判定
	if( m_pPlayer->GetZPos() <= CStageBlockManager::GetInstance()->GetZSize() )
	{
		// プレイヤーのインデックス番号取得
		UINT playerIndex = CStageBlockManager::GetInstance()->GetIndexToPlayerPos( m_pPlayer->GetXPos(), m_pPlayer->GetZPos() );

		// プレイヤーの状態によって前移動の動きを変える
		switch( m_pPlayer->GetPlayerStatus() )
		{
		// ダイス上
		case ePlayerStatus::eOnDice:
			// 後ろ移動していたら前には動けない
			if( CDiceObjManager::GetInstance()->GetMainDice()->rollState == DICE_ROLLSTATE_BACK )
			{
				break;
			}
			// ダイスの前の方まで移動したら
			if( this->IsHitPlayerToDiceZ( ConstPlayerToDiceDistanceZ + 0.2f, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true ) 
			{
				// ダイスが移動中だったらプレイヤーが飛び出ないように設定
				if( CDiceObjManager::GetInstance()->GetMainDice()->rollState != eDiceRollState::DICE_ROLLSTATE_NONE )
				{
					break;
				}
				else if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 7 ) == false ||
						 CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 7 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
				{
					// 前にダイスがない場合はダイス移動
					CDiceObjManager::GetInstance()->MoveFront();
					m_pPlayer->SetMoveStatus( ePlayerMoveStatus::eMoveFront );
				}
				else if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 7 ) == true &&
					   ( CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 7 )->GetDice()->GetStatus() == DICE_STATUS::e_statusStartAppear || 
						 CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 7 )->GetDice()->GetStatus() == DICE_STATUS::e_statusDelete ) )
				{
					// 前のダイスが出現し始めもしくは消え中だったらダイス移動
					CDiceObjManager::GetInstance()->MoveFront();
					m_pPlayer->SetMoveStatus( ePlayerMoveStatus::eMoveFront );				
				}
			}
		
			m_pPlayer->MoveFront( ConstPlayerSpeed );			// 移動

			break;

		// 出現し始め
		case ePlayerStatus::eOnDiceAppearStart:
			// 出現し始め中にダイスの前の方まで移動したら
			if( this->IsHitPlayerToDiceZ( ConstPlayerToDiceDistanceZ + 0.2f, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true ) 
			{
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 7 ) == false )
				{
					// ダイスが前にない場合はステージにのせる
					m_pPlayer->SetSpritePos( m_pPlayer->GetXPos(), 0.0f, m_pPlayer->GetZPos() );
					m_pPlayer->SetPlayerStatus( ePlayerStatus::eOnStage );	// ステージの上判定にする
					m_pDiceInfoManager->SetIsExist( false );
				}
				else if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex -7 ) == true &&
					     CStageBlockManager::GetInstance()->GetStageBlock( playerIndex -7 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
				{
					// ダイスが前にあってダイスが通常状態の場合は移動できない
					break;
				}
			}
			m_pPlayer->MoveFront( ConstPlayerSpeed );			// 移動
			break;

		// 出現中
		case ePlayerStatus::eOnDiceAppear:
			// 出現中にダイスの前の方まで移動したら
			if( this->IsHitPlayerToDiceZ( ConstPlayerToDiceDistanceZ + 0.2f, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true ) 
			{
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 7 ) == false )
				{
					break;
				}
			}
			m_pPlayer->MoveFront( ConstPlayerSpeed );			// 移動
			break;

		// 消え始め
		case ePlayerStatus::eOnDiceDeleteStart:
			// 消え始め中にダイスの前の方まで移動したら
			if( this->IsHitPlayerToDiceZ( ConstPlayerToDiceDistanceZ + 0.2f, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 7 ) == false )
				{
					// 動かさない
					break;
				}
			}
			m_pPlayer->MoveFront( ConstPlayerSpeed );			// 移動
			break;
		
		/// 消え中
		case ePlayerStatus::eOnDiceDelete:
			// 消え中にダイスの前の方まで移動したら
			if( this->IsHitPlayerToDiceZ( ConstPlayerToDiceDistanceZ + 0.2f, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true ) 
			{
				// 前にダイスがない場合はステージに乗せる
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 7 ) == false )
				{
					m_pPlayer->SetSpritePos( m_pPlayer->GetXPos(), 0.0f, m_pPlayer->GetZPos() );
					m_pPlayer->SetPlayerStatus( ePlayerStatus::eOnStage );	// ステージの上判定にする
					m_pDiceInfoManager->SetIsExist( false );
				}

				// 前のダイスの状態によって移動させない
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 7 ) == true &&
					CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 7 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
				{
					break;
				}
			}
			m_pPlayer->MoveFront( ConstPlayerSpeed );			// 移動
		break;	
		
		// ステージ上にいる
		case ePlayerStatus::eOnStage:	
			// プレイヤーが一番前の列にいたら移動のみ
			if( playerIndex <= 6  )
			{	
				m_pPlayer->MoveFront( ConstPlayerSpeed );
				break;
			}

			// もし目の前にダイスがあれば移動できない
			if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 7 ) == true && 
				CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 7 )->GetDice()->GetIsDice() == true &&
				CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 7 )->GetDice()->GetStatus() != DICE_STATUS::e_statusStartAppear &&
				CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 7 )->GetDice()->GetStatus() != DICE_STATUS::e_statusDelete )
			{
				if( !this->IsHitPlayerToDiceZ( ConstPlayerToDiceDistanceZ, CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 7 )->GetDice() ) )
				{
					// 目の前にダイスがあったら動かさない
					break;
				}
			}
			m_pPlayer->MoveFront( ConstPlayerSpeed );				// 移動
			break;

		default:
			break;
		}
	}

}

//----------------------------------------------------
// 後移動 
//----------------------------------------------------
void CPlayerManager::MoveBack( void )
{
	// ステージの一番後ろとの判定
	if( m_pPlayer->GetZPos() >= -CStageBlockManager::GetInstance()->GetZSize() )
	{
		// プレイヤーのインデックス番号取得
		UINT playerIndex = CStageBlockManager::GetInstance()->GetIndexToPlayerPos( m_pPlayer->GetXPos(), m_pPlayer->GetZPos() );

		// プレイヤーの状態によって後移動の動きを変える
		switch( m_pPlayer->GetPlayerStatus() )
		{
		// ダイス上
		case ePlayerStatus::eOnDice:	
			if( CDiceObjManager::GetInstance()->GetMainDice()->rollState == DICE_ROLLSTATE_FRONT )
			{
				break;
			}
			// ダイスの後ろまで移動したら
			if( this->IsHitPlayerToDiceZ ( -ConstPlayerToDiceDistanceZ + -0.2f, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				// ダイスが移動中の場合は飛び出ないようにする
				if( CDiceObjManager::GetInstance()->GetMainDice()->rollState != eDiceRollState::DICE_ROLLSTATE_NONE )
				{
					break;
				}
				else if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 7 ) == false ||
						 CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 7 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
				{
					// ダイスが後ろにない場合はダイスを移動
					CDiceObjManager::GetInstance()->MoveBack();
					m_pPlayer->SetMoveStatus( ePlayerMoveStatus::eMoveBack );
				}
				else if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 7 ) == true && 
					   ( CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 7 )->GetDice()->GetStatus() == DICE_STATUS::e_statusStartAppear ||
						 CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 7 )->GetDice()->GetStatus() == DICE_STATUS::e_statusDelete ) )
				{
					// 後ろのダイスが出現し始めもしくは消え中だったら移動可能
					CDiceObjManager::GetInstance()->MoveBack();
					m_pPlayer->SetMoveStatus( ePlayerMoveStatus::eMoveBack );
				}
			}

			m_pPlayer->MoveBack( ConstPlayerSpeed );	// 移動
			break;
		
		// 出現し始め
		case ePlayerStatus::eOnDiceAppearStart:		
			// 出現し始め中にダイスの後ろの方まで移動したら
			if( this->IsHitPlayerToDiceZ ( -ConstPlayerToDiceDistanceZ + - 0.2f, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 7 ) == false )
				{
					// 後ろにダイスがない場合はステージにのせる
					m_pPlayer->SetSpritePos( m_pPlayer->GetXPos(), 0.0f, m_pPlayer->GetZPos() );
					m_pPlayer->SetPlayerStatus( ePlayerStatus::eOnStage );	// ステージの上判定にする
					m_pDiceInfoManager->SetIsExist( false );
				}
				else if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex ) == true &&
						 CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 7 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
				{
					// 後ろにダイスがあって通常状態の場合は動かせない
					break;
				}	
			}
			m_pPlayer->MoveBack( ConstPlayerSpeed );	// 移動	
			break;

		// 出現中
		case ePlayerStatus::eOnDiceAppear:
			// 出現中にダイスの後ろの方まで移動したら
			if( this->IsHitPlayerToDiceZ ( -ConstPlayerToDiceDistanceZ + -0.2f, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				// ブロックが後ろにない場合は動かないし動かせない
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 7 ) == false )
				{
					break;
				}
			}
			m_pPlayer->MoveBack( ConstPlayerSpeed );	// 移動	
			break;

		// 消え始め
		case ePlayerStatus::eOnDiceDeleteStart:
			// 消え中にダイスの後ろの方まで移動したら
			if( this->IsHitPlayerToDiceZ ( -ConstPlayerToDiceDistanceZ + -0.2f, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 7 ) == false )
				{
					break;
				}
			}
			m_pPlayer->MoveBack( ConstPlayerSpeed );
			break;

		// 消え中
		case ePlayerStatus::eOnDiceDelete:
			// 消え中にダイスの後ろの方まで移動したら
			if( this->IsHitPlayerToDiceZ ( -ConstPlayerToDiceDistanceZ + -0.2f, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				// 後ろにダイスがない場合はステージにのせる
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 7 ) == false )
				{
					m_pPlayer->SetSpritePos( m_pPlayer->GetXPos(), 0.0f, m_pPlayer->GetZPos() );
					m_pPlayer->SetPlayerStatus( ePlayerStatus::eOnStage );	// ステージの上判定にする
					m_pDiceInfoManager->SetIsExist( false );
				}

				// 後ろのダイスの状態によって移動させない
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 7 ) == true &&
					CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 7 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
				{
					break;
				}
			}
			m_pPlayer->MoveBack( ConstPlayerSpeed );
			break;

		// ステージ上
		case ePlayerStatus::eOnStage:
			// プレイヤーが一番後の列にいたら
			if( playerIndex >= 42  )
			{
				m_pPlayer->MoveBack( ConstPlayerSpeed );
				break;
			}

			// もし後ろにダイスがあれば
			if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 7 ) == true && 
				CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 7 )->GetDice()->GetIsDice() == true &&
				CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 7 )->GetDice()->GetStatus() != DICE_STATUS::e_statusStartAppear &&
				CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 7 )->GetDice()->GetStatus() != DICE_STATUS::e_statusDelete )
			{
				if( !this->IsHitPlayerToDiceZ( -ConstPlayerToDiceDistanceZ, CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 7 )->GetDice() ) )
				{
					// 後ろにダイスがあったら動かさない
					break;
				}
				
			}
			// 移動
			m_pPlayer->MoveBack( ConstPlayerSpeed );
			break;

		default:
			break;
		}
	}
}

//----------------------------------------------------
// 右移動 
//----------------------------------------------------
void CPlayerManager::MoveRight( void )
{
	// ステージの右端かどうか
	if( m_pPlayer->GetXPos() <= CStageBlockManager::GetInstance()->GetXSize() )
	{
		// プレイヤーのインデックス番号取得
		UINT playerIndex = CStageBlockManager::GetInstance()->GetIndexToPlayerPos( m_pPlayer->GetXPos(), m_pPlayer->GetZPos() );

		switch( m_pPlayer->GetPlayerStatus() )
		{
		// ダイス上
		case ePlayerStatus::eOnDice:
			if( CDiceObjManager::GetInstance()->GetMainDice()->rollState == DICE_ROLLSTATE_LEFT )
			{
				break;
			}
			// ダイスの右の方まで移動したら判定
			if( this->IsHitPlayerToDiceX( ConstPlayerToDiceDistanceX, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				// ダイスが移動中の場合は飛び出さないように設定
				if( CDiceObjManager::GetInstance()->GetMainDice()->rollState != eDiceRollState::DICE_ROLLSTATE_NONE )	
				{
					break;
				}
				else if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 1 ) == false ||
						 CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 1 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )

				{
					// 右にダイスがない場合はダイス移動
					CDiceObjManager::GetInstance()->MoveRight();
					m_pPlayer->SetMoveStatus( ePlayerMoveStatus::eMoveRight  );
				}
				else if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 1 ) == true && 
					( CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 1 )->GetDice()->GetStatus() == DICE_STATUS::e_statusStartAppear ||
					  CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 1 )->GetDice()->GetStatus() == DICE_STATUS::e_statusDelete ) )
				{
					// ダイスが右にあって出現し始めもしくは消え中だったら移動可能
					CDiceObjManager::GetInstance()->MoveRight();
					m_pPlayer->SetMoveStatus( ePlayerMoveStatus::eMoveRight  );
				}
			}
			m_pPlayer->MoveRight( ConstPlayerSpeed );		// 移動
			break;

		// 出現し始め
		case ePlayerStatus::eOnDiceAppearStart:
			// 出現し始め中にダイスの右の方まで移動したら
			if( this->IsHitPlayerToDiceX( ConstPlayerToDiceDistanceX, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 1 ) == false )
				{
					// 右にダイスがない場合はステージにのせる
					m_pPlayer->SetSpritePos( m_pPlayer->GetXPos(), 0.0f, m_pPlayer->GetZPos() );
					m_pPlayer->SetPlayerStatus( ePlayerStatus::eOnStage );	// ステージの上判定にする
					m_pDiceInfoManager->SetIsExist( false );
				}
				else if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 1 ) == true &&
						 CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 1 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
				{
					// 右にダイスがあって通常状態の場合は動かせない
					break;
				}
			}
			m_pPlayer->MoveRight( ConstPlayerSpeed );		// 移動
			break;
		
		// 出現中
		case ePlayerStatus::eOnDiceAppear:			
			// 出現中にダイスの右の方まで移動したら
			if( this->IsHitPlayerToDiceX( ConstPlayerToDiceDistanceX, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				// 右にブロックがなかったら動かないし動かせない
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 1 ) == false )
				{
					break;
				}
			}
			m_pPlayer->MoveRight( ConstPlayerSpeed );		// 移動	
			break;

		// 消え始め
		case ePlayerStatus::eOnDiceDeleteStart:
			// 消え始め中にダイスの右の方まで移動したら
			if( this->IsHitPlayerToDiceX( ConstPlayerToDiceDistanceX, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 1 ) == false )
				{
					break;
				}
			}

			m_pPlayer->MoveRight( ConstPlayerSpeed );		// 移動
			break;

		// 消え中
		case ePlayerStatus::eOnDiceDelete:
			// 消え中にダイスの右の方まで移動したら
			if( this->IsHitPlayerToDiceX( ConstPlayerToDiceDistanceX, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				// 右にダイスがない場合はステージにのせる
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 1 ) == false )
				{
					m_pPlayer->SetSpritePos( m_pPlayer->GetXPos(), 0.0f, m_pPlayer->GetZPos() );
					m_pPlayer->SetPlayerStatus( ePlayerStatus::eOnStage );	// ステージの上判定にする
					m_pDiceInfoManager->SetIsExist( false );
				}

				// 右のダイスの状態によって移動させない
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 1 ) == true &&
					CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 1 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
				{
					break;
				}
			}
			m_pPlayer->MoveRight( ConstPlayerSpeed );		// 移動
			break;

		// ステージ上
		case ePlayerStatus::eOnStage:	
			// プレイヤーが一番右列にいたら判定しない
			if( ( ( playerIndex + 1 ) % 7 ) == 0 )
			{
				m_pPlayer->MoveRight( ConstPlayerSpeed );
				break;
			}

			// もし右にダイスがあれば
			if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex + 1 ) == true && 
				CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 1 )->GetDice()->GetIsDice() == true &&
				CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 1 )->GetDice()->GetStatus() != DICE_STATUS::e_statusStartAppear &&
				CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 1 )->GetDice()->GetStatus() != DICE_STATUS::e_statusDelete )
			{
				if( !this->IsHitPlayerToDiceX( ConstPlayerToDiceDistanceX + 1.5f, CStageBlockManager::GetInstance()->GetStageBlock( playerIndex + 1 )->GetDice() ) )
				{
					// 右にダイスがあったら動かさない
					break;
				}
			}
			// 移動
			m_pPlayer->MoveRight( ConstPlayerSpeed );

		default:
			break;
		}
	}
}

//----------------------------------------------------
// 左移動
//----------------------------------------------------
void CPlayerManager::MoveLeft( void )
{
	// ステージの左端との判定
	if( m_pPlayer->GetXPos() >= -CStageBlockManager::GetInstance()->GetXSize() )
	{
		// プレイヤーのインデックス番号取得
		UINT playerIndex = CStageBlockManager::GetInstance()->GetIndexToPlayerPos( m_pPlayer->GetXPos(), m_pPlayer->GetZPos() );

		switch( m_pPlayer->GetPlayerStatus() )
		{
		// ダイス上
		case ePlayerStatus::eOnDice:
			if( CDiceObjManager::GetInstance()->GetMainDice()->rollState == DICE_ROLLSTATE_RIGHT )
			{
				break;
			}
			// ダイスの左の方まで移動したら判定
			if( this->IsHitPlayerToDiceX( -ConstPlayerToDiceDistanceX, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{					
				// ダイスが移動中の場合は飛び出ないように設定
				if( CDiceObjManager::GetInstance()->GetMainDice()->rollState != eDiceRollState::DICE_ROLLSTATE_NONE )
				{	
					break;
				}
				else if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 1 ) == false ||
						 CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 1 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
				{
					// 左にダイスがない場合はダイスを移動
					CDiceObjManager::GetInstance()->MoveLeft();
					m_pPlayer->SetMoveStatus( ePlayerMoveStatus::eMoveLeft );
				}
				else if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 1 ) == true &&
					   ( CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 1 )->GetDice()->GetStatus() == DICE_STATUS::e_statusStartAppear ||
					     CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 1 )->GetDice()->GetStatus() == DICE_STATUS::e_statusDelete ) )
				{
					// 左のダイスが出現し始めもしくは消え中だったら移動可能
					CDiceObjManager::GetInstance()->MoveLeft();
					m_pPlayer->SetMoveStatus( ePlayerMoveStatus::eMoveLeft );
				}
			}
			m_pPlayer->MoveLeft( ConstPlayerSpeed );	// 移動
			break;

		// 出現し始め
		case ePlayerStatus::eOnDiceAppearStart:
			// 出現し始め中にダイスの左の方まで移動したら
			if( this->IsHitPlayerToDiceX( -ConstPlayerToDiceDistanceX, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 1 ) == false )
				{
					// 左にダイスがない場合はステージにのせる
					m_pPlayer->SetSpritePos( m_pPlayer->GetXPos(), 0.0f, m_pPlayer->GetZPos() );
					m_pPlayer->SetPlayerStatus( ePlayerStatus::eOnStage );	// ステージの上判定にする
					m_pDiceInfoManager->SetIsExist( false );
				}
				else if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 1 ) == true &&
						 CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 1 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
				{
					// 左にダイスがあって通常状態の場合は動かせない
					break;
				}
			}
			m_pPlayer->MoveLeft( ConstPlayerSpeed );	// 移動			
			break;

		// 出現中
		case ePlayerStatus::eOnDiceAppear:
			// 出現中にダイスの左の方まで移動したら
			if( this->IsHitPlayerToDiceX( -ConstPlayerToDiceDistanceX, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				// 左にブロックがなければ動かないし動かせない
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 1 ) == false )
				{
					break;
				}
			}
			m_pPlayer->MoveLeft( ConstPlayerSpeed );	// 移動
			break;

		// 消え始め
		case ePlayerStatus::eOnDiceDeleteStart:
			// 消え始め中にダイスの左の方まで移動したら
			if( this->IsHitPlayerToDiceX( -ConstPlayerToDiceDistanceX, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 1 ) == false )
				{
					break;
				}
			}
			m_pPlayer->MoveLeft( ConstPlayerSpeed );	// 移動		
			break;

		// 消え中
		case ePlayerStatus::eOnDiceDelete:
			// 消え中にダイスの左の方まで移動したら
			if( this->IsHitPlayerToDiceX( -ConstPlayerToDiceDistanceX, CDiceObjManager::GetInstance()->GetMainDice()->diceObj ) == true )
			{
				// 左にダイスがない場合はステージに乗せる
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 1 ) == false )
				{
					m_pPlayer->SetSpritePos( m_pPlayer->GetXPos(), 0.0f, m_pPlayer->GetZPos() );
					m_pPlayer->SetPlayerStatus( ePlayerStatus::eOnStage );	// ステージの上判定にする
					m_pDiceInfoManager->SetIsExist( false );
				}

				// 左のダイスの状態によって移動させない
				if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 1 ) == true &&
					CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 1 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
				{
					break;
				}
			}
			m_pPlayer->MoveLeft( ConstPlayerSpeed );	// 移動		
			break;

		case ePlayerStatus::eOnStage:

			// プレイヤーが一番左列にいたら判定しない
			if( playerIndex % 7 == 0 )
			{
				m_pPlayer->MoveLeft( ConstPlayerSpeed );
				break;
			}

			// もし左にダイスがあれば
			if( CStageBlockManager::GetInstance()->GetIsOnDice( playerIndex - 1 ) == true && 
				CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 1 )->GetDice()->GetIsDice() == true &&
				CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 1 )->GetDice()->GetStatus() != DICE_STATUS::e_statusStartAppear &&
				CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 1 )->GetDice()->GetStatus() != DICE_STATUS::e_statusDelete ) 
			{
				if( !this->IsHitPlayerToDiceX( -ConstPlayerToDiceDistanceX + -1.5f, CStageBlockManager::GetInstance()->GetStageBlock( playerIndex - 1 )->GetDice() ) )
				{
					// 左にダイスがあったら動かさない
					break;
				}
			}
			// 移動
			m_pPlayer->MoveLeft( ConstPlayerSpeed );

		default:
			break;
		}
	}
}

//----------------------------------------------------
// プレイヤーとダイスの判定(X判定)
//----------------------------------------------------
bool CPlayerManager::IsHitPlayerToDiceX( CONST  float distance, CDiceObj* dice )
{
	// 判定をずらしておく
	THITAABB playerAABB;
	::CopyMemory( &playerAABB, m_pPlayer->GetAABB(), sizeof( THITAABB ) );
	playerAABB.centerPos.x += distance;
	
	// ダイスの一定方向まで移動したら
	if( !CCollision::GetInstance()->IsHitAABB( &playerAABB, dice->GetAABB() ) )
	{
		// 当たっていない状態になった
		return true;
	}

	// 当たっている
	return false;
}

//----------------------------------------------------
// プレイヤーとダイスの判定(Z判定)
//----------------------------------------------------
bool CPlayerManager::IsHitPlayerToDiceZ( CONST  float distance, CDiceObj* dice  )
{
	// 判定をずらしておく
	THITAABB playerAABB;
	::CopyMemory( &playerAABB, m_pPlayer->GetAABB(), sizeof( THITAABB ) );
	playerAABB.centerPos.z += distance;
	
	// ダイスの一定方向まで移動したら
	if( !CCollision::GetInstance()->IsHitAABB( &playerAABB, dice->GetAABB() ) )
	{
		// 当たっていない状態になった
		return true;
	}

	// 当たっている状態
	return false;
}

//----------------------------------------------------
// プレイヤーの落下
//----------------------------------------------------
void CPlayerManager::Down( void )
{
	m_pPlayer->MoveDown( DICE_DOWN_SPEED );
}

//----------------------------------------------------
// プレイヤーの上昇
//----------------------------------------------------
void CPlayerManager::Up( CONST float speed )
{
	m_pPlayer->MoveUp( DICE_UP_SPEED );
}

//----------------------------------------------------
// カメラの情報をプレイヤーの行列にセット
//----------------------------------------------------
void CPlayerManager::SetCameraToMtx( CONST D3DXMATRIX* view )
{
	m_pPlayer->CalcWorldMtx( );
}