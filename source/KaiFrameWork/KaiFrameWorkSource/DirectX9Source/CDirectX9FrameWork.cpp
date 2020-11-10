
#include "../../KaiFrameWorkHeader/DirectX9Header/CDirectX9FrameWork.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CDirectX9FrameWork::CDirectX9FrameWork( void )
{
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
CDirectX9FrameWork::~CDirectX9FrameWork( void )
{
}

//----------------------------------------------------
// DirectX9�̏�����
//----------------------------------------------------
HRESULT CDirectX9FrameWork::Init( void )
{
	CONST HWND&	hWnd = CWindowSystem::GethWnd();
	LPDIRECT3D9& pd3d = CDirectX9FrameWork::Getpd3d();
	LPDIRECT3DDEVICE9& pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	D3DPRESENT_PARAMETERS	d3dpp;

	if( NULL == ( pd3d = Direct3DCreate9(D3D_SDK_VERSION )))
	{  //Direct3D�I�u�W�F�N�g�̍쐬���s
		return E_FAIL;	
	}

	ZeroMemory( &d3dpp, sizeof(d3dpp));

	d3dpp.Windowed					= TRUE;							// �E�B���h�E���[�h
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;		// �f���M���ɓ������ăt���b�v����
	d3dpp.BackBufferFormat			= D3DFMT_UNKNOWN;				// �o�b�N�o�b�t�@�̃t�H�[�}�b�g�͌��ݐݒ肳��Ă�����̂��g��
	d3dpp.EnableAutoDepthStencil	= TRUE;							// �f�v�X�o�b�t�@(Z�o�b�t�@)�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��

	if( FAILED( pd3d->CreateDevice(	D3DADAPTER_DEFAULT,							// �v���C�}���A�_�v�^��I��
										D3DDEVTYPE_HAL,							// �n�[�h�E�F�A�ɂ��`�揈����I��
										hWnd,									// �E�B���h�E�n���h��
										D3DCREATE_HARDWARE_VERTEXPROCESSING |	// �n�[�h�E�F�A�ɂ�钸�_�v�Z��I�� 
										D3DCREATE_MULTITHREADED ,				// �}���`�X���b�h�̃t���O��ON�ɂ���	
										&d3dpp,									// D3D Object
										&pd3dDevice	)))
	{
		DEBUG::PrintfColor( DEBUG::H_RED, "---- Init DirectX Failed... ----\n\n" );
		return	E_FAIL;		// ��������΃f�o�C�X�������
	}

	pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );						// Z�o�b�t�@���g�p
	pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );				// ���u�����h���s��
	pd3dDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );		// ���\�[�X�J���[�̎w��
	pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );	// ���f�X�e�B�l�[�V�����J���[�̎w��
	pd3dDevice->SetRenderState( D3DRS_CULLMODE,D3DCULL_NONE );

	pd3dDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
    pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
    pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);

	pd3dDevice->SetFVF( D3DFVF_XYZ  | D3DFVF_DIFFUSE | D3DFVF_TEX1 );
	

	DEBUG::PrintfColor( DEBUG::H_GREEN, "---- Init DirectX Successfully ---- \n\n" );
	return D3D_OK;		// ��������

}

