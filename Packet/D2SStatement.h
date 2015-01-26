#pragma once

namespace std {
	
	class D2SStatement
	{
	public:
		void setErrorCode(__i8 nErrorCode);
		
		D2SStatement();
		~D2SStatement();
		
	private:
		__i8 mErrorCode;
		__i32 mCommandNo;
	};
	typedef shared_ptr<D2SStatement> D2SStatementPtr;
	
}
