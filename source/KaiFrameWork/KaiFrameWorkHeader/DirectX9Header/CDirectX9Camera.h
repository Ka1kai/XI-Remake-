//----------------------------------------------------
// CDirectX9Camera 
//	DirectX�̃J�����𐧌䂷��
//
// @date	2013/6/2
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_DIRECTX9_CAMERA_H_
#define _C_DIRECTX9_CAMERA_H_

#include <d3dx9.h>

#include "../../KaiFrameWorkHeader/DirectX9Header/CDirectX9FrameWork.h"

class CDirectCamera
{
private:
	D3DXMATRIX	m_view;			// �r���[�s��
	D3DXMATRIX	m_projection;	// �ˉe�s��
	D3DXMATRIX	m_ortho;		// ���ˉe�s��

	D3DXMATRIX	m_worldMtx;		// �J�����̃��[���h�s��

	D3DXVECTOR3 m_vEye;			// �J�����̈ʒu
	D3DXVECTOR3 m_vAt;			// �J�����̒����_
	D3DXVECTOR3 m_vUp;			// �J�����̌���
public:
	D3DXMATRIX*		GetView	( void )
	{
		return &m_view;
	}
	D3DXVECTOR3*	GetEye	( void )
	{
		return &m_vEye;
	}
	D3DXVECTOR3*	GetAt	( void )
	{
		return &m_vAt;
	}

public:
	CDirectCamera			( void );	
	~CDirectCamera			( void );

public:
	//----------------------------------------------------
	// @name	Init
	// @content	�J�����̏�����
	// @param	windowSizeX		��ʂ�X�T�C�Y
	// @param	windowSizeY		��ʂ�Y�T�C�Y
	// @return	bool			���������s
	// @date	2013/6/3
	// @update	2013/11/18
	//----------------------------------------------------
	bool	Init			( CONST int windowSizeX, CONST int windowSizeY );	

	//----------------------------------------------------
	// @name	Init
	// @content	�J�����̏�����(�ʒu�E�����_�E����)
	// @param	none
	// @return	bool			���������s
	// @date	2013/6/4
	// @update	2013/11/18
	//----------------------------------------------------
	bool	Init			( void );

	//----------------------------------------------------
	// @name	Set
	// @content	�J�������Z�b�g
	// @param	none
	// @return	bool		���������s
	// @date	2013/6/3
	// @update	2013/11/18
	//----------------------------------------------------
	bool	Set				( void );

	//----------------------------------------------------
	// @name	SetPosition
	// @content	�J�����̈ʒu�Z�b�g
	// @param	xPos		�Z�b�g������X���W	
	// @param	yPos		�Z�b�g������Y���W
	// @param	zPos		�Z�b�g������Z���W
	// @return	bool		���������s
	// @date	2013/6/4
	// @update	2013/11/18
	//----------------------------------------------------
	bool	SetPosition		( CONST float xPos, CONST float yPos, CONST float zPos );	

	//----------------------------------------------------
	// @name	SetAt
	// @content	�J�����̒����_�̃Z�b�g
	// @param	xPos		�Z�b�g������X���W
	// @param	yPos		�Z�b�g������Y���W
	// @param	zPos		�Z�b�g������Z���W
	// @return	bool		���������s
	// @date	2013/6/5
	// @update	2013/11/18
	//----------------------------------------------------
	bool	SetAt			( CONST float xPos, CONST float yPos, CONST float zPos );		

	//----------------------------------------------------
	// @name	SetView
	// @content	�J�����̃��[���h�s��̃Z�b�g
	// @param	none
	// @return	BOOL		���������s
	// @date	2013/6/6
	// @update	2013/11/18
	//----------------------------------------------------
	bool	SetView			( void );

	//----------------------------------------------------
	// @name	SetPerspective
	// @content	�`��𓧎����e�ϊ��ɐݒ�
	// @param	none
	// @return	none
	// @date	2013/6/7
	//----------------------------------------------------
	void	SetPerspective	( void )
	{
		LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
		pd3dDevice->SetTransform(D3DTS_PROJECTION,&m_projection);
	}

	//----------------------------------------------------
	// @name	SetOrtho
	// @content	���ˉe�ϊ��ɃZ�ݒ�
	// @param	none
	// @return	none
	// @date	2013/6/7
	//----------------------------------------------------
	void	SetOrtho		( void )
	{
		LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
		pd3dDevice->SetTransform(D3DTS_PROJECTION, &m_ortho);
	}

	//----------------------------------------------------
	// @name	Tracking
	// @content	�Ǐ]�J����(�x�N�g�����l�����Ȃ�)
	// @param	pMtx			��ς��������f���̃��[���h���W	
	// @param	at				���f������̋���
	// @return	none
	// @date	2013/6/10
	// @update	2013/11/18		
	//----------------------------------------------------
	void	Tracking		( CONST D3DXMATRIX* pMtx, CONST float at );		
	
	//----------------------------------------------------
	// @name	Tracking
	// @content	�Ǐ]�����������f���̃x�N�g���𗘗p���Ă̒Ǐ]�J����
	// @param	pMtx			��ς��������f���̃��[���h���W
	// @param	pVec			��ς��������f���̃x�N�g��
	// @param	distance		���f������̃J�����̋���
	// @return	none
	// @date	2013/6/12
	// @update	2013/11/18
	//----------------------------------------------------
	void	Tracking		( CONST D3DXMATRIX* pMtx, CONST D3DXVECTOR3* pVec, CONST float distance );

public:
	//----------------------------------------------------
	// @name	SetBillBoardMat
	// @content	�s����r���{�[�h�p�s��ɕϊ�
	// @return	D3DXMATRIX*		�ύX�����s��	
	// @param	pBillBoardPos	�r���{�[�h�̈ʒu
	// @param	pBillBoardMat	�ϊ��������s��
	// @date	2013/6/20
	// @update	2013/11/18		�ϊ������s���Ԃ�
	//----------------------------------------------------
	D3DXMATRIX* SetBillBoardMtx	( D3DXMATRIX* pBillBoardMtx, CONST D3DXVECTOR3* pBillBoardPos );
	
	//----------------------------------------------------
	// @name	SetBillBoardMat
	// @content	�s����r���{�[�h�p�s��ɕϊ�
	// @param	pBillBoardMat	�ϊ��������s��
	// @param	distance		�J��������̋���
	// @return	D3DXMATRIX*		�ϊ������s��
	// @date	2013/6/21
	// @update	2013/11/18		�ϊ������s���Ԃ�
	//----------------------------------------------------
	D3DXMATRIX*	SetBillBoardMtx	( D3DXMATRIX* pBillBoardMtx, CONST float distance ); 

private:
	//----------------------------------------------------
	// @name	CalcQuaternion
	// @content	�N�H�[�^�j�I���̌v�Z
	// @param	pAxis			��]�����x�N�g��
	// @param	degree			��]�p�x
	// @return	bool			���������s
	// @date	2013/11/18
	//----------------------------------------------------
	bool	CalcLocalQuaternion		( CONST D3DXVECTOR3* pAxis, CONST float degree );

public:
	void	LocalRotationQuaterX( CONST float degree );		// ���[�J���N�H�[�^�j�I��X��]
	void	LocalRotationQuaterY( CONST float degree );		// ���[�J���N�H�[�^�j�I��Y��]
	void	LocalRotationQuaterZ( CONST float degree );		// ���[�J���N�H�[�^�j�I��Z��]

	//----------------------------------------------------
	// @name	LocalRotationQuater
	// @content	���[�J���C�ӎ��N�H�[�^�j�I����]
	// @param	pVec			�C�ӂ̎�
	// @param	degree			��]�p�x
	// @return	none
	// @date	2013/7/30
	// @update	2013/11/18
	//----------------------------------------------------
	void	LocalRotationQuater( CONST D3DXVECTOR3* pVec, CONST float degree );

};

#endif _C_DIRECTX9_CAMERA_H_