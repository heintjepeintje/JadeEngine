#pragma once

#include "String.hpp"
#include "Template.hpp"

#include <cstdio>

namespace Jade {

	template<typename _T>
	struct Formatter {
		static String FormatType(const String *args, Size argCount, const _T &value);
	};

	template<typename _T>
	struct Parser {
		static _T ParseType(const String &value);
	};

	template<typename _T>
	inline String ToString(const _T &value) { return Formatter<_T>::FormatType(value); }

	template<typename _T, typename ..._More>
	inline void FormatNext(String *output, UInt32 index, const _T &current, const _More &...more) {
		String data = Formatter<_T>::FormatType(current);
		output[index] = data;
		if constexpr (sizeof...(_More) > 0) FormatNext(output, index + 1, more...);
	}

	template<typename ..._Args>
	String Format(const String &string, _Args &&...args) {
		String result = string;
		
		if constexpr (sizeof...(_Args) != 0) {
			String formattedArgs[sizeof...(_Args)] = { };
			FormatNext(formattedArgs, 0, Jade::Forward<_Args>(args)...);
	
			Size offset = 0;
			for (Size i = 0; i < sizeof...(_Args); i++) {
				const String formatted = formattedArgs[i];
				result.ReplaceFirst("{}", formatted, offset);
				offset += formatted.GetLength() - 2;
			}
		}

		return result;
	}

	template<>
	struct Formatter<String> {
		static String FormatType(const String &value) {
			return value;
		}
	};

	template<>
	struct Formatter<Char *> {
		static String FormatType(Char *const &value) {
			return String(value);
		}
	};

	template<>
	struct Formatter<Bool8> {
		static String FormatType(const Bool8 &value) {
			return value ? String("true") : String("false");
		}
	};

	template<Size _Size>
	struct Formatter<Char[_Size]> {
		static String FormatType(const Char (&value)[_Size]) {
			return String(value);
		}
	};

	template<>
	struct Formatter<UInt32> {
		static String FormatType(const UInt32 &value) {
			return UInt32ToString(value);
		}
	};

	template<>
	struct Formatter<UInt64> {
		static String FormatType(const UInt64 &value) {
			return UInt64ToString(value);
		}
	};
	
	template<>
	struct Formatter<Int32> {
		static String FormatType(const Int32 &value) {
			return Int32ToString(value);
		}
	};

	template<>
	struct Formatter<Int64> {
		static String FormatType(const Int64 &value) {
			return Int64ToString(value);
		}
	};

	template<>
	struct Formatter<Float32> {
		static String FormatType(const Float32 &value) {
			return Float32ToString(value, 7);
		}
	};

	template<>
	struct Formatter<Float64> {
		static String FormatType(const Float64 &value) {
			return Float64ToString(value, 7);
		}
	};

}