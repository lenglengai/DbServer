#pragma once

namespace std {

	class DbResult : noncopyable
	{
	public:
		__i8 runQuery(D2SQuery * nD2SQuery);
		
		DbResult(MYSQL_RES * nHandle, __i16 nRowCount);
		~DbResult();
		
	private:
		MYSQL_RES * mHandle;
		__i16 mRowCount;
	};
	
}
