
#include "CDiceObjManager.h"

const float DICE_ROLL_SPEED = 5.0f;		// サイコロの回転速度(90度変化させるため90になるように)
const int  START_DICE_NUM = 10;			// 初期のサイコロの数 
const int  MIN_DICE_NUM = 10;			// ステージ中の最低ダイス数（これ以上少なくなったら強制的に出現させる）
const int DICE_APPER_TIME = 90;			// この時間でダイスの出るタイミングを管理
const int DICE_APPER = 70;

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CDiceObjManager::CDiceObjManager( void )
{
	m_pDice = new CDiceObj[MAX_DICE_NUM];		// サイコロの最大数分先に生成
	m_pResDiceFilePath = DICE_XFILEPATH;
	CResourceManager::GetInstance()->LoadXFile( m_pResDiceFilePath );

	m_pMainDice = new TMAINDICE;				// メインのサイコロの構造体をインスタンス化

	m_pSplitParticle = new CSplitParticle;		// パーティクル

	m_pDiceInfoManager = nullptr;
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CDiceObjManager::~CDiceObjManager( void )
{
	SAFE_DELETE( m_pMainDice );

	SAFE_DELETE_ALLAY( m_pDice );
	SAFE_DELETE( m_pSplitParticle );
}

//----------------------------------------------------
// 描画
//----------------------------------------------------
void CDiceObjManager::Draw( CONST D3DXMATRIX* view )
{
	// カリングモード
	CDirectDrawSystem::GetInstance()->SetCallMode( true );
	
	for( int i = 0; i < MAX_DICE_NUM; ++ i )
	{
		if( m_pDice[i].GetIsDice() == true )
		{
			CDirectDrawSystem::GetInstance()->Draw3D( CResourceManager::GetInstance()->GetXFile( m_pResDiceFilePath ),m_pDice[i].GetWorldMtx(), m_pDice[i].GetColor() );
		}
	}

	// パーティクル
//	m_pSplitParticle->Draw( view );

}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
void CDiceObjManager::Init( void )
{
	// ダイスのメッシュデータ取得
	TMESHDATA meshData;
	::ZeroMemory( &meshData, sizeof( TMESHDATA ) );
	CCollision::GetInstance()->GetMeshData( &meshData, CResourceManager::GetInstance()->GetXFile( DICE_XFILEPATH )->GetMesh() );

	// 先に全てのサイコロを初期化
	for( int i = 0; i < MAX_DICE_NUM; ++ i )
	{
		m_pDice[i].Init();
		m_pDice[i].SetSize( &meshData.size );
	}

	// 当たり判定用AABBを作成
	CDebugMode::m_pDiceBox[0].diceBox.CreateBox( m_pDice[0].GetSize() );
	CDebugMode::m_pDiceBox[0].diceBox.InitWorldMtx();
	CDebugMode::m_pDiceBox[0].diceBox.SetDiffuse( 0, 0, 0, 200 );
	CDebugMode::m_pDiceBox[0].diceBox.SetAmbient( 255, 0, 0, 255 );
	CDebugMode::m_pDiceBox[0].isDice = true;

	// メインのサイコロの設定
	m_pMainDice->diceObj = &m_pDice[0];
	m_pDice[0].SetIsDice( true );

	// 当たり判定用AABBを作成
	m_pDice[0].SetAABB();
	
	// ブロックの場所番号取得
	UINT index = CStageBlockManager::GetInstance()->GetIndexToDicePos( m_pDice[0].GetXPos(), m_pDice[0].GetZPos() );
	m_pMainDice->diceObj->SetIndexNo( index );
	CStageBlockManager::GetInstance()->SetIsOnDice( index, true );
	m_pMainDice->rollState = eDiceRollState::DICE_ROLLSTATE_NONE;
	m_pMainDice->degree = 0.0f;
	m_pMainDice->diceObj->SetNo( 0 );
	m_pMainDice->diceObj->SetStatus( DICE_STATUS::e_statusNormal );
	m_pMainDice->halfSize = D3DXVECTOR3( m_pDice[0].GetSize()->x / 2, m_pDice[0].GetSize()->y / 2, m_pDice[0].GetSize()->z / 2);

	// ステージにメインダイスの情報をセット
	CStageBlockManager::GetInstance()->SetBlockToDiceInfo( m_pMainDice->diceObj, m_pMainDice->diceObj->GetIndexNo() );

	// インフォ情報にメインダイスの情報をセット
	m_pDiceInfoManager->SetInfoDice( m_pMainDice->diceObj->GetWorldMtx() );
	
	m_diceNum = 1;
	m_appearTime = 0;

	// ステージに初期のダイスをセット
	for( int i = 0; i < START_DICE_NUM; ++ i )
	{
		this->Appear();
	}

}

//----------------------------------------------------
// 終了
//----------------------------------------------------
void CDiceObjManager::Uninit( void )
{
}

//----------------------------------------------------
// 処理
//----------------------------------------------------
void CDiceObjManager::Run()
{
	// デバッグ
	this->Debug();	

	// 出現管理
	this->AppearManager();

	// 移動回転
	this->MoveToRoll();


	// ダイスのアニメーション制御
	this->Animation();

	// パーティクル処理
	m_pSplitParticle->Move();
}

//----------------------------------------------------
// デバッグ
//----------------------------------------------------
void CDiceObjManager::Debug( void )
{
#ifdef _DEBUG
	// 移動
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

	// サイコロ出現
	if( ( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_SPACE ) || 
		  CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_X ) ) 
		  && m_pMainDice->rollState == eDiceRollState::DICE_ROLLSTATE_NONE )
	{
		this->Appear();
	}

#ifdef _DEBUG
	// 今自分が動かしているサイコロを変更する
	if( ( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_TAB ) ||
		CJoyStick::GetInstance()->GetTriggerButton( 0, XINPUT_GAMEPAD_Y ) ) && m_pMainDice->rollState == eDiceRollState::DICE_ROLLSTATE_NONE )
	{
		for( int i = 0; i < MAX_DICE_NUM; ++ i )
		{
			if( m_pDice[i].GetIsDice() == true && m_pDice[i].GetStatus() == DICE_STATUS::e_statusNormal && &m_pDice[i] != m_pMainDice->diceObj )
			{
				m_pMainDice->diceObj = (&m_pDice[i]);		// メインのダイスを変える
				m_pMainDice->diceObj->SetIndexNo(m_pDice[i].GetIndexNo());
				m_pMainDice->halfSize = D3DXVECTOR3( m_pDice[i].GetSize()->x / 2, m_pDice[i].GetSize()->y / 2, m_pDice[i].GetSize()->z / 2 );
				break;
			}
		}
	}
#endif 

}

//----------------------------------------------------
// 移動の遷移
//----------------------------------------------------
void CDiceObjManager::Move( void )
{
	// 右移動
	if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_D ) ||
		CJoyStick::GetInstance()->GetPressButton( 0, XINPUT_GAMEPAD_DPAD_RIGHT ))
	{
		this->MoveRight();
	}

	// 左移動
	else if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_A ) ||
		CJoyStick::GetInstance()->GetPressButton( 0, XINPUT_GAMEPAD_DPAD_LEFT ))
	{
		this->MoveLeft();
	}
	 
	// 前進
	else if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_W ) ||
		CJoyStick::GetInstance()->GetPressButton( 0, XINPUT_GAMEPAD_DPAD_UP ))
	{
		this->MoveFront();
	}

	// 後進
	else if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_S ) ||
		CJoyStick::GetInstance()->GetPressButton( 0, XINPUT_GAMEPAD_DPAD_DOWN ))
	{
		this->MoveBack();
	}
}

//----------------------------------------------------
// 右移動
//----------------------------------------------------
void CDiceObjManager::MoveRight( void )
{
	// ステージの右に達していないか
	if( m_pMainDice->diceObj->GetWorldMtx()->_41 < CStageBlockManager::GetInstance()->GetXSize() )
	{
		// 右にブロックがないか判定
		if( CStageBlockManager::GetInstance()->GetIsOnDice( m_pMainDice->diceObj->GetIndexNo() + 1 ) == true &&
			CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() + 1 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
		{
			// 右にブロックがある場合はメインのダイスを替える
			m_pMainDice->diceObj = CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() + 1 )->GetDice();
			m_pMainDice->diceObj->SetIndexNo( m_pMainDice->diceObj->GetIndexNo() );
			m_pDiceInfoManager->SetInfoDice( m_pMainDice->diceObj->GetWorldMtx() );

			return;
		}

		// 右のダイスが消え中，出現し始め中だったら前のダイスを消して移動させる
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
// 左移動
//----------------------------------------------------
void CDiceObjManager::MoveLeft( void )
{
	// ステージの左に達していないかを判定
	if( m_pMainDice->diceObj->GetWorldMtx()->_41 > -CStageBlockManager::GetInstance()->GetXSize() )
	{
		if( CStageBlockManager::GetInstance()->GetIsOnDice( m_pMainDice->diceObj->GetIndexNo() - 1 ) == true &&
			CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() - 1 )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal)
		{
			// 左にブロックがある場合はメインのダイスを替える
			m_pMainDice->diceObj = CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() - 1 )->GetDice();
			m_pMainDice->diceObj->SetIndexNo(m_pMainDice->diceObj->GetIndexNo());
			m_pDiceInfoManager->SetInfoDice( m_pMainDice->diceObj->GetWorldMtx() );

			return;
		}

		// 前のダイスが消え中，出現し始め中だったら前のダイスを消して移動させる
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
// 前移動
//----------------------------------------------------
void CDiceObjManager::MoveFront( void )
{
	// ステージの前に達していないか
	if( m_pMainDice->diceObj->GetWorldMtx()->_43 < CStageBlockManager::GetInstance()->GetXSize() )
	{
		if( CStageBlockManager::GetInstance()->GetIsOnDice( m_pMainDice->diceObj->GetIndexNo() - CStageBlockManager::GetInstance()->GetZNum() ) == true &&
			CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() - CStageBlockManager::GetInstance()->GetZNum()  )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
		{
			// 前にブロックがある場合はメインのダイスを替える
			m_pMainDice->diceObj = CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() - CStageBlockManager::GetInstance()->GetZNum() )->GetDice();
			m_pMainDice->diceObj->SetIndexNo(m_pMainDice->diceObj->GetIndexNo());
			m_pDiceInfoManager->SetInfoDice( m_pMainDice->diceObj->GetWorldMtx() );

			return;
		}
			
		// 前のダイスが消え中，出現し始め中だったら前のダイスを消して移動させる
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
		// 回転移動
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
// 後移動
//----------------------------------------------------
void CDiceObjManager::MoveBack( void )
{
	// ステージの後ろに達していないかを判定
	if( m_pMainDice->diceObj->GetWorldMtx()->_43 > -CStageBlockManager::GetInstance()->GetZSize() )
	{
		if( CStageBlockManager::GetInstance()->GetIsOnDice( m_pMainDice->diceObj->GetIndexNo() + CStageBlockManager::GetInstance()->GetZNum() ) == true &&
			CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() + CStageBlockManager::GetInstance()->GetZNum()  )->GetDice()->GetStatus() == DICE_STATUS::e_statusNormal )
		{
			// 後ろにブロックがある場合はメインのダイスを替える
			m_pMainDice->diceObj = CStageBlockManager::GetInstance()->GetStageBlock( m_pMainDice->diceObj->GetIndexNo() + CStageBlockManager::GetInstance()->GetZNum() )->GetDice();
			m_pMainDice->diceObj->SetIndexNo(m_pMainDice->diceObj->GetIndexNo());
			m_pDiceInfoManager->SetInfoDice( m_pMainDice->diceObj->GetWorldMtx() );

			return;
		}
		// 後ろのダイスが消え中，出現し始め中だったら前のダイスを消して移動させる
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
// 移動＋回転
//----------------------------------------------------
void CDiceObjManager::MoveToRoll( void )
{
	switch( m_pMainDice->rollState )
	{
		case DICE_ROLLSTATE_RIGHT:
			m_pMainDice->degree += DICE_ROLL_SPEED;
			m_pMainDice->diceObj->MoveX( -m_pMainDice->halfSize.x, m_pMainDice->halfSize.y, 0.0f, -1.0f,m_pMainDice->degree );
			m_pMainDice->diceObj->SetAABB();
			// 当たり判定用AABBの位置を更新
			CDebugMode::m_pDiceBox[m_pMainDice->diceObj->GetNo()].diceBox.SetWorldPos( m_pMainDice->diceObj->GetWorldMtx () );
	
			break;

		case DICE_ROLLSTATE_LEFT:
			m_pMainDice->degree += DICE_ROLL_SPEED;
			m_pMainDice->diceObj->MoveX( m_pMainDice->halfSize.x, m_pMainDice->halfSize.y, 0.0f, 1.0f, m_pMainDice->degree );
			m_pMainDice->diceObj->SetAABB();
			// 当たり判定用AABBの位置を更新
			CDebugMode::m_pDiceBox[m_pMainDice->diceObj->GetNo()].diceBox.SetWorldPos( m_pMainDice->diceObj->GetWorldMtx () );

			break;

		case DICE_ROLLSTATE_FRONT:
			m_pMainDice->degree += DICE_ROLL_SPEED;
			m_pMainDice->diceObj->MoveZ( 0.0f, m_pMainDice->halfSize.x, -m_pMainDice->halfSize.y , 1.0f, m_pMainDice->degree );
			m_pMainDice->diceObj->SetAABB();
			// 当たり判定用AABBの位置を更新
			CDebugMode::m_pDiceBox[m_pMainDice->diceObj->GetNo()].diceBox.SetWorldPos( m_pMainDice->diceObj->GetWorldMtx () );

			break;

		case DICE_ROLLSTATE_BACK:
			m_pMainDice->degree += DICE_ROLL_SPEED;
			m_pMainDice->diceObj->MoveZ( 0.0f, m_pMainDice->halfSize.x, m_pMainDice->halfSize.y , -1.0f, m_pMainDice->degree );			
			m_pMainDice->diceObj->SetAABB();
			// 当たり判定用AABBの位置を更新
			CDebugMode::m_pDiceBox[m_pMainDice->diceObj->GetNo()].diceBox.SetWorldPos( m_pMainDice->diceObj->GetWorldMtx () );
	
			break;

		case DICE_ROLLSTATE_NONE:
			break;

	}

	// 角度が90度( 1マス分移動したら )
	if( m_pMainDice->degree == 90 && m_pMainDice->rollState != DICE_ROLLSTATE_NONE )
	{
		m_pMainDice->rollState = DICE_ROLLSTATE_NONE;
		UINT index = CStageBlockManager::GetInstance()->GetIndexToDicePos( m_pMainDice->diceObj->GetWorldMtx()->_41, 
							   	 										   m_pMainDice->diceObj->GetWorldMtx()->_43 );
		m_pMainDice->diceObj->SetIndexNo( index );
		CStageBlockManager::GetInstance()->SetBlockToDiceInfo( m_pMainDice->diceObj, m_pMainDice->diceObj->GetIndexNo() );

		// ダイスのINFO情報を変更
		m_pDiceInfoManager->SetInfoDice( m_pMainDice->diceObj->GetWorldMtx() );

		// エミッター
		m_pSplitParticle->Emitter( m_pMainDice->diceObj->GetXPos(), m_pMainDice->diceObj->GetYPos() - 2.0f, m_pMainDice->diceObj->GetZPos() );

		// 判定
		CChainManager::GetInstance()->Chain( m_pMainDice->diceObj->GetIndexNo() );
	}

}

//----------------------------------------------------
// ダイス出現管理
//----------------------------------------------------
void CDiceObjManager::AppearManager( void )
{
	// 管理用変数に時間を足す
	m_appearTime ++;

	// ステージからどれだけ消してもとりあず最低数分は出現させる
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
// ダイスの出現
//----------------------------------------------------
bool CDiceObjManager::Appear( void )
{
	// 出現していないダイスを判定
	UINT notAppearNo = 0;
	for( int i = 0; i < MAX_DICE_NUM; ++ i )
	{
  		if ( m_pDice[i].GetIsDice() == false )
		{
			notAppearNo = i;
			break;
		}

		// 全部埋まっている場合は生成できない(普通はゲームオーバだが，とりあえずエラーを防ぐために実装）
		if( i == MAX_DICE_NUM )
		{
			return false;
		}
	}

	//　ランダムにブロックの添え字を取得
	UINT blockIndex = CStageBlockManager::GetInstance()->GetBlockIndexRnd();

	// ブロックがまだ生成されていないかどうか
	if( CStageBlockManager::GetInstance()->GetIsOnDice( blockIndex ) == false )
	{
		m_diceNum ++;	// ダイスの数追加

		// 現在のオブジェクトが持っている行列を初期化
		m_pDice[notAppearNo].InitWorldMtx();

		// 面判定配列を保存
		m_pDice[notAppearNo].InitPip();

		// ランダムで上面の目と横面の回転数を決める
		int upperFace = CDiceRandSystem::GetInstance()->GetUpperFace();
		int aroundNum = CDiceRandSystem::GetInstance()->GetAroundFace();

		// 上面を元にサイコロの初期をセット
		m_pDice[ notAppearNo ].SetPip( upperFace, aroundNum ); 

		// サイコロの位置セット
		D3DXVECTOR3	workVec;
		D3DXMATRIX  workMtx;
		D3DXMatrixIdentity( &workMtx );

		workVec = *CStageBlockManager::GetInstance()->GetPos( blockIndex );
		workMtx._41 = workVec.x;
		workMtx._42 = -4.0f;
		workMtx._43 = workVec.z;

		// 識別番号のセット
		m_pDice[ notAppearNo ].SetNo( notAppearNo );

		// 回転行列と平行移動行列を乗算
		m_pDice[ notAppearNo ].CalcWorldMtx( m_pDice[ notAppearNo ].GetWorldMtx(),&workMtx );
		
		// インデックス番号を保存
		m_pDice[ notAppearNo ].SetIndexNo( blockIndex );

		// α値の設定
		m_pDice[ notAppearNo ].SetColor( 255,255,255,127 );

		// 出現中に設定
		m_pDice[ notAppearNo ].SetStatus( DICE_STATUS::e_statusStartAppear );

		m_pDice[ notAppearNo ].SetAABB();

		// 生成されたらステージとダイスに生成されたという情報をセット
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
// ダイスのアニメーション
//----------------------------------------------------
void CDiceObjManager::Animation( void )
{
	for( int i = 0; i < MAX_DICE_NUM; ++ i )
	{
		if( m_pDice[i].GetIsDice() == true )
		{
			// プレイヤーの現在地からブロックの添え字番号を取得する
			UINT playerIndex = CStageBlockManager::GetInstance()->GetIndexToPlayerPos( CPlayerManager::GetInstance()->GetPlayerPos()->x, 
																					   CPlayerManager::GetInstance()->GetPlayerPos()->z );
			switch( m_pDice[i].GetStatus() )
			{
			// 出現して静止している状態
			case DICE_STATUS::e_statusNormal:
				if( m_pDice[i].GetIndexNo() == playerIndex && 
					( CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceDeleteStart ||
					CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceAppear ) )
				{
					m_pMainDice->diceObj = &m_pDice[i];		// メインのダイス変更
					CPlayerManager::GetInstance()->SetPlayerStatus( ePlayerStatus::eOnDice );
					// プレイヤーをダイスの上に乗せる
					CPlayerManager::GetInstance()->SetPlayerPos( CPlayerManager::GetInstance()->GetPlayerPos()->x, m_pDice[i].GetYPos() + 4.0f, CPlayerManager::GetInstance()->GetPlayerPos()->z );
					m_pDiceInfoManager->SetInfoDice( m_pMainDice->diceObj->GetWorldMtx() );
				}
				break;

			// 出現し始めアニメーション
			case DICE_STATUS::e_statusStartAppear:
				// 現在の添え字がメインダイスの添え字と同じだったらプレイヤーの状態を遷移
				if( m_pDice[i].GetIndexNo() == playerIndex &&
					( CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnStage ||
					CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceDelete ||
					CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceDeleteStart ||
					CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceAppear ||
					CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceAppearStart ) )
				{
					m_pMainDice->diceObj = &m_pDice[i];		// メインのダイス変更
					CPlayerManager::GetInstance()->SetPlayerStatus( ePlayerStatus::eOnDiceAppearStart );
					// プレイヤーをダイスの上に乗せる
					CPlayerManager::GetInstance()->SetPlayerPos( CPlayerManager::GetInstance()->GetPlayerPos()->x, m_pDice[i].GetYPos() + 4.0f, CPlayerManager::GetInstance()->GetPlayerPos()->z );
					m_pDiceInfoManager->SetIsExist( true );
					m_pDiceInfoManager->SetInfoDice( m_pMainDice->diceObj->GetWorldMtx() );
				}

				// 出現し始めアニメーションが終わったら
				if( m_pDice[i].UpAnimation( DICE_UP_SPEED ) )
				{
					m_pDice[i].SetStatus( DICE_STATUS::e_statusAppear );
					m_pDice[i].SetBeforStatus( DICE_STATUS::e_statusStartAppear );

					// ダイスのアニメーションが変わった時も、ダイスの上にいる場合はプレイヤーのステータスを変える
					if( m_pDice[i].GetIndexNo() == playerIndex )
					{
						CPlayerManager::GetInstance()->SetPlayerStatus( ePlayerStatus::eOnDiceAppear );
					}
				}
				CDebugMode::m_pDiceBox[m_pDice[i].GetNo()].diceBox.SetWorldMtx( m_pDice[m_pDice[i].GetNo()].GetWorldMtx() );
				m_pDice[i].SetAABB();
				break;

			// 出現中アニメーション
			case DICE_STATUS::e_statusAppear:
				// 出現中アニメーションの上にダイスの上にいるプレイヤーが移動してきたらダイスの上にセット
				if( m_pDice[i].GetIndexNo() == playerIndex && 
					( CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDice || 
					  CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceAppear ||
					  CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceAppearStart ||
					  CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceDeleteStart ||
					  CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceDelete ) )
				{

					m_pMainDice->diceObj = &m_pDice[i];		// メインのダイス変更
					// プレイヤーの状態を遷移
					CPlayerManager::GetInstance()->SetPlayerStatus( ePlayerStatus::eOnDiceAppear );
					// プレイヤーをダイスの上に乗せる
					CPlayerManager::GetInstance()->SetPlayerPos( CPlayerManager::GetInstance()->GetPlayerPos()->x, m_pDice[i].GetYPos() + 4.0f, CPlayerManager::GetInstance()->GetPlayerPos()->z );
					m_pDiceInfoManager->SetIsExist( true );
					m_pDiceInfoManager->SetInfoDice( m_pMainDice->diceObj->GetWorldMtx() );
				}

				// 出現アニメーションが終わったら
				if( m_pDice[i].UpAnimation( DICE_UP_SPEED ) )
				{
					m_pDice[i].SetStatus( DICE_STATUS::e_statusNormal );
					m_pDice[i].SetBeforStatus( DICE_STATUS::e_statusAppear );

					if( m_pDice[i].GetIndexNo() == playerIndex )
					{
						CPlayerManager::GetInstance()->SetPlayerStatus( ePlayerStatus::eOnDice );
					}
					
					// ステージのブロックの状態を変更
					CStageBlockManager::GetInstance()->SetIsOnDice( CStageBlockManager::GetInstance()->GetIndexToDicePos( m_pDice[i].GetXPos(), m_pDice[i].GetZPos() ), true );
				}
				CDebugMode::m_pDiceBox[m_pDice[i].GetNo()].diceBox.SetWorldMtx( m_pDice[m_pDice[i].GetNo()].GetWorldMtx() );
				m_pDice[i].SetAABB();
				break;

			// 消え始めアニメーション
			case DICE_STATUS::e_statusStartDelete:
				// プレイヤーとダイスの添え字番号が同じなら
				if( m_pDice[i].GetIndexNo() == playerIndex &&
					( CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDice ||
					CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceAppearStart ||
					CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceAppear ||
					CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceDeleteStart ||
					CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceDelete ) )
				{		
					m_pMainDice->diceObj = &m_pDice[i];		// メインのダイス変更
					// プレイヤーの状態を遷移
					CPlayerManager::GetInstance()->SetPlayerStatus( ePlayerStatus::eOnDiceDeleteStart );
					// プレイヤーをダイスの上に乗せる
					CPlayerManager::GetInstance()->SetPlayerPos( CPlayerManager::GetInstance()->GetPlayerPos()->x, m_pDice[i].GetYPos() + 4.0f, CPlayerManager::GetInstance()->GetPlayerPos()->z );
					m_pDiceInfoManager->SetIsExist( true );
					m_pDiceInfoManager->SetInfoDice( m_pMainDice->diceObj->GetWorldMtx() );
				}

				// 消え始めのアニメーションが終わったら
				if( m_pDice[i].DownAnimation( -DICE_DOWN_SPEED ) )
				{
					m_pDice[i].SetStatus( DICE_STATUS::e_statusDelete );
					m_pDice[i].SetBeforStatus( DICE_STATUS::e_statusStartDelete );

					// プレイヤーの位置からブロックの添え字番号を取得する
					UINT playerIndex = CStageBlockManager::GetInstance()->GetIndexToPlayerPos( CPlayerManager::GetInstance()->GetPlayerPos()->x, 
		   																						CPlayerManager::GetInstance()->GetPlayerPos()->z );
					// プレイヤーとダイスの添え字番号が同じなら
					if( m_pDice[i].GetIndexNo() == playerIndex )
					{
						CPlayerManager::GetInstance()->SetPlayerStatus( ePlayerStatus::eOnDiceDelete );
						// プレイヤーをダイスに乗せる
						CPlayerManager::GetInstance()->SetPlayerPos( CPlayerManager::GetInstance()->GetPlayerPos()->x, m_pDice[i].GetYPos() + 4.0f, CPlayerManager::GetInstance()->GetPlayerPos()->z );
						m_pDiceInfoManager->SetInfoDice( m_pMainDice->diceObj->GetWorldMtx() );	
					}
					CDebugMode::m_pDiceBox[m_pDice[i].GetNo()].diceBox.SetWorldMtx( m_pDice[m_pDice[i].GetNo()].GetWorldMtx() );
					m_pDice[i].SetAABB();
				}
				break;

			// 消え中アニメーション
			case DICE_STATUS::e_statusDelete:
				// プレイヤーとダイスの添え字番号が同じなら
				if( m_pDice[i].GetIndexNo() == playerIndex &&
				 ( CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceAppearStart ||
				   CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceAppear ||
				   CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnStage ||
				   CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceDelete ||
				   CPlayerManager::GetInstance()->GetPlayerStatus() == ePlayerStatus::eOnDiceDeleteStart ) )
				{
					m_pMainDice->diceObj = &m_pDice[i];		// メインのダイス変更
					// プレイヤーの状態を遷移
					CPlayerManager::GetInstance()->SetPlayerStatus( ePlayerStatus::eOnDiceDelete );
					// プレイヤーをダイスの上に乗せる
					CPlayerManager::GetInstance()->SetPlayerPos( CPlayerManager::GetInstance()->GetPlayerPos()->x, m_pDice[i].GetYPos() + 4.0f, CPlayerManager::GetInstance()->GetPlayerPos()->z );
					m_pDiceInfoManager->SetIsExist( true );
					m_pDiceInfoManager->SetInfoDice( m_pMainDice->diceObj->GetWorldMtx() );
				}

				// 消えアニメーションが終わったら
				if( m_pDice[i].DownAnimation( -DICE_DOWN_SPEED ) )
				{
					m_pDice[i].SetStatus( DICE_STATUS::e_statusNone );
					m_pDice[i].SetBeforStatus( DICE_STATUS::e_statusDelete );
					m_pDice[i].SetIsDice( false );	// ダイスなしの状態に設定する
					m_pDice[i].SetIsChain( false );	// チェインしていない状態に設定する
					
					// チェインのダイスの個数を減らしてもしなくなったらチェイン終了
					CChainManager::GetInstance()->GetChain( m_pDice[i].GetChainNo() )->chainDiceNum --;
					if( CChainManager::GetInstance()->GetChain( m_pDice[i].GetChainNo() )->chainDiceNum == 0 )
					{
						CChainManager::GetInstance()->GetChain( m_pDice[i].GetChainNo() )->isChain = false;
					}

					// プレイヤーの現在地からブロックの添え字番号を取得
					UINT playerIndex = CStageBlockManager::GetInstance()->GetIndexToPlayerPos( CPlayerManager::GetInstance()->GetPlayerPos()->x, 
																							   CPlayerManager::GetInstance()->GetPlayerPos()->z );

					// プレイヤーの添え字番号とダイスが同じだったらプレイヤーのステータス変更
					if( m_pDice[i].GetIndexNo() == playerIndex )
					{
						CPlayerManager::GetInstance()->SetPlayerStatus( ePlayerStatus::eOnStage );
						m_pDiceInfoManager->SetIsExist( false );
					}

					// ステージ上からダイスを削除
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