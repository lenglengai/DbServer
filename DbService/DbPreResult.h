#pragma once

namespace std {

	class DbPreResult : noncopyable
	{
	public:
		__i8 runQuery(D2SPreQuery * nD2SPreQuery);
		
	private:
		size_t fieldSize(MYSQL_FIELD * nField);
		
	public:
		DbPreResult(MYSQL_STMT * nStmt, MYSQL_RES * nHandle, 
			__i16 nRowCount, __i16 nFieldCount);
		~DbPreResult();
		
	private:
	    my_bool * mIsNull;
        unsigned long * mLength;
		MYSQL_BIND * mBind;
		MYSQL_STMT * mStmt;
		MYSQL_RES * mHandle;
		__i16 mRowCount;
		__i16 mFieldCount;
	};
	
}
