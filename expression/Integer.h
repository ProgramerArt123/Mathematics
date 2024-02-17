#ifndef __EXPRESSION_INTEGER_H__
#define __EXPRESSION_INTEGER_H__

#include "Number.h"
#include "number/Integer.h"
#include "Operator.h"

namespace expression {
	class Integer : public Number {
	public:
		Integer(const number::Integer &value);

		const std::string OutPutString(size_t pos = 0) const override;

		number::Integer m_value;
	};
}

#endif