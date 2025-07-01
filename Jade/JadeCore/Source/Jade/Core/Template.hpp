#pragma once

#include <Jade/Core/Core.hpp>

namespace Jade {

	typedef UInt64 TypeID;

	template<typename _T> struct RemoveReference_ { using Type = _T; };
	template<typename _T> struct RemoveReference_<_T &> { using Type = _T; };
	template<typename _T> class RemoveReference_<_T &&> { using Type = _T; };
	template<typename _T> using RemoveReference = typename RemoveReference_<_T>::Type;

	template<typename _T> struct RemoveConst_ { using Type = _T; };
	template<typename _T> struct RemoveConst_<_T const> { using Type = _T; };
	template<typename _T> using RemoveConst = typename RemoveConst_<_T>::Type;

	template<typename _T>
	constexpr _T &&Forward(RemoveReference<_T> &value) { return static_cast<_T &&>(value); }

	template<typename _T>
	constexpr RemoveReference<_T> &&Move(_T &&value) { return static_cast<RemoveReference<_T> &&>(value); }

}