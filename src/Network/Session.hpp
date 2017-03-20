#ifndef _SESSION_HPP_
#define _SESSION_HPP_

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <time.h>

#include "Log.hpp"
#include "MyException.hpp"

enum class STATE {VERIFIED, NORMAL};

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
	std::string m_buf;

public:
	CSession(std::string id_, int fd_);
	~CSession();

	int get_fd() {return m_fd;}
	time_t get_last_polling_time() {return m_last_polling_time;}
	std::string get_buffer() {return m_buf;}
	void update_polling_time();
};

/**
 * @brief 세션관리 유틸
 * @author Jeongseop Shim, jeongsub3312@naver.com
 * @date 2017-03-19
 * @version 1.0.0
 */
class CSesUtil
{
	typedef std::map<std::string,std::shared_ptr<CSession>> ses_map;
private:
	std::map<std::string, std::shared_ptr<CSession>> m_sessions;

public:
	CSesUtil();
	~CSesUtil();

public:
	void make_new_session(std::string id_, int fd_);
	void remove_session(std::string id_);
	std::shared_ptr<CSession> get_session(std::string id_);
	int get_session_cnt();
};

#endif // _SESSION_HPP_ end
