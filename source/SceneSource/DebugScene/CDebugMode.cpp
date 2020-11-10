
#include "CDebugMode.h"

C2DSpriteRHW	CDebugMode::m_pDebugMode;
LPSTR			CDebugMode::m_pDebugModeTexturePath;
bool			CDebugMode::m_isDebugMode;

float*			CDebugMode::m_pFps = nullptr;
int*			CDebugMode::m_pTime = nullptr;
C3DObjectShape	CDebugMode::m_pPlayerBox;

TDEBUGDICEBOX	CDebugMode::m_pDiceBox[49];

bool			CDebugMode::m_isCollisionBox;
bool			CDebugMode::m_isFps;

TFONTINFO		CDebugMode::m_font[ SELECT_DEBUG_NUM ];
int				CDebugMode::m_fontIndex;
bool			CDebugMode::m_debugOnOff;

int				CDebugMode::m_leftRightIndexDir;
int				CDebugMode::m_upDownIndexDir;
eDebugStatus	CDebugMode::m_eDebugStatus;
int				CDebugMode::m_debugIndex;

// �X�e�[�^�X�Ǘ��p�z��
const eDebugStatus debugStatus[ DEBUG_NUM ] = { 
eDebugStatus::FPS,
eDebugStatus::COLLISION_BOX,
eDebugStatus::GAME_TIME,
eDebugStatus::EXIT_DEBUG
};

const D3DXCOLOR defaultColor = DEFAULT_DEBUG_MODE_COLOR;

//----------------------------------------------------
// �R���X�g���N�^
//----------------------------------------------------
CDebugMode::CDebugMode( void )
{
}

//----------------------------------------------------
// �f�X�g���N�^
//----------------------------------------------------
CDebugMode::~CDebugMode( void )
{
}

//----------------------------------------------------
// ���[�h
//----------------------------------------------------
bool CDebugMode::Load( void )
{
	// �摜���[�h
	m_pDebugModeTexturePath = DEBUGMODE_PNGPATH;
	CResourceManager::GetInstance()->LoadTexture( m_pDebugModeTexturePath );
	m_pDebugMode.Init();
	m_pDebugMode.SetVertexPos( 400.0f,320.0f,800.0f,640.0f );
	m_pDebugMode.SetDiffuse( 0 , 255, 255, 200 );
	
	// �f�o�b�O�p�����쐬
	CResourceManager::GetInstance()->CreateXFont( 1, 12, 20 );

	return true;

}

//----------------------------------------------------
// ������
//----------------------------------------------------
bool CDebugMode::Init( void )
{
	// �f�o�b�O�e��̏��
	m_isCollisionBox = false;
	m_isFps = true;

	// �F�̐ݒ�
	for( int i = 0; i < SELECT_DEBUG_NUM; ++ i )
	{
		m_font[i].cheack = false;
		m_font[i].color = DEFAULT_DEBUG_MODE_COLOR;
	}

	// �����蔻��pAABB�\���t���OOFF
	for( int i = 0; i < 49; ++ i )
	{
		m_pDiceBox[i].isDice = false;
	}

	// �ŏ��̐F�̐ݒ�
	m_font[0].cheack = true;
	m_font[3].cheack = true;

	return true;
}

//----------------------------------------------------
// �f�o�b�O�p�l�̃Z�b�g
//----------------------------------------------------
void CDebugMode::Set( int* pTime )
{
	m_pTime = pTime;		// ���Ԃ̃A�h���X���Z�b�g
}

//----------------------------------------------------
// �f�o�b�O���[�h�̏�����( ���邽�тɖ��� )
//----------------------------------------------------
bool CDebugMode::InitDebugMode( void )
{
	// �f�o�b�O���[�h�t���OON
	m_isDebugMode = true;

	// �X�e�[�^�X�Ǘ��p�ϐ�
	m_debugIndex = 0;
	m_debugOnOff = true;		// ON
	m_eDebugStatus = eDebugStatus::FPS;
	m_leftRightIndexDir = 1;
	m_upDownIndexDir = 1;

	m_fontIndex = 0;
	for( int i = 0; i < SELECT_DEBUG_NUM; ++ i )
	{
		if( m_font[i].cheack == true )
		{
			m_font[i].color = SELECT_DEBUG_MODE_COLOR;
		}
		else
		{
			m_font[i].color = DEFAULT_DEBUG_MODE_COLOR;
		}
	}

	m_font[0].color = CHEACK_DEBUG_MODE_COLOR;

	return true;
}

//----------------------------------------------------
// �I��
//----------------------------------------------------
bool CDebugMode::Uninit( void )
{
	return true;
}

//----------------------------------------------------
// ����
//----------------------------------------------------
void CDebugMode::Run( CDirectCamera* camera )
{
 	float workDegree = 0.0f;
	// �f�o�b�O�̂��߂̃J������]
	if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_F10 ) )
	{
		workDegree = 1.0f;
		camera->LocalRotationQuaterY( workDegree );
	}

	if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_F9 ) )
	{
		workDegree = -1.0f;
		camera->LocalRotationQuaterY( workDegree );
	}

	if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_F8 ) )
	{
		workDegree = -1.0f;
		camera->LocalRotationQuaterX( workDegree );
	}

	if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_F7 ) )
	{
		workDegree = 1.0f;
		camera->LocalRotationQuaterX( workDegree );
	}
}

//----------------------------------------------------
// �f�o�b�O���[�h�̓���
//----------------------------------------------------
void CDebugMode::RunDebugMode( void )
{
	RunRight();		// �E����
	RunLeft();		// ������
	RunUp();		// �����
	RunDown();		// ������
	RunEnter();		// Enter����
}

//----------------------------------------------------
// �E����
//----------------------------------------------------
void CDebugMode::RunRight( void )
{
	if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_RIGHT ))
	{
		switch( m_eDebugStatus )
		{
			case eDebugStatus::EXIT_DEBUG:
				return;

			case eDebugStatus::GAME_TIME:
				DigitUpDown( m_pTime, m_pTime, 60 );
				break;

			default:
			if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_RIGHT ) )
			{
					// �������O�̐F�ύX
				if( m_font[ m_fontIndex ].cheack == true )
				{
					m_font[ m_fontIndex ].color = SELECT_DEBUG_MODE_COLOR;
				}
				else
				{
					m_font[ m_fontIndex ].color = DEFAULT_DEBUG_MODE_COLOR;
				}

				// ����������̐F�ύX
				if( m_debugOnOff == true )
				{
					m_fontIndex += 1;
				}
				else if( m_debugOnOff == false )
				{
					m_fontIndex -= 1;
				}

				m_font[ m_fontIndex ].color = CHEACK_DEBUG_MODE_COLOR;
				m_debugOnOff ^= true;

				break;
			}
		}

	}
}

//----------------------------------------------------
// ������
//----------------------------------------------------
void CDebugMode::RunLeft( void )
{
	if( CInputKeyboard::GetInstance()->GetPressKeyState( VK_LEFT ))
	{
		switch( m_eDebugStatus )
		{
			case eDebugStatus::EXIT_DEBUG:
				return;

			case eDebugStatus::GAME_TIME:
				DigitUpDown( m_pTime, m_pTime, -60 );
				break;

			default:
			if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_LEFT ) )
			{
					// �������O�̐F�ύX
				if( m_font[ m_fontIndex ].cheack == true )
				{
					m_font[ m_fontIndex ].color = SELECT_DEBUG_MODE_COLOR;
				}
				else
				{
					m_font[ m_fontIndex ].color = DEFAULT_DEBUG_MODE_COLOR;
				}

				// ����������̐F�ύX
				if( m_debugOnOff == true )
				{
					m_fontIndex += 1;
				}
				else if( m_debugOnOff == false )
				{
					m_fontIndex -= 1;
				}
				m_font[ m_fontIndex ].color = CHEACK_DEBUG_MODE_COLOR;
				m_debugOnOff ^= true;

				break;
			}
		}

	}


}

//----------------------------------------------------
// �����
//----------------------------------------------------
void CDebugMode::RunUp( void )
{
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_UP ) )
	{
		if( m_font[ m_fontIndex ].cheack == true )
		{
			m_font[ m_fontIndex ].color = SELECT_DEBUG_MODE_COLOR;
		}
		else 
		{
			m_font[ m_fontIndex ].color = DEFAULT_DEBUG_MODE_COLOR;
		}
		

		// ������ԁ��̏ꍇ
		if(  m_fontIndex <= 1 )
		{
			m_fontIndex = SELECT_DEBUG_NUM - 1;
			m_debugIndex = DEBUG_NUM - 1;
		}
		else 
		{
			if( m_eDebugStatus == eDebugStatus::EXIT_DEBUG )
			{
				m_fontIndex -= 1;
			}
			else if( m_eDebugStatus == eDebugStatus::GAME_TIME )
			{
				m_fontIndex -= 2;
				m_debugOnOff = true;
			}
			else
			{	
				m_fontIndex -= 2;
			}
						
			m_debugIndex -= 1;
		}

		m_eDebugStatus = debugStatus[ m_debugIndex ];	
		m_font[ m_fontIndex ].color = CHEACK_DEBUG_MODE_COLOR;
	}

}

//----------------------------------------------------
// ������
//----------------------------------------------------
void CDebugMode::RunDown( void )
{
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_DOWN ))
	{
		if( m_font[ m_fontIndex ].cheack == true )
		{
			m_font[ m_fontIndex ].color = SELECT_DEBUG_MODE_COLOR;
		}
		else if( m_font[ m_fontIndex ].cheack == false )
		{
			m_font[ m_fontIndex ].color = DEFAULT_DEBUG_MODE_COLOR;
		}
		
		// ���L�[���͂����Ƃ��Ɉ�ԉ���Exit���I������Ă�����
		if( m_fontIndex == SELECT_DEBUG_NUM - 1 )
		{
			m_fontIndex = 0;
			m_debugIndex = 0;
			m_leftRightIndexDir = 1;
			m_debugOnOff = true;
			m_eDebugStatus = debugStatus[ m_debugIndex ];
		}
		// ���L�[�ʏ�I�����
		else
		{
			m_debugIndex += 1;
			m_eDebugStatus = debugStatus[ m_debugIndex ];
			if( ( m_eDebugStatus == eDebugStatus::GAME_TIME && m_debugOnOff == false ) ||
				  m_eDebugStatus == eDebugStatus::EXIT_DEBUG  )
			{
				m_fontIndex += 1;
			}
			else
			{
				m_fontIndex += 2;
			}
		}

		m_font[ m_fontIndex ].color = CHEACK_DEBUG_MODE_COLOR;
	}
}

//----------------------------------------------------
// Enter����
//----------------------------------------------------
void CDebugMode::RunEnter( void )
{
	// �m��{�^��(ENTER)
	if( CInputKeyboard::GetInstance()->GetTriggerKeyState( VK_RETURN ) )
	{
		switch( m_eDebugStatus )
		{
			// FPS�\��
			case eDebugStatus::FPS:
				m_isFps = m_debugOnOff;
				DebugONOFF( m_isFps, &m_font[0], &m_font[1] );
				break;

			// �����蔻��p�{�b�N�X
			case eDebugStatus::COLLISION_BOX:
				m_isCollisionBox = m_debugOnOff;
				DebugONOFF( m_isCollisionBox, &m_font[2], &m_font[3] );
				break;

			// �Q�[���̎���
			case eDebugStatus::GAME_TIME:
				
				break;

			// Exit
			case eDebugStatus::EXIT_DEBUG:
				m_isDebugMode = false;
				break;
		}
	}
}

//----------------------------------------------------
// �`��
//----------------------------------------------------
void CDebugMode::Draw( void )
{
	// FPS�\��
	if( m_isFps == true )
	{
		CResourceManager::GetInstance()->GetXFont( 1 )->DrawColor( 0, 0, D3DXCOLOR( 255,255,255,255 ), "FPS:%4.2f", *m_pFps );
	}

	// �����蔻��p�{�b�N�X
	if( m_isCollisionBox == true )
	{
		// �v���C���[�pAABB
		CDirectDrawSystem::GetInstance()->DrawShape( m_pPlayerBox.GetWorldMtx(), m_pPlayerBox.GetMaterial(), m_pPlayerBox.GetMesh() );

		// �_�C�X�pAABB
		for( int i= 0; i< 49; ++ i )
		{
			if( m_pDiceBox[i].isDice == true )
			{
				CDirectDrawSystem::GetInstance()->DrawShape( m_pDiceBox[i].diceBox.GetWorldMtx(), m_pDiceBox[i].diceBox.GetMaterial(), m_pDiceBox[i].diceBox.GetMesh() );
			}
		}
	}
}

//----------------------------------------------------
// �f�o�b�O���[�h��ʂ̕`��
//----------------------------------------------------
void CDebugMode::DrawDebugMode( void )
{
	// �w�i
	CDirectDrawSystem::GetInstance()->DrawSpriteRHW( CResourceManager::GetInstance()->GetTexture( m_pDebugModeTexturePath )->Get(),m_pDebugMode.GetVertex() );

	// �^�C�g��
	CResourceManager::GetInstance()->GetXFont( 1 )->DrawColor( 340, 110, D3DXCOLOR(255,255,0,255), "Debug Mode" );

	// FPS
	CResourceManager::GetInstance()->GetXFont( 1 )->DrawColor( 100, 150, defaultColor, "FPS" );
	CResourceManager::GetInstance()->GetXFont( 1 )->DrawColor( 400, 150, m_font[0].color, "ON" );
	CResourceManager::GetInstance()->GetXFont( 1 )->DrawColor( 500, 150, m_font[1].color, "OFF" );


	// �����蔻��pAABBBOX�̕\��
	CResourceManager::GetInstance()->GetXFont( 1 )->DrawColor( 100, 180, defaultColor, "HitCheack AABBBOX" );
	CResourceManager::GetInstance()->GetXFont( 1 )->DrawColor( 400, 180, m_font[2].color, "ON" );
	CResourceManager::GetInstance()->GetXFont( 1 )->DrawColor( 500, 180, m_font[3].color, "OFF" );

	// Time
	CResourceManager::GetInstance()->GetXFont( 1 )->DrawColor( 100, 210, defaultColor, "Time Change" );
	CResourceManager::GetInstance()->GetXFont( 1 )->DrawColor( 400, 210, m_font[4].color, "%d", *m_pTime );

	// Exit
	CResourceManager::GetInstance()->GetXFont( 1 )->DrawColor( 380, 500, m_font[ SELECT_DEBUG_NUM - 1 ].color, "Exit" );

}

//----------------------------------------------------
// �f�o�b�O��ON/OFF�̐؂�ւ�
//----------------------------------------------------
void CDebugMode::DebugONOFF( bool isOnOff, TFONTINFO* font, TFONTINFO* font2 )
{
	if( isOnOff == true )
	{
		font->cheack = true;
		font2->cheack = false;
		font2->color = DEFAULT_DEBUG_MODE_COLOR;
	}
	else if( isOnOff == false )
	{
		font->cheack = false;
		font->color = DEFAULT_DEBUG_MODE_COLOR;
		font2->cheack = true;
	}
}

//----------------------------------------------------
// �l�̒���
//----------------------------------------------------
int* CDebugMode::DigitUpDown( int* pOut, int* pDigit, int value )
{
	*pOut = *pDigit + value;

	return pOut;
}