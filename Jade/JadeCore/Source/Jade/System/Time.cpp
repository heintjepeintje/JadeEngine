#include "Time.hpp"

#include <Platform/Native/NativeTime.hpp>

namespace Jade {

	UInt64 GetCurrentTime() {
		return Native::_GetCurrentTime();
	}

}