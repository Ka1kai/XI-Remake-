//----------------------------------------------------
// C2DSpriteAlphaBlend
//	���u�����h����2DObject�̂��߂̂���
// 
// @date	2013/8/15
// @author  T.Kawashita
//----------------------------------------------------
#ifndef _C_GRAPHICS_2D_ALPHABLEND_H_
#define _C_GRAPHICS_2D_ALPHABLEND_H_

#include "C2DSpriteRHW.h"

//----------------------------------------------------
// �t�F�[�h�̃X�e�[�^�X
//----------------------------------------------------
enum eFadeState
{
	FADE_IN,
	FADE_OUT,
	FADE_STOP
};

class C2DSpriteAlphaBlend : public C2DSpriteRHW
{
private:
	eFadeState		m_eFadeState;

public:
	C2DSpriteAlphaBlend			( void );
	C2DSpriteAlphaBlend			( eFadeState fadeState );
	virtual ~C2DSpriteAlphaBlend	( void );

public:
	//----------------------------------------------------
	// @name	Fade
	// @content	FadeIn��FadeOut���J��Ԃ��s���i�i�v�I�j
	// @param	alpha		0 �` 255 �͈̔�
	// @return	none
	// @date	2013/8/15
	//----------------------------------------------------	
	void	Fade	( CONST USHORT alpha );

	//----------------------------------------------------
	// @name	Fade
	// @content	FadeIn��FadeOut���J��Ԃ��s���i�i�v�I�E�͈͎w��j
	// @param	maxAlpha	���̍ő�
	// @param	minAlpha	���̍ŏ�
	// @param	alpha		���𑝌��������
	// @return	none
	// @date	2013/8/15	
	//----------------------------------------------------
	void	Fade	( CONST USHORT maxAlpha, CONST USHORT minAlpha, CONST USHORT alpha );

	//----------------------------------------------------
	// @name	Fade
	// @content	FadeIn��Fadeout���J��Ԃ��s���i�i�v�I�E�~�߂�l�w��j
	// @param	maxAlpha	���̍ő�
	// @param	minAlpha	���̍ŏ�
	// @param	alpha		���𑝌��������
	// @param	stopCnt		�~�߂�l
	// @return	none
	// @date	2013/8/16
	//----------------------------------------------------
	void	Fade	( CONST USHORT maxAlpha, CONST USHORT minAlpha, CONST USHORT alpha, CONST USHORT stopCnt );

	//----------------------------------------------------
	// @name	FadeIn
	// @content	�t�F�[�h�C���̂�	
	// @param	subAlpha	���炷��
	// @return	none
	// @date	2013/8//16
	//----------------------------------------------------
	bool	FadeIn	( CONST USHORT subAlpha );

	//----------------------------------------------------
	// @name	FadeIn
	// @content �t�F�[�h�C���̂݁i�ǂ��܂Ō��炷�����w��j
	// @param	subAlpha	���炷��
	// @param	minAlpha	���炷�͈�
	// @return	none
	// @date	2013/8/16
	//----------------------------------------------------
	bool	FadeIn	( CONST USHORT subAlpha, CONST USHORT minAlpha );

	//----------------------------------------------------
	// @name	FadeOut
	// @content	�t�F�[�h�A�E�g�̂�
	// @param	addAlpha	���₷��
	// @return	none
	// @date	2013/8/16
	//----------------------------------------------------
	bool	FadeOut	( CONST USHORT addAlpha );

	//----------------------------------------------------
	// @name	FadeOut
	// @content	�t�F�[�h�A�E�g�̂݁i�ǂ��܂ő��₷�����w��j
	// @param	addAlpha	���₷��
	// @param	maxAlpha	���₷�͈�
	// @return	none
	// @date	2013/8/16
	//----------------------------------------------------
	bool	FadeOut	( CONST USHORT addAlpha, CONST USHORT maxAlpha );		

};

#endif _C_GRAPHICS_2D_ALPHABLEND_H_