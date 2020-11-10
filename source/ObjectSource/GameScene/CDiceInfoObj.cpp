
#include "CDiceInfoObj.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CDiceInfoObj::CDiceInfoObj( void )
{
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CDiceInfoObj::~CDiceInfoObj( void )
{
}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
bool CDiceInfoObj::Init( void )
{
	m_isExist = true;

	this->InitWorldMtx();

	return true;

}

//----------------------------------------------------
// 回転行列をコピーしてワールド行列にセット
//----------------------------------------------------
void CDiceInfoObj::CopyRotationMtx( CONST D3DXMATRIX* worldMtx )
{
	m_worldMtx._11 = worldMtx->_11;
	m_worldMtx._12 = worldMtx->_12;
	m_worldMtx._13 = worldMtx->_13;
	m_worldMtx._21 = worldMtx->_21;
	m_worldMtx._22 = worldMtx->_22;
	m_worldMtx._23 = worldMtx->_23;
	m_worldMtx._31 = worldMtx->_31;
	m_worldMtx._32 = worldMtx->_32;
	m_worldMtx._33 = worldMtx->_33;
}