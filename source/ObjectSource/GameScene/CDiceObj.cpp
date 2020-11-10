
#include "CDiceObj.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CDiceObj::CDiceObj( void )
{
	m_pAABB = new THITAABB;
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CDiceObj::~CDiceObj( void )
{
	SAFE_DELETE( m_pAABB );
}

//----------------------------------------------------
// 初期化
//----------------------------------------------------
void CDiceObj::Init( void )
{
	C3DObjectAlphaBlend::Init();
	D3DXMatrixIdentity( &m_rotTemp );			// 回転保存用行列を初期化
	m_logPos = D3DXVECTOR3( 0.0f,0.0f,0.0f );	// 回転用保存ベクトルを初期化

	m_no = 0;									// 識別番号を0に設定
	m_indexNo = 0;								// 添え字番号を0に設定
	m_size = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_isDice = false;							// 出現フラグオフ
	m_status = DICE_STATUS::e_statusNone;		// 出現していない状態にしておく
	m_beforStatus = DICE_STATUS::e_statusNone;	// 前回の状態も同じ状態にしておく
	m_animeCnt = 0;								// アニメーションカウント
	m_chainNo = 0;								// チェイン番号を初期化
	m_isChain = false;							// チェインしてない状態にセット

	// 当たり判定の初期化
	D3DXVECTOR3 aabbPos = D3DXVECTOR3( this->GetXPos(), this->GetYPos(), this->GetZPos() );
	m_pAABB = CCollision::GetInstance()->SetAABB( m_pAABB, &aabbPos, &m_size );

	this->InitPip();	// 上面判定用配列初期化
}

//----------------------------------------------------
// 回転する前の初期化
//----------------------------------------------------
bool CDiceObj::InitRoll( void )
{
	m_logPos = this->GetWorldMtx()->m[3];					// 現在のワールド行列を保存
	CopyRotationMatrix( &m_rotTemp, this->GetWorldMtx() );	// 回転行列を保存

	return true;
}

//----------------------------------------------------
// 上面判定用配列の初期化
//----------------------------------------------------
bool CDiceObj::InitPip( void )
{	
	// サイコロの上面判定配列にデータを格納
	for( int i = 0; i < 7; ++ i )
	{
		m_dicePipAllay[ i ] = i;
	}

	return true;
}

//----------------------------------------------------
// X回転して移動
//----------------------------------------------------
void CDiceObj::MoveX( float x, float y, float z, float rotDir, float speed )
{
	D3DXMATRIX transMtx,lRotMtx,wRotMtx;

	// 軸を中心から移動させるための行列作成
	D3DXMatrixTranslation( &transMtx, x, y, z );
	
	// 回転行列を作成
	D3DXMatrixRotationZ(&lRotMtx,D3DXToRadian( speed * rotDir ) );	// x回転

	// 移動行列と回転行列を混ぜる
	D3DXMatrixMultiply( &wRotMtx, &transMtx, &lRotMtx );

	// ワールド行列にセット（中心座標を元に戻す）
	this->CalcWorldMtx( &m_rotTemp,&wRotMtx );
	this->MoveWorldPos( m_logPos.x - x, m_logPos.y - y, m_logPos.z - z );

}

//----------------------------------------------------
// Z回転して移動
//----------------------------------------------------
void CDiceObj::MoveZ( float x, float y, float z, float rotDir, float speed )
{
	D3DXMATRIX transMtx,lRotMtx,wRotMtx;
	D3DXMatrixIdentity( &transMtx );
	D3DXMatrixIdentity( &lRotMtx );
	D3DXMatrixIdentity( &wRotMtx );

	// 軸を中心から移動させるための行列作成
	D3DXMatrixTranslation( &transMtx, x, y, z );
	
	// 回転行列を作成
	D3DXMatrixRotationX(&lRotMtx,D3DXToRadian( speed * rotDir ) );	// z回転

	// 移動行列と回転行列を混ぜる
	D3DXMatrixMultiply( &wRotMtx, &transMtx, &lRotMtx);	

	// ワールド行列にセット（中心座標を元に戻す）
	this->CalcWorldMtx( &m_rotTemp, &wRotMtx );
	this->MoveWorldPos( m_logPos.x - x, m_logPos.y - y, m_logPos.z - z );
}

//----------------------------------------------------
// X回転のみ
//----------------------------------------------------
void CDiceObj::RollX( float degree )
{
	D3DXMATRIX lRotMtx;

	this->InitRoll();	// 回転のための初期化

	// 回転行列を作成
	D3DXMatrixRotationX(&lRotMtx,D3DXToRadian( degree ) );

	// ワールド行列にセット（中心座標を元に戻す）
	this->CalcWorldMtx( &m_rotTemp, &lRotMtx );
	this->MoveWorldPos( m_logPos.x, m_logPos.y, m_logPos.z );
}

//----------------------------------------------------
// Y回転のみ
//----------------------------------------------------
void CDiceObj::RollY( float degree )
{
	D3DXMATRIX lRotMtx;

	this->InitRoll();	// 回転のための初期化

	// 回転行列を作成
	D3DXMatrixRotationY(&lRotMtx,D3DXToRadian( degree ) );

	// ワールド行列にセット（中心座標を元に戻す）
	this->CalcWorldMtx( &m_rotTemp, &lRotMtx );
	this->MoveWorldPos( m_logPos.x, m_logPos.y, m_logPos.z );
}

//----------------------------------------------------
// Z回転のみ
//----------------------------------------------------
void CDiceObj::RollZ( float degree )
{
	D3DXMATRIX lRotMtx;
	D3DXMatrixIdentity( &lRotMtx );

	this->InitRoll();	// 回転のための初期化

	// 回転行列を作成
	D3DXMatrixRotationZ(&lRotMtx,D3DXToRadian( degree ) );

	// ワールド行列にセット（中心座標を元に戻す）
	this->CalcWorldMtx( &m_rotTemp, &lRotMtx );
	this->MoveWorldPos( m_logPos.x, m_logPos.y, m_logPos.z );
}

//----------------------------------------------------
// 回転させた時に回転させた方向によって内部の目を変える
//----------------------------------------------------
void CDiceObj::RollChangePip( CONST USHORT rollState )
{
	m_dicePipAllay[0] = m_dicePipAllay[1];	// 保存用に上面の番号保存

	switch( rollState )
	{
		// 右回転
		case ROLL_RIGTH_PIP:
			m_dicePipAllay[1] = m_dicePipAllay[2];
			m_dicePipAllay[2] = m_dicePipAllay[6];
			m_dicePipAllay[6] = m_dicePipAllay[5];
			m_dicePipAllay[5] = m_dicePipAllay[0];
			break;

		// 左回転
		case ROLL_LEFT_PIP:
			m_dicePipAllay[1] = m_dicePipAllay[5];
			m_dicePipAllay[5] = m_dicePipAllay[6];
			m_dicePipAllay[6] = m_dicePipAllay[2];
			m_dicePipAllay[2] = m_dicePipAllay[0];
			break;

		// 前回転
		case ROLL_FRONT_PIP:
			m_dicePipAllay[1] = m_dicePipAllay[3];
			m_dicePipAllay[3] = m_dicePipAllay[6];
			m_dicePipAllay[6] = m_dicePipAllay[4];
			m_dicePipAllay[4] = m_dicePipAllay[0];
			break;

		// 後回転
		case ROLL_BACK_PIP:
			m_dicePipAllay[1] = m_dicePipAllay[4];
			m_dicePipAllay[4] = m_dicePipAllay[6];
			m_dicePipAllay[6] = m_dicePipAllay[3];
			m_dicePipAllay[3] = m_dicePipAllay[0];
			break;

		// 左右180°回転
		case ROLL_HALFH_PIP:
			m_dicePipAllay[1] = m_dicePipAllay[6];
			m_dicePipAllay[6] = m_dicePipAllay[0];
			m_dicePipAllay[0] = m_dicePipAllay[2];
			m_dicePipAllay[2] = m_dicePipAllay[5];
			m_dicePipAllay[5] = m_dicePipAllay[0];
			break;

		// 前後180°回転
		case ROLL_HALFV_PIP:
			m_dicePipAllay[1] = m_dicePipAllay[6];
			m_dicePipAllay[6] = m_dicePipAllay[0];
			m_dicePipAllay[0] = m_dicePipAllay[3];
			m_dicePipAllay[3] = m_dicePipAllay[4];
			m_dicePipAllay[4] = m_dicePipAllay[0];
			break;
	}

}

//----------------------------------------------------
// 上面が回転しない回転をした時の内部の目を変える
//----------------------------------------------------
void CDiceObj::RollYChangePip( void )
{
	m_dicePipAllay[0] = m_dicePipAllay[2];
	m_dicePipAllay[2] = m_dicePipAllay[4];
	m_dicePipAllay[4] = m_dicePipAllay[5];
	m_dicePipAllay[5] = m_dicePipAllay[3];
	m_dicePipAllay[3] = m_dicePipAllay[0];
}

//----------------------------------------------------
// 上面と周りの面を同時にセット
//----------------------------------------------------
void CDiceObj::SetPip( CONST UINT upperFace, CONST UINT rollNum )
{
	this->SetUpperPip( upperFace );
	this->SetAroundPip( rollNum );
}

//----------------------------------------------------
// 上面をセット(１～６)
//----------------------------------------------------
void CDiceObj::SetUpperPip( CONST UINT upperFace )
{
	switch( upperFace )
	{
	case 1:
		// 1の場合は何もしない
		break;
	
	case 2:
		this->RollZ( -90.0f );
		this->RollChangePip( ROLL_RIGTH_PIP );
		break;

	case 3:
		this->RollX( 90.0f );
		this->RollChangePip( ROLL_FRONT_PIP );
		break;

	case 4:
		this->RollX( -90.0f );
		this->RollChangePip( ROLL_BACK_PIP );
		break;

	case 5:
		this->RollZ( 90.0f );
		this->RollChangePip( ROLL_LEFT_PIP );
		break;

	case 6:
		this->RollZ( 180.0f );
		this->RollChangePip( ROLL_HALFH_PIP );
		break;

	}
}

//----------------------------------------------------
// 周りの面をセット(０～３）
//----------------------------------------------------
void CDiceObj::SetAroundPip( CONST UINT rollNum )
{
	// 回数分右回転させる
	for( UINT i = 0; i < rollNum; ++ i )
	{
		this->RollY( -90.0f );
		this->RollYChangePip();
	}
}

//----------------------------------------------------
// 消滅アニメーション
//----------------------------------------------------
bool CDiceObj::DownAnimation( CONST float downSpeed )
{
	float speed = downSpeed;
	// 引数の値が0より大きい場合は-1を乗算
	if( speed > 0.0f ) 
	{
		speed *= -1;
	}

	// 位置変更
	this->MoveWorldPos( 0.0f, speed,0.0f );

	// ある一定距離消えたら色を変更
	if( this->GetYPos() <= -2.0 && m_status == DICE_STATUS::e_statusStartDelete )
	{
		this->SetColor( 255,0,0,127 );
		return true;
	}

	// 消えたらダイスをなくす
	if( this->GetYPos() <= -4.0f && m_status == DICE_STATUS::e_statusDelete )
	{
		this->SetIsDice( false );
		return true;
	}

	return false;
}

//----------------------------------------------------
// 出現アニメーション
//----------------------------------------------------
bool CDiceObj::UpAnimation( CONST float upSpeed )
{
	float speed = upSpeed;

	// 引数の値が0より小さい場合は-1を蒸散
	if( speed < 0.0f )
	{
		speed *= -1;
	}

	// 位置情報セット
	this->MoveWorldPos( 0.0f, speed, 0.0f );

	// ある程度出てきたら色変更
	if( this->GetWorldMtx()->_42 >= -2.0f && m_status == e_statusStartAppear )
	{
		this->SetColor( 255,255,255,255);
		this->SetIsDice( true );
		return true;
	}

	// 出てきたら
	if( this->GetWorldMtx()->_42 >= 0.0f && m_status == e_statusAppear )
	{
		return true;
	}

	return false;
}