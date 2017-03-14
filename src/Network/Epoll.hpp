#ifndef _EPOLL_HPP_
#define _EPOLL_HPP_

#include <iostream>
#include <string>
#include <cstdlib>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <thread>

#include "Log.hpp"
#include "Network.hpp"

class CEpollUtil : public CNetUtil
{
public: 
	CEpollUtil(int port_, bool isblock_);
	CEpollUtil(int port_, bool isblock_, int timeout);
	~CEpollUtil();

	int openServer();
	int epollCreate(int fd, int epoll_cnt);
	void sendPolling();
	int writePacket(int fd, char *message);
	int readPacket(int fd, char *message);
	void closeServer();

private:
	int setServerInfo(int port);
	void setNonblock(int fd);
	void setTimeout(int sec = 0);
};

#endif // _EPOLL_HPP_ end
