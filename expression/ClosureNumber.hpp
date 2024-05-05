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
		ClosureNumber(const number::Integer &value);
		ClosureNumber(const number::Fraction &value);
		ClosureNumber(const number::Complex &value);
		const std::string OutPutString(size_t pos = 0) const override;
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