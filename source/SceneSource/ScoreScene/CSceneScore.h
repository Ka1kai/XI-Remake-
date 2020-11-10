//----------------------------------------------------
// CSceneScore 
//	スコア表示シーン
//
// @date	2014/2/20
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_SCENE_SCORE_H_
#define _C_SCENE_SCORE_H_

#include "../../KaiFrameWork/KaiFrameWorkHeader/SceneHeader/CSceneBase.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/SceneHeader/CSceneChange.hpp"

#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CInputKeyboard.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/WindowsHeader/CJoyStick.hpp"

#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourcePath.hpp"
#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"

#include "../../UserSource/CUserManager.h"

class CSceneScore : public CSceneBase
{
private:
	// Result文字
	C2DSpriteRHW	*m_pHighScoreValue;
	LPSTR			m_pResHighScoreValueFilePath;

	// スコア数字
	LPSTR			m_pResScoreDigitFilePath;

	// Score
	C2DSpriteRHW	*m_pScoreValue;
	LPSTR			m_pResScoreValueFilePath;
	C2DSpriteRHW	*m_pScoreDigit;

	// MaxChain
	C2DSpriteRHW	*m_pMaxChainValue;
	LPSTR			m_pResMaxChainValueFilePath;
	C2DSpriteRHW	*m_pMaxChainDigit;

	// １～６用
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


	int				m_scoreDigitNum;
	int				m_maxChainDigitNum;
	int				m_oneDigitNum;
	int				m_twoDigitNum;
	int				m_threeDigitNum;
	int				m_fourDigitNum;
	int				m_fiveDigitNum;
	int				m_sixDigitNum;

public:
	CSceneScore		( void );		// コンストラクタ
	CSceneScore		( CSceneChange* sceneChange );
	~CSceneScore	( void );		// デストラクタ

	void	Initialize	( void ) override;
	void	Finalize	( void ) override;
	void	Run			( void ) override;
	void	Draw		( void ) override;
	bool	Load		( void ) override;
};


#endif _C_SCENE_SCORE_H_