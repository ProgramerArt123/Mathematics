#include "Output.h"


const std::string Output::GetStringRadix(uint8_t radix) const {
	return GetString(radix) + "[radix=" + std::to_string(radix) + "]";
}

const std::string Output::GetDecimalRadix(uint8_t radix, size_t decimalLength,
	std::function<bool(char)> round)const {
	return GetDecimal(radix, decimalLength, round) + "[radix=" + std::to_string(radix) + "]";
}
