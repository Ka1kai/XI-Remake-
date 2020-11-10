
#include "../../KaiFrameWorkHeader/ResourceHeader/CResourceXFile.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CResourceXFile::CResourceXFile( void )
{
	m_pMeshMaterials	= nullptr;
	m_pMeshTexture		= nullptr;
	m_pMesh				= nullptr;
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CResourceXFile::~CResourceXFile( void )
{
	SAFE_DELETE_FREE( m_pMeshMaterials );	// マテリアルの解放

	if( m_pMeshTexture != nullptr )
	{	// テクスチャの解放
		for( int i = 0; ( m_pMeshTexture[i] )&&( ( unsigned ) i < m_materialsCount ); i ++ ){
			m_pMeshTexture[i]->Release();
			m_pMeshTexture[i] = nullptr;
		}
	}

	SAFE_DELETE_FREE( m_pMeshTexture );	// テクスチャのクリア
	SAFE_DELETE_RELESE( m_pMesh );		// メッシュの解放
}

//----------------------------------------------------
// Xファイルのロード
//----------------------------------------------------
HRESULT CResourceXFile::Load( CONST LPSTR filePath )
{
		// 3Dデバイスのポインタをシングルトンで取得
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
	
	DEBUG::PrintfColor( DEBUG::H_CYAN, "%s\n",filePath );

	// Xファイル読み込み
	if( FAILED(D3DXLoadMeshFromX
		(filePath,
		D3DXMESH_MANAGED,
		pd3dDevice,
		NULL,
		&m_pMaterialsBuffer,
		NULL,
		&m_materialsCount,
		&m_pMesh)))
	{	// 読み込み失敗
		DEBUG::PrintfColor( DEBUG::H_RED, " Load XFile Failed... \n\n" );
		return E_FAIL;
	}

	// マテリアルをセット
	this->SetMaterials();
 
	DEBUG::PrintfColor( DEBUG::H_GREEN, "Load XFile Successfully\n" );
	return S_OK;
}

//----------------------------------------------------
// マテリアルのセット
//----------------------------------------------------
HRESULT CResourceXFile::SetMaterials( void )
{
	// 3Dデバイスのポインタをシングルトンで取得
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
	
	D3DXMATERIAL *pMaterials = (D3DXMATERIAL *)m_pMaterialsBuffer->GetBufferPointer();
	// マテリアルの総数だけ、マテリアルとテクスチャの配列を動的に確保
	m_pMeshMaterials = (D3DMATERIAL9*)malloc(sizeof(D3DMATERIAL9)*m_materialsCount);
	m_pMeshTexture = (LPDIRECT3DTEXTURE9*)malloc(sizeof(LPDIRECT3DTEXTURE9)*m_materialsCount);

	// マテリアルをセットしていく
	for( int i = 0;( unsigned )i < m_materialsCount;i ++ ){
		m_pMeshMaterials[ i ] = pMaterials[ i ].MatD3D;
		m_pMeshMaterials[ i ].Ambient = m_pMeshMaterials[ i ].Diffuse;
		// テクスチャ描画
		if( pMaterials[i].pTextureFilename != "" && pMaterials[i].pTextureFilename != NULL )
		{
			// テクスチャ読み込み
			if( FAILED( D3DXCreateTextureFromFile(
				pd3dDevice,
				pMaterials[ i ].pTextureFilename,
				&m_pMeshTexture[ i ] ) ) )
			{
				m_pMeshTexture[ i ] = NULL;
				DEBUG::PrintfColor(DEBUG::H_RED, "Load XFile To Texture Failed...\n" );
				return E_FAIL;
			}
		} 
		else 
		{
			m_pMeshTexture[ i ] = NULL;
		}
	}

	DEBUG::PrintfColor( DEBUG::H_GREEN, "Load XFile To Texture Successfuly\n" );
	return S_OK;
}
