
#include "../../KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"

//----------------------------------------------------
// レンダリング開始
//----------------------------------------------------
BOOL CDirectDrawSystem::BeginScene( void )
{
	// デバイスポインタの取得
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0);
	
	if( SUCCEEDED( pd3dDevice->BeginScene() ) )
	{	// 描画開始
		return true;
	}

	return false;
}

//----------------------------------------------------
// レンダリング終了 
//----------------------------------------------------
void CDirectDrawSystem::EndScene( void )
{
	// デバイスポインタの取得
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
	
	pd3dDevice->EndScene();
}

//----------------------------------------------------
// 2Dレンダリング( 同次座標計算あり )
//----------------------------------------------------
void CDirectDrawSystem::DrawSpriteRHW( CONST LPDIRECT3DTEXTURE9 pTexture,CONST tagTSPRITERHW* pVertex )
{
	// デバイスポインタの取得
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	// αブレンドを行う
	pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,TRUE );

	// 透過処理を行う
	pd3dDevice->SetRenderState( D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA );

	// 描画の型変換
	pd3dDevice->SetFVF( FVF_VERTEX_SPRITERHW );

	// テクスチャ描画
	pd3dDevice->SetTexture( 0,pTexture );

	// ポリゴン描画
	pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, pVertex, sizeof( tagTSPRITERHW ) );
}

//----------------------------------------------------
// 2Dレンダリング( 同次座標計算あり テクスチャなし )
//----------------------------------------------------
void CDirectDrawSystem::DrawSpriteRHW( CONST tagTSPRITERHW *pVertex )
{
	// デバイスポインタの取得
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	// 描画の型変換
	pd3dDevice->SetFVF( FVF_VERTEX_SPRITERHW );

	// テクスチャ描画しない
	pd3dDevice->SetTexture( 0,NULL );

	// ポリゴン描画
	pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, pVertex, sizeof( tagTSPRITERHW ) );
}

//----------------------------------------------------
// 2Dスプライトレンダリング( 同次座標計算なし　テクスチャあり )
//----------------------------------------------------
void CDirectDrawSystem::DrawSprite( CONST LPDIRECT3DTEXTURE9 pTexture, tagTSPRITE* pSpriteVertex, CONST D3DXMATRIX* pWorldMtx )
{
	// デバイスのポインタを取得
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
	
	// ライティング計算はしない。深度バッファには書き込まない
	pd3dDevice->SetRenderState( D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA );
	// 光源計算オフ（頂点の色が有効になる）
	pd3dDevice->SetRenderState( D3DRS_LIGHTING,FALSE );
	// Zバッファを無効化（アルファブレンドを有効にするため）
	pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,FALSE );
	
	// テクスチャステージステート
	pd3dDevice->SetTextureStageState( 0,D3DTSS_ALPHAOP,D3DTOP_MODULATE );
	pd3dDevice->SetTextureStageState( 0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE );
	pd3dDevice->SetTextureStageState( 0,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE );

	pd3dDevice->SetTexture( 0, pTexture );					// テクスチャをセット
	pd3dDevice->SetFVF( FVF_VERTEX_SPRITE );				// 頂点の型をセット
	pd3dDevice->SetTransform( D3DTS_WORLD, pWorldMtx );		// ワールド行列をセット

	// レンダリング
	pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, 2, pSpriteVertex, sizeof(tagTSPRITE) );	

}

//----------------------------------------------------
// ビルボードレンダリング
//----------------------------------------------------
void CDirectDrawSystem::DrawBillBoard( CONST LPDIRECT3DTEXTURE9 pTexture, CONST D3DXMATRIX* pBillboardMtx, CONST tagTBILLBORDVERTEX* pBillboardVertex )
{
	// デバイスのポインタを取得
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
	
	// ライティング計算はしない。深度バッファには書き込まない
	pd3dDevice->SetRenderState( D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA );
	// 光源計算オフ（頂点の色が有効になる）
	pd3dDevice->SetRenderState( D3DRS_LIGHTING,FALSE );
	// Zバッファを無効化（アルファブレンドを有効にするため）
	pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,FALSE );
	
	// テクスチャステージステート
	pd3dDevice->SetTextureStageState( 0,D3DTSS_ALPHAOP,D3DTOP_MODULATE );
	pd3dDevice->SetTextureStageState( 0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE );
	pd3dDevice->SetTextureStageState( 0,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE );

	pd3dDevice->SetTexture( 0,pTexture );					// テクスチャをセット
	pd3dDevice->SetFVF( FVF_VERTEX_BILLBOARD );				// 頂点の型をセット
	pd3dDevice->SetTransform( D3DTS_WORLD,pBillboardMtx );	// ワールド行列をセット

	// レンダリング
	pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN,2,pBillboardVertex,sizeof(tagTBILLBORDVERTEX) );	
}

//----------------------------------------------------
// 3Dモデルレンダリング
//----------------------------------------------------
void CDirectDrawSystem::Draw3D( CResourceXFile *pModel, CONST D3DXMATRIX *pWorldMtx )
{
	// デバイスポインタの取得
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	// 光源計算オン
	pd3dDevice->SetRenderState( D3DRS_LIGHTING,TRUE );

	// Zバッファを有効化
	pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,TRUE );
	pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

	// 頂点の型をセット
	pd3dDevice->SetFVF( FVF_VERTEX_3D );
	
	// メッシュをマテリアル単位で描画
	pd3dDevice->SetTransform( D3DTS_WORLD,pWorldMtx);

	// レンダリング
	for( unsigned int i = 0; i < pModel->GetMaterialCount(); ++ i ){
		pd3dDevice->SetMaterial( &pModel->GetMeshMaterial()[i] );
		pd3dDevice->SetTexture( 0,pModel->GetMeshTexture()[i] );
		pModel->GetMesh()->DrawSubset( i );
	}
}

//----------------------------------------------------
// 3Dモデルレンダリング(textureの指定) 
//----------------------------------------------------
void CDirectDrawSystem::Draw3D( CResourceXFile* pModel, CONST D3DXMATRIX* pWorldMtx, BOOL isTexture )
{
	// デバイスのポインタを取得
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	// 光源計算オン
	pd3dDevice->SetRenderState( D3DRS_LIGHTING,TRUE );
	// Zバッファを有効化
	pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,TRUE );

	pd3dDevice->SetFVF( FVF_VERTEX_3D );

	if( isTexture == false )
	{
		pd3dDevice->SetTexture( 0,NULL );	// テクスチャなし
	}

	pd3dDevice->SetTransform( D3DTS_WORLD,pWorldMtx );

	// レンダリング
	for( unsigned int i = 0; i < pModel->GetMaterialCount(); ++i ){
		pd3dDevice->SetMaterial( &pModel->GetMeshMaterial()[i] );
		pModel->GetMesh()->DrawSubset( i );
	}
}

//----------------------------------------------------
// 3Dモデルレンダリング( 色指定 )
//----------------------------------------------------
void CDirectDrawSystem::Draw3D( CResourceXFile* pModel, CONST D3DXMATRIX* pWorldMtx, D3DXCOLOR* color )
{
		// デバイスポインタの取得
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	// 光源計算オン
	pd3dDevice->SetRenderState( D3DRS_LIGHTING,TRUE );

	// Zバッファを有効化
	pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,TRUE );
	pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

	// 頂点の型をセット
	pd3dDevice->SetFVF( FVF_VERTEX_3D );
	
	// メッシュをマテリアル単位で描画
	pd3dDevice->SetTransform( D3DTS_WORLD,pWorldMtx);

	// レンダリング
	for( unsigned int i = 0; i < pModel->GetMaterialCount(); ++ i ){
		D3DMATERIAL9 workMat;
		
		// 色を作る
		::CopyMemory( &workMat,&pModel->GetMeshMaterial()[i],sizeof( D3DMATERIAL9 ) );

		workMat.Diffuse.r = pModel->GetMeshMaterial()[i].Diffuse.r * color->r;
		workMat.Diffuse.g = pModel->GetMeshMaterial()[i].Diffuse.g * color->g;
		workMat.Diffuse.b = pModel->GetMeshMaterial()[i].Diffuse.b * color->b;
		workMat.Diffuse.a = pModel->GetMeshMaterial()[i].Diffuse.a * color->a;

		pd3dDevice->SetMaterial( &workMat );
		pd3dDevice->SetTexture( 0,pModel->GetMeshTexture()[i] );
		pModel->GetMesh()->DrawSubset( i );
	}
}

//----------------------------------------------------
// クローン3Dモデルレンダリング
//----------------------------------------------------
void CDirectDrawSystem::Draw3DClone( UINT numFaces, CONST LPDIRECT3DTEXTURE9 textureData, tagTORIGINALMESHVERTEX* pCloneVertex, CONST D3DXMATRIX* pCloneMtx )
{
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	//pd3dDevice->SetFVF( FVF_VERTEX_CLONE );

	pd3dDevice->SetTexture( 0, textureData );
	pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,true );	// αブレンドの処理を有効にする

	for( UINT i = 0; i < numFaces; ++ i ){
		pd3dDevice->SetTransform(D3DTS_WORLD,pCloneMtx);
		pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP,1,pCloneVertex,sizeof(tagTORIGINALMESHVERTEX));
	
	}
}

//----------------------------------------------------
// クローン3Dモデルレンダリング(テクスチャなし)
//----------------------------------------------------
void CDirectDrawSystem::Draw3DClone( UINT numFaces, tagTORIGINALMESHVERTEX* pCloneVertex, CONST D3DXMATRIX* pCloneMtx )
{
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	//pd3dDevice->SetFVF( FVF_VERTEX_CLONE );
	pd3dDevice->SetTexture( 0, NULL );

	// クローンの3Dモデルレンダリング
	for( UINT i = 0; i < numFaces; ++ i ){
		pd3dDevice->SetTransform( D3DTS_WORLD, pCloneMtx );
		pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP,1,&pCloneVertex[i],sizeof( tagTORIGINALMESHVERTEX ) );
	}
}

//----------------------------------------------------
// 形状レンダリング ( スフィア,ボックス )
//----------------------------------------------------
void CDirectDrawSystem::DrawShape( CONST D3DXMATRIX* worldMtx, CONST D3DMATERIAL9* shapeMat, CONST LPD3DXMESH shapeMesh )
{
	// デバイスのポインタを取得
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );				// αブレンドを行う
	pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );		// αソースカラーの指定
	pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );	// αデスティネーションカラーの指定
	
	pd3dDevice->SetRenderState(D3DRS_LIGHTING,TRUE);		// ライトの計算をON
	pd3dDevice->SetRenderState(D3DRS_SPECULARENABLE,TRUE);

	// 行列をセット
	pd3dDevice->SetTransform( D3DTS_WORLD,worldMtx );

	// テクスチャのセット
	pd3dDevice->SetTexture( 0,NULL );
	
	// マテリアルのセット
	pd3dDevice->SetMaterial( shapeMat );
	
	// レンダリング
	shapeMesh->DrawSubset(0);
}

//----------------------------------------------------
// パーティクルレンダリング
// 加算合成あり，ライト計算なし，αブレンドあり
//----------------------------------------------------
void CDirectDrawSystem::DrawParticle( CONST LPDIRECT3DTEXTURE9 pTexture, CONST D3DXMATRIX* pBillboardMtx, CONST tagTBILLBORDVERTEX* pBillboardVertex )
{
	// デバイスポインタの取得
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
	
	pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,TRUE );
	pd3dDevice->SetRenderState( D3DRS_SRCBLEND,D3DBLEND_SRCALPHA );
	pd3dDevice->SetRenderState( D3DRS_BLENDOP,D3DBLENDOP_ADD );
	pd3dDevice->SetRenderState( D3DRS_DESTBLEND,D3DBLEND_ONE );		// 加算合成
	
	// ライティング計算はしない。深度バッファには書き込まない
	pd3dDevice->SetRenderState( D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA );
	// 光源計算オフ（頂点の色が有効になる）
	pd3dDevice->SetRenderState( D3DRS_LIGHTING,FALSE );
	// Zバッファを無効化（アルファブレンドを有効にするため）
	pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,FALSE );
	
	// テクスチャステージステート
	pd3dDevice->SetTextureStageState( 0,D3DTSS_ALPHAOP,D3DTOP_MODULATE );
	pd3dDevice->SetTextureStageState( 0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE );
	pd3dDevice->SetTextureStageState( 0,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE );

	pd3dDevice->SetTexture( 0,pTexture );					// テクスチャセット
	pd3dDevice->SetFVF( FVF_VERTEX_BILLBOARD );				// 頂点の型セット
	pd3dDevice->SetTransform( D3DTS_WORLD,pBillboardMtx );	// ワールド行列をセット

	// レンダリング
	pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN,2,pBillboardVertex,sizeof(tagTBILLBORDVERTEX) );
}

//----------------------------------------------------
// デバッグステージレンダリング
// テクスチャなし
//----------------------------------------------------
void CDirectDrawSystem::DrawDebugStage	( CONST UINT numLines, CONST tagTDEBUGVERTEX* pDebugStageVertex )
{
	// デバイスポインタの取得
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
	
	D3DXMATRIX workMtx;
	D3DXMatrixIdentity( &workMtx );

	// ライティング計算はしない。深度バッファには書き込まない
	pd3dDevice->SetRenderState( D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA );
	// 光源計算オフ（頂点の色が有効になる）
	pd3dDevice->SetRenderState( D3DRS_LIGHTING,FALSE );
	// Zバッファを無効化（アルファブレンドを有効にするため）
	pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,FALSE );

	pd3dDevice->SetTexture( 0,NULL );
	pd3dDevice->SetFVF( FVF_VERTEX_DEBUG );
	pd3dDevice->SetTransform( D3DTS_WORLD,&workMtx );

	// レンダリング
	pd3dDevice->DrawPrimitiveUP( D3DPT_LINELIST,numLines,pDebugStageVertex,sizeof( tagTDEBUGVERTEX ) ); 
}
