#pragma once

namespace std {
	
	class DbStatement : noncopyable
	{
	public:
		bool pushParam(__i16 nIndex, DbParamPtr& nDbParam);
		MYSQL_BIND * getParamBind();
		MYSQL_STMT * getHandle();
		
	private:
		enum_field_types getBufType(__i8 nDbType);
		__i16 getBufLength(__i8 nDbType);
		
	public:
		DbStatement(MYSQL_STMT * nHandle);
		~DbStatement();
		
	private:
        MYSQL_STMT * mHandle;
        MYSQL_BIND * mParamBind;
		__i16 nParamCount;
		unsigned long mLength;
	};
	typedef shared_ptr<DbStatement> DbStatementPtr;
	
}
