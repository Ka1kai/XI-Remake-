
#include "../../KaiFrameWorkHeader/DirectX9Header/CDirectX9FrameWork.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CDirectX9FrameWork::CDirectX9FrameWork( void )
{
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CDirectX9FrameWork::~CDirectX9FrameWork( void )
{
}

//----------------------------------------------------
// DirectX9の初期化
//----------------------------------------------------
HRESULT CDirectX9FrameWork::Init( void )
{
	CONST HWND&	hWnd = CWindowSystem::GethWnd();
	LPDIRECT3D9& pd3d = CDirectX9FrameWork::Getpd3d();
	LPDIRECT3DDEVICE9& pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	D3DPRESENT_PARAMETERS	d3dpp;

	if( NULL == ( pd3d = Direct3DCreate9(D3D_SDK_VERSION )))
	{  //Direct3Dオブジェクトの作成失敗
		return E_FAIL;	
	}

	ZeroMemory( &d3dpp, sizeof(d3dpp));

	d3dpp.Windowed					= TRUE;							// ウィンドウモード
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;		// 映像信号に同期してフリップする
	d3dpp.BackBufferFormat			= D3DFMT_UNKNOWN;				// バックバッファのフォーマットは現在設定されているものを使う
	d3dpp.EnableAutoDepthStencil	= TRUE;							// デプスバッファ(Zバッファ)とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;					// デプスバッファとして16bitを使う

	if( FAILED( pd3d->CreateDevice(	D3DADAPTER_DEFAULT,							// プライマリアダプタを選択
										D3DDEVTYPE_HAL,							// ハードウェアによる描画処理を選択
										hWnd,									// ウィンドウハンドル
										D3DCREATE_HARDWARE_VERTEXPROCESSING |	// ハードウェアによる頂点計算を選択 
										D3DCREATE_MULTITHREADED ,				// マルチスレッドのフラグをONにする	
										&d3dpp,									// D3D Object
										&pd3dDevice	)))
	{
		DEBUG::PrintfColor( DEBUG::H_RED, "---- Init DirectX Failed... ----\n\n" );
		return	E_FAIL;		// 成功すればデバイスが作られる
	}

	pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );						// Zバッファを使用
	pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );				// αブレンドを行う
	pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );		// αソースカラーの指定
	pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );	// αデスティネーションカラーの指定
	pd3dDevice->SetRenderState( D3DRS_CULLMODE,D3DCULL_NONE );

	pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	pd3dDevice->SetFVF( D3DFVF_XYZ  | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
	

	DEBUG::PrintfColor( DEBUG::H_GREEN, "---- Init DirectX Successfully ---- \n\n" );
	return D3D_OK;		// 生成成功

}

