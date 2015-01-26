#pragma once

namespace std {
	
	class D2SPreQuery
	{
	public:
		__i8 pushValue(enum_field_types nType, char * nValue, __i16 nLength);

		void setErrorCode(__i8 nErrorCode);
		void setRowCount(__i16 nRowCount);
		void runClear();

		D2SPreQuery(__i32 nCommandNo);
		~D2SPreQuery();
		
	private:
		BufWriter mBufWriter;
		__i32 mCommandNo;
		__i8 mErrorCode;
		__i16 mRowCount;
	};
	typedef shared_ptr<D2SPreQuery> D2SPreQueryPtr;
	
}
