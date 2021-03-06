#include "../Common.h"

namespace std {
	
	bool DbStatement::pushParam(__i16 nIndex, DbParamPtr& nDbParam)
	{
		if ( nIndex >= nParamCount ) return false;
		__i8 dbType_ = nDbParam->getDbType();
		if ( (DbType_::mBegin_ < dbType_) && (DbType_::mString_ > dbType_)  ) {
			mParamBind[nIndex].buffer_type = this->getBufType(dbType_);
			mParamBind[nIndex].buffer = nDbParam->getDbValue();
			mParamBind[nIndex].buffer_length = 0;
			mParamBind[nIndex].is_null_value = 0;
			mParamBind[nIndex].is_unsigned = 0;
			mParamBind[nIndex].length = nullptr;
			return true;
		} else if ( (DbType_::mDouble_ < dbType_) && (DbType_::mEnd_ > dbType_) ) {
			mParamBind[nIndex].buffer_type = this->getBufType(dbType_);
			mParamBind[nIndex].buffer = nDbParam->getValue();
			mLength = nDbParam->getLength();
			mParamBind[nIndex].buffer_length = mLength;
			mParamBind[nIndex].is_null_value = 0;
			mParamBind[nIndex].length = (&mLength);
			mParamBind[nIndex].is_unsigned = 0;
			return true;
		} else {
			return false;
		}
	}
	
	MYSQL_BIND * DbStatement::getParamBind()
	{
		return mParamBind;
	}
	
	MYSQL_STMT * DbStatement::getHandle()
	{
		return mHandle;
	}
	
	enum_field_types DbStatement::getBufType(__i8 nDbType)
	{
		if ( DbType_::mBool_ == nDbType ) {
			return MYSQL_TYPE_TINY;
		}
		if ( DbType_::mInt8_ == nDbType ) {
			return MYSQL_TYPE_TINY;
		}
		if ( DbType_::mInt16_ == nDbType ) {
			return MYSQL_TYPE_SHORT;
		}
		if ( DbType_::mInt32_ == nDbType ) {
			return MYSQL_TYPE_LONG;
		}
		if ( DbType_::mInt64_ == nDbType ) {
			return MYSQL_TYPE_LONGLONG;
		}
		if ( DbType_::mFloat_ == nDbType ) {
			return MYSQL_TYPE_FLOAT;
		}
		if ( DbType_::mDouble_ == nDbType ) {
			return MYSQL_TYPE_DOUBLE;
		}
		if ( DbType_::mString_ == nDbType ) {
			return MYSQL_TYPE_STRING;
		}
		if ( DbType_::mVarString_ == nDbType ) {
			return MYSQL_TYPE_VAR_STRING;
		}
		if ( DbType_::mTinyBlob_ == nDbType ) {
			return MYSQL_TYPE_TINY_BLOB;
		}
		if ( DbType_::mBlob_ == nDbType ) {
			return MYSQL_TYPE_BLOB;
		}
		if ( DbType_::mBigBlob_ == nDbType ) {
			return MYSQL_TYPE_MEDIUM_BLOB;
		}
		if ( DbType_::mMaxBlob_ == nDbType ) {
			return MYSQL_TYPE_LONG_BLOB;
		}
		return MYSQL_TYPE_NULL;
	}
	
	__i16 DbStatement::getBufLength(__i8 nDbType)
	{
		if ( DbType_::mBool_ == nDbType ) {
			return 1;
		}
		if ( DbType_::mInt8_ == nDbType ) {
			return 1;
		}
		if ( DbType_::mInt16_ == nDbType ) {
			return 2;
		}
		if ( DbType_::mInt32_ == nDbType ) {
			return 4;
		}
		if ( DbType_::mInt64_ == nDbType ) {
			return 8;
		}
		if ( DbType_::mFloat_ == nDbType ) {
			return sizeof(float);
		}
		if ( DbType_::mDouble_ == nDbType ) {
			return sizeof(double);
		}
		return 0;
	}
	
	DbStatement::DbStatement(MYSQL_STMT * nHandle)
		: mHandle (nHandle)
	{
		nParamCount = static_cast<__i16>(mysql_stmt_param_count(nHandle));
		mParamBind = new MYSQL_BIND[nParamCount];
		memset(mParamBind, 0, sizeof(MYSQL_BIND) * nParamCount);
		mLength = 0;

		my_bool tempBool_ = 1;
		mysql_stmt_attr_set(nHandle, STMT_ATTR_UPDATE_MAX_LENGTH, &tempBool_);
	}
	
	DbStatement::~DbStatement()
	{
		mysql_stmt_close(mHandle);
		delete[] mParamBind;
	}
	
}
