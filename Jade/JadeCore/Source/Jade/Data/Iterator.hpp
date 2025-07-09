#pragma once

#include <Jade/Core/Core.hpp>
#include <Jade/System/Memory.hpp>

namespace Jade {

	template<typename _T>
	class ConstIterator {
	public:
		ConstIterator(const _T *data, Size size) : mData(data), mSize(size) { }
		~ConstIterator() = default;

		inline void ForEach(void(*func)(const _T &)) { for (Size i = 0; i < mSize; i++) { func(mData[i]); } }
		inline void ForEach(void(*func)(Size, const _T &)) { for (Size i = 0; i < mSize; i++) { func(i, mData[i]); } }
		
		inline const _T *GetData() const { return mData; }
		inline Size GetSize() const { return mSize; }

		inline const _T &operator[](Size index) const { return mData[index]; }

		inline const _T *begin() const { return mData; }
		inline const _T *end() const { return OffsetPointer(mData, mSize); }

	private:
		const _T *mData;
		const Size mSize;
	};

	template<typename _T>
	class Iterator {
	public:
		Iterator(_T *data, Size size) : mData(data), mSize(size) { }
		~Iterator() = default;

		inline void ForEach(void(*func)(_T &)) { for (Size i = 0; i < mSize; i++) { func(mData[i]); } }
		inline void ForEach(void(*func)(const _T &)) { for (Size i = 0; i < mSize; i++) { func(mData[i]); } }
		inline void ForEach(void(*func)(Size, _T &)) { for (Size i = 0; i < mSize; i++) { func(i, mData[i]); } }
		inline void ForEach(void(*func)(Size, const _T &)) { for (Size i = 0; i < mSize; i++) { func(i, mData[i]); } }
		
		inline _T *GetData() { return mData; }
		inline const _T *GetData() const { return mData; }
		inline Size GetSize() const { return mSize; }

		inline _T *begin() { return mData; }
		inline _T *end() { return OffsetPointer(mData, mSize); }
		inline const _T *begin() const { return mData; }
		inline const _T *end() const { return OffsetPointer(mData, mSize); }

		inline _T &operator[](Size index) { return mData[index]; }
		inline const _T &operator[](Size index) const { return mData[index]; }

		inline operator ConstIterator<_T>() const { return ConstIterator<_T>(mData, mSize); }

	private:
		_T *mData;
		Size mSize;
	};

}