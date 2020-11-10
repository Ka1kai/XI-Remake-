//----------------------------------------------------
// CDebugStage
//　デバッグステージ
//
// @date	2013/9/8
// @author  T.Kawashita
//----------------------------------------------------
#ifndef _C_DEBUG_STAGE_H_
#define _C_DEBUG_STAGE_H_

#include <d3dx9.h>
#include "../UtilityHeader/Macro.hpp"

// デバッグ用の頂点構造体
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
	// @content	原点から正方形のステージを作成するための初期化
	// @param	lineLen		線の長さ
	// @return	none
	// @date	2013/9/8
	//----------------------------------------------------
	void	Init	( CONST FLOAT lineLen );

	// 終了処理
	void	Uninit	( void );

public:
	//----------------------------------------------------
	// @name	GetLineNum
	// @content	ライン数の取得
	// @param	none
	// @return	UINT		ライン数
	// @date	2013/9/8
	//----------------------------------------------------
	CONST UINT		GetLineNum	( void )
	{
		return m_lineNum;
	}

	//----------------------------------------------------
	// @name	GetVertex
	// @content 頂点情報の取得
	// @param	none
	// @return	tagTDEBUGVERTEX*	頂点情報
	// @date	2013/9/8
	//----------------------------------------------------
	tagTDEBUGVERTEX*	GetVertex	( void )
	{
		return m_pLineStage;
	}
};

#endif _C_DEBUG_STAGE_H_