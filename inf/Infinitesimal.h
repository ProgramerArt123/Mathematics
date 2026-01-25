#ifndef __INF_INFINITESIMAL_H__
#define __INF_INFINITESIMAL_H__

#include "RatioInf.h"

namespace inf {
	class Infinitesimal : public RatioInf {
	public:
		Infinitesimal(const std::string &name = "o", const number::Fraction& degree = number::Integer(1));

		const std::string GetString(uint8_t radix = LITERAL_DEFAULT_RADIX) const override;

		bool IsEqual(const Symbol &other) const override;

		bool ExtendMulDiv(expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> &exp) override;
		
		std::shared_ptr<expression::Symbol> GetClone() const override;

		bool operator==(const Infinitesimal &other) const;

		Infinitesimal operator+(const Infinitesimal &addition) const;
		Infinitesimal &operator+=(const Infinitesimal &addition);
		Infinitesimal operator-(const Infinitesimal &subtrahend) const;
		Infinitesimal &operator-=(const Infinitesimal &subtrahend);
		number::Fraction operator/(const Infinitesimal &divisor) const;

		Infinitesimal operator*(const number::Fraction &multiplier) const;
		Infinitesimal operator/(const number::Fraction &divisor) const;

		const Infinitesimal &SetDegree(const number::Fraction &degree);
		
	public:

		static void SetIgnoreLine(const number::Fraction &ignore);

	private:

		bool Multiple(expression::Expression<expression::OPERATOR_TYPE_MUL_DIV>& exp);

	private:
		static number::Fraction ignore_line;
	};
}

#define SYMBOL_INFINITESIMAL expression::SymbolWrapper(std::make_shared<inf::Infinitesimal>("o"))

#endif