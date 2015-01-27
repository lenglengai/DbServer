#include "../Common.h"
#include "IoService.h"

namespace std{
	
	void SessionService::removeSession(__i32 nSessionId)
	{
		lock_guard<mutex> lock_(mMutex);
		auto it = mSessions.find(nSessionId);
		if (it == mSessions.end()) {
			LogService& logService_ = Service<LogService>::instance();
			logService_.logError(log_1(nSessionId));
			return;
		}
		mSessions.erase(it);
	}
	
	SessionPtr& SessionService::createSession()
	{
		IoService& ioService_ = Service<IoService>::instance();
		asio::io_service& ioservice = ioService_.getIoService();
		SessionPtr session_(new Session(++mSessionId, ioservice));
		lock_guard<mutex> lock_(mMutex);
		mSessions[mSessionId] = session_;
		return mSessions[mSessionId];
	}
	
	void SessionService::runClear()
	{
		mSessions.clear();
		
		mSessionId = 0;
	}
	
	SessionService::SessionService()
	{
	}
	
	SessionService::~SessionService()
	{
	}
	
}
