#include <iostream>
#include <string>

#include "Log.hpp"

class CMyException {
private:
	std::string m_msg;

public:
	CMyException() { m_msg = "Unknown Error"; }
	CMyException(std::string msg) { m_msg = msg; }

	std::string what() {
		return m_msg;
	}
};
