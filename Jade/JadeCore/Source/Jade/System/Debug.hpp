#pragma once

#include <Jade/Core/Core.hpp>

namespace Jade {

	void DebugBreak();
	Bool8 IsDebugging();
	void PrintDebug(const Char8 *debugString);
	void PrintDebug(const Char16 *debugString);

	void Assert(bool expression, const Char8 *message);
	void Assert(bool expression, const Char16 *message);

}