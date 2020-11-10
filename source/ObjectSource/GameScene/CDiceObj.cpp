
#include "CDiceObj.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CDiceObj::CDiceObj( void )
{
	m_pAABB = new THITAABB;
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
CDiceObj::~CDiceObj( void )
{
	SAFE_DELETE( m_pAABB );
}

//----------------------------------------------------
// ������
//----------------------------------------------------
void CDiceObj::Init( void )
{
	C3DObjectAlphaBlend::Init();
	D3DXMatrixIdentity( &m_rotTemp );			// ��]�ۑ��p�s���������
	m_logPos = D3DXVECTOR3( 0.0f,0.0f,0.0f );	// ��]�p�ۑ��x�N�g����������

	m_no = 0;									// ���ʔԍ���0�ɐݒ�
	m_indexNo = 0;								// �Y�����ԍ���0�ɐݒ�
	m_size = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_isDice = false;							// �o���t���O�I�t
	m_status = DICE_STATUS::e_statusNone;		// �o�����Ă��Ȃ���Ԃɂ��Ă���
	m_beforStatus = DICE_STATUS::e_statusNone;	// �O��̏�Ԃ�������Ԃɂ��Ă���
	m_animeCnt = 0;								// �A�j���[�V�����J�E���g
	m_chainNo = 0;								// �`�F�C���ԍ���������
	m_isChain = false;							// �`�F�C�����ĂȂ���ԂɃZ�b�g

	// �����蔻��̏�����
	D3DXVECTOR3 aabbPos = D3DXVECTOR3( this->GetXPos(), this->GetYPos(), this->GetZPos() );
	m_pAABB = CCollision::GetInstance()->SetAABB( m_pAABB, &aabbPos, &m_size );

	this->InitPip();	// ��ʔ���p�z�񏉊���
}

//----------------------------------------------------
// ��]����O�̏�����
//----------------------------------------------------
bool CDiceObj::InitRoll( void )
{
	m_logPos = this->GetWorldMtx()->m[3];					// ���݂̃��[���h�s���ۑ�
	CopyRotationMatrix( &m_rotTemp, this->GetWorldMtx() );	// ��]�s���ۑ�

	return true;
}

//----------------------------------------------------
// ��ʔ���p�z��̏�����
//----------------------------------------------------
bool CDiceObj::InitPip( void )
{	
	// �T�C�R���̏�ʔ���z��Ƀf�[�^���i�[
	for( int i = 0; i < 7; ++ i )
	{
		m_dicePipAllay[ i ] = i;
	}

	return true;
}

//----------------------------------------------------
// X��]���Ĉړ�
//----------------------------------------------------
void CDiceObj::MoveX( float x, float y, float z, float rotDir, float speed )
{
	D3DXMATRIX transMtx,lRotMtx,wRotMtx;

	// ���𒆐S����ړ������邽�߂̍s��쐬
	D3DXMatrixTranslation( &transMtx, x, y, z );
	
	// ��]�s����쐬
	D3DXMatrixRotationZ(&lRotMtx,D3DXToRadian( speed * rotDir ) );	// x��]

	// �ړ��s��Ɖ�]�s���������
	D3DXMatrixMultiply( &wRotMtx, &transMtx, &lRotMtx );

	// ���[���h�s��ɃZ�b�g�i���S���W�����ɖ߂��j
	this->CalcWorldMtx( &m_rotTemp,&wRotMtx );
	this->MoveWorldPos( m_logPos.x - x, m_logPos.y - y, m_logPos.z - z );

}

//----------------------------------------------------
// Z��]���Ĉړ�
//----------------------------------------------------
void CDiceObj::MoveZ( float x, float y, float z, float rotDir, float speed )
{
	D3DXMATRIX transMtx,lRotMtx,wRotMtx;
	D3DXMatrixIdentity( &transMtx );
	D3DXMatrixIdentity( &lRotMtx );
	D3DXMatrixIdentity( &wRotMtx );

	// ���𒆐S����ړ������邽�߂̍s��쐬
	D3DXMatrixTranslation( &transMtx, x, y, z );
	
	// ��]�s����쐬
	D3DXMatrixRotationX(&lRotMtx,D3DXToRadian( speed * rotDir ) );	// z��]

	// �ړ��s��Ɖ�]�s���������
	D3DXMatrixMultiply( &wRotMtx, &transMtx, &lRotMtx);	

	// ���[���h�s��ɃZ�b�g�i���S���W�����ɖ߂��j
	this->CalcWorldMtx( &m_rotTemp, &wRotMtx );
	this->MoveWorldPos( m_logPos.x - x, m_logPos.y - y, m_logPos.z - z );
}

//----------------------------------------------------
// X��]�̂�
//----------------------------------------------------
void CDiceObj::RollX( float degree )
{
	D3DXMATRIX lRotMtx;

	this->InitRoll();	// ��]�̂��߂̏�����

	// ��]�s����쐬
	D3DXMatrixRotationX(&lRotMtx,D3DXToRadian( degree ) );

	// ���[���h�s��ɃZ�b�g�i���S���W�����ɖ߂��j
	this->CalcWorldMtx( &m_rotTemp, &lRotMtx );
	this->MoveWorldPos( m_logPos.x, m_logPos.y, m_logPos.z );
}

//----------------------------------------------------
// Y��]�̂�
//----------------------------------------------------
void CDiceObj::RollY( float degree )
{
	D3DXMATRIX lRotMtx;

	this->InitRoll();	// ��]�̂��߂̏�����

	// ��]�s����쐬
	D3DXMatrixRotationY(&lRotMtx,D3DXToRadian( degree ) );

	// ���[���h�s��ɃZ�b�g�i���S���W�����ɖ߂��j
	this->CalcWorldMtx( &m_rotTemp, &lRotMtx );
	this->MoveWorldPos( m_logPos.x, m_logPos.y, m_logPos.z );
}

//----------------------------------------------------
// Z��]�̂�
//----------------------------------------------------
void CDiceObj::RollZ( float degree )
{
	D3DXMATRIX lRotMtx;
	D3DXMatrixIdentity( &lRotMtx );

	this->InitRoll();	// ��]�̂��߂̏�����

	// ��]�s����쐬
	D3DXMatrixRotationZ(&lRotMtx,D3DXToRadian( degree ) );

	// ���[���h�s��ɃZ�b�g�i���S���W�����ɖ߂��j
	this->CalcWorldMtx( &m_rotTemp, &lRotMtx );
	this->MoveWorldPos( m_logPos.x, m_logPos.y, m_logPos.z );
}

//----------------------------------------------------
// ��]���������ɉ�]�����������ɂ���ē����̖ڂ�ς���
//----------------------------------------------------
void CDiceObj::RollChangePip( CONST USHORT rollState )
{
	m_dicePipAllay[0] = m_dicePipAllay[1];	// �ۑ��p�ɏ�ʂ̔ԍ��ۑ�

	switch( rollState )
	{
		// �E��]
		case ROLL_RIGTH_PIP:
			m_dicePipAllay[1] = m_dicePipAllay[2];
			m_dicePipAllay[2] = m_dicePipAllay[6];
			m_dicePipAllay[6] = m_dicePipAllay[5];
			m_dicePipAllay[5] = m_dicePipAllay[0];
			break;

		// ����]
		case ROLL_LEFT_PIP:
			m_dicePipAllay[1] = m_dicePipAllay[5];
			m_dicePipAllay[5] = m_dicePipAllay[6];
			m_dicePipAllay[6] = m_dicePipAllay[2];
			m_dicePipAllay[2] = m_dicePipAllay[0];
			break;

		// �O��]
		case ROLL_FRONT_PIP:
			m_dicePipAllay[1] = m_dicePipAllay[3];
			m_dicePipAllay[3] = m_dicePipAllay[6];
			m_dicePipAllay[6] = m_dicePipAllay[4];
			m_dicePipAllay[4] = m_dicePipAllay[0];
			break;

		// ���]
		case ROLL_BACK_PIP:
			m_dicePipAllay[1] = m_dicePipAllay[4];
			m_dicePipAllay[4] = m_dicePipAllay[6];
			m_dicePipAllay[6] = m_dicePipAllay[3];
			m_dicePipAllay[3] = m_dicePipAllay[0];
			break;

		// ���E180����]
		case ROLL_HALFH_PIP:
			m_dicePipAllay[1] = m_dicePipAllay[6];
			m_dicePipAllay[6] = m_dicePipAllay[0];
			m_dicePipAllay[0] = m_dicePipAllay[2];
			m_dicePipAllay[2] = m_dicePipAllay[5];
			m_dicePipAllay[5] = m_dicePipAllay[0];
			break;

		// �O��180����]
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
// ��ʂ���]���Ȃ���]���������̓����̖ڂ�ς���
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
// ��ʂƎ���̖ʂ𓯎��ɃZ�b�g
//----------------------------------------------------
void CDiceObj::SetPip( CONST UINT upperFace, CONST UINT rollNum )
{
	this->SetUpperPip( upperFace );
	this->SetAroundPip( rollNum );
}

//----------------------------------------------------
// ��ʂ��Z�b�g(�P�`�U)
//----------------------------------------------------
void CDiceObj::SetUpperPip( CONST UINT upperFace )
{
	switch( upperFace )
	{
	case 1:
		// 1�̏ꍇ�͉������Ȃ�
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
// ����̖ʂ��Z�b�g(�O�`�R�j
//----------------------------------------------------
void CDiceObj::SetAroundPip( CONST UINT rollNum )
{
	// �񐔕��E��]������
	for( UINT i = 0; i < rollNum; ++ i )
	{
		this->RollY( -90.0f );
		this->RollYChangePip();
	}
}

//----------------------------------------------------
// ���ŃA�j���[�V����
//----------------------------------------------------
bool CDiceObj::DownAnimation( CONST float downSpeed )
{
	float speed = downSpeed;
	// �����̒l��0���傫���ꍇ��-1����Z
	if( speed > 0.0f ) 
	{
		speed *= -1;
	}

	// �ʒu�ύX
	this->MoveWorldPos( 0.0f, speed,0.0f );

	// �����苗����������F��ύX
	if( this->GetYPos() <= -2.0 && m_status == DICE_STATUS::e_statusStartDelete )
	{
		this->SetColor( 255,0,0,127 );
		return true;
	}

	// ��������_�C�X���Ȃ���
	if( this->GetYPos() <= -4.0f && m_status == DICE_STATUS::e_statusDelete )
	{
		this->SetIsDice( false );
		return true;
	}

	return false;
}

//----------------------------------------------------
// �o���A�j���[�V����
//----------------------------------------------------
bool CDiceObj::UpAnimation( CONST float upSpeed )
{
	float speed = upSpeed;

	// �����̒l��0��菬�����ꍇ��-1�����U
	if( speed < 0.0f )
	{
		speed *= -1;
	}

	// �ʒu���Z�b�g
	this->MoveWorldPos( 0.0f, speed, 0.0f );

	// ������x�o�Ă�����F�ύX
	if( this->GetWorldMtx()->_42 >= -2.0f && m_status == e_statusStartAppear )
	{
		this->SetColor( 255,255,255,255);
		this->SetIsDice( true );
		return true;
	}

	// �o�Ă�����
	if( this->GetWorldMtx()->_42 >= 0.0f && m_status == e_statusAppear )
	{
		return true;
	}

	return false;
}