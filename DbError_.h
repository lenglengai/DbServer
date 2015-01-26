#pragma once

namespace std {
	
	struct DbError_
	{
		static const __i8 mBegin_ = 0;
		static const __i8 mSucess_ = 1;
		static const __i8 mError_ = 2;
		static const __i8 mOverflow_ = 3;
		static const __i8 mNoFindDb_ = 4;
		static const __i8 mAcquireConnetion_ = 5;
		static const __i8 mCommand_ = 6;
		static const __i8 mNoResult_ = 7;
		static const __i8 mNoField_ = 8;
		static const __i8 mStmtRepeat_ = 9;
		static const __i8 mStmtInit_ = 10;
		static const __i8 mStmtPrep_ = 11;
		static const __i8 mNoStatement_ = 12;
		static const __i8 mPushParam_ = 13;
		static const __i8 mPreCommand_ = 14;
		static const __i8 mReconnect_ = 15;
		static const __i8 mBindResult_ = 16;
		static const __i8 mEnd_ = 17;
	};
	
}
