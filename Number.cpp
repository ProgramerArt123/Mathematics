#include "Number.h"

std::ostream& operator<<(std::ostream& out, const Number &number) {
	out << number.GetStringRadix().c_str();
	return out;
}