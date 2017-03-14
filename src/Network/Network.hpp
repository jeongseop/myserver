#ifndef _NETWORK_HPP_
#define _NETWORK_HPP_

#include <iostream>
#include <string>

#include "Session.hpp"

class CNetUtil
{
protected:
	CSession m_sessions;
	int m_port;
	bool m_isBlocking;
	int m_timeout;
	bool m_isRunning;

public:
	CNetUtil(int port_, bool isblock_, int timeout_)
		: m_port(port_), m_isBlocking(isblock_), m_timeout(timeout_), m_isRunning(false)
	{
	}
	virtual ~CNetUtil();

public:
	virtual void openServer() = 0;
	virtual void sendPolling() = 0;
	virtual int writePacket(int fd, char *message) = 0;
	virtual int readPacket(int fd, char *message) = 0;
	virtual void closeServer() = 0;

private:
	virtual int setServerInfo(int port) = 0;
	virtual void setNonblock(int fd) = 0;
	virtual void setTimeout(int sec = 0) = 0;
}

#endif // _NETWORK_HPP_ end
