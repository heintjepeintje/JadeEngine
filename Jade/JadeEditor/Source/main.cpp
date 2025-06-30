#include <Jade/Core/Core.hpp>

#include <Jade/System/Debug.hpp>
#include <Jade/System/Memory.hpp>
#include <jade/Core/Error.hpp>

#include <Jade/Core/String.hpp>

#include <cstdio>

int main(int argc, char **argv) {
	Jade::WideString wideString(255);
	Jade::String string(255);

	for (Jade::Size i = 0; i < 255; i++) {
		wideString[i] = static_cast<Jade::WideChar>(i + 1);
		string[i] = static_cast<Jade::Char>(i + 1);
	}

	Jade::PrintDebug(wideString.GetData());
	Jade::PrintDebug(string.GetData());

	return 0;
}