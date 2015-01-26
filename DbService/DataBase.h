#pragma once

namespace std {
	
	class DataBase : noncopyable
	{
	public:
		__i8 runCommand(const string& nCommand, D2SCommand * nD2SCommand);
		__i8 runQuery(const string& nQuery, D2SQuery * nD2SQuery);
		__i8 registerStatement(S2DStatementPtr& nS2DStatement, D2SStatement * nD2SStatement);
		const map<__i16, string>& getStatements() const;
		__i8 runPreCommand(S2DPreCommandPtr& nS2DPreCommand, D2SPreCommand * nD2SPreCommand);
		__i8 runPreQuery(S2DPreQueryPtr& nS2DPreQuery, D2SPreQuery * nD2SPreQuery);
		
		void runClose();
		void runClear();
		
		const string& getDbName() const;
		const string& getHostName() const;
		const string& getUserName() const;
		const string& getPassword() const;
		__i32 getPort() const;
		__i32 getMaxSeconds() const;
		
	private:
		void recycleConnection(DbConnectionPtr& nDbConnection);
		DbConnectionPtr& acquireConnection();
		
	public:
		DataBase();
		~DataBase();
		
	private:
		map<__i16, string> mStatements;
		
		list<DbConnectionPtr> mDbConnections;
		mutex mMutex;
		
		string mDbName;
		string mHostName;
		string mUserName;
		string mPassword;
		__i32 mPort;
		__i32 mMaxCounts;
		__i32 mMaxSeconds;
	};
	typedef shared_ptr<DataBase> DataBasePtr;
	
}
