#pragma once

#include <Jade/Core/Core.hpp>

namespace Jade {

	UInt64 GetCurrentTime();

	class Time {
	public:
		static Time Now() { return Time(GetCurrentTime()); }

		inline static Time FromMilliseconds(UInt64 milliseconds) { return Time(milliseconds); }
		inline static Time FromSeconds(UInt64 seconds) { return Time(seconds * 1000); }
		inline static Time FromMinutes(UInt64 minutes) { return Time(minutes * 60000); }
		inline static Time FromHours(UInt64 hours) { return Time(hours * 3600000); }

	public:
		Time() = default;
		Time(UInt64 milliseconds) : mMilliseconds(milliseconds) { }
		~Time() = default;

		inline UInt64 GetMilliseconds() const { return mMilliseconds; }
		inline Float64 GetSeconds() const { return static_cast<Float64>(mMilliseconds) / 1000.0; }
		inline Float64 GetMinutes() const { return static_cast<Float64>(mMilliseconds) / 60000.0; }
		inline Float64 GetHours() const { return static_cast<Float64>(mMilliseconds) / 3600000.0; }

		inline Time operator+(const Time &other) const { return FromMilliseconds(mMilliseconds + other.mMilliseconds); }
		inline Time &operator+=(const Time &other) { mMilliseconds += other.mMilliseconds; return *this; }

		inline Time operator-(const Time &other) const {
			if (mMilliseconds < other.mMilliseconds) return FromMilliseconds(0);
			return FromMilliseconds(mMilliseconds - other.mMilliseconds);
		}

		inline Time &operator-=(const Time &other) {
			if (mMilliseconds < other.mMilliseconds) mMilliseconds = 0;
			else mMilliseconds -= other.mMilliseconds;
			return *this;
		}

		inline operator UInt64() const { return mMilliseconds; }
	
	private:
		UInt64 mMilliseconds = 0;
	};

}