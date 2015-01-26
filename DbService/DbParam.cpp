#include "../Common.h"

namespace std {
	
	void DbParam::setDbType(__i8 nDbType)
	{
		mDbType = nDbType;
	}

	void DbParam::setInt8(__i8 nValue)
	{
		mDbType = DbType_::mInt8_;
		mDbValue.mInt8 = nValue;
	}

	void DbParam::setInt16(__i16 nValue)
	{
		mDbType = DbType_::mInt16_;
		mDbValue.mInt16 = nValue;
	}

	void DbParam::setInt32(__i32 nValue)
	{
		mDbType = DbType_::mInt32_;
		mDbValue.mInt32 = nValue;
	}

	void DbParam::setInt64(__i64 nValue)
	{
		mDbType = DbType_::mInt64_;
		mDbValue.mInt64 = nValue;
	}

	void DbParam::setFloat(float nValue)
	{
		mDbType = DbType_::mFloat_;
		mDbValue.mFloat = nValue;
	}

	void DbParam::setDouble(double nValue)
	{
		mDbType = DbType_::mDouble_;
		mDbValue.mDouble = nValue;
	}

	void DbParam::setString(string& nValue)
	{
		mDbType = DbType_::mString_;
		mValue = const_cast<char *>(nValue.data());
		mLength = static_cast<__i16>(nValue.length());
	}

	__i8 DbParam::getDbType() const
	{
		return mDbType;
	}
	
	void * DbParam::getDbValue()
	{
		return reinterpret_cast<void *>(&(mDbValue.mInt64));
	}
	
	__i16 DbParam::getLength() const
	{
		return mLength;
	}
	
	char * DbParam::getValue() const
	{
		return mValue;
	}
	
	DbParam::DbParam()
	{
		mDbType = DbType_::mBegin_;
		mDbValue.mInt64 = 0;
		mLength = 0;
		mValue = nullptr;
	}
	
	DbParam::~DbParam()
	{
		mDbType = DbType_::mBegin_;
		mDbValue.mInt64 = 0;
		mLength = 0;
		mValue = nullptr;
	}
	
}
