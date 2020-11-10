
#include "../../KaiFrameWorkHeader/DirectX9Header/CDirectX9Light.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CDirectLight::CDirectLight( void )
{
	ZeroMemory( &light,sizeof( D3DLIGHT9 ) );
	
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;
	light.Diffuse.a = 1.0f;
	
	light.Specular.r = 1.0f;
	light.Specular.g = 1.0f;
	light.Specular.b = 1.0f;

	light.Direction = D3DXVECTOR3( 0.0f,-1.0f,0.0f);
	light.Range = 1000.0f;

	this->Set();
	this->Switch( true );
	this->SetStageAmbient( 0x88888888 );

}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CDirectLight::~CDirectLight( void )
{
}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
void CDirectLight::Init( void )
{

}

//----------------------------------------------------
// ライトのセット
//----------------------------------------------------
void CDirectLight::Set( void )
{
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	pd3dDevice->SetLight( 0,&light );
}


//----------------------------------------------------
// ライトのON OFF
//----------------------------------------------------
void CDirectLight::Switch( bool isLight )
{
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	if( isLight == true )
	{
		pd3dDevice->LightEnable( 0, true );
	}
	else
	{
		pd3dDevice->LightEnable( 0, false );
	}
}


//----------------------------------------------------
// ライトの位置セット
//----------------------------------------------------
void CDirectLight::SetPosition( float xPos,float yPos,float zPos )
{
	light.Direction.x = xPos;
	light.Direction.y = yPos;
	light.Direction.z = zPos;
}

//----------------------------------------------------
// ステージ全体のアンビエント光のセット
//----------------------------------------------------
void CDirectLight::SetStageAmbient( DWORD ambient )
{
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	pd3dDevice->SetRenderState( D3DRS_AMBIENT, ambient );
}



