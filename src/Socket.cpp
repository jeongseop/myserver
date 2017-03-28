#include "Socket.hpp"

bool CSocket::open_server(std::string host, int port)
{
}

bool CSocket::set_non_block(int fd, bool block)
{
	int flags = fcntl(fd, F_GETFL, 0);
	if( -1 == fcntl(fd, F_SETFL, flags | O_NONBLOCK) )
	{
		LOG_ERROR << "fcntl() O_NONBLOCK 설정 오류.. fd[" << fd << "]";
		return false;
	}

	return true;
}

bool CSocket::set_no_delay(int fd, bool nodelay)
{
	const int v(nodelay);
	return (0 == setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &v, sizeof(v)));
}

void CSocket::accept_client(int fd)
{
}

int CSocket::accept_client()
{
}

bool CSocket::send_message(int fd)
{
}

bool CSocket::recv_message(int fd)
{
}
