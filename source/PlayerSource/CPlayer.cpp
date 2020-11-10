
#include "CPlayer.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CPlayer::CPlayer( void )
{
	m_pAABB = new THITAABB;
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
CPlayer::~CPlayer( void )
{
	SAFE_DELETE( m_pAABB );
}

//----------------------------------------------------
// ������
//----------------------------------------------------
bool CPlayer::Init( void )
{
	// �X�v���C�g�̐ݒ�
	this->SetSprite( &D3DXVECTOR3( 0.0f,4.0f,0.0f ), &D3DXVECTOR3( 5.0f, 4.0f, 0.0f ));
	this->SetUV( 4, 4, 1, 1 );

	// �_�C�X�Ƃ̓����蔻��p�̉��zAABB���쐬
	D3DXVECTOR3 aabbPos = D3DXVECTOR3( this->GetXPos() , this->GetYPos(), this->GetZPos() );
	D3DXVECTOR3 aabbSize = D3DXVECTOR3( 0.5f, 8.0f , 0.5f );
	m_pAABB = CCollision::GetInstance()->SetAABB( m_pAABB, &aabbPos, &aabbSize );

	// �X�e�[�^�X������
	m_status = ePlayerStatus::eOnDice;
	m_moveStatus = ePlayerMoveStatus::eMoveNone;
	
	return true;
}
//----------------------------------------------------
// �I������
//----------------------------------------------------
bool CPlayer::Uninit( void )
{
	return true;
}

//----------------------------------------------------
// �O�ړ�
//----------------------------------------------------
void CPlayer::MoveFront( CONST float speed )
{
	MoveSpritePos( 0.0f, 0.0f, speed );
	this->SetUV( 4, 4, 1, 4 );

	// AABB�ʒu�X�V
	this->SetAABB();
	CDebugMode::m_pPlayerBox.SetWorldPos( GetXPos(), GetYPos(), GetZPos() );
}

//----------------------------------------------------
// ��ړ�
//----------------------------------------------------
void CPlayer::MoveBack( CONST float speed )
{
	MoveSpritePos( 0.0f, 0.0f, -speed );
	this->SetUV( 4, 4, 1, 1 );

	// AABB�ʒu�X�V
	this->SetAABB();
	CDebugMode::m_pPlayerBox.SetWorldPos( GetXPos(), GetYPos(), GetZPos() );
}

//----------------------------------------------------
// �E�ړ�
//----------------------------------------------------
void CPlayer::MoveRight( CONST float speed )
{
	MoveSpritePos( speed, 0.0f, 0.0f );
	this->SetUV( 4, 4, 1, 2 );

	// AABB�ʒu�X�V
	this->SetAABB();
	CDebugMode::m_pPlayerBox.SetWorldPos( GetXPos(), GetYPos(), GetZPos() );
}

//----------------------------------------------------
// ���ړ�
//----------------------------------------------------
void CPlayer::MoveLeft( CONST float speed )
{
	MoveSpritePos( -speed, 0.0f, 0.0f );
	this->SetUV( 4, 4, 1, 3 );
	
	// AABB�ʒu�X�V
	this->SetAABB();
	CDebugMode::m_pPlayerBox.SetWorldPos( GetXPos(), GetYPos(), GetZPos() );

}

//----------------------------------------------------
// �_�E������
//----------------------------------------------------
void CPlayer::MoveDown( CONST float speed )
{
	MoveSpritePos( 0.0f, -speed, 0.0f );

	// AABB�ʒu�X�V
	this->SetAABB();
	CDebugMode::m_pPlayerBox.SetWorldPos( GetXPos(), GetYPos(), GetZPos() );
}

//----------------------------------------------------
// �A�b�v����
//----------------------------------------------------
void CPlayer::MoveUp( CONST float speed  )
{
	MoveSpritePos( 0.0f, speed, 0.0f );

	// AABB�ʒu�X�V
	this->SetAABB();
	CDebugMode::m_pPlayerBox.SetWorldPos( GetXPos(), GetYPos(), GetZPos() );
}