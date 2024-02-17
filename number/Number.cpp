#include "Number.h"

namespace number {

	const std::string Number::OutPutString(size_t pos) const {
		return GetString();
	}

	const std::string Number::GetStringRadix(uint8_t radix) const {
		return GetString(radix) + "[radix=" + std::to_string(radix) + "]";
	}

	const std::string Number::GetDecimalRadix(uint8_t radix, size_t decimalLength,
		std::function<bool(char)> round)const {
		return GetDecimal(radix, decimalLength, round) + "[radix=" + std::to_string(radix) + "]";
	}

}

