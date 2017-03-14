/**
	@class	CMySql
	@date	2017/1/22
	@author	심정섭(jeongsub3312@gmail.com)
	@brief	MySql 관리 클래스
 */

#ifndef __MYSQL_H__
#define __MYSQL_H__

#include <iostream>
#include <string>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
using namespace std;

class CMySql
{
private:
	sql::Driver *m_MysqlDriver; ///< Mysql Driver 멤버변수
	sql::Connection *m_MysqlConn; ///< Mysql Connection 멤버변수
	sql::Statement *m_MysqlStmt; ///< Mysql Statement 멤버변수
	sql::ResultSet *m_MysqlRes; ///< Mysql ResultSet 멤버변수

	int m_ErrorCode; ///< 에러코드
	string m_ErrorMessage; ///< 에러메세지
	string m_SQLState; ///< SQL 상태

public:
	CMySql(); ///< MySql클래스 생성자
	~CMySql(); ///< MySql클래스 소멸자

	bool ConnectMySql(const char *host
			, const char *userId
			, const char *passwd
			, const char *DB); ///< MySql 연결시도
	void DisConnectMySql(); ///< MySql 연결종료

	bool ExecuteQuery(string query); ///< 쿼리 실행
	bool Next(); ///< 다음 조회테이터 셋팅

	char *operator[](const char *szFieldName) { return getField(szFieldName); }

	string GetErrorCode() { return m_ErrorCode; }
	string GetErrorMessage() { return m_ErrorMessage; }
	string GetSQLState() { return m_SQLState; }

private:
	char *GetField(const char *szFieldName); ///< 필드명으로 데이터 조회
	void MakeErrorData(const int error_code,
			const char *error_message,
			const char *sql_state,
			const char *file,
			const char *function,
			const int line); ///< 에러데이터 셋팅
};

#endif
