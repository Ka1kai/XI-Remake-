
#include "../../KaiFrameWorkHeader/GameMathHeader/CCollision.h"

//----------------------------------------------------
// 球体同士の衝突判定
//----------------------------------------------------
bool CCollision::IsHitCircle ( CONST THITCIRCLE* circle1, CONST THITCIRCLE* circle2 )
{
	if( pow( circle1->boxCenter.x - circle2->boxCenter.x, 2 ) +
		pow( circle1->boxCenter.y - circle2->boxCenter.y ,2 ) +
		pow( circle1->boxCenter.z - circle2->boxCenter.z, 2 ) < 
		pow( circle1->r + circle2->r,2 ) )
	{
 		return true;
	}

	return false;
}

//----------------------------------------------------
// OBB構造体に値セット
//----------------------------------------------------
THITOBB* CCollision::SetOBB( THITOBB* pOutOBB, CONST D3DXVECTOR3* pInLen, CONST D3DXMATRIX* pInMtx )
{
	// 位置座標をセット
	pOutOBB->position.x = pInMtx->_41;
	pOutOBB->position.y = pInMtx->_42;
	pOutOBB->position.z = pInMtx->_43;

	// 方向ベクトルをセット
	pOutOBB->normalDir[0].x = pInMtx->_11;
	pOutOBB->normalDir[0].y = pInMtx->_12;
	pOutOBB->normalDir[0].z = pInMtx->_13;
	pOutOBB->normalDir[1].x = pInMtx->_21;
	pOutOBB->normalDir[1].y = pInMtx->_22;
	pOutOBB->normalDir[1].z = pInMtx->_23;
	pOutOBB->normalDir[2].x = pInMtx->_31;
	pOutOBB->normalDir[2].y = pInMtx->_32;
	pOutOBB->normalDir[2].z = pInMtx->_33;

	// 軸の長さをセット
	pOutOBB->normalLength[0] = pInLen->x / 2;
	pOutOBB->normalLength[1] = pInLen->y / 2;
	pOutOBB->normalLength[2] = pInLen->z / 2;

	return pOutOBB;
}

//----------------------------------------------------
// AABB構造体に値セット
//----------------------------------------------------
THITAABB* CCollision::SetAABB( THITAABB* pOutAABB, CONST D3DXVECTOR3* pInPos, CONST D3DXVECTOR3* pInSize )
{
	// 位置セット
	pOutAABB->centerPos.x = pInPos->x;
	pOutAABB->centerPos.y = pInPos->y;
	pOutAABB->centerPos.z = pInPos->z;

	// サイズセット
	pOutAABB->size.x = pInSize->x;
	pOutAABB->size.y = pInSize->y;
	pOutAABB->size.z = pInSize->z;

	// 半分のサイズセット
	D3DXVECTOR3 halfSize = D3DXVECTOR3( pInSize->x / 2, pInSize->y / 2, pInSize->z / 2 );
	pOutAABB->halfSize.x = halfSize.x;
	pOutAABB->halfSize.y = halfSize.y;
	pOutAABB->halfSize.z = halfSize.z;

	return pOutAABB;
}

//----------------------------------------------------
// メッシュからメッシュデータ抜き出し
//----------------------------------------------------
TMESHDATA* CCollision::GetMeshData( TMESHDATA* pOutMeshData, LPD3DXMESH lpMesh )
{
	HRESULT hr;

	// 頂点座標データ
	float*	x = nullptr;
	float*	y = nullptr;
	float*	z = nullptr;
	float*	pFloat;
	BYTE	*data;
	LPDIRECT3DVERTEXBUFFER9 lpVertexBuff = NULL;
	int numVertex = 0;

	numVertex = lpMesh->GetNumVertices();		// 頂点数取得
	lpMesh->GetVertexBuffer( &lpVertexBuff );	// 頂点バッファオブジェクトへのポインタ取得
		
	// 頂点バッファをロック
	hr = lpVertexBuff->Lock( 0, 0, (void**)&data, D3DLOCK_READONLY );
	if( hr == D3D_OK )
	{	// 頂点数分の座標格納エリア確保
		x = new float[numVertex];
		y = new float[numVertex];
		z = new float[numVertex];
	}

	pFloat = (float*)data;
	for( int i = 0; i < numVertex; ++ i )
	{	// 頂点を取り出す
		x[i] = *pFloat++;
		y[i] = *pFloat++;
		z[i] = *pFloat++;			
	}

	// maxSizeとminSizeを求める
	for( int i = 0; i < numVertex; ++ i )
	{
		if( pOutMeshData->minSize.x >= x[i] )	pOutMeshData->minSize.x = x[i];
		if( pOutMeshData->minSize.y >= y[i] )	pOutMeshData->minSize.y = y[i];
		if( pOutMeshData->minSize.z >= z[i] )	pOutMeshData->minSize.z = z[i];
		if( pOutMeshData->maxSize.x <= x[i] )	pOutMeshData->maxSize.x = x[i];
		if( pOutMeshData->maxSize.y <= y[i] )	pOutMeshData->maxSize.y = y[i];
		if( pOutMeshData->maxSize.z <= z[i] )	pOutMeshData->maxSize.z = z[i];
	}

	// サイズを求める
	D3DXVECTOR3 workMinSize = pOutMeshData->minSize;
	D3DXVECTOR3 workMaxSize = pOutMeshData->maxSize;
	if( pOutMeshData->minSize.x < 0 ) workMinSize.x = pOutMeshData->minSize.x * -1;
	if( pOutMeshData->minSize.y < 0 ) workMinSize.y = pOutMeshData->minSize.y * -1;
	if( pOutMeshData->minSize.z < 0 ) workMinSize.z = pOutMeshData->minSize.z * -1;
	if( pOutMeshData->maxSize.x < 0 ) workMaxSize.x = pOutMeshData->maxSize.x * -1;
	if( pOutMeshData->maxSize.y < 0 ) workMaxSize.y = pOutMeshData->maxSize.y * -1;
	if( pOutMeshData->maxSize.z < 0 ) workMaxSize.z = pOutMeshData->maxSize.z * -1;


	pOutMeshData->size = workMaxSize + workMinSize;

	// 中心座標を求める
	pOutMeshData->center.x = ( pOutMeshData->maxSize.x + pOutMeshData->minSize.x ) / 2;
	pOutMeshData->center.y = ( pOutMeshData->maxSize.y + pOutMeshData->minSize.y ) / 2;
	pOutMeshData->center.z = ( pOutMeshData->maxSize.z + pOutMeshData->minSize.z ) / 2;

	// ２点間の距離を求めて半径を求める
	pOutMeshData->rect = pow( pOutMeshData->maxSize.x - pOutMeshData->center.x, 2 ) + 
						 pow( pOutMeshData->maxSize.y - pOutMeshData->center.y, 2 ) +
						 pow( pOutMeshData->maxSize.z - pOutMeshData->center.z, 2 );
	pOutMeshData->rect = sqrtf( pOutMeshData->rect );

	// 解放処理
	delete[] z;
	delete[] y;
	delete[] x;
		
	// 頂点バッファ解放
	lpVertexBuff->Unlock();
	lpVertexBuff->Release();
	lpVertexBuff = NULL;

	return pOutMeshData;
}

//----------------------------------------------------
// OBBによる衝突判定 
//----------------------------------------------------
bool CCollision::IsHitOBB( CONST THITOBB* obb1, CONST THITOBB* obb2 )
{
	//ベクトルの確保(標準化ベクトル）
	D3DXVECTOR3 NAe1 = obb1->normalDir[0];
	D3DXVECTOR3 NAe2 = obb1->normalDir[1];
	D3DXVECTOR3 NAe3 = obb1->normalDir[2];
	D3DXVECTOR3 NBe1 = obb2->normalDir[0];
	D3DXVECTOR3 NBe2 = obb2->normalDir[1];
	D3DXVECTOR3 NBe3 = obb2->normalDir[2];
	//長さを考慮したベクトル確保
	D3DXVECTOR3 Ae1 = NAe1 * obb1->normalLength[0];
	D3DXVECTOR3 Ae2 = NAe2 * obb1->normalLength[1];
	D3DXVECTOR3 Ae3 = NAe3 * obb1->normalLength[2];
	D3DXVECTOR3 Be1 = NBe1 * obb2->normalLength[0];
	D3DXVECTOR3 Be2 = NBe2 * obb2->normalLength[1];
	D3DXVECTOR3 Be3 = NBe3 * obb2->normalLength[2];	

	D3DXVECTOR3 vInterval = obb1->position - obb2->position;

	// 分離軸：Ae1
	FLOAT rA	= D3DXVec3Length( &Ae1 );
	FLOAT rB	= this->CalcLenSegOnSeparateAxis( &NAe1,&Be1,&Be2,&Be3);
	FLOAT L		= fabs( D3DXVec3Dot( &vInterval,&NAe1 ) );
	if( L > rA + rB )
		return FALSE;

	// 分離軸 : Ae3
   rA = D3DXVec3Length( &Ae3 );
   rB = this->CalcLenSegOnSeparateAxis( &NAe3, &Be1, &Be2, &Be3 );
   L = fabs(D3DXVec3Dot( &vInterval, &NAe3 ));
   if( L > rA + rB )
      return false;

   // 分離軸 : Be1
   rA = this->CalcLenSegOnSeparateAxis( &NBe1, &Ae1, &Ae2, &Ae3 );
   rB = D3DXVec3Length( &Be1 );
   L = fabs(D3DXVec3Dot( &vInterval, &NBe1 ));
   if( L > rA + rB )
      return false;

   // 分離軸 : Be2
   rA = this->CalcLenSegOnSeparateAxis( &NBe2, &Ae1, &Ae2, &Ae3 );
   rB = D3DXVec3Length( &Be2 );
   L = fabs(D3DXVec3Dot( &vInterval, &NBe2 ));
   if( L > rA + rB )
      return false;

   // 分離軸 : Be3
   rA = this->CalcLenSegOnSeparateAxis( &NBe3, &Ae1, &Ae2, &Ae3 );
   rB = D3DXVec3Length( &Be3 );
   L = fabs(D3DXVec3Dot( &vInterval, &NBe3 ));
   if( L > rA + rB )
      return false;

   // 分離軸 : C11
   D3DXVECTOR3 Cross;
   D3DXVec3Cross( &Cross, &NAe1, &NBe1 );
   rA = this->CalcLenSegOnSeparateAxis( &Cross, &Ae2, &Ae3 );
   rB = this->CalcLenSegOnSeparateAxis( &Cross, &Be2, &Be3 );
   L = fabs(D3DXVec3Dot( &vInterval, &Cross ));
   if( L > rA + rB )
      return false;

   // 分離軸 : C12
   D3DXVec3Cross( &Cross, &NAe1, &NBe2 );
   rA = this->CalcLenSegOnSeparateAxis( &Cross, &Ae2, &Ae3 );
   rB = this->CalcLenSegOnSeparateAxis( &Cross, &Be1, &Be3 );
   L = fabs(D3DXVec3Dot( &vInterval, &Cross ));
      if( L > rA + rB )
   return false;

   // 分離軸 : C13
   D3DXVec3Cross( &Cross, &NAe1, &NBe3 );
   rA = this->CalcLenSegOnSeparateAxis( &Cross, &Ae2, &Ae3 );
   rB = this->CalcLenSegOnSeparateAxis( &Cross, &Be1, &Be2 );
   L = fabs(D3DXVec3Dot( &vInterval, &Cross ));
   if( L > rA + rB )
      return false;

   // 分離軸 : C21
   D3DXVec3Cross( &Cross, &NAe2, &NBe1 );
   rA = this->CalcLenSegOnSeparateAxis( &Cross, &Ae1, &Ae3 );
   rB = this->CalcLenSegOnSeparateAxis( &Cross, &Be2, &Be3 );
   L = fabs(D3DXVec3Dot( &vInterval, &Cross ));
   if( L > rA + rB )
      return false;

   // 分離軸 : C22
   D3DXVec3Cross( &Cross, &NAe2, &NBe2 );
   rA = this->CalcLenSegOnSeparateAxis( &Cross, &Ae1, &Ae3 );
   rB = this->CalcLenSegOnSeparateAxis( &Cross, &Be1, &Be3 );
   L = fabs(D3DXVec3Dot( &vInterval, &Cross ));
   if( L > rA + rB )
      return false;

   // 分離軸 : C23
   D3DXVec3Cross( &Cross, &NAe2, &NBe3 );
   rA = this->CalcLenSegOnSeparateAxis( &Cross, &Ae1, &Ae3 );
   rB = this->CalcLenSegOnSeparateAxis( &Cross, &Be1, &Be2 );
   L = fabs(D3DXVec3Dot( &vInterval, &Cross ));
   if( L > rA + rB )
      return false;

   // 分離軸 : C31
   D3DXVec3Cross( &Cross, &NAe3, &NBe1 );
   rA = this->CalcLenSegOnSeparateAxis( &Cross, &Ae1, &Ae2 );
   rB = this->CalcLenSegOnSeparateAxis( &Cross, &Be2, &Be3 );
   L = fabs(D3DXVec3Dot( &vInterval, &Cross ));
   if( L > rA + rB )
      return false;

   // 分離軸 : C32
   D3DXVec3Cross( &Cross, &NAe3, &NBe2 );
   rA = this->CalcLenSegOnSeparateAxis( &Cross, &Ae1, &Ae2 );
   rB = this->CalcLenSegOnSeparateAxis( &Cross, &Be1, &Be3 );
   L = fabs(D3DXVec3Dot( &vInterval, &Cross ));
   if( L > rA + rB )
      return false;

   // 分離軸 : C33
   D3DXVec3Cross( &Cross, &NAe3, &NBe3 );
   rA = this->CalcLenSegOnSeparateAxis( &Cross, &Ae1, &Ae2 );
   rB = this->CalcLenSegOnSeparateAxis( &Cross, &Be1, &Be2 );
   L = fabs(D3DXVec3Dot( &vInterval, &Cross ));
   if( L > rA + rB )
      return false;

   // 分離平面が存在しないので「衝突している」
   return true;
}

//----------------------------------------------------
// AABBによる衝突判定
//----------------------------------------------------
bool CCollision::IsHitAABB( CONST THITAABB* aabb1, CONST THITAABB* aabb2 )
{
	if( aabb1->centerPos.x + aabb1->halfSize.x > aabb2->centerPos.x - aabb2->halfSize.x &&
		aabb1->centerPos.x - aabb1->halfSize.x < aabb2->centerPos.x + aabb2->halfSize.x &&
		aabb1->centerPos.y + aabb1->halfSize.y > aabb2->centerPos.y - aabb2->halfSize.y &&
		aabb1->centerPos.y - aabb1->halfSize.y < aabb2->centerPos.y + aabb2->halfSize.y &&
		aabb1->centerPos.z + aabb1->halfSize.z > aabb2->centerPos.z - aabb2->halfSize.z &&
		aabb1->centerPos.z - aabb1->halfSize.z < aabb2->centerPos.z + aabb2->halfSize.z )
	{
		// 当たっている
		return true;
	}

	return false;
}

//----------------------------------------------------
// 分離軸に投影された軸成分から投影線分長を算出
//----------------------------------------------------
float CCollision::CalcLenSegOnSeparateAxis( D3DXVECTOR3 *pSepAxis, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3)
{
   // 3つの内積の絶対値の和で投影線分長を計算
   // 分離軸pSepAxisは標準化されていること
   FLOAT r1 = fabs( D3DXVec3Dot( pSepAxis, e1 ) );
   FLOAT r2 = fabs( D3DXVec3Dot( pSepAxis, e2 ) );
   FLOAT r3 = e3 ? ( fabs( D3DXVec3Dot( pSepAxis, e3 ) ) ) : 0;
   return r1 + r2 + r3;
}

//----------------------------------------------------
// 平面の方程式を算出
//----------------------------------------------------
TPLANE* CCollision::CreatePlaneInfo( TPLANE* pOutPlane, CONST D3DXVECTOR3 *v1, CONST D3DXVECTOR3 *v2, CONST D3DXVECTOR3 *v3 )
{
	D3DXVECTOR3	v1v2;		// v1とv2を結ぶベクトル
	D3DXVECTOR3 v1v3;		// v1とv3を結ぶベクトル
	D3DXVECTOR3 normal;		// 法線ベクトル

	//ベクトルを算出
	D3DXVec3Subtract( &v1v2, v2, v1 );	// v1とv2を結ぶベクトル
	D3DXVec3Subtract( &v1v3, v3, v1 );	// v1とv3を結ぶベクトル
	
	D3DXVec3Cross( &normal, &v1v2, &v1v3 );	// 外積を求める
	// 平面の方程式決定
	pOutPlane->a = normal.x;
	pOutPlane->b = normal.y;
	pOutPlane->c = normal.z;
	
	// 平面方程式dを計算
	pOutPlane->d = -( pOutPlane->a * v1->x + pOutPlane->b * v1->y + pOutPlane->c * v1->z );

	return pOutPlane;
}

//----------------------------------------------------- 
// 直線と平面の交点を求める
//-----------------------------------------------------
bool CCollision::LineToPlaneCross( D3DXVECTOR3* pOutCross, CONST TPLANE* plane, CONST D3DXVECTOR3* vTriPos, CONST D3DXVECTOR3* vStartPos, D3DXVECTOR3* vDir )
{
	D3DXVECTOR3	v1v2;	// 3角形の一つの頂点と直線が通る点を結ぶベクトル
	D3DXVECTOR3 vNormal; // 法線ベクトル	
	FLOAT		t;

	// 平面の方程式から法線ベクトルを抜き取る
	vNormal.x = plane->a;
	vNormal.y = plane->b;
	vNormal.z = plane->c;

	//3角形の一つの頂点と始点を結ぶベクトルを算出
	D3DXVec3Subtract( vDir, vTriPos, vStartPos );

	//内積算出
	FLOAT dot = D3DXVec3Dot( vDir, &vNormal );

	// 内積の結果が０になっているかを判定
	if(( 0.0f - FLT_EPSILON < dot ) && ( dot < 0.0f + FLT_EPSILON ))
	{
		return FALSE;
	}

	t = D3DXVec3Dot( &vNormal, &v1v2 ) / D3DXVec3Dot( vDir,&vNormal );

	pOutCross->x = vStartPos->x + vDir->x * t;
	pOutCross->y = vStartPos->y + vDir->y * t;
	pOutCross->z = vStartPos->z + vDir->z * t;

	return TRUE;
}

//----------------------------------------------------
// ３角形の内部にあるかどうかを判定
//----------------------------------------------------
bool CCollision::CheckInTriangle( CONST D3DXVECTOR3* v1, CONST D3DXVECTOR3* v2, CONST D3DXVECTOR3* v3, CONST D3DXVECTOR3* pos )
{
	D3DXVECTOR3	v1v2,v2v3,v3v1,v1v3;	// 3辺のベクトル
	D3DXVECTOR3 ap,bp,cp;				// 内部の点とのベクトル
	D3DXVECTOR3 vNormal;				// 3角形の法線ベクトル
	D3DXVECTOR3 n1,n2,n3;				// 3辺と内部の点との法線ベクトル

	D3DXVec3Subtract( &v1v2, v2, v1 );
	D3DXVec3Subtract( &v2v3, v3, v2 );
	D3DXVec3Subtract( &v3v1, v1, v3 );
	D3DXVec3Subtract( &v1v3, v3, v1 );

	D3DXVec3Subtract( &ap, pos, v1 );
	D3DXVec3Subtract( &bp, pos, v2 );
	D3DXVec3Subtract( &cp, pos, v3 );

	D3DXVec3Cross( &vNormal, &v1v2, &v1v3 );

	D3DXVec3Cross( &n1, &v1v2, &ap );
	D3DXVec3Cross( &n2, &v2v3, &bp );
	D3DXVec3Cross( &n3, &v3v1, &cp );

	if( D3DXVec3Dot( &n1, &vNormal ) < 0.0f ) 
		return FALSE;

	if( D3DXVec3Dot( &n2, &vNormal ) < 0.0f )
		return FALSE;

	if( D3DXVec3Dot( &n3, &vNormal ) < 0.0f ) 
		return FALSE;

	return TRUE;
}

//----------------------------------------------------
// 平面との距離を求める
//----------------------------------------------------
float CCollision::LengthPointToPlane( D3DXVECTOR3* pOutCrossPos, CONST D3DXVECTOR3* vStartPos, CONST TPLANE* plane )
{
	//交点を求める
	FLOAT cross1 = -( plane->a * vStartPos->x + plane->b * vStartPos->y + plane->c * vStartPos->z + plane->d );
	FLOAT cross2 = ( plane->a * plane->a + plane->b*plane->b + plane->c * plane->c );
	FLOAT t = cross1 / cross2;

	pOutCrossPos->x = plane->a * t + vStartPos->x;
	pOutCrossPos->y = plane->b * t + vStartPos->y;
	pOutCrossPos->z = plane->c * t + vStartPos->z;

	//点と平面の距離を求める
	float p1 = abs( plane->a * vStartPos->x + plane->b * vStartPos->y + plane->c * vStartPos->z + plane->d );
	float p2 = sqrtf( plane->a * plane->a + plane->b * plane->b + plane->c * plane->c );

	return ( p1 / p2 );

}
