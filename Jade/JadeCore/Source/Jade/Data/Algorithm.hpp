#pragma once

#include <Jade/Core/Core.hpp>
#include <Jade/System/Memory.hpp>
#include "Iterator.hpp"
#include <Jade/Core/Logger.hpp>
#include <Jade/Core/Limits.hpp>

namespace Jade {

	template<typename _T>
	using Comparator = bool(const _T &, const _T &);

	template<typename _T> bool LessDefault(const _T &left, const _T &right) { return left < right; }
	template<typename _T> bool LessOrEqualDefault(const _T &left, const _T &right) { return left <= right; }
	template<typename _T> bool GreaterDefault(const _T &left, const _T &right) { return left > right; }
	template<typename _T> bool GreaterOrEqualDefault(const _T &left, const _T &right) { return left >= right; }
	template<typename _T> bool EqualDefault(const _T &left, const _T &right) { return left == right; }

	template<typename _T>
	Size Find(const ConstIterator<_T> &iterator, const _T &target, Comparator<_T> equals = EqualDefault<_T>) {
		for (Size i = 0; i < iterator.GetSize(); i++) {
			if (!equals(iterator[i], target)) continue;
			return i;
		}

		return MaxValue<Size>();
	}

}