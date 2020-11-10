
#include "../../KaiFrameWorkHeader/DebugHeader/CDebugStage.h"

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CDebugStage::CDebugStage( void )
{
	m_lineNum = 0;
	m_pLineStage = new tagTDEBUGVERTEX;
}

//----------------------------------------------------
// �R���X�g���N�^( ���C������ݒ� )
//----------------------------------------------------
CDebugStage::CDebugStage( CONST UINT lineNum )
{
	m_lineNum = lineNum;
	m_pLineStage = new tagTDEBUGVERTEX[ lineNum ];
}

//----------------------------------------------------
// �f�X�g���N�^ 
//----------------------------------------------------
CDebugStage::~CDebugStage( void )
{
	SAFE_DELETE_ALLAY( m_pLineStage );
}

//----------------------------------------------------
// ������ ���_�𒆐S�Ƃ��������`
//----------------------------------------------------
void CDebugStage::Init( CONST FLOAT  lineLen )
{
	float width = lineLen /  ( (m_lineNum - 1 ) / 2 / 2 );
	float lineWidth = lineLen / 2;
	int	j = 0;

	for( UINT i = 0; i < m_lineNum / 2; i += 2 ){
		m_pLineStage[i].pos.x = lineWidth;
		m_pLineStage[i+1].pos.x = -lineWidth;
		m_pLineStage[i].pos.y = -10.0f;
		m_pLineStage[i+1].pos.y = -10.0f;
		m_pLineStage[i].pos.z = lineWidth - j * width;
		m_pLineStage[i+1].pos.z = lineWidth - j * width;
		m_pLineStage[i].color = D3DCOLOR_RGBA( 255,255,255,255 );
		m_pLineStage[i+i].color = D3DCOLOR_RGBA( 255,255,255,255 );
		j ++;
	}

	j = 0;
	
	for( UINT i = m_lineNum / 2; i < m_lineNum; i += 2 ){
		
		m_pLineStage[i].pos.x = lineWidth - j * width;
		m_pLineStage[i+1].pos.x = lineWidth - j * width;
		m_pLineStage[i].pos.y = -10.0f;
		m_pLineStage[i+1].pos.y = -10.0f;
		m_pLineStage[i].pos.z = lineWidth;
		m_pLineStage[i+1].pos.z = -lineWidth;
		m_pLineStage[i].color = D3DCOLOR_RGBA( 255,255,255,255 );
		m_pLineStage[i+1].color = D3DCOLOR_RGBA( 255,255,255,255 );
		j ++;
	}
	
}

//----------------------------------------------------
// �I��
//----------------------------------------------------
void CDebugStage::Uninit( void )
{
}





