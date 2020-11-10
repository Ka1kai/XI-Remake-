//----------------------------------------------------
// C2DSpriteAlphaBlend
//	αブレンドする2DObjectのためのもの
// 
// @date	2013/8/15
// @author  T.Kawashita
//----------------------------------------------------
#ifndef _C_GRAPHICS_2D_ALPHABLEND_H_
#define _C_GRAPHICS_2D_ALPHABLEND_H_

#include "C2DSpriteRHW.h"

//----------------------------------------------------
// フェードのステータス
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
	// @content	FadeInとFadeOutを繰り返し行う（永久的）
	// @param	alpha		0 ～ 255 の範囲
	// @return	none
	// @date	2013/8/15
	//----------------------------------------------------	
	void	Fade	( CONST USHORT alpha );

	//----------------------------------------------------
	// @name	Fade
	// @content	FadeInとFadeOutを繰り返し行う（永久的・範囲指定）
	// @param	maxAlpha	αの最大
	// @param	minAlpha	αの最少
	// @param	alpha		αを増減させる量
	// @return	none
	// @date	2013/8/15	
	//----------------------------------------------------
	void	Fade	( CONST USHORT maxAlpha, CONST USHORT minAlpha, CONST USHORT alpha );

	//----------------------------------------------------
	// @name	Fade
	// @content	FadeInとFadeoutを繰り返し行う（永久的・止める値指定）
	// @param	maxAlpha	αの最大
	// @param	minAlpha	αの最少
	// @param	alpha		αを増減させる量
	// @param	stopCnt		止める値
	// @return	none
	// @date	2013/8/16
	//----------------------------------------------------
	void	Fade	( CONST USHORT maxAlpha, CONST USHORT minAlpha, CONST USHORT alpha, CONST USHORT stopCnt );

	//----------------------------------------------------
	// @name	FadeIn
	// @content	フェードインのみ	
	// @param	subAlpha	減らす量
	// @return	none
	// @date	2013/8//16
	//----------------------------------------------------
	bool	FadeIn	( CONST USHORT subAlpha );

	//----------------------------------------------------
	// @name	FadeIn
	// @content フェードインのみ（どこまで減らすかを指定）
	// @param	subAlpha	減らす量
	// @param	minAlpha	減らす範囲
	// @return	none
	// @date	2013/8/16
	//----------------------------------------------------
	bool	FadeIn	( CONST USHORT subAlpha, CONST USHORT minAlpha );

	//----------------------------------------------------
	// @name	FadeOut
	// @content	フェードアウトのみ
	// @param	addAlpha	増やす量
	// @return	none
	// @date	2013/8/16
	//----------------------------------------------------
	bool	FadeOut	( CONST USHORT addAlpha );

	//----------------------------------------------------
	// @name	FadeOut
	// @content	フェードアウトのみ（どこまで増やすかを指定）
	// @param	addAlpha	増やす量
	// @param	maxAlpha	増やす範囲
	// @return	none
	// @date	2013/8/16
	//----------------------------------------------------
	bool	FadeOut	( CONST USHORT addAlpha, CONST USHORT maxAlpha );		

};

#endif _C_GRAPHICS_2D_ALPHABLEND_H_