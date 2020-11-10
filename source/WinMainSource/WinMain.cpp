
#define _WINMAIN_MODULE_
#include "WinMain.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
// ���������[�N���N�����Ă��Ȃ������m�F���邽�߂̃e�X�g
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
	
	MSG	msg;

	CWindowSystem*		pWnd  = new CWindowSystem( 800, 640 );		// �E�B���h�E�̍쐬	
	CFpsControl*		pFpsControl  = new CFpsControl();			// FPS���R���g���[������N���X�̃C���X�^���X��
	CDirectX9FrameWork*	pDirectxFw = new CDirectX9FrameWork;		// DirectX9�̃N���X���C���X�^���X��

	// DirectX9�̏�����
	pDirectxFw->Init(); 

	CMySQLManager::GetInstance()->ConnectDatabase();

	// �Q�[���̋N���V�[��
	CSceneManager* sceneManager = new CSceneManager( GAME_STATUS );

#ifdef _DEBUG
	CDebugMode::m_pFps = pFpsControl->GetFPS();
#endif

	while( 1 )
	{
		if( !pWnd->PeekEventMessage() )
		{
			break;
		}
		else
		{
			if( pFpsControl->TuneFps() )
			{
				sceneManager->Run();

				if( CDirectDrawSystem::GetInstance()->BeginScene() )
				{
					sceneManager->Draw();
					CDirectDrawSystem::GetInstance()->EndScene();
				}
				CDirectDrawSystem::GetInstance()->Present();
			}
			pFpsControl->CalcFPS();
		}
	}

	SAFE_DELETE( pDirectxFw );
	SAFE_DELETE( pFpsControl );
	SAFE_DELETE( sceneManager );

	msg.wParam = pWnd->GetMessageWParam();
	SAFE_DELETE( pWnd );

	return msg.wParam;
}


