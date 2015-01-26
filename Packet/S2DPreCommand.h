#pragma once

namespace std {
	
	class S2DPreCommand
	{
	public:
		void pushDbParam(DbParamPtr& nDbParam);
		list<DbParamPtr>& getDbParams();
		__i16 getCommand() const;
		
		S2DPreCommand(__i32 nCommandNo, __i16 nCommand);
		~S2DPreCommand();
		
	private:
		list<DbParamPtr> mDbParams;
		__i16 mCommand;
		__i32 mCommandNo;
	};
	typedef shared_ptr<S2DPreCommand> S2DPreCommandPtr;
	
}
