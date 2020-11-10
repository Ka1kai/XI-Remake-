
#include "../../KaiFrameWorkHeader/DirectX9Header/CDirectX9Camera.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CDirectCamera::CDirectCamera( void )
{
	// �ʒu�E�����_�E����������
	this->Init();
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
CDirectCamera::~CDirectCamera( void )
{
}

//----------------------------------------------------
// ������
//----------------------------------------------------
bool CDirectCamera::Init( CONST int windowSizeX, CONST int windowSizeY )
{
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();

	D3DXMatrixIdentity( &m_view );
	D3DXMatrixIdentity( &m_projection );
	D3DXMatrixIdentity( &m_ortho );
	D3DXMatrixIdentity( &m_worldMtx );

	// �v���W�F�N�V�������W�ϊ��s��̎Z�o
	D3DXMatrixPerspectiveFovLH(&m_projection, D3DXToRadian( 45.0f ),
							   (float)windowSizeX / (float)windowSizeY,
							   1.0f,
							   2000.0f);
	
	// ���ˉe�ϊ����W�s��̎Z�o
	D3DXMatrixOrthoLH(&m_ortho,(float)windowSizeX,(float)-windowSizeY,1.0f,2000.0f);

	// �J�������W�ϊ��s��̎Z�o
	D3DXMatrixLookAtLH(&m_view, &m_vEye, &m_vAt, &m_vUp);
	
	// �J�����ƃv���W�F�N�V�����̕ϊ��s��̃Z�b�g
	pd3dDevice->SetTransform(D3DTS_VIEW, &m_view);
	pd3dDevice->SetTransform(D3DTS_PROJECTION, &m_projection);

	this->SetView();

	return true;
}//----------------------------------------------------

//----------------------------------------------------
// ������(�ʒu�{�����_�{����)
//----------------------------------------------------
bool CDirectCamera::Init( void )
{
	m_worldMtx._41 = 0.0f;	
	m_worldMtx._42 = 0.0f;	
	m_worldMtx._43 = -20.0f;	// �J�����̈ʒu���W
	m_worldMtx._31 = 0.0f;
	m_worldMtx._32 = 0.0f;	
	m_worldMtx._33 = 1.0f;		// �J�����̒����_���W
	m_worldMtx._21 = 0.0f;	
	m_worldMtx._22 = 1.0f;	
	m_worldMtx._23= 0.0f;		// �J�����̏�����x�N�g��	

	return true;
}

//----------------------------------------------------
// �J�����̃Z�b�g
//----------------------------------------------------
bool CDirectCamera::Set( void )
{
	CONST LPDIRECT3DDEVICE9 pd3dDevice = CDirectX9FrameWork::Getpd3dDevice();
	
	// �J�������W�ϊ��s��̎Z�o
	D3DXMatrixLookAtLH( &m_view, &m_vEye, &m_vAt, &m_vUp );
	
	// �J�����̃Z�b�g
	pd3dDevice->SetTransform( D3DTS_VIEW, &m_view );
	
	return true;
}

//----------------------------------------------------
// �J�����̈ʒu�Z�b�g
//----------------------------------------------------
bool CDirectCamera::SetPosition( CONST float xPos, CONST float yPos, CONST float zPos )
{
	m_worldMtx._41 = m_worldMtx._41 + xPos;
	m_worldMtx._42 = m_worldMtx._42 + yPos;
	m_worldMtx._43 = m_worldMtx._43 + zPos;
	
	// ���[���h�s��ɃZ�b�g�����ハ�[���h�ɔz�u
	this->SetView();

	return true;
}

//----------------------------------------------------
// �J�����̒����_�Z�b�g
//----------------------------------------------------
bool CDirectCamera::SetAt( CONST float xPos, CONST float yPos, CONST float zPos )
{
	m_worldMtx._31 = m_worldMtx._31 + xPos;
	m_worldMtx._32 = m_worldMtx._32 + yPos;
	m_worldMtx._33 = m_worldMtx._33 + zPos;

	// ���[���h�s��ɃZ�b�g�����ハ�[���h�ɔz�u
	this->SetView();

	return true;
}

//----------------------------------------------------
// �J�������[���h�s��̃Z�b�g
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

	// �J���������[���h�ɔz�u
	this->Set();

	return true;
}

//----------------------------------------------------
// ���f���̃x�N�g���𗘗p���Ă̒Ǐ]�J����
// ���f���̌��̈ʒu�ɃJ������u�����܂ܒǏ]�����
//----------------------------------------------------
void CDirectCamera::Tracking( CONST D3DXMATRIX* pMtx, CONST D3DXVECTOR3* pVec , CONST float distance)
{
	// �J�����̈ʒu�Z�b�g
	m_vEye.x = pVec->x * distance + pMtx->_41;
	m_vEye.y = pVec->y * distance + pMtx->_42;
	m_vEye.z = pVec->z * distance + pMtx->_43;
	
	// �J�����̒����_���W
	m_vAt.x = pMtx->_41;	
	m_vAt.y = pMtx->_42;
	m_vAt.z = pMtx->_43;	
	
	// �W���o�����b�N��h��
	m_vUp.x = pMtx->_21;	
	m_vUp.y = pMtx->_22;	
	m_vUp.z = pMtx->_23;

	// ���[���h�ʒu�ɃJ������z�u
	this->Set();

}

//----------------------------------------------------
// ��σJ����( �x�N�g�����l�����Ă��Ȃ� )
//----------------------------------------------------
void CDirectCamera::Tracking( CONST D3DXMATRIX* pMtx, CONST float at )
{
	// �J�����̒����_�X�V
	m_vAt.x = pMtx->_31 * at + pMtx->_41;	
	m_vAt.y = pMtx->_32 * at + pMtx->_42;
	m_vAt.z = pMtx->_33 * at + pMtx->_43;

	// �J�����̈ʒu�X�V
	m_vEye.x = pMtx->_41;	
	m_vEye.y = pMtx->_42;	
	m_vEye.z = pMtx->_43;

	// �J�����̏�����X�V(�W���o�����b�N��h���j
	m_vUp.x = pMtx->_21; 
	m_vUp.y = pMtx->_22; 
	m_vUp.z = pMtx->_23;

	// ���[���h�ʒu�ɔz�u
	this->Set();
}

//----------------------------------------------------
// �J�������������摜�`��i�r���{�[�h�j
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
// �J�����������Ă��ω����Ȃ��摜�`��i�r���{�[�h�j
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
// �N�H�[�^�j�I���̌v�Z
//----------------------------------------------------
bool CDirectCamera::CalcLocalQuaternion( CONST D3DXVECTOR3* pAxis, CONST float degree )
{
	D3DXQUATERNION	localQuater;
	D3DXMATRIX		rotationMat;

	D3DXMatrixIdentity( &rotationMat );

	// �s�񂩂�N�H�[�^�j�I���𐶐�
	D3DXQuaternionRotationMatrix( &localQuater, &m_worldMtx );

	// �C�ӂ̎�����]���Ƃ��ăN�H�[�^�j�I������]������
	D3DXQuaternionRotationAxis( &localQuater, pAxis, D3DXToRadian( degree ) );

	// �N�H�[�^�j�I������s������߂�
	D3DXMatrixRotationQuaternion( &rotationMat, &localQuater ); 
	D3DXMatrixMultiply( &m_worldMtx, &m_worldMtx,&rotationMat );

	// �J���������[���h�ɔz�u
	this->SetView();

	return true;
}

//----------------------------------------------------
// ���[�J���N�H�[�^�j�I��X��]
//----------------------------------------------------
void CDirectCamera::LocalRotationQuaterX( CONST float degree )
{
	D3DXVECTOR3		axis;

	axis.x = m_worldMtx._11;
	axis.y = m_worldMtx._12;
	axis.z = m_worldMtx._13;
	
	// �N�H�[�^�j�I���v�Z
	this->CalcLocalQuaternion( &axis, degree );
}

//----------------------------------------------------
// ���[�J���N�H�[�^�j�I��Y��]
//----------------------------------------------------
void CDirectCamera::LocalRotationQuaterY( CONST float degree )
{
	D3DXVECTOR3		axis;

	axis.x = m_worldMtx._21;
	axis.y = m_worldMtx._22;
	axis.z = m_worldMtx._23;
	
	// �N�H�[�^�j�I���v�Z
	this->CalcLocalQuaternion( &axis, degree );
}

//----------------------------------------------------
// ���[�J���N�H�[�^�j�I��Z��]
//----------------------------------------------------
void CDirectCamera::LocalRotationQuaterZ( CONST float degree )
{
	D3DXVECTOR3		axis;

	axis.x = m_worldMtx._31;
	axis.y = m_worldMtx._32;
	axis.z = m_worldMtx._33;
	
	// �N�H�[�^�j�I���v�Z
	this->CalcLocalQuaternion( &axis, degree );
}

//----------------------------------------------------
// ���[�J���C�ӎ��N�H�[�^�j�I����]
//----------------------------------------------------
void CDirectCamera::LocalRotationQuater( CONST D3DXVECTOR3* pVec, CONST float degree )
{
	D3DXVECTOR3		axis;

	axis.x = pVec->x;
	axis.y = pVec->y;
	axis.z = pVec->z;

	// �N�H�[�^�j�I����]�v�Z
	this->CalcLocalQuaternion( &axis, degree );
}