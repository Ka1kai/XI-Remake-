
#include "../../KaiFrameWorkHeader/ResourceHeader/CResourceXFile.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CResourceXFile::CResourceXFile( void )
{
	m_pMeshMaterials	= nullptr;
	m_pMeshTexture		= nullptr;
	m_pMesh				= nullptr;
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
CResourceXFile::~CResourceXFile( void )
{
	SAFE_DELETE_FREE( m_pMeshMaterials );	// �}�e���A���̉��

	if( m_pMeshTexture != nullptr )
	{	// �e�N�X�`���̉��
		for( int i = 0; ( m_pMeshTexture[i] )&&( ( unsigned ) i < m_materialsCount ); i ++ ){
			m_pMeshTexture[i]->Release();
			m_pMeshTexture[i] = nullptr;
		}
	}

	SAFE_DELETE_FREE( m_pMeshTexture );	// �e�N�X�`���̃N���A
	SAFE_DELETE_RELESE( m_pMesh );		// ���b�V���̉��
}

//----------------------------------------------------
// X�t�@�C���̃��[�h
//----------------------------------------------------
HRESULT CResourceXFile::Load( CONST LPSTR filePath )
{
		// 3D�f�o�C�X�̃|�C���^���V���O���g���Ŏ擾
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
	
	DEBUG::PrintfColor( DEBUG::H_CYAN, "%s\n",filePath );

	// X�t�@�C���ǂݍ���
	if( FAILED(D3DXLoadMeshFromX
		(filePath,
		D3DXMESH_MANAGED,
		pd3dDevice,
		NULL,
		&m_pMaterialsBuffer,
		NULL,
		&m_materialsCount,
		&m_pMesh)))
	{	// �ǂݍ��ݎ��s
		DEBUG::PrintfColor( DEBUG::H_RED, " Load XFile Failed... \n\n" );
		return E_FAIL;
	}

	// �}�e���A�����Z�b�g
	this->SetMaterials();
 
	DEBUG::PrintfColor( DEBUG::H_GREEN, "Load XFile Successfully\n" );
	return S_OK;
}

//----------------------------------------------------
// �}�e���A���̃Z�b�g
//----------------------------------------------------
HRESULT CResourceXFile::SetMaterials( void )
{
	// 3D�f�o�C�X�̃|�C���^���V���O���g���Ŏ擾
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
	
	D3DXMATERIAL *pMaterials = (D3DXMATERIAL *)m_pMaterialsBuffer->GetBufferPointer();
	// �}�e���A���̑��������A�}�e���A���ƃe�N�X�`���̔z��𓮓I�Ɋm��
	m_pMeshMaterials = (D3DMATERIAL9*)malloc(sizeof(D3DMATERIAL9)*m_materialsCount);
	m_pMeshTexture = (LPDIRECT3DTEXTURE9*)malloc(sizeof(LPDIRECT3DTEXTURE9)*m_materialsCount);

	// �}�e���A�����Z�b�g���Ă���
	for( int i = 0;( unsigned )i < m_materialsCount;i ++ ){
		m_pMeshMaterials[ i ] = pMaterials[ i ].MatD3D;
		m_pMeshMaterials[ i ].Ambient = m_pMeshMaterials[ i ].Diffuse;
		// �e�N�X�`���`��
		if( pMaterials[i].pTextureFilename != "" && pMaterials[i].pTextureFilename != NULL )
		{
			// �e�N�X�`���ǂݍ���
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
