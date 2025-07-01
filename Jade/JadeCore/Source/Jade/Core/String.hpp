#pragma once

#include <Jade/Core/Core.hpp>
#include <Jade/System/Memory.hpp>

#define JD_DEFAULT_FLOATING_POINT_PLACES 7

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

		static BaseString<_CharType> Concat(const _CharType *left, const _CharType *right) {
			if (left == nullptr && right == nullptr) return BaseString<_CharType>();

			Size leftLength = Length(left);
			Size rightLength = Length(right);
			Size newLength = leftLength + rightLength;

			BaseString<_CharType> result;
			result.mLength = newLength;
			result.mData = AllocateArray<_CharType>(newLength + 1);
			if (left != nullptr) CopyMemory(result.mData, left, leftLength * sizeof(_CharType));
			if (right != nullptr) CopyMemory((void*)((UIntPtr)result.mData + (UIntPtr)leftLength), right, rightLength * sizeof(_CharType));

			result.mData[newLength] = 0;
			return result;
		}

	public:
		BaseString() : mData(nullptr), mLength(0) { }
		
		BaseString(Size length) : mData(nullptr), mLength(0) {
			if (length == 0) return;

			mLength = length;
			mData = AllocateArray<_CharType>(length + 1);
		}

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

		inline void Resize(Size length, _CharType filler = '\0') {
			if (length < mLength || length == 0) return;
			
			_CharType *newData = AllocateArray<_CharType>(length + 1);
			if (mData != nullptr) {
				CopyMemory(newData, mData, mLength * sizeof(_CharType));
				Free(mData);
			}

			if (filler != '\0') {
				FillMemory(
					OffsetPointer(newData, mLength * sizeof(_CharType)),
					filler,
					(length - mLength) * sizeof(_CharType)
				);
			}
			
			mData = newData;
			mLength = length;
		}
		
		inline Size Find(const _CharType *string) const {
			if (string == nullptr || mData == nullptr || mLength == 0) return __SIZE_MAX__;
			
			Size stringLength = Length(string);
			if (stringLength == 0) return __SIZE_MAX__;
			if (stringLength > mLength) return __SIZE_MAX__;

			for (Size i = 0; i < mLength - stringLength + 1; i++) {
				for (Size j = 0; j < stringLength; j++) {
					if (mData[i + j] != string[j]) break;
					if (j == stringLength - 1) return i;
				}
			}
			
			return __SIZE_MAX__;
		}

		inline Size Find(const _CharType c) const {
			if (mData == nullptr) return __SIZE_MAX__;
			
			for (Size i = 0; i < mLength; i++) {
				if (mData[i] == c) return i;
			}
			
			return __SIZE_MAX__;
		}

		
		inline BaseString<_CharType> SubString(Size start, Size length) const {
			if (mData == nullptr || mLength == 0 || start + length > mLength || length == 0) return BaseString<_CharType>();

			_CharType *stringData = AllocateArray<_CharType>(length + 1);
			CopyMemory(stringData, mData + start, length * sizeof(_CharType));
			
			return BaseString<_CharType>(stringData, length);
		}

		inline Size Replace(Size start, Size length, const _CharType *replace) {
			if (mData == nullptr || mLength == 0 || start + length > mLength || length == 0 || replace == nullptr) return __SIZE_MAX__;
			
			Size replaceLength = Length(replace);
			if (replaceLength == 0) return __SIZE_MAX__;
			
			Size newLength = mLength - length + replaceLength;
			_CharType *newData = AllocateArray<_CharType>(newLength + 1);
			CopyMemory(newData, mData, start * sizeof(_CharType));
			
			MoveMemory(
				OffsetPointer(newData, start + replaceLength),
				OffsetPointer(mData, start + length),
				(mLength - start - length) * sizeof(_CharType)
			);
			
			CopyMemory(OffsetPointer(newData, start), replace, replaceLength * sizeof(_CharType));
			
			Free(mData);
			mData = newData;
			mLength = newLength;
			
			return start;
		}

		inline Size ReplaceFirst(const _CharType *search, const _CharType *replace, Size offset = 0) {
			if (mData == nullptr || mLength == 0 || search == nullptr || replace == nullptr) return __SIZE_MAX__;
			
			Size searchLength = Length(search);
			if (searchLength == 0 || offset + searchLength > mLength) return __SIZE_MAX__;
			
			Size foundIndex = Find(search, offset);
			if (foundIndex == __SIZE_MAX__) return __SIZE_MAX__;
			
			return Replace(foundIndex, searchLength, replace);
		}
		
		inline UInt32 ReplaceAll(const _CharType *search, const _CharType *replace, Size offset = 0) {
			if (mData == nullptr || mLength == 0 || search == nullptr || replace == nullptr) return 0;
			
			Size searchLength = Length(search);
			Size replaceLength = Length(replace);
			if (searchLength == 0 || replaceLength == 0 || offset + searchLength > mLength) return 0;
			
			UInt32 count = 0;
			Size foundIndex = Find(search, offset);
			while (foundIndex != __SIZE_MAX__) {
				count++;
				foundIndex = ReplaceFirst(search, replace, foundIndex + replaceLength);
			}
			
			return count;
		}
		
		inline Bool8 ContainsAll(const _CharType *string) const {
			if (string == nullptr || mData == nullptr || mLength == 0) return false;
			
			Size stringLength = Length(string);
			if (stringLength == 0 || stringLength > mLength) return false;
			
			for (Size i = 0; i < stringLength; i++) {
				if (Find(string[i]) == __SIZE_MAX__) return false;
			}
			
			return true;
		}
		
		inline Bool8 ContainsAny(const _CharType *string) const {
			if (string == nullptr || mData == nullptr || mLength == 0) return false;
			
			Size stringLength = Length(string);
			if (stringLength == 0 || stringLength > mLength) return false;
			
			for (Size i = 0; i < stringLength; i++) {
				if (Find(string[i]) != __SIZE_MAX__) return true;
			}
			
			return false;
		}

		inline Bool8 ContainsOnly(const _CharType *string) const {
			if (string == nullptr || mData == nullptr || mLength == 0) return false;

			Size stringLength = Length(string);
			if (stringLength == 0 || stringLength > mLength) return false;

			for (Size i = 0; i < mLength; i++) {
				if (Find(mData[i]) == __SIZE_MAX__) return false;
			}

			return true;
		}
		
		inline BaseString<_CharType> &operator+=(const BaseString<_CharType> &other) { return operator+=(other.mData); }
		inline BaseString<_CharType> operator+(const BaseString<_CharType> &other) { return operator+(other.mData); }
		inline Size Find(const BaseString<_CharType> &string, Size start = 0) const { return Find(string.mData); }
		inline Size Replace(Size start, Size length, const BaseString<_CharType> &replace) { return Replace(start, length, replace.mData); }
		inline Size ReplaceFirst(const BaseString<_CharType> &search, const BaseString<_CharType> &replace, Size offset = 0) { return ReplaceFirst(search.mData, replace.mData, offset); }
		inline UInt32 ReplaceAll(const BaseString<_CharType> &search, const BaseString<_CharType> &replace, Size offset = 0) { return ReplaceAll(search.mData, replace.mData, offset); }
		inline Bool8 ContainsAll(const BaseString<_CharType> &string) const { return ContainsAll(string.mData); }
		inline Bool8 ContainsAny(const BaseString<_CharType> &string) const { return ContainsAny(string.mData); }
		inline Bool8 ContainsOnly(const BaseString<_CharType> &string) const { return ContainsOnly(string.mData); }

		inline Bool8 IsEmpty() const { return mData == nullptr || mLength == 0; }

		inline _CharType &operator[](Size index) { return mData[index]; }
		inline const _CharType &operator[](Size index) const { return mData[index]; }

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
		_CharType *mData = nullptr;
		Size mLength = 0;
	};

	template<typename _CharType>
	inline BaseString<_CharType> &operator+(const _CharType *string, const BaseString<_CharType> &other) {
		return BaseString<_CharType>(string) + other;
	}

	using String = BaseString<Char>;
	using WideString = BaseString<WideChar>;

	Char ToChar(WideChar wideChar);
	WideChar ToWideChar(Char charValue);

	String ToString(const WideString &wide);
	WideString ToWideString(const String &string);

	String UInt32ToString(UInt32 value);
	String UInt64ToString(UInt64 value);
	String Int32ToString(Int32 value);
	String Int64ToString(Int64 value);
	String Float32ToString(Float32 value, UInt32 places = JD_DEFAULT_FLOATING_POINT_PLACES);
	String Float64ToString(Float64 value, UInt32 places = JD_DEFAULT_FLOATING_POINT_PLACES);

}