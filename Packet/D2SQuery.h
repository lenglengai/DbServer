#pragma once

namespace std {
	
	class D2SQuery
	{
	public:
		__i8 pushValue(enum_field_types nType, char * nValue, __i16 nLength);
		
		void setErrorCode(__i8 nErrorCode);
		void setRowCount(__i16 nRowCount);
		void runClear();
		
		D2SQuery(__i32 nCommandNo);
		~D2SQuery();
		
	private:
		BufWriter mBufWriter;
		__i32 mCommandNo;
		__i8 mErrorCode;
		__i16 mRowCount;
	};
	typedef shared_ptr<D2SQuery> D2SQueryPtr;
	
}
