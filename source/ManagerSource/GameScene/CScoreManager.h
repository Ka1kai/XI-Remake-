//----------------------------------------------------
// CScoreManager
//	�Q�[���̃X�R�A�̃}�l�[�W���[
//  ( �Q�[�����̃X�R�A���Ǘ����邾�� )
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
	CScore*			m_pScore;		// �X�R�A�W�v�p

	// �X�R�A�\���p
	C2DSpriteRHW*	m_pScoreValue;		// ����
	LPSTR			m_pResScoreValue;

	C2DSpriteRHW*	m_pScoreDigit;		// ����
	LPSTR			m_pResScoreDigit;

public:
	// �X�R�A�̎擾
	CScore*		GetScore	( void )
	{
		return m_pScore;
	}

public:
	CScoreManager	( void );	// �R���X�g���N�^	
	~CScoreManager	( void );	// �f�X�g���N�^	


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