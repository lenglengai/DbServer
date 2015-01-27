#pragma once

namespace std {

	class IoService
	{
	public:
		asio::io_service& getIoService();
		
	public:
		template<class __t>
		void headSerialize(__t& nT)
		{
			nT.runInt32(mIoServiceCount, "ioServiceCount");
		}
		const char * streamName() const;
		const char * streamUrl() const;
		
		bool runConfig();
		bool initBegin();
		void startBegin();
		void stopBegin();
		void runing();
		void runClear();
		
		IoService();
		~IoService();
		
	private:
		typedef shared_ptr<asio::io_service> IoServicePtr;
		typedef shared_ptr<asio::io_service::work> WorkPtr;
		shared_ptr<asio::signal_set> mSignals;
		vector<IoServicePtr> mIoServices;
		vector<WorkPtr> mWorks;
		size_t mNextIoService;
		__i32 mIoServiceCount;
	};

}
