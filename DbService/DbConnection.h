#pragma once

namespace std {
	
	class DataBase;
	class DbConnection : noncopyable
	{
	public:
		__i8 runCommand(const string& nCommand, D2SCommand * nD2SCommand);
		__i8 runQuery(const string& nQuery, D2SQuery * nD2SQuery);
		__i8 runPreCommand(S2DPreCommandPtr& nS2DPreCommand, D2SPreCommand * nD2SPreCommand);
		__i8 runPreCommand(S2DPreCommandPtr& nS2DPreCommand, __i16& nRowCount);
		__i8 runDbStatement(DbStatementPtr& nDbStatement);
		__i8 runPreQuery(S2DPreQueryPtr& nS2DPreQuery, D2SPreQuery * nD2SPreQuery);

		void beginTransaction();
		void rollbackTransaction();
		void commitTransaction();

		bool runAcquire();
		void runRecycle();
		
		bool runConnect();
		void runDisconnect();
		
	private:
		__i8 interalPreQuery(S2DPreQueryPtr& nS2DPreQuery, D2SPreQuery * nD2SPreQuery);
		__i8 runCommand(const char * nCommand, __i16 nLength);
		
		void runActivate(bool nForce = false);
		bool internalConnect();
		void internalDisconnect();
		
		__i8 runPreStatement();
		
	public:
		explicit DbConnection(DataBase * nDataBase);
		~DbConnection();
		
	private:
		map<__i16, DbStatementPtr> mDbStatements;
		
		DataBase * mDataBase;
		__i32 mTimeStamp;
		bool mConnected;
		bool mBusy;
		
		MYSQL mHandle;
	};
	typedef shared_ptr<DbConnection> DbConnectionPtr;
	
}
