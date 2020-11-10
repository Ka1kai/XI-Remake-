
#include "../../../KaiFrameWorkHeader/GameObjectHeader/2D/C2DSprite.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
C2DSprite::C2DSprite( void )
{
	m_pos = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_size = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );

	// 頂点座標・色を初期化
	for( int i = 0; i < 4; ++ i ){
		m_vertex[i].pos.x = 0.0f;
		m_vertex[i].pos.y = 0.0f;
		m_vertex[i].pos.z = 0.0f;
		m_vertex[i].diffuse = D3DCOLOR_RGBA( 255, 255, 255, 255);
	}

	// 頂点のテクスチャセット
	this->SetUV();
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
C2DSprite::~C2DSprite( void )
{
}

//----------------------------------------------------
// スプライトのセット
//----------------------------------------------------
bool C2DSprite::SetSprite( CONST D3DXVECTOR3* pos, CONST D3DXVECTOR3* size )
{
	// スプライトの位置のセット
	this->SetSpritePos( pos->x, pos->y, pos->z );

	// サイズのセット
	m_size.x = size->x;
	m_size.y = size->y;
	m_size.z = size->z;	// 当たり判定とかに使用する

	for( int i = 0; i < 4; ++ i )
	{
		m_vertex[i].diffuse = D3DCOLOR_RGBA( 255,255,255,255 );
	}

	// 頂点座標をセット
	this->SetVertexPos();

	// テクスチャ座標をセット
	this->SetUV();

	return true;
}

//----------------------------------------------------
// スプライト位置のセット
//----------------------------------------------------
void C2DSprite::SetSpritePos( CONST float x, CONST float y, CONST float z )
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;

	// 行列にも設定しておく
	this->SetWorldPos( &m_pos );
}

//----------------------------------------------------
// スプライト位置の移動
//----------------------------------------------------
void C2DSprite::MoveSpritePos( CONST float x, CONST float y, CONST float z )
{
	m_pos.x = m_pos.x + x;
	m_pos.y = m_pos.y + y;
	m_pos.z = m_pos.z + z;

	this->SetWorldPos( &m_pos );
}

//----------------------------------------------------
// スプライト位置の移動( vector指定 )
//----------------------------------------------------
void C2DSprite::MoveSpritePos( CONST D3DXVECTOR3* vec )
{
	m_pos.x = vec->x;
	m_pos.y = vec->y;
	m_pos.z = vec->z;

	this->SetWorldPos( &m_pos );
}

//----------------------------------------------------
// スプライトの大きさをセット
//----------------------------------------------------
void C2DSprite::SetSpriteSize( CONST float xSize, CONST float ySize )
{
	m_size.x = xSize;
	m_size.y = ySize;

	SetVertexPos();
}

//----------------------------------------------------
// 頂点の座標セット
//----------------------------------------------------
void C2DSprite::SetVertexPos( void )
{
	m_vertex[0].pos.x = -m_size.x / 2;
	m_vertex[0].pos.y = m_size.y / 2;
	m_vertex[0].pos.z = 0.0f;

	m_vertex[1].pos.x = m_size.x / 2;
	m_vertex[1].pos.y = m_size.y / 2;
	m_vertex[1].pos.z = 0.0f;

	m_vertex[2].pos.x = m_size.x / 2;
	m_vertex[2].pos.y = -m_size.y / 2;
	m_vertex[2].pos.z = 0.0f;

	m_vertex[3].pos.x = -m_size.x / 2;
	m_vertex[3].pos.y = -m_size.y / 2;
	m_vertex[3].pos.z = 0.0f;
}

//----------------------------------------------------
// テクスチャ座標セット
//----------------------------------------------------
void C2DSprite::SetUV( void )
{
	m_vertex[0].tu = 0.0f;
	m_vertex[0].tv = 0.0f;
	m_vertex[1].tu = 1.0f;
	m_vertex[1].tv = 0.0f;
	m_vertex[2].tu = 1.0f;
	m_vertex[2].tv = 1.0f;
	m_vertex[3].tu = 0.0f;
	m_vertex[3].tv = 1.0f;
}

//----------------------------------------------------
// テクスチャ座標セット(UVパターンを設定)
//----------------------------------------------------
void C2DSprite::SetUV( CONST UINT uPatern, CONST UINT vPatern, CONST UINT uNum, CONST UINT vNum )
{
	m_vertex[0].tu = 1.0f / uPatern * ( uNum - 1 );
	m_vertex[0].tv = 1.0f / vPatern * ( vNum - 1 );

	m_vertex[1].tu = 1.0f / uPatern * uNum;
	m_vertex[1].tv = 1.0f / vPatern * ( vNum - 1 );

	m_vertex[2].tu = 1.0f / uPatern * uNum;
	m_vertex[2].tv = 1.0f / vPatern * vNum;

	m_vertex[3].tu = 1.0f / uPatern * ( uNum - 1 );
	m_vertex[3].tv = 1.0f / vPatern *  vNum;

}

//----------------------------------------------------
// 頂点色のセット
//----------------------------------------------------
void C2DSprite::SetDiffuse( CONST UINT r, CONST UINT g, CONST UINT b, CONST UINT a )
{
	for( int i = 0; i < 4; ++ i )
	{
		m_vertex[i].diffuse = D3DCOLOR_RGBA( r, g, b, a );
	}
}

//----------------------------------------------------
// 板ポリゴンの行列をワールド行列に変換 
//----------------------------------------------------
void C2DSprite::CalcWorldMtx( void )
{
	m_worldMtx._11 = 1.0f;
	m_worldMtx._12 = 0.0f;
	m_worldMtx._13 = 0.0f;
	m_worldMtx._21 = 0.0f;
	m_worldMtx._22 = 1.0f;
	m_worldMtx._23 = 0.0f;	
	m_worldMtx._31 = 0.0f;
	m_worldMtx._32 = 0.0f;
	m_worldMtx._33 = 1.0f;
	m_worldMtx._14 = 0.0f;
	m_worldMtx._24 = 0.0f;
	m_worldMtx._34 = 0.0f;
	m_worldMtx._44 = 1.0f;
}