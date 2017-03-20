#ifndef _NETWORK_HPP_
#define _NETWORK_HPP_

#include <iostream>
#include <string>
#include <cstdlib>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "MyException.hpp"
#include "Session.hpp"
#include "Log.hpp"

/**
 * @brief 네트워크 유틸
 * @author Jeongseop Shim, jeongsub3312@naver.com
 * @date 2017-03-18
 * @version 1.0.0
 */
class CNetUtil
{
private:
	CSession m_sessions;
	int m_listenfd;
	int m_port;
	int m_timeout;
	bool m_isRunning;

public:
	CNetUtil(int port_);
	virtual ~CNetUtil();

public:
	void openServer();
	void sendPolling();
	int writePacket(int fd, std::string message);
	std::string readPacket(int fd);
	void closeServer();
	void setNonblock(int fd);
	void setTimeout(int sec = 0);
};

#endif // _NETWORK_HPP_ end
