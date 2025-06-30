#pragma once

#include <Jade/Core/Core.hpp>

namespace Jade {

	void DebugBreak();
	Bool8 IsDebugging();
	void PrintDebug(const Char *debugString);
	void PrintDebug(const WideChar *debugString);

	void Assert(bool expression, const Char *message);
	void Assert(bool expression, const WideChar *message);

}