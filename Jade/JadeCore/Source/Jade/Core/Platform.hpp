#pragma once

#ifdef _WIN32
#	define JD_PLATFORM_WINDOWS 1
#else
#	error "Unknown/Unsupported platform"
#endif

#if defined(__x86_64__) || defined(_M_X64) || defined(__amd64__)
#	define JD_ARCHITECTURE_X64 1
#elif defined(__i386__) || defined(_M_IX86) || defined(__i686__)
#	define JD_ARCHITECTURE_X86 1
#elif defined(__aarch64__) || defined(_M_ARM64)
#	define JD_ARCHITECTURE_ARM64 1
#elif defined(__arm__) || defined(_M_ARM)
#	define JD_ARCHITECTURE_ARM 1
#else
#	error "Unknown/Unsupported architecture"
#endif

#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#	define JD_BYTE_ORDER_LITTLE_ENDIAN 1
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#	define JD_BYTE_ORDER_BIG_ENDIAN 1
#else
#	error "Unknown/Unsupported byte order"
#endif

namespace Jade { }