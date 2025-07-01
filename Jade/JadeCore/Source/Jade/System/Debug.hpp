#pragma once

#include <Jade/Core/Core.hpp>
#include <Jade/Core/String.hpp>

namespace Jade {

	void DebugBreak();
	Bool8 IsDebugging();
	void PrintDebug(const String &debugString);
	void PrintDebug(const WideString &debugString);

	void Assert(bool expression, const String &message);
	void Assert(bool expression, const WideString &message);

}