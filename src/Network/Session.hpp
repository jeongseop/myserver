#ifndef _SESSION_HPP_
#define _SESSION_HPP_

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <time.h>

enum class STATE {VERIFIED, NORMAL};

class CSession
{
	typedef struct _session_info {
		int slot;
		int fd;
		STATE state;
		std::string id;
		time_t last_polling_time;
		std::string buf;
	} session_info;

private:
	int m_session_cnt;
	map<std::string, std::shared_ptr<session_info>> sessions;

public:
	CSessionUtil();
	~CSessionUtil();

public:
	void make_new_session(std::string id);
	int get_session_cnt();
	int search_session(std::string id);
	void update_polling_time(std::string id);
}

#endif // _SESSION_HPP_ end
