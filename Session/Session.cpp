#include "../Common.h"

namespace std {

	bool Session::runSend(PacketPtr& nPacket)
	{
		if ( SessionState_::mClosed_ == mSessionState ) {
			LogService& logService_ = Singleton<LogService>::instance();
			logService_.logError(log_1(mSessionState));
			return false;
		}
		nPacket->runInit();
		this->pushPacket(nPacket);
		if (false == mSending) {
			this->internalSend();
		}
		return true;
	}

	void Session::runStart()
	{
		try {
			mReadTimer.expires_from_now(boost::posix_time::seconds(Session::read_timeout));
			mReadTimer.async_wait(boost::bind(&Session::handleReadTimeout, 
				shared_from_this(), boost::asio::placeholders::error));
			mSocket.async_read_some(boost::asio::buffer(mReadBuffer),
				boost::bind(&Session::handleRead, shared_from_this(),
				asio::placeholders::error,
				asio::placeholders::bytes_transferred));
		} catch (boost::system::system_error& e) {
			LogService& logService_ = Singleton<LogService>::instance();
			logService_.logError(log_1(e.what()));
			this->runClose();
		}
	}

	void Session::handleRead(const boost::system::error_code& nError, size_t nBytes)
	{
		mReadTimer.cancel();
		if (nError) {
			LogService& logService_ = Singleton<LogService>::instance();
			logService_.logError(log_1(nError.message()));
			this->runClose();
			return;
		}
		BlockPushType_ blockPushType_ = mReadBlock->runPush(mReadBuffer.data(), nBytes);
		if (BlockPushType_::mError_ == blockPushType_) {
			LogService& logService_ = Singleton<LogService>::instance();
			logService_.logError(log_1("mBlockPushTypeError_ == blockPushType_"));
			this->runClose();
			return;
		}
		if (BlockPushType_::mLength_ == blockPushType_) return;
		ProtocolService& protocolService_ = Singleton<ProtocolService>::instance();
		if (!protocolService_.runReadBlock(mReadBlock, shared_from_this())) {
			LogService& logService_ = Singleton<LogService>::instance();
			logService_.logError(log_1("protocolService_.runReadBlock"));
			this->runClose();
			return;
		}
		mReadBlock->endPush();
		mReadBuffer.assign(0);
		this->runStart();
	}

	void Session::handleReadTimeout(const boost::system::error_code& nError)
	{
		if (mReadTimer.expires_at() <= asio::deadline_timer::traits_type::now()) {
			LogService& logService_ = Singleton<LogService>::instance();
			logService_.logError(log_1(nError.message()));
			mReadTimer.expires_at(boost::posix_time::pos_infin);
			this->runClose();
		}
	}

	void Session::handleWrite(const boost::system::error_code& nError)
	{
		mWriteTimer.cancel();
		if (nError) {
			LogService& logService_ = Singleton<LogService>::instance();
			logService_.logError(log_1(nError.message()));
			this->runClose();
			return;
		}
		this->internalSend();
	}

	void Session::handleWriteTimeout(const boost::system::error_code& nError)
	{
		if (mWriteTimer.expires_at() <= asio::deadline_timer::traits_type::now()) {
			LogService& logService_ = Singleton<LogService>::instance();
			logService_.logError(log_1(nError.message()));
			mWriteTimer.expires_at(boost::posix_time::pos_infin);
			this->runClose();
		}
	}

	__i32 Session::getSessionState() const
	{
		return mSessionState;
	}
	
	void Session::setSecond(const __i32 nSecond)
	{
		mSecond = nSecond;
	}
	
	__i32 Session::getSecond() const
	{
		return mSecond;
	}

	void Session::openSession()
	{
		mSessionState = SessionState_::mOpened_;
		this->runStart();
	}
	
	__i32 Session::getSessionId() const
	{
		return mSessionId;
	}

	void Session::runClose()
	{
		mSessionState = SessionState_::mClosed_;
		if (mSocket.is_open()) {
			try {
				boost::system::error_code error_;
				mSocket.shutdown(asio::socket_base::shutdown_both, error_);
				mSocket.close(error_);
				mSecond = 0;
				SessionService& sessionService_ = Singleton<SessionService>::instance();
				sessionService_.removeSession(mSessionId);
			} catch (boost::system::system_error& e) {
				LogService& logService_ = Singleton<LogService>::instance();
				logService_.logError(log_1(e.what()));
			}
		}
	}
	
	bool Session::isClosed()
	{
		if ( SessionState_::mClosed_ == mSessionState ) {
			return true;
		}
		if (!mSocket.is_open()) {
			return true;
		}
		return false;
	}

	void Session::pushPacket(PacketPtr& nPacket)
	{
		lock_guard<mutex> lock_(mMutex);
		mPackets.push_back(nPacket);
	}

	PacketPtr Session::popPacket()
	{
		lock_guard<mutex> lock_(mMutex);
		PacketPtr packet_;
		if (mPackets.size() > 0) {
			packet_ = mPackets.front();
			mPackets.pop_front();
		}
		return packet_;
	}

	void Session::internalSend()
	{
		PacketPtr packet_ = this->popPacket();
		if (!packet_) {
			mSending = false;
			return;
		}
		mWriteBlock->runClear();
		BlockPtr block_ = mWriteBlock;
		if (!packet_->runHeader(block_)) {
			this->runClose();
			return;
		}
		if (!packet_->runBlock(block_)) {
			this->runClose();
			return;
		}
		mWriteBlock->runEnd();
		try {
			mWriteTimer.expires_from_now(boost::posix_time::seconds(Session::write_timeout));
			mWriteTimer.async_wait(boost::bind(&Session::handleWriteTimeout,
				shared_from_this(), boost::asio::placeholders::error));
			asio::async_write(mSocket, boost::asio::buffer(mWriteBlock->getBuffer(), (mWriteBlock->getTotal())),
				boost::bind(&Session::handleWrite, shared_from_this(),
				asio::placeholders::error));
			mSending = true;
		}
		catch (boost::system::system_error& e) {
			LogService& logService_ = Singleton<LogService>::instance();
			logService_.logError(log_1(e.what()));
			this->runClose();
		}
	}

	asio::ip::tcp::socket& Session::getSocket()
	{
		return mSocket;
	}
	
	Session::Session(__i32 nSessionId, asio::io_service& nIoService)
		: mSessionState(SessionState_::mClosed_)
		, mSocket(nIoService)
		, mReadBlock(new ReadBlock())
		, mWriteBlock(new WriteBlock())
		, mReadTimer(nIoService)
		, mWriteTimer(nIoService)
		, mSending(false)
		, mSessionId(nSessionId)
		, mSecond(0)
	{
		mReadBuffer.fill(0);
		mPackets.clear();
	}

	Session::~Session()
	{
		mWriteBlock->runClear();
		mReadBlock->runClear();
		this->runClose();
		mReadBuffer.fill(0);
		mSending = false;
		mPackets.clear();
		mSessionId = 0;
		mSecond = 0;
	}

}
