#include "IO.hpp"

#include <Platform/Native/NativeIO.hpp>

namespace Jade {

	Size WriteConsole(const String &message) {
		if (message.IsEmpty()) return 0;

		return Native::_WriteConsole(message.GetData(), message.GetLength());
	}

	Size WriteConsole(const WideString &message) {
		if (message.IsEmpty()) return 0;

		return Native::_WriteConsole(message.GetData(), message.GetLength());
	}

}