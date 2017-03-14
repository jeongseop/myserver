#include "Epoll.hpp"

CEpollUtil::CEpollUtil(int port_, bool isblock_)
	: CNetUtil(port_, isblock_, 0)
{}

CEpollUtil::CEpollUtil(int port_, bool isblock_, int timeout_)
	: CNetUtil(port_, isblock_, timeout_)
{}

CEpollUtil::~CEpollUtil()
{
	if( this->m_isRunning ) closeServer();
}

int CEpollUtil::openServer()
{
	if( this->m_isRunning )
	{
		//실행중
		LOG_ERROR << "이미 실행중입니다.";
		return;
	}
	
	this->m_isRunning = true;

	// 서버 셋팅
	int serv_sock = setServerInfo(20000);

	if( bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1 )
	{
		// bind error
		LOG_ERROR << "bind() 실패";
	}

	if( listen(serv_sock, 10) == -1 )
	{
		// listen error
		LOG_ERROR << "listen() 실패";
	}

	// Nonblocking 셋팅
	setNonblock(serv_sock);

	LOG_INFO << "SERVER LISTEN START...";

	this.m_epfd = addEpollIn(serv_sock, 8192);
}

void CEpollUtil::sendPolling()
{
}

int CEpollUtil::writePacket(int fd, char *message)
{
}

int CEpollUtil::readPacket(int fd, char *size)
{
}

void CEpollUtil::closeServer()
{
}

int CEpollUtil::epollCreate(int fd, int epoll_cnt)
{
	struct epoll_event event;
	int epfd = epoll_create(epoll_cnt);
	event.events = EPOLLIN;
	event.data.fd = fd;
	epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);

	LOG_TRACE << "EPOLL 감시 시작";
}

int CEpollUtil::setServerInfo(int port)
{
	int serv_sock;
	struct sockaddr_in serv_addr;
	//int port = 20000;

	bzero(&serv_addr, sizeof(serv_addr));

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);

	LOG_INFO << "OPEN PORT[" << port << "]";

	return serv_sock;
}

void CEpollUtil::setNonblock(int fd)
{
	int flag = fcntl(fd, F_GETFL, 0);
	fcntl(fd, F_SETFL, flag | O_NONBLOCK);
}

void CEpollUtil::setTimeout(int sec)
{
}
