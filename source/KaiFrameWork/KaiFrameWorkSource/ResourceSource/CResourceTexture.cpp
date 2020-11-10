
#include "../../KaiFrameWorkHeader/ResourceHeader/CResourceTexture.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CResourceTexture::CResourceTexture( void )
{
	m_pTexture = nullptr;
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
CResourceTexture::~CResourceTexture( void )
{
	SAFE_DELETE_RELESE( m_pTexture );
}

//----------------------------------------------------
// �e�N�X�`���̃��[�h
//----------------------------------------------------
bool CResourceTexture::Load( CONST LPSTR filePath )
{
//�f�o�C�X�n���h�����V���O���g���Ŏ擾
	CONST LPDIRECT3DDEVICE9& pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
	
	DEBUG::PrintfColor(DEBUG::H_CYAN,"%s\n", filePath );

	// �e�N�X�`�����[�h
	if( FAILED( D3DXCreateTextureFromFile( pd3dDevice, filePath, &m_pTexture )))
	{	// ���[�h���s	
		DEBUG::PrintfColor(DEBUG::H_RED," Load Texture Failed...\n" );
		return false;
	}

	DEBUG::PrintfColor( DEBUG::H_GREEN,"Load Texture Successfully \n" );
	return true;

}