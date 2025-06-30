#pragma once

#include <Jade/Core/Core.hpp>
#include <Jade/System/Memory.hpp>

namespace Jade {

	template<typename _CharType>
	class BaseString {
	public:
		static Size Length(const _CharType *string) {
			if (string == nullptr) return 0;

			Size length = 0;
			_CharType currentChar = string[length];
			while (currentChar != 0) {
				length++;
				currentChar = string[length];
			}

			return length;
		}

	public:
		BaseString() : mData(nullptr), mLength(0) { }
		BaseString(const _CharType *data) : mData(nullptr), mLength(0) {
			if (data == nullptr) return;
			
			mLength = Length(data);
			mData = AllocateArray<_CharType>(mLength + 1);

			CopyMemory(mData, data, mLength * sizeof(_CharType));
		}

		BaseString(const BaseString<_CharType> &other) : mData(nullptr), mLength(0) {
			if (other.mData == nullptr) return;

			mLength = other.mLength;
			mData = AllocateArray<_CharType>(mLength + 1);

			CopyMemory(mData, other.mData, mLength * sizeof(_CharType));
		}

		BaseString<_CharType> &operator=(const BaseString<_CharType> &other) {
			if (mData != nullptr) Free(mData);

			if (other.mData == nullptr) {
				mData = nullptr;
				mLength = 0;
				return *this;
			}

			mLength = other.mLength;
			mData = AllocateArray<_CharType>(mLength + 1);

			CopyMemory(mData, other.mData, mLength * sizeof(_CharType));
			return *this;
		}

		BaseString<_CharType> &operator=(const _CharType *data) {
			if (mData == nullptr) Free(mData);

			if (data == nullptr) {
				mData = nullptr;
				mLength = 0;
				return *this;
			}

			mLength = Length(data);
			mData = AllocateArray<_CharType>(mLength + 1);

			CopyMemory(mData, data, mLength * sizeof(_CharType));
			return *this;
		}

		~BaseString() {
			if (mData == nullptr) return;
			Free(mData);
		}

		inline BaseString<_CharType> &operator+=(const BaseString<_CharType> &other) {
			if (other.mData == nullptr || other.mLength == 0) return *this;
			if (mData == nullptr) {
				mLength = other.mLength;
				mData = AllocateArray<_CharType>(other.mLength + 1);
				
				CopyMemory(mData, other.mData, other.mLength * sizeof(_CharType));
				
				return *this;
			}

			_CharType *newData = AllocateArray<_CharType>(mLength + other.mLength + 1);
			CopyMemory(newData, mData, mLength * sizeof(_CharType));
			CopyMemory((void*)((UIntPtr)newData + (UIntPtr)mLength), other.mData, other.mLength * sizeof(_CharType));
			
			Free(mData);
			mData = newData;
			mLength = mLength + other.mLength;

			return *this;
		}

		inline BaseString<_CharType> &operator+=(const _CharType *string) {
			if (string == nullptr) return *this;
			
			Size length = Length(string);
			if (mData == nullptr) {
				mLength = length;
				mData = AllocateArray<_CharType>(length + 1);
				
				CopyMemory(mData, string, length * sizeof(_CharType));
				return *this;
			}

			_CharType *newData = AllocateArray<_CharType>(mLength + length + 1);
			CopyMemory(newData, mData, mLength * sizeof(_CharType));
			CopyMemory((void*)((UIntPtr)newData + (UIntPtr)mLength), string, length * sizeof(_CharType));

			Free(mData);
			mData = newData;
			mLength = mLength + length;

			return *this;
		}

		inline BaseString<_CharType> operator+(const BaseString<_CharType> &other) {
			if (other.mData == nullptr || other.mLength == 0) return *this;
			if (mData == nullptr || mLength == 0) return other;

			_CharType *newData = AllocateArray<_CharType>(mLength + other.mLength + 1);
			CopyMemory(newData, mData, mLength * sizeof(_CharType));
			CopyMemory((void*)((UIntPtr)newData + (UIntPtr)mLength), other.mData, other.mLength * sizeof(_CharType));
			newData[mLength + other.mLength] = 0;

			return BaseString<_CharType>(newData, mLength + other.mLength);
		}

		inline BaseString<_CharType> operator+(const _CharType *string) {
			if (string == nullptr) return *this;
			if (mData == nullptr || mLength == 0) return BaseString<_CharType>(string);

			Size length = Length(string);

			_CharType *newData = AllocateArray<_CharType>(mLength + length + 1);
			CopyMemory(newData, mData, mLength * sizeof(_CharType));
			CopyMemory((void*)((UIntPtr)newData + (UIntPtr)mLength), string, length * sizeof(_CharType));
			newData[mLength + length] = 0;

			return BaseString<_CharType>(newData, mLength + length);
		}

		inline void Reserve(Size length) {
			if (length < mLength || length == 0) return;
			
			_CharType *newData = AllocateArray<_CharType>(length + 1);
			if (mData != nullptr) {
				CopyMemory(newData, mData, mLength * sizeof(_CharType));
				Free(mData);
			}
			mData = newData;
		}

		inline void Resize(Size length) {
			Reserve(length);
			mLength = length;
		}

		inline Size Find(const _CharType *string) const {
			if (string == nullptr || mData == nullptr || mLength == 0) return __SIZE_MAX__;

			Size stringLength = Length(string);
			if (stringLength == 0) return __SIZE_MAX__;
			if (stringLength > mLength) return __SIZE_MAX__;

			for (Size i = 0; i < mLength - stringLength; i++) {
				for (Size j = 0; j < stringLength; j++) {
					if (mData[i + j] != string[j]) break;
					if (j == stringLength - 1) return i;
				}
			}
		}

		inline Size Find(const BaseString<_CharType> &string, Size start = 0) const {
			if (start + string.mLength > mLength) return __SIZE_MAX__;
			if (string.mData == nullptr || mData == nullptr || mLength == 0) return __SIZE_MAX__;
			if (string.mLength == 0 || string.mLength > mLength) return __SIZE_MAX__;

			for (Size i = start; i < mLength - string.mLength; i++) {
				for (Size j = 0; j < string.mLength; j++) {
					if (mData[i + j] != string.mData[j]) break;
					if (j == string.mLength - 1) return i;
				}
			}

			return __SIZE_MAX__;
		}

		inline BaseString<_CharType> SubString(Size start, Size length) const {
			if (mData == nullptr || mLength == 0 || start + length > mLength || length == 0) return BaseString<_CharType>();

			_CharType *stringData = AllocateArray<_CharType>(length + 1);
			CopyMemory(stringData, mData + start, length * sizeof(_CharType));

			return BaseString<_CharType>(stringData, length);
		}

		inline const _CharType *GetData() const { return mData; }
		inline _CharType *GetData() { return mData; }
		inline Size GetLength() const { return mLength; }
	
	private:
		BaseString(_CharType *data, Size length) : mData(data), mLength(length) {
			if (mData == nullptr || mLength == 0) {
				mData = nullptr;
				mLength = 0;
			} else {
				mData[mLength] = 0;
			}
		}

	private:
		_CharType *mData;
		Size mLength;
	};

	using String = BaseString<Char>;
	using WideString = BaseString<WideChar>;

	Char ToChar(WideChar wideChar);
	WideChar ToWideChar(Char charValue);
 
}