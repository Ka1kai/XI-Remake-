//----------------------------------------------------
// CSceneBase Class
//	Scene�̊��N���X
//	 �e��V�[���ɔh��������
//
// @date	2013/6/10
// @auter	T.Kawashita
//----------------------------------------------------
#ifndef _C_SCENE_BASE_H_
#define _C_SCENE_BASE_H_

#include "CSceneChange.hpp"

#include "../DirectX9Header/CDirectX9DrawSystem.h"
#include "../DirectX9Header/CDirectX9Camera.h"

class CSceneBase
{
protected:
    CSceneChange* mSceneChanger;    // �N���X���L���ɃV�[���؂�ւ���`����C���^�[�t�F�C�X

public:
	// �R���X�g���N�^
    CSceneBase( CSceneChange* changer )
	{
		mSceneChanger = changer;
	}
	CSceneBase(){}
    virtual ~CSceneBase(){}

public:
    virtual void Initialize(){}			// ����������
	virtual void Finalize(){}			// �I������
    virtual void Run() {}				// �X�V����
	virtual void Draw(){}				// �`�揈��
	virtual bool Load(){return true;}	// ���[�h����
};

#endif _C_SCENE_BASE_H_