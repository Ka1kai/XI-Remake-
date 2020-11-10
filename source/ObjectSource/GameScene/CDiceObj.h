//----------------------------------------------------
// CDiceObj
//　3Dのサイコロオブジェクト
//
// @date	2013/11/20
// @author  T.Kawashita
//----------------------------------------------------
#ifndef _C_DICE_OBJ_H_
#define _C_DICE_OBJ_H_

#include "../../KaiFrameWork/KaiFrameWorkHeader/GameObjectHeader/3D/C3DObjectAlphaBlend.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/GameMathHeader/CCollision.h"
#include "../../KaiFrameWork/KaiFrameWorkHeader/UtilityHeader/Macro.hpp"

#define ROLL_RIGTH_PIP	( 1 )
#define ROLL_LEFT_PIP	( 2 )
#define ROLL_FRONT_PIP	( 3 )
#define ROLL_BACK_PIP	( 4 )
#define ROLL_HALFH_PIP	( 5 )	// 左右180°回転
#define ROLL_HALFV_PIP	( 6 )	// 上下180°回転

//----------------------------------------------------
// ステータス情報
//----------------------------------------------------
typedef enum DICE_STATUS
{
	e_statusNone = 0,		// 出現していない
	e_statusStartAppear,	// 出現中（出現し始め:薄い)
	e_statusAppear,			// 出現中（出現中：薄くない）
	e_statusNormal,			// 通常状態
	e_statusStartDelete,	// 消去中（消え始め:薄くない)
	e_statusDelete			// 消去中（消えている:薄い)
};

class CDiceObj : public C3DObjectAlphaBlend
{
private:	
	int			m_no;					// 識別番号
	int			m_indexNo;				// 添え字番号
	int			m_chainNo;				// チェイン番号
	D3DXVECTOR3	m_size;					// ダイスのサイズ
	D3DXVECTOR3	m_logPos;				// 保存行列
	D3DXMATRIX	m_rotTemp;				// 保存回転行列
	short		m_dicePipAllay[7];		// ダイスの目が保存された配列( 添え字の0番は入れ替え用のワーク )
	int			m_animeCnt;				// アニメーション用
	DICE_STATUS m_status;				// ステータス
	DICE_STATUS m_beforStatus;			// 前回のステータス
	THITAABB*	m_pAABB;				// 当たり判定用AABB
	bool		m_isDice;				// 生成されているかどうか
	bool		m_isChain;				// チェイン中かどうか

public:
	// 識別番号をセット
	void		SetNo		( CONST short no )
	{
		m_no = no;
	}
	// 識別番号を取得
	CONST short GetNo		( void )
	{
		return m_no;
	}

	// チェインしているかどうかをセット
	void		SetIsChain	( CONST bool isChain )
	{
		m_isChain = isChain;
	}
	// チェインしているかどうかを取得
	CONST bool	GetIsChain	( void )
	{
		return m_isChain;
	}

	// チェイン番号のセット
	void		SetChainNo	( CONST UINT chainNo )
	{
		m_chainNo = chainNo;
	}
	// チェイン番号の取得
	CONST UINT GetChainNo	( void )
	{
		return m_chainNo;
	}

	// 添え字番号をセット
	void		SetIndexNo	( CONST short indexNo )
	{
		m_indexNo = indexNo;
	}
	// 添え字番号を取得
	CONST short	GetIndexNo	( void )
	{
		return m_indexNo;
	}

	// 生成されているかどうかをセット
	void		SetIsDice	( CONST bool isDice )
	{
		m_isDice = isDice;
	}
	// 生成されているかどうかを取得
	bool		GetIsDice	( void )
	{
		return m_isDice;
	}
	
	// ステータスをセット
	void		SetStatus	( CONST DICE_STATUS status )
	{
		m_status = status;
	}
	// ステータスを取得
	CONST DICE_STATUS GetStatus	( void )
	{
		return m_status;
	}

	// 前回のステータスをセット
	void		SetBeforStatus ( CONST DICE_STATUS status )
	{
		m_beforStatus = status;
	}

	// 前回のステータスを取得
	CONST DICE_STATUS GetBeforStatus ( void )
	{
		return m_beforStatus;
	}

	// サイズをセット
	void		SetSize		( CONST D3DXVECTOR3* size )
	{
		m_size.x = size->x;
		m_size.y = size->y;
		m_size.z = size->z;
	}
	// サイズを取得
	CONST D3DXVECTOR3*	GetSize		( void )
	{
		return &m_size;
	}

	// 当たり判定用AABBをセット
	void		SetAABB		( void )
	{
		D3DXVECTOR3 aabbPos = D3DXVECTOR3( this->GetXPos(), this->GetYPos(), this->GetZPos() );
		m_pAABB = CCollision::GetInstance()->SetAABB( m_pAABB, &aabbPos, &m_size );
	}
	// 当たり判定用AABBを取得
	CONST THITAABB*	GetAABB		( void )
	{
		return m_pAABB;
	}

public:
	CDiceObj			( void );	// コンストラクタ
	virtual ~CDiceObj	( void );	// デストラクタ
	void	Init		( void );	// 初期化
	void	Uninit		( void );	// 終了処理

// 回転のみのためのメソッド
public:
	//----------------------------------------------------
	// @name	InitRoll
	// @content	回転する時の初期化
	// @param	none
	// @return	bool	成功か失敗
	// @date	2014/2/3
	//----------------------------------------------------
	bool	InitRoll	( void );

	//----------------------------------------------------
	// @name	RollX,Y,Z
	// @content	回転
	// @param	degree	回転量
	// @return	none
	// @date	2013/11/25
	//----------------------------------------------------
	void	RollX		( float degree );	// X軸回転
	void	RollY		( float degree );	// Y軸回転
	void	RollZ		( float degree );	// Z軸回転

public:
	//----------------------------------------------------
	// @name	MoveX,Z
	// @content	移動＋回転
	// @param	x		軸を移動させるためのx量	
	// @param	y		軸を移動させるためのy量
	// @param	z		軸を移動させるためのz量
	// @param	rotDir	回転させる方向ベクトル( 1.0, -1.0f )
	// @param	speed	スピード量
	// @return	none
	// @date	2013/11/26
	//----------------------------------------------------
	void	MoveX		( float x, float y, float z, float rotDir, float speed );	// X回転
	void	MoveZ		( float x, float y, float z, float rotDir, float speed );	// Z回転


// 面制御用のメソッド
public:
	//----------------------------------------------------
	// @name	InitPip
	// @content	面判定用配列の初期化
	// @param	none
	// @return	bool	成功か失敗
	// @date	2014/2/3
	//----------------------------------------------------
	bool	InitPip		( void );

	//----------------------------------------------------
	// @name	GetPip
	// @content	サイコロの上面の番号取得 
	//			※サイコロの面配列の添え字１が上面としている
	// @param	none	
	// @return	short			上面番号
	// @date	2013/11/27
	//----------------------------------------------------
	CONST	short	GetPip			( void )
	{
		return m_dicePipAllay[1];
	}

	//----------------------------------------------------
	// @name	RollChangePip
	// @content	回転させた時に回転させた方向によって
	//			ダイスの目を内部的に変える
	// @param	rollState		回転ステータス
	// @return	none
	// @date	2013/11/27
	//----------------------------------------------------	
	void			RollChangePip	( CONST USHORT rollState );

	//----------------------------------------------------
	// @name	RollYChangePip
	// @content	Y回転のみの場合回転させた方向によって
	//			ダイスの目を内部的に変える
	// @param	rollState		回転ステータス	
	// @return	none
	// @date	2013/11/27
	// @update
	//----------------------------------------------------
	void			RollYChangePip	( void );

	//----------------------------------------------------
	// @name	SetUpperFacePip
	// @content	上面をセット
	// @param	upperFace	セットしたい上面の番号(１～６）	
	// @return	none
	// @date	2013/11/26
	//----------------------------------------------------
	void			SetUpperPip		( CONST UINT upperFace );

	//----------------------------------------------------
	// @name	SetAroundFace
	// @content	周りの面をセット
	// @param	rollNum		回転させる回数（０～３）
	// @return	none
	// @date	2013/11/27
	//----------------------------------------------------
	void			SetAroundPip	( CONST UINT rollNum );

	//----------------------------------------------------
	// @name	SetPip
	// @content	上面と周りの面を同時にセット
	// @param	upperFace	セットしたい上面の番号（１～６）
	// @param	rollNum		回転させる回数（０～３）
	// @return	none
	// @date	2013/11/27
	//----------------------------------------------------
	void			SetPip				( CONST UINT upperFace, CONST UINT rollNum );

	//----------------------------------------------------
	// @name	DownAnimation
	// @content	消えていく処理
	// @param	downSpeed		落ちる速度
	// @return	bool			落ち切ったor一定距離落ちたかどうか
	// @date	2013/12/4
	// @update	2013/12/4		引数と戻り値追加
	//----------------------------------------------------
	bool			DownAnimation		( CONST float downSpeed );

	//----------------------------------------------------
	// @name	UpAnimatiion
	// @content	出てくる処理
	// @param	upSpeed			出てくる速度
	// @return	bool			出てきたor一定距離出てきたかどうか
	// @date	2013/12/4
	//----------------------------------------------------
	bool			UpAnimation			( CONST float upSpeed );
};

#endif _C_DICE_OBJ_H_