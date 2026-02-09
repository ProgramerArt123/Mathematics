#ifndef __INF_INFINITESIMAL_H__
#define __INF_INFINITESIMAL_H__

#include "RatioInf.h"

#define INFINITESIMAL_NAME "o"

namespace inf {
	class Infinitesimal : public RatioInf {
	public:
		Infinitesimal(const number::Fraction& degree = number::Integer(1));

		const std::string GetString(uint8_t radix = LITERAL_DEFAULT_RADIX) const override;

		bool IsEqual(const Symbol &other) const override;

		bool ExtendMulDiv(expression::Expression<expression::OPERATOR_TYPE_MUL_DIV> &exp) override;

		bool ExtendPowerRoot(expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT>& exp) override;
		
		std::shared_ptr<expression::Symbol> GetClone() const override;

		const Infinitesimal& operator=(const Infinitesimal& right);

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

		bool Transform(expression::Expression<expression::OPERATOR_TYPE_MUL_DIV>& exp);

		bool Multiple(expression::Expression<expression::OPERATOR_TYPE_MUL_DIV>& exp);

		bool Transform(expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT>& exp);

		bool Multiple(expression::Expression<expression::OPERATOR_TYPE_POWER_ROOT>& exp);

	private:
		static number::Fraction ignore_line;
	};
}

#endif