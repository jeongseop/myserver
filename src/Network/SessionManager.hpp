#ifndef _SESSION_HPP_
#define _SESSION_HPP_

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
 * @date 2017-03-19
 * @version 1.0.0
 */
class CSessionManager
{
public:
	static CSessionManager* getInstance();

public:
	CSessionManager();
	~CSessionManager();

private:
	static CSessionManager* _instance;
};

#endif // _SESSION_HPP_ end
