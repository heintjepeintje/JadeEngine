#pragma once

#include <Jade/Core/Core.hpp>
#include <Jade/Core/String.hpp>
#include <Jade/Core/Template.hpp>

namespace Jade {

	enum class ConsoleColor {
		None = 0,
		Normal,
		Black, Red, Green, Yellow, Blue, Magenta, Cyan, White,
		BrightBlack, BrightRed, BrightGreen, BrightYellow, BrightBlue, BrightMagenta, BrightCyan, BrightWhite
	};

	String GetConsoleColorAsString(ConsoleColor foreground, ConsoleColor background = ConsoleColor::None);

	Size WriteConsole(const String &message);
	Size WriteConsole(const WideString &message);

}