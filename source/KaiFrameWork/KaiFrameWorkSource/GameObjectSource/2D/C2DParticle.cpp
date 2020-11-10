
#include "../../../KaiFrameWorkHeader/GameObjectHeader/2D/C2DParticle.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
C2DParticle::C2DParticle( void )
{
	m_speed = D3DXVECTOR3( 0.0f,0.0f,0.0f );
	m_direct = D3DXVECTOR3( 0.0f,0.0f,0.0f );
	m_life = 0;
	m_isExist = false;
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
C2DParticle::~C2DParticle( void )
{
}

//----------------------------------------------------
// パーティクルのセット
//----------------------------------------------------
void C2DParticle::SetParticle( CONST D3DXVECTOR3* speed, CONST D3DXVECTOR3* dir, CONST UINT life )
{
	m_speed.x = speed->x;
	m_speed.y = speed->y;
	m_speed.z = speed->z;
	m_direct.x = dir->x;
	m_direct.y = dir->y;
	m_direct.z = dir->z;
	m_life = life;
	m_isExist = true;
}

//----------------------------------------------------
// パーティクルの移動
//----------------------------------------------------
void C2DParticle::Move( void )
{
	D3DXVECTOR3 workMove;		// 移動用work

	workMove.x = this->GetPos()->x + m_speed.x * m_direct.x;
	workMove.y = this->GetPos()->y + m_speed.y * m_direct.y;
	workMove.z = this->GetPos()->z + m_speed.z * m_direct.z;

	// スプライトの位置を変更してその後ワールド位置も変更する
	this->MoveSpritePos( &workMove );

}
