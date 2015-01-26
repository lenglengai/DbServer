#include "../Common.h"

namespace std {
	
	__i8 DbPreResult::runQuery(D2SPreQuery * nD2SPreQuery)
	{
		__i32 i = 0;
		MYSQL_FIELD * fieldInfo_ = mysql_fetch_field(mHandle);
		while (nullptr != fieldInfo_) {
			mBind[i].buffer_type = fieldInfo_->type;
			size_t size = this->fieldSize(fieldInfo_);
			mBind[i].buffer = malloc(size);
			memset(mBind[i].buffer, 0, size);
			mBind[i].buffer_length = size;
			mBind[i].length = &mLength[i];
			mBind[i].is_null = &mIsNull[i];
			mBind[i].error = nullptr;
			mBind[i].is_unsigned = 0;
			++i;
			fieldInfo_ = mysql_fetch_field(mHandle);
		}
		if (mysql_stmt_bind_result(mStmt, mBind)) {
			return DbError_::mBindResult_;
		}
		int errorCode_ = mysql_stmt_fetch(mStmt);
		while (0 == errorCode_) {
			for (__i16 i = 0; i < mFieldCount; i++) {
				errorCode_ = nD2SPreQuery->pushValue(mBind[i].buffer_type, (char *)(mBind[i].buffer), (__i16)(*(mBind[i].length)));
				if (DbError_::mSucess_ != errorCode_) {
					return errorCode_;
				}
			}
			errorCode_ = mysql_stmt_fetch(mStmt);
		}
		return DbError_::mSucess_;
	}
	
	size_t DbPreResult::fieldSize(MYSQL_FIELD * nField)
	{
		switch (nField->type) 
		{
			case MYSQL_TYPE_TINY:
                return 1;
            case MYSQL_TYPE_SHORT:
                return 2;
            case MYSQL_TYPE_LONG:
            case MYSQL_TYPE_FLOAT:
                return 4;
            case MYSQL_TYPE_DOUBLE:
            case MYSQL_TYPE_LONGLONG:
                return 8;
            case MYSQL_TYPE_TINY_BLOB:
            case MYSQL_TYPE_MEDIUM_BLOB:
            case MYSQL_TYPE_LONG_BLOB:
            case MYSQL_TYPE_BLOB:
            case MYSQL_TYPE_STRING:
            case MYSQL_TYPE_VAR_STRING:
				return nField->max_length + 1;
            default:
                return 0;
        }
    }
	
	DbPreResult::DbPreResult(MYSQL_STMT * nStmt, MYSQL_RES * nHandle, 
			__i16 nRowCount, __i16 nFieldCount)
		: mHandle (nHandle)
		, mStmt (nStmt)
		, mRowCount (nRowCount)
		, mFieldCount (nFieldCount)
	{
		mBind = new MYSQL_BIND[nFieldCount];
		mIsNull = new my_bool[nFieldCount];
		mLength = new unsigned long[nFieldCount];
		memset(mIsNull, 0, sizeof(my_bool) * nFieldCount);
		memset(mBind, 0, sizeof(MYSQL_BIND) * nFieldCount);
		memset(mLength, 0, sizeof(unsigned long) * nFieldCount);
	}
	
	DbPreResult::~DbPreResult()
	{
		if (nullptr != mHandle) {
			mysql_free_result(mHandle);
		}
		if (nullptr != mStmt) {
			mysql_stmt_free_result(mStmt);
		}

		for (__i32 i = 0; i < mFieldCount; ++i) {
			free(mBind[i].buffer);
		}
		
		delete [] mBind;
        delete [] mIsNull;
        delete [] mLength;
	}
	
}
