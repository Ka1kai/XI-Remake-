//----------------------------------------------------
// COriginalMesh Header
//	���b�V��������𔲂��o���w�b�_�[
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

#define VERTEX_NUM (3)	// ���_��
#define CLONE_FVF  ( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

struct Position
{
	float x,y,z;
};

//----------------------------------------------------
// �I���W�i�����b�V���̃g���C�A���O�����_�\����
//----------------------------------------------------
typedef struct TAGtORIGINALMESHVERTEX
{
	D3DXVECTOR3	pos;
	D3DCOLOR	diffuse;	
	FLOAT		tu,tv;
}tagTORIGINALMESHVERTEX;

// �������
struct MyConnect
{
	WORD	idx[3];
};

//----------------------------------------------------
// �I���W�i�����b�V���p�\����
//----------------------------------------------------
typedef struct TAGtORIGINALMESH
{
	UINT			numFaces;			// �|���S���ʐ�
	UINT			numVertex;			// ���_��
	MyConnect*		connect;			// �������
	tagTORIGINALMESHVERTEX*	vertex;		// ���_���
}tagTORIGINALMESH;


struct MyTriangle
{
	tagTORIGINALMESHVERTEX vertex[3];
	D3DXVECTOR3	angle;
	D3DXVECTOR3 d;
	Position	center;
	Position	normal;

	int			m_vLife;	// �����l
	bool		isExist;	// �����m�F
	D3DXVECTOR3 m_vLogPos;	// �ʒu���
	
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
	MyTriangle*			pTriangle;		// �g���C�A���O���̐擪

	D3DXMATRIX			m_worldMtx;		// �s��
	tagTORIGINALMESH	m_cloneData;	// �N���[�����b�V���p�f�[�^

public:
	COriginalMesh	( void );
	~COriginalMesh	( void );

	//----------------------------------------------------
	//  �I���W�i�����b�V���쐬
	//----------------------------------------------------
	tagTORIGINALMESH* CreateOriginalMesh	( tagTORIGINALMESH* cloneData, CONST LPSTR filePath );

public:
	//----------------------------------------------------
	// �|���S���ʐ� �擾
	// @data			none
	// @return[UINT]	�|���S���ʐ�
	//----------------------------------------------------
	UINT	GetFaces (void)
	{
		return m_cloneData.numFaces;
	}

	//----------------------------------------------------
	// ���_���W �擾 
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
	// �N���[���𐶐�����
	// @data	lpMesh
	// @return	bool
	// @overload
	//----------------------------------------------------
//	bool Create			( LPD3DXMESH lpMesh );

};

#endif _C_ORIGINAL_MESH_H_