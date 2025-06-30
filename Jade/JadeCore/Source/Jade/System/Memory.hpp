#pragma once

#include <Jade/Core/Core.hpp>

namespace Jade {

	void *Allocate(Size size);
	void *ReAllocate(void *pointer, Size size);
	void Free(void *pointer);

	void CopyMemory(void *destination, const void *source, Size size);
	void FillMemory(void *pointer, Byte value, Size size);
	void MoveMemory(void *destination, const void *source, Size size);
	void ZeroMemory(void *pointer, Size size);
	Size CompareMemory(const void *left, const void *right, Size size);

	UInt16 EndianSwap(UInt16 value);
	UInt32 EndianSwap(UInt32 value);
	UInt64 EndianSwap(UInt64 value);

	template<typename _T>
	inline _T *AllocateSingle() {
		return reinterpret_cast<_T*>(Allocate(sizeof(_T)));
	}

	template<typename _T>
	inline _T *AllocateArray(Size count) {
		return reinterpret_cast<_T*>(Allocate(sizeof(_T) * count));
	}

}