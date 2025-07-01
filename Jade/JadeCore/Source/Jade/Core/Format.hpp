#pragma once

#include "String.hpp"
#include "Template.hpp"

#include <vector>

namespace Jade {

	template<typename _T>
	class Formatter {
	public:
		static String FormatType(const _T &value);
	};

	template<> class Formatter<String> { public: static String FormatType(const String &value) { return value; } };
	template<> class Formatter<Bool8> { public: static String FormatType(const Bool8 &value) { return value ? String("true") : String("false"); } };
	template<> class Formatter<UInt8> { public: static String FormatType(const UInt8 &value) { return UInt32ToString(static_cast<UInt32>(value)); } };
	template<> class Formatter<UInt16> { public: static String FormatType(const UInt16 &value) { return UInt32ToString(static_cast<UInt32>(value)); } };
	template<> class Formatter<UInt32> { public: static String FormatType(const UInt32 &value) { return UInt32ToString(value); } };
	template<> class Formatter<UInt64> { public: static String FormatType(const UInt64 &value) { return UInt64ToString(value); } };
	template<> class Formatter<Int8> { public: static String FormatType(const Int8 &value) { return Int32ToString(static_cast<Int32>(value)); } };
	template<> class Formatter<Int16> { public: static String FormatType(const Int16 &value) { return Int32ToString(static_cast<Int32>(value)); } };
	template<> class Formatter<Int32> { public: static String FormatType(const Int32 &value) { return Int32ToString(value); } };
	template<> class Formatter<Int64> { public: static String FormatType(const Int64 &value) { return Int64ToString(value); } };
	template<> class Formatter<Float32> { public: static String FormatType(const Float32 &value) { return Float32ToString(value, 7); } };
	template<> class Formatter<Float64> { public: static String FormatType(const Float64 &value) { return Float64ToString(value, 7); } };

	template<typename _T>
	inline String ToString(const _T &value) {
		return Formatter<_T>::FormatType(value);
	}

	template<typename _T, typename ..._More>
	inline void FormatNext(String *output, UInt32 index, const _T &current, const _More &...more) {
		String data = Formatter<_T>::FormatType(current);
		output[index] = data;
		if constexpr (sizeof...(_More) > 0) FormatNext(output, index + 1, more...);
	}

	template<typename ..._Args>
	String Format(const String &string, _Args &&...args) {
		String result = string;

		String formattedArgs[sizeof...(_Args)] = { };
		FormatNext(formattedArgs, 0, Jade::Forward<_Args>(args)...);

		Size offset = 0;
		for (Size i = 0; i < sizeof...(_Args); i++) {
			Size foundIndex = result.ReplaceFirst("{}", formattedArgs[i], offset);
			if (foundIndex == __SIZE_MAX__) return String();

			offset += formattedArgs[i].GetLength() - 2;
		}

		return result;
	}

}