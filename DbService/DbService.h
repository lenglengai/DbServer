#pragma once

namespace std {
	
	class DbService : noncopyable
	{
	public:
		__i8 runCommand(__i32 nDataBaseId, const string& nCommand, D2SCommand * nD2SCommand);
		__i8 runQuery(__i32 nDataBaseId, const string& nQuery, D2SQuery * nD2SQuery);
		__i8 registerStatement(__i32 nDataBaseId, S2DStatementPtr& nS2DStatement, D2SStatement * nD2SStatement);
		__i8 runPreCommand(__i32 nDataBaseId, S2DPreCommandPtr& nS2DPreCommand, D2SPreCommand * nD2SPreCommand);
		__i8 runPreQuery(__i32 nDataBaseId, S2DPreQueryPtr& nS2DPreQuery, D2SPreQuery * nD2SPreQuery);
		
		bool runPreinit();
		void runStop();
		void runClear();
		void runExit();
		
		DbService();
		~DbService();
		
	private:
		map<__i32, DataBasePtr> mDataBases;
	};
	
}
