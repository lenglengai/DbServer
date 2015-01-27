#include "../Common.h"

namespace std {

	bool ReadBlock::runBool(bool& nValue)
	{
		__i8 value_ = 0;
		if (!this->runInt8(value_)) {
			return false;
		}
		nValue = __convert<__i8, bool>(value_);
		return true;
	}

	bool ReadBlock::runInt8(__i8& nValue)
	{
		const char * buffer = this->getBuffer(sizeof(__i8));
		if (nullptr == buffer) {
			return false;
		}
		nValue = *(__i8 *)(buffer);
		return true;
	}

	bool ReadBlock::runInt8s(list<__i8>& nValue)
	{
		__i16 count_ = 0;
		if (!this->runInt16(count_)) {
			return false;
		}
		for (__i16 i = 0; i < count_; ++i) {
			__i8 value_ = 0;
			if (!this->runInt8(value_)) {
				return false;
			}
			nValue.push_back(value_);
		}
		return true;
	}

	bool ReadBlock::runInt16(__i16& nValue)
	{
		const char * buffer = this->getBuffer(sizeof(__i16));
		if (nullptr == buffer) {
			return false;
		}
		nValue = *(__i16 *)(buffer);
		return true;
	}

	bool ReadBlock::runInt16s(list<__i16>& nValue)
	{
		__i16 count_ = 0;
		if (!this->runInt16(count_)) {
			return false;
		}
		for (__i16 i = 0; i < count_; ++i) {
			__i16 value_ = 0;
			if (!this->runInt16(value_)) {
				return false;
			}
			nValue.push_back(value_);
		}
		return true;
	}

	bool ReadBlock::runInt32(__i32& nValue)
	{
		const char * buffer = this->getBuffer(sizeof(__i32));
		if (nullptr == buffer) {
			return false;
		}
		nValue = *(__i32 *)(buffer);
		return true;
	}

	bool ReadBlock::runInt32s(list<__i32>& nValue)
	{
		__i16 count_ = 0;
		if (!this->runInt16(count_)) {
			return false;
		}
		for (__i16 i = 0; i < count_; ++i) {
			__i32 value_ = 0;
			if (!this->runInt32(value_)) {
				return false;
			}
			nValue.push_back(value_);
		}
		return true;
	}

	bool ReadBlock::runInt64(__i64& nValue)
	{
		const char * buffer = this->getBuffer(sizeof(__i64));
		if (nullptr == buffer) {
			return false;
		}
		nValue = *(__i64 *)(buffer);
		return true;
	}

	bool ReadBlock::runInt64s(list<__i64>& nValue)
	{
		__i16 count_ = 0;
		if (!this->runInt16(count_)) {
			return false;
		}
		for (__i16 i = 0; i < count_; ++i) {
			__i64 value_ = 0;
			if (!this->runInt64(value_)) {
				return false;
			}
			nValue.push_back(value_);
		}
		return true;
	}

	bool ReadBlock::runString(string& nValue)
	{
		__i16 count_ = 0;
		if (!this->runInt16(count_)) {
			return false;
		}
		const char * buffer = this->getBuffer(count_);
		if (nullptr == buffer) {
			return false;
		}
		nValue.assign(buffer, count_);
		return true;
	}

	bool ReadBlock::runStrings(list<string>& nValue)
	{
		__i16 count_ = 0;
		if (!this->runInt16(count_)) {
			return false;
		}
		for (__i16 i = 0; i < count_; ++i) {
			string value_ = 0;
			if (!this->runString(value_)) {
				return false;
			}
			nValue.push_back(value_);
		}
		return true;
	}

	bool ReadBlock::runFloat(float& nValue)
	{
		const char * buffer = this->getBuffer(sizeof(float));
		if (nullptr == buffer) {
			return false;
		}
		nValue = *(float *)(buffer);
		return true;
	}

	bool ReadBlock::runFloats(list<float>& nValue)
	{
		__i16 count_ = 0;
		if (!this->runInt16(count_)) {
			return false;
		}
		for (__i16 i = 0; i < count_; ++i) {
			float value_ = 0;
			if (!this->runFloat(value_)) {
				return false;
			}
			nValue.push_back(value_);
		}
		return true;
	}

	bool ReadBlock::runDouble(double& nValue)
	{
		const char * buffer = this->getBuffer(sizeof(double));
		if (nullptr == buffer) {
			return false;
		}
		nValue = *(double *)(buffer);
		return true;
	}

	bool ReadBlock::runDoubles(list<double>& nValue)
	{
		__i16 count_ = 0;
		if (!this->runInt16(count_)) {
			return false;
		}
		for (__i16 i = 0; i < count_; ++i) {
			double value_ = 0;
			if (!this->runDouble(value_)) {
				return false;
			}
			nValue.push_back(value_);
		}
		return true;
	}
	
	bool ReadBlock::isReader() const
	{
		return true;
	}

	BlockPushType_ ReadBlock::runPush(char * nBuffer, const __i16 nSize)
	{
		if (nSize <= 0) {
			return BlockPushType_::mError_;
		}
		mBuffer = nBuffer; mSize = nSize;
		if (0 >= mLength) {
			if (!this->runInt16(mLength)) {
				return BlockPushType_::mError_;
			}
		}
		if ( (mLength <= 0) || (mLength > (PACKETMAX - 2)) ) {
			return BlockPushType_::mError_;
		}
		if (mLength > (mSize + mLeft - 2)) {
			memcpy((mValue + mLeft), mBuffer, mSize);
			mLeft += mSize; mBuffer = nullptr; mSize = 0;
			return BlockPushType_::mLength_;
		}
		return BlockPushType_::mFinish_;
	}

	void ReadBlock::endPush()
	{
		if (mPos >= (mLeft + mSize)) {
			this->runClear();
			return;
		}
		if (mPos >= mLeft) {
			memset(mValue, 0, sizeof(mValue));
			memcpy(mValue, (mBuffer + mPos - mLeft), (mSize + mLeft - mPos));
			mBuffer = nullptr; mLeft = mSize + mLeft - mPos;
			mSize = 0; mPos = 0; mLength = 0;
			return;
		}
		memcpy(mValue, (mValue + mPos), (mLeft - mPos));
		memcpy((mValue + mLeft - mPos), mBuffer, mSize);
		mBuffer = nullptr; mLeft -= mPos; mLeft += mSize;
		mPos = 0; mSize = 0; mLength = 0; 
	}

	const char * ReadBlock::getBuffer(const __i16 nSize)
	{
		if ( (mPos + nSize) > (mLeft + mSize) ) {
			return nullptr;
		}
		char * result_ = nullptr;
		if (mLeft <= mPos) {
			result_ = (mBuffer + mPos - mLeft);
			mPos += nSize;
			return result_;
		}
		if ((mPos + nSize) > mLeft) {
			memcpy((mValue + mPos), mBuffer, (nSize - mLeft + mPos));
		}
		result_ = (mValue + mPos);
		mPos += nSize;
		return result_;
	}

	void ReadBlock::runClear()
	{
		memset(mValue, 0, sizeof(mValue));
		mBuffer = nullptr; mLength = 0;
		mSize = 0; mLeft = 0; mPos = 0;
	}

	ReadBlock::ReadBlock()
	{
		this->runClear();
	}

	ReadBlock::~ReadBlock()
	{
		this->runClear();
	}
	
}
