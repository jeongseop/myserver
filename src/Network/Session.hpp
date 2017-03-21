#ifndef _SESSION_HPP_
#define _SESSION_HPP_

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <time.h>

#include "Log.hpp"
#include "MyException.hpp"

enum class STATE {PRE_LOGIN, NORMAL, LOGOUT};

/**
 * @brief 세션 정보
 */
class CSession
{
private:
	int m_ses_id;
	int m_fd;
	STATE m_state;
	std::string m_id;
	time_t m_last_polling_time;

public:
	CSession(std::string id_, int fd_);
	~CSession();

	int get_fd() {return m_fd;}
	time_t get_last_polling_time() {return m_last_polling_time;}
	std::string get_buffer() {return m_buf;}
	void update_polling_time();
};

#endif // _SESSION_HPP_ end
