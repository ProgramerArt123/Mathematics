#ifndef __EXPRESSION_CLOSURE_NUMBER_HPP__
#define __EXPRESSION_CLOSURE_NUMBER_HPP__

#include "Number.h"
#include "number/Integer.h"
#include "number/Fraction.h"
#include "number/Complex.h"

namespace expression {
	class ClosureNumber : public Number {
	public:
		ClosureNumber(const expression::ClosureNumber &prototype);
		ClosureNumber(const expression::ClosureNumber &prototype, OPERATOR_TYPE_FLAG flag);
		ClosureNumber(const number::Integer &value, OPERATOR_TYPE_FLAG flag = OPERATOR_TYPE_FLAG_NONE);
		ClosureNumber(const number::Fraction &value, OPERATOR_TYPE_FLAG flag = OPERATOR_TYPE_FLAG_NONE);
		ClosureNumber(const number::Complex &value, OPERATOR_TYPE_FLAG flag = OPERATOR_TYPE_FLAG_NONE);
		const std::string GetString(size_t pos = 0, uint8_t radix = 10) const override;
		const ClosureNumber &operator=(const ClosureNumber &right);
		ClosureNumber operator+(const ClosureNumber &addition) const;
		ClosureNumber operator-(const ClosureNumber &subtrahend) const;
		ClosureNumber operator*(const ClosureNumber &multiplier) const;
		ClosureNumber operator/(const ClosureNumber &divisor) const;
		ClosureNumber &operator+=(const ClosureNumber &addition);
		ClosureNumber &operator-=(const ClosureNumber &subtrahend);
		ClosureNumber &operator*=(const ClosureNumber &multiplier);
		ClosureNumber &operator/=(const ClosureNumber &divisor);
	private:
		number::Complex m_value;
	};
}

#endif