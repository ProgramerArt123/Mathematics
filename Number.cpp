#include "Number.h"

const std::string Number::GetStringBase(uint8_t base) const {
	return GetString(base) +"[base=" + std::to_string(base) + "]";
}

std::ostream& operator<<(std::ostream& out, const Number &number) {
	out << number.GetStringBase().c_str();
	return out;
}