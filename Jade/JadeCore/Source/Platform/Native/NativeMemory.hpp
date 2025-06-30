#pragma once

namespace Jade::Native {

	void *_Allocate(Size size);
	void *_ReAllocate(void *ptr, Size size);
	void _Free(void *ptr);

	void _CopyMemory(void *destination, const void *source, Size size);
	void _FillMemory(void *pointer, Byte value, Size size);
	void _MoveMemory(void *destination, const void *source, Size size);
	void _ZeroMemory(void *pointer, Size size);
	Size _CompareMemory(const void *left, const void *right, Size size);

	UInt16 _EndianSwap(UInt16 value);
	UInt32 _EndianSwap(UInt32 value);
	UInt64 _EndianSwap(UInt64 value);

}