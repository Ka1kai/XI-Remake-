//----------------------------------------------------
// CSceneTitle Class 
//  Titleの画面シーンクラス
//
// @auter T.Kawashita
//----------------------------------------------------
#ifndef _C_SCENE_TITLE_H_
#define _C_SCENE_TITLE_H_

#include "../../KaiFrameWork/KaiFrameWorkHeader/SceneHeader/CSceneBase.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/SceneHeader/CSceneChange.hpp"

#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9Camera.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9Light.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CJoyStick.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CInputKeyboard.hpp"

#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/2D/C2DSpriteAlphaBlend.h"

// Manager
#include "../../ManagerSource/TitleScene/CTitleBackManager.h"
#include "../../ManagerSource/TitleScene/CTitleSoundManager.h"
#include "../../UserSource/CUserManager.h"

class CSceneTitle : public CSceneBase
{
private:
	CDirectCamera			*m_pDirectCamera;
	CDirectLight			*m_pDirectLight;

// Managerクラス
private:
	CTitleBackManager		*m_pTitleBackManager;
	CTitleSoundManager		*m_pTitleSoundManager;

public:
	CSceneTitle			 ( void ){}
	CSceneTitle			 ( CSceneChange* change );
	virtual ~CSceneTitle ( void );

public:
	void Initialize	( void ) override;
	void Finalize	( void ) override;
	void Run		( void ) override;
	void Draw		( void ) override;
	bool Load		( void ) override;

};

#endif _C_SCENE_TITLE_H_