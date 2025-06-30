#include "Debug.hpp"

#include <Platform/Native/NativeDebug.hpp>

namespace Jade {

	void DebugBreak() {
		return Native::_DebugBreak();
	}

	Bool8 IsDebugging() {
		return Native::_IsDebugging();
	}

	void PrintDebug(const Char *debugString) {
		if (debugString == nullptr) return;

		Native::_PrintDebug(debugString);
	}

	void PrintDebug(const WideChar *debugString) {
		if (debugString == nullptr) return;

		Native::_PrintDebug(debugString);
	}

	void Assert(bool expression, const Char *message) {
		if (expression) return;

		PrintDebug(message);
		DebugBreak();
	}

	void Assert(bool expression, const WideChar *message) {
		if (expression) return;

		PrintDebug(message);
		DebugBreak();
	}

}