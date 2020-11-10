//----------------------------------------------------
// CDirectDrawSystem Header 
//　DirectXの描画システム
//
// @date	2013/5/1
// @author  T.Kawashita
//----------------------------------------------------
#ifndef _C_DIRECTX9_DRAW_SYSTEM_H_
#define _C_DIRECTX9_DRAW_SYSTEM_H_

// 内部ヘッダー読み込み
#include <d3dx9.h>

// 外部ヘッダー読み込み
#include "../DirectX9Header/CDirectX9FrameWork.h"
#include "../GameObjectHeader/2D/C2DSprite.h"
#include "../GameObjectHeader/2D/C2DSpriteRHW.h"
#include "../GameObjectHeader/CObjectBase.hpp"
#include "../GameObjectHeader/BillBoard/CBillBoard.h"
#include "../DebugHeader/CDebugStage.h"
#include "../ResourceHeader/COriginalMesh.h"
#include "../ResourceHeader/CResourceXFile.h"
#include "../ResourceHeader/CResourceTexture.h"

#define	FVF_VERTEX_SPRITERHW	( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )	// Sprite(RHWあり)描画用FVF
#define FVF_VERTEX_SPRITE		( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )		// Sprite描画用FVF
#define FVF_VERTEX_3D			( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )		// 3D描画用FVF
#define FVF_VERTEX_MESH			( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )		// クローンモデル用FVF
#define FVF_VERTEX_BILLBOARD	( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )		// ビルボード用FVF
#define FVF_VERTEX_DEBUG		( D3DFVF_XYZ | D3DFVF_DIFFUSE )						// デバッグ用FVF
#define FVF_VERTEX_CLONE		( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )		// クローン用FVF

class CDirectDrawSystem
{
private:
	// コンストラクタ
	CDirectDrawSystem				( void ){}
	CDirectDrawSystem				( CONST CDirectDrawSystem& input ){}	// コピーコンストラクタを防ぐ
	CDirectDrawSystem	operator=	( CONST CDirectDrawSystem& input ){}	// メンバの代入を防ぐ

public:
	// デストラクタ
	~CDirectDrawSystem	( void ){}

	// 自身のインスタンス取得
	static CDirectDrawSystem*	GetInstance	( void )
	{
		static CDirectDrawSystem drawSystem;
		return &drawSystem;
	}

	BOOL	BeginScene	( void );		// レンダリング開始
	void	EndScene	( void );		// レンダリング終了
	
	//----------------------------------------------------
	// @name	SetFVF
	// @content	頂点の型をセット
	// @param	fvf		頂点の型
	// @return	none
	// @date	2013/7/1
	//----------------------------------------------------
	void	SetFVF		( CONST DWORD fvf )	
	{
		// デバイスのポインタを取得
		LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

		// 頂点の型セット
		pd3dDevice->SetFVF( fvf );
	}

	//----------------------------------------------------
	// @name	Present
	// @content	レンダリング情報をwindowに送信
	// @param	none	
	// @return	none
	// @date	2013/7/1
	//----------------------------------------------------
	void	Present		( void )
	{	
		// デバイスポインタの取得
		CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
	
		// 描画情報送信
		pd3dDevice->Present(NULL,NULL,NULL,NULL);
	}

	//----------------------------------------------------
	// @name	SetFillMode
	// @content	レンダリング状態を変更(WireFrame,Point,Solid)
	// @param	fillMode	変更したいレンダリングモード
	// @return	none
	// @date	2013/7/30
	//----------------------------------------------------
	void	SetFillMode	( CONST D3DFILLMODE fillMode )
	{
		// デバイスポインタの取得
		CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

		// 描画状態の変更
		pd3dDevice->SetRenderState( D3DRS_FILLMODE,fillMode );
	}

	//----------------------------------------------------
	// @name	SetCallMode
	// @content	カリングの状態を変更
	// @param	isCullMode
	// @return	none
	// @date	2013/7/31
	//----------------------------------------------------
	void	SetCallMode	( CONST BOOL isCullMode )
	{
		// デバイスポインタの取得
		CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
		
		if( isCullMode )
			pd3dDevice->SetRenderState( D3DRS_CULLMODE,D3DCULL_CCW );	// カリングＯＮ}
		else
			pd3dDevice->SetRenderState( D3DRS_CULLMODE,D3DCULL_NONE );	// カリングＯＦＦ
	}

public:
	//----------------------------------------------------
	// @name	DrawSpriteRHW
	// @content	スプライトレンダリング(同次座標計算あり)
	// @param	pTexture		テクスチャ	
	// @param	pVertex			頂点情報
	// @return	none	
	// @date	2013/7/3
	// @update	2013/12/13		関数名の変更
	//----------------------------------------------------
	void	DrawSpriteRHW		( CONST LPDIRECT3DTEXTURE9 pTexture, CONST tagTSPRITERHW* pVertex );

	//----------------------------------------------------
	// @name	DrawSpriteRHW
	// @content	スプライトレンダリング(同次座標計算あり)
	// @param	pVertex			頂点情報
	// @return	none
	// @date	2013/7/4
	// @update	2013/12/13		関数名の変更
	//----------------------------------------------------
	void	DrawSpriteRHW		( CONST tagTSPRITERHW* pVertex );
	
	//----------------------------------------------------
	// @name	DrawSprite
	// @content	スプライトレンダリング(同次座標計算なし)
	// @param	pTexture			テクスチャ
	// @param	pVertex				頂点情報
	// @param	pWorldMtx			ワールド行列
	// @return	none	
	// date		2013/12/12
	//----------------------------------------------------
	void	DrawSprite	( CONST LPDIRECT3DTEXTURE9 pTexture,tagTSPRITE* pSpriteVertex, CONST D3DXMATRIX* pWorldMtx );

public:
	//----------------------------------------------------
	// @name	Draw3D
	// @content	3Dモデルレンダリング
	// @param	pModel			モデルデータ
	// @param	pWorldMtx		モデル行列
	// @return	none
	// @date	2013/7/5
	//----------------------------------------------------
	void	Draw3D		(  CResourceXFile* pModel, CONST D3DXMATRIX *pWorldMtx );

	//----------------------------------------------------
	// @name	Draw3D
	// @content	3Dモデルレンダリング( textureの指定 )
	// @param	pModel			モデルデータ
	// @param	pWorldMtx		モデル行列
	// @param	isTexture		テクスチャのありなし
	// @return	none
	// @date	2013/7/6
	//----------------------------------------------------
	void	Draw3D		( CResourceXFile* pModel, CONST D3DXMATRIX *pWorldMtx, BOOL isTexture );

	//----------------------------------------------------
	// @name	Draw3D
	// @content	3Dモデルレンダリング( 色指定 )
	// @param	pModel			モデルデータ
	// @param	pWorldMtx		モデル行列	
	// @param	color			色情報
	// @return	none
	// @date	2013/12/4
	//----------------------------------------------------
	void	Draw3D		( CResourceXFile* pModel, CONST D3DXMATRIX *pWorldMtx, D3DXCOLOR* color );

public:
	//----------------------------------------------------
	// @name	Draw3DClone
	// @content	クローン3Dモデルレンダリング( テクスチャあり )
	// @param	numFaces		面数
	// @param	pTexture		テクスチャ
	// @param	pCloneVertex	クローン頂点
	// @param	pCloneMtx		クローン行列
	// @return	none
	// @date	2013/7/10
	//----------------------------------------------------
	void	Draw3DClone	( UINT numFaces, LPDIRECT3DTEXTURE9 pTexture, tagTORIGINALMESHVERTEX* pCloneVertex, CONST D3DXMATRIX* pCloneMtx );

	//----------------------------------------------------
	// @name	Draw3DClone
	// @content クローン3Dモデルレンダリング( テクスチャなし )
	// @param	numFaces		面数
	// @param	pCloneVertex	クローンの頂点情報
	// @param	pCloneMat		クローンの行列
	// @return	none
	// @date	2013/7/12
	//----------------------------------------------------
	void	Draw3DClone	( UINT numFaces, tagTORIGINALMESHVERTEX* pCloneVertex, CONST D3DXMATRIX* pCloneMtx );

	//----------------------------------------------------
	// @name	DrawShape	
	// @content	形状レンダリング
	// @param	pWorldMtx		ワールド行列
	// @param	pShapeMat		形状マテリアル
	// @aram	pShapeMesh		形状メッシュ
	// @return	none
	// @date	2013/7/15
	//----------------------------------------------------
	void	DrawShape	( CONST D3DXMATRIX* pWorldMtx,CONST D3DMATERIAL9* pShapeMat, CONST LPD3DXMESH pShapeMesh );

public:
	//----------------------------------------------------
	// @name	DrawBillBoard
	// @content	ビルボードレンダリング
	// @param	pTexture		ビルボードのテクスチャ
	// @param	pBillBoardMtx	ビルボードの行列
	// @param	pBillBoardVertexビルボードの頂点情報
	// @return	none
	// @date	2013/7/18
	//----------------------------------------------------
	void DrawBillBoard( CONST LPDIRECT3DTEXTURE9 pTexture, CONST D3DXMATRIX* pBillBoardMtx, CONST tagTBILLBORDVERTEX* pBillBoardVertex );

	//----------------------------------------------------
	// @name	DrawParticle
	// @content	パーティクルレンダリング
	// @param	pTexture		パーティクルのテクスチャ
	// @param	pBillBoardMtx	ビルボードの行列
	// @param	pBillBoardVertexビルボードの頂点情報
	// @return	none
	// @date	2013/7/19
	//----------------------------------------------------
	void DrawParticle	( CONST LPDIRECT3DTEXTURE9 pTexture, CONST D3DXMATRIX* pBillBoardMtx, CONST tagTBILLBORDVERTEX* pBillBoardVertex );

public:
	//----------------------------------------------------
	// @name	DrawDebugStage
	// @content	デバッグステージレンダリング
	// @param	numLines			ライン数
	// @param	pDebugStageVertex	デバッグステージの頂点情報
	// @return	none
	// @date	2013/8/25
	//----------------------------------------------------
	void DrawDebugStage	( CONST UINT numLines, CONST tagTDEBUGVERTEX* pDebugStageVertex );

};

#endif _C_DIRECTX9_DRAW_SYSTEM_H_