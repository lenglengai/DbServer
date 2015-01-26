#include "../Common.h"

namespace std {
	
	void D2SPreCommand::setErrorCode(__i8 nErrorCode)
	{
		mErrorCode = nErrorCode;
	}
	
	void D2SPreCommand::setRowCount(__i16 nRowCount)
	{
		mRowCount = nRowCount;
	}

	bool D2SPreCommand::getCommit() const
	{
		return mCommit;
	}

	D2SPreCommand::D2SPreCommand(__i32 nCommandNo)
		: mCommandNo (nCommandNo)
		, mErrorCode (DbError_::mError_)
		, mRowCount (0)
		, mCommit(false)
	{
	}
	
	D2SPreCommand::~D2SPreCommand()
	{
		mCommandNo = 0;
		mErrorCode = DbError_::mError_;
		mRowCount = 0;

		mCommit = false;
	}
	
}
