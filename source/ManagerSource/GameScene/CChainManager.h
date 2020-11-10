//----------------------------------------------------
// CChainManager
//	ブロックがつながった時の処理
//
// @date	2013/12/2
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_CHAIN_MANAGER_H_
#define _C_CHAIN_MANAGER_H_

#include <list>
#include <vector>
#include "../../ObjectSource/GameScene/CDiceObj.h"
#include "CStageBlockManager.h"
#include "../../PlayerSource/CPlayerManager.h"
#include "../../ObjectSource/CScore.hpp"

typedef struct TagChain
{
	bool	isChain;			// チェイン中かどうか
	UINT	chainNo;			// チェイン番号
	UINT	chainPip;			// チェインしている上面
	UINT	chainNum;			// チェインしている数
	UINT	chainDiceNum;		// チェインしているダイスの数
}tagChain;

class CChainManager
{
private:
	std::list< CDiceObj* >		m_connectDiceList;		// 繋がったダイス格納用リスト
	tagChain	m_chain[50];							// チェイン管理構造体配列
	int		m_connectDiceNum;							// つながっている数
	int		m_mainPip;									// メインダイスの上面保存用
	int		m_xNum;		
	int		m_yNum;
	int		m_zNum;
	bool	m_decisionBlock[BLOCK_DEFAULT_MAX_NUM];		// 判定したかどうかの配列

	CScore*	m_pScore;									// スコア管理クラスから受け取るスコアのポインタ

	// コンストラクタ
	CChainManager	( void );
	CChainManager	( CONST CChainManager& chainManager ){}	// コピーコンストラクタを防ぐ
	CChainManager	operator=	( CONST CChainManager& chainManager ){}	// メンバの代入を防ぐ


public:
	// 唯一のインスタンスの取得場所
	static CChainManager*	GetInstance	( void )
	{
		static CChainManager chainManager;
		return &chainManager;
	}

	// デストラクタ
	~CChainManager	( void );

	//----------------------------------------------------
	// ステージサイズをセット
	//----------------------------------------------------
	void		SetSize					( void )
	{
		m_xNum = CStageBlockManager::GetInstance()->GetXNum();
		m_yNum = CStageBlockManager::GetInstance()->GetYNum();
		m_zNum = CStageBlockManager::GetInstance()->GetZNum();
	}

	//----------------------------------------------------
	// 初期化
	//----------------------------------------------------
	bool		Init					( void );

	//----------------------------------------------------
	// スコアのポインタをセット
	//----------------------------------------------------
	void		SetScore				( CScore* score )
	{
		m_pScore = score;
	}

	//----------------------------------------------------
	// @name	SetStageBlockDiceStatus
	// @content	ブロック上のダイスのステータスを設定
	// @param	index		変更したいダイスのインデックス番号
	// @return	none
	// @date	2013/12/9
	//----------------------------------------------------
	void		SetStageBlockDiceStatus	( CONST UINT index );

	//----------------------------------------------------
	// @name	Chain
	// @content	つながったときの処理
	// @param	index		メインブロックのインデックス番号
	// @return	none
	// @date	2013/12/2
	// @update	2013/12/3
	//----------------------------------------------------
	void		Chain				( CONST UINT index );

public:
	//----------------------------------------------------
	// @name	CheckAround
	// @content	周りのダイスとの判定(再帰関数)
	// @param	index		ブロックのインデックス番号
	// @return	none		
	// @date	2013/12/3
	//----------------------------------------------------
	int			CheckAround			( CONST UINT index );
	
	bool		CheckRight			( CONST UINT index );		// 右方向判定
	bool		CheckLeft			( CONST UINT index );		// 左方向判定
	bool		CheckFront			( CONST UINT index );		// 前方向判定
	bool		CheckDown			( CONST UINT index );		// 後方向判定

	//----------------------------------------------------
	// @name	CheckOne
	// @content	１の目かどうかを判定
	// @param	index		自分自身のインデックス番号
	// @return	none
	// @date	2014/2/4
	// @update	引数を追加（自分自身は消してはいけない）
	//----------------------------------------------------
	void		CheckOne			( CONST UINT index );

	//----------------------------------------------------
	// @name	CheckChain
	// @content	周りの面が消えているかどうかチェック
	// @param	index		調べたいインデックス番号	
	// @return	bool		チェインしている
	// @date	2014/2/5
	//----------------------------------------------------
	bool		CheckChain			( CONST UINT index );

	//----------------------------------------------------
	// @name	CheckChain
	// @content	周りの面が調べたい上面で消えているかどうかチェック	
	// @param	index		調べたいインデックス番号
	// @param	pip			調べたい上面番号
	// @return	bool		調べたい上面番号でチェインしている	
	// @date	2014/2/10
	//----------------------------------------------------
	bool		CheckChain			( CONST UINT index, CONST UINT pip );

	//----------------------------------------------------
	// チェイン管理配列を取得
	//----------------------------------------------------
	tagChain*	GetChain			( CONST UINT chainNo )
	{
		return &m_chain[ chainNo ];
	}
};



#endif _C_CHAIN_MANAGER_H_