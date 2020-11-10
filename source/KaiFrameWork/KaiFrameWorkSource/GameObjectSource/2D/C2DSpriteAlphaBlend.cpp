
#include "../../../KaiFrameWorkHeader/GameObjectHeader/2D/C2DSpriteAlphaBlend.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
C2DSpriteAlphaBlend::C2DSpriteAlphaBlend( void )
{
	m_eFadeState = eFadeState::FADE_IN;
}

//----------------------------------------------------
// �R���X�g���N�^(�t�F�[�h�̃X�e�[�^�X��ݒ�j
//----------------------------------------------------
C2DSpriteAlphaBlend::C2DSpriteAlphaBlend( eFadeState fadeState )
{
	m_eFadeState = fadeState;
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
C2DSpriteAlphaBlend::~C2DSpriteAlphaBlend( void )
{
}

//----------------------------------------------------
// FadeIn��FadeOut���J��Ԃ��s��(�i�v�I)
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
// FadeIn��FadeOut���J��ւ����s��(�i�v�I)
// @data �ő�ƍŏ�
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
// FadeIn��Fadeout���J��Ԃ��s��(�i�v�I)
// @data max min alpha�̗� �~�߂�l
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
// FadeIn(�o��)
// @data ���炷��
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
// FadeIn(�͈͎w��ŏo��)
// @data ���炷�� ���炷�ő�l 
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
// FadeOut(����) 
// @data ���₷��
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
// FadeOut(�͈͎w��ŏ���) 
// @data ���₷�� ���₷�ő�l
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
