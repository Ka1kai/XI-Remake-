//----------------------------------------------------
// CColision Header
//	�����蔻����܂Ƃ߂��w�b�_�[
//
// @date	2013/6/15
// @author	T.Kawashita
//----------------------------------------------------
#ifndef _C_COLISION_H_
#define _C_COLISION_H_

#include <d3dx9.h>
#include <math.h>

//----------------------------------------------------
// �o�E���f�B���O�X�t�B�A�\���̒�`
//----------------------------------------------------
typedef	struct tagTHITCIRCLE
{
	D3DXVECTOR3 boxCenter;	// �o�E���f�B���O�X�t�B�A���S���W
	float		r;			// �o�E���f�B���O�X�t�B�A���a
}THITCIRCLE;

//----------------------------------------------------
// ���b�V���f�[�^�\���̒�`
//----------------------------------------------------
typedef struct tagTMESHDATA
{
	D3DXVECTOR3	center;
	D3DXVECTOR3 size;
	D3DXVECTOR3 maxSize;
	D3DXVECTOR3 minSize;
	float		rect;
}TMESHDATA;

//----------------------------------------------------
// AABB�����蔻��p�\���̒�`
//----------------------------------------------------
typedef struct tagTHITAABB
{
	D3DXVECTOR3 centerPos;	// AABB�̒��S���W
	D3DXVECTOR3 size;		// AABB�̃T�C�Y
	D3DXVECTOR3 halfSize;	// AABB�̔����̃T�C�Y
}THITAABB;

//----------------------------------------------------
// OBB�p�\���̒�`
//----------------------------------------------------
typedef struct tagTHITOBB
{
	D3DXVECTOR3	position;			// �ʒu���
	D3DXVECTOR3	normalDir[3];		// �e�������
	FLOAT		normalLength[3];	// �e���̒���
}THITOBB;

//----------------------------------------------------
// ���ʕ����������S�̌W��
//----------------------------------------------------
typedef struct tagPLANE
{
	FLOAT a,b,c,d;		
}TPLANE;


class CCollision
{
private:
	CCollision		( void ){}								// �R���X�g���N�^��h��
	CCollision		( CONST CCollision& colObj ){}			// �R�s�[�R���X�g���N�^��h��
	CCollision	operator= ( CONST CCollision& colObj ){}	// �����o�̑����h��

public:
	
	// �B��̃C���X�^���X�̎擾
	static CCollision* GetInstance	( void )
	{
		static CCollision pDirectCollision;
		return &pDirectCollision;
	}

	// �f�X�g���N�^
	~CCollision	(void){}

	/*
//====================================================
// ���g(��`)�Ɠ_�̓����蔻��
//====================================================

bool CDirectGraphics2D::HitPoint2Rect(float x, float y)
{
	if((ver[0].pos.x+objData.centerX < x && ver[1].pos.x+objData.centerX > x) &&
		(ver[0].pos.y+objData.centerY < y && ver[2].pos.y+objData.centerY > y))
		return true;

	return false;
}

//====================================================
// ���g(�~)�Ɠ_�̓����蔻��
//====================================================
bool CDirectGraphics2D::HitPoint2Circle(float x, float y, float r)
{
	double	workX, workY;

	workX = pow((x - objData.centerX), 2);
	workY = pow((y - objData.centerY), 2);

	if((workX+workY) <= pow(r, 2))
		return true;

	return false;
}

*/

	//----------------------------------------------------
	// @name	IsHitCircle
	// @content ���̓��m�̏Փ˔���
	// @param	circle1		����1
	// @param	circle2		����2
	// @return	���̓��m�Փ˂��Ă��邩�ǂ���
	// @date	2013/9/10
	//----------------------------------------------------
	bool	IsHitCircle		( CONST THITCIRCLE* circle1, CONST THITCIRCLE* circle2 );

	//----------------------------------------------------
	// @name	IsHitAABB
	// @content	AABB���m�̓����蔻��
	// @param	aabb1		AABB1
	// @param	aabb2		AABB2
	// @return	AABB���m�Փ˂��Ă��邩�ǂ���
	// @date	2014/1/15
	//----------------------------------------------------
	bool	IsHitAABB		( CONST THITAABB* aabb1, CONST THITAABB* aabb2 );

	//----------------------------------------------------
	// @name	IsHitOBB
	// @content	OBB�ɂ��Փ˔���
	// @param	obb1	OBB1
	// @param	obb2	OBB2
	// @return	OBB���m�Փ˂��Ă��邩�ǂ���
	// @date	2013/9/10
	//----------------------------------------------------
	bool	IsHitOBB		( CONST THITOBB* obb1,CONST THITOBB* obb2 );

public:
	//----------------------------------------------------
	// @name	SetOBB
	// @content	OBB�\���̂ɃZ�b�g
	// @param	pOutOBB*	�Z�b�g����OBB�\���̂̃|�C���^
	// @param	pInLen		�e���̒���
	// @param	PInMtx		���f���s��
	// @return	THITOBB		�����蔻��Ɏg��OBB�\����
	// @date	2013/9/10
	//----------------------------------------------------
	THITOBB*	SetOBB			( THITOBB* pOutOBB, CONST D3DXVECTOR3* pInLen, CONST D3DXMATRIX* pInMtx );  
	
	//----------------------------------------------------
	// @name	SetAABB
	// @content	AABB�\���̂ɃZ�b�g
	// @param	pOutAABB*		�Z�b�g������AABB�\���̃|�C���^
	// @param	pInPos			�Z�b�g���������S���W
	// @param	pInSize			�Z�b�g������AABB�̃T�C�Y
	// @return	THITAABB*		�Z�b�g����AABB�\���̃|�C���^
	// @date	2014/1/15
	//----------------------------------------------------
	THITAABB*	SetAABB			( THITAABB* pOutAABB, CONST D3DXVECTOR3* pInPos, CONST D3DXVECTOR3* pInSize );

	//----------------------------------------------------
	// @name	GetMeshData
	// @content	���b�V�����烁�b�V���f�[�^�𔲂��o��
	// @param	pOutMeshData	�����o���������b�V���f�[�^�\���̃|�C���^
	// @param	mesh			�����o���������b�V��
	// @return	TMESHDATA*		�����o�������b�V���f�[�^
	// @date	2014/1/15
	//----------------------------------------------------
	TMESHDATA* GetMeshData	( TMESHDATA* pOutMeshData, LPD3DXMESH lpMesh );

	//----------------------------------------------------
	// @name	CalcLenSegOnSeparateAxis
	// @content	�������ɓ��e���ꂽ���������瓊�e���������Z�o
	// @param	pSepAis	������
	// @param	e1		������1
	// @param	e2		������2
	// @param	e3		������3
	// @return	���e���ꂽ�����̒���
	// @date	2013/9/10
	//-----------------------------------------------------
	float CalcLenSegOnSeparateAxis( D3DXVECTOR3 *pSepAxis, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = nullptr );
	
	//----------------------------------------------------
	// @name	CreatePlaneInfo
	// @content	���ʕ����������߂�
	// @param	pOutPlane	���߂����ʕ�����
	// @param	v1			3�p�`�̒��_���W
	// @param	v2			3�p�`�̒��_���W
	// @param	v3			3�p�`�̒��_���W
	// @return	���߂����ʕ�����
	// @date	2013/9/10
	//----------------------------------------------------
	TPLANE* CreatePlaneInfo( TPLANE* pOutPlane, CONST D3DXVECTOR3* v1, CONST D3DXVECTOR3* v2, CONST D3DXVECTOR3* v3 );

	//----------------------------------------------------
	// @name	LineToPlaneCross
	// @content	�����ƕ��ʂ̌�_�����߂�
	// @param	pOutCross	���߂���_���W
	// @param	plane		���ʕ�����
	// @param	vTriPos		3�p�`�̂ǂꂩ��̒��_���W
	// @param	vStartPos	�������ʂ�_(���W)
	// @param	vDir		�����ƕ��s�ȃx�N�g��
	// @return	��_�����߂邱�Ƃ��o������
	// @date	2013/9/10
	//----------------------------------------------------
	bool LineToPlaneCross( D3DXVECTOR3* pOutCross, CONST TPLANE* plane, CONST D3DXVECTOR3* vTriPos, CONST D3DXVECTOR3* vStartPos, D3DXVECTOR3* vDir );	

	//----------------------------------------------------
	// name		CheckInTriangle
	// @content	3�p�`�̓����ɂ��邩�ǂ����𔻒�
	// @param	v1		���_���W1
	// @param	v2		���_���W2
	// @param	v3		���_���W3
	// @param	pos		���肵�������W
	// @return	3�p�`�̓����ɂ��邩�ǂ���
	// @date	2013/9/10
	//----------------------------------------------------
	bool CheckInTriangle( CONST D3DXVECTOR3* v1, CONST D3DXVECTOR3* v2,	CONST D3DXVECTOR3* v3, CONST D3DXVECTOR3* pos );

	//----------------------------------------------------
	// @name	LengthPontToPlane
	// @content	���ʂƂ̋��������߂�
	// @param	pOutCrossPos	�o�͂����_���W
	// @param	vStartPos		���_�ƂȂ���W
	// @param	plane			���ʕ�����
	// @return	���ʂƎn�_�̋���
	// @date	2013/9/10
	//----------------------------------------------------
	float LengthPointToPlane( D3DXVECTOR3* pOutCrossPos, CONST D3DXVECTOR3* vStartPos, CONST TPLANE* plane );
};

#endif _C_COLISION_H_