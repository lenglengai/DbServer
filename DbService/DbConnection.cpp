#include "../Common.h"

namespace std {
	
	__i8 DbConnection::runCommand(const string& nCommand, D2SCommand * nD2SCommand)
	{
		if (nD2SCommand->getCommit()) {
			this->beginTransaction();
		}
		__i8 errorCode_ = DbError_::mSucess_; __i16 rowCount_ = 0;
		errorCode_ = this->runCommand(nCommand.c_str(), nCommand.length());
		nD2SCommand->setErrorCode(errorCode_);
		if ( DbError_::mSucess_ == errorCode_ ) {
			rowCount_ = static_cast<__i16>(mysql_affected_rows(&mHandle));
			nD2SCommand->setRowCount(rowCount_);
			if (nD2SCommand->getCommit()) {
				this->commitTransaction();
			}
		} else {
			if (nD2SCommand->getCommit()) {
				this->rollbackTransaction();
			}
		}
		return errorCode_;
	}
	
	__i8 DbConnection::runCommand(const char * nCommand, __i16 nLength)
	{
		int errorCode_ = 0, errorNo_ = 0;
		for (int i = 0; i < 2; ++i) {
			errorCode_ = mysql_real_query(&mHandle, nCommand, nLength);
			if (0 == errorCode_) break;
			if ( i > 0 ) {
				LogService& logService_ = Singleton<LogService>::instance();
				logService_.logError(log_1(mysql_error(&mHandle)));
				return DbError_::mCommand_;
			}
			errorNo_ = mysql_errno(&mHandle);
			if ( (CR_SERVER_GONE_ERROR == errorNo_)
				|| (CR_SERVER_LOST == errorNo_) 
				|| (CR_SERVER_LOST_EXTENDED == errorNo_) ) {
				this->runActivate(true);
				continue;
			}
		}
		return DbError_::mSucess_;
	}
	
	__i8 DbConnection::runQuery(const string& nQuery, D2SQuery * nD2SQuery)
	{
		__i8 errorCode_ = DbError_::mSucess_;
		errorCode_ = this->runCommand(nQuery.c_str(), nQuery.length());
		if ( DbError_::mSucess_ != errorCode_ ) {
			nD2SQuery->setErrorCode(errorCode_);
			return errorCode_;
		}
		MYSQL_RES * resultHandle_ = mysql_store_result(&mHandle);
		if ( nullptr == resultHandle_ ) {
			nD2SQuery->setErrorCode(DbError_::mNoResult_);
			return DbError_::mNoResult_;
		}
		__i16 rowCount_ = static_cast<__i16>(mysql_num_rows(resultHandle_));
		if ( rowCount_ <= 0 ) {
			nD2SQuery->setErrorCode(DbError_::mNoResult_);
			mysql_free_result(resultHandle_);
			return DbError_::mNoResult_;
		}
		DbResult dbResult_(resultHandle_, rowCount_);
		errorCode_ = dbResult_.runQuery(nD2SQuery);
		nD2SQuery->setErrorCode(errorCode_);
		nD2SQuery->setRowCount(rowCount_);
		return errorCode_;
	}
	
	__i8 DbConnection::runPreStatement()
	{
		mDbStatements.clear();
		
		const map<__i16, string>& statements_ = mDataBase->getStatements();
		for ( auto& it : statements_ ) {
			MYSQL_STMT * stmtHandle_ = mysql_stmt_init(&mHandle);
			if ( nullptr == stmtHandle_ ) {
				LogService& logService_ = Singleton<LogService>::instance();
				logService_.logError(log_1(mysql_error(&mHandle)));
				return DbError_::mStmtInit_;
			}
			const string& command_ = it.second;
			if ( 0 != mysql_stmt_prepare(stmtHandle_, command_.c_str(), command_.length()) ) {
				LogService& logService_ = Singleton<LogService>::instance();
				logService_.logError(log_1(mysql_stmt_error(stmtHandle_)));
				mysql_stmt_close(stmtHandle_);
				return DbError_::mStmtPrep_;
			}
			DbStatementPtr dbStatement_(new DbStatement(stmtHandle_));
			mDbStatements[it.first] = dbStatement_;
		}
		return DbError_::mSucess_;
	}
	
	__i8 DbConnection::runPreCommand(S2DPreCommandPtr& nS2DPreCommand, D2SPreCommand * nD2SPreCommand)
	{
		if (nD2SPreCommand->getCommit()) {
			this->beginTransaction();
		}
		__i8 errorCode_ = DbError_::mSucess_; __i16 rowCount_ = 0;
		for ( int i = 0; i < 2; i++ ) {
			errorCode_ = this->runPreCommand(nS2DPreCommand, rowCount_);
			if ( DbError_::mSucess_ == errorCode_ ) {
				nD2SPreCommand->setRowCount(rowCount_);
				break;
			}
			if ( i > 0 ) break;
			if (DbError_::mReconnect_ == errorCode_) {
				this->runActivate(true);
			} else {
				break;
			}
		}
		nD2SPreCommand->setErrorCode(errorCode_);
		if (DbError_::mSucess_ == errorCode_) {
			if (nD2SPreCommand->getCommit()) {
				this->commitTransaction();
			}
		} else {
			if (nD2SPreCommand->getCommit()) {
				this->rollbackTransaction();
			}
		}
		return errorCode_;
	}
	
	__i8 DbConnection::runPreCommand(S2DPreCommandPtr& nS2DPreCommand, __i16& nRowCount)
	{
		__i16 command_ = nS2DPreCommand->getCommand();
		auto it = mDbStatements.find(command_);
		if ( it == mDbStatements.end() ) {
			LogService& logService_ = Singleton<LogService>::instance();
			logService_.logError(log_1(command_));
			return DbError_::mNoStatement_;
		}
		DbStatementPtr& dbStatement_ = it->second; __i16 count_ = 0;
		list<DbParamPtr>& dbParams_ = nS2DPreCommand->getDbParams();
		for ( auto& it0 : dbParams_ ) {
			if ( !dbStatement_->pushParam(count_, it0) ) {
				LogService& logService_ = Singleton<LogService>::instance();
				logService_.logError(log_1(count_));
				return DbError_::mPushParam_;
			}
			count_++;
		}
		__i8 errorCode_ = this->runDbStatement(dbStatement_);
		MYSQL_STMT* msql_STMT_ = dbStatement_->getHandle();
		if (DbError_::mSucess_ == errorCode_) {
			nRowCount = static_cast<__i16>(mysql_stmt_affected_rows(msql_STMT_));
		} else {
			LogService& logService_ = Singleton<LogService>::instance();
			logService_.logError(log_1( mysql_stmt_error(msql_STMT_)));
		}
		return errorCode_;
	}
	
	__i8 DbConnection::runDbStatement(DbStatementPtr& nDbStatement)
	{
        MYSQL_STMT* msql_STMT_ = nDbStatement->getHandle();
        MYSQL_BIND* msql_BIND_ = nDbStatement->getParamBind();
		int errorCode_ = mysql_stmt_bind_param(msql_STMT_, msql_BIND_);
		if (0 != errorCode_) {
			int errorNo_ = mysql_stmt_errno(msql_STMT_);
			if ( (CR_SERVER_GONE_ERROR == errorNo_)
				|| (CR_SERVER_LOST == errorNo_)
				|| (CR_SERVER_LOST_EXTENDED == errorNo_) ) {
				return DbError_::mReconnect_;
			}
			return DbError_::mPreCommand_;
		}
		errorCode_ = mysql_stmt_execute(msql_STMT_);
		if (0 != errorCode_) {
			int errorNo_ = mysql_stmt_errno(msql_STMT_);
			if ( (CR_SERVER_GONE_ERROR == errorNo_)
				|| (CR_SERVER_LOST == errorNo_)
				|| (CR_SERVER_LOST_EXTENDED == errorNo_) ) {
				return DbError_::mReconnect_;
			}
			return DbError_::mPreCommand_;
		}
		return DbError_::mSucess_;
	}
	
	__i8 DbConnection::runPreQuery(S2DPreQueryPtr& nS2DPreQuery, D2SPreQuery * nD2SPreQuery)
	{
		__i8 errorCode_ = DbError_::mSucess_;
		for ( int i = 0; i < 2; i++ ) {
			errorCode_ = this->interalPreQuery(nS2DPreQuery, nD2SPreQuery);
			if ( DbError_::mSucess_ == errorCode_ ) {
				break;
			}
			if ( i > 0 ) break;
			if (DbError_::mReconnect_ == errorCode_) {
				this->runActivate(true);
			} else {
				break;
			}
		}
		nD2SPreQuery->setErrorCode(errorCode_);
		return errorCode_;
	}
	
	__i8 DbConnection::interalPreQuery(S2DPreQueryPtr& nS2DPreQuery, D2SPreQuery * nD2SPreQuery)
	{
		__i16 command_ = nS2DPreQuery->getCommand();
		auto it = mDbStatements.find(command_);
		if ( it == mDbStatements.end() ) {
			LogService& logService_ = Singleton<LogService>::instance();
			logService_.logError(log_1(command_));
			return DbError_::mNoStatement_;
		}
		DbStatementPtr& dbStatement_ = it->second; __i16 count_ = 0;
		list<DbParamPtr>& dbParams_ = nS2DPreQuery->getDbParams();
		for ( auto& it0 : dbParams_ ) {
			if ( !dbStatement_->pushParam(count_, it0) ) {
				LogService& logService_ = Singleton<LogService>::instance();
				logService_.logError(log_1(count_));
				return DbError_::mPushParam_;
			}
			count_++;
		}
		__i8 errorCode_ = this->runDbStatement(dbStatement_);
		MYSQL_STMT* msql_STMT_ = dbStatement_->getHandle();
		if (DbError_::mSucess_ != errorCode_) {
			LogService& logService_ = Singleton<LogService>::instance();
			logService_.logError(log_1( mysql_stmt_error(msql_STMT_)));
			return errorCode_;
		}
		MYSQL_RES * resultHandle_ = mysql_stmt_result_metadata(msql_STMT_);
        __i16 rowCount_ = static_cast<__i16>(mysql_stmt_num_rows(msql_STMT_));
        __i16 fieldCount_ = static_cast<__i16>(mysql_stmt_field_count(msql_STMT_));
		
		if (mysql_stmt_store_result(msql_STMT_)) {
			return DbError_::mNoResult_;
		}
		
		DbPreResult dbPreResult_(msql_STMT_, resultHandle_, rowCount_, fieldCount_);
		errorCode_ = dbPreResult_.runQuery(nD2SPreQuery);
		nD2SPreQuery->setErrorCode(errorCode_);
		nD2SPreQuery->setRowCount(rowCount_);
		return errorCode_;
	}

	void DbConnection::beginTransaction()
	{
		const char * sql_ = "START TRANSACTION";
		this->runCommand(sql_, strlen(sql_));
	}

	void DbConnection::rollbackTransaction()
	{
		const char * sql_ = "ROLLBACK";
		this->runCommand(sql_, strlen(sql_));
	}

	void DbConnection::commitTransaction()
	{
		const char * sql_ = "COMMIT";
		this->runCommand(sql_, strlen(sql_));
	}
	
	bool DbConnection::runAcquire()
	{
		this->runActivate();
		if ( (!mBusy) && mConnected ) {
			mBusy = true;
			return true;
		}
		return false;
	}
	
	void DbConnection::runRecycle()
	{
		mBusy = false;
	}
	
	void DbConnection::runActivate(bool nForce)
	{
		if ( (!mConnected ) || nForce ) {
			this->runDisconnect();
			this->runConnect();
			return;
		}
		if (!mBusy) {
			TimeService& timeService_ = Singleton<TimeService>::instance();
			__i64 currentTime_ = timeService_.getLocalTime();
			if (currentTime_ > mTimeStamp) {
				this->runDisconnect();
				this->runConnect();
			}
		}
	}
	
	bool DbConnection::runConnect()
	{
		if (mConnected) return true;
		if ( internalConnect() ) {
			this->runPreStatement();
			TimeService& timeService_ = Singleton<TimeService>::instance();
			mTimeStamp = timeService_.getLocalTime();
			mTimeStamp += mDataBase->getMaxSeconds();
			mConnected = true;
			mBusy = false;
			return true;
		}
		return false;
	}
	
	void DbConnection::runDisconnect()
	{
		if (mConnected) {
			mDbStatements.clear();
			internalDisconnect();
			mConnected = false;
			mBusy = false;
			mTimeStamp = 0;
		}
	}
	
	bool DbConnection::internalConnect()
	{
	    if ( nullptr == mysql_init(&mHandle) ) {
			LogService& logService_ = Singleton<LogService>::instance();
			logService_.logError(log_1("mysql_init"));
			return false;
		}
		if ( nullptr == mysql_real_connect(&mHandle,
			mDataBase->getHostName().c_str(),
			mDataBase->getUserName().c_str(),
			mDataBase->getPassword().c_str(),
			mDataBase->getDbName().c_str(),
			mDataBase->getPort(), nullptr, 0) ) {
			LogService& logService_ = Singleton<LogService>::instance();
			logService_.logError(log_1(mysql_error(&mHandle)));
			return false;
		}
		mysql_autocommit(&mHandle, 0);
		mysql_set_character_set(&mHandle, "utf8");
		return true;
	}
	
	void DbConnection::internalDisconnect()
	{
		::mysql_close(&mHandle);
	}
	
	DbConnection::DbConnection(DataBase * nDataBase)
		: mDataBase (nDataBase)
		, mBusy (false)
		, mConnected (false)
		, mTimeStamp (0)
	{
	}
	
	DbConnection::~DbConnection()
	{
		mDataBase = nullptr;
		mConnected = false;
		mTimeStamp = 0;
		mBusy = false;
	}
	
}
