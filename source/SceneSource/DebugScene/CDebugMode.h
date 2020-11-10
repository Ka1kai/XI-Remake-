//----------------------------------------------------
// CDebugMode 
//	�Q�[���̃f�o�b�O�Ɏg���V�[��	
//
// @date	2014/1/13
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_DEBUG_MODE_H_
#define _C_DEBUG_MODE_H_

#include <Windows.h>

#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/2D/C2DSpriteAlphaBlend.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/3D/C3DObjectShape.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CInputKeyboard.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CJoyStick.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9Camera.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourcePath.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceXFont.h"

#define DEBUG_NUM					( 4 )
#define SELECT_DEBUG_NUM			( 6 )
#define DEFAULT_DEBUG_MODE_COLOR	D3DXCOLOR( 255, 255, 255, 255 )
#define SELECT_DEBUG_MODE_COLOR		D3DXCOLOR( 0, 255, 0, 255 )
#define CHEACK_DEBUG_MODE_COLOR		D3DXCOLOR( 255, 0, 0, 255 )

// �f�o�b�O�̃t�H���g
typedef struct tFONTINFO
{
	bool		cheack;
	D3DXCOLOR   color;
}TFONTINFO;

// �f�o�b�O�̃X�e�[�^�X
typedef enum DEBUGSTATUS
{
	FPS,
	COLLISION_BOX,
	GAME_TIME,
	EXIT_DEBUG
}eDebugStatus;

typedef struct tDEBUGDICEBOX
{
	bool				isDice;		// ��������Ă��邩
	C3DObjectShape		diceBox;	// AABB�{�b�N�X�\���p�{��
}TDEBUGDICEBOX;

class CDebugMode
{
public:
	// �f�o�b�O���[�h��ʗp2D�|���S��
	static C2DSpriteRHW			m_pDebugMode;
	static LPSTR				m_pDebugModeTexturePath;

	// �f�o�b�O���[�h�I���p�t���O
	static bool					m_isDebugMode;

	// �����蔻��m�F�p�̃{�b�N�X
	static C3DObjectShape		m_pPlayerBox;
	static TDEBUGDICEBOX		m_pDiceBox[49];

	// �f�o�b�O�̒l
	static float*				m_pFps;						// FPS
	static int*					m_pTime;					// �Q�[���̎���

	static TFONTINFO			m_font[ SELECT_DEBUG_NUM ];	// �f�o�b�O�̃t�H���g���
	static int					m_fontIndex;				// �f�o�b�O�̑I���C���f�b�N�X�ԍ�
	static bool					m_debugOnOff;				// �f�o�b�O��OnOFF�@�\��������̂̃t���O

	// �f�o�b�O�̍��ڂ��Ǘ�
	static int					m_leftRightIndexDir;		// ���E�̌���
	static int					m_upDownIndexDir;			// �㉺�̌���
	static int					m_debugIndex;				// �f�o�b�O�̍��ڃC���f�b�N�X�ԍ�
	static eDebugStatus			m_eDebugStatus;				// ���݂̑I�����ǂ̃f�o�b�O�̍��ڂ�

private:
	// �e��t���O
	static bool					m_isCollisionBox;			// �����蔻��`�F�b�N�p�{�b�N�X�\���t���O
	static bool					m_isFps;					// FPS�\���t���O

private:
	// �R���X�g���N�^
	CDebugMode				( void );
	CDebugMode				( CONST CDebugMode& debugMode ){}	// �R�s�[�R���X�g���N�^��h��
	CDebugMode	operator=	( CONST CDebugMode& debugMode ){}	// �����o�̑����h��

public:
	// �f�X�g���N�^
	~CDebugMode					( void );

	//----------------------------------------------------
	// ������
	//----------------------------------------------------
	static bool Load			( void );
	static bool	Init			( void );
	static void Set				( int* pTime );
	static bool InitDebugMode	( void );

	//----------------------------------------------------
	// ����
	//----------------------------------------------------
	static void	Run				( CDirectCamera* camera );
	static void RunDebugMode	( void );
	static void	RunRight		( void );	// �E����
	static void RunLeft			( void );	// ������
	static void	RunUp			( void );	// �����
	static void RunDown			( void );	// ������
	static void RunEnter		( void );	// Enter����

	//----------------------------------------------------
	// �`��
	//----------------------------------------------------
	static void	Draw			( void );
	static void DrawDebugMode	( void );

	//----------------------------------------------------
	// �I��
	//----------------------------------------------------
	static bool	Uninit			 ( void );

	//----------------------------------------------------
	// @name	DebugONOFF
	// @content	�f�o�b�O��ON/OFF�̏���
	// @param	isOnOff		ON/OFF
	// @param	font*		font�f�[�^1
	// @param	font2*		font�f�[�^2
	// @return	none
	// @date	2014/1/22
	//----------------------------------------------------
	static void DebugONOFF		( bool isOnOff, TFONTINFO* font, TFONTINFO* font2 );

	//----------------------------------------------------
	// @name	DigitUpDown
	// @content	�l�̒���
	// @param	pOut		�������I������l	
	// @param	pDigit		�����������l
	// @param	value		���������
	// @return	int*		�������I������l
	// @date	2014/1/22
	//----------------------------------------------------
	static int* DigitUpDown		( int* pOut, int* pDigit, int value );
};

#endif _C_DEBUG_MODE_H_