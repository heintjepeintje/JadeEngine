#pragma once

#include <Jade/Core/Core.hpp>
#include <Jade/System/Memory.hpp>
#include "Allocator.hpp"

namespace Jade {

	class BufferView {
	public:
		BufferView() = default;	
		BufferView(void *pointer, Size size) : mPointer(pointer), mSize(size) { }
		BufferView(void *pointer, Size offset, Size size) : mPointer(pointer), mOffset(offset), mSize(size) { }
		~BufferView() = default;

		template<typename _Type>
		inline _Type *GetPointerAs() { return reinterpret_cast<_Type*>(mPointer); }
		
		template<typename _Type>
		inline _Type const *GetPointerAs() const { return reinterpret_cast<_Type const*>(mPointer); }

		inline void *GetPointer() { return mPointer; }
		inline void const *GetPointer() const { return mPointer; }
		inline Size GetOffset() const { return mOffset; }
		inline Size GetSize() const { return mSize; }

	private:
		void *mPointer = nullptr;
		Size mOffset = 0;
		Size mSize = 0;
	};

	class Buffer {
	public:
		Buffer() = default;
		
		explicit Buffer::Buffer(Size size) {
			if (size == 0) return;
			mSize = size;
			mData = Allocate(mSize);
		}

		Buffer::Buffer(const Buffer &other) {
			if (other.mData == nullptr || other.mSize == 0) return;

			mSize = other.mSize;
			mData = Allocate(other.mSize);
			CopyMemory(mData, other.mData, mSize);
		}

		Buffer &Buffer::operator=(const Buffer &other) {
			if (mData != nullptr) {
				Free(mData);
				mData = nullptr;
				mSize = 0;
			}

			if (other.mSize == 0 || other.mData == nullptr) return *this;

			mSize = other.mSize;
			mData = Allocate(mSize);
			CopyMemory(mData, other.mData, mSize);
			return *this;
		}

		Buffer::Buffer(Buffer &&other) {
			mData = other.mData;
			mSize = other.mSize;

			other.mData = nullptr;
			other.mSize = 0;
		}

		Buffer &Buffer::operator=(Buffer &&other) {
			if (mData != nullptr) Free(mData);

			mSize = other.mSize;
			mData = other.mData;

			other.mData = nullptr;
			other.mSize = 0;
		}

		Buffer::~Buffer() {
			if (mData == nullptr) return;
			Free(mData);
		}

		void Buffer::Resize(Size size) {
			if (mSize >= size) return;

			void *newData = Allocate(size);
			CopyMemory(newData, mData, mSize);
			
			mSize = size;
			mData = newData;
		}

		template<typename _Type>
		inline _Type *GetPointerAs() { return reinterpret_cast<_Type*>(mData); }

		template<typename _Type>
		inline const _Type *GetPointerAs() const { return reinterpret_cast<_Type const*>(mData); }

		template<typename _Type>
		inline _Type &GetAtOffset(Size offset) { return *reinterpret_cast<_Type*>(*OffsetPointer(mData, offset)); }

		template<typename _Type>
		inline _Type const &GetAtOffset(Size offset) const { return *reinterpret_cast<_Type const*>(*OffsetPointer(mData, offset)); }

		inline void const *GetPointer() const { return mData; }
		inline void *GetPointer() { return mData; }
		inline Size GetSize() const { return mSize; }

		inline BufferView GetView() { return BufferView(mData, 0, mSize); }
		inline BufferView GetView(Size offset) { return BufferView(mData, offset, mSize - offset); }
		inline BufferView GetView(Size offset, Size size) { return BufferView(mData, offset, size); }

	private:
		void *mData = nullptr;
		Size mSize = 0;
	};
	
}