
#include "CStageBlockObj.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CStageBlockObj::CStageBlockObj( void )
{
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
CStageBlockObj::~CStageBlockObj( void )
{
}

//----------------------------------------------------
// ������
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
// �_�C�X�����邩�ǂ����擾����
//----------------------------------------------------
bool CStageBlockObj::CheckOnDice( void )
{
	return m_isOnDice;
}

//----------------------------------------------------
// �v���C���[������Ă��邩�ǂ������擾����
//----------------------------------------------------
bool CStageBlockObj::CheckOnPlayer( void )
{
	return m_isOnPlayer;
}

//----------------------------------------------------
// �ʒu���̃Z�b�g
//----------------------------------------------------
void CStageBlockObj::SetPosition( float x, float y, float z )
{
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}

//----------------------------------------------------
// �ԍ��̃Z�b�g
//----------------------------------------------------
void CStageBlockObj::SetNo( CONST UINT no )
{
	m_no = no;
}

//----------------------------------------------------
// �_�C�X���Z�b�g
//----------------------------------------------------
void CStageBlockObj::SetDice( CDiceObj* dice )
{
	m_pDice = dice;
}

//----------------------------------------------------
// �_�C�X������Ă��邩�ǂ����̃t���O���Z�b�g
//----------------------------------------------------
void CStageBlockObj::SetIsOnDice( CONST bool isDice )
{
	m_isOnDice = isDice;
}

//----------------------------------------------------
// �v���C���[������Ă��邩�ǂ����̃t���O���Z�b�g
//----------------------------------------------------
void CStageBlockObj::SetIsOnPlayer( CONST bool isPlayer )
{
	m_isOnPlayer = isPlayer;
}