#pragma once

#include <Jade/Core/Core.hpp>
#include "String.hpp"

namespace Jade {

	enum class ErrorLevel {
		None = 0,
		Warning, Error, Fatal
	};

	struct Error {
		ErrorLevel Level = ErrorLevel::None;
		String Message;
	};

	typedef void (*ErrorCallback)(const Error &error);

	void SetErrorCallback(ErrorCallback callback);
	ErrorCallback GetErrorCallback();

	void SetError(ErrorLevel level, const String &message);
	void SetError(const Error &error);
	const Error &GetLastError();

}