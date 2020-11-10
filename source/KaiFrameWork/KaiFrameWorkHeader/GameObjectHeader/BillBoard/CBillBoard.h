//----------------------------------------------------
// CBillBoard 
//	ビルボードのクラス
//
// @date	2013/6/15
// @update	2013/12/12
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_BILLBOARD_H_
#define _C_BILLBOARD_H_

#include <Windows.h>
#include <d3dx9.h>

// 頂点フォーマット(ビルボード用)
typedef struct TAGtBILLBORDVERTEX
{
	D3DXVECTOR3 pos;
	D3DCOLOR	color;
	float		tu,tv;
}tagTBILLBORDVERTEX;

class CBillBoard
{
private:
	D3DXMATRIX			m_mtx;			// ビルボード用の行列
	D3DXVECTOR3			m_pos;			// ビルボードの位置座標
	D3DXVECTOR3			m_size;			// ビルボードのサイズ
	D3DCOLOR			m_color;		// カラー値
	int					m_maxAlfa;		// 開始時のα値

	tagTBILLBORDVERTEX	m_vertex[4];	// ビルボードの頂点座標

public:
	// 引数なしコンストラクタ
	CBillBoard()
	{
		m_pos.x = 0.0f;
		m_pos.y = 0.0f;
		m_pos.z = 0.0f;
		D3DXMatrixIdentity( &m_mtx );	
	}

	// 引数を設定するコンストラクタ
	CBillBoard( float x, float y, float z, float xSize, float ySize, D3DCOLOR color)
	{
		m_pos.x = x;
		m_pos.y = y;
		m_pos.z = z;
		m_size.x = xSize;
		m_size.y = ySize;
		m_color = color;
		D3DXMatrixIdentity( &m_mtx );	
		this->SetVertex();
		m_maxAlfa = 255;	
	}

	// デストラクタ
	~CBillBoard(){}

public:
	// ビルボード用の行列の取得
	D3DXMATRIX* GetMat()
	{
		return &m_mtx;
	}

	// ビルボード用の頂点情報の取得
	const tagTBILLBORDVERTEX* GetVertex()
	{
		return m_vertex;
	}

	// ビルボード用座標の取得
	const D3DXVECTOR3* GetPos()
	{
		return &m_pos;
	}

public:
	// α値の取得
	const int GetAlfa			( void )
	{
		return ( m_color >> 24 );
	}

	// α値のセット
	void SetAlfa		( int alfa );
	void SetDiffuse		( int alfa );
	
	// 最大α値のセット
	void SetMaxAlfa		( int maxAlfa );
	const int GetMaxAlfa( void )
	{
		return m_maxAlfa;
	}

	void SetVertex		( void );										// 頂点座標のセット
	void SetVertex		( int windowX,int windowY );					// 頂点座標のセット（左上原点）
	void SetPosition	( const float x,const float y,const float z );	// 位置をセット
	void SetBillboard	( float xSize,float ySize,D3DCOLOR color);		// ビルボードのセット
	void SetBillboard	( float size,D3DCOLOR color );					// ビルボードのセット(サイズ同じ)

};

#endif _C_BILLBOARD_H_