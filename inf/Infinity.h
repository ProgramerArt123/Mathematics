#ifndef __INF_INFINITY_H__
#define __INF_INFINITY_H__

#include "RatioInf.h"

#include "number/Fraction.h"

namespace inf {
	class Infinity : public RatioInf {
	public:
		Infinity(const std::string& name = "oo", const number::Fraction& degree = number::Integer(1));
	
		const std::string GetString(uint8_t radix = LITERAL_DEFAULT_RADIX) const override;

		bool IsEqual(const Symbol& other) const override;

		bool ExtendMulDiv(expression::Expression<expression::OPERATOR_TYPE_MUL_DIV>& exp) override;

		std::shared_ptr<expression::Symbol> GetClone() const override;

		bool operator==(const Infinity& other) const;

		Infinity operator+(const Infinity& addition) const;
		Infinity& operator+=(const Infinity& addition);
		Infinity operator-(const Infinity& subtrahend) const;
		Infinity& operator-=(const Infinity& subtrahend);
		number::Fraction operator/(const Infinity& divisor) const;

		Infinity operator*(const number::Fraction& multiplier) const;
		Infinity operator/(const number::Fraction& divisor) const;

		const Infinity& SetDegree(const number::Fraction& degree);

	private:

		bool Closure(expression::Expression<expression::OPERATOR_TYPE_MUL_DIV>& exp);

		bool Multiple(expression::Expression<expression::OPERATOR_TYPE_MUL_DIV>& exp);

	
	};
}

#define SYMBOL_INFINITY expression::SymbolWrapper(std::make_shared<inf::Infinity>("oo"))

#endif