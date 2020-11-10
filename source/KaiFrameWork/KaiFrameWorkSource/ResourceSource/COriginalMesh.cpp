
#include "../../KaiFrameWorkHeader/ResourceHeader/COriginalMesh.h"
/*
//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
COriginalMesh::COriginalMesh()
{
	m_cloneData.connect = NULL;
	m_cloneData.vertex = NULL;
	m_cloneData.numVertex = 0;
	m_cloneData.numFaces = 0;
}

//----------------------------------------------------
// メッシュからバウンディングスフィア用の構造体データ取得
//----------------------------------------------------
void CMeshClone::Init( LPD3DXMESH lpMesh, COLISION_DATA* colData)
{
	// シングルトンでデバイスへのポインタを取得
	const   LPDIRECT3DDEVICE9 pd3dDevice = CDirectBase::Getpd3dDevice();

	HRESULT hr;
	// 頂点座標データ
	float*	x;
	float*	y;
	float*	z;
	float*	pFloat;
	BYTE	*data;

	cloneConnect = NULL;
	cloneVertex = NULL;
	pTriangle = NULL;

	// 当たり判定用データ作成のためにクローンメッシュ作成
	hr = lpMesh->CloneMeshFVF( D3DXMESH_MANAGED,(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 ),pd3dDevice,&cloneMesh);
	if( FAILED(hr) )
	{	// 作成できなかった場合エラーを表示　処理は続行
		MessageBox(0,"Colon Not Create...","error",MB_OK);
	}
	else
	{
		numVertex = cloneMesh->GetNumVertices();		// 頂点数取得
		cloneMesh->GetVertexBuffer( &lpVertexBuff );	// 頂点バッファオブジェクトへのポインタ取得
		
		// 頂点バッファをロック
		hr = lpVertexBuff->Lock(0,0,(void**)&data,D3DLOCK_READONLY);
		if( hr == D3D_OK )
		{	// 頂点数分の座標格納エリア確保
			x = new float[numVertex];
			y = new float[numVertex];
			z = new float[numVertex];
		}

		pFloat = (float *)data;
		for( int i = 0; i < numVertex; ++ i )
		{	// 頂点を取り出す
			x[i] = *pFloat++;
			y[i] = *pFloat++;
			z[i] = *pFloat++;			
		}

		// maxとminを求める
		for( int i = 0; i < numVertex; ++ i )
		{
			if( colData->minX >= x[i] )	colData->minX = x[i];
			if( colData->minY >= y[i] )	colData->minY = y[i];
			if( colData->minZ >= z[i] )	colData->minZ = z[i];
			if( colData->maxX <= x[i] )	colData->maxX = x[i];
			if( colData->maxY <= y[i] )	colData->maxY = y[i];
			if( colData->maxZ <= z[i] )	colData->maxZ = z[i];
		}

		// 球の中心座標を求める
		colData->cenX = ( colData->maxX + colData->minX ) / 2;
		colData->cenY = ( colData->maxY + colData->minY ) / 2;
		colData->cenZ = ( colData->maxZ + colData->minZ ) / 2;

		// ２点間の距離を求めて半径を求める
		colData->r = pow( colData->maxX - colData->cenX,2 ) + pow( colData->maxY - colData->cenY,2 ) + pow( colData->maxZ - colData->cenZ,2 );
		colData->r = sqrtf( colData->r );
		// ---- データ取得終了 ---- //

	delete[] z;
	delete[] y;
	delete[] x;
		
	// 頂点バッファ解放
	lpVertexBuff->Unlock();
	// 解放
	cloneMesh->Release();
	cloneMesh = NULL;
	}
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
COriginalMesh::~COriginalMesh(void)
{
	SAFE_DELETE_ALLAY( m_cloneData.connect );	// 結線情報削除
	SAFE_DELETE_ALLAY( m_cloneData.vertex );	// 頂点情報削除	
	SAFE_DELETE_ALLAY( pTriangle );		// 三角形情報削除する
}

/*
void COriginalMesh::TraiangleTransform(D3DXMATRIX mat)
{
	TCLONETRIANGLEVERTEX* TransformWork;	// ワールド座標系に変換するためのワーク
	D3DXVECTOR3 temp;

	int idx0,idx1,idx2;
	D3DXVECTOR3 normal;
	D3DXVECTOR3 p0p1;
	D3DXVECTOR3 p0p2;

	// 生成された三角形情報があれば削除する
	if( pTriangle != NULL )
	{
		delete[] pTriangle;
		pTriangle = NULL;
	}

	// 座標変換用ワークを頂点数分生成する
	TransformWork = new TCLONETRIANGLEVERTEX[numVertex];

	// 頂点をすべて取り出しワールド座標変換用ワークにセット
	for( UINT i = 0; i < numVertex; i ++ )
	{
		// ローカル座標を座標変換用ワークにセット
		TransformWork[i] = cloneVertex[i];

		temp.x = cloneVertex[i].pos.x;
		temp.y = cloneVertex[i].pos.y;
		temp.z = cloneVertex[i].pos.z;

		// 座標変換
		D3DXVec3TransformCoord(&temp,&temp,&mat);

		// 座標値のみワールド座標で書き換え
		TransformWork[i].pos.x = temp.x;
		TransformWork[i].pos.y = temp.y;
		TransformWork[i].pos.z = temp.z;
	}

	pTriangle = new MyTriangle[numFaces];	// 三角形の面数分オブジェクト生成

	// 三角形ポリゴン数分ループ
	for( UINT i = 0; i < numFaces; i ++ )
	{
		idx0 = cloneConnect[i].idx[0];
		idx1 = cloneConnect[i].idx[1];
		idx2 = cloneConnect[i].idx[2];


		pTriangle[i].vertex[0] = TransformWork[idx0];
		pTriangle[i].vertex[1] = TransformWork[idx1];
		pTriangle[i].vertex[2] = TransformWork[idx2];
		
		pTriangle[i].vertex[0].diffuse = D3DCOLOR_ARGB(255,255,255,255);
		pTriangle[i].vertex[1].diffuse = D3DCOLOR_ARGB(255,255,255,255);
		pTriangle[i].vertex[2].diffuse = D3DCOLOR_ARGB(255,255,255,255);
		
		p0p1.x = pTriangle[i].vertex[1].pos.x - pTriangle[i].vertex[0].pos.x;
		p0p1.y = pTriangle[i].vertex[1].pos.y - pTriangle[i].vertex[0].pos.y;
		p0p1.z = pTriangle[i].vertex[1].pos.z - pTriangle[i].vertex[0].pos.z;

		p0p2.x = pTriangle[i].vertex[2].pos.x - pTriangle[i].vertex[0].pos.x;
		p0p2.y = pTriangle[i].vertex[2].pos.y - pTriangle[i].vertex[0].pos.y;
		p0p2.z = pTriangle[i].vertex[2].pos.z - pTriangle[i].vertex[0].pos.z;		
	
		// 法線情報計算
		D3DXVec3Cross( &normal,&p0p1,&p0p2 );
		D3DXVec3Normalize( &normal,&normal );
		pTriangle[i].normal.x = normal.x;
		pTriangle[i].normal.y = normal.y;
		pTriangle[i].normal.z = normal.z;

		// 重心計算
		pTriangle[i].center.x = (pTriangle[i].vertex[0].pos.x + pTriangle[i].vertex[1].pos.x + pTriangle[i].vertex[2].pos.x)/3;
		pTriangle[i].center.y = (pTriangle[i].vertex[0].pos.y + pTriangle[i].vertex[1].pos.y + pTriangle[i].vertex[2].pos.y)/3;
		pTriangle[i].center.z = (pTriangle[i].vertex[0].pos.z + pTriangle[i].vertex[1].pos.z + pTriangle[i].vertex[2].pos.z)/3;

		// 現在の重心座標を保存しておく
		pTriangle[i].m_vLogPos.x = pTriangle[i].center.x;
		pTriangle[i].m_vLogPos.y = pTriangle[i].center.y;
		pTriangle[i].m_vLogPos.z = pTriangle[i].center.z;
	
		
		// 頂点座標を原点を基準とした座標に変換する
		for( int j = 0; j < VERTEX_NUM; j ++ )
		{
			pTriangle[i].vertex[j].pos.x -= pTriangle[i].center.x;
			pTriangle[i].vertex[j].pos.y -= pTriangle[i].center.y;
			pTriangle[i].vertex[j].pos.z -= pTriangle[i].center.z;
		}
		
		D3DXMatrixIdentity(&pTriangle[i].mat);

		pTriangle[i].m_vLife = 255;
		pTriangle[i].isExist = true;

	}
	delete[] TransformWork;
	TransformWork = NULL;
	return;
}
*/
	/*
void COriginalMesh::LocalToWorld( D3DXMATRIX mat )
{
	TCLONETRIANGLEVERTEX* TransformWork;	// ワールド座標系に変換するためのワーク
	D3DXVECTOR3 temp;

	int idx0,idx1,idx2;

	// 生成された三角形情報があれば削除する
	if( pTriangle != NULL )
	{
		delete[] pTriangle;
		pTriangle = NULL;
	}

	// 座標変換用ワークを頂点数分生成する
	TransformWork = new TCLONETRIANGLEVERTEX[numVertex];

	// 頂点をすべて取り出しワールド座標変換用ワークにセット
	for( UINT i = 0; i < numVertex; i ++ )
	{
		// ローカル座標を座標変換用ワークにセット
		TransformWork[i] = cloneVertex[i];

		temp.x = cloneVertex[i].pos.x;
		temp.y = cloneVertex[i].pos.y;
		temp.z = cloneVertex[i].pos.z;

		// 座標変換
		D3DXVec3TransformCoord(&temp,&temp,&mat);

		// 座標値のみワールド座標で書き換え
		TransformWork[i].pos.x = temp.x;
		TransformWork[i].pos.y = temp.y;
		TransformWork[i].pos.z = temp.z;
	}

	pTriangle = new MyTriangle[numFaces];	// 三角形の面数分オブジェクト生成

	// 三角形ポリゴン数分ループ
	for( UINT i = 0; i < numFaces; i ++ )
	{
		idx0 = cloneConnect[i].idx[0];
		idx1 = cloneConnect[i].idx[1];
		idx2 = cloneConnect[i].idx[2];

		pTriangle[i].vertex[0] = TransformWork[idx0];
		pTriangle[i].vertex[1] = TransformWork[idx1];
		pTriangle[i].vertex[2] = TransformWork[idx2];
	}

	delete[] TransformWork;
	TransformWork = NULL;
}
*/
/*
//----------------------------------------------------
// オリジナルメッシュの作成
//----------------------------------------------------
tagTORIGINALMESH* COriginalMesh::CreateOriginalMesh	( tagTORIGINALMESH* cloneData, CONST LPSTR filePath )
{
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	HRESULT			hr;
	LPD3DXMESH		pMesh;
	LPD3DXMESH		pCloneMesh;
	LPD3DXBUFFER	pMaterialsBuffer;
	LPDIRECT3DVERTEXBUFFER9 pVertexBuff;	// 頂点バッファ
	LPDIRECT3DINDEXBUFFER9	pIndexBuff;
	DWORD	materialsCount;
	
	//Xファイル読み込み
	hr = D3DXLoadMeshFromX(
		filePath,
		D3DXMESH_MANAGED,
		pd3dDevice,
		nullptr,
		&pMaterialsBuffer,
		nullptr,
		&materialsCount,
		&pMesh);
	if( FAILED( hr ) )
	{   // 読み込み失敗時
		return nullptr;
	}

	//クローンメッシュ
	hr = pMesh->CloneMeshFVF( D3DXMESH_MANAGED, CLONE_FVF, pd3dDevice, &pCloneMesh );
	if( FAILED( hr ) )
	{   // 生成失敗
		MessageBox( 0,"Colon Not Create...","error",MB_OK );
		return nullptr;
	}

	// 頂点数を取得
	cloneData->numVertex = pCloneMesh->GetNumVertices();
	pCloneMesh->GetVertexBuffer( &pVertexBuff );

	// 面数を取得
	cloneData->numFaces = pCloneMesh->GetNumFaces();			
	pCloneMesh->GetIndexBuffer( &pIndexBuff );

	BYTE* pVertexData;

	// 頂点バッファをロック
	hr = pVertexBuff->Lock( 0,sizeof( tagTORIGINALMESHVERTEX ),( void** )&pVertexData,D3DLOCK_READONLY );
	if( FAILED( hr ) )
	{   // 頂点バッファロック失敗		
		MessageBox( 0,"VertexBuff Not Lock...","error",MB_OK );
		return nullptr;
	}

	cloneData->vertex = new tagTORIGINALMESHVERTEX[cloneData->numVertex];	// 頂点数分確保
	memcpy( cloneData->vertex,pVertexData,sizeof( tagTORIGINALMESHVERTEX )*( cloneData->numVertex ));	// 頂点情報をコピー

	// 頂点バッファ解放
	pVertexBuff->Unlock();

	// インデックスバッファをロック
	hr = pIndexBuff->Lock(0, sizeof( tagTORIGINALMESHVERTEX ),(void**)&pIndexBuff,D3DLOCK_READONLY);
	if( FAILED( hr ) )
	{   // インデックスバッファロック失敗
		MessageBox( 0,"IndexBuff Not Lock...","error",MB_OK );
		return FALSE;
	}	
	
	cloneData->connect = new MyConnect[cloneData->numFaces];	// 面数分の結線情報を取得

	WORD*	pIndex = nullptr;		// インデックスバッファ

	// 3角形ポリゴン数分ループ
	for( UINT i = 0; i < cloneData->numFaces; ++ i )
	{
		cloneData->connect[i].idx[0] = *pIndex ++;
		cloneData->connect[i].idx[1] = *pIndex ++;
		cloneData->connect[i].idx[2] = *pIndex ++;
	}
	// インデックスバッファ解放
	pIndexBuff->Unlock();

	return cloneData;
}

/*
//====================================================
// 色変更
//====================================================
bool COriginalMesh::ColorClone3D(void)
{
	for( UINT i = 0; i < m_cloneData.numFaces; i ++ )
	{
		pTriangle[i].m_vLife -- ;
		if( pTriangle[i].m_vLife <= 0 )
		{
			return true;
			pTriangle[i].isExist = false;
		}
	}

	return false;
}

//====================================================
// クローン3Dモデルを法線方向に移動
//====================================================
void COriginalMesh::MoveClone3D( void )
{
	for( UINT i = 0; i < m_cloneData.numFaces; i ++ )
	{	
//		pTriangle[i].normal.x -= 0.1f;
//		pTriangle[i].normal.y -= 0.1f;
		pTriangle[i].normal.z -= 0.05f;

		pTriangle[i].mat._41 = pTriangle[i].m_vLogPos.x + pTriangle[i].normal.x * 0.12f;
		pTriangle[i].mat._42 = pTriangle[i].m_vLogPos.y + pTriangle[i].normal.y * 0.08f;
		pTriangle[i].mat._43 = pTriangle[i].m_vLogPos.z + pTriangle[i].normal.z * 0.08f;
		
		pTriangle[i].m_vLogPos.x = pTriangle[i].mat._41;
		pTriangle[i].m_vLogPos.y = pTriangle[i].mat._42;
		pTriangle[i].m_vLogPos.z = pTriangle[i].mat._43;
	}
}

//====================================================
// クローン3Dモデルを回転
//====================================================
void COriginalMesh::RotationClone3D(void)
{
	static  D3DXMATRIX rotX,rotY,rotZ;
	D3DXMatrixIdentity(&rotX);
	D3DXMatrixIdentity(&rotY);
	D3DXMatrixIdentity(&rotZ);
	
	for( UINT i = 0; i < m_cloneData.numFaces; i ++ )
	{			
		D3DXMatrixRotationX(&rotX,0.2f);
		D3DXMatrixRotationY(&rotY,0.2f);
		D3DXMatrixRotationZ(&rotZ,0.2f);
		pTriangle[i].mat = rotX * rotY * rotZ * pTriangle[i].mat;
	}
}
*/