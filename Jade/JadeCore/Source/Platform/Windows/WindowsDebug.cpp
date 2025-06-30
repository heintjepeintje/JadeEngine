#include <Jade/Core/Platform.hpp>

#if defined(JD_PLATFORM_WINDOWS)
#include "WindowsCore.hpp"

#include <Platform/Native/NativeDebug.hpp>

namespace Jade {

	void Native::_DebugBreak() {
		DebugBreak();
	}

	Bool8 Native::_IsDebugging() {
		const WINBOOL isDebuggerPresent = IsDebuggerPresent();
		return static_cast<Bool8>(isDebuggerPresent);
	}

	void Native::_PrintDebug(const Char8 *debugString) {
		OutputDebugStringA(reinterpret_cast<LPCSTR>(debugString));
	}

	void Native::_PrintDebug(const Char16 *debugString) {
		OutputDebugStringW(reinterpret_cast<LPCWSTR>(debugString));
	}

}

#endif