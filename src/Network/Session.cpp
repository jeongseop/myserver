#include "Session.hpp"

CSession::CSession(std::string id_, int fd_)
	: m_fd(fd_), m_state(STATE::PRE_LOGIN), m_id(id_)
{
	m_last_polling_time = time(NULL);
}

void CSession::update_polling_time()
{
	m_last_polling_time = time(NULL);
}
