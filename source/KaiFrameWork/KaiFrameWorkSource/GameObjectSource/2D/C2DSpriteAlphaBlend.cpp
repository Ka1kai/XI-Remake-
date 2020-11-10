
#include "../../../KaiFrameWorkHeader/GameObjectHeader/2D/C2DSpriteAlphaBlend.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
C2DSpriteAlphaBlend::C2DSpriteAlphaBlend( void )
{
	m_eFadeState = eFadeState::FADE_IN;
}

//----------------------------------------------------
// コンストラクタ(フェードのステータスを設定）
//----------------------------------------------------
C2DSpriteAlphaBlend::C2DSpriteAlphaBlend( eFadeState fadeState )
{
	m_eFadeState = fadeState;
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
C2DSpriteAlphaBlend::~C2DSpriteAlphaBlend( void )
{
}

//----------------------------------------------------
// FadeInとFadeOutを繰り返し行う(永久的)
// @data none
//----------------------------------------------------
void C2DSpriteAlphaBlend::Fade ( const unsigned short alpha )
{
	switch( m_eFadeState )
	{
	case FADE_IN:
		if( FadeIn( alpha ) )
		{
			m_eFadeState = FADE_OUT;
		}
		break;
	
	case FADE_OUT:
		if( FadeOut( alpha ) )
		{
			m_eFadeState = FADE_IN;
		}
		break;
	}
}

//----------------------------------------------------
// FadeInとFadeOutを繰り替えし行う(永久的)
// @data 最大と最少
//----------------------------------------------------
void C2DSpriteAlphaBlend::Fade( const unsigned short maxAlpha,const unsigned short minAlpha, const unsigned short alpha )
{
	switch( m_eFadeState )
	{
	case FADE_IN:
		if( FadeIn( alpha,minAlpha ) )
		{
			m_eFadeState = FADE_OUT;
		}
		break;
	
	case FADE_OUT:
		if( FadeOut( alpha,maxAlpha ) )
		{
			m_eFadeState = FADE_IN;
		}
		break;
	}
}

//----------------------------------------------------
// FadeInとFadeoutを繰り返し行う(永久的)
// @data max min alphaの量 止める値
// @overload
//----------------------------------------------------
void C2DSpriteAlphaBlend::Fade( const unsigned short maxAlpha,const unsigned short minAlpha, const unsigned short alpha, const unsigned short stopCnt )
{
	switch( m_eFadeState )
	{
	case FADE_IN:
		if( FadeIn( alpha,minAlpha ) )
		{
			m_eFadeState = FADE_OUT;
		}
		break;
	
	case FADE_OUT:
		if( FadeIn( alpha,maxAlpha ) )
		{
			m_eFadeState = FADE_IN;
		}
		break;

	case FADE_STOP:
		break;
	}
}

//----------------------------------------------------
// FadeIn(出現)
// @data 減らす量
// @overload
//----------------------------------------------------
bool C2DSpriteAlphaBlend::FadeIn( const unsigned short subAlpha )
{
	int alpha;
	alpha = this->GetAlpha();

	if( alpha > 0 ) 
	{
		alpha = alpha - subAlpha;
		this->SetDiffuse( 255,255,255,alpha );
	
		return false;
	}

	return true;
}

//----------------------------------------------------
// FadeIn(範囲指定で出現)
// @data 減らす量 減らす最大値 
// @overload
//----------------------------------------------------
bool C2DSpriteAlphaBlend::FadeIn( const unsigned short subAlpha, const unsigned short minAlpha )
{
	int alpha;
	alpha = this->GetAlpha();
	if( alpha > minAlpha )
	{
		alpha = alpha - subAlpha;
		this->SetDiffuse( 255,255,255,alpha );
		
		return false;
	}

	return true;
}

//----------------------------------------------------
// FadeOut(消滅) 
// @data 増やす量
// @overload
//----------------------------------------------------
bool C2DSpriteAlphaBlend::FadeOut( const unsigned short addAlpha )
{
	int alpha;
	alpha = this->GetAlpha();

	if( alpha < 255 )
	{
		alpha = alpha + addAlpha;
		this->SetDiffuse( 0,0,0,alpha );
		return false;
	}

	return true;
}

//----------------------------------------------------
// FadeOut(範囲指定で消滅) 
// @data 増やす量 増やす最大値
// @overload
//----------------------------------------------------
bool C2DSpriteAlphaBlend::FadeOut( const unsigned short addAlpha, const unsigned short maxAlpha )
{
	int alpha;
	alpha = this->GetAlpha();

	if( alpha < maxAlpha )
	{
		alpha = alpha + addAlpha;
		this->SetDiffuse( 255,255,255,alpha );

		return false;
	}

	return true;
}
