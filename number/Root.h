#ifndef __ROOT_H__
#define __ROOT_H__

#include "Number.h"
namespace number {
	class Complex;

	class Root : public Number {
	public:
		Root(const Integer &base, const Integer &exponent, bool positive = true);
		Root(const Integer &base, const Fraction &exponent, bool positive = true);
		Root(const Fraction &base, const Fraction &exponent, bool positive = true);

		const std::string GetString(uint8_t radix = 10) const override;
		void SetRadix(uint8_t radix = 10) override;
		uint8_t GetRadix() const override;
		bool EqualZero() const override;
		void SetPositive(bool isPositive) override;
		bool IsPositive() const override;
		const std::string GetDecimal(uint8_t radix, size_t decimalLength,
			std::function<bool(char)> round = [](char last) {return false; }) const override;

		bool IsImaginary() const;
		Fraction GetFraction(const Integer &base, uint8_t radix, size_t decimalLength)const;

		friend Root operator*(const Root &number, const Integer &multiplier);
		friend Root operator/(const Root &number, const Integer &divisor);

		friend Root operator*(const Root &number, const Fraction &multiplier);
		friend Root operator/(const Root &number, const Fraction &divisor);

		Fraction m_base;
		Fraction m_exponent;
		bool m_positive = true;
	};
}
#endif