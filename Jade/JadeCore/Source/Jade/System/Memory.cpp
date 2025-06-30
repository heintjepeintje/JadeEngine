#include "Memory.hpp"

#include <Platform/Native/NativeMemory.hpp>

namespace Jade {

	void *Allocate(Size size) {
		if (size == 0) return nullptr;

		return Native::_Allocate(size);
	}

	void *ReAllocate(void *pointer, Size size) {
		if (pointer == nullptr || size == 0) return nullptr;

		return Native::_ReAllocate(pointer, size);
	}
	
	void Free(void *pointer) {
		if (pointer == nullptr) return;

		Native::_Free(pointer);
	}

	void CopyMemory(void *destination, const void *source, Size size) {
		if (destination == nullptr || source == nullptr || size == 0) return;

		Native::_CopyMemory(destination, source, size);
	}

	void FillMemory(void *pointer, Byte value, Size size) {
		if (pointer == nullptr || size == 0) return;

		Native::_FillMemory(pointer, value, size);
	}

	void MoveMemory(void *destination, const void *source, Size size) {
		if (destination == nullptr || source == nullptr || size == 0) return;

		Native::_MoveMemory(destination, source, size);
	}

	void ZeroMemory(void *pointer, Size size) {
		if (pointer == nullptr || size == 0) return;

		Native::_ZeroMemory(pointer, size);
	}

	Size CompareMemory(const void *left, const void *right, Size size) {
		if (left == nullptr || right == nullptr || size == 0) return __SIZE_MAX__;

		return Native::_CompareMemory(left, right, size);
	}

	UInt16 EndianSwap(UInt16 value) {
		if (value == 0) return 0;

		return Native::_EndianSwap(value);
	}

	UInt32 EndianSwap(UInt32 value) {
		if (value == 0) return 0;
		
		return Native::_EndianSwap(value);
	}

	UInt64 EndianSwap(UInt64 value) {
		if (value == 0) return 0;

		return Native::_EndianSwap(value);
	}

}