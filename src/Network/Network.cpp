#include "Network.hpp"

/**
 * @brief 생성자
 * @param port_ listen할 포트
 */
CNetUtil::CNetUtil(int port_)
		:m_port(port_)
{}

/**
 * @brief 서버 오픈
 * @details 서버오픈 메서드, Nonblock
 * @exception CMyException
 */
void CNetUtil::openServer()
{
	if( this->m_isRunning )
	{
		//실행중
		LOG_ERROR << "이미 실행중입니다.";
		throw CMyException("이미 실행중입니다.");
	}
	
	this->m_isRunning = true;

	// 서버 셋팅
	int serv_sock;
	struct sockaddr_in serv_addr;

	bzero(&serv_addr, sizeof(serv_addr));

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(this->m_port);

	LOG_INFO << "OPEN PORT[" << this->m_port << "]";

	if( bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1 )
	{
		// bind error
		LOG_ERROR << "bind() 실패";
		throw CMyException("bind() 중 오류 발생");
	}

	if( listen(serv_sock, 10) == -1 )
	{
		// listen error
		LOG_ERROR << "listen() 실패";
		throw CMyException("listen() 중 오류 발생");
	}

	setNonblock(m_listenfd);

	LOG_INFO << "SERVER LISTEN START...";
}

void CNetUtil::sendPolling()
{
}

int CNetUtil::writePacket(int fd, std::string message)
{
}

std::string CNetUtil::readPacket(int fd)
{
}

void CNetUtil::closeServer()
{
}

void CNetUtil::setNonblock(int fd)
{
	int flag = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flag | O_NONBLOCK);
}

void CNetUtil::setTimeout(int sec)
{
}
