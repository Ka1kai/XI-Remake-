/*************************************************************
*	@file   	CDebugConsole.h
*	@brief  	CDebugConsole�N���X�w�b�_�[
*	@note		����
*	@author		Tatsunori Aoyama
*	@date		2013/04/17
*************************************************************/

#ifndef _Include_CDebugConsole_h_	// �C���N���[�h�K�[�h
#define _Include_CDebugConsole_h_

//------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------
#include<Windows.h>
#include<string>

//------------------------------------------------------------
// �萔�A�\���̒�`
//------------------------------------------------------------
enum CONSOLECOLOR {
	L_BLACK = 0,
	L_BLUE,
	L_GREEN,
	L_CYAN,
	L_RED,
	L_PURPLE,
	L_YELLOW,
	L_WHITE,

	H_BLACK,
	H_BLUE,
	H_GREEN,
	H_CYAN,
	H_RED,
	H_PURPLE,
	H_YELLOW,
	H_WHITE
};

/*!-----------------------------------------------------------
//	@class  CDebugConsole
//	@brief  �f�o�b�O�p�̃R���\�[��
//	@note	����
//	@author	Tatsunori Aoyama
//	@date	2013/04/17
------------------------------------------------------------*/
class CDebugConsole
{
public:
	/// �R���X�g���N�^
	CDebugConsole()
	{
		m_pFile = nullptr;
		SMALL_RECT	rc = {0,0,1024,512};
		COORD		cd = {rc.Right+1,rc.Bottom+1};
		::AllocConsole();	//�R���\�[���̊m��
		m_hStdOut	= GetStdHandle( STD_OUTPUT_HANDLE );
		SetConsoleScreenBufferSize(m_hStdOut, cd);
		SetConsoleWindowInfo(m_hStdOut,TRUE,&rc);
		m_backColor	= L_BLACK;
		m_textColor	= L_WHITE;
		this->SetColorF(H_RED);
		CDebugConsole::Printf("[==================== Start Up Debug Console ====================]\n\n");
		this->SetColorF(m_textColor);
	}

	/// �f�X�g���N�^
	~CDebugConsole()
	{
		this->Destory();
	}

	/*!-----------------------------------------------------------
	//	@brief		�������
	//	@note		���ɂȂ�
	//	@param[in]	�Ȃ�
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/12/03
	------------------------------------------------------------*/
	void	Destory()
	{
		if( m_hStdOut == nullptr )
			return;

		if( m_pFile != nullptr )
			fclose(m_pFile);
		//�R���\�[���̉��
		::FreeConsole();
		m_hStdOut = nullptr;
	}

	/*!-----------------------------------------------------------
	//	@brief		�t�@�C���|�C���^�I�[�v��
	//	@note		���ɂȂ�
	//	@param[in]	fileName	�쐬����t�@�C����
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/08/05
	------------------------------------------------------------*/
	void	CreateDebugLog(LPCTSTR fileName)
	{
		fopen_s(&m_pFile,fileName,"w");
	}

	/*!-----------------------------------------------------------
	//	@brief		�J�[�\���̑傫���Ɖ��ݒ�
	//	@note		���ɂȂ�
	//	@param[in]	dwSize    �J�[�\���̑傫��
	//	@param[in]	isVisible ���ݒ�
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/04/27
	------------------------------------------------------------*/
	void SetCursorInfo( DWORD dwSize = 25, BOOL isVisible = TRUE )
	{
		CONSOLE_CURSOR_INFO info = { dwSize, isVisible };
		::SetConsoleCursorInfo( m_hStdOut, &info );
	}

	/*!-----------------------------------------------------------
	//	@brief		�R���\�[���J�[�\���̈ʒu�ݒ�
	//	@note		���ɂȂ�
	//	@param[in]	x X���W
	//	@return		y Y���W
	//	@author		Tatsunori Aoyama
	//	@date		2013/04/27
	------------------------------------------------------------*/
	void SetCursorPosition( int x, int y )
	{
		COORD coord = { (short)x, (short)y };
		::SetConsoleCursorPosition( m_hStdOut, coord );
	}

	/*!-----------------------------------------------------------
	//	@brief		�w�i�F��ύX
	//	@note		���ɂȂ�
	//	@param[in]	backColor �w�i�F
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/04/27
	------------------------------------------------------------*/
	void SetColorB( WORD backColor = L_BLACK ){
		this->SetColor( backColor, m_textColor );
	}

	/*!-----------------------------------------------------------
	//	@brief		�����F��ύX
	//	@note		���ɂȂ�
	//	@param[in]	textColor �����F
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/04/27
	------------------------------------------------------------*/
	void SetColorF( WORD textColor = L_WHITE )
	{
		this->SetColor( m_backColor, textColor );
	}

	/*!-----------------------------------------------------------
	//	@brief		�w�i�E�����F��ύX
	//	@note		���ɂȂ�
	//	@param[in]	backColor �w�i�F
	//	@param[in]	textColor �����F
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/04/27
	------------------------------------------------------------*/
	void SetColor( WORD backColor = L_BLACK, WORD textColor = L_WHITE )
	{
		m_backColor = backColor;
		m_textColor = textColor;
		::SetConsoleTextAttribute( m_hStdOut, m_textColor|(m_backColor<<4) );
	}

	/*!-----------------------------------------------------------
	//	@brief		������̕`��
	//	@note		���ɂȂ�
	//	@param[in]	str ������
	//	@param[in]	... �ψ���
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/04/27
	------------------------------------------------------------*/
	DWORD Printf( const std::string str, ... )
	{
		DWORD len;
		va_list args;
		va_start( args, str );
		vsprintf_s( m_strBuf, _countof(m_strBuf), str.c_str(), args );
		va_end( args );
		::WriteConsoleA( m_hStdOut, m_strBuf, strlen(m_strBuf), &len, NULL );
		return len;
	}

	/*!-----------------------------------------------------------
	//	@brief		������̕`��
	//	@note		���O�e�L�X�g�ɂ��o�͂���
	//	@param[in]	str ������
	//	@param[in]	... �ψ���
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/05/20
	------------------------------------------------------------*/
	DWORD PrintfLog( const std::string str, ... )
	{
		DWORD len;
		va_list args;
		va_start( args, str );
		vsprintf_s( m_strBuf, _countof(m_strBuf), str.c_str(), args );
		va_end( args );
		::WriteConsoleA( m_hStdOut, m_strBuf, strlen(m_strBuf), &len, NULL );
		fprintf_s(m_pFile,"%s",m_strBuf);
		return len;
	}

	/*!-----------------------------------------------------------
	//	@brief		�`���ʂ̃N���A
	//	@note		���ɂȂ�
	//	@param[in]	�Ȃ�
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/04/27
	------------------------------------------------------------*/
	void Clear( void )
	{
		system( "cls" );
	}

	/*!-----------------------------------------------------------
	//	@brief		����{�^���𖳌���
	//	@note		���ɂȂ�
	//	@param[in]	�Ȃ�
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/04/27
	------------------------------------------------------------*/
	void RemoveClose( void )
	{
		HMENU hMenu = GetSystemMenu( ::GetConsoleWindow(), FALSE );
		::RemoveMenu( hMenu, SC_CLOSE, MF_BYCOMMAND );
	}

	/*!-----------------------------------------------------------
	//	@brief		������Ԃɖ߂�
	//	@note		���ɂȂ�
	//	@param[in]	�Ȃ�
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/04/27
	------------------------------------------------------------*/
	void Reset( void )
	{
		this->SetColor( L_BLACK, L_WHITE );
		this->Clear();
		this->SetCursorPosition( 0, 0 );
	}
private:
	FILE*	m_pFile;		///< �t�@�C���|�C���^	
	HANDLE	m_hStdOut;		///< �o�͐�n���h��
	CHAR	m_strBuf[512];	///< ������o�b�t�@
	WORD	m_backColor;	///< �w�i�F
	WORD	m_textColor;	///< �����F
};




#ifdef DEBUG_INSTANCE
#define	DEBUG_EXTERN
#else
#define	DEBUG_EXTERN	extern

#endif // !DEBUG_INSTANCE

DEBUG_EXTERN	CDebugConsole	g_DebugConsole;

namespace DEBUG
{
	static const int DUMMY_NONE = 0;

	enum CONSOLECOLOR {
		L_BLACK = 0,
		L_BLUE,
		L_GREEN,
		L_CYAN,
		L_RED,
		L_PURPLE,
		L_YELLOW,
		L_WHITE,

		H_BLACK,
		H_BLUE,
		H_GREEN,
		H_CYAN,
		H_RED,
		H_PURPLE,
		H_YELLOW,
		H_WHITE
	};

#if defined(_DEBUG) || defined(_BF_RELEASE_DEBUG)

	/*!-----------------------------------------------------------
	//	@brief		�ψ����ɕϊ�
	//	@note		���ɂȂ�
	//	@param[in]	�Ȃ�
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/04/27
	------------------------------------------------------------*/
	inline	void	OutPutStringArgList(CONST LPSTR str,va_list argList)
	{
		char buf[1024];
		_vsnprintf_s( buf, _countof(buf), str, argList );
		OutputDebugStringA( buf );
		g_DebugConsole.Printf( buf );
	}

	/*!-----------------------------------------------------------
	//	@brief		�ψ����ɕϊ�
	//	@note		���O�o�͔�
	//	@param[in]	�Ȃ�
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/05/20
	------------------------------------------------------------*/
	inline	void	OutPutStringArgListLog(CONST LPSTR str,va_list argList)
	{
		char buf[1024];
		_vsnprintf_s( buf, _countof(buf), str, argList );
		OutputDebugStringA( buf );
		g_DebugConsole.PrintfLog( buf );
	}

	/*!-----------------------------------------------------------
	//	@brief		�f�o�b�O�R���\�[���̏�����
	//	@note		���ɂȂ�
	//	@param[in]	�Ȃ�
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/04/27
	------------------------------------------------------------*/
	inline void		InitDebugConsole(void)
	{
		// �f�o�b�O�R���\�[���̕���{�^��������
		g_DebugConsole.RemoveClose();
	}

	/*!-----------------------------------------------------------
	//	@brief		���O�쐬������
	//	@note		���ɂȂ�
	//	@param[in]	fileName	�������ރt�@�C����
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/10/05
	------------------------------------------------------------*/
	inline	void	InitDebugLog(LPCTSTR fileName)
	{
		//�f�o�b�O���O�̏�����
		g_DebugConsole.CreateDebugLog(fileName);
	}

	/*!-----------------------------------------------------------
	//	@brief		�~�{�^���𖳌���
	//	@note		���ɂȂ�
	//	@param[in]	�Ȃ�
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/12/04
	------------------------------------------------------------*/
	inline	void	RemoveClose()
	{
		g_DebugConsole.RemoveClose();
	}

	/*!-----------------------------------------------------------
	//	@brief		������̕`��
	//	@note		���ɂȂ�
	//	@param[in]	str ������
	//	@param[in]	... �ψ���
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/04/27
	------------------------------------------------------------*/
	inline void Printf(CONST LPSTR str,...)
	{
		g_DebugConsole.SetColor();

		// �������`��
		va_list args;
		va_start( args, str );
		OutPutStringArgList(str,args);
		va_end( args );
	}

	/*!-----------------------------------------------------------
	//	@brief		������̕`��
	//	@note		���O�o�͔�
	//	@param[in]	str ������
	//	@param[in]	... �ψ���
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/05/20
	------------------------------------------------------------*/
	inline void PrintfLog(CONST LPSTR str,...)
	{
		g_DebugConsole.SetColor();

		// �������`��
		va_list args;
		va_start( args, str );
		OutPutStringArgListLog(str,args);
		va_end( args );
	}

	/*!-----------------------------------------------------------
	//	@brief		�w��F�ŕ�����̕`��
	//	@note		���ɂȂ�
	//	@param[in]	textColor �����F
	//	@param[in]	str       ������
	//	@param[in]	...       �ψ���
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/04/27
	------------------------------------------------------------*/
	inline void PrintfColor(WORD textColor,CONST LPSTR str,...)
	{
		// �F���Z�b�g
		g_DebugConsole.SetColorF( textColor );

		va_list args;
		va_start( args, str );
		OutPutStringArgList(str,args);
		va_end( args );
	}

	/*!-----------------------------------------------------------
	//	@brief		�w��F�ŕ�����̕`��
	//	@note		���O�o�͔�
	//	@param[in]	textColor �����F
	//	@param[in]	str       ������
	//	@param[in]	...       �ψ���
	//	@return		�Ȃ�
	//	@author		Tatsunori Aoyama
	//	@date		2013/05/20
	------------------------------------------------------------*/
	inline void PrintfColorLog(WORD textColor,CONST LPSTR str,...)
	{
		// �F���Z�b�g
		g_DebugConsole.SetColorF( textColor );

		va_list args;
		va_start( args, str );
		OutPutStringArgListLog(str,args);
		va_end( args );
	}
#else
	
#define InitDebugConsole()					DUMMY_NONE
#define InitDebugLog(fileName)				DUMMY_NONE
#define RemoveClose()						DUMMY_NONE
#define Printf(str, ... )					DUMMY_NONE
#define PrintfLog(str,... )					DUMMY_NONE
#define PrintfColor(fontColor,str, ... )	DUMMY_NONE
#define PrintfColorLog(textColor,str,...)	DUMMY_NONE
	
#endif
}


#endif // _Include_CDebugConsole_h_