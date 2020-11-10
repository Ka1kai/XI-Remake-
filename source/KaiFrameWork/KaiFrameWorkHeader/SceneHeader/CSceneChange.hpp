//----------------------------------------------------
// CSceneChangeClass 
//	Scene��ύX���邽�߂̃N���X
//
// @date	2013/6/13
// @author  T.Kawashita
//----------------------------------------------------
#ifndef _C_SCENE_CHANGE_H_
#define _C_SCENE_CHANGE_H_

typedef enum 
{
	eSceneTitle,
    eSceneModeSelect,	// ���[�h�Z���N�g���
	eSceneHighScore,	// �X�R�A�\����� 
    eSceneGame,			// �Q�[�����
    eSceneResult,		// ���U���g
	eSceneConfig,		// �ݒ���
	eSceneModelView,	// ���f���r���[���[
	eSceneDebug,		// �f�o�b�O���

    eScene_None,	    // ����
}eSceneState;

class CSceneChange
{
public:
	CSceneChange(){};
	virtual ~CSceneChange(){}

public:
    virtual void ChangeScene( eSceneState NextScene ) = 0;//�w��V�[���ɕύX����
};

#endif _C_SCENE_CHANGE_H_