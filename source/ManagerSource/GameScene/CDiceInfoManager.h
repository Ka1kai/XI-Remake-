//----------------------------------------------------
// CDiceInfoManager 
//	���ݏ���Ă���_�C�X��\������}�l�[�W��
//
// @date	2014/2/9
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_DICE_INFO_MANAGER_H_
#define _C_DICE_INFO_MANAGER_H_

#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"

#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/2D/C2DSpriteAlphaBlend.h"
#include "../../ObjectSource/GameScene/CDiceInfoObj.h"

class CDiceInfoManager
{
private:
	C2DSpriteRHW*		m_pInfo;
	LPSTR				m_pResInfoFilePath;

	CDiceInfoObj*		m_pDiceInfo;				// �`��p�̖{�̂̃A�h���X
	LPSTR				m_pResInfoDiceFilePath;		// �`��p�̖{�̂̃t�@�C���p�X


public:
	CDiceInfoManager	( void );	// �R���X�g���N�^
	~CDiceInfoManager	( void );	// �f�X�g���N�^

public:
	void		SetInfoDice	( CONST D3DXMATRIX* mainDiceWorldMtx );
	bool		Init	( void );
	bool		Uninit	( void );
	void		Draw	( void );

	void		SetIsExist	( bool isExist )
	{
		m_pDiceInfo->SetIsExist( isExist );
	}

public:
	void		BrightChange	( bool isBright )
	{
		if( isBright == true )
		{
			m_pInfo->SetDiffuse( 255, 255, 255, 255 );
		}
		else 
		{
			m_pInfo->SetDiffuse( 100, 100, 100, 255 );
		}
	}
};


#endif _C_DICE_INFO_MANAGER_H_