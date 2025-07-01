#pragma once

#include <Jade/Core/Template.hpp>

namespace Jade {

	template<typename _T>
	class Iterable {
	public:
		virtual _T *begin() = 0;
		virtual _T *end() = 0;
	};

	template<typename _T>
	class ConstIterable {
	public:
		virtual const _T *begin() const = 0;
		virtual const _T *end() const = 0;
	};

}