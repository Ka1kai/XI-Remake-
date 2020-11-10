
#include "CStageBlockObj.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CStageBlockObj::CStageBlockObj( void )
{
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CStageBlockObj::~CStageBlockObj( void )
{
}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
bool CStageBlockObj::Init( void )
{
	m_no = 50;
	m_pos.x = 0.0f;
	m_pos.y = 0.0f;
	m_pos.z = 0.0f;
	m_pDice = nullptr;
	m_isOnDice = false;
	m_isOnPlayer = false;

	return true;
}

//----------------------------------------------------
// ダイスがあるかどうか取得する
//----------------------------------------------------
bool CStageBlockObj::CheckOnDice( void )
{
	return m_isOnDice;
}

//----------------------------------------------------
// プレイヤーが乗っているかどうかを取得する
//----------------------------------------------------
bool CStageBlockObj::CheckOnPlayer( void )
{
	return m_isOnPlayer;
}

//----------------------------------------------------
// 位置情報のセット
//----------------------------------------------------
void CStageBlockObj::SetPosition( float x, float y, float z )
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}

//----------------------------------------------------
// 番号のセット
//----------------------------------------------------
void CStageBlockObj::SetNo( CONST UINT no )
{
	m_no = no;
}

//----------------------------------------------------
// ダイスをセット
//----------------------------------------------------
void CStageBlockObj::SetDice( CDiceObj* dice )
{
	m_pDice = dice;
}

//----------------------------------------------------
// ダイスが乗っているかどうかのフラグをセット
//----------------------------------------------------
void CStageBlockObj::SetIsOnDice( CONST bool isDice )
{
	m_isOnDice = isDice;
}

//----------------------------------------------------
// プレイヤーが乗っているかどうかのフラグをセット
//----------------------------------------------------
void CStageBlockObj::SetIsOnPlayer( CONST bool isPlayer )
{
	m_isOnPlayer = isPlayer;
}