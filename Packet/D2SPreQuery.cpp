#include "../Common.h"

namespace std {
	
	__i8 D2SPreQuery::pushValue(enum_field_types nType, char * nValue, __i16 nLength)
	{
		switch (nType) {
		case MYSQL_TYPE_TINY:
			return mBufWriter.runInt8(nValue, nLength, true);
		case MYSQL_TYPE_SHORT:
			return mBufWriter.runInt16(nValue, nLength, true);
		case MYSQL_TYPE_LONG:
			return mBufWriter.runInt32(nValue, nLength, true);
		case MYSQL_TYPE_LONGLONG:
			return mBufWriter.runInt64(nValue, nLength, true);
		case MYSQL_TYPE_FLOAT:
			return mBufWriter.runFloat(nValue, nLength, true);
		case MYSQL_TYPE_DOUBLE:
			return mBufWriter.runDouble(nValue, nLength, true);
		case MYSQL_TYPE_STRING:
		case MYSQL_TYPE_VAR_STRING:
			return mBufWriter.runString(nValue, nLength);
		case MYSQL_TYPE_TINY_BLOB:
		case MYSQL_TYPE_MEDIUM_BLOB:
		case MYSQL_TYPE_LONG_BLOB:
		case MYSQL_TYPE_BLOB:
			return mBufWriter.runBlob(nValue, nLength);
		default:
			return DbError_::mNoField_;
		}
	}

	void D2SPreQuery::setErrorCode(__i8 nErrorCode)
	{
		mErrorCode = nErrorCode;
	}
	
	void D2SPreQuery::setRowCount(__i16 nRowCount)
	{
		mRowCount = nRowCount;
	}

	void D2SPreQuery::runClear()
	{
		mBufWriter.runClear();

		mCommandNo = 0;
		mErrorCode = DbError_::mError_;
		mRowCount = 0;
	}

	D2SPreQuery::D2SPreQuery(__i32 nCommandNo)
		: mCommandNo (nCommandNo)
		, mErrorCode (DbError_::mError_)
		, mRowCount (0)
	{
		mBufWriter.runClear();
	}
	
	D2SPreQuery::~D2SPreQuery()
	{
		mBufWriter.runClear();

		mCommandNo = 0;
		mErrorCode = DbError_::mError_;
		mRowCount = 0;
	}
	
}
