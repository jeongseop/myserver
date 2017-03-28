#ifndef _SOCKET_HPP_
#define _SOCKET_HPP_

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <cerrno>
#include <fcntl.h>

#include "Log.hpp"

class CSocket
{
private:
	int m_listenfd;

public:
	bool open_server(std::string host, int port);
	bool set_non_block(int fd, bool block=false);
	bool set_no_delay(int fd, bool nodelay=true);

	int accept_client();
	bool send_message(int fd);
	bool recv_message(int fd);
};

#endif
