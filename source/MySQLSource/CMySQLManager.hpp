//----------------------------------------------------
// CMySQLBase
//	MySQLにつなぎ、基本的なSQL文を実行するためのもの
//
// @author  T.Kawashita
// @date	2013/11/11
//----------------------------------------------------
#ifndef _C_MYSQL_MANAGER_H_
#define _C_MYSQL_MANAGER_H_

#include <Windows.h>
#include <mysql.h>
#include <string>

// データベース情報
#define HOST_NAME ( NULL )
#define USER_NAME ( "Kaikai" )
#define PASS_WORD ( "tkwaterki7" )
#define DATA_BASE ( "XI_Remakedb" )
#define PORT_NUM  ( 0 )

class CMySQLManager
{
private:

	MYSQL* m_pMySql;
	MYSQL_RES*	m_pResult;

	// コンストラクタ
	CMySQLManager	( void )
	{
		m_pMySql = mysql_init( NULL );
		// MySQLの初期化の成功か否か
		if( m_pMySql == NULL )
		{
			MessageBox( NULL,"MySQL初期化失敗","InitError",MB_OK );
		}
		
	}
	CMySQLManager	( CONST CMySQLManager& mysqlManager );				// コピーコンストラクタ禁止
	CMySQLManager	operator=	( CONST CMySQLManager& mysqlManager );	// メンバの代入を防ぐ

public:
	// デストラクタ
	~CMySQLManager	( void )
	{
		mysql_server_end();		// MySQLを終了
	}

	//----------------------------------------------------
	// インスタンスの唯一の取得場所
	//----------------------------------------------------
	static CMySQLManager* GetInstance ( void )
	{
		static CMySQLManager mysqlManager;
		return &mysqlManager;
	}
	
	//----------------------------------------------------
	// @name	ConnectDatabase
	// @content	データベースへの接続(引数なし)
	// @param	none
	// @return	bool		成功か失敗
	// @date	2013/11/11
	//----------------------------------------------------
	bool ConnectDatabase		( void )
	{
		m_pMySql = mysql_init( NULL );
		if( mysql_real_connect( m_pMySql, HOST_NAME, USER_NAME, PASS_WORD, DATA_BASE, PORT_NUM,NULL, 0 ) == NULL )
		{
//			MessageBox( NULL, mysql_error( m_pMySql ), "MySQL接続エラー", MB_OK );
			return false;
		}

		return true;
	}

	//----------------------------------------------------
	// @name	ConnectDatabase
	// @content	データベースへの接続(引数あり)
	// @param	dataBase	接続したいデータベース名
	// @return	bool		成功か失敗
	// @date	2013/11/11
	//----------------------------------------------------	
	bool ConnectDatabase		( CONST std::string dataBase )
	{
		m_pMySql = mysql_init( NULL );
		if( mysql_real_connect( m_pMySql, HOST_NAME, USER_NAME, PASS_WORD, dataBase.c_str(), PORT_NUM,NULL, 0 ) == NULL )
		{
			MessageBox( NULL, mysql_error( m_pMySql ), "MySQL接続エラー", MB_OK );
			return false;	// 失敗
		}

		return true;		// 成功
	}

	//----------------------------------------------------
	// @name	Search(テーブル名のみの指定)
	// @content	検索処理
	// @param	searchResultFd	検索結果を保存するフィールド
	// @param	table			テーブル名
	// @return	MYSQL_FIELD*	検索結果
	// @date	2013/11/11
	//----------------------------------------------------
	CONST MYSQL_FIELD* Search	( MYSQL_FIELD* searchResultFd, CONST std::string table )
	{
		std::string sql = "SELECT * FROM " + table;
		if( this->Query( sql ) == true )
		{
			m_pResult = mysql_store_result( m_pMySql );		// 検索結果を保存
			
			if( m_pResult == NULL || mysql_errno( m_pMySql ) != 0 )
			{
				return NULL;
			}

			// 見つかった場合は列の情報をMYSQL_FIELD型の変数にセット
			searchResultFd = mysql_fetch_field( m_pResult );
	
			return searchResultFd;
		}
	}

	//----------------------------------------------------
	// @name	Search(テーブル名・列名・条件式）
	// @content	検索処理
	// @param	searchResultFd	検索結果を保存するフィールド
	// @param	table			テーブル名
	// @param	column			列名
	// @param	condition		条件式
	// @return	MYSQL_FIELD*	検索結果
	// @date	2014/2/19
	//----------------------------------------------------
	CONST MYSQL_ROW Search	( MYSQL_ROW searchResultFd, CONST std::string* table, CONST std::string* column, CONST std::string* condition )
	{
		std::string sql = "SELECT " + *column + " FROM " + *table + " WHERE " + *condition;
		// クエリ発行
		if( this->Query( sql ) == true )
		{
			m_pResult = mysql_store_result( m_pMySql );	// 検索結果を保存
			if( m_pResult == NULL || mysql_errno( m_pMySql ) != 0 )
			{
				// 検索エラー
				return false;
			}

			// 見つかった場合は列の情報をMYSQL_FIELD型の変数にセット
			searchResultFd = mysql_fetch_row( m_pResult );

			return searchResultFd;
		}
		return searchResultFd;
	}

	//----------------------------------------------------
	// @name	Search(テーブル名と列名を指定)
	// @content 検索処理
	// @param	fd			検索結果を保存するフィールド
	// @param	table		テーブル名
	// @param	column		列名
	// @return	bool		あるかどうか
	// @date	2013/11/11
	//----------------------------------------------------
	bool Search		(  CONST std::string table, CONST std::string condition )
	{
		std::string sql = "SELECT * FROM " + table + " WHERE " + condition + ";";
		if( this->Query( sql ) == true )
		{
			m_pResult = mysql_store_result( m_pMySql );
			if( m_pResult == NULL || mysql_errno( m_pMySql ) != 0 || m_pResult->row_count == 0 )
			{
				return false;
			}
			
			// 結果の破棄
			mysql_free_result( m_pResult );
			return true;
		}

		return false;
	}

	//----------------------------------------------------
	// @name	CreateTable
	// @content	テーブルの作成
	// @param	table	テーブル名
	// @return	bool	成功か失敗
	// @date	2013/11/11
	// @comment	実装していません。
	//----------------------------------------------------
	bool CreateTable			( CONST std::string table, CONST std::string )
	{
	}

	//----------------------------------------------------
	// @name	Insert
	// @content	列の追加
	// @param	table		追加したいテーブル名
	// @param	condition	条件
	// @return	bool		成功か失敗
	// @date	2013/11/11
	//----------------------------------------------------
	bool Insert					( CONST std::string table, std::string condision )
	{
		std::string sql = " INSERT INTO " + table + " VALUES ( " + condision + " ); " ;

		if( this->Query( sql ) == true )
		{
			// 追加成功
			return true;
		}
		
		// 追加失敗
		return false;
	}

	//----------------------------------------------------
	// @name	Update
	// @content	指定列の更新
	// @param	table		テーブル名
	// @param	column		指定列名
	// @param	condition	条件
	// @return	bool		更新できたか出来なかったか
	// @date	2013/11/11
	//----------------------------------------------------
	bool Update					( CONST std::string* table, CONST std::string* column, CONST std::string* condition )
	{
		std::string sql = " UPDATE " + *table + " SET " +  *column + " WHERE " + *condition;
		if( this->Query( sql ) == true )
		{
			// 更新
			return true;
		}

		// 更新できない
		return false;
	}

	//----------------------------------------------------
	// @name	Query
	// @content	SQL文の実行
	// @param	sql			sql文
	// @return	bool		成功か失敗か
	// @date	2013/10/10
	//----------------------------------------------------
	bool Query					( CONST std::string sql )
	{
		mysql_query( m_pMySql, sql.c_str() );	// SQL文の実行
		if( mysql_errno( m_pMySql ) != NULL )
		{
			MessageBox( NULL, mysql_error( m_pMySql ), "クエリの発行失敗", MB_OK );
			return false;
		}

		return true;		// クエリ発行成功
	}

	//----------------------------------------------------
	// @name	UnConnectionDatabase
	// @content	データベースからの切断
	// @param	none
	// @return	切断できたか出来なかったか
	// @date	2013/11/11
	//----------------------------------------------------
	bool UnConnectionDatabase	( void )
	{
		if( m_pMySql != NULL )
		{
			mysql_close( m_pMySql );
		}
		return true;
	}

	//----------------------------------------------------
	// @name	DestroyResult
	// @content	リザルト情報の破棄
	// @param	none
	// @return	bool	破棄できたかどうか
	// @date	2014/2/20
	// @update	none
	//----------------------------------------------------
	bool DestroyResult			( void )
	{
		mysql_free_result( m_pResult );		
	}
};

#endif	_C_MYSQL_BASE_H_