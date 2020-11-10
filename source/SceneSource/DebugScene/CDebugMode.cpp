
#include "CDebugMode.h"

C2DSpriteRHW	CDebugMode::m_pDebugMode;
LPSTR			CDebugMode::m_pDebugModeTexturePath;
bool			CDebugMode::m_isDebugMode;

float*			CDebugMode::m_pFps = nullptr;
int*			CDebugMode::m_pTime = nullptr;
C3DObjectShape	CDebugMode::m_pPlayerBox;

TDEBUGDICEBOX	CDebugMode::m_pDiceBox[49];

bool			CDebugMode::m_isCollisionBox;
bool			CDebugMode::m_isFps;

TFONTINFO		CDebugMode::m_font[ SELECT_DEBUG_NUM ];
int				CDebugMode::m_fontIndex;
bool			CDebugMode::m_debugOnOff;

int				CDebugMode::m_leftRightIndexDir;
int				CDebugMode::m_upDownIndexDir;
eDebugStatus	CDebugMode::m_eDebugStatus;
int				CDebugMode::m_debugIndex;

// ステータス管理用配列
const eDebugStatus debugStatus[ DEBUG_NUM ] = { 
eDebugStatus::FPS,
eDebugStatus::COLLISION_BOX,
eDebugStatus::GAME_TIME,
eDebugStatus::EXIT_DEBUG
};

const D3DXCOLOR defaultColor = DEFAULT_DEBUG_MODE_COLOR;

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CDebugMode::CDebugMode( void )
{
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CDebugMode::~CDebugMode( void )
{
}

//----------------------------------------------------
// ロード
//----------------------------------------------------
bool CDebugMode::Load( void )
{
	// 画像ロード
	m_pDebugModeTexturePath = DEBUGMODE_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pDebugModeTexturePath );
	m_pDebugMode.Init();
	m_pDebugMode.SetVertexPos( 400.0f,320.0f,800.0f,640.0f );
	m_pDebugMode.SetDiffuse( 0 , 255, 255, 200 );
	
	// デバッグ用文字作成
	CResourceManager::GetInstance()->CreateXFont( 1, 12, 20 );

	return true;

}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
bool CDebugMode::Init( void )
{
	// デバッグ各種の状態
	m_isCollisionBox = false;
	m_isFps = true;

	// 色の設定
	for( int i = 0; i < SELECT_DEBUG_NUM; ++ i )
	{
		m_font[i].cheack = false;
		m_font[i].color = DEFAULT_DEBUG_MODE_COLOR;
	}

	// 当たり判定用AABB表示フラグOFF
	for( int i = 0; i < 49; ++ i )
	{
		m_pDiceBox[i].isDice = false;
	}

	// 最初の色の設定
	m_font[0].cheack = true;
	m_font[3].cheack = true;

	return true;
}

//----------------------------------------------------
// デバッグ用値のセット
//----------------------------------------------------
void CDebugMode::Set( int* pTime )
{
	m_pTime = pTime;		// 時間のアドレスをセット
}

//----------------------------------------------------
// デバッグモードの初期化( 入るたびに毎回 )
//----------------------------------------------------
bool CDebugMode::InitDebugMode( void )
{
	// デバッグモードフラグON
	m_isDebugMode = true;

	// ステータス管理用変数
	m_debugIndex = 0;
	m_debugOnOff = true;		// ON
	m_eDebugStatus = eDebugStatus::FPS;
	m_leftRightIndexDir = 1;
	m_upDownIndexDir = 1;

	m_fontIndex = 0;
	for( int i = 0; i < SELECT_DEBUG_NUM; ++ i )
	{
		if( m_font[i].cheack == true )
		{
			m_font[i].color = SELECT_DEBUG_MODE_COLOR;
		}
		else
		{
			m_font[i].color = DEFAULT_DEBUG_MODE_COLOR;
		}
	}

	m_font[0].color = CHEACK_DEBUG_MODE_COLOR;

	return true;
}

//----------------------------------------------------
// 終了
//----------------------------------------------------
bool CDebugMode::Uninit( void )
{
	return true;
}

//----------------------------------------------------
// 動作
//----------------------------------------------------
void CDebugMode::Run( CDirectCamera* camera )
{
 	float workDegree = 0.0f;
	// デバッグのためのカメラ回転
	if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_F10 ) )
	{
		workDegree = 1.0f;
		camera->LocalRotationQuaterY( workDegree );
	}

	if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_F9 ) )
	{
		workDegree = -1.0f;
		camera->LocalRotationQuaterY( workDegree );
	}

	if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_F8 ) )
	{
		workDegree = -1.0f;
		camera->LocalRotationQuaterX( workDegree );
	}

	if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_F7 ) )
	{
		workDegree = 1.0f;
		camera->LocalRotationQuaterX( workDegree );
	}
}

//----------------------------------------------------
// デバッグモードの動作
//----------------------------------------------------
void CDebugMode::RunDebugMode( void )
{
	RunRight();		// 右入力
	RunLeft();		// 左入力
	RunUp();		// 上入力
	RunDown();		// 下入力
	RunEnter();		// Enter入力
}

//----------------------------------------------------
// 右入力
//----------------------------------------------------
void CDebugMode::RunRight( void )
{
	if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_RIGHT ))
	{
		switch( m_eDebugStatus )
		{
			case eDebugStatus::EXIT_DEBUG:
				return;

			case eDebugStatus::GAME_TIME:
				DigitUpDown( m_pTime, m_pTime, 60 );
				break;

			default:
			if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_RIGHT ) )
			{
					// 動かす前の色変更
				if( m_font[ m_fontIndex ].cheack == true )
				{
					m_font[ m_fontIndex ].color = SELECT_DEBUG_MODE_COLOR;
				}
				else
				{
					m_font[ m_fontIndex ].color = DEFAULT_DEBUG_MODE_COLOR;
				}

				// 動かした後の色変更
				if( m_debugOnOff == true )
				{
					m_fontIndex += 1;
				}
				else if( m_debugOnOff == false )
				{
					m_fontIndex -= 1;
				}

				m_font[ m_fontIndex ].color = CHEACK_DEBUG_MODE_COLOR;
				m_debugOnOff ^= true;

				break;
			}
		}

	}
}

//----------------------------------------------------
// 左入力
//----------------------------------------------------
void CDebugMode::RunLeft( void )
{
	if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_LEFT ))
	{
		switch( m_eDebugStatus )
		{
			case eDebugStatus::EXIT_DEBUG:
				return;

			case eDebugStatus::GAME_TIME:
				DigitUpDown( m_pTime, m_pTime, -60 );
				break;

			default:
			if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_LEFT ) )
			{
					// 動かす前の色変更
				if( m_font[ m_fontIndex ].cheack == true )
				{
					m_font[ m_fontIndex ].color = SELECT_DEBUG_MODE_COLOR;
				}
				else
				{
					m_font[ m_fontIndex ].color = DEFAULT_DEBUG_MODE_COLOR;
				}

				// 動かした後の色変更
				if( m_debugOnOff == true )
				{
					m_fontIndex += 1;
				}
				else if( m_debugOnOff == false )
				{
					m_fontIndex -= 1;
				}
				m_font[ m_fontIndex ].color = CHEACK_DEBUG_MODE_COLOR;
				m_debugOnOff ^= true;

				break;
			}
		}

	}


}

//----------------------------------------------------
// 上入力
//----------------------------------------------------
void CDebugMode::RunUp( void )
{
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_UP ) )
	{
		if( m_font[ m_fontIndex ].cheack == true )
		{
			m_font[ m_fontIndex ].color = SELECT_DEBUG_MODE_COLOR;
		}
		else 
		{
			m_font[ m_fontIndex ].color = DEFAULT_DEBUG_MODE_COLOR;
		}
		

		// もし一番↑の場合
		if(  m_fontIndex <= 1 )
		{
			m_fontIndex = SELECT_DEBUG_NUM - 1;
			m_debugIndex = DEBUG_NUM - 1;
		}
		else 
		{
			if( m_eDebugStatus == eDebugStatus::EXIT_DEBUG )
			{
				m_fontIndex -= 1;
			}
			else if( m_eDebugStatus == eDebugStatus::GAME_TIME )
			{
				m_fontIndex -= 2;
				m_debugOnOff = true;
			}
			else
			{	
				m_fontIndex -= 2;
			}
						
			m_debugIndex -= 1;
		}

		m_eDebugStatus = debugStatus[ m_debugIndex ];	
		m_font[ m_fontIndex ].color = CHEACK_DEBUG_MODE_COLOR;
	}

}

//----------------------------------------------------
// 下入力
//----------------------------------------------------
void CDebugMode::RunDown( void )
{
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_DOWN ))
	{
		if( m_font[ m_fontIndex ].cheack == true )
		{
			m_font[ m_fontIndex ].color = SELECT_DEBUG_MODE_COLOR;
		}
		else if( m_font[ m_fontIndex ].cheack == false )
		{
			m_font[ m_fontIndex ].color = DEFAULT_DEBUG_MODE_COLOR;
		}
		
		// ↓キー入力したときに一番下のExitが選択されていたら
		if( m_fontIndex == SELECT_DEBUG_NUM - 1 )
		{
			m_fontIndex = 0;
			m_debugIndex = 0;
			m_leftRightIndexDir = 1;
			m_debugOnOff = true;
			m_eDebugStatus = debugStatus[ m_debugIndex ];
		}
		// ↓キー通常選択状態
		else
		{
			m_debugIndex += 1;
			m_eDebugStatus = debugStatus[ m_debugIndex ];
			if( ( m_eDebugStatus == eDebugStatus::GAME_TIME && m_debugOnOff == false ) ||
				  m_eDebugStatus == eDebugStatus::EXIT_DEBUG  )
			{
				m_fontIndex += 1;
			}
			else
			{
				m_fontIndex += 2;
			}
		}

		m_font[ m_fontIndex ].color = CHEACK_DEBUG_MODE_COLOR;
	}
}

//----------------------------------------------------
// Enter入力
//----------------------------------------------------
void CDebugMode::RunEnter( void )
{
	// 確定ボタン(ENTER)
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_RETURN ) )
	{
		switch( m_eDebugStatus )
		{
			// FPS表示
			case eDebugStatus::FPS:
				m_isFps = m_debugOnOff;
				DebugONOFF( m_isFps, &m_font[0], &m_font[1] );
				break;

			// 当たり判定用ボックス
			case eDebugStatus::COLLISION_BOX:
				m_isCollisionBox = m_debugOnOff;
				DebugONOFF( m_isCollisionBox, &m_font[2], &m_font[3] );
				break;

			// ゲームの時間
			case eDebugStatus::GAME_TIME:
				
				break;

			// Exit
			case eDebugStatus::EXIT_DEBUG:
				m_isDebugMode = false;
				break;
		}
	}
}

//----------------------------------------------------
// 描画
//----------------------------------------------------
void CDebugMode::Draw( void )
{
	// FPS表示
	if( m_isFps == true )
	{
		CResourceManager::GetInstance()->GetXFont( 1 )->DrawColor( 0, 0, D3DXCOLOR( 255,255,255,255 ), "FPS:%4.2f", *m_pFps );
	}

	// 当たり判定用ボックス
	if( m_isCollisionBox == true )
	{
		// プレイヤー用AABB
		CDirectDrawSystem::GetInstance()->DrawShape( m_pPlayerBox.GetWorldMtx(), m_pPlayerBox.GetMaterial(), m_pPlayerBox.GetMesh() );

		// ダイス用AABB
		for( int i= 0; i< 49; ++ i )
		{
			if( m_pDiceBox[i].isDice == true )
			{
				CDirectDrawSystem::GetInstance()->DrawShape( m_pDiceBox[i].diceBox.GetWorldMtx(), m_pDiceBox[i].diceBox.GetMaterial(), m_pDiceBox[i].diceBox.GetMesh() );
			}
		}
	}
}

//----------------------------------------------------
// デバッグモード画面の描画
//----------------------------------------------------
void CDebugMode::DrawDebugMode( void )
{
	// 背景
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pDebugModeTexturePath )->Get(),m_pDebugMode.GetVertex() );

	// タイトル
	CResourceManager::GetInstance()->GetXFont( 1 )->DrawColor( 340, 110, D3DXCOLOR(255,255,0,255), "Debug Mode" );

	// FPS
	CResourceManager::GetInstance()->GetXFont( 1 )->DrawColor( 100, 150, defaultColor, "FPS" );
	CResourceManager::GetInstance()->GetXFont( 1 )->DrawColor( 400, 150, m_font[0].color, "ON" );
	CResourceManager::GetInstance()->GetXFont( 1 )->DrawColor( 500, 150, m_font[1].color, "OFF" );


	// 当たり判定用AABBBOXの表示
	CResourceManager::GetInstance()->GetXFont( 1 )->DrawColor( 100, 180, defaultColor, "HitCheack AABBBOX" );
	CResourceManager::GetInstance()->GetXFont( 1 )->DrawColor( 400, 180, m_font[2].color, "ON" );
	CResourceManager::GetInstance()->GetXFont( 1 )->DrawColor( 500, 180, m_font[3].color, "OFF" );

	// Time
	CResourceManager::GetInstance()->GetXFont( 1 )->DrawColor( 100, 210, defaultColor, "Time Change" );
	CResourceManager::GetInstance()->GetXFont( 1 )->DrawColor( 400, 210, m_font[4].color, "%d", *m_pTime );

	// Exit
	CResourceManager::GetInstance()->GetXFont( 1 )->DrawColor( 380, 500, m_font[ SELECT_DEBUG_NUM - 1 ].color, "Exit" );

}

//----------------------------------------------------
// デバッグのON/OFFの切り替え
//----------------------------------------------------
void CDebugMode::DebugONOFF( bool isOnOff, TFONTINFO* font, TFONTINFO* font2 )
{
	if( isOnOff == true )
	{
		font->cheack = true;
		font2->cheack = false;
		font2->color = DEFAULT_DEBUG_MODE_COLOR;
	}
	else if( isOnOff == false )
	{
		font->cheack = false;
		font->color = DEFAULT_DEBUG_MODE_COLOR;
		font2->cheack = true;
	}
}

//----------------------------------------------------
// 値の調整
//----------------------------------------------------
int* CDebugMode::DigitUpDown( int* pOut, int* pDigit, int value )
{
	*pOut = *pDigit + value;

	return pOut;
}