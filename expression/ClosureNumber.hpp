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
		ClosureNumber(const number::Integer &value, OPERATOR_TYPE_FLAG flag = OPERATOR_TYPE_FLAG_ADD);
		
		bool IsUnSigned() const override;

		const std::string GetString(size_t pos = 0, uint8_t radix = LITERAL_DEFAULT_RADIX) const override;

		bool IsEqual(const Node &other, bool ignoreOperator = false) const override;
		bool EqualZero() const override;
		bool EqualPositiveOne() const override;
		bool EqualNegativeOne() const override;

		void Opposite() override;

		const number::Integer &Value() const;
		
		const ClosureNumber &operator=(const ClosureNumber &right);
		bool operator==(const ClosureNumber &other) const;
		ClosureNumber operator+(const ClosureNumber &addition) const;
		ClosureNumber operator-(const ClosureNumber &subtrahend) const;
		ClosureNumber operator*(const ClosureNumber &multiplier) const;
		ClosureNumber operator/(const ClosureNumber &divisor) const;

		ClosureNumber &operator+=(const ClosureNumber &addition);
		ClosureNumber &operator-=(const ClosureNumber &subtrahend);
		ClosureNumber &operator*=(const ClosureNumber &multiplier);
		ClosureNumber &operator/=(const ClosureNumber &divisor);
						
	private:
		number::Integer m_value;

	};
}

#endif