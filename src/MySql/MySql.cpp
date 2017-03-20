#include "MySql.h"

CMySql::CMySql()
{
}

CMySql::~CMySql()
{
	DisConnectMySql();
}

bool CMySql::ConnectMySql(const char *host,
						  const char *userId,
						  const char *passwd,
						  const char *DB)
{
	try {
		if( isConnected() ) {
			// 이미 연결된 상태
			return 0;
		}
		// mysql 접속 시도
		m_MysqlDriver = get_driver_instance();
		string tcpHost = "tcp://";
		tcpHost.append(host);
		m_MysqlConn = m_MysqlDriver->connect(tcpHost.c_str(), userId, passwd);
		m_MysqlConn->setSchema(DB);
		return 1;
	}
	catch (sql::SQLException &e)
	{
		// mysql 접속 실패
		string err_msg = MakeErrorData(e.getErrorCode(),e.what(),e.getSQLState(),__FILE__,__FUNCTION__,__LINE__);
	}
	return -1;
}

void CMySql::DisConnectMySql()
{
	if( m_MysqlRes != NULL ) {
		delete m_MysqlRes;
		m_MysqlRes = NULL;
	}

	if( m_MysqlStmt != NULL ) {
		delete m_MysqlStmt;
		m_MysqlStmt = NULL;
	}

	if( m_MysqlConnection != NULL ) {
		delete m_MysqlConnection;
		m_MysqlConnection = NULL;
	}

	if( m_MysqlDriver != NULL ) {
		delete m_MysqlDriver;
		m_MysqlDriver = NULL;
	}
}

bool CMySql::ExecuteQuery(string query)
{
}

bool CMySql::Next()
{
}

string CMySql::MakeErrorData(const int error_code,
							 const char *error_message,
							 const char *sql_state,
							 const char *file,
							 const char *function,
							 const int line)
{
	m_ErrorCode = error_code;
	m_ErrorMessage = error_message;
	m_SQLState = sql_state;

	char retMsg[4096];
	sprintf(retMsg, "[%s:%s:%d] MySQL err_cd[%d], err_msg[%s], state[%s]",file,function,line, error_code, error_message, sql_state);

	string retStr = retMsg;
	return retStr;
}
