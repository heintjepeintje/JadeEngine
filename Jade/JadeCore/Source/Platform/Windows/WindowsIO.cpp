#include <Jade/Core/Platform.hpp>

#if defined(JD_PLATFORM_WINDOWS)
#include "WindowsCore.hpp"

#include <Platform/Native/NativeIO.hpp>

namespace Jade {

	Size Native::_WriteConsole(const Char *message, Size length) {
		DWORD charsWritten = 0;
		
		WINBOOL success = WriteConsoleA(
			GetStdHandle(STD_OUTPUT_HANDLE), 
			reinterpret_cast<LPCVOID>(message), 
			static_cast<DWORD>(length), 
			&charsWritten, 
			nullptr
		);

		return success ? charsWritten : 0;
	}

	Size Native::_WriteConsole(const WideChar *message, Size length) {
		DWORD charsWritten = 0;

		WINBOOL success = WriteConsoleW(
			GetStdHandle(STD_OUTPUT_HANDLE), 
			reinterpret_cast<LPCVOID>(message), 
			static_cast<DWORD>(length), 
			&charsWritten, 
			nullptr
		);	

		return success ? charsWritten : 0;
	}

}

#endif