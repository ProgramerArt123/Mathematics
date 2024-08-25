#ifndef __ROOT_H__
#define __ROOT_H__

#include "Number.h"
#include "Integer.h"
#include "Fraction.h"

namespace number {
	class Complex;

	class Root : public Number {
	public:
		Root();
		Root(const Integer &power, const Integer &exponent, bool positive = true);
		Root(const Integer &power, const Fraction &exponent, bool positive = true);
		Root(const Fraction &power, const Integer &exponent, bool positive = true);
		Root(const Fraction &power, const Fraction &exponent, bool positive = true);

		const std::string GetString(uint8_t radix = 10) const override;
		void SetRadix(uint8_t radix = 10) override;
		uint8_t GetRadix() const override;
		bool EqualZero() const override;
		bool EqualOne() const override;
		void SetPositive(bool isPositive) override;
		bool IsPositive() const override;
		const std::string GetDecimal(uint8_t radix, size_t decimalLength,
			std::function<bool(char)> round = [](char last) {return false; }) const override;

		Root operator-() const;
		bool operator==(const Root &other) const;

		const Fraction &Power()const;
		const Fraction &Exponent()const;
		const Fraction &ReductionCoefficient()const;
		const Fraction &ReductionPower()const;

		bool IsFraction() const;
		bool IsImaginary() const;
		Fraction GetFraction(const Integer &base, uint8_t radix, size_t decimalLength)const;

		bool EqualPower0(const Root &right) const;
		bool EqualPower1(const Root &right) const;
		Root AddEqual(const number::Root &right) const;
		Root MulEqual(const number::Root &right, bool isLeftMul, bool isRightMul) const;

		void Opposite();

		friend Root Power(const Fraction &base, const Fraction &exponent);

	private:

		bool m_positive = true;

		Fraction m_power;
		Fraction m_exponent;

		Fraction m_reduction_coefficient;
		Fraction m_reduction_power;

		void Reduce();
	};
}
#endif