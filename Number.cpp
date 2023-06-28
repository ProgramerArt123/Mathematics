#include "Number.h"

std::ostream& operator<<(std::ostream& out, const Number &number) {
	out << number.GetString().c_str();
	return out;
}