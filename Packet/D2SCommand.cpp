#include "../Common.h"

namespace std {
	
	void D2SCommand::setErrorCode(__i8 nErrorCode)
	{
		mErrorCode = nErrorCode;
	}
	
	void D2SCommand::setRowCount(__i16 nRowCount)
	{
		mRowCount = nRowCount;
	}

	bool D2SCommand::getCommit() const
	{
		return mCommit;
	}

	D2SCommand::D2SCommand(__i32 nCommandNo)
		: mCommandNo (nCommandNo)
		, mErrorCode (DbError_::mError_)
		, mRowCount (0)
		, mCommit(false)
	{
	}
	
	D2SCommand::~D2SCommand()
	{
		mCommandNo = 0;
		mErrorCode = DbError_::mError_;
		mRowCount = 0;

		mCommit = false;
	}
	
}
