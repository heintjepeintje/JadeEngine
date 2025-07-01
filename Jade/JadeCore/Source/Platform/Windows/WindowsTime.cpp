#include <Jade/Core/Platform.hpp>

#if defined(JD_PLATFORM_WINDOWS)

#include "WindowsCore.hpp"
#include <Platform/Native/NativeTime.hpp>

namespace Jade {

	LARGE_INTEGER sFrequency = {0};

	UInt64 Native::_GetCurrentTime() {
		if (sFrequency.QuadPart == 0) QueryPerformanceFrequency(&sFrequency);

		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);

		return static_cast<UInt64>((static_cast<Float64>(currentTime.QuadPart) * 1000.0) / static_cast<Float64>(sFrequency.QuadPart));
	}

}

#endif