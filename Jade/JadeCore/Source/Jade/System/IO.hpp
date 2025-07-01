#pragma once

#include <Jade/Core/Core.hpp>
#include <Jade/Core/String.hpp>
#include <Jade/Core/Template.hpp>

namespace Jade {

	Size WriteConsole(const String &message);
	Size WriteConsole(const WideString &message);

	template<typename ..._Args>
	inline void Print(const String &message, _Args &&...args) { WriteConsole(Format(message, Jade::Forward<_Args>(args)...)); }

}