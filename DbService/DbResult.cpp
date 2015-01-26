#include "../Common.h"

namespace std {
	
	__i8 DbResult::runQuery(D2SQuery * nD2SQuery)
	{
		unsigned long * length_ = nullptr;
		__i8 errorCode_ = DbError_::mSucess_;
		MYSQL_FIELD * filedInfo_ = nullptr;
		__i16 size_ = 0;
		__i16 fieldCount_ = mysql_num_fields(mHandle);
		MYSQL_ROW rowRes_ = mysql_fetch_row(mHandle);
		while (nullptr != rowRes_) {
			length_ = mysql_fetch_lengths(mHandle);
			if (nullptr == length_) break;
			for (__i16 i = 0; i < fieldCount_; i++) {
				filedInfo_ = mysql_fetch_field(mHandle);
				size_ = static_cast<__i16>(length_[i]);
				errorCode_ = nD2SQuery->pushValue(filedInfo_->type, rowRes_[i], size_);
				if (DbError_::mSucess_ != errorCode_) {
					return errorCode_;
				}
			}
			mysql_field_seek(mHandle, 0);
			rowRes_ = mysql_fetch_row(mHandle);
		}
		return DbError_::mSucess_;
	}
	
	DbResult::DbResult(MYSQL_RES * nHandle, __i16 nRowCount)
		: mHandle (nHandle)
		, mRowCount (nRowCount)
	{
	}
	
	DbResult::~DbResult()
	{
		if (nullptr != mHandle) {
			mysql_free_result(mHandle);
		}
	}
	
}
