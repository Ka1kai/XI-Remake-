#ifndef _WINMAIN_H_
#define _WINMAIN_H_

#if defined(DEBUG) || defined(_DEBUG)
#include<crtdbg.h>
#define	DEBUG_INSTANCE
#endif // _DEBUG

// 内部ヘッダ読み込み
#include <Windows.h>

// 外部ヘッダ読み込み
#include "../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CWindowSystem.h"
#include "../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9FrameWork.h"
#include "../KaiFrameWork/KaiFrameWorkHeader/SystemHeader/CFpsControl.hpp"

#include "../KaiFrameWork/KaiFrameWorkHeader/DebugHeader/CDebugConsole.hpp"
#include "../KaiFrameWork/KaiFrameWorkHeader/SceneHeader/CSceneManager.h"

#include "../SceneSource/DebugScene/CDebugMode.h"

#include "../MySQLSource/CMySQLManager.hpp"


//----------------------------------------------------
// @name	GameMain
// @content	ゲームのメイン関数
// @param	none
// @return	none
// @date	2013/5/10
//----------------------------------------------------
void GameMain	(void);

//----------------------------------------------------
// @name	UninitGame
// @content	ゲームの終了関数
// @param	none
// @return	none
// @date	2013/5/10
//----------------------------------------------------
void UninitGame	(void);

#endif _WINMAIN_H_