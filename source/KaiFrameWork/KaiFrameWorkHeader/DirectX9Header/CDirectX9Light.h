//----------------------------------------------------
// CDirectLight Header 
//�@DirectX�̃J����
//
// @date	2013/5/1
// @author  T.Kawashita
//----------------------------------------------------
#ifndef _C_DIRECTX9_LIGHT_H_
#define _C_DIRECTX9_LIGHT_H_

#include <d3dx9.h>

#include "CDirectX9FrameWork.h"

class CDirectLight
{
private:
	D3DLIGHT9		light;

public:
	CDirectLight			( void );
	virtual ~CDirectLight	( void );

public:
	void	Init			( void );

	//----------------------------------------------------
	// ���C�g��ON OFF
	// @data	true false
	// @return	none
	//----------------------------------------------------
	void	Switch		( bool isLight );

	//----------------------------------------------------
	// ���C�g�̃Z�b�g
	// @data	none
	// @return	none
	//----------------------------------------------------
	void	Set				( void );

	//----------------------------------------------------
	// ���C�g�̈ʒu�Z�b�g
	// @data	xPos,yPos,zPos
	// @return	none
	//----------------------------------------------------
	void	SetPosition		( float xPos,float yPos,float zPos );

	//----------------------------------------------------
	// �X�e�[�W�S�̂̃A���r�G���g����ݒ�
	// @data	ambient
	// @return	none
	//----------------------------------------------------
	void	SetStageAmbient ( DWORD ambient );	

};

#endif _C_DIRECTX9_LIGHT_H_