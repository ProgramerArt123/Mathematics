#include "Number.h"

const std::string Number::GetStringRadix(uint8_t radix) const {
	return GetString(radix) +"[radix=" + std::to_string(radix) + "]";
}

const std::string Number::GetDecimalRadix(uint8_t radix, size_t decimalLength,
	std::function<bool(char)> round)const {
	return GetDecimal(radix, decimalLength, round) + "[radix=" + std::to_string(radix) + "]";
}

std::ostream& operator<<(std::ostream& out, const Number &number) {
	out << number.GetStringRadix().c_str();
	return out;
}