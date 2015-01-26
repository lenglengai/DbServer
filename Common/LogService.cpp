#include "../Common.h"

#include <boost/log/sinks.hpp>
#include <boost/log/common.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/smart_ptr.hpp>

namespace std {

	namespace logging = boost::log;
	namespace sinks = boost::log::sinks;
	namespace keywords = boost::log::keywords;
	namespace expr = boost::log::expressions;
	namespace attrs = boost::log::attributes;

	void LogService::logError(boost::format& nFormat)
	{
		BOOST_LOG(mLogger) << "[error]" << nFormat;
	}

	void LogService::logInfo(boost::format& nFormat)
	{
		BOOST_LOG(mLogger) << "[info]" << nFormat;
	}
	
	bool LogService::runPreinit()
	{
		auto console_sink = logging::add_console_log();
		console_sink->set_formatter
        (
            expr::format("[%1%]%2%")
                % expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
                % expr::smessage
        );
        logging::core::get()->add_sink(console_sink);
		typedef sinks::asynchronous_sink< sinks::text_file_backend > text_sink;

		boost::shared_ptr< text_sink > testSink(new text_sink(keywords::file_name = "dbServer%Y-%m-%d.log",
			keywords::rotation_size = 10 * 1024 * 1024,
			keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
			keywords::open_mode = (std::ios::out | std::ios::app)
			));
		testSink->set_formatter
        (
            expr::format("[%1%]%2%")
                % expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S")
                % expr::smessage
        );
    	logging::core::get()->add_sink(testSink);
		logging::core::get()->add_global_attribute("TimeStamp", attrs::local_clock());
		return true;
	}

	LogService::LogService()
	{
	}

	LogService::~LogService()
	{
	}
	
}
