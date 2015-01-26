#pragma once

namespace std {
	
	class S2DPreQuery
	{
	public:
		void pushDbParam(DbParamPtr& nDbParam);
		list<DbParamPtr>& getDbParams();
		__i16 getCommand() const;
		
		S2DPreQuery(__i32 nCommandNo, __i16 nCommand);
		~S2DPreQuery();
		
	private:
		list<DbParamPtr> mDbParams;
		__i16 mCommand;
		__i32 mCommandNo;
	};
	typedef shared_ptr<S2DPreQuery> S2DPreQueryPtr;
	
}
