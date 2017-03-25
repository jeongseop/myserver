#ifndef _SESSION_HPP_
#define _SESSION_HPP_

#include <iostream>
#include <string>
#include <memory>
#include <time.h>

#include "Log.hpp"
#include "MyException.hpp"
#include "RingBuffer.hpp"

enum class STATE {PRE_LOGIN, NORMAL, LOGOUT};

/**
 * @brief 세션 정보
 * @author Jeongseop Shim, jeongsub3312@naver.com
 * @date 2017-03-25
 * @version 1.0.0
 */
class CSession
{
private:
	static const int BUF_SIZE;

	int m_fd;
	STATE m_state;
	std::string m_id;
	time_t m_last_io_time;

	CRingBuffer m_send_buf;
	CRingBuffer m_recv_buf;

public:
	CSession(std::string id_, int fd_);

	void init();
	void close();

	int get_fd() {return m_fd;}
	time_t get_last_polling_time() {return m_last_polling_time;}

	bool send_message(const char* msg);
	bool recv_message();

private:
};

#endif // _SESSION_HPP_ end
