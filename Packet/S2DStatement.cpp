#include "../Common.h"

namespace std {
	
	void S2DStatement::pushStatement(__i16 nCommandId, const char * nCommand)
	{
		mStatements[nCommandId] = nCommand;
	}
	
	const map<__i16, string>& S2DStatement::getStatements() const
	{
		return mStatements;
	}
	
	__i32 S2DStatement::getCommandNo() const
	{
		return mCommandNo;
	}
	
	S2DStatement::S2DStatement()
		: mCommandNo (0)
	{
		mStatements.clear();
	}
	
	S2DStatement::~S2DStatement()
	{
		mStatements.clear();
		mCommandNo = 0;
	}
	
}
