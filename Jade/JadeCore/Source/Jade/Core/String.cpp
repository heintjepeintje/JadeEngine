#include "String.hpp"

namespace Jade {

	Char ToChar(WideChar wide) {
		if (wide >= L'\0' && wide <= L'~') return static_cast<Char>(wide);
		return '\0';
	}

	WideChar ToWideChar(Char character) {
		if (character >= '\0' && character <= '~') return static_cast<Char>(character);
		return L'\0';
	}

	String ToString(const WideString &wide) {
		if (wide.GetData() == nullptr || wide.GetLength() == 0) return String();

		String result;
		result.Resize(wide.GetLength());
		
		for (Size i = 0; i < wide.GetLength(); i++) {
			result[i] = ToChar(wide[i]);
		}
		
		return result;
	}

	WideString ToWideString(const String &string) {
		if (string.GetData() == nullptr || string.GetLength() == 0) return WideString();

		WideString result;
		result.Resize(string.GetLength());

		for (Size i = 0; i < string.GetLength(); i++) {
			result[i] = ToWideChar(string[i]);
		}

		return result;
	}

	Size CountDigits(UInt64 value) {
		if (value == 0) return 1;

		Size count = 0;
		while (value > 0) {
			value /= 10;
			count++;
		}

		return count;
	}

	void FormatUnsigned(Char *output, UInt64 value, Size digitCount) {
		Size i = 0;

		while (value >= 10) {
			output[digitCount - i - 1] = (value % 10) + '0';
			value /= 10;
			i++;
		}

		output[0] = value + '0';
	}

	String UInt32ToString(UInt32 value) {
		Size digitCount = CountDigits(value);
		String result(digitCount);
		
		FormatUnsigned(result.GetData(), value, digitCount);

		return result;
	}

	String UInt64ToString(UInt64 value) {
		Size digitCount = CountDigits(value);
		String result(digitCount);
		
		FormatUnsigned(result.GetData(), value, digitCount);

		return result;
	}

	String Int32ToString(Int32 value) {
		UInt32 unsignedValue = value < 0 ? -value : value;
		Size digitCount = CountDigits(unsignedValue);

		Bool8 isNegative = value < 0;

		String result(digitCount + (value < 0 ? 1 : 0));
		FormatUnsigned(
			OffsetPointer(result.GetData(), (isNegative ? 1 : 0) * sizeof(Char)), 
			unsignedValue, 
			digitCount
		);

		if (isNegative) result[0] = '-';

		return result;
	}

	String Int64ToString(Int64 value) {
		UInt64 unsignedValue = value < 0 ? -value : value;
		Size digitCount = CountDigits(unsignedValue);

		Bool8 isNegative = value < 0;

		String result(digitCount + (value < 0 ? 1 : 0));
		FormatUnsigned(
			OffsetPointer(result.GetData(), (isNegative ? 1 : 0) * sizeof(Char)), 
			unsignedValue,
			digitCount
		);

		if (isNegative) result[0] = '-';

		return result;
	}

	String Float32ToString(Float32 value, UInt32 places) {
		Int32 integerPart = static_cast<Int32>(value);
		Float32 fractionalPart = value - static_cast<Float32>(integerPart);

		String result = Int32ToString(integerPart);
		Size digitCount = result.GetLength();

		if (places > 0) {
			result.Resize(digitCount + 1 + places, '0');

			result[digitCount] = '.';

			fractionalPart *= static_cast<Float32>(__builtin_powif(10, places));
			UInt32 fractionalValue = static_cast<UInt32>(fractionalPart);
			FormatUnsigned(
				OffsetPointer(result.GetData(), (digitCount + 1) * sizeof(Char)), 
				fractionalValue,
				places
			);
		}

		return result;
	}

	String Float64ToString(Float64 value, UInt32 places) {
		Int32 integerPart = static_cast<Int32>(value);
		Float64 fractionalPart = value - static_cast<Float64>(integerPart);

		String result = Int32ToString(integerPart);
		Size digitCount = result.GetLength();

		if (places > 0) {
			result.Resize(digitCount + 1 + places, '0');

			result[digitCount] = '.';

			fractionalPart *= static_cast<Float64>(__builtin_powi(10, places));
			UInt32 fractionalValue = static_cast<UInt32>(fractionalPart);
			FormatUnsigned(
				OffsetPointer(result.GetData(), (digitCount + 1) * sizeof(Char)), 
				fractionalValue,
				places
			);
		}

		return result;
	}

}