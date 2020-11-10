//----------------------------------------------------
// CMessageBar
//	メッセージバーのオブジェクト
//
// @date	2014/2/5
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_MESSAGE_BAR_H_
#define _C_MESSAGE_BAR_H_

#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/2D/C2DSpriteAlphaBlend.h"

class CMessageBar : public C2DSpriteAlphaBlend
{
public:
	CMessageBar				( void );
	virtual ~CMessageBar	( void );

public:
	//----------------------------------------------------
	// @name	RepositionRight
	// @content	ある位置にバーを移動させる（右）
	// @param	posX		移動させたい位置（中心）
	// @param	speed		速さ
	// @return	bool		移動し終わったかどうか
	// @date	2014/2/5
	//----------------------------------------------------
	bool	RepositionRight	( CONST float posX, CONST float speed );

	//----------------------------------------------------
	// @name	RepositionLeft
	// @content	ある位置にバーを移動させる（左）
	// @param	posX		移動させたい位置（中心）
	// @param	speed		速さ
	// @return	none
	// @date	2014/2/5
	//----------------------------------------------------
	bool	RepositionLeft( CONST float posX, CONST float speed );
};


#endif _C_MESSAGE_BAR_H_