//----------------------------------------------------
// CDirectDrawSystem Header 
//�@DirectX�̕`��V�X�e��
//
// @date	2013/5/1
// @author  T.Kawashita
//----------------------------------------------------
#ifndef _C_DIRECTX9_DRAW_SYSTEM_H_
#define _C_DIRECTX9_DRAW_SYSTEM_H_

// �����w�b�_�[�ǂݍ���
#include <d3dx9.h>

// �O���w�b�_�[�ǂݍ���
#include "../DirectX9Header/CDirectX9FrameWork.h"
#include "../GameObjectHeader/2D/C2DSprite.h"
#include "../GameObjectHeader/2D/C2DSpriteRHW.h"
#include "../GameObjectHeader/CObjectBase.hpp"
#include "../GameObjectHeader/BillBoard/CBillBoard.h"
#include "../DebugHeader/CDebugStage.h"
#include "../ResourceHeader/COriginalMesh.h"
#include "../ResourceHeader/CResourceXFile.h"
#include "../ResourceHeader/CResourceTexture.h"

#define	FVF_VERTEX_SPRITERHW	( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )	// Sprite(RHW����)�`��pFVF
#define FVF_VERTEX_SPRITE		( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )		// Sprite�`��pFVF
#define FVF_VERTEX_3D			( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )		// 3D�`��pFVF
#define FVF_VERTEX_MESH			( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )		// �N���[�����f���pFVF
#define FVF_VERTEX_BILLBOARD	( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )		// �r���{�[�h�pFVF
#define FVF_VERTEX_DEBUG		( D3DFVF_XYZ | D3DFVF_DIFFUSE )						// �f�o�b�O�pFVF
#define FVF_VERTEX_CLONE		( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )		// �N���[���pFVF

class CDirectDrawSystem
{
private:
	// �R���X�g���N�^
	CDirectDrawSystem				( void ){}
	CDirectDrawSystem				( CONST CDirectDrawSystem& input ){}	// �R�s�[�R���X�g���N�^��h��
	CDirectDrawSystem	operator=	( CONST CDirectDrawSystem& input ){}	// �����o�̑����h��

public:
	// �f�X�g���N�^
	~CDirectDrawSystem	( void ){}

	// ���g�̃C���X�^���X�擾
	static CDirectDrawSystem*	GetInstance	( void )
	{
		static CDirectDrawSystem drawSystem;
		return &drawSystem;
	}

	BOOL	BeginScene	( void );		// �����_�����O�J�n
	void	EndScene	( void );		// �����_�����O�I��
	
	//----------------------------------------------------
	// @name	SetFVF
	// @content	���_�̌^���Z�b�g
	// @param	fvf		���_�̌^
	// @return	none
	// @date	2013/7/1
	//----------------------------------------------------
	void	SetFVF		( CONST DWORD fvf )	
	{
		// �f�o�C�X�̃|�C���^���擾
		LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

		// ���_�̌^�Z�b�g
		pd3dDevice->SetFVF( fvf );
	}

	//----------------------------------------------------
	// @name	Present
	// @content	�����_�����O����window�ɑ��M
	// @param	none	
	// @return	none
	// @date	2013/7/1
	//----------------------------------------------------
	void	Present		( void )
	{	
		// �f�o�C�X�|�C���^�̎擾
		CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
	
		// �`���񑗐M
		pd3dDevice->Present(NULL,NULL,NULL,NULL);
	}

	//----------------------------------------------------
	// @name	SetFillMode
	// @content	�����_�����O��Ԃ�ύX(WireFrame,Point,Solid)
	// @param	fillMode	�ύX�����������_�����O���[�h
	// @return	none
	// @date	2013/7/30
	//----------------------------------------------------
	void	SetFillMode	( CONST D3DFILLMODE fillMode )
	{
		// �f�o�C�X�|�C���^�̎擾
		CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

		// �`���Ԃ̕ύX
		pd3dDevice->SetRenderState( D3DRS_FILLMODE,fillMode );
	}

	//----------------------------------------------------
	// @name	SetCallMode
	// @content	�J�����O�̏�Ԃ�ύX
	// @param	isCullMode
	// @return	none
	// @date	2013/7/31
	//----------------------------------------------------
	void	SetCallMode	( CONST BOOL isCullMode )
	{
		// �f�o�C�X�|�C���^�̎擾
		CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
		
		if( isCullMode )
			pd3dDevice->SetRenderState( D3DRS_CULLMODE,D3DCULL_CCW );	// �J�����O�n�m}
		else
			pd3dDevice->SetRenderState( D3DRS_CULLMODE,D3DCULL_NONE );	// �J�����O�n�e�e
	}

public:
	//----------------------------------------------------
	// @name	DrawSpriteRHW
	// @content	�X�v���C�g�����_�����O(�������W�v�Z����)
	// @param	pTexture		�e�N�X�`��	
	// @param	pVertex			���_���
	// @return	none	
	// @date	2013/7/3
	// @update	2013/12/13		�֐����̕ύX
	//----------------------------------------------------
	void	DrawSpriteRHW		( CONST LPDIRECT3DTEXTURE9 pTexture, CONST tagTSPRITERHW* pVertex );

	//----------------------------------------------------
	// @name	DrawSpriteRHW
	// @content	�X�v���C�g�����_�����O(�������W�v�Z����)
	// @param	pVertex			���_���
	// @return	none
	// @date	2013/7/4
	// @update	2013/12/13		�֐����̕ύX
	//----------------------------------------------------
	void	DrawSpriteRHW		( CONST tagTSPRITERHW* pVertex );
	
	//----------------------------------------------------
	// @name	DrawSprite
	// @content	�X�v���C�g�����_�����O(�������W�v�Z�Ȃ�)
	// @param	pTexture			�e�N�X�`��
	// @param	pVertex				���_���
	// @param	pWorldMtx			���[���h�s��
	// @return	none	
	// date		2013/12/12
	//----------------------------------------------------
	void	DrawSprite	( CONST LPDIRECT3DTEXTURE9 pTexture,tagTSPRITE* pSpriteVertex, CONST D3DXMATRIX* pWorldMtx );

public:
	//----------------------------------------------------
	// @name	Draw3D
	// @content	3D���f�������_�����O
	// @param	pModel			���f���f�[�^
	// @param	pWorldMtx		���f���s��
	// @return	none
	// @date	2013/7/5
	//----------------------------------------------------
	void	Draw3D		(  CResourceXFile* pModel, CONST D3DXMATRIX *pWorldMtx );

	//----------------------------------------------------
	// @name	Draw3D
	// @content	3D���f�������_�����O( texture�̎w�� )
	// @param	pModel			���f���f�[�^
	// @param	pWorldMtx		���f���s��
	// @param	isTexture		�e�N�X�`���̂���Ȃ�
	// @return	none
	// @date	2013/7/6
	//----------------------------------------------------
	void	Draw3D		( CResourceXFile* pModel, CONST D3DXMATRIX *pWorldMtx, BOOL isTexture );

	//----------------------------------------------------
	// @name	Draw3D
	// @content	3D���f�������_�����O( �F�w�� )
	// @param	pModel			���f���f�[�^
	// @param	pWorldMtx		���f���s��	
	// @param	color			�F���
	// @return	none
	// @date	2013/12/4
	//----------------------------------------------------
	void	Draw3D		( CResourceXFile* pModel, CONST D3DXMATRIX *pWorldMtx, D3DXCOLOR* color );

public:
	//----------------------------------------------------
	// @name	Draw3DClone
	// @content	�N���[��3D���f�������_�����O( �e�N�X�`������ )
	// @param	numFaces		�ʐ�
	// @param	pTexture		�e�N�X�`��
	// @param	pCloneVertex	�N���[�����_
	// @param	pCloneMtx		�N���[���s��
	// @return	none
	// @date	2013/7/10
	//----------------------------------------------------
	void	Draw3DClone	( UINT numFaces, LPDIRECT3DTEXTURE9 pTexture, tagTORIGINALMESHVERTEX* pCloneVertex, CONST D3DXMATRIX* pCloneMtx );

	//----------------------------------------------------
	// @name	Draw3DClone
	// @content �N���[��3D���f�������_�����O( �e�N�X�`���Ȃ� )
	// @param	numFaces		�ʐ�
	// @param	pCloneVertex	�N���[���̒��_���
	// @param	pCloneMat		�N���[���̍s��
	// @return	none
	// @date	2013/7/12
	//----------------------------------------------------
	void	Draw3DClone	( UINT numFaces, tagTORIGINALMESHVERTEX* pCloneVertex, CONST D3DXMATRIX* pCloneMtx );

	//----------------------------------------------------
	// @name	DrawShape	
	// @content	�`�󃌃��_�����O
	// @param	pWorldMtx		���[���h�s��
	// @param	pShapeMat		�`��}�e���A��
	// @aram	pShapeMesh		�`�󃁃b�V��
	// @return	none
	// @date	2013/7/15
	//----------------------------------------------------
	void	DrawShape	( CONST D3DXMATRIX* pWorldMtx,CONST D3DMATERIAL9* pShapeMat, CONST LPD3DXMESH pShapeMesh );

public:
	//----------------------------------------------------
	// @name	DrawBillBoard
	// @content	�r���{�[�h�����_�����O
	// @param	pTexture		�r���{�[�h�̃e�N�X�`��
	// @param	pBillBoardMtx	�r���{�[�h�̍s��
	// @param	pBillBoardVertex�r���{�[�h�̒��_���
	// @return	none
	// @date	2013/7/18
	//----------------------------------------------------
	void DrawBillBoard( CONST LPDIRECT3DTEXTURE9 pTexture, CONST D3DXMATRIX* pBillBoardMtx, CONST tagTBILLBORDVERTEX* pBillBoardVertex );

	//----------------------------------------------------
	// @name	DrawParticle
	// @content	�p�[�e�B�N�������_�����O
	// @param	pTexture		�p�[�e�B�N���̃e�N�X�`��
	// @param	pBillBoardMtx	�r���{�[�h�̍s��
	// @param	pBillBoardVertex�r���{�[�h�̒��_���
	// @return	none
	// @date	2013/7/19
	//----------------------------------------------------
	void DrawParticle	( CONST LPDIRECT3DTEXTURE9 pTexture, CONST D3DXMATRIX* pBillBoardMtx, CONST tagTBILLBORDVERTEX* pBillBoardVertex );

public:
	//----------------------------------------------------
	// @name	DrawDebugStage
	// @content	�f�o�b�O�X�e�[�W�����_�����O
	// @param	numLines			���C����
	// @param	pDebugStageVertex	�f�o�b�O�X�e�[�W�̒��_���
	// @return	none
	// @date	2013/8/25
	//----------------------------------------------------
	void DrawDebugStage	( CONST UINT numLines, CONST tagTDEBUGVERTEX* pDebugStageVertex );

};

#endif _C_DIRECTX9_DRAW_SYSTEM_H_