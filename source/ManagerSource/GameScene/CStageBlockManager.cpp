
#include "CStageBlockManager.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CStageBlockManager::CStageBlockManager( void )
{
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
CStageBlockManager::~CStageBlockManager( void )
{
}

//----------------------------------------------------
// �X�e�[�W�̃T�C�Y�Z�b�g(�f�t�H���g�T�C�Y)
//----------------------------------------------------
void CStageBlockManager::SetBlockPos( void )
{
	float workX = -BLOCK_MAXSIZE;
	float workZ = BLOCK_MAXSIZE;
	int	no = 0;

	// �X�e�[�W�̏��i�[
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

	// �X�e�[�W�̍ő�T�C�Y�������o�ɃZ�b�g
	m_xSize = BLOCK_MAXSIZE;
	m_ySize = 1;
	m_zSize = BLOCK_MAXSIZE;

	// �X�e�[�W�̃}�X�ڐ��������o�ɃZ�b�g
	m_xNum = BLOCK_DEFAULT_NUM_X;
	m_yNum = BLOCK_DEFAULT_NUM_Y;
	m_zNum = BLOCK_DEFAULT_NUM_Z;

	// �X�e�[�W�̃u���b�N�̐����Z�b�g
	m_blockNum = BLOCK_DEFAULT_NUM_X * BLOCK_DEFAULT_NUM_Z;
}

//----------------------------------------------------
// �X�e�[�W�̃T�C�Y�Z�b�g
//----------------------------------------------------
bool CStageBlockManager::SetBlockPos( UINT xNum, UINT yNum, UINT zNum )
{
	// �����ŃZ�b�g���ꂽ�l��0�Ȃ�Z�b�g���Ȃ�
	if( xNum == 0 || yNum == 0 || zNum == 0 )
	{
		return false;
	}

	float maxX = -( xNum * BLOCK_SIZE );
	float maxZ = zNum * BLOCK_SIZE;

	// �X�e�[�W�̍ő�T�C�Y�������o�ɃZ�b�g
//	m_xSize = BLOCK_MAXSIZE;
//	m_ySize = 0.0f;
//	m_zSize = BLOCK_MAXSIZE;

	// �X�e�[�W�̃u���b�N�����Z�b�g
	m_blockNum = xNum *  yNum *zNum;

	// �X�e�[�W�̃}�X�ڐ��������o�ɃZ�b�g
	m_xNum = BLOCK_DEFAULT_NUM_X;
	m_yNum = BLOCK_DEFAULT_NUM_Y;
	m_zNum = BLOCK_DEFAULT_NUM_Z;

	return true;
}

//----------------------------------------------------
// �_�C�X�̈ʒu����C���f�b�N�X�ԍ����擾
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
// �v���C���[�̈ʒu����C���f�b�N�X�ԍ����擾
//----------------------------------------------------
CONST UINT CStageBlockManager::GetIndexToPlayerPos( CONST float xPos, CONST float zPos )
{
	// �؂艺�����s��
	double workX = floor( ( xPos + 2.0f )  / BLOCK_SIZE);
	double workZ = -floor( ( zPos + 2.0f )  / BLOCK_SIZE);

	workX = workX + ( m_xSize / BLOCK_SIZE );
	workZ = workZ + ( m_zSize / BLOCK_SIZE );

	UINT index = UINT( workX + ( workZ * m_xNum ));

	return index;
}


//----------------------------------------------------
// ������
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
// �X�e�[�W�Ƀ_�C�X�̏����Z�b�g�i�ړ��̎��͂�����j
//----------------------------------------------------
void CStageBlockManager::SetBlockToDiceInfo( CDiceObj* dice, int diceNo )
{
	m_stageBlock[ diceNo ].SetDice( dice );
	m_stageBlock[ diceNo ].SetIsOnDice( true );
}
