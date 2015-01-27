#pragma once

#include "IProtocol.h"

namespace std {

	class ProtocolService
	{
	public:
		bool runReadBlock(ReadBlockPtr& nReadBlock, SessionPtr& nSession);
		
		template <class __t>
		void runRegister(__t * nT)
		{
			__i32 protocolId = __classid<__t>();
			auto it = mProtocols.find(protocolId);
			if (it != mProtocols.end()) {
				LogService& logService_ = Service<LogService>::instance();
				logService_.logError(log_1(protocolId));
				return;
			}
			mProtocols[protocolId] = nT;
		}
		
	public:
		bool runPreinit();
		void runClear();

		ProtocolService();
		~ProtocolService();

	private:
		map<__i32, IProtocol *> mProtocols;
	};

}
