#pragma once

#include <Jade/Core/Core.hpp>

namespace Jade {

	namespace Native {

		void _DebugBreak();
		Bool8 _IsDebugging();
		void _PrintDebug(const Char *debugString);
		void _PrintDebug(const WideChar *debugString);

	}

}