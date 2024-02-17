#ifndef __EXPRESSION_FRACTION_H__
#define __EXPRESSION_FRACTION_H__

#include "Number.h"
#include "number/Fraction.h"
#include "Operator.h"

namespace expression {
	class Fraction : public Number {
	public:
		Fraction(const number::Fraction &value);

		const std::string OutPutString(size_t pos = 0) const override;

		number::Fraction m_value;
	};
}

#endif