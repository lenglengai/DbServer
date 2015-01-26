#pragma once

namespace std {

	class TimeService : noncopyable
	{
	public:
		__i32 getBeforeDay(__i32 nDays) const;
		__i32 getLocalTime() const;
		__i32 getStartTime() const;
		
		static TimeService * getTimeService();
		
	private:
		const time_t fromTime(const __i32 nYear, const __i32 nMonth, const __i32 nDay) const;
		const time_t fromTime(const __i32 nYear, const __i32 nMonth, const __i32 nDay, const __i32 nHour) const;
		const time_t fromTime(const __i32 nYear, const __i32 nMonth, const __i32 nDay, const __i32 nHour, const __i32 nMin) const;
		const time_t fromTime(const __i32 nYear, const __i32 nMonth, const __i32 nDay, const __i32 nHour, const __i32 nMin, const __i32 nSec) const;
	
	public:
		bool runPreinit();
		void startEnd();
		
		TimeService();
		~TimeService();
		
	private:
		chrono::system_clock::time_point mBegin;
		__i32 mStartTime;
	};

}
