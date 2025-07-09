#pragma once

#include "Core.hpp"

namespace Jade {

	template<typename _T> _T MaxValue();

	template<> constexpr UInt8 MaxValue() { return __UINT8_MAX__; }
	template<> constexpr UInt16 MaxValue() { return __UINT16_MAX__; }
	template<> constexpr UInt32 MaxValue() { return __UINT32_MAX__; }
	template<> constexpr UInt64 MaxValue() { return __UINT64_MAX__; }

	template<> constexpr Int8 MaxValue() { return __INT8_MAX__; }
	template<> constexpr Int16 MaxValue() { return __INT16_MAX__; }
	template<> constexpr Int32 MaxValue() { return __INT32_MAX__; }
	template<> constexpr Int64 MaxValue() { return __INT64_MAX__; }

	template<> constexpr Float32 MaxValue() { return __FLT_MAX__; }
	template<> constexpr Float64 MaxValue() { return __DBL_MAX__; }

}