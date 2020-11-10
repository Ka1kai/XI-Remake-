#ifndef _WINMAIN_H_
#define _WINMAIN_H_

#if defined(DEBUG) || defined(_DEBUG)
#include<crtdbg.h>
#define	DEBUG_INSTANCE
#endif // _DEBUG

// �����w�b�_�ǂݍ���
#include <Windows.h>

// �O���w�b�_�ǂݍ���
#include "../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CWindowSystem.h"
#include "../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9FrameWork.h"
#include "../KaiFrameWork/KaiFrameWorkHeader/SystemHeader/CFpsControl.hpp"

#include "../KaiFrameWork/KaiFrameWorkHeader/DebugHeader/CDebugConsole.hpp"
#include "../KaiFrameWork/KaiFrameWorkHeader/SceneHeader/CSceneManager.h"

#include "../SceneSource/DebugScene/CDebugMode.h"

#include "../MySQLSource/CMySQLManager.hpp"


//----------------------------------------------------
// @name	GameMain
// @content	�Q�[���̃��C���֐�
// @param	none
// @return	none
// @date	2013/5/10
//----------------------------------------------------
void GameMain	(void);

//----------------------------------------------------
// @name	UninitGame
// @content	�Q�[���̏I���֐�
// @param	none
// @return	none
// @date	2013/5/10
//----------------------------------------------------
void UninitGame	(void);

#endif _WINMAIN_H_