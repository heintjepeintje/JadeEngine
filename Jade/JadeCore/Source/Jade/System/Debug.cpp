#include "Debug.hpp"

#include <Platform/Native/NativeDebug.hpp>

namespace Jade {

	void DebugBreak() {
		return Native::_DebugBreak();
	}

	Bool8 IsDebugging() {
		return Native::_IsDebugging();
	}

	void PrintDebug(const Char8 *debugString) {
		if (debugString == nullptr) return;

		Native::_PrintDebug(debugString);
	}

	void PrintDebug(const Char16 *debugString) {
		if (debugString == nullptr) return;

		Native::_PrintDebug(debugString);
	}

	void Assert(bool expression, const Char8 *message) {
		if (expression) return;

		PrintDebug(message);
		DebugBreak();
	}

	void Assert(bool expression, const Char16 *message) {
		if (expression) return;

		PrintDebug(message);
		DebugBreak();
	}

}