#include "../Common.h"

namespace std {
	
	const char * IoService::streamName() const
	{
		return "ioService";
	}
	
	const char * IoService::streamUrl() const
	{
		return "ioService.xml";
	}
	
	bool IoService::runConfig()
	{
		ArchiveService& archiveService_ = Service<ArchiveService>::instance();
		return archiveService_.loadStream(this);
	}
	
	bool IoService::initBegin()
	{
		for (__i32 i = 0; i < mIoServiceCount; ++i) {
			IoServicePtr ioService(new asio::io_service());
			WorkPtr work(new asio::io_service::work(*ioService));
			mIoServices.push_back(ioService);
			mWorks.push_back(work);
		}
		return true;
	}
	
	void IoService::startBegin()
	{
		mSignals.reset(new asio::signal_set(this->getIoService()));
		mSignals->add(SIGINT); mSignals->add(SIGTERM);
		mSignals->async_wait(boost::bind(&IoService::stopBegin, this));
	}
	
	void IoService::runing()
	{
		vector<shared_ptr<thread>> threads;
		for (size_t i = 0; i < mIoServices.size(); ++i) {
			shared_ptr<thread> thread_(new thread(boost::bind(&asio::io_service::run, mIoServices[i])));
			threads.push_back(thread_);
		}
		for (size_t i = 0; i < threads.size(); ++i) {
			threads[i]->join();
		}
	}
	
	void IoService::stopBegin()
	{
		for (size_t i = 0; i < mIoServices.size(); ++i) {
			mIoServices[i]->stop();
		}
	}
	
	asio::io_service& IoService::getIoService()
	{
		asio::io_service& ioService = (*(mIoServices[mNextIoService]));
		++mNextIoService;
		if (mNextIoService == mIoServices.size()) {
			mNextIoService = 0;
		}
		return ioService;
	}
	
	void IoService::runClear()
	{
		//mIoServices.clear();
		//mWorks.clear();
		mNextIoService = 0;
		mIoServiceCount = 1;
	}
	
	IoService::IoService()
	{
		this->runClear();
	}
	
	IoService::~IoService()
	{
		this->runClear();
	}
	
}
