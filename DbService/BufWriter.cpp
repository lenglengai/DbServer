#include "../Common.h"

namespace std {
	
	__i8 BufWriter::runInt8(char * nValue, __i16 nLength, bool nBin)
	{
		if (nBin) {
			__i8 value_ = __convert<char *, __i8>(nValue, ConvertType_::mBinary_);
			return this->runBlob(&value_, sizeof(__i8));
		} else {
			__i8 value_ = __convert<char *, __i8>(nValue);
			return this->runBlob(&value_, sizeof(__i8));
		}
	}
	
	__i8 BufWriter::runInt16(char * nValue, __i16 nLength, bool nBin)
	{
		if (nBin) {
			__i16 value_ = __convert<char *, __i16>(nValue, ConvertType_::mBinary_);
			return this->runBlob(&value_, sizeof(__i16));
		} else {
			__i16 value_ = __convert<char *, __i16>(nValue);
			return this->runBlob(&value_, sizeof(__i16));
		}
	}
	
	__i8 BufWriter::runInt32(char * nValue, __i16 nLength, bool nBin)
	{
		if (nBin) {
			__i32 value_ = __convert<char *, __i32>(nValue, ConvertType_::mBinary_);
			return this->runBlob(&value_, sizeof(__i32));
		} else {
			__i32 value_ = __convert<char *, __i32>(nValue);
			return this->runBlob(&value_, sizeof(__i32));
		}
	}
	
	__i8 BufWriter::runInt64(char * nValue, __i16 nLength, bool nBin)
	{
		if (nBin) {
			__i64 value_ = __convert<char *, __i64>(nValue, ConvertType_::mBinary_);
			return this->runBlob(&value_, sizeof(__i64));
		} else {
			__i64 value_ = __convert<char *, __i64>(nValue);
			return this->runBlob(&value_, sizeof(__i64));
		}
	}
	
	__i8 BufWriter::runFloat(char * nValue, __i16 nLength, bool nBin)
	{
		if (nBin) {
			float value_ = __convert<char *, float>(nValue, ConvertType_::mBinary_);
			return this->runBlob(&value_, sizeof(float));
		} else {
			float value_ = __convert<char *, float>(nValue);
			return this->runBlob(&value_, sizeof(float));
		}
	}
	
	__i8 BufWriter::runDouble(char * nValue, __i16 nLength, bool nBin)
	{
		if (nBin) {
			double value_ = __convert<char *, double>(nValue, ConvertType_::mBinary_);
			return this->runBlob(&value_, sizeof(double));
		} else {
			double value_ = __convert<char *, double>(nValue);
			return this->runBlob(&value_, sizeof(double));
		}
	}
	
	__i8 BufWriter::runString(char * nValue, __i16 nLength)
	{
		return this->runBlob(nValue, nLength);
	}
	
	__i8 BufWriter::runBlob(void * nValue, __i16 nLength)
	{
		if ((mPos + nLength) > BUFSIZE) {
			return DbError_::mOverflow_;
		}
		memcpy((mBuffer + mPos), nValue, nLength);
		mPos += nLength;
		return DbError_::mSucess_;
	}

	void BufWriter::runClear()
	{
		memset(mBuffer, 0, sizeof(mBuffer));
		mPos = 0;
	}
	
	BufWriter::BufWriter()
	{
		this->runClear();
	}
	
	BufWriter::~BufWriter()
	{
		this->runClear();
	}
	
}
