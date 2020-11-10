
#include "CMessageBar.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CMessageBar::CMessageBar( void )
{
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
CMessageBar::~CMessageBar( void )
{
}

//----------------------------------------------------
// �w��ʒu�Ƀo�[���ړ�
//----------------------------------------------------
bool CMessageBar::RepositionRight( CONST float posX, CONST float speed )
{
	if( m_center.x >= posX )
	{
		return true;
	}

	m_center.x += speed;
	this->SetVertexPos( m_center.x, m_center.y );

	return false;
}

//----------------------------------------------------
// �w��ʒu�Ƀo�[���ړ�
//----------------------------------------------------
bool CMessageBar::RepositionLeft( CONST float posX, CONST float speed )
{
	if( m_center.x <= posX )
	{
		return true;
	}

	m_center.x -= speed;
	this->SetVertexPos( m_center.x, m_center.y );

	return false;
}

