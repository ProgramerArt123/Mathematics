#ifndef __EXPRESSION_INTEGER_H__
#define __EXPRESSION_INTEGER_H__

#include "Number.h"
#include "number/Integer.h"

namespace expression {
	class Integer : public Number {
	public:
		Integer(const number::Integer &value);
	};
}

#endif