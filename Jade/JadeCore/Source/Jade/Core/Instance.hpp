#pragma once

#include "Core.hpp"
#include "TypeInfo.hpp"
#include <Jade/System/Memory.hpp>
#include <new>

namespace Jade {

	template<typename _T>
	void *AddressOf(_T &object) {
		return static_cast<void*>(&object);
	}

	template<typename _T, typename ..._Args>
	void *ConstructAt(_T *pointer, _Args &&...args) {
		static_assert(!IsArrayType<_T>::Value, "Cannot use ConstructAt with array type");
		return ::new (AddressOf(*pointer)) _T(Forward<_Args>(args)...);
	}

	template<typename _T>
	void DestroyAt(_T *pointer) {
		static_assert(!IsArrayType<_T>::Value, "Cannot use DestroyAt with array type");
		pointer->~_T();
	}

	template<typename _T>
	class Singleton {
		static _T &GetInstance() {
			static _T sInstance;
			return sInstance;
		}
	};

}