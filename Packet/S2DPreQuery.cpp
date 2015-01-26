#include "../Common.h"

namespace std {
	
	void S2DPreQuery::pushDbParam(DbParamPtr& nDbParam)
	{
		mDbParams.push_back(nDbParam);
	}

	list<DbParamPtr>& S2DPreQuery::getDbParams()
	{
		return mDbParams;
	}
	
	__i16 S2DPreQuery::getCommand() const
	{
		return mCommand;
	}
	
	S2DPreQuery::S2DPreQuery(__i32 nCommandNo, __i16 nCommand)
		: mCommandNo (nCommandNo)
		, mCommand (nCommand)
	{
		mDbParams.clear();
	}
	
	S2DPreQuery::~S2DPreQuery()
	{
		mDbParams.clear();
		mCommandNo = 0;
		mCommand = 0;
	}
	
}
