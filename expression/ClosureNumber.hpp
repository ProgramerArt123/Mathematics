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
		
		const std::string GetString(uint8_t radix = LITERAL_DEFAULT_RADIX) const override;

		bool IsEqual(const Node &other, bool ignoreSigned = false, bool ignoreOperator = false) const override;
		bool EqualZero() const override;
		bool EqualPositiveOne() const override;
		bool EqualNegativeOne() const override;
		bool IsDisplaySigned() const override;

		size_t AddSubSigned() override;
		size_t MulDivSigned() override;

		void Opposite() override;

		void SetOperator(OPERATOR_TYPE_FLAG flag) override;

		std::optional<bool> Compare(const ClosureNumber &other) const;

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