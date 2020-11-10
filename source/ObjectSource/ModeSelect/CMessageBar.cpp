
#include "CMessageBar.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CMessageBar::CMessageBar( void )
{
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CMessageBar::~CMessageBar( void )
{
}

//----------------------------------------------------
// 指定位置にバーを移動
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
// 指定位置にバーを移動
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

