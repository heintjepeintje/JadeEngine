#pragma once

#include "Core.hpp"
#include "TypeInfo.hpp"
#include <Jade/System/Memory.hpp>
#include <new>

namespace Jade {

	template<typename _Type>
	constexpr void *AddressOf(_Type &object) {
		return static_cast<void*>(&object);
	}

	template<typename _Type, typename ..._Args>
	constexpr void *ConstructAt(_Type *pointer, _Args &&...args) {
		static_assert(!IsArrayType<_Type>::Value, "Cannot use ConstructAt with array type");
		return ::new (AddressOf(*pointer)) _Type(Forward<_Args>(args)...);
	}

	template<typename _Type>
	constexpr void DestroyAt(_Type *pointer) {
		static_assert(!IsArrayType<_Type>::Value, "Cannot use DestroyAt with array type");
		pointer->~_Type();
	}

	template<typename _Type>
	class Singleton {
		static _Type &GetInstance() {
			static _Type sInstance;
			return sInstance;
		}
	};

}