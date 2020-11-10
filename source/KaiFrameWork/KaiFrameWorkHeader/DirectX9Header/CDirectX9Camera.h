//----------------------------------------------------
// CDirectX9Camera 
//	DirectXのカメラを制御する
//
// @date	2013/6/2
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_DIRECTX9_CAMERA_H_
#define _C_DIRECTX9_CAMERA_H_

#include <d3dx9.h>

#include "../../KaiFrameWorkHeader/DirectX9Header/CDirectX9FrameWork.h"

class CDirectCamera
{
private:
	D3DXMATRIX	m_view;			// ビュー行列
	D3DXMATRIX	m_projection;	// 射影行列
	D3DXMATRIX	m_ortho;		// 正射影行列

	D3DXMATRIX	m_worldMtx;		// カメラのワールド行列

	D3DXVECTOR3 m_vEye;			// カメラの位置
	D3DXVECTOR3 m_vAt;			// カメラの注視点
	D3DXVECTOR3 m_vUp;			// カメラの向き
public:
	D3DXMATRIX*		GetView	( void )
	{
		return &m_view;
	}
	D3DXVECTOR3*	GetEye	( void )
	{
		return &m_vEye;
	}
	D3DXVECTOR3*	GetAt	( void )
	{
		return &m_vAt;
	}

public:
	CDirectCamera			( void );	
	~CDirectCamera			( void );

public:
	//----------------------------------------------------
	// @name	Init
	// @content	カメラの初期化
	// @param	windowSizeX		画面のXサイズ
	// @param	windowSizeY		画面のYサイズ
	// @return	bool			成功か失敗
	// @date	2013/6/3
	// @update	2013/11/18
	//----------------------------------------------------
	bool	Init			( CONST int windowSizeX, CONST int windowSizeY );	

	//----------------------------------------------------
	// @name	Init
	// @content	カメラの初期化(位置・注視点・方向)
	// @param	none
	// @return	bool			成功か失敗
	// @date	2013/6/4
	// @update	2013/11/18
	//----------------------------------------------------
	bool	Init			( void );

	//----------------------------------------------------
	// @name	Set
	// @content	カメラをセット
	// @param	none
	// @return	bool		成功か失敗
	// @date	2013/6/3
	// @update	2013/11/18
	//----------------------------------------------------
	bool	Set				( void );

	//----------------------------------------------------
	// @name	SetPosition
	// @content	カメラの位置セット
	// @param	xPos		セットしたいX座標	
	// @param	yPos		セットしたいY座標
	// @param	zPos		セットしたいZ座標
	// @return	bool		成功か失敗
	// @date	2013/6/4
	// @update	2013/11/18
	//----------------------------------------------------
	bool	SetPosition		( CONST float xPos, CONST float yPos, CONST float zPos );	

	//----------------------------------------------------
	// @name	SetAt
	// @content	カメラの注視点のセット
	// @param	xPos		セットしたいX座標
	// @param	yPos		セットしたいY座標
	// @param	zPos		セットしたいZ座標
	// @return	bool		成功か失敗
	// @date	2013/6/5
	// @update	2013/11/18
	//----------------------------------------------------
	bool	SetAt			( CONST float xPos, CONST float yPos, CONST float zPos );		

	//----------------------------------------------------
	// @name	SetView
	// @content	カメラのワールド行列のセット
	// @param	none
	// @return	BOOL		成功か失敗
	// @date	2013/6/6
	// @update	2013/11/18
	//----------------------------------------------------
	bool	SetView			( void );

	//----------------------------------------------------
	// @name	SetPerspective
	// @content	描画を透視投影変換に設定
	// @param	none
	// @return	none
	// @date	2013/6/7
	//----------------------------------------------------
	void	SetPerspective	( void )
	{
		LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
		pd3dDevice->SetTransform(D3DTS_PROJECTION,&m_projection);
	}

	//----------------------------------------------------
	// @name	SetOrtho
	// @content	正射影変換にセ設定
	// @param	none
	// @return	none
	// @date	2013/6/7
	//----------------------------------------------------
	void	SetOrtho		( void )
	{
		LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
		pd3dDevice->SetTransform(D3DTS_PROJECTION, &m_ortho);
	}

	//----------------------------------------------------
	// @name	Tracking
	// @content	追従カメラ(ベクトルを考慮しない)
	// @param	pMtx			主観したいモデルのワールド座標	
	// @param	at				モデルからの距離
	// @return	none
	// @date	2013/6/10
	// @update	2013/11/18		
	//----------------------------------------------------
	void	Tracking		( CONST D3DXMATRIX* pMtx, CONST float at );		
	
	//----------------------------------------------------
	// @name	Tracking
	// @content	追従させたいモデルのベクトルを利用しての追従カメラ
	// @param	pMtx			主観したいモデルのワールド座標
	// @param	pVec			主観したいモデルのベクトル
	// @param	distance		モデルからのカメラの距離
	// @return	none
	// @date	2013/6/12
	// @update	2013/11/18
	//----------------------------------------------------
	void	Tracking		( CONST D3DXMATRIX* pMtx, CONST D3DXVECTOR3* pVec, CONST float distance );

public:
	//----------------------------------------------------
	// @name	SetBillBoardMat
	// @content	行列をビルボード用行列に変換
	// @return	D3DXMATRIX*		変更した行列	
	// @param	pBillBoardPos	ビルボードの位置
	// @param	pBillBoardMat	変換したい行列
	// @date	2013/6/20
	// @update	2013/11/18		変換した行列を返す
	//----------------------------------------------------
	D3DXMATRIX* SetBillBoardMtx	( D3DXMATRIX* pBillBoardMtx, CONST D3DXVECTOR3* pBillBoardPos );
	
	//----------------------------------------------------
	// @name	SetBillBoardMat
	// @content	行列をビルボード用行列に変換
	// @param	pBillBoardMat	変換したい行列
	// @param	distance		カメラからの距離
	// @return	D3DXMATRIX*		変換した行列
	// @date	2013/6/21
	// @update	2013/11/18		変換した行列を返す
	//----------------------------------------------------
	D3DXMATRIX*	SetBillBoardMtx	( D3DXMATRIX* pBillBoardMtx, CONST float distance ); 

private:
	//----------------------------------------------------
	// @name	CalcQuaternion
	// @content	クォータニオンの計算
	// @param	pAxis			回転方向ベクトル
	// @param	degree			回転角度
	// @return	bool			成功か失敗
	// @date	2013/11/18
	//----------------------------------------------------
	bool	CalcLocalQuaternion		( CONST D3DXVECTOR3* pAxis, CONST float degree );

public:
	void	LocalRotationQuaterX( CONST float degree );		// ローカルクォータニオンX回転
	void	LocalRotationQuaterY( CONST float degree );		// ローカルクォータニオンY回転
	void	LocalRotationQuaterZ( CONST float degree );		// ローカルクォータニオンZ回転

	//----------------------------------------------------
	// @name	LocalRotationQuater
	// @content	ローカル任意軸クォータニオン回転
	// @param	pVec			任意の軸
	// @param	degree			回転角度
	// @return	none
	// @date	2013/7/30
	// @update	2013/11/18
	//----------------------------------------------------
	void	LocalRotationQuater( CONST D3DXVECTOR3* pVec, CONST float degree );

};

#endif _C_DIRECTX9_CAMERA_H_