#pragma once

namespace std{

	enum class BlockPushType_ : __i8
	{
		mError_ = 0,
		mLength_ = 1,
		mFinish_ = 2
	};
	class ReadBlock : public IBlock
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

		BlockPushType_ runPush(char * nBuffer, const __i16 nSize);
		void endPush();
		void runClear();

		ReadBlock();
		~ReadBlock();

	private:
		const char * getBuffer(const __i16 nSize);
		
	private:
		char mValue[PACKETMAX];
		__i16 mLeft;
		char * mBuffer;
		__i16 mSize;
		__i16 mLength;
		__i16 mPos;
	};
	typedef shared_ptr<ReadBlock> ReadBlockPtr;

}
