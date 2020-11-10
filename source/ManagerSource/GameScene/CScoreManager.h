//----------------------------------------------------
// CScoreManager
//	ゲームのスコアのマネージャー
//  ( ゲーム中のスコアを管理するだけ )
//
// @date	2014/2/4
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_SCORE_MANAGER_H_
#define _C_SCORE_MANAGER_H_

#include <Windows.h>
#include "../../KaiFrameWork/KaiFrameWorkHeader/DirectX9Header/CDirectX9DrawSystem.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/ResourceHeader/CResourceManager.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/2D/C2DSpriteRHW.h"
#include "../../ObjectSource/CScore.hpp"

#define SCORE_DIGIT_NUM	(7)

class CScoreManager
{
private:
	CScore*			m_pScore;		// スコア集計用

	// スコア表示用
	C2DSpriteRHW*	m_pScoreValue;		// 文字
	LPSTR			m_pResScoreValue;

	C2DSpriteRHW*	m_pScoreDigit;		// 数字
	LPSTR			m_pResScoreDigit;

public:
	// スコアの取得
	CScore*		GetScore	( void )
	{
		return m_pScore;
	}

public:
	CScoreManager	( void );	// コンストラクタ	
	~CScoreManager	( void );	// デストラクタ	


public:
	bool	Init	( void );
	bool	Uninit	( void );
	void	Draw	( void );
	void	Run		( void );

public:
	void	BrightChange	( bool isBright )
	{
		if( isBright == true )
		{
			m_pScoreValue->SetDiffuse( 255, 255, 255, 255 );
			for( int i = 0; i < SCORE_DIGIT_NUM; ++ i ){
				m_pScoreDigit[i].SetDiffuse( 255, 255, 255, 255 );
			}
		}
		else 
		{
			m_pScoreValue->SetDiffuse( 100, 100, 100, 255 );
			for( int i = 0; i < SCORE_DIGIT_NUM; ++ i ){
				m_pScoreDigit[i].SetDiffuse( 100, 100, 100, 255 );
			}
		}
	}
};

#endif _C_SCORE_MANAGER_H_