
#include "CStageBlockManager.h"

//----------------------------------------------------
// コンストラクタ
//----------------------------------------------------
CStageBlockManager::CStageBlockManager( void )
{
}

//----------------------------------------------------
// デストラクタ
//----------------------------------------------------
CStageBlockManager::~CStageBlockManager( void )
{
}

//----------------------------------------------------
// ステージのサイズセット(デフォルトサイズ)
//----------------------------------------------------
void CStageBlockManager::SetBlockPos( void )
{
	float workX = -BLOCK_MAXSIZE;
	float workZ = BLOCK_MAXSIZE;
	int	no = 0;

	// ステージの情報格納
	for( int i = 0; i < BLOCK_DEFAULT_NUM_Z; ++ i )
	{
		for( int j = 0; j < BLOCK_DEFAULT_NUM_X; ++ j )
		{
			m_stageBlock[no].SetPosition( workX,0.0f,workZ );
			workX += BLOCK_SIZE;

			m_stageBlock[no].SetNo( no );
			no ++;
		}
		
		workX = -BLOCK_MAXSIZE;
		workZ -= BLOCK_SIZE;
	}

	// ステージの最大サイズをメンバにセット
	m_xSize = BLOCK_MAXSIZE;
	m_ySize = 1;
	m_zSize = BLOCK_MAXSIZE;

	// ステージのマス目数をメンバにセット
	m_xNum = BLOCK_DEFAULT_NUM_X;
	m_yNum = BLOCK_DEFAULT_NUM_Y;
	m_zNum = BLOCK_DEFAULT_NUM_Z;

	// ステージのブロックの数をセット
	m_blockNum = BLOCK_DEFAULT_NUM_X * BLOCK_DEFAULT_NUM_Z;
}

//----------------------------------------------------
// ステージのサイズセット
//----------------------------------------------------
bool CStageBlockManager::SetBlockPos( UINT xNum, UINT yNum, UINT zNum )
{
	// 引数でセットされた値が0ならセットしない
	if( xNum == 0 || yNum == 0 || zNum == 0 )
	{
		return false;
	}

	float maxX = -( xNum * BLOCK_SIZE );
	float maxZ = zNum * BLOCK_SIZE;

	// ステージの最大サイズをメンバにセット
//	m_xSize = BLOCK_MAXSIZE;
//	m_ySize = 0.0f;
//	m_zSize = BLOCK_MAXSIZE;

	// ステージのブロック数をセット
	m_blockNum = xNum *  yNum *zNum;

	// ステージのマス目数をメンバにセット
	m_xNum = BLOCK_DEFAULT_NUM_X;
	m_yNum = BLOCK_DEFAULT_NUM_Y;
	m_zNum = BLOCK_DEFAULT_NUM_Z;

	return true;
}

//----------------------------------------------------
// ダイスの位置からインデックス番号を取得
//----------------------------------------------------
CONST UINT CStageBlockManager::GetIndexToDicePos( CONST float xPos, CONST float zPos )
{
	float workX = xPos / BLOCK_SIZE;
	float workZ = -zPos / BLOCK_SIZE;

	workX = workX + ( m_xSize / BLOCK_SIZE );
	workZ = workZ + ( m_zSize / BLOCK_SIZE );

	UINT index = UINT( workX + ( workZ * m_xNum ));

	return index;
}

//----------------------------------------------------
// プレイヤーの位置からインデックス番号を取得
//----------------------------------------------------
CONST UINT CStageBlockManager::GetIndexToPlayerPos( CONST float xPos, CONST float zPos )
{
	// 切り下げを行う
	double workX = floor( ( xPos + 2.0f )  / BLOCK_SIZE);
	double workZ = -floor( ( zPos + 2.0f )  / BLOCK_SIZE);

	workX = workX + ( m_xSize / BLOCK_SIZE );
	workZ = workZ + ( m_zSize / BLOCK_SIZE );

	UINT index = UINT( workX + ( workZ * m_xNum ));

	return index;
}


//----------------------------------------------------
// 初期化
//----------------------------------------------------
bool CStageBlockManager::Init( void )
{
	for( int i = 0; i < BLOCK_DEFAULT_MAX_NUM; ++ i )
	{
		m_stageBlock[i].Init();
	}

	return true;
}

//----------------------------------------------------
// ステージにダイスの情報をセット（移動の時はこちら）
//----------------------------------------------------
void CStageBlockManager::SetBlockToDiceInfo( CDiceObj* dice, int diceNo )
{
	m_stageBlock[ diceNo ].SetDice( dice );
	m_stageBlock[ diceNo ].SetIsOnDice( true );
}
