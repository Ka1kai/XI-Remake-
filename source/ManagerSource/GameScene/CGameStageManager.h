//----------------------------------------------------
// CGameStageManager Header 
//　ゲームのステージの管理クラス
//
// @author T.Kawashita
//----------------------------------------------------
#ifndef _C_GAME_STAGE_MANAGER_H_
#define _C_GAME_STAGE_MANAGER_H_

#include"CDiceObjManager.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/2D/C2DSpriteAlphaBlend.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/CObjectBase.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"

#define	MAX_STAGE_NUM			( MAX_DICE_NUM )

class CGameStageManager
{
private:
	CObjectBase*		m_pGround;				// Stageの3Dオブジェクト
	LPSTR				m_pResGroundFilePath;	// Stageの3Dオブジェクト用リソース
	
public:
	CGameStageManager	( void );
	~CGameStageManager	( void );

public:
	void	Draw	( void );
	void	Run		( void );
	void	Init	( void );
	void	Uninit	( void );
};

#endif _C_GAME_STAGE_MANAGER_H_