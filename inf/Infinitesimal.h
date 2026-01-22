#ifndef __INF_INFINITESIMAL_H__
#define __INF_INFINITESIMAL_H__

#include "expression/Symbol.h"

#include "number/Fraction.h"
#include "number/Logarithm.h"

namespace inf {
	class Infinitesimal : public expression::Symbol {
	public:
		Infinitesimal(const std::string &name = "o", const number::Fraction& degree = number::Integer(1));

		const std::string GetString(uint8_t radix = LITERAL_DEFAULT_RADIX) const override;

		bool ExtendMulDiv(expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> &exp) override;
		
		std::shared_ptr<expression::Symbol> GetClone() const override;

		Infinitesimal operator+(const Infinitesimal &addition) const;
		Infinitesimal &operator+=(const Infinitesimal &addition);
		Infinitesimal operator-(const Infinitesimal &subtrahend) const;
		Infinitesimal &operator-=(const Infinitesimal &subtrahend);
		number::Fraction operator/(const Infinitesimal &divisor) const;

		number::Logarithm Logarithm(const Infinitesimal &base) const;

		Infinitesimal operator*(const number::Fraction &multiplier) const;
		Infinitesimal operator/(const number::Fraction &divisor) const;

		bool IsPositive() const;
		bool IsNegative() const;
		bool IsZero() const;

		bool IsLeft() const;
		bool IsRight() const;

		const Infinitesimal &SetDegree(const number::Fraction &degree);
		const number::Fraction &Degree() const;

	public:

		static void SetIgnoreLine(const number::Fraction &ignore);

	private:
		number::Fraction m_degree = number::Integer(1);
	
		static number::Fraction ignore_line;
	};
}

#define SYMBOL_INFINITESIMAL SymbolWrapper(std::make_shared<inf::Infinitesimal>("o"))

#endif