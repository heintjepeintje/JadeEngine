#pragma once

#include "Core.hpp"
#include "TypeInfo.hpp"
#include <Jade/System/Memory.hpp>
#include <new>

namespace Jade {

	template<typename _Type>
	constexpr void *AddressOf(_T &object) {
		return static_cast<void*>(&object);
	}

	template<typename _T, typename ..._Args>
	constexpr void *ConstructAt(_T *pointer, _Args &&...args) {
		static_assert(!IsArrayType<_Type>::Value, "Cannot use ConstructAt with array type");
		return ::new (AddressOf(*pointer)) _T(Forward<_Args>(args)...);
	}

	template<typename _Type>
	constexpr void DestroyAt(_T *pointer) {
		static_assert(!IsArrayType<_Type>::Value, "Cannot use DestroyAt with array type");
		pointer->~_T();
	}

	template<typename _Type>
	class Singleton {
		static _T &GetInstance() {
			static _T sInstance;
			return sInstance;
		}
	};

}