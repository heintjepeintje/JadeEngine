#include "String.hpp"

#include <cstdio>

namespace Jade {

	Char ToChar(WideChar wide) {
		if (wide >= L'\0' && wide <= L'~') return static_cast<Char>(wide);
		return '\0';
	}

	WideChar ToWideChar(Char character) {
		if (character >= '\0' && character <= '~') return static_cast<Char>(character);
		return L'\0';
	}

	String ToString(const WideString &wide) {
		if (wide.GetData() == nullptr || wide.GetLength() == 0) return String();

		String result;
		result.Resize(wide.GetLength());
		
		for (Size i = 0; i < wide.GetLength(); i++) {
			result[i] = ToChar(wide[i]);
		}
		
		return result;
	}

	WideString ToWideString(const String &string) {
		if (string.GetData() == nullptr || string.GetLength() == 0) return WideString();

		WideString result;
		result.Resize(string.GetLength());

		for (Size i = 0; i < string.GetLength(); i++) {
			result[i] = ToWideChar(string[i]);
		}

		return result;
	}

}