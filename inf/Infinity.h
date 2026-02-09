#ifndef __INF_INFINITY_H__
#define __INF_INFINITY_H__

#include "RatioInf.h"

#include "number/Fraction.h"

#include "Infinitesimal.h"

#define INFINITY_NAME "oo"

namespace expression {
	template<typename OperatorType>
	class Expression;
}

namespace inf {
	class Infinity : public RatioInf {
	public:
		Infinity(const number::Fraction& degree = number::Integer(1));
	
		const std::string GetString(uint8_t radix = LITERAL_DEFAULT_RADIX) const override;

		bool IsEqual(const Symbol& other) const override;

		bool ExtendMulDiv(expression::Expression<expression::OPERATOR_TYPE_MUL_DIV>& exp) override;

		bool ExtendPowerRoot(expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT>& exp) override;

		std::shared_ptr<expression::Symbol> GetClone() const override;

		const Infinity& operator=(const Infinity& right);

		bool operator==(const Infinity& other) const;

		Infinity operator+(const Infinity& addition) const;
		Infinity& operator+=(const Infinity& addition);
		Infinity operator-(const Infinity& subtrahend) const;
		Infinity& operator-=(const Infinity& subtrahend);
		number::Fraction operator/(const Infinity& divisor) const;

		Infinity operator*(const number::Fraction& multiplicand) const;
		Infinity operator/(const number::Fraction& divisor) const;

		friend number::Fraction operator*(const Infinitesimal &multiplier, const Infinity &multiplicand);
		friend number::Fraction operator*(const Infinity& multiplier, const Infinitesimal& multiplicand);

		const Infinity& SetDegree(const number::Fraction& degree);

	private:

		bool Transform(expression::Expression<expression::OPERATOR_TYPE_MUL_DIV>& exp);

		bool Multiple(expression::Expression<expression::OPERATOR_TYPE_MUL_DIV>& exp);

		bool Infinitesimal(expression::Expression<expression::OPERATOR_TYPE_MUL_DIV>& exp);

		bool Transform(expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT>& exp);

		bool Multiple(expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT>& exp);

		bool Infinitesimal(expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT>& exp);

	};
}

#endif