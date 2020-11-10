//----------------------------------------------------
// CDebugStage
//�@�f�o�b�O�X�e�[�W
//
// @date	2013/9/8
// @author  T.Kawashita
//----------------------------------------------------
#ifndef _C_DEBUG_STAGE_H_
#define _C_DEBUG_STAGE_H_

#include <d3dx9.h>
#include "../UtilityHeader/Macro.hpp"

// �f�o�b�O�p�̒��_�\����
typedef struct TAGtDEBUGVERTEX
{
	D3DXVECTOR3 pos;
	D3DCOLOR	color;
}tagTDEBUGVERTEX;

class CDebugStage
{
private:
	tagTDEBUGVERTEX*	m_pLineStage;
	UINT				m_lineNum;

public:
	CDebugStage		( void );
	CDebugStage		( CONST UINT lineNum );
	~CDebugStage	( void );

public:
	//----------------------------------------------------
	// @name	Init
	// @content	���_���琳���`�̃X�e�[�W���쐬���邽�߂̏�����
	// @param	lineLen		���̒���
	// @return	none
	// @date	2013/9/8
	//----------------------------------------------------
	void	Init	( CONST FLOAT lineLen );

	// �I������
	void	Uninit	( void );

public:
	//----------------------------------------------------
	// @name	GetLineNum
	// @content	���C�����̎擾
	// @param	none
	// @return	UINT		���C����
	// @date	2013/9/8
	//----------------------------------------------------
	CONST UINT		GetLineNum	( void )
	{
		return m_lineNum;
	}

	//----------------------------------------------------
	// @name	GetVertex
	// @content ���_���̎擾
	// @param	none
	// @return	tagTDEBUGVERTEX*	���_���
	// @date	2013/9/8
	//----------------------------------------------------
	tagTDEBUGVERTEX*	GetVertex	( void )
	{
		return m_pLineStage;
	}
};

#endif _C_DEBUG_STAGE_H_