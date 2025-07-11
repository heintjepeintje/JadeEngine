#pragma once

#include <Jade/Core/Core.hpp>
#include <Jade/System/Memory.hpp>

namespace Jade {

	template<typename _Type>
	class Iterator {
	public:
		Iterator() { }
		Iterator(_Type *pointer) : mPointer(reinterpret_cast<UIntPtr>(pointer)) { }
		Iterator(UIntPtr pointer) : mPointer(pointer) { }
		Iterator(_Type *pointer, Size size) : mPointer(reinterpret_cast<UIntPtr>(pointer) + static_cast<UIntPtr>(size) * sizeof(_Type)) { }
		~Iterator() { }

		inline _Type &operator*() const { return *reinterpret_cast<_Type*>(mPointer); }
		inline _Type *operator->() const { return static_cast<_Type*>(mPointer); }
		
		inline Iterator<_Type> &operator++() { mPointer += sizeof(_Type); return *this; }
		inline Iterator<_Type> operator++(Int32) { Iterator<_Type> tmp(mPointer); mPointer += sizeof(_Type); return tmp; }
		inline Iterator<_Type> &operator--() { mPointer -= sizeof(_Type); return *this; }
		inline Iterator<_Type> &operator--(Int32) { Iterator<_Type> tmp(mPointer); mPointer -= sizeof(_Type); return tmp; }

		Iterator<_Type> operator+(Int32 count) { return Iterator<_Type>(mPointer + count * sizeof(_Type)); }
		Iterator<_Type> operator-(Int32 count) { return Iterator<_Type>(mPointer - count * sizeof(_Type)); }
		Iterator<_Type> &operator+=(Int32 count) { mPointer += count * sizeof(_Type); return *this; }
		Iterator<_Type> &operator-=(Int32 count) { mPointer -= count * sizeof(_Type); return *this; }

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
		ConstIterator() { }
		ConstIterator(const _Type *pointer) : mPointer(reinterpret_cast<UIntPtr>(pointer)) { }
		ConstIterator(UIntPtr pointer) : mPointer(pointer) { }
		ConstIterator(const _Type *pointer, Size size) : mPointer(reinterpret_cast<UIntPtr>(pointer) + static_cast<UIntPtr>(size) * sizeof(_Type)) { }
		~ConstIterator() { }

		inline _Type &operator*() const { return *reinterpret_cast<_Type*>(mPointer); }
		inline _Type *operator->() const { return reinterpret_cast<_Type*>(mPointer); }
		
		inline ConstIterator<_Type> &operator++() { mPointer += sizeof(_Type); return *this; }
		inline ConstIterator<_Type> operator++(Int32) { ConstIterator<_Type> tmp(mPointer); mPointer += sizeof(_Type); return tmp; }
		inline ConstIterator<_Type> &operator--() { mPointer -= sizeof(_Type); return *this; }
		inline ConstIterator<_Type> &operator--(Int32) { ConstIterator<_Type> tmp(mPointer); mPointer -= sizeof(_Type); return tmp; }

		ConstIterator<_Type> operator+(Int32 count) { return ConstIterator<_Type>(mPointer + count * sizeof(_Type)); }
		ConstIterator<_Type> operator-(Int32 count) { return ConstIterator<_Type>(mPointer - count * sizeof(_Type)); }
		ConstIterator<_Type> &operator+=(Int32 count) { mPointer += count * sizeof(_Type); return *this; }
		ConstIterator<_Type> &operator-=(Int32 count) { mPointer -= count * sizeof(_Type); return *this; }

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
	class Iterable {
	public:
		Iterable() { }
		virtual ~Iterable() { }

		virtual _Type *GetData() = 0;
		virtual const _Type *GetData() const = 0;
		virtual Size GetSize() const = 0;

		virtual _Type &operator[](Size index) { return GetData()[index]; }
		virtual const _Type &operator[](Size index) const { return GetData()[index]; }
		
		virtual Iterator<_Type> begin() final { return Iterator<_Type>(GetData()); }
		virtual Iterator<_Type> end() final { return Iterator<_Type>(GetData(), GetSize()); }
		virtual ConstIterator<_Type> begin() const final { return ConstIterator<_Type>(GetData()); }
		virtual ConstIterator<_Type> end() const final { return ConstIterator<_Type>(GetData(), GetSize()); }
	};

}