#pragma once

#include <Jade/Core/Core.hpp>
#include <Jade/System/Memory.hpp>

namespace Jade {

	template<typename _Type>
	class Iterator {
	public:
		using ValueType = _T;
		using PointerType = _T*;
		using ReferenceType = _T&;
		
	public:
		Iterator() { }
		Iterator(_T *pointer) : mPointer(reinterpret_cast<UIntPtr>(pointer)) { }
		Iterator(UIntPtr pointer) : mPointer(pointer) { }
		Iterator(_T *pointer, Size size) : mPointer(reinterpret_cast<UIntPtr>(pointer) + static_cast<UIntPtr>(size) * sizeof(_T)) { }
		~Iterator() { }

		inline ReferenceType operator*() const { return *reinterpret_cast<PointerType>(mPointer); }
		inline PointerType operator->() const { return static_cast<PointerType>(mPointer); }
		
		inline Iterator<_Type> &operator++() { mPointer += sizeof(_T); return *this; }
		inline Iterator<_Type> operator++(Int32) { Iterator<_Type> tmp(mPointer); mPointer += sizeof(_T); return tmp; }
		inline Iterator<_Type> &operator--() { mPointer -= sizeof(_T); return *this; }
		inline Iterator<_Type> &operator--(Int32) { Iterator<_Type> tmp(mPointer); mPointer -= sizeof(_T); return tmp; }

		Iterator<_Type> operator+(Int32 count) { return Iterator<_Type>(mPointer + count * sizeof(_T)); }
		Iterator<_Type> operator-(Int32 count) { return Iterator<_Type>(mPointer - count * sizeof(_T)); }
		Iterator<_Type> &operator+=(Int32 count) { mPointer += count * sizeof(_T); return *this; }
		Iterator<_Type> &operator-=(Int32 count) { mPointer -= count * sizeof(_T); return *this; }

		inline Bool8 operator==(const Iterator<_Type> &other) const { return mPointer == other.mPointer; }
		inline Bool8 operator!=(const Iterator<_Type> &other) const { return mPointer != other.mPointer; }
		inline Bool8 operator>=(const Iterator<_Type> &other) const { return mPointer >= other.mPointer; }
		inline Bool8 operator>(const Iterator<_Type> &other) const { return mPointer > other.mPointer; }
		inline Bool8 operator<=(const Iterator<_Type> &other) const { return mPointer <= other.mPointer; }
		inline Bool8 operator<(const Iterator<_Type> &other) const { return mPointer < other.mPointer; }

		inline operator Bool8() { return mPointer != 0; }

		template<typename _ReturnType>
		inline _ReturnType GetPointerAs() const { return reinterpret_cast<_ReturnType>(mPointer); }

	private:
		UIntPtr mPointer = 0;
	};

	template<typename _Type>
	class ConstIterator {
	public:
		using ValueType = _T;
		using PointerType = const _T*;
		using ReferenceType = const _T&;

	public:
		ConstIterator() { }
		ConstIterator(const _T *pointer) : mPointer(reinterpret_cast<UIntPtr>(pointer)) { }
		ConstIterator(UIntPtr pointer) : mPointer(pointer) { }
		ConstIterator(const _T *pointer, Size size) : mPointer(reinterpret_cast<UIntPtr>(pointer) + static_cast<UIntPtr>(size) * sizeof(_T)) { }
		~ConstIterator() { }

		inline ReferenceType operator*() const { return *reinterpret_cast<PointerType>(mPointer); }
		inline PointerType operator->() const { return reinterpret_cast<PointerType>(mPointer); }
		
		inline ConstIterator<_Type> &operator++() { mPointer += sizeof(_T); return *this; }
		inline ConstIterator<_Type> operator++(Int32) { ConstIterator<_Type> tmp(mPointer); mPointer += sizeof(_T); return tmp; }
		inline ConstIterator<_Type> &operator--() { mPointer -= sizeof(_T); return *this; }
		inline ConstIterator<_Type> &operator--(Int32) { ConstIterator<_Type> tmp(mPointer); mPointer -= sizeof(_T); return tmp; }

		ConstIterator<_Type> operator+(Int32 count) { return ConstIterator<_Type>(mPointer + count * sizeof(_T)); }
		ConstIterator<_Type> operator-(Int32 count) { return ConstIterator<_Type>(mPointer - count * sizeof(_T)); }
		ConstIterator<_Type> &operator+=(Int32 count) { mPointer += count * sizeof(_T); return *this; }
		ConstIterator<_Type> &operator-=(Int32 count) { mPointer -= count * sizeof(_T); return *this; }

		inline Bool8 operator==(const ConstIterator<_Type> &other) const { return mPointer == other.mPointer; }
		inline Bool8 operator!=(const ConstIterator<_Type> &other) const { return mPointer != other.mPointer; }
		inline Bool8 operator>=(const ConstIterator<_Type> &other) const { return mPointer >= other.mPointer; }
		inline Bool8 operator>(const ConstIterator<_Type> &other) const { return mPointer > other.mPointer; }
		inline Bool8 operator<=(const ConstIterator<_Type> &other) const { return mPointer <= other.mPointer; }
		inline Bool8 operator<(const ConstIterator<_Type> &other) const { return mPointer < other.mPointer; }

		inline operator Bool8() { return mPointer != 0; }

		template<typename _ReturnType>
		inline _ReturnType GetPointerAs() const { return reinterpret_cast<_ReturnType>(mPointer); }

	private:
		UIntPtr mPointer;
	};

	template<typename _Type>
	class ConstIterable {
	public:
		ConstIterable() { }
		virtual ~ConstIterable() { }

		virtual const _T *GetData() const = 0;
		virtual Size GetSize() const = 0;

		virtual const _T &operator[](Size index) const { return GetData()[index]; }
		
		virtual ConstIterator<_Type> begin() const { return ConstIteratorType(GetData()); }
		virtual ConstIterator<_Type> end() const { return ConstIteratorType(GetData(), GetSize()); }
	};

	template<typename _Type>
	class Iterable : public ConstIterable<_Type> {
	public:
		Iterable() { }
		virtual ~Iterable() { }

		virtual _T *GetData() = 0;

		virtual _T &operator[](Size index) { return GetData()[index]; }
		
		virtual Iterator<_Type> begin() { return IteratorType(GetData()); }
		virtual Iterator<_Type> end() { return IteratorType(GetData(), GetSize()); }
	};

}