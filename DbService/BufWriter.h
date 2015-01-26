#pragma once

#define BUFSIZE 8192
namespace std {
	
	class BufWriter : noncopyable
	{
	public:
		__i8 runInt8(char * nValue, __i16 nLength, bool nBin = false);
		__i8 runInt16(char * nValue, __i16 nLength, bool nBin = false);
		__i8 runInt32(char * nValue, __i16 nLength, bool nBin = false);
		__i8 runInt64(char * nValue, __i16 nLength, bool nBin = false);
		__i8 runFloat(char * nValue, __i16 nLength, bool nBin = false);
		__i8 runDouble(char * nValue, __i16 nLength, bool nBin = false);
		__i8 runString(char * nValue, __i16 nLength);
		__i8 runBlob(void * nValue, __i16 nLength);
		
		void runClear();
		
		BufWriter();
		~BufWriter();
		
	private:
		char mBuffer[BUFSIZE];
		__i16 mPos;
	};
	
}
