#pragma once

#include <Jade/Core/Core.hpp>
#include <Jade/Core/TypeInfo.hpp>

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

	template<typename _Type>
	inline _Type *AllocateSingle() {
		return reinterpret_cast<_Type*>(Allocate(sizeof(_Type)));
	}

	template<typename _Type>
	inline _Type *AllocateArray(Size count) {
		return reinterpret_cast<_Type*>(Allocate(sizeof(_Type) * count));
	}

	template<typename _Type>
	inline _Type *OffsetPointer(_Type *pointer, Size offset) {
		if (pointer == nullptr || offset == 0) return pointer;
		return reinterpret_cast<_Type*>(reinterpret_cast<UIntPtr>(pointer) + offset);
	}

	template<typename _Type>
	inline const _Type *OffsetPointer(const _Type *pointer, Size offset) {
		if (pointer == nullptr || offset == 0) return pointer;
		return reinterpret_cast<const _Type*>(reinterpret_cast<UIntPtr>(pointer) + offset);
	}

}