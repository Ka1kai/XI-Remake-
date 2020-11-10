//----------------------------------------------------
// CModelViewStage 
//　モデルビューのステージ管理クラス
//
// @author T.Kawashita
//----------------------------------------------------
#ifndef _C_MODELVIEW_STAGE_MANAGER_H_
#define _C_MODELVIEW_STAGE_MANAGER_H_

#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"

#include "../../KaiFrameWork/KaiFrameWorkHeader/DebugHeader/CDebugStage.h"

class CModelViewStage
{
private:
	CDebugStage		*m_pStage;

public:
	CModelViewStage		( void );
	~CModelViewStage	( void );

public:
	void	Init		( void );
	void	Uninit		( void );
	void	Draw		( void );
};

#endif _C_MODELVIEW_STAGE_MANAGER_H_