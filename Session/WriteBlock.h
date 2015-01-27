#pragma once

namespace std {

	class WriteBlock : public IBlock
	{
	public:
		bool runBool(bool& nValue) OVERRIDE FINAL;

		bool runInt8(__i8& nValue) OVERRIDE FINAL;
		bool runInt8s(list<__i8>& nValue) OVERRIDE FINAL;

		bool runInt16(__i16& nValue) OVERRIDE FINAL;
		bool runInt16s(list<__i16>& nValue) OVERRIDE FINAL;

		bool runInt32(__i32& nValue) OVERRIDE FINAL;
		bool runInt32s(list<__i32>& nValue) OVERRIDE FINAL;

		bool runInt64(__i64& nValue) OVERRIDE FINAL;
		bool runInt64s(list<__i64>& nValue) OVERRIDE FINAL;

		bool runString(string& nValue) OVERRIDE FINAL;
		bool runStrings(list<string>& nValue) OVERRIDE FINAL;

		bool runFloat(float& nValue) OVERRIDE FINAL;
		bool runFloats(list<float>& nValue) OVERRIDE FINAL;

		bool runDouble(double& nValue) OVERRIDE FINAL;
		bool runDoubles(list<double>& nValue) OVERRIDE FINAL;
		
		bool isReader() const OVERRIDE FINAL;

		void runClear();
		void runEnd();

		const char * getBuffer() const;
		__i16 getLength() const;
		__i16 getTotal() const;

		WriteBlock();
		~WriteBlock();
	
	private:
		template<typename T>
		bool runCopy(const T& nT)
		{
			if ((mLength + sizeof(__i16)+sizeof(T)) > PACKETMAX) {
				return false;
			}
			memcpy((mBuffer + mLength + sizeof(__i16)), &nT, sizeof(T));
			mLength += sizeof(T);
			return true;
		}

		bool runCopy(const char * nValue, const __i16 nLength);

	private:
		char mBuffer[PACKETMAX];
		__i16 mLength;
	};
	typedef shared_ptr<WriteBlock> WriteBlockPtr;

}
