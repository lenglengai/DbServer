#include "../Common.h"

namespace std {
	
	__i8 DataBase::runCommand(const string& nCommand, D2SCommand * nD2SCommand)
	{
		DbConnectionPtr& dbConnection_ = this->acquireConnection();
		if (!dbConnection_) {
			return DbError_::mAcquireConnetion_;
		}
		__i8 result_ = dbConnection_->runCommand(nCommand, nD2SCommand);
		this->recycleConnection(dbConnection_);
		return result_;
	}
	
	__i8 DataBase::runQuery(const string& nQuery, D2SQuery * nD2SQuery)
	{
		DbConnectionPtr& dbConnection_ = this->acquireConnection();
		if (!dbConnection_) {
			return DbError_::mAcquireConnetion_;
		}
		__i8 result_ = dbConnection_->runQuery(nQuery, nD2SQuery);
		this->recycleConnection(dbConnection_);
		return result_;
	}
	
	__i8 DataBase::registerStatement(S2DStatementPtr& nS2DStatement, D2SStatement * nD2SStatement)
	{
		const map<__i16, string>& statements_ = nS2DStatement->getStatements();
		for ( auto& it : statements_ ) {
			auto it0 = mStatements.find(it.first);
			if ( it0 != mStatements.end() ) {
				nD2SStatement->setErrorCode(DbError_::mStmtRepeat_);
				return DbError_::mSucess_;
			}
		}
		for ( auto& it : statements_ ) {
			mStatements[it.first] = it.second;
		}
		nD2SStatement->setErrorCode(DbError_::mSucess_);
		return DbError_::mSucess_;
	}
	
	const map<__i16, string>& DataBase::getStatements() const
	{
		return mStatements;
	}
	
	__i8 DataBase::runPreCommand(S2DPreCommandPtr& nS2DPreCommand, D2SPreCommand * nD2SPreCommand)
	{
		DbConnectionPtr& dbConnection_ = this->acquireConnection();
		if (!dbConnection_) {
			return DbError_::mAcquireConnetion_;
		}
		__i8 result_ = dbConnection_->runPreCommand(nS2DPreCommand, nD2SPreCommand);
		this->recycleConnection(dbConnection_);
		return result_;
	}
	
	__i8 DataBase::runPreQuery(S2DPreQueryPtr& nS2DPreQuery, D2SPreQuery * nD2SPreQuery)
	{
		DbConnectionPtr& dbConnection_ = this->acquireConnection();
		if (!dbConnection_) {
			return DbError_::mAcquireConnetion_;
		}
		__i8 result_ = dbConnection_->runPreQuery(nS2DPreQuery, nD2SPreQuery);
		this->recycleConnection(dbConnection_);
		return result_;
	}
	
	void DataBase::recycleConnection(DbConnectionPtr& nDbConnection)
	{
		std::lock_guard<std::mutex> lock_(mMutex);
		nDbConnection->runRecycle();
	}
	
	DbConnectionPtr& DataBase::acquireConnection()
	{
		std::lock_guard<std::mutex> lock_(mMutex);
		for (auto& it : mDbConnections) {
			if ( it->runAcquire() ) {
				return it;
			}
		}
		__i32 connectionCount_ = static_cast<__i32>(mDbConnections.size());
		if (connectionCount_ >= mMaxCounts) {
			LogService& logService_ = Singleton<LogService>::instance();
			logService_.logError(log_1(connectionCount_));
			return __defaultptr<DbConnection>();
		}
		DbConnectionPtr dbConnection_(new DbConnection(this));
		dbConnection_->runAcquire();
		mDbConnections.push_back(dbConnection_);
		return mDbConnections.back();
	}
	
	void DataBase::runClose()
	{
		std::lock_guard<std::mutex> lock_(mMutex);
		for (auto& it : mDbConnections) {
			it->runDisconnect();
		}
	}
	
	void DataBase::runClear()
	{
		mStatements.clear();
		
		std::lock_guard<std::mutex> lock_(mMutex);
		mDbConnections.clear();
	}
	
	const string& DataBase::getDbName() const
	{
		return mDbName;
	}
	
	const string& DataBase::getHostName() const
	{
		return mHostName;
	}
	
	const string& DataBase::getUserName() const
	{
		return mUserName;
	}
	
	const string& DataBase::getPassword() const
	{
		return mPassword;
	}
	
	__i32 DataBase::getPort() const
	{
		return mPort;
	}
	
	__i32 DataBase::getMaxSeconds() const
	{
		return mMaxSeconds;
	}
	
	DataBase::DataBase()
		: mDbName ( "gameDb" )
		, mHostName ( "127.0.0.1" )
		, mUserName ( "root" )
		, mPassword ( "zyouhua" )
		, mPort ( 3307 )
		, mMaxCounts ( 100 )
		, mMaxSeconds ( 36000 )
	{
	}
	
	DataBase::~DataBase()
	{
		mDbName = "gameDb";
		mHostName = "127.0.0.1";
		mUserName = "root";
		mPassword = "zyouhua";
		mPort = 3307;
		
		mMaxCounts = 100;
		mMaxSeconds = 10;
	}
	
}
