#pragma once

namespace std {
	
	class S2DStatement
	{
	public:
		void pushStatement(__i16 nCommandId, const char * nCommand);
		const map<__i16, string>& getStatements() const;
		__i32 getCommandNo() const;
		
		S2DStatement();
		~S2DStatement();
		
	private:
		map<__i16, string> mStatements;
		__i32 mCommandNo;
	};
	typedef shared_ptr<S2DStatement> S2DStatementPtr;
	
}
