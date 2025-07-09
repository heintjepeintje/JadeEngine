#pragma once

#include <Jade/Core/Core.hpp>
#include "Iterator.hpp"
#include <Jade/System/Memory.hpp>
#include <Jade/Core/Instance.hpp>
#include <Jade/System/Debug.hpp>

namespace Jade {

	template<typename _T>
	class List {	
	public:
		List() = default;
		List(Size capacity) : mCapacity(capacity) {
			if (mCapacity == 0) return;
			mData = AllocateArray<_T>(mCapacity);
		}

		List(const List<_T> &other) {
			if (other.mData == nullptr || other.mCapacity == 0) return;

			mSize = other.mSize;
			mCapacity = other.mCapacity;
			mData = AllocateArray<_T>(mCapacity);

			for (Size i = 0; i < mSize; i++) ConstructAt(&mData[i], other.mData[i]);
		}

		List<_T> &operator=(const List<_T> &other) {
			if (this == &other) return *this;

			if (other.mData == nullptr || other.mCapacity == 0) {
				for (Size i = 0; i < mSize; i++) DestroyAt(&mData[i]);
				Free(mData);
				mData = nullptr;
				mCapacity = 0;
				mSize = 0;
				return *this;
			}

			_T *newData = AllocateArray<_T>(other.mCapacity);
			CopyMemory(newData, mData, mSize);
			Free(mData);
			mData = newData;
			mCapacity = other.mCapacity;

			if (mSize > other.mSize) {
				Size start = other.mSize == 0 ? 0 : other.mSize - 1;
				for (Size i = start - 1; i < mSize; i++) DestroyAt(&mData[i]);
			} else if (mSize < other.mSize) {
				Size start = mSize == 0 ? 0 : mSize - 1;
				for (Size i = start; i < other.mSize; i++) ConstructAt(&mData[i], other.mData[i]);
			}
			
			if (mSize != 0) {
				for (Size i = 0; i < other.mSize; i++) mData[i] = other.mData[i];
			}

			mSize = other.mSize;
			return *this;
		}

		List(List<_T> &&other) {
			if (other.mData == nullptr || other.mCapacity == 0) return;

			mData = other.mData;
			mSize = other.mSize;
			mCapacity = other.mCapacity;

			other.mData = nullptr;
			other.mCapacity = 0;
			other.mSize = 0;
		}

		List<_T> &operator=(List<_T> &&other) {
			if (mData != nullptr) {
				for (Size i = 0; i < mSize; i++) DestroyAt(&mData[i]);
				Free(mData);
			}

			mData = other.mData;
			mSize = other.mSize;
			mCapacity = other.mCapacity;

			mData = nullptr;
			mCapacity = 0;
			mSize = 0;
		}

		~List() {
			if (mData == nullptr) return;
			for (Size i = 0; i < mSize; i++) DestroyAt(&mData[i]);
			Free(mData); 
		}

		void ReserveExact(Size capacity) {
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

		void Reserve(Size capacity) {
			if (capacity < mCapacity) return;
			
			Size newCapacity = mCapacity;
			while (newCapacity < capacity) {
				newCapacity = static_cast<Size>(static_cast<float>(newCapacity) * 1.5f);
			}

			ReserveExact(newCapacity);
		}

		template<typename ..._Args>
		void Resize(Size size, _Args &&...args) {
			if (size > mCapacity) Reserve(size);
			
			if (size < mSize) {
				for (Size i = size; i < mSize; i++) DestroyAt(&mData[i]);
			} else if (size > mSize) {
				for (Size i = mSize; i < size; i++) ConstructAt(&mData[i], Forward<_Args>(args)...);
			}

			mSize = size;
		}

		inline void Add(const _T &item) {
			if (mSize + 1 > mCapacity) Reserve(mSize + 1);
			ConstructAt(&mData[mSize], item);
			mSize = mSize + 1;
		}

		template<typename ..._Args>
		inline void Emplace(_Args ...args) {
			if (mSize + 1 > mCapacity) Reserve(mSize + 1);
			ConstructAt(&mData[mSize], Forward<_Args>(args)...);
			mSize = mSize + 1;
		}

		template<typename ..._Args>
		inline void EmplaceAt(Size index, _Args &&...args) {
			if (index + 1 > mCapacity) Reserve(index + 1);
			
			if (index + 1 < mSize) {
				Jade::ConstructAt(&mData[index], Forward<_Args>(args)...);
			} else if (index + 1 > mSize) {
				for (Size i = mSize - 1; i < index; i++) ConstructAt<_T>(&mData[i]);
				ConstructAt(&mData[index], Forward<_Args>(args)...);
			}

			mSize = index + 1;
		}

		inline void Clear() {
			if (mSize == 0) return;
			for (Size i = 0; i < mSize; i++) DestroyAt(&mData[i]);
			mSize = 0;
		}

		inline _T &Get(Size index) { return mData[index]; }
		inline const _T &Get(Size index) const { return mData[index]; }

		inline _T &operator[](Size index) { return Get(index); }
		inline const _T &operator[](Size index) const { return Get(index); }

		inline Iterator<_T> GetIterator() { return Iterator<_T>(mData, mSize); }
		inline ConstIterator<_T> GetConstIterator() const { return ConstIterator<_T>(mData, mSize); }

		inline operator Iterator<_T>() { return Iterator<_T>(mData, mSize); }
		inline operator ConstIterator<_T>() const { return ConstIterator<_T>(mData, mSize); }

		template<typename _TransformType>
		inline List<_TransformType> Transform(_TransformType(*transform)(const _T &)) {
			List<_TransformType> transformedList(mSize);
			for (Size i = 0; i < mSize; i++) {
				transformedList.Emplace(transform(mData[i]));
			}
			return transformedList;
		}

		inline _T *GetData() { return mData; }
		inline const _T *GetData() const { return mData; }
		inline Size GetSize() const { return mSize; }
		inline Size GetCapacity() const { return mCapacity; }

	private:
		_T *mData = nullptr;
		Size mSize = 0;
		Size mCapacity = 0;
	};

}