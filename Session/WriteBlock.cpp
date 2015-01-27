#include "../Common.h"

namespace std {

	bool WriteBlock::runBool(bool& nValue)
	{
		__i8 value_ = __convert<__i8, bool>(nValue);
		return this->runInt8(value_);
	}

	bool WriteBlock::runInt8(__i8& nValue)
	{
		return this->runCopy(nValue);
	}

	bool WriteBlock::runInt8s(list<__i8>& nValue)
	{
		__i16 count_ = nValue.size();
		if (!this->runInt16(count_)) {
			return false;
		}
		list<__i8>::iterator it = nValue.begin();
		for (; it != nValue.end(); ++it) {
			if (!this->runInt8(*it)) {
				return false;
			}
		}
		return true;
	}

	bool WriteBlock::runInt16(__i16& nValue)
	{
		return this->runCopy(nValue);
	}

	bool WriteBlock::runInt16s(list<__i16>& nValue)
	{
		__i16 count_ = nValue.size();
		if (!this->runInt16(count_)) {
			return false;
		}
		list<__i16>::iterator it = nValue.begin();
		for (; it != nValue.end(); ++it) {
			if (!this->runInt16(*it)) {
				return false;
			}
		}
		return true;
	}

	bool WriteBlock::runInt32(__i32& nValue)
	{
		return this->runCopy(nValue);
	}

	bool WriteBlock::runInt32s(list<__i32>& nValue)
	{
		__i16 count_ = nValue.size();
		if (!this->runInt16(count_)) {
			return false;
		}
		list<__i32>::iterator it = nValue.begin();
		for (; it != nValue.end(); ++it) {
			if (this->runInt32(*it)) {
				return false;
			}
		}
		return true;
	}

	bool WriteBlock::runInt64(__i64& nValue)
	{
		return this->runCopy(nValue);
	}

	bool WriteBlock::runInt64s(list<__i64>& nValue)
	{
		__i16 count_ = nValue.size();
		if (!this->runInt16(count_)) {
			return false;
		}
		list<__i64>::iterator it = nValue.begin();
		for (; it != nValue.end(); ++it) {
			if (!this->runInt64(*it)) {
				return false;
			}
		}
		return true;
	}

	bool WriteBlock::runString(string& nValue)
	{
		__i16 count_ = nValue.length();
		if (!this->runInt16(count_)) {
			return false;
		}
		return this->runCopy(nValue.c_str(), count_);
	}

	bool WriteBlock::runStrings(list<string>& nValue)
	{
		__i16 count_ = nValue.size();
		if (!this->runInt16(count_)) {
			return false;
		}
		list<string>::iterator it = nValue.begin();
		for (; it != nValue.end(); ++it) {
			if (!this->runString(*it)) {
				return false;
			}
		}
		return true;
	}

	bool WriteBlock::runFloat(float& nValue)
	{
		return this->runCopy(nValue);
	}

	bool WriteBlock::runFloats(list<float>& nValue)
	{
		__i16 count_ = nValue.size();
		if (!this->runInt16(count_)) {
			return false;
		}
		list<float>::iterator it = nValue.begin();
		for (; it != nValue.end(); ++it) {
			if (!this->runFloat(*it)) {
				return false;
			}
		}
		return true;
	}

	bool WriteBlock::runDouble(double& nValue)
	{
		return this->runCopy(nValue);
	}

	bool WriteBlock::runDoubles(list<double>& nValue)
	{
		__i16 count_ = nValue.size();
		if (!this->runInt16(count_)) {
			return false;
		}
		list<double>::iterator it = nValue.begin();
		for (; it != nValue.end(); ++it) {
			if (!this->runDouble(*it)) {
				return false;
			}
		}
		return true;
	}

	bool WriteBlock::isReader() const
	{
		return false;
	}
	
	bool WriteBlock::runCopy(const char * nValue, const __i16 nLength)
	{
		if ((mLength + nLength + sizeof(__i16)) > PACKETMAX) {
			return false;
		}
		memcpy((mBuffer + mLength + sizeof(__i16)), nValue, nLength);
		mLength += nLength;
		return true;
	}

	void WriteBlock::runClear()
	{
		memset(mBuffer, 0, sizeof(mBuffer));
		mLength = 0;
	}

	void WriteBlock::runEnd()
	{
		memcpy(mBuffer, &mLength, sizeof(__i16));
	}

	const char * WriteBlock::getBuffer() const
	{
		return mBuffer;
	}

	__i16 WriteBlock::getLength() const
	{
		return mLength;
	}

	__i16 WriteBlock::getTotal() const
	{
		return (mLength + 2);
	}

	WriteBlock::WriteBlock()
	{
		this->runClear();
	}

	WriteBlock::~WriteBlock()
	{
		this->runClear();
	}

}
