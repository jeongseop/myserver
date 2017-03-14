#include <iostream>
#include <string>
#include "Log.hpp"

int main()
{
	LOG_TRACE << "test trace" << ", two";
	LOG_DEBUG << "test debug" << ", two";
	LOG_DEBUG << "test debug.." << 5;
	LOG_INFO << "test info" << ", two";
	LOG_WARNING << "test warning" << ", two";
	LOG_ERROR << "test error" << ", two";
	LOG_FATAL << "test fatal" << ", two";
}
