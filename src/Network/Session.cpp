#include "Session.hpp"

CSession::CSession(std::string id_, int fd_)
	: m_fd(fd_), m_state(STATE::NORMAL), m_id(id_), m_buf("")
{
	m_last_polling_time = time(NULL);
}

void CSession::update_polling_time()
{
	m_last_polling_time = time(NULL);
}


void CSesUtil::make_new_session(std::string id_, int fd_)
{
	ses_map::iterator itr = m_sessions.find(id_);
	if(itr == m_sessions.end()) throw CMyException("이미 로그인중인 아이디");

	m_sessions.insert(std::pair<std::string, std::shared_ptr<CSession>>(id_,std::make_shared<CSession>(id_, fd_)));
}

void CSesUtil::remove_session(std::string id_)
{
	ses_map::iterator itr = m_sessions.find(id_);
	if(itr == m_sessions.end()) throw CMyException("접속중인 아이디가 아닙니다.");

	m_sessions.erase(id_);
}

std::shared_ptr<CSession> CSesUtil::get_session(std::string id_)
{
	ses_map::iterator itr = m_sessions.find(id_);
	if(itr == m_sessions.end()) throw CMyException("접속중인 아이디가 아닙니다.");
}

int CSesUtil::get_session_cnt()
{
	return m_sessions.size();
}
