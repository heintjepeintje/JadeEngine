#pragma once

#include <Jade/Core/Core.hpp>

#define JD_TEMPLATE_BOOL_TRUE { static constexpr ::Jade::Bool8 Value = true; }
#define JD_TEMPLATE_BOOL_FALSE { static constexpr ::Jade::Bool8 Value = false; }

#define JD_TEMPLATE_HAS_TYPE(type) { using Type = type; };

namespace Jade {
	
	template<Bool8 _Eval, typename _If, typename _Else> struct IfElseType { };
	template<typename _If, typename _Else> struct IfElseType<true, _If, _Else> JD_TEMPLATE_HAS_TYPE(_If);
	template<typename _If, typename _Else> struct IfElseType<false, _If, _Else> JD_TEMPLATE_HAS_TYPE(_Else);

	template<typename _T> struct RemoveReference JD_TEMPLATE_HAS_TYPE(_T);
	template<typename _T> struct RemoveReference<_T &> JD_TEMPLATE_HAS_TYPE(_T);
	template<typename _T> class RemoveReference<_T &&> JD_TEMPLATE_HAS_TYPE(_T);
	template<typename _T> using RemoveReferenceType = RemoveReference<_T>::Type;
	
	template<typename _T> struct RemoveConst JD_TEMPLATE_HAS_TYPE(_T);
	template<typename _T> struct RemoveConst<_T const> JD_TEMPLATE_HAS_TYPE(_T);
	template<typename _T> using RemoveConstType = RemoveConst<_T>::Type;
	
	template<typename _T> struct RemoveVolatile JD_TEMPLATE_HAS_TYPE(_T);
	template<typename _T> struct RemoveVolatile<volatile _T> JD_TEMPLATE_HAS_TYPE(_T);
	template<typename _T> using RemoveConstType = RemoveConst<_T>::Type; 
	
	template<typename _T> struct RemovePointer JD_TEMPLATE_HAS_TYPE(_T);
	template<typename _T> struct RemovePointer<_T*> JD_TEMPLATE_HAS_TYPE(_T);
	template<typename _T> struct RemovePointer<_T *const> JD_TEMPLATE_HAS_TYPE(_T);
	template<typename _T> struct RemovePointer<_T *volatile> JD_TEMPLATE_HAS_TYPE(_T);
	template<typename _T> struct RemovePointer<_T *const volatile> JD_TEMPLATE_HAS_TYPE(_T);
	template<typename _T> using RemovePointerType = RemovePointer<_T>::Type;

	template<typename _T> struct IsVoidType JD_TEMPLATE_BOOL_FALSE;
	template<> struct IsVoidType<void> JD_TEMPLATE_BOOL_TRUE;
	
	template<typename _T> struct IsArrayType JD_TEMPLATE_BOOL_FALSE;
	template<typename _T> struct IsArrayType<_T[]> JD_TEMPLATE_BOOL_TRUE;
	template<typename _T, Size _Count> struct IsArrayType<_T[_Count]> JD_TEMPLATE_BOOL_TRUE;

	template<typename _T> struct IsConstType JD_TEMPLATE_BOOL_FALSE;
	template<typename _T> struct IsConstType<const _T> JD_TEMPLATE_BOOL_TRUE;
	
	template<typename _T> struct IsPointerType JD_TEMPLATE_BOOL_FALSE;
	template<typename _T> struct IsPointerType<_T *> JD_TEMPLATE_BOOL_TRUE;
	
	template<typename _A, typename _B> struct IsSameType JD_TEMPLATE_BOOL_FALSE;
	template<typename _T> struct IsSameType<_T, _T> JD_TEMPLATE_BOOL_TRUE;
	
	template<typename _T> struct IsNumericType JD_TEMPLATE_BOOL_FALSE;
	template<> struct IsNumericType<char> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsNumericType<short> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsNumericType<int> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsNumericType<long> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsNumericType<long long> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsNumericType<unsigned char> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsNumericType<unsigned short> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsNumericType<unsigned int> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsNumericType<unsigned long> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsNumericType<unsigned long long> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsNumericType<float> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsNumericType<double> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsNumericType<long double> JD_TEMPLATE_BOOL_TRUE;

	template<typename _T> struct IsSignedType JD_TEMPLATE_BOOL_FALSE;
	template<> struct IsSignedType<char> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsSignedType<short> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsSignedType<int> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsSignedType<long> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsSignedType<long long> JD_TEMPLATE_BOOL_TRUE;

	template<typename _T> struct IsUnsignedType JD_TEMPLATE_BOOL_FALSE;
	template<> struct IsUnsignedType<unsigned char> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsUnsignedType<unsigned short> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsUnsignedType<unsigned int> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsUnsignedType<unsigned long> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsUnsignedType<unsigned long long> JD_TEMPLATE_BOOL_TRUE;
	
	template<typename _T> struct IsFloatingPointType JD_TEMPLATE_BOOL_FALSE;
	template<> struct IsFloatingPointType<float> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsFloatingPointType<double> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsFloatingPointType<long double> JD_TEMPLATE_BOOL_TRUE;
	
	template<typename _T> struct IsCharType JD_TEMPLATE_BOOL_FALSE;
	template<> struct IsCharType<Char> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsCharType<WideChar> JD_TEMPLATE_BOOL_TRUE;

	template<typename _T>
	constexpr _T &&Forward(RemoveReferenceType<_T> &value) { return static_cast<_T&&>(value); }

	template<typename _T>
	constexpr RemoveReferenceType<_T> &&Move(RemoveReferenceType<_T> &&value) { return static_cast<RemoveReferenceType<_T>&&>(value); }

}