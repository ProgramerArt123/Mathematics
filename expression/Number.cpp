#include <sstream>
#include "number/Number.h"
#include "ClosureNumber.hpp"

namespace expression {
	
	Number::Number(const Number &prototype){
		*this = prototype;
	}
}