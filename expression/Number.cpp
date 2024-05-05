#include "number/Number.h"
#include "ClosureNumber.hpp"

namespace expression {
	Number::Number() {

	}
	Number::Number(const Number &prototype) {
		*this = prototype;
	}
	const Number &Number::operator=(const Number &right) {
		Node::operator=(right);
		return *this;
	}
}