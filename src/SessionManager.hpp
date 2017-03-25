#ifndef _SESSION_MANAGER_HPP_
#define _SESSION_MANAGER_HPP_

#include <iostream>
#include <string>
#include <memory>
#include <map>
#include <time.h>

#include "Log.hpp"
#include "MyException.hpp"
#include "Session.hpp"

/**
 * @brief 세션 관리 클래스
 * @author Jeongseop Shim, jeongsub3312@naver.com
 * @date 2017-03-25
 * @version 1.0.0
 */
class CSessionManager
{
private:
	CSessionManager(){}
	CSessionManager(const CSessionManager&){}

public:
	~CSessionManager();

public:
	static std::shared_ptr<CSessionManager> get_instance();
	std::shared_ptr<CSession> make_new_session();
	void remove_session();

private:
	std::map<int,std::shared_ptr<CSession>> m_sessions;
};

#endif // _SESSION_MANAGER_HPP_ end
