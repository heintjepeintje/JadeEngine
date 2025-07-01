#pragma once

#include <Jade/Core/Core.hpp>
#include "Iterator.hpp"
#include <Jade/System/Memory.hpp>

namespace Jade {

	template<typename _T>
	class List : public Iterable<_T>, public ConstIterable<_T> {
	public:
		List() = default;
		List(Size capacity) : mCapacity(capacity) {
			if (mCapacity == 0) return;
			mData = AllocateArray<_T>(mCapacity);
		}

		List(const List<_T> &other) : mData(nullptr), mSize(0), mCapacity(0) {
			if (other.mData == nullptr || other.mSize == 0) return;

			mSize = other.mSize;
			mCapacity = other.mCapacity;
			mData = AllocateArray<_T>(mCapacity);
			CopyMemory(mData, other.mData, mSize * sizeof(_T));
		}

		List<_T> &operator=(const List<_T> &other) {
			if (this == &other) return *this;

			if (mData != nullptr) Free(mData);

			if (other.mData == nullptr || other.mSize == 0) {
				mData = nullptr;
				mSize = 0;
				mCapacity = 0;
				return *this;
			}

			mSize = other.mSize;
			mCapacity = other.mCapacity;
			mData = AllocateArray<_T>(mCapacity);
			CopyMemory(mData, other.mData, mSize * sizeof(_T));
			return *this;
		}

		~List() {
			if (mData != nullptr) Free(mData);
		}

		void Reserve(Size capacity) {
			if (capacity == mCapacity) return;
			if (capacity < mSize) {
				mSize = capacity;
				return;
			}
			
			_T *newData = AllocateArray<_T>(capacity);

			if (mSize != 0) CopyMemory(newData, mData, mSize * sizeof(_T));
			if (mData != nullptr) Free(mData);

			mData = newData;
			mCapacity = capacity;
		}

		void Resize(Size size, const _T &value = _T()) {
			if (size > mCapacity) Reserve(size);
			
		}

		virtual _T *begin() override { return mData; }
		virtual _T *end() override { return OffsetPointer(mData, mSize); }
		virtual const _T *begin() const override { return mData; }
		virtual const _T *end() const override { return OffsetPointer(mData, mSize); }


	private:
		_T *mData = nullptr;
		Size mSize = 0;
		Size mCapacity = 0;
	};

}