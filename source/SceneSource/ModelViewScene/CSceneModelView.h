//----------------------------------------------------
// CSceneModelView Header 
// ���f���r���[���[�̃V�[��
//
// @author T.Kawashita
//----------------------------------------------------
#ifndef _C_SCENE_MODELVIEW_H_
#define _C_SCENE_MODELVIEW_H_

#include "../../KaiFrameWork/KaiFrameWorkHeader/SceneHeader/CSceneBase.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/SceneHeader/CSceneChange.hpp"

#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CInputMouse.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CInputKeyboard.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9Camera.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9Light.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/2D/C2DSpriteAlphaBlend.h"
#include "../../ObjectSource/GameScene/Particle/CSnowObj.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"

#include "../../ManagerSource/ModelViewScene/CModelViewBackManager.h"
#include "../../ManagerSource/ModelViewScene/CModelViewStage.h"


#define MODEL_CNT (3)
#define CAMERA_DEPTH ( 3.0f )

enum ModelViewState
{
	VIEW_X,
	VIEW_Y,
	VIEW_Z,
	VIEW_NORMAL
};

class CSceneModelView : public CSceneBase
{
private:
	CDirectCamera*		m_pDirectCamera;
	CDirectLight*		m_pDirectLight;

private:
	CObjectBase*		m_pViewObj;

private:
	// Manager
	CModelViewBackManager*	m_pModelViewBackManager;
	CModelViewStage*		m_pModelViewStage;
	CSnowObj*				m_pSnowObjManager;

private:
	ModelViewState			m_eModelViewState;
	bool					m_isTexture;		// �e�N�X�`���̃t���O
	bool					m_isMouseHoil;		// �}�E�X�z�C�[���̃t���O
	bool					m_isMouse;			// �}�E�X�̓����̃t���O
	bool					m_isCull;			// �J�����O�̃t���O
	bool					m_isLight;			// ���C�g�̃t���O
	float					m_degree;			// �J�����̉�]�p�x

public:
	CSceneModelView			 ( void ){}
	CSceneModelView			 ( CSceneChange* changeScene );
	virtual ~CSceneModelView ( void ){}

public:
	void Initialize ( void )	override;
	void Finalize	( void )	override;
	void Run		( void )	override;
	void Draw		( void )	override;
	bool Load		( void )	override;

public:
	void UpdatePict ( void );	
	void RotationCamera		( DWORD direction );	// �J�����̉�]
	void DrawModeChange		( void );				// �`�惂�[�h�ύX
	void CalcDepthCamera	( void );				// �J�����̉��s����
	void CalcCameraPos		( void );				// �J�����̈ʒu����

	void RotationModel		( void );				// ���f���̉�]
};

#endif _C_SCENE_MODELVIEW_H_