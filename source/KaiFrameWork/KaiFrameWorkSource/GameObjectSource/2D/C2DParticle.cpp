
#include "../../../KaiFrameWorkHeader/GameObjectHeader/2D/C2DParticle.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
C2DParticle::C2DParticle( void )
{
	m_speed = D3DXVECTOR3( 0.0f,0.0f,0.0f );
	m_direct = D3DXVECTOR3( 0.0f,0.0f,0.0f );
	m_life = 0;
	m_isExist = false;
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
C2DParticle::~C2DParticle( void )
{
}

//----------------------------------------------------
// �p�[�e�B�N���̃Z�b�g
//----------------------------------------------------
void C2DParticle::SetParticle( CONST D3DXVECTOR3* speed, CONST D3DXVECTOR3* dir, CONST UINT life )
{
	m_speed.x = speed->x;
	m_speed.y = speed->y;
	m_speed.z = speed->z;
	m_direct.x = dir->x;
	m_direct.y = dir->y;
	m_direct.z = dir->z;
	m_life = life;
	m_isExist = true;
}

//----------------------------------------------------
// �p�[�e�B�N���̈ړ�
//----------------------------------------------------
void C2DParticle::Move( void )
{
	D3DXVECTOR3 workMove;		// �ړ��pwork

	workMove.x = this->GetPos()->x + m_speed.x * m_direct.x;
	workMove.y = this->GetPos()->y + m_speed.y * m_direct.y;
	workMove.z = this->GetPos()->z + m_speed.z * m_direct.z;

	// �X�v���C�g�̈ʒu��ύX���Ă��̌ハ�[���h�ʒu���ύX����
	this->MoveSpritePos( &workMove );

}
