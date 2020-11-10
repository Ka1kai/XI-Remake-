
#include "CSceneDebug.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CSceneDebug::CSceneDebug( CSceneChange* change ) : CSceneBase( change )
{

}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CSceneDebug::~CSceneDebug( void )
{
}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
void CSceneDebug::Initialize( void )
{
	CResourceManager::GetInstance()->CreateXFont( 0,15,30 );
	CResourceManager::GetInstance()->CreateXFont( 99, 13, 20 );

	m_fontIndex = 0;
	for( int i = 0; i < FONT_NUM; ++ i )
	{
		m_fontColor[i] = DEFAULT_SCENE_COLOR;
		m_fontPos[i].x = 130.0f;
		m_fontPos[i].y = 150.0f + 40 * i;
	}
	m_fontColor[0] = SELECT_SCENE_COLOR;
	m_fontPos[0].x = 100.0f;
}

//----------------------------------------------------
// 処理
//----------------------------------------------------
void CSceneDebug::Run( void )
{
	CInputKeyboard::GetInstance()->Update();
	CJoyStick::GetInstance()->Update();

	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_DOWN ) ||
		CJoyStick::GetInstance()->GetTriggerButton(0,XINPUT_GAMEPAD_DPAD_DOWN ))
	{
		m_fontColor[ m_fontIndex ] = DEFAULT_SCENE_COLOR;
		m_fontPos[ m_fontIndex ].x = 130.0f;
		m_fontIndex ++;
		if( m_fontIndex == FONT_NUM )
		{
			m_fontIndex = 0;
		}
		m_fontColor[ m_fontIndex ] = SELECT_SCENE_COLOR;
		m_fontPos[ m_fontIndex ].x = 100.0f;
	}

	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_UP ) ||
		CJoyStick::GetInstance()->GetTriggerButton(0,XINPUT_GAMEPAD_DPAD_UP ))
	{
		m_fontColor[ m_fontIndex ] = DEFAULT_SCENE_COLOR;
		m_fontPos[ m_fontIndex ].x = 130.0f;
		m_fontIndex --;
		if( m_fontIndex == -1 )
		{
			m_fontIndex = FONT_NUM - 1;
		}
		m_fontColor[ m_fontIndex ] = SELECT_SCENE_COLOR;
		m_fontPos [m_fontIndex].x = 100.0f;
	}

	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_RETURN ) ||
		CJoyStick::GetInstance()->GetReleaseButton( 0,XINPUT_GAMEPAD_A ))
	{
		switch( m_fontIndex )
		{
		case 0:
			mSceneChanger->ChangeScene( eSceneState::eSceneTitle );
			break;

		case 1:
			mSceneChanger->ChangeScene( eSceneState::eSceneModeSelect );
			break;

		case 2:
			mSceneChanger->ChangeScene( eSceneState::eSceneGame );
			break;

		case 3:
			mSceneChanger->ChangeScene( eSceneState::eSceneResult );
			break;

		case 4:
			mSceneChanger->ChangeScene( eSceneState::eSceneModelView );
			break;

		case 5:
			SendMessage( CWindowSystem::GethWnd(),WM_CLOSE,0,0 );
			break;
		}
	}

}

//----------------------------------------------------
// 描画
//----------------------------------------------------
void CSceneDebug::Draw( void )
{
	CResourceManager::GetInstance()->GetXFont(0)->DrawColor( (ULONG)m_fontPos[0].x, (ULONG)m_fontPos[0].y, m_fontColor[0], "Title" );
	CResourceManager::GetInstance()->GetXFont(0)->DrawColor( (ULONG)m_fontPos[1].x, (ULONG)m_fontPos[1].y, m_fontColor[1], "ModeSelect");
	CResourceManager::GetInstance()->GetXFont(0)->DrawColor( (ULONG)m_fontPos[2].x, (ULONG)m_fontPos[2].y, m_fontColor[2], "GamePlay");
	CResourceManager::GetInstance()->GetXFont(0)->DrawColor( (ULONG)m_fontPos[3].x, (ULONG)m_fontPos[3].y, m_fontColor[3], "Result");
	CResourceManager::GetInstance()->GetXFont(0)->DrawColor( (ULONG)m_fontPos[4].x, (ULONG)m_fontPos[4].y, m_fontColor[4], "ModelView");
	CResourceManager::GetInstance()->GetXFont(0)->DrawColor( (ULONG)m_fontPos[5].x, (ULONG)m_fontPos[5].y, m_fontColor[5], "Exit" );
}

//----------------------------------------------------
// 終了
//----------------------------------------------------
void CSceneDebug::Finalize( void )
{
}

//----------------------------------------------------
// Load
//----------------------------------------------------
bool CSceneDebug::Load( void )
{
	return true;
}