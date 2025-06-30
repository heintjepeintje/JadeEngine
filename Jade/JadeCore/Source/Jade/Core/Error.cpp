#include "Error.hpp"

namespace Jade {

	ErrorCallback sErrorCallback = nullptr;
	Error sLastError = {};

	void SetErrorCallback(ErrorCallback callback) {
		sErrorCallback = callback;
	}

	ErrorCallback GetErrorCallback() {
		return sErrorCallback;
	}

	void SetError(const Error &error) {
		sLastError = error;

		if (sErrorCallback == nullptr) return;
		sErrorCallback(error);
	}

	const Error &GetLastError() {
		return sLastError;
	}

}