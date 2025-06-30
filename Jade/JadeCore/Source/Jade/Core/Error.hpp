#pragma once

#include <Jade/Core/Core.hpp>

namespace Jade {

	enum class ErrorLevel {
		None = 0,
		Warning, Error, Fatal
	};

	struct Error {
		ErrorLevel Level = ErrorLevel::None;
		Char16 Message[256] = {0};
	};

	typedef void (*ErrorCallback)(const Error &error);

	void SetErrorCallback(ErrorCallback callback);
	ErrorCallback GetErrorCallback();

	void SetError(const Error &error);
	const Error &GetLastError();

}