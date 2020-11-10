
#include "../../KaiFrameWorkHeader/DirectX9Header/CDirectX9Camera.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CDirectCamera::CDirectCamera( void )
{
	// 位置・注視点・方向初期化
	this->Init();
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CDirectCamera::~CDirectCamera( void )
{
}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
bool CDirectCamera::Init( CONST int windowSizeX, CONST int windowSizeY )
{
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	D3DXMatrixIdentity( &m_view );
	D3DXMatrixIdentity( &m_projection );
	D3DXMatrixIdentity( &m_ortho );
	D3DXMatrixIdentity( &m_worldMtx );

	// プロジェクション座標変換行列の算出
	D3DXMatrixPerspectiveFovLH(&m_projection, D3DXToRadian( 45.0f ),
							   (float)windowSizeX / (float)windowSizeY,
							   1.0f,
							   2000.0f);
	
	// 正射影変換座標行列の算出
	D3DXMatrixOrthoLH(&m_ortho,(float)windowSizeX,(float)-windowSizeY,1.0f,2000.0f);

	// カメラ座標変換行列の算出
	D3DXMatrixLookAtLH(&m_view, &m_vEye, &m_vAt, &m_vUp);
	
	// カメラとプロジェクションの変換行列のセット
	pd3dDevice->SetTransform(D3DTS_VIEW, &m_view);
	pd3dDevice->SetTransform(D3DTS_PROJECTION, &m_projection);

	this->SetView();

	return true;
}//----------------------------------------------------

//----------------------------------------------------
// 初期化(位置＋注視点＋方向)
//----------------------------------------------------
bool CDirectCamera::Init( void )
{
	m_worldMtx._41 = 0.0f;	
	m_worldMtx._42 = 0.0f;	
	m_worldMtx._43 = -20.0f;	// カメラの位置座標
	m_worldMtx._31 = 0.0f;
	m_worldMtx._32 = 0.0f;	
	m_worldMtx._33 = 1.0f;		// カメラの注視点座標
	m_worldMtx._21 = 0.0f;	
	m_worldMtx._22 = 1.0f;	
	m_worldMtx._23= 0.0f;		// カメラの上方向ベクトル	

	return true;
}

//----------------------------------------------------
// カメラのセット
//----------------------------------------------------
bool CDirectCamera::Set( void )
{
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
	
	// カメラ座標変換行列の算出
	D3DXMatrixLookAtLH( &m_view, &m_vEye, &m_vAt, &m_vUp );
	
	// カメラのセット
	pd3dDevice->SetTransform( D3DTS_VIEW, &m_view );
	
	return true;
}

//----------------------------------------------------
// カメラの位置セット
//----------------------------------------------------
bool CDirectCamera::SetPosition( CONST float xPos, CONST float yPos, CONST float zPos )
{
	m_worldMtx._41 = m_worldMtx._41 + xPos;
	m_worldMtx._42 = m_worldMtx._42 + yPos;
	m_worldMtx._43 = m_worldMtx._43 + zPos;
	
	// ワールド行列にセットした後ワールドに配置
	this->SetView();

	return true;
}

//----------------------------------------------------
// カメラの注視点セット
//----------------------------------------------------
bool CDirectCamera::SetAt( CONST float xPos, CONST float yPos, CONST float zPos )
{
	m_worldMtx._31 = m_worldMtx._31 + xPos;
	m_worldMtx._32 = m_worldMtx._32 + yPos;
	m_worldMtx._33 = m_worldMtx._33 + zPos;

	// ワールド行列にセットした後ワールドに配置
	this->SetView();

	return true;
}

//----------------------------------------------------
// カメラワールド行列のセット
//----------------------------------------------------
bool CDirectCamera::SetView( void )
{
	m_vEye.x = m_worldMtx._41;
	m_vEye.y = m_worldMtx._42;
	m_vEye.z = m_worldMtx._43;
	m_vAt.x = m_worldMtx._31;
	m_vAt.y = m_worldMtx._32;
	m_vAt.z = m_worldMtx._33;
	m_vUp.x = m_worldMtx._21;
	m_vUp.y = m_worldMtx._22;
	m_vUp.z = m_worldMtx._23;

	// カメラをワールドに配置
	this->Set();

	return true;
}

//----------------------------------------------------
// モデルのベクトルを利用しての追従カメラ
// モデルの後ろの位置にカメラを置いたまま追従される
//----------------------------------------------------
void CDirectCamera::Tracking( CONST D3DXMATRIX* pMtx, CONST D3DXVECTOR3* pVec , CONST float distance)
{
	// カメラの位置セット
	m_vEye.x = pVec->x * distance + pMtx->_41;
	m_vEye.y = pVec->y * distance + pMtx->_42;
	m_vEye.z = pVec->z * distance + pMtx->_43;
	
	// カメラの注視点座標
	m_vAt.x = pMtx->_41;	
	m_vAt.y = pMtx->_42;
	m_vAt.z = pMtx->_43;	
	
	// ジンバルロックを防ぐ
	m_vUp.x = pMtx->_21;	
	m_vUp.y = pMtx->_22;	
	m_vUp.z = pMtx->_23;

	// ワールド位置にカメラを配置
	this->Set();

}

//----------------------------------------------------
// 主観カメラ( ベクトルを考慮していない )
//----------------------------------------------------
void CDirectCamera::Tracking( CONST D3DXMATRIX* pMtx, CONST float at )
{
	// カメラの注視点更新
	m_vAt.x = pMtx->_31 * at + pMtx->_41;	
	m_vAt.y = pMtx->_32 * at + pMtx->_42;
	m_vAt.z = pMtx->_33 * at + pMtx->_43;

	// カメラの位置更新
	m_vEye.x = pMtx->_41;	
	m_vEye.y = pMtx->_42;	
	m_vEye.z = pMtx->_43;

	// カメラの上方向更新(ジンバルロックを防ぐ）
	m_vUp.x = pMtx->_21; 
	m_vUp.y = pMtx->_22; 
	m_vUp.z = pMtx->_23;

	// ワールド位置に配置
	this->Set();
}

//----------------------------------------------------
// カメラを向いた画像描画（ビルボード）
//----------------------------------------------------
D3DXMATRIX* CDirectCamera::SetBillBoardMtx( D3DXMATRIX* pBillBoardMtx, CONST D3DXVECTOR3* pBillBoardPos )
{	
	D3DXMatrixIdentity( pBillBoardMtx );

	pBillBoardMtx->_11 = m_view._11;
	pBillBoardMtx->_12 = m_view._21;
	pBillBoardMtx->_13 = m_view._31;
	pBillBoardMtx->_21 = m_view._12;
	pBillBoardMtx->_22 = m_view._22;
	pBillBoardMtx->_23 = m_view._32;
	pBillBoardMtx->_31 = m_view._13;
	pBillBoardMtx->_32 = m_view._23;
	pBillBoardMtx->_33 = m_view._33;
	pBillBoardMtx->_41 = pBillBoardPos->x;
	pBillBoardMtx->_42 = pBillBoardPos->y;
	pBillBoardMtx->_43 = pBillBoardPos->z;
	pBillBoardMtx->_14 = 0.0f;
	pBillBoardMtx->_24 = 0.0f;
	pBillBoardMtx->_34 = 0.0f;
	pBillBoardMtx->_44 = 1.0f;

	return pBillBoardMtx;
}

//----------------------------------------------------
// カメラが動いても変化しない画像描画（ビルボード）
//----------------------------------------------------
D3DXMATRIX* CDirectCamera::SetBillBoardMtx( D3DXMATRIX* pBillBoardMtx, CONST float distance )
{
	D3DXMatrixIdentity( pBillBoardMtx );

	pBillBoardMtx->_11 = m_view._11;
	pBillBoardMtx->_12 = m_view._12;
	pBillBoardMtx->_13 = m_view._13;
	pBillBoardMtx->_21 = m_view._21;
	pBillBoardMtx->_22 = m_view._22;
	pBillBoardMtx->_23 = m_view._23;	
	pBillBoardMtx->_31 = m_view._31;
	pBillBoardMtx->_32 = m_view._32;
	pBillBoardMtx->_33 = m_view._33;
	pBillBoardMtx->_41 = m_vEye.x + m_vAt.x * -1.0f * distance;
	pBillBoardMtx->_42 = m_vEye.y + m_vAt.y * -1.0f * distance;
	pBillBoardMtx->_43 = m_vEye.z + m_vAt.z * -1.0f * distance;
	pBillBoardMtx->_14 = 0.0f;
	pBillBoardMtx->_24 = 0.0f;
	pBillBoardMtx->_34 = 0.0f;
	pBillBoardMtx->_44 = 1.0f;
	
	return pBillBoardMtx;
}

//----------------------------------------------------
// クォータニオンの計算
//----------------------------------------------------
bool CDirectCamera::CalcLocalQuaternion( CONST D3DXVECTOR3* pAxis, CONST float degree )
{
	D3DXQUATERNION	localQuater;
	D3DXMATRIX		rotationMat;

	D3DXMatrixIdentity( &rotationMat );

	// 行列からクォータニオンを生成
	D3DXQuaternionRotationMatrix( &localQuater, &m_worldMtx );

	// 任意の軸を回転軸としてクォータニオンを回転させる
	D3DXQuaternionRotationAxis( &localQuater, pAxis, D3DXToRadian( degree ) );

	// クォータニオンから行列を求める
	D3DXMatrixRotationQuaternion( &rotationMat, &localQuater ); 
	D3DXMatrixMultiply( &m_worldMtx, &m_worldMtx,&rotationMat );

	// カメラをワールドに配置
	this->SetView();

	return true;
}

//----------------------------------------------------
// ローカルクォータニオンX回転
//----------------------------------------------------
void CDirectCamera::LocalRotationQuaterX( CONST float degree )
{
	D3DXVECTOR3		axis;

	axis.x = m_worldMtx._11;
	axis.y = m_worldMtx._12;
	axis.z = m_worldMtx._13;
	
	// クォータニオン計算
	this->CalcLocalQuaternion( &axis, degree );
}

//----------------------------------------------------
// ローカルクォータニオンY回転
//----------------------------------------------------
void CDirectCamera::LocalRotationQuaterY( CONST float degree )
{
	D3DXVECTOR3		axis;

	axis.x = m_worldMtx._21;
	axis.y = m_worldMtx._22;
	axis.z = m_worldMtx._23;
	
	// クォータニオン計算
	this->CalcLocalQuaternion( &axis, degree );
}

//----------------------------------------------------
// ローカルクォータニオンZ回転
//----------------------------------------------------
void CDirectCamera::LocalRotationQuaterZ( CONST float degree )
{
	D3DXVECTOR3		axis;

	axis.x = m_worldMtx._31;
	axis.y = m_worldMtx._32;
	axis.z = m_worldMtx._33;
	
	// クォータニオン計算
	this->CalcLocalQuaternion( &axis, degree );
}

//----------------------------------------------------
// ローカル任意軸クォータニオン回転
//----------------------------------------------------
void CDirectCamera::LocalRotationQuater( CONST D3DXVECTOR3* pVec, CONST float degree )
{
	D3DXVECTOR3		axis;

	axis.x = pVec->x;
	axis.y = pVec->y;
	axis.z = pVec->z;

	// クォータニオン回転計算
	this->CalcLocalQuaternion( &axis, degree );
}