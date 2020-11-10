
#include "../../KaiFrameWorkHeader/ResourceHeader/COriginalMesh.h"
/*
//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
COriginalMesh::COriginalMesh()
{
	m_cloneData.connect = NULL;
	m_cloneData.vertex = NULL;
	m_cloneData.numVertex = 0;
	m_cloneData.numFaces = 0;
}

//----------------------------------------------------
// ���b�V������o�E���f�B���O�X�t�B�A�p�̍\���̃f�[�^�擾
//----------------------------------------------------
void CMeshClone::Init( LPD3DXMESH lpMesh, COLISION_DATA* colData)
{
	// �V���O���g���Ńf�o�C�X�ւ̃|�C���^���擾
	const   LPDIRECT3DDEVICE9 pd3dDevice = CDirectBase::Getpd3dDevice();

	HRESULT hr;
	// ���_���W�f�[�^
	float*	x;
	float*	y;
	float*	z;
	float*	pFloat;
	BYTE	*data;

	cloneConnect = NULL;
	cloneVertex = NULL;
	pTriangle = NULL;

	// �����蔻��p�f�[�^�쐬�̂��߂ɃN���[�����b�V���쐬
	hr = lpMesh->CloneMeshFVF( D3DXMESH_MANAGED,(D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 ),pd3dDevice,&cloneMesh);
	if( FAILED(hr) )
	{	// �쐬�ł��Ȃ������ꍇ�G���[��\���@�����͑��s
		MessageBox(0,"Colon Not Create...","error",MB_OK);
	}
	else
	{
		numVertex = cloneMesh->GetNumVertices();		// ���_���擾
		cloneMesh->GetVertexBuffer( &lpVertexBuff );	// ���_�o�b�t�@�I�u�W�F�N�g�ւ̃|�C���^�擾
		
		// ���_�o�b�t�@�����b�N
		hr = lpVertexBuff->Lock(0,0,(void**)&data,D3DLOCK_READONLY);
		if( hr == D3D_OK )
		{	// ���_�����̍��W�i�[�G���A�m��
			x = new float[numVertex];
			y = new float[numVertex];
			z = new float[numVertex];
		}

		pFloat = (float *)data;
		for( int i = 0; i < numVertex; ++ i )
		{	// ���_�����o��
			x[i] = *pFloat++;
			y[i] = *pFloat++;
			z[i] = *pFloat++;			
		}

		// max��min�����߂�
		for( int i = 0; i < numVertex; ++ i )
		{
			if( colData->minX >= x[i] )	colData->minX = x[i];
			if( colData->minY >= y[i] )	colData->minY = y[i];
			if( colData->minZ >= z[i] )	colData->minZ = z[i];
			if( colData->maxX <= x[i] )	colData->maxX = x[i];
			if( colData->maxY <= y[i] )	colData->maxY = y[i];
			if( colData->maxZ <= z[i] )	colData->maxZ = z[i];
		}

		// ���̒��S���W�����߂�
		colData->cenX = ( colData->maxX + colData->minX ) / 2;
		colData->cenY = ( colData->maxY + colData->minY ) / 2;
		colData->cenZ = ( colData->maxZ + colData->minZ ) / 2;

		// �Q�_�Ԃ̋��������߂Ĕ��a�����߂�
		colData->r = pow( colData->maxX - colData->cenX,2 ) + pow( colData->maxY - colData->cenY,2 ) + pow( colData->maxZ - colData->cenZ,2 );
		colData->r = sqrtf( colData->r );
		// ---- �f�[�^�擾�I�� ---- //

	delete[] z;
	delete[] y;
	delete[] x;
		
	// ���_�o�b�t�@���
	lpVertexBuff->Unlock();
	// ���
	cloneMesh->Release();
	cloneMesh = NULL;
	}
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
COriginalMesh::~COriginalMesh(void)
{
	SAFE_DELETE_ALLAY( m_cloneData.connect );	// �������폜
	SAFE_DELETE_ALLAY( m_cloneData.vertex );	// ���_���폜	
	SAFE_DELETE_ALLAY( pTriangle );		// �O�p�`���폜����
}

/*
void COriginalMesh::TraiangleTransform(D3DXMATRIX mat)
{
	TCLONETRIANGLEVERTEX* TransformWork;	// ���[���h���W�n�ɕϊ����邽�߂̃��[�N
	D3DXVECTOR3 temp;

	int idx0,idx1,idx2;
	D3DXVECTOR3 normal;
	D3DXVECTOR3 p0p1;
	D3DXVECTOR3 p0p2;

	// �������ꂽ�O�p�`��񂪂���΍폜����
	if( pTriangle != NULL )
	{
		delete[] pTriangle;
		pTriangle = NULL;
	}

	// ���W�ϊ��p���[�N�𒸓_������������
	TransformWork = new TCLONETRIANGLEVERTEX[numVertex];

	// ���_�����ׂĎ��o�����[���h���W�ϊ��p���[�N�ɃZ�b�g
	for( UINT i = 0; i < numVertex; i ++ )
	{
		// ���[�J�����W�����W�ϊ��p���[�N�ɃZ�b�g
		TransformWork[i] = cloneVertex[i];

		temp.x = cloneVertex[i].pos.x;
		temp.y = cloneVertex[i].pos.y;
		temp.z = cloneVertex[i].pos.z;

		// ���W�ϊ�
		D3DXVec3TransformCoord(&temp,&temp,&mat);

		// ���W�l�̂݃��[���h���W�ŏ�������
		TransformWork[i].pos.x = temp.x;
		TransformWork[i].pos.y = temp.y;
		TransformWork[i].pos.z = temp.z;
	}

	pTriangle = new MyTriangle[numFaces];	// �O�p�`�̖ʐ����I�u�W�F�N�g����

	// �O�p�`�|���S���������[�v
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
	
		// �@�����v�Z
		D3DXVec3Cross( &normal,&p0p1,&p0p2 );
		D3DXVec3Normalize( &normal,&normal );
		pTriangle[i].normal.x = normal.x;
		pTriangle[i].normal.y = normal.y;
		pTriangle[i].normal.z = normal.z;

		// �d�S�v�Z
		pTriangle[i].center.x = (pTriangle[i].vertex[0].pos.x + pTriangle[i].vertex[1].pos.x + pTriangle[i].vertex[2].pos.x)/3;
		pTriangle[i].center.y = (pTriangle[i].vertex[0].pos.y + pTriangle[i].vertex[1].pos.y + pTriangle[i].vertex[2].pos.y)/3;
		pTriangle[i].center.z = (pTriangle[i].vertex[0].pos.z + pTriangle[i].vertex[1].pos.z + pTriangle[i].vertex[2].pos.z)/3;

		// ���݂̏d�S���W��ۑ����Ă���
		pTriangle[i].m_vLogPos.x = pTriangle[i].center.x;
		pTriangle[i].m_vLogPos.y = pTriangle[i].center.y;
		pTriangle[i].m_vLogPos.z = pTriangle[i].center.z;
	
		
		// ���_���W�����_����Ƃ������W�ɕϊ�����
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
	TCLONETRIANGLEVERTEX* TransformWork;	// ���[���h���W�n�ɕϊ����邽�߂̃��[�N
	D3DXVECTOR3 temp;

	int idx0,idx1,idx2;

	// �������ꂽ�O�p�`��񂪂���΍폜����
	if( pTriangle != NULL )
	{
		delete[] pTriangle;
		pTriangle = NULL;
	}

	// ���W�ϊ��p���[�N�𒸓_������������
	TransformWork = new TCLONETRIANGLEVERTEX[numVertex];

	// ���_�����ׂĎ��o�����[���h���W�ϊ��p���[�N�ɃZ�b�g
	for( UINT i = 0; i < numVertex; i ++ )
	{
		// ���[�J�����W�����W�ϊ��p���[�N�ɃZ�b�g
		TransformWork[i] = cloneVertex[i];

		temp.x = cloneVertex[i].pos.x;
		temp.y = cloneVertex[i].pos.y;
		temp.z = cloneVertex[i].pos.z;

		// ���W�ϊ�
		D3DXVec3TransformCoord(&temp,&temp,&mat);

		// ���W�l�̂݃��[���h���W�ŏ�������
		TransformWork[i].pos.x = temp.x;
		TransformWork[i].pos.y = temp.y;
		TransformWork[i].pos.z = temp.z;
	}

	pTriangle = new MyTriangle[numFaces];	// �O�p�`�̖ʐ����I�u�W�F�N�g����

	// �O�p�`�|���S���������[�v
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
// �I���W�i�����b�V���̍쐬
//----------------------------------------------------
tagTORIGINALMESH* COriginalMesh::CreateOriginalMesh	( tagTORIGINALMESH* cloneData, CONST LPSTR filePath )
{
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	HRESULT			hr;
	LPD3DXMESH		pMesh;
	LPD3DXMESH		pCloneMesh;
	LPD3DXBUFFER	pMaterialsBuffer;
	LPDIRECT3DVERTEXBUFFER9 pVertexBuff;	// ���_�o�b�t�@
	LPDIRECT3DINDEXBUFFER9	pIndexBuff;
	DWORD	materialsCount;
	
	//X�t�@�C���ǂݍ���
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
	{   // �ǂݍ��ݎ��s��
		return nullptr;
	}

	//�N���[�����b�V��
	hr = pMesh->CloneMeshFVF( D3DXMESH_MANAGED, CLONE_FVF, pd3dDevice, &pCloneMesh );
	if( FAILED( hr ) )
	{   // �������s
		MessageBox( 0,"Colon Not Create...","error",MB_OK );
		return nullptr;
	}

	// ���_�����擾
	cloneData->numVertex = pCloneMesh->GetNumVertices();
	pCloneMesh->GetVertexBuffer( &pVertexBuff );

	// �ʐ����擾
	cloneData->numFaces = pCloneMesh->GetNumFaces();			
	pCloneMesh->GetIndexBuffer( &pIndexBuff );

	BYTE* pVertexData;

	// ���_�o�b�t�@�����b�N
	hr = pVertexBuff->Lock( 0,sizeof( tagTORIGINALMESHVERTEX ),( void** )&pVertexData,D3DLOCK_READONLY );
	if( FAILED( hr ) )
	{   // ���_�o�b�t�@���b�N���s		
		MessageBox( 0,"VertexBuff Not Lock...","error",MB_OK );
		return nullptr;
	}

	cloneData->vertex = new tagTORIGINALMESHVERTEX[cloneData->numVertex];	// ���_�����m��
	memcpy( cloneData->vertex,pVertexData,sizeof( tagTORIGINALMESHVERTEX )*( cloneData->numVertex ));	// ���_�����R�s�[

	// ���_�o�b�t�@���
	pVertexBuff->Unlock();

	// �C���f�b�N�X�o�b�t�@�����b�N
	hr = pIndexBuff->Lock(0, sizeof( tagTORIGINALMESHVERTEX ),(void**)&pIndexBuff,D3DLOCK_READONLY);
	if( FAILED( hr ) )
	{   // �C���f�b�N�X�o�b�t�@���b�N���s
		MessageBox( 0,"IndexBuff Not Lock...","error",MB_OK );
		return FALSE;
	}	
	
	cloneData->connect = new MyConnect[cloneData->numFaces];	// �ʐ����̌��������擾

	WORD*	pIndex = nullptr;		// �C���f�b�N�X�o�b�t�@

	// 3�p�`�|���S���������[�v
	for( UINT i = 0; i < cloneData->numFaces; ++ i )
	{
		cloneData->connect[i].idx[0] = *pIndex ++;
		cloneData->connect[i].idx[1] = *pIndex ++;
		cloneData->connect[i].idx[2] = *pIndex ++;
	}
	// �C���f�b�N�X�o�b�t�@���
	pIndexBuff->Unlock();

	return cloneData;
}

/*
//====================================================
// �F�ύX
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
// �N���[��3D���f����@�������Ɉړ�
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
// �N���[��3D���f������]
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