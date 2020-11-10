
#include "../../KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"

//----------------------------------------------------
// �����_�����O�J�n
//----------------------------------------------------
BOOL CDirectDrawSystem::BeginScene( void )
{
	// �f�o�C�X�|�C���^�̎擾
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0);
	
	if( SUCCEEDED( pd3dDevice->BeginScene() ) )
	{	// �`��J�n
		return true;
	}

	return false;
}

//----------------------------------------------------
// �����_�����O�I�� 
//----------------------------------------------------
void CDirectDrawSystem::EndScene( void )
{
	// �f�o�C�X�|�C���^�̎擾
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
	
	pd3dDevice->EndScene();
}

//----------------------------------------------------
// 2D�����_�����O( �������W�v�Z���� )
//----------------------------------------------------
void CDirectDrawSystem::DrawSpriteRHW( CONST LPDIRECT3DTEXTURE9 pTexture,CONST tagTSPRITERHW* pVertex )
{
	// �f�o�C�X�|�C���^�̎擾
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	// ���u�����h���s��
	pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,TRUE );

	// ���ߏ������s��
	pd3dDevice->SetRenderState( D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA );

	// �`��̌^�ϊ�
	pd3dDevice->SetFVF( FVF_VERTEX_SPRITERHW );

	// �e�N�X�`���`��
	pd3dDevice->SetTexture( 0,pTexture );

	// �|���S���`��
	pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, pVertex, sizeof( tagTSPRITERHW ) );
}

//----------------------------------------------------
// 2D�����_�����O( �������W�v�Z���� �e�N�X�`���Ȃ� )
//----------------------------------------------------
void CDirectDrawSystem::DrawSpriteRHW( CONST tagTSPRITERHW *pVertex )
{
	// �f�o�C�X�|�C���^�̎擾
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	// �`��̌^�ϊ�
	pd3dDevice->SetFVF( FVF_VERTEX_SPRITERHW );

	// �e�N�X�`���`�悵�Ȃ�
	pd3dDevice->SetTexture( 0,NULL );

	// �|���S���`��
	pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, 2, pVertex, sizeof( tagTSPRITERHW ) );
}

//----------------------------------------------------
// 2D�X�v���C�g�����_�����O( �������W�v�Z�Ȃ��@�e�N�X�`������ )
//----------------------------------------------------
void CDirectDrawSystem::DrawSprite( CONST LPDIRECT3DTEXTURE9 pTexture, tagTSPRITE* pSpriteVertex, CONST D3DXMATRIX* pWorldMtx )
{
	// �f�o�C�X�̃|�C���^���擾
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
	
	// ���C�e�B���O�v�Z�͂��Ȃ��B�[�x�o�b�t�@�ɂ͏������܂Ȃ�
	pd3dDevice->SetRenderState( D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA );
	// �����v�Z�I�t�i���_�̐F���L���ɂȂ�j
	pd3dDevice->SetRenderState( D3DRS_LIGHTING,FALSE );
	// Z�o�b�t�@�𖳌����i�A���t�@�u�����h��L���ɂ��邽�߁j
	pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,FALSE );
	
	// �e�N�X�`���X�e�[�W�X�e�[�g
	pd3dDevice->SetTextureStageState( 0,D3DTSS_ALPHAOP,D3DTOP_MODULATE );
	pd3dDevice->SetTextureStageState( 0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE );
	pd3dDevice->SetTextureStageState( 0,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE );

	pd3dDevice->SetTexture( 0, pTexture );					// �e�N�X�`�����Z�b�g
	pd3dDevice->SetFVF( FVF_VERTEX_SPRITE );				// ���_�̌^���Z�b�g
	pd3dDevice->SetTransform( D3DTS_WORLD, pWorldMtx );		// ���[���h�s����Z�b�g

	// �����_�����O
	pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN, 2, pSpriteVertex, sizeof(tagTSPRITE) );	

}

//----------------------------------------------------
// �r���{�[�h�����_�����O
//----------------------------------------------------
void CDirectDrawSystem::DrawBillBoard( CONST LPDIRECT3DTEXTURE9 pTexture, CONST D3DXMATRIX* pBillboardMtx, CONST tagTBILLBORDVERTEX* pBillboardVertex )
{
	// �f�o�C�X�̃|�C���^���擾
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
	
	// ���C�e�B���O�v�Z�͂��Ȃ��B�[�x�o�b�t�@�ɂ͏������܂Ȃ�
	pd3dDevice->SetRenderState( D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA );
	// �����v�Z�I�t�i���_�̐F���L���ɂȂ�j
	pd3dDevice->SetRenderState( D3DRS_LIGHTING,FALSE );
	// Z�o�b�t�@�𖳌����i�A���t�@�u�����h��L���ɂ��邽�߁j
	pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,FALSE );
	
	// �e�N�X�`���X�e�[�W�X�e�[�g
	pd3dDevice->SetTextureStageState( 0,D3DTSS_ALPHAOP,D3DTOP_MODULATE );
	pd3dDevice->SetTextureStageState( 0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE );
	pd3dDevice->SetTextureStageState( 0,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE );

	pd3dDevice->SetTexture( 0,pTexture );					// �e�N�X�`�����Z�b�g
	pd3dDevice->SetFVF( FVF_VERTEX_BILLBOARD );				// ���_�̌^���Z�b�g
	pd3dDevice->SetTransform( D3DTS_WORLD,pBillboardMtx );	// ���[���h�s����Z�b�g

	// �����_�����O
	pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN,2,pBillboardVertex,sizeof(tagTBILLBORDVERTEX) );	
}

//----------------------------------------------------
// 3D���f�������_�����O
//----------------------------------------------------
void CDirectDrawSystem::Draw3D( CResourceXFile *pModel, CONST D3DXMATRIX *pWorldMtx )
{
	// �f�o�C�X�|�C���^�̎擾
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	// �����v�Z�I��
	pd3dDevice->SetRenderState( D3DRS_LIGHTING,TRUE );

	// Z�o�b�t�@��L����
	pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,TRUE );
	pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

	// ���_�̌^���Z�b�g
	pd3dDevice->SetFVF( FVF_VERTEX_3D );
	
	// ���b�V�����}�e���A���P�ʂŕ`��
	pd3dDevice->SetTransform( D3DTS_WORLD,pWorldMtx);

	// �����_�����O
	for( unsigned int i = 0; i < pModel->GetMaterialCount(); ++ i ){
		pd3dDevice->SetMaterial( &pModel->GetMeshMaterial()[i] );
		pd3dDevice->SetTexture( 0,pModel->GetMeshTexture()[i] );
		pModel->GetMesh()->DrawSubset( i );
	}
}

//----------------------------------------------------
// 3D���f�������_�����O(texture�̎w��) 
//----------------------------------------------------
void CDirectDrawSystem::Draw3D( CResourceXFile* pModel, CONST D3DXMATRIX* pWorldMtx, BOOL isTexture )
{
	// �f�o�C�X�̃|�C���^���擾
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	// �����v�Z�I��
	pd3dDevice->SetRenderState( D3DRS_LIGHTING,TRUE );
	// Z�o�b�t�@��L����
	pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,TRUE );

	pd3dDevice->SetFVF( FVF_VERTEX_3D );

	if( isTexture == false )
	{
		pd3dDevice->SetTexture( 0,NULL );	// �e�N�X�`���Ȃ�
	}

	pd3dDevice->SetTransform( D3DTS_WORLD,pWorldMtx );

	// �����_�����O
	for( unsigned int i = 0; i < pModel->GetMaterialCount(); ++i ){
		pd3dDevice->SetMaterial( &pModel->GetMeshMaterial()[i] );
		pModel->GetMesh()->DrawSubset( i );
	}
}

//----------------------------------------------------
// 3D���f�������_�����O( �F�w�� )
//----------------------------------------------------
void CDirectDrawSystem::Draw3D( CResourceXFile* pModel, CONST D3DXMATRIX* pWorldMtx, D3DXCOLOR* color )
{
		// �f�o�C�X�|�C���^�̎擾
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	// �����v�Z�I��
	pd3dDevice->SetRenderState( D3DRS_LIGHTING,TRUE );

	// Z�o�b�t�@��L����
	pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,TRUE );
	pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

	// ���_�̌^���Z�b�g
	pd3dDevice->SetFVF( FVF_VERTEX_3D );
	
	// ���b�V�����}�e���A���P�ʂŕ`��
	pd3dDevice->SetTransform( D3DTS_WORLD,pWorldMtx);

	// �����_�����O
	for( unsigned int i = 0; i < pModel->GetMaterialCount(); ++ i ){
		D3DMATERIAL9 workMat;
		
		// �F�����
		::CopyMemory( &workMat,&pModel->GetMeshMaterial()[i],sizeof( D3DMATERIAL9 ) );

		workMat.Diffuse.r = pModel->GetMeshMaterial()[i].Diffuse.r * color->r;
		workMat.Diffuse.g = pModel->GetMeshMaterial()[i].Diffuse.g * color->g;
		workMat.Diffuse.b = pModel->GetMeshMaterial()[i].Diffuse.b * color->b;
		workMat.Diffuse.a = pModel->GetMeshMaterial()[i].Diffuse.a * color->a;

		pd3dDevice->SetMaterial( &workMat );
		pd3dDevice->SetTexture( 0,pModel->GetMeshTexture()[i] );
		pModel->GetMesh()->DrawSubset( i );
	}
}

//----------------------------------------------------
// �N���[��3D���f�������_�����O
//----------------------------------------------------
void CDirectDrawSystem::Draw3DClone( UINT numFaces, CONST LPDIRECT3DTEXTURE9 textureData, tagTORIGINALMESHVERTEX* pCloneVertex, CONST D3DXMATRIX* pCloneMtx )
{
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	//pd3dDevice->SetFVF( FVF_VERTEX_CLONE );

	pd3dDevice->SetTexture( 0, textureData );
	pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,true );	// ���u�����h�̏�����L���ɂ���

	for( UINT i = 0; i < numFaces; ++ i ){
		pd3dDevice->SetTransform(D3DTS_WORLD,pCloneMtx);
		pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP,1,pCloneVertex,sizeof(tagTORIGINALMESHVERTEX));
	
	}
}

//----------------------------------------------------
// �N���[��3D���f�������_�����O(�e�N�X�`���Ȃ�)
//----------------------------------------------------
void CDirectDrawSystem::Draw3DClone( UINT numFaces, tagTORIGINALMESHVERTEX* pCloneVertex, CONST D3DXMATRIX* pCloneMtx )
{
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	//pd3dDevice->SetFVF( FVF_VERTEX_CLONE );
	pd3dDevice->SetTexture( 0, NULL );

	// �N���[����3D���f�������_�����O
	for( UINT i = 0; i < numFaces; ++ i ){
		pd3dDevice->SetTransform( D3DTS_WORLD, pCloneMtx );
		pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP,1,&pCloneVertex[i],sizeof( tagTORIGINALMESHVERTEX ) );
	}
}

//----------------------------------------------------
// �`�󃌃��_�����O ( �X�t�B�A,�{�b�N�X )
//----------------------------------------------------
void CDirectDrawSystem::DrawShape( CONST D3DXMATRIX* worldMtx, CONST D3DMATERIAL9* shapeMat, CONST LPD3DXMESH shapeMesh )
{
	// �f�o�C�X�̃|�C���^���擾
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );				// ���u�����h���s��
	pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );		// ���\�[�X�J���[�̎w��
	pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );	// ���f�X�e�B�l�[�V�����J���[�̎w��
	
	pd3dDevice->SetRenderState(D3DRS_LIGHTING,TRUE);		// ���C�g�̌v�Z��ON
	pd3dDevice->SetRenderState(D3DRS_SPECULARENABLE,TRUE);

	// �s����Z�b�g
	pd3dDevice->SetTransform( D3DTS_WORLD,worldMtx );

	// �e�N�X�`���̃Z�b�g
	pd3dDevice->SetTexture( 0,NULL );
	
	// �}�e���A���̃Z�b�g
	pd3dDevice->SetMaterial( shapeMat );
	
	// �����_�����O
	shapeMesh->DrawSubset(0);
}

//----------------------------------------------------
// �p�[�e�B�N�������_�����O
// ���Z��������C���C�g�v�Z�Ȃ��C���u�����h����
//----------------------------------------------------
void CDirectDrawSystem::DrawParticle( CONST LPDIRECT3DTEXTURE9 pTexture, CONST D3DXMATRIX* pBillboardMtx, CONST tagTBILLBORDVERTEX* pBillboardVertex )
{
	// �f�o�C�X�|�C���^�̎擾
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
	
	pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,TRUE );
	pd3dDevice->SetRenderState( D3DRS_SRCBLEND,D3DBLEND_SRCALPHA );
	pd3dDevice->SetRenderState( D3DRS_BLENDOP,D3DBLENDOP_ADD );
	pd3dDevice->SetRenderState( D3DRS_DESTBLEND,D3DBLEND_ONE );		// ���Z����
	
	// ���C�e�B���O�v�Z�͂��Ȃ��B�[�x�o�b�t�@�ɂ͏������܂Ȃ�
	pd3dDevice->SetRenderState( D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA );
	// �����v�Z�I�t�i���_�̐F���L���ɂȂ�j
	pd3dDevice->SetRenderState( D3DRS_LIGHTING,FALSE );
	// Z�o�b�t�@�𖳌����i�A���t�@�u�����h��L���ɂ��邽�߁j
	pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,FALSE );
	
	// �e�N�X�`���X�e�[�W�X�e�[�g
	pd3dDevice->SetTextureStageState( 0,D3DTSS_ALPHAOP,D3DTOP_MODULATE );
	pd3dDevice->SetTextureStageState( 0,D3DTSS_ALPHAARG1,D3DTA_TEXTURE );
	pd3dDevice->SetTextureStageState( 0,D3DTSS_ALPHAARG2,D3DTA_DIFFUSE );

	pd3dDevice->SetTexture( 0,pTexture );					// �e�N�X�`���Z�b�g
	pd3dDevice->SetFVF( FVF_VERTEX_BILLBOARD );				// ���_�̌^�Z�b�g
	pd3dDevice->SetTransform( D3DTS_WORLD,pBillboardMtx );	// ���[���h�s����Z�b�g

	// �����_�����O
	pd3dDevice->DrawPrimitiveUP( D3DPT_TRIANGLEFAN,2,pBillboardVertex,sizeof(tagTBILLBORDVERTEX) );
}

//----------------------------------------------------
// �f�o�b�O�X�e�[�W�����_�����O
// �e�N�X�`���Ȃ�
//----------------------------------------------------
void CDirectDrawSystem::DrawDebugStage	( CONST UINT numLines, CONST tagTDEBUGVERTEX* pDebugStageVertex )
{
	// �f�o�C�X�|�C���^�̎擾
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
	
	D3DXMATRIX workMtx;
	D3DXMatrixIdentity( &workMtx );

	// ���C�e�B���O�v�Z�͂��Ȃ��B�[�x�o�b�t�@�ɂ͏������܂Ȃ�
	pd3dDevice->SetRenderState( D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA );
	// �����v�Z�I�t�i���_�̐F���L���ɂȂ�j
	pd3dDevice->SetRenderState( D3DRS_LIGHTING,FALSE );
	// Z�o�b�t�@�𖳌����i�A���t�@�u�����h��L���ɂ��邽�߁j
	pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,FALSE );

	pd3dDevice->SetTexture( 0,NULL );
	pd3dDevice->SetFVF( FVF_VERTEX_DEBUG );
	pd3dDevice->SetTransform( D3DTS_WORLD,&workMtx );

	// �����_�����O
	pd3dDevice->DrawPrimitiveUP( D3DPT_LINELIST,numLines,pDebugStageVertex,sizeof( tagTDEBUGVERTEX ) ); 
}
