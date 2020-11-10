//----------------------------------------------------
// CColision Header
//	当たり判定をまとめたヘッダー
//
// @date	2013/6/15
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_COLISION_H_
#define _C_COLISION_H_

#include <d3dx9.h>
#include <math.h>

//----------------------------------------------------
// バウンディングスフィア構造体定義
//----------------------------------------------------
typedef	struct tagTHITCIRCLE
{
	D3DXVECTOR3 boxCenter;	// バウンディングスフィア中心座標
	float		r;			// バウンディングスフィア半径
}THITCIRCLE;

//----------------------------------------------------
// メッシュデータ構造体定義
//----------------------------------------------------
typedef struct tagTMESHDATA
{
	D3DXVECTOR3	center;
	D3DXVECTOR3 size;
	D3DXVECTOR3 maxSize;
	D3DXVECTOR3 minSize;
	float		rect;
}TMESHDATA;

//----------------------------------------------------
// AABB当たり判定用構造体定義
//----------------------------------------------------
typedef struct tagTHITAABB
{
	D3DXVECTOR3 centerPos;	// AABBの中心座標
	D3DXVECTOR3 size;		// AABBのサイズ
	D3DXVECTOR3 halfSize;	// AABBの半分のサイズ
}THITAABB;

//----------------------------------------------------
// OBB用構造体定義
//----------------------------------------------------
typedef struct tagTHITOBB
{
	D3DXVECTOR3	position;			// 位置情報
	D3DXVECTOR3	normalDir[3];		// 各方向情報
	FLOAT		normalLength[3];	// 各軸の長さ
}THITOBB;

//----------------------------------------------------
// 平面方程式が持つ４つの係数
//----------------------------------------------------
typedef struct tagPLANE
{
	FLOAT a,b,c,d;		
}TPLANE;


class CCollision
{
private:
	CCollision		( void ){}								// コンストラクタを防ぐ
	CCollision		( CONST CCollision& colObj ){}			// コピーコンストラクタを防ぐ
	CCollision	operator= ( CONST CCollision& colObj ){}	// メンバの代入を防ぐ

public:
	
	// 唯一のインスタンスの取得
	static CCollision* GetInstance	( void )
	{
		static CCollision pDirectCollision;
		return &pDirectCollision;
	}

	// デストラクタ
	~CCollision	(void){}

	/*
//====================================================
// 自身(矩形)と点の当たり判定
//====================================================

bool CDirectGraphics2D::HitPoint2Rect(float x, float y)
{
	if((ver[0].pos.x+objData.centerX < x && ver[1].pos.x+objData.centerX > x) &&
		(ver[0].pos.y+objData.centerY < y && ver[2].pos.y+objData.centerY > y))
		return true;

	return false;
}

//====================================================
// 自身(円)と点の当たり判定
//====================================================
bool CDirectGraphics2D::HitPoint2Circle(float x, float y, float r)
{
	double	workX, workY;

	workX = pow((x - objData.centerX), 2);
	workY = pow((y - objData.centerY), 2);

	if((workX+workY) <= pow(r, 2))
		return true;

	return false;
}

*/

	//----------------------------------------------------
	// @name	IsHitCircle
	// @content 球体同士の衝突判定
	// @param	circle1		球体1
	// @param	circle2		球体2
	// @return	球体同士衝突しているかどうか
	// @date	2013/9/10
	//----------------------------------------------------
	bool	IsHitCircle		( CONST THITCIRCLE* circle1, CONST THITCIRCLE* circle2 );

	//----------------------------------------------------
	// @name	IsHitAABB
	// @content	AABB同士の当たり判定
	// @param	aabb1		AABB1
	// @param	aabb2		AABB2
	// @return	AABB同士衝突しているかどうか
	// @date	2014/1/15
	//----------------------------------------------------
	bool	IsHitAABB		( CONST THITAABB* aabb1, CONST THITAABB* aabb2 );

	//----------------------------------------------------
	// @name	IsHitOBB
	// @content	OBBによる衝突判定
	// @param	obb1	OBB1
	// @param	obb2	OBB2
	// @return	OBB同士衝突しているかどうか
	// @date	2013/9/10
	//----------------------------------------------------
	bool	IsHitOBB		( CONST THITOBB* obb1,CONST THITOBB* obb2 );

public:
	//----------------------------------------------------
	// @name	SetOBB
	// @content	OBB構造体にセット
	// @param	pOutOBB*	セットするOBB構造体のポインタ
	// @param	pInLen		各軸の長さ
	// @param	PInMtx		モデル行列
	// @return	THITOBB		当たり判定に使うOBB構造体
	// @date	2013/9/10
	//----------------------------------------------------
	THITOBB*	SetOBB			( THITOBB* pOutOBB, CONST D3DXVECTOR3* pInLen, CONST D3DXMATRIX* pInMtx );  
	
	//----------------------------------------------------
	// @name	SetAABB
	// @content	AABB構造体にセット
	// @param	pOutAABB*		セットしたいAABB構造体ポインタ
	// @param	pInPos			セットしたい中心座標
	// @param	pInSize			セットしたいAABBのサイズ
	// @return	THITAABB*		セットしたAABB構造体ポインタ
	// @date	2014/1/15
	//----------------------------------------------------
	THITAABB*	SetAABB			( THITAABB* pOutAABB, CONST D3DXVECTOR3* pInPos, CONST D3DXVECTOR3* pInSize );

	//----------------------------------------------------
	// @name	GetMeshData
	// @content	メッシュからメッシュデータを抜き出し
	// @param	pOutMeshData	抜き出したいメッシュデータ構造体ポインタ
	// @param	mesh			抜き出したいメッシュ
	// @return	TMESHDATA*		抜き出したメッシュデータ
	// @date	2014/1/15
	//----------------------------------------------------
	TMESHDATA* GetMeshData	( TMESHDATA* pOutMeshData, LPD3DXMESH lpMesh );

	//----------------------------------------------------
	// @name	CalcLenSegOnSeparateAxis
	// @content	分離軸に投影された軸成分から投影線分長を算出
	// @param	pSepAis	分離軸
	// @param	e1		軸成分1
	// @param	e2		軸成分2
	// @param	e3		軸成分3
	// @return	投影された線分の長さ
	// @date	2013/9/10
	//-----------------------------------------------------
	float CalcLenSegOnSeparateAxis( D3DXVECTOR3 *pSepAxis, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = nullptr );
	
	//----------------------------------------------------
	// @name	CreatePlaneInfo
	// @content	平面方程式を求める
	// @param	pOutPlane	求めた平面方程式
	// @param	v1			3角形の頂点座標
	// @param	v2			3角形の頂点座標
	// @param	v3			3角形の頂点座標
	// @return	求めた平面方程式
	// @date	2013/9/10
	//----------------------------------------------------
	TPLANE* CreatePlaneInfo( TPLANE* pOutPlane, CONST D3DXVECTOR3* v1, CONST D3DXVECTOR3* v2, CONST D3DXVECTOR3* v3 );

	//----------------------------------------------------
	// @name	LineToPlaneCross
	// @content	直線と平面の交点を求める
	// @param	pOutCross	求めた交点座標
	// @param	plane		平面方程式
	// @param	vTriPos		3角形のどれか一つの頂点座標
	// @param	vStartPos	直線が通る点(座標)
	// @param	vDir		直線と平行なベクトル
	// @return	交点を求めることが出来たか
	// @date	2013/9/10
	//----------------------------------------------------
	bool LineToPlaneCross( D3DXVECTOR3* pOutCross, CONST TPLANE* plane, CONST D3DXVECTOR3* vTriPos, CONST D3DXVECTOR3* vStartPos, D3DXVECTOR3* vDir );	

	//----------------------------------------------------
	// name		CheckInTriangle
	// @content	3角形の内部にあるかどうかを判定
	// @param	v1		頂点座標1
	// @param	v2		頂点座標2
	// @param	v3		頂点座標3
	// @param	pos		判定したい座標
	// @return	3角形の内部にあるかどうか
	// @date	2013/9/10
	//----------------------------------------------------
	bool CheckInTriangle( CONST D3DXVECTOR3* v1, CONST D3DXVECTOR3* v2,	CONST D3DXVECTOR3* v3, CONST D3DXVECTOR3* pos );

	//----------------------------------------------------
	// @name	LengthPontToPlane
	// @content	平面との距離を求める
	// @param	pOutCrossPos	出力する交点座標
	// @param	vStartPos		視点となる座標
	// @param	plane			平面方程式
	// @return	平面と始点の距離
	// @date	2013/9/10
	//----------------------------------------------------
	float LengthPointToPlane( D3DXVECTOR3* pOutCrossPos, CONST D3DXVECTOR3* vStartPos, CONST TPLANE* plane );
};

#endif _C_COLISION_H_