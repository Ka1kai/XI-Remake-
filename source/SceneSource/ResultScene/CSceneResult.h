//----------------------------------------------------
// CSceneResult Header 
//	���U���g�V�[��
//
// @date	2014/2/14
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_SCENE_RESULT_H_
#define _C_SCENE_RESULT_H_

#include "../../KaiFrameWork/KaiFrameWorkHeader/SceneHeader/CSceneBase.hpp"

#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CInputKeyboard.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CJoyStick.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/2D/C2DSpriteAlphaBlend.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"
#include "../../UserSource/CUserManager.h"

class CSceneResult : public CSceneBase
{
private:
	// Result����
	C2DSpriteRHW	*m_pResultValue;
	LPSTR			m_pResResultValueFilePath;

	// �X�R�A����
	LPSTR			m_pResScoreDigitFilePath;

	// Score
	C2DSpriteRHW	*m_pScoreValue;
	LPSTR			m_pResScoreValueFilePath;
	C2DSpriteRHW	*m_pScoreDigit;

	// MaxChain
	C2DSpriteRHW	*m_pMaxChainValue;
	LPSTR			m_pResMaxChainValueFilePath;
	C2DSpriteRHW	*m_pMaxChainDigit;

	// �P�`�U�p
	C2DSpriteRHW	*m_pOnePip;
	LPSTR			m_pResOneTextureFilePath;
	C2DSpriteRHW	*m_pOnePipDigit;

	C2DSpriteRHW	*m_pTwoPip;
	LPSTR			m_pResTwoTextureFilePath;
	C2DSpriteRHW	*m_pTwoPipDigit;

	C2DSpriteRHW	*m_pThreePip;
	LPSTR			m_pResThreeTextureFilePath;
	C2DSpriteRHW	*m_pThreePipDigit;

	C2DSpriteRHW	*m_pFourPip;
	LPSTR			m_pResFourTextureFilePath;
	C2DSpriteRHW	*m_pFourPipDigit;

	C2DSpriteRHW	*m_pFivePip;
	LPSTR			m_pResFiveTextureFilePath;
	C2DSpriteRHW	*m_pFivePipDigit;

	C2DSpriteRHW	*m_pSixPip;
	LPSTR			m_pResSixTextureFilePath;
	C2DSpriteRHW	*m_pSixPipDigit;

	C2DSpriteRHW	*m_pPushEnter;
	LPSTR			m_pResPushEnterFilePath;
		
	// ���u�����h���������邽�߂̂���
	C2DSpriteAlphaBlend	*m_pBack;
	bool				m_isFade;

	int				m_scoreDigitNum;
	int				m_maxChainDigitNum;
	int				m_oneDigitNum;
	int				m_twoDigitNum;
	int				m_threeDigitNum;
	int				m_fourDigitNum;
	int				m_fiveDigitNum;
	int				m_sixDigitNum;

public:
	CSceneResult		( CSceneChange* change );
	CSceneResult		( void );
	~CSceneResult		( void );

public:
	void Initialize	( void ) override;		// ����������
    void Finalize	( void ) override;		// �I������
    void Run		( void ) override;		// �X�V����
    void Draw		( void ) override;		// �`�揈��
	bool Load		( void ) override;		// ���[�h����

};

#endif _C_SCENE_RESULT_H_