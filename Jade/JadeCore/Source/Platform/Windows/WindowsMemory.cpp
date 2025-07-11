#include <Jade/Core/Platform.hpp>

#if defined(JD_PLATFORM_WINDOWS)

#include "WindowsCore.hpp"

#include <Platform/Native/NativeMemory.hpp>

namespace Jade {

	void *Native::_Allocate(Size size) {
		HANDLE processHeap = GetProcessHeap();
		if (processHeap == nullptr) return nullptr;

		LPVOID allocatedMemory = HeapAlloc(
			processHeap,
			HEAP_ZERO_MEMORY,
			static_cast<SIZE_Type>(size)
		);

		return allocatedMemory;
	}

	void *Native::_ReAllocate(void *ptr, Size size) {
		HANDLE processHeap = GetProcessHeap();
		if (processHeap == nullptr) return nullptr;

		LPVOID reallocatedMemory = HeapReAlloc(
			processHeap,
			HEAP_ZERO_MEMORY,
			ptr,
			static_cast<SIZE_Type>(size)
		);

		return reallocatedMemory;
	}

	void Native::_Free(void *ptr) {
		if (ptr == nullptr) return;

		HANDLE processHeap = GetProcessHeap();
		if (processHeap == nullptr) return;

		HeapFree(processHeap, 0, ptr);
		// TODO: error handling
	}

	void Native::_CopyMemory(void *destination, const void *source, Size size) {
		RtlCopyMemory(destination, source, static_cast<SIZE_Type>(size));
	}

	void Native::_FillMemory(void *pointer, Byte value, Size size) {
		RtlFillMemory(pointer, static_cast<SIZE_Type>(size), value);
	}

	void Native::_MoveMemory(void *destination, const void *source, Size size) {
		RtlMoveMemory(destination, source, static_cast<SIZE_Type>(size));
	}

	void Native::_ZeroMemory(void *pointer, Size size) {
		RtlZeroMemory(pointer, static_cast<SIZE_Type>(size));
	}

	Size Native::_CompareMemory(const void *left, const void *right, Size size) {
		return RtlCompareMemory(left, right, static_cast<SIZE_Type>(size));
	}

	UInt16 Native::_EndianSwap(UInt16 value) {
		return __builtin_bswap16(value); 
	}

	UInt32 Native::_EndianSwap(UInt32 value) {
		return __builtin_bswap32(value);
	}

	UInt64 Native::_EndianSwap(UInt64 value) {
		return __builtin_bswap64(value);
	}

}

#endif