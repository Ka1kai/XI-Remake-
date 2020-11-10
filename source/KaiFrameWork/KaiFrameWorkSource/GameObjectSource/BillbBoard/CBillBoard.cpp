
#include "../../../KaiFrameWorkHeader/GameObjectHeader/Billboard/CBillBoard.h"

//----------------------------------------------------
// 中心を原点とした頂点座標をセットする関数（３Ｄ空間）
//----------------------------------------------------
void CBillBoard::SetVertex()
{
	m_vertex[0].pos.x = -m_size.x / 2;
	m_vertex[0].pos.y = m_size.y / 2;
	m_vertex[0].pos.z = 0.0f;
	m_vertex[0].color = m_color;
	m_vertex[0].tu = 0.0f;
	m_vertex[0].tv = 0.0f;

	m_vertex[1].pos.x = m_size.x / 2;
	m_vertex[1].pos.y = m_size.y / 2;
	m_vertex[1].pos.z = 0.0f;
	m_vertex[1].color = m_color;
	m_vertex[1].tu = 1.0f;
	m_vertex[1].tv = 0.0f;

	m_vertex[2].pos.x = m_size.x / 2;
	m_vertex[2].pos.y = -m_size.y / 2;
	m_vertex[2].pos.z = 0.0f;
	m_vertex[2].color = m_color;
	m_vertex[2].tu = 1.0f;
	m_vertex[2].tv = 1.0f;

	m_vertex[3].pos.x = -m_size.x / 2;
	m_vertex[3].pos.y = -m_size.y / 2;
	m_vertex[3].pos.z = 0.0f;
	m_vertex[3].color = m_color;
	m_vertex[3].tu = 0.0f;
	m_vertex[3].tv = 1.0f;

}

//----------------------------------------------------
// 左上を原点をした頂点座標をセットする関数（２Ｄ空間）
//----------------------------------------------------
void CBillBoard::SetVertex( int windowX, int windowY )
{
	m_vertex[0].pos.x = -m_size.x / 2 - windowX / 2;
	m_vertex[0].pos.y = m_size.y / 2 + windowY / 2;
	m_vertex[0].pos.z = 0.0f;
	m_vertex[0].color = m_color;
	m_vertex[0].tu = 0.0f;
	m_vertex[0].tv = 0.0f;

	m_vertex[1].pos.x = m_size.x / 2 + windowX / 2;
	m_vertex[1].pos.y = m_size.y / 2 + windowY / 2;
	m_vertex[1].pos.z = 0.0f;
	m_vertex[1].color = m_color;
	m_vertex[1].tu = 1.0f;
	m_vertex[1].tv = 0.0f;

	m_vertex[2].pos.x = m_size.x / 2 + windowX / 2;
	m_vertex[2].pos.y = -m_size.y / 2 - windowY / 2;
	m_vertex[2].pos.z = 0.0f;
	m_vertex[2].color = m_color;
	m_vertex[2].tu = 1.0f;
	m_vertex[2].tv = 1.0f;

	m_vertex[3].pos.x = -m_size.x / 2 - windowX / 2;
	m_vertex[3].pos.y = -m_size.y / 2 - windowY / 2;
	m_vertex[3].pos.z = 0.0f;
	m_vertex[3].color = m_color;
	m_vertex[3].tu = 0.0f;
	m_vertex[3].tv = 1.0f;

}

//----------------------------------------------------
// 位置をセット
//----------------------------------------------------
void CBillBoard::SetPosition(float x,float y,float z)
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}

//----------------------------------------------------
// ビルボードのセット
//----------------------------------------------------
void CBillBoard::SetBillboard( float xSize,float ySize,D3DCOLOR color )
{
	m_size.x = xSize;
	m_size.y = ySize;
	m_color = color;
	this->SetMaxAlfa( this->GetAlfa() );
	D3DXMatrixIdentity( &m_mtx );	
	this->SetVertex();
}

//----------------------------------------------------
// ビルボードのセット
// ＸとＹ両方同じ大きさ
//----------------------------------------------------
void CBillBoard::SetBillboard( float size,D3DCOLOR color )
{
	m_size.x = size;
	m_size.y = size;
	m_color = color;
	this->SetMaxAlfa( this->GetAlfa() );
	D3DXMatrixIdentity( &m_mtx );	
	this->SetVertex();
}

//----------------------------------------------------
// 更新したα値のセット
//----------------------------------------------------
void CBillBoard::SetAlfa( int alfa )
{
	m_color = D3DCOLOR_ARGB( alfa,255,255,255 );
	m_vertex[0].color = m_color;
	m_vertex[1].color = m_color;
	m_vertex[2].color = m_color;
	m_vertex[3].color = m_color;
}

//----------------------------------------------------
// 更新したα値のセット
//----------------------------------------------------
void CBillBoard::SetDiffuse( int alfa )
{
	int r,g,b;
	r = m_color >> 16;
	g = m_color >> 8;
	b = m_color >> 0;

	m_color = D3DCOLOR_ARGB( alfa,r,g,b );
	m_vertex[0].color = m_color;
	m_vertex[1].color = m_color;
	m_vertex[2].color = m_color;
	m_vertex[3].color = m_color;
}

//----------------------------------------------------
// マックスα値のセット
//----------------------------------------------------
void CBillBoard::SetMaxAlfa( int maxAlfa )
{
	m_maxAlfa = maxAlfa;
}