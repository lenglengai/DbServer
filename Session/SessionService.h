#pragma once

#include "Session.h"

namespace std {

	class SessionService : public IService
	{
	public:
		void removeSession(__i32 nSessionId);
		SessionPtr& createSession();
		
		void runClear();
		
		SessionService();
		~SessionService();
		
	private:
		map<__i32, SessionPtr> mSessions;
		mutex mMutex;
		
		__i32 mSessionId;
	};

}
