
#include "CSceneModelView.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CSceneModelView::CSceneModelView( CSceneChange* changeScene ) : CSceneBase(changeScene)
{

}

//----------------------------------------------------
// ロード
//----------------------------------------------------
bool CSceneModelView::Load( void )
{
	m_pDirectCamera = new CDirectCamera;

	m_pDirectLight = new CDirectLight;

	m_pViewObj = new CObjectBase;

	CResourceManager::GetInstance()->LoadXFile( modelViewPath );

	// Manager
	m_pModelViewBackManager = new CModelViewBackManager;
	m_pModelViewStage = new CModelViewStage;
	m_pSnowObjManager = new CSnowObj;

	return true;

}

//----------------------------------------------------
// モデルビューシーンの初期化
//----------------------------------------------------
void CSceneModelView::Initialize()
{
	CResourceManager::GetInstance()->CreateXFont( 1, 8, 14 );
	m_pDirectCamera->Init( 800,640 );
	m_pDirectCamera->SetPosition( 0.0f,10.0f,-10.0f );

	m_pViewObj->Init();

	// Manager
	m_pModelViewBackManager->Init();

	// 描画モードをポリゴンに変更
	CDirectDrawSystem::GetInstance()->SetFillMode( D3DFILL_SOLID );

	// カリングON
	CDirectDrawSystem::GetInstance()->SetCallMode( false );

	// アンビエント値更新
	m_pDirectLight->SetStageAmbient( 0x88888888 );

	// ライトON
	m_pDirectLight->Switch( true );

	// テクスチャON
	m_isTexture = true;

	m_isCull = true;
	m_isLight = true;
	m_isMouseHoil = false;
	m_isMouse = false;

	m_degree = 0.0f;

	// モデルビューステージの初期化
	m_pModelViewStage->Init();

	m_eModelViewState = VIEW_NORMAL;
}

//----------------------------------------------------
// モデルビューシーンの終了
//----------------------------------------------------
void CSceneModelView::Finalize( void )
{
	SAFE_DELETE( m_pViewObj );	// 表示するモデル
	SAFE_DELETE( m_pDirectCamera );
	SAFE_DELETE( m_pDirectLight );
	SAFE_DELETE( m_pModelViewBackManager );
	SAFE_DELETE( m_pModelViewStage );
	SAFE_DELETE( m_pSnowObjManager );
}

//----------------------------------------------------
// モデルビューシーンの処理
//----------------------------------------------------
void CSceneModelView::Run( void )
{
	CInputKeyboard::GetInstance()->Update();

	m_pSnowObjManager->Emitter();
	m_pSnowObjManager->Move();

	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_P ) )
	{
//		m_pSplitParticle->Emitter();
	}

//	m_pViewObj->InitMtx();
	
	this->DrawModeChange();
	this->CalcDepthCamera();
	this->CalcCameraPos();
	this->RotationModel();


	// モデルビューワーの終了
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_ESCAPE ) )
	{
		mSceneChanger->ChangeScene( eSceneDebug );
	}
/*
	if( m_pModelViewBackManager->GetIsFade() )
	{
		if( m_pModelViewBackManager->Fade() )
		{
			mSceneChanger->ChangeScene( eSceneTitle );
			CDirectDrawSystem::GetInstance()->SetFillMode( D3DFILL_SOLID );
			CDirectDrawSystem::GetInstance()->SetCallMode( true );
		}
	}
	*/
	
//	m_pViewObj->CalcLocalMtx();
}

//----------------------------------------------------
// モデルビューシーンの描画
//----------------------------------------------------
void CSceneModelView::Draw( void )
{
	m_pModelViewStage->Draw();
	
	if( m_isTexture )
	{
		CDirectDrawSystem::GetInstance()->Draw3D( CResourceManager::GetInstance()->GetXFile( modelViewPath ),m_pViewObj->GetWorldMtx());
	}
	else if( m_isTexture )
	{
		CDirectDrawSystem::GetInstance()->Draw3D( CResourceManager::GetInstance()->GetXFile( modelViewPath ),m_pViewObj->GetWorldMtx(),NULL );
	}

//	m_pSnowObjManager->Draw( m_pDirectCamera );

	CResourceManager::GetInstance()->GetXFont(1)->DrawColor( 690, 5, D3DXCOLOR( 255,0,0,100 ), "ESC:Exit" );
	CResourceManager::GetInstance()->GetXFont(1)->DrawColor( 680, 20, D3DXCOLOR( 255,0,0,100 ), "Right/Left:Rotation" );
	CResourceManager::GetInstance()->GetXFont(1)->DrawColor( 600, 35, D3DXCOLOR( 255,0,0,100 ), "F1,F2,F3:ViewChange" );
	CResourceManager::GetInstance()->GetXFont(1)->DrawColor( 560, 50, D3DXCOLOR( 255,0,0,100 ), "F4,F5,F6:DrawChange" );
	CResourceManager::GetInstance()->GetXFont(1)->DrawColor( 600, 65, D3DXCOLOR( 255,0,0,100 ), "F7:CalingO N/OFF" );
	CResourceManager::GetInstance()->GetXFont(1)->DrawColor( 580, 80, D3DXCOLOR( 255,0,0,100 ), "F8:Texture ON/OFF" );
	CResourceManager::GetInstance()->GetXFont(1)->DrawColor( 620, 95, D3DXCOLOR( 255,0,0,100 ), "F9:Light ON/OFF" );
	CResourceManager::GetInstance()->GetXFont(1)->DrawColor( 670, 110, D3DXCOLOR( 255,0,0,100 ), "F10:Initialize" );

	m_pModelViewBackManager->Draw();

}

//----------------------------------------------------
// 画像の更新
//----------------------------------------------------
void CSceneModelView::UpdatePict( void )
{
	this->Initialize();
}

//----------------------------------------------------
// カメラの回転
//----------------------------------------------------
void CSceneModelView::RotationCamera( DWORD direction )
{
	switch( direction )
	{
	// 左移動
	case VK_LEFT:
		m_degree = 1.0f;
		m_pDirectCamera->LocalRotationQuaterY( m_degree );
		break;
	// 右移動
	case VK_RIGHT:
		m_degree = -1.0f;
		m_pDirectCamera->LocalRotationQuaterY( m_degree );
		break;
	}	
}

//----------------------------------------------------
// 描画モード変更
//----------------------------------------------------
void CSceneModelView::DrawModeChange( void )
{
	// X視点
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_F1 ) )
	{
		m_pDirectCamera->Init();
		m_pDirectCamera->SetPosition( 40.0f,0.0f,19.0f );
		m_eModelViewState = VIEW_X;
	}

	// Y視点
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_F2 ) )
	{
		m_pDirectCamera->Init();
		m_pDirectCamera->SetPosition( 0.0f,40.0f,19.0 );
		m_eModelViewState = VIEW_Y;
	}

	// Z視点
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_F3 ) )
	{
		m_pDirectCamera->Init();
		m_pDirectCamera->SetPosition( 0.0f,0.0f,-20.0f );
		m_eModelViewState = VIEW_Z;
	}

	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_F4 ) )
	{	// 点描画
		CDirectDrawSystem::GetInstance()->SetFillMode( D3DFILL_POINT );
	}
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_F5 ) )
	{	// ワイヤーフレーム
		CDirectDrawSystem::GetInstance()->SetFillMode( D3DFILL_WIREFRAME );
	}
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_F6 ) )
	{	// ポリゴン描画
		CDirectDrawSystem::GetInstance()->SetFillMode( D3DFILL_SOLID );
	}

	// カリングON OFF　切り替え
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_F7 ) )
	{	
		m_isCull ^= true;
		CDirectDrawSystem::GetInstance()->SetCallMode( m_isCull );
	}

	// テクスチャON OFF切り替え
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_F8 ) )
	{
		m_isTexture ^= true;
	}

	// ライトのON OFF切り替え
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_F9 ) )
	{
		m_isLight ^= true;
		m_pDirectLight->Switch( m_isLight );
	}

	// 左回転
	if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_LEFT ) )
	{
		this->RotationCamera( VK_LEFT );
	}

	// 右回転
	if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_RIGHT ) )
	{
		this->RotationCamera( VK_RIGHT );
	}

	// クリア
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_F10 ) )
	{
		CDirectDrawSystem::GetInstance()->SetFillMode( D3DFILL_SOLID );
		CDirectDrawSystem::GetInstance()->SetCallMode( true );
		m_isTexture = true;
		this->Initialize();
	}

	// テクスチャの切り替え
	/*
	if( pInput->GetKeyboardTrigger( DIK_RIGHT ) )
	{
		if( m_viewNo < MODEL_CNT - 1 )
		{
			m_viewNo ++;
			this->UpdatePict();
		}
	}

	if( pInput->GetKeyboardTrigger( DIK_LEFT ) )
	{
		if( m_viewNo > 0 )
		{
			m_viewNo --;
			this->UpdatePict();
		}
	}
	*/

}

//----------------------------------------------------
// カメラの奥行調整
//----------------------------------------------------
void CSceneModelView::CalcDepthCamera( void )
{
	// ホイールの上下で奥行を調整
	/*
	if( CInputMouse::GetInstance()->GetWheelRotation() >= 1 )
	{
		switch( m_eModelViewState )
		{
		case VIEW_X:
			m_pDirectCamera->SetPosition( -CAMERA_DEPTH,0.0f,0.0f );
			m_pDirectCamera->SetAt( -CAMERA_DEPTH,0.0f,0.0f );
			break;

		case VIEW_Y:
			m_pDirectCamera->SetPosition( 0.0f,-CAMERA_DEPTH,0.0f );
			m_pDirectCamera->SetAt( 0.0f,-CAMERA_DEPTH,0.0f );
			break;

		case VIEW_Z:
			m_pDirectCamera->SetPosition( 0.0f,0.0f,CAMERA_DEPTH );
			m_pDirectCamera->SetAt( 0.0f,0.0f,CAMERA_DEPTH );
			break;

		case VIEW_NORMAL:
			m_pDirectCamera->SetPosition( 0.0f,0.0f,CAMERA_DEPTH );
			m_pDirectCamera->SetAt( 0.0f,0.0f,CAMERA_DEPTH );
			break;
		}
	}
	if( CInputMouse::GetInstance()->GetWheelRotation() <= -1 )
	{
		switch( m_eModelViewState )
		{
		case VIEW_X:
			m_pDirectCamera->SetPosition( CAMERA_DEPTH,0.0f,0.0f);
			m_pDirectCamera->SetAt( CAMERA_DEPTH,0.0f,0.0f );
			break;

		case VIEW_Y:
			m_pDirectCamera->SetPosition( 0.0f,CAMERA_DEPTH,0.0f );
			m_pDirectCamera->SetAt( 0.0f,CAMERA_DEPTH,0.0f );
			break;

		case VIEW_Z:
			m_pDirectCamera->SetPosition( 0.0f,0.0f,-CAMERA_DEPTH );
			m_pDirectCamera->SetAt( 0.0f,0.0f,-CAMERA_DEPTH );
			break;
		
		case VIEW_NORMAL:
			m_pDirectCamera->SetPosition( 0.0f,0.0f,-CAMERA_DEPTH );
			m_pDirectCamera->SetAt( 0.0f,0.0f,-CAMERA_DEPTH );
			break;
		}
	}
	*/
}

//----------------------------------------------------
// カメラの位置調整
//----------------------------------------------------
void CSceneModelView::CalcCameraPos( void )
{
	static long nowMouseXpos,nowMouseYpos;
	static long oldMouseXpos,oldMouseYpos;
	static long mouseXpos,mouseYpos;

	// カメラ位置の移動
	/*
	if( CInputMouse::GetInstance()->GetTriggerButton() && !m_isMouseHoil )
	{
		nowMouseXpos = pInput->GetMouseXpos();
		nowMouseYpos = pInput->GetMouseYpos();
		m_isMouseHoil = true;
	}

	if( m_isMouseHoil )
	{
		oldMouseXpos = nowMouseXpos;
		oldMouseYpos = nowMouseYpos;

		nowMouseXpos = pInput->GetMouseXpos();
		nowMouseYpos = pInput->GetMouseYpos();

		mouseXpos = nowMouseXpos - oldMouseXpos;
		mouseYpos = nowMouseYpos - oldMouseYpos;

		switch( m_eModelViewState )
		{
		case VIEW_X:
			m_pDirectCamera->SetAt( 0.0f,mouseYpos * 0.1f,mouseXpos * - 0.1f );
			m_pDirectCamera->SetPosition( 0.0f,mouseYpos * 0.1f,mouseXpos * -0.1f );
			break;	

		case VIEW_Y:
			m_pDirectCamera->SetAt( mouseXpos * -0.1f,0.0f,mouseYpos * 0.1f );
			m_pDirectCamera->SetPosition( mouseXpos * -0.1f,0.0f,mouseYpos * 0.1f );
			break;

		case VIEW_Z:
			m_pDirectCamera->SetAt( mouseXpos * -0.1f, mouseYpos * 0.1f,0.0f );	
			m_pDirectCamera->SetPosition( mouseXpos * -0.1f, mouseYpos * 0.1f,0.0f );
			break;

		case VIEW_NORMAL:
			m_pDirectCamera->SetAt( mouseXpos * 0.1f, mouseYpos * -0.1f,0.0f );	
			m_pDirectCamera->SetPosition( mouseXpos * 0.1f, mouseYpos * -0.1f,0.0f );
			break;
		}
	}

	// 離されたら
	if( pInput->GetMouseCenterRelease() && m_isMouseHoil )
	{
		m_isMouseHoil = false;
	}
	*/
}

//----------------------------------------------------
// モデルの回転
//----------------------------------------------------
void CSceneModelView::RotationModel( void )
{
	static long oldXpos,oldYpos,oldZpos;
	static long nowXpos,nowYpos,nowZpos;
	static long mouseXpos,mouseYpos,mouseZpos;
	
	/*
	if( pInput->GetMouseLeftTrigger() || pInput->GetMouseRightTrigger() && !m_isMouse )
	{
		nowXpos = pInput->GetMouseXpos();
		nowYpos = pInput->GetMouseYpos();
		m_isMouse = true;
	}

	if( m_isMouse )
	{		
		oldXpos = nowXpos;
		oldYpos = nowYpos;

		nowXpos = pInput->GetMouseXpos();
		nowYpos = pInput->GetMouseYpos();

		mouseXpos = nowXpos - oldXpos;
		mouseYpos = nowYpos - oldYpos;

		if( mouseXpos != 0 || mouseYpos != 0 )
		{
			m_pViewObj->RotationX( (float)mouseXpos );
			m_pViewObj->RotationY( (float)mouseYpos );

			switch( m_eModelViewState )
			{
			case VIEW_X:
				m_pViewObj->CalcRotation( 0.0f, -mouseXpos * 0.01f,-mouseYpos* 0.01f );
				break;

			case VIEW_Y:
				m_pViewObj->CalcRotation( -mouseYpos * 0.01f ,0.0f,-mouseXpos * 0.01f );
				break;

			case VIEW_Z:
				m_pViewObj->CalcRotation( -mouseYpos* 0.01f, -mouseXpos * 0.01f,0.0f );
				break;

			case VIEW_NORMAL:
				m_pViewObj->CalcRotation( -mouseYpos* 0.01f, -mouseXpos * 0.01f,0.0f );
				break;
			}
		}
	}

	if( pInput->GetMouseLeftRelease() || pInput->GetMouseRightRelease() )
	{
		m_isMouse = false;
	}
	*/
}