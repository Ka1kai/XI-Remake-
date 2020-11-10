/*************************************************************
*	@file   	CDebugConsole.h
*	@brief  	CDebugConsoleクラスヘッダー
*	@note		メモ
*	@author		Tatsunori Aoyama
*	@date		2013/04/17
*************************************************************/

#ifndef _Include_CDebugConsole_h_	// インクルードガード
#define _Include_CDebugConsole_h_

//------------------------------------------------------------
// インクルード
//------------------------------------------------------------
#include<Windows.h>
#include<string>

//------------------------------------------------------------
// 定数、構造体定義
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
//	@brief  デバッグ用のコンソール
//	@note	メモ
//	@author	Tatsunori Aoyama
//	@date	2013/04/17
------------------------------------------------------------*/
class CDebugConsole
{
public:
	/// コンストラクタ
	CDebugConsole()
	{
		m_pFile = nullptr;
		SMALL_RECT	rc = {0,0,1024,512};
		COORD		cd = {rc.Right+1,rc.Bottom+1};
		::AllocConsole();	//コンソールの確保
		m_hStdOut	= GetStdHandle( STD_OUTPUT_HANDLE );
		SetConsoleScreenBufferSize(m_hStdOut, cd);
		SetConsoleWindowInfo(m_hStdOut,TRUE,&rc);
		m_backColor	= L_BLACK;
		m_textColor	= L_WHITE;
		this->SetColorF(H_RED);
		CDebugConsole::Printf("[==================== Start Up Debug Console ====================]\n\n");
		this->SetColorF(m_textColor);
	}

	/// デストラクタ
	~CDebugConsole()
	{
		this->Destory();
	}

	/*!-----------------------------------------------------------
	//	@brief		解放処理
	//	@note		特になし
	//	@param[in]	なし
	//	@return		なし
	//	@author		Tatsunori Aoyama
	//	@date		2013/12/03
	------------------------------------------------------------*/
	void	Destory()
	{
		if( m_hStdOut == nullptr )
			return;

		if( m_pFile != nullptr )
			fclose(m_pFile);
		//コンソールの解放
		::FreeConsole();
		m_hStdOut = nullptr;
	}

	/*!-----------------------------------------------------------
	//	@brief		ファイルポインタオープン
	//	@note		特になし
	//	@param[in]	fileName	作成するファイル名
	//	@return		なし
	//	@author		Tatsunori Aoyama
	//	@date		2013/08/05
	------------------------------------------------------------*/
	void	CreateDebugLog(LPCTSTR fileName)
	{
		fopen_s(&m_pFile,fileName,"w");
	}

	/*!-----------------------------------------------------------
	//	@brief		カーソルの大きさと可視設定
	//	@note		特になし
	//	@param[in]	dwSize    カーソルの大きさ
	//	@param[in]	isVisible 可視設定
	//	@return		なし
	//	@author		Tatsunori Aoyama
	//	@date		2013/04/27
	------------------------------------------------------------*/
	void SetCursorInfo( DWORD dwSize = 25, BOOL isVisible = TRUE )
	{
		CONSOLE_CURSOR_INFO info = { dwSize, isVisible };
		::SetConsoleCursorInfo( m_hStdOut, &info );
	}

	/*!-----------------------------------------------------------
	//	@brief		コンソールカーソルの位置設定
	//	@note		特になし
	//	@param[in]	x X座標
	//	@return		y Y座標
	//	@author		Tatsunori Aoyama
	//	@date		2013/04/27
	------------------------------------------------------------*/
	void SetCursorPosition( int x, int y )
	{
		COORD coord = { (short)x, (short)y };
		::SetConsoleCursorPosition( m_hStdOut, coord );
	}

	/*!-----------------------------------------------------------
	//	@brief		背景色を変更
	//	@note		特になし
	//	@param[in]	backColor 背景色
	//	@return		なし
	//	@author		Tatsunori Aoyama
	//	@date		2013/04/27
	------------------------------------------------------------*/
	void SetColorB( WORD backColor = L_BLACK ){
		this->SetColor( backColor, m_textColor );
	}

	/*!-----------------------------------------------------------
	//	@brief		文字色を変更
	//	@note		特になし
	//	@param[in]	textColor 文字色
	//	@return		なし
	//	@author		Tatsunori Aoyama
	//	@date		2013/04/27
	------------------------------------------------------------*/
	void SetColorF( WORD textColor = L_WHITE )
	{
		this->SetColor( m_backColor, textColor );
	}

	/*!-----------------------------------------------------------
	//	@brief		背景・文字色を変更
	//	@note		特になし
	//	@param[in]	backColor 背景色
	//	@param[in]	textColor 文字色
	//	@return		なし
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
	//	@brief		文字列の描画
	//	@note		特になし
	//	@param[in]	str 文字列
	//	@param[in]	... 可変引数
	//	@return		なし
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
	//	@brief		文字列の描画
	//	@note		ログテキストにも出力する
	//	@param[in]	str 文字列
	//	@param[in]	... 可変引数
	//	@return		なし
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
	//	@brief		描画画面のクリア
	//	@note		特になし
	//	@param[in]	なし
	//	@return		なし
	//	@author		Tatsunori Aoyama
	//	@date		2013/04/27
	------------------------------------------------------------*/
	void Clear( void )
	{
		system( "cls" );
	}

	/*!-----------------------------------------------------------
	//	@brief		閉じるボタンを無効か
	//	@note		特になし
	//	@param[in]	なし
	//	@return		なし
	//	@author		Tatsunori Aoyama
	//	@date		2013/04/27
	------------------------------------------------------------*/
	void RemoveClose( void )
	{
		HMENU hMenu = GetSystemMenu( ::GetConsoleWindow(), FALSE );
		::RemoveMenu( hMenu, SC_CLOSE, MF_BYCOMMAND );
	}

	/*!-----------------------------------------------------------
	//	@brief		初期状態に戻す
	//	@note		特になし
	//	@param[in]	なし
	//	@return		なし
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
	FILE*	m_pFile;		///< ファイルポインタ	
	HANDLE	m_hStdOut;		///< 出力先ハンドル
	CHAR	m_strBuf[512];	///< 文字列バッファ
	WORD	m_backColor;	///< 背景色
	WORD	m_textColor;	///< 文字色
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
	//	@brief		可変引数に変換
	//	@note		特になし
	//	@param[in]	なし
	//	@return		なし
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
	//	@brief		可変引数に変換
	//	@note		ログ出力版
	//	@param[in]	なし
	//	@return		なし
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
	//	@brief		デバッグコンソールの初期化
	//	@note		特になし
	//	@param[in]	なし
	//	@return		なし
	//	@author		Tatsunori Aoyama
	//	@date		2013/04/27
	------------------------------------------------------------*/
	inline void		InitDebugConsole(void)
	{
		// デバッグコンソールの閉じるボタン無効化
		g_DebugConsole.RemoveClose();
	}

	/*!-----------------------------------------------------------
	//	@brief		ログ作成初期化
	//	@note		特になし
	//	@param[in]	fileName	書き込むファイル名
	//	@return		なし
	//	@author		Tatsunori Aoyama
	//	@date		2013/10/05
	------------------------------------------------------------*/
	inline	void	InitDebugLog(LPCTSTR fileName)
	{
		//デバッグログの初期化
		g_DebugConsole.CreateDebugLog(fileName);
	}

	/*!-----------------------------------------------------------
	//	@brief		×ボタンを無効化
	//	@note		特になし
	//	@param[in]	なし
	//	@return		なし
	//	@author		Tatsunori Aoyama
	//	@date		2013/12/04
	------------------------------------------------------------*/
	inline	void	RemoveClose()
	{
		g_DebugConsole.RemoveClose();
	}

	/*!-----------------------------------------------------------
	//	@brief		文字列の描画
	//	@note		特になし
	//	@param[in]	str 文字列
	//	@param[in]	... 可変引数
	//	@return		なし
	//	@author		Tatsunori Aoyama
	//	@date		2013/04/27
	------------------------------------------------------------*/
	inline void Printf(CONST LPSTR str,...)
	{
		g_DebugConsole.SetColor();

		// 文字列を描画
		va_list args;
		va_start( args, str );
		OutPutStringArgList(str,args);
		va_end( args );
	}

	/*!-----------------------------------------------------------
	//	@brief		文字列の描画
	//	@note		ログ出力版
	//	@param[in]	str 文字列
	//	@param[in]	... 可変引数
	//	@return		なし
	//	@author		Tatsunori Aoyama
	//	@date		2013/05/20
	------------------------------------------------------------*/
	inline void PrintfLog(CONST LPSTR str,...)
	{
		g_DebugConsole.SetColor();

		// 文字列を描画
		va_list args;
		va_start( args, str );
		OutPutStringArgListLog(str,args);
		va_end( args );
	}

	/*!-----------------------------------------------------------
	//	@brief		指定色で文字列の描画
	//	@note		特になし
	//	@param[in]	textColor 文字色
	//	@param[in]	str       文字列
	//	@param[in]	...       可変引数
	//	@return		なし
	//	@author		Tatsunori Aoyama
	//	@date		2013/04/27
	------------------------------------------------------------*/
	inline void PrintfColor(WORD textColor,CONST LPSTR str,...)
	{
		// 色をセット
		g_DebugConsole.SetColorF( textColor );

		va_list args;
		va_start( args, str );
		OutPutStringArgList(str,args);
		va_end( args );
	}

	/*!-----------------------------------------------------------
	//	@brief		指定色で文字列の描画
	//	@note		ログ出力版
	//	@param[in]	textColor 文字色
	//	@param[in]	str       文字列
	//	@param[in]	...       可変引数
	//	@return		なし
	//	@author		Tatsunori Aoyama
	//	@date		2013/05/20
	------------------------------------------------------------*/
	inline void PrintfColorLog(WORD textColor,CONST LPSTR str,...)
	{
		// 色をセット
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