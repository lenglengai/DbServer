#include "../Common.h"

namespace std {
	
	__i8 DbService::runCommand(__i32 nDataBaseId, const string& nCommand, D2SCommand * nD2SCommand)
	{
		auto it = mDataBases.find(nDataBaseId);
		if ( it == mDataBases.end() ) {
			LogService& logService_ = Singleton<LogService>::instance();
			logService_.logError(log_1(nDataBaseId));
			return DbError_::mNoFindDb_;
		}
		DataBasePtr& dataBase_ = it->second;
		return dataBase_->runCommand(nCommand, nD2SCommand);
	}
	
	__i8 DbService::runQuery(__i32 nDataBaseId, const string& nQuery, D2SQuery * nD2SQuery)
	{
		auto it = mDataBases.find(nDataBaseId);
		if ( it == mDataBases.end() ) {
			LogService& logService_ = Singleton<LogService>::instance();
			logService_.logError(log_1(nDataBaseId));
			return DbError_::mNoFindDb_;
		}
		DataBasePtr& dataBase_ = it->second;
		return dataBase_->runQuery(nQuery, nD2SQuery);
	}
	
	__i8 DbService::registerStatement(__i32 nDataBaseId, S2DStatementPtr& nS2DStatement, D2SStatement * nD2SStatement)
	{
		auto it = mDataBases.find(nDataBaseId);
		if ( it == mDataBases.end() ) {
			LogService& logService_ = Singleton<LogService>::instance();
			logService_.logError(log_1(nDataBaseId));
			return DbError_::mNoFindDb_;
		}
		DataBasePtr& dataBase_ = it->second;
		return dataBase_->registerStatement(nS2DStatement, nD2SStatement);
	}
	
	__i8 DbService::runPreCommand(__i32 nDataBaseId, S2DPreCommandPtr& nS2DPreCommand, D2SPreCommand * nD2SPreCommand)
	{
		auto it = mDataBases.find(nDataBaseId);
		if ( it == mDataBases.end() ) {
			LogService& logService_ = Singleton<LogService>::instance();
			logService_.logError(log_1(nDataBaseId));
			return DbError_::mNoFindDb_;
		}
		DataBasePtr& dataBase_ = it->second;
		return dataBase_->runPreCommand(nS2DPreCommand, nD2SPreCommand);
	}
	
	__i8 DbService::runPreQuery(__i32 nDataBaseId, S2DPreQueryPtr& nS2DPreQuery, D2SPreQuery * nD2SPreQuery)
	{
		auto it = mDataBases.find(nDataBaseId);
		if ( it == mDataBases.end() ) {
			LogService& logService_ = Singleton<LogService>::instance();
			logService_.logError(log_1(nDataBaseId));
			return DbError_::mNoFindDb_;
		}
		DataBasePtr& dataBase_ = it->second;
		return dataBase_->runPreQuery(nS2DPreQuery, nD2SPreQuery);
	}
	
	bool DbService::runPreinit()
	{
		if ( 0 != mysql_library_init(0, 0, 0) ) {
			LogService& logService_ = Singleton<LogService>::instance();
			logService_.logError(log_0());
			return false;
		}
		DataBasePtr dataBase_(new DataBase());
		mDataBases[1] = dataBase_;
		return true;
	}
	
	void DbService::runStop()
	{
		for ( auto& it : mDataBases ) {
			DataBasePtr& dataBase_ = it.second;
			dataBase_->runClose();
		}
	}
	
	void DbService::runClear()
	{
		for ( auto& it : mDataBases ) {
			DataBasePtr& dataBase_ = it.second;
			dataBase_->runClear();
		}
		mDataBases.clear();
	}
	
	void DbService::runExit()
	{
		mysql_library_end();
	}
	
	DbService::DbService()
	{
	}
	
	DbService::~DbService()
	{
	}
	
}
