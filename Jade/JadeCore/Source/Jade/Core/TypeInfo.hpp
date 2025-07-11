#pragma once

#include <Jade/Core/Core.hpp>
#include <string>

#define JD_TEMPLATE_BOOL_TRUE { static constexpr ::Jade::Bool8 Value = true; }
#define JD_TEMPLATE_BOOL_FALSE { static constexpr ::Jade::Bool8 Value = false; }

#define JD_TEMPLATE_HAS_TYPE(type) { using Type = type; };

namespace Jade {
	
	template<Bool8 _Eval, typename _If, typename _Else> struct IfElseType { };
	template<typename _If, typename _Else> struct IfElseType<true, _If, _Else> JD_TEMPLATE_HAS_TYPE(_If);
	template<typename _If, typename _Else> struct IfElseType<false, _If, _Else> JD_TEMPLATE_HAS_TYPE(_Else);

	template<typename _Type> struct RemoveReference JD_TEMPLATE_HAS_TYPE(_Type);
	template<typename _Type> struct RemoveReference<_Type &> JD_TEMPLATE_HAS_TYPE(_Type);
	template<typename _Type> class RemoveReference<_Type &&> JD_TEMPLATE_HAS_TYPE(_Type);
	template<typename _Type> using RemoveReferenceT = RemoveReference<_Type>::Type;
	
	template<typename _Type> struct RemoveConst JD_TEMPLATE_HAS_TYPE(_Type);
	template<typename _Type> struct RemoveConst<_Type const> JD_TEMPLATE_HAS_TYPE(_Type);
	template<typename _Type> using RemoveConstT = RemoveConst<_Type>::Type;
	
	template<typename _Type> struct RemoveVolatile JD_TEMPLATE_HAS_TYPE(_Type);
	template<typename _Type> struct RemoveVolatile<volatile _Type> JD_TEMPLATE_HAS_TYPE(_Type);
	template<typename _Type> using RemoveVolatileT = RemoveVolatile<_Type>::Type;
	
	template<typename _Type> struct RemovePointer JD_TEMPLATE_HAS_TYPE(_Type);
	template<typename _Type> struct RemovePointer<_Type*> JD_TEMPLATE_HAS_TYPE(_Type);
	template<typename _Type> struct RemovePointer<_Type *const> JD_TEMPLATE_HAS_TYPE(_Type);
	template<typename _Type> struct RemovePointer<_Type *volatile> JD_TEMPLATE_HAS_TYPE(_Type);
	template<typename _Type> struct RemovePointer<_Type *const volatile> JD_TEMPLATE_HAS_TYPE(_Type);
	template<typename _Type> using RemovePointerT = RemovePointer<_Type>::Type;

	template<typename _Type> struct IsVoidType JD_TEMPLATE_BOOL_FALSE;
	template<> struct IsVoidType<void> JD_TEMPLATE_BOOL_TRUE;
	template<typename _Type> constexpr Bool8 IsVoidTypeV() { return IsVoidType<_Type>::Value; }
	
	template<typename _Type> struct IsArrayType JD_TEMPLATE_BOOL_FALSE;
	template<typename _Type> struct IsArrayType<_Type[]> JD_TEMPLATE_BOOL_TRUE;
	template<typename _Type, Size _Count> struct IsArrayType<_Type[_Count]> JD_TEMPLATE_BOOL_TRUE;
	template<typename _Type> constexpr Bool8 IsArrayTypeV() { return IsArrayType<_Type>::Value; }

	template<typename _Type> struct IsConstType JD_TEMPLATE_BOOL_FALSE;
	template<typename _Type> struct IsConstType<const _Type> JD_TEMPLATE_BOOL_TRUE;
	template<typename _Type> constexpr Bool8 IsConstTypeV() { return IsConstType<_Type>::Value; }
	
	template<typename _Type> struct IsPointerType JD_TEMPLATE_BOOL_FALSE;
	template<typename _Type> struct IsPointerType<_Type *> JD_TEMPLATE_BOOL_TRUE;
	template<typename _Type> constexpr Bool8 IsPointerTypeV() { return IsPointerType<_Type>::Value; }
	
	template<typename _A, typename _B> struct IsSameType JD_TEMPLATE_BOOL_FALSE;
	template<typename _Type> struct IsSameType<_Type, _Type> JD_TEMPLATE_BOOL_TRUE;
	template<typename _A, typename _B> constexpr Bool8 IsSameTypeV() { return IsSameType<_A, _B>::Value; }
	
	template<typename _Type> struct IsNumericType JD_TEMPLATE_BOOL_FALSE;
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
	template<typename _Type> constexpr Bool8 IsNumericTypeV() { return IsNumericType<_Type>::Value; }

	template<typename _Type> struct IsSignedType JD_TEMPLATE_BOOL_FALSE;
	template<> struct IsSignedType<char> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsSignedType<short> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsSignedType<int> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsSignedType<long> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsSignedType<long long> JD_TEMPLATE_BOOL_TRUE;
	template<typename _Type> constexpr Bool8 IsSignedTypeV() { return IsSignedType<_Type>::Value; }

	template<typename _Type> struct IsUnsignedType JD_TEMPLATE_BOOL_FALSE;
	template<> struct IsUnsignedType<unsigned char> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsUnsignedType<unsigned short> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsUnsignedType<unsigned int> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsUnsignedType<unsigned long> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsUnsignedType<unsigned long long> JD_TEMPLATE_BOOL_TRUE;
	template<typename _Type> constexpr Bool8 IsUnsignedTypeV() { return IsUnsignedType<_Type>::Value; }
	
	template<typename _Type> struct IsFloatingPointType JD_TEMPLATE_BOOL_FALSE;
	template<> struct IsFloatingPointType<float> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsFloatingPointType<double> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsFloatingPointType<long double> JD_TEMPLATE_BOOL_TRUE;
	template<typename _Type> constexpr Bool8 IsFloatingPointTypeV() { return IsFloatingPointType<_Type>::Value; }
	
	template<typename _Type> struct IsCharType JD_TEMPLATE_BOOL_FALSE;
	template<> struct IsCharType<Char> JD_TEMPLATE_BOOL_TRUE;
	template<> struct IsCharType<WideChar> JD_TEMPLATE_BOOL_TRUE;
	template<typename _Type> constexpr Bool8 IsCharTypeV() { return IsCharType<_Type>::Value; }

	template<typename _Type>
	constexpr _Type &&Forward(RemoveReferenceT<_Type> &value) { return static_cast<_Type&&>(value); }

	template<typename _Type>
	constexpr RemoveReferenceT<_Type> &&Move(RemoveReferenceT<_Type> &&value) { return static_cast<RemoveReferenceT<_Type>&&>(value); }

}