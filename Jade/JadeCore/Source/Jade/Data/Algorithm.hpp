#pragma once

#include <Jade/Core/Core.hpp>
#include <Jade/System/Memory.hpp>
#include "Iterator.hpp"
#include <Jade/Core/Logger.hpp>
#include <Jade/Core/Limits.hpp>

namespace Jade {

	template<typename _Type>
	using Comparator = bool(const _Type &, const _Type &);

	template<typename _Type> bool LessDefault(const _Type &left, const _Type &right) { return left < right; }
	template<typename _Type> bool LessOrEqualDefault(const _Type &left, const _Type &right) { return left <= right; }
	template<typename _Type> bool GreaterDefault(const _Type &left, const _Type &right) { return left > right; }
	template<typename _Type> bool GreaterOrEqualDefault(const _Type &left, const _Type &right) { return left >= right; }
	template<typename _Type> bool EqualDefault(const _Type &left, const _Type &right) { return left == right; }

	template<typename _Type>
	ConstIterator<_Type> Find(ConstIterator<_Type> begin, ConstIterator<_Type> end, const _Type &target, Comparator<_Type> equals = EqualDefault<_Type>) {
		while (begin != end) {
			if (equals(*begin, target)) return begin;
			begin++;
		}

		return ConstIterator<_Type>();
	}

	template<typename _Type>
	Iterator<_Type> Find(Iterator<_Type> begin, Iterator<_Type> end, const _Type &target, Comparator<_Type> equals = EqualDefault<_Type>) {
		while (begin != end) {
			if (equals(*begin, target)) return begin;
			begin++;
		}

		return Iterator<_Type>();
	}

	template<typename _Type>
	void ForEach(Iterator<_Type> begin, Iterator<_Type> end, void(*func)(_Type &item)) {
		while (begin != end) {
			func(*begin);
			begin++;
		}
	}

	template<typename _Type>
	void ForEach(ConstIterator<_Type> begin, ConstIterator<_Type> end, void(*func)(const _Type &item)) {
		while (begin != end) {
			func(*begin);
			begin++;
		}
	}

	template<typename _Type>
	ConstIterator<_Type> Find(const Iterable<_Type> &iterable, const _Type &target, Comparator<_Type> equals = EqualDefault<_Type>) {
		return Find(iterable.begin(), iterable.end(), target, equals);
	}
	
	template<typename _Type>
	Iterator<_Type> Find(Iterable<_Type> &iterable, const _Type &target, Comparator<_Type> equals = EqualDefault<_Type>) {
		return Find(iterable.begin(), iterable.end(), target, equals);
	}

	template<typename _Type>
	void ForEach(Iterable<_Type> &iterable, void(*func)(_Type &item)) {
		ForEach(iterable.begin(), iterable.end(), func);
	}

	template<typename _Type>
	void ForEach(const Iterable<_Type> &iterable, void(*func)(const _Type &item)) {
		ForEach(iterable.begin(), iterable.end(), func);
	}
}