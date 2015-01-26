#include "../Common.h"

namespace std {
	
	void D2SStatement::setErrorCode(__i8 nErrorCode)
	{
		mErrorCode = nErrorCode;
	}
	
	D2SStatement::D2SStatement()
		: mCommandNo (0)
		, mErrorCode (DbError_::mSucess_)
	{
	}
	
	D2SStatement::~D2SStatement()
	{
		mCommandNo = 0;
		mErrorCode = DbError_::mSucess_;
	}
	
}
