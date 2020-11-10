
#include "../../KaiFrameWorkHeader/WindowsHeader/CWindowSystem.h"

//----------------------------------------------------
// �X�N���[���̑傫�����w�肵�Ȃ�(�����l)�R���X�g���N�^
//----------------------------------------------------
CWindowSystem::CWindowSystem(void)
{
	this->screenWidth	 = DEFAULT_WINDOW_X;
	this->screenHeight = DEFAULT_WINDOW_Y;

	// �E�B���h�E�쐬
	this->CreateWnd();

	// �N���C�A���g�T�C�Y�̐ݒ�
	this->SetClientSize();
	
	//���b�Z�[�W��o��
	PeekMessage(&msg,NULL,0,0,PM_REMOVE);
	
	// ms�P�ʂŎ��Ԏ擾
	timeBeginPeriod(1);	
}

//----------------------------------------------------
// �X�N���[���̑傫�����w�肵���R���X�g���N�^
//----------------------------------------------------
CWindowSystem::CWindowSystem( CONST UINT screenWidth, CONST UINT screenHeight)
{	
	this->screenWidth  = screenWidth;
	this->screenHeight = screenHeight;

	// �E�B���h�E�쐬
	this->CreateWnd();

	// �N���C�A���g�T�C�Y�̐ݒ�
	this->SetClientSize();

	//���b�Z�[�W��o��
	PeekMessage(&msg,NULL,0,0,PM_REMOVE);
	
	// ms�P�ʂŎ��Ԏ擾
	timeBeginPeriod(1);
}

//----------------------------------------------------
// �t���X�N���[�����[�h�ŋN�����邽�߂̃R���X�g���N�^
//----------------------------------------------------
CWindowSystem::CWindowSystem(bool isFullScr)
{
	this->screenWidth = WINDOW_MAX_X;
	this->screenHeight = WINDOW_MAX_Y;

	// �E�B���h�E�쐬
	this->CreateWnd();

	// �N���C�A���g�T�C�Y�̐ݒ�
	this->SetClientSize();

	//���b�Z�[�W��o��
	PeekMessage(&msg,NULL,0,0,PM_REMOVE);
	
	// ms�P�ʂŎ��Ԏ擾
	timeBeginPeriod(1);
}

//----------------------------------------------------
// �E�B���h�E�쐬
//----------------------------------------------------
HRESULT CWindowSystem::CreateWnd(void)
{
	HWND&		hWnd		= CWindowSystem::GethWnd();
	HINSTANCE	hInstance	= (HINSTANCE)GetModuleHandle(NULL);

	// �E�B���h�E�N���X�̍쐬
	SetWindowClass();

	hWnd = CreateWindow(wc.lpszClassName,
						GAME_TITLE,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						screenWidth,
						screenHeight,
						NULL,
						NULL,
						hInstance,
						NULL);

	// �E�B���h�E���쐬�ł������G���[�`�F�b�N
	if( hWnd == NULL )
	{
		DEBUG::PrintfColor(DEBUG::H_RED,"---- Create Window Failed... ----\n\n" );
		return E_FAIL;
	}

	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);

	DEBUG::PrintfColor(DEBUG::H_GREEN, "---- Create Window Successfully ----\n\n" );
	return S_OK;
}

//----------------------------------------------------
// �E�B���h�E�N���X����
//----------------------------------------------------
HRESULT CWindowSystem::SetWindowClass(void)
{
	HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);

	wc.cbSize			= sizeof(WNDCLASSEX);
	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.hInstance		= hInstance;
	wc.lpszClassName	= WINDOW_CLASS_NAME;
	wc.lpfnWndProc		= (WNDPROC)WndProc;
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName		= NULL;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;

	// �쐬�ł��������`�F�b�N
	if(!RegisterClassEx(&wc) ){
		MessageBox(NULL,"�݌v�G���[","bb",MB_OK);
		return	E_FAIL;
	}

	return	S_OK;
}

//----------------------------------------------------
// �E�B���h�E��\��
//----------------------------------------------------
HRESULT CWindowSystem::SetShowWindow(void)
{
	HWND&	hWnd = CWindowSystem::GethWnd();
	
	ShowWindow(hWnd, SW_SHOWNORMAL);
	
	return S_OK;
}

//----------------------------------------------------
// ���b�Z�[�W���o(���t���[���󂯎��)
//----------------------------------------------------
BOOL CWindowSystem::PeekEventMessage(void)
{
	if( PeekMessage(&msg,NULL,0,0,PM_REMOVE) )
	{
		if(this->msg.message == WM_QUIT)
			return false;

		// ���b�Z�[�W����
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}

//----------------------------------------------------
// ���b�Z�[�W���o(�C�x���g���󂯎�������̂�)
//----------------------------------------------------
BOOL CWindowSystem::GetEventMessage(void)
{
	if( GetMessage(&msg, NULL, 0, 0) )
	{
		if( msg.message == WM_QUIT )
		{
			return false;	
		}

		// ���b�Z�[�W����
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}

//----------------------------------------------------
// �E�B���h�E�v���V�[�W��
//----------------------------------------------------
LRESULT CALLBACK CWindowSystem::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
		// �E�B���h�E�j��
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

//----------------------------------------------------
// �N���C�A���g�T�C�Y�̐ݒ�
//----------------------------------------------------
void CWindowSystem::SetClientSize()
{
	RECT	rect;	// �T�C�Y�p���[�N
	HWND&	hWnd = CWindowSystem::GethWnd();

	GetClientRect(hWnd,&rect);	// �N���C�A���g�����̃T�C�Y�̎擾
	clientSize.x = rect.right - rect.left;
	clientSize.y = rect.bottom - rect.top;
}
