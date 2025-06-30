#pragma once

#define JD_CHAR8_STRING(x) reinterpret_cast<::Jade::Char8*>(x)
#define JD_CHAR8_CSTRING(x) reinterpret_cast<const ::Jade::Char8*>(x)
#define JD_CHAR16_STRING(x) reinterpret_cast<::Jade::Char16*>(L##x)
#define JD_CHAR16_CSTRING(x) reinterpret_cast<const ::Jade::Char16*>(L##x)
#define JD_CHAR32_STRING(x) reinterpret_cast<::Jade::Char32*>(U##x)
#define JD_CHAR32_CSTRING(x) reinterpret_cast<const ::Jade::Char32*>(U##x)

#define JD_CHAR_STRING(x) reinterpret_cast<::Jade::Char*>(x)
#define JD_CHAR_CSTRING(x) reinterpret_cast<const ::Jade::Char*>(x)
#define JD_WIDECHAR_STRING(x) reinterpret_cast<::Jade::WideChar*>(L##x)
#define JD_WIDECHAR_CSTRING(x) reinterpret_cast<const ::Jade::WideChar*>(L##x)

namespace Jade {

	typedef unsigned char Char8;
	typedef __CHAR16_TYPE__ Char16;
	typedef __CHAR32_TYPE__ Char32;
	typedef char Char;
	typedef wchar_t WideChar;

	typedef __UINT8_TYPE__ UInt8;
	typedef __UINT16_TYPE__ UInt16;
	typedef __UINT32_TYPE__ UInt32;
	typedef __UINT64_TYPE__ UInt64;

	typedef __INT8_TYPE__ Int8;
	typedef __INT16_TYPE__ Int16;
	typedef __INT32_TYPE__ Int32;
	typedef __INT64_TYPE__ Int64;
	
	typedef __UINTPTR_TYPE__ UIntPtr;
	typedef __INTPTR_TYPE__ IntPtr;

	typedef __SIZE_TYPE__ Size;
	typedef __PTRDIFF_TYPE__ PtrDiff;

	typedef bool Bool8;

	typedef unsigned char Byte;

	typedef float Float32;
	typedef double Float64;

}