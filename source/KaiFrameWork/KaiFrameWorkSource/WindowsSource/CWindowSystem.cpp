
#include "../../KaiFrameWorkHeader/WindowsHeader/CWindowSystem.h"

//----------------------------------------------------
// スクリーンの大きさを指定しない(初期値)コンストラクタ
//----------------------------------------------------
CWindowSystem::CWindowSystem(void)
{
	this->screenWidth	 = DEFAULT_WINDOW_X;
	this->screenHeight = DEFAULT_WINDOW_Y;

	// ウィンドウ作成
	this->CreateWnd();

	// クライアントサイズの設定
	this->SetClientSize();
	
	//メッセージ取出し
	PeekMessage(&msg,NULL,0,0,PM_REMOVE);
	
	// ms単位で時間取得
	timeBeginPeriod(1);	
}

//----------------------------------------------------
// スクリーンの大きさを指定したコンストラクタ
//----------------------------------------------------
CWindowSystem::CWindowSystem( CONST UINT screenWidth, CONST UINT screenHeight)
{	
	this->screenWidth  = screenWidth;
	this->screenHeight = screenHeight;

	// ウィンドウ作成
	this->CreateWnd();

	// クライアントサイズの設定
	this->SetClientSize();

	//メッセージ取出し
	PeekMessage(&msg,NULL,0,0,PM_REMOVE);
	
	// ms単位で時間取得
	timeBeginPeriod(1);
}

//----------------------------------------------------
// フルスクリーンモードで起動するためのコンストラクタ
//----------------------------------------------------
CWindowSystem::CWindowSystem(bool isFullScr)
{
	this->screenWidth = WINDOW_MAX_X;
	this->screenHeight = WINDOW_MAX_Y;

	// ウィンドウ作成
	this->CreateWnd();

	// クライアントサイズの設定
	this->SetClientSize();

	//メッセージ取出し
	PeekMessage(&msg,NULL,0,0,PM_REMOVE);
	
	// ms単位で時間取得
	timeBeginPeriod(1);
}

//----------------------------------------------------
// ウィンドウ作成
//----------------------------------------------------
HRESULT CWindowSystem::CreateWnd(void)
{
	HWND&		hWnd		= CWindowSystem::GethWnd();
	HINSTANCE	hInstance	= (HINSTANCE)GetModuleHandle(NULL);

	// ウィンドウクラスの作成
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

	// ウィンドウが作成できたかエラーチェック
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
// ウィンドウクラス生成
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

	// 作成できたかをチェック
	if(!RegisterClassEx(&wc) ){
		MessageBox(NULL,"設計エラー","bb",MB_OK);
		return	E_FAIL;
	}

	return	S_OK;
}

//----------------------------------------------------
// ウィンドウを表示
//----------------------------------------------------
HRESULT CWindowSystem::SetShowWindow(void)
{
	HWND&	hWnd = CWindowSystem::GethWnd();
	
	ShowWindow(hWnd, SW_SHOWNORMAL);
	
	return S_OK;
}

//----------------------------------------------------
// メッセージ送出(毎フレーム受け取る)
//----------------------------------------------------
BOOL CWindowSystem::PeekEventMessage(void)
{
	if( PeekMessage(&msg,NULL,0,0,PM_REMOVE) )
	{
		if(this->msg.message == WM_QUIT)
			return false;

		// メッセージ処理
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}

//----------------------------------------------------
// メッセージ送出(イベントを受け取った時のみ)
//----------------------------------------------------
BOOL CWindowSystem::GetEventMessage(void)
{
	if( GetMessage(&msg, NULL, 0, 0) )
	{
		if( msg.message == WM_QUIT )
		{
			return false;	
		}

		// メッセージ処理
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}

//----------------------------------------------------
// ウィンドウプロシージャ
//----------------------------------------------------
LRESULT CALLBACK CWindowSystem::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
		// ウィンドウ破棄
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
// クライアントサイズの設定
//----------------------------------------------------
void CWindowSystem::SetClientSize()
{
	RECT	rect;	// サイズ用ワーク
	HWND&	hWnd = CWindowSystem::GethWnd();

	GetClientRect(hWnd,&rect);	// クライアント部分のサイズの取得
	clientSize.x = rect.right - rect.left;
	clientSize.y = rect.bottom - rect.top;
}
