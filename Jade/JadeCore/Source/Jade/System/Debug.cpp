#include "Debug.hpp"

#include <Platform/Native/NativeDebug.hpp>

namespace Jade {

	void DebugBreak() {
		return Native::_DebugBreak();
	}

	Bool8 IsDebugging() {
		return Native::_IsDebugging();
	}

	void PrintDebug(const String &debugString) {
		if (debugString.IsEmpty()) return;

		Native::_PrintDebug(debugString.GetData());
	}

	void PrintDebug(const WideString &debugString) {
		if (debugString.IsEmpty()) return;

		Native::_PrintDebug(debugString.GetData());
	}

	void Assert(bool expression, const String &message) {
		if (expression) return;

		PrintDebug(message);
		DebugBreak();
	}

	void Assert(bool expression, const WideString &message) {
		if (expression) return;

		PrintDebug(message);
		DebugBreak();
	}

}