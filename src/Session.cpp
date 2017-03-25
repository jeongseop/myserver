#include "Session.hpp"

const int CSession::BUF_SIZE = 1024 * 16;

CSession::CSession(std::string id_, int fd_)
	: m_fd(fd_), m_state(STATE::PRE_LOGIN), m_id(id_), m_send_buf(), m_recv_buf()
{
}

void CSession::init()
{
	m_last_io_time = time(NULL);
	m_send_buf.create_buffer(CSession::BUF_SIZE);
	m_recv_buf.create_buffer(CSession::BUF_SIZE);
}

void CSession::close()
{
	m_send_buf.free_buffer();
	m_recv_buf.free_buffer();
}

bool CSession::send_message(const char* msg)
{
	char buf[2048];
	while(true)
	{
		//send_buf에 데이터가 있으면 먼저 전송
		if(m_send_buf.get_data_len() > 0)
		{
			bzero(buf, sizeof(buf));
		}

		//입력받은 메세지 전송
	}
}

bool CSession::recv_message()
{
}
