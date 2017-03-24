#ifndef __LOG_H__
#define __LOG_H__

#include <memory>
#include <iostream>
#include <string>
#include <exception>

#include <boost/core/null_deleter.hpp>
#include <boost/log/core.hpp>
#include <boost/log/common.hpp>
#include <boost/log/utility/setup.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/sources/global_logger_storage.hpp>

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

#define SYS_LOGFILE "../log/gameserver_%Y-%m-%d_%5N.log"
#define SYS_LOGTARGET "../log"

#define LOG(severity) BOOST_LOG_SEV(my_logger::get(),boost::log::trivial::severity) \
	<< "(" << __FILE__ << "::" << __func__ << "::" << __LINE__ << ") : "

#define LOG_TRACE	LOG(trace)
#define LOG_DEBUG	LOG(debug)
#define LOG_INFO	LOG(info)
#define LOG_WARNING LOG(warning)
#define LOG_ERROR	LOG(error)
#define LOG_FATAL	LOG(fatal)

typedef src::severity_logger_mt< logging::trivial::severity_level > logger_t;

BOOST_LOG_GLOBAL_LOGGER(my_logger, logger_t)

#endif
