//----------------------------------------------------
// CMessageBar
//	���b�Z�[�W�o�[�̃I�u�W�F�N�g
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
	// @content	����ʒu�Ƀo�[���ړ�������i�E�j
	// @param	posX		�ړ����������ʒu�i���S�j
	// @param	speed		����
	// @return	bool		�ړ����I��������ǂ���
	// @date	2014/2/5
	//----------------------------------------------------
	bool	RepositionRight	( CONST float posX, CONST float speed );

	//----------------------------------------------------
	// @name	RepositionLeft
	// @content	����ʒu�Ƀo�[���ړ�������i���j
	// @param	posX		�ړ����������ʒu�i���S�j
	// @param	speed		����
	// @return	none
	// @date	2014/2/5
	//----------------------------------------------------
	bool	RepositionLeft( CONST float posX, CONST float speed );
};


#endif _C_MESSAGE_BAR_H_