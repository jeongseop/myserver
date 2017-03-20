#include "Log.hpp"

BOOST_LOG_GLOBAL_LOGGER_INIT(my_logger, logger_t)
{
	logger_t lg;

	logging::core::get()->add_global_attribute("TimeStamp", attrs::local_clock());
	logging::core::get()->add_global_attribute("RecordID", attrs::counter< unsigned int >());

	logging::add_file_log(
			keywords::file_name = SYS_LOGFILE,
			keywords::open_mode = (std::ios_base::out | std::ios_base::app),
			keywords::rotation_size = 1024 * 1024 * 10,
			keywords::time_based_rotation = sinks::file::rotation_at_time_point(0,0,0),
			keywords::min_free_space = 1024 * 1024 * 200,
			keywords::format = (
				expr::stream
					<< "[" << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
					<< "] <" << logging::trivial::severity
					<< "> " << expr::message
				)
			);

	logging::add_console_log(
			std::cout,
			keywords::format = (
				expr::stream
					<< "[" << expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
					<< "] <" << logging::trivial::severity
					<< "> " << expr::message
				)
			);

#ifdef DEBUG
	logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::trace);
#else
	logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::info);
#endif

	return lg;
}
