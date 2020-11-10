//----------------------------------------------------
// COriginalMesh Header
//	メッシュから情報を抜き出すヘッダー
//
// @date	2013/8/7
// @author  T.Kawashita
//----------------------------------------------------
#ifndef _C_ORIGINAL_MESH_H_
#define _C_ORIGINAL_MESH_H_

#include <d3dx9.h>

#include "../UtilityHeader/Macro.hpp"
#include "../DirectX9Header/CDirectX9FrameWork.h"
//#include "../GameMathHeader/CCollision.h"

#define VERTEX_NUM (3)	// 頂点数
#define CLONE_FVF  ( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

struct Position
{
	float x,y,z;
};

//----------------------------------------------------
// オリジナルメッシュのトライアングル頂点構造体
//----------------------------------------------------
typedef struct TAGtORIGINALMESHVERTEX
{
	D3DXVECTOR3	pos;
	D3DCOLOR	diffuse;	
	FLOAT		tu,tv;
}tagTORIGINALMESHVERTEX;

// 結線情報
struct MyConnect
{
	WORD	idx[3];
};

//----------------------------------------------------
// オリジナルメッシュ用構造体
//----------------------------------------------------
typedef struct TAGtORIGINALMESH
{
	UINT			numFaces;			// ポリゴン面数
	UINT			numVertex;			// 頂点数
	MyConnect*		connect;			// 結線情報
	tagTORIGINALMESHVERTEX*	vertex;		// 頂点情報
}tagTORIGINALMESH;


struct MyTriangle
{
	tagTORIGINALMESHVERTEX vertex[3];
	D3DXVECTOR3	angle;
	D3DXVECTOR3 d;
	Position	center;
	Position	normal;

	int			m_vLife;	// 生存値
	bool		isExist;	// 生存確認
	D3DXVECTOR3 m_vLogPos;	// 位置情報
	
	D3DXMATRIX	mat;
	MyTriangle()
	{
		angle.x = 0.0f;
		angle.y = 0.0f;
		angle.z = 0.0f;
		d.x = 0.2f;
		d.y = 0.2f;
		d.z = 0.2f;
		D3DXMatrixIdentity(&mat);
	}
};

class COriginalMesh
{
private:
	MyTriangle*			pTriangle;		// トライアングルの先頭

	D3DXMATRIX			m_worldMtx;		// 行列
	tagTORIGINALMESH	m_cloneData;	// クローンメッシュ用データ

public:
	COriginalMesh	( void );
	~COriginalMesh	( void );

	//----------------------------------------------------
	//  オリジナルメッシュ作成
	//----------------------------------------------------
	tagTORIGINALMESH* CreateOriginalMesh	( tagTORIGINALMESH* cloneData, CONST LPSTR filePath );

public:
	//----------------------------------------------------
	// ポリゴン面数 取得
	// @data			none
	// @return[UINT]	ポリゴン面数
	//----------------------------------------------------
	UINT	GetFaces (void)
	{
		return m_cloneData.numFaces;
	}

	//----------------------------------------------------
	// 頂点座標 取得 
	//----------------------------------------------------
	D3DXVECTOR3* GetVertexVec	(int faceNum,int verNum)
	{
		return &(pTriangle+faceNum)->vertex[verNum].pos;
	}

public:
//	void Init				( LPD3DXMESH lpMesh,THITCIRCLE* colData2 );
//	void MoveClone3D		( void );
//	bool ColorClone3D		( void );
//	void RotationClone3D	( void );
//	void TraiangleTransform ( D3DXMATRIX mat );
//	void LocalToWorld		( D3DXMATRIX mat );

	//----------------------------------------------------
	// クローンを生成する
	// @data	lpMesh
	// @return	bool
	// @overload
	//----------------------------------------------------
//	bool Create			( LPD3DXMESH lpMesh );

};

#endif _C_ORIGINAL_MESH_H_