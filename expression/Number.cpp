#include <sstream>
#include "number/Number.h"
#include "ClosureNumber.hpp"

namespace expression {
	Number::Number(OPERATOR_TYPE_FLAG flag): Atom(flag) {
	}
	Number::Number(const Number &prototype){
		*this = prototype;
	}
	const Number &Number::operator=(const Number &right) {
		Atom::operator=(right);
		return *this;
	}
}