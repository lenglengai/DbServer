#include "../Common.h"

namespace std {
	
	void S2DPreCommand::pushDbParam(DbParamPtr& nDbParam)
	{
		mDbParams.push_back(nDbParam);
	}

	list<DbParamPtr>& S2DPreCommand::getDbParams()
	{
		return mDbParams;
	}
	
	__i16 S2DPreCommand::getCommand() const
	{
		return mCommand;
	}
	
	S2DPreCommand::S2DPreCommand(__i32 nCommandNo, __i16 nCommand)
		: mCommandNo (nCommandNo)
		, mCommand (nCommand)
	{
		mDbParams.clear();
	}
	
	S2DPreCommand::~S2DPreCommand()
	{
		mDbParams.clear();
		mCommandNo = 0;
		mCommand = 0;
	}
	
}
