//----------------------------------------------------
// CSceneManager Header 
//	Scene���Ǘ�����
//
// @date	2013/6/15
// @author  T.Kawashita
//----------------------------------------------------
#ifndef _C_SCENE_MANAGER_H_
#define _C_SCENE_MANAGER_H_

#include "CSceneChange.hpp"
#include "CSceneBase.hpp"

#include "../../../SceneSource/GameScene/CSceneGame.h"
#include "../../../SceneSource/ResultScene/CSceneResult.h"
#include "../../../SceneSource/GameTitleScene/CSceneTitle.h"
#include "../../../SceneSource/ModeSelectScene/CSceneModeSelect.h"
#include "../../../SceneSource/ScoreScene/CSceneScore.h"
#include "../../../SceneSource/ModelViewScene/CSceneModelView.h"
#include "../../../SceneSource/DebugScene/CSceneDebug.h"

#include "../SystemHeader/CPthread.hpp"

class CSceneManager : public CSceneChange
{
private:
	CSceneBase* m_pScene;			// �V�[���Ǘ��ϐ�
	eSceneState m_nowScene;			// ���݂̃V�[���Ǘ��ϐ�
    eSceneState m_nextScene;		// ���̃V�[���Ǘ��ϐ�

	bool		m_isLoad;			// ���[�h�t���O
//	CPthread*	m_pPthread;			// ���[�h�p�X���b�h

private:
	//----------------------------------------------------
	// Scene���C���X�^���X������
	//----------------------------------------------------
	void Update	(void);

public:
    CSceneManager	( eSceneState state );
	CSceneManager	( void );
	~CSceneManager	( void );

public:
    void   Initialize	( void );			// ������
    void   Finalize		( void );			// �I������
    void   Run			( void );			// �X�V
    void   Draw			( void );			// �`��
	static void* ThreadLoad ( void* func );	// �X���b�h�̂��߂̃��[�h�֐�
	bool   Load			( void );			// ���[�h
	void   DrawLoading	( void );			// nowloading�`��

public:
    //----------------------------------------------------
	// �V�[���ύX�֐�
	// @nextScene
	//----------------------------------------------------
	void ChangeScene( eSceneState NextScene ) override;
};

#endif _C_SCENE_MANAGER_H_