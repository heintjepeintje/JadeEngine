#include "IO.hpp"

#include <Platform/Native/NativeIO.hpp>

namespace Jade {

	constexpr const Char *sForegroundColors[] = {
		"",
		"\033[0m",
		"\033[30m", // Black
		"\033[31m", // Red
		"\033[32m", // Green
		"\033[33m", // Yellow
		"\033[34m", // Blue
		"\033[35m", // Magenta
		"\033[36m", // Cyan
		"\033[37m", // White
		"\033[90m", // Bright Black
		"\033[91m", // Bright Red
		"\033[92m", // Bright Green
		"\033[93m", // Bright Yellow
		"\033[94m", // Bright Blue
		"\033[95m", // Bright Magenta
		"\033[96m", // Bright Cyan
		"\033[97m", // Bright White
	};

	constexpr const Char *sBackgroundColors[] = {
		"",
		"\033[0m",
		"\033[40m", // Black
		"\033[41m", // Red
		"\033[42m", // Green
		"\033[43m", // Yellow
		"\033[44m", // Blue
		"\033[45m", // Magenta
		"\033[46m", // Cyan
		"\033[47m", // White
		"\033[100m", // Bright Black
		"\033[101m", // Bright Red
		"\033[102m", // Bright Green
		"\033[103m", // Bright Yellow
		"\033[104m", // Bright Blue
		"\033[105m", // Bright Magenta
		"\033[106m", // Bright Cyan
		"\033[107m", // Bright White
	};

	String GetConsoleColorAsString(ConsoleColor foreground, ConsoleColor background) {
		return String::Concat(
			sForegroundColors[static_cast<Size>(foreground)],
			sBackgroundColors[static_cast<Size>(background)]
		);
	}

	Size WriteConsole(const String &message) {
		if (message.IsEmpty()) return 0;

		return Native::_WriteConsole(message.GetData(), message.GetLength());
	}

	Size WriteConsole(const WideString &message) {
		if (message.IsEmpty()) return 0;

		return Native::_WriteConsole(message.GetData(), message.GetLength());
	}

}